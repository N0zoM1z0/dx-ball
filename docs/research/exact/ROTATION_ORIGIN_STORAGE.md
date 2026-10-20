# Rotation origin operands and initial storage

The later [closed follow-up](CLOSED_STORAGE_DIAGNOSTICS.md#rotation-and-value-copy-follow-up)
tests nested origin conversions, axis records, a sampled source-plane record and
floating consistency. None is adopted. The later
[visible-pixel scope](ROTATION_VISIBLE_PIXEL_PHASE.md) changes only four local
declarations and brings the current renderer to 1466/1572 with 1466 differences.

The renderer at `0x4026A0` now restores its two previously omitted zero writes
and the four-byte operand used by its first three origin divisions. One VC4
compilation preserves all four exact rotation companions, totaling 749 bytes.

| Complete renderer comparison | Before | Current | Original |
| --- | ---: | ---: | ---: |
| Code bytes | 1,447 | 1,451 | 1,572 |
| Instructions | 366 | 365 | 365 |
| Frame bytes | 416 | 424 | 424 |
| Strict differing byte positions | 1,491 | 1,475 | — |

The renderer remains a candidate. The accepted total stays **207 exact functions
and 44,832 code bytes**.

The original writes zero to independent DWORD words at EBP-344 and EBP-4,
immediately after sampling sprite dimensions. Neither word is read again in
the complete listing. The shared source represents these actual words as two
unclassified unsigned32 locals. Their semantic purpose and original signedness
are unknown. Their current homes, EBP-16 and EBP-36, still differ from the target.

The first three divisions read float `2.0` at `0x420038`; the last reads double
`2.046` at `0x420040`. A file-local float constant preserves the four-byte loads
and the three calls to `__adj_fdiv_m32` at `0x416DCC`. The previous literal in an
extended expression promoted the operand to double and emitted m64 calls.
The fourth divisor and its m64 fallback stay intact. Every constant binding
checks the full operand bytes against both the object and original image.

The retained renderer dossier is
`ev_1dfa14e3428cac399a6bc2876da74d5bbc4a5edc8a8e03a6af79783e189daf26`.
The complete constant carrier is
`ev_3981d4fe3871c6d5f4976aaec23007d066c24f80aedca23dd51270d63c19de71`.
These closed REA records cover the original writes, division operands and calls.
Remaining differences include stack homes, address-generation schedules and
instruction widths; equal instruction totals do not establish a complete match.

Linux and MinGW builds pass. VC4 links the same compiled owner with 36 verified
unchanged objects. The existing 351 renderer and 344 wrapper comparisons pass,
including complete guarded pixel buffers and seven live-handle/retry scenarios.
They exercise normal division; the FDIV fallback restoration has static
instruction evidence. All 207 accepted function extents and compiler closures
verify. Historical semantic scopes retain their case counts while their input
inventories refresh for the source change.

Inputs, complete comparisons, instruction inventories, products and the focused
Oracle are retained in `.analysis/rotation-origin-storage-20261012/`. No game
campaign ran. Verified gzip carriers retain disposable diagnostic object bytes
after cleanup.

## Current C++ nested-origin control, October18

A bounded review of21 earlier rotation phases and33 retained renderer sources
finds just one nested first-term model, compiled as C with older declarations.
The current C++ owner had not tested that fixed model. Original first-term
`FSTP qword` stores at EBP−368/−400 cross the following trig calls; current named
terms use−324/−336. This supports one current-context control, without proving
the original spelling or reopening other old models.

Remove only the two named first-term declarations and substitute the same prior
nested expressions, retaining explicit double rounding, full headers, flags,
integer pixel addressing and all five current functions. One compile compares
five complete units/115 bindings/25 literal references. There is no gain:
offset loses its259-byte exact result, becoming261/223. Y-offset191, width259
and height191 retain their exact identities. Renderer stays1458/1466 with a
different full digest. Reject the whole model; retaining the old offset object
selectively would conceal the shared-input loss.

Independent review checks78 origin instructions: the proposed temporary homes
match−368/−400, actual64-bit rounding and trig order survive, and normal/bug
fallback division paths retain their operands. This bounded check does not
claim complete renderer equivalence. Recovering these two homes alone does not
recover its source or offset's compiler context.

Sealed `.analysis/rotation-current-cpp-origin-20261018/` retains complete inputs,
comparisons and independent reviews. Ten raw copies/products, including two
objects, are archived and member-hash verified before deletion, releasing44 KiB
net after archive/journal costs. Peak159,252,480 bytes; no high/max/OOM events.
Canonical source, products, delivery and counts stay unchanged. No provider,
native build, runtime case, relink, game or full replay follows; no further
cast, parenthesis, flags or selective-object variants are queued.


## Complete retained-model tradeoff, October18

A later passive review fills the preceding78-instruction boundary using the
same sealed current and nested objects. No source variant or compilation is
introduced. All five complete comparisons,115 bindings and25 full literal
references reverify; the prior seal/archive and current eight project inputs agree.

The entire365-instruction renderer now has a nonoverlapping424-byte map across
36 value roles. Current and nested models have identical operations and
operands after translating each role's concrete frame address. Against the
original,349 instructions agree directly under that translation; the other16
belong to two signed loop guards, one unsigned rollover guard, two commuted
low32 products and one finite row-Y addition. Their exact operands, opposite
Jcc pairs and successors are checked. All22 call sites and26 branch targets
agree, and no branch enters a grouped dependency sequence partway through.

This current context differs from the old C-owner correspondence: the eight
bank-address groups already have the original operation/operand form after
frame translation. Reuse the earlier proof for its historical objects rather
than describing those64 instructions as current unexplained producers.
Thirty concrete CFG walks show that differing scratch-register values are
replaced or reach ordinary ABI boundaries before any read. Normal finite FP,
ordinary stable mapped memory and standard ABI scratch rules remain the scope;
unrestricted flags, traps, NaN payloads, frame aliasing and pointer retention
are not established.

| Concrete instruction correspondence | Maintained | Retained nested model |
| --- | ---: | ---: |
| Renderer, of365 |241 |260 |
| Horizontal offset, of77 |77 |61 |
| Other three helpers combined |203 |203 |
| Five-function total, of645 |521 |524 |
| Original physical renderer frame-role bytes, of424 |32 |88 |

The metric compares complete decoded operations and concrete operands, mapping
branch destinations by instruction ordinal. It is neither a raw exact count nor
a source-completion percentage. The nested renderer restores19 instructions
and56 physical frame-role bytes without losing a maintained matching renderer
instruction. Its two first-term homes and five integer-conversion homes move
to the original addresses. However, two complete eight-instruction bank
producers in horizontal offset lose their original forms. Exact coefficient
maps modulo2^32 still give `425980 + bank*1048 + slot*4` in each case, but the
259-byte exact helper becomes261/223. The other three helpers remain exact.

This is a real family tradeoff. Three more aggregate instruction matches do
not restore a complete function or dominate the maintained source. Keep the
canonical model and all394 exact claims; no selective old helper object is
adopted. The role map does not prove that original first-term stores were
unnamed compiler temporaries: rotation's original records and complete
named/temporary allocation, release and reuse order remain unknown. In
particular, deriving a464-byte impossibility from a named slot at−400 would
require unproved allocation-order and no-reuse assumptions.

Private `.analysis/rotation-nested-origin-complete-20261018/` retains the full
role/group/CFG proof and independent review. Its two tiny extracted object
copies are rechecked against the already sealed, member-verified original
archive before removal; no second archive of identical products is needed.
The verified cleanup releases12 KiB net after its journal; all19 protected
input/product identities remain intact.
Current source, objects, delivery, caches and counts remain unchanged. There
is no compiler, provider, solver, emulator, runtime case, relink, game or full
replay invocation.

## Observed scope output and fixed root-local model, October18

The preceding proof leaves a concrete producer question: how does the current
C++ frontend order its actual scope tables? One unchanged rotation compilation
observes C1XX at `417EF3`, immediately before `MOV EDI,[ESI+30]`. All eight list
snapshots pair with a checked single step of those exact three bytes; the
destination, owner, stack and other registers/ordinary flags are verified.
All three compiler processes exit normally. Only the known `4AB7D0` scope-table
vtable is decoded; eight other objects remain opaque. Eighteen null-head scope
tables are legitimate empty tables. All32 observed symbol occurrences verify
the actual stored hash word, bucket and linked-chain order.

The renderer is identified by its actual `source_column`, first-term and
descriptor names, rather than event order or reused owner addresses. Its
root table contains23 symbols/340 frame bytes; a later visible-pixel table
contains five symbols/20 bytes. Their actual bucket traversal orders agree
with the two maintained physical home sequences. Observed known parents
precede children in these lists; list construction, general parent-first
allocation and temporary release/reuse are not recovered. The other seven
snapshots remain unassigned to original entry points.

The five original pixel homes interleave pre-API height/zero roles within the
upper344 bytes. Together with the new actual table observation, this supports
one finite declaration hypothesis: move all five pixel locals to the function
root, preserving every expression, type, name, header, flag and other declaration.
The older four-root-local model retained the destination pointer in the branch.
The new model leaves both first-term declarations and all rounding untouched;
it does not combine the rejected nested-origin control.

One compilation checks all five complete units/115 bindings/25 full literal
references. The four exact companions retain all900 bytes and their complete
identities. Renderer changes1458/1466 to1443/1470, but code shrinkage and raw
positional differences do not decide adoption. Its365 instructions retain
identical operations and role operands under the complete424-byte/36-role map.
Concrete original instruction correspondences fall241→239: the two row-X-step
accesses lose their matching−24 home, moving to−32; none are restored. Matching
frame-role bytes fall32→24, and none of the five pixel homes match the original.
Reject this fixed model and retain the canonical source. This closes one
observed producer hypothesis, not all possible original scopes or declarations.

Sealed `.analysis/rotation-scope-output-list-20261018/` retains the actual trace,
guards and independent review. Its complete five-function output is unchanged;
11 copied inputs/products are archived and member-hash verified before deletion,
releasing192 KiB net. The fixed-model evidence and independent comparison are
retained in `.analysis/rotation-visible-root-20261018/`. Observation/model peaks
are288,722,944/164,306,944 bytes, with one CPU at35% and no memory-limit events.
The model's ten copied inputs/products, including two objects, are likewise
archived and member-hash verified before deletion, releasing44 KiB net.
No provider, native build, game, semantic replay, relink or full replay runs.
All394 exact claims and the tested restored-CRT delivery remain unchanged.

## Current frame encoding and manager path, October20

Independent current-object review covers all365 instructions and424 frame bytes.
The entire original1572/current1458-byte extent gap follows48 displacement
encodings:43 original-only long displacements minus five current-only long
displacements, each costing three bytes. Among124 differing decoded physical
instructions,109 differ in frame homes and15 in the six equivalent operand
groups. All22 calls,26 branch destinations,115 bindings and25 full literal
references verify; three current exact companions retain709 code bytes.
Authority: `.analysis/rotation-frame-source-question-20261020/findings.json`.

The earlier trace already observes both consumed first-term doubles as named
kind1 records, allocated at401556 to−324/−336. All48 owner allocation requests
and36 renderer slots are already paired. Repeating initial allocation is not a
new discriminator. A narrowly reviewed observation instead installs the exact
manager-entry-near MOV at41EE59 and extent-gate JLE at41EEA1, with original
instruction replay, one-thread/job ownership, bounded hits and deadlines.

One unchanged current rotation compilation records both installed hooks but no
hit at either. All three compiler processes, observer and REA capture exit0.
Thus this manager is not entered in the current complete closure; the earlier
zero late-write result is not an observed nonpositive-extent early return.
No original storage kind, lexical lifetime or general absence of reuse follows.
This closes this current manager-path question, without another source variant.

All five complete bodies,115 actual bindings,25 full literal references, seven
complete COFF section payloads and non-FILE symbols/aux records remain fixed.
All8 frozen/current inputs and12 protected files verify. The one-CPU35%,384/512MiB
scope takes4.994s and peaks at158,334,976 bytes, with zero memory-limit events.
REA process Evidence:
`ev_bba3ee1c69a3566c7565f01f7b4d102fdf5a24702aaf20d029592f1159402434`.
Private authority: `.analysis/rotation-frame-manager-20261020/`.
No source, compiler flag, exact claim, canonical object or delivery changes.
Independent plan/result reviews recheck the raw installation/exit records and
all complete comparisons. Only three COFF timestamp bytes differ between the
two whole objects. After member-size/SHA verification,26 explicit copied inputs,
helper/bytecode files, utility and two objects are removed, releasing303,104
allocated bytes net before the cleanup journal. All24 protected current
identities survive; unique traces/reviews and the verified archive remain.

## Fixed geometry ownership control, October20

A bounded21-phase/34-source audit finds no earlier exact four-helper-only
split. The four scalar bounds/projection queries form one genuine read-only
cohort: sprite dimensions, trig and abs, with no descriptors, pixel writes or
COM. One fixed private model moves precisely those four bodies and their sole
stdlib dependency into a geometry owner. The renderer retains origin_divisor;
all five executable bodies, types, names, scopes, seven shared headers and
compiler flags remain unchanged. This tests inferred responsibility ownership,
not an independently recovered original translation-unit boundary.

Two serial compiles compare all five complete functions/115 actual bindings/
25 full literal references. Every resolved code identity stays unchanged:
three exact companions retain709 bytes, Y-offset stays193/159 and renderer
1458/1466. No gain or loss; reject the entire model without adoption or variants.
The whole original40-byte readonly carrier partitions into renderer32 and
geometry8 bytes. Actual symbol offsets, every complete eight-byte cell, all
declared literal bytes and the float's four alignment bytes are checked, not
just a requested literal prefix. Complete same-function target identity and
the comparator's exact local-target guard remain enforced.

REA process Evidence:
`ev_3858de6fd99342939ace1855bad220c0d0dcd1bc61c4d5c1f3b9136d7bf9f08a`.
Independent plan/result reviews and whole-byte comparisons are retained in
`.analysis/rotation-geometry-owner-20261020/`. The scope peaks at156,008,448 bytes,
with zero memory-limit events. After member-size/SHA verification,25 copied
inputs/helpers/logs/objects are removed, releasing151,552 allocated bytes net
before the cleanup journal; all23 protected identities survive. No native/game
build, relink, runtime case, full replay, maintained source or claim changes.
