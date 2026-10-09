#!/usr/bin/env python3
"""Build analysis utilities with the pinned VC4.0 compiler and linker."""
import json
from pathlib import Path
import sys
import tomllib
from legacy_toolchain import ROOT, Toolchain, session_lock, windows_path, sha256


def main():
    lock = session_lock()
    toolchain = Toolchain()
    toolchain.verify(execute=True)
    from windows_resources import prepare_game_resources
    resource_object, resource_metadata = prepare_game_resources('vc40', toolchain)
    builds = tomllib.loads((ROOT / "config/match-units.toml").read_text())["builds"]
    build = builds["boards"]
    directory = ROOT / "build/vc40"
    directory.mkdir(parents=True, exist_ok=True)
    objects = []
    log = []
    for source in ("src/allocator.c", "src/allocator_host.c", "src/boards.c", "src/resources.c", "src/rotation.c", "src/raster.cpp", "src/list_initializers.cpp", "src/bitmap.c", "src/gameplay.c", "src/effects.c", "src/particles.c", "src/bonuses.c", "src/geometry.c", "src/paddle.c", "src/round.c", "src/trig.c", "src/balls.c", "src/core.c", "src/runtime.c", "src/display.c", "src/device.c", "src/platform.c", "src/startup.c", "src/ui.c", "src/intro.c", "src/gameover.c", "src/editor.c", "src/midi.c", "src/sound.c"):
        output = directory / (Path(source).stem + ".obj")
        flags = builds["raster"]["flags"] if source == "src/raster.cpp" else build["flags"]
        log.append(toolchain.compile(ROOT / source, output, flags).stdout)
        objects.append(output)
    products = {}
    entries = ["src/board_inspector.c", "src/resource_inspector.c"]
    for source, name in zip(entries, ["dxball_boards", "dxball_resources"]):
        entry = directory / (Path(source).stem + ".obj")
        log.append(toolchain.compile(ROOT / source, entry, build["flags"]).stdout)
        executable = directory / (name + ".exe")
        executable.unlink(missing_ok=True)
        arguments = ["/NOLOGO", "/MACHINE:IX86", "/SUBSYSTEM:CONSOLE",
                     "/INCREMENTAL:NO", "/PDB:NONE", "/OUT:" + windows_path(executable),
                     *map(windows_path, objects + [entry])]
        log.append(toolchain.run("link.exe", arguments).stdout)
        if not executable.is_file():
            raise RuntimeError("legacy linker produced no executable")
        products[name] = sha256(executable)
        print(f"legacy build OK: {executable}", flush=True)
    game_sources = ["src/windows_adapter.c", "src/windows_entry.c"]
    game_objects = []
    for source in game_sources:
        output = directory / (Path(source).stem + ".obj")
        flags = builds["raster"]["flags"] if source == "src/raster.cpp" else build["flags"]
        log.append(toolchain.compile(ROOT / source, output, flags).stdout)
        game_objects.append(output)
    executable = directory / "dxball.exe"
    link_map = directory / "dxball.map"
    executable.unlink(missing_ok=True)
    link_map.unlink(missing_ok=True)
    game_arguments = ["/NOLOGO", "/MACHINE:IX86", "/SUBSYSTEM:WINDOWS",
                      "/INCREMENTAL:NO", "/PDB:NONE", "/OUT:" + windows_path(executable),
                      "/MAP:" + windows_path(link_map),
                      *map(windows_path, objects + game_objects + [resource_object]),
                      "user32.lib", "gdi32.lib", "winmm.lib"]
    log.append(toolchain.run("link.exe", game_arguments).stdout)
    if not executable.is_file():
        raise RuntimeError("legacy game linker produced no executable")
    if not link_map.is_file():
        raise RuntimeError("legacy game linker produced no symbol map")
    products["dxball"] = sha256(executable)
    print(f"legacy game build OK: {executable}", flush=True)
    (directory / "build.log").write_text("\n".join(log))
    (directory / "build.json").write_text(json.dumps({
        "executables": products,
        "inputs": {name: sha256(ROOT / name) for name in
                   sorted(set(name for row in builds.values() for name in row["inputs"])) + ["src/allocator.c", "src/allocator.h", "src/allocator_host.c", "src/core.c", "src/core.h", "src/runtime.c", "src/runtime.h", "src/display.c", "src/display.h", "src/device.c", "src/device.h", "src/platform.c", "src/platform.h", "src/startup.c", "src/startup.h", "src/ui.c", "src/ui.h", "src/intro.c", "src/intro.h", "src/gameover.c", "src/gameover.h", "src/editor.c", "src/editor.h", "src/midi.c", "src/midi.h", "src/sound.c", "src/sound.h", "src/windows_adapter.h"] + entries + game_sources + ["scripts/build-legacy.py", "scripts/windows_resources.py", "scripts/verify-target.py", "config/windows-resources.json"]},
        "compiler_sha256": toolchain.lock["compiler_sha256"],
        "linker_sha256": toolchain.lock["linker_sha256"],
        "flags": build["flags"], "link_flags": arguments[:6],
        "game_link_flags": game_arguments[:7],
        "game_map_sha256": sha256(link_map),
        "game_resources": resource_metadata,
        "product": "board/resource inspectors and game EXE; playability requires runtime checks",
    }, indent=2) + "\n")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError, RuntimeError) as exc:
        print(f"legacy build failed: {exc}", file=sys.stderr)
        sys.exit(1)
