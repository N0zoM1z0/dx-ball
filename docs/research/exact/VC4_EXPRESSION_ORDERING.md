# VC4 expression ordering observations

The October 17 investigation connects a numeric symbol-record lookup key to a
real child-ordering decision in the pinned VC4 backend. It does **not** yet
connect that decision to a specific original-game instruction difference.
No game source, exact claim, compiler recipe or delivery product changes here.
This research-only checkpoint retained 393 exact functions and 22 authored
candidates; the later linked owner note below supplies the current totals.

The target is the attested `.tools/msvc400/bin/c2.exe`, SHA-256
`820ed4e4930db97bcba646afb88fdb7d1f329631ca8e5b84096c0d6daa82e9a9`.
This follows the [symbol-record reader observations](VC4_BACKEND_SYMBOL_RECORDS.md).
REA 6.5.0/Ghidra 12.1.4 retains four new records in
`.analysis/rea/vc4-backend/runs/2026-10-17T13-24-57.149Z-interactive-3651932/`
and 46 in
`.analysis/rea/vc4-backend/runs/2026-10-17T13-45-34.524Z-interactive-3690015/`.
The closed cumulative snapshot contains 64 records, including the previous 14.
Complete responses, profiles and provider limitations remain private.

## Actual ordering decision

The 58-byte function at `0x413ded` receives a node and two unsigned ranks. It
swaps the node's `+0x0c` and `+0x10` children only when left rank is less than
right rank; ties preserve the children. It returns their unsigned minimum.
After swapping, operator attribute bit `0x10` gates replacement of the root
opcode through `0x430323(opcode, 0)`. The assembly confirms both the unsigned
branch and the stores. Mode zero reads the table at `0x481c0c`.

The six table entries for opcodes `0x1f..0x24` are
`1f→1f`, `20→20`, `21↔23` and `22↔24`. All six have attributes `0x6118`.
These are numeric opcode mappings; their source operator names have not been
established by this investigation.

The 206-byte caller at `0x408d62` conditionally visits the right child, then
the left child, obtaining their ranks recursively. It computes the current
node's rank through `0x40846e` before the ordering decision. Attribute bit
`0x8` and a separate special path gate the call to `0x413ded`. This traversal
is not by itself the final machine-instruction evaluation order, and not every
node reaches the swap helper.

## Consumed record field

For opcode `0x26`, `0x40846e` reads a record pointer at node `+0x14` and its
32-bit field at record `+0x24`. A null record or record kind `0x18` at `+0x0c`
returns rank `0x10`. Otherwise, assembly establishes this arithmetic:

```text
k = u32(record + 0x24)
a = k >> 8
b = ((a - k) mod 2^32) >> 4
rank = 0x10 | ((b - a + k) & 0x0f)
```

Both shifts are logical. There are only 16 possible results; this is not
monotonic key ordering. For example, keys 16 and 18 produce ranks 31 and 16.

The existing reader at `0x41bb61` stores integer-reader results at `+0x24`;
its newly retained full assembly confirms those writes. Pseudocode for
`0x41a4c1` compares that field to a numeric lookup key in chained tables, and
pseudocode for the opcode-`0x26` builder at `0x407575` stores its supplied record
at node `+0x14`. This establishes a consumed numeric lookup key, not its original
frontend assignment rule, source declaration order or identifier spelling.
The reader's retained control-flow limitations still apply.

| Observation | Evidence ID |
| --- | --- |
| Swap helper pseudocode / assembly | `ev_f3697f64010353fa335cead0c3f0ffb10493bc76140926d0bbb920c4730c4bdb` / `ev_b46805a114b06c821f75a563a8c424152eb16d76d416cda8932324aab3227125` |
| Recursive caller pseudocode / assembly | `ev_df37b8dc3ce522d96cf46509d239bb4dcf9b839623e9cf2d17f8a672a89cd0c5` / `ev_2b6f9254159151bf2fc84c7a41ad22880c65240519dda60e0ff4585c0b3a0fa3` |
| Opcode mapping assembly / six actual table entries | `ev_590dd5d1b1e54073d524c88cbebe21fa747c5c775ac9fb89140f7adfdc5fd003` / `ev_dda3d22f55bf5101f1942ff8b6afd6211da8fa0142f65fb7bc37f14fc90feb76` |
| Rank function pseudocode / assembly | `ev_cb5eba78e7e479074c1480e2f9f262737eecb4896f899fccb83cb2305d0bcaa1` / `ev_b0fd95723f8982595e11981815cf9d9cba0fb3e1a53d4227a7a54ee20999891c` |
| Record reader assembly | `ev_b72644fd2d85d07e930898c7f59b826775d5ceeb65897545fdb7196799331f5a` |
| Key lookup / opcode-`0x26` builder pseudocode | `ev_a6c839e4776192f89a175ffe6797917cbda64da676bff56e68570348badb2610` / `ev_7b0d659b205c3a2ec492e9bd2ebe1b27e39a0cc3d1a425ab2f2453e92bbeab5e` |

## Bounds, validation and next question

Literal xrefs to `canon.c` and `cgcanon.c` first located tree rewrite code.
An instruction search for stores across the two observed child fields then
supplied candidates, not procedure or reachability claims. REA confirmed the
selected procedures, their actual extents and the algorithm above. Several
other procedures have noncontiguous bodies; their enclosing address spans
must not be treated as complete function bytes.

A bounded Unicorn execution of the unmodified pinned C2 instructions and PE
tables passes 44 synthetic cases: 20 record-key/kind rank cases and 24 swap,
tie, unsigned-boundary and opcode-map cases. No original-game keys are claimed.
The private source and complete observations are under
`.analysis/compiler-operand-canonicalization-20261017/`. Independent review
confirms the arithmetic and flags the missing game producer link.

The first session ended after an unowned procedure query returned invalid
input. The session helper now retains each interactive inspection error,
including its full response, and continues using the same live import. Batch,
transport, provider, open, identity and close failures remain fatal. Seven
actual-module mocked cases pass, including two consecutive invalid queries
followed by a successful query; they start no provider. Open/close failures and
event-only transport notifications were reviewed by inspection, not injected.
The second real session reused one import and closed normally; no invalid
query was needed there. Its cold query took 407,402 ms under the existing
CPU/memory caps. Both sessions' observations and the first failure are retained.

Two identical closed catalogs now share hash-verified immutable storage,
releasing 17,526,784 allocated bytes net (16.7 MiB). Their paths and bytes remain
intact. Current tested build products and useful CMake caches remain retained.
No game compilation, relink, game episode or full replay follows this research.

The later [resource drawing-wrapper investigation](RESOURCE_ROTATION_WRAPPER_OWNER.md)
captures concrete current-game node opcodes, record keys and both child ranks,
then compares all affected complete emitted functions. Original-game intermediate keys and original
compiler/settings identity remain unknown. Do not turn the ranking mechanism
into a name, declaration-count, order or compiler-flag sweep.

The October20 [runtime-interface investigation](VC4_RUNTIME_INTERFACE_OWNERSHIP.md)
also observes an unchanged actual elapsed compilation: keys29699/29702 produce
load ranks41/43 and the helper swaps the first comparison's children/opcode.
All16 complete runtime code identities remain unchanged. Private ownership
controls produce complete exact elapsed/reset/palette bodies but lose other
accepted companions; none is promoted. This supplies a concrete current-game
cause without establishing the original keys or authorizing declaration sweeps.

## C-source comparison observation, October18

The earlier line and resource observations compile C++ sources through C1XX.
Their frontend addresses and source-field formulas do not establish the C1
implementation used by `editor.c`. One unchanged editor compilation now observes
the actual CL/C1/C2 process chain, with no C1XX process. The selected C frontend
is pinned `c1.exe`, SHA-256
`7a7c14aff9631b9460a5666a8c344a5a177fce125ba3c4e9c2a4d57c7f402bb2`.
The existing sealed C2 debugger executable is reused byte-for-byte; no observer
build, source adaptation, compiler option or game-source variant is introduced.

All 181 helper entries have paired returns, including 23 in
`find-hit-region`; 32 calls actually swap children. Every owned process exits0,
all stack/register guards pass and there are no mandatory read failures or
extra C2 threads. Ten omitted children lie below the explicit depth-five bound
in unrelated trees. The selected loop guard has a complete five-node tree:
two symbol leaves and their load wrappers below the comparison.

| Current role | C2 record key | Record kind | Derived leaf rank | Observed load rank |
| --- | ---: | ---: | ---: | ---: |
| Live hit-region count | 219 | 1 | 29 | 32 |
| Local `i` | 1178 | 1 | 28 | 47 |

Call35 receives the actual rank pair32/47, exchanges the children and changes
opcode `0x24` to `0x22`. Its 27 single-step events reach the saved return address
with return rank32 and the expected stack/saved registers. The retained REA
rank/load instructions independently reproduce the observed ranks. This agrees
with the emitted current guard loading the count into EAX before comparing
local `i` against it. Original instructions instead load `i`, compare the live
count against EAX and exit through JLE rather than the current JGE.

The complete original173/current172-byte bodies each contain46 instructions.
Forty-two instruction encodings agree. Only the three guard instructions and
the necessary backedge displacement differ; all eight branch successors agree
by instruction ordinal. The strict132-position difference remains unmasked.
All14 complete editor units,223 bindings and12 full literal references compare
against the original and current authority, retaining every raw/resolved code
identity and all13 prior exacts/3,267 bytes. Forty applicable exact local-target
guards also pass. No exact, source or delivery claim changes.

This observes C2 records from an actual C-source compilation. It does not locate
C1's serializer/key-assignment instructions, observe a direct final-emitter node
chain or recover original IDs/names/declarations. Do not transfer the C1XX
NameMap/source-field formulas or derive source permutations from these ranks.
The next concrete gap is the actual C1 output/key producer and its transport
to these consumed records.

Private `.analysis/editor-c-comparison-20261018/` retains the sealed trace,
full comparisons, source/process identities and independent reviews. All851
protected hashes and22 source-input modes/nanosecond mtimes remain unchanged.
The single observation takes4.186 seconds, with a160,743,424-byte whole-scope
peak under one CPU/35%, memory high384 MiB/max512 MiB and zero memory-limit
events. There is no provider import, native build, oracle, game, relink or full
replay. One explicit metadata receipt corrects a field label:42 counts equal
instructions, not42 individual bytes; no successful producer is repeated.
Archive/member verification precedes removing21 temporary carriers, including
one object and one executable, releasing958,464 allocated bytes net. The reused
observer remains in its earlier verified carrier, without a duplicate binary
in the new archive. Current tested products and useful caches remain.

