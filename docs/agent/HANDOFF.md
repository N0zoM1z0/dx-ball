# Reconstruction handoff

Continue toward nearly complete original English DX-Ball v1.07 source that
rebuilds and plays. The goal is active and incomplete. Prioritize actual source
and game-flow recovery; exact counts alone do not establish completion.
Commit verified checkpoints with English `gpt-6.1-sol: ` subjects and push to
`origin/main`, then independently verify remote HEAD and a clean worktree.

This file is authoritative. The old `/tmp/dxball_reconstruction_handoff.md` is
stale. Optional REA feedback goes only into the existing
`/tmp/dxball_rea_feedback_20261010.md`; latest entry is 77. Append, never create
another feedback/handoff file in `/tmp`. Keep code and repository docs English.

## Current state

Latest checkpoint: **221 exact functions /55,163 code bytes /136 metadata bytes**;
285 source-present, 249 historical semantic scopes and 52 authored nonexact functions.
Bitmap loading now matches all976 bytes,237 instructions and18 relocations.
The consumed loading workspace restores its original2508-byte frame and arithmetic
lowering; input/output sizes, unwritten suffixes/flags and cleanup order remain.
One Bitmap compilation, Linux/MinGW builds and a VC4 relink reusing36 unchanged
objects pass. Existing975 full-buffer cases pass with the verified stack helper
reused without compilation. All221 exact closures verify. No game campaign.
See [Bitmap workspace](../research/exact/EXACT_BITMAP_LOAD_WORKSPACE.md) and
`.analysis/bitmap-load-workspace-20261012/verification.json`. Continue the52 candidates.

Recent retained source checkpoints:

- [File transfer](../research/exact/EXACT_FILE_TRANSFER_STATE.md): complete304-byte
  loader exact, including ten bindings and its four-byte prefix;38 file cases pass.
- [Intro grid cursor](../research/exact/EXACT_INTRO_GRID_CURSOR.md): complete1,996-byte
  initializer exact, fifteen intro companions and full287-point/360-wave case pass.
  [Ranking records](../research/exact/RANKING_ROW_RECORDS.md) restore36-byte frame
  homes but remain403/404 with330 differences; seventeen drawing cases pass.
  Both worsening UI measurement record diagnostics are rejected. Do not repeat them.
- [WAV upload](../research/exact/EXACT_SOUND_UPLOAD_WORKSPACE.md): complete695-byte
  upload exact, completing seventeen configured sound bodies across4,756 bytes;
  227 upload cases pass. [Polygon temporaries](../research/exact/POLYGON_SORT_TEMPORARIES.md)
  restore both80-byte frames/twenty homes;218 differences remain per controller,
  and1080 cases per original/native andVC4/native profile pass.
- [Sound workspaces](../research/exact/EXACT_SOUND_WORKSPACES.md): complete
  1,705/269-byte initialization/parser exact, including 70/5 provider-unowned jumps;
  fourteen prior sound companions and 922 initialization/parser/prepare cases pass.
- [Presentation selection sort](../research/exact/EXACT_PRESENT_SORT_RECORD.md):
  complete 296-byte sort exact, nine display companions and 60 sort/146 merge/60
  presentation cases pass.
- [Screen-point position](../research/exact/EXACT_SCREEN_POSITION.md): complete
  337-byte collision body exact, eight core companions and 1,152 boundary cases pass.
- [MDS workspaces](../research/exact/EXACT_MDS_WORKSPACES.md): parser and
  converter exact across 868/343 bytes, including all 40 provider-unowned parser
  jump bytes. Four MIDI exact companions and 253 parser/588 converter cases pass.
- [Window workspaces](../research/exact/EXACT_WINDOW_WORKSPACES.md): two
  initialization bodies exact across 1,343/1,147 bytes and 224 relocations.
  Nine platform companions and 126 fullscreen/122 compatible cases pass.
- [Optimized RNG](../research/exact/EXACT_RANDOM_RUNTIME.md): two runtime exacts,
  52 bytes and initialized state word; compatible /O2 /MT recipe is integrated.
- [Line cursor](../research/exact/LINE_LOCKED_CURSOR.md):445 complete bytes,
  all140 frame homes and121 instruction boundaries agree; nine comparison
  differences remain. Five exact UI companions and486 pixel cases pass.
