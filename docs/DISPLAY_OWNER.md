# Lightning and frame drawing

This batch follows three connected bosses through REA: last-brick logic
`0x415F40` (1,057 bytes), dirty-region restoration `0x408CC0` (827 bytes), and
sort/merge/presentation `0x409100` (984 bytes). Required enqueue, sprite, palette,
wait and flip operations connect these bodies to the gameplay frame. Independent
leaf tuning is deferred; helper functions receive no separate target claims.

Sixteen maintained entries pass 2,409 direct original-x86 cases. Another 192
continuous frames execute ALL twelve maintained gameplay phases across both
presentation modes, clipping and vertical-blank choices. These integration
frames are recorded SEPARATELY, not added to the direct-case count. Current
acceptance at this checkpoint was 117 functions and 69,813 direct cases; 40 exact functions /4,079
bytes remain unchanged. Windows/input/device, audio, glyph UI and non-game modes
still need implementation before a playable reconstruction is established.

## Entry evidence

Sixteen complete dossiers were collected in one pinned REA MCP/Ghidra session.
The first lazy query took about 56 seconds; subsequent queries reused the same
imported program. Explicit close saved 137 Evidence records /zero primitive
cache entries. All raw instructions, pseudocode and body-range Evidence remain
private under `.analysis/rea/runs/2026-10-07T09-29-28.570Z-interactive-2776129/`.
The table retains owned versus enclosing spans, even where they agree.

| Entry | Maintained function | Owned / span bytes | Direct cases | REA Evidence ID |
| --- | --- | ---: | ---: | --- |
| `0x00408070` | `dxball_reset_regions` | 267 / 267 | 1 | `ev_7fa4a6f3aca679c5c635db0c51c110bfda08836742abef83dc71b0f1ee1d1d34` |
| `0x004082F0` | `dxball_draw_effect_sprite` | 361 / 361 | 486 | `ev_487082b99cefd00540229ea43622fc5d56457b98c9b8f434f0002afa9227cb0b` |
| `0x004085D0` | `dxball_draw_reduced_sprite` | 361 / 361 | 486 | `ev_bde5005e002236529be930995e10017c75e10aad8e724216cbac463f299af083` |
| `0x00408990` | `dxball_queue_region` | 183 / 183 | 216 | `ev_8c8db0719620a4407f7ec289f38393456217a8f65ee947c84e20cf80f46b627c` |
| `0x00408A50` | `dxball_restore_effect_region` | 281 / 281 | 216 | `ev_28f895bfecc1cab9128bfbf634996e85c59e059ed77b0a81b83d293466ad9603` |
| `0x00408B70` | `dxball_invalidate_region` | 336 / 336 | 216 | `ev_083f7fc0ed9267a7d842e615acbda8b8257ad96982463a4c2cae58bdca37dfec` |
| `0x00408CC0` | `dxball_restore_regions` | 827 / 827 | 54 | `ev_2d9050e4b74d2fcb39692d85337c3a372235cd44f4cf5d22ee74c047bb4c3f76` |
| `0x00409000` | `dxball_bind_board_surface` | 24 / 24 | 2 | `ev_793213d9624462f067cc47da086586081b3930aeda1fdcb6bd960c76c67f27ab` |
| `0x00409020` | `dxball_bind_display_surface` | 24 / 24 | 2 | `ev_00b16a611bc5e4f266b1e88706440b0a105d15aae971652ef533c26512984fd7` |
| `0x00409040` | `dxball_present` | 180 / 180 | 60 | `ev_fcc3a545dae1d448edd6d472e4a638685b211cd3a231c967d9837b585b0f4692` |
| `0x00409100` | `dxball_present_regions_now` | 984 / 984 | 146 | `ev_ca79613a0bb131922a4f6c409b62ad80fbc94bc7bfc427358457a912a2e388e3` |
| `0x004094E0` | `dxball_sort_present_regions` | 296 / 296 | 60 | `ev_6fa464860fec11c6c9b89b25ac22ba8445585a8dba2390986ff40878fc054f10` |
| `0x00409610` | `dxball_wait_frames` | 170 / 170 | 18 | `ev_86e83ae4d777813cd233a8b5c9d0f3ccf67349f7605b270938902c442f023087` |
| `0x0040A970` | `dxball_animate_palette` | 234 / 234 | 81 | `ev_a5263d59f79fee20c3d1c580888f256c258a6bb80332e83da49071d7e3048e9a` |
| `0x00415F40` | `dxball_last_brick` | 1057 / 1057 | 198 | `ev_f8610be2baa2323aec8fcd14317794aebe74eefa78b4d66c9cf874ca117eb5bc` |
| `0x00416370` | `dxball_draw_last_brick` | 186 / 186 | 167 | `ev_63003d5621ef73504e785882f80a70043ccee9a339118544b722116d679ac13d` |

