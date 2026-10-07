#!/usr/bin/env python3
"""Execute original hit/scan/list/pan bodies; compare maintained C and boundaries."""
from source_state import source_global
import argparse
import ctypes as C
import csv
import hashlib
import json
from pathlib import Path
import random
import struct
import subprocess

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX
from target_oracle import TargetOracle, ROOT, TILES, MODE, ACTIVE_SURFACE
from test_boards_differential import Native

REMAINING = 0x43A8F4
HARD = 0x43FAC0
REDUCED = 0x4228D8
PENDING = 0x422D20
SCORE = 0x422D18
PAN_SCALE = 0x4210A0
LIST = 0x43F8E0


def signed(value):
    return C.c_int32(value).value


class Node(C.Structure):
    pass


Node._fields_ = [(name, C.c_int32) for name in ("kind", "x", "y")] + [
    ("next", C.POINTER(Node)), ("previous", C.POINTER(Node))]


class List(C.Structure):
    _fields_ = [(name, C.POINTER(Node)) for name in ("current", "first", "last")]


Allocate = C.CFUNCTYPE(C.c_void_p, C.c_size_t)
Effect = C.CFUNCTYPE(None, C.c_int32, C.c_int32, C.c_uint8, C.c_int32)
Stop = C.CFUNCTYPE(None, C.c_int32)
Play = C.CFUNCTYPE(None, C.c_int32, C.c_int32, C.c_int32, C.c_int32)
Random = C.CFUNCTYPE(C.c_int32, C.c_int32)
Particle = C.CFUNCTYPE(None, *([C.c_int32] * 6))


class Ops(C.Structure):
    _fields_ = [("allocate_node", Allocate), ("brick_effect", Effect),
                ("stop_sound", Stop), ("play_sound", Play),
                ("random_range", Random), ("particle", Particle)]


class GameNative(Native):
    def __init__(self, library):
        super().__init__(library)
        self.state = {key: source_global(C.c_int32, self.lib, name) for key, name in [
            (REMAINING, "dxball_remaining_bricks"), (HARD, "dxball_destroy_hard_tiles"),
            (REDUCED, "dxball_reduced_particles"), (PENDING, "dxball_explosion_pending"),
            (SCORE, "dxball_score")]}
        self.scale = C.c_double.in_dll(self.lib, "dxball_pan_scale")
        self.list = source_global(List, self.lib, "dxball_explosions")
        self.buffers = []
        self.cursor = 0
        self.cell = 0
        self.game_callbacks = (Allocate(self.allocate), Effect(self.effect),
                               Stop(self.stop), Play(self.play), Random(self.random),
                               Particle(lambda *args: self.events.append(("particle", *args))))
        ops = Ops.in_dll(self.lib, "dxball_gameplay_ops")
        for (name, _), callback in zip(Ops._fields_, self.game_callbacks):
            setattr(ops, name, callback)
        self.free_callback = C.CFUNCTYPE(None, C.c_void_p)(self.free)
        C.c_void_p.in_dll(self.lib, "dxball_effect_ops").value = C.cast(self.free_callback, C.c_void_p).value
        for name, args, result in [
            ("dxball_screen_pan", [C.c_int32], C.c_int32),
            ("dxball_append_explosion", [C.POINTER(List)], C.c_int32),
            ("dxball_hit_board_tile", [C.c_int32, C.c_int32], C.c_int32),
            ("dxball_scan_explosive_tiles", [], None)]:
            function = getattr(self.lib, name)
            function.argtypes, function.restype = args, result
        for name in ("begin_explosions", "advance_explosion", "remove_explosion"):
            function = getattr(self.lib, "dxball_" + name)
            function.argtypes, function.restype = [C.POINTER(List)], C.c_int32
        self.lib.dxball_queue_explosion_at.argtypes = [C.c_int32, C.c_int32]
        self.lib.dxball_queue_explosion_at.restype = None

    def free(self, address):
        node = C.cast(address, C.POINTER(Node)).contents
        self.events.append(("free-node", node.kind, node.x, node.y))

    def observed(self):
        return (self.tiles[self.cell], self.state[REMAINING].value,
                self.state[PENDING].value)

    def allocate(self, size):
        # Natural pointer growth is allowed; compare logical allocation shape.
        assert size == C.sizeof(Node)
        buffer = C.create_string_buffer(b"\xa5" * size, size)
        self.buffers.append(buffer)
        self.events.append(("allocate-node", self.observed()))
        return C.addressof(buffer)

    def effect(self, x, y, tile, mode):
        self.events.append(("effect", x, y, tile, mode, self.observed()))

    def stop(self, sound):
        self.events.append(("stop", sound, self.observed()))

    def play(self, *args):
        self.events.append(("play", *args, self.observed()))

    def random(self, limit):
        value = (self.cursor * 7 + 13) % limit
        self.cursor += 1
        self.events.append(("random", limit, value))
        return value

    def reset_list(self):
        self.list.current = self.list.first = self.list.last = C.POINTER(Node)()
        self.buffers.clear()

    def list_state(self):
        nodes = []
        pointer = self.list.first
        previous = 0
        addresses = []
        while pointer:
            address = C.addressof(pointer.contents)
            assert address not in addresses, "native list cycle"
            assert C.cast(pointer.contents.previous, C.c_void_p).value == (previous or None)
            addresses.append(address)
            nodes.append((pointer.contents.kind, pointer.contents.x, pointer.contents.y))
            previous = address
            pointer = pointer.contents.next
        assert C.cast(self.list.last, C.c_void_p).value == (previous or None)
        current = C.cast(self.list.current, C.c_void_p).value
        return nodes, addresses.index(current) if current else None


