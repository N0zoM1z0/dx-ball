# DX-Ball reconstruction

<p align="center">
  <img src="resources/dxball-title.png" alt="DX-Ball title screen" width="900">
</p>

This project reconstructs English DX-Ball v1.07 from its original executable
into readable C/C++ that can be rebuilt and played. We use
[REA](https://github.com/morluto/rea) to inspect the executable, recover the
functions, and guide the reconstruction. The tutorial below takes you from
downloading the game to continuing this work with Codex.

## Reconstruction with REA

REA gives the agent access to Ghidra's analysis of the executable: pseudocode,
instructions, calls, and data references. We use those observations to recover
the game's logic and object layouts. The immediate priority is to restore
every game function and make as many complete functions byte-exact as possible:
the rebuilt machine code should match the original once addresses for calls
and data are mapped. Comparing those bytes helps resolve details that
pseudocode can miss, such as argument widths, branch conditions, and the order
of state changes.

1. **Inspect a function with REA.** Read pseudocode alongside instructions,
   then follow its callers, callees, and data references to understand the logic
   and field layouts.
2. **Recover the source.** Turn those findings into typed C/C++ and connect
   the recovered functions into the game.
3. **Rebuild and refine.** Compile with VC4, compare the affected functions
   against the original executable, and use the differences to refine the source.
   Check the affected behavior when it helps answer a remaining question.

Saved REA responses connect the recovered source to its evidence. The
[worked example](docs/REA.md) follows a projectile-list routine from analysis
to source and a complete compiler match.

## Try the workflow with Codex

These steps continue the existing reconstruction on Linux x86-64. Install Git,
Python 3.11+ with pip, and Node.js 22.19.0 with npm. Use the official
[Node.js Linux x64 release](https://nodejs.org/download/release/v22.19.0/)
and put its `bin/` directory on your `PATH`: the project checks the Node
executable's hash as well as its version. The legacy compiler runs through
Wine, so also install Wine with 32-bit support, Xvfb, `xvfb-run`, `unzip`, and
`tar`. See [Build and play](docs/BUILD.md) for the other build targets.

### 1. Get the game and prepare the workspace

Download the English Windows archive from
[DX-Ball on Old Games Download](https://oldgamesdownload.com/game/dx-ball-m3r/).
Choose `DX_Ball_Win_Preinstalled_EN.zip` under **Windows (1996)**.
The [original English readme](https://oldgamesdownload.com/readme/dx-ball-windows-readme-english/)
identifies version 1.07 and describes the game and its controls. Keep the ZIP
intact; the importer extracts the executable and assets together.

Clone this repository, enter it, and import your download:

```bash
git clone https://github.com/N0zoM1z0/dx-ball.git
cd dx-ball
scripts/bootstrap-python.sh
scripts/repo-python scripts/import-target.py /absolute/path/to/DX_Ball_Win_Preinstalled_EN.zip
```

Replace the archive path with your download. The importer verifies the ZIP
and its game files, then places the executable and assets in `original/`.
The expected version and hashes are in [the target configuration](config/target.toml).
Use your fork's URL in the clone command if you want Codex to push your changes.

### 2. Install REA and connect it to Codex

Install the current CLI releases:

```bash
npm install --global @openai/codex@latest rea-agents@latest
codex --version
rea --version
```

Next, prepare the project's analysis engine and compiler from the repository root:

```bash
scripts/repo-python scripts/bootstrap-tools.py
scripts/repo-python scripts/bootstrap-rea.py
```

The first command installs the recorded JDK and Visual C++ 4.0 compiler.
The second installs REA 6.4.0 and Ghidra 12.1.4, as specified in
[the REA lock file](config/rea.lock.json). Tools stay in `.tools/`, and the
scripts verify their hashes. The global REA CLI connects Codex to the latest
release; the local copy keeps this repository's analysis and comparisons
reproducible.

Point REA at the installed Ghidra and JDK, then connect it to Codex:

```bash
export GHIDRA_INSTALL_DIR="$(pwd)/.tools/ghidra-rea"
export JAVA_HOME="$(pwd)/.tools/jdk"
rea setup --client codex
rea doctor --client codex --provider ghidra --json
```

Setup shows the changes it will make to Codex's configuration and skill files.
Accept the proposed REA integration. Setup registers the MCP server, records
the Ghidra and JDK paths, and installs the matching agent skill. The doctor
report checks the registration and provider; look for `healthy: true`.
If a check fails, follow the remedy in the report.

The [REA setup guide](https://github.com/morluto/rea/blob/main/docs/installation.md)
also covers using an existing Ghidra installation. During reconstruction,
Codex follows [the project REA instructions](docs/agent/REA.md) and uses
`scripts/rea`, which applies the repository's tool checks and resource limits.
When updating an existing Codex integration, rerun the installation and setup
commands above, then restart Codex.

### 3. Start Codex in the repository

From the same terminal, run:

```bash
codex
```

Sign in when prompted. Keep Codex in the repository root so it can read
`AGENTS.md`, find the original executable, and follow the source and research notes.
If Codex was already open when you configured REA, restart it to load the server
and skill. See the [Codex CLI guide](https://developers.openai.com/codex/cli/)
for installation and sign-in details.

### 4. Give Codex a reconstruction goal

A [Codex Goal](https://developers.openai.com/cookbook/examples/codex/using_goals_in_codex)
keeps the reconstruction moving across turns: inspect, recover, compare, then
choose the next unresolved function. It requires Codex 0.128.0 or newer.
Paste the following English prompt:

```text
/goal Reconstruct English DX-Ball v1.07 from original/DXBALL.EXE into readable
C/C++ that builds and reproduces the original game. Your first priority is to
recover all authored functions and make as many complete functions byte-exact
as possible using the project's Visual C++ 4.0 toolchain.

Read AGENTS.md, docs/agent/HANDOFF.md, and docs/agent/WORKFLOW.md. Use REA to
inspect instructions, calls, data layouts, and function boundaries. Reuse saved
evidence and work through unresolved functions in related groups.

Write natural source shared by the portable and legacy builds. Preserve the
original calling conventions, integer widths, ownership, and state changes.
Compile each stable batch once, compare complete functions with explicit
relocation mappings, and use the differences to refine the source. Recheck
existing exact functions that share the changed compiler inputs. Use focused
checks during recovery; defer long full-game campaigns until the functions
have been restored as far as possible.

Update the match ledgers, progress, and handoff with verified results. Keep
code and documentation in English. Use one CPU and one compiler or analysis
session at a time. Preserve unique evidence and clean disposable build products.
Commit verified checkpoints with the prefix "gpt-6.1-sol: " and push them
to my writable remote.

Continue through the entire function inventory, then verify the rebuilt game's
behavior. For functions that still differ, record the comparison and pursue
the remaining source corrections. If progress depends on missing tools or
inputs, report the specific blocker and what would resolve it.
```

You can steer the work with ordinary follow-up messages in the same thread.
Use `/goal` to view the objective, `/goal pause` to pause it, and `/goal resume`
to continue. As results arrive, the [matching guide](docs/MATCHING.md) explains
the comparisons and the [source map](src/README.md) helps you follow the code.

## Progress

<p align="center">
  <img src="resources/progress.svg" alt="DX-Ball source reconstruction progress" width="900">
</p>

The diagram tracks recovered functions and exact compiler matches. See the
[progress records](docs/PROGRESS.md) for current counts and the
[research notes](docs/research/README.md) for the recovered game flows.

## Build and explore

- [Build and play](docs/BUILD.md) — supply the original files, compile, and launch.
- [Source map](src/README.md) — find the modules behind each part of the game.
- [Architecture](docs/ARCHITECTURE.md) — follow startup, mode dispatch, and a frame.

DX-Ball was created by Michael P. Welch, with 3D graphics by Seumas McNally.
Original game files are supplied separately. See [LICENSE](LICENSE).
