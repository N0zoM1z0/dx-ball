#!/usr/bin/env python3
"""Report independent source, semantic, and byte-exact reconstruction facts."""
import argparse
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
    units_path = ROOT / "config/match-units.toml"
    units = tomllib.loads(units_path.read_text())["units"] if units_path.exists() else {}
    return {"target": "DX-Ball v1.07 (English)", "function_candidates": len(functions),
            "source_present": len(implementations), "exact_functions": len(matches),
            "exact_bytes": sum(units[row["unit"]]["size"] for row in matches),
            "authored_confirmed": sum(row["origin"] == "authored" for row in origins),
            "origin_unknown": sum(row["origin"] == "unknown" for row in origins),
            "semantic_validated_with_scope": len(semantics),
            "semantic_units": sorted({row["unit"] for row in semantics}),
            "playable": False,
            "denominator": "528 provisional Ghidra candidates, including unclassified CRT/library code"}


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
        print(f"Authored confirmed: {result['authored_confirmed']}; origin unknown: {result['origin_unknown']}")
        print("Playable game: no; current products are board-analysis utilities")
