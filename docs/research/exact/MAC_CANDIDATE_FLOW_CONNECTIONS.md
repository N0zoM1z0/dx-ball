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
