# Target observations and reconstruction evidence

## Target identity

DX-Ball v1.07 is supported by the included README and EXE string at
`0x00422C24`. The PE32 image base is `0x00400000`, entry `0x004187A0`, image size
`0x46000`, linker version 3.00, with relocations present and no Rich header.
Imports include DirectDrawCreate, DirectSoundCreate, WinMM MIDI stream APIs,
and ANSI Win32 window/input APIs. CRT startup calls WinMain at `0x0040D930`.
Compiler identity is a candidate until backed by reproducible emission evidence.

## Board owner

`DEFAULT.BDS` has 20,000 bytes: 50 row-major boards, 20 columns × 20 rows,
one byte per tile. All supplied tile values are 0..22. Target-observed globals:

| VA | Maintained name | Extent / meaning |
| --- | --- | --- |
| `0x0043AAB8` | `dxball_board_bank` | 20,000-byte bank |
| `0x0043F8F8` | `dxball_board_tiles` | Current 400-byte grid |
| `0x0043A918` | `dxball_board_aux` | 400-byte explosion occupancy grid; cleared at level load |
| `0x0043A8F8` | `dxball_board_index` | Signed editor/level index, valid 0..49 |
| `0x004265C8` | `dxball_board_file` | Last fopen result; remains stale after fclose |
| `0x004265CC` | `dxball_active_surface` | Active draw surface |
| `0x00421074` | `dxball_display_mode` | Mode selector; value 1 hides tile 7 |

At `0x0040CC30` / `0x0040CC90`, fopen uses `rb` / `wb`, then transfers
`fread` / `fwrite` size 1, count 20,000. Open failure returns without changing
the bank. Short reads replace the prefix; transfer and close errors are ignored.
Editor copy functions `0x0040CEA0` / `0x0040CEE0` copy exactly 400 bytes using
`bank + index * 400`. Index bounds are enforced by editor producers, not these
helpers. Initialization `0x00411930` zeroes the auxiliary grid then loads the
current bank slot. Editor input at `0x0040C3B0` corroborates row-major layout.

Tile sprite mapping at `0x0040CCF0` has cases 0..22; the palette producer at
`0x0040C9C0` generates 1..22. Unsupported values return an uninitialized stack
local in the target. The host helper aborts outside the supported domain, which
is an explicit semantic limitation and excludes it from exact promotion.

`0x004119F0` draws a cell at `(20 + 30*x, 50 + 15*y)`, rectangle 30×15.
Zero tiles and tile 7 in mode 1 restore the background with BltFast flag `0x10`.
Supported nonempty tiles call the sprite renderer. Unknown tile bytes do no
drawing. Invalidation occurs iff the third argument is zero, even for unknown
bytes. `0x00411970` selects the board surface, then traverses x first, y second.
The independently observed `0x00403E50` only assigns the active surface.

## Evidence limits

The function ledger is an auto-analysis inventory, not an authored-function
denominator. `0x0040CCF0` spans a jump table; raw linear disassembly can mistake
its entries for instructions. Drawing oracles intercept sprite/BltFast/update
calls and validate their arguments/order, without claiming pixel equivalence.
I/O interception exposes the requested transfer size; native tests use actual
temporary files. Original compiler flags, translation-unit boundaries, the
auxiliary grid's uses outside the recovered explosion lifecycle, and the complete runtime remain open.

## Resource owner

Sprite-bank, font, PCX and palette producers/consumers are maintained in
`src/resources.c`. [Resource evidence](RESOURCE_OWNER.md) records layouts,
file formats, DirectDraw slots, preserved original quirks and acceptance limits.
The 15 functions have 1,869 target execution cases; seven full functions cold
match exactly. The board test's sprite interception and the resource test's
actual sprite dispatch are distinct evidence scopes.

## Gameplay owner through REA

`src/gameplay.c` recovers hit transitions and their score-eligibility return,
the explosion scan, queue append and sound pan. [Gameplay evidence](GAMEPLAY_OWNER.md)
connects REA dossiers, callers, xrefs and constant reads to maintained state.
The owner has 13,689 target differential cases and six exact functions.
Tile 2 never decrements the destructible count; tile 21 decrements once while
becoming tile 2. Explosive tile 8 remains present after queueing, so repeated
scans append again. Particle RNG order is dy/dx/y/x. These are preserved
observations, not design corrections. Missing backends remain explicit.

## Explosion and animation owner

[Animation evidence](EFFECTS_OWNER.md) records the separate request/animation
containers, 32-byte animation payload, occupancy guard, center-clear timing and
fixed neighbor propagation order. The owner has nine functions, 12,977 direct
cases and five exact functions. Original-frame and hit-to-animation integration
cases are reported separately. Both queues preserve delete-then-advance skipping;
cleanup clears occupancy only when the explosion animation finishes.

## Particle and bonus owners

[Entity evidence](ENTITIES_OWNER.md) records separate particle and bonus lists
at `0x0043A868` and `0x0043FAC8`, with 44-byte and 36-byte original nodes.
The fourteen functions add 7,343 direct cases and nine exact functions.
Creating particles uses strict bounds, while surviving movement includes the
left/top boundary. Gravity applies only for flag 1, increments dy every sixth
update, and fading advances color every fifth surviving update. Original
2x2 writes agree with maintained C across complete controlled surface buffers.

Bonus production draws chance before checking the active count. Its screen x
is 19+30*tile_x, and its burst consumes RNG in dy/dx/y/x order. Selector 0/1
has an extra rare roll, selector 14 becomes kind 10, and count increments last.
Retirement decrements count even without a current node. Bonus movement and
application now have separate connected evidence in the power-up batch.

## Power-up dependencies through REA

[Power-up evidence](POWERUPS_OWNER.md) connects 21 additional maintained
functions and seven exact units. Bonus collision uses cached paddle coordinates;
width changes release attached balls before reading the base sprite width.
Explosive spread gathers its source tiles before editing neighbors, and uses a
separate scratch root at `0x0043FAA8`. Active/temporary ball roots are
`0x0043A8B8` / `0x0043AAA8`, with 60-byte original nodes.

The 361-entry sine/cosine tables are computed from 3.14159 and scaled by 1024.
Negative multiples of 360 preserve the separately initialized endpoint.
Rebounds use an extended first threshold and stored-float later thresholds.
REA instruction and CRT dispatch observations resolve missing pseudocode ABI.
The connected oracle adds 15,934 cases; current totals are 76 maintained
functions, 61,314 direct cases and 40 exact functions / 4,079 bytes.

The original terminal level transition still calls initialization after index
49 becomes 50. Adjacent-memory reads beyond the board bank remain unresolved;
terminal tests intercept that dependency. Main ball motion, full frame routing
and Windows backends are still open scopes.
