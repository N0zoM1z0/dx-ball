# Resource drawing wrapper ownership

The later [six Blt-coordinate sums](BLT_COORDINATE_WRAP.md) preserve this ownership
and all public APIs,while promoting plain Blt195exact and explicitly demoting
stretch139exact→141/94 and unchanged capture852exact→864/726. Their complete
instruction correspondences and six finite/120 unchanged calls pass. Current
totals become392 exacts/247 authored exacts/23 candidates. The dated owner
chronology below retains its own source context and comparison results.

The October 17 fixed two-owner model moves the unchanged rotated-sprite drawing
adapter from `rotation.cpp` to the resource drawing adapters in `resources.cpp`.
It restores three exact functions and explicitly demotes two prior exacts:

| Unit | Before size / differences | Current size / original / differences |
| --- | ---: | ---: |
| Vertical rotation offset | 193 / 159 | 191 / 191 / 0 |
| Draw keyed sprite | 107 / 94 | 105 / 105 / 0 |
| Stretch keyed sprite | 141 / 92 | 139 / 139 / 0 |
| Draw sprite | 105 / 0 | 107 / 105 / 94 |
| Blt sprite | 195 / 0 | 199 / 195 / 173 |
| Load sprite bank | 1486 / 945 | 1475 / 1475 / 66 |
| Load PCX | 979 / 850 | 979 / 862 / 851 |

The family is adopted together: net **one exact / 135 code bytes**, giving
**394 exact functions / 84,872 code bytes / 244 attached metadata bytes**.
Classified authored functions become **249 exact and 21 complete candidates**.
Load-bank and PCX remain candidates. Sixteen other complete functions preserve
their resolved code identities, including the renderer's current digest. Moving
the exact 40-byte drawing adapter does not change its complete code identity.

## Source basis and complete comparison

The adapter only reorders `(slot, x, y, angle)` into the renderer's arguments.
It consumes no private rotation mathematical state. The original renderer and
four mathematical helpers are contiguous at `0x4026a0..0x40306e`; the adapter
at `0x404280` instead lies between resource stretch and capture entries. This
supports one ordinary ownership model, not unique recovery of the original
translation unit. Current source contains no other caller of the adapter to
strengthen that ownership inference.

Only that definition moves, unchanged, into the existing drawing-adapter group.
No other definition moves. `resources.cpp` consumes the complete `rotation.h`
after its existing resource header, with the C linkage used by the shared API.
Public declarations, every other body and all data definitions remain unchanged.
There is no selective header view, alternate implementation or subsequent
position, name, count or flag search.

One compile per owner compares all 23 complete functions: five rotation and
18 resource entries after the move. Every one of the 377 actual bindings and
31 literal references is checked, including actual addend-four accesses and
complete owned initialized containers. Local/public targets cannot be rebound
to hide changed instructions. Independent review confirms the reverse source
transformation, full mapping and both gains and losses.

## Observed compiler decision

The [backend investigation](VC4_EXPRESSION_ORDERING.md) identified the actual
rank/swap helpers. One unchanged current rotation recipe was then observed under
Win32 `DEBUG_PROCESS`, with a temporary breakpoint at the pinned C2 helper entry.
The six complete emitted bodies and actual relocations match the preceding
baseline exactly. The trace records 290 real calls under the existing `/Od`
recipe, including bank, slot and renderer comparison inputs.

The baseline parameter-key group corresponding to y-offset has scaled bank/slot
ranks **93/94** and slot key **28256**; the established unsigned comparison
therefore selects a swap. The other three projection groups have lower slot
ranks and preserve bank-first order. That first capture's function grouping is
inferred from source/COFF order and expression records; it lacks an explicit
current-function field. Its word reader also substitutes zero on failed reads,
so zero-valued fields have no independent validity flag. The nonzero bank/slot
observations are not zero substitutions.

The improved observer records the selected function record from C2 global
`0x481734`, supported by retained driver Evidence
`ev_e6737a579cb9c6b4a816506a7259faf0704e8139c145118b88ff23cedf839bb7`.
It counts mandatory read failures and fails rather than accepting a partial
record. The proposed rotation/resource traces contain **290/1170 calls**, zero
mandatory read failures and no unavailable captured nodes or missing attributes.
They directly name y-offset's bank/slot inputs **93/74**, with slot key **28251**.
Keyed/stretch pairs are 75/84; the two demoted functions have 86/84 and 85/84.
These decisions agree with the observed current output. All three compiler
process trees exit normally. Captures stop at tree depth five; swap direction
is inferred from captured inputs and the established helper, not sampled after
return. The observations do not recover original-game keys or compiler settings.

## Validation and retention

Native and MinGW reuse their valid CMake configurations and compile only the two
changed owners, with serial links. The existing rotation Oracle retains its
1,024 cases and 151 complete guarded buffers. The moved wrapper keeps its
original **344** semantic cases and unchanged scope. Its unit-specific oracle
and target-oracle overrides preserve the actual rotation test files after the
physical source owner changes. Owner-header and complete input identities are
updated explicitly; no semantic case count or scope is broadened.

Private evidence lives under `.analysis/rotation-backend-ranks-20261017/`, with
complete two-owner comparisons and traces in `resource-wrapper-owner/`.
The initial summary driver completed both compiles and all comparisons before
using a nonexistent `compiled_size` report field. The summary was recovered
from those retained records using `object_size`; no compile or comparison was
repeated. The existing1,869 resource calls and24 retained original/native/full-relocated
VC4 helper observations also pass:2,917 selected calls in all. The VC4 relink
reuses116 objects and the same19 approved CRT members, with no new compiles.
All1,097 distinct MAP names/1,099 owner-qualified records retain their addresses.
Twelve retained functions per image pass complete linked-code/binding/constant
checks; eleven selected functions per image are discarded by OPT:REF. The
complete166,400-byte PE differs at1,205 bytes, confined to changed mapped resource
functions/their verified CC padding, six parsed timestamps and the loader table.
Its4,488 loader entries are checked against actual COFF fields:49 RVAs leave and
49 enter, with all other relocation semantics preserved. The first image bound
stopped because it omitted those table changes; the corrected check establishes
the complete typed table semantics before accepting its encoded bytes. No build,
link or behavior check is repeated for that correction.

Current executable SHA-256 is
`c8f4db718c15c9ee9b2cedfdc2287b3553cb16ed84dad439b662a614659415c5`.
All377 unaffected exact rows and75 unaffected candidate rows retain their full
results; all249 semantic scopes, case counts and oracle identities are unchanged.
No full replay or game campaign is used for this model.

Cleanup archives and member-hash verifies44 closed input/product/result carriers,
then removes their raw copies, including unused private observer executables and
three duplicate delivery-history members. Unique bytes remain in
`closed-inputs-products.tar.gz`, indexed by `cleanup.json`; extraction restores
their original repository-relative paths. Net released allocation is8,146,944
bytes (about7.77 MiB), after archive/receipt costs and inode-link accounting.
Current matching/delivery objects, tested products, direct runtime traces and
valid Native/MinGW CMake configurations remain retained.
