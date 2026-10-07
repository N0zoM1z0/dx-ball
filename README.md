# DX-Ball

<p align="center">
  <img src="resources/dxball-title.png" alt="DX-Ball title screen" width="900">
</p>

<p align="center">
  <img src="resources/progress.svg" alt="DX-Ball source reconstruction progress" width="900">
</p>

Source reconstruction of
**DX-Ball v1.07**, the 1996 Windows breakout game by
Michael P. Welch, with original 3D graphics by Seumas McNally.
Binary analysis uses [REA](https://github.com/morluto/rea) with its Ghidra
provider; original x86 execution and a pinned compiler check the recovered C.

> [!IMPORTANT]
> Core gameplay, lifecycle and frame drawing now join the board, resource and
> entity owners: **148 maintained functions**, **77,094 target differential cases**, and
> **40 byte-exact functions totaling 4,079 bytes**. The current builds provide inspection utilities and an
> analysis library. A playable whole-game reconstruction is still in progress.

DX-Ball serves as a working REA showcase: inspect a function, follow its callers
and state, recover maintainable source, then replay independent oracles.
For example, REA's instruction view recovered a missing sound-pan argument
from incomplete pseudocode; the resulting C passes 3,205 original-x86 cases
and reproduces all 63 compiled bytes. See the
[gameplay investigation](docs/GAMEPLAY_OWNER.md) for Evidence IDs and limits.
The [power-up investigation](docs/POWERUPS_OWNER.md) follows the bonus updater
through board effects and paddle rebounds, recovering the game's computed
trigonometry tables and checking its rounding against original execution.
The [core gameplay investigation](docs/CORE_OWNER.md) connects the main ball
updater to the full frame, testing collisions, shot damage and deferred powers
over 200 continuous frames. The [runtime investigation](docs/RUNTIME_OWNER.md)
follows the frame caller into initialization, paddle animation and life-loss
reset, checking 36 further connected frames through game-over dispatch. REA's
caller evidence distinguished the actual gameplay initializer from an intro
point-table routine. The [frame drawing investigation](docs/DISPLAY_OWNER.md)
connects last-brick lightning, dirty-region restoration and rectangle merging;
192 additional continuous frames execute all twelve maintained gameplay phases.
The [device recovery investigation](docs/DEVICE_OWNER.md) connects palette fades
and lost-surface recovery to real initialization, frame dispatch and redraw.
Following the shared bank layout also corrected two duplicated state fields.
The [Windows startup investigation](docs/PLATFORM_OWNER.md) follows WinMain
and the window procedure through device creation and game input, checking
4,742 original-x86 cases including startup failures and stdcall cleanup.
The [working-resource and UI investigation](docs/STARTUP_UI_OWNER.md) continues
into startup configuration, score files and vertical-blank timing, then recovers
text placement, original line pixels and palette operations in 1,424 cases.
Real Windows/driver integration, audio and non-game modes remain in progress.
We build on the evidence and
replay discipline of [th095](https://github.com/N0zoM1z0/th095), adapted to
DX-Ball's DirectX interfaces, C owners, board formats and compiler evidence.

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
private local inputs and are not included. The supplied title screenshot above
illustrates the original game. Supply the exact archive identified
in [target.toml](config/target.toml); another DX-Ball version cannot substitute
for this target.

## Get the original game

Download **`DX_Ball_Win_Preinstalled_EN.zip`** from the
[DX-Ball download page on Old Games Download](https://oldgamesdownload.com/game/dx-ball-m3r/).
The [English game README](https://oldgamesdownload.com/readme/dx-ball-windows-readme-english/)
identifies v1.07 and documents the original game. The README page contains the
manual; use the game page for the ZIP.

Keep the downloaded archive unchanged. Its expected SHA-256 is:

```text
e6c8a8d2b55e3d3bd5908b8febaab82493b2fb3e154877143f1266731a007cbb
```

The import command below verifies the archive, extracts local inputs into
ignored `original/`, and verifies the executable and asset manifest. A matching
archive plus the pinned tools lets readers replay every currently accepted
reconstruction checkpoint from this public repository. The complete playable
game remains work in progress.

## Local setup

The analysis workflow currently targets Linux x86-64 with Python 3.11+, Git,
Wine with win32 support, Xvfb, CMake, Ninja, GCC, MinGW i686, and
Node.js 22.19 with npm for the pinned REA runtime. Use
`scripts/repo-python` for all repository Python commands: it selects an
interpreter only after checking actual package and native-library hashes.

```bash
git clone https://github.com/N0zoM1z0/dx-ball.git
cd dx-ball
scripts/bootstrap-python.sh
scripts/repo-python scripts/bootstrap-tools.py
scripts/repo-python scripts/import-target.py /path/to/DX_Ball_Win_Preinstalled_EN.zip
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-toolchain.py --execute
scripts/repo-python scripts/bootstrap-rea.py
scripts/rea doctor --provider ghidra --json
```

For an existing local tool root, reuse its pinned JDK installation:

```bash
scripts/repo-python scripts/bootstrap-tools.py --reference-tools /path/to/th095/.tools
```

Version, archive, compiler-component, header/library, interpreter-package, and
native-engine identities are recorded in [tools.lock.toml](config/tools.lock.toml).
Compiler execution uses this repository's own ignored Wine prefix.
Builds run one job at a time. On Linux, project build and REA entry points keep
child processes on one allowed CPU; Ghidra's maximum Java heap is 512 MiB.
These resource limits keep the workflow modest and can make analysis slower.

REA and its npm dependencies are pinned in `config/rea/package-lock.json`;
`config/rea.lock.json` binds the installed runtime and Ghidra provider. Use
`scripts/rea` for project analysis. See [REA setup and showcase](docs/REA.md)
for MCP registration, evidence snapshots and the verified DX-Ball example.

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
The resource inspector decodes all seven supplied SBK banks and five PCX files;
native, MinGW and VC4.0 products reproduce identical metadata and pixel hashes.

```bash
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python tests/test_exact_oracle.py
scripts/repo-python tests/test_boards_differential.py
scripts/repo-python tests/test_resources_differential.py
scripts/repo-python tests/test_gameplay_differential.py
scripts/repo-python tests/test_effects_differential.py
scripts/repo-python tests/test_entities_differential.py
scripts/repo-python tests/test_powerups_differential.py
scripts/repo-python tests/test_core_differential.py
scripts/repo-python tests/test_runtime_differential.py
scripts/repo-python tests/test_display_differential.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

Exact replay compares complete function sections with every reviewed relocation
applied and referenced strings verified. It never masks differing bytes. The
semantic oracle executes the original x86 functions and compares maintained C
state and ordered dependency calls. Resource tests also compare decoded pixel
buffers; particle tests compare actual 2x2 writes to controlled 8-bit surfaces.
Drawing traces do not establish DirectDraw backend equivalence. Public GitHub Actions runs portable builds and
ledger validation; private-target oracles run locally.

To follow the sound-pan investigation with REA after setup:

```bash
scripts/rea function original/DXBALL.EXE 0x00406400 --provider ghidra \
  --snapshot .analysis/rea/dxball.snapshot.json --json
scripts/repo-python scripts/replay-exact-units.py --unit screen-pan
scripts/repo-python tests/test_gameplay_differential.py
```

The [REA workflow](docs/REA.md) explains retained Evidence and snapshots; the
[gameplay owner](docs/GAMEPLAY_OWNER.md) connects the returned instructions to
source, original behavior and acceptance limits.

## Reconstruction notes

- [Current handoff](docs/RE_HANDOFF.md), [architecture](docs/ARCHITECTURE.md),
  [workflow](docs/RE_WORKFLOW.md), and [knowledge base](docs/KNOWLEDGE_BASE.md).
- [Exact compiler evidence](docs/BUILD_MATCHING.md),
  [oracle matrix and limits](docs/ORACLES.md), and [progress](docs/PROGRESS.md).
- [Resource ownership and file formats](docs/RESOURCE_OWNER.md).
- [Brick-hit gameplay, explosions and sound pan](docs/GAMEPLAY_OWNER.md).
- [Explosion queues and brick animations](docs/EFFECTS_OWNER.md).
- [Particle updates, pixel writes and bonus production](docs/ENTITIES_OWNER.md).
- [Core ball physics and gameplay frame](docs/CORE_OWNER.md).
- [Game initialization, life-loss reset and mode routing](docs/RUNTIME_OWNER.md).
- [Lightning, dirty-region merging and frame presentation](docs/DISPLAY_OWNER.md).
- [REA analysis workflow and showcase](docs/REA.md).
- `config/functions.csv`: 528 provisional candidates; boundaries and runtime
  origins still require review.
- `config/implemented.csv`, `semantic-acceptance.csv`, and `matches.csv`:
  independent source, scoped semantic, and complete byte-exact facts.

Upcoming work includes Win32/input/device integration, surface recovery,
game-over and menu modes, sound and MIDI. Names and ownership
are promoted only with target-local evidence.

## License and attribution

The maintained reconstruction source and repository tooling are available under
the [MIT license](LICENSE). Original DX-Ball code, game artwork, audio, data, and
third-party toolchains retain their respective rights. The title screenshot is
included for illustration; original game binaries and asset files are not included.
The progress illustration is generated from reconstruction ledgers.
