# Current reconstruction handoff

Continue toward nearly complete original game source and a rebuildable,
playable game. Recover coherent flows with REA; compile stable families and
run only affected exact comparisons and useful existing Oracles.

## Current checkpoint

The [Bitmap batch](../research/exact/EXACT_BITMAP_LOADER.md) restores direct
40-byte information-header fields, four-byte input colors, recomputed pixel
counts, consumed HRESULTs and the shared row/palette counter. Bitmap now uses
the genuine File3 imports and shares LocalAlloc/LocalFree with MDS through
`src/memory.c/memory.h`. Windows binds each once; the native Bitmap fixture
saves and restores all five actual cells. Existing cases remain unchanged.

- 283 source-present functions; 134 exact functions / 20,887 code bytes.
- One compile per 21 affected recipes; 101 complete comparisons and 1,078
  actual relocations. All 99 affected accepted functions remain exact.
- Bitmap is candidate at 928/976 bytes, 614 differing byte positions.
  MDS opening remains 480/522. No local-layout, name or compiler-profile trials.
- Existing Bitmap 975 and MIDI 2,109 direct / 134 connected checks pass.
  Native, VC4 and MinGW builds pass. VC4 reuses 26 objects and compiles eight;
  the game now links 34 source objects including the shared memory owner.
- Bitmap retains its separate prefix at `0x422798`, memcpy `0x417CA0`,
  Boolean-only short reads, unwritten palette flags, failure leaks and row
  retreat by copy length. Active gameplay use remains unestablished.

The [File batch](../research/exact/EXACT_FILE_SERVICES.md) supplies the four
shared file cells. Its loader remains 307/304. `draw-effect-sprite` remains
candidate at 365/361 after shared declarations changed its indexing emission;
the prior exact object is retained. MDS parser/converter source follows the
[physical record recovery](../research/exact/EXACT_MDS_PARSER.md); no exact
claim replaces their remaining compiler differences.

## Next work

The complete saved `close_instance` dossier at `0x40DF80..0x40DFB2` establishes
one further shared CloseHandle consumer. Migrate that real call and remove its
Window table member, updating the actual 27-to-26 fixture layout and version
slot shift. Keep the affected existing Oracle selection bounded.

Continue into complete frame/lifecycle candidates and uncovered game entries.
The saved bounded inventory finds 43 unclassified entries below `0x416606`,
42 already annotated compiler/static-init fragments and one DirectDrawCreate
thunk. Resolve their origin from evidence; that inventory alone does not prove
the whole source denominator or 95% completion.

## Evidence and tools

Current epoch: `.analysis/checkpoints/exact-bitmap-loader-283-134/`, parent
`exact-file-services-283-134`. Full source inputs, prior/current objects,
comparisons and two bounded reviews are retained there. Working drivers and
receipts are under `.analysis/exact-bitmap-loader/`.

Bitmap's complete dossier is
`ev_e408e41080570698d5068c6aa811cbae0a93e65442822fc191ea85ea46c93cad`;
the Window closer is
`ev_1c8812cfc0cee3f5a725c911a8611a98678bac2db8eb4363445fadfda4b10263`.
This batch opens no provider session; the snapshot stays at 483 records.

REA checkout: `/home/pentester/Project/rea/`. Use project `scripts/rea`, pinned
to REA 4.1.0 / Ghidra 12.1.4; Python uses `scripts/repo-python`. One compiler
or provider session, one CPU, CMake `--parallel 1`, silent automated audio.
Keep README concise and implementation evidence in the owner notes.
