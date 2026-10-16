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


def validate_build_owners(manifest, implementations):
    by_address = {int(address, 0): row for address, row in implementations.items()}
    for group in ("units", "candidates"):
        for name, unit in manifest.get(group, {}).items():
            implementation = by_address.get(unit["target_address"])
            build = manifest["builds"][unit["build"]]
            if implementation is None or build["source"] != implementation["source"]:
                raise ValueError(f"{group} build owner disagrees with source ledger: {name}")


def validate_generated_source(address, implementation, source, origins, matches, manifest):
    name = implementation["semantic_unit"]
    unit = manifest["units"].get(name, manifest.get("candidates", {}).get(name))
    if unit is None or "source_generator" not in unit:
        return False
    generator = unit["source_generator"]
    if generator.get("kind") == "vc4-global-embedded-list-initializer":
        expected_generator = dict(kind="vc4-global-embedded-list-initializer",
            type="DxBallBoardStorage", global_name="dxball_board_storage",
            member="explosions", member_type="DxBallExplosionList",
            member_offset=20008, storage_header="src/board_storage.h",
            constructor_unit="initialize-explosion-list", inner_unit="list-global-init-13",
            stage=generator.get("stage"))
        build = manifest["builds"][unit["build"]]
        if (generator != expected_generator or
                origins[address]["origin"] != "compiler_generated" or
                unit["symbol"] != implementation["symbol"] or
                unit["target_address"] != int(address, 0) or
                build["source"] != implementation["source"] or
                build["flags"].count("/Ob1") != 1 or "/Ob0" in build["flags"] or
                generator["storage_header"] not in build["inputs"] or
                not re.search(r"^\s*DxBallBoardStorage\s+dxball_board_storage\s*;\s*$", source, re.MULTILINE)):
            raise ValueError(f"invalid embedded initializer identity: {address}")
        storage = (ROOT / generator["storage_header"]).read_text()
        if (not re.search(r"\bDxBallExplosionList\s+explosions\s*;", storage) or
                "offsetof(DxBallBoardStorage, explosions) == 20008" not in storage or
                not re.search(r"DxBallExplosionList::DxBallExplosionList\s*\([^;]*\)\s*\{", source)):
            raise ValueError(f"missing embedded initializer source anchor: {address}")
        ctor = manifest["units"][generator["constructor_unit"]]
        inner = manifest["candidates"][generator["inner_unit"]]
        if (ctor["build"] != unit["build"] or inner["build"] != unit["build"] or
                ctor["symbol"] != "??0DxBallExplosionList@@QAE@XZ" or
                matches.get(f'0x{ctor["target_address"]:08X}', {}).get("unit") != generator["constructor_unit"] or
                inner.get("source_generator") != dict(generator, stage="inner")):
            raise ValueError(f"unattested embedded initializer dependency: {address}")
        expected_inner = [dict(offset=8, type="DIR32", symbol="_dxball_board_storage",
                               addend=20008, target=0x0043AAB8),
                          dict(offset=13, type="REL32", symbol=ctor["symbol"],
                               addend=0, target=ctor["target_address"])]
        if (inner["symbol"] != "_$E13" or inner["target_address"] != 0x0040F320 or
                inner["size"] != 26 or inner["relocations"] != expected_inner):
            raise ValueError(f"invalid embedded constructor bindings: {address}")
        if generator["stage"] == "inner":
            if name != generator["inner_unit"] or address in matches:
                raise ValueError(f"embedded inner stage is not exact: {address}")
        elif generator["stage"] == "outer":
            if (name != "list-global-init-14" or unit["target_address"] != 0x0040F140 or
                    unit["symbol"] != "_$E14" or unit["size"] != 21 or
                    matches.get(address, {}).get("unit") != name or
                    unit["relocations"] != [dict(offset=7, type="REL32",
                        symbol=inner["symbol"], addend=0, target=inner["target_address"])]):
                raise ValueError(f"invalid embedded outer binding: {address}")
        else:
            raise ValueError("unknown embedded source stage")
        return True
    fields = {"kind", "type", "global", "constructor_unit", "inner_unit", "stage"}
    if (set(generator) != fields or generator["kind"] != "vc4-global-list-initializer" or
            origins[address]["origin"] != "compiler_generated" or
            unit["symbol"] != implementation["symbol"] or
            unit["target_address"] != int(address, 0) or
            manifest["builds"][unit["build"]]["source"] != implementation["source"] or
            matches.get(address, {}).get("unit") != name):
        raise ValueError(f"invalid generated source identity: {address}")
    type_name, global_name = generator["type"], generator["global"]
    for identifier in (type_name, global_name):
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", identifier):
            raise ValueError("invalid generated source declaration")
    declaration = r"^\s*" + re.escape(type_name) + r"\s+" + re.escape(global_name) + r"\s*;\s*$"
    constructor = re.escape(type_name + "::" + type_name) + r"\s*\([^;]*\)\s*\{"
    if not re.search(declaration, source, re.MULTILINE) or not re.search(constructor, source):
        raise ValueError(f"missing real generated source anchor: {address}")
    ctor = manifest["units"][generator["constructor_unit"]]
    inner = manifest["units"][generator["inner_unit"]]
    expected_inner = dict(generator, stage="inner")
    if (ctor["build"] != unit["build"] or inner["build"] != unit["build"] or
            ctor["symbol"] != "??0" + type_name + "@@QAE@XZ" or
            inner.get("source_generator") != expected_inner or
            matches.get(f'0x{ctor["target_address"]:08X}', {}).get("unit") != generator["constructor_unit"] or
            matches.get(f'0x{inner["target_address"]:08X}', {}).get("unit") != generator["inner_unit"]):
        raise ValueError(f"unattested generated source dependency: {address}")
    if generator["stage"] == "inner":
        relocations = unit["relocations"]
        if (unit["size"] != 26 or len(relocations) != 2 or
                relocations[0] != dict(offset=7, type="DIR32", symbol="_" + global_name,
                                       addend=0, target=relocations[0]["target"]) or
                relocations[1] != dict(offset=12, type="REL32", symbol=ctor["symbol"],
                                       addend=0, target=ctor["target_address"])):
            raise ValueError(f"invalid generated constructor bindings: {address}")
    elif generator["stage"] == "outer":
        expected = [dict(offset=7, type="REL32", symbol=inner["symbol"],
                         addend=0, target=inner["target_address"])]
        if unit["size"] != 21 or unit["relocations"] != expected:
            raise ValueError(f"invalid generated initializer binding: {address}")
    else:
        raise ValueError("unknown generated source stage")
    return True


