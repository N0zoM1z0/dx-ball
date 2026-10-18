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
| Accepted complete exact functions | 395 |
| Exact code / attached metadata bytes | 85,106 / 244 |
| Complete nonexact comparisons | 80: 20 authored / 60 runtime / 0 generated |
| Scoped semantic ledger rows | 249 |
| Entries without source | 78: 77 runtime / 1 generated |
| Inventory origins | 270 authored / 261 runtime / 21 generated / 1 unknown |

All 270 classified authored entries have source and complete current comparisons:
250 exact and 20 candidates across 30 compiler closures. The source-present
16-byte no-op at `0x40CC20` remains origin/prototype-unknown. Neither the final
authored denominator nor source optimality has been established. These inventories
are separate claims, not interchangeable completion percentages.

| Authority | Purpose |
| --- | --- |
| `config/functions.csv`, `function-origins.csv` | Provisional entries, reconciled extents and origins |
| `config/compiler-fragments.csv` | Retired aliases owned by complete C++ parents; not every internal block |
| `config/implemented.csv`, `matches.csv`, `semantic-acceptance.csv` | Source, exact and scoped semantic claims |
| `config/source-owners.toml`, `match-units.toml` | Source ownership; full compiler recipes, extents and bindings |
| `build/reports/exact-replay.json` | Current 395 accepted comparisons and producers |
| `.analysis/exact-candidate-audit-20261012/comparison.json` | Current 80 complete candidates; directory date is historical |
| [Remaining-functions table](../research/exact/REMAINING_EXACT_FUNCTIONS.md) | All candidate results and owner-note links |
| `.analysis/author-palette-debug-names-20261018/authored-coverage.json` | Current authored source/comparison/closure coverage |

Original `original/DXBALL.EXE`: English v1.07, 158,208 bytes, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
The pinned compiler is VC4 10.00.5270 and linker 3.00.5270; original CRT provenance
uses `.tools/msvc400/lib/libc.lib`. The compiler identity is
`f097e736bb04d38391c8b524945d58809ec4c42e97c056eca6f40bba2de910c3`.
Original compiler settings cannot be inferred solely from this candidate toolchain.

Keep `original/`, `.tools/`, `build/`, `.analysis/` and `ghidra-project/` private.
A source-only clone does not include the assets, tools, products or raw evidence.

## Current source and delivery

