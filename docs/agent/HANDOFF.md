# Current reconstruction handoff

Continue toward nearly complete original game source and a rebuildable,
playable game. Recover coherent flows with REA; compile stable families and
run only affected exact comparisons and useful existing Oracles.

## Current checkpoint

The [shared file-service batch](../research/exact/EXACT_FILE_SERVICES.md) moves
the complete binary loader to `src/file.c/file.h`. Sound and MDS now use four
independently typed Kernel32 cells; three are shared by the MDS opener.
Windows binds each once. The former sound table retains its device and actual
allocator callbacks. Source owner/build integration follows the moved entry.

- 283 source-present functions; 134 exact functions / 20,887 code bytes.
- One compile per 24 affected recipes. Complete comparison covers 127 units
  and 1,312 actual relocations; 124 of 125 affected accepted units remain exact.
- `draw-effect-sprite` is now candidate: its unchanged body emits a different
  global/parameter indexing expression, 365 bytes against 361. The previous
  exact product is retained; do not disguise the current difference.
- File loading remains 307/304; a longer ReadFile count-output address accounts
  for three extra bytes. MDS opening remains 480/522. Preserve natural locals.
- Existing MIDI and sound Oracles pass 2,109/134 and 5,782/48 direct/connected
  checks. Only native cell bindings change; cases are unchanged. Native, VC4
  and MinGW builds succeed. VC4 reuses 25 objects and compiles eight others.

The [MDS records batch](../research/exact/EXACT_MDS_PARSER.md) preserves the
12-byte format, eight-byte block and 64-byte input MIDIHDR. Parser/converter
parameter cursors, partial event writes and bank cleanup follow the original.
Conversion remains 343/343 with 38 local-displacement differences; parse is
788/868. The [music controls](../research/exact/EXACT_MIDI_IMPORTS.md) retain
five exact C++ bodies. No spelling/layout/compiler-profile trials are useful.

## Next work

Follow remaining file-service consumers in Bitmap and Window code using the
saved dossiers. Establish actual cells and SDK bindings before replacing their
callback-table members. Keep the owner's existing Oracle selection bounded.
Inspect uncovered game entries and complete frame/lifecycle candidates when
choosing the next family; an exact-function count is not source completeness.

## Evidence and tools

Current epoch: `.analysis/checkpoints/exact-file-services-283-134/`, parent
`exact-mds-parser-283-135`. Full source inputs, previous/current objects,
comparisons and two reviews are retained there. Working drivers and receipts
are under `.analysis/exact-file-services/`.

Existing REA dossiers establish all nine file-service callsites and four
physical IAT cells. This batch opens no provider session and leaves the saved
snapshot at 483 records. The complete loader dossier is
`ev_a52bb0030eab7563b8a83f854ffdd76af7e5b0382cd75bda896a04c3efed70a0`;
the complete MDS opener span is
`ev_a7b7f4ce05473f020601101338f2392f0e732597eaed9078a2bd13128a77a584`.

REA checkout: `/home/pentester/Project/rea/`. Use project `scripts/rea`, pinned
to REA 4.1.0 / Ghidra 12.1.4; Python uses `scripts/repo-python`. One compiler
or provider session, one CPU, CMake `--parallel 1`, silent automated audio.
Keep README concise and put implementation evidence in the owner notes.
