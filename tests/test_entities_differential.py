#!/usr/bin/env python3
"""Compare original particle/bonus bodies, typed queues and 8-bit surface writes."""
import argparse
import ctypes as C
import hashlib
import itertools
import json
from pathlib import Path
import struct
import subprocess

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX
from target_oracle import ROOT, TILES, AUX, MODE, ACTIVE_SURFACE
from test_gameplay_differential import Node, Ops, Allocate, Particle, Random, signed, PAN_SCALE
from test_effects_differential import (
    EffectsNative, EffectsTarget, EffectNode, EffectOps, Free, Bonus, Region,
    REMAINING, HARD, REDUCED, PENDING, SCORE, LIST, FX_LIST, HIT_DX, HIT_DY, FX_SURFACE,
)
from resources_oracle import Desc, Surface

PARTICLES, BONUSES, BONUS_COUNT = 0x43A868, 0x43FAC8, 0x43FA90


def entity_type(name, fields):
    node = type(name, (C.Structure,), {})
    node._fields_ = [(field, C.c_int32) for field in fields] + [
        ("next", C.POINTER(node)), ("previous", C.POINTER(node))]
    owner = type(name + "List", (C.Structure,), {
        "_fields_": [(field, C.POINTER(node)) for field in ("current", "first", "last")]})
    return node, owner


ParticleNode, ParticleList = entity_type("ParticleNode", (
    "x", "y", "dx", "dy", "gravity", "gravity_ticks", "color", "fade_steps", "fade_ticks"))
BonusNode, BonusList = entity_type("BonusNode", (
    "kind", "sprite", "x", "y", "dx", "dy", "gravity_ticks"))
SHAPES = {"explosions": (LIST, Node, 12), "effects": (FX_LIST, EffectNode, 32),
          "particles": (PARTICLES, ParticleNode, 36), "bonuses": (BONUSES, BonusNode, 28)}
ENTRIES = {
    "append_particle": 0x414960, "begin_particles": 0x414C10,
    "advance_particle": 0x414C50, "remove_particle": 0x414B30,
    "spawn_particle": 0x4148A0, "update_particles": 0x414A00, "draw_particles": 0x414CB0,
    "append_bonus": 0x413D80, "begin_bonuses": 0x4146A0,
    "advance_bonus": 0x4146E0, "remove_bonus": 0x4147C0,
    "generate_bonus": 0x4138D0, "retire_bonus": 0x4147A0, "draw_bonuses": 0x414740,
}


