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
and opaque-counter models as an exactness improvement. The six fade comparison
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

The later [stored-contact reads](EXACT_REBOUND_STORED_CONTACT.md) close the
complete rebound. The rejected models below retain their historical results.

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

A later chained float expression reproduces all 681 original bytes privately,
including all fifty bindings. Its C++ form retains C exports and also matches
the three exact ball companions. C++17 sequencing is independently checked.
It is not adopted: GNU's debug x87 model fails the added 7/100 precision witness;
optimized x87 fails an existing later threshold; adding float-store fails the
first witness again. Existing passing samples do not resolve those failures.

An explicit four-byte contact object separates the rounded stored value from
the unrounded immediate result. Its `/Ob1` legacy output is 755/681 bytes with
681 differences; three companions preserve 965 bytes. Inlined arguments and
returns still spill through double slots and change the first comparison.
That shared value model also remains unselected. Keep these compiler and
precision controls in `.analysis/rebound-x87-expression-20261013/`,
`.analysis/rebound-x87-cpp-20261013/` and
`.analysis/rebound-contact-value-20261013/`; canonical rebound stays 687/681.

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

## Device and board surface calls

Two further owner projections use the shared stdcall surface class with
unchanged expressions and scopes. Device converts six calls and preserves all
six complete relocated code hashes: five exacts retain 808 bytes and palette
transition stays 1339 bytes with 18 differences. Boards converts two BltFast
calls and preserves all nine complete code hashes: seven exacts retain 2,154
bytes, while editor load/store stay 58 bytes with 23/42 differences against
52-byte originals. Neither projection is adopted. Complete private inputs and
comparisons are retained in `.analysis/device-surface-com-20261013/` and
`.analysis/boards-surface-com-20261013/`.

A separate C board-copy trial passes the address of the complete 400-byte tile
array to memmove instead of letting the array decay. This preserves the same
aggregate owner and overlapping-copy behavior. VC4 still emits the root load,
20032-byte offset addition and pointer push, where the original load pushes
`0x43F8F8` directly. All nine complete code hashes are unchanged, so the trial
is rejected. Original load evidence is
`ev_5aa7369fc6fd8a1333d312332d7a4e40977ab9fa76272a6e0dd9192277fe66d2`;
retain `.analysis/board-copy-object-address-20261013/`. These are three bounded
single-compilation trials with no canonical edits or gameplay runs. Their
completed source/header/object copies are gzip verified before cleanup.

## Shared clock types in the current surface context

The previous shared-timestamp model was retested against the current C++
surface owners. It uses the Win32 unsigned-long clock word and LONG counter
fields, closes clock return/elapsed/callback types, and retains the earlier
consumed grayscale conversion cursor. Current source and surface interfaces
are preserved in an isolated tree.

Thirty-one matching recipes compile once each. All 273 complete units are
compared: 236 accepted functions and 37 candidates, including actual bindings,
full literals and 136 metadata bytes. Rotation height (191 bytes) and waiting
(170 bytes) become private zero comparisons. Fourteen accepted functions lose
their match: MDS parsing, seven resource functions, bonus update, rectangle
collision, rotation offset/width, reduced sprite drawing and hit-region
initialization. Reset remains nonexact in this context. The private result is
224 functions / 55,994 bytes: **net −12 functions / −5,955 bytes**. The coherent
model is rejected after the complete family comparison. These private zeros
do not enter the accepted ledger.

Four initial comparator gaps involved reordered genuine global reads and
renumbered static data. They were resolved against the saved objects without
recompiling. An auxiliary allocator recipe has no claim units; its old object
identity and current source inventory do not imply known prior compiler inputs.
Canonical sources, objects and products remain unchanged. Retain
`.analysis/shared-timestamp-surface-20261013/` for the full frozen tree, compiler
receipts, source/caller proof and comparisons. No fixture or game run accompanies
this trial.

## PCX header lifetime and editor interface

The 128-byte PCX header, its byte pointer and read iterator are used only before
Lock. One private source stage gives those three locals a block containing the
unchanged header read and maxima extraction. It introduces no fields, padding
or buffer capacity. The complete body worsens from 979/862 with 851 differences
to 985/862 with 929, while all fourteen resource exacts retain 3,433 bytes.
Reject the stage. Original header consumers end at 0x409CAC; retained evidence
is `ev_93b5290136b33bfcc5cee2cc186d2f6440c5a8c1595647d46ec6172e7d5c8566`.
Complete inputs and comparisons are in `.analysis/pcx-header-read-phase-20261013/`.

