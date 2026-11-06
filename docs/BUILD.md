# Build and play

The current verified game uses the original Visual C++ 4.0 compiler and the
`vc40-restored-crt` profile. See [progress](PROGRESS.md) for completed checks and
[the build record](research/CURRENT_VC4_BUILD.md) for product identities.

Run commands from the repository root. Linux needs Python 3.11+, Wine with
32-bit support and the original English DX-Ball v1.07 archive. The
[workspace setup](SETUP.md) covers prerequisites and analysis tools.

## Build the current Windows game

```bash
scripts/bootstrap-python.sh
scripts/repo-python scripts/import-target.py /path/to/DX_Ball_Win_Preinstalled_EN.zip
scripts/repo-python scripts/bootstrap-tools.py
scripts/repo-python scripts/build-legacy.py --restored-crt
scripts/repo-python scripts/run-windows.py --profile vc40-restored-crt
```

Import verifies the archive and places the EXE/assets in `original/`. The build
writes `build/vc40-restored-crt/dxball.exe`, its map and `build.json`. It links
138 source objects, three integration objects and 19 original CRT members.
Reused objects are checked against compiler, flags, source/header inputs and
object hashes. The link receipt records each reuse or compilation.

The launcher copies the game and supplied data into
`build/runtime/vc40-restored-crt/`. To prepare that folder for Windows without
launching Wine:

```bash
scripts/repo-python scripts/run-windows.py --profile vc40-restored-crt --prepare-only
```

Keep the data files beside `dxball.exe` when running the prepared folder.

## Native Windows source build

The local Windows package has these entry points:

- `Build Reconstruction.cmd`: compile all 141 C/C++ units with English progress.
- `Play DX-Ball.cmd`: run the existing tested game.
- `Play Rebuilt DX-Ball.cmd`: run the new `build/game/dxball.exe`.

The package contains `reconstruction/src`, the pinned VC4 compiler/headers/libs,
support resources and `Build-Reconstruction.ps1`. Windows PowerShell 5.1 is
sufficient; no Python, WSL, Visual Studio installation or administrator rights
are needed on Windows. The normal launcher performs a full source compilation.
`Build-Reconstruction.ps1 -Incremental` reuses objects only after checking their
compiler/source/header/flag context and object hashes.

The build extracts exactly 19 approved original CRT members, links with
`/NODEFAULTLIB`, verifies the x86 PE output and prepares a separate playable
folder. It preserves the existing `game` folder and existing rebuilt score saves.
`build/build-report.json` and `build/logs` retain the result and compiler output.
The compiler processes run serially in a Windows job on one CPU, capped at 35%
of one CPU and 512 MiB job memory. Windows has no equivalent to the Linux
`MemoryHigh` reclaim setting; that Linux soft limit is not claimed here.

VC4 link 3.00 fails during Pass1 on this Windows 11 host without a compatibility
layer. The script sets `WIN7RTM` only for the linker child; compilation keeps its
audited context and no compatibility registry setting is changed. All 270
authored functions in the native objects match across 53 compiler closures.
The native image's code/data/imports/relocations match the tested Wine build;
only PE/resource build timestamps differ. See [the build record](research/CURRENT_VC4_BUILD.md).

To export a package from this prepared Linux workspace, first place the game,
assets and chosen `ddraw.dll`/`ddraw.ini` beside the destination, then run:

```bash
scripts/repo-python scripts/export-windows-build.py /path/to/package/reconstruction
```

The exporter requires the current verified build and pinned local toolchain.
It copies source and build inputs, with no precompiled game-function objects.
Tools and original assets remain local and are not published in Git.

## Windowed Windows play

The original game requests a 640×480 eight-bit exclusive DirectDraw mode.
The local Windows setup uses [cnc-ddraw v7.1](https://github.com/FunkyFr3sh/cnc-ddraw/releases/tag/v7.1.0.0)
for a 960×720, 4:3 GDI window with `windowed=true`, `fullscreen=false` and
`nonexclusive=true`. `maxfps=60` limits presentation; `maxgameticks=-1` leaves
game tick pacing to the reconstructed game. The EXE is unchanged by the wrapper.

`Ctrl+Tab` releases the cursor; clicking inside captures it again. The first
click can acquire capture, so a second click may be needed for the game action.
`Alt+Enter` toggles windowed/borderless output in this profile. `P` pauses the
game before switching away. The wrapper filters activation messages in windowed
mode, so this setup does not test the original exclusive surface-loss contract.

Original WAV and MIDI files have been restored after the temporary muted setup.
Restart the game to reload any silent buffers. Windows master volume, other
application volumes and the default device are not changed by the package.

## Windowed Linux play with Steam Proton

An [interactive Proton and Xephyr trial](research/LINUX_PROTON_WINDOWED.md)
documents how the separately supplied original EXE was opened in a 640×480
Linux window. It also records a CPU quota bottleneck observed during that trial.
This does not establish playability of a locally rebuilt EXE under Proton.

## Headless Wine

Use a 640×480, 24-bit Xvfb host screen:

```bash
xvfb-run -a -s '-screen 0 640x480x24' \
  scripts/repo-python scripts/run-windows.py --profile vc40-restored-crt
```

The game requests an eight-bit DirectDraw mode. A 24-bit host screen renders
its palette correctly in the tested Wine environment; eight-bit Xvfb drops
filled glyph/title pixels in both original and rebuilt programs. See
[the display comparison](research/WINDOWS_DISPLAY_DEPTH.md).

For automated runs that must leave a Windows/WSLg desktop and audio alone, use
a private Xvfb display, unset `WAYLAND_DISPLAY`, disable `winewayland.drv`, and
set `PULSE_SINK=dxball_reconstruction_silent`. That sink must be a muted
`module-null-sink`; do not change the default sink or use the host display for
`xdotool` input. Follow [background execution](agent/BACKGROUND_PLAY.md) and the
serial resource limits in [AGENTS.md](../AGENTS.md).
The [playability record](research/PLAYABILITY_20261031.md) separates these checks
from manual Windows feedback and the historical focus failure.

## Local delivery

`build/delivery/dxball-v1.07-vc40-reconstructed.zip` contains the tested EXE,
48 supplied assets and extraction instructions. Extract the whole folder and
run `dxball.exe`. Its adjacent manifest records all 50 members and validation.
Original assets and local build products are supplied separately from Git.

## Other builds

| Profile | Build | Launch |
| --- | --- | --- |
| VC4 with compiler CRT | `scripts/repo-python scripts/build-legacy.py --game-only` | `scripts/repo-python scripts/run-windows.py --profile vc40` |
| MinGW i686 | `scripts/repo-python scripts/build-windows.py` | `scripts/repo-python scripts/run-windows.py --profile windows-i686` |

The default `build-legacy.py` command also builds the two VC4 asset inspectors.
The MinGW game uses `dxball.exe` and `libdxball_core.dll`. Its compiler runtime
and pthread support are linked into the core DLL. DirectDraw/DirectSound imports
come from the platform SDK; the VC4 build generates its import libraries through
`scripts/directx_imports.py`.

To build the portable core and inspectors with CMake, Ninja and GCC or Clang:

```bash
cmake -S . -B build/native -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/native --parallel 1
```

The native library and Windows game share recovered source. Compiler owners and
per-source flags are described in [matching](MATCHING.md); the
[source map](../src/README.md) identifies the code behind each subsystem.