## Last-brick countdown and lightning

A zero deadline first samples raw WinMM time, consumes RNG(20000), and adds
40,000. A SECOND raw-time sample is subtracted with 32-bit wrapping and viewed
as signed. Positive time updates sound 21 with negative volume derived from
half the remaining milliseconds, a minimum of three, then division by three.
Expiry stops sound 21 and plays sound 22 before scanning the board column-first.
The LAST tile whose value is neither zero nor two wins if several are present.
Defined scope requires an eligible tile; the original otherwise uses
uninitialized coordinates, and maintained source rejects that invalid state.

Expiry calls the existing request producer `dxball_queue_explosion_at`, not the
animation constructor. This preserves deferred application at the END of the
frame and avoids premature auxiliary-grid mutation. Fire is created immediately.
Thirty particles (fifteen when the graphics flag is nonzero) consume RNG in dy,
dx, Y, X order, retaining color 16 and gravity one. Bank 2 /sprite 1 supplies the
lightning dimensions. Left/top cropping sets source offsets; right/bottom use
639/479 rather than the rectangle engine's 640/480 limits. The overlay retains
four frames, clears its deadline and restores bank zero. Each overlay BltFast
queues right/bottom using the source rectangle's right/bottom values; it does
not subtract the left/top crop offsets.

## Dirty pages and presentation

`0x4305E8` holds 1,000 interleaved pairs of rectangles, one per page. Separate
counts live at `0x4305E0`; the current page is `0x4382EC`. `0x426990` is the
2,000-entry presentation list; its count is `0x4305D8`. Source uses natural arrays
with the same scalar layout. Queue saturation preserves existing records.
Region reset clears both rectangle arrays and counts, but does NOT clear the
separate presentation-sort keys.

Queueing a particle/overlay rectangle updates only the current dirty page.
Invalidating a changed board region may also update the other page when drawing
to secondary with display buffers and full graphics. Immediate effect-region
restoration performs Blt first, then queues only the OTHER dirty page where
eligible. Sprite helpers always draw using their own source rectangles before
queueing full width/height bounds. The graphics flag equals ONE adds a rectangle
to the presentation list; other nonzero values do not. This same flag was
previously named reduced_particles from its particle-count consumer; the name
is retained, with its additional graphics/presentation roles documented here.

Restoration uses the current page. Clip mode equals ONE selects Blt, retaining
inclusive visibility checks at 640/480 and clipping the stored rectangle in
place. Other values select BltFast with no explicit clipping. Restored records
may be appended to the presentation list, then only the current count is reset.

Presentation computes signed left+top keys and uses the original selection
sort, including tie/swap order. It compares each rectangle to the current merged
rectangle using the maintained overlap routine; current right/bottom receive
+1. Overlap expands the current rectangle and marks the later top as 9999.
Keys are not recomputed after merging. Eligible records are copied from secondary
to primary with Blt; optional clipping mutates those stored records. The count
is finally reset. This is the original sequential merge, not an invented global
union or replacement sort.

Full graphics calls primary Flip. BUSY (0x8876021C) retries; SURFACELOST
(0x887601C2) calls recovery and exits the retry loop. That operation now defaults
to maintained source in the subsequent [device owner](DEVICE_OWNER.md).
Only success toggles the dirty page. Software wait is performed after successful
flip only when vertical-blank mode is off. Nonzero graphics mode instead waits
one frame and executes actual dirty-region presentation.

## Corrected wait and buffer labels

