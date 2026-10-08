# Dependencies reached from maintained functions

The [eight-entry runtime allocator](ALLOCATOR_OWNER.md) is now maintained and
connected to the shared defaults. Current totals are **243 source-present
entries / 111,242 direct cases / 35 exact units / 3,379 bytes**, with 15 runtime
origins identified and 278 unknown. The inventory and private draft stages
below describe their earlier checkpoints; they retain their original hashes,
coverage and limits. Full frame failure ownership and remaining CRT helpers
are still open.


A bounded review of saved REA `analyze_function` records identifies the next
supporting contracts to inspect after the connected gameplay owners. It reuses
closed, target-matching Ghidra records; no new binary query or provider import
was needed. This is a static dependency inventory, not additional function
acceptance or observed runtime coverage.

The review retains 193 Evidence records covering **187 of 235 maintained
entries**. Their callee lists reach **33 unmaintained imported entries**:
23 still have unknown origins, and ten now have runtime classifications.
Those are copied ledger labels, not classifications inferred by this review.
Thirty dossiers exceed its 2 MiB per-record read boundary, and four are in runs
without a close record; all are excluded. Thus the other 48 maintained entries
and unrepresented computed/indirect calls remain outside this inventory.
External address namespaces such as `EXTERNAL:0x4f` stay separate from numeric
PE addresses.

The most frequently referenced targets in this bounded set are:

| Target | Saved candidate name | Distinct maintained callers | Provisional bytes |
| --- | --- | ---: | ---: |
| `0x00417910` | `FUN_00417910` | 9 | 18 |
| `0x00416760` | `FUN_00416760` | 9 | 14 |
| `0x0041678C` | `__ftol` | 8 | 39 |
| `0x00416770` | `FUN_00416770` | 7 | 16 |
| `0x00417DF0` | `FUN_00417df0` | 6 | 119 |
| `0x00417C40` | `_memset` | 6 | 88 |
| `0x004177F0` | `FUN_004177f0` | 6 | 7 |
| `0x0041F570` | `__ultoa` | 4 | 30 |

Names and sizes come from the existing imported inventory. A familiar library
name, a short wrapper or its location in the image does not establish its
implementation, provenance or reviewed extent.

