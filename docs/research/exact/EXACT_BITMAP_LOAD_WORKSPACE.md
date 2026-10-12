# Exact Bitmap loading workspace

`dxball_load_bitmap` at `0x00409F70` now matches its complete 976-byte original
body, all 237 instructions and eighteen actual relocations. One typed loading
workspace holds the existing file and palette owners, surface descriptor,
pixel/row cursors, counts, fallback path and input/output records. Every field
participates in a read, copy, conversion, API output or cleanup operation.

The 2,508-byte VC4 frame agrees with the original. The file and palette outputs
occupy EBP-2508/-2504; the 108-byte descriptor starts at EBP-2500. Pixels,
result, copy count and destination use EBP-2392/-2388/-2384/-2380. The unchanged
260-byte path starts at EBP-2376, index at EBP-2116, fourteen-byte header at
EBP-2112 and forty-byte information record at EBP-2096. Output palette, source,
transferred count and input colors start at EBP-2056/-1032/-1028/-1024.
The header-to-information-record alignment follows the existing field types.

The earlier body had 928 bytes and 614 differences. Grouping these actual
values restores the long local-address encodings and original arithmetic
lowering with zero whole-body differences. Sequential reads remain
14/40/1024/width×height bytes. Row copying still retreats the source by the copy
count; pixel and file cleanup precede palette creation. Short-read suffixes and
palette flags remain unwritten where the original leaves them unwritten.
The fallback prefix's four bytes retain their separate original address and
complete content attestation. No statement or API order changes, and original
declaration spelling remains unknown.

One canonical Bitmap compilation supplies the accepted object. Linux and
MinGW builds pass; VC4 relinks with 36 verified unchanged objects. The existing
975 original/native cases compare complete guarded destinations, allocation
bytes, short-read buffers, all palette bytes and ordered effects. The existing
stack-seeding helper is reused after its source, compiler, flags and product
identities verify; no helper compilation is needed.

All 221 accepted units and compiler-input closures verify. Current totals are
55,163 code bytes and 136 separate metadata bytes, with 52 authored functions
remaining nonexact. No game campaign runs.

Original evidence is
`ev_e408e41080570698d5068c6aa811cbae0a93e65442822fc191ea85ea46c93cad`,
operation 07 of run `2026-10-07T10-33-32.118Z-interactive-2912559`.
The complete contiguous dossier is reused without another REA query.
Compiler inputs, complete comparison, full case payloads and verified compressed
before/staging products remain in `.analysis/bitmap-load-workspace-20261012/`.
