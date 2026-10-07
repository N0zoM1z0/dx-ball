#!/usr/bin/env python3
"""Check reconstruction ledgers without confusing source presence with exactness."""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import re
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def rows(name):
    with (ROOT / "config" / name).open(newline="") as stream:
        return list(csv.DictReader(stream))


def unique(records, key):
    result = {record[key]: record for record in records}
    if len(result) != len(records):
        raise ValueError(f"duplicate {key} in ledger")
    return result


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def validate(require_target=False):
    target = tomllib.loads((ROOT / "config/target.toml").read_text())
    pe = target["pe"]
    functions = unique(rows("functions.csv"), "address")
    origins = unique(rows("function-origins.csv"), "address")
    implementations = unique(rows("implemented.csv"), "address")
    semantics = unique(rows("semantic-acceptance.csv"), "address")
    matches = unique(rows("matches.csv"), "address")
    owners = tomllib.loads((ROOT / "config/source-owners.toml").read_text())["owners"]
    by_source = {owner["source"]: owner for owner in owners.values()}
    if functions.keys() != origins.keys():
        raise ValueError("function and origin ledgers disagree")
    for address, function in functions.items():
        start, size, end = int(address, 0), int(function["size"]), int(function["span_end"], 0)
        if size <= 0 or end != start + size - 1 or not (
                int(pe["text_start"], 0) <= start <= end <= int(pe["text_end"], 0)):
            raise ValueError(f"invalid provisional function extent: {address}")
    for address, implementation in implementations.items():
        if address not in functions or functions[address]["source_file"] != implementation["source"]:
            raise ValueError(f"implementation absent from function ledger: {address}")
        path = (ROOT / implementation["source"]).resolve()
        path.relative_to((ROOT / "src").resolve())
        if not re.search(r"\b" + re.escape(implementation["symbol"]) + r"\s*\([^;]*\)\s*\{",
                         path.read_text()):
            raise ValueError(f"missing source definition: {implementation['symbol']}")
    for address, accepted in semantics.items():
        if address not in implementations or accepted["unit"] != implementations[address]["semantic_unit"]:
            raise ValueError("semantic unit absent from source ledger")
        if accepted["target_sha256"] != target["target"]["sha256"] or int(accepted["cases"]) <= 0:
            raise ValueError("invalid semantic evidence identity/count")
        owner = by_source[implementations[address]["source"]]
        for field, path in (("source_sha256", ROOT / implementations[address]["source"]),
                            ("header_sha256", ROOT / owner["header"]),
                            ("oracle_sha256", ROOT / owner["oracle"]),
                            ("target_oracle_sha256", ROOT / owner["target_oracle"])):
            if accepted[field] != sha(path):
                raise ValueError(f"accepted semantic input changed: {field}")
        inputs = [owner[field] for field in ("source", "header", "oracle", "target_oracle")]
        inputs += owner["additional_inputs"]
        if json.loads(accepted["inputs_sha256"]) != {name: sha(ROOT / name) for name in inputs}:
            raise ValueError("accepted semantic input set changed; replay required")
    manifest_path = ROOT / "config/match-units.toml"
    manifest = tomllib.loads(manifest_path.read_text()) if manifest_path.exists() else {"units": {}}
    for address, match in matches.items():
        if address not in implementations or int(match["difference_count"]) != 0:
            raise ValueError(f"invalid exact claim: {address}")
        unit = manifest["units"].get(match["unit"])
        if unit is None or unit["target_address"] != int(address, 0) or unit["size"] != int(functions[address]["size"]):
            raise ValueError(f"exact unit extent disagrees with function ledger: {address}")
        if match["target_sha256"] != target["target"]["sha256"]:
            raise ValueError("exact row uses another target")
        tools = tomllib.loads((ROOT / "config/tools.lock.toml").read_text())
        if match["compiler_sha256"] != tools["msvc40"]["compiler_sha256"]:
            raise ValueError("exact row uses another compiler")
        build = manifest["builds"][unit["build"]]
        owner = by_source[match["source"]]
        if build["source"] != match["source"]:
            raise ValueError("exact unit build owner disagrees with source ledger")
        for field, path in (("source_sha256", ROOT / match["source"]),
                            ("header_sha256", ROOT / owner["header"]),
                            ("manifest_sha256", manifest_path)):
            if match[field] != sha(path):
                raise ValueError(f"accepted exact input changed; replay and refresh evidence: {field}")
        if json.loads(match["inputs_sha256"]) != {name: sha(ROOT / name) for name in build["inputs"]}:
            raise ValueError("accepted exact build input set changed; replay required")
    if rows("claims.csv"):
        raise ValueError("one-session claims ledger must be header-only")
    if require_target:
        import importlib.util
        spec = importlib.util.spec_from_file_location("verify_target", ROOT / "scripts/verify-target.py")
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        module.verify()
    return functions, implementations, matches


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--require-target", action="store_true")
    args = parser.parse_args()
    try:
        functions, implementations, matches = validate(args.require_target)
        print(f"tracking OK: {len(functions)} candidates, {len(implementations)} source-present, {len(matches)} exact")
    except (OSError, ValueError, KeyError) as exc:
        print(f"tracking validation failed: {exc}", file=sys.stderr)
        sys.exit(1)
