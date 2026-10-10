# Complete splash source restoration

This connected family restores eight complete bodies from retained REA 4.1.0 /
Ghidra 12.1.4 instruction dossiers, totaling 3,029 original bytes. Static evidence
does not establish execution or exactness; the following grouped compiler and
original-execution results establish their separate acceptance scopes.

| Address | Entry | Contiguous bytes | REA Evidence ID |
| --- | --- | ---: | --- |
| `0x00407420` | initialize splash | 430 | `ev_61c4212874ada28527bff5917d72525d34eed9f3b168a27f413b46eefec7948c` |
| `0x004075D0` | redraw splash | 949 | `ev_4a967bbbf38cd42ec661c8b5dc82686fc9c2ab4f8e75a5c9b7132067706f4739` |
| `0x00407990` | splash frame | 274 | `ev_7818bf9bdac1f23ebe2ac4798a9137426d357a7e5f7e060469add4fb9fee3f23` |
| `0x00407AE0` | dispose splash | 185 | `ev_57ee9ffdab9d682c65d0b645600262f0013224bdad8a466304a77cd940794454` |
| `0x00407BA0` | draw scroller wave | 235 | `ev_ecc8bc98f207e2dcf6101e2f1fbf61126d0081fced68e29388f49128c78d7f89` |
| `0x00407C90` | update scroller | 233 | `ev_60ffa0dd2052ca4d66e244d13dff9c0927c40df0a2c284e69e239173f8e96e25` |
| `0x00407D80` | draw waving credits | 353 | `ev_7921a58cbee918a0e153804ca0dbd7c123d0a0f183a6f0a8b32af893053e796f` |
| `0x00407EF0` | pulse splash palette | 370 | `ev_2c669d6d7ae4ed75294367bdef23972e96d8cd5430ddbee9bcd729c55f1398c3` |

The original has distinct direct resource, sound, text, surface-binding and
palette calls. Initialization preserves the separate reset stores and consumed
color-key initialization at its COM call. Frame cursor clamps are explicit.
Disposal stops sound even for fade zero and consumes a full rectangle only when
fading. Live COM surface handles replace cached helper aliases.

Scroller wave restores the consumed step of five and two complete destination
branches with sine and COM calls. Credits likewise retains both complete branches.
Scroller update initializes its rectangle after the optional glyph call. Palette
pulsing retains unsigned positive-byte tests, the consumed half-span, wrapped
phase and the unusual SetEntries count of span+48.

The original redraw line calls push a full DWORD color expression. The maintained
typed line API narrows color to a byte. This caller evidence alone does not prove
the original C prototype; no unprototyped call or ABI-forcing cast is introduced.
Source names and declaration order remain unproven. No capacity, name/order,
layout or alternate-body trials, inert locals, padding or copied code are used.

The native harness forwards the genuine void four-integer update_sound API
through the current copied-image DisplayOps slot. Default/null/self/reentry
callbacks are rejected. Existing constructors, fixtures, cases, oracles and
campaigns remain unchanged. This host boundary does not prove physical Windows
graphics or audio behavior. The >=95% complete-source goal remains unachieved.

One configured cold epoch accepts 110 whole exact units / 14,658 code bytes,
plus 136 separate exception metadata bytes. All 106 prior complete code/metadata
identities are preserved. Initialization (430 bytes), frame (274), disposal (185)
and credits (353) add 1,242 exact bytes. Redraw (949), scroller wave (235),
scroller update (233) and pulse (370) remain candidates with 23/19/3/17 complete
differences, respectively. All 241 new relocations, 21 complete NUL string
operands and four eight-byte double operands are
bound. Existing candidate results are unchanged.

Only one actual 69-input diagnostic and one limited strict native build execute;
no source/body revisions follow the initial reconstruction. Removing the unused
scene helpers shifts generated COFF literal names in unchanged prior intro
initialization and redraw. Full literal/operand proofs refresh these names after
native replay under a separate manifest amendment, without changing source,
headers, harness, build flags or recipe. The original frozen manifest and native
results remain intact. Two initial mapping-script failures for missing known
global bindings are retained; they compile no additional product and do not
change source or the manifest.

All 22 existing owner scripts pass in 546.074 seconds with 288 physically frozen
inputs. All 1,510 runtime cases and the existing 5,615 intro cases plus 58 separate
integration checks pass. Fourteen existing rejection controls, 7,164 fresh raster
and 1,024 fresh rotation vectors, strict MinGW and full VC4 builds pass. The actual cold raster
product is adopted for the unchanged complete recipe without recompilation;
semantic_driver_executed=false is explicit. 235 semantic input identities refresh
without changing case totals or source-present counts.

The shim checks 24 genuine symbol identities and 25 production-default slots,
including the existing music adapter check, and retains 46 actual compiler
dependencies. Current native SHA256 `b53eed692c71cb40fb62a8e98a0d611a40356d9e0b2b61cc3ea06f45ea76449e`;
shim `2004740f65c9e3938f43c9c7c20c5a749eb91f7bb9fe272fa6bef2dafdd1ba97`.
Snapshot 468 records remains unchanged; no new REA request,
runtime-origin promotion, source-presence entry, case or campaign is introduced.
Private evidence lives at `.analysis/checkpoints/exact-splash-283-110`, linked
to the preceding intro 106 checkpoint. The >=95% complete-source goal stays open.
