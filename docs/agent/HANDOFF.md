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

- 283 source-present entries; 185 exact functions / 32,688 full-span bytes and
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
snapshot contains twenty cumulative records, including the reading/insertion
literals, three sprite-lifetime dossiers, six font facets, three PCX facets and
the complete rectangle-span read. Its latest close reports seven
primitive entries and no workflow entries. New analysis responses expose
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

The current `a53c18a` VC4 product then passes the unchanged real-Wine
ball/pause/editor/exit flow with 83 read-only observations, the established
complete saved-bank hash and all 49 original identities unchanged. Receipts
are in `.analysis/windows-play-paddle-a53c18a/`. Original/MinGW prior controls
were not rerun; synchronized pixels, audio/MIDI and complete-game fidelity
remain outside this selection.

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
context. Entry 17 records an excluded unreachable clock-divisor store and its
relocation, with a proposed classified enclosing-span view. Nothing has been
sent externally.

Entry 18 adds measured sprite-lifetime cold/warm provider latency, the 3.38 MB
warm loader response and bounded descriptor/stride consumer suggestions.
Entry 19 records the useful existing native info/pseudocode/assembly interfaces:
six font responses total 61,666 bytes; later facets take 23–45 ms, but the
first info query still takes about 62 seconds. It documents the drawing span
gap, remaining cold-start visibility and compact discovery suggestions.
Entry 20 records three PCX facets totaling 75,138 serialized MCP bytes,
a 58.7-second cold info query and 136/32 ms warm pseudo/assembly calls.
It describes header/descriptor producer-consumer views and the original
duplicated literal/run paths, redundant checks and unconsumed row updates.
Entry 21 reuses text/line dossiers without a provider call: 443,325/821,198-byte
archives project to 5,019/8,996 bytes including procedure/pseudo/assembly. It
documents local search versus a helper call and descriptor/operand views.

## Clock boundary checkpoint before sprite recovery

The complete current-time controller at `0x403450` matches all 148 bytes with
nine relocations. Three independent typed SDK clock slots replace the
contiguous callback-table assumption; host defaults still forward live native
callbacks. Frequency BOOL storage and the retained unreachable divisor-zero
store follow the complete original instructions. Both previously excluded
intervals are covered. REA Evidence was reused without a new provider call.

One runtime compile verifies its 26-file consumed closure and all affected
units. Nine previous runtime exacts stay exact. The unchanged elapsed body
now has three compare-operand differences and is explicitly a candidate;
retain its earlier exact object and do not force declaration/name/layout
changes. Paddle is now 678/677 bytes with 494 unaligned differences and 52
bindings; its meaningful rectangles and floating literal consumers remain.
That checkpoint retained 167 exact functions, 29,831 bytes plus 136 metadata.

Native/MinGW builds and a VC4 relink pass: three affected source objects
compiled, 32 independently verified objects reused. The unchanged 837 selected
existing checks pass, including 36 connected frames. The new VC4 product
passes real ball/pause/editor/exit with 81 read-only states, the expected saved
bank, exit zero and all 49 original assets unchanged. Receipts are in
`.analysis/exact-clock-api/` and `.analysis/windows-play-clock-api/`.
No full owner replay or prior mutation/original/MinGW play controls were rerun;
complete-game, synchronized rendering and physical audio/MIDI stay unproven.

Continue with remaining genuine storage/call gaps in the controllers; use
retained Evidence and complete comparisons. Do not revisit
elapsed by trying variable/declaration permutations. REA feedback still uses
only `/tmp/dxball_rea_feedback_20261010.md`; append to that existing document.

## Current sprite-lifetime checkpoint

Capture and SBK loading now follow the original live bank/record reads and
actual allocator entry. SBK uploads retain GetSurfaceDesc's pitch before Lock
and the consumed destination pixel pointer. The release controller matches its
complete 262 bytes with fifteen relocations; all ten previous resource exacts
remain exact. Capture/load remain 876/852 and 1,655/1,475-byte candidates with
803 and 1,577 unaligned differences. Correct 140/180-byte frames do not prove
local-home or address-scheduling exactness; avoid declaration/layout trials.

The resources matching recipe now declares exactly its eight recursively
consumed project files, narrowed from 29 after one /ML compile. Production
keeps the established /MT recipe; an initial attempt to link the /ML matching
object was rejected for mixed CRT startup definitions. One /MT resource-source
compile and 34 verified object reuses produce the current game. Current totals
are 168 exact functions, 30,093 full-span bytes and 136 metadata bytes.

Native/MinGW builds pass. All 31 unchanged selected release/capture/SBK cases
pass, including the seven original streams. Six separate original/native COM
mutation probes pass and the preceding sealed library fails all six. The new
VC4 real ball/pause/editor/exit flow passes with 83 read-only states, five
captures, expected saved-bank hash, zero exit and all 49 originals unchanged.
Other suites and original/MinGW prior play controls remain historical after
input-identity refresh. Full-game/image/physical audio fidelity stays unproven.

