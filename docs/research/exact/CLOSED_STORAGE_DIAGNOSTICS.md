# Closed drawing and SDK storage diagnostics

These models were tested against the frozen 041b1c1 compiler inputs and rejected.
Canonical source, objects and accepted receipts are restored by hash. Preserve
these results when choosing the next question.

| Model | Complete result | Decision |
| --- | --- | --- |
| Line iteration record: extents, error and index | 445 bytes, nine differences; six UI companions exact | No improvement |
| Four paddle scale/animation/overlay records | 679/677 bytes, 487/496/487/487 differences; ten runtime companions exact | No complete match |
| DirectDraw descriptor/key DWORD and LONG kinds | Line445/3; ordinary Blt195 and glyph328 exact; accepted stretch gains four differences and glyph search becomes146/86 | Reject companion losses |
| Descriptor pitch LONG only | Line445/6; glyph328 exact; accepted draw/keyed draw107/94 and stretch141/92 | Reject companion losses |
| Complete SDK declaration kinds, including RECT, COM signatures and specified fill fields | Same resource regressions as descriptor/key stage; six UI companions exact, line445/3 | Reject companion losses |

The final paddle record restores all observed source homes in the 68-byte frame:
scale, animation, margin, both rectangles and overlay coordinates. Bank/sprite
address scheduling still adds two bytes relative to the original; canonical
678/677 remains preferable. No record introduces unused fields or changes buffer
capacity. The original paddle dossier is Evidence
`ev_0b4d5d681d951be5b6a69ac1d9d09db3cc965811c767e0b2b4f7296609cc020a`.

The SDK diagnoses use actual declarations: pinned VC4 `windef.h` defines DWORD
as unsigned long and RECT members as LONG; `winnt.h` defines LONG as long;
`wtypes.h` defines HRESULT as LONG. The installed DirectDraw header corroborates
descriptor pitch and COM slots. Portable aliases retain32-bit width on LP64.
These corrections are legitimate ABI models, but do not preserve the current
accepted emission closure. No SDK declaration stage is adopted.

Independent narrow-parameter review found that raster colors and glyph forwarding
already emit the original DWORD argument reads. Editor key and line color use
original byte reads. There is no missing operation that justifies widening them.

Private complete source stages, objects and comparisons are in
`.analysis/line-iteration-record-20261012/`,
`.analysis/paddle-drawing-records-20261012/` and
`.analysis/ddraw-word-types-20261012/`. There are one, four and six completed
compilations respectively. No fixture, game or provider run accompanies these
rejected models. Completed copies are retained in verified gzip carriers.

## Clock and cursor follow-up

Five clock SDK-kind compilations test actual DWORD/LONG counter and tick contracts.
SDK-only kinds lose three accepted grayscale-read bytes. A consumed grayscale
cursor restores them, but grouped paddle states retain 679/677 with487 differences.
Shared full-word timestamp declarations make reset 426 exact but lose accepted
resource stretch and glyph search. A clock-owned header preserves runtime
companions but reset retains20 differences. These stages are rejected; their
private carrier is `.analysis/clock-sdk-kinds-20261012/`.

Three additional one-compile models are also closed. Separate fixed-X ranking
origin and mutable Y/index cursor keep 403/404 with330 differences and seven
companions exact. Unsigned score/cache ownership leaves every runtime result
unchanged and does not establish unique original signedness. Joint shared-index/
merge-index state keeps 984 bytes but worsens presentation from two to 14 differences.
All canonical inputs/products are restored before the later direct WinMM recovery.
Private carriers are `.analysis/ranking-row-cursor-20261012/`,
`.analysis/unsigned-score-state-20261012/` and
`.analysis/presentation-merge-cursor-20261012/`. No fixture or game accompanies them.

A bounded independent rotation/resource/raster review finds no missing operation.
The bank-loader pseudocode's `local_4c = 0` before Lock has no corresponding original
store: complete assembly goes directly from pitch at `0x404A8E` to pushes at
`0x404A91`. Do not add that pseudocode artifact. Both polygon controllers retain
identical mnemonic sequences, all mapped homes and equivalent operand scheduling.
No new layout, capacity or parameter-width model is justified by these reviews.

## Direct Kernel clock and scroller guard

The genuine QueryPerformanceFrequency/Counter imports bind the original IAT
slots `0x4412A0` and `0x44129C`. A shared Windows SDK header makes refresh-score
74 bytes exact, but loses three accepted ranking-insertion bytes. Narrow ABI
declarations preserve ranking insertion and remove that gain. Moving the SDK
to the clock header loses the accepted effect blit and still leaves refresh-score
with six differences. All three stages are rejected and canonical source and
products restored. Four runtime, two game-over, one display and one startup
compilation are retained in `.analysis/direct-kernel-clock-20261012/`.

Reversing the equivalent scroller advance guard leaves 233 bytes and three
differences unchanged: VC4 still loads advance before shift and commutes the
comparison. One intro compilation preserves all 17 exact companions and is
rejected. Do not repeat this guard spelling. Its carrier is
`.analysis/scroller-update-guard-20261012/`. Neither probe runs fixtures or games.
