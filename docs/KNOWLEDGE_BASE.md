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
| `0x0043A918` | `dxball_board_aux` | 400 bytes zeroed at level load; later meaning unknown |
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
auxiliary grid's full semantics, and the complete runtime remain open.

## Resource owner

Sprite-bank, font, PCX and palette producers/consumers are maintained in
`src/resources.c`. [Resource evidence](RESOURCE_OWNER.md) records layouts,
file formats, DirectDraw slots, preserved original quirks and acceptance limits.
The 15 functions have 1,869 target execution cases; seven full functions cold
match exactly. The board test's sprite interception and the resource test's
actual sprite dispatch are distinct evidence scopes.
