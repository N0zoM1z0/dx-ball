# Reconstruction records

| Record | Purpose |
| --- | --- |
| `target.toml` | Original executable identity |
| `functions.csv` | Original addresses, extents and recovered names |
| `implemented.csv` | Functions with maintained source |
| `match-units.toml`, `matches.csv` | Complete compiler comparisons and accepted exact units |
| `source-owners.toml`, `semantic-acceptance.csv` | Scoped original-execution comparisons and their inputs |
| `function-origins.csv` | Game, runtime and compiler-generated origins |
| `assets.csv`, `windows-resources.json` | Original resource inventory and Windows embedding |
| `tools.lock.toml`, `rea.lock.json` | Pinned compiler and analysis tools |
| `rea-*.json` | Focused analysis requests |

Read [matching](../docs/MATCHING.md) for the compiler comparison and
[the research notes](../docs/research/README.md) for the evidence behind these records.