- [Rotation origin](../research/exact/ROTATION_ORIGIN_STORAGE.md): two original
  zero writes and three m32 division operands/fallbacks recovered;1451/1572bytes
  retains1475 differences. Four exact companions and695 pixel cases pass.
- [Tile mapper](../research/KNOWLEDGE_BASE.md):426 complete bytes including92
  switch-table bytes and24 bindings exact; six prior board exacts preserved.

[Closed compiler hypotheses](../research/exact/FRONTIER_COMPILER_MODELS.md)
cover condition/negation spellings, UI/Bitmap C++ models, geometry/core /Z7,
UI/resource /Os, sound upload scopes and sprite prototype variants. Do not
repeat them without new evidence. The current window checkpoint also retains
its rejected attachment-record/sibling-result stages. Canonical private products
and unique Evidence remain preserved; completed disposable copies are compressed.

Latest storage cleanup compresses only the completed REA4.1 historical snapshot:
`.analysis/rea-upgrade-6.3.0/snapshot-4.1.0.json.gz` preserves all72,771,098bytes
with verified decompressed SHA; `snapshot-compression.json` records identities
and removal of the raw copy.68,034,560allocated bytes released. Active campaign
inputs/products/probe/report files are untouched. The general cleanup script
requires the writable session lock and includes runtime probes; do not run it
against the live campaign. See [REA storage](REA.md).

STOPPED: the user requires exact function restoration before long game validation.
The independent VC4 campaign received SIGINT at its verified controller identity;
child exit130 and all five recorded process identities inactive are confirmed.
The compiler session is available. Private
`.analysis/current-vc40-campaign-independent/stopped-for-exact/verification.json`
checks108 frozen inputs, four products and unchanged originals, and retains
complete initial slots0–14 plus the final partial observation and SDK logs.
KeyboardInterrupt leaves the harness status as running despite finally cleanup;
the lifecycle receipt establishes termination. This is a deliberate priority
stop, not a full pass or game-source failure. Do not run `verify-finished.py`
or restart the campaign.49 backed runtime copies are removed, releasing
1,708,032allocated bytes; see `stopped-for-exact/cleanup.json`.

Next priority: the 52 authored non-exact functions. Use current manifest objects
under `build/exact/` and validate their input closures; `build/vc40/` contains
older candidate objects. Advance source and complete-unit comparisons with
focused checks. Long campaigns wait until function recovery is ready.

INTERRUPTED: current VC4 full original-bank campaign, executor session7397
returned143. All recorded boot/PID/start-tick identities are inactive. Complete
initial events0–12 are verified; last periodic event3626.414seconds, board12,
157bricks, score29708/lives3. Cause unknown; no game-source failure is established.
No final child/recorder/capture-summary receipt, final harness summary or REA
Evidence exists. Do not invoke the prepared completed-run consumer or restart
this producer for visibility. Full goal50 then terminal50/mode0/clearedrequests
is unproved for this current product.
The game SHA remains7c44dc20c84a7b3c96670200c6a772b1a9263b85c44e58cd057dd0864292a551.
Existing campaign reader/controller are reused on640x480x24; the new campaign
CLI depth defaults24/forwards/reports. Actual SDK reader compiled once with
strictC90/both source-file identities and six selected SDK hashes.
No game compile/link.108run inputs are frozen; only bounded transition samples
remain available. No final SDK stream counters/digest may be inferred.
`.analysis/current-vc40-campaign/interruption-verification.json` verifies all
inputs/products/originals and complete prefix; `interruption-sha256.json`
seals182files. Complete partial observer/Wine/reader/REA logs are verified gzip
carriers in `interrupted/`.49 hash-equal disposable probe files are removed,
1590725bytes released; raw5069846-byte REA log removed after gzip verification.
See [original campaign](../research/ORIGINAL_CAMPAIGN.md); historical full
original/VC4/MinGW runs are proved only for their older recorded products.

An unnecessary duplicate watch-mode SDK extension was compiled once, then
rejected on finding the existing persistent campaign observer. Its source and
binary are restored by hashes without a second compile; rejected stage/receipt
remain private in the same folder. DO NOT recreate this duplicate functionality.
No target writes, hooks or altered boards; full campaign still unproved here.

