# Editor controller evidence

REA 4.1.0 with Ghidra 12.1.4 follows mode 2 through initialization, redraw,
mouse painting, key commands and cleanup, then into its toolbar hit regions.
Ten maintained entries reuse the existing board-bank, tile mapping, rendering,
UI, dirty-region, palette and clock owners. All five mode controllers now have
source defaults. Actual Windows/audio/MIDI delivery and a playable EXE remain
pending.

## Entries and retained observations

| Address | Maintained entry | Owned/span bytes | REA Evidence ID |
| --- | --- | ---: | --- |
| `0x0040C1A0` | `initialize_editor` | 263/263 | `ev_9811081f6d6d1f2204b198cd34ee1b421fe72b0d249a4372fa80a6a93ca3e8e1` |
| `0x0040C2B0` | `redraw_editor` | 252/252 | `ev_1976120e8d242c0582fd80747e4b120df885c94be7db9f231b5b9dd98d593009` |
| `0x0040C3B0` | `editor_frame` | 908/908 | `ev_12f27f7831f215d80c2a1a27d88e1638ffa9ab2fd568793f66258b328927431e` |
| `0x0040C740` | `editor_key` | 362/632 | `ev_c3b032921ff367662243437140e61960889bc020f84de66d663fcd0d86c2cc17` |
| `0x0040CF20` | `dispose_editor` | 78/78 | `ev_17b4b43767031f638f192df04ea596fd41e851c49a4e47cd4eb25d36b3ae8b87` |
| `0x0040C9C0` | `draw_editor_choices` | 163/163 | `ev_cb841f57985bd317bc65c2afc1fac963232011a2ad093fcd2e1790a944019088` |
| `0x0040CA70` | `draw_editor_status` | 431/431 | `ev_9dbf933b2d5fd904d65e26784bd95865202411ab4c95711d72b9ec72adf0bdfe` |
| `0x00401E10` | `initialize_hit_regions` | 147/147 | `ev_2797cbe8ffc3201146f6835ba0855cabeb3ccbad0d73961cce83fdc2f7c997aa` |
| `0x00401EB0` | `set_hit_region` | 97/97 | `ev_5eaf4df89184d5cd2372ce07008f453d3320f40a61205fdbfa5c79538fe2b180` |
| `0x00401F90` | `find_hit_region` | 173/173 | `ev_a59b234e495b19e155577097063cb2985bb4c4d5ac3e6741d0b331fd292453dd` |

The key controller owns three inclusive ranges: `0x40C740..0x40C87C`,
`0x40C882..0x40C8A4`, and `0x40C9AE..0x40C9B7`. Embedded switch tables are
excluded from owned instructions. Imported candidate spans match the reviewed
REA spans. Static observations retain prototype and indirect-flow limitations;
independent original execution establishes the accepted behavior.

One constrained interactive session retained ten dossiers and three data
reads. Open took 16.9 seconds; lazy first analysis took 40.6 seconds; subsequent
dossiers took 0.02..0.32 seconds. Explicit close saved 224 cumulative Evidence
records. Complete results survive in the closed 14-34 private archive.

## Shared state and region ownership

`src/editor.c` owns a 100-record hit-region array at `0x4251A0`, count at
`0x421064`, and DWORD selected tile at `0x438AF0`. Each region has five signed
32-bit fields: left, top, right, bottom and active. The 2,000-byte array ends
at the existing clock divisor `0x425970`; the divisor is separate storage.
Selected tile is not a new byte-sized alias: original paint stores only its
low byte into a board cell. Initial image data and retained reads establish
zero defaults:

- Count/adjacent clock-mode read: `ev_e22f58330188e8269458c1004de1d55c0440a3e78f582a9c36002b1a87c34cf8`.
- Selected DWORD read: `ev_197db226cea3569134ecc711fcf3694e74f4777536907538b702b924f228702c`.
- Complete region array read: `ev_0583e9e557b3b76d512371f61c807c3b7a2b4dd385599bb559417480701fc333`.

Region initialization stores argument + 1, then clears indices zero through
that stored count inclusive. The editor passes 23, storing 24 and clearing
25 records. Tested arguments are -2, -1, 0, 1, 23, 50 and 98; argument 99
would reach adjacent original storage and is outside the portable claim.
The setter supports indices 0..99. Lookup checks indices 1 through count - 1,
accepts any nonzero active flag and includes all four rectangle edges. It keeps
the highest matching index. Count 0/1 yields no hit; index zero is ignored.

Board index, the 50-board bank, 400 working tiles, auxiliary cells, FILE slot,
mouse/control input and menu cursor coordinates reuse existing owners. Existing
board read/write/load/store bodies are dependencies, not new function claims.

## Lifecycle, toolbar and mouse

