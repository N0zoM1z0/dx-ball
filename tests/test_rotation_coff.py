#!/usr/bin/env python3
"""Execute compiled VC4 rotation bodies against complete original/native vectors."""
import ctypes as C
import hashlib
import json
from pathlib import Path
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from coff import function, symbol_data
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from rotation_oracle import RotationTarget, RotationNative
from test_rotation_differential import baseline, callbacks, offsets, sha


class CoffTarget(RotationTarget):
    """Relocate generated code into fresh memory; never replace original code."""

    def __init__(self, object_path):
        super().__init__()
        self.uc.mem_map(0x08000000, 0x10000)
        names = {'_dxball_render_rotated_sprite': 0x08000000,
                 '_dxball_rotated_sprite_offset': 0x08002000,
                 '_dxball_draw_rotated_sprite': 0x08004000}
        # Reviewed game globals and actual original trig/CRT helpers. These
        # helpers are dependencies of this probe, not reconstructed CRT claims.
        bindings = dict(names, **{
            '_dxball_sprite_bank': 0x421088, '_dxball_sprite_banks': 0x425980,
            '_dxball_active_surface': 0x4265CC,
            '_dxball_sine': 0x402400, '_dxball_cosine': 0x402490,
            '__adjust_fdiv': 0x42309C, '__adj_fdiv_m64': 0x416E18,
            '__ftol': 0x41678C, '_abs': 0x416780})
        self.entries = {0x4026A0: names['_dxball_render_rotated_sprite'],
                        0x402CD0: names['_dxball_rotated_sprite_offset'],
                        0x404280: names['_dxball_draw_rotated_sprite']}
        self.manifest = {}
        allowed = {struct.pack('<d', value) for value in (0.0, 2.0, 2.046, 0.5, 1.3)}
        for name, address in names.items():
            code, relocations = function(object_path, name)
            assert len(code) <= 0x2000, 'Generated function exceeds assigned memory'
            for row in relocations:
                symbol = row['symbol']
                if symbol not in bindings:
                    assert symbol.startswith('$T'), ('Unreviewed dependency', symbol)
                    data = symbol_data(object_path, symbol, 8)
                    assert bytes(data) in allowed, ('Unreviewed literal', symbol, data.hex())
                    index = sum(key.startswith('$T') for key in bindings)
                    bindings[symbol] = 0x08008000 + 8 * index
                    self.write(bindings[symbol], data)
                value = bindings[symbol] + row['addend']
                if row['type'] == 'REL32':
                    value -= address + row['offset'] + 4
                else:
                    assert row['type'] == 'DIR32', ('Unreviewed relocation', row)
                struct.pack_into('<I', code, row['offset'], value & 0xFFFFFFFF)
            self.write(address, code)
            self.manifest[name] = dict(address=address, size=len(code), relocations=relocations,
                                       relocated_sha256=hashlib.sha256(code).hexdigest())
        self.bindings = bindings

    def call(self, entry, *arguments):
        return super().call(getattr(self, 'entries', {}).get(entry, entry), *arguments)


def main():
    assert __debug__, 'Oracle assertions must stay enabled'
    limit_cpu()
    with session_lock():
        object_path = ROOT / 'build/exact/rotation.obj'
        reference_path = ROOT / 'build/reports/rotation-differential.json'
        reference = json.loads(reference_path.read_text())
        exact = json.loads((ROOT / 'build/reports/exact-replay.json').read_text())
        assert reference['status'] == 'pass'
        for path, digest in reference['inputs'].items():
            assert sha(ROOT / path) == digest, ('Stale original/native reference', path)
        library = ROOT / 'build/native/libdxball_core.so'
        assert sha(library) == reference['library_sha256']
        assert exact['manifest_sha256'] == sha(ROOT / 'config/match-units.toml')
        assert exact['builds']['rotation']['object_sha256'] == sha(object_path)
        for path, digest in exact['builds']['rotation']['inputs'].items():
            assert sha(ROOT / path) == digest, ('Stale compiler input', path)
        target, native = CoffTarget(object_path), RotationNative(library)
        assert target.target_sha256 == reference['target_sha256'] == exact['target_sha256']
        original_code = target.read(0x401000, 0x1F000)
        target.write_u32(0x42309C, 0)
        target.call(0x402250)
        native.lib.dxball_initialize_trig()
        for name, address in (('sine', 0x424650), ('cosine', 0x424BF8)):
            table = target.read(address, 1444)
            assert table == bytes((C.c_int32 * 361).in_dll(native.lib, 'dxball_' + name + '_table'))
            assert hashlib.sha256(table).hexdigest() == reference['trig_table_sha256'][name]
        buffers = {}
        result = dict(baseline=baseline(target, native, buffers),
                      callbacks=callbacks(target, native, buffers), offsets=offsets(target, native),
                      guarded_destinations=buffers)
        for name, value in result.items():
            # Saved JSON encodes event tuples as arrays; compare all values
            # through the same representation, including complete buffers.
            assert json.loads(json.dumps(value)) == reference[name], name
        assert target.read(0x401000, len(original_code)) == original_code, 'Original code changed'
        native.reset()
        inputs = dict(reference['inputs'])
        inputs.update({name: sha(ROOT / name) for name in
                       ('tests/test_rotation_coff.py', 'scripts/coff.py', 'scripts/legacy_toolchain.py',
                        'scripts/resource_limits.py', 'config/tools.lock.toml', 'config/match-units.toml')})
        report = dict(status='pass', target_sha256=target.target_sha256,
                      cases=reference['cases'], total=reference['total'], inputs=inputs,
                      library_sha256=sha(library), object_sha256=sha(object_path),
                      compiler_sha256=exact['compiler_sha256'],
                      original_reference_sha256=sha(reference_path), emitted_functions=target.manifest,
                      bindings=target.bindings,
                      scope='Generated VC4 bodies in separate executable memory; full original/native '
                            'vectors; original trig/CRT dependencies, controlled COM, normal division '
                            'branch; no original code writes; same fixtures counted once')
        output = ROOT / 'build/reports/rotation-coff-differential.json'
        output.write_text(json.dumps(report, indent=2) + '\n')
        print('PASS VC4 rotation bodies:', report['total'], 'cases; complete reference vectors equal')


if __name__ == '__main__':
    main()
