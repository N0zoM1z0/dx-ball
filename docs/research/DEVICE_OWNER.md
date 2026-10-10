# Palette transitions and surface recovery

The [device-frame restoration](exact/DEVICE_FRAME.md) now makes synchronization
and recovery exact, preserving live surface reads and the original HRESULT
writes. That note records the current affected checks and compiler receipts.

REA's gameplay initialization and presentation callers lead to the palette
transition controller at `0x40A340` and recovery at `0x403640`. The maintained
owner is [device.c](../../src/device.c), with shared declarations in
[device.h](../../src/device.h). These are algorithms over the original DirectDraw
interfaces; creation of the actual Windows device and driver behavior remain
pending.

## Original bodies and evidence

All six bodies are contiguous. Their owned byte counts equal their spans.
The retained REA 4.1.0 / Ghidra 12.1.4 interactive session is
`2026-10-07T10-33-32.118Z-interactive-2912559`; it saved 152 cumulative Evidence
records on explicit close. Complete pseudocode, instructions, body ranges,
callers and callees remain private under `.analysis/rea/runs/`.

| Entry | Maintained symbol | Bytes | Direct cases | REA Evidence |
| --- | --- | ---: | ---: | --- |
| `0x40A340` | `dxball_palette_transition` | 1,339 | 774 | `ev_eaf357e839ddf4487c962040bded218134cadfcccd5854a83a07cee7f285a71a` |
| `0x4096C0` | `dxball_initialize_palette` | 206 | 4 | `ev_1f7ee3646ca9d02b5f9f7b91f0c1cbfe3f3af3a8f021debadd09191a0c844cbd` |
| `0x409F10` | `dxball_clear_surface` | 89 | 18 | `ev_017375bcddb7d6708aadc8ec0d071b77e9d37c7f877f9da584462f4e561360db` |
| `0x403D30` | `dxball_restore_sprite_banks` | 282 | 64 | `ev_6086488847b0abeff3f7ed6af657fd76f1d18d085752c4ae7c38ff49c74b9d94` |
| `0x403640` | `dxball_recover_surfaces` | 97 | 63 | `ev_38016d73060dc54237eaa650b38484472bf814f4c1eee8d11110beaecbc771de` |
| `0x4035B0` | `dxball_synchronize_surface` | 134 | 192 | `ev_7528b8fd339fe77e2bd500279969b4c0f36946e98a3556d3f30044c87289bb30` |

## Behavior retained

Palette transition handles direction 0 (toward black) and 1 (toward the saved
palette), using an inclusive entry range. RGB channels move separately; entry
flags and entries outside the range stay unchanged. Integer comparisons use
the full step, while additions/subtractions use its low byte. The loop issues
SetEntries and the maintained frame wait once more after reaching the target,
because its continuation flag records changes attempted in the preceding
iteration. An already matching palette still performs that final iteration.
Direction values other than 0/1 do nothing. The flag at `0x422898`, currently
named `cursor_warp_disabled`, suppresses this function only when exactly 1.

Palette initialization clears both palettes' RGB channels, retaining their
flags. It calls CreatePalette with flag 4 and writes its output directly to the
shared palette pointer, including failure outputs. Only success attaches that
palette to the primary surface; the attachment result is ignored.

Color fill requests a 640 by 480 rectangle and Blt flag `0x400`, passing a
100-byte DDBLTFX with the requested color at offset 80. The original specifies
only the size and color fields. Source zeroes the remaining unspecified fields;
acceptance compares the declared fields rather than original stack garbage.
The Blt result is ignored. No independent pixel fill or driver claim is made.

Recovery restores primary surface `0x4228B4` first and game working surface
`0x4228BC` second, stopping if either fails. The latter is `board_surface`,
distinct from presentation's secondary surface at `0x4228B8`. Only then does it
restore sprite banks and redraw the current mode. Banks whose allocation mode
is exactly 1 scan all 255 pointer slots, independently of their count. Non-null
sprites with non-null surfaces receive Restore; individual sprite Restore
failures do not prevent the subsequent bank reload. Reload dispatch defaults to
the existing maintained SBK parser through the runtime operations table.

