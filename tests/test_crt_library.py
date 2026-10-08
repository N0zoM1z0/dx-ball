"""Public rejection controls for whole CRT sections and explicit relocations."""
import struct
import hashlib
import importlib.util
import json
import sys
import tempfile
import unittest
from unittest.mock import patch
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import coff
from crt_library import defines, function_section, members, relocate


def object_bytes(code=b'\xe9\0\0\0\0', value=0, extra=False, relocation=1, kind=20, target=1):
    symbols = [struct.pack('<8sIhHBB',b'_probe',value,1,0x20,2,0),
               struct.pack('<8sIhHBB',b'_dep',0,0,0x20,2,0)]
    if extra:
        symbols.append(struct.pack('<8sIhHBB',b'_other',4,1,0x20,2,0))
    return (struct.pack('<HHIIIHH',0x14c,1,0,60+len(code)+10,len(symbols),0,0)
            +struct.pack('<8sIIIIIIHHI',b'.text',0,0,len(code),60,60+len(code),0,1,0,0x60000020)
            +code+struct.pack('<IIH',relocation,target,kind)+b''.join(symbols)+struct.pack('<I',4))


class Controls(unittest.TestCase):
    def section(self, raw):
        with tempfile.TemporaryDirectory() as directory:
            path=Path(directory)/'member.obj';path.write_bytes(raw)
            return function_section(path,'_probe')

    def test_ordinary_assembly_section_keeps_exact_oracle_rejection(self):
        code, relocations=self.section(object_bytes())
        self.assertEqual(len(code),5)
        with tempfile.TemporaryDirectory() as directory:
            path=Path(directory)/'member.obj';path.write_bytes(object_bytes())
            with self.assertRaises(ValueError):coff.function(path,'_probe')

    def test_section_tail_cannot_disappear(self):
        code,_=self.section(object_bytes(code=b'\xe9\0\0\0\0\xcc'))
        self.assertEqual(bytes(code),b'\xe9\0\0\0\0\xcc')

    def test_symbol_inside_section_rejected(self):
        with self.assertRaises(ValueError):self.section(object_bytes(value=1))

    def test_second_function_rejected(self):
        with self.assertRaises(ValueError):self.section(object_bytes(extra=True))

    def test_cross_section_relocation_rejected(self):
        with self.assertRaises(ValueError):self.section(object_bytes(relocation=3))

    def test_unknown_relocation_rejected(self):
        with self.assertRaises(ValueError):self.section(object_bytes(kind=7))

    def test_missing_symbol_rejected(self):
        with self.assertRaises(ValueError):self.section(object_bytes(target=999))

    def test_missing_mapping_rejected(self):
        code,relocations=self.section(object_bytes())
        with self.assertRaises(ValueError):relocate(code,relocations,0x1000,{})

    def test_wrong_mapping_changes_compared_operand(self):
        code,relocations=self.section(object_bytes())
        expected=b'\xe9'+struct.pack('<I',0x4000-0x1005)
        self.assertEqual(relocate(code,relocations,0x1000,{'_dep':0x4000}),expected)
        self.assertNotEqual(relocate(code,relocations,0x1000,{'_dep':0x4004}),expected)

    def test_truncated_archive_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            path=Path(directory)/'bad.lib';path.write_bytes(b'!<arch>\n'+b' '*59)
            with self.assertRaises(ValueError):list(members(path))

    def test_unrelated_high_byte_symbol_does_not_hide_requested_definition(self):
        raw=bytearray(object_bytes());symbol_start=struct.unpack_from('<I',raw,8)[0]
        raw[symbol_start+18:symbol_start+26]=b'\0'*4+struct.pack('<I',4)
        strings=b'?unrelated\xf2\0';raw[-4:]=struct.pack('<I',4+len(strings))+strings
        self.assertTrue(defines(bytes(raw),'_probe'))
        self.assertFalse(defines(bytes(raw),'_absent'))

    def test_evidence_replacement_cannot_relabel_parsed_bytes(self):
        module_path=Path(__file__).resolve().parents[1]/'scripts/verify-crt-provenance.py'
        spec=importlib.util.spec_from_file_location('crt_provenance',module_path)
        module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
        provider=dict(id='ghidra',name='Ghidra',version='12.1.4')
        record=dict(evidence=dict(subject=dict(digest=dict(sha256='target')),provider=provider,
                                  analysis_profile=dict(provider=provider)),
                    result=dict(procedure=dict(address='0x1000',body=dict(available=True))))
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory);run=root/'closed';run.mkdir();(run/'close.json').write_text('{}')
            path=run/'00-analyze_function.json';before=json.dumps(record).encode();path.write_bytes(before)
            original_read=Path.read_bytes
            def replaced_after_read(p):
                raw=original_read(p)
                if p==path:p.write_bytes(raw.replace(b'0x1000',b'0x1004'))
                return raw
            with patch.object(Path,'read_bytes',replaced_after_read):
                bodies,_,_=module.observations(root,'target',provider)
            self.assertEqual(bodies[0x1000][2],hashlib.sha256(before).hexdigest())
            self.assertNotEqual(bodies[0x1000][2],module.digest(path))


if __name__=='__main__':unittest.main()
