#!/usr/bin/env python3
"""Run public build/tracking checks or the complete private oracle suite."""
import argparse
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
PYTHON = ROOT / "scripts/repo-python"


def run(arguments):
    print("+ " + " ".join(map(str, arguments)), flush=True)
    subprocess.run(list(map(str, arguments)), cwd=ROOT, check=True)


def python(script, *arguments):
    run([PYTHON, script, *arguments])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--public", action="store_true",
                        help="build and validate public metadata without private originals/tools")
    args = parser.parse_args()
    python("scripts/verify-python.py")
    python("scripts/validate-tracking.py", *([] if args.public else ["--require-target"]))
    run(["cmake", "-S", ".", "-B", "build/native", "-G", "Ninja", "-DCMAKE_BUILD_TYPE=Debug"])
    run(["cmake", "--build", "build/native"])
    if args.public:
        print("Public checks passed. Target, exact, and runtime oracles require private originals.")
        return
    python("scripts/verify-target.py")
    python("scripts/verify-toolchain.py", "--execute")
    python("scripts/ghidra.py", "check")
    python("scripts/replay-exact-units.py")
    python("tests/test_exact_oracle.py")
    python("tests/test_boards_differential.py")
    python("tests/test_resources_differential.py")
    python("scripts/build-legacy.py")
    run(["cmake", "-S", ".", "-B", "build/windows-i686", "-G", "Ninja",
         "-DCMAKE_TOOLCHAIN_FILE=config/mingw-i686.cmake", "-DCMAKE_BUILD_TYPE=Release"])
    run(["cmake", "--build", "build/windows-i686"])
    python("tests/test_inspector_builds.py")
    python("scripts/validate-tracking.py", "--require-target")
    python("scripts/report-reconstruction-status.py", "--summary")
    print("Complete private checks passed.")


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as exc:
        sys.exit(exc.returncode)
