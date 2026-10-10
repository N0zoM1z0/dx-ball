# Current reconstruction handoff

Continue toward nearly complete original game source that rebuilds and plays.
Prioritize complete flows and exact restoration. Use one CPU, one writable
compiler/provider session and only affected existing checks. Keep the README
short, with its title PNG and progress SVG.

## Current checkpoint

The [device-frame restoration](../research/exact/DEVICE_FRAME.md) connects the
exact dispatcher to original device/reset behavior. Surface synchronization
`0x4035B0` (134 bytes), recovery `0x403640` (97) and background cleanup
`0x403BD0` (80) are exact on their first stable compilation. Initialization
`0x403A00` now restores all original calls and descriptor stores; its complete
359/359-byte candidate has ten remaining differences: nine descriptor/index
stack displacements and one failure-branch epilogue target.

- 283 source-present functions; 146 exact / 23,401 code bytes and 136 metadata
  bytes. Whole-source >=95% completion remains unproven.
- The genuine background owner is now a COM pointer. Seven explicit casts
  bridge existing integer-handle APIs. All 27 affected recipes compiled once;
  all 135 affected prior exact units survived. The full batch compares 141
  units with 1,642 actual relocations, including the four new complete units
  and two current platform candidates.
- One typed native board-loader forward uses the existing actual callback
  slot and copied-image real default. Startup's termination callback binds
  the existing process-exit backend. Case bodies remain unchanged.
- Only the affected existing loops ran: 392 direct cases and 21 connected
  checks, each selected owner once. Other owner rows retain historical scope
  after input-hash refresh.
- Native, VC4 and MinGW builds pass. VC4 reuses 26 valid objects and compiles
  nine remaining game sources. Saved REA dossiers cover all 670 bytes,
  170 instructions, 15 direct calls and six COM sites; snapshot495 unchanged.
  No provider session or new binary query was needed.

Full drivers/receipts: `.analysis/exact-device-frame/`; saved proposal:
`.analysis/device-frame-next-review/`. Checkpoint:
`.analysis/checkpoints/exact-device-frame-283-146/`, parent `exact-main-mode-283-143`.
Bounded independent audit: `.analysis/device-frame-flow-review/`.
Main frame228, mode controllers416, editor-frame908, clock83 and key dispatch162
remain exact. Game-key836/831 and WindowProc1166/1171 remain complete candidates.

## Next work

Follow the palette and sprite dependencies called by the restored device path.
Preserve the already exact initialize_palette206 body. Investigate clear_surface
`0x409F10` (89) and restore_sprite_banks `0x403D30` (282) from their saved complete
REA dossiers; a bounded proposal is under `.analysis/device-dependencies-next-review/`.
Clear-surface still adds a memset and caches its COM destination. Sprite
recovery still caches a sprite and reloads via authored RuntimeOps instead of
the original direct load_sprite_bank API. The observed unconsumed Restore
result store is unresolved source-local versus compiler-spill evidence; avoid
adding a fake local. Do not run declaration/name/layout or compiler-profile
trials to force initialization's ten residual bytes.

REA checkout: `/home/pentester/Project/rea/`. New binary questions use
`scripts/rea`, pinned to REA4.1.0/Ghidra12.1.4; retain full responses/Evidence IDs
and snapshots, then close the provider. Run Python through `scripts/repo-python`,
CMake with `--parallel 1`, and automated audio with
`PULSE_SINK=dxball_reconstruction_silent`. Preserve unique evidence before
cleaning duplicate products. Commit subjects begin `gpt-6.1-sol: `.
