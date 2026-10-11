# Complete CRT initialized objects and transcendental group

Seven complete initialized objects now have independent storage authority.
They unlock the complete 519-byte `87tran.obj` code and its 244-byte pointer
table. All nineteen code and twenty-eight data relocations agree with the
original. One imported entry, `0x41CDA1`, becomes runtime: 270 authored / 115
runtime / 42 compiler-generated / 101 unknown. Game source 283, semantic 247
and exact 188 / 35,003 code / 136 metadata remain unchanged.

## Complete object scope

The earlier 28-byte `fpinit.obj` observation independently locates its unique
nonrelocated 16-byte prefix at `0x423090`. Four actual external COFF definitions
occupy adjacent four-byte extents. The next definition starts at offset 16,
where the first pointer relocation also begins. Each selected object's complete
boundary is therefore known without granting authority to the entire section.
The full 12-byte `nlsdata1.obj` record is independently unique at `0x42387C`.

| Object | Address | Complete COFF extent |
| --- | --- | ---: |
| `__fltused` | `0x423090` | 4 |
| `__ldused` | `0x423094` | 4 |
| `___fastflag` | `0x423098` | 4 |
| `__adjust_fdiv` | `0x42309C` | 4 |
| `___mb_cur_max` | `0x42387C` | 4 |
| `___decimal_point` | `0x423880` | 4 |
| `___decimal_point_length` | `0x423884` | 4 |

These are complete COFF object extents, including any allocation padding; they
do not prove the original C declaration types or spelling. Initialized bytes
are `0x9875`, `0x9873`, zero and zero in the first group; one, ASCII dot with
zero padding, and one in the second. This describes initial storage, not a
runtime observation after locale or floating-point initialization.

The new maintained `scripts/crt_objects.py` requires at least three adjacent
complete four-byte external object extents, the exact actual symbol indices,
no missing or overlapping object, no relocation touching the group, and unique
nonzero initialized bytes across the original carrier. Full authenticated
Evidence bytes, including a retained superset if used, must agree with the PE.
The next actual definition or section end determines every object boundary.
Only listed object exports become authority. Static `.data`, unselected fields
and the three `__FPinit`/thread callback pointers remain excluded. The parent
`fpinit` section is still incomplete; the locale record covers its full section.

The main verifier records these as `initialized_object_groups`, separate from
whole data sections and their member-scoped definitions. A consumer receipt
identifies complete initialized object authority explicitly. Existing whole
section and small-string rules remain intact. A failed object group returns no
exports or acceptance report.

## Complete code and pointer table

The `87tran.obj` member at header offset 962694 has independent code placement
`0x41CC00` from a unique 73-byte nonrelocated run at offset 360. Its data base
`0x423EF0` independently follows the complete unique `_log2max` subobject at
offset 30, twenty bytes. Both whole sections close atomically using actual
member/index/storage/value identities, verified external code and the newly
proved `__adjust_fdiv` object. No observed relocation field supplies an address.
All table pointers and participating code bytes pass before publication.

The section contains the actual `__rtinfnpop`, `__rtinfnpopse`, `__fFLN`,
`__rtinfpop`, `__ffexpm1`, `__rtinfpopse` and `__fFEXP` definitions. Its data
includes the logarithm, power and exponential dispatch tables. The already
verified `__powhlp`/`__d_inttype` code and constants are reused unchanged.
A separate complete 89-byte `__cropzeros` body at `0x418DE0` binds both decimal
point relocations through the locale object. That entry is absent from the
imported inventory; retain its code provenance without inventing a function row.

Current maintained scope: 89 complete code sections / 14,669 disjoint bytes /
105 declared origin entries; 20 whole data sections / 3,330 bytes; seven complete
objects / 28 additional initialized bytes. There are 425 whole-section scoped
definitions, including 235 static definitions, plus seven separately scoped
object definitions. Every preceding 87-code-section/19-data-section result and
394 prior definitions survive unchanged. CRT provenance bytes remain separate
from game exact-code totals. Complete floating-point startup callbacks,
conversion-table/locale/BSS dependencies and full authored denominator remain
open.

## Verification and REA

One maintained positive and six negative controls pass. Controls reject missing
objects, a partial boundary, inclusion of an unverified pointer, a wrong actual
index, shifted placement and a changed retained carrier. Original library,
executable and Evidence stay fixed; the altered bytes are a separate negative
fixture. Failed cases publish no report and preserve the positive receipt.
The actual candidate-path receipt is retained; the published recipe is a
byte/hash-identical alias rather than an invented later validation run.

Code reuses complete original Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
The original 28-byte initialization carrier is reused:
`ev_a2f5d1c3fc5ef8319359d0881d566dc636ada695329883450840841b59790899`.
Two new closed REA 6.3 / Ghidra 12.1.4 sessions observe only missing storage:

- 12 bytes: `ev_b5bf61f78c4eecb0f1c01d471e91e46c88a67cfa311621b1d2b0a62f8e8c4119`,
  run `2026-10-11T05-36-42.465Z-requests-1784528`, 49,169.66 ms.
- 244 bytes: `ev_86e6cb7d19a108f9784a3a93e2ab193547dfcfc6258578eb1c0e07e753b3a3ce`,
  run `2026-10-11T05-42-20.681Z-coupled-requests-1791122`, 47,805.31 ms.

New retained carriers total 7,137 bytes for 256 original bytes. The configured
heap is 512 MiB; no measured peak RSS or model-token claim. Both native sessions
close, with snapshot counts 42 and 43 Evidence records. The second extent was
identified after the first session closed; no successful request was repeated.
No game source, compiler, product build or gameplay replay is needed. Current
four products remain those of the PCX packet-loop checkpoint.

Private proof: `.analysis/crt-locale-frontier/`; immutable checkpoint:
`.analysis/checkpoints/crt-initialized-objects-283-188/sha256.json`.
Feedback continues only in `/tmp/dxball_rea_feedback_20261010.md`.
Physical x87 behavior, unique original link selection/source spelling and
synchronized rendering/audio fidelity remain unproved.

Checkpoint preservation: 79 owned files and 291 explicit immutable dependencies
verify after fifteen scoped archive links replace 1,486,848 previously single-link
allocated bytes, about 1.4 MiB. No device-free-space delta is claimed. Current and
public paths retain independent archive inodes; unique Evidence, before inputs,
current products and probe objects remain. Cleanup is confined to this new seal.