class EntitiesNative(EffectsNative):
    def __init__(self, library):
        super().__init__(library)
        self.owners = {"explosions": self.list, "effects": self.fx,
                       "particles": ParticleList.in_dll(self.lib, "dxball_particles"),
                       "bonuses": BonusList.in_dll(self.lib, "dxball_bonuses")}
        self.count = C.c_int32.in_dll(self.lib, "dxball_bonus_count")
        self.script, self.errors = [], []
        # ctypes otherwise prints and discards callback exceptions. Retain them.
        def checked(function, fallback=None):
            def callback(*args):
                try:
                    return function(*args)
                except Exception as error:
                    self.errors.append(repr(error))
                    return fallback
            return callback
        self.entity_callbacks = [Allocate(checked(self.allocate)), Free(checked(self.free)),
                                 Random(checked(self.random, 0))]
        ops = Ops.in_dll(self.lib, "dxball_gameplay_ops")
        ops.allocate_node, ops.random_range = self.entity_callbacks[0], self.entity_callbacks[2]
        EffectOps.in_dll(self.lib, "dxball_effect_ops").deallocate_node = self.entity_callbacks[1]
        for table, field, function in [(Ops, "particle", "dxball_spawn_particle"),
                                       (EffectOps, "bonus", "dxball_generate_bonus")]:
            base = C.addressof(table.in_dll(self.lib, "dxball_gameplay_ops" if table is Ops else "dxball_effect_ops"))
            C.c_void_p.from_address(base + getattr(table, field).offset).value = C.cast(getattr(self.lib, function), C.c_void_p).value
        for name in ENTRIES:
            function = getattr(self.lib, "dxball_" + name)
            if name.startswith(("append_", "begin_", "advance_", "remove_")):
                owner = ParticleList if "particle" in name else BonusList
                function.argtypes, function.restype = [C.POINTER(owner)], C.c_int32
            else:
                nargs = 6 if name == "spawn_particle" else 4 if name == "generate_bonus" else 0
                function.argtypes, function.restype = [C.c_int32] * nargs, None
        self.pitch, self.lock_failures = 643, 0
        self.pixels = C.create_string_buffer(672 * 480)
        self.vtable = (C.c_void_p * 33)()
        self.surface = Surface(self.vtable)
        self.surface_pointer = C.addressof(self.surface)
        signatures = [C.CFUNCTYPE(C.c_int32, C.c_void_p, C.c_void_p),
                      C.CFUNCTYPE(C.c_int32, C.c_void_p, C.c_void_p, C.c_void_p, C.c_uint32, C.c_void_p),
                      C.CFUNCTYPE(C.c_int32, C.c_void_p, C.c_void_p)]
        for slot, signature, function in zip((22, 25, 32), signatures, (self.desc, self.lock, self.unlock)):
            callback = signature(checked(function, -1))
            self.entity_callbacks.append(callback)
            self.vtable[slot] = C.cast(callback, C.c_void_p).value
        self.entity_callbacks.append(Region(lambda *a: self.events.append(("particle-region", *a))))
        C.c_void_p.in_dll(self.lib, "dxball_particle_region").value = C.cast(self.entity_callbacks[-1], C.c_void_p).value
        C.c_size_t.in_dll(self.lib, "dxball_effect_surface").value = self.surface_pointer

    def observed(self):
        return super().observed() + (self.count.value,)

    def random(self, limit):
        if self.script:
            expected, value = self.script.pop(0)
            assert expected == limit and 0 <= value < limit, (expected, limit, value)
        else:
            value = (self.cursor * 7 + 13) % limit
        self.cursor += 1
        self.events.append(("random", limit, value))
        return value

    def allocate(self, size):
        assert size in {C.sizeof(shape[1]) for shape in SHAPES.values()}
        buffer = C.create_string_buffer(b"\xa5" * size, size)
        self.buffers.append(buffer)
        address = C.addressof(buffer)
        # Bonus and effect nodes share their host size. Recover type from roots,
        # not an ambiguous size heuristic, and compare target sizes separately.
        self.allocations[address] = {"size": size, "live": True, "owner": None}
        self.events.append(("allocate", self.observed()))
        return address

    def free(self, address):
        allocation = self.allocations[address]
        assert allocation["live"], "native double deletion"
        owner = allocation["owner"]
        assert owner is not None, "unclassified native deletion"
        self.events.append(("free", owner, C.string_at(address, SHAPES[owner][2]).hex(), self.observed()))
        allocation["live"] = False
        C.memset(address, 0xDD, allocation["size"])

    def queue(self, owner):
        root, node, payload = SHAPES[owner]
        values, addresses, previous = [], [], None
        pointer = self.owners[owner].first
        while pointer:
            address = C.cast(pointer, C.c_void_p).value
            allocation = self.allocations[address]
            assert address not in addresses and allocation["live"]
            assert allocation["size"] == C.sizeof(node)
            assert allocation["owner"] in (None, owner)
            allocation["owner"] = owner
            assert C.cast(pointer.contents.previous, C.c_void_p).value == previous
            addresses.append(address)
            values.append(C.string_at(address, payload).hex())
            previous, pointer = address, pointer.contents.next
        assert C.cast(self.owners[owner].last, C.c_void_p).value == previous
        current = C.cast(self.owners[owner].current, C.c_void_p).value
        return values, addresses.index(current) if current else None

    def reset(self):
        for owner, (_, node, _) in SHAPES.items():
            value = self.owners[owner]
            value.current = value.first = value.last = C.POINTER(node)()
        self.buffers.clear()
        self.allocations.clear()
        self.cursor, self.script, self.errors = 0, [], []

    def fill_desc(self, pointer):
        desc = C.cast(pointer, C.POINTER(Desc)).contents
        assert desc.size == C.sizeof(Desc) and desc.flags == 0xE
        desc.height, desc.width, desc.pitch = 480, 640, self.pitch
        desc.pixels = C.addressof(self.pixels)

    def desc(self, surface, pointer):
        assert surface == self.surface_pointer
        self.fill_desc(pointer)
        self.events.append(("get-desc",))
        return 0

    def lock(self, surface, rect, pointer, flags, event):
        assert surface == self.surface_pointer and rect is None and flags == 0 and event is None
        result = -1 if self.lock_failures else 0
        self.lock_failures = max(0, self.lock_failures - 1)
        self.fill_desc(pointer)
        self.events.append(("lock", result))
        return result

    def unlock(self, surface, pointer):
        assert surface == self.surface_pointer and pointer is None
        self.events.append(("unlock",))
        return 0


