#!/usr/bin/env python3
"""Generate progress counts, verification results and the inventory graphic."""
import csv
import importlib.util
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("status", ROOT / "scripts/report-reconstruction-status.py")
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)


def main():
    status = module.status()
    with (ROOT / "config/functions.csv").open() as stream:
        functions = list(csv.DictReader(stream))
    with (ROOT / "config/matches.csv").open() as stream:
        exact = {row["address"] for row in csv.DictReader(stream)}
    with (ROOT / "config/implemented.csv").open() as stream:
        source = {row["address"] for row in csv.DictReader(stream)}
    svg = ['<svg xmlns="http://www.w3.org/2000/svg" width="900" height="460" viewBox="0 0 900 460" role="img" aria-labelledby="title desc">',
           '<title id="title">DX-Ball reconstruction progress</title>',
           f'<desc id="desc">{status["authored_exact_functions"]} of {status["authored_confirmed"]} authored functions exact; {status["exact_functions"]} exact entries in the full {len(functions)}-entry inventory.</desc>',
           '<rect width="900" height="460" rx="20" fill="#101722"/>',
           '<g font-family="sans-serif">',
           '<text x="34" y="46" fill="#eef4ff" font-size="25" font-weight="bold">DX-BALL  /  RECONSTRUCTION</text>',
           '<text x="34" y="75" fill="#9baec8" font-size="14">English v1.07 · REA / Ghidra · Visual C++ 4.0</text>',
           f'<text x="34" y="109" fill="#4ed8b7" font-size="16">{status["authored_exact_functions"]}/{status["authored_confirmed"]} authored exact · {status["authored_exact_bytes"]:,} bytes</text>',
           f'<text x="520" y="109" fill="#f5bd57" font-size="16">{status["exact_functions"]} exact total · {status["source_present"]} source-present</text>']
    for i, function in enumerate(functions):
        color = "#4ed8b7" if function["address"] in exact else "#f5bd57" if function["address"] in source else "#29384c"
        x, y = 34 + (i % 33) * 25, 132 + (i // 33) * 14
        svg.append(f'<rect x="{x}" y="{y}" width="22" height="10" rx="2" fill="{color}"/>')
    svg += ['<text x="34" y="388" fill="#9baec8" font-size="13">Green: exact · Amber: source present · Dark: source missing</text>',
            '<text x="34" y="412" fill="#9baec8" font-size="13">Inventory includes game routines, CRT dependencies and compiler-generated entries.</text>',
            '</g></svg>']
    (ROOT / "resources").mkdir(exist_ok=True)
    (ROOT / "resources/progress.svg").write_text("\n".join(svg) + "\n")

    play = status["playability"]
    build = play["build"]
    lines = ["# Reconstruction progress", "", f"Updated {play['updated']}.", "", "## Source reconstruction", "",
             "| Item | Result |", "| --- | ---: |",
             f"| Authored functions with source | {status['authored_source_present']} / {status['authored_confirmed']} |",
             f"| Authored exact functions | {status['authored_exact_functions']} / {status['authored_confirmed']} |",
             f"| Authored exact code bytes | {status['authored_exact_bytes']:,} / {status['authored_code_bytes']:,} |",
             f"| Authored compiler closures | {status['authored_compiler_closures']} |",
             f"| Authored nonexact functions | {status['authored_nonexact']} |", "",
             "## Build and playability", "",
             f"The {play['profile']} game builds with Visual C++ 4.0. It links "
             f"{build['source_objects']} source objects, {build['integration_objects']} integration objects "
             f"and {build['original_crt_members']} original CRT members.", "",
             f"Verification environment: {play['environment']}.", "",
             "| Check | Status | Observed result |", "| --- | --- | --- |"]
    labels = {"passed": "Passed", "failed": "Failed"}
    for check in play["checks"]:
        lines.append(f"| {check['name']} | {labels[check['status']]} | {check['result']} |")
    lines += ["", "See [the build record](research/CURRENT_VC4_BUILD.md) and "
              "[playability results](research/PLAYABILITY_20261022.md) for the tested image and evidence.",
              "", "## Still to verify", ""]
    lines += ["- " + item for item in play["remaining"]]
    lines += ["", "## Full function inventory", "",
              "The inventory also contains CRT routines and compiler-generated entries.", "",
              "| Item | Count |", "| --- | ---: |",
              f"| Provisional independent entries | {status['function_candidates']} |",
              f"| Parent-owned compiler fragments | {status['parent_owned_compiler_fragments']} |",
              f"| Source-present entries | {status['source_present']} |",
              f"| Exact entries | {status['exact_functions']} |",
              f"| Exact code bytes | {status['exact_bytes']:,} |",
              f"| Scoped semantic acceptances | {status['semantic_validated_with_scope']} |",
              f"| Source-present nonexact entries | {status['source_present_nonexact']} |",
              f"| Entries without source | {status['source_missing']} |", "",
              "| Origin | Source-present nonexact | Without source |",
              "| --- | ---: | ---: |"]
    origin_labels = {"authored": "Authored", "runtime": "Runtime", "compiler_generated": "Compiler-generated", "unknown": "Unknown"}
    for origin in sorted(status["source_present_nonexact_origins"].keys() | status["source_missing_origins"].keys()):
        lines.append(f"| {origin_labels[origin]} | {status['source_present_nonexact_origins'].get(origin, 0)} | {status['source_missing_origins'].get(origin, 0)} |")
    lines += ["",
              "Generated by `scripts/repo-python scripts/progress.py` from the function ledgers "
              "and [verification record](../config/playability-status.json)."]
    (ROOT / "docs/PROGRESS.md").write_text("\n".join(lines) + "\n")
    print("generated resources/progress.svg and docs/PROGRESS.md")


if __name__ == "__main__":
    main()
