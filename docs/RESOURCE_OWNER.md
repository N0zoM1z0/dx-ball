# Sprite, font, PCX and palette owner

Evidence is the hash-pinned DX-Ball v1.07 target in `config/target.toml`.
Attested Ghidra queries cover the entries below; original x86 execution supplies
the behavioral evidence. The maintained implementation is `src/resources.c`.

| Entry | Maintained function | Target extent | Acceptance |
| --- | --- | ---: | --- |
| `0x00403E70` | select_sprite_bank | 24 | full exact |
| `0x00403E90` | select_font_bank | 24 | full exact |
| `0x00403F70` | blt_keyed_sprite | 195 | full exact |
| `0x00404040` | draw_keyed_sprite | 105 | full exact |
| `0x004040B0` | blt_sprite | 195 | full exact |
| `0x00404180` | draw_sprite | 105 | full exact |
| `0x004041F0` | stretch_keyed_sprite | 139 | full exact |
| `0x004042B0` | capture_sprite | 852 | scoped semantic |
| `0x00404610` | load_sprite_bank | 1475 | scoped semantic |
| `0x00404BE0` | release_sprite | 262 | scoped semantic |
| `0x00404CF0` | draw_glyph | 328 | scoped semantic |
| `0x00404E40` | find_glyph | 145 | scoped semantic |
| `0x00409790` | load_live_palette | 337 | scoped semantic |
| `0x004098F0` | load_saved_palette | 307 | scoped semantic |
| `0x00409BB0` | load_pcx | 862 | scoped semantic |

## Storage and interface

The three banks begin at `0x00425980`, stride `0x418`. Each owns 255 sprite
pointers, a count at `+0x3FC`, allocation mode at `+0x400`, and a 20-byte filename
at `+0x404`. Current sprite/font selectors are `0x00421088` / `0x0042108C`.
The file pointer at `0x004265C8` is shared with board I/O. Selectors and banks
are zero-initialized in the file-backed target image.

A sprite has a surface pointer at `+0`, unclassified integer at `+4`, width,
height and pitch at `+8/+12/+16`, source RECT at `+20`, character byte at `+36`,
and signed baseline adjustment at `+40`. Allocation requests 45 bytes for this
44-byte i386 record. The spare byte and opaque integer are not assigned meaning
or accepted as initialized output. Native pointers grow naturally; the same
source and declarations compile for the native host and Windows i386.

DirectDraw dependencies use actual vtable slot order and the Windows stdcall
ABI. Surface slots used here are Release 2, Blt 5, BltFast 7, GetSurfaceDesc 22,
Lock 25, SetColorKey 29 and Unlock 32. IDirectDraw CreateSurface and palette
SetEntries use slot 6. The target descriptor is 108 bytes, with height/width/
pitch at `+8/+12/+16`, pixels at `+36`, and caps at `+104`. Microsoft's
[DDSURFACEDESC declaration](https://learn.microsoft.com/en-us/windows/win32/api/ddraw/ns-ddraw-ddsurfacedesc)
corroborates these fields. Unused vtable slots and descriptor fields remain
opaque.

## SBK stream and ownership

The stream starts with a signed little-endian 32-bit sprite count. Each record
is width i32, height i32, character byte, baseline i32, then exactly
`width * height` pixel bytes. Rows are stored bottom-up: the first stream row
becomes the last surface row. Surface pitch comes from GetSurfaceDesc and may
exceed width; padding bytes remain untouched.

All seven supplied streams consume exactly their file lengths: CANDY 52,
CHISEL2 50, MAINMENU 7, MBALL2 166, SFONT 96, SYSFONT 94 and THEFONT 48 sprites.
The loader frees slots 1 through 253 before opening the file, preserving slots
0 and 254. Successful loading restores the prior bank; an empty stream leaves
the previous count, allocation mode and filename unchanged. Mode 1 requests
surface caps `0x40`, other modes `0x840`; source color key is zero, flags 8.
Descriptor and Lock failures are retried until success.

CreateSurface failure returns with the new bank selected, an open file and
allocated partial record/pixel buffer. These observed effects are preserved.
Input filenames must fit the original 20-byte field; supplied basenames do.
Malformed/unbounded counts, dimensions and filenames are outside acceptance.
Allocation failure and open failure invoke exit(1); process-exit behavior has
not yet been compared. Release handles NULL records and NULL surfaces.

Capture releases an old slot, creates an offscreen surface and copies a RECT
from the active surface through Blt. The oracle accepts initialized record
fields and ordered API arguments, not hardware Blt pixel results. After failed
creation, uninitialized pitch and opaque fields are outside the compared state.

## Drawing and fonts

BltFast uses flags `0x10` for plain sprites and `0x11` for keyed sprites.
Blt uses `0x01000000` for plain copies and `0x01008000` for keyed copies.
Unstretched destination dimensions come from the sprite; stretch takes explicit
dimensions. Stored source RECTs are passed directly without replacement.

Glyph lookup checks slots 1 through count-1 and deliberately excludes the last
slot. No match returns 0; an empty bank returns 1 without inspecting a record.
Drawing requires populated records and accepts all 256 character byte values
for the three supplied fonts. Glyph top is `baseline-height-record.baseline`;
bottom is `baseline-record.baseline`. The return value is glyph width, or zero
for missing characters. Drawing an empty bank is outside acceptance.

## PCX behavior and palette

The decoder reads 128 header bytes and treats header xmax/ymax as signed i16.
It ignores xmin/ymin and bytes-per-line. It decodes while the number of emitted
pixels is **less than or equal to xmax*ymax**, rather than decoding the full
image area. A final RLE packet may overshoot this limit. Packet bytes below
192 are literals; other bytes supply count byte-192 and the following value.
Count-zero packets consume a value without emitting pixels.

Column wraps when it exceeds xmax. Output is clipped to the destination width
and height, with supplied x/y offsets and descriptor pitch. The original saves
dimensions and pitch before Lock. Palette mode 1 loads the live palette and
calls SetEntries; mode 2 loads the saved palette without that call; other modes
leave both untouched. Both loaders seek 768 bytes before EOF, read RGB triplets,
and preserve each entry's fourth flag byte.

## Reproducible evidence and limits

`scripts/repo-python tests/test_resources_differential.py` compares 1,869 cases:
all supplied SBK/PCX files, bank restoration, edge slots, creation failure,
descriptor/Lock retries, row reversal, pitch padding, clipping, RLE overshoot,
zero-count packets, signed maxima, all font bytes, glyph placement and palettes.
The unmodified target performs its own decoding and record access. Synthetic
CRT boundaries supply file buffers; target inline getc accesses those buffers
directly. The native implementation uses host libc on identical files.

Comparisons cover initialized bank/sprite state, all resulting allocated pixel
bytes, palette RGB/flags, return values, and ordered DirectDraw call arguments.
Target file traces and allocation/free ownership receive explicit checks.
DirectDraw operations are controlled boundary callbacks; COM driver behavior,
real Blt pixels, actual display, and backend error codes beyond modeled retries
are not proven by this test. Shared-source changes require fresh replay.

Seven resource functions match their complete /Gy COMDAT extents after every
reviewed DIR32 relocation is applied: 787 bytes, zero differences. Extents agree
with the function ledger and terminate at actual epilogues; alignment gaps are
excluded. Eight larger functions currently have semantic evidence only. Their
different object lengths are not masked or reported as exact.
