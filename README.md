# DX-Ball reconstruction

<p align="center">
  <img src="resources/dxball-title.png" alt="DX-Ball title screen" width="900">
</p>

This project reconstructs English DX-Ball v1.07 as readable C/C++ that can be
compiled into a working game. Codex uses [REA](https://github.com/morluto/rea)
to inspect the original executable through Ghidra, recover its functions, and
refine the source by comparing compiled code with the original.

## Reconstruction with REA

REA gives Codex access to Ghidra's pseudocode, instructions, calls, and data
references. The reconstruction proceeds function by function:

1. **Inspect a function with REA.** Read pseudocode alongside instructions,
   then follow its callers, callees, and data references to understand the logic
   and field layouts.
2. **Recover the source.** Turn those findings into typed C/C++ and connect
   the recovered functions into the game.
3. **Rebuild and refine.** Compile with Visual C++ 4.0 and compare complete
   functions against the original executable. Use the differences to refine
   the source. Run a focused behavior check when the comparison leaves a
   question about what the function does.

A byte-exact match means the entire function's machine code agrees after
mapping addresses for calls and data. The original and rebuilt programs place
functions and globals at different addresses, so those references need an
explicit mapping. The remaining bytes help resolve argument widths, branch
conditions, and the order of state changes that pseudocode alone can miss.

Saved REA responses link source decisions to the executable. The
[worked example](docs/REA.md) follows a projectile-list routine from analysis
to source and a complete compiler match.

## Try the workflow with Codex

The tutorial below uses Linux x86-64 and continues the reconstruction from
this repository's source and research. You will need:

- Git and Python 3.11+ with pip.
- Node.js 22.19.0 with npm. Use the official Linux x64 binary; the project
  checks the Node executable's hash as well as its version.
- Wine with 32-bit support, Xvfb with `xvfb-run`, `unzip`, and `tar`.
  Wine runs the original-era Windows compiler on Linux.
- CMake, Ninja, and GCC or Clang to build the portable source.

The setup scripts install the JDK, Ghidra, and Visual C++ 4.0 compiler.

If you need the matching Node version, download
[`node-v22.19.0-linux-x64.tar.gz`](https://nodejs.org/download/release/v22.19.0/node-v22.19.0-linux-x64.tar.gz)
and extract it into a directory you own. For example, with the archive in
your Downloads directory:

```bash
mkdir -p "$HOME/.local/opt"
tar -xzf "$HOME/Downloads/node-v22.19.0-linux-x64.tar.gz" -C "$HOME/.local/opt"
export PATH="$HOME/.local/opt/node-v22.19.0-linux-x64/bin:$PATH"
node --version
npm --version
```

`node --version` should print `v22.19.0`. Keep using this terminal for the
remaining steps. Add the `export PATH` line to your shell configuration if
you want it available in future terminals.

### 1. Get the game and prepare the workspace

Download the English Windows archive from
[DX-Ball on Old Games Download](https://oldgamesdownload.com/game/dx-ball-m3r/).
Choose `DX_Ball_Win_Preinstalled_EN.zip` under **Windows (1996)**.
The [original English readme](https://oldgamesdownload.com/readme/dx-ball-windows-readme-english/)
identifies version 1.07 and describes the game and its controls. Keep the ZIP
intact; the importer extracts the executable and assets together.

Fork [this repository](https://github.com/N0zoM1z0/dx-ball) on GitHub so Codex
can publish checkpoints to your copy. Replace `YOUR_GITHUB_USERNAME` below
with your username, and use Git credentials that can push to the fork:

```bash
git clone https://github.com/YOUR_GITHUB_USERNAME/dx-ball.git
cd dx-ball
scripts/bootstrap-python.sh
scripts/repo-python scripts/import-target.py /absolute/path/to/DX_Ball_Win_Preinstalled_EN.zip
```

Replace the archive path with your download. The importer checks the ZIP and
its game files against [the target configuration](config/target.toml), then
puts `DXBALL.EXE` and the assets in `original/`. Its final line reports how
many files were verified and imported. Git ignores this directory.

### 2. Install REA and connect it to Codex

Install or update Codex and REA. The `/goal` workflow used below requires
Codex 0.128.0 or newer:

```bash
npm install --global @openai/codex@latest rea-agents@latest
codex --version
rea --version
```

From the repository root, install the project's compiler and analysis tools:

```bash
scripts/repo-python scripts/bootstrap-tools.py
scripts/repo-python scripts/bootstrap-rea.py
```

The first command installs the JDK and Visual C++ 4.0 compiler. The second
installs REA and Ghidra from [the project's lock file](config/rea.lock.json),
currently REA 6.4.0 and Ghidra 12.1.4. Both scripts verify their downloads
and keep the tools in `.tools/`. The global REA CLI configures Codex;
the project's `scripts/rea` command uses the locked tools for analysis.

Point REA at the installed Ghidra and JDK, then connect it to Codex:

```bash
export GHIDRA_INSTALL_DIR="$(pwd)/.tools/ghidra-rea"
export JAVA_HOME="$(pwd)/.tools/jdk"
rea setup --client codex
rea doctor --client codex --provider ghidra --json
```

Setup shows the configuration changes for you to review and accept. It
registers REA as an MCP server, saves the Ghidra and JDK paths, and installs
the REA skill with instructions for Codex. The doctor command checks the
registration and Ghidra provider. Look for `healthy: true`, or follow the
instructions beside a failed check.

The [REA setup guide](https://github.com/morluto/rea/blob/main/docs/installation.md)
also covers using an existing Ghidra installation. To update an existing
integration, repeat the global installation and setup commands, then restart
Codex. Project analysis follows [the REA instructions](docs/agent/REA.md).

### 3. Start Codex in the repository

From the same terminal, run:

```bash
codex
```

Sign in when prompted; the [Codex CLI guide](https://developers.openai.com/codex/cli/)
explains the authentication options. Codex reads `AGENTS.md` from this
checkout and can inspect the original executable, recovered source, and
research notes. Restart Codex if it was running during REA setup so it loads
the newly registered tools.

### 4. Give Codex a reconstruction goal

A [Codex Goal](https://developers.openai.com/cookbook/examples/codex/using_goals_in_codex)
keeps Codex working toward an outcome across turns. Paste this prompt into
Codex. It makes function recovery the first priority and asks Codex to push
verified checkpoints to your fork:

```text
/goal Reconstruct English DX-Ball v1.07 from original/DXBALL.EXE as readable,
rebuildable C/C++. First recover every game-authored function as faithfully as
possible and maximize complete byte-exact matches with Visual C++ 4.0. Once
function recovery is complete, validate the rebuilt game's full behavior.

Read AGENTS.md, docs/agent/HANDOFF.md, and docs/agent/WORKFLOW.md. Continue from
the handoff, using REA to inspect unresolved functions and their callers,
callees, and data. Reuse saved evidence and recover related functions together.

Write typed source shared by the portable and legacy builds, preserving the
original calling conventions, integer widths, ownership, and state changes.
Compile each stable batch and compare whole functions with explicit mappings
for address references. Fix the differences and recheck affected exact matches.
Use focused checks to answer recovery questions along the way.

Record verified results in the match ledgers, progress, and handoff. Keep code
and documentation in English. Follow the project's resource limits and clean
disposable build products after preserving unique evidence. Commit verified
checkpoints with the prefix "gpt-6.1-sol: " and push to origin/main.

Report progress through recovered functions and exact matches. For remaining
mismatches, give the function addresses, comparison results, and next steps.
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
