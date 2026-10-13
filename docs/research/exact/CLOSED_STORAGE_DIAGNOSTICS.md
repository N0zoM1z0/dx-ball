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

The later [pointer-qualifier correction](DDRAW_MUTABLE_POINTERS.md) follows the
SDK's mutable rectangle, key and palette-entry parameters. All four earlier
SDK-type headers below retained const pointers; this was a separate question.
The correction preserves all exact functions and leaves candidate code unchanged.

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

## Rotation and value-copy follow-up

Eight completed compilations and one rejected C89 draft close these additional
questions. Canonical source, flags and objects remain unchanged.

| Model | Complete result |
| --- | --- |
| Nested double conversions instead of named rotation intermediates | Restores compiler temporary homes -368/-400; renderer1451/1572 with1476 differences, but loses two accepted projection bodies at261/223 each. |
| Per-axis origin/scan records | Renderer1451/1572 with1475 differences; same two projection losses. |
| Sampled source height/pixel/width record | Renderer1436/1572 with1479 differences; same projection losses. Initial declaration placement fails C89; corrected sampling/zero-store order compiles once. |
| VC4 floating consistency `/Op` | Four companions remain exact; renderer1455/1572 with1473 differences and additional FP operations. |
| C++ explosion cleanup record | Four companions remain exact across841 bytes; nested rectangle still uses address-based argument loads,799/797 with227 differences. Decorated calls bind their actual C API identities only in the private comparison. |
| Direct SetCursorPos import, narrow and actual SDK declarations | Both remain203/203 with four differences; USER32 IAT0x441350 is confirmed. Neither is adopted. |
| Disabled global optimization with `/O2` | VC4 `/O2 /Og-` preserves both geometry companions; collision remains329 bytes with two differences. |

The axis pairs have actual adjacent homes and coupled row/scan lifetimes. The
sampled plane groups only its consumed dimensions and cursor; both original
unclassified zero words remain separate. Neither record introduces padding or
extra fields. Private carriers use the corresponding `rotation-*`,
`explosion-cpp-value-copy-*`, `direct-cursor-import-*` and
`author-global-optimizer-*` directories under `.analysis/`.

A bounded PCX review verifies the existing227-instruction correspondence and
current979/862-byte comparison. The original reads exactly128 header bytes;
the unexplained four-byte frame gap has no access. No larger header, extra
stream member or missing packet operation is supported.

All [44 current candidates](REMAINING_EXACT_FUNCTIONS.md) receive complete
comparisons against verified canonical objects. None is already exact. These
rejected stages run no fixtures, game or provider session.

## Polygon record-copy boundary

A pending/active queue-pointer pair retains all nine accepted raster bodies,
but leaves ordinary/clipped differences at211/226. A whole20-role80-byte
workspace restores the intended record extent but adds five LEAs for nested
point copies:1553/1543 with1274 differences and1602/1592 with1314. Both reject.
Separating the two real endpoint temporaries yields the selected
[64-byte scan/sort workspace](POLYGON_SCAN_WORKSPACE.md), with211/210 differences.
A signed-long32 coordinate-kind diagnostic worsens those to212/214 and is
rejected; `raster.h` is restored. No original Windows POINT type is claimed.

## Owner-local Kernel clock declarations

Four runtime compilations test a private SDK sample, an opaque SDK counter and
narrow direct import declarations. The private and opaque models preserve all
ten runtime exacts (2,282 bytes), but change the paddle candidate from677/104 to
678/494. Seven ranking and twelve resource exacts also survive the opaque model.
None gains a complete function. The narrow import model loses accepted effect
blit366/332 and waiting170/6 in the display owner; startup's six exacts survive.
All source and canonical VC4 objects are restored.

The private SDK sample passes468 existing original/native clock and elapsed
cases. An initial receipt assertion mishandles unchanged zero-count keys; the
corrected receipt passes. Native and MinGW products are rebuilt from restored
source. Complete original code and real relocation mappings remain the basis
for the229 accepted exact closures. No game, provider query or online source
search accompanies this batch.

The complete comparisons, source stages and rejection receipt are retained in
`.analysis/kernel-clock-boundary-20261012/`. This closes owner-local SDK exposure
and opaque-counter models as an exactness improvement. The six palette compare
groups and elapsed/measure/scroller/presentation operand commutations receive
read-only reviews; no missing source operation or justified new state model is
found. Their earlier equivalent spelling experiments remain closed.


## Traversal iterator lifetimes

Two bounded trials on October 13 limit real iterators to their consuming
traversals. Neither introduces a value or changes an executable expression.

Text measurement keeps the sprite index and returned width outside a block
containing only its character iterator and loop. The complete emitter grows
from 279 to 280 bytes and differences rise from 3 to 63. The original iterator,
sprite and width homes were already EBP-8, EBP-4 and EBP-12; narrowing the iterator
lifetime does not preserve that arrangement.

Line drawing keeps one shared iterator in a block around the major-axis
if/else and both loops, after step normalization and before Unlock. Original
iterator initialization occurs at 0x403151 or 0x4031B5, with no consumer before
Lock or after traversal. The emitter shrinks from 445 to 439 bytes and
differences rise from 9 to 281. This plain block is distinct from the previously
closed four-value iteration record.

Both trials preserve all six accepted UI companions, but neither restores
a complete candidate. Sources are restored byte-for-byte; canonical compiler
objects and build products were never replaced. All 231 accepted complete
code/literal/metadata closures and their compiler inputs verify afterward.
No fixture, game, new provider session or online source search runs.

