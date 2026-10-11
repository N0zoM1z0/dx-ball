# DX-Ball reconstruction

<p align="center">
  <img src="resources/dxball-title.png" alt="DX-Ball title screen" width="900">
</p>

This project reconstructs English DX-Ball v1.07 from its original executable
into readable, rebuildable C/C++. [REA](https://github.com/morluto/rea) lets
Codex inspect the executable and use Ghidra's analysis to recover the source.
The tutorial below shows how to get the game, set up the tools, and continue
the reconstruction with a Codex Goal.

## Reconstruction with REA

REA gives Codex access to Ghidra's pseudocode, instructions, calls, and data
references. We use them in a repeated cycle:

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

The first priority is to restore every game function as exactly as possible.
During recovery, focused checks answer questions about the affected code;
broader game testing follows once the function work is ready. Saved REA
responses let readers trace source decisions back to the executable. The
[worked example](docs/REA.md) follows a projectile-list routine from analysis
to source and a complete compiler match.

## Try the workflow with Codex

These steps continue this repository's reconstruction on Linux x86-64.
Before you start, install:

- Git and Python 3.11+ with pip.
- Node.js 22.19.0 with npm, from the official
  [Linux x64 release](https://nodejs.org/download/release/v22.19.0/).
  Put its `bin/` directory on your `PATH`; the project verifies the Node
  executable's hash as well as its version.
- Wine with 32-bit support, Xvfb with `xvfb-run`, `unzip`, and `tar`.
  Wine runs the original-era Windows compiler on Linux.

The scripts below download the remaining tools. For building and launching
the game, see [Build and play](docs/BUILD.md).

### 1. Get the game and prepare the workspace

Download the English Windows archive from
[DX-Ball on Old Games Download](https://oldgamesdownload.com/game/dx-ball-m3r/).
Choose `DX_Ball_Win_Preinstalled_EN.zip` under **Windows (1996)**.
The [original English readme](https://oldgamesdownload.com/readme/dx-ball-windows-readme-english/)
identifies version 1.07 and describes the game and its controls. Keep the ZIP
intact; the importer extracts the executable and assets together.

Clone this repository and import your download. If you want Codex to push
checkpoints to your own repository, fork it first and use your fork's URL:

```bash
git clone https://github.com/N0zoM1z0/dx-ball.git
cd dx-ball
scripts/bootstrap-python.sh
scripts/repo-python scripts/import-target.py /absolute/path/to/DX_Ball_Win_Preinstalled_EN.zip
```

Replace the archive path with your download. The importer verifies the ZIP
and its game files, then places `DXBALL.EXE` and the assets in `original/`.
The expected version and hashes are in [the target configuration](config/target.toml).

### 2. Install REA and connect it to Codex

Install or update Codex and REA:

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
and keep the tools in `.tools/`. The global CLI supplies the current Codex
integration; the project uses its local REA copy for reproducible analysis.

Point REA at the installed Ghidra and JDK, then connect it to Codex:

```bash
export GHIDRA_INSTALL_DIR="$(pwd)/.tools/ghidra-rea"
export JAVA_HOME="$(pwd)/.tools/jdk"
rea setup --client codex
rea doctor --client codex --provider ghidra --json
```

Review and accept the REA integration shown by setup. It registers the MCP
server in Codex's configuration, saves the Ghidra and JDK paths, and installs
the REA skill that guides the agent's analysis. The doctor command checks the
Codex registration and Ghidra provider. Look for `healthy: true`; failed checks
include instructions for fixing them.

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
lets Codex keep working toward an outcome across turns. It requires Codex
0.128.0 or newer. The prompt below starts from the repository's current
handoff and prioritizes function recovery. If your fork is ready for pushes,
paste it into Codex:

```text
/goal Reconstruct English DX-Ball v1.07 from original/DXBALL.EXE into readable,
rebuildable C/C++ that reproduces the game. Recover every authored function
and make as many complete functions byte-exact as possible with the project's
Visual C++ 4.0 toolchain. Function recovery is the first priority.

Read AGENTS.md, docs/agent/HANDOFF.md, and docs/agent/WORKFLOW.md. Use REA to
inspect instructions, calls, data layouts, and function boundaries. Start
from the current handoff, reuse saved evidence, and work through unresolved
functions in related groups.

Write natural source shared by the portable and legacy builds. Preserve the
original calling conventions, integer widths, ownership, and state changes.
Compile each stable batch once and compare complete functions with explicit
relocation mappings. Refine the source from those differences, and recheck
existing exact functions affected by the changes. Use focused checks during
recovery. Run broader game validation after restoring the functions as far
as possible.

Record verified results in the match ledgers, progress, and handoff. Keep code
and documentation in English. Use one CPU and one compiler or analysis session
at a time. Preserve unique evidence and clean disposable build products.
Commit verified checkpoints with the prefix "gpt-6.1-sol: " and push to origin.

Work through the entire function inventory, pursuing source corrections for
every remaining mismatch, then verify the rebuilt game's behavior. If missing
tools or inputs block progress, explain what is needed to continue.
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
