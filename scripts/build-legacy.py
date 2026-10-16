#!/usr/bin/env python3
"""Build the game and analysis utilities with the pinned VC4.0 toolchain."""
import argparse
import json
from pathlib import Path
import re
import shutil
import sys
import tomllib
from legacy_toolchain import ROOT, Toolchain, session_lock, windows_path, sha256


def project_inputs(source):
    """Include the source and recursively quoted project headers, in both branches."""
    pending, found = [ROOT / source], set()
    while pending:
        path = pending.pop().resolve()
        if path in found:
            continue
        found.add(path)
        for name in re.findall(r'^\s*#\s*include\s*"([^"]+)"',
                               path.read_text(), re.MULTILINE):
            header = path.parent / name
            if header.is_file():
                pending.append(header)
    return {str(path.relative_to(ROOT)): sha256(path) for path in sorted(found)}


def accepted_objects(builds, compiler_sha256):
    """Reuse complete owner objects bound to the current exact report and inputs."""
    try:
        report = json.loads((ROOT / 'build/reports/exact-replay.json').read_text())
        if (report['manifest_sha256'] != sha256(ROOT / 'config/match-units.toml') or
                report['compiler_sha256'] != compiler_sha256):
            return {}
    except (OSError, KeyError, ValueError, TypeError):
        return {}
    report_sha256 = sha256(ROOT / 'build/reports/exact-replay.json')
    verified = {}
    for name, spec in builds.items():
        try:
            record = report['builds'][name]
            inputs = project_inputs(spec['source'])
            if (record['flags'] != spec['flags'] or
                    not set(inputs) <= set(record['inputs']) or
                    record['inputs'] != {p: sha256(ROOT / p) for p in spec['inputs']} or
                    sha256(ROOT / record['object']) != record['object_sha256']):
                continue
            key = (spec['source'], tuple(spec['flags']))
            verified[key] = dict(record, build=name,
                                 report='build/reports/exact-replay.json',
                                 report_sha256=report_sha256)
        except (OSError, KeyError, ValueError, TypeError):
            continue
    return verified


