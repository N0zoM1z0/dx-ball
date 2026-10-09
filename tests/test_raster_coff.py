#!/usr/bin/env python3
"""Execute actual VC4 raster COMDATs in memory separate from original code."""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

from unicorn import UC_HOOK_CODE

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from coff import data_comdat, function, parse
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from raster_oracle import RasterTarget, RasterNative, api_muldiv
from test_raster_differential import vectors, sha


class CoffTarget(RasterTarget):
    def __init__(self, object_path):
        super().__init__()
        self.uc.mem_map(0x08000000, 0x20000)
        names = ('_dxball_fill_horizontal_span', '_dxball_fill_polygon@20',
                 '_dxball_fill_polygon_clipped@20', '_dxball_fill_triangle',
                 '?fill_polygon@@YAXPAEHPBUDxBallRasterPoint@@HEH@Z',
                 '?sort_edges@@YAXPAPAURasterEdge@@HH@Z',
                 '??0DxBallFixedPoint@@QAE@XZ', '??1DxBallFixedPoint@@QAE@XZ',
                 '??0DxBallFixedPoint@@QAE@H@Z', '??BDxBallFixedPoint@@QAEHXZ',
                 '??KDxBallFixedPoint@@QAE?AV0@V0@@Z', '_dxball_fixed_divide',
                 '??MDxBallFixedPoint@@QAEHV0@@Z', '??YDxBallFixedPoint@@QAEAAV0@V0@@Z')
        bindings = {name: 0x08000000 + i * 0x1000 for i, name in enumerate(names)}
        bindings.update(_dxball_raster_ops=0x08010000, _memmove=0x417ca0,
                        __except_list=0, ___CxxFrameHandler=0x418570)
        # Allocation/free remain cdecl. MulDiv restores its actual stdcall ABI.
        self.write(0x08010000, struct.pack('<III', 0x417770, 0x417750, 0x50d000))
        self.uc.hook_add(UC_HOOK_CODE, self._math, begin=0x50d000, end=0x50d000)
        data, sections, symbols = parse(object_path)
        section_addresses = {}
        for name in names:
            entries = [symbol for symbol in symbols.values()
                       if symbol['name'] == name and symbol['section'] > 0]
            assert len(entries) == 1, name
            section_addresses[entries[0]['section']] = bindings[name]
        metadata_sections = sorted({symbol['section'] for symbol in symbols.values()
                                    if symbol['name'].startswith('$T') and symbol['section'] > 0
                                    and sections[symbol['section'] - 1]['flags'] & 0x1040 == 0x1040})
        assert len(metadata_sections) == 4, 'Expected triangle and three class EH tables'
        for index, number in enumerate(metadata_sections):
            section_addresses[number] = 0x08011000 + index * 0x1000
        for symbol in symbols.values():
            if symbol['section'] in section_addresses and symbol['type'] != 0x20:
                bindings[symbol['name']] = section_addresses[symbol['section']] + symbol['value']
        self.manifest, self.metadata_manifest = {}, {}

        def relocate(code, rows, address):
            for row in rows:
                assert row['symbol'] in bindings, ('Unreviewed dependency', row)
                value = bindings[row['symbol']] + row['addend']
                if row['type'] == 'REL32':
                    value -= address + row['offset'] + 4
                else:
                    assert row['type'] == 'DIR32', row
                struct.pack_into('<I', code, row['offset'], value & 0xffffffff)
            return hashlib.sha256(code).hexdigest()

        for name in names:
            address = bindings[name]
            code, relocations = function(object_path, name)
            assert len(code) <= 0x1000
            digest = relocate(code, relocations, address)
            self.write(address, code)
            self.manifest[name] = dict(address=address, size=len(code), relocations=relocations,
                                       relocated_sha256=digest)
        for number in metadata_sections:
            section, address = sections[number - 1], section_addresses[number]
            roots = [s['name'] for s in symbols.values() if s['section'] == number
                     and s['value'] == 0 and s['name'].startswith('$T')]
            assert len(roots) == 1
            code, relocations = data_comdat(object_path, roots[0])
            assert 0 < len(code) <= 0x1000
            digest = relocate(code, relocations, address)
            self.write(address, code)
            self.metadata_manifest[str(number)] = dict(address=address, size=len(code),
                relocations=relocations, relocated_sha256=digest)
        self.bindings = bindings
        self.entries = {0x40b4c0: bindings[names[0]], 0x40b550: bindings[names[1]],
                        0x40bb60: bindings[names[2]], 0x40ab90: bindings[names[3]]}

    def _math(self, *unused):
        import ctypes as C
        args = tuple(C.c_int32(x).value for x in self._args(3))
        self.events.append(('MulDiv', *args))
        self._return(api_muldiv(*args) & 0xffffffff, pop=12)

    def call(self, entry, *arguments):
        return super().call(getattr(self, 'entries', {}).get(entry, entry), *arguments)


