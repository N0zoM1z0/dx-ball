#!/usr/bin/env python3
"""Adversarial checks that exact acceptance cannot hide corrupt inputs."""
import copy
import importlib.util
from pathlib import Path
import struct
import sys
import tempfile
import tomllib
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import coff

spec = importlib.util.spec_from_file_location("exact_replay", ROOT / "scripts/replay-exact-units.py")
replay = importlib.util.module_from_spec(spec)
spec.loader.exec_module(replay)


class ExactOracleTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        _, _, image = replay.verify_target.verify()
        cls.pe = replay.pefile.PE(data=image)
        manifest = tomllib.loads((ROOT / "config/match-units.toml").read_text())
        cls.units = manifest["units"]
        cls.builds = manifest["builds"]
        cls.object = ROOT / "build/exact/boards.obj"
        cls.data, cls.sections, cls.symbols = coff.parse(cls.object)

    def mutate(self, unit, mutator, object_path=None):
        data = bytearray(self.data if object_path is None else object_path.read_bytes())
        mutator(data)
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "mutant.obj"
            path.write_bytes(data)
            return replay.compare(path, unit, self.pe)

    def section(self, symbol):
        entry = next(s for s in self.symbols.values() if s["name"] == symbol and s["section"] > 0)
        return entry, self.sections[entry["section"] - 1]

    def fixed_metadata(self):
        unit = self.units["fixed-point-divide"]
        object_path = ROOT / self.builds[unit["build"]]["object"]
        _, sections, symbols = coff.parse(object_path)
        metadata = unit["data_comdats"][0]
        symbol = next(s for s in symbols.values()
                      if s["name"] == metadata["symbol"] and s["section"] > 0)
        return unit, object_path, symbol, sections[symbol["section"] - 1]

    def test_baseline_all_units(self):
        for unit in self.units.values():
            object_path = ROOT / self.builds[unit["build"]]["object"]
            self.assertTrue(replay.compare(object_path, unit, self.pe)["exact"])

    def test_instruction_corruption_is_not_exact(self):
        unit = self.units["select-surface"]
        _, section = self.section(unit["symbol"])
        result = self.mutate(unit, lambda data: data.__setitem__(section["data"], 0x90))
        self.assertFalse(result["exact"])
        self.assertGreater(result["difference_count"], 0)

    def test_static_function_keeps_complete_comdat_extent(self):
        unit = self.units["select-surface"]
        index = next(i for i, s in self.symbols.items() if s["name"] == unit["symbol"])
        symbol_offset = struct.unpack_from("<I", self.data, 8)[0]
        result = self.mutate(unit, lambda data: data.__setitem__(symbol_offset + index * 18 + 16, 3))
        self.assertTrue(result["exact"])
        self.assertEqual(result["object_size"], unit["size"])

    def test_static_alias_cannot_hide_another_function_in_section(self):
        unit = self.units["select-surface"]
        selected, _ = self.section(unit["symbol"])
        index = next(i for i, s in self.symbols.items()
                     if s["type"] == 0x20 and s["section"] > 0 and s["name"] != unit["symbol"])
        symbol_offset = struct.unpack_from("<I", self.data, 8)[0]

        def mutation(data):
            position = symbol_offset + index * 18
            struct.pack_into("<Ih", data, position + 8, 0, selected["section"])
            data[position + 16] = 3

        with self.assertRaises(ValueError):
            self.mutate(unit, mutation)

    def test_matching_prefix_with_extra_code_is_not_exact(self):
        unit = self.units["select-surface"]
        symbol, section = self.section(unit["symbol"])
        header_offset = 20 + (symbol["section"] - 1) * 40 + 16
        result = self.mutate(unit, lambda data: struct.pack_into("<I", data, header_offset, section["size"] + 1))
        self.assertFalse(result["exact"])
        self.assertEqual(result["object_size"], unit["size"] + 1)

    def test_wrong_relocation_destination_is_not_exact(self):
        unit = copy.deepcopy(self.units["select-surface"])
        unit["relocations"][0]["target"] += 4
        self.assertFalse(replay.compare(self.object, unit, self.pe)["exact"])

    def test_missing_relocation_is_rejected(self):
        unit = copy.deepcopy(self.units["select-surface"])
        unit["relocations"] = []
        with self.assertRaises(ValueError):
            replay.compare(self.object, unit, self.pe)

    def test_changed_addend_is_rejected(self):
        unit = self.units["select-surface"]
        _, section = self.section(unit["symbol"])
        with self.assertRaises(ValueError):
            self.mutate(unit, lambda data: struct.pack_into("<I", data, section["data"] + 10, 4))

    def test_changed_mapped_literal_is_rejected(self):
        unit = self.units["read-board-bank"]
        row = next(r for r in unit["relocations"] if "data_hex" in r)
        symbol, section = self.section(row["symbol"])
        with self.assertRaises(ValueError):
            self.mutate(unit, lambda data: data.__setitem__(section["data"] + symbol["value"], ord("w")))

    def test_metadata_corruption_is_not_exact(self):
        unit, object_path, _, section = self.fixed_metadata()
        result = self.mutate(unit, lambda data: data.__setitem__(
            section["data"], data[section["data"]] ^ 1), object_path)
        self.assertFalse(result["exact"])
        self.assertEqual(result["code_difference_count"], 0)
        self.assertGreater(result["data_comdats"][0]["difference_count"], 0)
        self.assertEqual(result["target_size"], unit["size"])

    def test_missing_metadata_attestation_is_rejected(self):
        unit, object_path, _, _ = self.fixed_metadata()
        unit = copy.deepcopy(unit)
        del unit["data_comdats"]
        with self.assertRaises(ValueError):
            replay.compare(object_path, unit, self.pe)

    def test_missing_metadata_relocation_is_rejected(self):
        unit, object_path, _, _ = self.fixed_metadata()
        unit = copy.deepcopy(unit)
        unit["data_comdats"][0]["relocations"].pop()
        with self.assertRaises(ValueError):
            replay.compare(object_path, unit, self.pe)

    def test_matching_metadata_prefix_with_extra_bytes_is_not_exact(self):
        unit, object_path, symbol, section = self.fixed_metadata()
        header_offset = 20 + (symbol["section"] - 1) * 40 + 16
        result = self.mutate(unit, lambda data: struct.pack_into(
            "<I", data, header_offset, section["size"] + 1), object_path)
        self.assertFalse(result["exact"])
        self.assertEqual(result["code_difference_count"], 0)
        self.assertEqual(result["data_comdats"][0]["object_size"],
                         unit["data_comdats"][0]["size"] + 1)
        self.assertEqual(result["difference_count"], 1)
        self.assertEqual(result["target_size"], unit["size"])

    def test_wrong_target_hash_is_rejected(self):
        image = bytearray((ROOT / "original/DXBALL.EXE").read_bytes())
        image[0x500] ^= 1
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "DXBALL.EXE"
            path.write_bytes(image)
            with self.assertRaises(ValueError):
                replay.verify_target.verify(path)


if __name__ == "__main__":
    unittest.main()
