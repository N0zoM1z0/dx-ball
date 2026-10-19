# Build and play

Run these commands from the repository root. Linux builds use Python 3.11+,
CMake, Ninja, and GCC or Clang. Windows cross-builds also need i686 MinGW;
launching them on Linux needs Wine with 32-bit Windows support.

For a headless Wine display, use a 640-by-480 **24-bit Xvfb screen**:

```bash
xvfb-run -a -s '-screen 0 640x480x24' scripts/repo-python scripts/run-windows.py --profile vc40
```

The game still requests its original eight-bit DirectDraw mode. A 24-bit host
screen presents its palette correctly in the tested Wine environment; an
eight-bit Xvfb screen drops filled glyph and title pixels even in the unmodified
original. Keep the 640-by-480 resolution. The optional Windows runtime, play,
round, game-over and campaign checks now default to 24-bit Xvfb;
`--display-depth 8` reproduces the historical
configuration. See [the display-depth comparison](research/WINDOWS_DISPLAY_DEPTH.md).
Round and game-over checks also accept `--profile original`, `--profile vc40`
or `--profile windows-i686` to run only the affected control. The
[current game-over controls](research/GAMEOVER_DISPLAY_DEPTH.md) retain actual
life loss, name entry and complete ranking persistence through process restart.

## Set up the original files

The reconstruction targets English DX-Ball v1.07. Its identity is recorded in
[`config/target.toml`](../config/target.toml). Import a matching archive:

```bash
scripts/bootstrap-python.sh
scripts/repo-python scripts/import-target.py /path/to/DX_Ball_Win_Preinstalled_EN.zip
```

The importer puts the executable and game data under `original/`.

## Compile the Windows game

```bash
scripts/repo-python scripts/build-windows.py
scripts/repo-python scripts/run-windows.py --profile windows-i686
```

The build produces `build/windows-i686/dxball.exe` and `libdxball_core.dll`.
Compiler runtime support, including the POSIX toolchain's pthread dependency,
is linked into the core DLL; the isolated Wine launch needs no additional
compiler runtime DLL in the tested build.
The launcher prepares `build/runtime/windows-i686/` with that build and the
original game data, then starts it through Wine. To prepare a directory for
running on Windows, use `--prepare-only` and launch `dxball.exe` there.

For the original-era Visual C++ build:

```bash
scripts/repo-python scripts/bootstrap-tools.py
scripts/repo-python scripts/build-legacy.py
scripts/repo-python scripts/run-windows.py --profile vc40
```

For a game-only iteration, use `scripts/repo-python scripts/build-legacy.py --game-only`.
The builder reuses objects only after checking compiler identity, flags, current
source/header inputs and object hashes. Matching accepted owner objects take
precedence over previous game objects. `build/vc40/build.json` records each
reuse or compilation and its inputs; the default command still builds both
diagnostic tools as well as the game.

To build the optional restored-CRT entry profile, use
`scripts/repo-python scripts/build-legacy.py --restored-crt`, then
`scripts/repo-python scripts/run-windows.py --profile vc40-restored-crt`.
It builds only the game in `build/vc40-restored-crt/`, with explicit source and
remaining original-member dependencies. The [VC4 build and play record](research/CURRENT_VC4_BUILD.md)
distinguishes the verified delivery at717cc2f from the later intermediate EXE
at12ccdb1. The latter includes file-field/text-width,PCX,ranking and glyph
corrections and passes complete linked checks, but its play observation times
out returning to menu after pause/resume. Its cause remains unresolved.
The ZIP retains the earlier verified image. The subsequent
[last-brick Y correction](research/exact/LIGHTNING_Y_COORDINATE_WRAP.md) and
[six Blt coordinate sums](research/exact/BLT_COORDINATE_WRAP.md) are in
current source/matching objects/native library and has not been linked into a
new game. The bounded candidate review's concrete Blt gap is now closed;
next rebuild from current source before diagnosing the retained menu-init timeout.
The23 remaining nonexact functions and inventory/context proof limits stay explicit.
Full campaign and physical-driver acceptance remain
open. The earlier [entry integration evidence](research/RESTORED_CRT_GAME_ENTRY.md)
retains its own image identity.

The current private local bundle is
`build/delivery/dxball-v1.07-vc40-reconstructed.zip`. It contains the rebuilt game,
its verified supplied assets and extraction instructions; extract the whole
folder and run `dxball.exe` there. The adjacent manifest records every member.
This artifact and the original assets are excluded from a source-only clone.

These builds share the reconstructed game source. The compiler configuration
and matching process are described in [Matching](MATCHING.md).
The legacy build includes `cpp_allocator.cpp` so typed C++ `new/delete` use the
recovered heap. Its allocator flags and other owner overrides are recorded in
`build.json`; focused entry/link checks are described in the
[allocator note](research/ALLOCATOR_OWNER.md).
Allocator, list and resource files now use their maintained comparison recipes.
The linker selects one `LIBCMT` runtime while preserving the resource owner's
`/ML` compiler lowering. See [owner linkage and the focused game check](research/VC4_OWNER_LINKAGE.md).
Windows allocation defaults use real private-heap APIs. Standalone clients must
initialize the heap before allocating; the game wrapper and resource inspector
do so when needed. An earlier heap survives game-entry binding. See
[heap startup checks](research/WINDOWS_HEAP_STARTUP.md).

Windows builds import `DirectDrawCreate` and `DirectSoundCreate` from the SDK
libraries. MinGW supplies `ddraw` and `dsound`. The pinned legacy build uses
`scripts/directx_imports.py` and its own librarian to generate the two small
import libraries under `build/directx-imports/`, with decorated stdcall link
symbols and the original undecorated DLL exports. Generation receipts record
the librarian, definitions and library hashes; original game code is not copied.

The MinGW build leaves the three Windows diagnostic tools out of the default
build. Request one when needed, for example:

```bash
cmake --build build/windows-i686 --target dxball_state_reader --parallel 1
```

## Compile the portable library and tools

```bash
cmake -S . -B build/native -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/native --parallel 1
```

This produces `dxball_core` and the board/resource inspectors. The game frontend
uses Windows graphics and audio services. A Windows compile without the original
embedded resources is available through `build-windows.py --without-game-resources`.

See [the script map](../scripts/README.md) for analysis and targeted comparison
commands, and [the Windows notes](research/WINDOWS_ADAPTER.md) for recorded play runs.
