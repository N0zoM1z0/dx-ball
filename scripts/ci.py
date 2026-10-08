#!/usr/bin/env python3
"""Run public build/tracking checks or the complete private oracle suite."""
import argparse
from pathlib import Path
import subprocess
import sys
from resource_limits import BUILD_JOBS, limit_cpu

ROOT = Path(__file__).resolve().parents[1]
PYTHON = ROOT / "scripts/repo-python"


def run(arguments):
    print("+ " + " ".join(map(str, arguments)), flush=True)
    subprocess.run(list(map(str, arguments)), cwd=ROOT, check=True)


def python(script, *arguments):
    run([PYTHON, script, *arguments])


def main():
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--public", action="store_true",
                        help="build and validate public metadata without private originals/tools")
    args = parser.parse_args()
    python("scripts/verify-python.py")
    python("scripts/validate-tracking.py", *([] if args.public else ["--require-target"]))
    run(["cmake", "-S", ".", "-B", "build/native", "-G", "Ninja", "-DCMAKE_BUILD_TYPE=Debug"])
    run(["cmake", "--build", "build/native", "--parallel", str(BUILD_JOBS)])
    if args.public:
        print("Public checks passed. Target, exact, and runtime oracles require private originals.")
        return
    python("scripts/verify-target.py")
    python("scripts/verify-toolchain.py", "--execute")
    rea_runs = ROOT / ".analysis/rea/runs"
    saved_smoke = any((run / "close.json").is_file() for run in rea_runs.glob("*-rea-smoke-*"))
    python("scripts/verify-rea.py", *(["--saved"] if saved_smoke else []))
    python("scripts/replay-exact-units.py")
    python("tests/test_exact_oracle.py")
    python("tests/test_boards_differential.py")
    python("tests/test_resources_differential.py")
    python("tests/test_rotation_differential.py")
    python("tests/test_rotation_coff.py")
    python("tests/test_gameplay_differential.py")
    python("tests/test_effects_differential.py")
    python("tests/test_entities_differential.py")
    python("tests/test_powerups_differential.py")
    python("tests/test_core_differential.py")
    python("tests/test_runtime_differential.py")
    python("tests/test_display_differential.py")
    python("tests/test_device_differential.py")
    python("tests/test_platform_differential.py")
    python("tests/test_startup_differential.py")
    python("tests/test_ui_differential.py")
    python("tests/test_intro_differential.py")
    python("tests/test_gameover_differential.py")
    python("tests/test_editor_differential.py")
    python("tests/test_midi_differential.py")
    python("tests/test_sound_differential.py")
    python("scripts/build-legacy.py")
    python("scripts/build-windows.py")
    python("tests/test_inspector_builds.py")
    python("tests/test_windows_abi.py")
    python("tests/test_windows_resources.py")
    python("tests/test_windows_storage.py")
    python("tests/test_windows_runtime.py")
    python("tests/test_windows_play.py")
    python("tests/test_windows_gameover.py")
    python("tests/test_windows_round.py")
    python("tests/test_windows_ddraw_loss.py")
    python("tests/test_windows_terminal.py")
    python("scripts/validate-tracking.py", "--require-target")
    python("scripts/report-reconstruction-status.py", "--summary")
    print("Complete private checks passed.")


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as exc:
        sys.exit(exc.returncode)
