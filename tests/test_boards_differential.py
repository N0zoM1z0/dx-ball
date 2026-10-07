#!/usr/bin/env python3
"""Compare compiled maintained C against actual, hash-verified target x86."""
import argparse
import ctypes as C
import hashlib
import json
from pathlib import Path
import random
import sys
import tempfile

from target_oracle import (
    TargetOracle, ROOT, BANK, TILES, AUX, INDEX, MODE, FILE_SLOT, ACTIVE_SURFACE,
)


class Rect(C.Structure):
    _fields_ = [(name, C.c_int32) for name in ("left", "top", "right", "bottom")]


Sprite = C.CFUNCTYPE(None, C.c_int32, C.c_int32, C.c_int32)
Restore = C.CFUNCTYPE(None, C.c_size_t, C.c_int32, C.c_int32, C.c_size_t,
                     C.POINTER(Rect), C.c_uint32)
Invalidate = C.CFUNCTYPE(None, C.c_int32, C.c_int32, C.c_int32, C.c_int32)


class RenderOps(C.Structure):
    _fields_ = [("sprite", Sprite), ("restore", Restore), ("invalidate", Invalidate)]


class Native:
    def __init__(self, library):
        self.lib = C.CDLL(str(library.resolve()))
        self.bank = (C.c_uint8 * 20000).in_dll(self.lib, "dxball_board_bank")
        self.tiles = (C.c_uint8 * 400).in_dll(self.lib, "dxball_board_tiles")
        self.aux = (C.c_uint8 * 400).in_dll(self.lib, "dxball_board_aux")
        self.index = C.c_int32.in_dll(self.lib, "dxball_board_index")
        self.mode = C.c_int32.in_dll(self.lib, "dxball_display_mode")
        self.active = C.c_size_t.in_dll(self.lib, "dxball_active_surface")
        self.file = C.c_void_p.in_dll(self.lib, "dxball_board_file")
        C.c_size_t.in_dll(self.lib, "dxball_board_surface").value = TargetOracle.SURFACE
        C.c_size_t.in_dll(self.lib, "dxball_background_surface").value = TargetOracle.BACKGROUND
        self.events = []
        self.callbacks = (
            Sprite(lambda sprite, x, y: self.events.append(("sprite", sprite, x, y))),
            Restore(self.restore),
            Invalidate(lambda *rect: self.events.append(("invalidate", *rect))),
        )
        ops = RenderOps.in_dll(self.lib, "dxball_render_ops")
        ops.sprite, ops.restore, ops.invalidate = self.callbacks
        for name, types, result in [
            ("dxball_read_board_bank", [C.c_char_p], None),
            ("dxball_write_board_bank", [C.c_char_p], None),
            ("dxball_load_editor_board", [C.c_int32], None),
            ("dxball_store_editor_board", [C.c_int32], None),
            ("dxball_initialize_board", [], None),
            ("dxball_board_tile_sprite", [C.c_int32], C.c_int32),
            ("dxball_select_surface", [C.c_size_t], None),
            ("dxball_draw_board_tile", [C.c_int32, C.c_int32, C.c_int32], None),
            ("dxball_draw_board", [C.c_int32], None),
        ]:
            function = getattr(self.lib, name)
            function.argtypes, function.restype = types, result

    def restore(self, destination, x, y, source, rect, flags):
        value = rect.contents
        self.events.append(("restore", destination, x, y, source,
                            (value.left, value.top, value.right, value.bottom), flags))

    def call(self, name, *args):
        self.events = []
        return getattr(self.lib, name)(*args)


def assert_memory(native, target):
    assert bytes(native.bank) == target.read(BANK, 20000), "board bank differs"
    assert bytes(native.tiles) == target.read(TILES, 400), "current board differs"
    assert bytes(native.aux) == target.read(AUX, 400), "auxiliary board differs"


def seed(native, target, bank, tiles, aux):
    native.bank[:], native.tiles[:], native.aux[:] = bank, tiles, aux
    for address, data in ((BANK, bank), (TILES, tiles), (AUX, aux)):
        target.write(address, data)


def test_copy(native, target, original):
    rng = random.Random(0xD0BA11)
    checks = 0
    # All slots, including boundaries, and the actual CRT memcpy/memset code.
    for board in range(50):
        seed(native, target, original, rng.randbytes(400), rng.randbytes(400))
        target.call(0x0040CEA0, board)
        native.call("dxball_load_editor_board", board)
        assert_memory(native, target)
        checks += 1
        new_tiles = rng.randbytes(400)
        native.tiles[:] = new_tiles
        target.write(TILES, new_tiles)
        target.call(0x0040CEE0, board)
        native.call("dxball_store_editor_board", board)
        assert_memory(native, target)
        checks += 1
        native.index.value = board
        target.write_u32(INDEX, board)
        target.call(0x00411930)
        native.call("dxball_initialize_board")
        assert_memory(native, target)
        assert bytes(native.aux) == b"\0" * 400
        checks += 1
    return checks


