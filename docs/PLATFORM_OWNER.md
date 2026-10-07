# Windows startup and input routing

REA follows the frame dispatcher back to WinMain and the window procedure, then
through fullscreen/compatible DirectDraw creation and game key handling. The
shared owner is [platform.c](../src/platform.c), declared in
[platform.h](../src/platform.h). It recovers the caller algorithms and their
Windows/COM contracts; the actual Windows adapter and audio/UI implementations
remain pending, so these builds are still analysis libraries and inspectors.
Startup-only COM signatures are declared in the platform header and applied
to the resource interface's existing opaque slots before invocation. This keeps
the resource owner's declaration boundary stable; expanding its vtable types
altered VC4 register allocation and failed strict replay. Both builds share
the same interfaces and typed casts; no layout/body selector or comparator
exception was introduced.

## Original bodies and evidence

REA 4.1.0 / Ghidra 12.1.4 session
`2026-10-07T11-04-09.689Z-interactive-2967798` saved 163 cumulative Evidence
records on explicit close. Original bytes remain unchanged. Owned ranges can
exclude switch data and gaps; the ledger retains the complete entry span.

| Entry | Maintained symbol | Owned / span bytes | Direct cases | REA Evidence |
| --- | --- | ---: | ---: | --- |
| `0x40D930` | `dxball_win_main` | 320 / 320 | 56 | `ev_44569046e29fafd9e3d92f911c45121c537e6f2fd3112ffd497195c11e26321e` |
| `0x40DA70` | `dxball_window_proc` | 1,136 / 1,171 | 2,138 | `ev_ec5246e677575ed67dc6c47dec0ffc7106e9ff2c86eaf9c4c562e39071b603cf` |
| `0x40CF70` | `dxball_initialize_fullscreen` | 1,343 / 1,343 | 126 | `ev_2cc92baf4edd1bfc64e4ea142dd7d186ca9124af4dda1bda4b72cb0945cc88d8` |
| `0x40D4B0` | `dxball_initialize_compatible` | 1,147 / 1,147 | 122 | `ev_11e3dc434ea2130b97aafcbdeb5927e235c6ea83b327a1346881a3898124fa3b` |
| `0x40DF10` | `dxball_claim_instance` | 104 / 109 | 18 | `ev_62be40ba52c99f99d98901a5d736ae5250673c0cd2a257527bb0748dce67c357` |
| `0x40DF80` | `dxball_close_instance` | 51 / 51 | 4 | `ev_1c8812cfc0cee3f5a725c911a8611a98678bac2db8eb4363445fadfda4b10263` |
| `0x403550` | `dxball_detect_clock` | 83 / 83 | 10 | `ev_dc0dafecc27f037b35f96d78484d3582f5e70e4666096d803238dfccb02c6c96` |
| `0x403820` | `dxball_dispatch_key` | 137 / 162 | 1,792 | `ev_ac5f83bb902255b7f7e010c66c9f6f8ddd53fe3dc3d95f96621ab1c202bf4f39` |
| `0x410290` | `dxball_game_key` | 645 / 831 | 420 | `ev_a1126b60967546aced7cce45fa25634c65245ad3a415585374561d88ccbbaccb` |
| `0x403BD0` | `dxball_dispose_working_surface` | 80 / 80 | 54 | `ev_165c97de81ef73fd69541c691fb8e54c52dab143890299a2cb392e597a303df5` |
| `0x403C20` | `dxball_initialize_sprite_banks` | 131 / 131 | 2 | `ev_ac7fa0e07bc68efa267f3caf8637f4a6912b4f5ba66ae42249ffbff5e5b53672` |

## Behavior retained

WinMain claims the named semaphore first. An existing semaphore returns zero
without closing the opened handle; failed creation also takes the existing
instance path. That path displays the original period-terminated message,
"DX-Ball is already running.", then exits through a non-returning CRT boundary.
Initialization failure returns zero without closing the claimed semaphore here.
WinMain selects compatible creation for every nonzero cursor flag, unlike the
palette transition's equality-to-one gate. On success it initializes clock/trig,
clears modifier state, reads the system cursor and enters the message loop.
Inactive iterations call WaitMessage; active iterations execute the maintained
mode dispatcher. GetMessage returning -1 is treated as nonzero, with defined
message fields supplied by the test boundary. WinMain and the window procedure
both use stdcall and clean sixteen argument bytes on original x86.

Window creation retains class style 3, icon/cursor identifier 0x7F00, stock
object 4 and a 640 by 480 popup. RegisterClass's result is ignored. Ordered
ShowWindow/update/focus/sound preparation calls are preserved. Fullscreen uses
cooperative flags 0x11 and display mode 640/480/8; compatible uses flag 8 and
omits SetDisplayMode. Primary/working surfaces use the original 108-byte
DDSURFACEDESC contract. Creation failure outputs are retained in shared
handles. Only fields selected by DDSD flags are consumed; source initializes remaining unspecified fields
to zero, while the original leaves stack bytes unwritten.

