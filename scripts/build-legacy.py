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
    builds = tomllib.loads((ROOT / "config/match-units.toml").read_text())["builds"]
    build = builds["boards"]
    directory = ROOT / "build/vc40"
    directory.mkdir(parents=True, exist_ok=True)
    objects = []
    log = []
    for source in ("src/boards.c", "src/resources.c"):
        output = directory / (Path(source).stem + ".obj")
        log.append(toolchain.compile(ROOT / source, output, build["flags"]).stdout)
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
    (directory / "build.log").write_text("\n".join(log))
    (directory / "build.json").write_text(json.dumps({
        "executables": products,
        "inputs": {name: sha256(ROOT / name) for name in
                   sorted(set(name for row in builds.values() for name in row["inputs"])) + entries},
        "compiler_sha256": toolchain.lock["compiler_sha256"],
        "linker_sha256": toolchain.lock["linker_sha256"],
        "flags": build["flags"], "link_flags": arguments[:6],
        "product": "board/resource inspectors; not the game executable",
    }, indent=2) + "\n")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError, RuntimeError) as exc:
        print(f"legacy build failed: {exc}", file=sys.stderr)
        sys.exit(1)
