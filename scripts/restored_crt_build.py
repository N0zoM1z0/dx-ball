"""Build the checked source CRT/game closure without implicit CRT libraries."""
import json
import shutil
from pathlib import Path
from crt_library import members
from legacy_toolchain import ROOT, sha256, windows_path


def build_game(toolchain, builds, resource_object, resource_metadata,
               directx_imports, directx_metadata, reusable, project_inputs):
    recipe_path = ROOT / 'config/restored-crt-link.json'
    recipe = json.loads(recipe_path.read_text())
    if recipe['default_libraries'] or recipe['subsystem'] != 'WINDOWS':
        raise ValueError('Unsupported restored CRT entry recipe')
    directory = ROOT / 'build/vc40-restored-crt'
    directory.mkdir(parents=True, exist_ok=True)
    def retain(path):
        if not path.is_file():
            return
        destination = directory / 'history' / sha256(path) / path.name
        if not destination.exists():
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(path, destination)
    for name in ('build.json', 'build.log', 'dxball.exe', 'dxball.map'):
        retain(directory / name)
    specs = dict(builds)
    for name in recipe['additional_producer_recipes']:
        data = json.loads((ROOT / name).read_text())
        if 'additional_producers' in data:
            specs.update({row['owner']: row for row in data['additional_producers']})
        else:
            specs[Path(data['source']).stem] = data
    for name, source in recipe['integration_sources'].items():
        specs[name] = dict(source=source, flags=recipe['integration_flags'])
    library = toolchain.path / 'lib' / recipe['original_library']
    if sha256(library) != recipe['original_library_sha256']:
        raise ValueError('Restored CRT original-library identity mismatch')
    member_dir = directory / 'members'
    member_dir.mkdir(exist_ok=True)
    member_specs = {row['header_offset']: row for row in recipe['original_members']}
    original_objects = {}
    missing = set()
    for offset, row in member_specs.items():
        path = member_dir / (f'{offset:08x}.obj')
        if not path.is_file() or sha256(path) != row['object_sha256']:
            missing.add(offset)
        else:
            original_objects[row['id']] = path
    if missing:
        for offset, name, raw in members(library):
            if offset not in missing:
                continue
            row = member_specs[offset]
            if name != row['member']:
                raise ValueError('Restored CRT member name/offset mismatch')
            path = member_dir / (f'{offset:08x}.obj')
            path.write_bytes(raw)
            if sha256(path) != row['object_sha256']:
                raise ValueError('Restored CRT member contents mismatch')
            original_objects[row['id']] = path
        if set(original_objects) != {row['id'] for row in member_specs.values()}:
            raise ValueError('Missing required original CRT member')
    objects, receipts, logs = [], {}, []
    for owner in recipe['link_order']:
        if owner == 'game-resources':
            objects.append(resource_object)
            continue
        if owner.startswith('member:'):
            objects.append(original_objects[owner])
            continue
        if owner.startswith('game:'):
            source = owner.removeprefix('game:')
            spec = dict(source=source, flags=builds['boards']['flags'])
        else:
            spec = specs[owner]
            source = spec['source']
        inputs = project_inputs(source)
        if 'inputs' in spec and not set(inputs) <= set(spec['inputs']):
            raise ValueError('Incomplete producer inputs: ' + owner)
        output = directory / (Path(source).stem + '.obj')
        producer = reusable.get((source, tuple(spec['flags'])))
        if producer is None:
            retain(output)
            logs.append(toolchain.compile(ROOT / source, output, spec['flags']).stdout)
            action = 'compiled'
        else:
            if (not set(inputs) <= set(producer['inputs']) or
                    any(sha256(ROOT / n) != h for n, h in producer['inputs'].items()) or
                    sha256(ROOT / producer['object']) != producer['object_sha256']):
                raise ValueError('Producer changed after validation: ' + owner)
            if output.is_file() and sha256(output) != producer['object_sha256']:
                retain(output)
            temporary = output.with_suffix('.obj.reuse')
            shutil.copyfile(ROOT / producer['object'], temporary)
            temporary.replace(output)
            action = 'reused'
        row = dict(owner=owner, source=source, object=str(output.relative_to(ROOT)),
                   object_sha256=sha256(output), inputs=inputs, flags=spec['flags'], action=action)
        if producer is not None:
            row['reuse_producer'] = producer
        receipts[source] = row
        objects.append(output)
        print('restored CRT object ' + action + ': ' + source, flush=True)
    if len(objects) != len(set(objects)):
        raise ValueError('Duplicate restored CRT link input')
    if (len(receipts) != recipe['source_objects'] + recipe['integration_objects'] or
            len(recipe['integration_sources']) != recipe['integration_objects']):
        raise ValueError('Restored CRT source closure count mismatch')
    executable = directory / 'dxball.exe'
    link_map = directory / 'dxball.map'
    imports = {path.name: path for path in directx_imports}
    arguments = ['/NOLOGO', '/MACHINE:IX86', '/SUBSYSTEM:' + recipe['subsystem'],
                 '/ENTRY:' + recipe['entry'], '/NODEFAULTLIB', '/OPT:REF',
                 '/INCREMENTAL:NO', '/PDB:NONE', '/OUT:' + windows_path(executable),
                 '/MAP:' + windows_path(link_map), *map(windows_path, objects),
                 *recipe['sdk_libraries'],
                 *(windows_path(imports[name]) for name in recipe['directx_library_order'])]
    logs.append(toolchain.run('link.exe', arguments).stdout)
    if not executable.is_file() or not link_map.is_file():
        raise RuntimeError('Restored CRT linker produced no executable/map')
    all_inputs = {name for row in receipts.values() for name in row['inputs']}
    all_inputs.update(['scripts/build-legacy.py', 'scripts/restored_crt_build.py',
                      'scripts/legacy_toolchain.py', 'scripts/resource_limits.py',
                      'scripts/crt_library.py', 'scripts/coff.py',
                      'scripts/directx_imports.py', 'scripts/windows_resources.py',
                      'scripts/verify-target.py', 'config/tools.lock.toml',
                      'config/match-units.toml', 'config/windows-resources.json',
                      'config/restored-crt-link.json', *recipe['additional_producer_recipes']])
    report = dict(status='linked', profile='vc40-restored-crt',
                  compiler_sha256=toolchain.lock['compiler_sha256'],
                  linker_sha256=toolchain.lock['linker_sha256'],
                  inputs={name: sha256(ROOT / name) for name in sorted(all_inputs)},
                  objects=receipts, link_arguments=arguments,
                  original_library_sha256=sha256(library), original_members=recipe['original_members'],
                  game_resources=resource_metadata, directx_imports=directx_metadata,
                  executable_sha256=sha256(executable), game_map_sha256=sha256(link_map),
                  source_owners=recipe['source_objects'], integration_objects=recipe['integration_objects'],
                  compiled=sum(row['action'] == 'compiled' for row in receipts.values()),
                  reused=sum(row['action'] == 'reused' for row in receipts.values()),
                  scope=recipe['remaining_scope'])
    (directory / 'build.log').write_text('\n'.join(logs))
    (directory / 'build.json').write_text(json.dumps(report, indent=2) + '\n')
    print('Restored CRT game build OK: ' + str(executable), flush=True)
