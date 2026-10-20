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
