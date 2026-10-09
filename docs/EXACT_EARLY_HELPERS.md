# Early region, geometry, rotation and text helpers

Eleven previously unmaintained entries now have shared source bodies. Ten have
application contracts; the no-effect entry at `0x40CC20` remains of unknown
origin. Existing horizontal rotation offset source is also reconciled with the
related maximum-projection contracts. Reconstructed names describe observed
operations, not recovered original identifiers or source filenames. No caller
was found in these eleven direct dossiers or the bounded saved-evidence review;
active game use remains unresolved.

The target is English DX-Ball v1.07, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
REA 4.1.0 / Ghidra 12.1.4 supplied 30 bounded requests in two closed runs,
reproducible with `config/rea-early-helpers.json`. They added 30 Evidence records
to the saved 457-record snapshot. Five instruction queries could not decode
undefined listing gaps; their limitation is retained, and focused byte reads
establish the complete gap bytes separately. The complete comparison never
masks those gaps, relocations, literals or epilogues.

## Complete function boundaries

| Maintained entry | Address | Whole span | Proposal differences | REA dossier |
| --- | --- | ---: | ---: | --- |
| `dxball_clear_hit_region` | `0x00401F20` | 101 | 0 | `ev_636d8c9d45d1dc1e58e72cdf47a1ae3750dc23167d60e2d93897e5b170a44b2c` |
| `dxball_hit_region_contains` | `0x00402040` | 153 | 0 | `ev_213c359a739b95cb4578a25111184d2dccb8a766bcd70f51a47f6f2692279671` |
| `dxball_reset_hit_region_count` | `0x004020E0` | 26 | 0 | `ev_3ae91047189d7c1aeb483781afc89946cc9f33b4ef4f842b4805f951703eb228` |
| `dxball_unclassified_noop_40cc20` | `0x0040CC20` | 16 | 0 | `ev_1bbbaa4099a533a8cce83d347c9c09c1c7e92a2010860513846d65c01c8183fc` |
| `dxball_point_angle` | `0x004025A0` | 109 | 0 | `ev_04235c3e2d3f65c8c2605c47cb8cc26323676db637d40a80931d206f308cee79` |
| `dxball_point_distance` | `0x00402610` | 130 | 52 | `ev_c00ff92fb8c6b7716952bed048968fc8ee66daaf782d6dd40d19389de053df98` |
| `dxball_rotated_sprite_y_offset` | `0x00402DE0` | 191 | 6 | `ev_0bb8d29f0bbb9230ce62dfeaaa226c4099138a7443f31974dbb2b206ef459987` |
| `dxball_rotated_sprite_width` | `0x00402EA0` | 259 | 6 | `ev_c3cc1cd772f6eac8a8ffc6584b3eac3e0650bb9c1d80d6d28b1d184ebe95f947` |
| `dxball_rotated_sprite_height` | `0x00402FB0` | 191 | 158 | `ev_5a48619a2f498c7a99cf625e4cdd4a257959fde0d5534b0e5b2910f949077bbc` |
| `dxball_copy_text_word` | `0x00403290` | 143 | 14 | `ev_63f0bd40bfeed979044f1c1862d14811d39f1052b4915f2b65be015d631224af` |
| `dxball_release_sprite_bank` | `0x00403EB0` | 178 | 0 | `ev_0059b35c48ef9caf01f1a844bb25b51a29ce3518da71601c97c70895eed6d434` |

Six complete emissions have zero differences: clear region (101 bytes),
contains point (153), reset count (26), point angle (109), release sprite bank
(178), and the unclassified no-effect entry (16), totaling 583 code bytes.
Only these are added to the configured exact set. The five remaining new
entries and existing horizontal offset remain complete configured candidates.
Candidate size equality is not exact acceptance. Accepted ledgers depend on a
fresh grouped cold replay of every unit after these shared input changes.

Ghidra owns 143 bytes in the region-containment function's 153-byte span.
The two missing five-byte relative branches at `0x4020BC` and `0x4020C8` both
contain `e907000000`: the first targets the second branch, which targets the
common epilogue at `0x4020D4`. Rotation gaps at `0x402E8B`, `0x402F8F` and
`0x40305B` contain `e90a000000`, targeting their common epilogues. The whole
function COMDAT, including these otherwise unowned branches, is compared.