## Downstream glyph generation boundary, October20

One pinned C2 session follows the retained phase5 call at43A425 rather than
repeating rank-only observation. Four complete dossiers establish this bounded
static chain:412F1B calls40CF4F for each input list item;40CF4F creates a new
block context through40D8EC, visits item expression trees through40CFF2 and
sets global48BA70. The original phase driver subsequently passes that actual
global to4063C4 with EDX=1.40CFF2 dispatches tree operations and calls40D968
on expression roots/children. This is not yet a final glyph address-selector
or actual emitted-instruction observation. Ghidra signatures remain inferred;
the optional415D66 gate is the actual WORD at ECX+20, not the misleading typed
pseudocode offset.

| Complete dossier | Total body bytes | Evidence |
| --- | ---: | --- |
| 412F1B | 294 | `ev_a4aa14631ad48a1824d84c0805b3a36a69d9a3ff9658413c6da4b1e43abdc7ba` |
| 40CF4F | 177, noncontiguous | `ev_a97f5df64a4e586028563ea70820a5500b24e95af0d556db5bd5868f576d94aa` |
| 4063C4 | 177 | `ev_42fc83cd3514d637c7905542fb16922ec164b4898d33405cf1a3cadb4c49c60b` |
| 40CFF2 | 2273, noncontiguous | `ev_dea770c7b49f950a9fe0fc08b8e8ce1a410ddf6b8b4f997ec769f11fa2b8f8ea` |

The first cold query takes456,095ms; followups reuse that import. A fifth full
dossier at40D968 (6166 noncontiguous body bytes) completes server-side but
exceeds the10MiB MCP response budget. Its reported Evidence ID is
`ev_12b478e5e4884001532c18fbcd71ef2be41a1ff6bb048862b7d3231657c478b0`;
the complete result is **not recovered** after fatal cleanup triggers a
256MiB Node-heap error. Neither a fifth saved dossier nor a new cumulative
snapshot is claimed. The four successful responses, exact transport error and
close failure remain in immutable run
`.analysis/rea/vc4-backend/runs/2026-10-20T05-59-25.754Z-interactive-1650967/`.
All owned processes are verified absent; the previous112-record snapshot stays
byte-identical. No import or successful producer is repeated.

