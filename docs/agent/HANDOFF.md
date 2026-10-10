# Current reconstruction handoff

Continue toward nearly complete original game source and a rebuildable,
playable game. Recover coherent flows with REA, compile each stable family
once, and run only useful affected exact comparisons and existing Oracles.

## Current checkpoint

The [Window instance batch](../research/exact/EXACT_WINDOW_INSTANCE.md) restores
the complete semaphore claim and close routines. Their first stable VC4
compilation matches all 109 and 51 bytes. OpenSemaphoreA and CreateSemaphoreA
have genuine independent cells; closing uses the shared File CloseHandle cell.
The two original name arrays retain separate storage. Windows binds the cells
once, and the existing Platform fixture binds the same typed boundaries.

- 283 source-present functions; 136 exact functions / 21,047 code bytes.
- One compile per 25 affected recipes; 122 complete comparisons and 1,242
  actual relocations. All 120 affected accepted functions remain exact.
- Existing Platform Oracle: 4,742 cases pass. No new cases or other owner
  Oracle runs. WindowApi has 24 slots; Sound still uses message-box slot 9.
- Native, VC4 and MinGW builds pass. VC4 reuses 26 objects and compiles eight,
  linking 34 source objects.
- Two focused REA reads fill the claim's five-byte body gap and recover both
  name arrays. The saved snapshot advances from 483 to 485 records.

The [Bitmap batch](../research/exact/EXACT_BITMAP_LOADER.md) supplies typed
40-byte information and four-byte color records, genuine File3 cells and
shared LocalAlloc/LocalFree ownership. Bitmap remains candidate at 928/976
bytes; MDS opening remains 480/522. The [File loader](../research/exact/EXACT_FILE_SERVICES.md)
remains 307/304, and `draw-effect-sprite` remains candidate at 365/361.
Their prior products and scoped behavior evidence remain retained.

## Next work

Restore complete fullscreen initialization at `0x40CF70` (1,343 bytes)
and compatible initialization at `0x40D4B0` (1,147 bytes). Both saved dossiers
are contiguous through their returns. Recover the original inline window,
DirectDraw and audio flow, HRESULT locals, failure paths and live global reads.
Replace authored factoring where it changes those original bodies.

CreateSurface/GetAttachedSurface publish directly through the actual surface
globals. Resolve their shared pointer-storage types before replacing cached
temporary outputs. Ten Windows/GDI calls use genuine independent imports;
DirectDrawCreate is a direct call to the SDK import thunk at `0x416600`.
Keep that backend boundary distinct from the Window callback table.

Continue into uncovered game entries and complete frame flows. The bounded
low-address inventory identifies 42 annotated compiler/static-init fragments
and one DirectDrawCreate thunk among 43 unclassified entries. Whole-source
origin classification and the denominator for 95% completion remain open.

## Evidence and tools

Current epoch: `.analysis/checkpoints/exact-window-instance-283-136/`, parent
`exact-bitmap-loader-283-134`. Working receipts are under
`.analysis/exact-window-instance/`; bounded reviews are under
`.analysis/window-lifecycle-review/` and `.analysis/window-import-review/`.
Next-family analysis is under `.analysis/window-init-next-review/`.

Claim/close primary dossiers:
`ev_62be40ba52c99f99d98901a5d736ae5250673c0cd2a257527bb0748dce67c357`,
`ev_1c8812cfc0cee3f5a725c911a8611a98678bac2db8eb4363445fadfda4b10263`.
Complete claim and name reads:
`ev_7dbfc11820be1873717327d586d542dff0bd036a754698d9db2132f6280f3867`,
`ev_0a43fa7b195da89748b440011a7a22c726bffb69573e8574010b4cff63bf3769`.

REA checkout: `/home/pentester/Project/rea/`. Use `scripts/rea`, pinned to
REA 4.1.0 / Ghidra 12.1.4; Python uses `scripts/repo-python`. One compiler or
provider session, one CPU, CMake `--parallel 1`, silent automated audio.
Keep README concise, with its title PNG and current progress SVG.