Completed passive frame supplement:
`.analysis/current-vc40-campaign/play-spotcheck/verification.json` and
`sha256.json`. Three unaltered640x480 frames show actual play;147/148/147colors.
All108 frozen inputs/four products verify; complete initial events0–11 retained.
Later X window owner matches the game's kernel PID/start ticks. Periodic states
are not frame-synchronized: do not assign an exact board or claim pixel fidelity.
No extra game run, target input/write, rebuild or new ledger acceptance.
First ImageMagick client omitted XAUTHORITY and produced no image; corrected
capture reused the controller's existing authorization without changing access.
Completed observation snapshots are byte-exact verified gzip carriers; raw
copies removed, approximately2.5MiB released. See `compression.json`; no live
campaign file is modified. The supplement retains its original digest manifest.
The capture is complete; consume saved report/images instead of restarting it
after the prior client-output truncation. Interrupted campaign7397 is separate.

Current VC4 digital-audio delivery is now observed independently during the
same live campaign: one per-input Pulse monitor records5.948458seconds,
262327finite samples/channel,44651/44539nonzero samples, peaks1.0 and RMS
0.101348/0.071733. The selected sink-input owner matches the recorded game's
PID/start ticks before/after; another application on the same silent sink is
excluded by `--monitor-stream`. No target/routing changes or extra game run.
The2,098,616PCMbytes are preserved byte-exactly in199,929bytegzip; rawcopyremoved.
See [digital-audio evidence](../research/CURRENT_DIGITAL_AUDIO.md).
No physical playback, waveform/mixing/pan/frequency or asynchronousMIDI claim.
The guarded `.analysis/current-vc40-campaign/verify-finished.py` applies only
to a completed capture with terminal receipts. This interrupted attempt cannot
satisfy it; its partial consumer is `verify-interrupted.py`, already completed.

Current-product natural game-over at640x480x24 passes original219/VC4234/
MinGW213 read-only states: nine actual life losses, `rex`/Backspace/Shift-A to
`reA`, independent660-byte ranking expectations in memory/file, fresh-process
reload and six zero-code exits. All three earn222/rank0 with saved rankingSHA
fcc15ac92dc92e402d565da1a7fb5a23afd42d544e3308096a47aba8f65c62e8.
Twelve unaltered frames/eight original-sourceRGBpairs have zero differences;
name-entry/ranking44colors and filled text visible. These are sequential samples,
not moving-frame synchronization or complete-campaign/audio/MIDI proof.
Game-over nowselects `--profile`; game-over/round `--display-depth {8,24}`
default24/forward/report. Round CLI/syntaxchecked only; no new round/focus flow.
No game/reader compilation, link, provider request or owner-oracle replay.
See [current game-over evidence](../research/GAMEOVER_DISPLAY_DEPTH.md).

The cursor follow-up closes the persistent-missing-pointer hypothesis for the
sampled editor states: initial board66 original/69VC4 reads; actual two-cell
paint/save/clear/load75 original/82VC4 reads. Three samples each before reload,
after reload and after motion give36 unaltered frames/18 complete RGB pairs,
all zero differences. Cursor X/Y and draw-to-primary are observed through the
retained read-only SDK reader; all four runs exit zero,49assets unchanged.
Two-cell saved banks equal b88441eb5e06676a106501a60a450b8046fa7b880e8f53ffe5f556ae75a42cd2.
Prior186-pixel snapshot remains historical/unsynchronized; no source defect,
atomic synchronization, all-state fidelity or fresh MinGW cursor run is claimed.
See [editor cursor presentation](../research/EDITOR_CURSOR_PRESENTATION.md).

One canonical paddle compilation tests the natural reversed inequality spelling.
The complete203-byte body and all20bindings are identical to before; four
reversed equality-address bytes remain at139/140/145/146. Reject the diagnostic;
source/object restored by hashes without another compilation. DO NOT repeat
paddle equality spellings or infer a missing operation from the commuted read.
REA dossier ev_5be09046f1c60aeabad5697e07a604bbd89c05139b40ac5bda631e4864a44630
is reused; no new provider request. No native/MinGW rebuild, legacy link, reader
compile or owner-oracle replay. All four products remain byte-identical.

| Current claims | Count |
| --- | ---: |
| Source-present / inferred authored | 285 /270 |
| Scoped semantic acceptances | 249 |
| Complete exact functions | 221 |
| Exact code / separate metadata bytes | 55,163 /136 |
| Runtime /compiler-generated /unknown origins | 117 /42 /99 |

