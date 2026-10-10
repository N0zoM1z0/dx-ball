# Current reconstruction handoff

Continue toward nearly complete original game source that rebuilds and plays.
Prioritize complete flows and exact restoration. Use one CPU, one writable
compiler/provider session and only affected existing checks. Keep the README
short, with its title PNG and progress SVG.

## Current checkpoint

The [main frame dispatcher](../research/exact/MAIN_FRAME.md) at `0x403730` is
exact across its complete 228-byte span. It calls the original five frame
owners directly, preserves reset-clear order and copies the live return-mode
DWORD after cleanup. The ordinary switch emits both the original five-byte
jump gap and the complete five-DWORD table.

- 283 source-present functions; 140 exact / 22,674 code bytes and 136 metadata
  bytes. Whole-source >=95% completion remains unproven.
- One runtime recipe compiled once. Five affected prior exact units preserved;
  six whole comparisons / 167 actual relocations. First stable dispatch emission
  is exact at 228/228, without compiler-driven source alternatives.
- Seven typed native fixture boundaries follow the actual live ModeOps slots.
  Real defaults and the mode1 game-frame body belong to the copied library.
  Shared game APIs and case bodies are unchanged.
- Only the two existing dispatch loops ran: 128 cases. A private report-count
  error after all comparisons completed caused a second invocation; both logs
  are retained. Other entry/owner and connected checks keep historical scope.
- Native, VC4 and MinGW builds pass. VC4 reuses 35 valid objects and compiles
  no remaining sources. Saved REA snapshot492 reused; no new queries this batch.

Full drivers/receipts: `.analysis/exact-main-frame/`. Checkpoint:
`.analysis/checkpoints/exact-main-frame-283-140/`, parent `exact-editor-frame-283-139`.
Bounded audit: `.analysis/main-frame-flow-review/final-review.json`.
The editor frame stays exact at 908 bytes. Clock83 and direct key dispatch162
stay exact; game-key836/831 and WindowProc1166/1171 remain complete candidates.

## Next work

Continue the main mode lifecycle: initialization at `0x4038D0`, redraw at
`0x4036B0` and cleanup at `0x403950`. These runtime bodies still use authored
callback routing. Recover genuine owner calls and complete switch/argument
phases using existing evidence first. A bounded next-family review is under
`.analysis/main-mode-next-review/`; reconcile extents, gaps and internal tables
before a whole-unit claim. No compiler profiles or source-expression, name or
layout trials. Provisional function counts are not the whole-source completion
denominator; complete flows and runtime-origin classification still matter.

REA checkout: `/home/pentester/Project/rea/`. New binary questions use
`scripts/rea`, pinned to REA4.1.0/Ghidra12.1.4; retain full responses/Evidence IDs
and snapshots, then close the provider. Run Python through `scripts/repo-python`,
CMake with `--parallel 1`, and automated audio with
`PULSE_SINK=dxball_reconstruction_silent`. Preserve unique evidence before
cleaning duplicate products. Commit subjects begin `gpt-6.1-sol: `.
