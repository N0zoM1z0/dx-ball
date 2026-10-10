# Reconstruction handoff

Continue toward nearly complete original DX-Ball v1.07 source that rebuilds and
plays. Prioritize whole game flows and exact recovery. Use only the minimum
useful existing replay/Oracle; do not expand the historical test queue.

## Local state

- Source checkpoint: `522fc28`, following published `5f17d1a`.
- Pushes are deferred at the user's request. The source checkpoint is local;
  its exact-head CI has not run. Commit subsequent work locally too.
- 283 source-present functions; 147 exact functions / 23,490 code bytes and
  136 metadata bytes; 247 scoped semantic acceptances.
- README explains the REA workflow and retains the centered 900px title PNG
  and progress SVG. Agent instructions belong here and in `AGENTS.md`.
- No score-initialization edits or compilation have started. Its proposal is
  saved for the next batch. No compiler or REA provider is left running.

## Latest source recovery

Surface fill at `0x409F10` is exact across all 89 bytes on its first stable
compile. Sprite-bank recovery at `0x403D30` now reads live owners and calls
`load_sprite_bank` directly. Its complete candidate is 279/282 bytes with
80 unmasked differences; original unused HRESULT storage remains unresolved.

One device recipe compiled once. All three affected prior exact units retained
identical code and relocations: palette (206 bytes), synchronization (134),
recovery (97). Five whole comparisons account for 35 relocations. Only 145 existing direct
cases and eight connected lost-surface checks ran, once. Native, VC4 and MinGW
builds passed; VC4 reused all 35 objects. Snapshot 495 was reused with no query.
See [device dependencies](../research/exact/DEVICE_DEPENDENCIES.md).

Private receipts: `.analysis/exact-device-dependencies/`.
Sealed checkpoint: `.analysis/checkpoints/exact-device-dependencies-283-147/`.
The local-commit receipt and full supplemental journals record failed publication
attempts. Do not restart those attempts while pushes remain deferred.

## Next batch: complete score initialization

Recover `dxball_initialize_scores` at `0x406EE0`, 723 bytes, in `src/startup.c`.
Current source factors the names through a `strcpy` loop and file callbacks.
The original performs 15 explicit name-clear / `strcat` / score-store phases,
then calls CRT file APIs directly. Preserve the 44-byte records, untouched name
tails, scores 150..10, the access==-1 gate, NULL-open return, ignored write/close
results, and the shared closed `FILE *` slot.

Start with `.analysis/remaining-game-source-next-review/`:

- `initialize-scores-proposal.c.txt`: complete source proposal, SHA256
  `5d1bc731f404d28a35bd6c0d3b30c44cb25dd0e94c0b7b5f88efe9376e927154`.
- `findings.json`: whole-flow coverage and remaining-source inventory.
- `stdio-transport-review.json`: corrected dependency review with 22 retained
  input hashes. The initial review is kept separately as historical evidence.

Accepted board-bank callers already establish `fopen`→`0x417C20`,
`fwrite`→`0x417E70`, and `fclose`→`0x417A30`. Their unknown runtime-origin rows
are a separate question. Resolve three concrete gaps before compiling:

1. Attest the `access` binding at `0x417FF0`; the caller establishes its cdecl
   two-argument contract and -1 result gate.
2. Verify the complete consumed literal bytes, including NULs, `wb`, and the
   three distinct original addresses holding the separator text.
3. Establish image-local native stdio transport for the existing startup
   fixture. Its shim uses `RTLD_GLOBAL`; avoid process-wide libc interposition.

Saved complete dossier:
`.analysis/rea/runs/2026-10-07T11-58-17.972Z-interactive-3053414/08-analyze_function.json`,
Evidence ID `ev_8dac6e01bb85d2646a688aaa07a710a92aa40634ba392304d3263f05ee92cbd6`.
The 723-byte instruction flow is contiguous. Reuse it; query only missing data
or a specific unresolved target. Compile once when the shared source and real
API boundaries are stable, then compare all accepted units affected by those
inputs and run the affected existing check.

## Limits and working environment

The origin inventory identifies 270 authored entries, all source-present, plus
runtime/compiler-generated and unknown entries. Presence is not a measure of
original source fidelity; >=95% complete restoration remains unproven.
Keep unresolved origins unknown rather than assigning them to CRT by location.

Read `AGENTS.md`, [workflow](WORKFLOW.md), and the relevant owner note.
REA checkout: `/home/pentester/Project/rea/`. New binary questions use
`scripts/rea`, pinned to REA 4.1.0/Ghidra 12.1.4, with full responses/Evidence IDs
and snapshots retained under `.analysis/rea/`. Close the provider afterwards.
Use `scripts/repo-python`, CPU 0, one writable compiler/provider session, the
512 MiB Ghidra heap, and CMake `--parallel 1`. Compilers use
`legacy_toolchain.session_lock()`. Automated audio uses
`PULSE_SINK=dxball_reconstruction_silent`.

Keep current builds, original assets, toolchains and unique evidence. Clean
superseded products and hash-verified duplicates. Commit subjects begin
`gpt-6.1-sol: `; keep commits local until the user resumes publishing.

## Handoff cleanup

Windows diagnostic tools are explicit CMake targets, excluded from the default
MinGW build. Configuration and the build graph were checked; no compilation
or Oracle rerun was needed. Only five historical semantic rows needed their
CMake input identity refreshed; their cases and scope remain historical.

The cleanup shared 23,579 byte-identical archived files through hardlinks.
`.analysis` fell from about 3.5 GiB to 2.1 GiB. Thirteen duplicate publication
inputs/drivers were removed after verifying their full checkpoint copies,
freeing another 6,463,488 allocated bytes. Current builds and unique evidence
remain. Receipts: `.analysis/handoff-2026-10-10/` and
`.analysis/cleanup/20261010T135954340137Z.json`.
