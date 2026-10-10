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

- 283 source-present entries; 167 exact functions / 29,764 full-span bytes and
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
`.analysis/exact-gameover-lifecycle/`, `.analysis/exact-gameover-keys/`, and
`.analysis/exact-editor-lifecycle/` and `.analysis/exact-editor-commands/` and `.analysis/exact-board-rendering/` and `.analysis/exact-intro-key-points/`.
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
snapshot contains seven cumulative new records, including the reading/insertion literals. New analysis responses expose
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

Editor initialization (`0x40C1A0`, 263 bytes / 28 relocations), redraw
(`0x40C2B0`, 252 / 20) and cleanup (`0x40CF20`, 78 / 6) are now exact on one
stable compilation, using their retained 14-34 dossiers. All nine editor units,
including the existing 908-byte frame, match together. The complete 21-file
project input closure is included in the retained 34-file recipe. Native and
MinGW builds and the 35-object VC4 relink pass.

Final editor checks select 54 existing lifecycle/redraw cases, all 32 connected
checks and fifteen existing file-outcome cases. One existing score-insertion
case checks the default score import transport. The inherited game-over stdio
binding initially intercepted editor board saves; `EditorNative` now explicitly
skips score bindings, preserving its independent actual-host stdio behavior.
Default game-over binding and assertions remain intact. The failed probe and
passing current-library reports are retained; no full owner suite was rerun.

Editor choices (`0x40C9C0`, 163 bytes / five relocations), region initialization
(`0x401E10`, 147 / seven) and lookup (`0x401F90`, 173 / six) are now exact.
Choices retain tile initialization before surface selection and the original
loop/wrap order. Region initialization restores five independent field stores;
lookup restores the global-count-first comparison and last-hit precedence.
All twelve accepted editor units match together after two family compilations.
The 35-file recipe contains the complete 22-file project header/source closure.

Status (`0x40CA70`) restores genuine CRT `_itoa(..., 10)`, the eight-byte number
buffer, two meaningful rectangles, coordinate state and direct typed COM calls.
The original frame is 52 bytes. It remains a complete 431-byte candidate with
25 relocations and 28 differing local-storage operands. No declaration/name/
layout trials were used. The Linux-only decimal service is a host bridge, not
recovered vendor runtime source; Windows uses its actual CRT implementation.

Key dispatch restores signed-char switch input, all twelve original empty cases,
actual board-index reloads and complete table bindings. The original 632-byte
span contains 367 instruction bytes (362 owned plus an excluded five-byte JMP
at `0x40C87D`) and 265 inline table bytes. It remains a 638/632-byte candidate:
VC4 emits MOV-base/ADD-field/PUSH for the genuine structured board tile address,
where the original uses an immediate address. This six-byte difference shifts
later code/tables and produces 260 full-span differences. An explicit first-byte
address emits the same code. Keep the natural shared storage owner; do not add
alias/padding/layout trials merely to force this match.

The intermediate library passed all 2,921 existing editor cases and 32 connected
checks. After the final expression recovery, the final library passes 1,439
existing lookup/key/file-outcome cases, the same 32 connected checks and six
signed decimal bridge boundary values. The private selection wrapper initially
compared its counters to a dictionary without the owner's zero-valued entries;
its count assertion was corrected and the selection rerun. Maintained oracle
cases/assertions are unchanged. Reports retain distinct library hashes; other
owner scopes stay historical. Native/MinGW builds and the 35-object VC4 relink
pass. No full historical queue was replayed.

Board traversal (`0x411970`, 113 bytes / three relocations) and cell drawing
(`0x4119F0`, 1,349 / 55) are now exact. The source restores each original signed
switch case, the actual promoted DWORD tile local, independent rectangle field
calculations and genuine sprite/COM/invalidation calls. Two family compilations
were used; all six accepted board units stay exact together. The 27-file recipe
contains the complete eleven-file consumed project closure. The 1,349-byte
span includes the excluded five-byte JMP at `0x411E94` and 92 table bytes.

The new REA session is closed and saved with seven cumulative Evidence records.
Dossier IDs and exact scope are in [board evidence](../research/KNOWLEDGE_BASE.md).
The mapper (`0x40CCF0`, 426 bytes) confirms the original uninitialized-local
return outside 0..22. Preserve the host abort policy and bounded acceptance;
it is deliberately not promoted. Editor board-copy candidates stay 52-byte
full-span comparisons with their existing structured-storage emission gap.

Final drawing validation: 9,319 selected existing rendering/traversal cases and
32 existing connected editor checks; the intermediate library passed all 9,502
board-owner cases and the same connected checks. Reports retain distinct hashes.
The fixture now binds actual sprite/invalidation API slots in a copied ELF image
and supplies a typed COM destination while preserving handle identities and
all maintained assertions. Core fixtures keep their established transport.
Native/MinGW builds and the 35-object VC4 relink pass. Historical semantic rows
keep their old scopes after identity refresh; no historical queue was replayed.

Menu key dispatch (`0x40E430`) now matches its complete 305-byte span on one
compilation, with eighteen relocations. The original signed-char switch,
eleven empty cases and Control-F1 stores are retained. Its full span contains
161 instruction bytes (156 owned plus a five-byte JMP at `0x40E4A2`) and 144
embedded table bytes. All thirteen accepted intro units match together; the
22-file recipe includes the complete consumed project closure.

