"""Build private Win32 resources from the hash-pinned, REA-reviewed original.

Callers hold the compiler session lock. No original resource payload is public.
"""
import hashlib
import importlib.util
import json
from pathlib import Path
import shutil
import struct
import subprocess

import pefile
from legacy_toolchain import ROOT, sha256, windows_path

MANIFEST = ROOT / 'config/windows-resources.json'


def resource_payloads(data):
    manifest = json.loads(MANIFEST.read_text())
    if hashlib.sha256(data).hexdigest() != manifest['target_sha256']:
        raise ValueError('Embedded resources require the pinned original executable')
    image = pefile.PE(data=data)
    rows = []
    for kind in image.DIRECTORY_ENTRY_RESOURCE.entries:
        for name in kind.directory.entries:
            for language in name.directory.entries:
                if any(entry.name is not None for entry in (kind, name, language)):
                    raise ValueError('Unexpected named resource in the reviewed target')
                entry = language.data.struct
                payload = image.get_data(entry.OffsetToData, entry.Size)
                row = dict(type=kind.id, name=name.id, language=language.id,
                           rva=entry.OffsetToData, size=entry.Size,
                           codepage=entry.CodePage, sha256=hashlib.sha256(payload).hexdigest())
                rows.append((row, payload))
    rows.sort(key=lambda pair: (pair[0]['type'], pair[0]['name'], pair[0]['language']))
    if [row for row, _ in rows] != manifest['resources']:
        raise ValueError('Original resource inventory/payload differs from REA manifest')
    return rows


def res_entry(kind, name, language, data, flags=0x1030):
    # Win32 RESOURCEHEADER: ordinal type/name and DWORD-aligned header/data.
    header = struct.pack('<IIHHHHIHHII', len(data), 32, 0xffff, kind,
                         0xffff, name, 0, flags, language, 0, 0)
    return header + data + bytes((-len(data)) % 4)


def prepare_game_resources(profile, toolchain=None):
    spec = importlib.util.spec_from_file_location('resource_target', ROOT / 'scripts/verify-target.py')
    target = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(target)
    _, _, data = target.verify()
    rows = resource_payloads(data)
    directory = ROOT / 'build' / profile
    directory.mkdir(parents=True, exist_ok=True)
    resource = directory / 'game-resources.res'
    obj = directory / 'game-resources.obj'
    binary = res_entry(0, 0, 0, b'', flags=0)
    for row, payload in rows:
        binary += res_entry(row['type'], row['name'], row['language'], payload)
    if not resource.is_file() or resource.read_bytes() != binary:
        resource.write_bytes(binary)
    obj.unlink(missing_ok=True)
    manifest = json.loads(MANIFEST.read_text())
    if profile == 'vc40':
        converter = ROOT / manifest['legacy_converter']['path']
        if sha256(converter) != manifest['legacy_converter']['sha256']:
            raise ValueError('Legacy resource converter hash mismatch')
        result = toolchain.run('cvtres.exe', [*manifest['legacy_converter']['flags'],
            '/OUT:' + windows_path(obj), windows_path(resource)])
        log = result.stdout
        flags = manifest['legacy_converter']['flags']
    elif profile == 'windows-i686':
        installed = shutil.which('i686-w64-mingw32-windres')
        if not installed:
            raise RuntimeError('Install the i686 MinGW resource converter (windres)')
        converter = Path(installed).resolve()
        flags = ['-J', 'res', '-O', 'coff', '--target=pe-i386']
        result = subprocess.run([str(converter), *flags, str(resource), str(obj)],
                                capture_output=True, text=True, check=True, timeout=60)
        log = result.stdout + result.stderr
    else:
        raise ValueError('Unknown resource build profile: ' + profile)
    if not obj.is_file():
        raise RuntimeError('Resource converter did not produce an object')
    metadata = dict(target_sha256=manifest['target_sha256'], resources=[row for row, _ in rows],
        inputs={name: sha256(ROOT / name) for name in
                ('config/windows-resources.json', 'scripts/windows_resources.py', 'scripts/verify-target.py')},
        resource_sha256=sha256(resource), object_sha256=sha256(obj),
        converter=str(converter), converter_sha256=sha256(converter), flags=flags)
    (directory / 'game-resources.json').write_text(json.dumps(metadata, indent=2) + '\n')
    (directory / 'game-resources.log').write_text(log)
    return obj, metadata
