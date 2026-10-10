# Menu and splash evidence

The subsequent [complete intro source batch](EXACT_INTRO.md) restores initialization,
redraw, point setup and disposal from their complete contiguous bodies / 3,035
original bytes. Grouped cold replay accepts initialization (277 bytes) and disposal (175 bytes) /
452 bytes, preserving all 104 prior exact identities. Redraw 578/587 retains 560
full differences; point setup 2,041/1,996 retains 750. The consumed local binary
mask replaces synthetic ASCII division/comparison; direct resource/music/text
calls and live COM handles follow the original. Original buffer capacities and
source spelling remain unproven. Existing 5,615 direct intro cases and 58 separate
integration checks pass, with no fixture, case or campaign additions.

REA 4.1.0 with Ghidra 12.1.4 follows the actual mode-0 menu and mode-4
splash controllers through initialization, redraw, frame, input and cleanup.
This owner reuses all twenty complete dossiers from the closed 11-58 archive;
no new import or query was needed for this batch. Instructions, callers and
program data resolve details that incomplete pseudocode alone does not supply.
The maintained C connects these controllers to existing text, glyph, palette,
point, line, dirty-region and timing bodies. A playable Windows EXE is pending.
Subsequent [game-over](GAMEOVER_OWNER.md) and [editor](EDITOR_OWNER.md)
checkpoints connect the remaining mode controllers.

## Entries and retained observations

| Address | Maintained entry | Owned/span bytes | Direct cases | REA Evidence ID |
| --- | --- | ---: | ---: | --- |
| `0x0040DFC0` | `initialize_intro` | 277/277 | 6 | `ev_75f34375487bd0aa69c53dd2f4f5dd57fad9d8a4cc8ee85a09d0f40d06d65e0f` |
| `0x0040E0E0` | `redraw_intro` | 587/587 | 9 | `ev_8d3b245893789331b1a53500a14aae87ed382cd5465098be8604a64b721a1440` |
| `0x0040E330` | `intro_frame` | 242/242 | 32 | `ev_6209121031ff06b1a5ae1e284316241f2d319a9129ad4c33ccab80d4381195b1` |
| `0x0040E430` | `intro_key` | 156/305 | 1,024 | `ev_8f5f071d402bea6e963d3fdefc5bfde8e766fb3a31f74e23fbdb64856813cffd` |
| `0x0040E570` | `initialize_intro_points` | 1996/1996 | 1 | `ev_001f48ac971f132ed4b29b98cf1549ec4136da2eab0a9448b6ed27d7f5e41fb8` |
| `0x0040F010` | `dispose_intro` | 175/175 | 16 | `ev_e0df354eaa8c193e9ccbfb2486aa6532ed5cba21a7ed5d8c69097af79bf7e7dc` |
| `0x00407420` | `initialize_splash` | 430/430 | 6 | `ev_61c4212874ada28527bff5917d72525d34eed9f3b168a27f413b46eefec7948c` |
| `0x004075D0` | `redraw_splash` | 949/949 | 16 | `ev_4a967bbbf38cd42ec661c8b5dc82686fc9c2ab4f8e75a5c9b7132067706f4739` |
| `0x00407990` | `splash_frame` | 274/274 | 32 | `ev_7818bf9bdac1f23ebe2ac4798a9137426d357a7e5f7e060469add4fb9fee3f23` |
| `0x00407AB0` | `splash_key` | 36/36 | 1 | `ev_d1c87d90c887ddeb6eefe0dcd882a3c99b7c1bbfa0c5ffdad565e81e696538ac` |
| `0x00407AE0` | `dispose_splash` | 185/185 | 16 | `ev_57ee9ffdab9d682c65d0b645600262f0013224bdad8a466304a77cd940794454` |
| `0x00402520` | `wave_x` | 50/50 | 555 | `ev_916def4083f9636ec2455ade5918e3a2ad718cbfb806f38e649d086280c1a1b1` |
| `0x00402560` | `wave_y` | 50/50 | 555 | `ev_1b08c598ad977d80959318e20842816faa305f5345f823cf80b5cba35d227c00` |
| `0x0040ED40` | `update_intro_points` | 711/711 | 36 | `ev_380287bfea6a4f582b8e8ee477b5c7d470de69c6555f3ab997e0f5f7d4650b2d` |
| `0x00402340` | `raw_sine` | 84/84 | 1,441 | `ev_f54833f6bdefa3ac2f65eb81ed53cd5e9722d4155caeae6d947f02db2c6242d1` |
| `0x004023A0` | `raw_cosine` | 84/84 | 1,441 | `ev_dfb4bd59f79a192687135c6244bb42f195fa6e89d307f8146a685f02ac44b3fe` |
| `0x00407BA0` | `draw_scroller_wave` | 235/235 | 4 | `ev_ecc8bc98f207e2dcf6101e2f1fbf61126d0081fced68e29388f49128c78d7f89` |
| `0x00407C90` | `update_scroller` | 233/233 | 48 | `ev_60ffa0dd2052ca4d66e244d13dff9c0927c40df0a2c284e69e239173f8e96e25` |
| `0x00407D80` | `draw_waving_credits` | 353/353 | 256 | `ev_7921a58cbee918a0e153804ca0dbd7c123d0a0f183a6f0a8b32af893053e796f` |
| `0x00407EF0` | `pulse_splash_palette` | 370/370 | 120 | `ev_2c669d6d7ae4ed75294367bdef23972e96d8cd5430ddbee9bcd729c55f1398c3` |