The [actual C1 editor writer/getter observation](../research/exact/VC4_C_FRONTEND_SYMBOL_KEYS.md#current-editor-writergetter-observation-october18)
uses one unchanged editor compile. Actual mode1 reads join the count key219
and local`i` key1178 to the same C1 store`406B04`, after counter INC`406AEF`.
These agree with the earlier sealed C2 keys under identical inputs/outputs;
there is no same-run wire/C2 claim. All464 getters join earlier object writes;
1,265 complete writer boundaries are established across six sites, with six
explicit unsupported counter paths among1,271 counter writes. All464 getter
MOV steps pass reviewed register/flag guards. Raw +8/context strings identify
these samples, not a universal ABI or complete object lifetime. Original Dr6
and complete post-MOV contexts are guarded by code rather than independently
replayable from raw logs. All14 units/223 bindings/12 literals,13 exacts/3,267
bytes and852 protected hashes remain unchanged before documentation updates;
this note and the C1 note leave850 other baseline hashes unchanged. Source,
delivery and250 authored exact/20 candidates remain. One CPU0/35%,384/512MiB,
capture peak166,559,744 bytes, zero memory events;9.205 seconds. No provider,
source variant, relink, game or replay. The selected current ID producer is
answered. Next seek independent original-source/translation-unit evidence for
a bounded declaration inference; do not repeat an unchanged current getter/C2
capture solely to rediscover these IDs or turn key arithmetic into a sweep.
Independent review reconstructs the actual joins and all14 full comparisons,
including40 local-target guards. All54 archived members pass size/SHA-256 checks
before35 temporary carriers, including one EXE/two objects, are removed; net
allocated space released is2,342,912 bytes. Current game/products/caches remain.

The [own-target C1 key investigation](../research/exact/VC4_C_FRONTEND_SYMBOL_KEYS.md)
adds the attested `vc4-c-frontend` REA route and retains57 observations in one
normally closed import. Actual C1 getter `4180DB` selects source`+18` low24
when mode`45662C` is nonzero; mode0 uses the separate source`+14` cache path.
The operator and format serializers call that getter. Three actual stores
`4185D9/419AA2/41AA8A` assign counter`455E14`, increment it and preserve the
source word's high8. The lazy path assigns only when low24 is zero. Counter16
and mode0 are initialized PE values, not observed editor runtime values. The
selected writers are not established constructors for editor`i` or count.
Next observe actual C1 mode/source identity and the relevant writer/record
relationship during the unchanged editor compile; do not transfer C1XX
addresses or begin declaration/name/order/type/flag sweeps. Twelve dispatcher
and nine provider-free lifecycle cases pass. Before documentation updates,
all849 hashes other than the two route scripts remain unchanged; this published
checkpoint also changes the existing REA/handoff notes, leaving847 other baseline
hashes unchanged and adding the C1 research note. Source and delivery remain
unchanged;250 authored exact/20 candidates.
No game compile, relink, runtime or replay runs. One CPU0/35%,384/512MiB and
256MiB heap hold. Whole-session peak403,206,144 bytes;5200 soft-high reclaim
events, no hard-max or OOM events. First-query wrapper timing is260,506ms and warm
queries reuse it; normal close removes the temporary project.
Independent passive review verifies all57 raw records/eight PE carriers and
the current847 baseline hashes. All88 archived members pass size/SHA-256 checks
before ten temporary carriers are removed. A byte-identical closed catalog is
shared; net allocated space released is8,769,536 bytes. Current observations,
snapshot, tested game and useful caches remain.

The [C-source comparison observation](../research/exact/VC4_EXPRESSION_ORDERING.md#c-source-comparison-observation-october18)
uses one unchanged editor compile through actual CL/C1/C2, with no C1XX process.
An existing sealed observer is reused without building or adapting it. All181
paired C2 calls/32 swaps pass their return guards. The complete selected guard
records count key219/load-rank32 and local `i` key1178/load-rank47; actual
call35 swaps children/opcode0x24→0x22, agreeing with the current count-loaded CMP.
All46 original/current instructions and eight branch successors are accounted;
find remains173/172/132. All14 full units/223 bindings/12 literals retain their
identities, including13 prior exacts/3,267 bytes and40 exact local-target guards.
Independent review verifies851 hashes and22 input modes/nsmtimes. Source,
delivery and250 authored exact/20 candidates remain. This does not observe
C1's internal key producer, original IDs or direct emitter-node identity; do
not transfer C1XX addresses/formulas or begin name/order/type/flag variants.
Next locate the actual C1 serializer/key producer and its transport to C2.
One observation takes4.186 seconds, peaks at160,743,424 bytes and retains one
CPU/35%,384/512 MiB with zero memory events. No provider, native build, oracle,
game, relink or full replay runs. A metadata-only instruction-count label
correction retains the original proof without rerunning it. Archive/member
verification precedes deleting21 temporary carriers, including one object and
one executable, releasing958,464 allocated bytes net. The reused binary stays
in its earlier verified archive; current tested products/caches remain.

The [related integer trigonometry](../research/exact/AUTHOR_SOURCE_CONTEXT.md#integer-trigonometry-and-material-scale-difference)
connects five complete DOS routines (524 bytes/192 instructions) to the game's
already exact initializer/raw-lookups/coordinate helpers (500 bytes/166
instructions/24 bindings/ten full literal references). Actual typed 361-entry
tables, fixups, calls and angle/origin writes establish the relationship.
Keep the material scale difference: DOS uses 1000, game uses 1024. The renderer
instead calls the separate exact floating wrappers eight times, with no raw
lookup call; no DOS formula explains its `2.046` or temporary partition. This
supplies no renderer source model or new name/type/scope/order/flag trial.
Independent review checks the raw artifacts, full current COFF-to-PE bodies and
all 851 protected hashes. Source, delivery and 250 authored exact/20 candidates
remain. No compile, provider, download, runtime, relink or replay runs, and no
object/executable is written. Passive helpers retain one CPU/35%, 384/512 MiB;
earlier helper peaks are unknown. The final summary/hash-check scope alone
peaks at 43,352,064 bytes with zero events. Archive/member verification precedes
removing twelve temporary carriers, releasing 217,088 allocated bytes net.
Current tested products and useful caches remain.

The [fixed paired palette iterator-scope model](../research/exact/AUTHOR_SOURCE_CONTEXT.md#fixed-author-palette-iterator-scope-model)
uses the related author's actual emitted procedure ownership for both signed
`i` locals. A complete raw 349-record walk and official Watcom scope consumer
exclude silently omitted block records; historical producer block retention
remains unknown. Earlier sources already compiled root `i` after RGB under
older names/left C, so this is one independently grounded joint inference,
not a first root trial. Move only the existing iterator after current RGB and
remove its plain loop wrapper in both functions. Two serial compiles compare
all 27 complete units/459 bindings: all raw/resolved code identities stay
unchanged, including 22 prior exacts/5,524 bytes; right remains 234/0 and left
234/3. Reject the whole pair without further name/scope/order/owner/flag variants.
Independent review verifies actual COFF bodies/bindings, 851 hashes and both
sources' original bytes/modes/nsmtimes. Current source, delivery and 250 authored
exact/20 candidates remain. The full affected comparison takes 7.609 seconds,
peaks at 166,141,952 bytes, and uses one CPU/35% and 384/512 MiB with zero
memory-limit events. No provider, native build, oracle, game, relink or full
replay runs. Archive/member verification precedes removing 21 obsolete raw
carriers, including two objects, releasing 569,344 allocated bytes net.
Current tested products and useful caches remain.

The [fixed paired RNG declaration model](../research/exact/AUTHOR_SOURCE_CONTEXT.md#fixed-author-rng-declaration-model)
binds two full DOS helpers (108 bytes / 51 instructions), actual typed `num`
records and three actual CRT/clock calls to the game's complete 31/49-byte helpers. Preserve
the Win32 unsigned clock/DIV difference. One inferred `rnd/rndseed/num` pair
changes 50 public plus eight local/prototype tokens in nine shared files.
All 11 actual affected owners compile once: 122 whole functions/3,338 bindings/
177 full literals, all raw/resolved code identities unchanged, including 113
prior exacts/42,881 bytes and nine candidates. Reject the whole pair without
name, subset, owner or flag variants; no API aliases or test-export changes are
adopted. Independent review verifies the complete primary witness, comparisons,
source transform, 851 hashes and nine files' original bytes/modes/nsmtimes. Current
source, delivery and 250 authored exact/20 candidates remain. Total affected
compile/comparison takes 28.799 seconds, peaks at 207,253,504 bytes, and uses
one CPU/35% and 384/512 MiB with zero memory-limit events.
No provider, native build, oracle, game, relink or full historical replay runs.
Two passive pre-output assertion corrections are retained, without compiler
retries. Archive/member checks precede deleting 58 obsolete raw carriers,
including 11 objects, releasing 3,624,960 allocated bytes net. Current products
and useful caches remain.

The [historical Microsoft header model](../research/exact/CLOSED_STORAGE_DIAGNOSTICS.md#historical-microsoft-directdraw-header-october18)
tests a complete 103,774-byte 1994–1996 `ddraw.h` from a pinned VC4.2 repository;
the actual compiler/libraries stay VC4.0. Header release/original-game use remain
unproved. Its real offset 20 mipmap union differs from the modern header, while
the original consumed 108-byte descriptor/v1 methods agree. Two fixed C/C++
compatibility compiles pass first try. One subsequent resource compile compares
all 18 functions/262 bindings/six literals: release privately becomes 262 exact,
bank/PCX each lose one difference, but five prior exacts regress. Reject the
entire 30-owner/278-unit model; other 29 owners/260 units remain uncompiled.
Do not adopt favorable owners or retry header/include-position variants.
Independent review recomputes all results and both fixture objects. All 851
hashes survive; 17 staged files regain bytes/mode/nsmtime and two new headers
are removed. Current source, delivery and 250 authored exact/20 candidates stay
unchanged. Resource compile takes 3.399 seconds with a 163,635,200-byte peak;
the compatibility pair takes 5.719 seconds with a 157,458,432-byte peak.
One CPU/35%, 384/512 MiB and zero memory-limit events hold. No provider, native build,
oracle, game, relink or full replay runs. Archive/member checks precede deleting
68 obsolete raw carriers, including three objects, releasing 1,150,976 allocated
bytes net. Current products/caches remain.

The [fixed drawing parameter model](../research/exact/AUTHOR_SOURCE_CONTEXT.md#fixed-author-drawing-parameter-declaration-model)
uses the retained complete DOS `num/x/y` index/coordinate witnesses for one
four-function,16-token inference. The earlier missing-operation gate was an
uncompiled conceptual decline and is withdrawn. One resource compile compares
all18 complete functions/262 bindings/six full literals: every code identity
remains unchanged, including13 prior exacts/3,050 bytes. The complete12,332-byte
COFF differs only at two parsed timestamp bytes. Reject the entire fixed model
without further spelling, subset or context variants. Independent review
verifies all851 protected hashes and original source bytes/mode/nsmtime; source,
current delivery and counts remain unchanged. The compile takes4.186 seconds,
peaks at161,742,848 bytes, and has zero memory-limit events under one CPU/35%
and384/512 MiB limits. No provider, native build, oracle, game, relink or full
replay runs. Archive/member checks precede deleting20 obsolete raw carriers,
including both objects, releasing421,888 allocated bytes net. Current products
and useful caches remain. The tighter384/512 MiB defaults now appear in
AGENTS and the REA instructions; reuse retained compiler evidence instead of
repeating the already answered NameMap/mode/ID/cursor investigations.

The [fixed capture/release declaration model](../research/exact/AUTHOR_SOURCE_CONTEXT.md#fixed-author-capturerelease-declaration-model)
connects the newly checked complete DOS `getshape` allocation/null/publication
and indexed metadata roles to the game. Actual debug names support one paired
`num`/`new_shape` inference, preserving all Win32 operations. DOS capture has no
delete call; the game's preliminary release and additional COM/record/slot
cleanup are explicit differences. One compile compares all eighteen resource
units/262 bindings/six full literals. Every code identity stays unchanged;
thirteen prior exacts/3,050 bytes survive. The entire 12,332-byte COFF differs
only in two file-header timestamp bytes. Reject the whole model without name,
subset or owner variants. All 851 hashes and original source bytes, mode and
nanosecond mtime are restored and independently verified. Archive/member checks precede deleting
nineteen obsolete raw carriers, including two objects, releasing 503,808 allocated
bytes net. Current products and caches remain. Peak memory is 171,053,056 bytes
under one CPU/35% and 384/512 MiB limits, with zero memory-limit events. No native
build, provider, oracle, game, relink or full replay runs. Current totals and
delivery remain 250 authored exact / 20 candidates and 395 total exacts.

The [fixed author palette declaration model](../research/exact/AUTHOR_SOURCE_CONTEXT.md#fixed-author-palette-declaration-model)
adopts one paired `r/g/b/mode` inference from actual debug-bound rotation roles.
Right rotation becomes complete 234/0 exact; left rotation improves 234/9 to
234/3. Only six original RGB frame-home bytes recover per function, with no lost
matches. Two private compiles compare all 27 units and 459 bindings, retaining
21 prior exacts/5,290 bytes and 25 other code identities. Independent result
review verifies all 851 protected hashes and both source modes and nanosecond mtimes before
adoption. Native compilation touches only the two changed sources; 146 unchanged
existing checks pass. VC4 then reuses all 117 objects with zero game compiles.
Full PE verification accounts for twelve palette bytes and twelve parsed
timestamp bytes only; all 1,099 MAP records, 4,488 HIGHLOW sites, resources,
imports and nineteen CRT dependencies remain. Current totals are 250 authored
exact / 20 candidates and 395 total exacts / 85,106 code bytes / 244 metadata
bytes. The private compiler peak is 188,338,176 bytes under one CPU/35% and
384/512 MiB limits, with zero memory-limit events. No provider, game or full
replay runs for this source adoption. Keep the whole paired model; do not try
additional spellings or scopes from this result alone.
Independent integration review passes. Archive/member checks precede removing
55 obsolete raw carriers, including six objects and six production-history
files, releasing 7,397,376 allocated bytes net. Current products, useful caches
and the directly referenced `compiled.json` receipt remain. All 835 protected
files outside sixteen intentional changes retain their hashes. A cleanup
preflight corrects the history count before any archive/deletion; no completed
producer is repeated.

The [DX-Ball 2 installer check](../research/exact/AUTHOR_SOURCE_CONTEXT.md#dx-ball-2-v12-installer-boundary-october-18)
independently validates 77 CRC streams, 61 main file records and the real sequel
PE, without execution or extraction of a game executable. It has no named main
source/PDB/MAP attachment or PE debug directory. All 34 selected whole byte-clone
checks miss; modified common source remains possible. This package supplies no
new 1.07 declaration or compiler fact. Archive/member verification precedes
removing sixteen raw carriers, including the download, releasing 319,488 allocated
bytes net. The initial REA entry peaks at 671,473,664 bytes with 473 soft-high
events and zero hard-max/OOM events; subsequent readers use 384/512 MiB limits
and remain below 50 MB. Reuse the sealed evidence without another import.

The [fixed author image-record declaration model](../research/exact/AUTHOR_SOURCE_CONTEXT.md#fixed-author-image-record-declaration-model)
uses actual debug-bound `shp`/`SHAPE`, `letter` and `yoffset` roles as one inferred
1.07 declaration, preserving the game's 44-byte layout and signed letter. One
resource compile compares 18 whole functions, 262 bindings and six full literals.
Release-sprite becomes privately exact and bank/PCX each lose one difference,
but four prior exacts are lost. Reject the entire model without adopting gains;
27 owners and 254 units remain uncompiled. All 851 protected hashes and four
staged files' bytes, modes and nanosecond mtimes are restored and independently
verified. Archive/member checks precede deleting 21 obsolete raw files, including
the sole private object, releasing 966,656 allocated bytes net. Current products
and caches remain. The single compile takes 3.898 seconds on one CPU/35%, peaks
at 170,913,792 bytes and records zero memory-limit events. No provider, relink,
game, oracle or full replay runs. Source, delivery and totals remain unchanged:
249 authored exact / 21 candidates, 394 total exacts. Do not retry spelling,
alias, subset or owner variants of this closed fixed model.

The [genuine SDK interface model](../research/exact/CLOSED_STORAGE_DIAGNOSTICS.md#genuine-sdk-interfaces-october18)
uses actual installed DirectDraw/IUnknown declarations, which earlier custom
interface controls did not test. A fixed VC4 feature-detection bridge makes
both unchanged SDK C/C++ fixtures compile after two retained initial failures.
One subsequent resource compilation compares 18 whole functions/262 bindings/six
literals: zero gains, two prior exact losses, bank1475/64→1486/943. Reject the
entire model; its other 29 owners/260 units remain uncompiled. Current source and
all 851 protected hashes survive; 17 staged files also regain their original
mtime/mode, avoiding cache invalidation, and two new headers are removed.
Independent result review passes. All 69 obsolete raw carriers, including three
private objects, are archive/member-hash verified before deletion, releasing
917,504 allocated bytes net. Current products and caches remain. Peak scope
memory is 198,963,200 bytes across the four small compatibility attempts and one
game-owner compile, all serial under one CPU/35%, with zero memory-limit events.
No provider, relink, game, oracle or full replay runs; totals remain 249 authored
exact/21 candidates. Do not try spelling/header-placement/owner variants of
this closed fixed model.

The [actual bank declaration inference](../research/exact/BANK_ALLOCATION_SCOPE.md#actual-author-declaration-inference-october-18)
adopts one fixed seven-role model from the author's debug-bound DOS loaders.
The prior conceptual decline of this identical uncompiled model required a
missing Win32 operation and was too restrictive; that condition is withdrawn.
All game types/scopes/order/member names/operations remain. Bank1475/66→1475/64
recovers both yoffset EBP−48 sites without losing a matching original byte;
17 companions and13 exacts/3,050 bytes survive18 complete comparisons/262
bindings/six literals. Ten unchanged existing bank cases pass. Native/MinGW
each compile32 sources after old trial restores invalidated mtimes; completed
builds are not repeated. VC4 compiles31 production objects/reuses86, with only
resources.cpp content changed. Full PE verification accounts for18 bank bytes
plus18 parsed timestamp bytes; all1,099 MAP records and other PE bytes remain.
No game/provider/full replay runs. Current counts remain249 authored exact/21
candidates. Separate current-input metadata corrects179 pre-existing helper
hash fields; historical semantic cases/scopes are unchanged. Independent final
review passes. Archive/member verification precedes removing59 obsolete raw
carriers, including36 production-history files, releasing7,876,608 allocated
bytes net; current tested products and useful caches remain. Do not try name
or scope variants of this closed fixed model.

The [fixed author global declaration model](../research/exact/AUTHOR_SOURCE_CONTEXT.md#fixed-author-global-declaration-model)
tests actual DOS `fontspacing`: signed int, fixup-bound metric read and initial
value 1 support one same-role inference. Only that identifier changes in two
canonical files. Six serial compiles compare all 67 affected functions/1,276
bindings/95 complete literals; every code identity stays unchanged, including
59 accepted companions/17,310 bytes. Reject as an exactness improvement without
spelling variants. All 49 protected canonical hashes are restored. Nineteen
archive/member-verified raw carriers, including all 12 temporary objects, are
removed, releasing 1,163,264 allocated bytes net; current products/caches remain.
Peak memory
is 292,687,872 bytes under one CPU/35%, with zero memory events; no game,
provider, relink or full replay runs. A separate three-query
[PCX decoder-flow search](../research/exact/EXACT_PCX_PACKET_LOOP.md#bounded-decoder-flow-source-search-october-18)
finds no connected primary source in returned excerpts; it does not depend on
the unproved 132-byte header. Current totals remain 249 authored exact/21 candidates.

The [pinned 1.07 installer boundary](../research/exact/AUTHOR_SOURCE_CONTEXT.md#pinned-107-distribution-and-installer-boundary-october-18)
binds all 64 CRC streams and 52 observed old-format file records. The actual
installer game is byte-identical to the current target, so no game import or
code replay follows. Both inspected repacks also contain the same pinned files;
no new declaration or compiler-setting evidence follows. Modern Wise records
are not compatible with this installer's observed 19-byte prefix. Auxiliary
stream roles remain limited; do not claim blanket source absence. Independent
review passes. All 11 protected authority/original/delivery hashes and current
249 authored exact/21 candidate claims remain fixed. Thirty-nine raw evidence
carriers are archive/member-hash verified and removed; retired producers and
both complete REA archive responses remain in the private phase archive. No
new object or executable is written; current products and caches remain.

The [clock-kind eligibility recheck](../research/exact/EXACT_WINMM_CLOCK_IMPORT.md#clock-kind-eligibility-recheck-october18)
declines another compilation: the later C++ shared-timestamp control already
covers the type/signature contract; the narrower header placement has no new
original ownership support. Nine low-word timer source queries find no connected
C/C++ elapsed/wait source in returned excerpts; full responses are compressed
and hash verified. Current wait170/8, elapsed81/3 and reset426/20 retain matching
source/object authority hashes. The WinMM note now labels its waiting exact as
historical. No source/product/claim change, compile, provider, runtime or replay.

The [complete C DirectDraw table control](../research/exact/CLOSED_STORAGE_DIAGNOSTICS.md#complete-c-directdraw-table-october18)
completes20 opaque method signatures without changing23-slot layout, called
slots or bodies. Four compiles/47 full units/721 bindings/six literals produce
three candidate exacts but lose11 prior exacts; reject the entire model without
subsets or variants. Uncompiled header consumers are not claimed unchanged.
All36 protected canonical hashes remain fixed, including the restored header,
matching objects and delivery. Totals stay249 authored exact/21 candidates.
One CPU/35%, peak190,787,584 bytes, zero memory-limit events; no provider,
runtime, relink or full replay. Private
`.analysis/ddraw-c-vtable-contract-20261018/` retains the independent result
review and archive/member-verified cleanup of13 closed pilot carriers, releasing
675,840 allocated bytes net. Current tested products and useful caches remain.

The latest [author DOS-demo investigation](../research/exact/AUTHOR_SOURCE_CONTEXT.md#author-dos-demo-with-complete-debug-records-october18)
finds genuine Watcom debug records in the author's previously unread`plasm.zip`:
145 modules and57 typed author procedures with actual`sprite.c`/`misc.c` cues.
The custom SBK framing and complete fixup-bound font routines connect directly
to the pinned game's families. Foreign packed17-byte records and register ABI
are explicit differences. Actual`fontwidth` records identify inner`i`/outer`j`
and parameters`size,array`; lexical declaration order and original1.07 spelling
remain unknown. One independently reviewed fixed declaration model compiles at
the canonical UI source path, then restores it. All seven full bodies/38 actual
bindings retain identical code; measure279/3 and right-palette234/6 remain
candidates. Reject this model without permutations. No exact count, source,
recipe or delivery change; no game, relink or full replay. Compiler peak is
276,594,688 bytes on one CPU/35%, with zero memory-limit events. Reuse the
retained complete debug/fixup proofs; do not repeat archive inventory or this
text hypothesis. Complete related palette bodies retain real endpoint, step,
mode and ABI differences; they supply no missing game operation or justified
declaration trial. Their full proof is compressed and hash verified. The UI
model's17 copied inputs/products, including both objects, are archive/member-
hash verified and removed; protected current products and caches remain.
The independently reviewed complete bank loaders establish the shared
allocation/publication/read/field-write core. DOS old-count/frame ownership
differs from the game's slots1..253 and surface-upload/temporary-bitmap cleanup;
there is no missing game producer or justified name/root-scope model. Its
256,420-byte full proof is retained as a38,174-byte roundtrip-verified gzip.
All three related families are now closed evidence boundaries, not pending
declaration trials.

The later [three DOS drawing wrappers](../research/exact/AUTHOR_SOURCE_CONTEXT.md#drawing-wrapper-boundary)
add105 complete instructions/6 real calls/9 actual fixups. Their separate
`fg_move(x,y)` and height/width/pixel calls differ from the game's explicit
banked surface/source-rectangle COM interface. The47-byte DOS deletion proof
was already complete and is reused. No missing game operation or justified
parameter-name/context model follows. Current draw/blt/release hashes and all
claims remain unchanged; there is no compiler/provider/runtime/replay. Private
`.analysis/author-plasma-draw-delete-boundary-20261018/` retains the independent
review and roundtrip-hash-verified compressed proof; no new build product or
executable extraction is created.

The later [Classic 1.09 installer inspection](../research/exact/AUTHOR_SOURCE_CONTEXT.md#classic-109-installer-boundary-october18)
uses REA 6.5.0 root inventory and independently verified Wise framing: 65 CRC-valid
streams, 51 typed records and 49 main paths. The bound game has no COFF symbols
or PE debug directory; none of the 49 main paths names source/PDB/MAP. No new
1.07 declaration or settings fact follows. Eighteen copied decoder/HTTP carriers
are archive/member verified and removed; no raw game member is extracted.
Current `elapsed`/`reset-round` and paddle residual reviews also find no missing
producer: swapped unsigned comparison, equivalent bank/slot address scheduling,
and known frame homes respectively. Paddle's dirty rectangle is a pre-COM
snapshot, queued by value afterwards; it cannot be delayed or merged with the
source-rectangle pointer. Reuse the private `runtime-residual-frontier-20261018`
and `paddle-residual-frontier-20261018` receipts. No compile, native provider,
game, relink or replay runs for these follow-ups; all current authorities remain
unchanged.

A fresh [current PCX proof](../research/exact/EXACT_PCX_PACKET_LOOP.md#current-object-correspondence-refresh-october18)
replaces the historical205-direct/22-grouped partition for the current object:
202 direct instructions plus seven exchanged signed comparison triples and two
product pairs cover all227. All30 branches/10 calls/8 bindings/full literal
verify;18 EAX/flags CFG walks end at defined overwrites. Original four unused
frame bytes remain unknown. The [clock rejection recheck](../research/exact/LIGHTNING_EXPIRY_SCOPE.md)
also corrects an old private receipt: the second sample's EBX producer was
already present; the two rejected controls still reverse the first time/RNG
calls. Neither passive review changes source or calls for another trial.
The later [actual1.09 loader comparison](../research/exact/EXACT_PCX_PACKET_LOOP.md#successor-loader-boundary-october18)
binds its full637-byte/201-instruction body and corrects the decompiler's argument
count from real ESP flow. Its128-byte header has no new field access; another
unused four-byte tail does not establish a132-byte declaration. Close this
related-version check without a source trial; reuse its archived proof.

The current restored-CRT executable is
`d5dca81954937a6f9f3212fb041a1aed02f455b037dea0d9b7997a19a98587f6`.
Its recipe is `vc40-restored-crt`: 117 source objects from 114 owners plus three
integration owners, 19 pinned CRT members, `/NODEFAULTLIB /OPT:REF`, six OS DLLs
and no MSVCRT DLL. The image, map and full input/object identities are in
`build/vc40-restored-crt/build.json`. Reuse only after checking the complete closure.

The latest [lightning crop-producer recovery](../research/exact/EXACT_LIGHTNING_CROP_CHAIN.md)
adopts exactly two direct excess subtractions. A passive review of the sealed
old diagnostic corrects its false unsupported-simplification rejection: both
full original13-instruction/44-byte crop chains survive. Current C++ last-brick
shrinks1067→1061 bytes; strict raw differences990→992 reflect suffix shifts,
not a lost original producer. It remains a candidate: explicit time-before-RNG
sampling, frame68 versus original64 and original EBX time preservation remain.
All20 full display bodies/421 bindings compare;19 companion code identities
and16 exacts/4,628 bytes survive. Current totals stay394/84,872/244 and21 authored
candidates. Native/MinGW each compile only display using valid caches;197
existing deadline/crop cases pass with the verified fixture.235 semantic input
inventories/16 source hashes refresh; all249 case/scopes remain historical.
VC4 reuses117 objects/19 CRT members with zero compiles. All1,099 owner-qualified
MAP records remain identical. Both full linked bodies/51 bindings verify within
the unchanged1072-byte padded span. All318 changed PE bytes are explained:
292 body/padding,14 loader and12 parsed timestamp bytes. Thirteen changed DIR32
sites explain the exact4,488-HIGHLOW set; both complete loader directories are
reconstructed. All other PE bytes/resources/imports remain unchanged. No new
provider, full replay or game run. Private
`.analysis/lightning-excess-producer-20261018/` retains producers, independent
reviews, focused cases and linked proof. Archive/member-hash verification precedes removal of51 raw files, including
six objects and12 superseded VC4 history copies, releasing8,658,944 allocated
bytes net of archive/journal. Current tested products and useful caches remain;
the regular cleanup preview finds zero further disposable items.

The later [complete retained rotation-origin review](../research/exact/ROTATION_ORIGIN_STORAGE.md#complete-retained-model-tradeoff-october18)
reuses the existing fixed nested/current objects and fills its78→365 instruction
boundary. All five comparisons/115 bindings/25 literals reverify. Both renderers
have identical complete role-normalized operations across424 bytes/36 roles:
349 instructions agree with original directly and16 belong to explicitly
checked compare/product/finite-row-add groups. All22 calls/26 branch targets
agree;30 scratch-register CFG walks pass. Current eight bank-address groups
already have original forms after frame translation. Nested restores19 concrete
renderer instructions/56 physical frame-role bytes with no renderer loss, but
horizontal offset loses16 original producer instructions and its259-byte exact.
The family521→524 concrete-instruction match count is not a full-function gain
or source-optimality proof; keep canonical394 exact/21 authored candidates.
Original named/temporary allocation order remains unknown; do not infer an
impossible464-byte frame from unsupported parent-first/no-reuse assumptions.
Private `.analysis/rotation-nested-origin-complete-20261018/` retains the complete
proof, source/object identities and independent review. Two extracted object
copies are removed only after their existing sealed archive members reverify;
current tested products/caches remain. No compiler, provider, solver, emulator,
runtime case, relink, game or full replay follows this passive review.

The [actual rotation scope-output observation](../research/exact/ROTATION_ORIGIN_STORAGE.md#observed-scope-output-and-fixed-root-local-model-october18)
then observes23 root symbols/340 bytes before five visible locals/20 bytes in
the current renderer. Eight snapshots pair with guarded MOV single steps;
all five complete output bodies/115 bindings/25 literals remain unchanged.
Actual scope names identify the renderer; recycled owner addresses and event
order do not identify the other snapshots. This supports one fixed all-five-root
declaration hypothesis, preserving every expression and both first-term locals.
Its single compilation retains four exact helpers/900 bytes but changes renderer
1458/1466→1443/1470. Full365 role instructions agree; concrete original matches
fall241→239 and physical frame-role bytes32→24, with no restored home/instruction.
Reject the model, keep canonical counts/delivery, and do not combine the earlier
nested model or start scope permutations. Current C2 named/scratch allocation
events, cursor reset and reuse remain the specific missing mechanism facts.
Private `.analysis/rotation-scope-output-list-20261018/` and
`.analysis/rotation-visible-root-20261018/` retain full comparisons/reviews.
Observation cleanup removes11 archive-verified copied inputs/products, releasing
192 KiB net; the fixed model's ten copies/products release44 KiB by the same
verified archive procedure. Current caches and tested delivery remain. Both heavy steps use
one CPU/35%, peaks288,722,944/164,306,944 bytes with zero memory-limit events.
No provider, native build, runtime case, game, relink or full replay runs.

The later [NameMap key-producer investigation](../research/exact/VC4_FRONTEND_SYMBOL_ORDER.md#namemap-key-generation-october18)
checks full472-byte C1XX48B887 and the actual CASE5 encoding blocks. Ordinary
named keys use a NameMap query, preserve the source symbol's low3 flags and
return`(output_index+16)&1fffffff`; cache reuse occurs in the caller. The actual
MSPDB40 NameMap::open import supplies the queried object. Scope hashes/masks,
prepared names and numeric keys remain distinct. No bare-name/method-name or
original-name recovery is claimed. Next observe actual C1 key/cache/bytes against
current C2+24, with unchanged inputs and complete affected comparisons; do not
start name/order/context variants. One fresh explicit profile omits the timed-out
parameter analyzer, retains old115 records in their existing sealed carrier,
and closes with74 new Evidence records/71 direct results. First query327,899ms;
owned temporary database is removed. Private `.analysis/frontend-key-producer-20261018/`
retains checks/review. No game source, build, exact claim, replay or delivery change.
Verified snapshot retention, immutable-catalog sharing and duplicate-log removal
release10,043,392 allocated bytes net; current game caches and tested delivery stay.
A first unchanged resources observation then finds zero hits at mode-zero cache
branch44A1F4, although all compiler processes exit0; observer exit1 explicitly
marks missing C1 samples. C2 has116 guarded hits and20 bank records. All18
functions/262 bindings/6 literal references remain unchanged; no C1 mode,
NameMap or transport linkage is established. The raw local names lack the
function tag's leading underscore. Private `.analysis/frontend-wire-reader-20261018/`
retains this bounded negative. Twelve archive-verified copies/products are
removed, releasing225,280 bytes net; peak292,057,088 bytes, zero memory events.
The [common-entry follow-up](../research/exact/VC4_FRONTEND_SYMBOL_ORDER.md#actual-transport-modes-october18)
then observes28 C1 samples, all mode1/source+18 low24 with unchanged+14 and
actual2-byte wire IDs. All stream flags2/3/4 select6090. C2 mode0 records16 bank
locals with one matching key/raw name/function tag/encoding correspondence each;
width28281 actually writes796e. No C2 stream byte positions or NameMap output
are observed. All413 MOV hits are stepped,18/262/6 complete comparisons stay
unchanged, peak181,526,528 bytes and zero memory events. Private
`.analysis/frontend-mode-wire-reader-20261018/` retains the evidence. Next find
the actual source+18 numeric-ID writer in this mode; the static NameMap branch
is a different path. No names/scopes/flags/context trials follow automatically.
The [low24-writer investigation](../research/exact/VC4_FRONTEND_SYMBOL_ORDER.md#low24-id-writers-october18)
then checks121 reported direct counter references/40 increments:34 complete
+18 stores across32 windows are distinct from output/tag helpers and+14 cache
writes. Counter PE initial value16 is a static fact, not a sampled runtime reset.
One reused-profile import closes with141 Evidence records/67 new direct results,
one indexed invalid procedure lookup; the owned temporary database is removed.
Private `.analysis/frontend-local-id-producer-20261018/` retains the proof and
verified snapshot; closed-catalog sharing releases8,695,808 allocated bytes net.
The actual40AA3F write observation subsequently links all16 bank locals to
later CASE5 source reads by same PID/TID/address/raw name/function tag/fullword
and order. All17,462 MOV hits are checked (17,221 writer/241 reader), while only
28 selected pairs/56 step logs are printed. IDs agree with the earlier wire
capture, without repeating C2/wire traps or excluding other writers/object reuse.
Full18/262/6 comparisons stay unchanged; peak215,941,120 bytes/events0, one
CPU35%. Private `.analysis/frontend-local-id-write-observation-20261018/` retains
the capture. This current-ID producer question is answered for the selected
samples. Return to the remaining game differences and concrete C2 scratch
allocation/cursor-reset/reuse facts; no further name/order/context/namespace
survey or source variant follows automatically.
Twelve archive/member-hash-verified copied inputs/products are removed, releasing
229,376 allocated bytes net. The exact next C2 gap is47EA40 cursor save/restore/
reset across named-record and body-temporary stages. Existing backend run
`2026-10-17T14-59-10.027Z-interactive-3840208` records05/13 already cover
401551→40AED4, cursor subtraction/alignment and401556 record+4 write. Query
`xrefs47EA40` and `40AED4` incoming references, then only uncovered actual cursor
writes/non401551 callers. Do not re-query the complete helper or infer scratch
allocation solely from renderer344+80/current360+64 or PCX312/308 frame sizes.

The [cursor/reset investigation](../research/exact/VC4_BACKEND_SYMBOL_RECORDS.md#cursor-resets-and-later-home-reassignment-october18)
then closes 26 new direct records/112 total using the same C2 profile. Eight raw
carriers/2,442 bytes match pinned C2. Five reported direct cursor writers include
two resets. Beyond initial named allocation, actual callers allocate internal
kind`0x18` records and later special/sequential/grouped homes. `41EE56` can reset
the cursor and rewrite record`+4`; `4304F8` can share a group base or store
`group_base + group_size - record_size`. These mechanisms invalidate assuming
initial homes are always final; current renderer branch, liveness semantics and
original storage remain unknown. This motivates one unchanged rotation observation
before drawing a source model. The provider is closed and owned temporary tree
removed. Private `.analysis/backend-frame-cursor-20261018/` is sealed and
independently reviewed; catalog sharing releases 8,683,520 allocated bytes net.
Sampled peak 672,075,776 bytes includes soft reclaim, with zero hard/OOM events.
No game compile/replay, source or exact/delivery changes in this static phase.

The accompanying passive frame review confirms no unassigned renderer byte and
disproves universal 8-byte alignment using original doubles 20 bytes apart, while
leaving phase-specific allocation alignment open. PCX's original 128-byte header
occupies−192..−65; the four-byte gap−64..−61 has no established typed consumer.
Three new public-source queries for short screen-size fields/filler58 yield no
qualifying original declaration. Private
`.analysis/pcx-extra-screen-fields-source-search-20261018/` retains this bounded
negative with verified compressed responses; it does not justify a 132-byte
header or another declaration trial.

The following [actual rotation allocation observation](../research/exact/VC4_BACKEND_SYMBOL_RECORDS.md#observed-rotation-allocations-october18)
completes that single unchanged `/MT` compile: 246 guarded steps, comprising
48 allocator calls/four sites each, six initial resets, 32 named-home and
16 internal-home writes. Renderer records match 28 current names/360 bytes,
then eight internal records of eight bytes extend the frame to 424. Alignment
is actually four. Four helpers each have one eight-byte named record and two
four-byte internal records. Later reset/special/sequential/group writes have
zero hits; there is no manager-entry trap, so do not infer skipped versus early
return or exclude aliases. The reset tag still names the previous function.
All five complete functions/115 bindings/25 literals remain identical; peak
269,717,504 bytes, zero memory-limit events, one CPU35%. Private
`.analysis/backend-frame-runtime-20261018/` retains exact states and comparisons.
This answers the selected current allocation mechanism. Return to concrete
remaining game differences; it does not recover original declarations or
justify more identifier/order/flag/context sweeps or another unchanged compile.
Archive/member-hash verification precedes removal of eight copied inputs,
two objects and the observer executable; private Python cache removal is also
recorded. Net release is 208,896 allocated bytes, preserving current tested
products and useful build caches. No source, exact count or delivery changes.

The preceding [actual line comparison observation](../research/exact/LINE_LOCKED_CURSOR.md#actual-backend-comparison-decisions-october18)
compiles the unchanged drawing-primitive owner once under an owned C2 observer.
All62 helper entries/returns pair;55 belong to line and seven to fill. Current
scalar-load ranks i43/dx44/dy45 follow actual record keys and the retained
opcode30 transformation, not the bare symbol rank. The three dx/dy, i/dx and
i/dy calls actually swap their children and remap opcodes; role-based comparison
accounts for all nine residual bytes across all121 instructions. Both complete
bodies stay byte-identical:line445/9 andfill85exact. No original intermediate
keys or emitter-consumption identity is observed; do not infer original names
or start guard/name/scope/type/header/order/flag sweeps from this result.
`.analysis/line-backend-comparisons-20261018/` retains all primary/secondary
identities, full trace, comparisons and independent reviews. Original/production
source, objects, delivery and current counts remain unchanged. One CPU/35% and
640–768MiB caps hold; peak210,264,064 bytes, zero high/max/OOM events. No new
provider, native/MinGW game build, runtime case, relink, game or full replay.
Archive/member-hash verification precedes removal of16 raw files:13 copied
inputs, two objects and the observer executable, releasing208,896 allocated
bytes net of archive/journal. Primary trace and proofs remain; current tested
products and valid caches are preserved.

The later [fixed role-rank inference](../research/exact/LINE_LOCKED_CURSOR.md#fixed-role-rank-declaration-inference-october-18)
independently accounts for all 55 line events and tests one existing-variable
declaration cohort. All three comparison directions recover, but i/error/dx
homes cycle: line445/9 becomes445/22; fill85 stays exact. Reject the complete
model, with no follow-up declaration variants. Canonical 13 inputs and six
authorities/products remain unchanged. One compile takes 6.103s with 273,899,520
peak bytes and zero high/max/OOM events; no full replay or runtime check runs.
Member-verified archival removes 16 private copied inputs/products/proposal,
releasing 61,440 allocated bytes net. Receipts remain under
`.analysis/line-rank-declarations-20261018/`.

The preceding [drawing-primitive owner](../research/exact/DRAWING_PRIMITIVES_OWNER.md)
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

The later [independent hit-region owner](../research/EDITOR_OWNER.md#closed-hit-region-implementation-owner-october18)
moves six consecutive original functions and their exclusively accessed real
array/count into one C file, retaining full editor.h and every body. Selected
tile stays in editor. Two fixed compiles compare all14 units/223 bindings/12
literals: every full identity is unchanged,13 exacts/3,267 bytes survive, find
stays172/132. Independent review checks all265 editor-key switch bytes and20
actual local targets. Reject without class/header/type/name/order/flag variants.
`.analysis/hit-regions-owner-20261018/` retains full receipts; no canonical
source, claim or delivery changes, and no provider/runtime/full replay follows.
Archive/member verification precedes deletion of26 raw inputs/products including
three objects, releasing116 KiB net. Together with the nested-origin control,
this checkpoint removes36 raw files/five objects and releases160 KiB net;
current tested products and valid caches remain. Peak208,924,672 bytes with no
high/max/OOM events. The standard cleanup preview finds no other registered
disposable products.

The later [local FixedPoint aggregate control](../research/exact/TRIANGLE_SCANLINE_SCOPE.md#local-aggregate-compiler-control-october18)
answers the previously untested local `/Od /Ob0 /GX` EH question in one small
compiler fixture. Four independent roots produce four parent states; a plain
two-member aggregate plus two roots produces three, with separate129/120-byte
implicit ctor/dtor and internal partial-construction cleanup. Full11-section/
61-relocation review passes. It does not match the original triangle machinery;
no game slope-pair compile follows. Sealed
`.analysis/fixedpoint-local-aggregate-20261018/` archives/member-verifies then
removes five raw carriers/one object, releasing92 KiB net. Canonical game source,
products and counts stay unchanged; no provider/runtime/relink/full replay.

The later [capture/load/release lifecycle owner](../research/RESOURCE_OWNER.md#closed-captureloadrelease-owner-october18)
tests three unchanged bodies backed by consecutive original entries and their
actual allocation/publication/free protocol. Two compiles compare18 complete
functions/262 bindings/six literals. Capture852exact→864/726 loses its match:
12 bank/slot address groups each grow one byte. Release269/245 is unchanged;
bank1475/66→1475/65 and PCX979/851 change only local product/guard producers.
Fifteen full identities/12 exacts survive; reject the whole model, with no
selective retention or variants. Sealed
`.analysis/sprite-lifecycle-owner-20261018/` archives/member-verifies and removes
13 raw files/three objects, releasing72 KiB net. Along with the local aggregate
control this turn removes18 raw files/four objects, releasing164 KiB net.
Canonical source, claims and delivery remain unchanged; no native, provider,
runtime, relink or full replay. Both scopes stay below158 MB with zero high/max/
OOM events. The separate endpoint-bias source search remains a four-query
negative, with compressed complete responses and an explicit zero-slope wording
erratum; it supplies no original polygon declaration or compiled source model.

The [RLE run-index scope](../research/exact/EXACT_PCX_PACKET_LOOP.md#closed-rle-run-index-lifetime-october18)
closes an uncovered declaration-only question: old C++ header/value/workspace
models all kept run-index at root. One compile compares18 complete functions/
262 bindings/six literals, preserving17 identities and13 exacts. PCX979/851→
979/871, run-index−8→−308 rather than original−48; no original typed role is
restored. Reject without variants. Its11 raw inputs/products/two objects are
archived/member-verified then removed, releasing72 KiB net.
The [three-function round owner](../research/exact/EXACT_LIFECYCLE.md#closed-round-implementation-owner-october18)
uses actual consecutive finish/reset/restart entries and their direct protocol.
Two compiles retain the full16-project/two-standard include prelude and compare
16 units/352 bindings/33 literals/24 actual local targets: every full identity
stays unchanged,13 exacts/2,895 bytes survive; reset426/20 remains nonexact.
Reject without further partition/header/type/name/order/flag variants. Its30 raw
inputs/products/three objects are archived/member-verified then removed,
releasing148 KiB net. Both phases are sealed under their respective
`.analysis/pcx-run-index-scope-20261018/` and
`.analysis/round-lifecycle-owner-20261018/` directories. Together41 raw files/five
objects are removed, releasing220 KiB net; canonical source/products/counts stay
fixed. Scope peaks stay below161 MB, with zero high/max/OOM events; no new
provider, native, relink, runtime or full replay runs.

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
resource producers. Load-bank's complete extent is restored at1475 bytes with64
remaining differences; the fixed author model also restores yoffset's home.
Use its retained full body and current trace to locate
the remaining actual producer before another compile. The fixed owner control
is closed; do not search wrapper position, function order or key values.

The author's related DOS routines now provide real typed names and complete
code, rather than an unconnected name list. The fixed text declaration control
nevertheless produces the same complete COFF apart from timestamps. Palette
endpoint/platform differences prohibit wholesale transfer. Reuse these closed
findings when selecting the next actual game producer; related names or debug
record order alone do not justify another compilation.
Its displayed char-pointer types also do not establish absence of pointee
`const`; the proposed qualifier change is declined before compilation.

Continue exploring the remaining20 authored candidates. The user explicitly
corrected the earlier missing-declarations blocker: recovering those facts is
the task. Original source, MAP/PDB or build records would help but are not a
prerequisite. Do not treat an unproved declaration as proof no hypothesis can be
tested. The score workspace recovery supersedes the earlier read-only review's
overly restrictive capacity decision. Form a specific inference from actual
consumers and independent layout facts, compile once, then judge the complete
result while preserving the distinction between inferred and unique source.

The [contemporary MSJ wrapper check](../research/exact/AUTHOR_SOURCE_CONTEXT.md#contemporary-directdraw-wrapper-check-october-18)
finds a distinct BMP/composite-sprite implementation, without a connecting game
routine or new source model. Its source-package size differs from the archive
index; use the actual nested member identities and retained limits. No compiler
trial follows, and seven raw carriers are removed after verified archival.

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

Continue the20 current authored candidates, including the eight declared-context
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
record key`+0x24`;44 executions of the pinned helper bytes pass. Later sealed
resource/editor observations supply current game keys, ranks and corresponding
complete instruction comparisons. The C1 observation above also supplies its
actual selected editor ID producer. Original-game intermediate IDs and
declaration context remain unknown. This is
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
  compare/register commutations. Blind guard/name/type/flag permutations add no
  primary fact. Independently connected author declarations can support one
  fixed inference, as in the bank and palette models; a missing executable
  operation is not a prerequisite. Keep the closed model boundaries.
- Keep time sampled before RNG. The reversed-addition proposal fails an existing
  ordered case. Clang reverses the four last-brick particle RNG arguments relative
  to original/current GCC; the recorded port gap is deferred, not repaired here.

The initial [public author-context review](../research/exact/AUTHOR_SOURCE_CONTEXT.md)
established no 1.07 declaration. Later connected debug roles support the adopted
bank and palette inferences, without proving unique original spelling or another
project's settings. Reuse those bounded results; do not replace source work with
repeated coverage audits or unchanged runtime episodes.

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

Run heavy commands in a user scope with CPU35%, memory high384 MiB/max512 MiB.
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

The October 18 maintenance pass additionally archives and member-hash verifies
237 obsolete single-link `.analysis/*/before/build/` objects/libraries/executables,
then removes their raw copies. The bounded selection excludes current builds,
tools, source and primary evidence. It releases about 7.1 MiB net of its archive
and receipts, with current source/object/report/delivery identities unchanged.
Restore instructions and member hashes are in
`.analysis/storage-before-products-20261018/started.json` and `cleanup.json`.
The rejected line declaration pilot separately removes its 16 private inputs
and products after verification; no unused proposal binary remains.

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
