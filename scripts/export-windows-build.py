#!/usr/bin/env python3
"""Export a self-contained native Windows source/compiler package beside game/."""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]


def digest(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('destination', type=Path, help='New reconstruction directory beside the existing game directory')
    args = parser.parse_args()
    destination = args.destination.resolve()
    if destination.exists():
        raise ValueError('Refusing to replace an existing build package')
    build = json.loads((ROOT / 'build/vc40-restored-crt/build.json').read_text())
    assert build['status'] == 'linked' and len(build['objects']) == 141
    assert len(build['original_members']) == 19
    assert all(digest(ROOT / name) == expected for name, expected in build['inputs'].items())
    destination.mkdir(parents=True)
    # Export the readable project, excluding all ignored originals, tools,
    # raw evidence and prior build products. Include these new entry points
    # when preparing a package before their first Git checkpoint.
    tracked = subprocess.check_output(['git', 'ls-files', '-z'], cwd=ROOT).decode().split('\0')
    sources = set(filter(None, tracked)) | {'scripts/build-native-windows.ps1', 'scripts/export-windows-build.py'}
    for name in sorted(sources):
        path = ROOT / name
        if path.is_file():
            target = destination / name
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(path, target)
    for part in ('bin', 'include', 'lib'):
        shutil.copytree(ROOT / '.tools/msvc400' / part, destination / 'toolchain' / part)
    shutil.copyfile(ROOT / 'scripts/build-native-windows.ps1', destination / 'Build-Reconstruction.ps1')
    support = destination / 'support'
    support.mkdir()
    shutil.copyfile(ROOT / 'build/vc40-restored-crt/game-resources.res', support / 'game-resources.res')
    for name in ('ddraw.lib', 'dsound.lib'):
        shutil.copyfile(ROOT / 'build/directx-imports' / name, support / name)
    for name in ('ddraw.dll', 'ddraw.ini'):
        shutil.copyfile(destination.parent / 'game' / name, support / name)
    units = [dict(source=row['source'], owner=row['owner'], flags=row['flags'], object=Path(row['object']).name)
             for row in build['objects'].values()]
    source_objects = {Path(row['object']).name for row in build['objects'].values()}
    link = []
    prefix = 'Z:' + str(ROOT).replace('/', '\\') + '\\'
    for argument in build['link_arguments']:
        if argument.startswith('/OUT:'):
            link.append('/OUT:{BUILD}\\game\\dxball.exe')
        elif argument.startswith('/MAP:'):
            link.append('/MAP:{BUILD}\\dxball.map')
        elif argument.startswith(prefix):
            relative = argument[len(prefix):].replace('\\', '/')
            name = Path(relative).name
            if relative.startswith('build/vc40-restored-crt/members/'):
                link.append('{BUILD}\\crt\\' + name)
            elif name == 'game-resources.obj':
                link.append('{BUILD}\\game-resources.obj')
            elif relative.startswith('build/directx-imports/'):
                link.append('{ROOT}\\support\\' + name)
            else:
                assert name in source_objects, argument
                link.append('{BUILD}\\objects\\' + name)
        else:
            assert not argument.startswith('Z:'), argument
            link.append(argument)
    assets = [row.name for row in sorted((ROOT / 'original').iterdir())
              if row.is_file() and row.suffix.lower() != '.exe']
    assert len(assets) == 48
    files = {path.relative_to(destination).as_posix(): digest(path)
             for path in sorted(destination.rglob('*')) if path.is_file()}
    assert files['toolchain/bin/cl.exe'] == build['compiler_sha256']
    assert files['toolchain/bin/link.exe'] == build['linker_sha256']
    assert files['toolchain/lib/libc.lib'] == build['original_library_sha256']
    assert files['support/game-resources.res'] == build['game_resources']['resource_sha256']
    for entry in build['directx_imports']:
        assert files['support/' + Path(entry['library']).name] == entry['library_sha256']
    compiler_context = dict(objects=units, inputs={name: value for name, value in files.items()
        if name.startswith(('src/', 'toolchain/bin/', 'toolchain/include/'))})
    compiler_context_sha256 = hashlib.sha256(json.dumps(compiler_context, sort_keys=True).encode()).hexdigest()
    plan = dict(format=1, profile='vc40-restored-crt-native-windows',
                source_checkpoint='ecfc475715238c43241a5979b1745a163749b9dc',
                source_build_report_sha256=digest(ROOT / 'build/vc40-restored-crt/build.json'),
                authored_functions=270, authored_code_bytes=84968, objects=units,
                compiler_context_sha256=compiler_context_sha256,
                linker_compatibility_layer='WIN7RTM',
                original_members=build['original_members'], link_arguments=link,
                assets=assets, files=files)
    (destination / 'build-plan.json').write_text(json.dumps(plan, indent=2) + '\n')
    launchers = {
        'Build Reconstruction.cmd': '@echo off\nchcp 65001 >nul\ntitle DX-Ball Reconstruction Build\npowershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0reconstruction\\Build-Reconstruction.ps1"\nset "build_result=%ERRORLEVEL%"\necho.\necho Press any key to close this window...\npause >nul\nexit /b %build_result%\n',
        'Play Rebuilt DX-Ball.cmd': '@echo off\nif not exist "%~dp0build\\game\\dxball.exe" (\n  echo Build the reconstruction first with Build Reconstruction.cmd.\n  echo Press any key to close this window...\n  pause >nul\n  exit /b 1\n)\ncd /d "%~dp0build\\game"\nstart "" "dxball.exe"\n',
    }
    for name, contents in launchers.items():
        (destination.parent / name).write_bytes(contents.replace('\n', '\r\n').encode('ascii'))
    (destination / 'README.txt').write_text(
        'DX-Ball native Windows source build\n\n'
        'Run Build Reconstruction.cmd in the parent folder for a complete build.\n'
        'The console shows English progress for all 141 C/C++ units.\n'
        'Output: ../build/game/dxball.exe. The existing ../game copy is preserved.\n'
        'Run Play Rebuilt DX-Ball.cmd to play the newly compiled version.\n\n'
        'Windows PowerShell 5.1 is sufficient; Python, WSL and Visual Studio are\n'
        'not needed on Windows. The pinned VC4 compiler is supplied locally.\n'
        'The linker child alone uses WIN7RTM compatibility; no registry change\n'
        'or administrator rights are needed. Nineteen original CRT members\n'
        'are retained explicitly in build-plan.json and extracted during build.\n\n'
        'Advanced: ./Build-Reconstruction.ps1 -Incremental reuses only hash-verified\n'
        'objects from the same compiler/source/header/flag context. The normal\n'
        'launcher always compiles all source units for a clean build demonstration.\n'
        'Compiler logs and build-report.json are written under ../build.\n', encoding='ascii')
    print('Exported native Windows build package:', destination)
    print('Source units: 141; retained original CRT members: 19; input files:', len(files))


if __name__ == '__main__':
    main()