An editor projection converts five surface calls to virtual stdcall dispatch
with preserved source expressions, scopes and C linkage. It gains no exact,
loses hit-region search (172/173 bytes, 132 differences), and leaves editor key
at 638/632 with 260 differences. Reject the projection; retain
`.analysis/editor-surface-com-20261013/`. Both owners are unchanged in canonical
source. Each trial compiles once; no fixtures or games run. Completed private
sources, headers and objects are gzip verified before cleanup.

## DirectDraw-only calls after palette integration

A separate class projection keeps the accepted surface and palette interfaces
and restores only IDirectDraw's 23 SDK slots. Four existing C++ calls change:
two surface creations and one palette creation in resources, and vertical-blank
waiting in display. The enum callback, HWND boundary and original three-argument
SetDisplayMode follow the installed SDK. No caps layout is inferred.

All 26 affected owners compile once, and all 253 complete affected units are
compared without unresolved mappings. The model gains no exact and loses seven:
keyed draw, keyed blit, stretch, ordinary blit, sprite release, reset and splash
palette pulse. Its net result is **−7 functions / −1,692 code bytes**. Reject it.
The three changed files reverse exactly to the previous source, and native C
and Win32 C preprocessing retain identical interface views. Complete source,
ABI, input and comparison receipts are in `.analysis/ddraw-only-com-20261013/`.
Canonical sources and products stay unchanged. Verified gzip cleanup of 144
completed carriers releases 483,328 allocated bytes including its receipt.

## Board byte-owner slice

One bounded copy-address stage replaces tile-array decay with the actual
whole-region byte pointer plus `offsetof(DxBallBoardStorage, tiles)` in both
editor memmove calls. Ownership, member layout, transfer size and overlapping
copy behavior are preserved. The compiler still emits a root load followed by
an offset addition. All nine complete code hashes are unchanged: seven exacts
retain 2,154 bytes; load/store remain 58/52 with 23/42 differences.

Reject the stage and retain `.analysis/board-copy-byte-slice-20261013/`.
The byte slice and the earlier complete-array address now both have complete
trial receipts; further cast/offset spelling changes have no new support.
No fixture, game, new provider session or online search runs. Completed private
source/header/object copies are gzip verified before cleanup.

## SDK counter and Kernel calls after palette integration

One API-only stage replaces the clock callback-cell calls with the actual
QueryPerformanceFrequency/Counter APIs. Windows uses SDK LARGE_INTEGER; the
native view keeps the same eight-byte LowPart/HighPart layout and forwards
through the existing live callback cells. The delta is limited to runtime.h,
clock_api.h, runtime.cpp and platform_host.c. Current restart, timestamp globals,
surface and palette code remain intact.

All 21 affected matching recipes compile once, and all 182 complete affected
units are compared. Effect blit (362 bytes) and effect drawing (361 bytes)
become private zero comparisons. Six accepted functions lose their match:
hit-region initialization/search, reduced blit/draw, splash palette pulsing
and high-score insertion. The net result is **−4 functions / −1,136 bytes**;
reject the stage. Current-time and reset remain exact. Effect stretch improves
to 306/306 with two differences, but no candidate is promoted from this model.

Actual stdcall import symbols are bound to independently verified named PE IAT
entries: frequency at 0x4412A0 and counter at 0x44129C. Complete source reversal,
caller/SDK contracts, compiler inputs and comparisons are retained in
`.analysis/sdk-counter-palette-20261013/`. No native, game or fixture run accompanies the trial.
Verified gzip cleanup of 123 completed carriers releases 397,312 allocated
bytes including its receipt; current sources and products remain untouched.

## Counter definition owned by the clock interface

A follow-up keeps the same actual Kernel calls but makes the counter opaque
in runtime.h. Only clock_api.h provides the complete SDK union or native
eight-byte structure. This confines the type definition to consumers that
need its value or fields; pointer-only consumers retain a forward declaration.
The four-file delta leaves the current restart and drawing code intact.

All 21 matching recipes compile once, and all 182 complete affected units are
compared. The two effect draw bodies match, while reduced blit, reduced draw
and splash palette pulsing lose their matches. The net result is
**−1 function / −370 code bytes**, so the model is rejected. Current-time and
reset remain exact; canonical state stays at 238 functions / 62,514 bytes.

Complete source reversal, native/Win32 header ownership, SDK/IAT contracts and
comparisons are retained in `.analysis/opaque-clock-owner-20261013/`.
Gzip-verified cleanup of 123 completed carriers releases 397,312 allocated
bytes including its receipt. No game or fixture runs accompany the trial.

## Rotation surface member calls

