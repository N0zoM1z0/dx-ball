# Brick-drop movement and redraw state

`dxball_drop_bricks` at `0x415670` now restores every original local home in
its 44-byte frame. A movement cursor holds the current column, movement flag,
two signed-byte pointers and row. The redraw branch owns its standalone
rectangle and two loop indices. The rectangle remains standalone for the
original four-field by-value invalidation call.

| Role | Original and current EBP displacement |
| --- | --- |
| Movement column | -4 |
| Movement flag | -8 |
| Current tile pointer | -12 |
| Next-row pointer | -16 |
| Movement row | -20 |
| Redraw rectangle left/top/right/bottom | -36/-32/-28/-24 |
| Redraw column/row | -40/-44 |

The complete candidate is 436/426 bytes with 306 strict differences, previously 317.
A proof against saved REA assembly accounts for all 120 original instructions:
operations, registers and all source homes agree after translating branch
positions and grouping two address calculations. Each calculation adds the
real BoardStorage base `0x43AAB8` and tiles offset `0x4E40`; the original adds
their sum `0x43F8F8` in one instruction. These two additional five-byte ADDs
remain in the full byte comparison. The function remains nonexact.

An explicit base-pointer expression generates 442 bytes and 313 differences,
and is rejected. The selected indexed-address form retains the actual shared
20,432-byte storage owner, including its terminal board transport. No source
or linkage alias is added.

Original evidence is
`ev_8602dd7fec1b8aff85a2c581b96d7a85bcf62a791d3741ecaecd0c5a411812fc`,
in `.analysis/rea/runs/2026-10-07T08-21-37.400Z-interactive-2545594/02-analyze_function.json`.
The proof parses these original instructions and decodes only reconstructed
COFF. Its complete raw result and separate source correspondence are retained
in `.analysis/brick-drop-cursor-20261012/`.

Nine accepted core bodies retain 4,659 exact bytes. Fifty shipped-board cases
and six filled/empty/special-board cases compare full board/aux storage, queues,
state and ordered sound/DirectDraw/redraw calls against the original. Linux and
MinGW products build; VC4 links the changed core object and 36 verified unchanged
objects. All 225 accepted exact closures pass. Totals remain 55,998 code bytes
and 136 metadata bytes, with 48 authored nonexact functions. No game runs.

## Closed companion models

Scoping glyph drawing's destination rectangle to its found-glyph branch leaves
332/328 bytes and 258 differences, with all accepted resource companions preserved.
Four typed left/right span records leave the triangle's 1710-byte code and 99
differences unchanged; its complete 160-byte candidate metadata stays identical.
Only generated COFF symbol identities differ, and their bindings are attested.
Two actual height-projection values as a record leave 193/191 bytes and 158
differences, with four accepted rotation companions preserved. All three models
are reverted by source/object hashes and receive no extra Oracle or game run.

The triangle replacement initially qualified a record field declaration and
failed compilation. That source is retained separately; one corrected complete
compile supplies the comparison. Private receipts are in
`.analysis/glyph-rectangle-scope-20261012/`,
`.analysis/triangle-span-records-20261012/` and
`.analysis/height-projection-record-20261012/`. Do not repeat these scope/record
models without new evidence.
