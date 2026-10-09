#!/usr/bin/env python3
"""Execute complete VC4/MinGW termination objects with resolved relocations."""
if not __debug__:
    raise RuntimeError('Termination object comparisons require nonoptimized Python')

import argparse
import hashlib
import json
from pathlib import Path
import shutil
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(ROOT / 'scripts'), str(ROOT / 'tests')]
from coff import parse, region
from legacy_toolchain import Toolchain, session_lock
from resource_limits import limit_cpu
from termination_oracle import Target, ENTRIES, WIDTHS
from test_termination_differential import compare, inputs, sha, compiler_inputs


class CoffTarget(Target):
    BASE, COMMON = 0x08000000, 0x080FF000

    def __init__(self, path):
        super().__init__()
        data, sections, symbols = parse(path)
        assert len(sections) < 128
        self.uc.mem_map(self.BASE, 0x100000)
        addresses = {i + 1: self.BASE + i * 0x2000 for i in range(len(sections))}
        common = {'_' + name: self.COMMON + i * 0x40 for i, name in enumerate(WIDTHS)}
        def resolve(symbol):
            if symbol['section'] == 0 and symbol['name'] in common:
                assert symbol['storage'] == 2 and symbol['value'] == WIDTHS[symbol['name'][1:]], symbol
                return common[symbol['name']]
            assert symbol['section'] > 0, ('Unresolved termination dependency', symbol)
            assert symbol['value'] <= sections[symbol['section'] - 1]['size']
            return addresses[symbol['section']] + symbol['value']
        def named(name):
            matches = [s for s in symbols.values() if s['name'] == '_' + name]
            assert len(matches) == 1, (name, matches)
            return matches[0]
        self.storage = {name: resolve(named(name)) for name in WIDTHS}
        for name, width in WIDTHS.items():
            symbol = named(name)
            if symbol['section'] > 0:
                assert symbol['value'] + width <= sections[symbol['section'] - 1]['size']
        ranges = [(address, address + WIDTHS[name]) for name, address in self.storage.items()]
        assert all(a1 <= b0 or b1 <= a0 for i, (a0, a1) in enumerate(ranges)
                   for b0, b1 in ranges[i + 1:]), 'Overlapping generated globals'
        self.entries = {}
        for name in ENTRIES:
            symbol = named('dxball_' + name)
            assert symbol['section'] > 0 and symbol['type'] == 0x20
            self.entries[name] = resolve(symbol)
        self.sections = []
        for index, section in enumerate(sections, 1):
            assert section['size'] <= 0x2000
            code = bytearray(region(data, section['data'], section['size'])) if section['data'] else bytearray(section['size'])
            occupied, relocations = set(), []
            for i in range(section['relocation_count']):
                offset, symbol_index, kind = struct.unpack('<IIH', region(data, section['relocations'] + i * 10, 10))
                assert kind in (6, 7, 20) and symbol_index in symbols
                assert offset + 4 <= len(code) and not occupied.intersection(range(offset, offset + 4))
                occupied.update(range(offset, offset + 4))
                symbol = symbols[symbol_index]
                addend = struct.unpack_from('<I', code, offset)[0]
                value = resolve(symbol) + addend
                if kind == 20:
                    value -= addresses[index] + offset + 4
                elif kind == 7:
                    value -= self.BASE
                struct.pack_into('<I', code, offset, value & 0xFFFFFFFF)
                relocations.append(dict(offset=offset, kind=kind, symbol=symbol['name'],
                                        addend=addend, resolved=value & 0xFFFFFFFF))
            self.write(addresses[index], code)
            self.sections.append(dict(index=index, bytes=len(code), relocations=relocations,
                                      relocated_sha256=hashlib.sha256(code).hexdigest()))
        self.write_u32(self.storage['dxball_termination_ops'], self.EXIT)

    def exit_hook(self, uc, address, size, userdata):
        self.platform_exit(self._args(1)[0])
        self._return()  # Explicit portable C dependency bridge uses cdecl.


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/reports/termination-coff.json')
    args = parser.parse_args()
    output = args.output.resolve()
    assert output.is_relative_to(ROOT / 'build/reports') or output.is_relative_to(ROOT / '.analysis')
    assert not output.is_relative_to(ROOT / '.analysis/checkpoints')
    limit_cpu()
    with session_lock():
        import unicorn.unicorn_py3.arch.intel
        tool = Toolchain()
        tool.verify(execute=True)
        original = Target()
        directory = ROOT / 'build/probes/termination'
        directory.mkdir(parents=True, exist_ok=True)
        frozen = inputs()
        for p in (Path(__file__), ROOT / 'scripts/coff.py', ROOT / 'config/tools.lock.toml'):
            frozen[str(p)] = sha(p)
        gcc = Path(shutil.which('i686-w64-mingw32-gcc')).resolve()
        frozen[str(gcc)] = sha(gcc)
        frozen.update(compiler_inputs(gcc))
        for name in ('cl.exe', 'c1.exe', 'c2.exe', 'mspdb40.dll'):
            path = tool.path / 'bin' / name
            frozen[str(path)] = sha(path)
        products = {}
        for profile in ('vc40', 'mingw'):
            path = directory / ('termination-' + profile + '.obj')
            if profile == 'vc40':
                flags = ['/nologo', '/c', '/O2', '/Gy', '/G5', '/MT']
                result = tool.compile(ROOT / 'src/termination.c', path, flags)
                command = dict(flags=flags, compiler_sha256=tool.lock['compiler_sha256'])
            else:
                flags = ['-std=c90', '-Wall', '-Wextra', '-Wpedantic', '-Werror', '-O2']
                command = [str(gcc), *flags, '-c', str(ROOT / 'src/termination.c'), '-o', str(path)]
                result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
                result.check_returncode()
            (directory / (profile + '-compiler.log')).write_text(result.stdout)
            frozen[str(path)] = sha(path)
            maintained = CoffTarget(path)
            products[profile] = dict(object_sha256=sha(path), compiler=command,
                                     sections=maintained.sections, **compare(original, maintained))
        assert products['vc40']['observations_sha256'] == products['mingw']['observations_sha256']
        for name, digest in frozen.items():
            assert sha(name) == digest, name
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(dict(status='pass', inputs=frozen,
            target_sha256=original.target_sha256, products=products,
            limitations=['Generated-code semantics with controlled cdecl callbacks/platform bridge; no exactness claim.',
                         'Original ExitProcess uses stdcall; portable object dependency bridge uses cdecl.',
                         'Profiles repeat the same original cases, counted once.']), indent=2) + '\n')
        print('CRT termination original/objects:', {name: value['total'] for name, value in products.items()})


if __name__ == '__main__':
    main()