Original measurement evidence is
`ev_6a25f94931f763de87b46ce0de325939c392113a9c31de1568162431ea46a545`;
line evidence is
`ev_25f8571b40b1ee8c589f398fa1211552c03d241352d0737d904789e2664b8af2`.
Private full comparisons and rejected sources are retained in
`.analysis/measurement-loop-scope-20261013/` and
`.analysis/line-traversal-scope-20261013/`. Verified gzip copies release 16,384
allocated bytes while retaining the complete inputs and emitted objects.

## Rebound contact stages

Original rebound reuses one float slot for the paddle left edge, relative offset
and normalized contact position. At `0x411476`, an intermediate FST writes the
offset without popping the x87 value before division. The first threshold uses
the retained quotient; later thresholds use the stored float.

A shared-source stage reuses the float local and restores the intermediate write
while retaining the existing precise carrier for division and the first check.
Its complete comparison worsens from 687/681 with 550 differences to 699/681
with 552. All three accepted ball bodies in that recipe remain exact. The stage
is rejected and source restored; canonical objects and receipts are untouched.

A carrier-free chained assignment would return a float before the first native
comparison. For an offset of 7 and width of 100, that rounds above double 0.07
and changes the branch. No compiler-specific source body is introduced. The
original expression and portable precision requirement remain unresolved.

Original REA evidence is
`ev_6055fe1d318fa3f71d76b5cdbbbe862a3944dd9890035a53264b8ccfa2d7a074`.
Private source, compilation and complete comparison are retained in
`.analysis/rebound-contact-stages-20261013/`. No game or new fixture runs.

## DirectDraw SDK return types and interface boundary

Local VC4 headers establish HRESULT as LONG and ULONG/DWORD as unsigned long.
Seven resource compilations examine those actual types and the RECT coordinate
type. Some produce zero-difference blit, capture and glyph candidates, but lose
accepted resource companions. Adding the SDK flag and descriptor types preserves
the companions while leaving capture with two differences. None is adopted.

One full family comparison then retains all twelve resource exacts and obtains
three additional private zero comparisons, totaling 3572 bytes. It fails at
`update-bonuses`, whose complete comparison has 180 differences. A separate
typed interface split also fails the accepted resource comparisons. Both are
rejected; all tracked source and recipes return to the prior checkpoint.

These private results do not change the published exact count. Sources, actual
input receipts, complete comparisons and the independent SDK review remain in
`.analysis/ddraw-result-kinds-20261013/`, `.analysis/ddraw-native-sdk-20261013/`
and `.analysis/sdk-interface-boundary-20261013/`. No game runs accompany them.

## Embedded explosion-list member call

A private C++ caller declares `clear()` on the existing explosion-list type
and uses that member for both list clears in the entity cleanup controller.
The declaration follows the established ECX/list-pointer contract. It tests
whether a member call changes the embedded owner's address producer; no method
implementation is recovered or counted by this probe.

One compilation leaves cleanup at 107/106 bytes with 59 differences: the
embedded-owner LEA remains. Ten accepted runtime bodies retain all 2282 bytes.
Elapsed changes from three to two differences, while paddle drawing worsens
from 677/104 to 678/210. The C++ caller is rejected and canonical source, recipes
and products stay unchanged. There is no fixture, game or provider run.

Actual C++ names are bound through their unchanged source declarations.
Generated switch labels are checked against the owning function section and
their actual offsets, types and storage; section ordinals alone are insufficient.
The complete comparisons, declaration and rejection receipt remain in
`.analysis/explosion-member-call-20261013/`. Thirty-one completed copies are
gzip verified, releasing 593,920 allocated bytes. Reuse this result before
trying a member declaration as an embedded-address fix.

## DirectDraw surface virtual calls

The [later linked integration](EXACT_SURFACE_COM_CALLS.md) supersedes the
SDK-record rejection below. It restores allocator C linkage and validates
the whole shared family, promoting three bodies and explicitly demoting stretch
for a net gain of two exact functions. The other two views remain rejected.

Three private C++ compilations replace eighteen explicit surface vtable calls
with direct virtual member calls. The ordered interface follows all 36 original
IDirectDrawSurface/IUnknown slots, with stdcall and no virtual destructor.
The local VC4 `objbase.h` and installed DirectDraw header corroborate this ABI;
the original instruction sequence does not establish a unique source language.

Every model produces complete private zero comparisons for blit, capture and
glyph drawing. None preserves all accepted resource functions:

| Interface/data view | Accepted functions that lose their match |
| --- | --- |
| Existing fixed-width domains | Stretch: 139 bytes / 4 differences; release: 269 / 245 |
| Pinned SDK scalar types and Win32 records | Stretch: 141 / 90 |
| SDK method scalar types with shared C records | Keyed draw: 107 / 94; stretch: 141 / 94; release: 269 / 245 |

The SDK-record stretch retains its original rectangle arithmetic, but its two
bank/sprite address producers change register order and grow by one byte each.
There is no missing dispatch operation to restore. This initial batch rejected
all three views because each lost an accepted function; its private zeros were
not promoted. Canonical source, headers, recipes and products stayed unchanged
in that batch. No fixture, game or new provider session ran.

Complete source views, actual compiler inputs, bindings and owner comparisons
remain in `.analysis/ddraw-virtual-surface-20261013/`. Thirty-five completed
copies are gzip verified, releasing 684,032 allocated bytes. Further primitive
type or interface permutations need new evidence.