Gap-byte Evidence: `ev_5938d45b103eebbc97eb8350ec208bd0305c140b7cb4930bf5f176f8a3412fe5`,
`ev_cea3ec1a8ad14d6fbeedd5f8f40d784e373958caad092d1757f08e9dfa9ddb53`,
`ev_ef7ec380e69c68892ba8533b87c32732187310fd913801791fd55af7d41f3d99`,
`ev_aa9bbd7b60942a296e17fd5a95276859e76c4db2aa6e00a2dc146103ba6be659`,
`ev_f2cd7344def72e95aa5a3b2aaf3b6e7994b9cb9a7f789ac43883a490f3a28734`.

## Observed contracts and bounded interfaces

Region records contain five signed 32-bit words at root `0x4251A0`, stride 20.
Clear performs five independent zero stores. Containment accepts any nonzero
active word and tests all four bounds inclusively; inverted bounds do not get
normalized. Single-record indices require 0–99. Reset writes only the count at
`0x421064`, leaving the entire array unchanged.

Point angle subtracts integer coordinates before converting the differences
to double and calling cdecl `atan2(y_difference,x_difference)`. It stores a
float local, multiplies by the double constant 180.0, divides by 3.1415927,
and returns through ST0. The old compiler keeps extended intermediates across
its float stores; modern native float assignments can round earlier. Exact
acceptance concerns the complete legacy emission, not cross-runtime math
kernels or all floating-point rounding modes. Coordinate subtraction must be
representable in the maintained signed integer domain.

Point distance converts the first coordinate to double before each subtraction,
passes both differences to `fabs`, stores two double differences, computes their
squared sum, calls `sqrt`, stores a double result and truncates through `__ftol`.
The maintained interface returns a signed 32-bit result within its representable
finite domain. EDX:EAX comes from the original CRT conversion; an original wider
public return type has not been established. The four actual double temporaries
are maintained. Current VC4 scheduling retains the second `fabs` result in ST0
and emits 127 bytes instead of the original 130; this remains a candidate.

Rotation dimensions use the current bank and valid slot backed by a sprite.
They truncate and take the integer absolute value of projections at angle+45
and angle+135, then select the larger. Cosine width projections divide by 1.3;
sine height projections do not. Offsets negate the maximum, while dimensions
double it. Casts keep intermediate division extended on the native host;
the observed boundary 13/1.3 truncates to nine. Angle additions, conversion,
absolute value, negation and doubling require representable results. Local
allocation and index-register scheduling still differ from the original.

The text helper skips `skip` literal spaces, then copies through the next literal
space using the source offset as the destination offset. It leaves the skipped
prefix unchanged, writes a NUL at the stopping offset, and returns the source
pointer just after that space. It does not stop at NUL. Both source and writable
destination need backing through the stopping space; the source must contain
the required spaces. The maintained source keeps offset, space count and source
pointer locals; their allocation differs from the original despite a matching
143-byte section size.

Bank release (`src/resources_bank.h`) saves the current bank, selects the requested valid bank, calls
the existing single-sprite release for all 255 slots (including slot zero),
zeros count and allocation mode, copies the literal `" "` into the filename,
and restores the previous bank. Existing sprite/heap/COM ownership contracts
apply. It does not clear the filename's unused trailing storage.

The 16-byte entry at `0x40CC20` has ordinary unoptimized saves/restores and a
return branch, with no observed state effects or argument access. A void,
zero-argument interface exposes that observed operation. Its original name,
prototype, authorship and owning source are unknown; placement beside editor
code is a maintained organization choice, not an origin finding. It remains
`unknown` in the origin ledger and is not counted as a new authored function.

Constants are attested independently: 180.0/3.1415927 at `0x420028`/`0x420030`
by `ev_b4ace81f906f7f473dc73c40a249afe80a6377f4e046dc3a1cb2f2ce1dc3b816`,
1.3 at `0x420060` by
`ev_76af9ac845d31f06cc085307aa2c90e9c6c6425e9c832079c0329a5410b2d5ee`,
and the space string at `0x421090` by
`ev_4f764ec8257afec6273255653eee23aced70d8ec4223cea931db10274734b474`.

## CRT dependencies and compiler-model limits

Four unknown origins are now identified as CRT runtime entries, using saved
REA dossiers and named members in pinned VC4 `libc.lib`, SHA-256
`e5f0d0e6dd2e01dbb0005e9dd4764507b852ede9a824798f0970bc570966a7e3`.
This does not add runtime implementation source or exact units.

