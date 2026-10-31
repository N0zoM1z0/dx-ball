#!/usr/bin/env python3
"""Generate authored completion, verification results and the progress graphic."""
import csv
import importlib.util
from html import escape
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("status", ROOT / "scripts/report-reconstruction-status.py")
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)


def main():
    status = module.status()
    authored = status['authored_confirmed']
    authored_exact = status['authored_exact_functions']
    fraction = authored_exact / authored if authored else 0
    with (ROOT / "config/function-origins.csv").open() as stream:
        authored_addresses = {row['address'] for row in csv.DictReader(stream)
                              if row['origin'] == 'authored'}
    with (ROOT / "config/functions.csv").open() as stream:
        functions = [row for row in csv.DictReader(stream)
                     if row['address'] in authored_addresses]
    with (ROOT / "config/matches.csv").open() as stream:
        exact = {row['address'] for row in csv.DictReader(stream)}
    columns = 30
    rows = (len(functions) + columns - 1) // columns
    grid_bottom = 132 + max(rows - 1, 0) * 14 + 10
    height = grid_bottom + 76
    svg = [f'<svg xmlns="http://www.w3.org/2000/svg" width="900" height="{height}" viewBox="0 0 900 {height}" role="img" aria-labelledby="title desc">',
           '<title id="title">DX-Ball reconstruction progress</title>',
           f'<desc id="desc">{authored_exact} of {authored} authored game functions and {status["authored_exact_bytes"]:,} authored code bytes exact. Each brick represents one authored game function.</desc>',
           f'<rect width="900" height="{height}" rx="20" fill="#101722"/>',
           '<g font-family="sans-serif">',
           '<text x="32" y="46" fill="#eef4ff" font-size="25" font-weight="bold">DX-BALL  /  RECONSTRUCTION</text>',
           '<text x="32" y="75" fill="#9baec8" font-size="14">English v1.07 · REA / Ghidra · Visual C++ 4.0</text>',
           f'<text x="32" y="109" fill="#4ed8b7" font-size="18">{authored_exact} / {authored} authored game functions exact</text>',
           f'<text x="868" y="109" text-anchor="end" fill="#4ed8b7" font-size="22" font-weight="bold">{100 * fraction:g}%</text>',
           '<g id="authored-functions">']
    for i, function in enumerate(functions):
        color = '#4ed8b7' if function['address'] in exact else '#29384c'
        x, y = 32 + (i % columns) * 28, 132 + (i // columns) * 14
        name = escape(function['proposed_name'] or function['current_name'])
        address = escape(function['address'])
        state = 'exact' if function['address'] in exact else 'not yet exact'
        svg.append(f'<rect x="{x}" y="{y}" width="24" height="10" rx="2" fill="{color}"><title>{name} ({address}): {state}</title></rect>')
    svg += ['</g>',
            f'<text x="32" y="{grid_bottom + 28}" fill="#9baec8" font-size="13">One brick = one authored game function. Green = exact.</text>',
            f'<text x="32" y="{grid_bottom + 54}" fill="#eef4ff" font-size="14">{status["authored_exact_bytes"]:,} / {status["authored_code_bytes"]:,} code bytes exact · {status["authored_compiler_closures"]} compiler closures</text>',
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
             "Windows manual feedback is recorded separately from automated Wine checks.", "",
             "| Check | Date | Status | Observed result |", "| --- | --- | --- | --- |"]
    labels = {"passed": "Passed", "failed": "Failed", "reported": "User-reported"}
    for check in play["checks"]:
        lines.append(f"| {check['name']} | {check['date']} | {labels[check['status']]} | {check['result']} |")
    playability_report = Path(play['playability_report']).relative_to('docs').as_posix()
    lines += ["", "See [the build record](research/CURRENT_VC4_BUILD.md) and "
              f"[playability results]({playability_report}) for the tested image and evidence.",
              "", "## Still to verify", ""]
    lines += ["- " + item for item in play["remaining"]]
    lines += ["",
              "Generated by `scripts/repo-python scripts/progress.py` from the function ledgers "
              "and [verification record](../config/playability-status.json)."]
    (ROOT / "docs/PROGRESS.md").write_text("\n".join(lines) + "\n")
    print("generated resources/progress.svg and docs/PROGRESS.md")


if __name__ == "__main__":
    main()
