# DX-Ball reconstruction handoff

Updated October 20, 2026. The reconstruction is unfinished. Recover the English
DX-Ball v1.07 functions as exactly as possible, as readable shared C/C++;
then verify the original VC4 build and playability; resume ports after that.
The user permits the **19 explicit original CRT members** in the restored-CRT
delivery. Removing them is not a delivery gate. Prioritize authored functions.

Repository: `/home/pentester/coding/codex_ida/dx-ball-reconstruction/dx-ball`.
The environment may start one directory above it. Read [AGENTS.md](../../AGENTS.md),
[WORKFLOW.md](WORKFLOW.md) and the selected owner note before changing source.
Keep code, tracked documentation and commits English. Keep the README focused on
the reconstruction approach and REA, with its two centered 900px images.

This file describes current decisions and open work. The detailed
[handoff at c99ab9e](https://github.com/N0zoM1z0/dx-ball/blob/c99ab9e62fcc1625a0c0754a3ee0abb67dc10623/docs/agent/HANDOFF.md)
retains the preceding adoption and cleanup chronology. Owner notes and private
receipts remain authoritative within their stated scopes. Historical totals
are not current totals.

The user reiterated on October20: finish function/source recovery before
complete game verification. The23 authored nonexact candidates remain active;
do not infer readiness from a bounded audit finding no omitted operation.
The current build/play checks ran prematurely. Record their actual results,
then resume source work. Whole-EXE byte identity is not required. Use necessary
focused checks; no broader game verification or campaign is pending.

## Current authorities

| Inventory | Current value |
| --- | ---: |
| Provisional independent entries | 553 |
| Retired parent-owned compiler-fragment rows, counted separately | 24 |
| Source-present entries | 475 |
| Accepted complete exact functions | 392 |
| Exact code / attached metadata bytes | 83,837 / 244 |
| Complete nonexact comparisons | 83: 23 authored / 60 runtime / 0 generated |
| Scoped semantic ledger rows | 249 |
| Entries without source | 78: 77 runtime / 1 generated |
| Inventory origins | 270 authored / 261 runtime / 21 generated / 1 unknown |

All 270 classified authored entries have source and complete current comparisons:
247 exact and 23 candidates across 30 compiler closures. The source-present
16-byte no-op at `0x40CC20` remains origin/prototype-unknown. Neither the final
authored denominator nor source optimality has been established. These inventories
are separate claims, not interchangeable completion percentages.

| Authority | Purpose |
| --- | --- |
| `config/functions.csv`, `function-origins.csv` | Provisional entries, reconciled extents and origins |
| `config/compiler-fragments.csv` | Retired aliases owned by complete C++ parents; not every internal block |
| `config/implemented.csv`, `matches.csv`, `semantic-acceptance.csv` | Source, exact and scoped semantic claims |
| `config/source-owners.toml`, `match-units.toml` | Source ownership; full compiler recipes, extents and bindings |
| `build/reports/exact-replay.json` | Current 392 accepted comparisons and producers |
| `.analysis/exact-candidate-audit-20261012/comparison.json` | Current 83 complete candidates; directory date is historical |
| [Remaining-functions table](../research/exact/REMAINING_EXACT_FUNCTIONS.md) | All candidate results and owner-note links |
| `.analysis/text-width-accumulator-20261020/authored-coverage.json` | Current authored source/comparison/closure coverage |

Original `original/DXBALL.EXE`: English v1.07, 158,208 bytes, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
The pinned compiler is VC4 10.00.5270 and linker 3.00.5270; original CRT provenance
uses `.tools/msvc400/lib/libc.lib`. The compiler identity is
`f097e736bb04d38391c8b524945d58809ec4c42e97c056eca6f40bba2de910c3`.
Original compiler settings cannot be inferred solely from this candidate toolchain.

Keep `original/`, `.tools/`, `build/`, `.analysis/` and `ghidra-project/` private.
A source-only clone does not include the assets, tools, products or raw evidence.

## Current source and delivery

Current source includes the [unsigned text-width accumulator](../research/exact/TEXT_WIDTH_ACCUMULATOR.md).
The existing width uses unsigned32 storage and compound additions, preserving
original modulo32 sums and signed glyph half-width division; conversion to the
unchanged signed32 ABI occurs at return. One complete seven-function/38-binding
compile improves measurement282/26→279/3, preserving all six exact companion
raw/resolved identities. The216 unchanged existing measurement cases and four
retained finite boundary controls pass. Only native ui.c rebuilds;38 other
native objects stay fixed. Current native SHA is
`a25f31c84a17af6c748e02781dc73bfa0241072a7a817bf82a40502e28681f80`.
All270 authored receipts verify across30 closures. Counts remain392 exacts,
247 authored exact/23 candidates. Private authority is
`.analysis/text-width-accumulator-20261020/`. No game rebuild/run or full replay follows;
the tested bff527e game/ZIP below predate this change. Source recovery continues.

Current source includes [all six Blt destination-edge sums](../research/exact/BLT_COORDINATE_WRAP.md).
One18-function/262-binding/six-literal compile promotes plain Blt195exact,
preserves keyed195exact,and explicitly demotes stretch139exact→141/94 and
unchanged capture852exact→864/726. Full51/248-instruction correspondences account
for both losses; PCX's nine-byte comparison ripple keeps979/851. All six actual
bank-prefix/failing-Blt witnesses and120 unchanged selected calls pass. That checkpoint's
native SHA is `0a632e94edf77f0278257d1c0b7f13512ec842e8b4f6cc72e5f669016dd957cc`.
All270 authored receipts verify across30 closures. Totals are392 overall exacts,
247 authored exacts/23 candidates; no old-object mix hides the net one-exact loss.
Private authority is `.analysis/blt-coordinate-wrap-20261019/`.

The earlier recoveries below retain their own comparison epochs; current totals
and products are given above.

Current source includes [last-brick destination Y arithmetic](../research/exact/LIGHTNING_Y_COORDINATE_WRAP.md):
one expression preserves the original consumed DWORD subtraction before signed
clipping. A finite initialized-sprite witness rejects the old instrumented
source and matches the original after recovery;197 unchanged countdown/crop
cases pass. All20 complete display raw/resolved bodies/421 actual bindings
stay fixed, including16 exact companions. Last-brick stays1061/992. That checkpoint's
native SHA is `e980f545aca7e5019c46a4914caca066bd4d9eab5fa6ad52fe04950f39b080a0`.
Private authority is `.analysis/lightning-y-wrap-20261019/`. All270 current
authored closures verify without a replay; source recovery remains unfinished.

Current source includes [glyph destination coordinates](../research/exact/GLYPH_COORDINATE_WRAP.md):
three expressions preserve four consumed DWORD arithmetic operations. Four
finite actual-font/CreateSurface-failure cases match original rectangles and
returns;769 existing lookups/768 draws pass. All18 complete resource functions/
262 bindings/six literals compare;11 exacts and17 code identities survive.
Glyph stays332/258. Unchanged PCX source has a fully accounted227-instruction
compiler ripple,979/850→979/851; its strict result is not hidden. Glyph-checkpoint native
SHA is `d400ba4da656ba3f9cb688812954e16ff87903109966cecdee1ed9d2e818097b`.
Private authority is `.analysis/glyph-coordinate-wrap-20261019/`.

Current source includes the [ranking coordinate subtraction](../research/exact/RANKING_COORDINATE_WRAP.md):
the original DWORD subtraction is explicit before the signed text coordinate.
All8 gameover code identities/234 bindings/13 literals stay fixed, including
seven exacts; ranking stays403/330. The finite boundary case and17 unchanged
ranking cases pass. The ranking-checkpoint native SHA was
`cd30d703f106cece05e62912d6033519b2c7238f25e26bc456fa3464efe83e2e`.
Private authority is `.analysis/ranking-coordinate-wrap-20261019/`.
The separate text-advance proposal loses draw-text150exact→153/20 and is rejected;
canonical ui.c stays fixed. Its finite final-advance boundary remains documented,
without claiming all exceptional text arithmetic is defined.

Current source includes the [PCX coordinate correction](../research/exact/PCX_COORDINATE_WRAP.md):
four literal/RLE destination increments preserve original DWORD wrap before
signed clipping. All18 complete resource identities/262 bindings/six literals
stay fixed, including11 exacts and PCX979/850. Four finite clipped counterexamples
and99 unchanged existing PCX cases pass. The PCX-checkpoint native SHA was
`78d8e0e6f9f63e8e19a277f3df7dc4e722243eff3fb2e605d30be5127dfb8c6c`.
Private authority is `.analysis/pcx-coordinate-wrap-20261019/`.

Source also retains the [file-field/text-width corrections](../research/exact/AUTHORED_BOUNDARY_CONTRACTS.md):
four fread output lifetimes span later EOF; both measurement branches retain
original modulo32 addition and signed half-width division. Full25-body/300-binding/
six-literal comparisons preserve17 exacts and23 other code identities. Bank
worsens1475/63→1475/68; measurement279/3→282/26. Bounded counterexamples and
10 existing bank/216 measurement cases pass. Counts stay248 authored exact/22
candidates,393 overall exacts. Both current matching objects and native library
include those source changes. The preceding boundary-checkpoint native SHA was
`8ed0f953adda504213452d801130961e1ad6ae0c6572d12e5ad077db33359bb5`.
Private authority is `.analysis/authored-boundaries-20261019/`.

Current local EXE and ZIP now come from source bff527e; both include the
last-brick Y and six Blt corrections. The166,400-byte EXE SHA-256 is
`76be8c25a07f972ff55465c47ea47a067434e84c669bf7f64c3cd96692b21db6`.
A14.894s relink reuses118 verified source/integration objects and19 approved
CRT members. All673 complete linked sections/144,681 bytes,5,904 COFF bindings,
4,488 loader fields and1,099 unchanged named map addresses verify.

The [current build/play record](../research/CURRENT_VC4_BUILD.md) records the
premature existing basic/editor, real-round and natural-loss/ranking/fresh-reload
checks. They pass on this image with541/130/1052 state observations and normal
exits. They add no source/exact/semantic acceptance or recovery-readiness proof.
All49 originals and protected inputs stay fixed; CPU0/35%,384MiB high/512MiB max
limits have zero high/max/OOM events. Do not repeat or broaden these flows.
Private authority is `.analysis/current-vc4-build-20261020/`.

The older12ccdb1 image's20s return-menu timeout remains unresolved; the current
pass does not establish its cause or a fix. Preserve
`.analysis/current-vc4-refresh-20261019/` and retained4d962e image history.
The previous717cc2f passing delivery retains its own historical records.
Current private bundle `build/delivery/dxball-v1.07-vc40-reconstructed.zip` is
475,005 bytes, SHA-256
`b9e81852cb1e6096e0014835103548682396fcec648ea8f319daac0e543017b0`.
Its50 member-verified files contain the current rebuilt EXE,48 unchanged supplied
assets and instructions. Test rankings are excluded. Current EXE/map/manifest,
useful caches and unique evidence remain private.

The [bank byte-count recovery](../research/exact/BANK_BYTE_COUNT_ARITHMETIC.md)
defines the observed low32 allocation/fread product and explicitly demotes two
glyph exacts after changed address producers. The latest
[count-bound recovery](../research/exact/BANK_COUNT_BOUND.md) preserves the live
modulo32 increment and signed guard, improving bank64→63 differences. All18
resource bodies/262 bindings/six full literals compare together;11 exacts and
16 complete code identities survive the count-bound change. The bounded actual
INT_MAX counterexample and ten existing bank cases pass. PCX stays979/850;
find-glyph146/86 and draw-glyph332/258 remain candidates. Current authored totals
stay248 exact/22 complete candidates across30 verified compiler closures.
The focused native receipts are `.analysis/bank-count-bound-20261019/native-build.json`
and `selected-oracle.json`.

The older `build/native/retained-build.json` predates MulDiv integration in four
non-resource inputs; it remains historical and must not be used as a current
whole-build input attestation. No such native claim is added here.

Relevant accepted source contracts:

- [Independent board storage](../research/exact/INDEPENDENT_BOARD_STORAGE.md)
  preserves seven real objects, two mutable unknown slots, the real list word
  at +0xC, natural pointer widths, ordered linker sections and retained memmove.
  The 20,432-byte layout and 368-byte terminal overlap are ABI observations;
  the descriptor is a view, with no enclosing instance or ISO array-bounds claim.
  Adoption promoted17 complete units and demoted eight; do not hide those losses
  with old objects or selective header variants.
- [Score workspace](../research/exact/INTRO_SCORE_PHASE.md) and
  [score strip](../research/exact/SCORE_STRIP_SOURCE.md) capacities follow real
  consumers and independent workspace regions. They do not justify padding in
  unrelated functions.
- [Paddle sampling](../research/exact/PADDLE_WIDTH_SAMPLING_SCOPE.md) preserves
  the sampled width and dirty-right sum; its complete body remains677/68.
- Bank loading preserves callback-visible state, partial failure ownership,
  and the pitch snapshot before Lock. Keep the Windows allocation-mode argument
  and COM behavior; foreign Image/backend records are different.
- Keep the documented GNU C++17/x87/excess-precision options for `balls.cpp`,
  C linkage, real Win32 heap/raster defaults, and stdio-before-onexit ordering.

## Last closed work

October20 [unsigned text-width accumulation](../research/exact/TEXT_WIDTH_ACCUMULATOR.md)
retains the wrapping contract through the unsigned accumulator type and improves
measurement to279/3 without changing exact counts. Six complete companions,
38 bindings,216 existing calls and four retained finite boundaries verify.
All270 authored closures are current. The235 historical semantic input rows
refresh without changing scopes/cases or collapsing duplicate unit names.
No game rebuild, game run or full replay follows this source checkpoint.
Thirty-eight closed files are archived/member-size/SHA verified before removal:
449,321-byte archive,6,111,232 allocated bytes released net before small receipts.
All623 protected SHA/size/mode/mtime identities survive; current products/caches
and unique JSON proofs remain. See the authority's archive/cleanup receipts.

October20 current-source relink and existing play/lifecycle checks pass; the
local bundle is refreshed as described above. These checks were premature under
the user's source-first priority. Source and claim ledgers stay fixed at247
authored exact/23 candidates,392 overall exacts. No complete game verification
or campaign is authorized next; return to concrete source reconstruction.
Nineteen closed copies/helpers are member-size/SHA verified in a1,731,770-byte
archive before removal; net1,654,784 allocated bytes are released and183
protected identities stay fixed. Forty-nine byte-verified isolated runtime
copies release another1,724,416 bytes. Current products/caches and unique
evidence stay. See the current authority's archive/cleanup receipts.

October19 [Blt coordinate recovery](../research/exact/BLT_COORDINATE_WRAP.md)
adopts one frozen six-operation family after complete comparison and independent
source/result review. Six old instrumented cases fail; six restored/canonical
cases and108 existing Blt/twelve capture calls pass. All three compiler ripples
are fully accounted. Plain Blt gains195 exact bytes; stretch/capture lose139/852
exact bytes, giving392 exacts/83,837 code bytes and247 authored exact/23 candidates.
Source recovery takes precedence over the prepared relink, which remains
unexecuted. Current products/caches and the retained failed-play evidence stay.
All66 closed copies/products/helpers are archived and member-size/SHA verified
before cleanup,net8,372,224 allocated bytes released. All926 protected identities
survive; the archive is1,356,538 bytes. No game or full replay is repeated.

October19 [last-brick Y recovery](../research/exact/LIGHTNING_Y_COORDINATE_WRAP.md)
adopts one expression after one complete display compile, an instrumented
before/after counterexample and197 unchanged countdown/crop cases. All20 raw
and resolved bodies/421 actual bindings remain identical, including16 exacts.
One native display compile/link and current finite witness pass. No provider,
replay, game rebuild or game run follows. Counts remain248 authored exact/22
candidates; all270 source/comparison receipts verify. Closed files are archived
and member-hash verified before cleanup:57 files,1,303,455-byte archive and
7,733,248 allocated bytes released net before small receipts. All925 protected
identities survive; current products,caches and failed-play evidence remain.

October19 glyph-coordinate recovery adopts three expressions after one complete
resource compile, four bounded original/native counterexamples and unchanged
769-lookup/768-draw selection. Eleven resource exacts survive and17 code
identities stay fixed. The PCX851 result is adopted with its complete before/
proposal correspondence; no old object is retained to hide the compiler ripple.
See [glyph coordinates](../research/exact/GLYPH_COORDINATE_WRAP.md). All270
authored closures verify without a replay; exact/candidate totals stay fixed.
Forty-seven closed input/product/helper files are archived/member-hash verified
before cleanup, releasing7847936 allocated bytes net before small receipts.
All91 current protected identities survive; current products/caches stay.

October19 [complete raster instruction correspondence](../research/exact/RASTER_OPERATION_CORRESPONDENCE.md)
accounts for all1408 instructions/4845 bytes of the three current raster
candidates. Bijective frame-role maps and20 checked comparison groups explain
every instruction difference;80 CFG register/flag checks leave no later
observation of the exchanged values. The actual30-byte conversion callee and
36 fixed EH-state byte writes verify. Strict517 differing bytes remain; no
source, exact or semantic case acceptance changes. Private authority is
`.analysis/raster-operation-correspondence-20261019/inspection.json`. This is a
bounded source-operation correspondence, not unrestricted machine equivalence,
original spelling, source optimality or actual EH execution. No compile, provider,
target execution or replay follows; all90 protected identities remain fixed.

October19 [full early-SDK source check](../research/exact/EXACT_FIXED_POINT.md#full-sdk-carrier-and-source-corpus-check-october19)
verifies both received Game SDK/DirectX2 packages and retains551 source/text
members with original CRC and retained SHA checks. The1995 triangle was already
obtained earlier; the1996 counterpart differs only in copyright year range.
No new declaration model or compile follows the unchanged source. Four bounded
fingerprints expose no new connected PCX/polygon candidate. Do not repeat the
earlier SDK model; reuse `.analysis/early-sdk-raster-20261019/` for the now-retained
source corpora and explicit search limits. Verified cleanup replaces the two
whole package copies and18 closed files with source/helper archives, releasing
41267200 allocated bytes net before small receipts. All90 protected identities
and all claim totals stay fixed; no provider/runtime/relink/replay runs.

October19 ranking subtraction recovery adopts one expression after a complete
eight-body comparison, finite original/native counterexample and17 existing
ranking cases. All code identities and claim counts remain unchanged. The
separate UI unsigned-advance trial is rejected after its full comparison loses
draw-text's exact body; no alternate source model or216-case replay follows.
See [ranking coordinates](../research/exact/RANKING_COORDINATE_WRAP.md) for the
source/fixture boundaries and private authorities.
Both closed trials archive/member-verify80 files before exact-list removal,
releasing10285056 allocated bytes net before the small receipts. Current tested
products, useful caches, comparisons and unique evidence remain.

October19 PCX destination-coordinate recovery adopts four explicit modulo32
increments while preserving all18 complete resource code identities. One VC4
owner compile and one resource-only native build suffice; four bounded cases
and99 unchanged PCX cases pass. All270 current authored closure receipts verify.
Independent source/result reviews, full receipts and37 verified archived
inputs/products/helpers are retained; cleanup releases7,815,168 allocated bytes
net before small receipts. Source recovery remains unfinished at22 candidates;
no final game rebuild or game run follows this source checkpoint.

October19 authored boundary-contract recovery adopts the two source corrections
above despite worse byte comparison. Two owner compiles and one two-source
native incremental build are sufficient; no full replay, relink or game run.
Independent source/result reviews and focused current native receipts are in
the new private authority. The earlier iteration-scope inference is explicitly
corrected; historical semantic case scopes/counts remain unchanged.
The61 closed inputs/products/helpers are member-hash verified in a1,217,038-byte
archive before removal, releasing9,302,016 allocated bytes net before its small
receipts. Current matching/native products, useful caches and previous tested
EXE/ZIP remain. See `archive-manifest.json` and `cleanup.json` in the authority.

A subsequent [13-pattern Mac traceback check](../research/exact/AUTHOR_SOURCE_CONTEXT.md#nonzero-parameter-traceback-patterns-october19)
finds no new bounded nonempty name/declaration under the primary32-bit PEF
extension grammar: nine name overruns, one anchor-array overrun and three empty
names, all with parameter-count contradictions. Private
`.analysis/mac-traceback-parameter-layout-20261019/` retains raw slices, complete
compressed format sources and independent verification. This closes only those
previously excluded patterns, without changing source/counts or proving scan
exhaustiveness. No new compile/provider/runtime or disposable files follow.

October19 current-image round/game-over checks and the local delivery bundle
close the missing current-version lifecycle evidence described above. Source,
objects and all acceptance counts stay fixed; no compiler,relink,full replay or
campaign runs. Thirteen closed input/state/resource/helper files are archived
and member-hash verified before cleanup, releasing2,002,944 allocated bytes net.
Forty-nine verified runtime copies release another1,724,416 bytes. Complete
files/captures,current products/caches,the467,599-byte delivery and failed-run
evidence remain. The preceding rebuild/basic-flow checkpoint follows.

October19 [current VC4 rebuild and play](../research/CURRENT_VC4_BUILD.md) closes
the previously missing current-source delivery check. The17.003s build and
86.614s existing play flow pass under the capped scope. Seven closed build
helper/evidence files are member-hash verified in a140,888-byte archive,
releasing1,572,864 allocated bytes net before the receipt. The49 automated runtime
copies are removed after matching retained originals,current game or complete
saved bank; current products,caches and manual files stay. Exact/semantic counts
are unchanged. Source recovery and broader acceptance remain unfinished.

October19 [count-bound recovery](../research/exact/BANK_COUNT_BOUND.md) retains
the original live count reload, DWORD increment and signed comparison without
signed C++ overflow. Independent source/result review confirms the bounded
counterexample and complete18-body comparison. Totals stay248 authored exacts/
22 candidates,393 overall exacts; all270 current authored closure receipts pass
without a replay. Private authority is `.analysis/bank-count-bound-20261019/`.
Its26 closed input/product copies are member-hash verified in a1,025,437-byte
archive, releasing7,774,208 allocated bytes net before the small receipt.
Current products and incremental caches remain. The preceding byte-count work
and its cleanup follow.

October19 [byte-count arithmetic](../research/exact/BANK_BYTE_COUNT_ARITHMETIC.md)
is adopted with its full18-body comparison, bounded overflow witness, ten existing
bank cases and explicit two-glyph demotion. All270 authored entries have current
source/object/flag/complete-comparison receipts. The28 reviewed closed input and
product files are member-hash verified in a1,023,104-byte archive, releasing
7,790,592 allocated bytes after archive cost and before the small cleanup receipt.
Current products and caches remain. Private authority is
`.analysis/bank-byte-count-20261019/`, including independent review, coverage and
`cleanup.json`. The following filename/path review is the preceding closed work.

The [bank filename and path review](../research/exact/MAC_CANDIDATE_FLOW_CONNECTIONS.md#bank-filename-qualification-and-path-boundary)
reads one previously missing416-byte Mac helper through REA6.5 process capture
of the saved Ghidra project. All104 instructions,18 branches and six calls are
accounted for. Direct nonstack writes use a separate pointer loaded through r2;
input/output aliasing and four callee effects remain unknown. This does not
recover the Windows qualifier or prove mutable input.

One fixed filename/callback qualifier inference then receives one resource
compile. All18 complete raw/resolved bodies,262 bindings and six full literals
remain identical;13 prior exacts/3,050 bytes survive. Both complete12,332-byte
COFF files differ only in timestamp bytes4–5. Bank remains1475/64. Reject the
whole model; keep the canonical const API. The other27 owners/254 functions
remain uncompiled and unknown for that proposal. All754 protected SHA/mode/
nsmtime identities restore. No native build, relink, game or full replay follows.

The compiler/restore/comparison pipeline takes4.795s, peak193,404,928 bytes,
zero memory-limit events. The saved-project capture peaks403,165,184 bytes,
767 soft-high events and zero max/OOM events. Both use CPU0/35%,384/512MiB.
The verified33-member archive removes two temporary objects, seven proposals
and closed capture/runner inputs, releasing729,088 allocated bytes net.
Current products, useful caches, the saved project and selected helper export
remain. Private receipts:

- `.analysis/bank-filename-qualifier-20261018/`: eligibility/plan/result reviews,
  `summary.json`, `restoration.json`, `protected.json`, `archive-manifest.json`,
  `cleanup.json`, and `closed-model-and-path-capture.tar.gz`.
- `.analysis/mac-path-contract-20261018/`: question, complete selected export,
  process resource receipts and `independent-path-contract-review.json`.
- Capture Evidence `ev_acd98536850530d1f826c778dcdfaea0a33588ea746708b4111168ceaf0ce64c`.
  Full process Evidence is inside the verified archive, not a native snapshot.

Other recent closed models are indexed in
[Mac candidate flows](../research/exact/MAC_CANDIDATE_FLOW_CONNECTIONS.md) and
[fixed-point notes](../research/exact/EXACT_FIXED_POINT.md): bank API names,
paddle float-input precision, line public name, score parameter kind, and the
paired triangle/span DWORD colour declaration. The colour model regresses both
polygons while preserving ten other bodies; reject the whole model. The score
parameter model regresses paddle. Do not repeat these trials or widen them in
response to their outputs. The bounded polygon source-index lookup returned
zero matches with shard limits; it does not prove source absence.

## Resuming authored recovery

The bounded22-candidate review at608cca4 identifies the Blt gap now closed above;
the other21 rows expose no new consumed-operation omission in their stated
domains. The inventory review finds no concrete missing authored body/callee:
all3,719 direct edges,191 switch words,249 code-address words and177 COM sites
are accounted,with no unexplained non-CC text-gap bytes. Final denominator and
original context remain proof limits. Reuse `.analysis/authored-readiness-20261019/`.
The October20 relink/play record does not close these source questions. The
user explicitly returned priority to the23 authored nonexact functions. Resume
one evidence-supported source/declaration inference; complete game verification
stays deferred. Do not start another inventory pass, cast variant or identical
game flow without a new concrete source question.

For a new source question,use the current [23-function table](../research/exact/REMAINING_EXACT_FUNCTIONS.md#authored-candidates),
`config/functions.csv`, the relevant owner note and retained complete evidence.
Missing original declarations are reconstruction work, not an external blocker.
Form one bounded inference from actual producers, consumers, ownership or layout;
unique historical spelling is not required. A small byte-difference count alone
is not a new source question. Keep inference separate from recovered fact.

| Family | Reuse before another proposal | Boundary to preserve |
| --- | --- | --- |
| Bank/resources | [Bank flow and closed controls](../research/exact/MAC_CANDIDATE_FLOW_CONNECTIONS.md#reused-bankshape-bodies-and-api-name-control), [conditional-output lifetime](../research/exact/AUTHORED_BOUNDARY_CONTRACTS.md) | Bank1475/68 preserves extent/yoffset, low32 byte/count arithmetic and four later-EOF fields; names, filename qualification, cursor/row/column and transfer scopes are closed |
| PCX | [Complete packet proof](../research/exact/EXACT_PCX_PACKET_LOOP.md), [storage diagnostics](../research/exact/CLOSED_STORAGE_DIAGNOSTICS.md) | Original862/current979; all227 instructions accounted. Current308-byte frame has305 typed bytes plus3 slot padding. Original unaddressed four bytes do not justify a132-byte header or fake local |
| Triangle/polygons | [Fixed-point](../research/exact/EXACT_FIXED_POINT.md), [polygon workspace](../research/exact/POLYGON_SCAN_WORKSPACE.md), [complete instruction correspondence](../research/exact/RASTER_OPERATION_CORRESPONDENCE.md) | All1408 instructions map through frame roles/20 comparison groups; physical homes/source context stay open. Four root FixedPoint constructions/EH states;28-byte edge has one unknown word at+12. Preserve paired accesses, three pools, both Shellsorts and signed negative-error carry |
| Rotation | [Pixel-address correspondence](../research/exact/ROTATION_PIXEL_ADDRESS.md) | All365 instructions/22 calls/26 branches accounted. Unknown80-byte frame difference is not permission to add padding; integer-offset-before-base order is restored |
| Line/ranking/presentation | [Line](../research/exact/LINE_LOCKED_CURSOR.md), [ranking](../research/exact/RANKING_OWNER_FAMILY.md), [presentation](../research/exact/PRESENTATION_MERGE_SCOPE.md) | Known comparison/register producers remain. Fixed line rank model restores directions but loses correct homes; ranking has original homes and one shorter compare producer |
| Clocks/palette/last brick | [Author context](../research/exact/AUTHOR_SOURCE_CONTEXT.md), [lightning crop chain](../research/exact/EXACT_LIGHTNING_CROP_CHAIN.md), [destination Y](../research/exact/LIGHTNING_Y_COORDINATE_WRAP.md) | Clock cache/sampling order accounted; shared unsigned-long context already tested. Consumed destination-Y subtraction now wraps explicitly. Keep clock before RNG and existing callback-visible state; abs(INT_MIN) remains open |

Ranking's signed630−measure_text question is closed by the adopted explicit
DWORD subtraction. Its eight complete identities stay fixed; do not replay
the closed equality/owner controls. The connected unsigned text-advance trial
is also closed without adoption: the finite witness consumes no wrapped final
advance, while the proposal loses a complete exact. Retain that boundary and
avoid treating UBSan completion alone as an original-source declaration proof.

Resource callback-table extraction and historical DirectDraw header controls
can produce a private exact release-sprite while losing prior exact companions.
Those models remain rejected. Full-owner C/C++ and broad declaration controls
are also closed. Avoid name/order/count/flag sweeps, fake unused storage, assembly,
per-profile bodies, selective old objects, and repeated unchanged controls.
The [historical handoff](https://github.com/N0zoM1z0/dx-ball/blob/c99ab9e62fcc1625a0c0754a3ee0abb67dc10623/docs/agent/HANDOFF.md)
and linked owner notes retain the detailed boundaries of older trials.

## Reusable evidence and runtime limits

[REA](REA.md) is pinned at6.5.0/Ghidra12.1.4. The old MCP catalog can still report6.4;
use fresh `scripts/rea` CLI calls. Reuse closed evidence before opening a provider.
Native PEF admission is unsupported. Retained Mac observations use REA process
capture of pinned Ghidra; no native-provider snapshot or runtime r2/TOC model is
established. Use corrected `PowerPC:BE:32:default` exports with r2 unset.

Useful private Mac paths are `mac-port-payload-20261018` (carrier and321 named
traceback records), `mac-pef-focused-bodies-20261018` (corrected17-body export),
`mac-candidate-bodies-20261018` (loaded data/relocations/symbols), and the later
candidate-flow/score/path review directories, all under `.analysis/`.
The loaded645,276-byte data image is static loader evidence. Keep original
failed/wrong-width records separate. Reuse sealed compiler C1/C1XX/C2 snapshots
and traces; cold imports are expensive and do not recover original declarations
by themselves. [Frontend symbol order](../research/exact/VC4_FRONTEND_SYMBOL_ORDER.md)
and [backend records](../research/exact/VC4_BACKEND_SYMBOL_RECORDS.md) explain their limits.

[CRT dependency receipts](../research/exact/CRT_DEPENDENCY_INVENTORY.md#complete-receipt-coverage)
cover all78 no-source entries;19 original member dependencies are approved.
Do not divert authored recovery into fake C implementations of x87/SEH/stack
probe transports. Joined text/direct-flow audits retain their bounded scopes;
the final authored inventory is not established. The October19 inventory review
classifies all177 register-relative sites as DirectDraw/DirectSound COM calls
using receiver provenance and actual slots:98 surface,19 draw,9 palette,2 clipper,
13 sound-device and36 sound-buffer calls. Concrete runtime method addresses and
driver behavior remain unknown; these sites do not identify missing authored
functions. All74 retained instruction carriers are hash verified. See private
`bank-count-bound-20261019/directx-call-classification.json` and `inventory-review.json`.
These bounded reviews do not prove a final denominator or unrestricted semantic
equivalence of the22 candidates. After concrete source gaps are fixed, proceed
to the requested VC4 rebuild and actual game checks; do not block that work on
unique historical source spelling.

Earlier [entry/exit evidence](../research/RESTORED_CRT_ROUND_FLOW.md#current-image-bounded-entry-and-exit)
passes a bounded board0 episode on an earlier image. The historical
[original50 campaign](../research/ORIGINAL_CAMPAIGN.md#current-restored-crt-original-bank-prefix-october-17)
ended at its14,400s deadline after verifying initial boards0–19. It did not
complete50 or establish a crash/normal application exit; never restart that
producer. Custom single-brick boards and prior GUI episodes retain their own
image identities. Physical Windows, graphics/audio fidelity, exceptional paths,
full campaign acceptance and Wine9
[focus/surface-loss](../research/ROUND_FOCUS_RUNTIME.md) remain open.
The current image passes only the bounded play/editor flow described above;
it adds no full campaign or physical-driver acceptance. Ports remain deferred.

## Execution, cleanup and publication

Use `scripts/repo-python`, bounded LeanToken source reads, one allowed CPU and
one writable compiler/provider/Wine session. `session_lock()` is non-reentrant;
do not wrap a helper that already acquires it. CMake uses `--parallel 1`.
Heavy commands run in a user scope:

```bash
systemd-run --user --scope --quiet \
  -p CPUQuota=35% -p MemoryHigh=384M -p MemoryMax=512M \
  scripts/repo-python <focused-command>
```

REA's general Java heap cap is256MiB; the saved Mac project queries use128MiB
and Node192MiB. Do not overlap heavy trees. Automated audio uses
`PULSE_SINK=dxball_reconstruction_silent`; never change the default sink.

For a genuine new source model, verify the relevant target/toolchain, freeze
previous products and all recursive inputs, compile once per stable family,
and compare complete affected candidates and accepted companions. Include
all actual relocations, local destinations, full literals and metadata.
Restore canonical bytes, modes and nanosecond mtimes in `finally` under the lock;
verify Toolchain on both sides, including failures. Own child process groups
before restoring parent signals; unblock inherited signals in workers. Cleanup
ignores repeated TERM/INT, uses TERM plus bounded communicate, then unconditional
KILLPG and wait even if the group leader exited. A timeout preview is not a
reason to restart a still-live producer.

No default full replay, historical Oracle queue or repeated unchanged game run.
Update only changed claims; the handoff cleanup changes no ledger or progress
count. Current tested native/exact/VC4 products, useful incremental caches,
originals, manual saves and saved Ghidra project remain private and retained.
The20 existing probe/reference files inspected during handoff include reusable
readers and unique evidence; none is blindly deleted.

Archive unique closed evidence, verify every member's size/SHA, then remove only
the exact reviewed list. The latest archive/member hashes and allocated-byte
accounting are in the cleanup receipts above. Older historical raw paths may
have verified `.json.gz` carriers; check their original decompressed seals.
Never hardlink mutable products or aliases to immutable archives. The general
`scripts/clean-local.py` defaults to preview; inspect its proposed scope before
using `--apply`. Do not recursively remove evidence, tools or current caches.

Publish verified checkpoints to `origin/main` with an English subject beginning
`gpt-6.1-sol: `. Disable opportunistic Git GC/maintenance, verify raw commit message
bytes against the prepared message, check the remote with `git ls-remote`, and
finish with a clean worktree. A tidy handoff or complete source coverage does not
mean reconstruction is complete.
