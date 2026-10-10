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

- 283 source-present entries; 148 exact functions / 24,213 code bytes and
  136 metadata bytes; 247 scoped semantic acceptances.
- The affected 125-byte bank-release unit stays exact. Device initialization
  stays a complete 359-byte candidate with ten differing bytes.
- One stable startup recipe compilation, three complete comparisons, and
  the 158 existing startup cases plus one connected dispatch check, once.
- The native fixture binds only copied-image ELF import slots to the existing
  typed stdio callbacks. No process-wide libc symbols are interposed.
- Actual canonical libc creation and existing-file gating passed independently.
- Native and MinGW builds passed. VC4 relinked using all 35 verified objects;
  there was no further legacy source compilation.
- Other semantic rows retain their historical cases and scope after input
  identity refresh; these are not newly rerun suites.

Private receipts: `.analysis/exact-score-initialization/`.
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

REA 6.3 rejects the old snapshot's integrity format. The old snapshot is
retained at `.analysis/rea-upgrade-6.3.0/snapshot-4.1.0.json`; historical runs,
Evidence IDs and dossiers remain available for direct reuse. The current
snapshot contains the two new records. New analysis responses expose
`raw_result` and `normalized_result`, while older responses use `result`.
See [REA commands](REA.md). No registration rewrite or provider installation
was necessary; the configured MCP path now points at the upgraded package.

## Next batch

Continue the score persistence flow with `dxball_read_scores` at `0x406CC0`,
94 bytes, in `src/startup.c`. It still uses the startup file callback table.
Reuse its complete saved dossier in the closed 2026-10-07 11-58 REA archive,
Evidence `ev_60906ff615d2fceb6d7e4cb83c367f0f2612498b4c30cf1d1b20cd4d1c80f2ea`.
Recover actual direct file calls and original local storage from instructions;
do not insert an inert local to force a match. The new fixture transport can
bind the real `fread` import using its existing typed read callback.

Then inspect score submission at `0x406D20` through its complete 446-byte flow.
The now-established access/stdio boundaries can be reused. Keep unknown origins
unknown and prefer recovery that closes the complete score lifetime.

Earlier unresolved candidates remain: device initialization (359 bytes / ten
differences), and live sprite-bank recovery at `0x403D30` (279/282 bytes / 80
differences). The latter's original unused HRESULT storage is unresolved.
Do not add fake locals or profile-specific bodies.

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