For example, saved rebound Evidence
`ev_6055fe1d318fa3f71d76b5cdbbbe862a3944dd9890035a53264b8ccfa2d7a074`
and paddle-rendering Evidence
`ev_0b4d5d681d951be5b6a69ac1d9d09db3cc965811c767e0b2b4f7296609cc020a`
both list `0x0041678C`. Their caller contracts and compiler comparisons do not
accept that helper's body. Saved brick-effect constructor Evidence
`ev_6a32fd651ca3a7fb5d9cfda71f66a09b545b0a7baf59e584310935a7953e64af`
lists allocation entry `0x00416770`. The removal entry at `0x00412A50`, Evidence
`ev_15590b4df69e7901145c02e294dca11e8f4f9c5be7675b3a332149d8dddde90e`,
lists release entry `0x00416760`.
The [gameplay owner](GAMEPLAY_OWNER.md#linked-list-layout-and-dependencies)
already distinguishes its default host allocator from the original allocator
and new-handler behavior. Mapping an append call relocation does not recover
that dependency.

The next focused review should reconcile these supporting entries' instructions,
ABI, callees and failure paths through REA before proposing source or an origin
classification. Compiler/library attribution needs its own corroboration;
forwarding to a host service remains a bridge. Independent unused graphics
leaves can follow the dependencies needed by the connected game.

The private inventory `.analysis/maintained-call-frontier.json` binds the
current function/origin ledgers, its producer and each retained Evidence file
by SHA-256. It preserves the excluded-record list and per-target caller
references, so a later pass can expand the boundary without repeating the
existing queries. At that inventory checkpoint, the accepted totals were **235 maintained / 109,805 direct
cases / 36 exact units / 3,518 bytes**, with 279 unknown origins and 14 identified
runtime entries.

## Focused REA instruction review

A subsequent sequential REA `analyze_function` batch inspects five selected
entries with the pinned Ghidra provider. The complete dossiers and closed
session are retained. This supplies instruction contracts, not semantic
acceptance or a compiler/library attribution.

| Entry | Observed contract | REA Evidence |
| --- | --- | --- |
| `0x0041678C` | Convert x87 ST0 to signed 64-bit integer, temporarily selecting truncation toward zero; restore control word and return EDX:EAX | `ev_3a0b896bedfb7224268a3a8d3bfcb8d1acc636a35884319167561b64e8056aea` |
| `0x00416760` | Forward one stack argument to `0x00417750`; caller cleanup | `ev_dd4c8eb171fe4da4755816c3387814ad47a13e806c38958c44aa8cbc190e44ac` |
| `0x00416770` | Forward size and constant `1` to `0x00417790`; preserve returned EAX | `ev_2f47da62f234bfb025db282149258ce5cb1b53a74591f045695579a7d8887f91` |
| `0x00417910` | Forward argument and two zero constants to `0x00417950`; preserve returned EAX | `ev_df594328fa0899467c7969112f2ca49e255c91e1d3fb81b92b74f5e60db13234` |
| `0x00417DF0` | Return byte distance to the first zero byte; scan prefix to four-byte alignment, then aligned words | `ev_2771927e99efdb9e148301e8bf8aac67206ddd30c00c25219f34783b1586cd01` |

All five observed bodies are contiguous and match their imported sizes:
39/14/16/18/119 bytes. This reconciliation alone does not create an exact unit.

The floating conversion illustrates why the instruction evidence matters:
Ghidra's pseudocode says `ROUND`, but `OR AH, 0xc` selects x87 truncation
before `FISTP`. Likewise, the allocation wrapper's inferred `void` result
omits EAX forwarding, and the string scanner's inferred pointer result is an
integer byte distance. Neither inferred signature should be copied into C.
The scanner can read beyond a terminator within its aligned word; inaccessible
backing and exceptional floating conversions need explicit boundaries.

Existing closed REA dossiers supply two downstream contracts without another
query. Release at `0x00417750`, Evidence
`ev_71abe55c26ab63d390b070c27874d920fa335c74cc9b406dcdab748a7f3bdd33`,
skips a null pointer and otherwise calls `HeapFree` with heap `0x00440D70` and
zero flags. Allocation at `0x00417790`, Evidence
`ev_5b84dc43a44b86e3cd73f1ebfddc73bdb1f4ef29d11181f1d56181f54cc327b4`,
rejects unsigned sizes above `0xFFFFFFE0`, changes zero to one, and retries
allocation only when its handler flag and the handler result permit it.
The `0x00417950` backend and the allocation/handler dependencies need focused
review or matching saved evidence before any implementation acceptance.
Host allocation, release or string services remain dependency bridges until
the original implementations are separately recovered and validated. Names,
Ghidra's library match and these wrapper shapes do not establish a particular
VC4 library object. The subsequent [whole-object comparison](CRT_PROVENANCE.md)
provides that additional corroboration and identifies eight further runtime
entries. Its three new dossiers also resolve the HeapAlloc/new-handler and
`0x00417950` termination contracts. The latter is `doexit`; the `0x00417910`
wrapper is C `exit`. The inventory is refreshed against those origin labels and the three
subsequently maintained [sound controls](SOUND_CONTROLS.md). Their closed
dossiers added three covered entries. The later [core queue batch](CORE_QUEUES.md)
adds ten covered entries from eleven distinct matching dossiers; eight former
frontier targets now have independent semantic acceptance, leaving 33 targets.
The original excluded-record boundary remains the same. Exact counts are unchanged.

## Next connected allocation batch

The next implementation priority is the original new/delete, heap allocation,
handler and release chain. Current [allocation](../src/gameplay.c) and
[release](../src/effects.c) defaults forward to host `malloc/free`. Seven
maintained allocation callers and nine release callers reach these entries in
the bounded saved frontier, including ball, projectile, fire, particle, bonus
and MIDI owners. Their accepted consumer behavior leaves the original
allocator's failure and retry rules outside the implementation boundary.

Six closed REA dossiers already cover the proposed batch: `0x00416760`
(delete), `0x00416770` (new), `0x00417750` (free), `0x00417790`
(handler-controlled allocation), `0x004177D0` (HeapAlloc forwarding), and
`0x00419EA0` (handler invocation), totaling 172 reviewed instruction bytes.
The records cited above and in [runtime provenance](CRT_PROVENANCE.md) can be
reused without another function query. These are observed contracts;
maintained implementation and configured semantic/exact acceptance remain
pending. The private controlled-API comparison below has now executed.

| Required proof | Original behavior to preserve |
| --- | --- |
| Size boundaries | Zero becomes one; unsigned requests above `0xFFFFFFE0` return null without allocating or invoking a handler. |
| Failure and retries | Retry only when enabled and the handler returns nonzero; normalize positive and negative nonzero handler results to one. Fixtures must terminate without imposing a production retry limit. |
| Callback mutation | Reload the handler on invocation and the heap on allocation; callbacks can replace/remove the handler or change the heap between retries. |
| Release and ABI | Null skips HeapFree; nonnull forwards the current heap, zero flags and pointer. New/handler calls use cdecl; HeapAlloc/HeapFree use stdcall on i686. Free/delete have a void return contract. |
| Connected ownership | Execute append/remove/retirement through the complete original chain; compare typed roots, cursor effects, untouched payload, ordered calls and poisoned freed storage. |

The oracle must execute the six original bodies with only physical heap APIs
and controlled handler callbacks as declared boundaries. The focused producer
review below identifies heap initialization; teardown, handler registration
and indirect or aliased writes remain separate obligations. Shared
defaults must preserve allocation/release ownership across every affected
family; host allocations cannot be released through a different private heap.
The malloc/newmode wrapper at `0x00417770` is outside this six-entry proposal.

A bounded search of the same 268 saved REA dossiers finds the three direct
heap/handler readers above, but establishes no initialization or registration
producer. It also finds non-primary Ghidra WRITE references from editor entry
`0x0040C3B0` to `0x0043FB13`, labelled `DAT_0043fb10+3`. Saved Evidence
`ev_12f27f7831f215d80c2a1a27d88e1638ffa9ab2fd568793f66258b328927431e`
shows indexed board-byte writes at `0x0040C577` and `0x0040C6F3`, based at
`0x0043F8F8`. Those inferred reference labels alone cannot establish a handler
mutation. Producer selection must inspect the original operand and reference
provenance; this saved subset does not prove an exhaustive absence of writers.

A separate saved-record search inspected 268 dossiers for eight remaining
application candidates. It recovered the palette-load variant at `0x00409A30`
but found no represented caller edge to those eight candidates. Thirty-one
large records were searched in full, correcting an earlier smaller boundary
that missed its 829,684-byte dossier. Missing dossiers, indirect calls and
provisional extents still prevent describing these candidates as unused.
This review prioritizes a represented core dependency, without assigning
runtime origin from image location or changing the acceptance ledgers.

The private `allocator-next-batch-review-235-36` checkpoint retains the audit,
reviewed source/documents and 271 external evidence identities. Verification
checks target identity, all six instruction lists and extents,
the saved caller edges, current owner/exact products and unchanged frozen
campaign inputs. No new binary query, build, differential case or exact unit
is claimed by this historical review.

## Executed allocator draft

After the original campaign stops and its capture is sealed, an isolated C
draft passes **624 original-entry fixtures**, **210 connected node fixtures**,
**45 ball-retirement fixtures**, and two separate native pointer controls.
The seven node families cover ball, bonus, effect, explosion, particle,
projectile and fire ownership. The original allocator bodies and their internal
calls execute unchanged; only HeapAlloc/HeapFree and controlled handler
callbacks form the external boundary. Comparisons check queue roots/cursors,
payloads, ordered callbacks, heap pairing and poisoned released storage.
The draft's compiled source, product, 410 execution-input identities and
independent reviews are retained in `allocator-first-execution-235-36`.

These are private draft results. Shared production defaults, MIDI/resource
ownership, terminal exits and complete frame paths remain pending. Subsequent
isolated initializer/malloc, i686 and SDK checks are recorded below. They add
no maintained function, accepted direct case or exact unit to published ledgers.

## Heap initialization and malloc mode

Focused REA `xrefs`, `inspect_native_instruction` and `analyze_function` calls
identify the actual heap producer at `0x00419E80`, a 21-byte initializer.
Evidence `ev_10ce1eaed90f0753871a24f6fad805895e13fb1cbf155903597f6e751ae3cd91`
shows `HeapCreate(1, 0x1000, 0)` followed by an unconditional store of its
handle, including null on failure, into `0x00440D70`. Startup calls it at
`0x00418801` and does not inspect that call's EAX before subsequent calls
(`ev_d4cdbb3cea74cf5ff8ce35743dcfa01fdcd54a492152e16462402ddb2f6429c8`).
This establishes a private-heap initializer; its physical lifecycle still needs
implementation and connected execution.

The 20-byte malloc wrapper at `0x00417770` reads `0x004234D4` and forwards
that current mode and the requested size to `0x00417790`, retaining its pointer
in EAX. Evidence
`ev_bab5314682949a397f2c04f0c60c4d9c0e5c760c6d5adaf4a98355d823f22354`
preserves the instructions; its inferred void pseudocode is not the return
contract. This path is distinct from new's always-enabled handler argument.

Instruction inspection classifies the remaining listed heap references as
reads; `0x0041D81F` compares an immediate address and never accesses heap
storage. The two additional listed mode references are reads as well.
REA `read_bytes` observes four initial zero bytes at heap, handler and mode
storage. These are static loaded-image observations, not proof of permanent
runtime values or absence of indirect registration. Handler/mode producers
and teardown remain unresolved beyond this bounded direct-reference search.

## Eight-entry and i686 execution

The private source now includes the initializer and malloc wrapper. It passes
**1,433 original/native fixtures**, comprising the earlier 624 and 809 new
controls, with **1,437 top-level original calls** across multi-call sequences.
Coverage includes null/nonzero heap replacement, five malloc modes, unsigned
size boundaries, callback mutation during retries, mode reload between calls,
and new's independence from malloc mode. The 210 node connections and 45 ball
retirements pass again; three native-only pointer checks remain separate.

The same C compiles under pinned VC4 and MinGW. Each generated i686 object
passes all 1,433 fixtures / 1,437 calls against the saved original observations,
including cdecl stack and callee-saved state. Whole-object relocation uses the
compiler's actual BSS/common storage and applies DIR32, DIR32NB and REL32
records. It never replaces original code or claims a byte match.

An actual Win32 heap probe under Wine passes **41 cases per compiler**, including
bounded fixed-heap allocation failure, handler stop, retry after switching heap,
mode mutation, native pointer forwarding and null release. Each run records 38
HeapAlloc calls, 34 successful HeapFree calls and four handler callbacks.
Its SDK wrappers preserve stdcall; each expected release checks HeapFree's BOOL
while the reconstructed release retains its void ABI. The instrumented original
initializer performs one HeapCreate; a second direct SDK call creates the fixed
test heap. HeapDestroy is fixture cleanup, not a recovered teardown claim.

REA `capture-process` Evidence
`ev_e9bf2b7c6884c0c0eea9bc549517e6fe6cc1d5f8db464804faa1d4faa857cdb5`
records child exit zero and binds the complete final report. The harness freezes
1,632 input identities, including parsed reference bytes, compiler engines,
matching preprocessing inputs and linker libraries, and checks products before
use and afterward. Earlier failed log/loader controls remain retained. The
link-map parser recognizes only GNU ld's exact synthetic `dll stuff` marker;
all real LOAD files must be prebound ([binutils source](https://gnu.googlesource.com/binutils-gdb/+/aa1ee363bce1eac43bf9824069e231d7113f7453/ld/pe-dll.c)).

This establishes the isolated shared-C contracts and the recorded Wine SDK
boundary. Production startup/teardown, MIDI/resource connection, full frame
paths and reconstructed campaigns remain open. No maintained, direct-case or
exact ledger promotion follows from this private experiment.