def test_sprite(native, target, original):
    for tile in range(23):
        assert native.call("dxball_board_tile_sprite", tile) == target.call(0x0040CCF0, tile)
    # Unsupported target values read an uninitialized local. No host equivalence
    # is claimed there; renderer unknown-byte behavior is tested separately.
    assert target.call(0x0040CCF0, 23) == 0xA5A5A5A5
    return 23


def test_render(native, target, original):
    checks = 0
    for surface in (0, 0x123400, target.SURFACE):
        native.call("dxball_select_surface", surface)
        target.call(0x00403E50, surface)
        assert native.active.value == target.read_u32(ACTIVE_SURFACE)
        checks += 1
    native.active.value = target.SURFACE
    target.write_u32(ACTIVE_SURFACE, target.SURFACE)
    for tile in range(256):
        for mode in (0, 1, 2, 4):
            native.mode.value = mode
            target.write_u32(MODE, mode)
            for defer in (0, 1, -1):
                for x, y in ((0, 0), (19, 19), (3, 17)):
                    native.tiles[x + y * 20] = tile
                    target.write(TILES + x + y * 20, bytes([tile]))
                    target.call(0x004119F0, x, y, defer)
                    native.call("dxball_draw_board_tile", x, y, defer)
                    assert native.events == target.events, (tile, mode, defer, x, y)
                    checks += 1
    # Full real boards compare x-major traversal and all ordered dependency calls.
    for board in range(50):
        tiles = original[board * 400:(board + 1) * 400]
        native.tiles[:] = tiles
        target.write(TILES, tiles)
        for mode, defer in ((0, 0), (1, 1)):
            native.mode.value = mode
            target.write_u32(MODE, mode)
            native.active.value = 0xAA
            target.write_u32(ACTIVE_SURFACE, 0xAA)
            target.call(0x00411970, defer)
            native.call("dxball_draw_board", defer)
            assert native.events == target.events, (board, mode, defer)
            assert native.active.value == target.read_u32(ACTIVE_SURFACE)
            checks += 1
    return checks


def test_io(native, target, original):
    checks = 0
    rng = random.Random(0x107)
    with tempfile.TemporaryDirectory(prefix="dxball-oracle-") as directory:
        path = Path(directory) / "board.bds"
        for size in (None, 0, 1, 399, 400, 19999, 20000, 20037):
            seed(native, target, rng.randbytes(20000), rng.randbytes(400), rng.randbytes(400))
            data = None if size is None else rng.randbytes(size)
            if path.exists():
                path.unlink()
            if data is not None:
                path.write_bytes(data)
            target.open_succeeds = data is not None
            target.file_data = data
            target.call(0x0040CC30, target.PATH)
            native.call("dxball_read_board_bank", str(path).encode())
            assert_memory(native, target)
            assert bool(native.file.value) == bool(target.read_u32(FILE_SLOT))
            expected = [("open", b"oracle.bds", b"rb")]
            if data is not None:
                expected += [("read", 1, 20000), ("close",)]
            assert target.io_events == expected
            checks += 1
        for success in (False, True):
            seed(native, target, original, rng.randbytes(400), rng.randbytes(400))
            output = path if success else Path(directory) / "missing" / "board.bds"
            target.open_succeeds = success
            target.call(0x0040CC90, target.PATH)
            native.call("dxball_write_board_bank", str(output).encode())
            assert_memory(native, target)
            assert bool(native.file.value) == bool(target.read_u32(FILE_SLOT))
            expected = [("open", b"oracle.bds", b"wb")]
            if success:
                assert output.read_bytes() == target.written == original
                expected += [("write", 1, 20000), ("close",)]
            else:
                assert target.written is None and not output.exists()
            assert target.io_events == expected
            checks += 1
    return checks


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--library", type=Path, default=ROOT / "build/native/libdxball_core.so")
    parser.add_argument("--unit", choices=("board-copy", "tile-sprite", "board-render", "board-io"))
    parser.add_argument("--report", type=Path, default=ROOT / "build/reports/boards-oracle.json")
    args = parser.parse_args()
    if not __debug__:
        raise SystemExit("run without -O; oracle assertions must stay enabled")
    target = TargetOracle()
    native = Native(args.library)
    original = (ROOT / "original/DEFAULT.BDS").read_bytes()
    # Verify the oracle fixture separately from executable identity.
    import csv
    expected = next(r for r in csv.DictReader((ROOT / "config/assets.csv").open())
                    if r["filename"] == "DEFAULT.BDS")
    assert hashlib.sha256(original).hexdigest() == expected["sha256"]
    report = {"target_sha256": target.target_sha256,
              "library_sha256": hashlib.sha256(args.library.read_bytes()).hexdigest(),
              "units": {}, "byte_exact": False,
              "limits": "CRT file I/O and drawing dependencies intercepted; no Windows runtime or pixel equivalence claim."}
    for name, test in (("board-copy", test_copy), ("tile-sprite", test_sprite),
                       ("board-render", test_render), ("board-io", test_io)):
        if args.unit and name != args.unit:
            continue
        count = test(native, target, original)
        report["units"][name] = {"status": "passed", "cases": count}
        print(f"PASS {name}: {count} target differential cases", flush=True)
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, indent=2) + "\n")
    print(f"report: {args.report}")


if __name__ == "__main__":
    main()
