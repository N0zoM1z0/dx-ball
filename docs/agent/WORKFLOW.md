# Contributor reconstruction workflow

Authored exact recovery is complete. Start with [the handoff](HANDOFF.md) and
[progress](../PROGRESS.md); the current priority is live-game validation.
[AGENTS.md](../../AGENTS.md) sets execution limits and publication rules.

## Establish the question

Inspect the worktree and the relevant owner note. Use `config/functions.csv`
for entry ownership and `config/function-origins.csv` for origin classification.
Reuse saved REA evidence before opening another session. Identify the behavior,
call boundary or compiler difference the next step will resolve.

For source recovery, follow the authorized [bounded source-candidate policy](SOURCE_CANDIDATE_SEARCH.md).
Natural identifiers, declaration order, scope, translation-unit organization and
build-context hypotheses may be tested as finite families. Keep each hypothesis
and its affected inputs explicit. Missing historical project files do not prevent
these trials; the policy describes how to distinguish a matching reconstruction
from uniquely recovered source spelling.

Before new binary/compiler work, verify its inputs:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-toolchain.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Use the pinned [REA commands](REA.md) and Ghidra provider. Retain full responses,
Evidence IDs and unresolved gaps in `.analysis/rea/`, then save/close the session.

## Change and verify one coherent scope

Write typed C/C++ shared by portable and legacy builds. Follow each function
through its exits and inline data, and establish structures from producers and
consumers. Preserve ABI, integer widths, state writes and resource ownership.
Use the real shared API when connecting owners or adapting an existing fixture.

Freeze each distinct candidate, compile it once and compare the complete affected
closure. Reuse results with identical source/header/flag identities. A proposed
source split must verify every affected object before adoption.

For an exact claim, record all compiler inputs, recursive project headers, flags,
extent and relocation bindings in `config/match-units.toml`. Retain the previous
object/report before replacing it. Replay all accepted units sharing changed
inputs, literals or metadata. Compare complete spans and literal contents; the
[local-target guard](../research/exact/EXACT_LOCAL_TARGET_GUARD.md) also checks
actual internal COFF destinations.

Build the affected target using [BUILD.md](../BUILD.md), with CMake `--parallel 1`.
Choose focused checks for changed behavior. Documentation and status edits use
retained receipts and ledger checks; they do not require another game build.

## Verify live behavior

Use a separate runtime copy and record the tested executable hash, environment,
input path and observed state. Keep normal application exit distinct from observer
cleanup. For a failure, retain the failing trace and compare the original under
the same conditions when that will narrow the cause. Follow the current focus
investigation in [the playability record](../research/PLAYABILITY_20261022.md).

Run one writable compiler/provider/Wine session at a time under the resource limits
in AGENTS.md. Route automated audio to the dedicated silent capture sink.

## Record and publish

Update the owner note with the result, useful evidence and remaining question.
Change only the ledgers affected by the work: `implemented.csv` for source,
`semantic-acceptance.csv` for scoped behavior and `matches.csv` for exact units.
Update `config/playability-status.json` when the tested image or live results
change, then run `scripts/repo-python scripts/progress.py`.

Validate tracking after ledger changes. Preserve input/product identities for
new claims. Archive useful closed evidence and verify member size, SHA and mode
before retiring duplicate probes; retain current products and incremental caches.

Commit and push the verified checkpoint to `origin/main` with an English subject
beginning `gpt-6.1-sol: `. Keep originals, toolchains and raw evidence private.
