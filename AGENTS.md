# Working on DX-Ball

Reconstruct English DX-Ball v1.07 as readable, rebuildable C/C++. Authored exact
recovery is complete: 270 functions and 84,968 code bytes. The current VC4 game
passes the checks in [progress](docs/PROGRESS.md); focus recovery and further
live-game coverage are the next work. Keep the 19 approved original CRT members
explicit in the restored-CRT delivery. Platform ports follow game validation.

Read [the handoff](docs/agent/HANDOFF.md), [workflow](docs/agent/WORKFLOW.md) and the
relevant research note before changing source. `config/functions.csv` maps
original addresses to owners; `config/function-origins.csv` identifies authored,
runtime and compiler-generated entries.

## Source and verification

- Use typed source shared by portable and legacy builds. Preserve ABI, integer
  widths, ownership, call order and state writes. Keep copied machine code,
  assembly replacements, padding and fake locals out of exact reconstruction.
- Follow the [source-candidate policy](docs/agent/SOURCE_CANDIDATE_SEARCH.md).
  The user authorized bounded natural-source and build-context hypotheses on
  October 21, 2026. Use the supplied EXE/resources to recover missing context;
  original project files, PDBs and uniquely known names are not prerequisites.
- Freeze each distinct candidate, compile it once and compare the complete
  affected closure, including accepted functions sharing its inputs. Reuse
  unchanged compiler results and existing receipts.
- Select checks for the changed behavior. Status and documentation work use
  retained evidence; source work runs the relevant complete comparisons and
  focused behavior checks. Keep the full historical queue out of routine runs.
- Use `scripts/repo-python` for Python. Use `scripts/rea` and the installed REA
  skill for new binary analysis. The lock pins REA 6.5.0/Ghidra 12.1.4; retain
  full responses and Evidence IDs under `.analysis/rea/`.

## Execution and cleanup

Run one compiler/provider/Wine job at a time on one allowed CPU, with
`CPUQuota=35%`, `MemoryHigh=384M` and `MemoryMax=512M` in a user systemd scope.
Use CMake `--parallel 1`, the REA wrapper's 256 MiB Ghidra heap and
`PULSE_SINK=dxball_reconstruction_silent` for automated audio. See
[REA operations](docs/agent/REA.md).

Keep originals in `original/`, tools in `.tools/`, products in `build/`, evidence
in `.analysis/` and databases in `ghidra-project/`. These directories are private.
Archive useful closed evidence and verify member size/SHA/mode before retiring
obsolete copies. Retain the current tested game, delivery bundle, accepted
objects and useful incremental caches.

## Documentation and publication

Write English documentation with direct descriptions of the current result and
remaining work. Keep the README focused on progress, reconstruction and REA;
retain its centered title PNG and progress SVG at 900px. Put run details in the
research records and operating instructions in `docs/agent/`.

Update affected ledgers when claims change. `config/playability-status.json`
records the tested image and live-check outcomes; `scripts/progress.py` generates
the progress page and graphic. Keep historical observations attached to their
recorded images and dates.

Commit and push verified checkpoints to `origin/main`. Use English subjects
beginning `gpt-6.1-sol: `. Publish source, useful notes and ledgers; keep original
assets, tools and raw evidence untracked.
