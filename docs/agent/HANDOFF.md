# Current reconstruction handoff

Continue toward nearly complete original game source and a rebuildable,
playable game. Prioritize whole game flows and exact restoration. Use one CPU,
one writable compiler/provider session and minimum affected existing checks.
Keep the README concise, with its title PNG and progress SVG.

## Current checkpoint

[WindowProc](../research/exact/EXACT_WINDOW_PROC.md) now follows the complete
input, focus/audio and teardown flow. Seven calls use their actual typed owners;
COM operations read live canonical pointers. Its original full span is 1,171
bytes: 1,136 saved instruction bytes, three five-byte jump gaps and 20 bytes
of internal switch data. Full REA byte evidence covers that entire span.

- VC4 emits 1,166 bytes, with 74 actual relocations and 1,006 differing
  positions. This whole unit remains candidate.
- Four affected accepted functions remain exact: sprite-bank initialization,
  instance claim/close and WinMain. Five complete comparisons / 112 relocations.
- Totals remain 283 source-present functions, 136 exact / 21,293 code bytes
  and 136 metadata bytes. Whole-source >=95% completion is unproven.
- Only the existing 2,138 WindowProc cases were replayed. Five typed native
  forwarders/default-owner rows connect existing callback slots. No new cases
  or other owner Oracle runs; other semantic receipts retain historical scope.
- Native, VC4 and MinGW builds pass. VC4 reuses 35 valid objects and compiles
  no remaining sources. Three exact-recipe invocations were required across
  comment-only native fallthrough annotation corrections; all executable
  statements and complete emissions are identical.
- REA snapshot stays at 487 records; this batch reuses saved evidence.

Current epoch: `.analysis/checkpoints/exact-window-proc-283-136/`; parent
`exact-win-main-283-136`. Full drivers/receipts:
`.analysis/exact-window-proc/`. Bounded independent audit:
`.analysis/window-proc-flow-review/`.

WinMain remains exact at 320 bytes. Complete fullscreen/compatible creation
flows remain candidates at 1,406/1,343 and 1,180/1,147. `refresh-score` remains
candidate after six changed operand bytes. Previous compiler inputs and
accepted objects are retained in their checkpoints.

## Next work

Restore the connected clock and key-routing family in `platform.c`:
`detect-clock` at `0x403550`, `dispatch-key` at `0x403820`, and `game-key`
at `0x410290`. Read-only proposals live under
`.analysis/window-key-next-review/`; inspect the final findings before editing.
The dispatcher has 137 owned bytes in a 162-byte span; game-key has 645
owned bytes in an 831-byte span. Reconcile all gaps and internal switch data
before declaring complete exact units.

Saved instructions show mode 4 pushes a key argument before calling splash
at `0x407AB0`, while the maintained splash entry and callback currently take
no argument. Recover the actual caller/callee ABI through shared typed source.
Replace authored callback dispatch and collapsed music loading with the
original direct calls and branches. Avoid local-layout, naming or compiler
profile trials. Continue into uncovered frame flows and runtime-origin
classification; provisional function counts are not the completion denominator.

## Evidence and tools

WindowProc dossier:
`ev_ec5246e677575ed67dc6c47dec0ffc7106e9ff2c86eaf9c4c562e39071b603cf`.
Complete byte read:
`ev_454b9b00147a98b6a0f82cf928c9a3af94a4d1f90f0311809c080c7e4d2664bc`.
The three gaps are E9 jumps to `0x40DEF5`; their original source syntax
remains inferred. Do not add unreachable breaks to force their emission.
Full byte read and before/after snapshots remain under
`.analysis/window-proc-byte-review/`.

REA checkout: `/home/pentester/Project/rea/`. New binary questions use
`scripts/rea`, pinned to REA 4.1.0 / Ghidra 12.1.4. Run Python through
`scripts/repo-python`, CMake with `--parallel 1`, and automated audio with
`PULSE_SINK=dxball_reconstruction_silent`.
