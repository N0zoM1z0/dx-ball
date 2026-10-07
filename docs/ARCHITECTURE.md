# Reconstruction layout and current owner map

The original is a 32-bit Windows DirectX game, with statically linked Microsoft
CRT code mixed into `.text`. WinMain at `0x0040D930` is called by CRT startup
at `0x004187A0`. Do not classify whole address ranges as authored or runtime
without checking their individual evidence.

| Area | Target evidence / current work |
| --- | --- |
| Platform startup | `src/platform.c`; WinMain, window/input routing, singleton and fullscreen/compatible DirectDraw creation; Windows adapter pending |
| Mode routing | `src/runtime.c`, mode global `0x00421074`, init/redraw/frame/cleanup dispatch; all five mode controllers maintained; Windows/audio adapter pending |
| Board owner | `src/boards.c`, bank I/O, editor copy, initialization, render traversal |
| Resource owner | `src/resources.c`, SBK ownership, PCX pixels, palettes and fonts |
| Sprite draw | `0x00404180`; exact API dispatch; hardware backend pending |
| Gameplay owner | `src/gameplay.c`; tile hits, explosive scan, request-list helpers and sound pan |
| Animation owner | `src/effects.c`; constructors, timer steps, dispatch, occupancy and propagation |
| Particle owner | `src/particles.c`; clipped creation, movement/fading, typed list and 2x2 pixel writes |
| Bonus owner | `src/bonuses.c`; RNG selection, particle burst, movement, collection and application |
| Geometry/trig owners | `src/geometry.c`, `src/trig.c`; integer-center overlap and computed quantized trig |
| Paddle/round owners | `src/paddle.c`, `src/round.c`; mouse clamping, cursor warp, lives and level transition |
| Ball owner | `src/balls.c`; typed lists, creation, cloning, attachment release and paddle rebound |
| Core owner | `src/core.c`; main ball motion, gameplay frame, shots, fire and brick dropping |
| Runtime owner | `src/runtime.c`; game initialization, life-loss reset, clocks, paddle animation and score drawing |
| Display owner | `src/display.c`; lightning, dirty pages, sort/merge, palette, frame waits and presentation |
| Device owner | `src/device.c`; palette fades/initialization, color fills, sprite/surface recovery and synchronization |
| Startup/UI owners | `src/startup.c`, `src/ui.c`; working-resource setup, scores, text, line pixels and palette operations |
| Menu/splash owner | `src/intro.c`; mode-0/4 controllers, point cloud, scroller/credit waves and palette pulses |
| Game-over owner | `src/gameover.c`; mode-3 lifecycle/input, name buffer, rank insertion, score-file persistence and ranking pixels |
| Editor owner | `src/editor.c`; mode-2 lifecycle/input, toolbar hit regions, board painting and persistence |
| MIDI/music owner | `src/midi.c`; RIFF/MIDS parsing, event expansion, WinMM stream state and music wrappers; real WinMM adapter pending |
| Sound owner | `src/sound.c`; DirectSound startup, WAV/RIFF/file loading, buffer upload, play/stop, focus and lost-buffer recovery; physical device adapter pending |

`src/boards.h` defines one owner declaration shared by native and VC4.0 builds.
`DxBallInt` and `DxBallUInt` are explicit 32-bit scalars; opaque surface handles
use pointer-sized `size_t` for host compatibility. Legacy x86 builds use 32-bit
handles. No source selection macro changes any type or function body.

Rendering operations default to maintained sprite, background-restoration and
invalidation code. Individual board oracles replace those operations to retain
their isolated scope; the display oracle executes their actual bodies. Active
surface selection remains maintained code. The original board oracle executes
board routines and CRT memcpy/memset, intercepting file and rendering boundaries.
These separate scopes validate state and effect traces while leaving hardware
Windows display and pixel behavior unclaimed.

Project structure:

- `config/`: pinned identities, function/origin inventories, source/exact ledgers.
- `src/`: maintained C owners and the separate host board-inspection entry point.
- `scripts/`: attestation, REA/Ghidra queries, pinned builds, exact replay, reporting.
- `tests/`: target-machine differential and oracle rejection tests.
- `docs/`: accepted evidence, workflow, architecture, and handoff.
- `resources/`: generated progress SVG and the user-supplied original title screenshot.

Ignored local state: `original/`, `.tools/`, `.analysis/`, `build/`,
`ghidra-project/`. Ghidra databases and generated decompiler text are never the
durable authority for accepted source facts.

`src/resources.h` supplies one shared sprite/bank declaration and the known
DirectDraw interface slots. Only the platform ABI attribute varies: Windows
uses stdcall for COM methods. Resource oracles execute real sprite routines and
decoders against controlled file and surface storage; decoded pixel buffers
are compared independently. Real display and hardware Blt behavior remain open.

New inspection runs through REA's Ghidra 12.1.4 provider; the 12.1.3 inventory
is historical. REA opens its own immutable target copy and ephemeral Program,
then returns complete Evidence and function body ranges. See [REA workflow](REA.md)
for the first verified target session and current boundary observations.

`src/gameplay.h` declares the explosion list and gameplay dependency bridge.
The original append ABI uses ECX; Windows builds retain fastcall, while native
tests use the host ABI. Pointer fields grow with the host without changing the
three 32-bit payload values. Brick effects now call the maintained animation
owner, and particles call the maintained particle owner. Allocation, RNG and
DirectSound remain dependency boundaries. Individual owner tests can replace
the maintained calls to isolate their scope; the entity oracle connects their
real bodies. See [gameplay evidence](GAMEPLAY_OWNER.md).