The imported spans were reconciled against inclusive REA body ranges. The
menu key entry owns 156 bytes in three ranges within a 305-byte span; intervening
switch data is not promoted to code ownership. Every other entry is contiguous.
Static Evidence IDs establish observations, not execution proof. Provider
prototype inference and unresolved indirect flows retain their limitations.

## Menu controller

`src/intro.c` loads `mainmenu.pcx`, `mainmenu.sbk`, `thefont.sbk`, `sfont.sbk`
and `ethno_pa.mds`, selects the observed banks, binds the board/display surfaces,
redraws, initializes the point cloud, updates it, restores regions and fades in.
Presentation depends on the existing draw-to-primary flag. Redraw reads the
existing game score at `0x422D18` and formats its 32-bit value as unsigned
`Last Score - %u`. There is no separate last-score global. An independent
original-execution comparison caught that mistaken alias in the initial draft.

The 287 point records contain four 32-bit fields each. A seven-row, 41-column
mask expresses the observed DX-BALL pattern, replacing 287 individual constant
assignments. All initialized point records and all 360 offset pairs compare
with original execution. The offsets use the existing computed integer trig
tables, signed multiplication and division by 1024. Negative multiples of
360 select table endpoint 360; nonnegative multiples select endpoint zero.
Negating INT_MIN and overflowing arithmetic remain outside the accepted domain.

Point animation checks a 50 ms elapsed gate. It restores rectangle
`(112,37,530,115)`, obtains and locks writable pixels, advances kind-0 points
by 30 degrees and writes color 200, unlocks, then advances kind-1 points and
executes the actual keyed-sprite draw at `0x404040`. It invalidates the region,
rotates palette entries 200..207 and stores a new tick. Lock retries, unsigned
clock wrap, pixel rows and padding are checked. The descriptor request's
meaningful fields are exactly size 108 and flags 14 on both sides; the native
bridge returns pixels through its typed host structure, whose pointer layout
is not claimed to equal the original x86 layout.

The frame clamps cursor X to 8..599 and Y only at the upper bound 447, preserving
negative Y. Left mouse action requests gameplay mode 1; right action clears.
Control plus F1 requests editor mode 2. Tests cover every key byte with zero,
positive and negative control flags. Menu disposal with fade zero does nothing;
nonzero fade clears surfaces and releases banks, sounds and music in order.

## Splash controller