Synchronization queries **GetBltStatus**, slot 13 / offset `0x34`, with flag 1;
it does not query GetFlipStatus. When `cursor_warp_disabled` is 0, only
SURFACELOST (`0x887601C2`) triggers recovery, and a request flag exactly 1 is
cleared afterward. For any other cursor flag, a request exactly 1 triggers
recovery and is then cleared. Other request values remain unchanged. The typed
COM slots are corroborated by the local MinGW `ddraw.h` declarations.

The later [actual round/focus investigation](ROUND_FOCUS_RUNTIME.md) reuses this
dossier to explain an external runtime difference. Independent DirectDraw1 SDK
surfaces under Wine9/Xvfb report SURFACELOST through IsLost and Lock after focus
returns, but success through GetBltStatus. Both default and GDI runs restore
successfully when the probe explicitly restores its own primary and working
surfaces. The original and source game controls still stall; their recovery
gate is preserved. This SDK observation changes no original-function or exact
acceptance, and is distinct from physical Windows driver verification.

The connected investigation also corrects two duplicated state declarations.
Addresses `0x4265AC` and `0x4265B0` are the third sprite bank's `count` and
`allocation_mode`: base `0x425980`, stride `0x418`, offsets `0x3FC` / `0x400`.
Gameplay initialization now writes those fields directly. They were previously
named independent text settings. Lifecycle tests compare all three banks'
metadata, so recovery and initialization share the same storage in C as in the
original.

## Validation and boundaries

Run after the native build:

```bash
scripts/repo-python tests/test_device_differential.py
```

The oracle executes all six unmodified original entries and compares full
palettes, relevant globals, grids, bank metadata, dirty/presentation arrays,
ordered COM calls and typed entity ownership against compiled C. Its **1,115
direct cases** cover both fade directions, endpoint/full palette ranges,
positive steps including 256/300, equality gates, palette failure outputs,
color values, bank modes, null sprite/surface slots, ignored sprite failures,
recovery short circuits and valid/invalid mode routing.

Another **26 connected checks are separate integration evidence**: eight
BUSY-to-SURFACELOST presentations execute real recovery and game redraw; twelve
frame dispatches execute real synchronization and gameplay; three game
initialization/cleanup pairs execute actual fades and clear requests. Original
wait, redraw and gameplay bodies run alongside these new entries.

COM objects supply controlled HRESULTs and writable particle storage. Bank
reloads, PCX loading/capture, glyph drawing, audio, device setup and non-game
mode bodies are explicit boundaries. The restored bank algorithm is exercised,
while parsing on its reload edge is covered by the separate resource oracle.
Native and target backgrounds now have actual controlled COM objects; the
earlier lifecycle oracle's opaque background handle cannot serve a real fill.
Boundary failures terminate immediately instead of entering native retry loops.
There is still no playable reconstructed executable.

The terminating palette domain is `0 <= first <= last < 256` and positive
steps. Suppressed calls also test zero/negative steps; an unsuppressed original
can repeat forever with such inputs, so no terminating equality is claimed.
Unspecified stack bytes and hardware rasterization are excluded.

This checkpoint brings maintained entries to **123** and direct cases to
**70,928**. Shared source/header/helper changes receive a grouped replay of all
earlier differential suites, 40 cold exact units, rejection tests, native,
MinGW and VC4 builds, Wine inspectors and saved REA evidence verification. No
new byte-exact claim is made: the accepted total remains 40 functions / 4,079
bytes. The two board I/O literal symbols are rebound from `$SG733` / `$SG737`
to `$SG731` / `$SG735` after reviewing unchanged rb/wb bytes in object and target
and the complete relocation offsets, types and addends. Private reports,
input identities and binding review are archived at
`.analysis/checkpoints/device-123-40/`.
