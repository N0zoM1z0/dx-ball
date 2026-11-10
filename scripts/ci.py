#!/usr/bin/env python3
"""Fast public checks; no originals, analysis packages or private tools required."""
import argparse
import ast
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import tomllib
from resource_limits import BUILD_JOBS, limit_cpu

ROOT = Path(__file__).resolve().parents[1]


def run(arguments):
    print("+ " + " ".join(map(str, arguments)), flush=True)
    subprocess.run(list(map(str, arguments)), cwd=ROOT, check=True)


def python(script, *arguments):
    run([sys.executable, script, *arguments])


def check_files():
    # Inspect the complete checkout, including files added earlier in a PR.
    names = subprocess.check_output(["git", "ls-files", "-z"], cwd=ROOT).decode().split("\0")
    private = {"original", ".tools", ".analysis", "ghidra-project", "build", ".venv", "__pycache__"}
    products = {".exe", ".dll", ".obj", ".o", ".lib", ".a", ".so", ".pdb", ".pyc",
                ".zip", ".gz", ".7z", ".tar", ".gpr"}
    checked = 0
    for name in filter(None, names):
        path = Path(name)
        if private.intersection(path.parts) or path.suffix.lower() in products or any(
                part.endswith(".rep") for part in path.parts):
            raise ValueError("private input or generated product is tracked: " + name)
        absolute = ROOT / path
        if not absolute.exists():  # Allow unstaged deletions during local work.
            continue
        with absolute.open("rb") as stream:
            signature = stream.read(8)
        if signature.startswith((b"MZ", b"\x7fELF", b"!<arch>\n", b"PK\x03\x04")):
            raise ValueError("binary input or product is tracked: " + name)
        if path.suffix == ".py":
            ast.parse(absolute.read_bytes(), filename=name)
        elif path.suffix == ".json":
            json.loads(absolute.read_text())
        elif path.suffix == ".toml":
            tomllib.loads(absolute.read_text())
        elif path.suffix == ".sh" or name in {"scripts/repo-python", "scripts/rea", "scripts/ghidra"}:
            run(["bash", "-n", absolute])
        checked += 1
    print(f"Syntax and artifact checks OK: {checked} tracked files", flush=True)


def main():
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--public", action="store_true",
                        help="compatibility flag; checks are public by default")
    parser.add_argument("--build", action="store_true", help="also compile the portable targets")
    parser.add_argument("--require-target", action="store_true", help="also verify the local original EXE")
    args = parser.parse_args()
    check_files()
    python("scripts/validate-tracking.py", *(["--require-target"] if args.require_target else []))
    # A temporary tree cannot borrow a previous developer's CMake cache.
    with tempfile.TemporaryDirectory(prefix="dxball-ci-") as directory:
        run(["cmake", "-S", ROOT, "-B", directory, "-DCMAKE_BUILD_TYPE=Debug"])
        if args.build:
            run(["cmake", "--build", directory, "--parallel", str(BUILD_JOBS)])
    print("Public checks passed. Select complete comparisons and behavior checks for affected changes.")


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as exc:
        sys.exit(exc.returncode)
    except (OSError, ValueError) as exc:
        print(f"public checks failed: {exc}", file=sys.stderr)
        sys.exit(1)
