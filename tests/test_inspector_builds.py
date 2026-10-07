#!/usr/bin/env python3
"""Run native, MinGW i386, and pinned VC4.0 utilities against the real bank."""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from legacy_toolchain import Toolchain, windows_path, session_lock


def main():
    original = ROOT / "original/DEFAULT.BDS"
    bank = original.read_bytes()
    expected_outputs = {}
    native = ROOT / "build/native/dxball_boards"
    for board in range(1, 51):
        result = subprocess.run([str(native), str(original), str(board)],
                                capture_output=True, text=True, check=True)
        decoded = json.loads(result.stdout)
        assert decoded["board"] == board and decoded["width"] == decoded["height"] == 20
        flat = bytes(value for row in decoded["tiles"] for value in row)
        assert flat == bank[(board - 1) * 400:board * 400]
        expected_outputs[board] = decoded
    for invalid in ("0", "51", "junk", "1junk"):
        result = subprocess.run([str(native), str(original), invalid], capture_output=True)
        assert result.returncode == 2 and not result.stdout
    print("PASS native inspector: 50 boards and 4 rejected inputs", flush=True)
    resource_outputs = {}
    resource_native = ROOT / "build/native/dxball_resources"
    resource_directory = ROOT / "original"
    for suffix, mode in (("SBK", "--sbk"), ("PCX", "--pcx")):
        for path in sorted(resource_directory.glob("*." + suffix)):
            result = subprocess.run([str(resource_native), mode, path.name],
                                    cwd=resource_directory, capture_output=True, text=True, check=True)
            resource_outputs[(mode, path.name)] = json.loads(result.stdout)
    print("PASS native resource inspector: all 7 SBK and 5 PCX files", flush=True)
    lock = session_lock()
    tools = Toolchain()
    tools.verify()
    for profile in ("windows-i686", "vc40"):
        executable = ROOT / "build" / profile / "dxball_boards.exe"
        for board in (1, 25, 50):
            result = subprocess.run(
                ["wine", str(executable), windows_path(original), str(board)],
                env=tools.env, cwd=ROOT, capture_output=True, text=True, timeout=60,
            )
            if result.returncode != 0:
                raise RuntimeError(f"{profile} execution failed:\n{result.stderr}")
            assert json.loads(result.stdout) == expected_outputs[board]
        print(f"PASS {profile} inspector: boards 1, 25, 50 under Wine", flush=True)
        resource_executable = ROOT / "build" / profile / "dxball_resources.exe"
        for (mode, name), expected in resource_outputs.items():
            result = subprocess.run(["wine", str(resource_executable), mode, name],
                                    env=tools.env, cwd=resource_directory,
                                    capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                raise RuntimeError(f"{profile} resource execution failed:\n{result.stderr}")
            assert json.loads(result.stdout) == expected, (profile, name)
        print(f"PASS {profile} resource inspector: all 12 files under Wine", flush=True)
    (ROOT / "build/reports/inspector-builds.json").write_text(json.dumps({
        "bank_sha256": hashlib.sha256(bank).hexdigest(), "native_boards": 50,
        "rejected_inputs": 4, "windows_boards": [1, 25, 50],
        "profiles": ["native", "windows-i686", "vc40"], "status": "passed",
        "resources": [name for mode, name in resource_outputs],
    }, indent=2) + "\n")


if __name__ == "__main__":
    if not __debug__:
        raise SystemExit("run without -O")
    # Keep one display alive throughout the suite; per-executable xvfb-run
    # teardown lets Wine clients append asynchronous X11 errors to captured JSON.
    if os.environ.get("DXBALL_INSPECTOR_XVFB") != "1":
        environment = os.environ.copy()
        environment["DXBALL_INSPECTOR_XVFB"] = "1"
        result = subprocess.run(["xvfb-run", "-a", str(ROOT / "scripts/repo-python"),
                                 str(Path(__file__).resolve())], env=environment)
        raise SystemExit(result.returncode)
    main()