def main():
    assert __debug__, 'Oracle assertions must stay enabled'
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--library', type=Path, default=ROOT / 'build/native/libdxball_core.so')
    args = parser.parse_args()
    with session_lock():
        object_path = ROOT / 'build/exact/raster.obj'
        reference_path = ROOT / 'build/reports/raster-differential.json'
        reference = json.loads(reference_path.read_text())
        compiled = json.loads((ROOT / 'build/reports/raster-compile.json').read_text())
        assert reference['status'] == compiled['status'] == 'pass'
        inputs = dict(reference['inputs'])
        inputs.update(compiled['inputs'])
        inputs.update({p: sha(ROOT / p) for p in ('tests/test_raster_coff.py', 'scripts/coff.py',
                      'scripts/legacy_toolchain.py', 'scripts/compile-semantic-build.py',
                      'config/tools.lock.toml', 'config/match-units.toml')})
        for p, value in inputs.items():
            assert sha(ROOT / p) == value, ('Stale reference/compiler input', p)
        assert sha(ROOT / 'config/match-units.toml') == compiled['manifest_sha256']
        assert sha(ROOT / 'scripts/compile-semantic-build.py') == compiled['driver_sha256']
        assert sha(object_path) == compiled['object_sha256']
        library = args.library.resolve()
        assert sha(library) == reference['library_sha256']
        target, native = CoffTarget(object_path), RasterNative(library)
        assert target.target_sha256 == reference['target_sha256']
        code, iat = target.read(0x401000, 0x1f000), target.read(0x4412a8, 4)
        try:
            result = vectors(target, native)
        finally:
            native.restore()
        for name, value in result.items():
            assert json.loads(json.dumps(value)) == reference[name], name
        assert target.read(0x401000, len(code)) == code and target.read(0x4412a8, 4) == iat
        for p, value in inputs.items():
            assert sha(ROOT / p) == value, p
        assert sha(object_path) == compiled['object_sha256'] and sha(library) == reference['library_sha256']
        report = dict(status='pass', target_sha256=target.target_sha256,
                      cases=reference['cases'], total=reference['total'], inputs=inputs,
                      library_sha256=reference['library_sha256'], object_sha256=compiled['object_sha256'],
                      compiler_sha256=compiled['compiler_sha256'], emitted_functions=target.manifest, emitted_metadata=target.metadata_manifest,
                      bindings=target.bindings, original_reference_sha256=sha(reference_path),
                      scope='Complete generated C/C++ public/static/member COMDAT bodies and EH metadata, explicit relocations and data '
                            'callback slots; real original overlap-copy dependency; controlled allocation/free '
                            'and MulDiv; full original/native vectors including complete pixel buffers; '
                            'original code/IAT untouched; same fixtures counted once; no exact claim')
        output = ROOT / 'build/reports/raster-coff-differential.json'
        output.write_text(json.dumps(report, indent=2) + '\n')
        print('PASS VC4 raster bodies:', report['total'], 'cases; complete reference vectors equal')


if __name__ == '__main__':
    main()