Private receipts: `.analysis/exact-sprite-lifetime/` and
`.analysis/windows-play-sprite-lifetime/`. Three new contiguous REA dossiers
are retained in closed run `2026-10-10T17-22-54.305Z-requests-825249`.
REA performance/usability feedback remains only in
`/tmp/dxball_rea_feedback_20261010.md`, now eighteen numbered entries.
Continue with unresolved rendering/font/resource storage and real call shapes,
using these closed records. Do not repeat the full historical validation queue.

## Current font checkpoint and recipe correction

Glyph lookup at `0x404E40` matches all 145 bytes /six relocations after restoring
the original count-first short-circuit loop. Glyph drawing retains the found
branch fallthrough and separate missing-glyph return, but is a complete
332/328-byte candidate /258 unaligned differences /seventeen bindings. The
observed twenty-byte frame agrees; bank-address scheduling remains unresolved.
The omitted five-byte JMP at `0x404E27` is independently decoded and included.
Do not force source-layout or naming trials to resolve the remaining gap.

The previous comparison helper incorrectly appended release/capture/load under
the runtime recipe despite comparing the resources object. The manifest and
release match row now record resources ownership and its actual eight-file
closure. Archived wrong receipts remain intact; tracking rejects that old
manifest and checks both exact and candidate source owners. All twelve resource
exacts and four candidates compare together. Current totals: 169 exact functions,
30,238 complete code bytes and 136 metadata bytes; no prior exact was lost.

Native/MinGW builds pass. The final native library passes the unchanged 1,537
font calls: all byte codes across three supplied fonts and empty-bank lookup.
One matching `/ML` compile and one established `/MT` production compile were
used; 34 verified game objects were reused. Real VC4 ball/pause/editor/save/
reload/exit passes with 78 read-only states, five captures, expected saved bank,
zero exit and all 49 originals unchanged. Other owner scopes and prior controls
remain historical; no full owner or historical validation queue was replayed.
Receipts: `.analysis/exact-font-rendering/` and
`.analysis/windows-play-font-rendering/`. Six new bounded REA facets are retained
in closed run `2026-10-10T17-38-24.772Z-requests-846003`; current snapshot has
sixteen Evidence records /seven primitive entries. Feedback uses only
`/tmp/dxball_rea_feedback_20261010.md`, now nineteen entries.

Continue resolving genuine rendering/resource/call gaps with retained evidence.
Near-complete source fidelity remains unproven; the reconstruction goal is active.

## Current PCX source checkpoint

The decoder restores independent RLE/literal paths, the complete typed 128-byte
header and byte-pointer producer, signed 16-bit maxima, distinct header/run
indices and actual row-counter initialization/increments. The counter has no
later original consumer; it is supported by direct instructions. Both clipping
paths use the consumed pixel pointer. Original redundant byte-range checks,
inclusive limit, zero runs, overshoot and pre-Lock dimensions/pitch remain.
Scoped GCC diagnostic annotations preserve the observed check and counter
without changing the shared executable logic.

The complete original span is contiguous at 862 bytes. Current comparison is
984/862 bytes /869 unaligned differences /eight bindings, with current/original
308/312-byte frames. Local homes, address scheduling and four unexplained frame
bytes remain; do not add storage or perform declaration/name/layout trials to
force agreement. Full `rb` storage, including NUL, is bound to `0x422794`.
All twelve resource exacts and five candidates compare together. Totals remain
169 exact functions /30,238 complete code bytes /136 metadata bytes.

Two matching `/ML` compiles and one established `/MT` production compile were
used; 34 verified game objects were reused. Native/MinGW builds pass. The final
library passes 99 unchanged selected PCX calls across five original images,
all palette modes and existing edge cases. Real VC4 ball/pause/editor/save/
reload/exit passes with 84 read-only states, five captures, expected saved bank,
exit zero and all 49 originals unchanged. Other semantic scopes and prior
controls remain historical after input refresh; no full owner or historical
validation queue was replayed. Source/frame/full-game fidelity stays unproven.

Receipts: `.analysis/exact-pcx-decoding/` and
`.analysis/windows-play-pcx-decoding/`. The closed REA run is
`2026-10-10T17-54-16.976Z-requests-866362`; current snapshot contains nineteen
Evidence records and seven primitive entries. Feedback still uses only
`/tmp/dxball_rea_feedback_20261010.md`, now twenty numbered entries.
Continue restoring genuine rendering/resource/call gaps from retained evidence.

## Current UI text/line checkpoint

