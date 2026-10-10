# Reconstruction handoff

Continue toward nearly complete original English DX-Ball v1.07 source that
rebuilds and plays. Prioritize complete game flows and exact recovery. Commit
locally with `gpt-6.1-sol: ` subjects; pushes remain deferred. Use targeted
comparisons and existing affected checks, without expanding the historical queue.

## Current source recovery

Score initialization at `0x406EE0` is exact across its complete 723 bytes on
its first stable VC4 compilation. `src/startup.c` restores fifteen explicit
name-clear / `strcat` / score-store phases, then genuine direct `access`,
`fopen`, `fwrite` and `fclose` calls. Preserve the 44-byte records, untouched
name tails, scores 150..10, access==-1 gate, NULL-open return, ignored results,
and shared closed `FILE *` slot. All 87 relocations and eighteen consumed
literal storage operands, including NULs and independent repeated literals,
are declared in `config/match-units.toml`.

- 283 source-present entries; 149 exact functions / 24,307 code bytes and
  136 metadata bytes; 247 scoped semantic acceptances.
- Score reading at `0x406CC0` is also exact across its complete 94 bytes after
  ten explicit relocations. The 723-byte initializer and 125-byte bank release
  stay exact. Device initialization
  stays a complete 359-byte candidate with ten differing bytes.
- Initialization used one startup recipe compilation. The following persistence
  batch used one startup compilation and four game-over compilations to recover
  loop structure and bound the remaining comparison-emission difference.
- Final current-library checks: 158 existing startup cases + one connected
  dispatch check; 6,531 game-over cases +76 connected checks. No cases were added.
  Intermediate-source checks are retained separately, not counted as new cases.
- The native fixture binds only copied-image ELF import slots to the existing
  typed stdio callbacks. No process-wide libc symbols are interposed.
- Actual canonical libc creation, existing-file gating, accepted/rejected
  insertion, persisted bytes and partial reads passed independently.
- Native and MinGW builds passed. VC4 relinked using all 35 verified objects;
  there was no further legacy source compilation.
- Other semantic rows retain their historical cases and scope after input
  identity refresh; these are not newly rerun suites.

Private receipts: `.analysis/exact-score-initialization/` and
`.analysis/exact-score-reading/`. The first batch is committed as `177de9d`;
the following local checkpoint contains score reading and insertion recovery.
See [startup evidence](../research/STARTUP_UI_OWNER.md).

## REA upgrade

The user's requested local upgrade is installed and pinned to REA 6.3.0,
verified against the official npm registry. Ghidra remains 12.1.4. The scoped
Ghidra and Codex registration doctor checks pass. The upgraded project wrapper
successfully queried two missing boundaries and closed its provider.

New access dossier:
`.analysis/rea/runs/2026-10-10T14-29-24.089Z-score-boundaries-590652/00-analyze_function.json`,
Evidence `ev_3c45a24fc90e2bb90489bc9c3533d438174388a59cbd469eb9c5b5f992897241`.
The full 77-byte body matches the pinned CRT `access.obj` member after five
explicit relocation bindings. This corroborates the direct API; it does not
promote the origin ledger or prove unique original alias spelling.
The adjacent `01-read_bytes.json` attests all 592 literal bytes with Evidence
`ev_8e62c86b8565325f7f6450aed6e6a8b3c37df251bb87cee577dfaf1a8d0776cb`.

REA 6.3 rejects the old snapshot during integrity validation; the exact cause
is unisolated. The old snapshot is
retained at `.analysis/rea-upgrade-6.3.0/snapshot-4.1.0.json`; historical runs,
Evidence IDs and dossiers remain available for direct reuse. The current
snapshot contains four new records, including the reading/insertion literals. New analysis responses expose
`raw_result` and `normalized_result`, while older responses use `result`.
See [REA commands](REA.md). No registration rewrite or provider installation
was necessary; the configured MCP path now points at the upgraded package.

## Next batch

The complete score initialization/read/insertion flow now uses genuine direct
CRT file APIs. `read_scores` has no local storage and preserves the NULL-open
return, ignored read/close results and closed shared pointer. Its complete
94-byte dossier was reused, without another function query.

Insertion at `0x406D20` restores the distinct last-rank branch and backwards
scan/shift loops. It is a complete 446-byte candidate with 26 explicit
relocations and three differences at offsets 172, 175 and 177: the shift-loop
comparison loads the opposite local first and uses the equivalent signed exit
condition. Equivalent relational spellings produced identical code; the source
keeps `while (i >= rank)`. Do not perform declaration/name/layout or padding
trials to force this comparison. Candidate receipts retain the actual objects,
inputs, full differences and intermediate checks.

Follow the score lifetime into name editing (`0x4071C0`, 421 bytes) and ranking
drawing (`0x406B20`, 404 bytes), reusing their complete 2026-10-07 13-44 dossiers.
Inspect actual control flow, state writes and real shared API boundaries before
compiling a coherent family. The current `gameover` recipe and typed image-local
stdio fixture are available. Keep the three-byte insertion gap explicit until
independent evidence resolves its original compiler expression.

Earlier unresolved candidates remain: device initialization (359 bytes / ten
differences), and live sprite-bank recovery at `0x403D30` (279/282 bytes / 80
differences). The latter's original unused HRESULT storage is unresolved.
Do not add fake locals or profile-specific bodies.

## Ongoing REA feedback

Append performance, response-size, context and usability findings to the single
English document `/tmp/dxball_rea_feedback_20261010.md`. Do not create another
feedback document. Current observations include approximately 54-55 second
cold byte reads, a 150,222-byte MCP response for a 77-byte function, a
4,795,431-byte catalog for 139 tools, generic legacy-snapshot rejection, and
response-field/lifecycle migration issues. Measurements and suggestions are
separate; exact model-token counts and snapshot failure root cause are unknown.
Nothing has been sent externally.

## Working limits and completeness

Read `AGENTS.md`, [workflow](WORKFLOW.md), and the relevant owner note.
Use `scripts/repo-python`, `scripts/rea`, CPU 0, one writable compiler/provider
session, the 512 MiB Ghidra heap, and CMake `--parallel 1`. Compiler/provider
work uses `legacy_toolchain.session_lock()`. Automated audio uses
`PULSE_SINK=dxball_reconstruction_silent`.

The inventory identifies 270 authored entries, all source-present, plus runtime,
compiler-generated and unknown entries. Source presence does not establish
original fidelity; >=95% complete restoration remains unproven.
Keep current builds, originals, toolchains and unique evidence. Clean superseded
products and verified duplicates. README retains its 900px PNG and progress SVG.
