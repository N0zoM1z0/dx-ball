# Sprite-record allocation scope

The bank loader's temporary record pointer now belongs to its allocation,
null check and publication block. After publication, every record access reads
the live bank slot; the pointer has no later consumer. The file pixel buffer
still spans reading, upload and release. This changes one existing declaration's
scope without changing its type, name, executable operations or failure cleanup.

The complete candidate improves from **1,475 bytes / 70 differences** to
**1,475 / 66**, including all 77 actual bindings and the full `rb` literal.
It remains nonexact. All fifteen resource exact companions preserve 3,572 bytes;
the other sixteen complete function identities, including PCX, stay unchanged.
One matching compilation covers all seventeen functions and eight project inputs.

## Instruction and lifetime evidence

Both loader bodies contain 425 instructions and reserve 180 frame bytes.
The only fifteen changed bytes are actual EBP displacement fields. They rotate
three disjoint DWORD homes:

| Value | Previous home | Current home | Original home |
| --- | --- | --- | --- |
| Width | EBP−56 | EBP−52 | EBP−52 |
| Height | EBP−52 | EBP−48 | EBP−28 |
| Temporary record | EBP−48 | EBP−56 | EBP−12 |

Five width accesses now match. One formerly coincident displacement in the
commuted width/height product becomes different, giving the net reduction of
four. All other complete instruction bytes remain identical, including branches,
calls and the descriptor, result, upload-pointer and color-key homes.
Original height/record homes, scalar allocation and two multiplication operand
orders remain unresolved. This does not recover the original declaration scope.

The original evidence remains
`ev_b55c6def4c1b4af6c165acfb1623311bffa077753d93fab01531787dca6b6d70`,
operation 01 in `2026-10-10T17-22-54.305Z-requests-825249`. No new provider query runs.
The [preceding iteration scope](BANK_SPRITE_ITERATION_SCOPE.md) retains its
historical source, product and test counts.

## Focused validation and VC4 integration

Ten existing bank cases pass against the unmodified original: seven supplied
banks, a small sprite stream, creation failure and an empty stream. Three
existing callback scenarios also pass, checking live bank changes during
color-key/descriptor calls and the pitch snapshot before Lock. Ordered calls,
defined bank/record state, pixel bytes and ownership effects agree.
No new semantic cases are added. The 235 historical input inventories receive
the changed source hash; their other cases are not rerun.

The native incremental build compiles this owner and its pending raster owner,
then links the library. The restored-CRT builder reuses all 116 source objects
and only relinks; its resource producer already uses the same `/ML` recipe.
The allocation-scope batch has no second VC4 source compilation or GUI run.
The approved nineteen original CRT members remain unchanged. A subsequent
startup observation uses this image, as described below.

The new image SHA-256 is
`ebe4a4ff8e6557fe0a89a32a064365941103b574f7373460e8e7cd5f51b2eb56`.
All 1,091 mapped addresses are unchanged. A complete comparison with the preceding
executed image finds only the fifteen bank displacement bytes and twelve bytes
inside six parsed COFF/resource-directory timestamp fields. Resource payloads
and all other image bytes are identical. The linked 1,475-byte body verifies
after all 77 relocations. Earlier GUI observations remain evidence for their
recorded preceding image; they are not claimed as new executions of this image.

## Current-image startup

One subsequent run records 75 read-only states from this `ebe4a4ff…` image,
using the unchanged startup/mouse/release prefix of the maintained play observer.
It reuses the existing game and SDK reader without compilation. The complete
400-byte initial board equals original board 0; the entire 20,000-byte saved
bank and all 49 originals remain unchanged. Real mouse input moves the paddle
to 480 then 200; a real click releases the ball and its coordinates change.
The game returns to menu mode 0 and completes the existing zero-exit/no-window
assertion. Reviewed captures show the colored first board, paddle and free ball.

