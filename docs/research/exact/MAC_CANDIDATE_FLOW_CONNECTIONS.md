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
