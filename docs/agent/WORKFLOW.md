# Contributor reconstruction workflow

Aim for nearly complete original game source that rebuilds and plays. Choose
work that closes a game flow: initialization, a frame phase, drawing, input,
audio, or resource lifetime. Small exact helpers are useful dependencies, but
an exact-function count is not the project's completion measure.

## Establish the next question

Read [`AGENTS.md`](../../AGENTS.md), the current handoff, and the relevant owner
notes. Inspect the worktree and consult `config/functions.csv`; imported
function boundaries are provisional. Reuse the existing REA dossier before
opening another analysis session. Record what behavior is missing and which
caller, callee or data owner will answer it.

Use repository Python and the pinned REA wrapper. When beginning binary or
compiler work, verify the inputs relevant to that work:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-toolchain.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

[`REA commands`](REA.md) shows the pinned 4.1 CLI and session protocol. New binary
queries use its Ghidra provider. Ask focused questions about complete control
flow, actual call targets, argument widths and data consumers. Retain full
responses, Evidence IDs and limitations in `.analysis/rea/`, then close/save
the session. Query a missing byte range or unresolved callee only when the
saved evidence leaves that concrete gap.

## Recover one coherent source family

Reconcile each entry through its exits, branches, switch data and any unowned
bytes inside the enclosing span. Read the original instructions alongside
pseudocode. Establish structures from both their producers and consumers;
check the ABI against the actual callers and callees.

Write natural typed C in the existing owner. Portable and legacy builds share
one implementation. Preserve meaningful state writes, resource ownership,
integer widths and call order. Keep unknown source spelling or backend behavior
in the notes. Do not introduce fake locals, padding, copied code bytes or
profile-specific bodies to force compiler agreement.

For a direct call, use the genuine shared API. If an existing native fixture
needs isolation, adapt only its actual typed boundary and current callback
table. Keep real defaults and standalone loading intact. A callback fixture
checks effects at that boundary; it does not recover a missing driver.

Ask an independent reviewer a bounded question when useful: does this struct
layout follow the consumers, does the whole body match the dossier, or does
the fixture preserve the real ABI? Resolve the answer before broadening work.

## Build and check the affected behavior

Once the family is stable, compile the affected maintained target. Use the
build instructions in [`BUILD.md`](../BUILD.md); CMake builds run with
`--parallel 1`. Prefer a small startup/play check or one affected existing
Oracle when it resolves a concrete issue. Tests are optional evidence. Do not
default to the complete owner suite or historical validation batches, and do
not repeat successful checks with identical inputs. Redundant tests can be
removed after retaining useful evidence and checking their remaining users.

For a new exact claim, add the whole unit to `config/match-units.toml` with
complete compiler inputs, flags, extent and explicit relocation bindings.
Include every recursively consumed project header. Retain the previous object
and report before a shared-source compile overwrites them. Replay the affected
accepted units together, including units whose literals or metadata may move.
For example, both append bodies share the core recipe:

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit append-projectile --unit append-fire-effect \
  --report build/reports/projectile-appends.json
```

Extend that selection to the other accepted units affected by the change.
Apply every actual COFF relocation and compare the complete span, full literal
contents and declared metadata against the verified target. Zero differences
can establish exactness; partial similarity remains a candidate. A source
restoration can still be valuable when compiler storage choices differ.

Use one writable compiler/provider session at a time. Existing project entry
points constrain CPU and provider heap use. Keep audio probes on the silent
capture sink described in the owner notes.

## Leave the next contributor a clear result

Update the owner note with the recovered behavior, evidence links, useful
validation and remaining gap. Update only the ledgers whose claims changed:
`implemented.csv` for source, `semantic-acceptance.csv` for scoped behavior,
and `matches.csv` for configured exact units. Check tracking and refresh
progress when those ledgers change. Preserve input and product identities
needed to reproduce a new acceptance claim.

Commit a stable, readable checkpoint with the required English subject prefix
`gpt-6.1-sol: `. Explain the REA findings, source change and actual checks in
the commit body. Keep originals, assets, toolchains and raw analysis private.
Clean disposable probes after unique evidence and accepted products are
retained; `scripts/repo-python scripts/clean-local.py` previews cleanup.