Measurement at `0x404FD0` restores the original local glyph-search loop and
separate width accumulation. Its complete 279/279-byte comparison has eleven
bindings and three differences at 33/36/38: compare operand orientation and
the signed exit branch. The twelve-byte frame agrees. Do not try names,
declarations or layouts to force this comparison. Original compiler inlining
versus duplicated source spelling is unproven.

Line drawing restores partial descriptor setup, fresh incoming-surface COM
reads, consumed Lock result, post-Lock pitch/pixel consumers and sign branches.
It remains a complete 409/445-byte candidate /379 unaligned differences /zero
relocations. The 140-byte frame agrees, but local homes/address scheduling and
the original subtract/negate correction's source expression remain unexplained.
Keep the natural equivalent subtraction and avoid redundant emission trials.

One `/MT` matching compile compares all four prior UI exacts and five candidates
together; no exact was lost or gained. Current totals remain 169 exact functions,
30,238 complete code bytes and 136 metadata bytes. UI inputs narrow from 35
to the actual fourteen-file recursive project closure. Matching/production
flags agree, so the game reuses that object and 34 independently verified
unchanged objects without another source compile. Native/MinGW builds pass.

The final library passes 1,134 unchanged selected UI cases: 216 each text
measurement/drawing/centering and 486 line cases. Actual glyphs, whole padded
buffers, octants, endpoint order and retries are compared. Real VC4 ball/pause/
editor/save/reload/exit passes with 77 read-only states, five captures, expected
saved bank, exit zero and all 49 originals unchanged. Other scopes and prior
controls stay historical after identity refresh; no full owner or historical
queue was replayed. Source/frame/full-game fidelity stays unproven.

Receipts: `.analysis/exact-ui-text-line/` and
`.analysis/windows-play-ui-text-line/`. Old 11-58 REA dossiers were reused; no
provider session was opened. Snapshot stays at nineteen records /seven primitive
entries. Feedback remains only `/tmp/dxball_rea_feedback_20261010.md`, now
twenty-one entries. Continue genuine rendering/resource/call recovery from
retained evidence; the full reconstruction goal stays active.

## Current lightning clock checkpoint

Countdown at `0x415F40` now uses the independent typed WinMM import. It captures
the real start timestamp before RNG, preserving the order at `0x415F56` and
`0x415F63`, then samples again at `0x415F7F`. The initial replacement expression
compiled RNG before time under VC4; its actual object is retained and rejected
by one existing zero-deadline case. Explicit sequencing restores that behavior
across builds, with meaningful consumed timestamp storage. The final complete
candidate is 1,067/1,057 bytes /992 unaligned differences /51 bindings, with
68/64-byte frames. Original source spelling/register scheduling remains
unproven; avoid layout/name/declaration trials.

All eight prior display exacts stay exact. The unchanged effect-sprite Blt
matches its complete 362-byte contiguous body and 23 bindings with the current
twenty-file recursive recipe. It returns to exact acceptance without a new
direct-case or active-use claim; earlier nonexact receipts remain historical.
Totals are 170 exact functions /30,600 complete code bytes /136 metadata bytes,
283 source-present and 247 scoped semantic acceptances.

Two matching `/MT` compiles were used, including the ordering correction. Both
matching objects were reused for game links, each with 34 verified unchanged
objects; there was no extra production source compile. Native/MinGW builds
pass. Final native and relocated actual VC4 countdown checks each pass the
same 443 selected unchanged direct cases and 48 existing connected frames;
these separate product checks do not double historical case totals. A full
owner suite, historical queue and new Wine play run were not performed.
Previous real-game controls keep their own product identities.

Receipts: `.analysis/exact-lightning-clock/`. Six old 09-29 display dossiers
and the 13-18 effect-sprite dossier were reused; no provider was opened. The
current snapshot remains nineteen records /seven primitive entries. REA
feedback uses only `/tmp/dxball_rea_feedback_20261010.md`, now twenty-two
entries. Entry 22 records 7,989,125 retained bytes versus 51,934 bytes of local
selected projections and suggests explicit call-order/import views and indexed
retained-evidence lookup. These are not measured model-token/cache/latency
savings. Near-complete source and full-game fidelity remain unproven; continue
genuine rendering/resource/call recovery.

## Current DirectX factory checkpoint

Sound initialization calls the genuine external `DirectSoundCreate` stdcall
export; fullscreen/compatible creation call `DirectDrawCreate`. Original REA
callee classification resolves the thunks at `0x416606` /`0x416600` to DSOUND/
DDRAW. The sound wrapper, draw backend facade and dynamic factory lookup are
removed from the active Windows paths. Separate `directx_factory_host.c`
preserves live native callbacks; `directx_factory.h` declares the actual
three-argument ABI with the observed NULL GUID/aggregation inputs.