def validate_compiler_fragments(functions, origins, implementations, semantics, matches, manifest):
    fragments = unique(rows("compiler-fragments.csv"), "address")
    units = dict(manifest.get("units", {}), **manifest.get("candidates", {}))
    for address, fragment in fragments.items():
        if any(address in ledger for ledger in
               (functions, origins, implementations, semantics, matches)):
            raise ValueError(f"compiler fragment counted independently: {address}")
        parent = units[fragment["parent_unit"]]
        parent_address = f"0x{parent['target_address']:08X}"
        build = manifest["builds"][parent["build"]]
        start, size = int(address, 0), int(fragment["size"])
        end = int(fragment["span_end"], 0)
        if (size <= 0 or end != start + size - 1 or
                not parent["target_address"] < start <= end <
                    parent["target_address"] + parent["size"] or
                fragment["parent_address"] != parent_address or
                fragment["parent_symbol"] != parent["symbol"] or
                fragment["source"] != build["source"] or
                implementations[parent_address]["source"] != build["source"] or
                not re.fullmatch(r"ev_[0-9a-f]{64}", fragment["evidence_id"])):
            raise ValueError(f"invalid compiler fragment ownership: {address}")
        if fragment["kind"] == "unwind_cleanup":
            bindings = [row for metadata in parent.get("data_comdats", [])
                        if metadata["symbol"] == fragment["metadata_symbol"]
                        for row in metadata["relocations"]
                        if row["symbol"] == fragment["source_label"] and
                           row["target"] == start]
            if len(bindings) != 1:
                raise ValueError(f"compiler cleanup lacks parent unwind binding: {address}")
        elif fragment["kind"] == "shared_epilogue":
            if (end + 1 != parent["target_address"] + parent["size"] or
                    fragment["metadata_symbol"] or fragment["source_label"]):
                raise ValueError(f"invalid parent epilogue extent: {address}")
        else:
            raise ValueError(f"unknown compiler fragment kind: {address}")


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
    manifest_path = ROOT / "config/match-units.toml"
    manifest = tomllib.loads(manifest_path.read_text()) if manifest_path.exists() else {"units": {}}
    validate_compiler_fragments(functions, origins, implementations, semantics, matches, manifest)
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
        source = path.read_text()
        if validate_generated_source(address, implementation, source, origins, matches, manifest):
            continue
        if not re.search(r"\b" + re.escape(implementation["symbol"]) + r"\s*\([^;]*\)\s*\{", source):
            raise ValueError(f"missing source definition: {implementation['symbol']}")
    for address, accepted in semantics.items():
        if address not in implementations or accepted["unit"] != implementations[address]["semantic_unit"]:
            raise ValueError("semantic unit absent from source ledger")
        if accepted["target_sha256"] != target["target"]["sha256"] or int(accepted["cases"]) <= 0:
            raise ValueError("invalid semantic evidence identity/count")
        owner = by_source[implementations[address]["source"]]
        oracle = owner.get("unit_oracles", {}).get(accepted["unit"], owner["oracle"])
        for field, path in (("source_sha256", ROOT / implementations[address]["source"]),
                            ("header_sha256", ROOT / owner["header"]),
                            ("oracle_sha256", ROOT / oracle),
                            ("target_oracle_sha256", ROOT / owner["target_oracle"])):
            if accepted[field] != sha(path):
                raise ValueError(f"accepted semantic input changed: {field}")
        inputs = [owner[field] for field in ("source", "header", "target_oracle")]
        inputs.append(oracle)
        inputs += owner["additional_inputs"]
        if json.loads(accepted["inputs_sha256"]) != {name: sha(ROOT / name) for name in inputs}:
            raise ValueError("accepted semantic input set changed; replay required")
    validate_build_owners(manifest, implementations)
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
        if (build["source"] != match["source"] or
                match["source"] != implementations[address]["source"]):
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