The [session helper recovery](../../agent/REA.md#transport-budget-recovery-october20)
now permits retained native pages after interactive transport-budget errors and
avoids serializing that oversized ledger on close. Nine new provider-free
actual-module cases and six existing lifecycle cases pass. Real paging/heap
recovery is not newly executed. The remaining narrow static question is the
40D968 expression path, using bounded pseudocode/assembly facets rather than
another large dossier. No compiler/source/model/claim change follows these
static results.

The failed provider's124 scratch/before-copy files are archived and member-hash
verified before removal. Its identical catalog shares an already closed immutable
carrier, preserving every path and byte. Cleanup releases11,038,720 allocated
bytes net before the journal. Four unique dossiers and all failure records remain
directly available. Private authority: `.analysis/glyph-selector-static-20261020/`.

## Lower operand construction, October20

The missing40D968 facet is now recovered through one narrow pseudocode query,
not a repeat of its oversized full dossier. Sixteen same-import followups supply
the actual assembly and direct operand constructors. All17 responses survive a
normal close; the129-record snapshot preserves every preceding112 record.
The first query takes609,103ms at CPU35%, memory high384/max512MiB and the256MiB
Ghidra heap. A pre-close sample peaks at403,173,376 bytes with6031 soft-high
reclaim events and no hard-max/OOM event. All three owned processes and the
temporary project are subsequently absent. This does not retest transport paging.

The ordinary integer-binary path actually lowers node`+0C` at40D9DD before
node`+10` at40D9F2, constructs their operands, then calls40D71C at40DA32.
Opcode30 instead obtains an operand through41480D: a non26 indirect child is
recursively lowered and its returned reference enters4198A5 with kind4.
The8-byte operand points to a payload containing two32-bit fields and a16-bit
base reference.40D71C copies complete operands into instruction-record`+10/+18`
and writes the numeric instruction/width fields at`+8`. These are concrete
lower-record boundaries, not yet a final machine-byte encoder.

Two interpretation corrections matter.40E961 is a constructor wrapper through
40D917/401C79, **not** a virtual-register table lookup.40E972 recognizes kind1
with specific symbol flags, or kind18; that predicate alone does not establish
stack-only storage or physical EBP. Virtual references return in AX, and the
transient operand pool can be reused: any future observer must copy bounded
records immediately and retain pointer generations, not equate repeated addresses.

Primary Evidence is `ev_3d3be10651712daada5f86b5cc640d101dc83873d861f803ebb92a52e94cdcbd`
(40D968 pseudocode), `ev_7a3092d14f0bddb113a796c17375de28aef0304e33098cbec53d980b359ea031`
(its assembly), and `ev_27af67e5cf374235d8424f0ca696a46020b4126e48bb7fd8326b58b0a4cc74f7`
(40D71C). The complete17-record identities, actual hook bytes, snapshot-preservation
receipt and independent review are in `.analysis/glyph-operand-lowering-20261020/`;
raw responses remain in the immutable06-38-40 C2 run.

No live glyph subtree is yet joined through these stages to physical registers,
encoded address bytes or a COFF instruction offset. Static child order alone
does not prove glyph-specific scheduling or authorize source-ID/name changes.

## Address IR to instruction bytes, October20

The next bounded session follows the retained412F1B→4063C4→402F39 call edge.
402F39 consumes the same instruction header and two operands, then folds,
inserts and deletes records. Its address-kind5 payload carries references at
`+8/+C` and scale bits in the operand header. This is address-IR legalization,
not final encoding. The complete pseudocode and independent review describe its
Ghidra-reported13,585-byte noncontiguous body; textual callee counts are not
runtime coverage.

The actual post-phase6 call43A434 invokes401730 before413103 returns source
list nodes to a freelist.401730 contains the subsequent function pipeline.
On its47E964==0 path,46B7BC maps virtual references through46B949. Arity2 visits
the second operand before the first; kind5 visits payload`+8` before`+C`,
except for the1B no-base sentinel. These static orders differ from simply
reading the earlier binary tree. The current glyph's actual47E964 value and
reached path are not observed; `/Od` alone is not that observation.

41D6C8 supplies a concrete record-to-byte boundary: class0 calls41C920 with
an instruction record,20-byte stack buffer, current code position and mode1.
The encoder writes opcode bytes and calls425DA1 for ModRM/SIB/address data.
425DA1 can convert an ESP-based kind4 operand or exchange kind5 base/index
when its index is4 and scale is0. A future observer must therefore retain
pre/post operand payloads as well as the final buffer. The returned length
advances both the caller's code position and its section record's cursor.

| Actual site | Proven static contract |
| --- | --- |
| 41D725, `e8f6f1ffff` | Before CALL41C920: ECX=record, EDX=buffer, `[ESP]`=position, `[ESP+4]`=1. |
| 41D72A, `8bd0` | EAX is the returned length. The common41CF89 footer subtracts buffer start from cursor and returns with RET8 at41CF99. |
| 41D732, `ff1554a24800` | Before the output callback: ECX=buffer and EDX=returned length, established by the actual intervening instructions. |

The assembly facet for41D6C8 stops at41D711 even though its entry branches to
41D799. A complete528-byte REA read and separately labelled Capstone decoding
join that dispatch through table41D868 to class0 at41D712 and the two calls.
Every byte is checked against the pinned C2. This is not a whole-function CFG
claim: two dispatch cases leave that byte carrier. A first secondary decoder
attempt rejects a guessed end address splitting an instruction before writing
its report; bounded instruction-count decoding repairs only that local helper.
No provider query or compiler is repeated for it.

Primary Evidence includes `ev_bbef49c48efc437125411d0d88e8a464d8915cf1b6aeedd6d2a3282acf07920e`
(402F39), `ev_8bdc932287bb93aceb37fca8989ceb00832de32ee072ba269937301561760688`
(401730), `ev_bd3175412d038cb8b731ac9579ec1ab347a0d4bdc03cd4d68779af3091903a26`
(41C920), `ev_1f84bb940bff5e13d178efbfe457b750c0d34e92fb68419c70779c1771f24061`
(425DA1) and `ev_e72d142fbf408ba6af6f626f406da986ed9726a844c09e84af6efb60ba2f6803`
(complete caller bytes). All25 responses live in the immutable08-16-58 C2 run;
the result, prior129-record sealed snapshot, secondary decode, source-model
audit and independent static review are in
`.analysis/glyph-machine-legalizer-20261020/`.
Normal close preserves all129 previous records in the154-record snapshot.
The first query takes459,430ms at the unchanged35%/384/512MiB/256MiB limits;
the pre-close peak is403,267,584 bytes with5660 soft-high events and no hard-max
or OOM event. All four owned processes and the temporary project are absent.
Three closed helpers are member-size/hash verified in `closed-helpers.tar.gz`
before removal. The identical8.4MiB catalog shares its prior immutable carrier,
preserving both paths and all bytes. Net allocated release is8,777,728 bytes
before the cleanup journal; current products, tools and unique evidence remain.

No live glyph subtree, allocation path, output callback implementation or
COFF instruction/relocation correspondence is captured here. The next useful
experiment is one independently reviewed unchanged-owner observation joining
those boundaries, not another current-rank-only capture or source spelling
sweep. Repeated pointers do not establish cross-pass generations. The companion
source audit also rejects unsupported timer-carrier reuse: during the second
clock call EBX holds the deadline, not the raw sample; the original delta's
stack home is first written only afterward. No source, compiler output or
claim changes follow:392 overall exact,247 authored exact,23 authored candidates.

## Observed glyph slot mapping and output, October20

One independently reviewed observer now follows the unchanged current resources
recipe through the actual statement DAG, recursive operand/IR calls, late virtual
IR, reached mapper and instruction output. Its18 complete instruction pins and
12 footer instructions are checked against the pinned C2 and compiled observer
tables. Loaded CL/C1XX/C2 paths, job/thread ownership, real instruction effects,
call IDs, stack cleanup, nonvolatiles and all52 mapping word stores are checked.
This changes no compiler operand, counter, source input or compilation flag.

REA process Evidence is
`ev_d82cee55315ee876c76ed6eb995d41e15365ef4d2bdf0a9eed04864aab1cdf6b`;
the separate utility-build Evidence is
`ev_78616c09285d9880c366ae6bcdaf40c54db68bb5667ac3393298375cc13c726d`.
All three compiler processes exit0. The actual47E964 value is0 and its virtual
mapper is reached.622 selected events include23 statement roots,40 paired
recursive lower calls,63 paired IR calls,52 mapper call/return/store triples and
44 encoder call/return/output triples. Every returned buffer byte agrees with
its actual raw COFF interval, covering the entire146-byte current lookup with
no gaps/overlaps and with the observed section cursor/owner base checked.

The complete object comparison preserves all ordered section payloads/flags,
actual relocation targets and every non-FILE symbol/aux record; timestamp,
transport offsets and separately retained FILE records are explicit exclusions.
All18 complete resources functions/262 bindings and six entire literal carriers
retain their current identities. The run takes83.49s at the existing one-CPU,
35% quota,384/512MiB limits; peak memory is151,879,680 bytes with no memory-limit
or OOM event. REA verifies owned-process cleanup; sampled process trees are not
substituted for the debugger's actual compiler-exit checks.

Statement107 uniquely contains the full typed slot load, code-field access and
signed-byte comparison chain. The other22 roots select zero. Its complete
23-node graph has address `((S<<2)+(F*1048))+B`, where S/F are the observed local
sprite/global font loads and B is the bank address. The pointer load is followed
by `L+36`, a signed8 load, signed16/signed32 conversions and comparison with the
similarly widened actual code argument. The bank-count access cannot satisfy
this selector. Opcode1F alone is not used to infer branch polarity.

The first offline selector explicitly rejects opcode09 rather than discarding
it. Retained source9→IR2A mapping, this exact recursive call and actual IR2A→SHL
encoder observations establish a bounded constant-left-shift extension modulo
2^32. It accepts only32-bit input/result and an established inline literal0..31;
dynamic/oversized shifts and unknown casts remain unsupported. The first report
and original selector are retained. No compiler or runtime capture is repeated.

The eight actual output records541..562 also reproduce the previously retained
29-byte current slot group against the original28-byte group. Independent
low32 algebra gives `B+1048*F+4*S` for both. Original loads F into EAX first;
current loads S into EAX and then F into ECX. The absolute global load therefore
takes6 rather than5 bytes. Complete current/original body identities and all
six actual DIR32 bindings are checked, not just those eight instructions.
This establishes the observed current output, not original compiler IDs or a
unique source declaration. Unobserved rewrites, allocation reuse, optional
operand metadata and the output callback implementation remain separate limits.

The actual late graph independently gives S→8026 and F→8028, then preserves F
in8034 while deriving64F,65F,131F and1048F. Its slot address uses base8028 and
index8026 at scale4. Mapper triples418/419/420 and421/422/423 commit those two
references to codes1/0. Encoder560, return561 and output562 then retain the actual
kind5 address and seven bytes `8b848100000000` at raw offset72, with the bank
DIR32 at75. The physical-stage graph independently has the same polynomial;
one earlier LEA is now SHL3. These are checked phase-local semantic relations,
not a claim that an unobserved allocator generation survived every rewrite.

Private receipts and the full528,274-byte trace are in
`.analysis/glyph-generation-observation-20261020/`; trace SHA-256 is
`e7817c52b748efbe5144769cb326c1817bdda7df49f2e28f2ffcb352b4cb9587`.
The next reconstruction question is the supported source/compilation context
that produces the original F-first address order. A current pointer or low16
token is not an original compiler identity, and no name/declaration permutation
or source change follows from this observation alone. Totals remain392 overall
exact/247 authored exact/23 authored candidates; the user's objective stays active.

The closed observer, proposal object and helpers are retained in the12-member
`closed-inputs-products.tar.gz`, with every member size/SHA-256 checked before
exact-file deletion. Cleanup releases278,528 allocated bytes net before its
journal. Direct reports, both REA responses and the full trace remain available;
the latter three also have space-neutral hard links under REA observations.
All137 protected inputs/products/tools stay fixed. Current30-owner products,
native library/cache, originals and tools are retained. `result.json`,
`cleanup.json` and `verification.json` seal the closed experiment, not the goal.

## Fixed byte-count context pair, October20

Two immutable historical resource inputs now isolate the unsigned-before-product
change. The eight project headers and all compiler flags are identical; the sole
source difference is `nbytes = width * height` versus
`nbytes = (DxBallUInt)width * height`. Both inputs/objects come from the verified
bank-byte-count archive, not a new source variant. The older October17 rank trace
also produced an exact145-byte lookup, but its loader has seven different local
identifiers. It cannot substitute for this pair's missing rank observation.

One reviewed20-site observer extends the preceding18-site observer only at the
actual413DED rank helper's entry and RET4 boundary. Complete instruction pins,
real instruction stepping, stack/nonvolatile state and root writes are checked;
the observer changes no source, symbol key, counter or operand. The utility is
built once, then the two fixed inputs compile serially once each. AFTER is gated
on BEFORE's successful complete comparison, including live trace/object hashes.
Each sample uses its own retained relocation and literal mappings; applying
BEFORE's offsets or literal names to AFTER would be invalid.

| Actual observation | Before unsigned cast | After unsigned cast |
| --- | ---: | ---: |
| Sprite symbol key | 28321 | 28322 |
| Sprite leaf / load / multiply-by4 rank | 31 / 34 / 75 | 16 / 35 / 92 |
| Font key / multiply-by1048 rank | 28107 / 85 | 28107 / 85 |
| Rank arguments, F then S | 85, 75 | 85, 92 |
| Observed child exchange / returned rank | No / 75 | Yes / 85 |
| Complete raw lookup bytes / original differences | 145 / 0 | 146 / 86 |

Actual rank events43/44/45 independently select F*1048 and S*4 from typed captured
symbol/load/literal records in each run. The footer exchanges exactly the two
ADD child fields only in AFTER; RET4 advances ESP by8 and returns the observed
unsigned minimum. Each run's later statement173 uniquely contains the complete
`B+1048*F+4*S` pointer-slot load, `L+36` signed-byte field and widened code-argument
comparison. The other22 statements select zero. At this snapshot multiplication
by4 has become a shift; BEFORE is F-first and AFTER is S-first. These are
independently selected phase-local semantic observations, not a pointer-lifetime
join between phases or processes. AFTER's multiply rank92/key28322 must not be
identified with the later current cohort's shift rank92/key28342.

Both runs close22 rank,40 lower and63 IR triples,52 mapper call/return/store
triples and44 encoder/output triples. Returned buffers cover every byte of the
respective145/146-byte raw COFF body, with all six actual lookup relocations
checked. All18 complete functions/262 bindings/six entire literal carriers equal
their own frozen baselines. Full normalized COFF compares ordered section
payloads/flags, actual relocation targets and non-FILE symbols/raw auxiliaries;
timestamp/transport offsets and separately retained FILE records are exclusions.
The loader remains the same complete1475-byte code with77 actual relocations.

REA process Evidence is
`ev_38904e08f8cb761ad7d3a6d95a51309e7f99a31496ecf899bf02feeb2894e565`
and `ev_0b8cdfebdad15b89de7d630860c25973121e7ebd11f752e7f898f8454a78f5f6`;
utility-build Evidence is
`ev_6d6c4034418f393635809210bff7637f72d5c5e0efb6aa3d8793328bdda0c2cf`.
All three compiler processes exit0 in each sample; REA verifies owned-process
cleanup. Runs take73.22/72.83s, peak at149,139,456/149,856,256 bytes, and retain
the existing one-CPU/35% quota/384–512MiB limits without memory-limit/OOM events.
Both full traces, immutable gates and independently reviewed reports remain in
`.analysis/glyph-order-context-20261020/`, sealed by `result.json`.

This observes the real historical key/rank/order sensitivity without recovering
the original frontend record allocation or unique source spelling. BEFORE's
implicit conversion on unsigned assignment occurs after signed multiplication
and does not define the overflow witness. It is diagnostic, not an adopted
reversion. A staged unsigned accumulator is not a tested rejection, but the
original instructions show only the post-product count write and supply no
positive reason to introduce that staging. Moving the cast between operands
would add no missing contract. Keep current defined-wrap source and all accepted
companions; no spelling/order/flag sweep follows. The next upstream question is
the actual frontend producer/context responsible for the additional symbol
record, using existing artifacts rather than unavailable original sources.
Totals stay392 overall exact/247 authored exact/23 authored candidates.

All32 closed copied inputs, objects, utility executable, logs and helper files
are archived and individually size/SHA-256 verified before exact-file removal.
Cleanup releases1,114,112 allocated bytes net before its journal. All142
protected baseline/input/tool hashes stay fixed. Direct reports, full traces and
REA responses remain; the latter also have space-neutral REA observation links.
Current products, native incremental caches, originals and tools are untouched;
each removed file is recoverable from `closed-inputs-products.tar.gz`.

## Observed frontend counter divergence, October20

The same immutable historical pair now has a bounded C1XX counter observation.
It reuses the already established40AA3F writer and401BD5 reader MOV guards plus
an owned four-byte hardware watch at4B0F90. Each run arms at actual counter28087,
before named font28107, and stops at28330 after exactly243 consecutive increments.
Actual instruction effects, debug state, thread/process/job ownership, full tool
paths and bounded raw snapshots are checked. No compiler record, counter, source
or option is changed; no C2 rank/output instrumentation is repeated.

Both runs observe unchanged nbytes28285 and bitmap28286. The subsequent window is:

| Assigned counter | BEFORE actual writer/record | AFTER actual writer/record |
| --- | --- | --- |
| 28287 | 4163EF | 4163EF |
| 28288 | 41639D, raw kind8 | 4163EF |
| 28289 | Ordinary named new_shape | 41639D, raw kind8 |
| 28290 | 4163EF | Ordinary named new_shape |

Among common unique named writer/reader roles, new_shape28289→28290 is the first
stable+1 shift; sprite later shifts28321→28322. Ambiguous names are retained but
not aligned. The first same-counter site/name signature difference is28288, not
a proof that repeated unnamed records have unique cross-run identities. The
following raw kind8 has an actual later recordcode3/mode1 reader in each run;
its label/temporary/other semantic role remains unknown.

At AFTER's two consecutive4163EF events, actual EAX is28287/28288 and EDI has the
same physical address62672744, with zero object`+18` at both snapshots. Complete
captured instructions4163F5..416404 and retained C1XX record08 establish the
straight-line store `(old & 0xff000000) | (EAX & 0xffffff)` to EDI`+18`; no
branch/call/EDI/EAX change intervenes.416407 writes raw kind byte0C. This is an
observed-entry/static-fallthrough proof, not an independently stepped store.
The repeated address/zero word supports intervening reset/reinitialization/reuse,
but neither its writer nor two distinct allocations or continuous object identity
is established. No source-local, type-id or other semantic name is assigned to
kind0C. The extra counter use is observed, not a newly recovered source declaration.

An offline verifier initially rejects a missing owner-name string after complete
owner/code-window/MOV checks pass. The observer's conservative decoding guard
leaves those names blank and does not serialize owner kind. A separately reviewed
offline adapter retains actual same-run owner pointers: unique nbytes anchors
width/height's owner, while the unique sprite/name/key pair has a distinct owner.
Fixed-source placement and every original counter/MOV/COFF check remain required.
Names and owner kinds stay unknown; four exact verifier replacements, their hashes
and the original failure are retained. No target is retried or frozen input edited.
Only after corrected BEFORE passes does the hash-bound serial AFTER gate run.

BEFORE has145 selected writes/135 reads; AFTER145/134, giving280/279 verified
MOV pairs. Both entire18-function/262-binding/six-carrier comparisons and normalized
COFF equal their own frozen baselines. Timestamp/transport offsets and separately
retained FILE records remain explicit exclusions. All153 protected current hashes
stay fixed. Runs take40.792/40.148s and peak at151,543,808/151,912,448 bytes under
the existing one-CPU/35%/384–512MiB limits with no memory-limit/OOM events.

REA process Evidence is
`ev_5462ef5f2fd0d2ff6d1d7ae218abfc204c53bc210fbd3237d31a9929b5d5f216`
and `ev_58329ac68ac3a0a4137e58dd628b9d04b72c9bb39d7d2d48041649b096029fb2`;
utility Evidence is
`ev_98732d1a1d294fe88aca32a0e8e0db37b50730ab2e627d0009d6ff20783fdba6`.
All compiler/observer/outer exits are0 and owned cleanup is verified. AFTER's
outer `truncated=true` is retained: its2MiB filesystem hash budget omits only the
prior utility-response digest. That digest independently matches the build review
and before snapshot. Target trace, terminal output and file enumeration are not
truncated; outer process coverage remains sampled, not exhaustive.

Private authority is `.analysis/glyph-frontend-counter-20261020/result.json`.
Complete traces, direct closures/reviews/failure receipts and a focused summary
remain available, with space-neutral REA observation links. All32 closed copied
inputs/objects/EXE/helpers/logs and the1,516,218-byte expanded analysis are archived
and member-size/SHA-256 verified before removal. Net release is1,802,240 allocated
bytes before journals; every removed file is individually recoverable. Current
products, originals/tools and native incremental caches remain untouched.

The next source question is a coherent signed32 arithmetic family:16 observed
DWORD additions/subtractions/multiplications in15 expressions across six resource
functions, independently grounded in the bank/count/Blt/glyph/PCX boundary notes.
One fixed native-only per-owner wrap contract could preserve their natural signed
source with unchanged VC4 flags. The closed nbytes-only control does not test this
whole family. Pointer bounds, division, shifts, unsigned byte-count`+3`, API widths
and signed-byte normalization are separate and must stay intact. This is a source
hypothesis requiring complete companion comparisons and unchanged boundary cases,
not an adopted compiler setting or permission to add unit-one padding expressions.
No source or acceptance claim changes:392 overall exact/247 authored exact/23
authored candidates remain; the goal stays active.

## Complete resource arithmetic-family comparison, October20

The [fixed whole-family control](RESOURCE_ARITHMETIC_FAMILY.md) now tests that
source hypothesis once, without changing VC4 flags or current headers. All18
complete functions/262 actual bindings/six distinct entire literal carriers
compare. Stretch139, unchanged capture852 and unchanged lookup145 are privately
exact, but plain Blt grows195→199 and glyph328→332, losing two accepted exacts.
Twelve code identities remain unchanged; nine of11 accepted resource exacts
survive. The fixed no-loss gate fails. No native compile/witnesses, modern option,
source, object/config/report replacement or exact promotion follows.

Independent514-instruction/81-binding review attributes the five outcomes to32
equivalent bank/slot address graphs and stretch's two commuted ADD inputs. All
consumed arithmetic instructions of the two lost functions remain unchanged.
No original source/TU responsibility or new split/type model is established;
current COMDAT order and prior text/glyph-owner controls do not supply one.
Do not retry family subsets or an already answered current rank capture. The
earlier kind0C physical-storage reset/reuse writer remains unobserved; the
historical trace is not a complete allocation/lifetime history.

REA process Evidence is
`ev_da9c4f52778372a0d768e2f348da72d7e54a12a87a425463984c78a6f3e7af87`.
The capture is untruncated, exits0 and verifies owned cleanup. Compilation takes
2.185s, peaks160,960,512 bytes and has zero memory-limit events under existing
limits; outer process coverage remains sampled. Private authority is
`.analysis/resource-arithmetic-family-20261020/result.json`. All18 closed copied
inputs/products/helpers/duplicate expanded mappings are archived and individually
member-size/hash verified before removal, releasing262,144 allocated bytes net
before journals. All155 protected hashes stay fixed. Current392/247/23 and the
active all270-authored-exact goal remain unchanged.

## Storage-reset boundary and closed provider failure, October20

The paired trace's repeated physical address is not evidence for two allocations.
Retained C1XX record08 shows4163C5 reserving eight stack bytes and saving three
registers, then reading the preexisting record through `[EBX+4]`. It does not
allocate or clear the observed word before4163EF. On that inferred normal
prologue path, the return slot is ESP+20, containing423AA3 in both events;
ESP+16's422BA7/422BD1 values are reserved local storage, not proved adjacent
callers. Entry/path and continuous record lifetime are not independently observed.

A new minimal tail query returns no bytes. The initial default-profile open is
rejected without analysis; the corrected matching-profile import reaches its
900,000ms provider deadline. Its late complete error response and normal close
are retained. No query result or new static Evidence record is produced. All141
old records and the1,168,540-byte snapshot remain byte-identical, as do155 current
protected files. Owned processes and the temporary Ghidra directory are gone.
Do not repeat this cold import or promote an offline decoder concordance into
provider evidence. The actual reset/reuse writer remains unknown.

Private authority is `.analysis/glyph-kind0c-storage-20261020/result.json`.
The observer draft was never compiled or executed. Its two files are archived
and member-verified before removal; a duplicate snapshot archive is deduplicated
against an existing identical immutable payload. Net release is86,016 allocated
bytes before journals. Sampled resource counters are not final disposal counters;
this failed observation adds no source, native, exact or semantic claim.

The subsequent [whole-owner integration](RESOURCE_ARITHMETIC_FAMILY.md#validated-whole-owner-integration)
reuses the closed arithmetic-family object without another legacy compile.
Actual GNU wrap-contract checks,32 finite invocations and1,766 unchanged existing
cases pass; the entire18-function object is adopted with three promotions and
two honest demotions. Current totals are393 overall/248 authored exact/22 authored
candidates. This does not resolve original frontend record/TU responsibility or
retroactively pass the earlier failed no-loss gate. Reuse the current adoption
and authored-coverage receipts rather than repeating completed observations.

## Actual physical-storage reset, October20

The failed static-tail import is not repeated. One reviewed hardware write
watch instead answers the still-open physical-storage question using only the
exact archived historical AFTER owner. It introduces no source, spelling,
type/header, flag or counter variant. Current adopted source is protected
separately from those historical inputs; this diagnostic object is not installed.

The owned Dr1 watch observes the same DWORD at03BC4F80 continuously through
`0 -> 28287 -> 0 -> 28288`. The first/third actual stores are416404, with
416407 contexts. The previously unseen zeroing write traps at402FB8 with
pinned bytes F3AB at the reported PC, EAX0, DF0, EDI03BC4F84, ECX77 and EDX424.
The complete48-byte observed window matches the attested C1XX image. Its
instruction/register geometry supports an in-progress REP STOSD zero-fill:
EBX03BC4F08 plus8 is the fill start;106 minus77 DWORDs have completed, placing
EDI exactly at the watched address plus4. This is an analyst interpretation of
REA-observed bytes/state, not new provider-decoded helper or source evidence.

Importantly, the captured32-byte record prefix is **not entirely zero**:
the first28 bytes are zero while the final DWORD at+1C remains20hex. The
observation establishes this watched word's reset and the retained prefix,
not completion of the full424-byte clear. The frozen verifier's descriptive
phrase "post-instruction only" is too narrow: hardware debug state follows a
write, but REP can retain its current/restart PC. Preserve that original report
and the explicit clarification rather than altering raw evidence or rerunning.

All243 consecutive counter transitions,279 selected MOV steps and three Dr1
events verify. One utility build and one37.435-second observed compile suffice;
there is no target retry or provider import. Complete18-function/262-binding/
six-literal-carrier comparisons and all26 ordered normalized COFF sections/
69 non-FILE symbols equal the frozen AFTER baseline. FILE auxiliaries5 versus8,
timestamps and transport-offset exclusions remain explicit. All887 current
protections, including native/delivery products, are unchanged through cleanup.
No source/semantic adoption, exact promotion, relink or game/native run follows;
current393 overall/248 authored exact/22 candidates remain incomplete.

Capture Evidence
`ev_513541114e7e836a4daa8f3b40ab5b8f5117adb4629dc877f571c37a1af4a28a`
exits0, is untruncated and verifies owned-group cleanup/temporary-root removal.
One CPU/35%,384/512MiB limits hold, with153,919,488-byte peak and no high/max/OOM
events. Process coverage remains sampled. The utility capture separately retains
two inaccessible sampled /proc environments; a later exact-PID check finds
neither remaining. Do not describe that earlier sample as fully verified.
An initial prepare hash gate safely rejects a final-guard/read race before any
staging or build. Its failure and initial review stay retained; main rereads the
final guards and prepares successfully, without a source variant or target retry.

Private authority is `.analysis/glyph-storage-watch-20261020/result.json`.
All37 expanded inputs, utility/object, trace, complete reports, raw REA responses,
receipts, failure and helpers are archived and member-size/SHA256 verified before
removal. The255,540-byte archive releases1,257,472 allocated bytes net before its
cleanup journal;883 remaining direct protections and current useful caches stay
intact. Every removed file remains individually recoverable.

The missing4163C5 tail is no longer needed to identify the reset writer. The
useful next relation is which actual source/type/IR producer requests the rebuilt
kind0C record and where it is consumed or serialized before the storage reset.
Physical-address reuse does not establish a single logical object's lifetime,
two allocations, semantic record kind or a missing source local. Bind that
producer to an actual typed conversion/product consumer before changing source;
do not repeat the cold import, zeroer/rank capture or declaration/name/flag sweeps.

## Typed-record completion and caller windows, October20

Two previously absent69-byte ranges are extracted from attested C1XX
SHA256 `3376b1dfaff0bdb1018b13fbb22cf407858044f327d4bbc3e4d9335640aea7f0`:
41642F/file88111, hash `aadad09826386c2a6e17282eece307ab16c0d4ed16da8a0a335379fc5f23880c`;
423A96/file142998, hash `1ac60926eac73892654096968eaaedfde48ae2725431e30ea821161636094780`.
Separate REA6.5/Ghidra12.1.4 raw-x86 sessions each return all69 bytes and
assembly, with exactly two records in each saved snapshot. The original
141-record snapshot stays byte-identical. This avoids the failed whole-image
import; no original-function/ABI or whole-PE context is claimed from raw inputs.

The tail clears input byte bit7 at416438, copies its first DWORD into record+1C,
and conditionally clears record+1F bit0 before calling407D5F,40A31C and406670.
Their identities remain unknown. Its shown fallthrough returns EDI in EAX;
the external conditional branch at416447 lies outside the fragment. The caller
sets EDX to old EBP-18 and ECX to old EBP-30, calls4163C5 at423A9E, and stores
returned EAX to4B4D40 at423AA9. Next address423AA3 agrees with the historical
ESP+20 value under the previously stated normal-prologue/path inference; it is
not a newly observed executed entry/return. EBP arithmetic is not evidence of
an architectural frame or a recovered C++ prototype.

Primary assembly Evidence is
`ev_51c6771fe6bb218610d4440c33952708526ae3bd7bca24d6908e7a7a1fa8be09`
and `ev_9abd1697744509d5be8a64d2b0b08008ad8a066152ea05b73ef891877481bdf1`.
Raw-input mapping, generic gcc compiler specification and unmapped external
code/data limit these observations to the shown ISA relations. Retained4B4D40
references identify pointer/result slots, not a typed byte-count conversion,
product, IR serializer or original source local. The historical input A0hex
could become20hex on this tail path, but20hex alone does not mean unsigned32.

A read-only review of the hash-bound historical trace finds no register-prefix
sample starting at954190,958354,95CBD8,95CB6C or95CB78. Forty-eight discrete
32-byte samples starting at958344 overlap958354: its available16 bytes are
`63400000000000000000000000000000`. The selected pair201/202 merely holds
the five pointers and does not dereference them. Those samples establish no
continuous contents/lifetime or source/type identity, and no other requested
pointer is covered. Do not infer a semantic type from these address values.

Both failed workflows remain preserved. The first capture reaches its200s idle
deadline because buffered output hides completed-tail progress; it returns
cleanup_incomplete. Its caller import becomes an unattachable orphan. Exact
PID/start-time/run-token/cgroup/executable/target checks bind three processes
before pidfd-directed termination. All54 workspace members are size/hash verified
in a recoverable archive before workspace removal. The first libc capability
failure occurs before any signal and remains retained. This supplemental cleanup
does not rewrite the original capture's status. Only after that terminal check
does a reviewed caller-only continuation expose progress/heartbeats and avoid
repeating the tail or changing the target.

The continuation obtains both records and a snapshot, then close reports
cleanup_incomplete/ownership-token mismatch for PID2426643 despite diagnostic
JVM exit0. Outer capture
`ev_9b1aba35642192f60353b00db7eca44afb1ba239226e5ef490e32e6aa1afecb8`
exits1, untruncated, with owned-group cleanup verified and temporary root removed.
Subsequent exact-PID/workspace checks confirm absence; this is usable static
evidence, not a fully successful workflow. One CPU/35%,384/512MiB and256MiB JVM
limits hold. First/continuation peaks are403,156,992/403,189,760 bytes, with
2,917/2,105 soft memory.high events and zero max/OOM events. Process coverage
remains sampled; a clean later check is not proof of exhaustive process history.

Private authority is `.analysis/rea/c1xx-typed-record-windows-20261020/result.json`.
All950 original and963 continuation protections verify before cleanup. All38
closed helpers/raw responses/windows/snapshots, including the prior orphan
archive, are member-size/SHA256 verified in a319,529-byte archive before removal.
Net release is962,560 allocated bytes before journals;946 protections remain
direct and17 phase protections are individually recoverable from archive. Current
products, caches, tools, originals and game source remain unchanged. No compile,
native/game replay, source adoption or exact promotion occurs;393 overall/248
authored exact/22 candidates remain incomplete. Follow the actual returned
record into its typed downstream consumer before proposing a source change;
do not replay these fragments or turn a metadata bit into a type/name/order sweep.

## Returned-record consumer observation, October20

One unchanged historical AFTER resource compilation now observes the missing
generation relation with owned Dr1 record+1C and Dr2 global4B4D40 read/write
watches. Actual counter28288 arms them on EDI's kind0C record; counter28289
disarms both before the next assignment. Existing Dr0 selection and transparent
writer/reader MOV hooks remain. A source review first catches a legitimate
simultaneous-Dr1/Dr2 case; both observer and verifier accept bits2/4/6 and retain
independent previous/current values before any preparation or execution. That
finding and corrected review remain preserved. Runtime exercises no combined
event; source review is not execution coverage of that branch.

All243 counter transitions,279 MOV pairs and108 accesses verify against pinned
runtime code bytes/state and the owned thread. Seven accesses concern record+1C,
101 the reused global. Event7's actual423AA9 store publishes EAX=3BC4F68 into
4B4D40, with post-PC423AAE and ID28287. That instruction is also covered by the
preceding primary caller Evidence. Event8 has REP restart PC421314, DF0,
ECX5, ESI4B4D44 and EDI3B8BB14. Event22 has restart PC42137F, ESI3B8BB14 and
EDI4B4D44, again ECX5/DF0, and restores the numeric pointer value into the global.
The raw F3A5 contexts support a first-DWORD round trip through3B8BB10. The
copied DWORD lies immediately before the captured pointer prefixes; intervening
writes to that slot were not watched. A completed24-byte transfer, continuous
object lifetime and the inferred semantic-stack interpretation are not proved.
Events9/23 overwrite the global with other values; its101 accesses are not101
uses of the selected record.

The seven record-field post-access PCs are416443,416451,406678,406686,406B4D,
406B5D and402FB8. The first six precede publication. During the406670 path,
record+10 changes3BC4F98→958354 while+1C stays20hex; an input-context prefix
already contains958354. The helper's meaning is still unknown. Event63 observes
+1C20hex→0 at the known F3AB/REP restart, with all32 captured record-prefix
bytes zero. This extends the earlier28-byte prefix observation by one DWORD;
it does not prove completion of the entire424-byte clear. Unchanged values
are not proof of reads: event2 is the retained tail's byte AND. Other than the
two tail accesses/publication, these code windows are raw runtime Evidence and
analyst interpretation, not newly provider-decoded procedures or original types.

The utility and target are each built once. The complete historical18-function/
262-binding/six-entire-literal closure equals its own frozen baseline, as do all
26 ordered normalized COFF sections and69 non-FILE symbols. FILE auxiliaries
5→8 and timestamp/transport-offset exclusions stay explicit. All895 current
protections and nine copied inputs remain fixed through cleanup, before this
documentation update; the historical object is not installed. Capture Evidence
`ev_0687d53f94c192ad27d07799586019ad10fd313bd95cdfb7a0f86195ba9d0dc0`
exits0, untruncated, with owned cleanup verified and temporary root removed.
The39.895586s observation peaks153,100,288 bytes under one CPU/35%,384/512MiB,
with no high/max/OOM events. Outer process coverage remains sampled.

Private authority is `.analysis/glyph-record-consumer-20261020/result.json`.
All37 closed inputs, object/utility, raw trace/REA responses, complete reports,
reviews and helpers are size/SHA256 verified in a266,331-byte archive before
removal, releasing1,609,728 allocated bytes net before journals. There are891
remaining direct protections and four archived phase protections; all current
tested products, useful caches, tools/originals and the141-record snapshot remain.
No game/native replay, source adoption or promotion occurs;393 overall/248
authored exact/22 candidates remain incomplete. The next primary static question
is406670's observed metadata normalization path and record+10 transformation,
not another global/reset/prefix/rank observation or a source spelling/flag sweep.

## Primary metadata normalization window, October20

One derived raw-x86 window now covers406670..406B63, extracted from the same
pinned C1XX at file23152:1,268 bytes, SHA256
`4004675e12638118f1673edf7d2db299870adba7ca45bf8ab3754acad5dd129a`.
REA6.5/Ghidra12.1.4 reads every byte and returns332 instructions in two inclusive
body ranges406670..406AE3 and406AFE..406B63:1,242 analyzed bytes. The26-byte gap
406AE4..406AFD is read but not claimed as code, padding or full-function coverage.
External cold branches, callees, globals and table406E70 remain outside this
fragment. Its generic gcc profile does not recover the original ABI or types.
The four historical48-byte samples overlap this fragment only partially:
32/46/47/31 bytes,93 unique bytes, not four complete contained samples.

Primary instruction Evidence
`ev_d5dfe4802cdf53062a47cc62c721d527f750bf4063ad2342e055e30cbf009120`
and five separate instruction facets establish the local dataflow. Entry EDX
supplies the record and ECX the context.406675 reads record+1C;40667E spills it
to final ESP+18 before406694..4066A6 copies it into the working ESP+10/+14 pair.
ESP+18 later becomes0/1 control scratch, not retained payload.406B42..406B4A
reloads/writes the working value to record+1C. The zero-companion fallthrough
at406B59 clears byte+1F bit0. These are metadata operations; the observed20→20
does not decode a source-type enum.

4066E8 loads context+28 into EDI;406718 can store that value to record+10.
The later path reloads record+10 and406B56 can store EDI again. This fits the
historical context+28=958354 and record+10 transition3BC4F98→958354, but neither
candidate store was directly watched and the complete executed path is unknown.
Static possible stores are not a newly observed execution.

A separate read of the hash-bound historical trace adds a positive type-carrier
association. In the same PID280/thread284, named nbytes writer hit17231 and
reader hit17273 both have ID28285, symbol62374476 and record+10=958354. Its
archived source declares `DxBallUInt nbytes`, with the unsigned-before-product
assignment. The selected anonymous record acquires this same descriptor value.
Named nbytes has record+1C=24hex, while the anonymous record has20hex: the latter
is not itself a UInt enum. This establishes same-run descriptor equality to a
known source declaration, not the anonymous record's source identity, continuous
lifetime or actual typed conversion/product consumption. No source repair is
justified by this historical mechanism alone. Original source/debug material is
neither available nor required to continue the reconstruction.

All seven complete records equal the saved65,394-byte snapshot. The query closes
normally; outer Evidence
`ev_4e5ac1eaf377ca388d91baef260afa50a2092ac06a0aaa384b5886fdd06633ce`
exits0, untruncated, with owned process-group cleanup verified and temporary
root removed. The exact provider workspace is independently absent afterward.
The172.769s capture holds one CPU/35%,384/512MiB and256MiB JVM limits; peak is
403,177,472 bytes with2,906 soft memory.high events and zero max/OOM events.
Process sampling remains nonexhaustive. There is no whole-image import retry,
compiler run, native/game replay, source adoption or exact promotion.

Private authority is
`.analysis/rea/c1xx-record-normalization-20261020/result.json`. Independent
integrity and dataflow reviews pass. All901 direct protections and four prior
archived aliases verify unchanged before closure. All22 closed helpers, reviews,
responses, raw window and snapshot are member-size/SHA256 verified in a102,374-byte
archive before removal, releasing724,992 allocated bytes net before journals.
Afterward898 protections remain direct; three phase protections and the four
prior aliases remain recoverable from their archives. Current tested products,
useful caches, originals/tools and the original141-record snapshot stay fixed.
Current393 overall/248 authored exact/22 candidates remain incomplete. Follow
actual typed conversion/product consumption or a separately evidence-backed
source family; do not repeat these decoded windows or the closed watches.

## Primary descriptor-to-expression prefix, October21

The retained consumer event23 identifies a new caller edge42377B->41B33B.
One hash-bound raw-x86 window now covers41B33B..41B7FF, file108347:1,221 bytes,
SHA256 `f6223a06a23189cf45b85161b0439faef2e10bbc7fbfe9988b220f13085c222f`.
It comes from the same attested C1XX, not another whole-image import. REA6.5/
Ghidra12.1.4 reads every byte and retains six primary records in a separate
46,748-byte snapshot; the original141-record snapshot remains unchanged.

Wrapper instruction Evidence
`ev_1fd10f2ae319915bcd80b54f9bcb013c61c59a867db182519ff5b4e78583a825`
establishes13 instructions/45 bytes at41B33B..41B367.41B345 loads the stack
operand;41B351 loads the input record's DWORD+10;41B35D/35E pass operand on
stack and that descriptor inEDX to CALL41B360->41B663. Null inputs and selectorF1
leave through external branches. These are register/ISA relations, not a recovered
prototype or proof that event23 actually entered with the selected record.

Constructor-prefix instruction Evidence
`ev_241c2c6969805a8c687ef675aea85addb4177206153cc32f3f8e47aa6e485234`
adds113 instructions/413 bytes at41B663..41B7FF.41B666 saves **CL only**;
later DWORD ECX reloads from stack+13 do not establish zero-extended0x66.
41B66B/674 pass the operand to unknown helper408B52;41B679 stores the returned
working operand. ESI carries the descriptor,41B67D reads its+4, and later paths
inspect descriptor/header words and working-operand+4. No returned-node field
write appears in this prefix: the explicit writes are stack writes.

The selected instruction bodies cover458 bytes; the intervening763 bytes were
read but are outside these two instruction results. They are not classified as
padding or data. The413-byte body ends mid-path at the raw-window boundary;
forward41B911/91F/9FA branches,45xxxx cold paths and external callees prevent a
complete original-function/ABI/type claim. The generic gcc raw profile does not
repair those missing contexts.

The smallest new static edge is41B706->4101AE on the unsigned EAX<0x400 path, carrying the
descriptor, selector carrier and working operand. Another path calls43EBE5 at
41B787. The selected actual path and returned-node write schema remain open.
Historical event23's header0x166, descriptor958354 and child pointer3BC5014 remain
observed post-state, not proof of the selected-record call entry, conversion
semantics or product consumption. No new source variant follows yet; do not
repeat this prefix, closed normalization/global/reset/rank watches or name/ID
searches. Missing original materials are not an external prerequisite.

The initial helper wrongly holds the same non-reentrant lock that `scripts/rea
mcp` acquires in its child. MCP initialization times out60s before any catalog,
open or provider query; the original source gate missed this dispatcher lock.
Evidence `ev_3805b868d5286f897755b813a6d03f5dffc9ac12fabfbdf7f87ff8cdc50b5351`
retains child exit1/capture CLI exit0, verified cleanup and untruncated output.
A separate reviewed continuation removes only the redundant outer lock, preserves
the first attempt and keeps every query/input/resource/time limit unchanged.
It adds connection-stage logging and fail-closed inner-exit propagation; no
completed analysis is repeated.

The continuation closes normally. Process Evidence
`ev_d1c9e66852be4e93f6625867a008fb487ebd7bd2c7e7ea4f356000d9eec9d9f4`
records child/CLI exit0, verified cleanup and untruncated output; the exact owned
provider workspace is absent afterward. All402 initial and416 continuation
byte/stat seals pass. The one-CPU/35%,384/512MiB and256MiB JVM limits hold, with
403,083,264-byte peak,1,470 soft-high events and zero max/OOM events. Its26 process
observations are sampled, not exhaustive history. Independent integrity and
dataflow reviews pass, including all six snapshot records by ID rather than
assuming call order.

Private authority is `.analysis/rea/c1xx-operator-constructor-20261021/result.json`.
No source compilation, native/game build, source adoption or exact promotion occurs;
current394 overall/249 authored exact/21 candidates remain incomplete.
Both attempts'36 closed files, including every primary response/snapshot and
failed helper, are member-size/SHA256 verified in a124,762-byte archive before
removal, releasing872,448 allocated bytes net before journals. All398 remaining
direct protections and18 archived phase aliases verify size/hash/mode/nsmtime.
Current products, useful caches, originals/tools and the original141-record
snapshot remain intact; every retired member is individually recoverable.

## Primary numeric-selector dispatch, October21

The conditional41B706->4101AE edge is now decoded from the same pinned C1XX.
Three distinct raw-x86 windows read1,920 bytes in total:4101AE..4104AD,
411DB0..4120AF and41367C..4137FB. Eight individually complete primary records
retain three selected instruction bodies:198 instructions/494 bytes. The other
1,426 read bytes are not classified as padding/data or claimed as decoded bodies.
Two successful sessions save separate three-record snapshots. The third session
ends with a retained partial failure; its two successful records remain in their
complete raw response files, not a fabricated snapshot.

Evidence `ev_17558d10f7fa435b80407e6c58962832eb8c0777c388200743b54e38f56fd1f0`
establishes112 instructions/295 bytes at4101AE..4102D4. This path can return an
existing operand, clear its byte+1 bit7, or retag its DWORD+4 with the descriptor
carrier.410287 modifies helper-returned descriptor word+2;410292 decrements
global4B5C80. Other paths return40F4ED,411DB0 or41368A results. No header0x166 or
child+0x10 store appears. BL receives CL only, so subsequent ECX<-EBX does not
establish zero extension. Cold4537CC/4537D5/4537E1 paths remain outside the body.

Evidence `ev_d4741fa016fe145de5770351fb3be6a9a6dd0fce880f660b6fb3afff645d26ee`
adds81 instructions/185 bytes at411DB0..411E68, called conditionally at410220. It has
no direct node/object store or identified allocation. After earlier helper,
descriptor and operand-flag gates, BL==0x66 or BL==0x1 dispatches ECX=descriptor,
EDX=operand to41367C at411E4C. Other selectors first call41ABE8. Other branches
return411469,4100D0,419DE5 or43C135 results; cold4542FF/454308 paths remain open.
This establishes numeric dispatch, not an executed event23 conversion path.

Evidence `ev_5dff2f3da489ccad2c3f3c6e5e8dfe5187fd3530bc8ce41eb8c5e3165670c089`
then establishes the five-instruction/14-byte wrapper41367C..413689:
PUSH EDX; MOV EDX,ECX; MOV ECX,0x66; CALL41329B; RET. Here the complete ECX is
explicitly overwritten with0x66, unlike the earlier byte-only saves. Descriptor
and operand reach41329B in EDX and on stack. Its field writes are not observed.
This wrapper also does not prove event23's0x166/+4/+0x10 returned-node schema.

The third import seeds only41367C. The separately reached41368A has no procedure
in that analysis; its instruction request returns invalid_request/invalid_input,
with remote not_found diagnostics stating "No procedure exists". The helper stops,
closes without a snapshot and never issues either planned entry facet. This is
not evidence that41368A is not a function. No completed query is repeated and
no whole-image/profile/source variant is attempted. Process Evidence
`ev_73adf41e82bc86d5bb01a91df42a8707c520da713aec8bd9592b66230e02c8a7`
retains child exit1/capture CLI0; the outer controller correctly propagates1.
All26 raw frames/16,288 bytes are retained, but one rendered frame has unknown
size, so the aggregate truncated flag remains true. No five-record success or
untruncated-capture claim follows from the two complete primary responses.

All411/430/449 direct byte/stat seals and18 prior archived aliases pass within
their respective captures; the original141-record snapshot and current products
remain unchanged. Owned-process cleanup and provider-workspace removal verify.
The second capture also retains three EACCES process-visibility warnings: one
PID is currently an unrelated root system service; the other two are absent.
Those scoped observations do not establish exhaustive historical ownership.
The one-CPU/35%,384/512MiB and256MiB JVM caps are unchanged. All three captures
have soft-high events but no max/OOM events. Independent source, integrity,
dataflow and partial-failure reviews preserve these distinctions.

Private authority is `.analysis/rea/c1xx-node-factory-20261021/result.json`.
No source/options/object adoption, source compilation, native/game run or exact
promotion occurs;394 overall/249 authored exact/21 candidates remain incomplete.
The next missing relation is the actual selected-record call entry, taken
constructor/dispatch path and returned operand/node identity. Use a bounded
call-entry/return observation of the unchanged historical input before further
static callee expansion or any source variant. Zero selected-route hits are a
meaningful negative result, not grounds to retry or broaden the observation.
Do not repeat the decoded bodies,
global/reset/rank watches or identifier/flag sweeps. Existing EXE/resources and
retained toolchain artifacts remain the reconstruction inputs; missing original
source materials are not an external prerequisite.

All56 closed phase files, including the partial-failure helper, full responses
and both snapshots, are individually member-size/SHA256 verified in a225,062-byte
archive before exact-file removal. Net allocated release is1,634,304 bytes before
journals. All408 remaining direct protections and59 archive aliases retain their
byte/stat identities, including mode and nanosecond mtime metadata. Current
products, useful caches, tools/originals and the original141-record snapshot
remain intact; every retired file is recoverable from the closed archive.

## Executed selected-record constructor path, October21

The next bounded experiment observes the missing entry/return relation, using
exactly the nine frozen historical AFTER inputs from the closed record-consumer
experiment. It does not introduce a source hypothesis or compile current game
source. One independently reviewed utility build and one VC4 compilation run;
there is no retry, flag/identifier variant, native/game build or source adoption.
The utility retains seven reviewed warnings, not a warning-free build claim.

Process Evidence
`ev_4636a6e2a3ed0e185b0984234ae7d3d5eeb9a75f4e1dcfc00554028a35621bf5`
retains terminal child/CLI0, the complete33,169-byte/21-row trace and an
untruncated capture. CL, C1XX and C2 each enter and exit once with zero status.
The observer uses execution-only hardware slots, not code patches, single-step,
data watches or edits to ordinary registers, PC, arithmetic flags or source IDs.
Its RF/debug-context writes have32 preservation readbacks for31 hardware hits;
these are observer guard attestations, not31 separately retained raw contexts.
There are11 bounded raw snapshots, including the first/start/stop boundaries.
The one-CPU/35%,384/512MiB caps hold; peak capture memory is152,780,800 bytes,
with no memory events. Owned-group cleanup and temporary-root removal verify.
Process samples are not exhaustive; non-atomic image binding, inherited
environment and unobserved network activity remain explicit limitations.
The X connection shutdown diagnostic is retained with the zero-status capture.

At4163F5 counter28288/EAX28287, actual EDI is3BC5F70. Its raw prefix starts0x0C,
with DWORD+0x18 zero. The first eligible41B33B entry has return423780,
ECX=0x66 and EDX=3BC5F70. Pointer equality is an observation, not a selection
filter. Its stack operand is3BC601C, whose raw prefix starts0x13F and has
DWORD+4=958344 and DWORD+0x10=3BC6004. The selected record's raw prefix has
changed by this entry, including DWORD+0x10=958354 and DWORD+0x18=28287;
these snapshots do not establish continuous object lifetime or a persistent
record schema.

The actually observed chain is
41B33B ->41B663 ->4101AE ->411DB0 ->41367C ->41329B, with captured return
addresses41B365,41B70B,410225,411E51 and413689 respectively after the wrapper.
At4101AE the full ECX is0x166; at411DB0 it is0x66. This distinction is retained,
not erased by treating every byte-only selector save as zero extension.
41367C receives ECX=958354 and EDX=3BC601C. At41329B, all five independent
raw transport relations hold: return413689, fullECX=0x66,
EDX=the route-entry ECX, stack+4=the route-entry EDX and
ESP=the route-entry ESP minus8.

At413689 the matched route frame returns EAX=3BC6034; its64-byte raw prefix
starts DWORD0x166, with DWORD+4=958354 and DWORD+0x10=3BC601C. The latter is
the numeric operand captured at wrapper/route/builder entry. The matched423780
caller frame returns the same EAX and the same64-byte prefix. EAX differs
numerically from both the selected record and operand. This establishes the
executed relation for this call; it does not yet identify41329B's field stores,
prove fresh allocation, assign a semantic type or prove unsigned-product
consumption. Prefix bytes remain raw observations, not initialized-field claims.

Every selected call/path/return snapshot still has counter28288. The next
observed4163F5 boundary is28289; the call has returned and all slots are cleared,
with no missing-return cutoff. Counter coverage is limited to4163F5:31 total
hardware hits do not mean all global counter increments or writers were traced.
No expanded window or additional route search follows the positive result.

Complete18-function/262-binding/six-entire-carrier comparisons pass against the
frozen baseline. All ordered normalized COFF sections, payloads, flags, actual
relocation targets and non-FILE symbols/raw auxiliary records also agree.
Different FILE path/auxiliary records are retained separately; timestamp and
transport offsets are excluded, so this is not raw-object identity. Current
source/options/products/caches and the original141-record snapshot retain their
sealed identities. Independent source, prepared-input, build, integrity and raw
dataflow reviews retain the same bounds.394 overall/249 authored exact/21
candidates remain unchanged and the exact-recovery objective remains active.

Private authority is `.analysis/glyph-constructor-entry-20261021/result.json`.
The next narrow question is the complete41329B builder body and the stores or
reuse branches that account for this now-executed0x166/+4/+0x10 result. Use this
captured descriptor/operand transport rather than another global/reset/rank
watch, repeated constructor prefix, source-ID/flag sweep or original-source ask.
No source model is justified solely by the numeric node prefix.

All42 closed files, including the unique trace, full process responses,
observer sources/EXE, historical inputs and objects, are member-size/SHA256
verified in a200,680-byte archive before exact-file removal. Net allocated
release is729,088 bytes before journals. All420 remaining direct protections,
63 archived protections and12 separately recorded copied-input seals preserve
their byte/full-mode/nanosecond-mtime identities. Retired files are recoverable;
current tested products, useful caches, tools/originals and the original141-record
snapshot remain intact. Plans, results and independent result/dataflow reviews
remain directly available.

## Selected builder field stores and retained parent, October21

The executed41329B entry now grounds one fixed1,024-byte raw-x86 window from
the same pinned C1XX, file75,419, SHA256
`db14ccd47fbdb0c0b80974c3cccef3c75d7accfbf91323f8910c157514333b34`.
Three complete primary records and a23,118-byte snapshot retain the bytes,
selected instructions and entry facet. No whole-image import, repeated entry
observation, source variant/compile, native/game work or adoption follows.

Instruction Evidence
`ev_356e9f7370e742e53e19de51cddde85ad83a72e3f0c6243a078477f32c0c3ba5`
establishes34 instructions/104 contiguous bytes at41329B..413302. The other920
read bytes are not claimed as the selected body, padding or data. The entry
facet independently decodes53/PUSH EBX. The common return path has these writes:

| Instruction | Width | Destination | Value |
| --- | --- | --- | --- |
| 4132CE | byte | EAX+1 | 1 |
| 4132D6 | byte | EAX | saved lowCL |
| 4132D9 | DWORD | EAX+0x10 | incoming stack+4 operand |
| 4132DC | DWORD | EAX+4 | saved entryEDX descriptor |

The three saved registers account for the ESP+0x10 operand reload.4132E1
restores the caller frame with RET4; these stores leave returnedEAX unchanged.
For the already observed fullECX66/EDX958354/operand3BC601C entry, this accounts
for lowWORD0166 and the captured descriptor/operand fields in returned3BC6034.
Only the low16 header bits are explicitly constructed. No visible instruction
clears bytes+2/+3, DWORD+8/+C or DWORD+0x14. Prior observed zeroes are not a
general initialization guarantee; unknown helper/cold effects are outside this
explicit-store statement.

Storage selection first loads global4B1B30 after the captured runtime entry.
Thus entryEAX1 does not establish its value or the executed branch. A nonzero,
non-minus-one value indexes16-byte control records at4B1AB0. Their DWORD+8
cursor and DWORD+C remaining size consume0x18 bytes before the common writes.
An unsigned remaining-size failure calls402F91 with ECX4B1AA8/EDXcontrol record,
then resumes cursor consumption without another local size test. Zero instead
calls424A15 with ECX4B0F54/EDX0x18 and initializes its returnedEAX. Minus one
branches to45508C outside the window. Both helpers and that cold branch remain
unknown. These allocation-like operations establish neither a free-list,
fresh allocation, continuous lifetime nor an observed storage branch. The
visible body has no return-existing-operand alternative, but external behavior
remains open. Generic raw/gcc context does not prove an original ABI/type or
complete original cold-function extent.

Process Evidence
`ev_f137247ed209dee081241c38e7711fb8997677e7e462cd98c2fe95dc24c419db`
retains child/CLI0 and all19 raw/rendered frames, untruncated. Owned-group cleanup,
temporary-root removal and the exact provider-workspace absence verify.
All433 direct full byte/stat seals,63 archive aliases and12 separately preserved
copied-input aliases agree. The original141-record snapshot and current
products/caches/tools/originals remain unchanged. One CPU/35%,384/512MiB and
the observed256MiB Java heap hold. Peak is403,111,936 bytes, with1,241 soft-high
events and zero max/OOM events. The67,818ms byte-read timing is client/tool-call
wrapper elapsed, not isolated provider CPU.23 process observations remain
sampled; standard image-binding/environment/network unknowns remain explicit.

A separate bounded read of the existing historical consumer trace supplies the
next association without another capture. Its SHA remains
`0df75816d84d144ad41cd414038a6f5d86b5f1384a5e6a7a11488c0a0503ff7c`.
In that older PID280/thread284/counter28288, consumer_access_watch event23's
returned166-prefix R=3BC502C later appears at DWORD+0x10 of P=3BC5088.
Events45@postPC42374A and48@postPC4235CB capture the same first24 parent bytes:
`[0x24C,958354,0,0,R,3BC5070]`. Events12/32@postPC423A63 separately capture
the13F-prefix operand-side records3BC5014/3BC5070 with descriptor958344.
Event48 also observes P at DWORD+0x14 of a236-prefix record. These exact event
kinds are not the unrelated same-numbered counter_write_watch rows.
This is same-run numeric parent/descriptor association, not proof that4C means
multiplication,13F denotes a named source operand, or either descriptor is a
universal signed/unsigned enum. Do not equate old pointer addresses with objects
in the separate latest observer process or infer continuous lifetime.

Private authority is `.analysis/rea/c1xx-selected-builder-20261021/result.json`;
the archived historical-parent-association receipt pins the additional old-trace
read. Independent integrity and dataflow reviews pass.394 overall/249 authored
exact/21 candidates remain unchanged; the all270-authored-exact goal is active.
The field schema is now answered. Reuse the retained post42374A/4235CB
operator/descriptor consumer before any new primary query or evidence-backed
whole-source-family model. Do not follow424A15/402F91/45508C merely to prove
freshness, repeat166 entry/builder/prefix/global/reset/rank observations or
rerun rejected unsigned/name/ID/flag variants. Numeric headers alone do not
justify semantic product/type claims.

All21 closed files, including the three full primary responses/snapshot, raw
window, helpers and historical-parent sidecar, are individually member-size/
SHA256 verified in an81,697-byte archive before exact-file removal. The full
mode/nanosecond-mtime manifest is persisted before the first retirement. Net
allocated release is548,864 bytes before journals. All428 remaining direct
protections and68 archive aliases preserve their identities, with12 earlier
copied-input aliases kept separate. Current tested products, useful caches,
originals/tools and the141-record snapshot remain intact and retired files are
recoverable; plan/result and independent integrity/dataflow reviews remain direct.

## Known product route and retained raw names, October21

One fixed, include-free source function returns `left * right` for two
`unsigned int` parameters, matching the primitive current `DxBallUInt` alias.
One observation utility build and one VC4 compile use the unchanged nine flags,
including `/Od` and `/ML`. No game source, options or installed object changes;
no game/native build or play check occurs. There is no input variant or retry.

The actual compiler run records one same-thread tuple:

| Site | ESP | Observation |
| --- | --- | --- |
| 423740, before CALL | 31FCD4 | ECX4C, EDX3B501F0, stack operand3B50234 |
| 4102D5, actual entry | 31FCD0 | return423745; both inputs/fullECX unchanged |
| 423745, caller return | 31FCD8 | EAX3B5024C, prefix `[24C,958354,0,0,left,right]` |

All three compiler processes exit0. Three hardware hits have four context
preservation readbacks, no mandatory read failure or active frame at exit.
Trace SHA256 is
`8934a3ac55a9c0c51fb083494af6ae3f1ff4d1356def35ef8c66ce227861c700`.
The strict predeclared calibration **does not pass**: graph queues drop
117/117/118 candidates, and the kind9 parameter decoder rejects the actual
low-kind10 records. Its `semantic_candidate=false` and null names are retained.
Zero mandatory read failures would not cover optional graph reads; these
bounded depth4/64-node snapshots are not a complete graph.

A separate posthoc read of those same retained bytes, without another target
execution or query, finds complete numeric paths:

```text
3B501F0 (13F) +10 -> 3B501D8 (402) +10 -> 3B7C168 +8 -> 954B90 "left\0"
3B50234 (13F) +10 -> 3B5021C (402) +10 -> 3B7C1D8 +8 -> 954BA0 "right\0"
```

Offsets above are hexadecimal. Both intermediate raw records have header
0400020A, low5=10. This is an observed pointer/string association, not a new
general symbol-kind10 decoder, type proof or repair of the frozen negative.

The entire420-byte COFF has two sections, four primary symbols/13 total slots
including FILE auxiliaries, and exactly one defined external function. Its
whole23-byte `.text` has no relocations or additional executable payload.
Three complete primary records and a17,684-byte snapshot inspect every byte.
Instruction Evidence
`ev_12fa65c18da7077bf847afd0ce12455b8b0693846507c650097dd77ee59feef0`
covers13 instructions, contiguous10000..10016: load the second stack parameter,
IMUL by the first, jump to balanced register/frame restoration, RET. The low32
product is equivalent to the unsigned-int source product modulo2^32 for all
32-bit input patterns. This is static body equivalence, not arithmetic execution;
the generic raw import's gcc context is not original-compiler ABI evidence.

Together, the fixed source, actual tuple, retained name bytes and whole output
corroborate a multiplication interpretation for this particular4C/24C route.
That is a contextual inference, not a passed strict calibration or universal
opcode enum. Combined with the earlier166R->24CP+10 association, it gives the
old parent multiplication-context evidence, not a direct old-entry observation,
166 conversion/type meaning, universal signedness descriptor, original-game
source spelling, continuous lifetime or cross-process object identity.

The older trace also already contains numeric4C transport. Of923 rows/108
consumer events/101 global accesses, current-or-previous4C occurs exactly at
consumer27,28,29,86,87,88,91,92. Early26 transfers R's first DWORD to3B8BB10,
the later raw EDX input slot, not an established descriptor.27 transfers4C into
global4B4D40;28 transfers that first DWORD to later selector slot3B8BB28.
These are DF0/F3A5 restart observations, not a completed six-DWORD copy or
static literal/table-row proof. Later86+ uses a different cell3B8BB40;92 changes
the global, not necessarily that cell. The sidecar pins all exact boundaries.

Process Evidence
`ev_7c2477af367dca8d2b702a1859d1435c5c2ace87555fb983f5aa140ac44a5b89`
retains the known-source compile, and
`ev_6497c1767250eb1743c5282272dc1b4456c7b122816e3f746ddabb3cfaf8e4cf`
retains the one output import. All three process captures have CLI/target0,
untruncated1/1 raw/rendered frames, quiescence and verified owned-group cleanup/
temporary-root removal.9/11/21 process observations are sampled. CPU0/35%,
384/512MiB and observed JVM256MiB hold. Import peak403,128,320 bytes has1,292
soft-high events, zero max/OOM; image-binding, environment and network unknowns
remain explicit. All442 direct seals,68 aliases and12 separate earlier copies
hold before cleanup, including current products/caches and the141-record snapshot.

Private authority is `.analysis/rea/c1xx-product-calibration-20261021/result.json`.
Independent integrity and dataflow reviews pass within those scopes.249 authored
exact/21 candidates and394 overall remain unchanged; the all270 goal is active.
Reuse the selected166->24C->236 operand/descriptor consumer with this contextual
product evidence. Do not rerun calibration for name/kind/depth variants, repeat
166 entry/builder/global/reset/rank watches or rejected sourceID/name/flag sweeps.
Existing EXE/resources remain sufficient; no original source/debug material is needed.

All50 closed files, including the observation EXE, full COFF, temporary input,
helpers and unique raw responses, are individually member-size/SHA verified in
a210,752-byte archive before exact-file retirement. The full mode/nanosecond-mtime
manifest precedes the first unlink. Net allocated release is917,504 bytes before
journals.436 direct protections/74 recoverable archive aliases and12 separate
earlier copied-input aliases preserve their identities; current products,
useful caches, tools/originals and the141-record snapshot remain intact.

## Binary operand descriptor consumer, October21

The next fixed1,024-byte C1XX window starts at the actually observed binary
entry4102D5, file63,189, SHA256
`f78703ab3d87bbb8e8df21516ff99a888742d5fd356e6ac3bfbb470a6e36c288`.
The earlier node-factory carrier already read473 of these bytes;551 extend it.
Its previous decoded body ended4102D4, so this is a new consumer decode, not a
repeat of the166 builder, allocation/reset/rank watch or known-source calibration.
One raw import yields three complete primary records and a26,460-byte snapshot.
No compiler/target execution, game source/option change or object adoption occurs.

Instruction Evidence
`ev_1d627f8be7aa990e5d4fdd122624c955f29222b22b00ed58105a305599bdf1b7`
covers95 instructions/289 bytes at4102D5..4103F5. The other735 read bytes are
not classified as code, padding or data. Six cold destinations4538xx lie outside
the import: provider-selected body coverage is not whole original-function
coverage. The generic raw gcc context does not establish the original ABI.

The visible entry saves24 bytes of local/register space, holds entryEDX inESI,
and reads the original stack+4 operand intoEDI. BL saves entryCL; no instruction
clears EBX's upper bits.408BBD(ESI) returns a value retained inEBP, while408030
returns the newEDI. Their classification/transformation semantics remain unknown.

| Visible site | Explicit relation |
| --- | --- |
| 41033D..410342 | Push EDI, forward ESI inEDX and EBX inECX, call411E69 |
| 410364 | Alternate path delegates to41ED2D |
| 410395..4103A5 | Conditional BL36/EBP test reads[ESI+4], tests descriptor byte+1 with mask0x02 (bit1), then may branch externally |
| 4103BE..4103C1 | Another conditional read[ESI+4] feeds40F5B5 |
| 4103CD..4103D1 | Its lowAX code feeds419A9C with selector/EDX2; result chooses generic dispatch or external branch |

Selectors34/51 have a separate right-operand helper path;4C is not explicitly
compared here. None of these95 instructions directly reads right+4 or stores
returned-parent+4. This local absence does not cover helper/cold effects. Visible generic
construction and descriptor selection are delegated, principally to411E69; the
actual historical call's taken branch is not observed inside this fragment.

Stack offsets are reconciled without inventing a helper signature. With
`B=entryESP-24`, localA isB+10hex and localB isB+14hex. After the first PUSH,
41035A's `[ESP+14hex]=0` clears localA, not localB. Three stack arguments enter
41ED2D. Normal balanced continuation would require a net12-byte removal before
410369 writes localB and4103AB reads localA. Its RET/actual cleanup is not decoded
here, so this is a conditional stack relation, not a recovered RET12/ABI.

Existing old trace rows also name kind9 records width3B7C00C/ID28281,
height3B7C09C/28282 and nbytes3B7C24C/28285. The historical source declares signed
width/height and unsigned nbytes; their numeric descriptor associations are
958344/958354, not universal type enums. Consumer5/6's nonaligned64-byte prefix
contains L3BC4F24 `[402,958354,0,0,nbytesSymbol,0]`. Later48's236-prefix parent
has L at+10 and the24C-prefix product parent at+14. These are separate snapshots,
not continuous lifetime or an assignment enum proof. The earlier counter190
sample precedes these consumers; its different bytes are not a later reset/reuse
writer. Zero-based row ordinals are explicit in both archived sidecars.

Consumer47 already samples36 in candidate selector slot3B8BAF8 before48,
but not at the actual call entry. Global36 transport at76/77/78 is later than48
and63's clear and cannot be48's last definition. Repeated numeric slot addresses
do not prove no intervening writes or a completed six-DWORD REP transfer.

This static phase has no REA behavioral process capture. Its owned utility
returns0 in108.913s; full responses/log/status remain retained. CPU0/35%,384/512MiB
hold; peak403,247,104 bytes has940 soft-high events, zero max/OOM. One selected-field
owned-cgroup sample observes actual JVM `-Xmx256M`; all five sampled PIDs and
the exact temporary workspace are absent after close. This is not exhaustive
process cleanup, atomic image binding, inherited-environment or network evidence.
All448 direct seals,74 aliases and12 separate earlier copies hold before cleanup.

Private authority is `.analysis/rea/c1xx-binary-descriptors-20261021/result.json`.
Independent integrity/dataflow reviews pass within these limits. No source model
or new exact follows:249 authored exact/21 candidates and394 overall remain.
The next specific consumer is411E69, for which a retained raw carrier already
exists but no primary decode does. Reuse it before a focused new query; do not
automatically expand this phase into cold/error helpers, repeat old observations
or resume ungrounded source/name/ID/order/flag trials. Existing EXE/resources suffice.

All21 closed files, including full primary responses/snapshot, raw window,
helpers and historical/process sidecars, are individually member-size/SHA verified
in a69,024-byte archive before exact-file retirement. Full mode/nanosecond-mtime
descriptors are persisted before the first unlink. Net allocated release is327,680
bytes before journals.444 direct protections/78 recoverable aliases and12 separate
earlier copied-input aliases retain their identities; current tested products,
useful caches, tools/originals and the141-record snapshot remain intact.
