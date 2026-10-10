# Exact projection and text traversal restoration

Four existing source bodies now emit complete original functions under the
pinned VC4 recipe. Both projection results are stored in a real two-element
array, and text traversal groups its existing pointer, offset and space count
in a local cursor. Every member is initialized and consumed. The arithmetic,
call order, destination offsets, return values and external ABI are preserved.
These are maintained declarations consistent with observed layout; exact
emission does not establish the original source spelling or identifiers.

| Unit | Original entry | Complete code bytes |
| --- | --- | ---: |
| Horizontal projection offset | `0x00402CD0` | 259 |
| Vertical projection offset | `0x00402DE0` | 191 |
| Rotated width | `0x00402EA0` | 259 |
| Copy text word | `0x00403290` | 143 |

The four additions total 852 code bytes. The grouped cold replay accepts all
80 configured units, 10,685 complete code bytes plus 136 separate exception
metadata bytes. Every previous 76-unit emission remains exact. Each comparison
uses the entire dedicated COFF section, the complete independently established
target span, every relocation and attested literal contents. No bytes, gaps,
operands or epilogues are masked.

## Reused original evidence and literal correction

No new original-analysis session is needed. Matching saved REA 4.1.0 /
Ghidra 12.1.4 observations remain bound to English DX-Ball v1.07, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
The projection and text dossiers are:

- Horizontal offset: `ev_274065db33e0f5af45f91e84ec3c68bf86d6b31f20e54434e568a1cca50290f5`.
  Its request parameter is `0x402D30`, but its returned function entry is
  `0x402CD0`; retrieval must respect the returned entry.
- Vertical offset: `ev_0bb8d29f0bbb9230ce62dfeaaa226c4099138a7443f31974dbb2b206ef459987`.
- Width: `ev_c3cc1cd772f6eac8a8ffc6584b3eac3e0650bb9c1d80d6d28b1d184ebe95f947`.
- Text: `ev_63f0bd40bfeed979044f1c1862d14811d39f1052b4915f2b65be015d631224af`.

Projection results occupy EBP-8 and EBP-4 in the original 16-byte frame.
Text traversal uses EBP-12 for its pointer, EBP-8 for its offset and EBP-4
for its space count. The arrays and cursor contain only these actual values.
The complete horizontal span, including the otherwise unowned five-byte jump,
was established in [EXACT_CORE.md](EXACT_CORE.md); the remaining boundaries
and gap reads are retained in [EXACT_EARLY_HELPERS.md](EXACT_EARLY_HELPERS.md).

The horizontal offset's divide and emulated divide arguments use the double
1.3 at `0x420058`; the width uses a separate identical double at `0x420060`.
The earlier horizontal candidate mapped this literal to `0x420060`, introducing
six relocation-byte differences. That candidate mapping is corrected using
the original operand addresses, rather than selecting an address by value.
No previously accepted exact unit used the incorrect candidate mapping.
`ev_3981d4fe3871c6d5f4976aaec23007d066c24f80aedca23dd51270d63c19de71`
reads the complete eight-byte literal at `0x420058` within its 40-byte buffer
starting at `0x420038`; `ev_76af9ac845d31f06cc085307aa2c90e9c6c6425e9c832079c0329a5410b2d5ee`
attests the separate width literal. Both contain `cdccccccccccf43f`.

## Remaining differences and bounded verification

Height remains a complete candidate: 193 emitted bytes versus the original
191, with 158 differences. Applying the same projection array is semantically
consistent, but bank/slot address evaluation still differs. One explicit
pointer-arithmetic spelling produced no improvement and is not selected.
Distance remains unchanged at 127/130 bytes and 52 differences. A bounded
nested-scope hypothesis for its four actual double temporaries reduced the
comparison to 49 differences without restoring the original stores and
scheduling, so it is not selected. Earlier C++ and `/Op` model trials remain
unselected. Removing redundant coordinate casts in the earlier distance
proposal did not change its emission; the saved listings already used
FILD/FISUB. The old private review's contrary explanation is superseded.

There is no profile-specific source/layout, unused local, padding, assembly,
volatile barrier, copied instruction or identifier search. Private diagnostics
preserve frozen inputs, generated listings, failed hypotheses, full comparisons
and independent review. Their zero-difference trial results were provisional
until the fresh grouped replay of the stable source.

The 22 existing owner scripts pass once against the new native Debug library.
The existing 14 exact rejection checks, MinGW and full legacy builds, and
1,024 rotation COFF vectors pass. The private original/native/full-relocated
COFF helper probe repeats its existing 59 observations, including all four
projection contracts and text destination/return offsets. No tracked tests,
fixture matrices, direct acceptance rows or distinct cases are added.
235 existing application semantic input closures are refreshed; the accepted
247 entries and 112,273 distinct cases keep their existing scopes.

Source presence remains 283 entries: 270 authored, one unknown-origin no-effect
body and 12 runtime bodies. Origins remain 270 authored / 48 runtime /
42 compiler-generated / 168 unknown. The 459-record snapshot is unchanged.
The complete authored denominator, synchronized whole-game fidelity and
>=95% complete-source objective remain unresolved.

The private `.analysis/checkpoints/exact-projections-283-80` checkpoint retains
this batch before verified cleanup and links to the previous origin checkpoint.
The native alias comes from `build/native-exact-projections`; its identity is
recorded in the current handoff. All historical native products remain separate.