class EntitiesTarget(EffectsTarget):
    PIXELS = 0x800000

    def __init__(self):
        super().__init__()
        self.uc.hook_del(self.boundary_hooks["bonus"])
        self.script = []
        self.pitch, self.lock_failures = 643, 0
        self.uc.mem_map(self.PIXELS, 0x100000)
        self.write_u32(FX_SURFACE, self.SURFACE)
        for slot, address, callback in [(22, 0x50B000, self.desc), (25, 0x50B010, self.lock),
                                         (32, 0x50B020, self.unlock)]:
            self.write_u32(self.VTABLE + slot * 4, address)
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE, callback, begin=address, end=address))
        address = 0x408990
        def region(*unused):
            self.events.append(("particle-region", *(signed(a) for a in self._args(4))))
            self._return()
        self._hooks.append(self.uc.hook_add(UC_HOOK_CODE, region, begin=address, end=address))

    def particle(self, *unused):
        pass  # Execute original particle construction, including its clipping.

    def observed(self):
        return super().observed() + (signed(self.read_u32(BONUS_COUNT)),)

    def random(self, *unused):
        limit = self._args(1)[0]
        if self.script:
            expected, value = self.script.pop(0)
            assert expected == limit and 0 <= value < limit, (expected, limit, value)
        else:
            value = (self.cursor * 7 + 13) % limit
        self.cursor += 1
        self.events.append(("random", limit, value))
        self._return(value)

    def allocate(self, *unused):
        size = self._args(1)[0]
        assert size in {payload + 8 for _, _, payload in SHAPES.values()}
        self.events.append(("allocate", self.observed()))
        if self.fail_allocation:
            self._return(0)
            return
        assert self.used + size <= 0x10000
        address = self.HEAP + self.used
        self.used += size
        self.allocations[address] = {"size": size, "live": True, "owner": None}
        self.write(address, b"\xa5" * size)
        self._return(address)

    def free(self, *unused):
        address = self._args(1)[0]
        allocation = self.allocations[address]
        assert allocation["live"], "target double deletion"
        owner = allocation["owner"]
        assert owner is not None, "unclassified target deletion"
        self.events.append(("free", owner, self.read(address, SHAPES[owner][2]).hex(), self.observed()))
        allocation["live"] = False
        self.write(address, b"\xdd" * allocation["size"])
        self._return()

    def queue(self, owner):
        root, node, payload = SHAPES[owner]
        current, first, last = struct.unpack("<3I", self.read(root, 12))
        values, addresses, previous, address = [], [], 0, first
        while address:
            allocation = self.allocations[address]
            assert address not in addresses and allocation["live"]
            assert allocation["size"] == payload + 8
            assert allocation["owner"] in (None, owner)
            allocation["owner"] = owner
            following, preceding = struct.unpack("<2I", self.read(address + payload, 8))
            assert preceding == previous
            addresses.append(address)
            values.append(self.read(address, payload).hex())
            previous, address = address, following
        assert last == previous
        return values, addresses.index(current) if current else None

    def reset(self):
        for root, _, _ in SHAPES.values():
            self.write(root, bytes(12))
        self.used, self.cursor, self.script = 0, 0, []
        self.allocations.clear()

    def fill_desc(self, pointer):
        assert self.read_u32(pointer) == 108 and self.read_u32(pointer + 4) == 0xE
        self.write(pointer + 8, struct.pack("<3i", 480, 640, self.pitch))
        self.write_u32(pointer + 36, self.PIXELS)

    def desc(self, *unused):
        surface, pointer = self._args(2)
        assert surface == self.SURFACE
        self.fill_desc(pointer)
        self.events.append(("get-desc",))
        self._return(pop=8)

    def lock(self, *unused):
        surface, rect, pointer, flags, event = self._args(5)
        assert surface == self.SURFACE and (rect, flags, event) == (0, 0, 0)
        result = -1 if self.lock_failures else 0
        self.lock_failures = max(0, self.lock_failures - 1)
        self.fill_desc(pointer)
        self.events.append(("lock", result))
        self._return(result & 0xFFFFFFFF, pop=20)

    def unlock(self, *unused):
        assert self._args(2) == (self.SURFACE, 0)
        self.events.append(("unlock",))
        self._return(pop=8)


