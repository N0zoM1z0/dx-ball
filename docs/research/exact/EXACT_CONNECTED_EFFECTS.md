# Connected brick-drop and fire-effect source restoration

This batch restores four complete observed function bodies from retained full
REA dossiers: brick dropping (426 original bytes), fire-effect allocation and
clamping (185), fire-effect iteration (124), and rectangle invalidation (336).
Their combined original extent is 1,071 bytes. Each saved body is contiguous
through its plain return. Original source spelling and declaration order remain
unproven. New original decoding was unnecessary; the hash-pinned executable and
retained primary records supply the evidence.

| Original entry | Maintained unit | Original bytes | Retained REA Evidence |
| --- | --- | ---: | --- |
| `0x415670` | drop-bricks | 426 | `ev_8602dd7fec1b8aff85a2c581b96d7a85bcf62a791d3741ecaecd0c5a411812fc` |
| `0x4135B0` | spawn-fire-effect | 185 | `ev_875ff3c542a834d79e1f45f8f9b68dd1ae6e354b32f2a0de4300bb862819716e` |
| `0x413710` | process-fire-effects | 124 | `ev_9e33b3e41981c17ce9b99bb5029edf970e747c87fe3c82b3d6bcc19d45443a84` |
| `0x408B70` | invalidate-region | 336 | `ev_083f7fc0ed9267a7d842e615acbda8b8257ad96982463a4c2cae58bdca37dfec` |

## Source and rectangle ownership

Brick dropping consumes two signed byte pointers for the current and next row,
separate movement and redraw loop counters, a moved flag and a real local RECT.
It calls the actual sound entries, reads the board surface afresh for both the
COM receiver and vtable, redraws occupied cells, and directly invalidates the
rectangle. Its 44-byte local frame accounts for consumed values only. The
shared BoardStorage member remains the owner of the tile array. VC4 currently
emits two additional member-offset additions and different local homes; the
whole 436-byte emission against the 426-byte original stays a nonexact candidate.
No padding, fake local, alternate layout, copied instruction or name/order
search is used to eliminate these differences.

Invalidation takes a rectangle by value and copies that aggregate into the
current dirty page, conditionally the opposite page, and conditionally the
present queue. Capacities are 1,000 and 2,000. The callee addresses the incoming
16-byte stack object directly and has no local frame or helper calls. Independent
brick-drop and score-drawing callers push an existing local RECT's four fields
and clean 16 stack bytes. Together these support the aggregate interface; caller
bytes alone also permit four scalar formals and do not prove original names.
The shared header, RenderOps callback type and six maintained invalidate calls
use the coherent rectangle type. Native aggregate calling convention differs
from i686, so ctypes constructs a real Rect value at that boundary.

The game-over frame's complete saved dossier instead calls `queue_region` at
`0x408990`. The previous invalidator call is corrected to that genuine owner.
This is separate from the six invalidator callers and adds no exact game-over
claim. Score drawing is a semantic companion; the accepted 74-byte refresh-score
wrapper remains a separate function.

Fire allocation retains fresh list-current reads and the observed clamping.
Fire processing directly calls `draw_effect_sprite`, increments ticks, removes
at ticks >=22 and advances the list, preserving the complete return paths.

## Exact accounting and verification scope

The sole grouped cold compilation produces 22 actual objects. Complete COFF
comparisons accept spawn-fire-effect, process-fire-effects and invalidate-region:
645 code bytes with every relocation. Shared API/body translation context also
changes seven previously exact emissions; the API alone was not isolated as the
cause. Historical zero objects remain in the parent checkpoint.

| Current nonexact unit | Original / emitted bytes | Whole byte differences |
| --- | ---: | ---: |
| blt-effect-sprite | 362 / 366 | 332 |
| blt-reduced-sprite | 362 / 366 | 332 |
| stretch-effect-sprite | 306 / 308 | 252 |
| queue-sprite-region | 272 / 274 | 245 |
| draw-reduced-sprite | 361 / 365 | 330 |
| blt-sprite | 195 / 199 | 173 |
| rotated-sprite-y-offset | 191 / 193 | 159 |

These seven demotions remove 2,049 prior exact code bytes. The same actual cold
products naturally recover two existing candidates, without source trials:
139-byte keyed stretch (six relocations) and 191-byte rotated height (ten).
Height's 186 owned bytes and the intervening five-byte branch at 0x40305B are
reconciled through the retained explicit read-bytes Evidence; all 191 bytes are
compared. No unowned gap, padding or masking is accepted without evidence.

The final ledger is **99 exact units / 11,474 code bytes + 136 separate metadata
bytes**: 101 prior units minus seven, plus three new and two recovered units.
All 94 surviving complete code/metadata identities remain unchanged. The net
exact count falls by two and code bytes by 1,074. Actual cold objects, original
99-unit diagnostic manifest, amended 97-unit report and final 99-unit report
are retained distinctly. Literal ordinal repairs attest complete constant
contents and actual relocation order/type/addend; they do not recompile code.
The final two promotions change ledger grouping only.

The native test shim additionally forwards the real invalidation and effect-draw
symbols through the copied image's current RenderOps and FrameOps tables. Its
bindings occur after fixture callbacks are installed, verify table/real-function
ownership, and reject null, self and recursive bindings. Display owners can
rebind tables to real functions from their explicit copied-image handle. Fresh
canonical default audits retain their separate LOCAL image. This host boundary
does not validate physical DirectDraw or sound hardware. Production sources use
one body and one layout for native, MinGW and VC4.

Existing owner matrices and case counts are preserved. Private aggregate-ABI
observations add no tracked direct acceptance. All 22 owner scripts pass against 283 frozen inputs in 432.867 seconds. The
sole cold epoch, 14 existing rejection controls, strict MinGW and full VC4
builds pass. All 1,024 affected rotation COFF vectors were rerun before the
identity-only final promotions; unchanged 7,164 raster COFF vectors reuse
verified inputs, recipes and logs. No new target cases or campaigns are added. Source-present, authored, direct semantic and exact
counts remain separate. The >=95% complete-source objective remains open.
