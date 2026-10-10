# Working on the reconstruction

The goal is nearly 100% restoration of English DX-Ball v1.07 source and a
rebuildable, playable game. Prioritize complete game flows and exact restoration.
Keep the README short: explain the reconstruction approach and REA's role.
Put operational detail in these instructions or `docs/agent/`.

Read [the current handoff](docs/agent/HANDOFF.md),
[workflow](docs/agent/WORKFLOW.md), and the relevant research note before changing
source. Use `config/functions.csv` to locate entries; reconcile imported extents
against instructions, exits and embedded data.

- Run Python through `scripts/repo-python`.
- Use `scripts/rea` and the installed REA skill for new binary analysis.
  The project pins REA 4.1.0/Ghidra 12.1.4 in `config/rea.lock.json`.
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
  `--parallel 1`, and the 512 MiB Ghidra heap through the project entry points.
  Route automated game/audio probes to `PULSE_SINK=dxball_reconstruction_silent`.
- Keep originals in `original/`, tools in `.tools/`, products in `build/`,
  raw evidence in `.analysis/`, and databases in `ghidra-project/`; these are private.
  Publish recovered source, useful research notes and claim ledgers.
- Update the affected ledgers and progress when claims change. Preserve unique
  evidence before cleaning disposable products.
- Public commits and pushes are authorized. Subjects are English and begin
  `gpt-6.1-sol: `. Describe the source recovery, REA findings and actual validation.
