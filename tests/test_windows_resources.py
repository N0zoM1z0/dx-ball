#!/usr/bin/env python3
"""Compare linked resources and SDK-decoded icons with a resource-free control."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from legacy_toolchain import Toolchain, session_lock, windows_path
from resource_limits import limit_cpu
from windows_resources import resource_payloads


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def main():
    if not __debug__:
        raise SystemExit('Assertions must remain enabled')
    limit_cpu()
    if os.environ.get('DXBALL_RESOURCE_DISPLAY') != '1':
        subprocess.run(['xvfb-run', '-a', '-s', '-screen 0 640x480x24',
                        str(ROOT / 'scripts/repo-python'), str(Path(__file__).resolve())],
                       env=dict(os.environ, DXBALL_RESOURCE_DISPLAY='1'),
                       check=True, timeout=240)
        return
    lock = session_lock()
    tools = Toolchain()
    tools.verify(execute=True)
    original = ROOT / 'original/DXBALL.EXE'
    rows = resource_payloads(original.read_bytes())
    directory = ROOT / 'build/probes/windows-resources'
    directory.mkdir(parents=True, exist_ok=True)
    reader = directory / 'resource-reader.exe'
    compiler = Path(shutil.which('i686-w64-mingw32-gcc')).resolve()
    flags = ['-std=c90', '-O0', '-Wall', '-Wextra', '-Wpedantic', '-Werror']
    subprocess.run([str(compiler), *flags, str(ROOT / 'tests/windows_resource_reader.c'),
                    '-o', str(reader), '-luser32', '-lgdi32'], check=True, timeout=60)
    negative = directory / 'without-resources.exe'
    # Link the same game objects, including explicit dependency backends.
    # Owner metadata enumerates recovered entries, not the entire link graph.
    objects = [ROOT / 'build/vc40' / (path.stem + '.obj')
               for path in sorted((ROOT / 'src').glob('*.c'))
               if path.stem not in ('board_inspector', 'resource_inspector')]
    tools.run('link.exe', ['/NOLOGO', '/MACHINE:IX86', '/SUBSYSTEM:WINDOWS',
        '/INCREMENTAL:NO', '/PDB:NONE', '/OUT:' + windows_path(negative),
        *map(windows_path, objects), 'user32.lib', 'gdi32.lib', 'winmm.lib'])
    reports = ROOT / 'build/reports/windows-resources'
    reports.mkdir(parents=True, exist_ok=True)
    observations = {}
    expected = [{k: row[k] for k in ('type', 'name', 'language', 'size')} | {'hex': payload.hex()}
                for row, payload in rows]
    # One display throughout keeps icon decoding in the same SDK environment.
    for profile, executable in [('original', original), ('vc40', ROOT / 'build/vc40/dxball.exe'),
        ('windows-i686', ROOT / 'build/windows-i686/dxball.exe'), ('negative', negative)]:
        result = subprocess.run(['wine', str(reader), windows_path(executable)],
            env=tools.env, capture_output=True, text=True, check=True, timeout=60)
        (reports / (profile + '.log')).write_text(result.stdout + result.stderr)
        lines = [line for line in result.stdout.splitlines() if line.startswith('{')]
        assert len(lines) == 1, (profile, result.stdout)
        record = json.loads(lines[0])
        (reports / (profile + '.json')).write_text(json.dumps(record, indent=2) + '\n')
        assert record['requested_icon'] == 0, (profile, record)
        if profile == 'negative':
            assert record['resources'] == [] and record['embedded_icon'] == 0
        else:
            assert record['resources'] == expected and record['embedded_icon'] == 1, profile
            assert record['enumerated'] == 1
            if profile != 'original':
                assert record['color'] == observations['original']['color'], profile
                assert record['mask'] == observations['original']['mask'], profile
                assert record['requested_error'] == observations['original']['requested_error'], profile
        observations[profile] = record
        print('PASS resource SDK:', profile, flush=True)
    manifest = json.loads((ROOT / 'config/windows-resources.json').read_text())
    inputs = ['tests/test_windows_resources.py', 'tests/windows_resource_reader.c',
              'scripts/windows_resources.py', 'config/windows-resources.json',
              'scripts/build-legacy.py', 'scripts/build-windows.py', 'CMakeLists.txt',
              'scripts/legacy_toolchain.py', 'scripts/resource_limits.py', 'config/tools.lock.toml',
              'scripts/verify-target.py', 'config/target.toml', 'config/assets.csv',
              'config/source-owners.toml', 'config/mingw-i686.cmake']
    inputs += [str(path.relative_to(ROOT)) for path in sorted((ROOT / 'src').glob('*.[ch]'))]
    builds = {}
    for profile in ('vc40', 'windows-i686'):
        path = ROOT / 'build' / profile
        metadata = json.loads((path / 'game-resources.json').read_text())
        assert metadata['resources'] == manifest['resources'], profile
        assert metadata['object_sha256'] == digest(path / 'game-resources.obj'), profile
        assert metadata['resource_sha256'] == digest(path / 'game-resources.res'), profile
        assert metadata['converter_sha256'] == digest(metadata['converter']), profile
        assert all(digest(ROOT / p) == h for p, h in metadata['inputs'].items()), profile
        builds[profile] = metadata
    report = dict(status='pass', target_sha256=manifest['target_sha256'],
        resources=manifest['resources'], color_sha256=hashlib.sha256(bytes.fromhex(observations['original']['color'])).hexdigest(),
        mask_sha256=hashlib.sha256(bytes.fromhex(observations['original']['mask'])).hexdigest(),
        requested_id=0x7f00, embedded_group_id=101,
        requested_errors={p: r['requested_error'] for p, r in observations.items()},
        inputs={name: digest(ROOT / name) for name in inputs}, reader_sha256=digest(reader),
        compiler_sha256=digest(compiler), flags=flags, resource_builds=builds,
        executables={profile: digest(path) for profile, path in [('original', original),
            ('vc40', ROOT / 'build/vc40/dxball.exe'), ('windows-i686', ROOT / 'build/windows-i686/dxball.exe'), ('negative', negative)]},
        scope='Complete ordinal resource inventory/payloads and SDK-decoded 32x32 color/mask; '
              'same maintained objects linked without resources as negative control. '
              'Original startup requests 0x7f00 while its only group is 101; lookup failure is preserved. '
              'Data-file resource loading does not execute WinMain or establish live class-icon/shell behavior.')
    (ROOT / 'build/reports/windows-resources.json').write_text(json.dumps(report, indent=2) + '\n')
    lock.close()
    print('Embedded resource checks passed; complete payloads and both decoded bitmaps agree.')


if __name__ == '__main__':
    main()
