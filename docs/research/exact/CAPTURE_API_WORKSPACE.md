# Capture API workspace

Capture at `0x004042B0` now groups its existing surface description and result
in a 112-byte API workspace. The rectangle, color key and allocation-pointer
block retain their previous ownership. No fields, values or operations are
added; source expressions keep their order after member qualification.

All five object homes now match the original 140-byte frame: rectangle
EBP-16, key EBP-24, allocation pointer EBP-28, result EBP-32 and description
EBP-140. The description is consumed through pitch transfer. Final Blt still
uses the live sprite and standalone capture rectangle.

The complete comparison improves from **873 bytes / 745 differences** to
**864 / 726**, against 852 original bytes. All 248 instructions and 42 actual
bindings are included. Twelve bank-selector reads use six-byte non-EAX loads
instead of original five-byte EAX loads. The original eighteen selector loads
total 96 bytes; current loads total 108. All other instructions total 756 bytes
in each body. Remaining register/address scheduling keeps capture nonexact.

This capture sequence is identical to the earlier rejected whole-workspace
emission. The smaller API workspace now integrates it while preserving
**all twelve resource exacts / 2,197 bytes**, including the 145-byte glyph
search. Four other resource candidates and all forty other candidate code
hashes remain unchanged. Original use of a record is inferred.

Twelve existing original/native capture cases and three existing callback
mutation cases pass. They compare defined owner/pixel state and ordered effects
across all banks, creation failure, descriptor retries and live-bank changes.
Native and MinGW builds pass. VC4 uses separate `/ML` matching and `/MT` game
recipes; capture code and bindings coincide. One production resource object
links with 36 verified unchanged objects. All 232 exact closures verify, and
235 historical input inventories refresh without changing case scopes.

Original REA evidence is
`ev_d7dd48a6f210a1a2cffea6be8318655763959610c9d94f8f8ff5621dad169b76`,
operation 00 of the closed `2026-10-10T17-22-54.305Z-requests-825249` run.
Full source/frame/input review, eight actual compiler inputs, comparisons and
build/case receipts are retained in `.analysis/capture-api-workspace-20261013/`.
Totals remain 232 exact functions / 59,486 code bytes / 136 metadata bytes.
Nineteen completed source/object/tracking copies are retained in verified gzip
carriers, releasing 4,321,280 allocated bytes. Current products are preserved.
