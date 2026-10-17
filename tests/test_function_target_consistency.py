"""Keep known function relocation targets consistent with the source catalog."""
import copy
import importlib.util
from pathlib import Path
import tomllib
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("tracking", ROOT / "scripts/validate-tracking.py")
tracking = importlib.util.module_from_spec(spec)
spec.loader.exec_module(tracking)


class FunctionTargetTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.manifest = tomllib.loads((ROOT / "config/match-units.toml").read_text())

    def test_current_catalog_agrees(self):
        self.assertGreater(tracking.validate_function_targets(self.manifest), 0)

    def test_wrong_game_call_target_is_rejected(self):
        manifest = copy.deepcopy(self.manifest)
        unit = manifest["candidates"]["hit-board-tile"]
        binding = next(r for r in unit["relocations"] if r["symbol"] == "_dxball_screen_pan")
        binding["target"] += 1
        with self.assertRaisesRegex(ValueError, "function target.*hit-board-tile.*_dxball_screen_pan"):
            tracking.validate_function_targets(manifest)

    def fixture(self):
        # Constructed metadata fixture: the current manifest has no attached
        # metadata relocations to catalogued functions. It is not game evidence.
        return {"units": {
            "callee": dict(symbol="_callee", target_address=0x401000, relocations=[]),
            "caller": dict(symbol="_caller", target_address=0x402000, relocations=[],
                           data_comdats=[dict(symbol="_table", relocations=[
                               dict(symbol="_callee", target=0x401000, addend=4)])]),
        }}

    def test_metadata_checks_base_target_without_folding_addend(self):
        manifest = self.fixture()
        self.assertEqual(tracking.validate_function_targets(manifest), 1)
        binding = manifest["units"]["caller"]["data_comdats"][0]["relocations"][0]
        binding["target"] += 4
        with self.assertRaisesRegex(ValueError, "function target.*caller/_table.*_callee"):
            tracking.validate_function_targets(manifest)

    def test_unlisted_symbols_retain_explicit_mapping(self):
        manifest = self.fixture()
        manifest["units"]["caller"]["relocations"] = [
            dict(symbol=name, target=0x450000, addend=4)
            for name in ("__imp__Function@0", "_data", "$L1")]
        self.assertEqual(tracking.validate_function_targets(manifest), 1)

    def test_declared_aliases_allow_either_entry(self):
        manifest = self.fixture()
        manifest["units"]["callee-alias"] = dict(
            symbol="_callee", target_address=0x403000, relocations=[])
        binding = manifest["units"]["caller"]["data_comdats"][0]["relocations"][0]
        binding["target"] = 0x403000
        self.assertEqual(tracking.validate_function_targets(manifest), 1)


if __name__ == "__main__":
    unittest.main()