Both Windows artifacts have clean import tables containing the expected
undecorated SDK exports. The old compiler has no DirectX SDK libraries;
`scripts/directx_imports.py` uses its librarian to generate them, then updates
only the name-hint data to the observed DLL spelling while retaining stdcall
symbols and untouched generated thunk code. No original instructions are copied
or counted as reconstructed game code. A GNU import library that the old linker
accepted produced a damaged descriptor and was rejected; its product remains
private. The normal legacy build now includes both SDK libraries for inspectors
and the game.

All eight sound and seven platform exacts remain exact together. Three matching
source compilations (two sound, one platform) and two changed adapter compiles
were used. The final game reuses both matching objects and 32 independently
verified unchanged objects. Sound/platform recursive project closures contain
17/25 files. Sound initialization remains 1,741/1,705 bytes /1,447 unaligned
differences; fullscreen and compatible remain 1,406/1,343 and 1,180/1,147-byte
candidates. No source-layout/name/declaration trials. Totals stay 170 exact
functions /30,600 complete code bytes /136 metadata bytes, 283 source-present
and 247 scoped semantic acceptances.

Final native checks pass 124 unchanged sound initialization/prepare cases and
48 existing connected focus/reload/recovery checks, plus 304 unchanged creation/
WinMain cases. Native/MinGW builds pass. Final real VC4 startup/ball/pause/editor/
save/reload/exit passes with 77 read-only states, five captures, expected saved
bank, zero exit and all 49 originals unchanged. Other profiles/campaigns remain
historical. No full owner suite/historical queue. Physical/asynchronous audio,
near-complete original source and full-game fidelity remain unproven.

Receipts: `.analysis/exact-sound-factory/` and
`.analysis/windows-play-directx-factories/`; the earlier sound-only SDK play
has its own intermediate product and report. The old sound/fullscreen dossiers
were reused, without opening a provider. Snapshot stays nineteen records /
seven primitive entries. Feedback remains only
`/tmp/dxball_rea_feedback_20261010.md`, now twenty-three numbered entries.
Entry 23 records 10,033,784 retained bytes versus 39,067 bytes of local selected
views and suggests resolved call-site → thunk → DLL/export views. These are
local archive sizes, not measured model-token/cache/latency savings.
Continue genuine rendering/resource/platform/call recovery.

The sealed current checkpoint is
`.analysis/checkpoints/directx-factories-283-170/sha256.json`. It preserves the
current products, recursive inputs, vendor import receipts, reused REA Evidence
and both the rejected import-table control and valid actual play records.

## Current raster controller checkpoint

`src/raster.cpp` restores independent polygon scan controllers, their genuine
runtime malloc/release calls and the horizontal fill's alignment/postfix loops.
The fill at `0x40B4C0` is exact across all144 bytes on one stable VC4 compile.
Eight fixed-point units retain all571 code /136 metadata bytes. Complete triangle
and both polygon bodies remain candidates; no layout/name/declaration trials.
Actual recursive project closure is four files, including `allocator.h`.

Final native and actual relocated VC4 checks each pass the same2,232 selected
existing cases:1,080 polygon,72 triangle,1,080 span. Full guarded pixels, scratch,
normalized pointers and ordered allocation/free/MulDiv calls agree. Native now
exercises genuine allocator bodies through controlled physical heap slots;
original/COFF allocator boundaries remain controlled. Existing failure masks and
assertions are unchanged. No full owner/historical queue or new Wine play run.
Actual raster game use, exceptional unwind and physical driver fidelity remain
unproven. Earlier play controls retain their historical executable hashes.

Native/MinGW builds pass. The VC4 game link reuses the actual matching object
and34 verified unchanged objects, with zero extra production source compiles;
existing resources and SDK import libraries are verified/reused. Global counts
are171 exact /30,744 complete code bytes /136 metadata bytes,283 source-present
and247 scoped semantic rows. Source presence is not full-source/frame fidelity.

Receipts: `.analysis/exact-raster-controllers/`; seal:
`.analysis/checkpoints/raster-controllers-283-171/sha256.json`.
See [current raster recovery](../research/exact/EXACT_RASTER_CONTROLLERS.md).
REA was not opened. Feedback entry24 in the same `/tmp` document records
5,983,244 retained bytes /55,397 local selected bytes and loop-state/allocator
identity usability suggestions, without claiming measured tokens or latency.

## Current ball ownership and rebound checkpoint

`src/balls.c` restores genuine operator-new/delete and direct audio edges,
including the independent live-angle/current bank/height reads after callbacks.
All seven accepted ball exacts remain exact on one VC4 compile; complete removal
208/220 diff 52 and rebound 687/681 diff 550 remain candidates. Eighteen actual
recursive project files are covered by 28 declared inputs, including allocator.h.

