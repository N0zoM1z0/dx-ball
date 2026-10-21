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

October21 resumed status: the user explicitly resumed all270 authored exact
recoveries, with serial CPU/memory limits, frequent commits/pushes and periodic
cleanup. The maintained checkpoint is263/270 after verified frame-wait/resource/glyph/polygon adoption;
see the current handoff. Earlier stopped/unadopted records are historical.

Read [the current handoff](docs/agent/HANDOFF.md),
[workflow](docs/agent/WORKFLOW.md), and the relevant research note before changing
source. Use `config/functions.csv` to locate entries; reconcile imported extents
against instructions, exits and embedded data.

The user explicitly authorized relaxing reconstruction restrictions on
October 21, 2026. Follow [the standing search policy](docs/agent/SOURCE_CANDIDATE_SEARCH.md).
It supersedes older blanket bans on names, declaration/definition order, scope,
translation-unit organization and bounded build-recipe hypotheses. The user has
only the existing EXE/resources; reconstruct the missing context from them.
Do not ask again for original projects, PDB/MAP files or build records, or require
uniquely proved historical declarations before trying a recorded hypothesis.
Choose and execute eligible bounded families without renewed user approval.
Repair local tooling and evidence mappings within scope instead of treating
their failures as a new permission boundary. Keep exactness checks strict.
Keep routine execution lightweight: a short hypothesis, frozen compiler inputs,
the affected complete-unit comparison and a concise result are sufficient.
Independent reviews, bespoke orchestration, whole-workspace seals and replaying
unrelated historical evidence are not mandatory gates. Reuse verified receipts;
documentation-only changes do not invalidate unchanged compiler results.
Private module-first probes are allowed; compare the matching complete closure
before adoption, not as a prerequisite for rejecting an unpromising probe.
Unknown historical source details are experiment inputs, not permission gates.

- Run Python through `scripts/repo-python`.
- Use `scripts/rea` and the installed REA skill for new binary analysis.
  The project pins REA 6.5.0/Ghidra 12.1.4 in `config/rea.lock.json`.
  Retain full responses, Evidence IDs and snapshots under `.analysis/rea/`.
- Write natural typed source shared by portable and legacy builds. Preserve
  ABI, widths, ownership and actual state writes. Do not force matches with
  copied machine code, assembly, padding, fake locals or alternate profile bodies.
- New exact claims require complete units, compiler inputs and explicit
  relocation mappings. Compile each distinct frozen candidate once and compare
  all affected units, including accepted units sharing those inputs. Reuse
  results for identical input/flag digests instead of recompiling them.
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
