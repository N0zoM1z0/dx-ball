# DirectDraw line interface

The line routine at `0x403070` now takes `DxBallDDSurface *` and calls
GetSurfaceDesc, Lock and Unlock directly through that interface. Splash callers
already own surface pointers; ranking drawing converts its selected surface at
the call boundary. The byte color parameter and traversal are unchanged.

The original loads its first argument at `0x403099`, dereferences the vtable at
`0x40309C` and calls GetSurfaceDesc at `0x40309E`. The complete saved dossier is
Evidence `ev_25f8571b40b1ee8c589f398fa1211552c03d241352d0737d904789e2664b8af2`,
operation 24 of the closed October 7 11:58 run. This establishes interface use;
the recovered C type name is ours.

Five consuming recipes preserve all 53 accepted bodies. Complete candidate
comparisons are unchanged: line remains 445 bytes with nine differences in
three commuted signed guards. The exact total stays **229 functions / 57,649
code bytes / 136 metadata bytes**, with 44 authored candidates.

One unchanged 486-case line selection checks complete padded pixel buffers,
all octants, endpoint order, zero length, lock retries and ordered COM calls.
Native and MinGW builds pass. VC4 links five fresh matching objects and 32
verified unchanged objects. All 229 complete code, literal and metadata closures
verify. No game runs.

The initial public prototype used the resource typedef before its declaration.
Using the existing `struct DxBallDDSurface` forward declaration fixes that
dependency; the final five-owner family compiles once. Private receipts are in
`.analysis/line-interface-20261012/`.

The later [drawing-primitive owner](DRAWING_PRIMITIVES_OWNER.md) moves line and
fill into one C++ implementation while retaining the public C API. Their full
445/9 and85/0 comparisons stay unchanged; one residual palette guard recovers
three bytes. The new complete owner, final products and562 focused cases are
verified together. The original owner boundary remains inferred.
