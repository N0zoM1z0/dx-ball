# Remaining exact functions

All 41 authored candidates were compared against the complete original extents
on October 13, 2026. Current compiler inputs and objects match their receipts.
Every relocation, declared literal and attached metadata block is included.
None of these candidates is already exact. The accepted total remains
**232 functions / 59,486 code bytes / 136 metadata bytes**.

| Function | Original bytes | Current bytes | Differing positions |
| --- | ---: | ---: | ---: |
| `present-regions-now` | 984 | 984 | 2 |
| `elapsed` | 81 | 81 | 3 |
| `measure-text` | 279 | 279 | 3 |
| `update-scroller` | 233 | 233 | 3 |
| `update-paddle-position` | 203 | 203 | 4 |
| `rotate-palette-right` | 234 | 234 | 6 |
| `animate-palette` | 234 | 234 | 6 |
| `refresh-score` | 74 | 74 | 6 |
| `draw-line` | 445 | 445 | 9 |
| `palette-transition` | 1339 | 1339 | 18 |
| `reset-round` | 426 | 426 | 20 |
| `draw-score` | 433 | 433 | 21 |
| `load-editor-board` | 52 | 58 | 23 |
| `store-editor-board` | 52 | 58 | 42 |
| `queue-explosion-at` | 99 | 100 | 51 |
| `clear-all-entities` | 106 | 107 | 59 |
| `load-sprite-bank` | 1475 | 1475 | 72 |
| `fill-triangle` | 1710 | 1710 | 88 |
| `draw-paddle` | 677 | 677 | 104 |
| `rotated-sprite-height` | 191 | 193 | 158 |
| `blt-sprite` | 195 | 199 | 173 |
| `fill-polygon-clipped` | 1592 | 1592 | 210 |
| `fill-polygon` | 1543 | 1543 | 211 |
| `queue-sprite-region` | 272 | 274 | 245 |
| `stretch-effect-sprite` | 306 | 308 | 252 |
| `draw-glyph` | 328 | 332 | 258 |
| `editor-key` | 632 | 638 | 260 |
| `drop-bricks` | 426 | 436 | 306 |
| `draw-high-scores` | 404 | 403 | 330 |
| `draw-effect-sprite` | 361 | 365 | 330 |
| `draw-reduced-sprite` | 361 | 365 | 330 |
| `blt-reduced-sprite` | 362 | 366 | 332 |
| `hit-board-tile` | 1315 | 1316 | 418 |
| `bounce-ball-from-paddle` | 681 | 687 | 550 |
| `redraw-intro` | 587 | 578 | 560 |
| `capture-sprite` | 852 | 864 | 726 |
| `restore-regions` | 827 | 846 | 746 |
| `load-pcx` | 862 | 979 | 851 |
| `last-brick` | 1057 | 1067 | 992 |
| `game-frame` | 1688 | 1691 | 1155 |
| `render-rotated-sprite` | 1572 | 1466 | 1466 |

Differences are raw byte positions after genuine relocation resolution, not
a count of missing operations. Different instruction lengths move later bytes.
The matching recipes and target addresses are in `config/match-units.toml`;
each candidate links its retained research evidence there.

The latest rotation expression, axis-cursor and sampled-plane records are
rejected: they leave the renderer nonexact and lose two accepted projection
bodies. Floating consistency also leaves it nonexact. C++ rectangle passing
retains the extra instruction in explosion cleanup; both direct cursor-import
contexts leave four paddle-position differences. See
[closed diagnostics](CLOSED_STORAGE_DIAGNOSTICS.md#rotation-and-value-copy-follow-up).

The latest [polygon workspace](POLYGON_SCAN_WORKSPACE.md) reduces the two
polygon comparisons while preserving all accepted raster functions. The three
raster candidates above reflect that verified checkpoint. The original EXE has
no COFF symbols or debug directory.
The verified original game archive contains 51 files, with no source, PDB,
object files or linker map. Its inventory is retained in
`.analysis/exact-input-frontier-20261013/audit.json`; no online search runs.

The [explosion cleanup scope](EXACT_EXPLOSION_CLEANUP_SCOPE.md) promotes its
797-byte controller; the [secondary-width scope](EXACT_OVERLAP_SECONDARY_WIDTH.md)
promotes the 329-byte overlap. The [triangle scanline scope](TRIANGLE_SCANLINE_SCOPE.md)
reduces its differences from 107 to 88. The latest
[intro point phases](EXACT_INTRO_POINT_PHASES.md) promote the 711-byte update.
The [capture allocation phases](CAPTURE_ALLOCATION_PHASES.md) reduce its
comparison from 803 to 745 differences. The latest
[API workspace](CAPTURE_API_WORKSPACE.md) restores the remaining frame homes
and reduces differences to 726; the other 40 candidate hashes are unchanged.

The [sprite-bank API workspace](BANK_API_WORKSPACE.md) restores the complete
1475-byte loader size and reduces its comparison from 1577 to 76 differences,
while preserving all 12 resource exacts.

The later [upload-pointer workspace](BANK_TRANSFER_WORKSPACE.md) restores the
pixel pointer's original EBP-68 home and reduces that comparison to 74
differences. The descriptor and result homes remain exact; the loader is still
a candidate.

The [standalone color-key phase](BANK_COLOR_KEY_PHASE.md) restores EBP-64 and
brings the bank comparison to 72 differences. It preserves glyph search,
which the earlier key-as-record-field model lost.

The [intro score phase](INTRO_SCORE_PHASE.md) restores rectangle and text-length
homes while keeping the buffers unchanged. Redraw remains 578/587 with 560
differences; the change preserves every accepted intro body.

The [rotation visible-pixel scope](ROTATION_VISIBLE_PIXEL_PHASE.md) brings its
comparison to 1466/1572 with 1466 differences while preserving all four accepted
rotation functions. The frame and instruction count stay unchanged; the local
homes still differ from the original.

Private complete comparison: `.analysis/exact-candidate-audit-20261012/comparison.json`.
No new game, fixture or provider session accompanies this audit.