Current product/comparison receipt: `.analysis/bitmap-load-workspace-20261012/verification.json`.
Earlier digital-audio receipts and the 285/206 seal retain their historical products.
Additional current live MIDI unavailable-device receipt:
`.analysis/midi-device-fallback/verification.json`. Original58/VC457 SDK reads;
four ordinary F5 requests each trace stream-open and MIDIERR_INVALIDSETUP,
physical MIDI output devices0/mapper1, absent `/dev/snd/seq`. Music wrapper
returns null, attached-ball game remains responsive, F6/menu/two natural0exits.
105inputs/existingreader/four products/originals verify. No builds/newcases.
First premature-focus startup failure retained; changed input order waitsmode4
beforefocus/Space and succeeds. Original final log includes verified65byte
X teardown tail beyond its reported prefix digest; do not rebase that receipt.
Successful async MIDI/physical audio/fullcampaign remain unproved. See MIDI_OWNER.
Rejected stage: `.analysis/paddle-cursor-load-order/rejected-order-stage/`.
Cleanup only recorded probe copies after unique files are retained, then immutable
hash-equal before/new-seal copies versus immediately preceding display-depth seal.
Game-over cleanup likewise preserves unique exits and compares immutable copies
only with the immediately preceding editor-cursor seal. Public/current files
must remain independent of archives. Consume completed
receipts after output truncation or consumer errors; do not restart producers.

## Working runtime and recent source baseline

Use640x480x24 Xvfb for headless Wine. The game still requests original8-bit
DirectDraw;8-bit host Xvfb drops filled glyph/title pixels even in the original.
Maintained runtime/play checks default24; `--display-depth 8` reproduces history.
Editor input tests hold presses until actual selection/paint acknowledgement.
[Display/deployment](../research/WINDOWS_DISPLAY_DEPTH.md) records original103,
VC4115 and repairedMinGW116 states,15captures, real ball/pause/editor/save/reload/
zeroexit, and complete equal saved banks. Opening/initial-editor full RGB buffers
agree; animation/clock observations remain unsynchronized. MinGW core links
compiler support statically, including POSIX pthread: imports onlyddraw/dsound/
Kernel32/msvcrt. That repair relinks with43unchanged objects and zero source
compiles; native/VC4 products unchanged. Current cursor runs follow this baseline.

[Random runtime](../research/RANDOM_RUNTIME.md) fixes differing host rand defaults:
original seed1 gives41/18467/6334/26500/19169. Shared unsigned32 global state starts1,
uses214013U*state+2531011U and mask7FFF0000/shift16. Actual startup seed remains
unsigned clock modulo300; range remains signed remainder.169seeds/2728directnext/
90realrange/8clockseed cases and158startup+1connected check passed once.
Six startup exacts1381bytes remain. Runtime seed19/10/19diff andnext65/42/62diff
are candidates, not optimized vendor exactness or unique source spelling.
Complete52 original bytes/3actual COFF fields corroborate runtime origin and
observed cell4230F4, not independently unique CRT data placement.

## Preserve these closed questions

These notes retain complete proofs and compiler stages. Reuse them instead of
repeating speculative source, declaration, capacity or spelling permutations.

- [Rotation traversal](../research/exact/ROTATION_PIXEL_TRAVERSAL.md): renderer1447/
  original1572/1491diff; actual traversal/dimension/pointer/Unlock/float operations
  restored, full operand/frame/width equality unproved. Float2.0 m32 versus emitted
  m64 remains unresolved. Rejected stored-float trial loses three projections;
  preserve it and accepted stage. No fake locals for two unclassified zeros.
  Y-offset191bytes/10bindings exact; unchanged height193/191/158diff is candidate.
- [Screen-point stages](../research/exact/SCREEN_POINT_STAGES.md): complete337bytes,
  26 scalar-frame-home differences; all90operations/13branches/2calls/10bindings
  correspond. No new missing-operation or name/layout hypothesis.
- [Platform owner](../research/PLATFORM_OWNER.md) and
  [display initialization](../research/exact/EXACT_DISPLAY_INITIALIZATION_FRAME.md):
  complete fullscreen/compatible operations map through typed frames/registers;
  retire layout/name trials. [Main frame](../research/exact/MAIN_FRAME.md),
  [device frame](../research/exact/DEVICE_FRAME.md) and
  [control flow](../research/FRAME_CONTROL_FLOW.md) retain complete source phases.
