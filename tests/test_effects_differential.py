#!/usr/bin/env python3
"""Execute original animation bodies and a bounded explosion phase of its frame."""
import argparse
import ctypes as C
import hashlib
import json
from pathlib import Path
import struct
import subprocess

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX
from target_oracle import ROOT, TILES, AUX, MODE, ACTIVE_SURFACE
from test_gameplay_differential import (
    GameNative, GameTarget, Node, Ops, Allocate, REMAINING, HARD, REDUCED,
    PENDING, SCORE, LIST, signed,
)

FX_LIST, HIT_DX, HIT_DY, FX_SURFACE = 0x43FA98, 0x43A8A8, 0x43A8AC, 0x42E690


class EffectNode(C.Structure):
    pass


EffectNode._fields_ = [(name, C.c_int32) for name in ("kind", "sprite", "x", "y")] + [
    ("tile", C.c_uint8)] + [(name, C.c_int32) for name in ("frames", "period", "ticks")] + [
    ("next", C.POINTER(EffectNode)), ("previous", C.POINTER(EffectNode))]


class EffectList(C.Structure):
    _fields_ = [(name, C.POINTER(EffectNode)) for name in ("current", "first", "last")]


Free = C.CFUNCTYPE(None, C.c_void_p)
Bonus = C.CFUNCTYPE(None, *([C.c_int32] * 4))
Sprite = C.CFUNCTYPE(None, *([C.c_int32] * 3))
Region = C.CFUNCTYPE(None, *([C.c_int32] * 4))


class EffectOps(C.Structure):
    _fields_ = [("deallocate_node", Free), ("bonus", Bonus), ("keyed_sprite", Sprite),
                ("reduced_sprite", Sprite), ("region", Region)]


class EffectsNative(GameNative):
    def __init__(self, library):
        super().__init__(library)
        self.fx = EffectList.in_dll(self.lib, "dxball_brick_effects")
        self.hit_dx = C.c_int32.in_dll(self.lib, "dxball_hit_dx")
        self.hit_dy = C.c_int32.in_dll(self.lib, "dxball_hit_dy")
        C.c_size_t.in_dll(self.lib, "dxball_effect_surface").value = 0x334455
        self.allocations = {}
        self.effect_callbacks = (
            Free(self.free), Bonus(lambda *a: self.events.append(("bonus", *a))),
            Sprite(lambda *a: self.events.append(("keyed-sprite", *a))),
            Sprite(lambda *a: self.events.append(("reduced-sprite", *a))),
            Region(lambda *a: self.events.append(("region", *a))))
        for (name, _), callback in zip(EffectOps._fields_, self.effect_callbacks):
            setattr(EffectOps.in_dll(self.lib, "dxball_effect_ops"), name, callback)
        for name in ("begin_brick_effects", "advance_brick_effect", "append_brick_effect", "remove_brick_effect"):
            function = getattr(self.lib, "dxball_" + name)
            function.argtypes, function.restype = [C.POINTER(EffectList)], C.c_int32
        for name, args in [("spawn_explosion_effect", [C.c_int32] * 2),
                           ("spawn_brick_effect", [C.c_int32, C.c_int32, C.c_uint8, C.c_int32]),
                           ("step_explosion_effect", []), ("step_brick_effect", []),
                           ("process_brick_effects", []), ("apply_explosion_requests", [])]:
            function = getattr(self.lib, "dxball_" + name)
            function.argtypes, function.restype = args, None
        # Execute the maintained brick constructor when actual hit logic calls it.
        pointer = C.cast(self.lib.dxball_spawn_brick_effect, C.c_void_p).value
        C.c_void_p.from_address(C.addressof(Ops.in_dll(self.lib, "dxball_gameplay_ops")) + C.sizeof(C.c_void_p)).value = pointer

    def allocate(self, size):
        assert size in (C.sizeof(Node), C.sizeof(EffectNode))
        is_fx = size == C.sizeof(EffectNode)
        buffer = C.create_string_buffer(b"\xa5" * size, size)
        self.buffers.append(buffer)
        address = C.addressof(buffer)
        self.allocations[address] = (is_fx, True)
        self.events.append(("allocate-effect" if is_fx else "allocate-node", self.observed()))
        return address

    def free(self, address):
        is_fx, live = self.allocations[address]
        assert live, "native double deletion"
        if is_fx:
            self.events.append(("free-effect", C.string_at(address, 32).hex()))
        else:
            self.events.append(("free-node", *struct.unpack("<3i", C.string_at(address, 12))))
        self.allocations[address] = (is_fx, False)
        C.memset(address, 0xDD, C.sizeof(EffectNode) if is_fx else C.sizeof(Node))

    def reset(self):
        self.reset_list()
        self.fx.current = self.fx.first = self.fx.last = C.POINTER(EffectNode)()
        self.allocations.clear()

    def fx_state(self):
        nodes, addresses = [], []
        pointer, previous = self.fx.first, None
        while pointer:
            address = C.cast(pointer, C.c_void_p).value
            assert address not in addresses and self.allocations[address] == (True, True)
            assert C.cast(pointer.contents.previous, C.c_void_p).value == previous
            addresses.append(address)
            nodes.append(C.string_at(address, 32).hex())
            previous, pointer = address, pointer.contents.next
        assert C.cast(self.fx.last, C.c_void_p).value == previous
        current = C.cast(self.fx.current, C.c_void_p).value
        return nodes, addresses.index(current) if current else None


