# Current reconstruction handoff

Continue toward nearly complete original game source that rebuilds and plays.
Prioritize complete flows and exact restoration; use one CPU and one writable
compiler/provider session. Run only affected existing checks. Keep the README
short, with the title PNG and progress SVG.

## Current checkpoint

[Clock and key routing](../research/exact/EXACT_WINDOW_KEYS.md) restores the
connected controllers at `0x403550`, `0x403820` and `0x410290`. Clock and the
five direct key-owner dispatcher are exact at 83 and 162 bytes. The shared
splash(char) caller/callee API preserves its existing 36-byte exact body.
Game input now has both pause paths, original bonus/paddle writes and six
direct music loads; VC4 emits 836/831 bytes with 522 differing positions.
WindowProc remains a complete 1,166/1,171-byte candidate.

- 283 source-present functions; 138 exact / 21,538 code bytes and 136 metadata
  bytes. Whole-source >=95% completion remains unproven.
- 25 affected recipes compiled once each. All 122 affected accepted functions
  preserved; 126 full comparisons / 1,418 actual relocations. Anonymous symbols
  refreshed only after literal contents or local-label identity were proved.
- Existing clock10/dispatch1792/game-key420 checks pass; no new cases or other
  owner runs. Two invocations include a corrected private post-run counter
  assertion. Four typed fixture forwarders use current real owner slots.
- Native, VC4 and MinGW builds pass. VC4 reuses 26 valid objects and compiles
  nine remaining sources. Stable sources were not recompiled for comparison.
- REA snapshot491 and saved full evidence reused; no new provider queries.

Full drivers and receipts: `.analysis/exact-window-key/`. Checkpoint:
`.analysis/checkpoints/exact-window-key-283-138/`, parent `exact-window-proc-283-136`.
Independent bounded audit: `.analysis/window-key-flow-review/final-review.json`.

## Next work

Next restore editor-frame at `0x40C3B0` from the complete 908-byte saved
dossier (`ev_12f27f7831f215d80c2a1a27d88e1638ffa9ab2fd568793f66258b328927431e`).
The whole-body proposal and 21 full inputs are in
`.analysis/editor-frame-next-review/`: 209 instructions and 16 direct calls,
with separate cursor draws and both inline paint/erase value phases. Existing
helper factoring preserves most logical effects; recover the original call and
value timing. No gaps, tables, new ABI or provider query are needed. Do not iterate compiler profiles,
local layouts or source-expression variants to force the game-key candidate.
The provisional 528 functions are not a whole-source completion denominator;
remaining runtime-origin classification and complete game flows still matter.

REA checkout: `/home/pentester/Project/rea/`. New binary questions use
`scripts/rea` pinned to REA4.1.0/Ghidra12.1.4. Retain full responses, Evidence IDs
and snapshots, then close the provider. Run Python through `scripts/repo-python`,
CMake with `--parallel 1`, and automated audio with
`PULSE_SINK=dxball_reconstruction_silent`. Preserve unique evidence before
cleaning duplicate build products. Commit subjects begin `gpt-6.1-sol: `.
