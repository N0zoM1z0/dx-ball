#!/usr/bin/env python3
"""Compare resource owner source with actual hash-pinned x86 execution."""
import argparse
import ctypes as C
import hashlib
import json
import os
from pathlib import Path
import struct
import tempfile

from resources_oracle import (ResourceTarget, ResourceNative, BANKS, SPRITE_BANK,
                              FONT_BANK, LIVE_PALETTE, SAVED_PALETTE)
from target_oracle import ROOT


def sbk(records):
    result = struct.pack("<i", len(records))
    for width, height, code, baseline, pixels in records:
        result += struct.pack("<iiBi", width, height, code, baseline) + pixels
    return result


def pcx(xmax, ymax, encoded):
    header = bytearray(128)
    struct.pack_into("<hh", header, 8, xmax, ymax)
    return bytes(header) + encoded + bytes(range(256)) * 3


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--library", type=Path, default=ROOT / "build/native/libdxball_core.so")
    args = parser.parse_args()
    target, native = ResourceTarget(), ResourceNative(args.library.resolve())
    cases = {}

    def reset():
        target.reset()
        native.reset()

    def trace(label):
        assert target.events == native.events, (label, target.events[:12], native.events[:12])

    def bank(label, number):
        expected, actual = target.bank_snapshot(number), native.bank_snapshot(number)
        assert expected == actual, (label, number, "bank state differs")

    for address, name, global_address, host in [
        (0x403E70, "select_sprite_bank", SPRITE_BANK, native.bank),
        (0x403E90, "select_font_bank", FONT_BANK, native.font),
    ]:
        for number in (-1, 0, 1, 2, 7, 0x7FFFFFFF):
            target.call(address, number)
            getattr(native.lib, "dxball_" + name)(number)
            assert target.read_u32(global_address) == host.value & 0xFFFFFFFF
        cases[name] = 6

    draw_functions = [(0x404180, "draw_sprite"), (0x404040, "draw_keyed_sprite"),
                      (0x4040B0, "blt_sprite"), (0x403F70, "blt_keyed_sprite"),
                      (0x4041F0, "stretch_keyed_sprite")]
    for address, name in draw_functions:
        count = 0
        for number in range(3):
            for slot in (1, 127, 254):
                reset()
                target.seed(number, slot)
                native.seed(number, slot)
                target.write_u32(SPRITE_BANK, number)
                native.bank.value = number
                for x, y in [(-27, -9), (0, 0), (619, 470), (100000, -100000)]:
                    arguments = (slot, x, y, 31, 17) if name.startswith("stretch") else (slot, x, y)
                    native.events = []
                    target.call(address, *arguments)
                    getattr(native.lib, "dxball_" + name)(*arguments)
                    trace(name)
                    count += 1
        cases[name] = count

    cases["release_sprite"] = 0
    for number in range(3):
        for state in ("empty", "surface", "null"):
            reset()
            target.write_u32(SPRITE_BANK, number)
            native.bank.value = number
            if state != "empty":
                record = target.seed(number, 254, null=state == "null")
                native.seed(number, 254, null=state == "null")
            target.call(0x404BE0, 254)
            native.lib.dxball_release_sprite(254)
            trace(state)
            bank(state, number)
            assert len(target.freed) == (state != "empty")
            if state != "empty":
                assert record in target.freed
            cases["release_sprite"] += 1

    cases["capture_sprite"] = 0
    for number in range(3):
        for failure in (False, True):
            for retries in (0, 2):
                reset()
                target.write_u32(SPRITE_BANK, number)
                native.bank.value = number
                target.seed(number, 5)
                native.seed(number, 5)
                target.fail_create = native.fail_create = failure
                target.desc_failures = native.desc_failures = retries
                target.call(0x4042B0, 5, -7, 11, 9, 6)
                native.lib.dxball_capture_sprite(5, -7, 11, 9, 6)
                trace("capture")
                # Pitch is uninitialized after failure; only initialized fields
                # and the NULL surface output are in the acceptance domain.
                if failure:
                    t = target.bank_snapshot(number)[3][5]
                    n = native.bank_snapshot(number)[3][5]
                    assert t[0][:2] == n[0][:2] and t[0][3:] == n[0][3:] and t[1:] == n[1:]
                else:
                    bank("capture", number)
                cases["capture_sprite"] += 1

    cases["load_sprite_bank"] = 0
    original_cwd = Path.cwd()
    try:
        # Target strcpy has a 20-byte owner field; real basenames fit it.
        os.chdir(ROOT / "original")
        for index, path in enumerate(sorted(Path.cwd().glob("*.SBK"))):
            reset()
            number, mode = index % 3, 1 if index % 2 else 0
            target.write_u32(SPRITE_BANK, 2)
            native.bank.value = 2
            for slot in (1, 253, 254):
                target.seed(number, slot)
                native.seed(number, slot)
            target.set_file(path.name, path.read_bytes())
            target.desc_failures = native.desc_failures = 2
            target.lock_failures = native.lock_failures = 3
            target.call(0x404610, number, mode, target.PATH)
            native.lib.dxball_load_sprite_bank(number, mode, path.name.encode())
            trace(path.name)
            bank(path.name, number)
            assert target.read_u32(SPRITE_BANK) == native.bank.value == 2
            assert target.io_events[0] == ("open", path.name.encode(), b"rb")
            assert target.io_events[-1] == ("close",)
            assert len(target.freed) == target.read_u32(BANKS + number * 1048 + 1020) + 2
            cases["load_sprite_bank"] += 1
            print(f"PASS SBK {path.name}", flush=True)
        with tempfile.TemporaryDirectory() as directory:
            os.chdir(directory)
            for empty, failure in [(False, False), (False, True), (True, False)]:
                reset()
                name = "fixture.sbk"
                data = sbk([] if empty else [(3, 2, 0xE9, -4, bytes(range(6)))])
                Path(name).write_bytes(data)
                for slot in (0, 1, 253, 254):
                    target.seed(1, slot)
                    native.seed(1, slot)
                target.write_u32(BANKS + 1048 + 1020, 91)
                native.banks[1].count = 91
                target.fail_create = native.fail_create = failure
                target.set_file(name, data)
                target.call(0x404610, 1, 2, target.PATH)
                native.lib.dxball_load_sprite_bank(1, 2, name.encode())
                trace("SBK edge")
                if failure:
                    t, n = target.bank_snapshot(1), native.bank_snapshot(1)
                    assert t[:3] == n[:3]
                    assert t[3][1][0][:2] == n[3][1][0][:2]
                    assert t[3][1][0][3:] == n[3][1][0][3:] and t[3][1][1:] == n[3][1][1:]
                    assert target.read_u32(SPRITE_BANK) == native.bank.value == 1
                    assert target.io_events[-1][0] != "close"
                else:
                    bank("SBK edge", 1)
                    assert target.read_u32(SPRITE_BANK) == native.bank.value == 0
                cases["load_sprite_bank"] += 1
        os.chdir(ROOT / "original")

        cases["find_glyph"] = cases["draw_glyph"] = 0
        for number, font in enumerate(("SFONT.SBK", "SYSFONT.SBK", "THEFONT.SBK")):
            reset()
            target.set_file(font, Path(font).read_bytes())
            target.call(0x404610, number, 1, target.PATH)
            native.lib.dxball_load_sprite_bank(number, 1, font.encode())
            target.write_u32(FONT_BANK, number)
            native.font.value = number
            for code in range(256):
                result = target.call(0x404E40, code)
                assert result == native.lib.dxball_find_glyph(bytes([code])), (font, code)
                cases["find_glyph"] += 1
                native.events = []
                result = target.call(0x404CF0, code, -13, 97)
                assert result == native.lib.dxball_draw_glyph(bytes([code]), -13, 97), (font, code)
                trace((font, code))
                cases["draw_glyph"] += 1
        reset()
        assert target.call(0x404E40, 65) == native.lib.dxball_find_glyph(b"A") == 1
        cases["find_glyph"] += 1

        cases["load_pcx"] = cases["load_live_palette"] = cases["load_saved_palette"] = 0
        def test_pcx(name, data, mode, x, y, width=640, height=480, retries=0):
            reset()
            surface = target.surface(width, height)
            host_surface = native.surface(width, height)
            target.lock_failures = native.lock_failures = retries
            target.set_file(name, data)
            target.call(0x409BB0, surface, target.PATH, mode, x, y)
            native.lib.dxball_load_pcx(host_surface, name.encode(), mode, x, y)
            trace(name)
            model = target.surfaces[surface]
            actual = bytes(native.surfaces[host_surface]["pixels"])
            assert target.read(model["pixels"], model["pitch"] * height) == actual, (name, mode, x, y, "pixels")
            assert target.read(LIVE_PALETTE, 1024) == bytes(native.live)
            assert target.read(SAVED_PALETTE, 1024) == bytes(native.saved)
            cases["load_pcx"] += 1

        for path in sorted(Path.cwd().glob("*.PCX")):
            data = path.read_bytes()
            for mode in (0, 1, 2):
                test_pcx(path.name, data, mode, 0, 0, retries=2)
            print(f"PASS PCX {path.name}", flush=True)
            for address, name in [(0x409790, "load_live_palette"), (0x4098F0, "load_saved_palette")]:
                reset()
                target.set_file(path.name, data)
                target.call(address, target.PATH)
                getattr(native.lib, "dxball_" + name)(path.name.encode())
                trace(name)
                assert target.read(LIVE_PALETTE, 1024) == bytes(native.live)
                assert target.read(SAVED_PALETTE, 1024) == bytes(native.saved)
                cases[name] += 1
        with tempfile.TemporaryDirectory() as directory:
            os.chdir(directory)
            fixtures = [(0, 0, b"\x07"), (3, 2, bytes(range(40))),
                        (3, 2, b"\xff\xe9"), (1, 1, b"\xc0\x17\xc2\x23"),
                        (9, 3, b"\xca\x44\xc5\x55\xd4\x66"),
                        (-1, 7, b"\x04"), (2, 2, b"\xc5\xc2")]
            for xmax, ymax, encoded in fixtures:
                data = pcx(xmax, ymax, encoded)
                Path("fixture.pcx").write_bytes(data)
                for x, y in [(0, 0), (-2, -1), (6, 4), (100, -1)]:
                    for mode in (0, 1, 2):
                        test_pcx("fixture.pcx", data, mode, x, y, 8, 6)
    finally:
        os.chdir(original_cwd)
        native.reset()

    report = {"target_sha256": target.target_sha256, "cases": cases,
              "total": sum(cases.values()), "scope": "target resource execution; controlled CRT/DirectDraw boundaries",
              "source_sha256": hashlib.sha256((ROOT / "src/resources.c").read_bytes()).hexdigest()}
    output = ROOT / "build/reports/resources-differential.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