class EffectsTarget(GameTarget):
    def __init__(self):
        super().__init__()
        self.allocations = {}
        self.write_u32(FX_SURFACE, 0x334455)
        for address, name, count in [(0x4138D0, "bonus", 4), (0x404040, "keyed-sprite", 3),
                                     (0x4085D0, "reduced-sprite", 3), (0x408A50, "region", 4)]:
            def callback(*unused, name=name, count=count):
                self.events.append((name, *(signed(x) for x in self._args(count))))
                self._return()
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE, callback, begin=address, end=address))

    def effect(self, *unused):
        pass  # Keep the original 0x412BA0 body executing.

    def allocate(self, *unused):
        size = self._args(1)[0]
        assert size in (20, 40)
        self.events.append(("allocate-effect" if size == 40 else "allocate-node", self.observed()))
        if self.fail_allocation:
            self._return(0)
            return
        assert self.used + size <= 0x10000
        address = self.HEAP + self.used
        self.used += size
        self.allocations[address] = (size == 40, True)
        self.write(address, b"\xa5" * size)
        self._return(address)

    def free(self, *unused):
        address = self._args(1)[0]
        is_fx, live = self.allocations[address]
        assert live, "target double deletion"
        if is_fx:
            self.events.append(("free-effect", self.read(address, 32).hex()))
        else:
            self.events.append(("free-node", *struct.unpack("<3i", self.read(address, 12))))
        self.allocations[address] = (is_fx, False)
        self.write(address, b"\xdd" * (40 if is_fx else 20))
        self._return()

    def reset(self):
        self.reset_list()
        self.write(FX_LIST, bytes(12))
        self.allocations.clear()

    def fx_state(self):
        current, first, last = struct.unpack("<3I", self.read(FX_LIST, 12))
        nodes, addresses, previous, address = [], [], 0, first
        while address:
            assert address not in addresses and self.allocations[address] == (True, True)
            following, preceding = struct.unpack("<2I", self.read(address + 32, 8))
            assert preceding == previous
            addresses.append(address)
            nodes.append(self.read(address, 32).hex())
            previous, address = address, following
        assert last == previous
        return nodes, addresses.index(current) if current else None

    def neutralize_other_frame_phases(self):
        # These controlled dependencies are outside this phase's equivalence claim.
        for address in (0x415880, 0x412DF0, 0x410770, 0x413170, 0x413E20, 0x414A00,
                        0x408CC0, 0x410130, 0x413710, 0x412EC0, 0x4100F0, 0x414740,
                        0x414CB0, 0x416370, 0x409040, 0x4034F0, 0x415DF0):
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE, lambda *unused: self._return(),
                                               begin=address, end=address))
        for address in (0x43FAE4, 0x4228D0, 0x43FAEC, 0x43A8D8, 0x43A864,
                        0x43FAE8, 0x43A910, 0x43FAF4, 0x438B10):
            self.write_u32(address, 0)


