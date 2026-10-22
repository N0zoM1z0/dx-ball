#!/usr/bin/env python3
"""Report independent source, semantic, and byte-exact reconstruction facts."""
import argparse
from collections import Counter
import csv
import json
from pathlib import Path
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def status():
    def read(name):
        with (ROOT / "config" / name).open() as stream:
            return list(csv.DictReader(stream))
    functions = read("functions.csv")
    implementations = read("implemented.csv")
    matches = read("matches.csv")
    semantics = read("semantic-acceptance.csv")
    origins = read("function-origins.csv")
    fragments = read("compiler-fragments.csv")
    units_path = ROOT / "config/match-units.toml"
    units = tomllib.loads(units_path.read_text())["units"] if units_path.exists() else {}
    authored = {row["address"] for row in origins if row["origin"] == "authored"}
    source = {row["address"] for row in implementations}
    exact = {row["address"] for row in matches}
    authored_matches = [row for row in matches if row["address"] in authored]
    all_entries = {row["address"] for row in functions}
    origin_by_address = {row["address"]: row["origin"] for row in origins}
    def origin_counts(addresses):
        return dict(sorted(Counter(origin_by_address[address] for address in addresses).items()))

    playability = json.loads((ROOT / "config/playability-status.json").read_text())
    return {"target": "DX-Ball v1.07 (English)", "function_candidates": len(functions),
            "source_present": len(implementations), "exact_functions": len(matches),
            "parent_owned_compiler_fragments": len(fragments),
            "exact_bytes": sum(units[row["unit"]]["size"] for row in matches),
            "authored_confirmed": sum(row["origin"] == "authored" for row in origins),
            "authored_source_present": len(authored & source),
            "authored_exact_functions": len(authored & exact),
            "authored_code_bytes": sum(int(row["size"]) for row in functions if row["address"] in authored),
            "authored_exact_bytes": sum(units[row["unit"]]["size"] for row in authored_matches),
            "authored_compiler_closures": len({units[row["unit"]]["build"] for row in authored_matches}),
            "authored_nonexact": len((authored & source) - exact),
            "source_present_nonexact": len(source - exact),
            "source_present_nonexact_origins": origin_counts(source - exact),
            "source_missing": len(all_entries - source),
            "source_missing_origins": origin_counts(all_entries - source),
            "runtime_identified": sum(row["origin"] == "runtime" for row in origins),
            "compiler_generated_identified": sum(row["origin"] == "compiler_generated" for row in origins),
            "origin_unknown": sum(row["origin"] == "unknown" for row in origins),
            "semantic_validated_with_scope": len(semantics),
            "semantic_units": sorted({row["unit"] for row in semantics}),
            "playable": any(row["id"] == "basic_editor" and row["status"] == "passed" for row in playability["checks"]),
            "playability": playability,
            "products": ["VC4 restored-CRT Windows game", "portable analysis library", "board/resource inspectors", "read-only Windows probes"],
            "windows_runtime_scope": playability["summary"],
            "denominator": f"{len(functions)} provisional independent entries, including compiler-generated initialization and unclassified CRT/library code; {len(fragments)} parent-owned compiler fragments are tracked separately"}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--summary", action="store_true")
    args = parser.parse_args()
    result = status()
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print(f"{result['target']}: {result['function_candidates']} provisional candidates")
        print(f"Source-present: {result['source_present']}; exact: {result['exact_functions']} ({result['exact_bytes']} bytes)")
        print(f"Authored exact: {result['authored_exact_functions']}/{result['authored_confirmed']} functions; {result['authored_exact_bytes']}/{result['authored_code_bytes']} bytes; {result['authored_compiler_closures']} compiler closures")
        print(f"Parent-owned compiler fragments: {result['parent_owned_compiler_fragments']} (excluded from the independent entry count)")
        print(f"Authored confirmed: {result['authored_confirmed']}; runtime identified: {result['runtime_identified']}; compiler-generated identified: {result['compiler_generated_identified']}; origin unknown: {result['origin_unknown']}")
        print(f"Windows runtime scope: {result['windows_runtime_scope']}")