Final native and actual relocated VC4 checks each pass 1,085 selected maintained
ball/trig cases with unchanged assertions, plus four separate audio-state
controls. Original code is immutable. The retained old native product fails all
four controls at the expected y field. No physical/asynchronous audio, full owner
queue or new Wine play claim; older campaign records remain historical.
Native/MinGW builds and the VC4 link pass, reusing the matching balls object and 34
verified unchanged objects, resources and SDK libraries; zero extra production
source compiles. Counts remain 171 exact / 30,744 code bytes / 136 metadata bytes,
283 source-present and 247 scoped semantic rows.

Receipts: `.analysis/exact-ball-rebound/`; seal:
`.analysis/checkpoints/ball-rebound-283-171/sha256.json`.
See [ball recovery](../research/exact/EXACT_BALL_REBOUND.md).
REA remains 6.3.0 and was not reopened. Entry 25 in the same existing `/tmp`
feedback document records 2,067,168 archive / 16,492 selected local bytes and
live-state/precision/projection usability findings. No token/latency claim.

## Current entity allocation checkpoint

Latest entity allocation checkpoint: `src/gameplay.c`, `effects.c`, `particles.c`
and `bonuses.c` restore actual new/delete edges; the extracted explosion phase
uses direct RNG/bonus/audio calls. Four matching VC4 compiles preserve 28 exact
units / 5,400 code bytes. Three complete deletion candidates are 208/220 diff 52.
Actual recursive closures 19/18/14/22 are covered by 28 declared inputs each.
Native and actual relocated VC4 pass 1,085 selected entity calls, 264 effect-list
calls and 288 separate existing phase frames, with identical per-case traces.
Fatal subprocesses use existing typed owned loaders; assertions/cases remain.
No full-owner queue, new Wine play or physical driver/audio claim. Native/MinGW
and VC4 game link pass; four matching +31 unchanged objects/resources/SDK imports
are verified/reused. Global counts stay 171 exact / 30,744 code / 136 metadata,
283 source-present and 247 scoped semantic rows.
Receipts `.analysis/exact-entity-allocation/`; seal
`.analysis/checkpoints/entity-allocation-283-171/sha256.json`.
See [entity recovery](../research/exact/EXACT_ENTITY_ALLOCATION.md).
REA stays 6.3.0, unopened; feedback entry 26 in the same existing `/tmp` document
records 11,479,750 archive / 41,676 selected local bytes and callee/ownership
usability suggestions, without measured token/latency claims.

## Working limits and completeness

Latest source recovery: one shared `src/midi.cpp` replaces the C owner, with
C linkage and unchanged headers/widths/layouts. Restart error now has the observed
cleanup goto. One private C++ diagnostic and one production matching compile
establish automatic generation of all four tail stubs/error exits/skipped jumps.
The actual/declared project closure is17/17. Release149/pause133 remain exact;
play516/513 diff169, stop225 diff14, callback127 diff10, parser838/868 diff347,
converter343 diff38, opener480/522 diff406 remain candidates. Extra play bytes
include byte-flag promotion; do not change inferred widths/layouts for matching.
Original language/prototype/source names remain unproven.
Unchanged Native/original and actual MIDI/music COFF each pass2,109 direct cases
and134 separate connected checks, all six songs. Thirteen emitted bodies and
their internal direct calls execute; original code is immutable. Controlled SDK
callback pointer retains original identity; emitted callback is invoked explicitly.
No asynchronous delivery/physical audio/live-game claim. Native/MinGW rebuild
MIDI; VC4 links one matching+34verified unchanged objects/resources/imports.
All171 exact identities remain verified; no full historical replay. Current
build/owner paths migrate; old sealed checkpoints preserve their C source epochs.
See [MIDI lowering](../research/exact/EXACT_MIDI_PLAY_LOWERING.md).
Private `.analysis/exact-midi-play/`; seal
`.analysis/checkpoints/midi-play-283-171/sha256.json`.
REA remains6.3.0, unopened; snapshot20. Entry29 in the same feedback document
records retained byte/facet sizes, source-language/control-flow and incorrect
pseudocode-return usability findings, with no new latency/token measurements.

Latest source batch: `src/geometry.c` restores the rectangle fallback's repeated
`abs` calls, original comparison order and independent nested returns. One VC4
compile yields 329/329 bytes with 22 local EBP displacement differences; candidate
only. Four abs relocations and both otherwise unowned five-byte jumps are
included. Point-angle 109 remains exact; point-distance 130 retains 52 differences.
The six-file actual project closure is covered by 27 declared inputs. Native and
actual relocated VC4 each pass 8,000 unchanged maintained rectangle cases and
full assertions. Native/MinGW rebuild geometry; VC4 links one matching +34
verified unchanged objects/resources/SDK imports, zero extra source compiles.
Historical semantic input rows 235 refresh without changing scopes/counts.
All 171 accepted exact product/input receipts remain verified; no full replay.
See [rectangle recovery](../research/exact/EXACT_RECTANGLE_COLLISION.md).
Private proof `.analysis/exact-rectangle-collision/`; seal
`.analysis/checkpoints/rectangle-collision-283-171/sha256.json`.
The entity-play record below retains the older d544ecf executable identity.
REA 6.3 performed one full 329-byte read, then closed: 20 Evidence/7 primitives.
Entry 28 in the same existing feedback document records actual cold-read timings,
byte sizes and full-span/retained-facet usability suggestions; no token claim.

