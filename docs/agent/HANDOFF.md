# Current reconstruction handoff

Continue toward nearly complete original game source that rebuilds and plays.
Prioritize complete flows and exact restoration. Use one CPU, one writable
compiler/provider session and only affected existing checks. Keep the README
short, with its title PNG and progress SVG.

## Current checkpoint

The [mode lifecycle](../research/exact/MAIN_MODE_LIFECYCLE.md) now calls the
original owners directly. Redraw `0x4036B0` (127 bytes), initialization
`0x4038D0` (127) and cleanup `0x403950` (162) are exact on the first stable
compilation. Cleanup passes the full DWORD argument. All five modes connect
to their original initialize/redraw/dispose entries.

- 283 source-present functions; 143 exact / 23,090 code bytes and 136 metadata
  bytes. Whole-source >=95% completion remains unproven.
- One runtime recipe compiled once. Six affected prior exact units preserved;
  nine whole comparisons / 203 actual relocations. The dispatcher body and
  same-section label offsets are unchanged; its six local symbol IDs refreshed
  against the actual object.
- Twelve typed non-game lifecycle fixture forwards use actual live ModeOps
  slots and copied-image real defaults. The three mode1 bodies, shared game
  APIs and case bodies are unchanged.
- Only three existing mode/dispatch loops ran: 149 cases, once. Other owner
  and connected checks retain historical scope after input-hash refresh.
- Native, VC4 and MinGW builds pass. VC4 reuses 35 valid objects and compiles
  no remaining sources. One REA session read the three full spans, verified all
  416 bytes / 102 instructions / 15 calls and closed with snapshot495.

Full drivers/receipts: `.analysis/exact-main-mode/`; byte evidence:
`.analysis/main-mode-byte-review/`. Checkpoint:
`.analysis/checkpoints/exact-main-mode-283-143/`, parent `exact-main-frame-283-140`.
Bounded audit: `.analysis/main-mode-flow-review/final-review.json`.
Main dispatcher228, editor-frame908, clock83 and direct key dispatch162 stay
exact; game-key836/831 and WindowProc1166/1171 remain complete candidates.

## Next work

Follow the now-direct device/reset boundary: initialize_device_state at
`0x403A00` and synchronize_surface at `0x4035B0`, with surface recovery and
working-surface lifetime where needed to complete that path. Inspect current
startup/device source and reuse saved REA/caller evidence first. A bounded
proposal is under `.analysis/device-frame-next-review/`. Resolve any actual
missing byte/COM/ownership evidence before an exact claim; avoid compiler
profiles or source-expression, name and layout trials. Function counts are not
the whole-source completion denominator; complete flows and runtime-origin
classification still matter.

REA checkout: `/home/pentester/Project/rea/`. New binary questions use
`scripts/rea`, pinned to REA4.1.0/Ghidra12.1.4; retain full responses/Evidence IDs
and snapshots, then close the provider. Run Python through `scripts/repo-python`,
CMake with `--parallel 1`, and automated audio with
`PULSE_SINK=dxball_reconstruction_silent`. Preserve unique evidence before
cleaning duplicate products. Commit subjects begin `gpt-6.1-sol: `.
