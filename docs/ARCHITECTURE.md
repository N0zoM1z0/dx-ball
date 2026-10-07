# Reconstruction layout and current owner map

The original is a 32-bit Windows DirectX game, with statically linked Microsoft
CRT code mixed into `.text`. WinMain at `0x0040D930` is called by CRT startup
at `0x004187A0`. Do not classify whole address ranges as authored or runtime
without checking their individual evidence.

| Area | Target evidence / current work |
| --- | --- |
| Platform startup | `0x0040D930`, Win32 imports, fullscreen DirectDraw messages |
| Mode routing | `src/runtime.c`, mode global `0x00421074`, init/redraw/frame/cleanup dispatch; non-game modes pending |
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
| Audio/MIDI | DirectSound and WinMM imports, WAV/MDS references; pending |

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
terminal-level call order while leaving the original out-of-bank read unresolved.
`src/core.c` connects main ball physics and the gameplay frame to these owners.
`src/runtime.c` supplies real gameplay initialization and life-loss reset, plus
clock, score and paddle routines. Its mode table defaults mode 1 to maintained
source; other valid modes require configured implementations. All twelve frame
phases now default to maintained owners. The display owner supplies lightning,
dirty pages, sort/merge, palette animation and flip/wait dispatch; platform,
COM drivers, device creation, glyph UI and audio remain pending. Surface recovery,
color fills and palette fades now default to `src/device.c`. The third sprite
bank's count and allocation mode own addresses `0x4265AC` / `0x4265B0`; gameplay
initialization writes those fields rather than duplicated globals. See
[core evidence](CORE_OWNER.md), [runtime evidence](RUNTIME_OWNER.md) and
[display evidence](DISPLAY_OWNER.md) and [device evidence](DEVICE_OWNER.md).
