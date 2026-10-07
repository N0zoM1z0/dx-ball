#!/usr/bin/env python3
"""Run native, MinGW i386, and pinned VC4.0 utilities against the real bank."""
import hashlib
import json
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
    lock = session_lock()
    tools = Toolchain()
    tools.verify()
    for profile in ("windows-i686", "vc40"):
        executable = ROOT / "build" / profile / "dxball_boards.exe"
        for board in (1, 25, 50):
            result = subprocess.run(
                ["xvfb-run", "-a", "wine", str(executable), windows_path(original), str(board)],
                env=tools.env, cwd=ROOT, capture_output=True, text=True, timeout=60,
            )
            if result.returncode != 0:
                raise RuntimeError(f"{profile} execution failed:\n{result.stderr}")
            assert json.loads(result.stdout) == expected_outputs[board]
        print(f"PASS {profile} inspector: boards 1, 25, 50 under Wine", flush=True)
    (ROOT / "build/reports/inspector-builds.json").write_text(json.dumps({
        "bank_sha256": hashlib.sha256(bank).hexdigest(), "native_boards": 50,
        "rejected_inputs": 4, "windows_boards": [1, 25, 50],
        "profiles": ["native", "windows-i686", "vc40"], "status": "passed",
    }, indent=2) + "\n")


if __name__ == "__main__":
    if not __debug__:
        raise SystemExit("run without -O")
    main()
