# Unsigned text-width accumulator

October21 update: the subsequent [declaration-order recovery](DECLARATION_ORDER_RECOVERY.md)
preserves this unsigned arithmetic contract and restores all279 measurement
bytes exactly. Its216 existing cases pass; all six UI companions stay exact.
The three-byte residual below is historical, not the current comparison.

October20,2026. The complete `measure-text` comparison improves from282 bytes/
26 differences to279 bytes/3 differences. It remains nonexact. All six exact UI
companions keep their complete raw and relocated code identities. Overall
counts remain392 exacts; authored coverage remains247 exact/23 candidates.

## Source inference

Original measurement at404FD0 adds into a DWORD accumulator. The three additions
at4050A5,4050CC and4050D2 have no overflow branch. The accumulator has no signed
comparison, division, address escape or consumer before its signed32 return.
The missing-glyph half-width is separately computed from a signed sprite width
through CDQ/SUB/SAR before accumulation. Retained original Evidence is
`ev_6a25f94931f763de87b46ce0de325939c392113a9c31de1568162431ea46a545`.

The preceding [boundary correction](AUTHORED_BOUNDARY_CONTRACTS.md) correctly
retains wrapping additions through a signed accumulator and explicit conversions.
The present single model makes that existing accumulator `DxBallUInt`, uses
compound additions and converts its final bits to `DxBallInt` at return. Glyph
width plus spacing is still unsigned32; the half-width division stays signed.
Parameters, search, loop, character handling, variable names/order, other
functions, headers and compiler flags stay fixed.

Inductively, each iteration stores the same low32 bits as the preceding source.
Only the final supported VC4/GNU signed32 conversion observes their signed value.
This is a natural type inference from actual producers/consumers. It does not
uniquely recover the historical author's accumulator declaration. No alternate
type, identifier, scope or operand model is compiled after this fixed proposal.

## Complete comparison

One canonical-path UI compile checks all seven complete functions and38 actual
COFF bindings, with no literals or attached metadata. All target extents and
binding targets/types/addends stay fixed. Six raw/resolved companion identities
stay unchanged and no exact is lost. The complete measurement body now has the
same relocated SHA as the earlier279/3 candidate, while its new C source retains
the defined modulo32 contract. The intermediate ADD/MOV producer is gone.
The three remaining strict positions33,36,38 are the previously documented
outer signed-loop comparison transpose. They are not masked or accepted exact.

Compile time is10.041s, peak166,772,736 bytes, with zero high/max/OOM events.
The frozen proposal, producer, complete comparisons, actual mappings, restoration
and resource receipts are under private `.analysis/text-width-accumulator-20261020/`.

## Focused verification and integration

Only ui.c recompiles in the native build; all38 other native objects stay fixed.
Build/relink takes1.220s. Current library SHA-256 is
`a25f31c84a17af6c748e02781dc73bfa0241072a7a817bf82a40502e28681f80`.
The216 unchanged existing measurement cases pass, retaining three banks,
spacing−2/0/1/3, signed high bytes, NUL, duplicate/excluded glyphs and signed counts.
The three retained finite font overflow cases and negative-half control also
match original x86: −2147483648,−2147483648,−1073741827 and−1073741824.
They use actual17-byte bank files and failed CreateSurface before measurement;
there is no surface draw or giant allocation. Prior instrumented failure
receipts remain historical; no new instrumented compilation repeats them.
Focused verification peaks66,961,408 bytes with zero high/max/OOM events.
Heavy operations remain serial on CPU0,35% CPU,384MiB high/512MiB max.

All270 authored source/object/flags/comparison receipts verify across30 closures,
without replay. Six exact-ledger source/object identities refresh. The235
historical semantic input rows and six owner-source hashes refresh with scopes,
case counts and all249 ordered row identities preserved, including duplicate
unit names. No new semantic acceptance is added.

Thirty-eight closed input/product/helper files are archived and member-size/SHA
verified before exact-list removal. The449,321-byte archive releases6,111,232
allocated bytes net before small receipts. All623 protected SHA/size/mode/mtime
identities remain fixed. Current products/caches and unique JSON proofs stay.

The tested bff527e EXE and ZIP retain their earlier identities and predate this
source change. They are not rebuilt or replayed. Complete game verification
stays deferred while authored recovery continues. Original declaration/compiler
context and the final inventory proof remain open.
