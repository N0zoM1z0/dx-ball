"""Actual VC4 bitmap bodies, explicitly relocated away from original code."""
import json
from pathlib import Path
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from coff import function, symbol_data
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from probe_bmp_loader import BitmapProbe
from bitmap_oracle import NativeBitmap
from test_bitmap_differential import vectors, sha


class CoffBitmap(BitmapProbe):
    def __init__(self, object_path):
        super().__init__()
        self.uc.mem_map(0x8000000, 0x20000)
        self.manifest = {}
        bindings = dict(_dxball_load_bitmap=0x8000000, _read_u32=0x8001000,
                        _dxball_bitmap_api=0x8012000, _dxball_direct_draw=0x8012020,
                        _memcpy=0x416610, _memset=0x417c40,
                        _strcpy=0x4177f0, _strcat=0x4177f8)
        prefix = symbol_data(object_path, '$SG412', 4)
        assert prefix == b'..\\\0'
        bindings['$SG412'] = 0x8011000
        self.write(bindings['$SG412'], prefix)
        api = (0x44127c, 0x441298, 0x441280, 0x44126c, 0x441264)
        self.write(0x8012000, struct.pack('<5I', *(self.import_slots[p] for p in api)))
        self.write_u32(bindings['_dxball_direct_draw'], self.DDRAW)
        for name in ('_dxball_load_bitmap', '_read_u32'):
            code, relocations = function(object_path, name)
            address = bindings[name]
            assert len(code) <= 0x1000
            for row in relocations:
                assert row['symbol'] in bindings, ('Unreviewed binding', row)
                value = bindings[row['symbol']] + row['addend']
                if row['type'] == 'REL32':
                    value -= address + row['offset'] + 4
                else:
                    assert row['type'] == 'DIR32', row
                struct.pack_into('<I', code, row['offset'], value & 0xffffffff)
            self.write(address, code)
            self.manifest[name] = dict(address=address, size=len(code), relocations=relocations,
                                       relocated_sha256=__import__('hashlib').sha256(code).hexdigest())
        self.bindings = bindings

    def invoke(self, seed, entry=0x8000000):
        return super().invoke(seed, entry)


def main():
    assert __debug__, 'Oracle assertions must stay enabled'
    limit_cpu()
    with session_lock():
        reference_path = ROOT / 'build/reports/bitmap-differential.json'
        reference_sha = sha(reference_path)
        reference = json.loads(reference_path.read_text())
        compiled = json.loads((ROOT / 'build/reports/bitmap-compile.json').read_text())
        assert reference['status'] == compiled['status'] == 'pass'
        object_path = ROOT / compiled['object']
        helper = ROOT / 'build/probes/bitmap-stack-driver.so'
        library = ROOT / 'build/native/libdxball_core.so'
        inputs = dict(reference['inputs'])
        inputs.update(compiled['inputs'])
        inputs.update({p: sha(ROOT / p) for p in ('tests/test_bitmap_coff.py', 'scripts/coff.py',
                      'scripts/compile-semantic-build.py', 'config/match-units.toml')})
        for name, value in inputs.items():
            assert sha(ROOT / name) == value, name
        assert sha(ROOT / 'config/match-units.toml') == compiled['manifest_sha256']
        assert sha(ROOT / 'scripts/compile-semantic-build.py') == compiled['driver_sha256']
        assert sha(object_path) == compiled['object_sha256']
        assert sha(library) == reference['library_sha256']
        assert sha(helper) == reference['stack_driver']['product_sha256']
        target, native = CoffBitmap(object_path), NativeBitmap(library, helper)
        assert target.target_sha256 == reference['target_sha256']
        try:
            result = vectors(target, native)
        finally:
            native.restore()
        for name, value in result.items():
            assert json.loads(json.dumps(value)) == reference[name], name
        for name, value in inputs.items():
            assert sha(ROOT / name) == value, name
        assert sha(reference_path) == reference_sha
        assert sha(object_path) == compiled['object_sha256']
        assert sha(library) == reference['library_sha256']
        assert sha(helper) == reference['stack_driver']['product_sha256']
        report = dict(status='pass', target_sha256=target.target_sha256,
                      cases=reference['cases'], total=reference['total'], inputs=inputs,
                      library_sha256=reference['library_sha256'], object_sha256=compiled['object_sha256'],
                      compiler_sha256=compiled['compiler_sha256'], emitted_functions=target.manifest,
                      bindings=target.bindings, original_reference_sha256=reference_sha,
                      stack_driver_sha256=sha(helper),
                      scope='Complete generated public/static COMDATs with explicit bindings and original CRT helpers. Same full 975 native/original vectors, counted once; unchanged original code/IAT; no exactness claim.')
        (ROOT / 'build/reports/bitmap-coff-differential.json').write_text(json.dumps(report, indent=2) + '\n')
        print('PASS VC4 bitmap:', report['total'], 'cases; complete reference vectors equal')


if __name__ == '__main__':
    main()
