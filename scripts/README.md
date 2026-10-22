# Script map

Run Python entry points through `scripts/repo-python` from the repository root.

| Task | Entry point |
| --- | --- |
| Python environment | `bootstrap-python.sh` |
| Import original game files | `import-target.py` |
| Portable build and tracking | `ci.py --public` |
| MinGW Windows game | `build-windows.py` |
| Current VC4 game | `bootstrap-tools.py`, `build-legacy.py --restored-crt` |
| Prepare or launch the current game | `run-windows.py --profile vc40-restored-crt` |
| REA setup and binary analysis | `bootstrap-rea.py`, `rea` |
| Compare selected complete functions | `replay-exact-units.py --unit UNIT` |
| Check source and acceptance ledgers | `validate-tracking.py` |
| Read current source and verification status | `report-reconstruction-status.py --json` |
| Refresh the progress page and graphic | `progress.py` |
| Preview disposable products and verified raw/gzip evidence deduplication | `clean-local.py` |

See [build and play](../docs/BUILD.md), [REA in practice](../docs/REA.md), and
[matching](../docs/MATCHING.md) for commands in context. Choose an affected
existing Oracle or replay when changing an affected source owner. Progress counts
come from the ledgers; play results come from `config/playability-status.json`.
The [current handoff](../docs/agent/HANDOFF.md) lists the retained evidence.
