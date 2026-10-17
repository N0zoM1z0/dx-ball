"""Reject a byte-equal comparison whose COFF label would link elsewhere."""
import importlib.util
from pathlib import Path
import struct
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("exact_replay", ROOT / "scripts/replay-exact-units.py")
replay = importlib.util.module_from_spec(spec)
spec.loader.exec_module(replay)


class Image:
    class OPTIONAL_HEADER:
        ImageBase = 0x400000

    def __init__(self, contents):
        self.contents = contents

    def get_data(self, offset, size):
        assert offset == 0x1000 and size == 8
        return self.contents


class LocalTargetTests(unittest.TestCase):
    def compare(self, label_value=4, label_section=1, target=0x401004, changed_byte=False):
        # This is a COFF/relocation fixture, with opaque bytes rather than an
        # executable. The independently declared target image stays fixed when
        # only the object's internal label definition changes.
        header_size = 20 + 40
        code = bytes(8)
        relocation_offset = header_size + len(code)
        symbol_offset = relocation_offset + 10
        header = struct.pack("<HHIIIHH", 0x14C, 1, 0, symbol_offset, 2, 0, 0)
        section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code),
                              header_size, relocation_offset, 0, 1, 0, 0x60501020)
        relocation = struct.pack("<IIH", 0, 1, 6)
        owner = struct.pack("<8sIhHBB", b"_entry", 0, 1, 0x20, 2, 0)
        label = struct.pack("<8sIhHBB", b"$Lcase", label_value, label_section,
                            0, 2 if label_section == 0 else 3, 0)
        original = bytearray(struct.pack("<I", target) + bytes(4))
        if changed_byte:
            original[-1] = 1
        unit = dict(symbol="_entry", target_address=0x401000, size=8,
                    relocations=[dict(offset=0, type="DIR32", symbol="$Lcase", addend=0, target=target)])
        with tempfile.TemporaryDirectory() as directory:
            obj = Path(directory) / "labels.obj"
            obj.write_bytes(header + section + code + relocation + owner + label + struct.pack("<I", 4))
            return replay.compare(obj, unit, Image(original))

    def test_matching_local_definition_is_exact(self):
        self.assertTrue(self.compare()["exact"])

    def test_changed_local_definition_cannot_claim_exact(self):
        with self.assertRaisesRegex(ValueError, "local target"):
            self.compare(label_value=6)

    def test_external_definition_uses_explicit_target(self):
        self.assertTrue(self.compare(label_value=0, label_section=0, target=0x417000)["exact"])

    def test_nonexact_candidate_keeps_explicit_mapping(self):
        result = self.compare(label_value=6, changed_byte=True)
        self.assertFalse(result["exact"])
        self.assertEqual(result["difference_count"], 1)


if __name__ == "__main__":
    unittest.main()