class GameTarget(TargetOracle):
    HEAP = 0x700000

    def __init__(self):
        super().__init__()
        self.uc.mem_map(self.HEAP, 0x10000)
        self.used = 0
        self.cursor = 0
        self.cell = 0
        self.fail_allocation = False
        self.exit_status = None
        self.game_hooks = {}
        for address, callback in [(0x412BA0, self.effect), (0x405EF0, self.stop),
                                  (0x405C50, self.play), (0x403B70, self.random),
                                  (0x4148A0, self.particle), (0x416770, self.allocate),
                                  (0x417910, self.exit)]:
            hook = self.uc.hook_add(UC_HOOK_CODE, callback, begin=address, end=address)
            self._hooks.append(hook)
            self.game_hooks[address] = hook
        self._hooks.append(self.uc.hook_add(UC_HOOK_CODE, self.free, begin=0x416760, end=0x416760))

    def free(self, *unused):
        self.events.append(("free-node", *struct.unpack("<3i", self.read(self._args(1)[0], 12))))
        self._return()

    def observed(self):
        return (self.read(TILES + self.cell, 1)[0], signed(self.read_u32(REMAINING)),
                signed(self.read_u32(PENDING)))

    def effect(self, *unused):
        x, y, tile, mode = self._args(4)
        self.events.append(("effect", signed(x), signed(y), tile & 255,
                            signed(mode), self.observed()))
        self._return()

    def stop(self, *unused):
        self.events.append(("stop", self._args(1)[0], self.observed()))
        self._return()

    def play(self, *unused):
        self.events.append(("play", *(signed(x) for x in self._args(4)), self.observed()))
        self._return()

    def random(self, *unused):
        limit = self._args(1)[0]
        value = (self.cursor * 7 + 13) % limit
        self.cursor += 1
        self.events.append(("random", limit, value))
        self._return(value)

    def particle(self, *unused):
        self.events.append(("particle", *(signed(x) for x in self._args(6))))
        self._return()

    def allocate(self, *unused):
        assert self._args(1) == (20,), "original allocation size changed"
        self.events.append(("allocate-node", self.observed()))
        if self.fail_allocation:
            self._return(0)
            return
        assert self.used + 20 <= 0x10000
        address = self.HEAP + self.used
        self.used += 20
        self.write(address, b"\xa5" * 20)
        self._return(address)

    def exit(self, *unused):
        self.exit_status = self._args(1)[0]
        self.uc.emu_stop()

    def reset_list(self):
        self.write(LIST, bytes(12))
        self.used = 0

    def append(self):
        self.uc.reg_write(UC_X86_REG_ECX, LIST)
        return self.call(0x412470)

    def list_state(self):
        current, first, last = struct.unpack("<3I", self.read(LIST, 12))
        nodes, addresses = [], []
        previous, address = 0, first
        while address:
            assert address not in addresses, "original list cycle"
            kind, x, y, next_address, prev_address = struct.unpack("<3i2I", self.read(address, 20))
            assert prev_address == previous
            addresses.append(address)
            nodes.append((kind, x, y))
            previous, address = address, next_address
        assert last == previous
        return nodes, addresses.index(current) if current else None


