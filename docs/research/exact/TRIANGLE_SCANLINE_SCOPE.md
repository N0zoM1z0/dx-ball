# Triangle scanline lifetime

The triangle routine at `0x0040AB90` now declares its scanline `y` in a block
covering the upper and lower scan phases. The block starts after long-edge
step and X initialization and includes the lower flat-edge return. Fixed-point
objects and the observed vertical-scale calculation remain outside it.

The original first stores `y1` into the scanline home at `0x40AD33`. Its later
reads and increments occur only in the four scan loops, with no consumer in
vertex sorting or initial fixed-point setup. This supports the narrower
lifetime. The selected emitter restores y's original EBP-36 home from EBP-32.
All existing arithmetic, branches, calls and writes keep their order.
Long-step, short-step and long-X storage still differ; short-X remains at its
original EBP-16 home.

One VC4 compilation reduces the complete 1,710-byte comparison from **107 to
88 differing positions**. The function remains a candidate. Its complete
160-byte exception metadata stays exact. Nine accepted raster functions
preserve 715 code bytes and 136 metadata bytes; ordinary and clipped polygon
comparisons remain 1,543/211 and 1,592/210. The other 41 candidate code hashes
are unchanged.

Both original/native and relocated VC4/native profiles pass the same 72
existing triangle cases. These cover four existing shapes, endpoint
permutations, pitches and colors, comparing guarded destinations, input points
and ordered effects. Native and MinGW builds pass. VC4 links the single matching
raster object with 36 verified unchanged objects. All 231 complete exact
closures verify, and 235 historical input inventories refresh without changing
their case scopes. No game runs.

The global total stays **231 exact functions / 58,775 code bytes / 136 metadata
bytes**, with 42 authored functions still nonexact. Full source and compiler
receipts, complete comparisons, independent review and focused case payloads
are retained in `.analysis/triangle-scanline-scope-20261013/`. Seventeen completed
source/object/tracking copies are preserved in verified gzip carriers, releasing
4,317,184 allocated bytes. Current build products remain available.

Original triangle evidence is
`ev_ad1b11b19724c19c9001ac422c47b0b3b83c6b2965625e31729f969414a6467a`.
The separate 168-byte cleanup/handler continuation and complete metadata
attestation are retained in the
[full correspondence note](../RASTER_METADATA_CORRESPONDENCE.md). Complete
comparisons cover those bytes as well as the provider-owned body.

## Edge-record ownership review, October18

The original root constructors run long step (EBP−24), short step (−20), long
position (−32), then short position (−16), before sorting and both early exits.
The four root cleanup funclets reverse that order. Two ordinary slope/position
edge records would group construction by edge, contrary to these instructions;
the long pair is also separated by the retained vertical-scale home at−28.
The actual increment operators couple values logically but do not establish
aggregate ownership. No edge-record or narrower-root lifetime trial follows.
Private `.analysis/triangle-edge-ownership-20261018/review.json` retains exact
constructor/cleanup addresses and the original dossier, continuation and metadata
Evidence IDs. This does not establish unique original names or declarations.
