# Contributor reconstruction workflow

Authored recovery is complete. Start with [the handoff](HANDOFF.md) and
[progress](../PROGRESS.md), then follow the user's current scope. Long campaign
and frame-rate sampling runs were stopped. [AGENTS.md](../../AGENTS.md) sets
execution limits and publication rules.

## Source work

Read the relevant owner note. `config/functions.csv` maps original entries;
`config/function-origins.csv` classifies authored, runtime and generated code.
Use the [bounded source-candidate policy](SOURCE_CANDIDATE_SEARCH.md) for new
hypotheses. Original project files, PDBs and uniquely known identifiers are not
prerequisites.

Before compiler/binary work, verify the target, toolchain and tracking. Write
typed C/C++ shared by portable and legacy builds. Preserve ABI, widths,
ownership, state writes and call order. Freeze each distinct candidate and
compile it once. Compare the complete affected closure, including accepted
companions, relocations, local targets, literals and attached metadata. Reuse
unchanged outputs and receipts. Do not combine winners from incompatible inputs.

Use temporary outputs for experiments; leave canonical objects, receipts and
recorded historical results intact during validation. A failed helper does not
require rerunning a successful compiler. Repair the helper and reuse its output.
Adoption updates the actual source owners, recipes and affected ledgers.

## Checks

Default CI is `scripts/repo-python --stdlib scripts/ci.py`: full-checkout syntax,
ledger consistency, CMake configuration and private-artifact checks. It works
without original assets or private tools. Add `--build` for portable compilation.
Run comparator and behavior tests when their code or inputs change. Documentation
work uses current ledgers and existing conclusions, without a new game build.

Build serially with CMake `--parallel 1`. Compiler/provider/Wine jobs use one
allowed CPU in the 35% CPU, 384/512 MiB user systemd scope. Use the REA wrapper's
256 MiB heap and a silent audio sink. See [REA operations](REA.md).

For requested live checks, use a separate runtime copy and record the tested EXE
hash, environment and observed state. Distinguish normal application exit from
observer cleanup. Compare the original under the same conditions when a failure
needs a control. Follow [background execution](BACKGROUND_PLAY.md).

## Retention and publication

Keep necessary original inputs, the locked tools actually used, Ghidra projects,
current source/ledgers, complete comparison scripts and current useful products.
Keep knowledge as concise conclusions, remaining questions and failed approaches
worth avoiding. A file's age, old citation or former passing result is not by
itself a reason to keep it. Delete obsolete probes, duplicate evidence, archives
and cleanup reports without creating replacement archives or an audit framework.

Reuse identical Factory tools when available. Share immutable programs; keep each
game's Wine prefix, Ghidra project and writable state separate. Test uncertain
components while temporarily unavailable; restore on failure, remove the temporary
copy after success. Choose affected compile/link/resource/runtime checks, without
a default full-graph replay. Check the original environment before blaming a
trim for a failed test.

Update only affected ledgers. `config/playability-status.json` keeps dated checks
bound to their tested image; regenerate progress when those claims change.
Commit and push verified checkpoints to `origin/main` with English subjects
beginning `gpt-6.1-sol: `. Keep originals, tools and raw evidence untracked.