Initialization resets regions, clears and loads `mbbkgrnd.pcx`, then loads
`mball2.sbk`, `sfont.sbk`, and `mainmenu.sbk` into banks 0/1/2. It selects
sprite bank 0 and font bank 1, binds board and display surfaces, selects tile 1,
initializes regions, loads board zero, redraws and fades in. There is no editor
music-load call. Redraw copies the background to the board, draws actual board
tiles, choices and status, then copies to primary and, for draw-to-primary zero,
secondary. Cleanup with fade zero does nothing; otherwise it fades out, clears
only primary and releases sprite banks, sounds and music.

Choices draw mapped tiles 1..22 starting at (20,385), stepping X by 32 and
wrapping after X > 280 with Y + 17. Hit rectangles extend by 30 and 15. Status
draws the mapped selected tile at (25,5); tile zero restores that preview from
background. It restores the board-number label, formats index + 1 and draws
six original instruction strings with their exact explicit character counts.

Each frame waits only for nonzero draw-to-primary, restores regions, clamps
shared cursor X to 8..599 and Y only at its upper bound 447. Bank 2 draws cursor
sprite 4 outside toolbar regions or 6 on a hit; sprite bank returns to zero.
Presentation occurs only for draw-to-primary zero, before click processing.

Inside strict board bounds `20 < x < 620`, `50 < y < 350`, left action 1
paints the selected low byte; right action 2 paints zero. Coordinates map to
20x20 cells, followed by actual tile drawing and immediate store into the
current bank slot. Outside the board, left clicks choose a hit region, draw
status and invalidate `(0,0,639,49)` through original `0x408B70`. They do not
perform an immediate surface copy. Control zero clears a handled action;
any nonzero Control value retains it for following frames. Other actions stay
unchanged.

## Key commands and persistence

The signed-char entry recognizes all original virtual-key bytes. Backspace
clears only working tiles and redraws; it does not immediately store the bank.
L reads `default.bds`, selects board zero, loads and redraws. S stores the
current working board, writes the whole bank, then closes. Plus/minus first
store the old board, increment/decrement and clamp to 0..49, then load and
redraw. Store-before-clamp remains observable at both ends of the bank.
Many F-key and other switch branches are real no-ops. Escape belongs to the
existing window procedure, which requests menu return; no extra editor key
action is invented.

Native board I/O uses actual host stdio in an isolated temporary directory.
Original board bodies execute unchanged with controlled CRT file APIs and an
independent in-memory file dictionary. The two sides compare the full file,
bank and working tiles without allowing either side to overwrite the other's
output. Missing/empty/short/full reads and failed write-open are covered. A
directory fixture causes host write-open failure; read-open failure uses a
missing file. The shared FILE slot retains its original closed nonnull role.

## Validation and limits

`tests/test_editor_differential.py` passes **2,921 direct cases** across all ten unmodified entries:
initialization 6, redraw 32, frame 1,272, key 1,039, cleanup 16, choices 3,
status 46, region initialization 7, setter 100 and lookup 400. Coverage includes
complete 100-record tables with poison/canaries, inclusive/overlap lookup,
every key byte at four board indices, every board cell for paint and erase,
toolbar edges/gaps, selected-DWORD truncation, Control gates, palette/surface
flags and independent board-file outcomes. It compares complete board, region,
palette, controlled pixel and dirty arrays, bank metadata, globals and ordered
rendering effects. Text placement is checked; hardware glyph/blit pixels are
not claimed.

Another **32 checks are separate connected evidence**. They enter through actual menu Control-F1 and
mode dispatch, select a tile, hold Control across painting frames, switch/save/
clear/reload boards, return through actual Escape/window/frame routing, and
start actual game mode 1. Production mode/key defaults are checked before
harness bindings.

Valid finite scripts, initialized surfaces, bounded storage/arithmetic, mapped
tiles 0..22 and board indices 0..49 are required. Resource lifecycle reload/
release, audio/MIDI and actual Windows/DirectDraw delivery remain controlled
boundaries. This family makes no new exact or playable-EXE claim. The existing
forty configured exact units are replayed together at the stable checkpoint.
Every earlier suite, native/MinGW/VC4 product, Wine inspector and saved REA
verification runs at the same grouped checkpoint. The new-family report is
reused only with identical complete inputs and native library; private reports,
input identities and logs are retained in `.analysis/checkpoints/editor-186-40/`.


## Compiler portability follow-up

Public CI with GCC 13.3 rejects an eight-byte decimal scratch buffer under
`-Werror=format-overflow`: the compiler cannot infer the accepted 0..49 board
index domain from the external global. The shared owner now reserves 12 bytes
for a signed 32-bit decimal value, sign and NUL. It retains the original
index-plus-one formatting and draw calls; no clamp or profile-selected body
is introduced. This affects a temporary buffer, with no new exactness claim.
Existing original-x86 status/editor and complete regression suites are replayed
against the GCC 13 native library, plus MinGW/VC4 products and forty exact units.
The failed remote run and final input identities are retained under
`.analysis/checkpoints/editor-format-199-40/`.
