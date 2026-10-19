# Remaining exact functions

Updated October19,2026, after the ranking coordinate-subtraction correction.
Accepted totals are **393 functions / 84,633 code bytes / 244 metadata bytes**.
There are **82 complete nonexact comparisons: 22 authored and 60 runtime**. None is an accepted exact.

These 82 are all currently source-present nonexact entries. The eight allocator
functions now have complete exact comparisons, closing the three previous
report gaps. Another 78 of the 553 independent inventory entries lack a
source-present ledger row. The 24 overlapping compiler fragments are tracked
separately in `config/compiler-fragments.csv`. The provisional inventory and
origin review still need reconciliation; this is not a final authored denominator.

The [dependency inventory audit](CRT_DEPENDENCY_INVENTORY.md) adds eight omitted
CRT entries and recovers five existing helper identities. Source/exact/candidate
counts and all 34 authored comparisons remain unchanged.
The subsequent [intrinsic-entry closure](CRT_CI_ENTRY_ORIGINS.md) proves thirteen
runtime origins; only source-present no-op40CC20 remains origin-unknown. It adds
no source or exact acceptance and does not prove the final authored denominator.
The [dependency receipt reconciliation](CRT_DEPENDENCY_INVENTORY.md#complete-receipt-coverage)
now gives all78 current no-source entries complete original receipts; it adds no
source, exact or origin claim. The [height correspondence](ROTATION_PIXEL_ADDRESS.md#height-helper-correspondence)
accounts for all63 instructions and identifies only two bank-address producers
as its extent difference; the maintained comparison remains unchanged.
The [CRT suffix ownership review](CRT_SUFFIX_OWNERSHIP.md) accounts for every
non-CC gap byte through existing complete CRT sections and corrects one
46→53-byte runtime extent. It adds no source, exact or independent entry.

The original two-byte decimal-point array and shared declarations close all310
exponent-formatting bytes and the six-byte suffix, preserving all13 affected
prior exacts. Multiplication's unchanged C body emits50 differences through the
new declaration context. See [character state](RUNTIME_CHARACTER_STATE.md).

Two omitted complete runtime functions add74 exact bytes: onexit bootstrap54
and stdio finalizer20. Default pretermination storage now invokes the finalizer;
all prior exact and candidate byte results are preserved. See
[exit bootstrap](RUNTIME_TERMINATION_BOOTSTRAP.md).

The omitted193-byte stdio initializer is also exact, with644 initialized data
bytes/two bindings restored. Prior exact/candidate results remain unchanged.
See [stdio initialization](RUNTIME_STDIO_INITIALIZATION.md).

Two new complete runtime candidates cover unsigned64 division/remainder with
actual stdcall16 and64-bit results. Their327/104 and280/117-byte comparisons
remain nonexact;990 logical arithmetic cases and12 emulated fault cases pass.
See [unsigned64 helpers](RUNTIME_U64_ARITHMETIC.md).

Both memcpy/memmove entries now have complete ordinary-memory source, including
overlap. Their 215/334-byte comparisons remain nonexact; 1,688 layouts and eight
unmapped zero-count cases pass. The original EDX-dependent grouping preserves
the final bytes without a hidden argument. See [memory copy](RUNTIME_MEMORY_COPY.md).

The abstract `_control87` layer now has complete C source. Its 68/63-byte
comparison remains nonexact with 44 differing positions; 1,792 logical cases
and 1,792 actual Win32 x87 comparisons pass. Physical backend source and full
startup remain open. See [abstract x87 control](RUNTIME_CONTROL87.md).

Three stdcall-to-thiscall member-call APIs now have C++ direct-call source,
with 784 logical cases and seven affected Win32 selectors passing. Their
37/42/47-byte bodies remain nonexact against seven bytes each; extra call-frame
and return-address identity remain open. See [member calls](RUNTIME_CPP_MEMBER_CALL.md).

The [cross-function score workspaces](SCORE_WORKSPACE_REGIONS.md) restore two
complete exact functions: draw-score433 and redraw-intro587. The existing consumed
arrays use decimal20 in both functions and menu text100. All30 prior exact
companions and four other candidate identities survive36 complete comparisons;
135 existing focused calls pass. Capacities remain inferred, not uniquely
recovered source declarations. There is no full replay or game campaign.

The [bonus C++ owner](BONUS_CPP_OWNER.md) restores the complete2,168-byte updater,
reducing180 differences to zero while preserving all three prior bonus exacts.
Only the implementation language and complete header view change; all bodies
and public APIs remain unchanged. Existing2,851 bonus calls plus one setup pass.
The current linked BSS and all actual references to moved mapped data are checked.
No full replay or game run follows.

The [current-context C++ rotation owner](ROTATION_CPP_OWNER.md) promotes complete
horizontal offset259 and width259, and explicitly demotes vertical offset to
193/191/159. Height and wrapper stay exact; the renderer keeps1458/1466 with a
new digest. All six complete functions,116 actual bindings and full constants
are checked together. Existing1,024 rotation calls,329 width cases and24
original/Native/full-VC4 helper observations pass. This is a net one-exact gain,
with no selective object/header mix or full replay.

The later [resource drawing-wrapper owner](RESOURCE_ROTATION_WRAPPER_OWNER.md)
restores y-offset191, keyed draw105 and stretch139, explicitly demoting ordinary
draw and blt. Net+1 exact/+135 bytes. Load-bank improves to1475/66; PCX is979/851.
All23 full functions and their constants/bindings are compared together;16 code
identities survive. Current classified authored coverage is249 exact/21 candidates.

The [drawing-primitive owner](DRAWING_PRIMITIVES_OWNER.md) moves line/fill together
and restores three original right-palette guard bytes,234/9→234/6, with no lost
matching byte. Eight complete companions and all six affected exacts survive.
Existing562 focused calls pass. Classified authored coverage remains249 exact/
21 candidates, now across30 compiler closures; there is no new exact claim.

The tables below come from the retained current comparison report:
`.analysis/exact-candidate-audit-20261012/comparison.json`.
The directory date is historical; its contents are current.
`config/match-units.toml` supplies target addresses, full extents, compiler
inputs, relocation bindings and research links. Origin classification comes
from `config/function-origins.csv`.

Differences count raw byte positions after relocation resolution, not missing
operations. Different instruction lengths shift later bytes. Whole functions,
actual relocations, declared literals and attached metadata are compared;
zero in a private control is not automatically a maintained exact.

The earlier recovery chronology is preserved
[in Git](https://github.com/N0zoM1z0/dx-ball/blob/d3053ebf453d5e2db1dc545dbe188f28f02f2d00/docs/research/exact/REMAINING_EXACT_FUNCTIONS.md).
Use the [handoff](../../agent/HANDOFF.md) for priorities, latest adopted work,
resource requirements and resume procedure.

## Authored candidates

The [ranking coordinate-subtraction correction](RANKING_COORDINATE_WRAP.md)
preserves all8 complete gameover code identities/234 bindings/13 literals and
seven exacts. A finite original/native boundary case and17 unchanged existing
ranking cases pass; ranking stays403/330. The separate text-advance proposal
loses the existing150-byte exact body and is rejected, with its boundary
evidence retained. Current270 authored closure receipts are in
`.analysis/ranking-coordinate-wrap-20261019/authored-coverage.json`.

The [PCX destination-coordinate correction](PCX_COORDINATE_WRAP.md) makes four
observed DWORD increments explicit without changing any of the18 complete
resource code identities. All11 exacts survive, PCX stays979/850, and four
finite clipped counterexamples plus99 unchanged existing PCX cases pass.
Current270 authored closure receipts are in
`.analysis/pcx-coordinate-wrap-20261019/authored-coverage.json`; counts stay fixed.

The [conditional-output/text-width corrections](AUTHORED_BOUNDARY_CONTRACTS.md)
retain later-EOF scalar lifetimes and explicit modulo32 width sums. Byte
comparisons worsen: bank1475/63→1475/68 and measurement279/3→282/26. All25
affected complete functions/300 bindings/six literals compare, preserving17
exacts and23 other code identities. Bounded counterexamples and10 existing
bank/216 measurement cases pass. Counts remain248 authored exact/22 candidates;
current receipts are `.analysis/authored-boundaries-20261019/authored-coverage.json`.

The [live count-bound recovery](BANK_COUNT_BOUND.md) preserves the original
modulo32 increment followed by a signed comparison, including every guard
reload. The actual INT_MAX counterexample rejects the old native path and
passes after recovery. All18 complete resource functions/262 bindings/six
literals compare together; all11 exacts and16 code identities survive.
Bank improves1475/64 to1475/63; the other candidate counts remain unchanged.
Ten existing bank cases pass. Current authored receipts are in
`.analysis/bank-count-bound-20261019/authored-coverage.json`.

The [bank byte-count recovery](BANK_BYTE_COUNT_ARITHMETIC.md) explicitly defines
the original modulo32 product before malloc/fread. One resource compile checks
all18 functions/262 bindings/six full literals. Bank remains1475/64; two glyph
functions are honestly demoted to146/86 and332/258 after changed address
producers. Their complete operations remain present. PCX becomes979/850.
An actual overflow/CreateSurface-failure witness and ten existing bank cases
pass. Current coverage is248 exact/22 candidates across30 compiler closures;
`.analysis/bank-byte-count-20261019/authored-coverage.json` records that checkpoint.
The historical October18 chronology below retains its own totals.

At the October18 handoff, the [bank filename qualifier control](MAC_CANDIDATE_FLOW_CONNECTIONS.md#bank-filename-qualification-and-path-boundary)
closes after one resource compile: all18 complete raw/resolved bodies and13
prior exacts remain unchanged; full COFF differences are timestamps only.
The canonical const API and250 authored exact/20 candidates remain. The new
complete Mac path helper does not recover Windows qualification or input
mutability. Other27 header owners stay uncompiled for that rejected proposal.
Reuse the archived evidence; no qualifier variants or full replay follow.

The [public author-context check](AUTHOR_SOURCE_CONTEXT.md) initially inspected
a VC5 tutorial and later publisher sources; its34-candidate count is historical.
Actual DOS debug records subsequently connect the author's font, palette and
bank families. One fixed text declaration model leaves all seven UI code bodies
unchanged and is rejected. The Classic1.09 installer supplies no source/PDB/MAP
among its49 named main paths, and its actual game PE has no symbols or debug
directory. These are bounded findings, not proof of source absence or optimality;
no further declaration or compiler-setting trial follows from them.

The current receipt audit verifies source/object/flag identities for all270
classified authored entries across30 matching recipes:250 exact and20 complete
candidates. It reuses existing comparisons without replaying; it does not prove
source optimality, semantic equivalence or a final authored denominator.
Authority: `.analysis/raster-muldiv-integration-20261018/authored-coverage.json`.
The [fixed palette declaration inference](AUTHOR_SOURCE_CONTEXT.md#fixed-author-palette-declaration-model)
uses actual connected `r/g/b/mode` roles in both rotations. Right rotation is
now complete 234/0 exact, while animate-palette improves from nine differences
to three. All 27 affected units/459 bindings compare, preserving 21 prior exacts
and 25 other identities. The paired model is adopted without spelling variants.
The later [actual line comparison observation](LINE_LOCKED_CURSOR.md#actual-backend-comparison-decisions-october18)
captures the three current symbol-role swaps and checks their correspondence to
all nine residual bytes. It changes no source, product or acceptance claim.
One [fixed rank-constrained declaration model](LINE_LOCKED_CURSOR.md#fixed-role-rank-declaration-inference-october-18)
then restores those three directions but cycles the previously correct scalar
homes, producing445/22. It is rejected after a complete two-function comparison;
canonical line445/9, fill85exact and all claim counts remain unchanged.

The [genuine MulDiv API integration](EXACT_FIXED_POINT.md#genuine-api-integration-october18)
adopts the previously frozen direct-import/host model for its independently
established API contract. All 12 raster functions, 141 bindings and 296 metadata
bytes verify; nine existing exacts survive. Ordinary/clipped polygons change
214→216 and 214→213 differences and remain paired candidates. Existing 7,164
raster cases and both legacy builds pass. This restores an API boundary without
claiming a new exact or original header placement; no full replay runs.

The [sampled paddle width lifetime](PADDLE_WIDTH_SAMPLING_SCOPE.md) restores its
677-byte extent and original right-edge sum order, reducing210 to68 strict
differences. All15 runtime companion identities and13 exacts survive;332 existing
paddle calls pass. This is partial source recovery; exact/candidate counts stay
unchanged, and physical variable homes remain different.

The [ranking implementation owner control](RANKING_OWNER_FAMILY.md) leaves all
14 affected code/metadata identities unchanged, including 13 exacts. Ranking
drawing's complete 135-instruction correspondence has all original frame homes;
one comparison producer explains its one-byte shortening. The model is rejected
without source or claim changes. The current
[presenter correspondence](PRESENTATION_MERGE_SCOPE.md#current-producer-correspondence-october-17)
locates all six differences in left/right/bottom min/max index loads, with top
now matching. These are complete candidate explanations, not new exacts.

The [independent-global adoption](INDEPENDENT_BOARD_STORAGE.md#production-acceptance-october-17)
compares all278 affected complete units, promotes17 and explicitly demotes eight.
This includes16 authored gains/eight authored losses and one generated gain.
Actual production placement, terminal-copy and the eight demoted flows pass;
all prior before-images and failures remain retained. No selective interfaces,
old objects for changed inputs or full historical replay are used. The historical
context below predates that adoption; the tables show current comparisons.

All 34 authored candidates were compared across their complete original
extents on October 13. The bank loader's [allocation scope](BANK_ALLOCATION_SCOPE.md)
updates its complete comparison on October 17; subsequent source updates are
described below.
The [rotation address recovery](ROTATION_PIXEL_ADDRESS.md) changes eight bytes
to restore integer-offset-before-base evaluation at both pixel writes; its
complete raw difference count remains1466 and all five companions are unchanged.
The [last-brick expiry scope](LIGHTNING_EXPIRY_SCOPE.md) restores six original
homes and improves its complete comparison from992 to990 differences, preserving
all twelve exact companions and the other nineteen complete code identities. The later
[complete crop-producer recovery](EXACT_LIGHTNING_CROP_CHAIN.md) restores both
original13-instruction chains and shrinks the current body to1061 bytes;992 raw
differences reflect shifted byte positions. All19 companions/16 current exacts
retain their identities; time/frame representation remains unresolved.
The [editor-key correspondence](EDITOR_KEY_ADDRESS_CORRESPONDENCE.md) explains
its six-byte extent difference through the board-clear address producer, with
the complete switch data and all 256 input-byte routes accounted for. Its
maintained 638/632/260 comparison remains unchanged and nonexact.

The [complete brick-hit review](EXACT_BRICK_POWERS.md#complete-hit-correspondence-and-internal-binding-repair-october-17)
accounts for all362 instructions and71 switch bytes, repairing two wrong internal
comparison targets from actual COFF definitions. The complete relocated digest
changes while its pre-adoption1316/1315/418 result stays nonexact. The subsequent
[particle scope adoption](EXACT_BRICK_POWERS.md#particle-iterator-scope-adoption)
reuses the unchanged prior producer closure and restores the score-flag home,
improving that comparison to1316/1315/416. The subsequent
[joint shared-counter/switch-pan scope](EXACT_BRICK_POWERS.md#shared-counter-and-switch-pan-scope)
restores all19 frame accesses to their original homes and improves416→405.
One owner compile preserves five exact companions and six other body identities;
108 existing cases pass. Independent ownership subsequently restores that receiver and the full1,315-byte function is exact.

| Function | Original bytes | Current bytes | Differing positions |
| --- | ---: | ---: | ---: |
| `elapsed` | 81 | 81 | 3 |
| `animate-palette` | 234 | 234 | 3 |
| `present-regions-now` | 984 | 984 | 6 |
| `wait-frames` | 170 | 170 | 8 |
| `draw-line` | 445 | 445 | 9 |
| `reset-round` | 426 | 426 | 20 |
| `measure-text` | 279 | 282 | 26 |
| `load-sprite-bank` | 1475 | 1475 | 68 |
| `draw-paddle` | 677 | 677 | 68 |
| `find-glyph` | 145 | 146 | 86 |
| `fill-triangle` | 1710 | 1710 | 88 |
| `draw-sprite` | 105 | 107 | 94 |
| `find-hit-region` | 173 | 172 | 132 |
| `blt-sprite` | 195 | 199 | 173 |
| `fill-polygon` | 1543 | 1543 | 216 |
| `fill-polygon-clipped` | 1592 | 1592 | 213 |
| `release-sprite` | 262 | 269 | 245 |
| `draw-glyph` | 328 | 332 | 258 |
| `draw-high-scores` | 404 | 403 | 330 |
| `load-pcx` | 862 | 979 | 850 |
| `last-brick` | 1057 | 1061 | 992 |
| `render-rotated-sprite` | 1572 | 1458 | 1466 |

## Runtime candidates

| Function | Original bytes | Current bytes | Differing positions |
| --- | ---: | ---: | ---: |
| `crt-flush-output` | 328 | 328 | 1 |
| `crt-commit-descriptor` | 111 | 111 | 2 |
| `crt-open-shared-descriptor` | 1053 | 1053 | 2 |
| `crt-read-stream` | 326 | 326 | 2 |
| `crt-register-onexit` | 121 | 121 | 2 |
| `crt-set-file-mode` | 128 | 128 | 2 |
| `crt-set-os-handle` | 163 | 163 | 2 |
| `cpp-build-catch-object` | 510 | 510 | 4 |
| `crt-allocate-descriptor` | 184 | 184 | 4 |
| `crt-force-decimal-point` | 101 | 101 | 4 |
| `crt-add-with-carry` | 35 | 35 | 5 |
| `crt-copy-mantissa` | 29 | 29 | 5 |
| `crt-initialize-math` | 23 | 25 | 5 |
| `crt-math-function-name` | 38 | 38 | 5 |
| `crt-run-initializers` | 32 | 32 | 6 |
| `crt-user-math-error` | 174 | 174 | 6 |
| `crt-multibyte-classify` | 58 | 58 | 7 |
| `crt-pow-special` | 584 | 584 | 8 |
| `crt-exception-filter` | 351 | 351 | 9 |
| `crt-set-codepage` | 475 | 475 | 11 |
| `crt-zero-allocate` | 82 | 82 | 11 |
| `crt-x87-exception-bridge` | 288 | 288 | 14 |
| `crt-bounded-byte-count` | 44 | 44 | 15 |
| `crt-decimal-digits96` | 232 | 232 | 20 |
| `crt-fseek` | 153 | 153 | 20 |
| `crt-raise-float-exception` | 876 | 876 | 22 |
| `crt-write-descriptor` | 555 | 555 | 22 |
| `crt-initialize-lowio` | 467 | 467 | 32 |
| `crt-unwind-handler` | 34 | 31 | 34 |
| `crt-right-mantissa96` | 54 | 48 | 35 |
| `cpp-call-member-0` | 7 | 37 | 37 |
| `cpp-call-member-1` | 7 | 42 | 42 |
| `crt-control87` | 63 | 68 | 44 |
| `cpp-call-member-2` | 7 | 47 | 47 |
| `crt-left-mantissa96` | 62 | 50 | 47 |
| `crt-multiply-extended12` | 678 | 678 | 50 |
| `crt-strncpy` | 36 | 58 | 56 |
| `crt-strncat` | 49 | 69 | 68 |
| `crt-double-to-extended` | 187 | 185 | 75 |
| `crt-extended-convert` | 459 | 459 | 95 |
| `cpp-find-foreign-handler` | 213 | 212 | 105 |
| `crt-locale-map` | 555 | 551 | 110 |
| `crt-string-length` | 119 | 102 | 112 |
| `crt-shift-mantissa` | 173 | 172 | 134 |
| `crt-double-integer-type` | 127 | 154 | 141 |
| `crt-classify-double` | 162 | 161 | 148 |
| `crt-round-mantissa` | 172 | 163 | 153 |
| `crt-memory-fill` | 88 | 177 | 176 |
| `crt-raise-signal` | 393 | 397 | 215 |
| `crt-strcpy` | 232 | 198 | 232 |
| `crt-u64-remainder` | 117 | 280 | 275 |
| `crt-strcat` | 224 | 291 | 276 |
| `crt-u64-divide` | 104 | 327 | 322 |
| `cpp-find-handler` | 659 | 658 | 326 |
| `crt-memory-copy` | 334 | 215 | 327 |
| `crt-memcpy-entry` | 334 | 215 | 329 |
| `crt-write-error` | 494 | 493 | 412 |
| `crt-read-descriptor` | 611 | 609 | 473 |
| `crt-decimal-output` | 923 | 922 | 535 |
| `crt-parse-extended12` | 1871 | 1851 | 1662 |

No compiler-generated candidate remains; the real global-list inner initializer is now exact.

## Allocator comparison gaps closed

All eight allocator bodies now match 213 complete code bytes. Independent typed
Heap import cells preserve the public binding record and unchanged public
header, so the five prior allocator exacts and outside compiler inputs remain.
See [allocator ownership](../ALLOCATOR_OWNER.md) for the three new acceptances,
focused native/Win32 checks and the earlier rejected controls. There are now
zero source-present entries outside the exact and candidate comparison reports.

## Evidence and closed controls

Read the relevant note before selecting another source model:

- [Closed storage diagnostics](CLOSED_STORAGE_DIAGNOSTICS.md) covers rejected
  game-owner layout, SDK, declaration, rotation and workspace controls.
  Preserve accepted companions; do not sweep equivalent spellings or invent
  buffer capacity/padding to explain a frame gap.
- [Float rendering](RUNTIME_FLOAT_RENDER.md) records the completed private
  original `cvt.c` owner control: exponent formatting becomes exact, but fixed
  and general lose their accepted results. Not adopted; maintained values above
  remain authoritative.
- [FP exception entries](RUNTIME_FP_DECOMPOSITION.md) records matherr's remaining
  adjacent store/load scheduling difference. [FP dispatch](RUNTIME_FP_DISPATCH.md)
  records the C producer's raising-exact/handling-nonexact tradeoff.
- [Stream transfer](RUNTIME_STREAM_TRANSFER.md),
  [stream opening](RUNTIME_STREAM_OPEN.md),
  [stream operations](RUNTIME_STREAM_OPERATIONS.md) and
  [low-I/O lifetime](RUNTIME_LOWIO_READ_CLOSE.md) retain near-match producer
  controls. Original ownership helps some functions but is not a blanket fix.
- [Decimal conversion](RUNTIME_DECIMAL_CONVERSION.md) retains full parser,
  multiplication and table evidence. Do not introduce fake uninitialized reads
  solely to fill an original length difference.
- [Memory copy](RUNTIME_MEMORY_COPY.md),
  [string concatenation](RUNTIME_STRING_CONCATENATION.md) and
  [memory fill](RUNTIME_MEMORY_FILL.md) describe assembly-origin boundaries;
  do not replace missing ABI evidence with copied bytes or a convenient wrapper.
- [CRT initialized storage](../CRT_INITIALIZED_STORAGE_CLOSURE.md) and
  [FDIV initialization](../CRT_FDIV_INITIALIZATION_FRONTIER.md) cover integration
  frontiers separately from standalone function exactness.

The allocator checkpoint includes one adopted optimized compilation and two
rejected source controls. The rejected public-cell control also ran the existing
allocator differential check; no gameplay was rerun. The final complete replay
uses retained verified objects; `validate-tracking.py --require-target` passes
with 543 / 457 / 367.
The subsequent C++ terminal checkpoint adds two exact source bodies and their
scope tables; tracking passes 543 / 459 / 369. Previous exact inputs/products
are verified and reused; seven Wine SEH boundary controls pass. See
[terminal source](RUNTIME_CPP_TERMINAL.md).