The private driver's later first-board postcondition initially exits with code 1: it takes
the first `game-ready`-labelled poll, which still shows the menu. The wait records
every attempt. Existing gameplay and shutdown assertions had already completed
before that postcondition. A separate verifier checks the final successful wait
sample and the retained files; no second game runs. The executed driver,
traceback, corrected future driver, all samples and captures remain in private
`.analysis/bank-startup-20261017/`. The result is explicitly a verification of
retained observations, rather than a claim that the initial driver exited zero.
Pause, editor, clear, ranking, terminal and focus controls are not repeated.

## Closed file-metadata scope

One later private model limits baseline, signed code and pixel count to the
file-read/allocation/record-initialization phase. Width, height and file pixels
keep their iteration lifetime. All operations and the existing allocation/API
blocks remain unchanged. One compilation compares all 17 complete resource
functions: fifteen exact companions preserve 3,572 bytes and the other sixteen
code identities stay unchanged, but the bank worsens from 66 to 69 differences.
Reject this scope; canonical source, cached objects, ledgers and the linked
image stay unchanged. Do not repeat this model. Frozen source reversal,
comparisons and rejection are retained under
`.analysis/bank-file-metadata-scope-20261017/`; no runtime check uses that proposal.

## Retained evidence and scope

Private `.analysis/bank-allocation-scope-20261017/` retains source reversal,
before/after products and reports, complete comparisons, instruction changes,
existing case drivers/results and the whole-image delta. Preparation first
found a repeated allocation block in capture; it stopped before compilation
and was restricted to the selected loader. The first image verifier's narrower
timestamp assumption is retained with the parsed resource-field correction;
neither correction repeats a compiler or game run.

Nineteen frozen input/report files are archived and both matching objects are
compressed after complete byte checks, releasing 5,382,144 allocated bytes.
Current cache objects and the linked/native products remain available.
The subsequent metadata/startup batch archives eight proposal inputs and 233
observer inputs, then removes 49 verified automated runtime copies, releasing
another 2,936,832 allocated bytes. Manual runtimes and other profiles remain.

Totals remain **475 source / 380 exact / 95 complete candidates**, including
34 authored candidates. No full replay runs. Heavy work remains serial under
CPU 35%, memory high 640 MiB / maximum 768 MiB. This is a partial source improvement;
original campaign and physical-driver fidelity remain open.

## Current reader-order observation

The later [resource drawing-wrapper owner](RESOURCE_ROTATION_WRAPPER_OWNER.md)
leaves the bank at1475/66. A subsequent unchanged-closure
[C2 symbol-reader observation](VC4_BACKEND_SYMBOL_RECORDS.md#current-bank-loader-reader-order)
captures all14 scalar roles and both workspace objects. Incoming record`+8`
values equal their object sizes; actual reader order accumulates to their current
four-byte-aligned frame homes. This identifies a concrete intermediate order,
without proving its producer, an allocator algorithm or original declarations.
Width remains EBP−52 in both bodies; height is original−28/current−48. All18
complete resource identities survive one observed compile; no source proposal,
claim update, semantic replay, relink or game run follows. Current repository
totals remain394 exact/81 candidates, including21 authored candidates.

The subsequent [actual allocator investigation](VC4_BACKEND_SYMBOL_RECORDS.md#frame-allocation-from-the-symbol-reader)
identifies record`+4` across all16 objects and observes its real count write at
`0x401556`. The reader calls the normal allocation path per record, without
another bulk ordering step.17 final controlled pinned-code calls reproduce all
current homes and the180-byte frame. Original record order and declarations
remain unknown; no new source model or acceptance follows. The retained C++
before-iteration body proves root14/current116-byte API workspace was already
instantiated and compared at1475/72. Its exact reversal/product identities are
retained; do not retry that model solely because declaration context changed.

The later [C1XX symbol traversal](VC4_FRONTEND_SYMBOL_ORDER.md) explains the
current16-object order through actual name hashing, head insertion and ascending
bucket traversal.36 controlled compiler-helper calls match the earlier actual
C2 trace. Current source scopes/names are explicit inputs; original identifiers
and declarations remain unknown. This does not authorize identifier permutations
or reopen the root14 control. The bank remains1475/66 without another compile.
