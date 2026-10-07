#!/usr/bin/env python3
"""Attest the actual imported Python wrappers and native analysis libraries."""
import hashlib
import importlib
from pathlib import Path
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def verify():
    lock = tomllib.loads((ROOT / "config/tools.lock.toml").read_text())["python"]
    for name, expected in lock.items():
        module = importlib.import_module(name)
        if module.__version__ != expected["version"]:
            raise ValueError(f"{name} version mismatch: {module.__version__}")
        wrapper = Path(module.__file__)
        if hashlib.sha256(wrapper.read_bytes()).hexdigest() != expected["wrapper_sha256"]:
            raise ValueError(f"{name} Python wrapper hash mismatch")
        if name == "capstone":
            native = Path(module._cs._name)
        elif name == "unicorn":
            native = Path(importlib.import_module(module.Uc.__module__).uclib._name)
        else:
            continue
        if hashlib.sha256(native.read_bytes()).hexdigest() != expected["native_sha256"]:
            raise ValueError(f"{name} loaded native library hash mismatch")


if __name__ == "__main__":
    try:
        verify()
        print(f"Python analysis tools OK: {sys.executable}")
    except (OSError, ValueError, ImportError, AttributeError, KeyError) as exc:
        print(f"Python attestation failed: {exc}", file=sys.stderr)
        sys.exit(1)
