#!/usr/bin/env python3
"""Build portable source and check its recorded reconstruction ledger."""
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
    print("Source build and tracking passed. Run only the affected Oracle when needed.")


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as exc:
        sys.exit(exc.returncode)