One rotation-owner projection replaces its six GetSurfaceDesc, Lock and Unlock
dispatches with members of the recovered surface interface. It preserves the
live receiver expressions, retries, result stores, locals and scopes. Project
headers retain C linkage; the standard library stays outside that enclosure.
No shared header changes.

All six complete functions are compared after one matching compilation.
There are no gains. Horizontal offset loses its 259-byte match at three
differences; three accepted companions retain 490 bytes. The renderer becomes
1,458/1,572 with 1,467 differences, and height remains 193/191 with 158.
Reject the projection and keep canonical sources and products unchanged.

Complete source reversal, unchanged header inputs, all 116 relocation bindings
and full literal-container identities are retained in
`.analysis/rotation-surface-com-20261013/`. Gzip-verified cleanup of thirteen
completed carriers releases 20,480 allocated bytes including its receipt.
No fixture or game runs accompany this trial.

## Implemented explosion traversal members

The original frame loads the explosion owner into ECX before begin, remove
and advance; the callees consume that object and return with plain RET.
One private model moves their complete implementations into the existing
list class. Three genuine C adapters forward to those methods for remaining
C consumers. Original entry bindings refer to the implemented members,
not the adapters. The frame and list cleanup call the members directly.

The core C++ projection also needs the previously tested surface Blt conversion
to use the current interface. Every receiver expression, list operation,
node deletion and local scope is preserved. No data layout changes.

Two matching compilations compare all 53 core and list-owner functions.
All 51 accepted exacts retain 9,027 bytes, including the implemented members
at 57, 89 and 220 bytes and list cleanup at 48. Neither candidate improves:
frame stays 1,691/1,688 with 1,155 differences, and brick dropping stays
436/426 with 306. The three embedded-owner address loads still use LEA.

The model is rejected without compiling the remaining header consumers.
This is a two-owner result; it makes no linked-product or broader caller
claim. Independent source and full comparison review agrees. Retain
`.analysis/explosion-traversal-members-20261013/` for implementations,
compiler inputs, actual member bindings and complete comparisons.
Gzip-verified cleanup of 32 completed carriers releases 110,592 allocated
bytes including its receipt; canonical products remain untouched.

## Complete explosion-list API and callers

The full model implements append, begin, advance, remove and clear as ordinary
members of the existing list class. Every game caller uses those definitions:
gameplay, effects, core, runtime and list cleanup. Five C adapters remain for
fixtures, with no original-entry bindings. Necessary C++ owner conversions
retain C API linkage and the current surface interface. List fields, constructor,
allocation, deletion and traversal operations stay unchanged.

All 28 affected recipes compile once, and all 259 complete units compare.
The five implemented methods stay exact. Effect blit becomes exact, but keyed
blit, glyph drawing, reset, reduced drawing and region restoration lose their
matches. The net result is **−4 functions / −1,775 code bytes**, so the model
is rejected. Frame, brick dropping, explosion queueing and total cleanup retain
their previous complete code identities.

Independent review verifies all six source reversals, actual member definitions,
caller bindings, compiler inputs and comparisons. Retain
`.analysis/explosion-list-api-20261013/`. Gzip-verified cleanup of 152 completed
carriers releases 491,520 allocated bytes including its receipt.

## Captured HRESULT values in current C++ owners

One stage gives all six stored DirectDraw results their actual HRESULT type:
capture and bank API workspaces, surface palette loading, PCX Lock, display Flip
and intro Lock. The existing alias supplies Windows LONG and native signed32.
Calls, expressions, declaration order, scopes and shared headers are unchanged.
This extends the earlier two-field C diagnostic to current C++ virtual calls.

Three matching compilations compare all 57 complete affected functions.
Every complete code identity is unchanged; 46 exacts preserve 13,914 bytes.
Reject the stage as an exactness improvement. Complete source reversals,
SDK contracts and independent review are in
`.analysis/hresult-local-captures-20261013/`. Verified gzip cleanup of 38
completed carriers releases 122,880 allocated bytes including its receipt.

## Scalar calculation and transfer lifetimes

The triangle's vertical-scale calculation writes one scalar before constructing
the long-edge expression, then never reads it. One computation-only block moves
that declaration beside the existing assignment. Four FixedPoint objects and
the scanline block remain intact. All twelve complete code identities and
metadata blocks stay unchanged, including triangle's 1,710 bytes, 88 differences
and exact 160-byte metadata. The scale home stays EBP−32 rather than original
EBP−28. Reject the stage; retain `.analysis/triangle-scale-lifetime-20261013/`.
Verified gzip cleanup of seven carriers releases 24,576 allocated bytes.

