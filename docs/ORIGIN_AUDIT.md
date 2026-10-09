# Bounded origin audit

The origin ledger now records **270 authored / 48 runtime / 42 compiler-generated /
168 unknown entries**. This batch resolves 27 CRT entries and 24 generated raster
fragments. Source presence remains **283** (270 authored, one unknown-origin
no-effect body and 12 runtime bodies); semantic acceptance remains **247 entries /
112,273 distinct cases**, and exact acceptance remains **76 complete units /
9,833 code bytes plus 136 separate metadata bytes**.

All 270 currently confirmed authored entries have maintained source. That
conditional result does not establish the full authored denominator or >=95%
complete source recovery. The remaining 168 unknown origins, provisional
boundaries, original type uncertainty and whole-game fidelity remain open.

## Complete CRT sections

[The section manifest](../config/runtime-origin-sections.json) selects 26 complete
code sections from the pinned VC4 `libc.lib`, covering 2,137 bytes and 27 previously
unknown entry rows. REA Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`
provides a complete 39,136-byte loaded read at `0x416610`. The saved target and
provider identity are checked before that read supplies comparison bytes.
The two-request run closes normally and saves a 459-record cumulative snapshot.

Run `scripts/repo-python scripts/verify-runtime-origin-sections.py` to repeat the
section comparisons. Each selected archive member and complete code section is
checked, every DIR32/REL32 operand is applied, and every byte is compared. Bindings
come only from the preceding reviewed CRT map or symbols defined in that same
section. Candidate-search relocation addresses are excluded from acceptance.
The private report binds all verifier inputs, members, original Evidence and
close marker. The twelve existing CRT archive/section/relocation controls pass.
No new tests or runtime observations are added.

| Original section start | Complete bytes | Pinned library symbol or family |
| --- | ---: | --- |
| `0x00416610` | 334 | `memcpy/memmove family; symbol alias unresolved` |
| `0x004177f0` | 232 | `strcpy/strcat or multibyte aliases; two entries` |
| `0x00417c40` | 88 | `_memset` |
| `0x004184a0` | 53 | `?_JumpToContinuation@@YGXPAXPAUEHRegistrationNode@@@Z` |
| `0x00418c00` | 79 | `__ms_p5_test_fdiv` |
| `0x00419370` | 17 | `__statfp` |
| `0x00419390` | 18 | `__clrfp` |
| `0x004193b0` | 52 | `__ctrlfp` |
| `0x00419ca0` | 50 | `__errcode` |
| `0x00419ce0` | 57 | `__set_exp` |
| `0x00419d20` | 99 | `__sptype` |
| `0x00419fa0` | 57 | `__freebuf` |
| `0x0041d0e0` | 100 | `__ZeroTail` |
| `0x0041d270` | 29 | `__CopyMan` |
| `0x0041d290` | 15 | `__FillZeroMan` |
| `0x0041d2a0` | 29 | `__IsZeroMan` |
| `0x0041d2c0` | 173 | `__ShrMan` |
| `0x0041d600` | 129 | `__fptostr` |
| `0x0041d700` | 187 | `___dtold` |
| `0x0041dfd0` | 36 | `_strncpy` |
| `0x0041e5c0` | 35 | `___addl` |
| `0x0041e660` | 62 | `___shl_12` |
| `0x0041e6a0` | 54 | `___shr_12` |
| `0x0041f490` | 49 | `_strncat` |
| `0x0041f590` | 82 | `_calloc` |
| `0x0041f8c0` | 21 | `__frnd` |

The copy-family section includes its internal tables and disjoint instruction
ranges. Its REA dossier
`ev_20c05a6d694698f74f5570f7b83299850bfe1432ca2974dec7c7a0b6f23e4ec1`
reports 285 owned bytes inside the 334-byte span; the complete section comparison
includes every intervening byte. Both pinned memcpy and memmove members agree,
so their names remain alternatives. The 232-byte string section contains two
entry points and alignment; narrow and multibyte aliases remain alternatives.
The 53-byte JumpToContinuation section exceeds its provisional 46-byte inventory
span. These are complete **section-origin** comparisons, not new independent
function extents, source implementations or configured exact units. Existing
function extents and accepted source/semantic/exact rows are unchanged.

A broader private library scan retained additional candidates, including
unconfirmed external bindings and byte-identical alternatives. Those candidates
remain diagnostic and do not change origins. The scan is bounded to this pinned
library and the stated original read; it does not establish the whole original
link configuration or classify every procedure in the executable.

## Generated raster ownership

[The generated-entry manifest](../config/generated-raster-origins.json) records
20 destructor cleanup funclets and four frame epilogues within the maintained
triangle and fixed-point operators. Their ownership is established by actual
parent CALL/JMP sites, generated interior labels, destructor relocations and
original FuncInfo/unwind action pointers. Address containment alone is not used
to assign an origin or create a new source body.

| Maintained parent | Cleanup entries | Epilogues | Complete metadata bytes compared |
| --- | ---: | ---: | ---: |
| Triangle `0x40AB90` | 16 | 1 | 160 |
| Divide `0x40B2D0` | 2 | 1 | 56 |
| Less `0x40B3C0` | 1 | 1 | 40 |
| Add `0x40B450` | 1 | 1 | 40 |

Original metadata Evidence
`ev_6c6c33dc195917063f7db16dfa2c0358a9df49960944255f739688593df6d089`
and the add supplement recorded in the manifest support all four complete
metadata comparisons, totaling 296 bytes. Generated cleanup labels are actual
unwind-map action targets; frame continuations have parent rendered JMPs and
frame-restoration evidence. Some provider reference fields label those JMPs as
calls; the review retains that limitation and uses their rendered instructions.
Thirty saved Evidence records and the complete current raster input closure are
bound in the independent private receipt to the immutable preceding checkpoint.

Twenty-one piece comparisons have zero differences. Three triangle cleanups
retain one local-displacement difference each at `0x40B20D`, `0x40B216` and
`0x40B21F`. Their generated ownership is established, but the full triangle
remains a candidate. Matching its 160 metadata bytes does not add code or
metadata acceptance. The previously accepted operator metadata remains 136
bytes. Existing normal-vector tests do not prove exceptional unwinding, and no
new such runtime claim is made.

The generated pieces require no independent authored C bodies. Precise historical
local names and source spelling remain uncertain. Two external import-thunk
rows and the no-effect body below `0x416780` remain unknown; the other 165 unknown
rows are at or above that address. The >=95% source objective remains active.