def main():
    if not __debug__:
        raise SystemExit("run without -O; oracle assertions must stay enabled")
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--library", type=Path, default=ROOT / "build/native/libdxball_core.so")
    args = parser.parse_args()
    native, target = EffectsNative(args.library), EffectsTarget()
    cases = {name: 0 for name in ("begin_brick_effects", "advance_brick_effect",
             "append_brick_effect", "remove_brick_effect", "spawn_explosion_effect",
             "spawn_brick_effect", "step_explosion_effect", "step_brick_effect", "process_brick_effects")}
    integration_cases = 0
    hit_integration_cases = 0

    def seed(tile=8, mode=0, reduced=0, pending=0):
        native.reset()
        target.reset()
        native.tiles[:] = bytes([tile]) * 400
        target.write(TILES, bytes(native.tiles))
        native.aux[:] = bytes(400)
        target.write(AUX, bytes(400))
        native.cell = target.cell = 85
        native.cursor = target.cursor = 0
        native.mode.value = mode
        target.write_u32(MODE, mode)
        native.active.value = 0xAA
        target.write_u32(ACTIVE_SURFACE, 0xAA)
        native.hit_dx.value, native.hit_dy.value = -3, 7
        target.write_u32(HIT_DX, -3)
        target.write_u32(HIT_DY, 7)
        for address, value in [(REMAINING, 200), (HARD, 0), (REDUCED, reduced),
                               (PENDING, pending), (SCORE, 1234)]:
            native.state[address].value = value
            target.write_u32(address, value)

    def compare(context):
        assert bytes(native.tiles) == target.read(TILES, 400), (context, "tiles")
        assert bytes(native.aux) == target.read(AUX, 400), (context, "busy grid")
        assert native.fx_state() == target.fx_state(), (context, "effect list", native.fx_state(), target.fx_state())
        assert native.list_state() == target.list_state(), (context, "request list")
        assert native.events == target.events, (context, native.events, target.events)
        assert native.cursor == target.cursor, (context, "RNG cursor")
        assert native.active.value == target.read_u32(ACTIVE_SURFACE), (context, "surface")
        for address, value in native.state.items():
            assert value.value == signed(target.read_u32(address)), (context, hex(address))

    def call(name, address, *values, fastcall=False):
        target.uc.reg_write(UC_X86_REG_ECX, FX_LIST)
        result = target.call(address, *values)
        host = native.call("dxball_" + name, C.byref(native.fx)) if fastcall else native.call("dxball_" + name, *values)
        if fastcall:
            assert host == result, (name, "full EAX")
        compare((name, values))
        cases[name] += 1

    seed()
    for i in range(128):
        call("append_brick_effect", 0x412690, fastcall=True)
        assert C.string_at(C.cast(native.fx.current, C.c_void_p).value, 32) == b"\xa5" * 32
        native.fx.current = native.fx.first
        target.write_u32(FX_LIST, target.read_u32(FX_LIST + 4))
    target.fail_allocation = True
    target.uc.reg_write(UC_X86_REG_ECX, FX_LIST)
    try:
        target.call(0x412690)
        raise AssertionError("allocation failure returned")
    except AssertionError as error:
        assert str(error) == "instruction limit reached" and target.exit_status == 1
    child = '''import ctypes as C, sys
lib = C.CDLL(sys.argv[1])
callback = C.CFUNCTYPE(C.c_void_p, C.c_size_t)(lambda size: None)
C.c_void_p.in_dll(lib, "dxball_gameplay_ops").value = C.cast(callback, C.c_void_p).value
owner = (C.c_void_p * 3)()
lib.dxball_append_brick_effect(C.byref(owner))
'''
    assert subprocess.run([ROOT / "scripts/repo-python", "-c", child, args.library.resolve()]).returncode == 1
    target.fail_allocation = False
    cases["append_brick_effect"] += 1

    for name, address in [("begin_brick_effects", 0x4100B0), ("advance_brick_effect", 0x412590),
                          ("remove_brick_effect", 0x412A50)]:
        for length in range(9):
            for current in [None, *range(length)]:
                seed()
                host_nodes, target_nodes = [], []
                for index in range(length):
                    native.call("dxball_spawn_explosion_effect", index, 0)
                    target.call(0x4125F0, index, 0)
                    host_nodes.append(C.cast(C.cast(native.fx.current, C.c_void_p).value, C.POINTER(EffectNode)))
                    target_nodes.append(target.read_u32(FX_LIST))
                native.fx.current = host_nodes[current] if current is not None else C.POINTER(EffectNode)()
                target.write_u32(FX_LIST, target_nodes[current] if current is not None else 0)
                call(name, address, fastcall=True)

    for y in range(20):
        for x in range(20):
            seed()
            call("spawn_explosion_effect", 0x4125F0, x, y)
    for tile in range(256):
        for mode in (0, 1, -1):
            for x, y in ((0, 0), (19, 19), (5, 4)):
                seed()
                call("spawn_brick_effect", 0x412BA0, x, y, tile, mode)

    positions = ((0, 0), (19, 0), (0, 19), (19, 19), (5, 4))
    # Timer boundaries, center clear/count rules, exact neighbor order and edges.
    for kind, name, address in [(1, "step_explosion_effect", 0x412730), (2, "step_brick_effect", 0x412CB0)]:
        for frames in range(9):
            for period, ticks in ((0, -2), (0, 0), (1, 0), (2, 0), (2, 1), (2, 2)):
                for tile in (0, 2, 7, 8, 22, 255):
                    for reduced in (0, 1, -1):
                        for x, y in positions:
                            seed(tile, mode=reduced == 1, reduced=reduced)
                            if kind == 1:
                                native.call("dxball_spawn_explosion_effect", x, y)
                                target.call(0x4125F0, x, y)
                            else:
                                native.call("dxball_spawn_brick_effect", x, y, tile, 1)
                                target.call(0x412BA0, x, y, tile, 1)
                            for field, offset, value in (("frames", 20, frames), ("period", 24, period), ("ticks", 28, ticks)):
                                setattr(native.fx.current.contents, field, value)
                                target.write_u32(target.read_u32(FX_LIST) + offset, value)
                            # Alternating empty neighbors test enqueue filtering.
                            for cell in range(0, 400, 2):
                                if cell != x + y * 20:
                                    native.tiles[cell] = 0
                                    target.write(TILES + cell, b"\0")
                            call(name, address)

    # Run mixed queues until completion; deletion must skip its immediate successor.
    for length in range(9):
        for reduced in (0, 1):
            seed(reduced=reduced)
            for index in range(length):
                if index % 2:
                    native.call("dxball_spawn_brick_effect", index, 0, 8, 1)
                    target.call(0x412BA0, index, 0, 8, 1)
                else:
                    native.call("dxball_spawn_explosion_effect", index, 0)
                    target.call(0x4125F0, index, 0)
            for frame in range(16):
                call("process_brick_effects", 0x412510)
            assert not native.fx.first and target.read_u32(FX_LIST + 4) == 0
    seed()
    native.call("dxball_spawn_explosion_effect", 5, 4)
    target.call(0x4125F0, 5, 4)
    native.fx.current.contents.kind = 99
    target.write_u32(target.read_u32(FX_LIST), 99)
    call("process_brick_effects", 0x412510)

    # Exercise actual hit -> maintained/original constructor calls, extending
    # the hit owner's separately controlled effect-boundary evidence.
    for tile in range(256):
        for hard in (0, 1, -1):
            for mode in (0, 1):
                seed(tile, mode=mode)
                native.state[HARD].value = hard
                target.write_u32(HARD, hard)
                assert native.call("dxball_hit_board_tile", 5, 4) == target.call(0x411F40, 5, 4)
                compare(("hit-to-animation", tile, hard, mode))
                hit_integration_cases += 1

    # Full original frame executes, but only animation/request phase state is
    # compared; unrelated gameplay/UI/clock callbacks are explicitly neutralized.
    target.neutralize_other_frame_phases()
    for length in range(9):
        for pending in (0, 1, 2, -1):
            for busy in (False, True):
                seed(pending=pending)
                for index in range(length):
                    native.call("dxball_queue_explosion_at", 5 + index % 2, 4)
                    target.call(0x412B30, 5 + index % 2, 4)
                if busy:
                    native.call("dxball_spawn_explosion_effect", 5, 4)
                    target.call(0x4125F0, 5, 4)
                # Queue producers set pending=1; cover other values at frame entry.
                native.state[PENDING].value = pending
                target.write_u32(PENDING, pending)
                for frame in range(12):
                    target.call(0x40F8B0)
                    native.events = []
                    native.lib.dxball_process_brick_effects()
                    native.lib.dxball_apply_explosion_requests()
                    compare(("frame explosion phases", length, pending, busy, frame))
                    integration_cases += 1

    report = {"target_sha256": target.target_sha256, "cases": cases, "total": sum(cases.values()),
              "integration_cases": integration_cases,
              "hit_integration_cases": hit_integration_cases,
              "source_sha256": hashlib.sha256((ROOT / "src/effects.c").read_bytes()).hexdigest(),
              "scope": "original animation/list bodies; controlled allocation/deletion, bonus production and rendering; bounded original-frame explosion phases, not whole-frame equivalence"}
    output = ROOT / "build/reports/effects-differential.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