def main():
    if not __debug__:
        raise SystemExit("run without -O; oracle assertions must stay enabled")
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--library", type=Path, default=ROOT / "build/native/libdxball_core.so")
    args = parser.parse_args()
    native, target = GameNative(args.library), GameTarget()
    cases = {"screen_pan": 0, "append_explosion": 0, "hit_board_tile": 0,
             "scan_explosive_tiles": 0, "begin_explosions": 0,
             "advance_explosion": 0, "remove_explosion": 0, "queue_explosion_at": 0}
    rng = random.Random(0x411F40)

    def seed(tiles, flags=0, reduced=0, mode=0, cell=0, preserve_list=False):
        native.tiles[:] = tiles
        target.write(TILES, tiles)
        native.cell = target.cell = cell
        native.cursor = target.cursor = 0
        native.scale.value = 1.0
        target.write(PAN_SCALE, struct.pack("<d", 1.0))
        for address, value in [(REMAINING, 200), (HARD, flags), (REDUCED, reduced),
                               (PENDING, 0), (SCORE, 1234)]:
            native.state[address].value = value
            target.write_u32(address, value)
        native.mode.value = mode
        target.write_u32(MODE, mode)
        native.active.value = 0xAA
        target.write_u32(ACTIVE_SURFACE, 0xAA)
        if not preserve_list:
            native.reset_list()
            target.reset_list()

    def compare(context):
        assert bytes(native.tiles) == target.read(TILES, 400), (context, "board")
        for address, value in native.state.items():
            assert value.value == signed(target.read_u32(address)), (context, hex(address))
        assert native.active.value == target.read_u32(ACTIVE_SURFACE), (context, "surface")
        assert native.cursor == target.cursor, (context, "RNG position")
        assert native.events == target.events, (context, native.events, target.events)
        assert native.list_state() == target.list_state(), (context, "linked list")

    seed(bytes(400))
    # Original x87 arithmetic and its _ftol helper execute without hooks.
    for scale in (0.0, 0.5, 1.0, 20.0, -1.0):
        native.scale.value = scale
        target.write(PAN_SCALE, struct.pack("<d", scale))
        for x in range(641):
            assert native.call("dxball_screen_pan", x) == signed(target.call(0x406400, x)), (scale, x)
            cases["screen_pan"] += 1

    seed(bytes(400))
    for i in range(128):
        assert target.append() == native.call("dxball_append_explosion", C.byref(native.list)) == 1
        # First three fields remain allocation poison until the caller fills them.
        assert bytes(native.list.current.contents)[:12] == b"\xa5" * 12
        assert target.read(target.read_u32(LIST), 12) == b"\xa5" * 12
        compare(("append", i))
        cases["append_explosion"] += 1
        native.list.current.contents.kind = i
        target.write_u32(target.read_u32(LIST), i)
        # Existing current need not be the tail; append must replace it.
        native.list.current = native.list.first
        target.write_u32(LIST, target.read_u32(LIST + 4))

    target.fail_allocation = True
    try:
        target.append()
        raise AssertionError("allocation failure returned")
    except AssertionError as error:
        assert str(error) == "instruction limit reached" and target.exit_status == 1
    target.fail_allocation = False
    child = '''import ctypes as C, sys
lib = C.CDLL(sys.argv[1])
callback = C.CFUNCTYPE(C.c_void_p, C.c_size_t)(lambda size: None)
C.c_void_p.in_dll(lib, "dxball_gameplay_ops").value = C.cast(callback, C.c_void_p).value
owner = (C.c_void_p * 3)()
lib.dxball_append_explosion(C.byref(owner))
'''
    result = subprocess.run([ROOT / "scripts/repo-python", "-c", child, args.library.resolve()])
    assert result.returncode == target.exit_status == 1
    assert native.list_state() == target.list_state(), "failed append changed list"
    cases["append_explosion"] += 1

    for tile in range(256):
        for x, y in ((0, 0), (19, 19), (3, 17)):
            board = bytearray(400)
            board[x + y * 20] = tile
            seed(board, cell=x + y * 20)
            native.call("dxball_queue_explosion_at", x, y)
            target.call(0x412B30, x, y)
            compare(("queue", tile, x, y))
            cases["queue_explosion_at"] += 1

    for name, address in [("begin_explosions", 0x410070),
                          ("advance_explosion", 0x410170), ("remove_explosion", 0x40FF50)]:
        for length in range(9):
            for current in [None, *range(length)]:
                seed(bytes(400))
                host_nodes, target_nodes = [], []
                for index in range(length):
                    target.append()
                    native.call("dxball_append_explosion", C.byref(native.list))
                    host_nodes.append(C.cast(C.cast(native.list.current, C.c_void_p).value, C.POINTER(Node)))
                    target_nodes.append(target.read_u32(LIST))
                native.list.current = host_nodes[current] if current is not None else C.POINTER(Node)()
                target.write_u32(LIST, target_nodes[current] if current is not None else 0)
                target.uc.reg_write(UC_X86_REG_ECX, LIST)
                assert native.call("dxball_" + name, C.byref(native.list)) == target.call(address), (name, length, current)
                compare((name, length, current))
                cases[name] += 1

    for tile in range(256):
        for flags in (0, 1, -1):
            for reduced in (0, 1):
                for mode in (0, 1):
                    for x, y in ((0, 0), (19, 19), (3, 17)):
                        board = bytearray(rng.randbytes(400))
                        board[x + y * 20] = tile
                        seed(board, flags, reduced, mode, x + y * 20)
                        actual = target.call(0x411F40, x, y)
                        result = native.call("dxball_hit_board_tile", x, y)
                        assert result == actual and actual in (0, 1), (tile, flags, "full EAX")
                        compare((tile, flags, reduced, mode, x, y))
                        cases["hit_board_tile"] += 1

    # Repeated damage preserves progression, hard-brick returns and queue growth.
    for tile in (2, 3, 4, 7, 8, 21):
        board = bytearray(400)
        board[85] = tile
        seed(board, cell=85)
        for hit in range(4):
            assert native.call("dxball_hit_board_tile", 5, 4) == target.call(0x411F40, 5, 4)
            compare(("repeat", tile, hit))
            cases["hit_board_tile"] += 1

    original = (ROOT / "original/DEFAULT.BDS").read_bytes()
    with (ROOT / "config/assets.csv").open() as stream:
        fixture = next(row for row in csv.DictReader(stream) if row["filename"] == "DEFAULT.BDS")
    assert hashlib.sha256(original).hexdigest() == fixture["sha256"]
    boards = [original[i:i + 400] for i in range(0, len(original), 400)]
    boards += [bytes(400), bytes([8]) * 400, bytes((i % 256 for i in range(400)))]
    for index, board in enumerate(boards):
        for mode in (0, 1):
            seed(board, mode=mode)
            for scan in range(2):
                # Re-scan appends again: this function does not consume tile 8.
                native.call("dxball_scan_explosive_tiles")
                target.call(0x4155A0)
                compare(("scan", index, mode, scan))
                cases["scan_explosive_tiles"] += 1

    report = {"target_sha256": target.target_sha256, "cases": cases,
              "total": sum(cases.values()),
              "source_sha256": hashlib.sha256((ROOT / "src/gameplay.c").read_bytes()).hexdigest(),
              "scope": "unmodified x86 hit/scan/list/pan and board drawing; controlled allocation, audio, effect, RNG and particle boundaries"}
    output = ROOT / "build/reports/gameplay-differential.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
