# Remaining exact functions

Updated October 17, 2026, after the last-brick expiry scope recovery.
Accepted totals are **380 functions / 77,485 code bytes / 244 metadata bytes**.
There are **95 complete nonexact comparisons: 34 authored, 60 runtime and one
compiler-generated**. None is an accepted exact.

These 95 are all currently source-present nonexact entries. The eight allocator
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

The [public author-context check](AUTHOR_SOURCE_CONTEXT.md) finds no basis within
its inspected pages/archive/nine source files for a new1.07 declaration or
compiler-setting trial. The linked tutorial explicitly uses VC5, and the other
contexts are later publisher projects. All34 comparisons remain unchanged; this
is neither a whole-repository search nor proof of source optimality.

An October 17 receipt audit verifies current source/object/flag identities for
all 270 classified authored entries across 29 matching-build recipes: 236 exact
and 34 complete candidates. It reuses existing comparisons without replaying.
This coverage audit does not establish source optimality, semantic equivalence
or the final authored denominator. Its retained rows and compiler closures are
`.analysis/brick-hit-binding-repair-20261017/authored-coverage.json`.
This read-only refresh follows thirteen notes-only ledger corrections and two
instruction-backed brick-hit internal target repairs; source, status, extents,
ABI, acceptance and all comparison counts stay
unchanged. The earlier coverage receipt remains preserved in its original phase.

All 34 authored candidates were compared across their complete original
extents on October 13. The bank loader's [allocation scope](BANK_ALLOCATION_SCOPE.md)
updates its complete comparison on October 17; the other results are unchanged.
The [rotation address recovery](ROTATION_PIXEL_ADDRESS.md) changes eight bytes
to restore integer-offset-before-base evaluation at both pixel writes; its
complete raw difference count remains1466 and all five companions are unchanged.
The [last-brick expiry scope](LIGHTNING_EXPIRY_SCOPE.md) restores six original
homes and improves its complete comparison from992 to990 differences, preserving
all twelve exact companions and the other nineteen complete code identities.
The [editor-key correspondence](EDITOR_KEY_ADDRESS_CORRESPONDENCE.md) explains
its six-byte extent difference through the board-clear address producer, with
the complete switch data and all 256 input-byte routes accounted for. Its
maintained 638/632/260 comparison remains unchanged and nonexact.

The [complete brick-hit review](EXACT_BRICK_POWERS.md#complete-hit-correspondence-and-internal-binding-repair-october-17)
accounts for all362 instructions and71 switch bytes, repairing two wrong internal
comparison targets from actual COFF definitions. The complete relocated digest
changes while1316/1315/418 and all acceptance counts stay unchanged. Three DWORD
homes and one receiver address producer remain; no new source or compiler trial.

| Function | Original bytes | Current bytes | Differing positions |
| --- | ---: | ---: | ---: |
| `present-regions-now` | 984 | 984 | 2 |
| `elapsed` | 81 | 81 | 3 |
| `measure-text` | 279 | 279 | 3 |
| `sort-present-regions` | 296 | 296 | 3 |
| `update-paddle-position` | 203 | 203 | 4 |
| `animate-palette` | 234 | 234 | 6 |
| `refresh-score` | 74 | 74 | 6 |
| `rotate-palette-right` | 234 | 234 | 6 |
| `wait-frames` | 170 | 170 | 6 |
| `draw-line` | 445 | 445 | 9 |
| `palette-transition` | 1339 | 1339 | 12 |
| `draw-score` | 433 | 433 | 21 |
| `load-editor-board` | 52 | 58 | 23 |
| `store-editor-board` | 52 | 58 | 42 |
| `draw-paddle` | 677 | 677 | 48 |
| `queue-explosion-at` | 99 | 100 | 51 |
| `clear-all-entities` | 106 | 107 | 59 |
| `load-sprite-bank` | 1475 | 1475 | 66 |
| `fill-triangle` | 1710 | 1710 | 88 |
| `rotated-sprite-height` | 191 | 193 | 158 |
| `fill-polygon-clipped` | 1592 | 1592 | 214 |
| `fill-polygon` | 1543 | 1543 | 214 |
| `stretch-effect-sprite` | 306 | 308 | 252 |
| `editor-key` | 632 | 638 | 260 |
| `drop-bricks` | 426 | 436 | 306 |
| `draw-effect-sprite` | 361 | 365 | 330 |
| `draw-high-scores` | 404 | 403 | 330 |
| `blt-effect-sprite` | 362 | 366 | 332 |
| `hit-board-tile` | 1315 | 1316 | 418 |
| `redraw-intro` | 587 | 578 | 560 |
| `load-pcx` | 862 | 979 | 851 |
| `last-brick` | 1057 | 1067 | 990 |
| `game-frame` | 1688 | 1691 | 1155 |
| `render-rotated-sprite` | 1572 | 1466 | 1466 |

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
| `crt-strcat` | 224 | 291 | 276 |
| `cpp-find-handler` | 659 | 658 | 326 |
| `crt-memory-copy` | 334 | 215 | 327 |
| `crt-memcpy-entry` | 334 | 215 | 329 |
| `crt-write-error` | 494 | 493 | 412 |
| `crt-read-descriptor` | 611 | 609 | 473 |
| `crt-decimal-output` | 923 | 922 | 535 |
| `crt-parse-extended12` | 1871 | 1851 | 1662 |
| `crt-u64-divide` | 104 | 327 | 322 |
| `crt-u64-remainder` | 117 | 280 | 275 |

## Compiler-generated candidate

| Function | Original bytes | Current bytes | Differing positions |
| --- | ---: | ---: | ---: |
| `list-global-init-13` | 26 | 32 | 21 |

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
