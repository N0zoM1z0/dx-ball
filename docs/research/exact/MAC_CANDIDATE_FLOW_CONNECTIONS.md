# Mac candidate-flow connections

Two focused REA6.5.0 process captures reuse the saved Ghidra12.1.4 PEF project
on October18. Five newly selected bodies connect score drawing, waiting and
lightning to the Windows reconstruction. They supply no independently justified
new Windows source model, so no compiler, relink, replay or game runs follow.
Current totals remain250 authored exact/20 candidates; the19 permitted original
CRT dependencies and current delivery remain unchanged.

This follows the [carrier and font work](AUTHOR_SOURCE_CONTEXT.md#focused-pef-bodies-and-qualifier-control-october18).
The private Mac carrier SHA-256 is
`f1004702aed6416ed5eca4a02ae6c276c8f66be0a3e5f7155a95cb537c37b69b`.
These are `rea-process` observations of the analysis engine, not successful
native PEF admission or native-provider snapshots. There is no reimport, global
analysis or runtime/TOC context assignment. The selected32-bit profile remains
`PowerPC:BE:32:default`; decompiler types and metadata-derived extents retain
their stated limits.

## Complete selected bodies

| Mac named body | Bytes | Decoded / explicitly undecoded words | Result |
| --- | ---: | ---: | --- |
| `drawScores` |456 |114 /0 | Score-row drawing family, with additional table/title work |
| `vwait` |120 |28 /2 | Platform-specific deadline and message-pump implementation |
| `doLBricks` |224 |56 /0 | Exploding/hit-brick list dispatcher, not the countdown |
| `doLightning` |676 |169 /0 | Actual last-brick countdown family, with material port changes |
| `showLightning` |212 |53 /0 | Four-frame overlay family, with a different drawing boundary |

Independent review verifies all1,688 bytes/422 words against the original PEF,
including file/VA mappings, raw/loaded hashes, branches, calls and exits. In
`vwait`, the two undecompiled words are not both padding: `48000010` at100034E0
is an unlinked relative branch to100034F0; `60000000` at100034E4 is a NOP.
The selected entry CFG bypasses both. Preserve them and the additional raw
branch explicitly rather than claiming every word was decoded.

Full process Evidence is
`ev_69b9e8fdc66b48a837098af444cfab693d675d11b097500bea61a81bd0a9d427`
and `ev_eed2b0f1c6dc8f0c3214fdd1be1cb32ecd80a0ae4e3360dbab8acb706b01a47d`.

## Score rows, line drawing and waiting

Mac and Windows score drawing share15 records of44 bytes, name/score offset
difference40, Y170 with20-pixel advance, four selected-row lines at X5/635 and
Y-14/Y+5, and score text right-aligned to630. Complete original Windows evidence
is `ev_a42b5c952ba3c544d58bf1b3c0c2456c9e13f6149d7090c32e2952888fd6ff3e`.
Mac additionally selects a score table and draws its centered title. Its
format-style score call differs from Windows `_ultoa`. The two CRT-like Mac
targets have no positive names in the321-record traceback inventory; their
roles are inferred from call/data use, not recovered `strlen`/`sprintf` symbols.
The decompiler's24-byte stack array does not establish source buffer capacity
or justify changing the Windows20-byte workspace. The current Windows draw
candidate remains403/404 bytes with one comparison-producer difference.

The retained176-byte Mac `line` body and complete445-byte Windows dossier
`ev_25f8571b40b1ee8c589f398fa1211552c03d241352d0737d904789e2664b8af2`
share signed X/pitch steps and the asymmetric error tests: shallow error>dx,
steep error>0. Windows owns the surface-description/lock retry/unlock wrapper;
Mac accepts pixels and pitch directly. This connects the drawing algorithm
for valid nonoverflowing coordinates without recovering Windows declarations,
local scopes or backend comparison ranks. Reuse the closed
[line control](LINE_LOCKED_CURSOR.md); do not resume declaration permutations.

Mac `vwait` compares the unsigned clock against a stored deadline, pumps
messages while waiting, samples again and stores clock+15. Actual metadata
binds its callees to `cp_pumpMessage` and `cp_timeGetTime`. Windows has separate
vertical-blank and17ms software-wait paths, including a backward-clock escape.
The foreign loop does not recover the missing Windows frame-cursor declaration.

`doLBricks` traverses current/head/next list state and dispatches node type1 to
`doExplodingBrick`, type2 to `doHitBrick`. Its complete body disproves the
proposed countdown correspondence based on the similar name.

## Actual lightning connection

All888 bytes/222 instructions/16 branches/17 calls of the Mac controller/overlay
are compared with the complete1,243-byte/357-instruction/27-branch/26-call Windows
pair. Original Evidence is
`ev_f8610be2baa2323aec8fcd14317794aebe74eefa78b4d66c9cf874ca117eb5bc`
and `ev_63003d5621ef73504e785882f80a70043ccee9a339118544b722116d679ac13d`.
Both families use a zero deadline, random20000 plus clock plus40000, an independent
expiry sample, a20x20 scan ignoring tiles0/2, centers at30x+35/15y+57, explosion
and spark creation, sprite1 in bank2, four overlay frames and restoration to bank0.

Material differences prohibit transferring the foreign body as Windows source:

- Mac calls RNG before its first clock; Windows calls clock before RNG. This
  cannot excuse the previously rejected [clock-expression controls](LIGHTNING_EXPIRY_SCOPE.md#complete-vc4-clock-expression-rejections-october18).
- Mac has one30-spark loop; Windows retains its15/30 reduced-particle split.
  Mac also omits the nonexpiry volume update and uses a different audio boundary.
- Mac leaves clipping to the named `Image::BlitClipped` boundary, passing local
  bounds0/0/639/479 in the overlay. Windows precomputes and saves the source crop
  in the controller, then uses COM `BltFast`. The Image callee is unread, so its
  rectangle mutation and drawing equivalence are not established.

Keep the Windows [complete crop producers](EXACT_LIGHTNING_CROP_CHAIN.md) and
explicit time-before-RNG sample. Neither literal operand spelling nor original
local declarations follow from the port's different compiler output.

## Reusable static evidence and resource limits

One capture also retains the645,276-byte loaded data image,3,134 `APPLIED`
relocation records, symbols and a bounded512-byte startup window. All8,830
raw/loaded differing bytes lie inside the recorded four-byte relocation fields;
this is not independent verification of every CFM relocation opcode. The entry
descriptor contains PC1001DA90/TOC10064D70. Conditional evaluation using that TOC
finds `%d` at the score format displacement. No selected-body runtime r2 value,
absolute global identity or original source declaration is established or applied.

All747 protected hashes, modes and nanosecond mtimes verify before documentation
edits. Both process captures exit0. CPU0/35%, memory high384MiB/max512MiB,
Node heap192MiB and Java heap128MiB constrain each serial heavy tree. Peaks are
403,161,088 and403,128,320 bytes; high events788/629, with zero max/OOM events.
Private `mac-candidate-bodies-20261018` and `mac-lightning-bodies-20261018` retain
the exports, static image, analyses and independent reviews. Reuse this evidence
and the useful saved project before another query.

All26 closed capture/projection members pass size/SHA-256 verification before
their listed raw copies are deleted. The archive, including both full process
responses, remains under `.analysis/rea/mac-reference-20261018/`; net allocated
storage released after archive/journals is655,360 bytes. Useful static data,
current products and incremental caches remain available.

## Reused bank/shape bodies and API-name control

The next question reuses five bodies from the earlier corrected export, with
no new engine query or import. Independent review checks all 1,996 bytes,
499 instructions, 33 calls and 19 branches. All words are decoded. The complete
Windows capture/load/release dossiers cover 2,589 bytes, 753 instructions,
32 calls and 31 branches; drawing checks retain their separate scope.

| Actual Mac name | Windows counterpart | Connected operation and limit |
| --- | --- | --- |
| `deleteshape` | `release-sprite` | Null guards, live indexed owner, release/free and slot clear; Mac uses an Image destructor instead of explicit COM release and surface clear |
| `getshape` | `capture-sprite` | Preliminary deletion, allocation/null/publication and metadata initialization; pixel capture uses a different backend |
| `loadshapes` | `load-sprite-bank` | Save/select bank, release slots1..253, ordered metadata reads, allocation/publication and bottom-up upload; Mac lacks the Windows allocation-mode argument and COM failure path |
| `fastdrwshape` | `draw-keyed-sprite` | Indexed Image draw through the named `BlitTransFast` boundary |
| `fastputshape` | `draw-sprite` | Indexed Image draw through the named `BlitFast` boundary |

These fast wrappers do not expose the separate Windows `blt-sprite` rectangle
producers. Named Image/read-helper targets establish boundaries, not the
implementation or all-input equivalence of those unread callees. Selected r2
contexts remain unset. The shared bank stride is `0x418`, but the observed
record allocation is43 bytes on Mac versus45 on Windows; the baseline field
is at38 versus40. Do not transplant the foreign record layout or reopen the
closed record-name model from those already distinct layouts.

The capture caller also demonstrates a decompiler prototype limit. Besides
r3..r10, it stores four outgoing words at SP+38/3C/40/44: the active pitch,
479, width and height. The named `cp_blit` signature encodes twelve parameters;
the default pseudocode prints only eight. Preserve the full caller evidence,
without claiming recovered callee semantics or changing the exact Windows
capture implementation.

Complete linkage supports one new, fixed function-identifier inference:
`loadshapes`, `getshape`, `deleteshape`, `fastdrwshape` and `fastputshape`.
These are inferred Windows names, not uniquely recovered spellings. The DOS
author evidence supports the first three family names, but its drawing names
are `drwshape`/`clpshape`/`putshape`; the exact fast-wrapper names come from Mac.
This differs from the closed parameter/local, record, global and qualifier
controls. No prefix, spelling or subset variants follow this one model.

The private proposal adds exactly five uniform header macros. It preserves
source call spelling and calling conventions, while changing emitted C-symbol
names. It does **not** preserve the old exported-name/dlsym ABI. No compiled
wrapper is added, and no native-consumer compatibility or source adoption is
claimed. The prospective header closure is28 owners/272 functions. One resource
pilot first compares all18 complete functions, 262 actual bindings, six complete
object/original-PE literal references and applicable local targets.

Every resolved code identity is unchanged. Thirteen prior exacts retain3,050
bytes; ordinary draw107/94, blt199/173, release269/245, bank1475/64 and PCX979/851
remain. Independent full-COFF review checks all26 section payloads and actual
relocation records. The five defined function names and corresponding string
table/offset encoding change, plus two timestamp bytes; no wrapper or other
symbol role appears.
Reject the whole model as an exactness improvement. The other27 owners/254
functions stay uncompiled and unknown for this proposal; do not claim their
outputs are unchanged or continue the name model.

The canonical header is staged only under the serial compiler lock and restored
in `finally`, including bytes, mode and nanosecond mtime. Toolchain verification
runs before/after the attempt, including failure cleanup. All749 protected
identities verify before documentation edits, explicitly including the current
resource object. The one pilot takes6.303s across compilation, restoration and
comparison; this is not compiler-only timing. CPU0/35%,384/512MiB; peak174,260,224B
and zero memory-limit events. No provider, native build, relink, game or full
replay runs. Private `mac-shape-flow-20261018` and
`mac-shape-api-identifiers-20261018` retain the bound reviews and closed result.
All25 closed raw members, including both temporary objects and the header
proposal, are archived and member-size/SHA-256 verified before deletion.
Listed net allocated release is520,192 bytes after archive/cleanup journals;
current products, caches and the useful shared foreign export/data remain.

## Reused paddle bodies and input precision control

The corrected export also supplies complete `doPaddle` and `drawPaddle` bodies:
936 bytes, 234 instructions, nine calls and13 branches, with every word decoded.
Independent review connects these to the Windows position update203B/20 bindings
(already whole exact) and the original draw677B/185 instructions/10 calls/12
branches. Retained raw instruction records reconstruct the complete pinned PE
span; no separately located original REA response or new decoder is claimed.
Current Windows draw remains677 bytes/68 differences with52 actual bindings.
No new provider query, import or runtime context assignment is needed.

| Flow | Shared operation | Material port difference |
| --- | --- | --- |
| Position | Mouse-x, y450, signed half-width clamps at21/618, sprite68 | Windows additionally conditionally warps the cursor and updates mouse-x |
| Animation | Select the old frame before advancing/wrapping0..3 | Mac stores an absolute clock+64 deadline; Windows uses `elapsed` and an unadjusted last sample |
| Attached overlay | Raw deadline/width refresh, random4, second clock+33, remembered width | Mac dirty-right subtracts twice the margin; original Windows explicitly uses width+x |
| Drawing | Selected sprite, margin and rectangle producers | Mac uses Image/raw buffer/pitch; Windows uses COM `BltFast`, source RECT and queued dirty RECT |

The actual `BlitTransClipped` call has six register arguments including `this`:
Image, pixels, pitch, rectangle reference, x-margin and y/source-top. Its mangled
name encodes five explicit parameters, while the printed pseudocode omits the
last register argument. The final named boundary is `fastdrwBlit`. These caller
facts do not establish unread Image behavior or after-call pixel equivalence.
Windows `DxBallRect` already aliases SDK `RECT`; this is no new type-name model.

Both Mac width conversions execute actual `Fsubs` words at10008564/100085A0,
before double multiplication and integer conversion. The pinned PowerPC Sleigh
rule explicitly rounds the subtraction to four-byte precision and extends it.
Conditional evaluation with descriptor TOC10064D70 finds double0.075/0.03 and
the integer-conversion bias; selected r2 contexts stay unset. This supports one
foreign input-precision hypothesis, without proving an explicit cast or original
Windows source spelling. Original Windows uses `FILD`/`FMUL`/`_ftol` without an
explicit single-precision store at these sites.

The fixed private proposal inserts `(float)` inside the existing `(long double)`
cast at exactly two margin expressions. It preserves the outer product, double
literals, integer result and every other token. Direct float-only replacement
was withdrawn before proposal/compile: it changes product precision, including
the existing width240 case. Input conversion is exact for integer widths with
absolute value at most2^24; no arbitrary-int or floating-environment equivalence
is claimed. Foreign compiler lowering remains an alternative explanation.

One runtime compile uses all26 project inputs. The initial comparator correctly
stops at a generated literal-ID collision: its sixth unit, `initialize-game`,
finds `$SG29805` referring to different data from the fixed baseline ID. Keep
that failure; the frozen runner never passed. A separate passive review of the
retained object fixes an unambiguous symbol bijection from actual section,
value, type, storage and complete container before comparing all16 functions,
352 actual bindings,33 complete COFF/original-PE literals and applicable local
targets. There is no second compilation or weakened original guard.

Every raw and resolved function identity is unchanged. All13 prior exacts retain
2,895 bytes; elapsed81/3, reset426/20 and paddle677/68 remain. Whole-object review
checks23 identical section headers/payloads and389 logical relocation targets.
The objects are not byte-identical:57 generated names change, `.file` auxiliary
records shrink8→5, raw symbol records261→258 and relocation indices shift by
three; debug path, timestamp and string-table differences are retained.
Reject the whole precision model without cast, scope, name or flag variants.

All750 protected hashes/modes/nsmtimes verify before documentation edits,
including the current runtime object. The compiler lock, before/after toolchain
verification and `finally` restoration include the failed comparison outcome.
CPU0/35%, memory high384MiB/max512MiB constrain the compile/restoration scope;
its peak is171,892,736 bytes, with zero memory-limit events. Later passive review
uses a separate CPU0/10%,128/256MiB scope, without a measured peak claim.
No native build, game, relink or full replay runs; source, delivery and250 authored
exacts/20 candidates remain. Private `mac-paddle-flow-20261018` and
`mac-paddle-input-precision-20261018` retain the bound reviews and result.
All18 closed raw members, including both objects and the source proposal, are
archived and member-size/SHA-256 verified before deletion. Listed net allocated
release is323,584 bytes after archive/cleanup journals. Current products, caches,
the corrected foreign export and static data remain available.

## Reused line body and public-name control

The corrected17-span export already contains the complete named Mac `line`:
file90544..90720,176 bytes/44 instructions, SHA-256
`ffb39e26b3b5db2137d0fbbe7f13c19226c08810a5af6c0136f06fa26e00e383`.
The previous next-question note did not establish that this body was missing.
Review locates it before any new query is prepared or run. All words decode,
including the reachable NOP; nine local branches, two conditional returns and
two plain returns are accounted for. There are no calls or r2/global references.

The original Windows line dossier
`ev_25f8571b40b1ee8c589f398fa1211552c03d241352d0737d904789e2664b8af2`
is reread with the complete445B PE span and current object. Its121 instruction
boundaries,140-byte frame,16 branches and three COM calls remain accounted for.
The same distinctive traversal uses signed extent normalization, signed pitch,
inclusive endpoints, byte color, and asymmetric error tests: error>dx in the
x-major arm but error>0 in the y-major arm. The preliminary suggestion that the
latter was a port difference is corrected before any source proposal.

Mac takes pixels/pitch/four coordinates/color, seven explicit parameters.
Windows takes a surface/four coordinates/color and retains GetSurfaceDesc,
Lock retries and Unlock. The raw-plane signature and optimized CTR loops do not
recover Windows local declarations or replace these operations. This is bounded
ordinary-plane correspondence, not arbitrary-overflow or invalid-pointer
equivalence. No new operation, type or lifetime correction follows.

All nine Windows differences remain the three known commuted signed comparison
groups: major-axis selection and two loop bounds. Every other byte and all frame
homes match. The closed rank/declaration control cannot be reopened from PPC
register choices. A bounded review of the selected prior controls finds no
identical public `line` name control; that is not a global history absence proof.
The actual name and complete distinctive core support one separate inferred
identifier, without proving original Windows spelling.

The fixed private proposal inserts only `#define dxball_draw_line line` in the
existing full UI header. Windows signature, operations, locals, types, scopes
and flags stay intact. Source spelling survives the macro; the old exported-name
or dlsym ABI does not. No wrapper or consumer compatibility is claimed.
The prospective closure is six owners/67 functions. One drawing-owner compile
first compares both whole functions, with zero actual bindings, literals or
attached metadata and applicable local-definition guards.

Both code identities are unchanged: line445/9 and fill85 exact. Reject the whole
name model without alternatives or adoption. The other five owners/65 functions
remain uncompiled and unknown for this proposal. Full COFF review checks all
three section headers/file-backed payloads and15 raw symbol records. The objects
change1020→1002B: one defined function name becomes `_line`, its old18-byte
string-table entry disappears, and timestamp bytes change. The `.file` path and
auxiliary bytes are identical; no wrapper or other difference appears.

All751 protected hashes/modes/nsmtimes restore before documentation edits,
explicitly including the current drawing object. Serial compiler lock,
before/after toolchain verification and owned-process cleanup remain enforced.
The5.489s pilot includes compilation, restoration and comparison; it is not
compiler-only timing. CPU0/35%,384/512MiB; peak170,553,344B and zero memory-limit
events. No provider, native build, relink, game or full replay runs. Source,
delivery and250 authored exacts/20 candidates remain. Private `mac-line-flow-20261018`
and `mac-line-api-identifier-20261018` retain the complete reviews and result.
All16 listed closed raw members, including both objects and the header proposal,
are archived and member-size/SHA-256 verified before deletion, releasing143,360
allocated bytes net of archive/cleanup journals. Current products, caches and
the useful shared foreign export/data remain.

## Reused score producers and parameter-kind control

The corrected 17-body export already contains both remaining score producers. Reuse
it rather than opening another provider session. Complete reader/inserter spans
are 740/860 bytes: 400 words, 399 decoded instructions, 39 calls and 43 local branch
instructions. The sole undecoded word at 0x1000F11C is 60000000, skipped by the
branch at 0x1000F118 and the loop back to 0x1000F120; keep it explicitly accounted
for without counting it as decoded. Every word is bound to the original PEF.
Original Windows read/insert/draw bodies are 94/446/404 bytes and 30/134/135
instructions, with 54 actual bindings and five complete literal references.
Current reader and inserter are exact; drawing remains 403 bytes/330 differences.
Its only normalized discrepancy remains the known selected-global/index
load/CMP pair; the 36-byte frame and all local homes already agree.

The Mac producer/consumer connection confirms 15 rows of 44 bytes, 40-byte names
and 4-byte score words. Its 732-byte grouped node also holds 8 bytes of links
and a 64-byte group name. Clear/free-before-read, per-name tail clearing,
group selection/creation and framed serialization are Mac behavior. Windows
keeps one fixed 660-byte array, reads it before insertion, shifts names with
strcpy and writes its raw bytes after access/open checks. Do not transplant
Mac list ownership, clearing, headers, markers or endian helpers. Conditional
static TOC observations are not applied r2 contexts or runtime proof.

Actual `.updateHighScore__FPcUl` metadata and the incoming score's unsigned
comparisons/stores qualify one foreign-derived Windows parameter-kind inference,
not unique Windows source spelling. They do not establish the record field's
nominal kind: the positively named writer helper encodes an int input. A
conceptual field extension was declined before any proposal or compile.
The one fixed proposal adds a role alias in existing gameover.h, using
unsigned long on Win32 and existing 32-bit DxBallUInt on the host, and changes
only the existing insertion definition/prototype parameter. Record score fields,
44-byte layout, formatting cast, operations, names, qualifiers and scopes stay.
No new header, assertion typedef or output-driven alternative is introduced.

The actual header closure is runtime/platform/gameover: three serial compiles,
all 35 complete functions, 1011 actual bindings, 87 full literal references and
zero configured metadata. A frozen preflight accounts for 81 unique physical
literal roles, 849 fixed nonliteral references and 75 same-section definitions.
Generated numeric names are not literal identities: require a unique actual
section/value/type/storage/aux anchor, complete unchanged initialized container,
full payload/original PE payload and role multiplicity. Fixed symbols retain
their actual definitions and target roles. Same-section targets derive from
the new actual definition offsets, never forced old label addresses. All 35
binding tables and provenance hashes freeze before any private code comparison;
production full-span and applicable exact-local-target guards remain active.

All 31 prior exacts/11,098 code bytes survive. All 34 other raw and resolved
code identities stay unchanged, including elapsed 81/3, reset 426/20 and
high-score drawing 403/330. Paddle drawing regresses from 677/68 to 678/210
against 677 original bytes; there is no gain. Complete baseline/private paddle
correspondence retains 185 instructions and the 68-byte frame. Only the dirty rectangle
right-edge producer changes from a 5-byte global-width load plus 3-byte local-X add to a
3-byte local-X load plus 6-byte global-width add; two branch encodings move
with the extra byte. No new game operation is recovered. Reject the entire
fixed model, with no field, spelling, qualifier, owner or subset variant and no adoption.
All 754 protected byte/mode/nsmtime identities restore, including all three
canonical objects; toolchain verification passes before and after staging.
The 9.492s figure covers the complete compile/restore/compare pipeline.
CPU 0/35%, 384/512 MiB and peak 179,445,760 B hold with zero memory-limit events.
No new provider, native build, oracle, game, relink or full replay runs.
Source, delivery and 250 authored exact/20 candidates remain unchanged.

The frozen family review is retained at
`.analysis/mac-score-producers-20261018/independent-family-review.json`, SHA-256
`7dfc6215e1703de0716d5797832207a7f829c8607041fa9274e1463af47026f3`.
Private plan/result reviews, binding freeze, summary and restoration receipts
remain under `.analysis/mac-score-parameter-kind-20261018/`; result review SHA-256
`063c08f328a5a8d5ac073269c133263494e19feb5226e36fd2dd2c6f5540fc63`.
All 30 listed closed raw members, including six objects and both proposals,
are archived and individually size/SHA verified before exact-list deletion.
`closed-model.tar.gz` is 216,035 bytes, SHA-256
`e2c1f37707a7245019154194a344f2288dd5c2d6ff204bc9a45361ef3725121b`.
The net allocated file space released, including all cleanup journals, is
2,310,144 bytes. Current products, useful caches and shared Mac evidence stay.

A separate bounded review finds no qualified new missing-operation query in
this retained Mac set. Both clock helpers are already in the corrected export.
Unread Image::BlitClipped would describe the foreign rectangle mutation, while
the Windows crop chains and COM boundary are already fully accounted for.
Historical rotation zero-store gaps are superseded by the complete current
frame-role correspondence. Re-examine original Windows producer/declaration
evidence before qualifying another model; no blind spelling/context variants,
repeated closed controls or automatic foreign queries follow this result.

## Bank filename qualification and path boundary

The next bounded question closes an actual gap in the retained bank family:
`.loadshapes__FiPc` passes its input through `.cp_path__FPc`, whose complete body
was not among the17 corrected exports. It does not call `Bankfile::Open`.
One REA6.5.0 process capture queries the saved pinned Ghidra12.1.4 project without
reimport, global analysis or an r2 assignment. The new span is416 bytes at
`10019A60..10019BFF`,104 decoded instructions,18 branches, six calls to four
unnamed targets, and one return. Raw/loaded bytes agree with the original PEF.

Input is saved in r28. A pointer is loaded into r31 through `[r2-0x7234]`;
all four direct nonstack byte-store sites use r31 or its derived cursor.
The no-separator path returns the original input; the conversion path returns
r31. The complete caller forwards that return to an open-like target, but later
copies the original r28 filename into bank storage. These observations fit a
port path-output buffer. With r2 unset, its identity/disjointness are unknown;
the four callees are not fully inspected. Do not claim no indirect input write,
a specific buffer capacity, recovered CFM TOC, or proven CRT identities.
The decompiler omits the first call's actual input argument; instructions govern.

The positive Pc metadata remains a foreign unqualified-pointer declaration,
not a recovered Windows cv qualifier or a mutable-input requirement. Together
with the complete bank connection it supports one bounded read-only API inference.
The fixed private proposal changes only the bank definition/prototype and genuine
RuntimeOps/interposer callback boundary to char*. Seven explicit C++ literal
casts and one const inspector cast preserve the maintained no-write behavior;
no fake buffer, function-pointer cast, unrelated filename API or operation changes.
Earlier bank-name and three-UI-qualifier controls did not test this model.

One resource compile is the frozen early rejection gate for the prospective
28-owner/272-function closure. All18 complete raw/resolved code identities remain
unchanged, including bank1475/64, draw107/94, blt199/173, release269/245 and
PCX979/851. Thirteen prior exacts/3,050 bytes survive. All262 actual bindings and
multiplicities, six physical literal anchors/whole containers and original-PE
payloads verify; there are no attached metadata or same-section references.
All18 mapping tables freeze before private comparisons. The complete12,332-byte
objects differ only in COFF timestamp bytes4–5; all other bytes agree.
Reject the entire model without qualification variants or adoption. The other
27 owners/254 functions and native/fixture consumers stay uncompiled/unknown.
Canonical source keeps the const filename API.

All754 protected hashes/modes/nsmtimes restore under the serial lock, with
Toolchain verification before/after including failure cleanup. The one compile/
restore/comparison pipeline takes4.795s and peaks193,404,928 bytes with zero
memory-limit events. The saved-project capture peaks403,165,184 bytes with767
soft-high events and zero max/OOM events. Both use CPU0/35%,384/512MiB; the
capture uses Java128MiB and Node192MiB. There is no further provider query,
native build, relink, game or full replay after rejection.

Private `mac-path-contract-20261018` retains the complete selected export,
question, resource receipts and independent contract review. Process Evidence
`ev_acd98536850530d1f826c778dcdfaea0a33588ea746708b4111168ceaf0ce64c`
is retained in the verified archive; it is not native-provider admission or a
snapshot. `bank-filename-qualifier-20261018` retains eligibility/plan/result
reviews, summary, restoration and cleanup receipts. Its33-member archive is
114,955 bytes, SHA-256
`6f7aae5e8e1dc37d9f9e9f99f6615b05ae3876f7099e26977a99e8b1a6590d42`.
Every member size/hash verifies before exact-list deletion of both temporary
objects, seven proposals and closed capture/runner carriers. Net allocated
release is729,088 bytes including the archive/manifest/cleanup receipt.
Current tested products, useful caches, static Mac evidence and saved project
remain; source/delivery and250 authored exact/20 candidates are unchanged.
The user then stops exploration and requests handoff preparation.
