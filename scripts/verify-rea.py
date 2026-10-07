#!/usr/bin/env python3
"""Verify REA's actual MCP/Ghidra path against the independent target oracle."""
import importlib.util
import argparse
import json
import subprocess

import pefile
from legacy_toolchain import ROOT, session_lock
from rea import environment


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--saved", action="store_true", help="verify already captured smoke evidence")
    args = parser.parse_args()
    spec = importlib.util.spec_from_file_location("verify_target", ROOT / "scripts/verify-target.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    _, manifest, image = module.verify()
    node, _, env = environment()
    lock = session_lock()
    if not args.saved:
        subprocess.run([str(node), str(ROOT / "scripts/rea-session.mjs"),
                        str(ROOT / "config/rea-smoke.json")], env=env, cwd=ROOT, check=True)
    directory = ROOT / ".analysis/rea"
    snapshot_path = directory / "dxball.snapshot.json"
    if args.saved:
        # Interactive queries also update the root convenience aliases. Reuse
        # one complete smoke run instead of mixing its records with later work.
        runs = sorted((directory / "runs").glob("*-rea-smoke-*"))
        completed = [run for run in runs if (run / "close.json").is_file()]
        if not completed:
            raise ValueError("No completed REA smoke run; run verification without --saved")
        directory = completed[-1]
    opened = json.loads((directory / "open.json").read_text())["result"]
    if opened["sha256"] != manifest["target"]["sha256"] or opened["architecture"] != "x86":
        raise ValueError("REA opened another target")
    loaded = json.loads((directory / "02-read_bytes.json").read_text())["result"]
    pe = pefile.PE(data=image)
    expected = pe.get_data(0x404180 - pe.OPTIONAL_HEADER.ImageBase, 105)
    if not loaded["complete"] or bytes.fromhex(loaded["bytes_hex"]) != expected:
        raise ValueError("REA loaded-byte observation disagrees with independent PE bytes")
    dossier = json.loads((directory / "01-analyze_function.json").read_text())
    if int(dossier["result"]["procedure"]["address"], 0) != 0x404180:
        raise ValueError("REA smoke evidence belongs to another function")
    body = dossier["result"]["procedure"]["body"]
    if not body["available"] or body["total_bytes"] != 105:
        raise ValueError("REA accepted sprite function extent changed; reconcile ledger")
    snapshot = json.loads(snapshot_path.read_text())
    if snapshot["target"]["sha256"] != manifest["target"]["sha256"]:
        raise ValueError("REA snapshot belongs to another target")
    closed = json.loads((directory / "close.json").read_text())["result"]
    if closed["path"] != str(snapshot_path) or closed["bytes"] <= 0:
        raise ValueError("REA close did not save the configured snapshot")
    evidence_ids = {record["evidence_id"] for record in snapshot["evidence_bundle"]["records"]}
    for name in ("00-binary_overview", "01-analyze_function", "02-read_bytes",
                 "03-inspect_native_load_image", "04-analyze_function"):
        record = json.loads((directory / (name + ".json")).read_text())
        if record["evidence_id"] not in evidence_ids:
            raise ValueError("REA snapshot omitted a smoke Evidence record")
    if snapshot["binding"]["provider"]["version"] != "12.1.4":
        raise ValueError("REA snapshot provider differs from the pinned installation")
    print("REA MCP/Ghidra verified: target SHA, x86, full 105-byte function, loaded bytes, snapshot and close")
    print("Evidence run:", directory.relative_to(ROOT))


if __name__ == "__main__":
    main()