def main():
    if not __debug__:
        raise SystemExit("run without -O; oracle assertions must stay enabled")
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--library", type=Path, default=ROOT / "build/native/libdxball_core.so")
    args = parser.parse_args()
    native, target = EntitiesNative(args.library), EntitiesTarget()
    cases = dict.fromkeys(ENTRIES, 0)
    integration_cases = 0

    def seed(reduced=0, count=0, mode=0):
        native.reset()
        target.reset()
        native.tiles[:] = bytes([7]) * 400
        native.aux[:] = bytes(400)
        target.write(TILES, bytes(native.tiles))
        target.write(AUX, bytes(400))
        native.cell = target.cell = 85
        native.mode.value = mode
        target.write_u32(MODE, mode)
        native.active.value = 0xAA
        target.write_u32(ACTIVE_SURFACE, 0xAA)
        native.hit_dx.value, native.hit_dy.value = -3, 7
        target.write_u32(HIT_DX, -3)
        target.write_u32(HIT_DY, 7)
        native.scale.value = 1.0
        target.write(PAN_SCALE, struct.pack("<d", 1.0))
        native.count.value = count
        target.write_u32(BONUS_COUNT, count)
        for address, value in [(REMAINING, 200), (HARD, 0), (REDUCED, reduced), (PENDING, 0), (SCORE, 1234)]:
            native.state[address].value = value
            target.write_u32(address, value)

    def compare(context):
        assert not native.errors, (context, native.errors)
        assert bytes(native.tiles) == target.read(TILES, 400), (context, "tiles")
        assert bytes(native.aux) == target.read(AUX, 400), (context, "aux")
        assert native.count.value == signed(target.read_u32(BONUS_COUNT)), (context, "count")
        for address, value in native.state.items():
            assert value.value == signed(target.read_u32(address)), (context, hex(address))
        active = target.SURFACE if native.active.value == native.surface_pointer else native.active.value
        assert active == target.read_u32(ACTIVE_SURFACE), (context, "surface")
        assert native.cursor == target.cursor and native.script == target.script, (context, "RNG")
        assert native.events == target.events, (context, native.events, target.events)
        live_count = 0
        for owner in SHAPES:
            assert native.queue(owner) == target.queue(owner), (context, owner, native.queue(owner), target.queue(owner))
            live_count += len(native.queue(owner)[0])
        # Every live allocation must remain reachable, and freed bytes stay poison.
        for oracle in (native, target):
            assert sum(a["live"] for a in oracle.allocations.values()) == live_count, (context, "lost live allocation")
            for address, allocation in oracle.allocations.items():
                assert allocation["owner"] is not None, (context, "unreachable allocation")
                if not allocation["live"]:
                    data = C.string_at(address, allocation["size"]) if oracle is native else oracle.read(address, allocation["size"])
                    assert data == b"\xdd" * allocation["size"], (context, "write after free")

    def call(name, *arguments, owner=None, count=True):
        if owner:
            target.uc.reg_write(UC_X86_REG_ECX, SHAPES[owner][0])
            result = native.call("dxball_" + name, C.byref(native.owners[owner]))
            actual = target.call(ENTRIES[name])
            assert result == actual, (name, result, actual)
        else:
            native.call("dxball_" + name, *arguments)
            target.call(ENTRIES[name], *arguments)
        compare((name, arguments, owner))
        if count:
            cases[name] += 1

    def append_seed(owner, values):
        name = "append_particle" if owner == "particles" else "append_bonus"
        call(name, owner=owner, count=False)
        pointer = native.owners[owner].current
        address = target.read_u32(SHAPES[owner][0])
        for index, (field, value) in enumerate(zip((f for f, _ in SHAPES[owner][1]._fields_), values)):
            setattr(pointer.contents, field, value)
            target.write_u32(address + index * 4, value)
        return C.cast(C.cast(pointer, C.c_void_p).value, C.POINTER(SHAPES[owner][1])), address

    for owner, append in (("particles", "append_particle"), ("bonuses", "append_bonus")):
        seed()
        for index in range(64):
            call(append, owner=owner)
            native.owners[owner].current = native.owners[owner].first
            target.write_u32(SHAPES[owner][0], target.read_u32(SHAPES[owner][0] + 4))
        # Null allocation is fatal, but must not change roots on either side.
        target.fail_allocation = True
        target.uc.reg_write(UC_X86_REG_ECX, SHAPES[owner][0])
        try:
            target.call(ENTRIES[append])
            raise AssertionError("allocation failure returned")
        except AssertionError as error:
            assert str(error) == "instruction limit reached" and target.exit_status == 1
        target.fail_allocation = False
        child = '''import ctypes as C, sys
lib = C.CDLL(sys.argv[1])
callback = C.CFUNCTYPE(C.c_void_p, C.c_size_t)(lambda size: None)
C.c_void_p.in_dll(lib, "dxball_gameplay_ops").value = C.cast(callback, C.c_void_p).value
owner = (C.c_void_p * 3)()
getattr(lib, sys.argv[2])(C.byref(owner))
'''
        result = subprocess.run([ROOT / "scripts/repo-python", "-c", child, args.library.resolve(), "dxball_" + append])
        assert result.returncode == 1
        assert native.queue(owner) == target.queue(owner)
        cases[append] += 1
        for operation in ("begin_", "advance_", "remove_"):
            name = operation + ("particles" if operation == "begin_" and owner == "particles" else
                                "bonuses" if operation == "begin_" else "particle" if owner == "particles" else "bonus")
            for length in range(9):
                for current in (None, *range(length)):
                    seed()
                    nodes = [append_seed(owner, (i,) * (9 if owner == "particles" else 7)) for i in range(length)]
                    node = SHAPES[owner][1]
                    native.owners[owner].current = nodes[current][0] if current is not None else C.POINTER(node)()
                    target.write_u32(SHAPES[owner][0], nodes[current][1] if current is not None else 0)
                    call(name, owner=owner)

    for x, y, gravity, color in itertools.product((19, 20, 21, 618, 619, 620), (-1, 0, 1, 478, 479, 480), (0, 1, -1, 2), (0, 16, 255, 256, -1)):
        seed()
        call("spawn_particle", x, y, -3, 4, color, gravity)

    # Inclusive updater boundaries differ from the strict constructor bounds.
    for x, y, gravity, gtick, ftick, fade in itertools.product(
            (19, 20, 21, 617, 618, 619), (-1, 0, 1, 477, 478, 479),
            (0, 1, -1, 2), (0, 5, 6), (0, 4, 5), (0, 6, 7)):
        seed()
        append_seed("particles", (x, y, 0, 0, gravity, gtick, 255, fade, ftick))
        call("update_particles")
    for length in range(9):
        seed()
        for index in range(length):
            append_seed("particles", (21 + index, 1 + index, -1 if index % 2 else 2,
                                      -1 if index % 3 else 2, index % 3, index % 6, 250 + index,
                                      index % 7, index % 5))
        for frame in range(40):
            call("update_particles")

    for length, pitch, failures in itertools.product(range(9), (643, 672), (0, 2)):
        seed()
        for index in range(length):
            append_seed("particles", ((20, 618, 101)[index % 3], (0, 478, 202)[index % 3],
                                      0, 0, 1, 0, (-1, 0, 255, 256)[index % 4], 0, 0))
        native.pitch = target.pitch = pitch
        native.lock_failures = target.lock_failures = failures
        C.memset(native.pixels, 0xA5, 672 * 480)
        target.write(target.PIXELS, b"\xa5" * (672 * 480))
        call("draw_particles")
        assert C.string_at(native.pixels, 672 * 480) == target.read(target.PIXELS, 672 * 480), (length, pitch, failures, "pixels and guards")

    for length in range(9):
        for current in (None, *range(length)):
            for count in (-1, 0, 1, 3):
                seed(count=count)
                nodes = [append_seed("bonuses", (i, i + 35, i * 30 + 19, i * 15 + 50, -3, 7, 0)) for i in range(length)]
                native.owners["bonuses"].current = nodes[current][0] if current is not None else C.POINTER(BonusNode)()
                target.write_u32(BONUSES, nodes[current][1] if current is not None else 0)
                call("retire_bonus")
        seed()
        for index in range(length):
            append_seed("bonuses", (index, index + 35, index * 30 + 19, index * 15 + 50, -3, 7, 0))
        call("draw_bonuses")

    for count, chance in itertools.product((-1, 0, 1, 2), range(10)):
        seed(count=count)
        native.script = [(10, chance)]
        target.script = list(native.script)
        call("generate_bonus", 0, 0, -3, 7)
    for reduced, kind, rare, position in itertools.product((0, 1, -1), range(19), range(5), ((0, 0), (19, 19), (5, 4))):
        seed(reduced=reduced)
        script = [(10, 0)]
        for index in range(15 if reduced == 0 else 8):
            script.extend((limit, index % limit) for limit in (7, 9, 15, 30))
        script.append((19, kind))
        if kind in (0, 1):
            script.append((5, rare))
        native.script, target.script = list(script), list(script)
        call("generate_bonus", *position, -3, 7)
        assert not native.script, ("unconsumed scripted RNG", reduced, kind, rare)
        # A second producer call still draws chance, but the occupied count stops
        # audio, particles, allocation and selection. Preserve existing queues.
        native.script, target.script = [(10, 0)], [(10, 0)]
        call("generate_bonus", *position, -3, 7)

    # Connect real maintained hit/effect/bonus/particle bodies without the pending
    # power-up application or unrelated frame/UI dependencies.
    for tile, reduced, mode in itertools.product((1, 3, 7, 8, 21), (0, 1), (0, 1)):
        seed(reduced=reduced, mode=mode)
        native.tiles[85] = tile
        target.write(TILES + 85, bytes([tile]))
        assert native.call("dxball_hit_board_tile", 5, 4) == target.call(0x411F40, 5, 4)
        compare(("connected hit", tile, reduced, mode))
        integration_cases += 1
        for frame in range(12):
            for name, entry in (("update_particles", 0x414A00), ("process_brick_effects", 0x412510),
                                ("draw_bonuses", 0x414740),
                                ("draw_particles", 0x414CB0)):
                native.call("dxball_" + name)
                target.call(entry)
                compare(("connected entities", tile, reduced, mode, frame, name))
                integration_cases += 1
            assert C.string_at(native.pixels, 672 * 480) == target.read(target.PIXELS, 672 * 480), ("connected pixels", tile, reduced, mode, frame)

    report = {"target_sha256": target.target_sha256, "cases": cases, "total": sum(cases.values()),
              "integration_cases": integration_cases,
              "source_sha256": {owner: hashlib.sha256((ROOT / ("src/" + owner + ".c")).read_bytes()).hexdigest() for owner in ("particles", "bonuses")},
              "scope": "original particle/bonus producer, list and draw bodies; typed live/free allocation checks, controlled RNG/audio/render boundaries and complete 8-bit pixel buffers; bonus movement/application and whole frame remain unclaimed"}
    output = ROOT / "build/reports/entities-differential.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
