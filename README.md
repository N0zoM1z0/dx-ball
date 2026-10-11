# DX-Ball reconstruction

<p align="center">
  <img src="resources/dxball-title.png" alt="DX-Ball title screen" width="900">
</p>

This project reconstructs English DX-Ball v1.07 from its original executable
into readable C/C++ that can be rebuilt and played. It shows how
[REA](https://github.com/morluto/rea) helps a coding agent recover a real game:
follow its behavior, understand the original code, and rebuild the pieces
into a working whole.

## Reconstruction with REA

REA gives the agent access to Ghidra's analysis of the executable: pseudocode,
instructions, calls, and data references. We use those observations to recover
the game's logic and object layouts, working through complete flows such as
startup, a gameplay frame, or sprite loading.

1. **Trace a game behavior with REA.** Follow calls and data references, then
   read pseudocode alongside instructions to establish the logic, field layouts,
   and order of state changes.
2. **Recover the source.** Turn those findings into typed C/C++ and connect
   the recovered functions into the game.
3. **Rebuild and refine.** Compile with VC4, compare the affected functions
   against the original executable, and check the restored behavior. Differences
   guide the next focused REA query.

Saved REA responses connect the recovered source to its evidence. The
[worked example](docs/REA.md) follows a projectile-list routine from analysis
to source and a complete compiler match.

## Try the workflow with Codex

You can use this repository as a starting point and continue the reconstruction
with your own Codex session. The steps below use a Linux terminal with Git,
Python 3.11+, and Node.js 22.19.0 with npm installed.

### 1. Get the game and prepare the workspace

Download the English Windows archive from
[DX-Ball on Old Games Download](https://oldgamesdownload.com/dx-ball/).
The [original English readme](https://oldgamesdownload.com/readme/dx-ball-windows-readme-english/)
identifies version 1.07 and describes the game and its controls. Keep the ZIP;
the importer extracts the executable and assets together.

Clone this repository, enter it, and import your download:

```bash
git clone https://github.com/N0zoM1z0/dx-ball.git
cd dx-ball
scripts/bootstrap-python.sh
scripts/repo-python scripts/import-target.py /absolute/path/to/DX_Ball_Win_Preinstalled_EN.zip
```

Replace the archive path with the file you downloaded. The importer checks the
target identity and puts the files in `original/`. This gives Codex the original
`DXBALL.EXE`, its data files, and the existing source and comparison records in
one workspace. If you want to publish your changes, clone your own fork instead.

### 2. Install REA and connect it to Codex

Install the current CLI releases:

```bash
npm install --global @openai/codex@latest rea-agents@latest
```

For this native Windows executable, REA needs a disassembler. We use Ghidra.
Download and extract [Ghidra](https://github.com/NationalSecurityAgency/ghidra/releases),
install its required JDK, and set both installation paths in your terminal:

```bash
export GHIDRA_INSTALL_DIR=/absolute/path/to/ghidra_12.1.4_PUBLIC
export JAVA_HOME=/absolute/path/to/jdk-21
rea setup --client codex
rea doctor --client codex --provider ghidra --json
```

Use your actual Ghidra and JDK directories. Setup shows the configuration changes,
registers the REA MCP server, and installs its matching agent skill. Accept those
changes, then check the doctor report for Codex registration and Ghidra readiness.
The [REA setup guide](https://github.com/morluto/rea/blob/main/docs/installation.md)
covers installation paths and provider configuration.

For reproducible compiler comparisons, the repository also provides pinned REA,
Ghidra, JDK, and Visual C++ toolchains through its bootstrap scripts. The agent
can prepare those using [Build and play](docs/BUILD.md) and
[the project REA instructions](docs/agent/REA.md).

### 3. Start Codex in the repository

From the same terminal, run:

```bash
codex
```

Sign in when prompted. Starting from the repository root lets Codex read
`AGENTS.md`, find the original executable, and use the source and research notes.
If Codex was already open when you configured REA, restart it to load the server
and skill. See the [Codex CLI guide](https://developers.openai.com/codex/cli/)
for installation and sign-in details.

### 4. Give Codex a reconstruction goal

A [Codex Goal](https://developers.openai.com/cookbook/examples/codex/using_goals_in_codex)
keeps the objective active across turns, so the agent can investigate, edit,
compare, and choose the next function without a fresh request each time.
Paste this English prompt into Codex:

```text
/goal Reconstruct English DX-Ball v1.07 from original/DXBALL.EXE into readable,
rebuildable C/C++ that reproduces the original game. First priority: recover
every authored function and make as many complete functions byte-exact as
the evidence and original compiler allow.

Read AGENTS.md, docs/agent/HANDOFF.md, and docs/agent/WORKFLOW.md. Use REA to
resolve instructions, calls, data layouts, and function boundaries. Reuse saved
evidence and prepare the documented toolchains before compiling. Work through
the remaining non-exact functions and investigate unclassified entries.

Use natural source shared by the builds, preserving the original ABI, widths,
ownership, and state changes. Compare complete emitted functions with explicit
relocation mappings. Let concrete byte differences guide each correction.
Compile once per stable source change and check the affected units, including
previous exact matches that share their inputs. Keep tests focused; reserve
long full-game campaigns for after the function recovery work.

Update the match ledgers and progress from verified results. Keep code and
documentation in English. Limit CPU and memory use, preserve unique evidence,
and regularly clean disposable build products. Commit verified checkpoints
with the prefix "gpt-6.1-sol: " and push to my writable remote when configured.

Continue toward the full reconstruction. At completion, verify the source,
complete-function matches, builds, and game behavior, and explain any remaining
compiler or source uncertainties with their evidence.
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
