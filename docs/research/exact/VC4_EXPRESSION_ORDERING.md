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
