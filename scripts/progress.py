#!/usr/bin/env python3
"""Generate public progress from ledgers, without copying original game assets."""
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
           f'<desc id="desc">{status["source_present"]} source-present functions, {status["exact_functions"]} exact functions, out of {len(functions)} provisional candidates.</desc>',
           '<rect width="900" height="460" rx="20" fill="#101722"/>',
           '<g font-family="sans-serif">',
           '<text x="34" y="46" fill="#eef4ff" font-size="25" font-weight="bold">DX-BALL  /  RECONSTRUCTION</text>',
           '<text x="34" y="75" fill="#9baec8" font-size="14">REA showcase · English v1.07 · Windows 95 · Ghidra + VC4.0</text>',
           f'<text x="34" y="109" fill="#4ed8b7" font-size="16">{status["exact_functions"]} exact functions · {status["exact_bytes"]} bytes</text>',
           f'<text x="470" y="109" fill="#f5bd57" font-size="16">{status["source_present"]} source-present · {status["semantic_validated_with_scope"]} scoped semantic</text>']
    for i, function in enumerate(functions):
        color = "#4ed8b7" if function["address"] in exact else "#f5bd57" if function["address"] in source else "#29384c"
        x, y = 34 + (i % 33) * 25, 132 + (i // 33) * 14
        svg.append(f'<rect x="{x}" y="{y}" width="22" height="10" rx="2" fill="{color}"/>')
    svg += ['<text x="34" y="388" fill="#9baec8" font-size="13">Green: exact compiler match · Amber: reconstructed source · Dark: remaining candidates</text>',
            '<text x="34" y="412" fill="#9baec8" font-size="13">Goal: recover the game source, rebuild it, and play.</text>',
            '</g></svg>']
    (ROOT / "resources").mkdir(exist_ok=True)
    (ROOT / "resources/progress.svg").write_text("\n".join(svg) + "\n")
    (ROOT / "docs/PROGRESS.md").write_text(
        "# Reconstruction progress\n\nRecover the original game source into a rebuildable, playable game.\n"
        "The current records cover gameplay, all five screen modes, resources, graphics and audio.\n\n"
        "| Fact | Count |\n| --- | ---: |\n"
        f"| Provisional Ghidra candidates | {status['function_candidates']} |\n"
        f"| Source-present functions | {status['source_present']} |\n"
        f"| Functions with scoped semantic acceptance | {status['semantic_validated_with_scope']} |\n"
        f"| Byte-exact functions | {status['exact_functions']} |\n"
        f"| Complete exact code bytes | {status['exact_bytes']} |\n"
        f"| Entries identified as runtime dependencies | {status['runtime_identified']} |\n"
        f"| Entries identified as compiler-generated code | {status['compiler_generated_identified']} |\n"
        f"| Origin still unclassified | {status['origin_unknown']} |\n\n"
        "The inventory includes game routines, runtime dependencies and compiler-generated code.\n"
        "Both Windows builds have completed recorded original-board campaigns under Wine.\n"
        "Continue with the remaining rendering and runtime routines.\n\n"
        "See [the architecture](ARCHITECTURE.md), [compiler matching](MATCHING.md),\n"
        "and [recorded play runs](research/ORIGINAL_CAMPAIGN.md).\n\n"
        "Generated from the ledgers by `scripts/repo-python scripts/progress.py`.\n")
    print("generated resources/progress.svg and docs/PROGRESS.md")


if __name__ == "__main__":
    main()