GetCaps is supplied a 316-byte original DDCAPS record. NOHARDWARE comes from
bit 0x02000000 at offset 4; free video memory is at offset 64. The HRESULT is
ignored, so acceptance requires those output fields to be defined. Fullscreen
sets reduced particles from the hardware bit and forces it, together with the
low-memory flag, below 310000 bytes. At or above that boundary the old low-memory
flag survives. Compatible creation sets draw_to_primary and zeroes buffer
count, while preserving old reduced/low-memory flags and the secondary surface.
Clipper creation requires clip_regions exactly 1. Fullscreen optionally attaches
it to the secondary surface; compatible attaches only to primary. Original
failure-message punctuation/capitalization and differing silent failure paths
are preserved. Successful initialization clears all 765 sprite pointer slots
and three counts, retaining bank modes, filenames and selected banks.

The window procedure preserves focus/audio order, activation's full integer
value, capture-before-mouse-action writes, modifier updates after key dispatch,
and the default return on mouse movement after reading the system cursor.
Escape cleans intro mode then posts WM_CLOSE, or requests mode exit elsewhere.
Power messages retain their specific wparam gates. Palette changes require
DirectDraw, primary surface and a zero device-reset flag. Destruction disposes
working resources first, releases audio/music, releases banks and board before
primary/palette, closes the semaphore, and posts quit. The original clears the
DirectDraw pointer without calling Release on it; secondary is cleared only
when primary exists. Clipper storage is not independently released here.

Game key handling first unpauses on any key when paused equals 1. P pauses only
from zero. Both paths optionally fade out, redraw, then always fade in. The
fade-out gate is the existing restart_requested flag at 0x43A90C; there is no
second independent pause flag. F1/F2 access bonus_9_active at 0x43A890, and F1/F3
also access bonus_8_active at 0x43A860. They do not access bonus_12_active at
0x43A910. Control gates F1 through F4; F5 draws a music choice then closes and
loads its selected MDS, F6 closes music, and F12 negates the existing pan double.
Dispatch narrows the key to its byte and routes modes 0 through 4, including
mode 4's no-argument handler. Other modes do nothing.

## Validation boundaries

```bash
scripts/repo-python tests/test_platform_differential.py
```

The test executes all eleven original entry bodies and compares returns,
relevant state, every bank pointer's presence and metadata, palettes, grids,
dirty/presentation buffers, particle pixels, entity ownership and ordered API
calls with snapshots of state at boundaries. Native pointer growth is normalized
only for object identity and typed Windows records. Existing actual mode
routing, game input, palette transitions, waits, game redraw and cleanup remain
connected. Callback errors fail immediately. The two stdcall entries retain
callee-saved-register checks and explicit stack cleanup checks; cdecl remains
the unchanged default for all earlier oracle callers.

Windows APIs, COM HRESULTs/output objects, audio/MIDI, non-game mode bodies,
glyph drawing and lifecycle resource loading are explicit controlled boundaries.
DestroyWindow and DispatchMessage are traced API contracts in this suite;
synchronous Windows callback delivery and actual driver behavior are not
established. Version/caps failure cases provide valid consumed output fields;
unwritten original stack fields are outside acceptance. Sprite reset uses
caller-owned fixtures, not leaked C allocations. Key widths use valid selected
sprite metadata and bounded signed arithmetic. Finite palette inputs and valid
mode dependencies are required. Native process-exit cases run in child
processes and must exit instead of returning from the callback.

The batch adds **4,742 direct cases** across eleven entries, bringing the
current checkpoint to **134 maintained entries / 75,670 direct cases**. Key
tests cover every byte in seven valid/invalid routing modes, pause/equality
gates, all music choices, alternate sprite banks and signed-zero pan behavior.
Window tests cover message ordering, modifier/capture state, high wparam values,
palette gates and all destruction handle combinations. Startup tests cover both
creation modes, every declared failure stage with null/non-null outputs,
310000-byte memory boundaries, stale state, active/inactive main loops,
GetMessage -1, and two non-returning singleton paths.

Shared inputs receive one grouped checkpoint replay: forty accepted exact
units remain **4,079 bytes**, with zero differences, alongside rejection tests,
every earlier differential suite, native/MinGW/VC4 builds, Wine inspectors and
saved REA verification. No platform byte-exact claim is made. Private identities,
reports, logs and literal binding review are retained under
`.analysis/checkpoints/platform-134-40/`.
