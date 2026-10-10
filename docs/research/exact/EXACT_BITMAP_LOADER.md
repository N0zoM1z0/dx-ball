# Bitmap records and shared imports

The complete `load_bitmap` body at `0x409F70..0x40A33F` reads a file into a
DirectDraw surface and creates its palette. REA dossier
`ev_e408e41080570698d5068c6aa811cbae0a93e65442822fc191ea85ea46c93cad`
retains all 237 instructions and 976 bytes. This batch reuses that saved analysis.

[`bitmap.c`](../../../src/bitmap.c) now reads the 40-byte information record
directly: signed width/height at offsets 4/8 and an unsigned 16-bit bit count
at offset 14. The input palette uses four-byte blue/green/red/reserved records.
The previous byte-decoding helper is removed. Width times height is computed
at both allocation and pixel read, and one counter serves the row and palette
loops. Lock and palette-creation results retain their consumed local value.

The original calls shared Kernel32 imports:

| Service | Original cell | Shared source symbol |
| --- | --- | --- |
| CreateFileA | `0x44127C` | `dxball_file_create` |
| ReadFile | `0x441298` | `dxball_file_read` |
| CloseHandle | `0x441264` | `dxball_file_close` |
| LocalAlloc | `0x441280` | `dxball_local_alloc` |
| LocalFree | `0x44126C` | `dxball_local_free` |

Bitmap uses seven file calls and four local-memory calls. The five-field
Bitmap callback table is removed. [`memory.c`](../../../src/memory.c) owns
the two local-memory cells previously defined in MIDI; both consumers use
them directly. Windows binds each shared cell once. The native Bitmap fixture
saves and restores all five actual cells; the MIDI fixture follows the renamed
imports. Their existing callbacks and cases are unchanged.

The Bitmap fallback prefix remains separate storage at `0x422798`, confirmed
by REA `ev_0bf8c40924cea03a09e6b27ffa6d9e1c3531fdcb50b6aa934e790f870cdda023`.
Its four bytes are `2e2e5c00`. Bitmap memcpy calls `0x417CA0`, whereas MDS uses
`0x416610`; the whole-unit relocation map keeps those targets distinct.

Sequential reads remain 14/40/1024/width×height bytes. Boolean read gates,
unwritten suffixes and palette flags, failure leaks, retreat by copy length,
and unlock/free/close/palette ordering follow the original instructions.
The [Bitmap investigation](../BITMAP_INVESTIGATION.md) explains these effects.

One compile per 21 affected recipes preserves all 99 affected accepted units.
The complete Bitmap candidate is 928/976 bytes with 614 differing byte positions;
MDS opening stays 480/522. Both remain candidates. The recorded comparison
covers 101 whole units and 1,078 actual relocations. Current totals remain
283 source-present functions and 134 exact functions / 20,887 code bytes.

Native, VC4, and MinGW builds pass. The two affected existing Oracles pass
Bitmap 975 and MIDI 2,109 direct / 134 connected checks. Bitmap's result covers
controlled file and DirectDraw boundaries; its active gameplay use is still
unestablished. Full inputs, prior/current products and comparisons are retained
in `.analysis/checkpoints/exact-bitmap-loader-283-134/`.
