# Working on the reconstruction

The goal is nearly 100% restoration of English DX-Ball v1.07 source and a
rebuildable, playable game. Prioritize complete game flows and exact restoration.
The user's first priority is recovering all functions as exactly as possible.
The user permits the 19 explicit original CRT members in the restored-CRT
delivery. Keep those dependencies documented and prioritize authored game
functions; removing the remaining x87/SEH runtime members is not a delivery gate.
Finish exact reconstruction first, then build and verify a playable game with
the original Visual C++ 4.0 compiler. Resume platform ports only after that.
Advance complete-function comparisons with focused checks; defer long full-game
campaigns until the function recovery work is ready for them.
Keep the README focused on the reconstruction approach and REA's role,
with sections that help readers follow the workflow.
Put operational detail in these instructions or `docs/agent/`.
Keep the centered title PNG and progress SVG in the README, both at 900px.

Read [the current handoff](docs/agent/HANDOFF.md),
[workflow](docs/agent/WORKFLOW.md), and the relevant research note before changing
source. Use `config/functions.csv` to locate entries; reconcile imported extents
against instructions, exits and embedded data.

- Run Python through `scripts/repo-python`.
- Use `scripts/rea` and the installed REA skill for new binary analysis.
  The project pins REA 6.5.0/Ghidra 12.1.4 in `config/rea.lock.json`.
  Retain full responses, Evidence IDs and snapshots under `.analysis/rea/`.
- Write natural typed source shared by portable and legacy builds. Preserve
  ABI, widths, ownership and actual state writes. Do not force matches with
  copied machine code, assembly, padding, fake locals or alternate profile bodies.
- New exact claims require complete units, compiler inputs and explicit
  relocation mappings. Compile once per stable family and compare the affected
  units, including accepted units sharing those inputs.
- Run only the minimum useful existing Oracle/replay or play check. Tests are
  optional; do not run the full historical queue by default or repeat unchanged
  checks. Remove redundant scripts and their obsolete references when appropriate.
- Use one writable compiler/provider session, one allowed CPU, CMake
  `--parallel 1`, and the 256 MiB Ghidra heap through the REA entry point.
  On this host, wrap compiler/provider/Wine commands in a user systemd scope
  with `CPUQuota=35%`, `MemoryHigh=384M` and `MemoryMax=512M`. This caps the
  whole process tree; do not overlap heavy tasks. Prefer retained evidence over
  another cold provider import. See `docs/agent/REA.md`.
  Route automated game/audio probes to `PULSE_SINK=dxball_reconstruction_silent`.
- Keep originals in `original/`, tools in `.tools/`, products in `build/`,
  raw evidence in `.analysis/`, and databases in `ghidra-project/`; these are private.
  Publish recovered source, useful research notes and claim ledgers.
- Update the affected ledgers and progress when claims change. Preserve unique
  evidence before cleaning disposable products.
- At each closed experiment, archive and member-hash verify useful evidence,
  then delete obsolete proposal objects, executables and copied inputs. Retain
  current tested products and useful incremental build caches; avoid accumulating
  unused build products between checkpoints.
- Commit and push verified checkpoints to the configured `origin/main`.
  The user resumed publishing; keep private originals/tools/evidence untracked.
  Subjects are English and begin
  `gpt-6.1-sol: `. Describe the source recovery, REA findings and actual validation.