| Original entry | Identity | Corroboration |
| --- | --- | --- |
| `0x416780` | cdecl `abs` | Complete 10-byte named section; `ev_a870a9d02727538615076e72a59b2014379e6436c091dea56c40e59fd9a01464` |
| `0x417608` | cdecl `atan2` | Named 10-byte interval/table/dispatcher; `ev_8caa88e28db733daf28fd0d67bc0be8cc090400be2e2c4f84078cbb5f281c57c` |
| `0x417640` | cdecl `sqrt` | Named 10-byte interval/table/dispatcher; `ev_249602787ea9e10af81f8d135f6c47375382c6597a852332d16d406986d7882c` |
| `0x417660` | cdecl `fabs` | Complete 229-byte named section with seven corroborated helper-call positions; `ev_1a543a56cee2cb35ea1a3404d535eb45c633d35c065e199252e48c0b52979f4f` |

The `atan2` and `sqrt` intervals reside in sections containing other functions;
they are not dedicated whole-section exact units. Their generic wrappers alone
would not establish identities. Original operation-table headers at `0x423290`
and `0x4232E0` match the pinned named tables byte-for-byte, including the names:
`ev_3a4dc133c1644a7eca30723d32434c445069162b3c916e09a9a15cfb0c983d1b` and
`ev_f6a414600d6f4d61172f65edeb5491e6d910bbcfc248fad3ddebaba403ab32cc`.
The unexamined pointer remainder and semantic names of header-tail fields are
not claimed. Ghidra's inferred stdcall signatures are superseded by the actual
cdecl call sites and pinned declarations.

The initial frozen C++ language-model diagnostic improves sine projection
indexing but changes cosine indexing and leaves local allocation/distance
scheduling unresolved. A single `/Op` diagnostic emits angle/distance sections
of 127/133 bytes, unlike the originals' 109/130. Neither model is selected.
New definitions are appended after existing owner definitions. The bank-wide
API is declared in `src/resources_bank.h`, included beside its definition, so
its declaration does not disturb the existing resource declaration graph. The
ordinary existing Blt arithmetic is unchanged; all prior exact emissions must
remain accepted after the full replay. This is maintained source organization,
not a recovered original filename or declaration order.

No profile-selected body/layout, artificial local, volatile barrier, padding,
identifier brute force, copied instruction or assembly is introduced. Failed
and nonmatching proposals, complete listings, inputs and raw Evidence remain
in the private sealed checkpoint. The complete authored denominator and the
>=95% objective remain unresolved.

## Accepted checkpoint and verification

The stable grouped cold replay accepts all 76 configured units, 9,833 complete
code bytes, plus 136 separate exception-metadata bytes. All 70 prior units
remain exact. The 22 existing owner scripts pass once with 268 frozen inputs;
235 existing application semantic input closures are refreshed without changing
247 direct entries, 112,273 distinct cases, existing scopes or fixture matrices.
Strict native Debug, MinGW and full legacy builds pass, along with the existing
14 exact rejection checks and existing 1,024 rotation COFF vectors. No tracked
tests, direct acceptance rows, cases or campaign observations are added.

A private 59-observation probe compares the unmodified original, full relocated
VC4 emissions and native calls for the reconstructed contracts. It checks
single-region clearing, active/inclusive containment edges, count-only reset,
no-effect state preservation, skipped text prefixes and returned source offsets,
finite coordinate distance, all four rotation projection results, and three
bank releases with owned slots 0/127/254. Release preserves other-bank storage
and filename trailing bytes, restores the previous bank and frees three owned
records. Eight cardinal/diagonal angle results agree after transport to float;
this is a bounded observation, not general native rounding-mode or math-kernel
fidelity. Actual original CRT finite math executes in the target-machine probe.

Source presence is 283 entries: 270 authored bodies, one unknown-origin no-effect
body and 12 runtime bodies. Origins are 270 authored, 21 runtime, 18 generated
and 219 unknown. The current native alias comes from `build/native-early-helpers`,
SHA-256 `bacf8063f6dc64e062063cdb52623318a1283869cab83c15efbcf5a0b3565479`.
The private `.analysis/checkpoints/exact-early-283-76` checkpoint seals frozen
inputs, closed evidence, complete failed/final proposals, accepted compiler
products, reports, probe and compressed snapshot before verified cleanup.
The prior list-initialization native product and all earlier identities remain
separate. The complete authored denominator and >=95% objective remain open.
