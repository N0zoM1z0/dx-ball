# Reconstruction layout and current owner map

The original is a 32-bit Windows DirectX game, with statically linked Microsoft
CRT code mixed into `.text`. WinMain at `0x0040D930` is called by CRT startup
at `0x004187A0`. Do not classify whole address ranges as authored or runtime
without checking their individual evidence.

| Area | Target evidence / current work |
| --- | --- |
| Platform startup | `0x0040D930`, Win32 imports, fullscreen DirectDraw messages |
| Mode routing | `0x00403950`, mode global `0x00421074`, init/cleanup dispatch |
| Board owner | `src/boards.c`, bank I/O, editor copy, initialization, render traversal |
| Resource owner | `src/resources.c`, SBK ownership, PCX pixels, palettes and fonts |
| Sprite draw | `0x00404180`; exact API dispatch; hardware backend pending |
| Gameplay owner | `src/gameplay.c`; tile hits, explosive scan, linked-list append and sound pan |
| Audio/MIDI | DirectSound and WinMM imports, WAV/MDS references; pending |

`src/boards.h` defines one owner declaration shared by native and VC4.0 builds.
`DxBallInt` and `DxBallUInt` are explicit 32-bit scalars; opaque surface handles
use pointer-sized `size_t` for host compatibility. Legacy x86 builds use 32-bit
handles. No source selection macro changes any type or function body.

The rendering bridge injects only the unresolved sprite, background restoration,
and invalidation dependencies. Active-surface selection remains maintained code.
The target oracle uses original code for board routines and CRT memcpy/memset;
it intercepts file functions and the three rendering boundaries. This validates
state and effect traces while leaving Windows and pixel behavior unclaimed.

Project structure:

- `config/`: pinned identities, function/origin inventories, source/exact ledgers.
- `src/`: maintained C owners and the separate host board-inspection entry point.
- `scripts/`: attestation, REA/Ghidra queries, pinned builds, exact replay, reporting.
- `tests/`: target-machine differential and oracle rejection tests.
- `docs/`: accepted evidence, workflow, architecture, and handoff.
- `resources/`: generated public progress artwork; no original game artwork.

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
three 32-bit payload values. Brick effects, RNG, particles and DirectSound are
explicit pending dependencies. See [gameplay evidence](GAMEPLAY_OWNER.md).
