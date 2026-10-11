# DX-Ball reconstruction

<p align="center">
  <img src="resources/dxball-title.png" alt="DX-Ball title screen" width="900">
</p>

This project reconstructs English DX-Ball v1.07 as readable C/C++ that can be
compiled into a working game. Codex uses [REA](https://github.com/morluto/rea)
to inspect the original executable through Ghidra, recover its functions, and
refine the source by comparing compiled code with the original.

To continue the reconstruction, follow the setup below and paste the English
`/goal` prompt into Codex.

## Reconstruction with REA

REA exposes Ghidra's pseudocode, instructions, calls, and data references as
tools Codex can query. We repeat three steps as each function takes shape:

1. **Inspect a function with REA.** Read pseudocode alongside instructions,
   then follow its callers, callees, and data references to understand the logic
   and field layouts.
2. **Recover the source.** Turn those findings into typed C/C++ and connect
   the recovered functions into the game.
3. **Rebuild and refine.** Compile with Visual C++ 4.0 and compare complete
   functions against the original executable. Use the differences to refine
   the source, with focused behavior checks where they help resolve a question.

A byte-exact match means the machine code agrees after mapping addresses for
calls and data. These comparisons help resolve argument widths, branch
conditions, and the order of state changes that pseudocode alone can miss.

Saved REA responses link source decisions to the executable. The
[worked example](docs/REA.md) follows a projectile-list routine from analysis
to source and a complete compiler match.

## Try the workflow with Codex

The commands below use Linux x86-64 and continue from this repository's
current source and research. Before you start, install:

- Git and Python 3.11+ with pip.
- Node.js 22.19.0 with npm. Use the official Linux x64 binary; the project
  checks the Node executable's hash as well as its version.
- Wine with 32-bit support, Xvfb with `xvfb-run`, `unzip`, and `tar`.
  Wine runs the original-era Windows compiler on Linux.

The setup scripts download the remaining tools. You can also follow
[Build and play](docs/BUILD.md) to compile and run the recovered game yourself.

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

Fork this repository on GitHub to publish checkpoints to your own copy.
Use your fork's URL in the clone command below and make sure your Git
credentials allow you to push to it. Then import the download:

```bash
git clone https://github.com/N0zoM1z0/dx-ball.git
cd dx-ball
scripts/bootstrap-python.sh
scripts/repo-python scripts/import-target.py /absolute/path/to/DX_Ball_Win_Preinstalled_EN.zip
```

Replace the archive path with your download. The importer verifies the ZIP
and its game files, then places `DXBALL.EXE` and the assets in `original/`.
The expected version and hashes are in [the target configuration](config/target.toml).
The original files stay in your local workspace; Git ignores `original/`.

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
installs the repository's fixed REA 6.4.0 and Ghidra 12.1.4 versions from
[the REA lock file](config/rea.lock.json). Both scripts verify their downloads
and keep the tools in `.tools/`. The global REA CLI configures Codex's
integration; `scripts/rea` uses the project copy for reproducible analysis.

Point REA at the installed Ghidra and JDK, then connect it to Codex:

```bash
export GHIDRA_INSTALL_DIR="$(pwd)/.tools/ghidra-rea"
export JAVA_HOME="$(pwd)/.tools/jdk"
rea setup --client codex
rea doctor --client codex --provider ghidra --json
```

Review and accept the changes shown by setup. It registers REA as an MCP
server so Codex can call its analysis tools. It also saves the Ghidra and JDK
paths and installs the REA skill with instructions for using those tools.
The doctor command checks the Codex registration and Ghidra provider. Look
for `healthy: true`; failed checks include instructions for fixing them.

The [REA setup guide](https://github.com/morluto/rea/blob/main/docs/installation.md)
also covers using an existing Ghidra installation. In this project, Codex
follows [the REA instructions](docs/agent/REA.md) and runs analysis through
`scripts/rea`, which checks the tools and applies the project's resource limits.
To update an existing integration, repeat the installation and setup commands,
then restart Codex.

### 3. Start Codex in the repository

From the same terminal, run:

```bash
codex
```

Sign in with your ChatGPT account or API key when prompted. Starting here lets
Codex read `AGENTS.md` and find the executable, source, and research notes.
Restart any Codex session that was open during REA setup so it loads the
integration. The [Codex CLI guide](https://developers.openai.com/codex/cli/)
explains installation and sign-in.

### 4. Give Codex a reconstruction goal

A [Codex Goal](https://developers.openai.com/cookbook/examples/codex/using_goals_in_codex)
keeps Codex working toward an outcome across turns. Paste the following into
Codex to continue from the current handoff. It asks Codex to recover functions,
check compiler matches, and publish verified checkpoints to your fork:

```text
/goal Reconstruct English DX-Ball v1.07 from original/DXBALL.EXE into readable,
rebuildable C/C++ that reproduces the game. Recover every authored function
and make as many complete functions byte-exact as possible with the project's
Visual C++ 4.0 toolchain. Finish function recovery before broader game validation.

Read AGENTS.md, docs/agent/HANDOFF.md, and docs/agent/WORKFLOW.md. Use REA to
inspect instructions, calls, data layouts, and function boundaries. Start
from the current handoff, reuse saved evidence, and work through unresolved
functions in related groups.

Write typed source shared by the portable and legacy builds. Preserve calling
conventions, integer widths, ownership, and state changes. Compile each stable
batch once and compare complete functions with explicit relocation mappings.
Use the differences to guide source corrections and recheck existing exact
functions affected by the changes. Use focused checks when they help resolve
a recovery question.

Record verified results in the match ledgers, progress, and handoff. Keep code
and documentation in English. Use one CPU and one compiler or analysis session
at a time. Preserve unique evidence and clean disposable build products.
Commit verified checkpoints with the prefix "gpt-6.1-sol: " and push to origin.

After recovering the functions, verify the rebuilt game's behavior. Report
remaining mismatches with their addresses, comparison results, and next steps.
If tools or inputs block progress, explain what is needed to continue.
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
