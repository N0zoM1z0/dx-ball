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

## C-compatible polygon owner control, October 17

One later private pilot tests the two POD polygon controllers as a separate C
owner, keeping the previously tested full80-byte workspace and every aggregate
copy. The actual C-compatible public declarations, explicit stdcall convention,
allocator/span APIs and absence of class lifetimes support this bounded source
family hypothesis. Triangle and its FixedPoint lifetime machinery stay in C++.
Neither the original language nor translation-unit boundary is established.

| Complete controller | Maintained bytes / differences | C full80 pilot |
| --- | ---: | ---: |
| Ordinary polygon | 1543 / 214 | 1553 / 1274 |
| Clipped polygon | 1592 / 214 | 1602 / 1314 |

Both complete relocation-resolved pilot digests equal the earlier rejected
full80 C++ results. Selecting the C frontend does not remove the nested-copy
address producers in this model. Each controller has four point-copy statements;
the emitted copies add five LEAs and ten bytes. Original copies read X and Y
before either destination store. For example, the first ordinary copy reads at
`0x40B626` and `0x40B628`, then stores directly to its two EBP homes at
`0x40B62B` and `0x40B62E`. The nested workspace instead forms the destination
address between the paired reads and stores. The local-to-local copy also forms
its source address. The retained proof accounts for all eight copy sites.

A separate proposal to expand the copies into x/y assignments is declined
before compilation: it would interleave stores with reads and repeat indexed
expressions, including the modulo producer. Ordinary stable, nonalias values
would not establish the original producer order. No temporary pointer, padding,
alternate body or flag sweep is introduced to repair that lowering.

The C-owner pilot is rejected without integration. One serial, resource-capped
compile supplies two complete comparisons; there is no companion compile,
fixture, game, provider query or full replay. Current source, cached objects,
delivery and totals remain unchanged:391 exacts and24 authored candidates.
This closes the tested full80/C model, not all possible source declarations or
all frontend behavior. Private `.analysis/polygon-c-owner-20261017/` retains the
inputs, complete comparisons, independent reviews and copy-producer proof.
Verified archival replaces seven disposable input/object files, releasing48 KiB
of allocated storage after archive cost, excluding small JSON receipts.

## Current workspace in an independent C owner, October 17

A distinct follow-up keeps the maintained 64-byte workspace and separate
`first`/`second` points. The older C control above used full80 and therefore
did not test this source model. The two controllers consume POD, C allocator/span
APIs and explicit stdcall entries, with no class lifetimes. This supports one
inferred C owner; it does not establish the original language or owner boundary.

One serial, resource-capped compile compares both complete controllers:
ordinary remains 1,543 bytes with 212 differences, versus 214 before; clipped
remains 1,592 bytes with 214 differences and an identical resolved digest.
The entire function bodies and every workspace member remain unchanged. C needs
only a same-name typedef for the existing struct. Both actual `RET20` entries
and their eleven relocation bindings each retain all symbols, targets and addends.

Only eight ordinary-function instruction bytes change, in three comparisons.
The endpoint equality at `0x40B64E/0x40B651` and orientation comparison at
`0x40B65F/0x40B662/0x40B665` lose their prior original producer order after
translation by actual point roles. The final dy/error comparison at
`0x40BAF3/0x40BAF6/0x40BAF9` recovers the original instructions. Physical frame
homes and every other byte stay unchanged. Thus two fewer raw differences
include both recovered and lost producers; neither function becomes exact.
The frontend and independent owner/header view were tested together.

Close this fixed model without adoption or further layout/header/flag variants.
There is no untouched C++ companion compile, Native/MinGW build, runtime test,
new provider query, relink, game or full replay. Current source, cached products
and ledgers remain at 392 exacts and 23 authored candidates. Independent review
confirms the source, ABI, binding and instruction deltas. Private evidence is
in `.analysis/polygon-current-c-owner-20261017/`. All seven raw input/object
copies are archived, every member hash verified, then removed, releasing
48 KiB net of the archive, excluding receipt costs. Useful current caches remain.
