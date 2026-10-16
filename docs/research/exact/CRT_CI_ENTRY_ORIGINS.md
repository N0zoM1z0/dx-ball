# Complete CRT intrinsic-entry origins

Thirteen entries previously classified as unknown now have runtime-origin
proofs. The complete original code groups, all 44 actual relocations and their
data owners agree with the pinned VC4 CRT members. No function source, exact
acceptance, semantic case or ABI declaration is added.

| Original member | Full code bytes | Newly classified runtime entries |
| --- | ---: | --- |
| `87ctrig.obj` | 48 | `__CIsin`, `__CIcos`, `__CItan` |
| `87ctriga.obj` | 68 | `__CIasin`, `__CIacos`, `__CIatan`, `__CIatan2` |
| `87csqrt.obj` | 20 | `__CIsqrt` |
| `87cdisp.obj` | 589 | `__cintrindisp2`, `__cintrindisp1`, `__ctrandisp2`, internal entries `0x418A3E` and `0x418A45` |
| Total | 725 | 13 |

The four groups cover 23 existing inventory entries without overlap. The
previously runtime-labelled atan2 also receives its first complete receipt in
this audit. The nineteen approved original CRT members remain unchanged.

## Binding and storage evidence

The independently proved 44-byte `__ctrandisp1` and 60-byte `__fload` place their
containing dispatcher section at `0x418990`. Every byte outside the twenty
relocation fields agrees across its complete 589 bytes. External bindings use
the existing complete `__trandisp1/2` member definitions, exception-bridge entry
and matherr-flag binding, and independently matched fastflag initialized object.

The entire 48-byte readonly section is unique at `0x420140`. A new REA 6.5.0 read
confirms every byte, including the six binary64 constants already represented
by the maintained standalone data owner. This supplies the independent data
placement for all six constant operands; no source-data count changes.

The remaining two private symbols occupy the original member's nine-byte BSS:
`LocalFac` at `0x43FB00` and `intrinflag` at `0x43FB08`. Their placement is inferred
from six consistent relocation operands, the COFF offsets 0/8, and the actual
LocalFac+6 use. All nine bytes lie in the PE's writable virtual tail, beyond
file-backed data. This is a relocation-derived storage placement, not a claim
of independently observed source types or live values. No zero-byte search,
invented symbol cell or source implementation supplies this binding.

With those explicit mappings, the whole dispatcher matches every relocation
and byte. Its public function definitions then supply independent destinations
for the intrinsic wrappers. Selector addresses come from the already proved
trig, arctrig and sqrt data owners. All four complete sections match; short
shared exits retain their actual instruction spans.

## Entry boundaries and remaining claims

Fresh procedure information confirms contiguous spans of 58 bytes at
`0x418A04`, seven at `0x418A3E`, and 304 at `0x418A45`. Two decoded calls target
each internal entry. The seven-byte flag-clear entry falls through into the
shared dispatcher. These are existing inventory entries, not newly counted
public COFF definitions. Their original names and machine interfaces remain
unrecovered; inferred Ghidra C prototypes are not adopted.

The no-source inventory remains 78: **77 runtime and one compiler-generated**.
This origin closure reached 73 complete original comparison receipts, up from
59. Five older runtime labels still had only region associations in that index:
`0x418570`, `0x4185B0`, `0x418620`, `0x418650` and `0x418730`. They are not silently
promoted to complete comparisons by this origin audit. The later
[receipt reconciliation](CRT_DEPENDENCY_INVENTORY.md#complete-receipt-coverage)
validates their existing complete proofs and brings current coverage to78/78,
without repeating a compiler, provider or runtime.

Overall origins are **270 authored / 261 runtime / 21 compiler-generated /
one unknown**. The unknown is source-present no-op `0x40CC20`; its origin stays
unclassified. All 270 currently authored entries have source, with 236 exact
and 34 complete candidates. Neither this bounded inventory nor CRT matching
proves a final authored denominator or absence of undiscovered entries.

Source remains 475, exact 380 and complete candidates 95. Source, objects, linked
image, exact/candidate reports, implementation and semantic ledgers remain
unchanged. The image remains
`345a68875bad0693476c55fcd69f41c5a9b158fc96e1f3e4f3189358001d3f14`.

## Evidence and resource scope

Complete original code reuses REA Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
The new constant read is
`ev_39f9d623b52c13381768fdcc0b885373516875e8d9cfef5caac51d2cecd672c3`;
entry-boundary observations are
`ev_ad749c1c19caa3fe0ffe31cf80da15b62e3d71ee2043a0e2c8dac9bb18b3b074`,
`ev_6e7da0d8ebef218790ced1d5c9ba9ce7b2b198a623413505162713a7bc970b52`
and `ev_287a579fce391382971643ff1409cb0c1d801876e817bdbeb3547ca305aaa008`.
Private `.analysis/crt-ci-entry-origins-20261017/` retains complete proofs,
authority records, coverage, before ledgers and publication verification.

The cached provenance's 121 input identities verify; its full library scan is
not repeated. One serial REA session performs one 48-byte read and three entry
queries, then closes. CPU stays capped at 35%, memory high 640 MiB / maximum 768 MiB,
with Ghidra heap 256 MiB. No runtime, relink, full replay or compiler follows this
origin audit. A separate scan-local compilation is rejected at 990→991,
as recorded in the [last-brick note](LIGHTNING_EXPIRY_SCOPE.md#closed-scan-only-scope).
