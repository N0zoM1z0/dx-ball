# Current reconstruction handoff

Continue toward nearly complete original game source that rebuilds and plays.
Prioritize complete flows and exact restoration. Use one CPU, one writable
compiler/provider session and only affected existing checks. Keep the README
short, with its title PNG and progress SVG.

## Current checkpoint

[Editor-frame](../research/exact/EXACT_EDITOR_FRAME.md) at `0x40C3B0` is exact:
908 bytes, all 209 saved instructions and 16 original direct calls. The source
keeps separate cursor draw branches and both complete paint/erase coordinate
phases, including live post-call state reads. Two authored frame-only helpers
are removed. No shared-header, API, fixture or case changes.

- 283 source-present functions; 139 exact / 22,446 code bytes and 136 metadata
  bytes. Whole-source >=95% completion remains unproven.
- One editor recipe compiled once. Five affected prior exact units preserved;
  six whole comparisons / 78 actual relocations. First stable frame emission
  is exact at 908/908, without compiler-driven source alternatives.
- Only the three existing editor-frame loops ran, passing 1,272 cases once.
  Other entry/owner and connected checks retain historical scope.
- Native, VC4 and MinGW builds pass. VC4 reuses 35 valid objects and compiles
  no remaining sources. Saved REA snapshot491 reused; no new queries.

Full drivers/receipts: `.analysis/exact-editor-frame/`. Checkpoint:
`.analysis/checkpoints/exact-editor-frame-283-139/`, parent `exact-window-key-283-138`.
Independent bounded audit: `.analysis/editor-frame-flow-review/final-review.json`.
Clock83 and direct key dispatch162 stay exact. Game-key836/831 and
WindowProc1166/1171 remain complete candidates.

## Next work

Continue the main frame controller at `0x403730`: restore its original direct
owner calls, reset-clear order and post-frame mode transition. The saved
dossier owns 203 bytes in a 228-byte span; reconcile its five-byte gap and
20-byte switch table before an exact claim. The whole-source proposal and
23 full inputs are in `.analysis/main-frame-next-review/`; its 46 saved
instructions and ten direct calls are reviewed. One focused full read of
`0x403730/228` resolves the remaining byte coverage. Use saved evidence first. Avoid
compiler profiles, local-layout/name or source-expression trials. Provisional
function counts are not the whole-source completion denominator; complete
flows and remaining runtime-origin classification still matter.

REA checkout: `/home/pentester/Project/rea/`. New binary questions use
`scripts/rea`, pinned to REA4.1.0/Ghidra12.1.4; retain full responses/Evidence IDs
and snapshots, then close the provider. Run Python through `scripts/repo-python`,
CMake with `--parallel 1`, and automated audio with
`PULSE_SINK=dxball_reconstruction_silent`. Preserve unique evidence before
cleaning duplicate products. Commit subjects begin `gpt-6.1-sol: `.
