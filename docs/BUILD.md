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
original. Keep the 640-by-480 resolution. The optional Windows runtime/play
checks now default to 24-bit Xvfb; `--display-depth 8` reproduces the historical
configuration. See [the display-depth comparison](research/WINDOWS_DISPLAY_DEPTH.md).

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

These builds share the reconstructed game source. The compiler configuration
and matching process are described in [Matching](MATCHING.md).

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
