# Runtime sections with established bindings

Eight formerly unknown entries match complete sections of the pinned VC4
`libc.lib`, including every actual relocation and any embedded data. The
existing 39,136-byte original REA observation supplies all target bytes.
No provider, compiler or game runtime invocation is needed.

Origins now comprise 270 authored, 76 runtime, 42 compiler-generated and 140
unknown entries. Source presence 283, scoped semantic acceptance 247 and exact
acceptance 185 functions /32,688 code bytes plus 136 metadata bytes are unchanged.
The full authored denominator and whole-game fidelity remain unproved.

| Original section | Complete bytes | Actual COFF name | Visibility |
| --- | ---: | --- | --- |
| `0x41AC40` | 44 | `_strncnt` | Object-local |
| `0x41BBE0` | 33 | `?AdjustPointer@@YAPAXPAXABUPMD@@@Z` | Object-local |
| `0x41C680` | 95 | `_CPtoLCID` | Object-local |
| `0x41CF90` | 161 | `__abstract_cw` | Object-local |
| `0x41D040` | 141 | `__hw_cw` | Object-local |
| `0x41FDE0` | 21 | `__msize` | External |
| `0x41F7E0` | 121 | `__onexit` | External |
| `0x41F860` | 19 | `_atexit` | External |

The first five names have COFF storage class 3. Matching them does not publish
external bindings for other members. Two members supply byte-identical
`_strncnt` sections; both alternatives remain declared without claiming unique
original selection. The imported `_CPtoLCID` function extent is 56 bytes, while
its whole section is 95. Every section byte is compared; the imported boundary
stays separate. This is runtime provenance, not new function-extent or exact
acceptance.

## Independent imports and ordered definitions

Initial discovery uses 94 grounded bindings from the reviewed prior CRT map,
named imports, fully verified definitions, independently placed data and
external definitions of previously accepted sections. Five complete sections
pass without introducing a new external dependency.

The unresolved dependency inventory then identifies 37 additional archive
imports uniquely named in the original PE. The maintained verifier checks
DLL/name, COFF import spelling and the actual IAT cell for each. It does not
infer their addresses from an unmatched code operand. Those bindings establish
`KERNEL32.dll!HeapSize` for the complete `__msize` section. Only after that
section passes does its actual external definition supply a binding to
`__onexit`; its accepted definition then grounds `_atexit`. Each consumer is
compared completely, in that order. Source names and alternate original link
selection remain unproved.

The final bounded scan uses 134 established bindings and finds no further
complete sections. Static names remain object-local; unresolved BSS and calls
stay unresolved. Same-member definitions in other sections require explicit
namespace-aware provenance before reuse. Failure to match does not establish
an authored origin or complete the remaining origin audit.

## Verification and preservation

The retained inventory initially rejects 31 missing disposable extracted
objects after cleanup. The maintained verifier re-extracts their exact members
from the hash-verified library and checks all prior bytes before discovery.
Their hashes agree with the preceding receipt. These are regenerated members,
without compilation or a replacement analysis session.

Final acceptance checks 62 complete code sections /6,661 section bytes /63
code-origin rows, two independently placed data sections /594 bytes and three
forwarding entries /18 bytes: 66 distinct origin rows. The preceding 54 sections
remain accepted. Eight additions account for 635 section bytes. These provenance
figures are separate from the game's exact-code totals. Every actual compile
and analysis claim retains its own evidence; no gameplay suite is rerun.

Original bytes are bound to Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`
and SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
Origin updates use atomic replacement. Game source, fixtures, semantic/exact
acceptance ledgers and production products remain unchanged; all 185 current
exact identities and product hashes are checked independently.

Private proof: `.analysis/window-message-topology/`; immutable seal:
`.analysis/checkpoints/window-runtime-origins-283-185/sha256.json`.
Repeat acceptance with
`scripts/repo-python scripts/verify-runtime-origin-sections.py`.