REA's instructions establish that `0x409610` waits frames, correcting the former
restore_surfaces callback label. Its nonzero vertical-blank flag calls DirectDraw
WaitForVerticalBlank (slot 22 /0x58) once per frame. Otherwise it repeatedly
executes the maintained clock until unsigned wrap or the 17-ms threshold, then
samples time AGAIN for its stored tick. Negative/zero frame counts perform no
API work. Known Flip and wait signatures are declared in the shared COM header,
corroborated against the installed MinGW DirectDraw header.

Global `0x4228D0` is now named draw_to_primary. Initialization binds primary
when it is nonzero and secondary otherwise; the frame then waits before drawing
and skips Flip when drawing to primary. Cross-page invalidation follows the same
flag. This replaces the earlier restore_before_frame interpretation without
changing the observed bits or branches.

Palette animation is suppressed only when the cursor-warp flag equals ONE.
Entries in [first,last) move as complete RGBA/flag records. The last RGB receives
the first RGB for rotate==1, otherwise black; the last FLAGS remain in place.
The inclusive range is then passed to real SetEntries dispatch. Palette driver
behavior itself remains a controlled API boundary.

## Connected source and oracle scope

All twelve `dxball_frame_ops` phases now default to maintained bodies. Board
sprite drawing, restoration and invalidation, effect sprite/region operations,
particle region queueing, and runtime reset/bind operations also default to
maintained source. `dxball_restore_board_region` is a necessary portable COM
bridge with no independent original-entry claim. Driver calls are configured
explicitly; their traces do not establish hardware rasterization or display.

`tests/test_display_differential.py` removes the prior original-entry hooks for
these phases and their render/region helpers. It executes unmodified original
lightning, sort/merge, dirty arrays, palette, wait and presentation bodies, plus
real physics, resources' sprite routines, animation and particle code in
continuous frames. Comparison covers every byte of dirty/presentation/key arrays,
lightning rectangle, palettes, tile/aux and particle buffers, surface/bank roles,
phase-entry globals, ordered COM calls, typed queues/cursors/payloads, allocation
ownership, poisoned freed storage, stack and callee-saved registers.

COM callbacks report results and provide one declared controlled particle storage
buffer for board/primary/secondary roles on both sides; they do not implement
Blt copies, Flip or palette hardware. Audio update/recovery, lifecycle resource
loads, glyph text, device setup and other modes remain controlled. Clock mocks
advance or follow a finite script. Native callback errors fail immediately;
they cannot accumulate error traces inside a retry loop. The original execution
budget is ten million instructions per call, sufficient for a full-board redraw's
quadratic rectangle sort while still detecting nontermination.

Input scopes require page 0/1, counts in [0,1000] /[0,2000], valid sprite records,
live queue cursors, bounded defined arithmetic, palette ranges 0<=first<=last<=255,
finite API retry scripts and progressing clocks. Tests cover capacity boundaries,
all queue modes, clipping edges, arbitrary sort keys/ties, randomized region
merges through 128 entries, clock wrap/waits, error/retry paths, lightning edge
cropping, signed countdown differences and 192 connected frames. They do not
claim driver pixel equivalence or execution of an arbitrary 2,000-rectangle sort.

This shared-header/source change receives ONE grouped cold replay of all forty
accepted exact units, all earlier differential suites, native/MinGW/VC4 builds,
Wine inspector comparisons, oracle rejections and saved REA verification. The
board read/write literals changed internal COFF names to $SG733 /$SG737; both
object and original target bytes were checked as rb\0 /wb\0 before updating
explicit relocation bindings. No offsets, addends, bytes or comparison rules
were relaxed. No new exact unit is claimed. Complete semantic inputs now bind
all maintained sources and headers; exact inputs include the full shared-header
closure. Private checkpoint reports are retained under
`.analysis/checkpoints/display-117-40/`.

## Next work

Surface recovery and palette fades are connected by the subsequent
[device owner](DEVICE_OWNER.md). Connect window/input/display startup and device creation, then
mode-3 game-over UI and audio. The frame algorithms are maintained, but the
configured driver/resource/UI boundaries still separate these libraries from a
playable whole-game executable. Independent leaf matching remains secondary.

```bash
scripts/repo-python tests/test_display_differential.py
scripts/repo-python scripts/ci.py
```
