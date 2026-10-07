#!/usr/bin/env python3
"""Verify the canonical DX-Ball v1.07 executable and its PE mapping."""
import argparse
import hashlib
from pathlib import Path
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def verify(path=None):
    manifest = tomllib.loads((ROOT / "config/target.toml").read_text())
    target = manifest["target"]
    path = Path(path) if path else ROOT / "original" / target["filename"]
    data = path.read_bytes()
    for field, actual in (("size", len(data)),
                          ("sha256", hashlib.sha256(data).hexdigest()),
                          ("md5", hashlib.md5(data).hexdigest())):
        if actual != target[field]:
            raise ValueError(f"{field} mismatch: {actual} != {target[field]}")
    # Same standard-library PE mapping check used by the Ghidra wrapper.
    import ghidra
    ghidra.verify_pe_manifest(data, manifest["pe"])
    return path, manifest, data


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", nargs="?", type=Path)
    args = parser.parse_args()
    try:
        path, manifest, _ = verify(args.executable)
        print(f"target OK: {path.resolve()}\nsha256: {manifest['target']['sha256']}")
    except (OSError, ValueError, KeyError) as exc:
        print(f"target verification failed: {exc}", file=sys.stderr)
        sys.exit(1)
