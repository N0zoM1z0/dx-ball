# Current reconstruction handoff

Continue toward nearly complete original game source that rebuilds and plays.
Prioritize complete flows and exact restoration. Use one CPU, one writable
compiler/provider session and only affected existing checks. Keep the README
short, with its title PNG and progress SVG.

## Current checkpoint

The [device dependencies](../research/exact/DEVICE_DEPENDENCIES.md) now follow the
restored initialization/recovery path into its original surface-fill and bank
reload calls. Fill `0x409F10` is exact across all 89 bytes on the first stable
compilation. Bank recovery `0x403D30` rereads live sprite/surface owners and calls
`load_sprite_bank` directly; its whole 279/282-byte candidate has 80 counted
byte differences. Original unused Restore-result storage remains unresolved;
no inert local was added to force it.

- 283 source-present functions; 147 exact / 23,490 code bytes and 136 metadata
  bytes. Whole-source >=95% completion remains unproven.
- Only the device recipe compiled, once. All three prior exact device bodies
  and their relocations are unchanged: palette206, synchronization134 and
  recovery97. Five full comparisons account for 35 actual relocations.
- No header, fixture or case-body changes. Existing typed RuntimeOps slot5
  forwarding covers the restored direct bank-loader call.
- Four existing device loops ran once: 145 direct cases and eight connected
  lost-surface presentations. Other owner rows retain historical scope after
  input-hash refresh. The selector initially stopped before fixture creation
  because the fill loop uses its full symbol name; both driver versions remain.
- Native4, MinGW5 build steps pass. VC4 reuses35 valid game objects and compiles
  no remaining sources. Saved REA dossiers cover577 contiguous bytes and170
  instructions, including the unchanged palette. Snapshot495 remains unchanged;
  no provider session or new query was needed.

Full drivers/receipts: `.analysis/exact-device-dependencies/`; proposal:
`.analysis/device-dependencies-next-review/`. Checkpoint:
`.analysis/checkpoints/exact-device-dependencies-283-147/`, parent `exact-device-frame-283-146`.
Independent audit: `.analysis/device-dependencies-flow-review/final-review.json`.
Main frame228, mode controllers416, editor-frame908, clock83, key dispatch162
and background cleanup80 remain exact. Device initialization359/359diff10,
game-key836/831diff522 and WindowProc1166/1171diff1006 remain complete candidates.

## Next work

Follow initialization into `initialize_scores` at `0x406EE0` (723 bytes).
Its saved complete REA dossier shows fifteen explicit name-clear/strcat/score
phases and original direct CRT file calls; current source factors the names
through a strcpy loop and callback operations. A bounded inventory/proposal is
under `.analysis/remaining-game-source-next-review/`. Establish full string
identity and authentic CRT/fixture boundaries before one stable compilation.
Avoid global libc interposition and guessed helper relocation targets.

The source-origin inventory is useful triage, not a completion denominator.
It identifies maintained source for270 confirmed authored entries; the remaining
origin-unknown entries still need evidence rather than an automatic CRT label.
Function totals alone do not establish95% original readable source restoration.
Do not run declaration/name/layout or compiler-profile trials for existing
candidates; proceed through substantive complete game flows.

REA checkout: `/home/pentester/Project/rea/`. New binary questions use
`scripts/rea`, pinned to REA4.1.0/Ghidra12.1.4; retain full responses/Evidence IDs
and snapshots, then close the provider. Run Python through `scripts/repo-python`,
CMake with `--parallel 1`, and automated audio with
`PULSE_SINK=dxball_reconstruction_silent`. Preserve unique evidence before
cleaning duplicate products. Commit subjects begin `gpt-6.1-sol: `.
