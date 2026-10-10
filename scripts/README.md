# Script map

Run Python entry points through `scripts/repo-python` from the repository root.

| Task | Entry point |
| --- | --- |
| Python environment | `bootstrap-python.sh` |
| Import original game files | `import-target.py` |
| Portable build and tracking | `ci.py --public` |
| MinGW Windows game | `build-windows.py` |
| Original-era compiler setup and build | `bootstrap-tools.py`, `build-legacy.py` |
| Prepare or launch a game build | `run-windows.py --profile windows-i686` or `--profile vc40` |
| REA setup and binary analysis | `bootstrap-rea.py`, `rea` |
| Compare selected complete functions | `replay-exact-units.py --unit UNIT` |
| Check source and acceptance ledgers | `validate-tracking.py` |
| Refresh public progress | `progress.py` |
| Preview disposable local products | `clean-local.py` |

See [build and play](../docs/BUILD.md), [REA in practice](../docs/REA.md), and
[matching](../docs/MATCHING.md) for commands in context. Choose an affected
existing Oracle or replay as needed during reconstruction.
