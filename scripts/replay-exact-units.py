#!/usr/bin/env python3
"""Cold-build canonical shared source and compare every byte after relocations."""
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tomllib

import pefile
from coff import function, symbol_data
from legacy_toolchain import ROOT, Toolchain, session_lock, sha256

spec = importlib.util.spec_from_file_location("verify_target", ROOT / "scripts/verify-target.py")
verify_target = importlib.util.module_from_spec(spec)
spec.loader.exec_module(verify_target)


def compare(object_path, unit, pe):
    code, actual_relocations = function(object_path, unit["symbol"])
    expected = unit["relocations"]
    actual_keys = [(r["offset"], r["type"], r["symbol"]) for r in actual_relocations]
    expected_keys = [(r["offset"], r["type"], r["symbol"]) for r in expected]
    if sorted(actual_keys) != sorted(expected_keys):
        raise ValueError(f"relocation manifest differs for {unit['symbol']}: {actual_relocations}")
    address = unit["target_address"]
    mappings = {(r["offset"], r["type"], r["symbol"]): r for r in expected}
    for actual in actual_relocations:
        row = mappings[(actual["offset"], actual["type"], actual["symbol"])]
        if actual["addend"] != row["addend"]:
            raise ValueError(f"relocation addend differs: {actual}")
        if row["symbol"].startswith("$SG") and "data_hex" not in row:
            raise ValueError("literal relocation lacks content attestation")
        if "data_hex" in row:
            literal = bytes.fromhex(row["data_hex"])
            if (symbol_data(object_path, row["symbol"], len(literal)) != literal or
                    pe.get_data(row["target"] - pe.OPTIONAL_HEADER.ImageBase,
                                len(literal)) != literal):
                raise ValueError("object/target mapped literal differs")
        resolved = row["target"] + actual["addend"]
        if row["type"] == "REL32":
            resolved -= address + row["offset"] + 4
        struct.pack_into("<I", code, row["offset"], resolved & 0xFFFFFFFF)
    target = pe.get_data(address - pe.OPTIONAL_HEADER.ImageBase, unit["size"])
    if len(target) != unit["size"]:
        raise ValueError("target extent is not fully file-backed")
    differences = [i for i in range(max(len(code), len(target)))
                   if i >= len(code) or i >= len(target) or code[i] != target[i]]
    return {"symbol": unit["symbol"], "address": f"0x{address:08X}",
            "object_size": len(code), "target_size": len(target),
            "relocations": actual_relocations, "difference_count": len(differences),
            "first_differences": differences[:24], "exact": not differences,
            "relocated_sha256": hashlib.sha256(code).hexdigest(),
            "target_span_sha256": hashlib.sha256(target).hexdigest()}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--unit", action="append", help="replay only named units")
    parser.add_argument("--report", type=Path, default=ROOT / "build/reports/exact-replay.json")
    args = parser.parse_args()
    config_path = ROOT / "config/match-units.toml"
    manifest = tomllib.loads(config_path.read_text())
    builds = manifest["builds"]
    selected = {name: unit for name, unit in manifest["units"].items()
                if not args.unit or name in args.unit}
    if not selected or (args.unit and set(args.unit) - selected.keys()):
        raise ValueError("no units or unknown requested unit")
    path, target_manifest, data = verify_target.verify()
    lock = session_lock()
    toolchain = Toolchain()
    tools = toolchain.verify(execute=True)
    pe = pefile.PE(data=data)
    report = {"target_sha256": target_manifest["target"]["sha256"],
              "compiler_sha256": tools["compiler_sha256"],
              "manifest_sha256": sha256(config_path),
              "builds": {}, "units": {}}
    for build_name in dict.fromkeys(unit["build"] for unit in selected.values()):
        build = builds[build_name]
        output = ROOT / build["object"]
        compiled = toolchain.compile(ROOT / build["source"], output, build["flags"])
        output.with_suffix(".log").write_text(compiled.stdout)
        report["builds"][build_name] = {
            "object_sha256": sha256(output),
            "inputs": {name: sha256(ROOT / name) for name in build["inputs"]},
            "flags": build["flags"], "object": build["object"]}
    for name, unit in selected.items():
        output = ROOT / builds[unit["build"]]["object"]
        result = compare(output, unit, pe)
        result["build"] = unit["build"]
        report["units"][name] = result
        print(f"{'EXACT' if result['exact'] else 'DIFF'} {name}: "
              f"{result['difference_count']} differing bytes, "
              f"{result['object_size']}/{result['target_size']} bytes", flush=True)
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, indent=2) + "\n")
    return 0 if all(r["exact"] for r in report["units"].values()) else 1


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (OSError, ValueError, RuntimeError) as exc:
        print(f"exact replay failed: {exc}", file=sys.stderr)
        sys.exit(1)