`src/effects.h` declares the separate animation node/list and deletion, bonus,
sprite and region callbacks. `dxball_apply_explosion_requests` composes the
recovered request phase, without claiming the entire original frame updater.
The frame-phase oracle neutralizes unrelated work and checks only the declared
phase's state and ordered calls. See [animation evidence](EFFECTS_OWNER.md).

`src/particles.h` and `src/bonuses.h` declare two additional typed containers,
preserving original 32-bit payloads and native pointer growth. Animation bonus
production defaults to maintained source. Particle rendering uses the shared
DirectDraw surface declaration and writes into controlled writable pixels in
the differential oracle. See [entity evidence](ENTITIES_OWNER.md) for the
production/lifecycle scope and [power-up evidence](POWERUPS_OWNER.md) for movement,
collision and application through the new dependencies.

`src/balls.h` defines the thirteen-field ball payload and separate active/clone
containers. `src/trig.c` computes the game's 361-entry tables from the observed
constants. `src/round.h` exposes initialization/count operations, preserving
terminal-level call order. `src/board_storage.h` represents the recovered bank,
clock, request-list, count and tile region as one writable object; three unknown
four-byte intervals remain opaque mutable bytes. Copying through the entire
object preserves terminal overlap without an extra board or index-specific path.
The observed x86 layout is checked independently of the native pointer ABI.
`src/core.c` connects main ball physics and the gameplay frame to these owners.
`src/runtime.c` supplies real gameplay initialization and life-loss reset, plus
clock, score and paddle routines. Its mode table defaults all five modes to
maintained source. All twelve frame
phases now default to maintained owners. The display owner supplies lightning,
dirty pages, sort/merge, palette animation and flip/wait dispatch; platform,
COM drivers, Windows binding and audio remain pending. Glyph and shared UI
bodies default to maintained source. Surface recovery,
color fills and palette fades now default to `src/device.c`. The third sprite
bank's count and allocation mode own addresses `0x4265AC` / `0x4265B0`; gameplay
initialization writes those fields rather than duplicated globals. See
[core evidence](CORE_OWNER.md), [runtime evidence](RUNTIME_OWNER.md) and
[display evidence](DISPLAY_OWNER.md) and [device evidence](DEVICE_OWNER.md).

`src/platform.c` recovers the Windows entry loop, message procedure, device
creation and game key dispatch. Startup-only COM signatures live in
`src/platform.h`, applied to opaque resource-interface slots with typed calls.
WinMain/WndProc use stdcall on Windows and the host ABI for native analysis.
The new oracle compares Windows records with native pointer growth, explicit
COM output objects, message ordering and non-returning process exits. Audio
and the actual Win32 adapter remain boundaries on this platform test edge. Shared state
includes the existing restart flag and bonus-9 flag; no duplicate pause/bonus
fields are introduced. See [platform evidence](PLATFORM_OWNER.md).

`src/startup.c` supplies working-resource initialization, score-file handling,
CRT RNG calls and sprite-bank cleanup. `src/ui.c` supplies text/centering,
line pixels, fill requests and palette operations using the shared interfaces.
`src/intro.c` connects actual menu and splash lifecycle controllers to these
owners, with typed point/offset arrays, program welcome text and the RGB-int
pool. Menu Last Score reuses the existing gameplay score. Public startup/UI/
intro headers depend only on board scalar types; platform/device dependencies
stay in implementation files. See [startup/UI evidence](STARTUP_UI_OWNER.md)
and [menu/splash evidence](INTRO_OWNER.md). The products remain analysis
components and inspectors until the Windows/audio adapters and EXE entry
integration are complete.

`src/gameover.c` maintains mode 3 and connects it to the production mode/key
tables. Score data reuses `src/startup.c`; current-game score and menu cursor
state stay shared. Native and original tests execute actual name/ranking/UI
bodies, controlling only file APIs, lifecycle resource operations and hardware
boundaries. The name buffer is forty bytes with the original thirty-character
input limit; record shifts retain strcpy semantics rather than copying entire
records. See [game-over evidence](GAMEOVER_OWNER.md). The subsequent
[editor evidence](EDITOR_OWNER.md) completes the mode-controller family; actual
platform/audio/WinMM adapter work remains.

`src/editor.c` shares existing board/input/cursor storage and maintains a
100-record toolbar hit table plus a DWORD selected tile. It connects actual
board read/write/load/store and mode/key/window routing. Native host stdio
and original controlled CRT have independent files; complete outcomes agree.
Backspace clears only working tiles, while plus/minus store before switching
or clamping. See [editor evidence](EDITOR_OWNER.md).


`src/midi.c` owns the music pointer at `0x421060`, typed context/header arrays,
compact-event expansion and stream callback. Headers and context retain i686
layouts while growing with host pointers. The explicit stdcall import table
preserves original request contracts. Platform and final runtime music
operations now default to maintained wrappers; real Kernel32/WinMM binding
and asynchronous device effects remain open. See [music evidence](MIDI_OWNER.md).

Private Windows game links include the two REA-reviewed embedded resources.
`scripts/windows_resources.py` binds extraction to the original hash and full
resource manifest, emits a standard private resource object for each linker,
and records converter/input/product identities. Maintained C and the analysis
library stay shared. Public CI explicitly omits private resources while compiling
the same sources and the independent SDK resource reader. See
[embedded resource evidence](EMBEDDED_RESOURCES.md) for payload/bitmap controls
and the original startup identifier mismatch.
