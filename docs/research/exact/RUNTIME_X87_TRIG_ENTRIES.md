# Scalar trigonometric entries and dispatch constants

Three scalar entries from pinned `87ctrig.obj` now have complete runtime-origin
proofs. The review also finds four entries omitted from the provisional
inventory. These additions recover inventory coverage, without adding function
source or exact acceptances.

| Entry | Address | Own bytes | Current claim |
| --- | --- | ---: | --- |
| `sin` | `0x004167C0` | 10 | Runtime origin proved |
| `cos` | `0x004167CA` | 7 | Runtime origin proved |
| `tan` | `0x004167D1` | 7 | Newly inventoried; runtime origin proved |
| `__CIsin` | `0x004167D8` | 10 | Newly inventoried; origin pending |
| `__CIcos` | `0x004167E2` | 7 | Newly inventoried; origin pending |
| `__CItan` | `0x004167E9` | 7 | Newly inventoried; origin pending |

Each external type-32 definition selects its operation record in **EDX** and
jumps. Cosine and tangent share the five-byte sine exit at `0x4167C5`. Their
complete scalar control-flow group is 24 bytes, with three DIR32 table bindings
and one REL32 to the already proved `__ctrandisp1` at `0x418B75`. All four
bindings come from complete preceding table/dispatcher proofs. Every byte of
the group matches, including the short backward jumps. The individual entry
spans do not count the shared exit again.

The intrinsic group also occupies 24 bytes and has its own shared exit at
`0x4167DD`. Its three table selectors and internal jumps match. The one external
relocation names `__cintrindisp1`; the original displacement points to
`0x4189CE`, whose complete body still lacks BSS authority. That observation
does not supply an accepted binding. All three intrinsic origins remain
unknown, and no complete 48-byte member comparison is claimed. Their named
definitions and observed instructions do establish the omitted inventory
entries. No ordinary C wrapper is substituted for their x87/register ABI.

The inventory becomes **524 independent entries plus 24 parent fragments**,
with 270 authored, 224 runtime, 21 compiler-generated and nine unknown origins.
Two old unknowns become runtime entries; the new intrinsic entries add three
unknowns. Another 60 independent entries lack source. Function source 464,
exact 376, exact code 76,908 bytes, attached metadata 244 bytes, candidates 88
and scoped semantic rows 249 remain unchanged.

## Complete readonly constant source

`runtime_x87_dispatch_constants.c/.h` restore the entire 48-byte readonly
section from `87cdisp.obj` as six typed binary64 values:

| Offset | Original label | Meaning | Actual x87 consumer |
| --- | --- | --- | --- |
| 0 | `DblMax` | Largest finite positive double | FCOMP at `0x418B01` |
| 8 | `DblMin` | Smallest positive normal double | FCOMP at `0x418AD3` |
| 16 | `IeeeAdjO` | Overflow scaling exponent, -1536 | FLD at `0x418AF1` |
| 24 | `IeeeAdjU` | Underflow scaling exponent, +1536 | FLD at `0x418AC3` |
| 32 | `_infinity` | Positive infinity | FMUL at `0x418B0D` |
| 40 | `_zero` | Positive zero | FMUL at `0x418ADF` |

The exponent values feed FSCALE. The minimum/maximum comparisons and subsequent
multiplications consume the other fields. Each original label has one qword
consumer and the recorded member symbol offset. Ordinary union-word
initializers preserve the IEEE representations, including infinity, and expose
their double values. The aggregate has no padding or pointer fields. Compile
assertions preserve all offsets and its 48-byte extent on each supported ABI.

The complete literal is unique in the original and independently places the
record at `0x420140`. VC4 emits exactly those 48 bytes in a readonly section
with zero relocations; native and i686 C90 compilation also pass with warnings
as errors. An initial header order exposed MinGW's existing errno declaration
conflict; placing the project header first resolves it. The corrected owner
is compiled once after that input change. Existing owners are reused.

The public data recipe is `config/runtime-x87-dispatch-constants.json`, separate
from the unchanged 480-byte descriptor family and the function exact ledger.
This is a standalone source owner outside CMake. It supplies neither the
dispatcher implementation nor its unresolved `LocalFac/intrinflag` storage.

Retained REA Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`
covers the entry instructions and constant consumers. The complete constant
data is compared directly between the pinned PE, original CRT member and new
source object; no new REA data observation is claimed. Private proofs, input
closures, initial failure, final compiler products and adoption receipt are in
`.analysis/trig-entries-dispatch-constants-20261016/`. No new provider, full
replay, runtime probe, final game build or play check runs at this checkpoint.
