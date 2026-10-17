# Independent board globals

The original immediate explosion-list receivers and its26-byte generated
initializer support an independent global owner. The current reconstructed
aggregate instead produces LEA receivers and a32-byte embedded initializer.
This ownership reconstruction is now adopted after the complete consumer and
production checks below. Seventeen complete units become exact and eight prior
exacts are explicitly demoted: the current total is391 exact functions,
82,242 code bytes and244 attached metadata bytes. Of270 classified authored
entries,246 are exact and24 remain complete candidates. Declarations remain
inferred, not uniquely recovered original source.

## Storage model and evidence

The proposal defines seven real neighboring objects: the20,000-byte bank,
palette clock, four mutable unclassified bytes, explosion list, ball count,
four mutable unclassified bytes, and400-byte tiles. The list retains its real
constructor-cleared `unclassified_0c` word. The existing enclosing type serves
only as an `offsetof`/`sizeof` descriptor. No actual enclosing instance,
alias cell, invented padding, copied code or alternate function body is added.
Original spellings and declarations remain inferred, not uniquely recovered.

The retained [terminal-storage evidence](../TERMINAL_RUNTIME.md#original-read-boundary)
establishes the bank/read boundary, clock/count consumers and overlapping
index50 copy. Relevant original REA Evidence is:

- Loader: `ev_5aa7369fc6fd8a1333d312332d7a4e40977ab9fa76272a6e0dd9192277fe66d2`.
- Initializer: `ev_92be01dc5bd27943d2a7e4db4df66ded90a7e2b76219f3c62058ef728d7ba02c`.
- Terminal advance: `ev_10dedc1278e4815286d503ac118934dbfa5686b95b7ab47456756e5f5df0672a`.
- Backward CRT copy: `ev_7c4ccda4f0b66e6e162c21ff7248a6806209fa96607f7d9e75dd5b00befe53a9`.

The two generated initializer dossiers are retained in
[the earlier embedded-initializer note](LIST_EMBEDDED_INITIALIZATION.md).
No new original-provider query or game run was needed for this investigation.

Ordered linker sections express the actual adjacency contract. VC4 accepts
`data_seg` and an allocated section for the class object; GCC/MinGW use section
attributes. ELF additionally needs a sorted, nonloaded output section. Each
object keeps its natural alignment and the host's genuine pointer width.
Cross-object bank traversal is explicitly a supported compiler/linker ABI
contract; it is not a claim of ISO C/C++ array-bounds portability.

## Diagnostic placement and overlap

One successful diagnostic execution per ABI checks every actual object address,
initial zero state and both complete-region index50 transfer directions.
The VC4/Native diagnostics retain a raw region observer under the stated ABI
contract; the corrected MinGW observer gathers/scatters each object within its
own bounds. The observed offsets, relative to the bank, are:

| Object / extent | VC4 and MinGW x86 | Native64 |
| --- | ---: | ---: |
| Clock | 20,000 | 20,000 |
| Clock tail | 20,004 | 20,004 |
| Explosion list | 20,008 | 20,008 |
| Ball count | 20,024 | 20,040 |
| Count tail | 20,028 | 20,044 |
| Tiles | 20,032 | 20,048 |
| Total extent | 20,432 | 20,448 |

Terminal reads preserve32 peer bytes plus368 old tile bytes on x86, and48 plus352
on Native64. The latter is a host-layout observation, not equality with x86.
These programs use diagnostic settings; real production placement, optimization
and startup remain separate gates.

Closed failures remain evidence. VC4 rejects `bss_seg`; `data_seg` alone fails
to place the uninitialized class with its peers, and the address guard stops
before traversal. Allocating the real class in its section succeeds. Its program
returns zero, although the first driver then rejects trailing Wine output during
JSON parsing. That successful program was not repeated. MinGW rejects the first
observer's whole-region array accesses under `-Werror`; bounded gather/scatter
fixes only observation, leaving the storage, constructor and board functions
unchanged. This is distinct from a game-function failure.

A separate ELF shared-library control finds two actual `R_X86_64_COPY`
relocations: a normal executable moves bank and tiles independently, breaking
their adjacency to the library's other objects. Protected storage definitions
and a PIC data consumer remove those copy relocations and pass the address and
overlap checks. The proposal therefore includes those linkage controls for ELF.
The Windows model does not receive ELF visibility attributes.

## Complete consumer comparisons during the proposal phase

The first two-owner pilot yields complete zeros for editor load/store, queue
explosion and brick hit. The independent globals also expose four changed
left-neighbor expression groups in `spread-explosive-bricks`. Using the flat
index `x + y *20 -1` restores that prior exact under the existing `x >0` grid
guard. All other instructions remain accounted for. The inference is restricted
to the real0..19 grid domain; arbitrary signed-overflow equivalence is not claimed.
The16-unit pilot preserves all12 prior exact companions.

A broad five-declaration interface trial then finds13 prior regressions and six
mapping issues. A bounded complete-interface control adds declarations for the
two genuinely defined mutable tail arrays, exposing exactly the seven objects.
It preserves all nine MIDI/bitmap comparisons. Broadening this same interface
does not preserve every other exact; it is not a universal emission fix.
The observed context sensitivity does not establish a parser-ID explanation.
No name, declaration-count, ordering or compiler-flag sweep was performed.

The completed seven-object proposal compares all278 complete units sharing the
header:248 prior exacts and30 prior candidates. Each of29 stable owner products
is compiled once or reused after full input/flag/object equivalence. Nine control
comparisons are reused. Six initially unhandled mappings are then reconciled
from actual named external identities and compared from the same objects;
the272 completed comparisons are retained rather than repeated.

There are17 new private zero results, covering7,528 complete code bytes:

| Function | Complete bytes |
| --- | ---: |
| Editor load / store | 52 / 52 |
| Queue explosion / clear all entities | 99 / 106 |
| Blit / stretch / draw effect sprite | 362 / 306 / 361 |
| Rotated sprite height | 191 |
| Drop bricks / game frame | 426 / 1,688 |
| Hit board tile / editor key | 1,315 / 632 |
| Sort present regions | 296 |
| Update paddle position / refresh score | 203 / 74 |
| Palette transition | 1,339 |
| Generated explosion-list inner initializer | 26 |

At that point these were16 authored functions and one generated function, awaiting
production acceptance. Eight previously exact functions become nonexact: keyed draw,
keyed stretch, rotated offset, rotated width, hit-region search, sprite release,
round reset and bonus update. A selective report of only the new zeros would
misstate the result. All other240 prior exact companions in this closure remain
exact. Canonical source, ledgers, caches and delivery stayed unchanged until the production gates below passed.

Literal contents, relocation addends and actual same-section local destinations
remain checked by the maintained full-span comparator. Named operand loads can
change order: relocation occurrence order alone is insufficient for the six
reconciled cases. The first pilot's proof also has six unequal unnormalized sums:
four encode `-1` as `0xFFFFFFFF`, and two editor rows replace a separate
`root +20032` instruction sequence with a direct tile-symbol push. Whole-body
agreement and the independently established tile address support those cases;
not all raw relocation sums are equal.

An independent read-only review checks all409 records in the six reconciled
functions, including34 reordered named external bindings. The three additional
zeros retain full original-span hashes and active local-target checks; the other
three functions remain nonexact. That review performs no compilation or replay.

One further uniform dependency-boundary control moves the analysis descriptor
and derived metadata out of the common game interface, leaving real global
declarations there. The source graph supports that separation: only `boards.c`
needs the post-split descriptor. Nevertheless, two representative owner compiles
produce nine regressions across27 prior exacts. This branch is closed without
another broad build; owners must not receive selective header variants.

## Production acceptance, October 17

The actual restored-CRT VC4 image, MinGW Release DLL and Native Debug library
retain all seven addresses and the complete extents in the table above.
VC4's actual `.CRT$XCU` contains the nine distinct owners once in the recovered
order; each outer wrapper calls its inner once, and the explosion inner uses
the direct receiver and real constructor clearing offsets0/4/8/12. The linked
normal startup chain reaches the initializer walk once, conditional on successful
startup. This is static linked evidence, not an observed VC4 game startup.
One ordinary Native `dlopen`, observed with read-only constructor breakpoints,
constructs those nine actual owners once in order and leaves the full region zero.

Two production-only failures required actual linkage/build fixes. CMake's
generic position-independent setting gives executable consumers `-fPIE`;
the two ELF data consumers need explicit `-fPIC` to avoid destructive COPY
relocations against the protected globals. Their actual relocations were checked.
More seriously, GCC Release turns the cross-object `memmove` into forward
`REP MOVSL`: existing Windows storage case303, terminal load50, first differs
at region byte20,064. The earlier diagnostic build did not reveal this.
The failing DLL, object, complete fixtures/results and first mismatch are sealed
before cleanup. The maintained GNU board recipe now uses
`-fno-builtin-memmove`, retaining the genuine overlap-aware library call in both
directions. No game body changes for this fix. VC4 already uses `/Oi-`.

The corrected actual MinGW DLL passes all459 existing full-region original
comparisons: three operations, all51 indices, zero/ramp/random state and nine
terminal cases. Native passes150 normal original calls and nine complete
20,448-byte terminal controls with its genuine wide-pointer layout. Existing
focused original/source matrices also pass for all eight demoted functions:
keyed draw36, keyed stretch36, release9, hit-region search400, round reset300,
bonus update912, rotated offset329 and rotated width329. The width check uses
the existing bounded geometry against the actual original width entry, including
unchanged-state/event assertions. Other historical owner loops were not run.

The eight demotions are retained deliberately: independent receivers, generated
construction and terminal-layout evidence support real independent globals.
Their five owning source files are byte-identical to the prior source; the
shared declaration context changes backend emission. All278 complete affected
units, including248 prior exacts, were already compared. The17 gains and eight
losses are both reflected in the manifest, reports and ledgers;240 prior exact
companions remain. No owner receives a selective interface or old accepted
object for changed inputs. The eight current nonexact results are:

| Function | Current / original bytes | Differing positions |
| --- | ---: | ---: |
| Keyed draw | 107 /105 | 94 |
| Keyed stretch | 141 /139 | 92 |
| Rotated offset / width | 261 /259 each | 223 each |
| Hit-region search | 172 /173 | 132 |
| Sprite release | 269 /262 | 245 |
| Round reset | 426 /426 | 20 |
| Bonus update | 2,168 /2,168 | 180 |

The generated inner/outer anchors now describe the ordinary real list instance
with its explicit section qualifier. Tracking accepts the actual declaration
and rejects wrong-slot, wrong-type and arbitrary-suffix controls while retaining
all constructor, dependency, extent and binding checks. The obsolete embedded
initializer special case is removed. Historical semantic scopes/counts are
preserved; their source-input inventories are refreshed with this documented
compatibility evidence. Before-images remain sealed. This does not claim the
entire historical semantic queue was rerun.

The canonical VC4 delivery relink reuses all116 current objects and the same19
approved original CRT members, compiling nothing further. Its image differs
from the checked private production image only in the PE timestamp. Current GNU
libraries/tools are installed byte-identically from the tested products with
input-equivalence receipts. Their old CMake caches are removed; later builds
must configure from current source. Native debug paths retain the private source
root. There is no new game run or full replay.

Current production/adoption authority:
`.analysis/independent-board-production-20261017/`, particularly
`placement-current.json`, `native-startup.json`, `windows-storage.json`,
`native-storage.json`, the five `*-flows.json` receipts, `adopted.json`,
`canonical-link.json` and `authored-coverage.json`. A tracking-format helper
initially stops before manifest writing because nested TOML array tables remain
after replacement; the corrected continuation repeats no producer or comparison.
Other driver/parser failures remain separate from actual successful producers.

Closed products are compressed, extracted member hashes verified, then deleted.
The latest cleanup removes669 closed files and releases13,246,464 allocated
bytes net of the archive and installed replacement products; small JSON receipt
allocation is excluded. Current matching products and canonical delivery caches
remain reusable. The fixture-generated default board is also removed.

## Consumer producer follow-up

The October17 follow-up accounts for372 instruction pairs across six newly
nonexact consumers using the retained prior-exact/current object digests.
Fifteen concrete bank/slot address groups occur in keyed draw, keyed stretch,
sprite release, rotated offset and rotated width. Each computes the same
`0x425980 +1048*bank +4*slot` load, compare or store. Keyed stretch also
transposes the two operands of its low32 `y +height` sum. Hit-region search
instead transposes its signed count/index comparison and branch condition;
the shorter global-load encoding accounts for its one-byte extent change.
All other instructions and branch successor ordinals agree. Scratch checks
end at actual overwrites or normal ABI calls; group end addresses are exclusive.

A separate independent retained-instruction review isolates the same address
producer in round reset (one31-byte group) and bonus update (eight31-byte groups
and one32-byte group). They account for20 and180 differing positions respectively;
all following addresses rejoin unchanged code. Live selector reads, including
reads after sound callbacks, remain necessary. Caching these values would remove
observed operations. Stable ordinary storage and actual normal calling contracts
bound this analysis; arbitrary aliasing, concurrency, flags/traps and implicit
register APIs are not established. No comparison mask or acceptance follows.

Two distinct declaration hypotheses then receive bounded private pilots:

| Hypothesis | Whole consumer comparisons | Result |
| --- | ---: | --- |
| Uniform actual Win32 SDK scalar/RECT kinds in C and C++, preserving fixed32 Native types | 30 from three owner compiles | 21 prior exacts preserved; no gain/loss. Only measure-text changes279/3 to281/186 bytes/differences. |
| Uniform shared FILE*/surface/RECT/render declarations, generic resource dependency and scalar-only trig dependency, with game board state omitted from both pilot consumers | 23 from two owner compiles | 15 prior exacts preserved; no gain/loss. Only renderer changes1458 to1466 bytes, with1466 strict differences unchanged. |

The SDK question differs from the October12 pre-C++-interface control; the
engine-state question differs from the descriptor-only split that retained all
seven board declarations. Both have independent source/consumer support as
inferences, but neither result justifies adoption or a broad compile. Canonical
headers, sources, caches, ledgers and delivery stay unchanged. Do not repeat
these same controls or infer original header organization from tidier layering.

One further canonical-path resource compile compares all17 complete units and
literals against the existing frozen-root results. All resolved digests agree.
Whole objects differ in COFF timestamp, `.file` source-path auxiliary records,
symbol count and resulting numeric relocation indexes. All25 section extents,
initialized payloads, primary symbol definitions, non-file auxiliary records and
named relocation targets agree. This establishes the tested owner's path pair,
not universal compiler path independence. The metadata explanation contributes
no code-acceptance mask. The six compiles total70 focused complete comparisons;
there is no full replay, runtime check, new provider query or game run.

The existing full explosion-member API control is also retained: all five real
member bodies are exact and259 complete consumer comparisons give net-4 exacts.
Zero-argument ECX callers alone cannot distinguish thiscall members from the
existing sole-pointer fastcall functions. That older result does not justify
another class-family rewrite or an unobserved destructor.

Authorities are `.analysis/board-consumer-producers-20261017/`,
`.analysis/win32-shared-dd-kinds-20261017/`,
`.analysis/engine-state-declarations-20261017/` and
`.analysis/canonical-resource-path-20261017/`. Successful producers are not
repeated. Closed input/object products are archived, member/decompressed hashes
verified, then49 raw files deleted; net245,760 allocated bytes are released
after carrier and retained proposal-copy costs, excluding small JSON receipts.
Totals remain391 exacts and24 authored candidates; the reconstruction is unfinished.

### Fixture callback-table owner control

Within `src`, `DxBallRenderOps` and `dxball_render_ops` occur only as a typedef,
extern and initialized definition; authored bodies call restored APIs directly.
Python fixtures read and modify the table and derive default function addresses
from it. `tests/core_gameplay_interposer.c` also consumes the type through
`bound_render` and typed binders, reading its live callbacks. An extraction must
preserve the shared C type, writable table, callback ABI and default addresses
for both consumer families. This supports a
distinct ownership hypothesis: move the unchanged table to one fixture bridge
and omit its declarations from authored headers. The earlier common-engine
pilot retained the table. Its extraction is therefore a new bounded control.

One resource compile with the uniform proposed header compares all17 complete
units. `release-sprite` becomes262 bytes exact, with the full resolved/target
SHA-256 `73d1a40d79b07a6725503ebc9b9ce494d85ccf8d856f925280d977c6f2930af2`.
All15 relocation identities, addends and targets are unchanged; only their
actual offsets move. The normal complete-span/local-target guards remain active.
However, six prior exacts regress: draw-sprite, keyed/plain blit, capture-sprite,
find-glyph and draw-glyph. Six others stay exact, leaving seven private exacts
versus twelve before. Keyed stretch changes92 to90 differences; the other three
candidates retain their results.

The branch is closed without adoption or a broad affected-owner build. The
prepared bridge preserves the callback ABI/default addresses but is uncompiled
and unvalidated; it is not a delivered implementation. The private zero cannot
be combined with canonical objects that consume different headers. Source,
ledgers, current caches and delivery remain unchanged. There is no full replay,
runtime check or new game query. Raw trial inputs/products are hash-verified in
an archive before cleanup. Authorities are
`.analysis/render-fixture-owner-20261017/{summary,comparison-resources,units-resources}.json`.
The separate [compiler-record observations](VC4_BACKEND_SYMBOL_RECORDS.md) do not
yet establish the cause of these declaration-context emission changes.

## Closed proposal phase

Before adoption, the seven-object proposal was ready for production placement, startup
and storage checks. Before adopting it, verify the actual VC4 restored-CRT,
MinGW Release DLL and Native Debug library layouts; exactly-once list construction
and the real `+0xC` clear; existing full-storage/terminal controls and affected
flows; all current compiler inputs; exports, source-generator anchors and delivery.
The diagnostic executables do not discharge those gates.

Resolve the eight regressions through supported source evidence, or explicitly
justify and record any demotions when adopting a better-supported ownership
model. Comparing accepted companions is a repository requirement; a monotonic
exact count is an acceptance policy, not proof of original declaration fidelity.
Never reuse old accepted objects as receipts for changed source inputs. Do not
repeat the closed member-call, declaration-interface or layout-split controls.

Private root: `.analysis/independent-board-storage-20261017/`.
The main authorities are `allocated-class/summary.json`,
`shared-linkage/summary.json`, `complete-interface/summary.json`,
`complete-wide/reconciled/{comparison,selected-units,proofs,summary}.json` and
`candidate/candidate.json`. The current frozen29-owner tree and products are
retained for reuse. Closed diagnostic products and superseded input/product
trees are archived with member hashes verified before deletion; the two cleanup
receipts distinguish raw allocation removed from net storage released.
Together they remove239 superseded files and release4,927,488 allocated bytes
net of the verified compressed carriers. Current reusable products remain.