Initialization loads `intro.pcx`, `candy.sbk`, `chisel2.sbk` and `whine.wav`,
zeros all eight scroller/credit fields, reads the 3,480-byte welcome string and
sets the board surface's color key to zero with flags 8. It redraws, updates
sound, clears saved RGB entries 48 through 48+span inclusive while retaining
flags, and fades in. The retained welcome text is program data, not a bundled
external game asset; the untouched source string is compared with the original.

Redraw preserves the original video-status branches and text. It requests
secondary fill `(0,0,639,479)` only when draw-to-primary is zero and blits logo
rectangle `(0,19,639,169)` to primary. Its gradient draws two complete horizontal
lines per step with inclusive endpoints. The 66-int color pool is 22 RGB triples,
not 66 bytes. REA read-bytes Evidence
`ev_12a98e0862011195dd7f38a363bfd5800c83483593c4a2f57a99d318f2f92ad3`
retains the initial pool and span/offset/phase (120/0/1). An untouched native
library independently agrees with all original initialized data.

The scroller advances by four, loads the next glyph only when advance is less
than shift, wraps at the actual string length, and uses width+1 with missing-glyph
fallback 15. Its self-blit retains the original rectangle and destination.
Wave drawing emits 112 five-pixel strips. Instructions and the saved double
constants establish sine arguments and truncation of scales 20.0 and 3.0;
pseudocode omitted those arguments. Data Evidence is
`ev_04a3838b07983d54266eac7aa58be3bb0ee1396732075f94d21d26887841fc3b`.
The credits wave has only the redraw caller at `0x4075D0`; it is not added to the
per-frame controller. Both waves select effect surface only for reduced mode
zero, otherwise primary.

Palette pulsing runs only when the cursor gate equals zero. Nonzero red and
blue bytes subtract 4 and 2 with byte wrap; green and flags survive. A sine-based
moving pair receives red/blue 160. The original SetEntries call starts at 48
and submits **span+48 entries**, although mutation visits span+1 entries. That
unusual count is retained. Tests use valid palette/storage bounds, including
span 160 and gate values 0, 1, 2 and -1. Each splash frame updates sound, handles
wait/restore/scroller/presentation, rotates the 66-int pool, pulses the palette
and handles mouse actions. Any splash key requests menu mode 0. Splash cleanup
stops sound 0 even when fade is zero, unlike menu cleanup.

## Independent validation and limits

`tests/test_intro_differential.py` executes twenty unmodified original entries
for **5,615 direct cases**. It compares complete point/offset/RGB arrays, all
palette bytes and flags, controlled pixel buffers including padding, bank and
font selection, globals, meaningful descriptors, both blit rectangles and ordered
resource/audio/COM effects. Actual UI/glyph, keyed-sprite, line, palette,
dirty-region, time and wait bodies execute rather than being transcribed into
callbacks. Original x86 calls retain stack/register checks.

Another **58 checks are separate integration evidence**. For both primary
settings, actual mode dispatch initializes the splash, executes twelve frames,
routes a key and switches to the menu, executes twelve menu frames, then routes
Control-F1 into pending editor mode 2. Fresh production mode/key tables are
checked before controlled providers are installed. They default modes 0, 1
and 4 to maintained source.

File parsing on this lifecycle edge, release of synthetic Python-owned bank
records, audio/MIDI, COM rasterization and real Windows callback delivery remain
explicit boundaries. Their independent resource/startup acceptance is not
counted again here. Valid terminating storage and nonoverflowing arithmetic
are required. Editor and complete playable EXE integration remain pending. The subsequent
[game-over checkpoint](GAMEOVER_OWNER.md) now maintains mode 3 with its own
acceptance scope. This batch makes no new byte-exact claim.

All earlier suites, forty cold exact units, eight oracle rejection checks,
native/MinGW/VC4 products, Wine inspector comparison and saved REA verification
pass at the grouped checkpoint. Existing pan literal bindings remain
`$T637`/`$T638`; no relocation exception or source profile is added. Complete
reports and input identities are private under
`.analysis/checkpoints/intro-168-40/`.
