# Build and play

Run these commands from the repository root. Linux builds use Python 3.11+,
CMake, Ninja, and GCC or Clang. Windows cross-builds also need i686 MinGW;
launching them on Linux needs Wine with 32-bit Windows support.

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
