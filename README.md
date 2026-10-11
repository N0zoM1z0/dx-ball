# DX-Ball reconstruction

<p align="center">
  <img src="resources/dxball-title.png" alt="DX-Ball title screen" width="900">
</p>

This project reconstructs English DX-Ball v1.07 from its original executable
into readable C/C++ that can be rebuilt and played. We use
[REA](https://github.com/morluto/rea) to inspect the executable, recover the
functions, and compare the rebuilt code with the original. You can follow
the same process with Codex using the tutorial below.

## Reconstruction with REA

REA gives the agent access to Ghidra's analysis of the executable: pseudocode,
instructions, calls, and data references. We use those observations to recover
the game's logic and object layouts. The immediate priority is to restore
every game function and make as many complete functions byte-exact as possible.
Comparing the compiled bytes helps resolve details that pseudocode can miss,
such as argument widths, branch conditions, and the order of state changes.

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

You can use this repository as a starting point and continue the reconstruction
with your own Codex session. These steps use Linux x86-64 with Git, Python
3.11+ and pip, and Node.js 22.19.0 with npm. The repository's analysis scripts
check the recorded Node executable as well as the analysis tools. Building
with the legacy compiler also needs Wine with 32-bit support, Xvfb, and
`xvfb-run`; the other build requirements are listed in [Build and play](docs/BUILD.md).

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

Replace the archive path with the file you downloaded. The importer checks
the archive and each game file against [the recorded target](config/target.toml),
then places them in `original/`. A successful import reports the number of
verified and imported files. Codex can now work with `original/DXBALL.EXE`,
the game data, and the recovered source in one directory. To publish your own
changes, use your fork's URL in the clone command.

### 2. Install REA and connect it to Codex

Install the current CLI releases:

```bash
npm install --global @openai/codex@latest rea-agents@latest
codex --version
rea --version
```

REA uses Ghidra to analyze this Windows executable. Prepare the project's
recorded tools from the repository root:

```bash
scripts/repo-python scripts/bootstrap-tools.py
scripts/repo-python scripts/bootstrap-rea.py
```

The first command downloads the JDK and Visual C++ 4.0 compiler. The second
installs the project's REA package and Ghidra. These tools stay in `.tools/`;
the scripts verify their recorded hashes. This also prepares the compiler
Codex will use for function comparisons.

Point REA at the installed Ghidra and JDK, then connect it to Codex:

```bash
export GHIDRA_INSTALL_DIR="$(pwd)/.tools/ghidra-rea"
export JAVA_HOME="$(pwd)/.tools/jdk"
rea setup --client codex
rea doctor --client codex --provider ghidra --json
```

Setup shows the changes it will make to Codex's configuration and skill files.
Accept the proposed REA integration. It registers the MCP server, records the
Ghidra and JDK paths, and installs the matching agent skill. The doctor report
checks both that registration and the Ghidra provider; look for `healthy: true`
in its JSON output. If a check fails, follow the remedy shown in the report.

The [REA setup guide](https://github.com/morluto/rea/blob/main/docs/installation.md)
also covers using an existing Ghidra installation. During reconstruction,
Codex follows [the project REA instructions](docs/agent/REA.md) and uses
`scripts/rea`, which applies the repository's tool checks and resource limits.

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
keeps Codex working toward an objective across turns. For this project, that
means inspecting a function, recovering its source, comparing it, and moving
to the next unresolved function. Goals require Codex 0.128.0 or newer.
Paste this English prompt into Codex:

```text
/goal Reconstruct English DX-Ball v1.07 from original/DXBALL.EXE into readable
C/C++ that rebuilds and reproduces the original game. First, recover every
authored function and make as many complete functions byte-exact as possible
with the original compiler.

Read AGENTS.md, docs/agent/HANDOFF.md, and docs/agent/WORKFLOW.md. Use REA to
resolve instructions, calls, data layouts, and function boundaries. Reuse
saved evidence. Work through the remaining non-exact functions and investigate
unclassified entries, choosing a related group of functions for each batch.

Write natural source shared by the portable and legacy builds. Preserve the
original ABI, integer widths, ownership, and state changes. Compare complete
compiled functions using explicit relocation mappings, and use the byte
differences to guide corrections. Compile each stable batch once and check
the affected functions, including existing exact matches that share its inputs.
Use focused checks while restoring functions. Run long full-game campaigns
after the function recovery work is ready.

Update the match ledgers, progress, and handoff with verified results. Keep
code and documentation in English. Use one CPU and one compiler or provider
session at a time. Preserve unique evidence and clean disposable build products
regularly. Commit verified checkpoints with the prefix "gpt-6.1-sol: " and
push them to my writable remote when configured.

Continue until the function inventory is accounted for and the reconstructed
game builds and passes the relevant behavior checks. Record any functions that
still differ, what the comparison shows, and what is needed to resolve them.
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
