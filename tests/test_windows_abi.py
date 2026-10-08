#!/usr/bin/env python3
"""Compile SDK layout checks for real i686 adapters, then execute under Wine."""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from legacy_toolchain import Toolchain, session_lock, windows_path


def digest(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--report', type=Path,
                        default=ROOT / 'build/reports/windows-abi.json')
    args = parser.parse_args()
    lock = session_lock()
    toolchain = Toolchain()
    toolchain.verify(execute=True)
    compiler = shutil.which('i686-w64-mingw32-gcc')
    if compiler is None:
        raise RuntimeError('i686 MinGW compiler is required')
    directory = ROOT / 'build/probes'
    directory.mkdir(parents=True, exist_ok=True)
    flags = ['-std=c90', '-Wall', '-Wextra', '-Wpedantic', '-Werror', '-O0']
    logs, products = [], {}
    for source in ('windows_core_abi', 'windows_directx_abi'):
        executable = directory / (source + '-mingw.exe')
        executable.unlink(missing_ok=True)
        result = subprocess.run([compiler, *flags, str(ROOT / 'tests' / (source + '.c')),
                                 '-o', str(executable)], capture_output=True, text=True)
        logs.append(result.stdout + result.stderr)
        if result.returncode:
            raise RuntimeError(result.stdout + result.stderr)
        products[source + '-mingw'] = executable
        print('MinGW ABI probe compiled:', source, flush=True)
    obj = directory / 'windows_core_abi.obj'
    legacy_flags = ['/nologo', '/c', '/Od', '/MT']
    logs.append(toolchain.compile(ROOT / 'tests/windows_core_abi.c', obj, legacy_flags).stdout)
    executable = directory / 'windows_core_abi-vc4.exe'
    executable.unlink(missing_ok=True)
    logs.append(toolchain.run('link.exe', ['/NOLOGO', '/MACHINE:IX86',
        '/SUBSYSTEM:CONSOLE', '/INCREMENTAL:NO', '/PDB:NONE',
        '/OUT:' + windows_path(executable), windows_path(obj)]).stdout)
    products['windows_core_abi-vc4'] = executable
    print('Pinned VC4 ABI probe compiled.', flush=True)
    results = {}
    for name, executable in products.items():
        run = subprocess.run(['xvfb-run', '-a', 'wine', str(executable)],
            env=toolchain.env, capture_output=True, text=True, timeout=60, check=True)
        logs.append(run.stdout + run.stderr)
        lines = [line.strip() for line in run.stdout.splitlines() if line.strip()]
        assert lines and lines[0].startswith('{'), (name, run.stdout)
        # Wine/Xvfb can send its display shutdown notice to stdout after the
        # console process exits. Preserve the log and reject any other chatter.
        assert all(line.startswith('X connection to :') and
                   line.endswith('(explicit kill or server shutdown).')
                   for line in lines[1:]), (name, run.stdout)
        results[name] = json.loads(lines[0])
        print(name, lines[0], flush=True)
    expected_core = dict(pointer=4, message=28, window_class=40, security=12,
        version=148, counter=8, midi_header=64, midi_property=8,
        sound_record=36, sound_desc=20, projectile_node=24, projectile_list=12,
        fire_node=20, fire_list=12)
    assert results['windows_core_abi-mingw'] == results['windows_core_abi-vc4'] == expected_core
    assert results['windows_directx_abi-mingw'] == dict(surface_desc=108,
        color_fill=100, sound_desc_v1=20, sound_desc_modern=36,
        sound_buffer_slots=21, sound_restore_slot=20)
    inputs = [Path(__file__), ROOT / 'tests/windows_core_abi.c',
        ROOT / 'tests/windows_directx_abi.c', ROOT / 'scripts/legacy_toolchain.py',
        ROOT / 'scripts/resource_limits.py', ROOT / 'config/tools.lock.toml']
    inputs += sorted(ROOT.glob('src/*.h'))
    sdk = Path('/usr/i686-w64-mingw32/include')
    report = dict(status='pass', results=results,
        inputs={str(p.relative_to(ROOT)): digest(p) for p in inputs},
        compiler_sha256=toolchain.lock['compiler_sha256'],
        legacy_sdk_sha256=toolchain.lock['include_tree_sha256'],
        mingw_compiler_sha256=digest(compiler),
        mingw_sdk_headers={name: digest(sdk / name) for name in
            ('windows.h', 'winuser.h', 'winnt.h', 'windef.h', 'mmsystem.h', 'dsound.h', 'ddraw.h')},
        executables={name: digest(p) for name, p in products.items()},
        legacy_object_sha256=digest(obj), mingw_flags=flags, legacy_flags=legacy_flags,
        scope='SDK record sizes/offsets and COM slots; no driver or original-entry acceptance')
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, indent=2) + '\n')
    (directory / 'windows-abi.log').write_text('\n'.join(logs))
    print('Windows SDK ABI checks passed.', flush=True)


if __name__ == '__main__':
    main()
