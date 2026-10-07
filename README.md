# DX-Ball

<p align="center">
  <img src="resources/progress.svg" alt="DX-Ball source reconstruction progress" width="900">
</p>

Source reconstruction of **DX-Ball v1.07**, the 1996 Windows breakout game by
Michael P. Welch, with original 3D graphics by Seumas McNally.

> [!IMPORTANT]
> Board data, sprite banks, fonts, PCX decoding and palettes now have **24 maintained
> functions**, **11,371 target differential cases**, and **13 byte-exact functions
> totaling 1,157 bytes**. The current builds provide a board-inspection utility and
> analysis library. A playable whole-game reconstruction is still in progress.

This project uses Ghidra 12.1.3 and a hash-pinned Visual C++ 4.0 compiler/linker
candidate. It follows the evidence and replay discipline of
[th095](https://github.com/N0zoM1z0/th095), with DX-Ball's own target, DirectX
interfaces, C owners, board formats, and compiler evidence. This is a separate
game-preservation project.

## Supported target

| Property | Value |
| --- | --- |
| Game | DX-Ball v1.07, English |
| Original release in included README | October 31, 1996 |
| Executable | `DXBALL.EXE`, 158,208 bytes |
| SHA-256 | `756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba` |
| Platform | Windows i386, DirectDraw / DirectSound / WinMM |
| Image base / entry | `0x00400000` / `0x004187A0` |
| PE linker | 3.00 |
| Compiler candidate | VC4.0, compiler 10.00.5270 / linker 3.00.5270 |

The original game, data, archives, toolchain binaries, and Ghidra database are
private local inputs and are not included. Supply the exact archive identified
in [target.toml](config/target.toml); another DX-Ball version cannot substitute
for this target.

## Local setup

The analysis workflow currently targets Linux x86-64 with Python 3.11+, Git,
Wine with win32 support, Xvfb, CMake, Ninja, GCC, and MinGW i686. Use
`scripts/repo-python` for all repository Python commands: it selects an
interpreter only after checking actual package and native-library hashes.

```bash
scripts/bootstrap-python.sh
scripts/repo-python scripts/bootstrap-tools.py
scripts/repo-python scripts/import-target.py /path/to/DX_Ball_Win_Preinstalled_EN.zip
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-toolchain.py --execute
scripts/repo-python scripts/ghidra.py initialize
```

For an existing local tool root, reuse its pinned Ghidra/JDK installation:

```bash
scripts/repo-python scripts/bootstrap-tools.py --reference-tools /path/to/th095/.tools
```

Version, archive, compiler-component, header/library, interpreter-package, and
native-engine identities are recorded in [tools.lock.toml](config/tools.lock.toml).
Compiler execution uses this repository's own ignored Wine prefix.

## Build and verify

```bash
# Public portable source and ledger checks; no original game required.
scripts/repo-python scripts/ci.py --public

# Complete private suite: target/Ghidra attestation, cold exact replay,
# rejection tests, original-x86 differential tests, and Windows utility runs.
scripts/repo-python scripts/ci.py

# Inspect one original board (1..50) as JSON.
build/native/dxball_boards original/DEFAULT.BDS 1
```

The shared C owner builds natively, with MinGW i386, and with the pinned VC4.0
compiler/linker. The native utility checks all 50 boards; both Windows utilities
run boards 1, 25, and 50 under Wine and reproduce the same JSON output.

```bash
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python tests/test_exact_oracle.py
scripts/repo-python tests/test_boards_differential.py
scripts/repo-python tests/test_resources_differential.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

Exact replay compares complete function sections with every reviewed relocation
applied and referenced strings verified. It never masks differing bytes. The
semantic oracle executes the original x86 functions and compares maintained C
state and ordered dependency calls. Resource tests also compare decoded pixel
buffers; drawing traces do not establish DirectDraw backend equivalence. Public GitHub Actions runs portable builds and
ledger validation; private-target oracles run locally.

## Reconstruction notes

- [Current handoff](docs/RE_HANDOFF.md), [architecture](docs/ARCHITECTURE.md),
  [workflow](docs/RE_WORKFLOW.md), and [knowledge base](docs/KNOWLEDGE_BASE.md).
- [Exact compiler evidence](docs/BUILD_MATCHING.md),
  [oracle matrix and limits](docs/ORACLES.md), and [progress](docs/PROGRESS.md).
- [Resource ownership and file formats](docs/RESOURCE_OWNER.md).
- `config/functions.csv`: 528 provisional candidates; boundaries and runtime
  origins still require review.
- `config/implemented.csv`, `semantic-acceptance.csv`, and `matches.csv`:
  independent source, scoped semantic, and complete byte-exact facts.

Upcoming owners include board-hit transitions,
ball/paddle physics, bonuses, Win32/DirectDraw integration, menus, sound, and
MIDI. Names and ownership are promoted only with target-local evidence.

## License and attribution

The maintained reconstruction source and repository tooling are available under
the [MIT license](LICENSE). Original DX-Ball code, game artwork, audio, data, and
third-party toolchains retain their respective rights and are not included.
The progress illustration is generated from reconstruction ledgers.
