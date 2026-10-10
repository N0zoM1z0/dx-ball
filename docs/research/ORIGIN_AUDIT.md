# Bounded origin audit

The origin ledger now records **270 authored / 68 runtime / 42 compiler-generated /
148 unknown entries**. The latest origin batch resolves two further CRT entries through complete prior
code definitions and independently placed initialized data sections. Source presence remains **283** (270 authored,
one unknown-origin no-effect body and 12 runtime bodies); scoped semantic
acceptance remains **247 entries**, and exact acceptance is **185 complete
functions /32,688 code bytes plus 136 separate metadata bytes**. Earlier batches
below retain their own scopes and counts.

All 270 currently confirmed authored entries have maintained source. That
conditional result does not establish the full authored denominator or >=95%
complete source recovery. The remaining 148 unknown origins, provisional
boundaries, original type uncertainty and whole-game fidelity remain open.

## Complete CRT storage and prior definitions

The [storage checkpoint](CRT_DATA_DEFINITIONS.md) validates all 594 initialized
data bytes, both actual relocations and thirteen prior code definitions. Only
actual external COFF definitions supply new bindings. Independently established
anchors place zero storage; a unique complete array places the ctype section
before its full relocated bytes pass. Two new consumers match all 153 bytes.

The current verifier checks 54 code sections /6,026 bytes /55 code-origin rows,
two data sections /594 bytes, and three import jumps /18 bytes: 58 distinct
origin rows. Five actual-verifier negative controls pass. Game source, function
exactness, semantic scopes and production products are unchanged. Both new
provider sessions closed. Private proof `.analysis/crt-data-frontier/`; seal
`.analysis/checkpoints/crt-data-definitions-283-171/sha256.json`.

## Named imports and complete forwarding code

The verifier now binds selected COFF import references from the verified
original PE's DLL/name/IAT tuple. An IAT symbol binds the named cell itself;
a function symbol binds a complete six-byte indirect jump through that cell.
Neither address is copied from a candidate's inferred relocation. The entire
retained 39,136-byte observation is also compared with the pinned PE.

Five additional `libc.lib` code sections match all 1,048 bytes and thirteen
relocations. Independent imports resolve the otherwise identical Read/Write
candidates; their actual IAT operands differ.

| Original section | Complete bytes | Pinned COFF symbol | Named import dependency |
| --- | ---: | --- | --- |
| `0x418510` | 81 | `?_UnwindNestedFrames@@YGXPAUEHRegistrationNode@@PAUEHExceptionRecord@@@Z` | `RtlUnwind` forwarding code |
| `0x41E1D0` | 32 | `?_ValidateRead@@YAHPBXI@Z` | `IsBadReadPtr` IAT |
| `0x41E1F0` | 32 | `?_ValidateWrite@@YAHPAXI@Z` | `IsBadWritePtr` IAT |
| `0x41E210` | 27 | `?_ValidateExecute@@YAHP6GHXZ@Z` | `IsBadCodePtr` IAT |
| `0x419560` | 876 | `__raise_exc` | `RaiseException` IAT plus earlier verified floating-status helpers |

Three complete forwarding entries are separately classified as runtime imports:

| Entry | Bytes | Named PE import / IAT cell | Retained REA corroboration |
| --- | ---: | --- | --- |
| `0x416600` | 6 | `DDRAW.dll!DirectDrawCreate` /`0x44122C` | Complete six-byte read |
| `0x416606` | 6 | `DSOUND.dll!DirectSoundCreate` /`0x441230` | Sound dossier's unique callee/body, contiguous six-byte extent |
| `0x41FEE6` | 6 | `KERNEL32.dll!RtlUnwind` /`0x4412C4` | Complete CRT byte observation |

Each executable PE span must contain exactly `FF 25` and the named cell operand.
The DirectSound archive supplies identity and extent; the PE supplies its actual
six bytes. This differs from byte-read corroboration and remains explicit in the
report. Evidence IDs: DirectDraw
`ev_3597b5834cfe1492671d77296cc122baf817aaa5d4b565180b3d4735a12ee517`,
sound/callee `ev_0c19fd7b02df4709514364206dec7df270a537b02ffbdda25a57516fcd78ce1f`,
and CRT `ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
External namespaces remain separate from numeric PE addresses. The first reader
attempted to convert an unrelated `EXTERNAL:0x4d`; it stopped before acceptance
and is retained, then corrected to select only numeric PE callees.

That checkpoint verified 39 CRT code sections /5,327 bytes /40 section entry
rows, plus three forwarding entries /18 bytes: 43 distinct origin rows. Four
actual-verifier controls reject a wrong named cell, wrong DLL, Read/Write
substitution and a shifted SDK jump. All external COFF function-name sets are
checked independently against the selected member sections.

Only eight origin rows change; game source, 171 function exact acceptances,
247 semantic scopes and current products are unchanged. No compiler, provider,
SDK runtime or gameplay process was started. DLL implementation, asynchronous
fault/unwind behavior and unique original source/link selection are unproven.
Private proof `.analysis/import-origin-closure/`; immutable seal
`.analysis/checkpoints/import-origin-closure-283-171/sha256.json`.

## Verified cross-section CRT definitions

The verifier now makes an external symbol available to later sections only after
its defining section passes a complete byte comparison with every relocation.
Static symbols remain local to their COFF object. Conflicting established
addresses fail; later candidates and byte-derived diagnostic addresses never
supply bindings. The manifest orders dependencies before consumers.

Eight additional code sections match the same pinned `libc.lib` and retained
39,136-byte REA observation, Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
The observation also agrees with the verified original PE. Their complete
2,142 bytes and all 32 relocation operands are checked without masks.

| Section start | Complete bytes | COFF external symbol | Earlier verified dependencies |
| --- | ---: | --- | --- |
| `0x41D150` | 99 | `__IncMan` | `___addl` |
| `0x41E5F0` | 102 | `___add_12` | `___addl` |
| `0x41F990` | 678 | `___ld12mul` | `___addl`, `___shl_12`, `___shr_12` |
| `0x41F8E0` | 162 | `__fpclass` | `__sptype` |
| `0x419D90` | 238 | `__decomp` | `__set_exp` |
| `0x41D1C0` | 172 | `__RoundMan` | `__ZeroTail`, `__IncMan` |
| `0x41E6E0` | 232 | `___mtold12` | `___shl_12`, `___add_12` |
| `0x41D370` | 459 | `__ld12cvt` | `__IsZeroMan`, `__FillZeroMan`, `__CopyMan`, `__RoundMan`, `__ShrMan` |

The preceding manifest verified 34 complete sections /4,279 bytes /35 imported
entry rows. The eight new rows move from unknown origin to runtime dependency;
this does not recover additional game source or create function exactness.
Independent negative controls reject a consumer placed before its unverified
export, a section shifted one byte and a forged conflicting export address.
No compiler, provider or gameplay process was started; production products,
semantic scopes and function acceptance receipts are unchanged.

Private receipts, controls and the dependency projection are retained in
`.analysis/origin-closure/`; the immutable seal is
`.analysis/checkpoints/origin-closure-283-171/sha256.json`.
Repeat the bounded origin check with
`scripts/repo-python scripts/verify-runtime-origin-sections.py`.
Candidate discovery remains diagnostic; aliases with conflicting placements
are not added to the binding map. Original library selection, source spelling,
unknown-entry ownership and whole-game fidelity remain unresolved.

## Earlier complete CRT sections

[The section manifest](../../config/runtime-origin-sections.json) originally selected 26 complete
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

[The generated-entry manifest](../../config/generated-raster-origins.json) records
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
