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

- 283 source-present entries; 155 exact functions / 26,636 full-span bytes and
  136 metadata bytes; 247 scoped semantic acceptances.
- Score reading at `0x406CC0` is also exact across its complete 94 bytes after
  ten explicit relocations. The 723-byte initializer and 125-byte bank release
  stay exact. Device initialization
  stays a complete 359-byte candidate with ten differing bytes.
- Initialization used one startup recipe compilation. The following persistence
  batch used one startup compilation and four game-over compilations to recover
  loop structure and bound the remaining comparison-emission difference.
- Persistence-batch checks: 158 existing startup cases + one connected
  dispatch check; 6,531 game-over cases +76 connected checks. The subsequent
  interface batch checks the affected game-over owner against its library. The
  final lifecycle/drawing batch selects 285 existing cases and 76 connected
  checks. No cases were added; earlier checks retain their own product hashes.
- The native fixture binds only copied-image ELF import slots to the existing
  typed stdio callbacks. No process-wide libc symbols are interposed.
- Actual canonical libc creation, existing-file gating, accepted/rejected
  insertion, persisted bytes and partial reads passed independently.
- Native and MinGW builds passed. VC4 relinked using all 35 verified objects;
  there was no further legacy source compilation.
- Other semantic rows retain their historical cases and scope after input
  identity refresh; these are not newly rerun suites.

Private receipts: `.analysis/exact-score-initialization/` and
`.analysis/exact-score-reading/`, `.analysis/exact-ranking-interface/`, and
`.analysis/exact-gameover-lifecycle/` and `.analysis/exact-gameover-keys/`.
Initialization is committed as `177de9d`; persistence as `5d3db52`. The current
interface checkpoint is `4499a3d`. The current lifecycle checkpoint restores
initialization, redraw, frame and cleanup exactly; no push was made.
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

Name editing at `0x4071C0` is now exact across 421 bytes and 33 relocations,
using its original independent character branches and genuine shared palette/PCX
calls. Two game-over compilations were used for this interface batch; the second
adds the standard MinGW `_ultoa` declaration and the observed equality operand
order. No additional REA query was needed.

Ranking drawing at `0x406B20` restores `_ultoa`, stored lengths, meaningful X
coordinate and row updates, but remains a 403/404-byte candidate. Different
local storage and a one-byte-shorter comparison produce 335 differences in the
unaligned full-span comparison. No declaration/layout/name/padding trials were
used. Do not describe this as exact or tune those layouts to force a match.

Initialization (`0x406440`, 321 bytes / 34 relocations), redraw (`0x406590`,
414 / 32), frame (`0x406730`, 696 / 62) and cleanup (`0x407370`, 175 / 12)
are now exact. Their complete old dossiers and referenced strings were reused.
The source restores genuine shared APIs and typed COM blits, original branches,
clock/cursor/dirty-region order and meaningful storage. No new REA call was
needed. This batch used three VC4 compilations, including typed music/sound
header completion; all project header inputs are tracked in a 21-file closure.

The final native library passes 285 selected existing initialization/ranking/
redraw/frame/cleanup cases and all 76 connected mode/name/persistence checks.
The private selector executes unmodified maintained oracle loops. The earlier
40-case lifetime selection and previous 6,531-case full owner check retain their
own intermediate/earlier library hashes. Native and MinGW builds pass; VC4
relinks 35 verified objects without further source compilation. All five
accepted game-over bodies are compared together; both existing candidate gaps
remain explicit. No full historical queue was replayed.

Key dispatch (`0x4069F0`) now matches its full 302-byte span on the first
compile, with seventeen relocations. Twelve original empty cases, switch data
and the missing internal five-byte JMP are retained. There are 158 instruction
bytes and 144 embedded table bytes; the old REA view listed only 153 owned
instruction bytes. The full-span metric includes the switch data as with the
existing Windows key controllers. All six accepted game-over bodies match
together; candidate gaps remain unchanged. The final library passes 1,024
existing key-routing cases and all 76 connected checks; other direct owner
loops remain historical. Native/MinGW builds and the 35-object VC4 relink pass.

Next follow the actual mode-2 editor initialization/redraw/frame/resource
lifetime family using `docs/research/EDITOR_OWNER.md` and its saved dossiers.
Inspect direct call boundaries and complete original branches before compiling
one coherent family. Do not perform layout/name/padding trials on the insertion
or ranking-drawing gaps.

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
response-field/lifecycle migration issues. Entry 8 records how projecting old
function dossiers to pseudocode/assembly avoided new provider calls and reduced
the required view from 0.6/0.98 MB to approximately 5/4.6 KB. Entry 9 records
how normalized pseudocode hides original eligibility branches relevant to exact
source restoration. Entry 10 records installed-skill drift and existing bounded
view capabilities: the installed skill now matches the 6.3 package at version
34 / 139 tools. Backups and hashes are private in the upgrade receipts. Entry
11 records the excluded native key-span instruction and a proposed coverage map.
Measurements and suggestions are
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
