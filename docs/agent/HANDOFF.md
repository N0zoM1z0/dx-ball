# DX-Ball reconstruction handoff

Updated October 18, 2026. The reconstruction is unfinished. Recover the English
DX-Ball v1.07 functions as exactly as possible, as readable shared C/C++;
then verify the original VC4 build and playability; resume ports after that.
The user permits the **19 explicit original CRT members** in the restored-CRT
delivery. Removing them is not a delivery gate. Prioritize authored functions.

Repository: `/home/pentester/coding/codex_ida/dx-ball-reconstruction/dx-ball`.
The environment may start one directory above it. Read [AGENTS.md](../../AGENTS.md),
[WORKFLOW.md](WORKFLOW.md) and the selected owner note before changing source.
Keep code, tracked documentation and commits English. Keep the README focused on
the reconstruction approach and REA, with its two centered 900px images.

This file describes current decisions and open work. The previous detailed
[handoff at 865a648](https://github.com/N0zoM1z0/dx-ball/blob/865a648e959df831813b07002f0dbd011c550877/docs/agent/HANDOFF.md)
retains the historical adoption and cleanup chronology. Owner notes and raw
receipts remain in place; old checkpoint totals are not current totals.

## Current authorities

| Inventory | Current value |
| --- | ---: |
| Provisional independent entries | 553 |
| Retired parent-owned compiler-fragment rows, counted separately | 24 |
| Source-present entries | 475 |
| Accepted complete exact functions | 394 |
| Exact code / attached metadata bytes | 84,872 / 244 |
| Complete nonexact comparisons | 81: 21 authored / 60 runtime / 0 generated |
| Scoped semantic ledger rows | 249 |
| Entries without source | 78: 77 runtime / 1 generated |
| Inventory origins | 270 authored / 261 runtime / 21 generated / 1 unknown |

All 270 classified authored entries have source and complete current comparisons:
249 exact and 21 candidates across 30 compiler closures. The source-present
16-byte no-op at `0x40CC20` remains origin/prototype-unknown. Neither the final
authored denominator nor source optimality has been established. These inventories
are separate claims, not interchangeable completion percentages.

| Authority | Purpose |
| --- | --- |
| `config/functions.csv`, `function-origins.csv` | Provisional entries, reconciled extents and origins |
| `config/compiler-fragments.csv` | Retired aliases owned by complete C++ parents; not every internal block |
| `config/implemented.csv`, `matches.csv`, `semantic-acceptance.csv` | Source, exact and scoped semantic claims |
| `config/source-owners.toml`, `match-units.toml` | Source ownership; full compiler recipes, extents and bindings |
| `build/reports/exact-replay.json` | Current 394 accepted comparisons and producers |
| `.analysis/exact-candidate-audit-20261012/comparison.json` | Current 81 complete candidates; directory date is historical |
| [Remaining-functions table](../research/exact/REMAINING_EXACT_FUNCTIONS.md) | All candidate results and owner-note links |
| `.analysis/drawing-primitives-owner-20261018/authored-coverage.json` | Current authored source/comparison/closure coverage |

Original `original/DXBALL.EXE`: English v1.07, 158,208 bytes, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
The pinned compiler is VC4 10.00.5270 and linker 3.00.5270; original CRT provenance
uses `.tools/msvc400/lib/libc.lib`. The compiler identity is
`f097e736bb04d38391c8b524945d58809ec4c42e97c056eca6f40bba2de910c3`.
Original compiler settings cannot be inferred solely from this candidate toolchain.

Keep `original/`, `.tools/`, `build/`, `.analysis/` and `ghidra-project/` private.
A source-only clone does not include the assets, tools, products or raw evidence.

## Current source and delivery

The current restored-CRT executable is
`068d2e8bc904e8433d0fa9260ebc374cd9e3349947752ab0266bacb582fd3123`.
Its recipe is `vc40-restored-crt`: 117 source objects from 114 owners plus three
integration owners, 19 pinned CRT members, `/NODEFAULTLIB /OPT:REF`, six OS DLLs
and no MSVCRT DLL. The image, map and full input/object identities are in
`build/vc40-restored-crt/build.json`. Reuse only after checking the complete closure.

The latest [drawing-primitive owner](../research/exact/DRAWING_PRIMITIVES_OWNER.md)
moves the adjacent line/fill pair to one C++ implementation with full unchanged
public headers. Line445/9 and fill85exact retain their complete identities;
right-palette234/9→234/6 restores three original guard bytes without losing a
matching byte. All nine functions/38 bindings compare; eight identities and six
exacts survive. The original owner boundary remains inferred. Final canonical
compiles attest comments moved with the functions. Native/MinGW each compile
only two files using valid caches;562 existing line/fill/right-palette cases pass.
All249 semantic input inventories refresh without changing historical scopes
or cases. The linked image reuses117 objects/19 CRT members, with no new compile.
Five functions move; full old/new bodies, nine incoming fields,20 replaced loader
RVAs and all1,064 changed PE bytes are checked. All other PE bytes, resources and
six OS DLL imports remain unchanged. No provider, full replay or new game runs.
`.analysis/drawing-primitives-owner-20261018/` retains final producers, independent
reviews, affected checks and full linked verification. Current totals stay394
exacts/21 authored candidates across30 verified compiler closures.
Archive/member-hash verification precedes deletion of43 closed input/product
copies, including six objects and four superseded history files, releasing
7,647,232 allocated bytes net of archive/journal costs. Current tested products
and valid incremental caches remain; final tracking passes553/475/394.

The preceding [resource drawing-wrapper owner](../research/exact/RESOURCE_ROTATION_WRAPPER_OWNER.md)
moves only the unchanged40-byte argument adapter to resources, with the complete
rotation header under C linkage. Both owners are accepted together: y-offset191,
keyed draw105 and stretch139 become exact; ordinary draw107/94 and blt199/173 are
explicit demotions. Net+1 exact/+135 code bytes. Load-bank becomes1475/66 and
PCX979/851, both candidates;16 other full code identities survive. All23 complete
units/377 bindings/31 literal references pass. Real C2 traces capture bank/slot
ranks and current function records; original keys/TU ownership remain unknown.
Native/MinGW each compile2 owners; existing1024 rotation calls,1869 resource calls
and24 original/native/full-relocated-VC4 helpers pass. The moved wrapper preserves
its344 semantic cases and original rotation oracles through explicit unit overrides.
The VC4 relink reuses116 objects/19 CRT members. All1099 owner-qualified MAP
records stay fixed; full linked bodies/constants and all other PE bytes are
checked, including loader relocation semantics derived from changed COFF fields.
No full replay or new game run follows.44 closed raw carriers are archived and
member-hash verified before removal, releasing7.77 MiB net. Current tested
products, direct traces and valid CMake caches remain.

The later [bank symbol-reader observation](../research/exact/VC4_BACKEND_SYMBOL_RECORDS.md#current-bank-loader-reader-order)
uses one unchanged resource compile and retained REA assembly. All14 scalar
roles plus key/API workspace are captured; field+8 equals object size, and actual
reader order accumulates to all16 current frame homes. saved_bank key28266 is
directly observed. Width is original/current EBP−52; height is original−28/current−48.
This is a current-closure correlation, not an allocator algorithm or original
declaration recovery. All18 full comparisons/262 bindings/six literal references
retain their identities, including13 exacts. No source, count, delivery, replay
or game changes. Private `.analysis/sprite-bank-current-producers-20261017/`
retains direct trace, corrections and reviews.98 old duplicate runtime copies
and two archived observer products are removed after hash/reference checks,
releasing3.38 MiB net after the cleanup archive/journal. Current tested products
and valid CMake caches remain. The producer of reader order is the next concrete
gap; do not repeat the closed root/scope/name/order controls.

The subsequent [frame allocator investigation](../research/exact/VC4_BACKEND_SYMBOL_RECORDS.md#frame-allocation-from-the-symbol-reader)
connects that correlation to actual C2 control flow.16 same-address records retain
kind/key/decorated name; only+4 matches every signed home. A count data watch
captures0→−4 at401556; reader41b877 calls401508, which rounds size+8 and stores
the negative cursor result. The normal path does not read key+24; upstream
reader-order production is the next gap. One reused REA import adds22 records,
closes and saves86 cumulative observations. Account for the imported shared-tail/
prologue splits and wrong void signature.17 final pinned-code synthetic calls
reproduce all16 homes/180-byte frame with explicit cursor0/alignment4. The66-byte
residual review covers425 boundaries/23 calls/22 branches. An archive proof closes
root14/current116-byte API workspace by exact body equality to the prior1475/72
model. A whole-loader aggregate lacks independent ownership evidence and is not
tried. Both unchanged-closure observed compiles preserve18 full comparisons/262
bindings/six literal references. No source, count, delivery, semantic case, game
or full replay changes. Four observer products are archived/member-verified and
removed; the closed identical catalog shares its immutable carrier. Cleanup
releases8.66 MiB after archive/journal. Receipts are in
`.analysis/bank-frame-writer-20261017/`; retain current tested products and caches.

The later [C1XX traversal investigation](../research/exact/VC4_FRONTEND_SYMBOL_ORDER.md)
explains all16 current bank records through actual name hashing, head insertion
and ascending buckets.36 controlled pinned-helper calls agree with the earlier
live C2 trace for the four current source declaration groups. Explicit mode1/
kind9/mask15 inputs and emitter/header stubs limit that result: no new live
frontend mask, complete IL transport or original names/scopes are recovered.
Do not turn the hash into name/order/mask fishing or reopen the root14 control.
The pinned wrapper adds only `vc4-cpp-frontend`; nine Python and six JavaScript
provider-free guard/lifecycle cases pass. One reused import closes115 records
and five indexed failures. Reuse them before another819,640ms cold query.
Private `.analysis/frontend-record-order-20261017/` retains full primary evidence,
machine checks, independent review and the compressed closed snapshot. The
temporary Ghidra project is removed; catalog sharing releases8,658,944 allocated
bytes after snapshot/journal. Standard cleanup previews zero further disposable
products. No game source, exact count, compiler run, delivery, game or replay changes.
One CPU/35%, memory high640MiB/max768MiB remain enforced with no max/OOM events.

The October18 [palette-effects owner control](../research/exact/PALETTE_EFFECTS_OWNER.md)
extracts four consecutive original palette operations into one C++ owner, with
complete unchanged public headers and two genuine SetEntries member calls.
Three compiles compare29 complete functions/459 bindings. Every resolved digest
stays unchanged;22 exacts/5,375 bytes and all seven candidates survive. Close
without adoption or order/header/name variants. Independent review and full
receipts are in `.analysis/palette-implementation-owner-20261018/`. Archive/member
verification precedes deletion of28 raw copies/products and a Python cache,
releasing163,840 allocated bytes after archive/journal. Canonical source, objects,
caches, delivery and totals stay unchanged; no provider, game or replay runs.
The separate [triangle edge review](../research/exact/TRIANGLE_SCANLINE_SCOPE.md#edge-record-ownership-review-october18)
rejects two slope/position records before compiling: original root construction/
cleanup order and noncontiguous long-edge homes contradict that ordinary model.
Keep all four root objects before sorting/exits. Its primary IDs/addresses remain
in `.analysis/triangle-edge-ownership-20261018/review.json`.

The distinct October18 [complete surface descriptor control](../research/exact/SURFACE_DESCRIPTOR_CONTRACT.md)
reconstructs the genuine nested v1 API shape and void surface pointer, retaining
current scalar abstractions and interfaces. Three serial compiles compare32
complete resource/UI/rotation functions and415 bindings/31 literal references.
Draw and release become exact, but nine prior exacts are lost: reject the fixed
model as a family, with no selective object/header adoption or further variants.
Fifteen code identities remain unchanged. Private
`.analysis/surface-descriptor-contract-20261018/` retains full inputs,
transformation, comparisons and independent reviews. No broader consumer build,
native build, relink, provider, game or full replay follows. Scope peak is
241,090,560 bytes with zero high/max/OOM events under the required one-CPU35%/
high640MiB/max768MiB limits. Copied inputs and all six before/proposal objects
are archived/member-verified before removal. Current source/products/counts stay
unchanged. Modern SDK layout corroboration is not recovery of1990s header text.
Cleanup removes26 raw copied inputs/products, releasing139,264 allocated bytes
after archive/journal costs. Finalization corrects literal-name/report-annotation
handling and the location of mapped literal data without repeating compiles or
comparisons; the final verification passes. Standard cleanup previews zero other
registered disposable products. The current build tree totals about62MiB.

Two further bounded ownership reviews decline unsupported models before
compilation: ordinary selected tile/center points contradict original homes
([last-brick review](../research/exact/LIGHTNING_EXPIRY_SCOPE.md#selected-coordinate-ownership-review-october18));
a slope-only triangle pair fits layout but lacks aggregate ownership/required
ctor/EH flattening evidence ([triangle review](../research/exact/TRIANGLE_SCANLINE_SCOPE.md#edge-record-ownership-review-october18)).
The latter does not universally exclude local `/GX` aggregates. A separate
[three-file publisher-source follow-up](../research/exact/AUTHOR_SOURCE_CONTEXT.md#three-related-raster-implementations-october18)
establishes no PCX/triangle routine connection, checks57,186 bytes against pinned
Git blobs and removes raw copies after archive/member verification, releasing
40,960 allocated bytes. Neither review nor bounded search changes source or claims.

The later [five-function glyph/text owner](../research/STARTUP_UI_OWNER.md#glyphtext-implementation-owner-control-october18)
joins the original contiguous lower-glyph/upper-text call family and real spacing
state, unlike the older whole-UI controls. All five bodies and full headers stay
unchanged. Three compiles compare27 functions/300 bindings/six literals: no gain,
one glyph-lookup loss145/0→146/86. PCX also exchanges two multiplicand operands
while staying979/851;25 code identities survive. Reject without variants or
partial adoption. `.analysis/text-glyph-owner-20261018/` retains independent
reviews and sealed full verification. All24 raw inputs/products, including five
objects, are archived/member-verified and removed, releasing118,784 allocated
bytes net of archive/journal. Scope peak167,350,272 bytes, zero high/max/OOM
events; required resource limits hold. No native build, relink, provider, game
or full replay. Canonical source, objects, delivery and counts remain unchanged.

The later [clock owner control](../research/exact/EXACT_WINMM_CLOCK_IMPORT.md#closed-clock-implementation-owner-october18)
compares27 full functions/777 bindings from three compiles: no exact gain/loss,
26 unchanged code identities; paddle alone regresses677/68→678/210. Reject it.
Two fixed [legacy clock-expression checks](../research/exact/LIGHTNING_EXPIRY_SCOPE.md#complete-vc4-clock-expression-rejections-october18)
each compare all20 current-C++ display functions/421 bindings. Both yield the
same1063/356 last-brick body with a64-byte frame but wrongly call RNG before
time. Reject both despite closer raw bytes. The first corrects a prior native-only
closure; the second answers a time-left control previously compiled only as C.
Neither changes source, products, semantic/exact claims or delivery. All80 raw
inputs/products across these three pilots are archived/member-hash verified
before removal, releasing452 KiB net; scope peaks stay below246 MiB with zero
high/max/OOM events. No native build, relink, runtime, provider query, game or
full replay follows. Sealed evidence lives in `.analysis/clock-family-owner-20261018/`,
`.analysis/lightning-rng-left-vc4-20261018/` and
`.analysis/lightning-time-left-cpp-20261018/`. A separate four-query
[polygon source-identity search](../research/exact/POLYGON_SCAN_WORKSPACE.md#bounded-source-identity-search-october18)
finds that Graphics Gems' ConcaveScan differs in allocations, sorting, edge fields
and advancement. Retain its hash-verified gzip source carrier; delete the raw
copy. The supplied edge stride was incorrectly24; a separately sealed erratum
verifies28 against both original allocation producers, including the unknown
four-byte slot at offset12. Do not describe the old search premise as complete.
This bounded negative result supplies no new original declaration. The capped
standard cleanup preview finds zero further registered disposable products;
the build tree remains about62 MiB with useful caches and current products.

The later [complete PCX disk-header control](../research/exact/EXACT_PCX_PACKET_LOOP.md#complete-external-header-control-october18)
tests one independently documented128-byte record without changing decoder
tokens or signed maxima. One current resource compile leaves all18 full bodies/
262 bindings/six literals unchanged. Reject it without variants; original
declarations and the frame gap stay unresolved. Its11 raw inputs/products are
archived/member-verified then removed, releasing72 KiB net. A separate passive
[edge-consumer review](../research/exact/POLYGON_SCAN_WORKSPACE.md#bounded-source-identity-search-october18)
confirms30 actual accesses per polygon, with+12..15 untouched and no external
domain consumer of the records. Both investigations retain sealed evidence;
neither adds a function, exact claim, provider query or runtime case.

The later [current C++ nested-origin control](../research/exact/ROTATION_ORIGIN_STORAGE.md#current-c-nested-origin-control-october18)
closes a specific gap: the sole earlier nested model used C and older inputs.
One current compile compares five complete functions/115 bindings/25 literals.
No gain; offset259exact→261/223, three other exacts retain their identities,
renderer1458/1466 changes digest. Original first-term homes−368/−400 return,
with78 origin instructions checking64-bit rounding, trig order and both FDIV
paths; this is not a full renderer equivalence claim. Reject the whole model,
without selective old objects or further expression variants. Sealed
`.analysis/rotation-current-cpp-origin-20261018/` retains reviews and full
comparisons. Ten raw inputs/products including two objects are archived/member
verified then removed, releasing44 KiB net. Peak159,252,480 bytes, zero high/max/
OOM events. No source, claim, delivery, provider, runtime or full replay changes.

The separate [PCX header-tail review](../research/exact/EXACT_PCX_PACKET_LOOP.md#header-tail-geometry-and-bounded-search-october18)
places the unexplained four bytes immediately after the observed128-byte
header and before its pixel pointer. Adjacency and incidental alignment do
not establish a132-byte declaration. Four targeted external queries find no
qualifying published declaration; the receipt preserves search excerpts and
their limitations, not downloaded source provenance. No guessed header is
compiled. Sealed `.analysis/pcx-header-tail-search-20261018/` retains original
Evidence/carrier hashes and geometry; no disposable raw files are created.

The preceding [current-context C++ rotation owner](../research/exact/ROTATION_CPP_OWNER.md)
restores offset and width at259 bytes each, explicitly demoting y-offset to
193/191/159. Net gain is one exact/327 bytes. Height and wrapper remain exact;
renderer stays1458/1466 with a new digest. All116 actual bindings and full
literals pass. Six real surface member calls preserve arguments/live reads;
four math bodies remain unchanged. Existing1,024 rotation calls,329 width cases
and24 original/Native/full-VC4 helper observations pass. Native/MinGW each
compile one owner using retained caches. The whole family is adopted together;
all1,097 distinct MAP names and owner-qualified static records retain their
addresses. All six rotation functions are discarded from the OPT:REF delivery;
the complete PE changes only within six parsed timestamp fields. Source recovery
is a separate claim. There is no selective object/header mix, full replay or new
game run. Cleanup archives/member-verifies45 closed raw carriers and removes
eight obsolete/duplicate products, releasing9.35 MiB net. Current tested objects,
products and valid CMake configurations remain useful and retained.

The preceding [bonus C++ implementation owner](../research/exact/BONUS_CPP_OWNER.md)
recovers the complete2,168-byte update function, reducing180 differences to zero
while preserving all three prior bonus exacts/1,316 bytes. All bodies and public
APIs remain unchanged; frontend and complete header view are tested together.
Native/MinGW each compile this owner once using retained caches;2,851 existing
bonus calls plus one trig setup pass. VC4 reuses116 objects/19 CRT members.
Ten globals now occupy actual40-byte BSS, moving157 mapped names; complete linked
bonus bodies and3,162 moved-data reference fields pass. Board terminal ABI,
resources and imports remain intact. No full replay or new game observation.
Temporary copies and obsolete C objects are archived, member-hash verified and
removed; current tested products and useful canonical CMake caches remain.

The preceding [paddle width sampling scope](../research/exact/PADDLE_WIDTH_SAMPLING_SCOPE.md)
restores the677-byte extent and original right-edge sum order, reducing210 to68
strict differences. All15 runtime companions retain their code identities,
including13 exacts. All185 instructions,12 branches,10 calls and52 bindings are
accounted; physical source homes remain different. The candidate stays nonexact.
Existing332 paddle calls and fresh Native/MinGW builds pass. VC4 relinks with116
reused objects/19 unchanged members; all1,097 map addresses stay fixed. Its PE
changes are confined to paddle/alignment, nine actual loader relocation updates
and six timestamp fields. No game run or full replay follows. Valid canonical
CMake configurations now remain for incremental reuse.

Two later bounded lifetime controls are closed without adoption. The
[joint paddle model](../research/exact/PADDLE_WIDTH_SAMPLING_SCOPE.md#closed-joint-lifetime-model)
keeps short sampled width with long factor, but regresses to 679/487; all 15
companions, including 13 exacts, retain their identities. The
[last-brick crop/publication scope](../research/exact/LIGHTNING_EXPIRY_SCOPE.md#closed-croppublication-lifetime)
moves only rectangle and destination locals after bank 2 selection. It regresses
1067/990 to 1067/992; all 19 companions, including 16 current exacts, remain
unchanged. Its 302 instructions differ only in 58 frame-displacement bytes.
Keep both canonical implementations and all current claim/product identities.
No native build, relink, game, provider query or full replay follows rejected code.

The later [ranking implementation owner](../research/exact/RANKING_OWNER_FAMILY.md)
control moves the shared table and four consecutive drawing/persistence functions
into one private implementation. Three compiles compare exactly 14 functions;
all complete code/metadata identities, including 13 exacts/4,156 bytes, remain
unchanged. Reject the model without order/include variants. Ranking drawing has
all original frame homes and 135 instructions; only its two-instruction
index/global comparison producer explains the 403/404-byte extent difference.
The [current presenter correspondence](../research/exact/PRESENTATION_MERGE_SCOPE.md#current-producer-correspondence-october-17)
accounts for its six changed loads in left/right/bottom min/max producers; top
now agrees. SDK macros expand to the current expressions. Neither comparison
justifies a new text-scope or equivalent-expression compile.

The latest [independent board globals](../research/exact/INDEPENDENT_BOARD_STORAGE.md#production-acceptance-october-17)
recover seven real neighboring objects instead of an enclosing instance, while
preserving the full terminal-copy ABI. All278 affected complete units are
accounted:17 promotions and eight explicit demotions give a net nine exacts,
including16 authored gains/eight authored losses. The generated inner initializer
is26 bytes exact. The eight demoted owners' bodies are unchanged; declaration
context changes backend emission. Keep both gains and losses in current reports.

Actual VC4, MinGW Release and Native Debug placement passes. The existing MinGW
full-storage459 cases, Native150 normal original calls/nine wide terminal cases,
and focused flows for all eight demotions pass. Native dlopen observes nine
list owners once; VC4 startup has conditional linked static evidence, not a new
game observation. GNU boards retain the real memmove call because Release
inlining produced an observed terminal overlap failure. ELF data tools use
explicit-fPIC with protected globals. All116 current VC4 producers/19 members
are reused for the canonical relink, with zero new compiles. GNU tested products
are installed byte-identically, with retained-build.json receipts; old CMake
caches were removed at that checkpoint. The later paddle scope above configures
fresh canonical builds and retains their valid caches for subsequent reuse.

The earlier [joint hit scope](../research/exact/EXACT_BRICK_POWERS.md#shared-counter-and-switch-pan-scope)
restored all19 frame homes and reduced416→405 differences. The independent
receiver now completes that function exactly at1,315 bytes. Original scopes and
declarations remain inferred. Earlier delivery/game observations retain their
own image identities.

The preceding adoption restores [score formatting workspace regions](../research/exact/SCORE_WORKSPACE_REGIONS.md):
decimal20 in both formatters and menu text100 make `draw-score`433 and
`redraw-intro`587 bytes exact. Two owner compiles compare36 complete functions,
preserving30 prior exacts and four other candidate identities. Existing135
focused calls pass; the delivery relink reuses116 source objects/19 members.
No game run follows this change. Original capacity declarations remain inferred,
not uniquely recovered; the complete emitted functions are exact.

The earlier [brick-hit iterator scope](../research/exact/EXACT_BRICK_POWERS.md#particle-iterator-scope-adoption)
at `fd4196d` returns score-flag storage to original EBP-8; the complete candidate
improves from 418 to 416 differences. A retained object with identical producer
inputs supplies the change without another VC4 compile. Seven complete comparisons
preserve five exacts/1,572 bytes and all other affected identities. The final
108-case native selection passes with the existing typed board-surface backing;
initial fixture crashes and a private cleanup error remain retained. Relinking
reuses all 116 objects/19 members; all 1,091 map addresses stay fixed. Only nine
proved frame displacements and twelve timestamp bytes differ from the preceding
image. The subsequent joint scope above restores counter/pan homes; one receiver
producer remains open.

Earlier adopted authored changes remain in their owner notes: [bank allocation scope](../research/exact/BANK_ALLOCATION_SCOPE.md),
[rotation pixel addresses](../research/exact/ROTATION_PIXEL_ADDRESS.md) and
[last-brick expiry scope](../research/exact/LIGHTNING_EXPIRY_SCOPE.md). Their
historical game observations retain their own image identities. No new exact
function follows from these partial improvements.

The [local-target comparator guard](../research/exact/EXACT_LOCAL_TARGET_GUARD.md)
checks actual same-section COFF destinations before accepting a zero-byte result.
Tracking also checks known function-symbol mappings against catalogued entries,
including attached metadata. These guards do not independently recover unknown
symbol identity or ABI. Keep addends separate from symbol targets. The two earlier
brick-hit case mappings are repaired; explanatory operand projections are not exacts.

## Next source question

Choose a specific unaccounted operation, ABI, ownership, lifetime or producer fact.
A small difference count is not itself a source question. Complete correspondence
and unchanged tests do not prove original declarations or absolute optimality.

The drawing-wrapper owner now supplies actual named C2 rank observations for
resource producers. Load-bank's complete extent is restored at1475 bytes with66
remaining differences; use its retained full body and current trace to locate
the remaining actual producer before another compile. The fixed owner control
is closed; do not search wrapper position, function order or key values.

Continue exploring the remaining21 authored candidates. The user explicitly
corrected the earlier missing-declarations blocker: recovering those facts is
the task. Original source, MAP/PDB or build records would help but are not a
prerequisite. Do not treat an unproved declaration as proof no hypothesis can be
tested. The score workspace recovery supersedes the earlier read-only review's
overly restrictive capacity decision. Form a specific inference from actual
consumers and independent layout facts, compile once, then judge the complete
result while preserving the distinction between inferred and unique source.

| Function | Established boundary | Missing producer fact |
| --- | --- | --- |
| `load-pcx` | All 227 instructions accounted; current frame308 contains305 typed bytes plus3 slot-padding bytes | Original distances61–64 are unaddressed; their owner, declaration/lifetime context and producer scheduling remain unknown |

Reuse [intro score phase](../research/exact/INTRO_SCORE_PHASE.md),
[score strip](../research/exact/SCORE_STRIP_SOURCE.md),
[PCX packet proof](../research/exact/EXACT_PCX_PACKET_LOOP.md) and
[closed storage diagnostics](../research/exact/CLOSED_STORAGE_DIAGNOSTICS.md).
Score/intro capacities are inferred from both independent workspace regions and
their complete exact emissions. Adjacency alone does not establish a PCX
aggregate; a smaller body or one-position count gain does not recover a variable
home. The PCX packet trial rotates four homes and restores none; it stays rejected.
Do not repeat its API-record, scanline-record, header-scope or packet-scope trials.

The adopted [independent board storage](../research/exact/INDEPENDENT_BOARD_STORAGE.md)
keeps all seven real objects, both mutable unknown slots, the real +0xC list
word and natural pointer widths. Ordered linker sections and retained memmove
provide the supported compiler/linker ABI contract. It is not an ISO array-bounds
portability claim. The layout descriptor is a view, with no enclosing instance.
That checkpoint's29 matching products/frozen inputs remain in
`.analysis/independent-board-storage-20261017/complete-wide/`, with its comparisons
in `reconciled/`. The later paddle scope replaces the runtime producer; the other
28 remain current. Production/adoption receipts and the checkpoint audit remain
in `.analysis/independent-board-production-20261017/`. Current source/object and
comparison authority follows the table above. No full replay or game run.

Continue the21 current authored candidates, including the eight declared-context
demotions. Choose a concrete producer, ownership, ABI or lifetime discrepancy;
no evidence requires accepting the present declaration context as optimal.
Do not repeat the closed five-declaration broad trial, member-call probe or
uniform layout/interface split (nine regressions across27 prior exacts).
Avoid name/order/count/flag sweeps or owner-specific header variants.

The latest [producer follow-up](../research/exact/INDEPENDENT_BOARD_STORAGE.md#consumer-producer-follow-up)
accounts for all eight new demotions through actual bank address, sum or guard
lowering. Two bounded SDK/common-engine declaration pilots gain nothing and
remain unadopted; their53 complete comparisons are retained. A canonical-path
resource control preserves all17 full bodies/literals, with only COFF/file
bookkeeping differences. Do not repeat these pilots or the earlier complete
explosion-member API control. Current source, caches, image and counts are unchanged.

The distinct [fixture callback-table extraction](../research/exact/INDEPENDENT_BOARD_STORAGE.md#fixture-callback-table-owner-control)
compares17 complete resource units: a private262-byte release-sprite zero comes
with six prior exact losses. It is closed without adoption; do not mix that
object with canonical headers or repeat the same pilot. Its bridge was prepared
but never integrated. [VC4 backend record observations](../research/exact/VC4_BACKEND_SYMBOL_RECORDS.md)
and the [expression-ordering follow-up](../research/exact/VC4_EXPRESSION_ORDERING.md)
retain64 cumulative REA records in a separate closed snapshot. The latter
establishes the actual child swap/opcode map and a rank derived from numeric
record key`+0x24`;44 executions of the pinned helper bytes pass. Concrete game
node keys/ranks and their final emitted instructions remain unobserved. This is
not a declaration-order/name/count/flag experiment basis. Reuse the closed
records before another cold import. Interactive invalid-input queries now retain
their complete diagnostics without discarding the import; seven mocked cases
pass. Two closed catalogs share hash-verified storage, releasing16.7 MiB net.
No game source, claim or product changes in this follow-up; the wrapper owner above sets
the current totals and delivery identities.

Other authored boundaries and retained controls:

- Preserve the real20,432-byte Win32 storage layout and368-byte terminal overlap.
  The descriptor is a recovered view, not uniquely recovered original source.
  No alias cells, artificial padding, unverified split or alternate offset/cast
  spelling solely to force emission. Editor key and game frame are now exact after the independent ownership adoption.
- [Rotation](../research/exact/ROTATION_PIXEL_ADDRESS.md) accounts for all 365
  renderer instructions, 22 calls and 26 branches under its stated stable-memory,
  finite-FP model. Height is now exact after independent board ownership; all four projection helpers are now exact after the resource wrapper owner; the renderer remains a candidate.
  Row-add, inline-bank, max/return/FP and type-context controls are closed.
- [Effect sprites](../research/exact/EFFECT_SPRITE_PATH_CORRESPONDENCE.md) have
  complete path/ABI/RECT-write correspondence and retained SMT mutation controls.
  Independent board ownership now makes all three effect-sprite entries exact; other context trials stay closed.
- Triangle's four root-constructed FixedPoint objects precede early exits; do not
  narrow them arbitrarily. The adopted scanline scope restores y's home; vertical
  scale and polygon endpoint-scope controls are closed.
  The [read-only FixedPoint receiver model](../research/exact/EXACT_FIXED_POINT.md#read-only-receiver-control-october-17)
  also closes unchanged: all12 full code digests and attached metadata agree
  after one compile. It changes no claim; do not repeat qualifier combinations.
- The [C-compatible polygon owner](../research/exact/POLYGON_SCAN_WORKSPACE.md#c-compatible-polygon-owner-control-october-17)
  full80 pilot reproduces the rejected C++ full80 bodies, including five extra
  copy-address LEAs each. Separate x/y assignments would change the original
  paired reads and writes; that proposal is declined before compiling. Neither
  result proves the original language boundary or a source optimum.
  The distinct [current64 C-owner control](../research/exact/POLYGON_SCAN_WORKSPACE.md#current-workspace-in-an-independent-c-owner-october-17)
  preserves separate endpoints and all body tokens. Ordinary becomes1543/212,
  clipped stays1592/214 unchanged. Eight instruction bytes lose two prior
  original comparison orders while recovering the final dy/error comparison.
  Close without adoption or further variants; all current source/products and
  totals were unchanged at that checkpoint; the later rotation adoption sets current counts. Seven raw copies are archived/member-verified
  and removed, releasing48 KiB net; useful current caches remain.
- Bank cursor/row/column, file-metadata and transfer-workspace scopes are closed.
  Preserve callback-visible state and the pitch snapshot before Lock.
- [Brick-hit pan consumer scope](../research/exact/EXACT_BRICK_POWERS.md#closed-pan-consumer-scope)
  alone was rejected:416→418 differences and loss of the score flag. The distinct
  joint scope restored all original homes; independent ownership subsequently makes the complete hit exact. Do not
  repeat the standalone trial or treat its rejection as closing all combinations.
- Line, ranking, presentation, palette, clock and text near-matches include known
  compare/register commutations. Reversing guards, renaming identifiers, changing
  equivalent types or sweeping `/G3`, `/G4`, `/G5` is not new evidence.
- Keep time sampled before RNG. The reversed-addition proposal fails an existing
  ordered case. Clang reverses the four last-brick particle RNG arguments relative
  to original/current GCC; the recorded port gap is deferred, not repaired here.

The [public author-context review](../research/exact/AUTHOR_SOURCE_CONTEXT.md)
supplies no 1.07 declaration, capacity, flag or shared-routine identity. Do not
repeat that search or import another project's settings. Do not replace source
work with repeated coverage audits or unchanged runtime episodes.

## Inventory evidence and approved runtime dependencies

[Joined text coverage](../research/exact/CRT_SUFFIX_OWNERSHIP.md#joined-declared-text-coverage)
accounts for all 126,700 declared text bytes through existing source/CRT owners;
3,650 gap bytes are CC. [Incoming-reference](../research/exact/CRT_SUFFIX_OWNERSHIP.md#incoming-references-to-declared-game-bodies)
and [PE relocation](../research/exact/CRT_SUFFIX_OWNERSHIP.md#original-pe-code-address-relocations)
reviews retain their bounded scopes. The [direct-transfer review](../research/exact/CRT_SUFFIX_OWNERSHIP.md#direct-transfers-in-the-declared-game-prefix)
accounts for all 289 declared prefix spans: 23,469 instruction sites, 3,719 direct
transfers, 16 tables/191 address words and 492 selector bytes. All represented
direct/table destinations are known entries or same-parent instructions. Another
142 calls use import cells; 177 register-relative call values remain unresolved.
Outside-prefix sources, alternate code and runtime-only targets remain open.
None of these checks proves the final authored denominator. Reuse their sealed
results rather than repeating a walk for the unchanged original.

[Dependency receipts](../research/exact/CRT_DEPENDENCY_INVENTORY.md#complete-receipt-coverage)
cover all 78 no-source entries; 19 member dependencies remain explicitly approved.
Do not fabricate ordinary C wrappers for EAX/ESP stack probes, x87/SEH transports,
or assembly memcpy/strlen/memset. C++ frame handlers use their actual implicit EAX
contract. Original dead/indeterminate reads, overlapping copies and pointer
formation are documented behaviors, not opportunities for silent repair.

Existing runtime/data source authorities remain separate from function counts:
`runtime-x87-operation-tables.json` (12 records/480 bytes),
`runtime-x87-dispatch-constants.json` (48 readonly bytes),
`runtime-character-state.json` (ctype/locale storage and pointer bindings), and
`runtime-locale-handles.json` (28-byte relative layout; target address null), all
under `config/`. No independent BSS address follows merely from a code operand.
All eight allocator functions are exact; actual C++ new/delete, entry, stdio and
exit integration are documented in their owner notes. Preserve `.CRT$XIC` stdio
before onexit, the shared callback state and real Win32 heap/raster defaults.
SEH bodies require a capable compiler; do not substitute no-op host catches.
Historical whole-cvt/C-mode/register-order controls remain rejected. Keep accepted
companions; do not split owners or add barriers solely to select private zeros.

## Actual game evidence

The [preceding-image bounded entry/exit check](../research/RESTORED_CRT_ROUND_FLOW.md#current-image-bounded-entry-and-exit)
passes 5.019 seconds on original board0: all 400 initial bytes, 1,410 valid samples,
no malformed lines, score10/lives3, menu return and actual exit0/no window. The
20,000-byte bank and 49 originals stay unchanged. Measured CPU is32.1% of one CPU,
peak301.668 MiB, no memory-limit events. A preceding per-read attempt fails before
gameplay with 42 reset-requested samples; keep its failure separate. Persistent
reader success does not establish failure causality or focus recovery. These
observations retain image50e40609, before the score workspace adoption. Both runs
reuse the game/reader without compilation. Do not repeat this unchanged episode.

The historical [original50 attempt](../research/ORIGINAL_CAMPAIGN.md#current-restored-crt-original-bank-prefix-october-17)
is terminal, observer exit1 at the14,400-second deadline. It verifies initial
boards0–19, then retains index19/15 bricks/score52,538/lives3. Its611,084 valid
samples and1,473 events do not establish full50 completion, a crash or normal
application exit. All three owned identities are absent. Never restart its
producer or reapply pass-only verification to that failure.

Earlier [editor](../research/RESTORED_CRT_EDITOR_FLOW.md),
[game-over](../research/RESTORED_CRT_GAMEOVER_FLOW.md),
[round](../research/RESTORED_CRT_ROUND_FLOW.md),
[custom terminal50](../research/RESTORED_CRT_TERMINAL_FLOW.md) and
[natural expiry](../research/RESTORED_CRT_LIGHTNING_FLOW.md) controls keep their
recorded images and limits. Custom single-brick boards are not the untouched
original campaign. [Sparse-tail controller](../research/CAMPAIGN_TAIL_CONTACTS.md)
checks do not prove live speedup or full50 progression. The original Wine9
[focus/surface-loss failure](../research/ROUND_FOCUS_RUNTIME.md) remains unresolved;
do not patch exact game behavior or rerun its unchanged loop. Physical Windows,
graphics/audio fidelity, exceptional paths and full campaign acceptance stay open.
The macOS PR was already answered and deferred; no further message or port work
is pending. The complete objective remains active and unachieved.

## Resources, cleanup and publication

Use `scripts/repo-python`, `resource_limits.limit_cpu()` and one allowed CPU.
One writable compiler/provider/Wine session at a time; the blocking
`legacy_toolchain.session_lock()` is non-reentrant. Do not wrap a helper that
already acquires it. CMake uses `--parallel 1`; keep `balls.cpp`'s documented GNU
C++17/x87/excess-precision options and C linkage. Prepare native interposers before
taking the lock. Automated audio goes to `PULSE_SINK=dxball_reconstruction_silent`;
never change the default sink.

Run heavy commands in a user scope with CPU35%, memory high640 MiB/max768 MiB.
[REA](REA.md) is pinned at6.5.0/Ghidra12.1.4 with a256 MiB heap. Reuse retained
Evidence first, query only missing facets, retain full responses and close/save
sessions. Use LeanToken for bounded source reads. A timeout/truncated preview is
not producer failure: poll its live handle or inspect terminal receipts before
considering a restart. Optional REA feedback stays in the existing single
`/tmp/dxball_rea_feedback_20261010.md` file.

Compile once per stable family; compare complete affected candidates and accepted
companions, including all relocations, full literals and attached metadata. Freeze
previous products and recursively consumed inputs before overwriting them. Use
only the minimum useful existing Oracle/play check. No default historical queue,
repeated unchanged checks or full replay after every edit. When beginning actual
binary/compiler work, verify relevant inputs with `verify-target.py`,
`verify-toolchain.py` and `validate-tracking.py --require-target` through repo Python.

Clean unused products regularly after verifying unique evidence. Historical
`build/native-*` directories were archived and removed; restore their retained
product only if needed. Current native/exact/VC4 caches, originals and manual saves
remain. `scripts/clean-local.py` previews cleanup and includes restored-CRT probe
directories. Its verified gzip fallback obeys the decompressed old seal; mutable
current products must never be hardlinked to immutable archives. Do not recursively
delete evidence trees or tool caches. Recent journals are
`.analysis/storage-cleanup-current-20261017/verification.json`,
`.analysis/storage-maintenance-20261017/verification.json`, and
`.analysis/game-prefix-direct-flow-20261017/verification.json`. They distinguish
allocated disk release from logical duplicate-byte totals.

The later `.analysis/historical-json-retention-20261017/receipt.json` records
205 unused raw JSON carriers compressed under existing immutable checkpoint
seals. Each has a single link and at least 256 KiB; every decompressed SHA-256
is verified before deleting the raw file. The unchanged seal still identifies
the logical bytes, and `clean-local.py` already accepts the `.json.gz` fallback.
Use `gzip -dc <historical-path>.gz > <historical-path>` to restore a historical
raw path if needed, then check its seal. This releases 301,236,224 allocated bytes
net of carriers, excluding receipt costs. Current source, reports, matching
objects, tested executable and valid CMake configurations retain their hashes.
The two rejected lifetime trials additionally archive and remove 50 raw files,
releasing 282,624 allocated bytes net of their verified archives. Their receipts
are `.analysis/paddle-joint-lifetimes-20261017/cleanup.json` and
`.analysis/lightning-crop-lifetime-20261017/cleanup.json`.

The independent-storage investigation additionally archives239 closed/superseded
files and releases4,927,488 allocated bytes net of verified carriers. Receipts are
`.analysis/independent-board-storage-20261017/cleanup.json` and
`superseded-cleanup.json`; the current29-owner tree/products and control producers
remain available for the next production checks.

Update only changed claims; refresh progress when ledgers change. Commit and push
verified checkpoints to `origin/main` with the English subject prefix
`gpt-6.1-sol: `. State the actual source question, evidence, checks and limits.
Disable opportunistic git GC for these checkpoints, verify the remote independently
with `git ls-remote`, and finish with `git status --short`. Do not mark the goal
complete because a fixture passes, all current rows have source, or a handoff is tidy.
