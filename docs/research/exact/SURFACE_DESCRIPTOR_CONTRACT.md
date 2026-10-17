# Complete DirectDraw surface descriptor control

October 18, 2026. One fixed shared v1 surface-descriptor model gains two exact
functions and loses nine among 32 complete comparisons. Reject it as a family;
keep the maintained source and all current claims: 394 exact functions and
21 authored candidates. Do not select its two successful objects/functions or
extend it into declaration, union, alias, name, header or order variants.

## Independent contract and fixed model

Original GetSurfaceDesc, Lock and CreateSurface calls consume the 108-byte
32-bit descriptor. Its known API contract includes four color-key records, a
32-byte pixel-format record, a surface-capability record and a void surface
pointer. The maintained declaration flattens these records into arrays and
declares the surface pointer as a byte pointer. Earlier SDK/scalar-kind controls
retain that flat shape; this is a distinct, independently grounded model.

The installed MinGW `ddraw.h` corroborates the v1 layout. It does not recover
the original 1990s header text or establish its modern union-alias list as
historical source. The fixed model uses that compatible nested shape, named
unions for strict C compatibility and `void *lpSurface`. Existing scalar
abstractions, interface declarations, linkage and flags stay unchanged.
The existing color-key low/high fields are retained inside the four records.

Only actual descriptor field accesses and required casts to byte pointers
change in executable source. All live reads, call order, scopes, writes and
unused fields are preserved; no new initialization or pointer cache is added.
The 32-bit member offsets remain size0, flags4, height8, width12, pitch16,
surface36, keys40, pixel format72 and caps104. Native pointer width is retained.

## Complete pilot comparison

Resources, UI and rotation compile once each with their unchanged recipes.
All 18, nine and five complete functions respectively compare with 415 actual
COFF bindings, 31 complete literal references and local-target guards. This is
a pilot, not a validated replacement for every consumer of the shared descriptor.

| Selected result | Maintained size / differences | Proposal size / differences |
| --- | ---: | ---: |
| Draw sprite |107 /94|105 /0|
| Release sprite |269 /245|262 /0|
| Load sprite bank |1475 /66|1475 /65|
| Load PCX |979 /851|979 /850|
| Rotate palette right |234 /9|234 /6|
| Measure text |279 /3|281 /186|
| Draw line |445 /9|445 /12|

Nine prior exacts are lost: keyed draw, keyed stretch, capture, glyph lookup,
glyph drawing and all four rotation projections. Fifteen resolved code
identities stay unchanged, including blt sprite and the rotation renderer.
The net loss is seven exacts. Small differing-position improvements do not
recover original declarations or justify adopting a partial header view.

Private `.analysis/surface-descriptor-contract-20261018/` retains the full
transformation, recursive inputs, original/proposal identities, complete
comparisons and independent reviews. No wider consumer compile, native build,
relink, provider query, game or full replay follows the rejected model.
The three compiles run serially on one CPU under CPU35%, memory high640MiB/
max768MiB. Observed scope peak is 241,090,560 bytes, with zero high/max/OOM
events. Disposable copied inputs and all six before/proposal objects are
archived and every member hash verified before removal; current tested
products and valid CMake caches remain.

Cleanup removes26 copied inputs/products and releases139,264 allocated bytes
net of archive/journal costs. Finalization initially compared generated literal
names and a report-only build annotation as identities, then looked for literal
data in comparison rows rather than mapped units. The corrected final check
verifies every other result/binding field and the attested literal mapping;
no compilation or complete comparison is repeated. The final verification and
four bounded investigation directories are SHA-256 sealed.