Latest runtime evidence: the VC4 product from `d544ecf` has a 45.019-second
bounded original-board episode, 3,940 processed SDK records /3,480 game samples,
score 824, board 0, one ball and seven remaining bricks. Particles/animations/
explosions have 252/256/151 nonzero **current** reads; bonuses have 1,088 nonempty
list reads. Zero current is not proof of empty first/last. Sequential samples
and presence changes do not prove individual lifecycle or ownership events.
The observer stops the still-running game; no graceful-exit claim. No new
original/MinGW trajectory, screenshots, full campaign or physical/audio claim.
All 35 game objects/inputs/resources/imports and 49 original assets are verified;
only one SDK reader compilation, zero production compilations. Ledger totals
are unchanged. See [current entity play](../research/CURRENT_ENTITY_PLAY.md).
Private proof `.analysis/windows-entity-use-current/`; seal
`.analysis/checkpoints/entity-play-283-171/sha256.json`.
REA remains 6.3.0; retained contracts suffice without a new provider query.
Entry 27 in the **same existing** `/tmp/dxball_rea_feedback_20261010.md` records
pointer/list labeling and compact original-to-rebuilt state provenance usability
suggestions. No new REA response, token or latency measurements.

Latest origin batch: named PE DLL/name/IAT tuples ground five further CRT
sections and three complete import jumps. All1,048 new section bytes/13
relocations match; each jump's full6bytes match. Current manifest39 sections
/5,327 bytes /40 section origin rows, plus3 jumps /18bytes:43 distinct rows.
Read/Write candidates differ in actual IAT operands; numeric PE addresses stay
separate from EXTERNAL addresses. Four actual-verifier controls reject wrong
cells/DLLs, Read/Write substitution and shifted jumps. Origins now270 authored
/66 runtime /42 generated /150 unknown. Source/exact/semantic/product identities
are unchanged; no provider/compiler/SDK runtime/gameplay process was started.
Private .analysis/import-origin-closure/; seal
.analysis/checkpoints/import-origin-closure-283-171/sha256.json. See
[import origin audit](../research/ORIGIN_AUDIT.md#named-imports-and-complete-forwarding-code).
Feedback entry31 stays in the same existing /tmp document: namespace-aware
addresses, compact import-cell/forwarder/caller views and retained facets.

Previous origin batch: eight further CRT entries are grounded by complete
code sections and definitions from earlier fully verified sections. All
2,142 added bytes and 32 actual relocation operands match. The current manifest
checks 34 complete sections /4,279 bytes /35 origin entries. Future unverified
exports, shifted spans and conflicting established addresses fail three
independent controls. At that preceding checkpoint: 270 authored /58 runtime /42 generated
/158 unknown. Source, function exactness and semantic acceptance are unchanged;
no production build or runtime check was repeated. Original source denominator
and full-game fidelity remain unresolved.
Private proof `.analysis/origin-closure/`; immutable seal
`.analysis/checkpoints/origin-closure-283-171/sha256.json`. See
[origin audit](../research/ORIGIN_AUDIT.md#verified-cross-section-crt-definitions).
REA remains6.3.0, unopened; the complete retained39,136-byte read is PE-verified.
Feedback entry30 in the same existing document records retained range indexing,
definition provenance and compact dependency-view suggestions, without new
latency, cache-hit or token measurements.

Latest origin checkpoint: complete initialized CRT storage and prior definitions.
Thirteen complete code definitions /546 bytes pass; eleven actual external
COFF names supply bindings, while `_doexit` and `__initterm` remain static.
Two independently placed data sections /594 bytes and both pointer relocations
match fresh REA reads and the original PE. Reviewed anchors place zero storage;
a unique complete ctype array is followed by a full relocated comparison.
`_realloc` and `__set_errno` now have complete runtime provenance: 270 authored
/68 runtime /42 generated /148 unknown. The current verifier checks54 code
sections /6,026 bytes /55 code rows plus3 jumps /18 bytes:58 distinct origins.
Data provenance is separate from accepted exact metadata. Five actual-verifier
negative controls pass. Source/exact/semantic/product counts remain unchanged;
no production compilation or gameplay replay. Both new provider sessions closed;
the cumulative snapshot has22 records/seven primitives. Feedback entry32 in
`/tmp/dxball_rea_feedback_20261010.md` records51–62second cold data reads,
canonical legacy/new Evidence shapes and compact storage/anchor-view suggestions.
Private .analysis/crt-data-frontier/; seal
.analysis/checkpoints/crt-data-definitions-283-171/sha256.json. See
[complete CRT storage](../research/CRT_DATA_DEFINITIONS.md).

Latest game-source checkpoint: startup RNG helpers now restore direct CRT
rand/srand calls, signed range remainder and the independent unsigned timeGetTime
seed modulo300. Both complete31/49-byte spans and three relocations match.
One startup compile preserves all three prior startup exacts, including all
literals after emitted-label refresh;16 actual recursive inputs equal the recipe.
The initial stale-label comparison failure is retained, then corrected against
actual emitted literal contents without recompilation. Device initialization
remains359 bytes/10 differences. Exact totals173 /30,824 code bytes /136 metadata;
source283 and scoped semantic247 unchanged. Current Native/original158 existing
startup cases plus one connected dispatch check pass with actual copied-image
RNG import bindings. Native/MinGW builds pass; VC4 reuses one matching object
plus34 unchanged objects/resources/imports, no extra source compile. All173
current receipts have valid object/input identities. Other semantic scopes/counts
remain historical after input refresh; no new live game or full replay.
Private .analysis/startup-rng-recovery/; seal
.analysis/checkpoints/startup-rng-283-173/sha256.json. See
[exact startup RNG](../research/exact/EXACT_STARTUP_RNG.md).
REA remains6.3.0; retained dossiers reused, no new provider session. Feedback33
is appended only to the same existing /tmp document.

Latest list lifetime checkpoint: ordinary C++ delete naturally reproduces both
pointer-copy homes in projectile/fire removal. Both complete220-byte spans are
exact, with the retained five-byte intervals and actual operator-delete binding.
Ten list helpers move to the existing C++ constructor owner, retaining C/ECX
ABI, payload, cursor and nullable-allocation behavior. Paired C++ adapters use
the existing C allocator; ELF symbols are local, leaving other host images'
C++ APIs intact. Initial visibility-attribute and duplicate inline-relocation
failures are retained, corrected before acceptance without body/layout trials.
Two stable matching compiles use actual closures23/13; all18 affected units pass,
including16 preceding exacts. All18 initialization functions retain raw bytes
and relocations. One new adapter compile plus two matching and33 unchanged
objects yields36 verified game objects. Native/MinGW pass; current Native/original
590 direct queue cases plus64 separate connected calls pass. Current VC4 real-Wine
ball/pause/editor/save-reload/exit passes84 reads/five captures/exit0 and49
original identities, with the expected whole saved bank. Other scopes remain
historical; no full replay or synchronized hardware/full-game claim.
Exact totals175 /31,264 code bytes /136 metadata; source283/scoped semantic247
and origins unchanged. Private .analysis/list-delete-recovery/ and
.analysis/core-language-lifetime/; seal
.analysis/checkpoints/list-delete-283-175/sha256.json. See
[exact list delete](../research/exact/EXACT_LIST_DELETE.md).
REA6.3.0 uses retained closed records; snapshot22 unchanged. Feedback34 goes
only into the same existing /tmp document.

Latest entity-list lifetime checkpoint: the remaining explosion, brick-effect,
particle, bonus and ball deletions now use ordinary typed C++ delete. Five
complete220-byte spans match, including every actual relocation and excluded
five-byte jump. Twenty-five list helpers move into the same C++ constructor
owner, preserving existing C/ECX ABI, nullable POD new, untouched payloads,
roots/cursors and ownership. All seven maintained list families now share this
natural allocation/deletion source; game controllers remain in their owners.
Six stable matching compiles preserve48 prior affected exacts and add five,
for53 full comparisons. All18 initializer functions and the ordered36-byte,
nine-relocation constructor table remain unchanged. Current Native/original
passes832 selected maintained list cases, including three terminal allocation
failures. No new vectors/assertions or broad owner replay. Native/MinGW pass;
VC4 reuses six matching objects plus30 verified unchanged objects with no extra
source compilation. Earlier Wine play retains its earlier executable identity;
no new live-game result is claimed. Totals180 /32,364 code bytes /136 metadata;
source283/scoped semantics247/origins unchanged.235 historical semantic input
rows refresh hashes while retaining cases, scopes and original oracle bindings.
Private .analysis/entity-list-delete/; seal
.analysis/checkpoints/entity-list-delete-283-180/sha256.json. See
[complete entity-list deletion](../research/exact/EXACT_ENTITY_LIST_DELETE.md).
REA6.3.0 matches current official npm latest. Five closed dossiers are reused;
one new19,644-byte read attests all five spans, with42,332ms client latency and
162,654 serialized MCP response bytes; full carriers stay outside context.
The provider closed. Feedback35 is appended in the same existing /tmp document.

Latest cursor-return checkpoint: the four projectile/fire begin and advance
bodies now match all57/89 bytes. Natural predicate/fallthrough source preserves
integer ABI, current-before-result writes, exhaustion rewind and original
branch/epilogue topology. One stable list-owner compile retains13 actual inputs.
All42 maintained list functions are exact: seven constructors and five helpers
per seven families.38 prior exacts survive;18 generated initializer functions
and the ordered36-byte/nine-relocation constructor table are unchanged.
Native/original590 direct queue cases plus64 separate connected calls pass,
including two fatal allocations. The raw receipt has separate supplemental
C++/build-input identities; existing cases/assertions/oracles are unchanged.
Native/MinGW rebuild one owner. VC4 reuses one matching+35 unchanged objects,
with zero extra source compiles. No new live-game or broad replay claim.
Totals184 /32,656 code bytes /136 metadata; source283/scoped semantics247/
origins unchanged.235 historical input rows refresh while preserving scope,
cases and original oracle identities. Private .analysis/list-cursor-returns/;
seal .analysis/checkpoints/list-cursor-returns-283-184/sha256.json. See
[exact cursor returns](../research/exact/EXACT_LIST_CURSOR_RETURNS.md).
REA6.3.0 reuses four closed dossiers; snapshot23/seven primitives unchanged.
Feedback36 goes only into the same existing /tmp document. Other owners,
controller storage choices, retirement, unknown origins and full-game fidelity
remain open; do not force layouts or declarations to close those gaps.

Latest retirement checkpoint: natural void source at0x4134B0 matches all32
bytes and three actual relocations. Reused complete callee/controller evidence
shows no local frame or authored result producer and two direct callers that
discard/overwrite EAX. Bounded executable E8/E9 and whole-file literal-address
searches do not exclude indirect/computed callers or establish unique source
spelling. The former inferred integer result contract is explicitly superseded;
the fixture records original EAX separately as diagnostic data. All state,
ownership and integer-list assertions remain. Native/original590 direct cases
plus64 connected calls pass, including210 void retirement vectors and two fatal
allocations.22 stable matching compiles preserve150 prior affected exacts;
18 initializer functions and the ordered36-byte/nine-relocation table stay
unchanged. Three additional genuine game header consumers compiled in the
initial adoption attempt and are reused. Eleven unchanged game objects and
four unchanged matching recipes have original-compiler preprocessing proof of
their actual consumed inputs; overdeclared inventories are narrowed without
body recompilation. Final VC4 links all36 verified objects; Native/MinGW pass.
Totals185 /32,688 code bytes /136 metadata; source283/scoped semantics247 and
origin ledger unchanged. Only retirement scope changes; other cases/scopes
retain their historical boundary after input refresh. No new live-game or broad
replay claim. Private .analysis/projectile-retirement-contract/; immutable seal
.analysis/checkpoints/projectile-retirement-283-185/sha256.json. See
[void retirement](../research/exact/EXACT_PROJECTILE_RETIREMENT.md).
REA6.3.0 matches official npm latest; two closed dossiers are reused and no new
provider request is made. Feedback37 is appended only to the existing
/tmp/dxball_rea_feedback_20261010.md. Remaining controller storage choices,
unknown origins and whole-game fidelity stay open; preserve natural source.

Latest full-frame source checkpoint restores the direct paused return, signed
auxiliary-byte consumer and zero completion predicate. The full candidate is
1691/1688 bytes, with1156 unmasked differences; no new exact claim.379 original
and379 current instructions correspond, with every internal branch preserving
its destination. Remaining differences are three explosion-owner MOV/LEA
address forms caused by recovered contiguous board storage, local stack homes
and shifted branch distances. Do not invent aliases or alter live peer storage
to force agreement. Two actual core compile phases preserve six existing
exacts and all three unchanged core candidates. First-phase runtime passes708
existing frame cases including200 connected frames; after direct pause return
restoration the final product passes24 existing pause/input/timer cases. Those
runtime/source identities remain distinct; active-phase text is unchanged after
unwrapping the outer else. Native/MinGW pass; final VC4 links one matching core
object plus35 unchanged verified objects without extra source compilation.
All185 exact receipts remain current; source283, semantic247 and origins/cases/
scopes unchanged. Private .analysis/frame-signed-consumers/; seal
.analysis/checkpoints/frame-control-flow-283-185/sha256.json. See
[full frame control flow](../research/FRAME_CONTROL_FLOW.md). Two closed
controller/frame dossiers and prior gap evidence are reused; no new REA call.
Feedback38 is appended to the same existing /tmp document. Core storage and
original declaration provenance, unknown origins and whole-game fidelity remain
open. This is progress toward source fidelity, not full-game completion.

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
