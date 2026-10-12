# Polygon scan and sort workspace

The later [triangle scanline scope](TRIANGLE_SCANLINE_SCOPE.md) reduces its
comparison to 88 differences. The polygon source and results below are unchanged.

Both polygon controllers now keep their edge queues, sort cursors, scanline
state and two distinct exchange pointers in one 64-byte i386 workspace.
The two endpoint points remain separate construction temporaries. All values
retain their original producer sites; the workspace is not zero-initialized.
Allocations, failure cleanup, endpoint rereads, clipping and span calls keep
their existing order.

| Complete body | Before differences | Current differences | Bytes |
| --- | ---: | ---: | ---: |
| Ordinary polygon | 218 | 211 | 1543 |
| Clipped polygon | 218 | 210 | 1592 |
| Triangle, unchanged source | 99 | 107 | 1710 |

Both polygon functions retain their original 80-byte frames and 458/468
instruction counts. They remain candidates. The three complete candidate
comparisons improve by seven raw byte positions in aggregate; the accepted
total stays **229 functions / 57,649 code bytes / 136 metadata bytes**.

A whole 80-byte record also grouped the endpoint points. It added five LEAs
for nested point copies in each controller, growing the bodies by ten bytes.
Keeping those actual construction values separate removes that extra code.
A queue-pointer pair and a Windows coordinate-kind model are also rejected.
The selected grouping follows the values' scan/sort and construction roles;
its original declaration spelling remains unknown.

Nine accepted raster bodies preserve 715 code bytes and 136 metadata bytes.
The triangle's complete 160-byte candidate metadata remains exact. All generated
labels are refreshed against actual COFF definitions and full metadata bindings.
All 229 current exact closures verify after the manifest update.

Each original/native and relocated VC4/native profile passes 1,152 unchanged
existing cases: 1,080 polygon cases and 72 triangle cases. Guarded pixels,
point storage, allocation order, scratch state and calls compare. Native and
MinGW builds pass; VC4 links the single fresh matching raster object with
36 verified unchanged objects. No game runs.

Original evidence remains
`ev_493013a754a8856f617731fcd1fddd0b00f6bd3d39f2de9d39f29742e542e205`
and `ev_4ae581c6e8ad135b183d562df04de63db4419e39e3f9b46891bdec2634ee5358`.
Complete receipts are in `.analysis/polygon-scan-workspace-20261012/`.