- [Capture flow](../research/exact/EXACT_CAPTURE_ADDRESS_FLOW.md): all248instructions,
  18bank-address groups/140byte frame explained;876/852/803diff candidate.
  [Region flow](../research/exact/EXACT_REGION_ADDRESS_FLOW.md) similarly closes
  aggregate address scheduling. LEA versus MOV of aggregate owners is not a new
  producer. [PCX](../research/exact/EXACT_PCX_PACKET_LOOP.md) retains independent
  packet paths and original tail increment; register/frame/commuted arithmetic
  differs. Glyph and draw-line addressing have already been reviewed.
- [Score strip](../research/exact/SCORE_STRIP_SOURCE.md),
  [intro storage](../research/INTRO_POINT_STORAGE.md) and
  [intro request writes](../research/exact/INTRO_UNUSED_FILL_WRITES.md): retain real
  source writes. Do not expand arrays from reserved frame gaps (intro32/11 versus
  gaps100/20, score eight-byte gap) or split coextensive scopes without evidence.
  Equal-CMP reversals in measure-text/score insertion already have trial evidence.
- [Early helpers](../research/exact/EXACT_EARLY_HELPERS.md): the16-byte no-effect
  entry40CC20 remains unknown origin. Bounded initialized-pointer searches do not
  prove complete incoming-reference absence or authored ownership. Source-present
  and byte equality do not establish its original source role.
- [CRT storage closure](../research/CRT_INITIALIZED_STORAGE_CLOSURE.md) and
  [FDIV frontier](../research/CRT_FDIV_INITIALIZATION_FRONTIER.md): maintained
  authority is89complete code sections/20data sections/seven initialized objects.
  Unresolved BSS and FP initializer callbacks remain open;23/1/56/16-byte entries
  lack independent16-byte anchors. Static symbol names are member-local; initialized
  definitions do not place themselves. Never weaken unique placement, scopes,
  namespaces or verifier gates to promote compatibility discovery.

## Next work and operating rules

Find the next concrete missing state operation, call/ABI, resource lifetime or
actual game-flow failure. Inspect `config/functions.csv`, current owner notes,
full retained REA assembly and emitted complete units. The remaining99 origins,
full authored denominator, original source spelling/link selection, physical
rendering/audio/MIDI, synchronized moving frames and complete campaign remain
unproved. Keep the original objective intact; do not mark complete from tests.
The sampled editor pointer is now closed as a persistent source-gap hypothesis.

- Read [workflow](WORKFLOW.md); run Python via `scripts/repo-python`.
- New binary queries use `scripts/rea`; pinned/currentREA6.4.0/Ghidra12.1.4,
  one allowedCPU and512MiB provider heap. Reuse saved dossiers first; retain full
  Evidence IDs/target hashes and close/save every opened session.
- One writable compiler/provider/Wine session via `legacy_toolchain.session_lock()`;
  CMake `--parallel 1`. Automated audio uses `PULSE_SINK=dxball_reconstruction_silent`.
- Natural typed source shared by portable/legacy builds; preserve ABI,widths,
  ownership, actual writes/call order. No machine-code copies, assembly,padding,
  fake locals, alternate profile bodies or blind storage/name/capacity trials.
- Compile once per stable family; compare every affected accepted unit with actual
  relocations/full literals/complete extents. Run only the minimum useful affected
  Oracle or runtime check. Refresh historical input inventories without claiming
  new case execution. Do not repeat successful historical/full queues.
- Live handle/terminal receipts determine process state. Observation timeout or
  truncated client output is not producer failure. Recover bounded saved output,
  repair consumers and reuse completed products; never restart just for visibility.
- Keep originals/tools/products/raw evidence private. Cleanup only verified
  disposable files or immutable hash-equal copies; preserve unique stages, evidence,
  manual saves and archive/current inode independence. Do not recreate install caches.

The previous100,614-byte chronological handoff is preserved in Git at
[2d2b0dd](https://github.com/N0zoM1z0/dx-ball/blob/2d2b0dd/docs/agent/HANDOFF.md)
and `.analysis/paddle-cursor-load-order/before/docs/agent/HANDOFF.md`.
Historical case/compiler counts belong to those recorded products, not this run.
Use the linked focused research notes for detail; keep this handoff compact.
