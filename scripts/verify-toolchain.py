#!/usr/bin/env python3
"""Attest the pinned VC4.0 candidate and optionally execute compiler/linker."""
import argparse
import sys
from legacy_toolchain import Toolchain, session_lock


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--execute", action="store_true")
    args = parser.parse_args()
    lock = session_lock()
    expected = Toolchain().verify(args.execute)
    print("toolchain OK: " + expected["compiler_banner"])
    print(expected["linker_banner"])
    print("identity: candidate; per-unit exact evidence is tracked separately")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError, RuntimeError) as exc:
        print(f"toolchain verification failed: {exc}", file=sys.stderr)
        sys.exit(1)
