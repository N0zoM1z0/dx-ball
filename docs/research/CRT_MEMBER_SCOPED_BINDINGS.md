# CRT bindings within a verified archive member

Four additional unknown entries are proved to be complete pinned VC4 CRT code
sections. Resolving actual COFF symbol indices within their own archive members
closes their dependencies without publishing object-local names globally.

| Original entry | Library definition | Complete bytes | Relocations |
| --- | --- | ---: | ---: |
| `0x0041BEF0` | `__ismbblead` | 18 | 1 |
| `0x0041CF30` | `__control87` | 63 | 2 |
| `0x0041CF70` | `__controlfp` | 24 | 1 |
| `0x00418BE0` | `__setdefaultprecision` | 19 | 1 |

All 124 bytes and all five relocations match the original complete byte
observation. Origins become 270 authored / 83 runtime / 42 compiler-generated /
133 unknown. Source-present 283, scoped semantic 247, and game exact 186 /
33,001 code bytes / 136 metadata bytes remain unchanged. This proves dependencies;
it does not recover additional game source or establish a complete authored
denominator.

## Bind definitions by their actual identity

`scripts/crt_scope.py` keys verified definitions by archive member offset and
SHA-256, then by the actual COFF symbol-table index. Each stored definition
retains section, storage, value, type, name and proved section address. A later
relocation must agree with that same member's actual symbol definition.

The helper follows the real relocation-table symbol index. Its temporary
relocation map uses index identities rather than symbol names, so repeated
section/static names cannot overwrite one another. Static storage-class-3
definitions cannot resolve through the shared external name map, even when
that map contains the same name and address. External storage-class-2 bindings
retain their existing independent authority and conflict checks.

Only after every byte and relocation in a complete section passes does the
maintained verifier publish that section's member-scoped definitions. Already
verified prior definition sections and independently placed data sections
provide the initial scoped authority. The section being compared can resolve
its own actual definitions; an unverified section in the same object cannot
provide another section's address.

Names are retained for reporting, with actual symbol indices and same-member
authority alongside them. A name-only report that would hide conflicting
actual-index bindings fails closed. No source, target or library payload is
modified to make these bindings agree.

## Concrete closure

- `ismbbyte.obj` calls its already verified `_x_ismbbtype` through actual COFF
  symbol index 60, storage 3, section 23, at `0x0041BF10`. This proves the
  complete `__ismbblead` section.
- `ieee87.obj` calls its previously complete `__abstract_cw` and `__hw_cw`
  definitions at `0x0041CF90` and `0x0041D040`, actual indices 31 and 36,
  storage 3, sections 11 and 13. This proves `__control87`.
- The same member then binds `__control87` through actual index 14,
  storage 2, section 5. This proves `__controlfp`.
- `fp8.obj` uses the fully verified external `__controlfp` binding to prove
  `__setdefaultprecision`. This external dependency is distinct from a static
  name borrowed from another member.

Discovery parses 615 actual COFF members. Its first round finds two complete
unique matches, the next two rounds find one each, and the final round finds
none. Later rounds use only definitions whose entire preceding section already
matches. Discovery is followed by the maintained verifier; its report, rather
than a scanner similarity result, grounds the four origin changes.

## Verification and retained scope

The first maintained run with member-index binding preserves all previous
65 complete code sections / 7,229 bytes and all existing binding values. A
second unchanged run occurs because an overly strict review compares two
equivalent hexadecimal address spellings and the command sequence continues
after that guard fails. Both actual receipts are retained; neither is described
as a new candidate verification or lost-process recovery.

The final maintained run accepts 69 complete code sections / 7,353 bytes and
73 distinct origin rows, including three import forwarders. Three initialized
sections / 1,130 bytes and two independently verified ABS constants retain
their preceding scope. Its 180 member-scoped definitions include 95 static
definitions; these counts are symbol metadata, not function or source counts.

Eleven controls use genuine unchanged member data and original payloads:
six helper controls reject a different member offset/hash, a static name in the
global map, a different actual symbol index, a changed definition value and a
changed definition name. Five complete-verifier controls reject a missing
static owner, callers before their verified static/control owners, a partial
caller section and shifted owner code. Each full-verifier rejection produces
no acceptance report.

Reused original code Evidence:
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
Its target digest and complete 39,136-byte range are fixed by the prior receipt.
No new REA provider, compiler, game replay or physical-runtime observation
occurs. Baseline inputs whose mutable probes were deliberately removed resolve
to their individually hash-verified immutable copies. Current game source,
tests, 36 game objects and four products retain the preceding identities.

Private `.analysis/crt-member-scope/` retains before-state, actual stage inputs,
discovery rounds, full reports, controls and final review. Immutable seal:
`.analysis/checkpoints/crt-member-scope-283-186/sha256.json`.
REA performance, context and usability observations remain appended only to
the existing single `/tmp` feedback document.

Remaining BSS, pointer-bearing data and unverified same-object sections are not
located by symbol spelling or resemblance. The complete original authored
denominator, source declarations, whole-campaign rendering and hardware audio
remain unproved.
