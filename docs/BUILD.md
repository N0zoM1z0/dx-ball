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

Automated checks use the silent audio sink and the serial resource limits in
[AGENTS.md](../AGENTS.md). The [playability record](research/PLAYABILITY_20261022.md)
contains the current input flows, results and remaining focus-recovery problem.

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