The bank's pitch, cursor, row and column have no consumer outside its existing
surface-transfer block. One stage moves their unchanged declaration into that
block, retaining the pitch snapshot before Lock and both upload loops.
After one compilation, all seventeen complete functions compare: fifteen exacts
preserve 3,572 bytes and sixteen code identities stay unchanged. Bank loading
worsens from 1,475/72 differences to 1,487/279, with 425 instructions in both.
Reject it and retain `.analysis/bank-transfer-scalars-20261013/`.
Verified gzip cleanup of eleven carriers releases 36,864 allocated bytes
including its receipt.

Both lifetime models have independent source and complete comparison reviews.
Canonical sources and products remain unchanged. No fixture or game runs
accompany these four trials.

## SDK types in the current Windows C view

Two header gates extend the existing HRESULT, DWORD, ULONG, LONG and RECT
declarations to Windows C consumers. C++ and native header branches remain
unchanged. Seven resource-inspector callbacks receive the corresponding SDK
return and argument types, with fixed32 native aliases and unchanged bodies.
This model uses the current surface and palette interfaces rather than the
earlier C-only SDK context.

All 28 affected recipes compile once; all 259 complete units compare.
Paddle positioning matches its complete 203 bytes. Five accepted functions
lose their matches: bonus update, rotation offset and width, bitmap loading
and hit-region initialization. The net result is **−4 functions / −3,606 bytes**,
so the model is rejected. All 128 code, literal and metadata identities across
the seven C++ owners remain unchanged.

Independent review verifies source reversals, callback contracts, actual SDK
declarations and all compiler receipts. Retain
`.analysis/sdk-c-view-current-20261013/`. Verified gzip cleanup of 150 completed
carriers releases 454,656 allocated bytes including its receipt; two complete
preprocessor carriers remain compressed. Canonical sources and products stay
unchanged.

## C++ paddle positioning with the actual cursor API

One isolated paddle projection preserves canonical SDK headers and replaces
the callback-cell call with the actual SetCursorPos import. Project declarations
retain C linkage. The native API forwarder calls the existing live callback;
the Windows call follows the SDK BOOL/stdcall/int-coordinate contract.
All arithmetic, guards, global writes and the callback export remain intact.

One matching compilation compares all 203 bytes and twenty actual bindings.
The complete relocated code identity is unchanged, with four differences.
The real USER32 import is independently bound to named IAT entry 0x441350.
Reject the one-owner trial without compiling other header consumers. Retain
`.analysis/paddle-win32-cpp-20261013/` for complete source reversal, API/native
contracts, separate uncompiled source closures and independent review.
Verified gzip cleanup of 29 carriers releases 16,384 allocated bytes including
its receipt. Neither of these trials runs a fixture or game.

## Motion API dependency boundary

Paddle declarations need only fixed32 integers and the platform calling
convention. One private model extracts the unchanged convention macro into
platform_abi.h, consumed by resources and paddle. Paddle no longer includes
the resource interface; its C++ implementation privately includes the genuine
Windows API for SetCursorPos. Other existing callers retain their independent
resource dependencies. No SDK interface view or executable expression changes.

The single matching compilation has four actual project inputs. Its complete
203-byte function and twenty bindings retain the same code identity and four
differences. Reject the pilot without compiling the remaining header consumers.
Independent review verifies the macro identity, source reversal, dependency
routes, real import and native callback bridge. Retain
`.analysis/paddle-input-boundary-20261013/`. Gzip-verified cleanup of thirty
completed carriers releases 12,288 allocated bytes including its receipt.
Canonical sources and products remain unchanged; no fixture or game runs.

## UI surface and palette member calls together

One private C++ UI model converts four surface calls and both palette calls
through the current shared interfaces. The preceding surface-only model still
used manual palette dispatch. Project declarations retain C linkage; the
existing color-fill payload passes at the same address through the opaque
SDK argument type. All thirteen project headers, executable arguments, local
types, scopes and writes remain unchanged.

One matching compilation compares all nine complete functions and 38 actual
relocations. There are no gains. Draw-text loses its 150-byte match, with three
differences; five accepted companions preserve 597 bytes. Right palette
rotation becomes 234/9 differences, measurement 280/279 bytes with 55
differences, and line drawing retains its complete preceding code identity.
Reject the model. Independent source, ABI, input and comparison proofs are in
`.analysis/ui-all-com-20261013/`. Eighteen gzip-verified carriers release
8,192 allocated bytes including the cleanup receipt. Canonical remains
238 exact functions / 62,514 bytes; no fixture or game runs.