def previous_objects(compiler_sha256, path=None):
    """Reuse prior game/adapter products with current complete project inputs."""
    path = ROOT / 'build/vc40/build.json' if path is None else path
    try:
        report = json.loads(path.read_text())
        if report['compiler_sha256'] != compiler_sha256:
            return {}
        for name in ('scripts/legacy_toolchain.py', 'config/tools.lock.toml'):
            if report['inputs'].get(name) != sha256(ROOT / name):
                return {}
        report_sha256 = sha256(path)
    except (OSError, KeyError, ValueError, TypeError):
        return {}
    verified = {}
    for source, record in report.get('objects', {}).items():
        try:
            if (record['inputs'] != project_inputs(source) or
                    sha256(ROOT / record['object']) != record['object_sha256']):
                continue
            verified[(source, tuple(record['flags']))] = dict(
                object=record['object'], object_sha256=record['object_sha256'],
                flags=record['flags'], inputs=record['inputs'],
                report=str(path.relative_to(ROOT)), report_sha256=report_sha256)
        except (OSError, KeyError, ValueError, TypeError):
            continue
    return verified


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--game-only', action='store_true',
                        help='build the game without the two diagnostic executables')
    parser.add_argument('--restored-crt', action='store_true',
                        help='build the game with restored CRT entry and explicit remaining original members')
    args = parser.parse_args()
    lock = session_lock()
    toolchain = Toolchain()
    toolchain.verify(execute=True)
    from windows_resources import prepare_game_resources
    from directx_imports import prepare_directx_imports
    resource_profile = 'vc40-restored-crt' if args.restored_crt else 'vc40'
    resource_object, resource_metadata = prepare_game_resources(resource_profile, toolchain)
    directx_imports, directx_import_metadata = prepare_directx_imports(toolchain)
    builds = tomllib.loads((ROOT / "config/match-units.toml").read_text())["builds"]
    if args.restored_crt:
        from restored_crt_build import build_game
        reusable = previous_objects(toolchain.lock['compiler_sha256'])
        for receipt in ('build.json', 'object-cache.json'):
            reusable.update(previous_objects(toolchain.lock['compiler_sha256'],
                ROOT / 'build/vc40-restored-crt' / receipt))
        reusable.update(accepted_objects(builds, toolchain.lock['compiler_sha256']))
        build_game(toolchain, builds, resource_object, resource_metadata,
                   directx_imports, directx_import_metadata, reusable, project_inputs)
        return
    build = builds["boards"]
    owner_flags = {
        "src/raster.cpp": builds["raster"]["flags"],
        "src/random.c": builds["random"]["flags"],
        "src/cpp_allocator.cpp": builds["allocator"]["flags"],
        "src/allocator.c": builds["allocator"]["flags"],
        "src/list_initializers.cpp": builds["list_initializers"]["flags"],
        "src/resources.cpp": builds["resources"]["flags"],
    }
    directory = ROOT / "build/vc40"
    directory.mkdir(parents=True, exist_ok=True)
    objects = []
    log = []
    object_receipts = {}
    reusable = previous_objects(toolchain.lock['compiler_sha256'])
    reusable.update(accepted_objects(builds, toolchain.lock['compiler_sha256']))

    def compile_source(source, flags):
        output = directory / (Path(source).stem + '.obj')
        inputs = project_inputs(source)
        producer = reusable.get((source, tuple(flags)))
        if producer is not None:
            cached = ROOT / producer['object']
            # Recheck at use, and replace through a separate inode.
            if (producer['inputs'] != {p: sha256(ROOT / p) for p in producer['inputs']} or
                    sha256(cached) != producer['object_sha256']):
                producer = None
        if producer is None:
            log.append(toolchain.compile(ROOT / source, output, flags).stdout)
            action = 'compiled'
        else:
            temporary = output.with_suffix('.obj.reuse')
            shutil.copyfile(cached, temporary)
            temporary.replace(output)
            action = 'reused'
        object_receipts[source] = dict(object=str(output.relative_to(ROOT)),
                                      object_sha256=sha256(output), inputs=inputs,
                                      flags=flags, action=action)
        if producer is not None:
            object_receipts[source]['reuse_producer'] = producer
        print(f'legacy object {action}: {source}', flush=True)
        return output

    for source in ("src/allocator.c", "src/cpp_allocator.cpp", "src/random.c", "src/allocator_host.c", "src/boards.c", "src/resources.cpp", "src/rotation.c", "src/raster.cpp", "src/list_initializers.cpp", "src/bitmap.c", "src/gameplay.c", "src/effects.c", "src/particles.c", "src/bonuses.c", "src/geometry.c", "src/paddle.c", "src/round.c", "src/trig.c", "src/balls.cpp", "src/core.c", "src/runtime.cpp", "src/display.cpp", "src/device.cpp", "src/platform.c", "src/platform_host.c", "src/startup.c", "src/ui.c", "src/intro.cpp", "src/gameover.c", "src/editor.c", "src/midi.cpp", "src/music.cpp", "src/file.c", "src/memory.c", "src/sound.c"):
        flags = owner_flags.get(source, build["flags"])
        output = compile_source(source, flags)
        objects.append(output)
    products = {}
    entries = [] if args.game_only else ["src/board_inspector.c", "src/resource_inspector.c"]
    inspector_link_flags = []
    for source, name in zip(entries, ["dxball_boards", "dxball_resources"]):
        entry = compile_source(source, build["flags"])
        executable = directory / (name + ".exe")
        executable.unlink(missing_ok=True)
        inspector_link_flags = ["/NOLOGO", "/MACHINE:IX86", "/SUBSYSTEM:CONSOLE",
                                "/INCREMENTAL:NO", "/PDB:NONE", "/NODEFAULTLIB:LIBC",
                                "/OUT:" + windows_path(executable)]
        arguments = [*inspector_link_flags,
                     *map(windows_path, objects + [entry] + directx_imports),
                     "winmm.lib"]
        log.append(toolchain.run("link.exe", arguments).stdout)
        if not executable.is_file():
            raise RuntimeError("legacy linker produced no executable")
        products[name] = sha256(executable)
        print(f"legacy build OK: {executable}", flush=True)
    game_sources = ["src/windows_adapter.c", "src/windows_entry.c"]
    game_objects = []
    for source in game_sources:
        flags = owner_flags.get(source, build["flags"])
        output = compile_source(source, flags)
        game_objects.append(output)
    executable = directory / "dxball.exe"
    link_map = directory / "dxball.map"
    executable.unlink(missing_ok=True)
    link_map.unlink(missing_ok=True)
    game_link_flags = ["/NOLOGO", "/MACHINE:IX86", "/SUBSYSTEM:WINDOWS",
                       "/INCREMENTAL:NO", "/PDB:NONE", "/NODEFAULTLIB:LIBC",
                       "/OUT:" + windows_path(executable),
                       "/MAP:" + windows_path(link_map)]
    game_arguments = [*game_link_flags,
                      *map(windows_path, objects + game_objects + [resource_object]),
                      "user32.lib", "gdi32.lib", "winmm.lib", *map(windows_path, directx_imports)]
    log.append(toolchain.run("link.exe", game_arguments).stdout)
    if not executable.is_file():
        raise RuntimeError("legacy game linker produced no executable")
    if not link_map.is_file():
        raise RuntimeError("legacy game linker produced no symbol map")
    products["dxball"] = sha256(executable)
    print(f"legacy game build OK: {executable}", flush=True)
    (directory / "build.log").write_text("\n".join(log))
    all_inputs = {name for record in object_receipts.values() for name in record['inputs']}
    all_inputs.update(['scripts/build-legacy.py', 'scripts/legacy_toolchain.py',
                      'scripts/resource_limits.py', 'scripts/directx_imports.py',
                      'scripts/crt_library.py', 'scripts/coff.py',
                      'scripts/windows_resources.py', 'scripts/verify-target.py',
                      'config/windows-resources.json', 'config/tools.lock.toml',
                      'config/match-units.toml'])
    (directory / "build.json").write_text(json.dumps({
        "executables": products,
        "inputs": {name: sha256(ROOT / name) for name in sorted(all_inputs)},
        "objects": object_receipts,
        "build_scope": 'game-only' if args.game_only else 'game and inspectors',
        "compiler_sha256": toolchain.lock["compiler_sha256"],
        "linker_sha256": toolchain.lock["linker_sha256"],
        "flags": build["flags"], "owner_flags": owner_flags, "link_flags": inspector_link_flags,
        "game_link_flags": game_link_flags,
        "game_map_sha256": sha256(link_map),
        "game_resources": resource_metadata,
        "directx_imports": directx_import_metadata,
        "product": ('game EXE' if args.game_only else 'board/resource inspectors and game EXE')
                   + '; playability requires runtime checks',
    }, indent=2) + "\n")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError, RuntimeError) as exc:
        print(f"legacy build failed: {exc}", file=sys.stderr)
        sys.exit(1)
