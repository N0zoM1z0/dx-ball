# Sprite-bank API workspace

The loader at `0x00404610` now groups its existing surface description and API
result in a 112-byte workspace inside each sprite iteration. Its lifetime starts
with the surface request and ends after Unlock. File metadata, the color key,
allocation pointers and upload cursors keep their existing ownership.

The description is used by CreateSurface, GetSurfaceDesc and Lock, then supplies
the destination pixels during upload. The stored pitch still comes from
GetSurfaceDesc before Lock. The workspace therefore spans a complete surface
transfer, while temporary file pixels are released afterward.

The full matching body improves from **1655 bytes / 1577 differences** to
**1475 / 76**, matching the original length. All 77 actual relocation bindings
are resolved, including the complete file-mode literal. The function remains
nonexact. The API-only stage leaves 83 differences. Restoring the original
row-address producer order (row times pitch, then column, then descriptor
pixels) reduces that to 76. All 12 accepted resource functions preserve their 2197 exact bytes,
including the 145-byte glyph search that earlier whole-frame records disturbed.
The other 40 candidate code hashes are unchanged.

Both bodies contain 425 instructions and reserve 180 stack bytes. Description
and result match their original homes at EBP-180 and EBP-72. All 76 raw byte
differences occur in EBP displacement fields. Once each scalar is mapped by its
actual role, two multiplication pairs also have reversed operand order: width
and height, and row and pitch. Changing only those source operand spellings
emits identical code and is rejected. These are equivalent products, but the
function still lacks a complete byte match.

Ten unchanged maintained bank cases pass: seven supplied banks, a small sprite
stream, surface-creation failure and an empty stream. Three existing controlled
callback cases also pass, covering bank changes during color-key and descriptor
calls and a pitch change during Lock. These compare ordered calls and defined
bank, sprite and pixel state against the original.

Native and MinGW builds pass. VC4 matching uses `/ML`; the game uses its separate
`/MT` recipe from the same source. Their loader bodies are 1475 and 1486 bytes
respectively. The final production resource compilation links with 36 verified
unchanged objects. All 232 accepted exact functions verify, and 235 historical
input inventories refresh with their case scopes unchanged. The API-only and
row-order stages each use one matching and one production compilation. No game runs.

Original REA evidence is
`ev_b55c6def4c1b4af6c165acfb1623311bffa077753d93fab01531787dca6b6d70`,
operation 01 in `2026-10-10T17-22-54.305Z-requests-825249`.
Compiler inputs, complete comparisons and validation receipts are retained in
`.analysis/bank-api-phase-20261013/`.
The accepted total remains 232 functions / 59,486 code bytes / 136 metadata bytes,
with 41 authored functions still nonexact.

Independent source, frame and complete-candidate review passes. 25 completed
copies are retained in verified gzip carriers, releasing 4,395,008 allocated
bytes. Current build products and unique original evidence are preserved.