The point updater (`0x40ED40`) restores live global surface loads at each COM
call, its actual lock-result loop, indexed point/offset consumers, descriptor
size/flags and original rectangle-store order. It removes auxiliary pointer/
offset copies and the unobserved whole-descriptor zeroing. The original still
has two writes into an unpassed 100-byte request-shaped area; their source
origin is unexplained. No unused local is added to mimic it. Its complete
666/711-byte comparison has forty relocations and 637 unaligned differences;
it remains a candidate, with no full-original storage claim.

The final library passes 1,060 selected existing key/point cases and all 58
connected splash/menu/editor-request scenarios. Native/MinGW builds and the
35-object VC4 relink pass. No fixture or maintained cases/assertions changed;
other intro loops remain historical. All six prior candidates were compared
alongside the new candidate. The prior pulse manifest had an outdated relocation
offset; bindings now reflect the actual current object, whose existing 368/370
and 127-difference result is preserved. All candidate differences remain explicit.
No full owner suite or historical queue was replayed.

The subsequent unchanged real-Wine VC4 play selection passes with 77 read-only
state observations: ball motion, pause/resume, editor painting/save/reload,
the expected complete bank hash and exit code zero. All 49 originals remain
unchanged. Receipts and the retained pre-observation stale-map failure are in
`.analysis/windows-play-menu-732731b/`. The state reader supports verified
focused link receipts, checking EXE/map, all objects/inputs and resource inputs;
five simulated stale identities are rejected. Existing runtime inputs and
assertions are unchanged. Original/MinGW controls remain historical, with no
synchronized frame, audio/MIDI or complete-game fidelity claim.

Round transitions now match together: level advance (`0x415B30`, 123 bytes /
eleven relocations) and life loss (`0x415BB0`, 81 / seven). Direct board/count
and sound calls, live pan input and the signed zero-count branch follow the
original. Two round compilations were used; all sixteen consumed project inputs
are covered by the existing 27-file recipe. The old 07-26 dossiers were reused.
The final library passes 80 existing round cases, all 912 existing bonus cases
and one trig setup. Sixteen connected bonus frames are included. Another 420
core-frame cases include 200 connected frames. No cases/assertions changed.
The fixture keeps the inherited verified gameplay/core image and binds only
its actual board API slots to the existing live round table. Uncontrolled calls
enter the genuine initializer/counter; sound uses its established transport.
Native/MinGW builds and the 35-object VC4 relink pass. Receipts and failed private
attempts are in `.analysis/exact-round-transitions/`. Terminal board initialization
remains controlled; other owner cases stay historical after identity refresh.
No full owner suite or historical queue was replayed.

The current `9ec72c3` VC4 EXE then passes the unchanged real-Wine round flow:
editor-created single brick, natural clear, ten points, original board1 loaded
with all 400 matching bytes / 222 destructible bricks, three lives, attached
ball and zero-code exit. It records 71 read-only states and preserves all 49
original assets. Bank/board bytes, captures and receipts are in
`.analysis/windows-round-9ec72c3/`. Prior original/MinGW controls were not rerun;
focus recovery, physical audio/MIDI, terminal board50 and full-game fidelity
remain outside this selection.

Continue source restoration in another connected game phase. Preserve the
original/asset identities and disposable probe working copies. Existing
intro/splash candidate gaps are documented in
the owner notes; do not perform declaration/name/layout/padding permutations
or add unconsumed request storage simply to force exactness.

The subsequent paddle batch restores original direct calls, independent x87
margin branches, fresh surface/sprite reads and the pre-COM dirty rectangle.
Six private original/native COM-mutation cases accept the final library and
reject the preceding sealed library. The complete 679/677-byte paddle candidate
has 52 bindings /496 unaligned differences and both verified eight-byte literals.
Do not use local/operand-layout permutations to force a match.

Elapsed (`0x4034F0`) now has a complete 81-byte exact claim with one relocation,
including its internal five-byte jump. Its current body is unchanged: the
pre-batch object is identical and also matches, superseding the stale historical
three-difference description after `8bf2931`. All ten accepted runtime bodies
match together. One stable runtime compile follows an API-type diagnostic;
all 25 project inputs are declared. The final library passes 837 selected
existing clock/elapsed/paddle and initializer/death/reset/dispatch calls, including
36 connected frames. The fixture keeps complete COM events on both sides;
maintained cases/assertions are unchanged. Native/MinGW builds and 35-object
VC4 relink pass. Private evidence is in `.analysis/exact-paddle-rendering/`.
Other owner scopes remain historical; no full owner or historical replay was run.

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
Entry 12 records bounded editor facet sizes and confirms the span gap in a second
controller, with a proposed evidence-linked native reconstruction view.
Measurements and suggestions are
separate; exact model-token counts and snapshot failure root cause are unknown.
Entry 13 adds current cold/warm function latency and response-size measurements.
Entry 14 records bounded key/point archive views and the unresolved storage
consumer boundary. Entry 15 records inferred call prototypes hiding actual
arguments. Entry 16 records pre-COM rectangle consumers and x87 precision/literal
context. Nothing has been sent externally.

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
