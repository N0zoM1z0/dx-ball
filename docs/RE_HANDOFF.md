# Current handoff

The original target is DX-Ball v1.07, English, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
The provided archive is private under the parent `game_exe/`; verified files
live under ignored `original/`. Ghidra 12.1.3 imported 528 provisional functions.
Its private project is `ghidra-project/DXBALL`.

The first maintained family is board-bank I/O, editor load/store, per-board
initialization, tile-to-sprite mapping, active-surface selection, and board
drawing. Original x86 execution is the behavioral oracle. File I/O and rendering
dependencies are intercepted; memcpy/memset execute the target's actual CRT.
Drawing validation checks ordered call arguments, not pixels or DirectDraw.

Portable builds are analysis libraries and a board-inspection utility. Windows
builds now also produce experimental game EXEs with real Win32, DirectDraw,
DirectSound and WinMM bindings. Original/VC4/MinGW Wine control runs cover
opening/menu, ball/paddle/pause, editor bank persistence, natural game-over/name/
ranking persistence and zero-code shutdown; complete gameplay,
actual physical device delivery and asynchronous MIDI remain unverified.
DirectSound/WAV and MDS/music controllers have scoped implementations. Main ball motion,
full frame routing/drawing, game initialization and life-loss reset now have
scoped maintained implementations. All twelve frame phases default to source.

VC4.0 compiler 10.00.5270 and linker 3.00.5270 are pinned and executable.
Forty configured units cold-replay exactly, totaling 4,079 bytes; accepted
records are in `config/matches.csv`. Two hundred fourteen source functions have scoped
semantic evidence from 95,873 differential cases. Eight oracle rejection checks
pass. The second owner, `src/resources.c`, covers 15 sprite/font/PCX/palette
functions. Its 1,869 cases execute actual target parsing and compare decoded
pixels, pitch padding, initialized records and DirectDraw call traces. See
`docs/RESOURCE_OWNER.md` for ownership, original quirks and acceptance limits.

Exact replay now compiles owner-specific build groups. `source-owners.toml`
declares semantic inputs, and both acceptance ledgers bind complete input sets,
including shared headers/oracle helpers. Board oracle hooks 0x404180; resource
oracle removes that hook and executes the actual sprite function. DirectDraw
hardware rasterization remains unresolved. The third owner, `src/gameplay.c`,
adds tile hits, explosion request-list helpers, explosive scan and sound pan, validated
with 13,689 original-x86 cases. Append, pan, scan and three request helpers also match exactly; hit
logic has semantic acceptance only. See `docs/GAMEPLAY_OWNER.md` for REA
Evidence IDs, original quirks and controlled dependency boundaries.

The fourth owner, `src/effects.c`, recovers nine animation functions with 12,977
direct cases, 864 bounded original-frame phase cases, and 1,536 hit-to-animation
integration cases. Integration counts are separate from function acceptance.
Five animation units match exactly; deletion and timer steps remain semantic-only.
REA now
confirms that `0x412B52` belongs to enqueue producer `0x412B30`, not a consumer.
Explosion requests at `0x43F8E0` and brick animations at `0x43FA98` are distinct
typed containers; the auxiliary grid guards duplicate animation creation.
Delete-then-advance skips a successor and is preserved across frames. See
`docs/EFFECTS_OWNER.md` for body ranges, Evidence IDs and acceptance boundaries.
`dxball_apply_explosion_requests` extracts the request phase but does not claim
the whole frame updater.

The fifth and sixth owners recover seven particle and seven bonus functions.
They add 7,343 direct cases and 980 connected-body integration checks, plus nine
complete exact units. Gameplay particles and animation bonus production now
default to maintained source. Particle writes agree across complete controlled
8-bit buffers; the DirectDraw driver is still pending. See `docs/ENTITIES_OWNER.md`
for all fourteen REA Evidence IDs, typed layouts, RNG order and exact boundaries.
The entity checkpoint used pan literal names `$T637` / `$T638`, with both
contents attested; the current sound checkpoint uses `$T1072` / `$T1073`.

The bonus updater at `0x413E20`, Evidence
`ev_927b00b89e0931308e5cd78eb83b9e33a11d5e7c63e32d7d9da49f53ca6f81cf`:
2,087 owned bytes in a 2,168-byte span, is now maintained. The connected batch
adds 21 functions and 15,934 cases across bonus application, board powers,
geometry, paddle position, round transitions, ball ownership/release/cloning,
computed trig and paddle rebounds. Seven new exact units add 675 bytes. See
`docs/POWERUPS_OWNER.md` for complete Evidence IDs and scopes. Terminal level
initialization at index 50 is controlled; original adjacent-memory behavior
remains unresolved. Sixteen multi-frame bonus checks are included in this
batch's direct total, not added as separate acceptance counts.

The preceding core checkpoint added nine functions and 4,580 direct cases, including
200 continuous frames as a subset. Main ball updater 0x410770 (3,223 bytes) and
full gameplay frame 0x40F8B0 (1,683 owned / 1,688 span) are maintained alongside
point hits, retirement, drops, fire effects and shooting. See `docs/CORE_OWNER.md`
for every Evidence ID, typed queue, original collision/input order and scope.
All twelve frame callbacks now default to maintained runtime/display source;
COM drivers, audio and UI/platform integration remain pending. Surface recovery
is now maintained in the device owner. Global 0x43A884 is now correctly named displayed_score.
No new exact claims were made while prioritizing core behavior.

The preceding runtime checkpoint added sixteen functions and 1,510 direct cases,
including 36 continuous frames as a subset. Actual game initialization 0x40F4C0,
mode dispatch 0x403730, life-loss reset 0x415DF0 / 0x415C40, paddle animation,
clock, score, redraw and disposal now execute alongside real gameplay bodies.
See `docs/RUNTIME_OWNER.md` for all Evidence IDs, body ranges and controlled
boundaries. Clock/elapsed/score/paddle/reset default to maintained source.
Resource loading defaults to existing parsers but is controlled in this lifecycle
oracle; glyph/render/audio/device setup and modes other than 1 remain pending.
The unsigned score-refresh JBE branch is preserved.

The preceding display checkpoint adds sixteen entries and 2,409 direct cases.
Another 192 continuous frames are separate integration evidence, not counted
again as direct cases. Last-brick logic 0x415F40 (1,057 bytes), dirty restoration
0x408CC0 (827 bytes) and sort/merge/presentation 0x409100 (984 bytes) connect to
palette, sprite, wait/flip and region helpers. All twelve original frame phases
execute in the new oracle. See `docs/DISPLAY_OWNER.md` for Evidence IDs, arrays,
quirks, corrected names and precise backend scope. Source now defaults board,
effect, particle and runtime reset/bind operations to these maintained owners.

The former restore_surfaces label at 0x409610 is corrected to wait_frames:
it uses software clock polling or DirectDraw WaitForVerticalBlank. Global
0x4228D0 is draw_to_primary, matching initialization and frame consumers.
Last-brick expiry queues an explosion request at 0x412B30 before frame-end
application; it does not create the animation immediately. Presentation retains
original selection sorting, sequential merging and BUSY/SURFACELOST behavior.

The preceding device checkpoint adds six entries and 1,115 direct cases. Palette
transition 0x40A340 (1,339 bytes), palette creation, color fills, sprite-bank
restoration, surface recovery and synchronization now connect to actual waits,
redraw and frame dispatch. Another 26 connected checks are separate integration
evidence, covering lost presentation, frame synchronization and init/cleanup
fades. See docs/DEVICE_OWNER.md for all Evidence IDs and explicit COM/reload/
glyph/audio/platform scope. Recovery restores primary 0x4228B4 then board
working surface 0x4228BC; it does not restore presentation secondary 0x4228B8.
Synchronization calls GetBltStatus at slot 13, not GetFlipStatus.

Addresses 0x4265AC /0x4265B0 are bank 2 count/allocation_mode, not independent
text settings. Source and lifecycle tests now share actual bank storage and
compare all three banks' metadata. New native background COM objects replace
opaque trace-only handles when invoking maintained clears. Palette fades retain
their final extra SetEntries/wait and distinct equality gates.

REA establishes that 0x40E570 initializes the mode-0 intro point table;
gameplay initialization is 0x40F4C0. WinMain 0x40D930, window/input routing and DirectDraw creation now have scoped
platform implementations. Continue through actual Windows binding, mode-0 intro, mode-3 game-over/UI and audio. Retained
0x403A00 initializes working resources and vblank timing, not the WinMain entry;
0x401000 /0x401210 handle MDS music loading, and 0x4026A0 rotates sprite pixels.
Do not guess their roles from sizes or address ranges. Inspect connected bosses
through REA before independent leaf matching. The 10-33 interactive
session saved 152 cumulative Evidence records. Feedback continues in
`/tmp/dxball_rea_feedback.md`. These libraries are still not a playable game.

This shared source/header change performs one grouped cold replay of all forty
accepted exact units, every earlier differential suite, native/MinGW/VC4 builds,
Wine inspector comparison, rejection tests and saved REA verification. The
read/write bank literals were rebound to $SG731 /$SG735 only after verifying
unchanged rb/wb bytes in both object and target; offsets/types/addends and full
comparison remain strict. No new exact claim is made. Semantic input sets now
include all maintained source/header closure, and exact build inputs include
all shared headers. Private reports, literal binding review and current identities
are retained under `.analysis/checkpoints/device-123-40/`. Batch replay remains
the policy; no per-function replay is required.

The user requires modest CPU/memory use. Project build and REA entry points
inherit one allowed Linux CPU; CMake uses `--parallel 1`. Ghidra's heap is
limited to 512 MiB. Measured complete REA process-tree RSS exceeds that heap
because JVM native overhead, Node and Ghidra subprocesses are separate; do not
describe the heap as a process-tree memory bound. A clean native build peaked
at about 57 MiB RSS. The project MCP client uses the pinned split SDK's
`callTool(params, options)` signature so the 360-second deadline actually applies.

New binary analysis now uses REA 4.1.0 / Ghidra 12.1.4 through `scripts/rea`.
Codex MCP registration and the package-matched skill are installed. Direct
agent tools require restart/reconnect; CLI and the project MCP session helper
have already completed real target queries. See `docs/REA.md` and
`config/rea-verification.json`. The old 12.1.3 project is historical evidence.

REA's tile-hit dossier, Evidence
`ev_d09866ff22dc07f3ac28ef1d992c5876c1e58e1796dbe0f0c5c2814544aa27eb`,
reports body ranges 0x411F40..0x4123EE and 0x412436..0x412462: 1,244 owned
bytes, 1,315-byte span. Raw complete dossier and snapshot are under ignored
`.analysis/rea/`. Its overview reports 624 procedures; retain the original
528-candidate ledger until inventory/origin reconciliation. The independent
PE load-image check is unsupported; our separately verified 105-byte sprite
read does not prove the whole load image.

Commit subjects retain `gpt-6.1-sol: `. Include detailed English bodies describing
actual REA operations, evidence, implementation and validation where relevant;
mention REA naturally rather than inserting it into unrelated changes.

The platform checkpoint adds eleven entries and 4,742 direct cases
(**134 maintained / 75,670 direct / 40 exact / 4,079 bytes**). See
`docs/PLATFORM_OWNER.md` for all REA Evidence IDs, owned/span extents and Windows
API scope. The closed 11-04 session saved 163 cumulative Evidence records.
WinMain and WndProc both retain stdcall cleanup of sixteen argument bytes.
Newly identified startup-only COM signatures are typed in the platform header
over the resource owner's opaque slots; extending the shared vtable types
changed VC4 register allocation and failed strict replay, so that draft was
not accepted. The natural owner boundary restores all earlier exact units
without source profiles, padding, assembly or comparison exceptions.

Input evidence identifies shared restart_requested at 0x43A90C as the
pause-fade gate and bonus_9_active at 0x43A890 as F1/F2 state. Do not introduce
independent pause flags or confuse it with bonus_12_active at 0x43A910.
Compatible creation preserves reduced/low-memory state and stale secondary
handles; fullscreen uses a strict 310000-byte free-video-memory threshold.
Only DDSD-selected descriptor fields are meaningful; original unwritten stack
bytes are excluded. Windows/audio/MIDI/non-game/resource/glyph APIs are
controlled, with real message callback delivery and drivers still pending.
Platform builds remain analysis products, not a playable executable.

All earlier oracles, 40 cold exact units, eight rejection checks, native/MinGW/
VC4 builds, Wine inspectors and saved REA verification pass at this grouped
checkpoint. Full input identities/reports are private at
`.analysis/checkpoints/platform-134-40/`. Startup's existing-instance message
ends with a period, and the process-exit callback must never return.

Local housekeeping recovered 164.64 MiB by deduplicating identical catalogs
in closed REA archives, deleting root aliases only after verifying archived
byte-identical results, and removing superseded probe objects/logs. Evidence
paths, snapshots, tools and checkpoint reports survive. Use
`scripts/repo-python scripts/clean-local.py` for a preview, add `--apply` for
cleanup, and retain the private `.analysis/cleanup/` SHA-256 operation journal.
The saved REA smoke verifier passes after cleanup.

The startup/UI checkpoint adds six working-resource functions and
eight shared UI functions. REA 11-58 dossiers retain 198 cumulative Evidence
records; 0x403A00 uses its previously saved dossier. See
`docs/STARTUP_UI_OWNER.md`. Native/MinGW/VC4 now compile `startup.c` and `ui.c`.
Startup, text, centered text, range RNG and bank release default to maintained
source in production dependency tables. Fresh buffer/reset/primary/software
state and text spacing match original initial values of 1. Fourteen new entries
have 1,424 direct cases, with one separate connected startup-dispatch check.
All prior suites, forty cold exact units, eight rejection checks, three toolchains,
Wine inspectors and saved REA verification pass as one batch. Reports/input
identities are at `.analysis/checkpoints/startup-ui-148-40/`.

The menu/splash checkpoint adds twenty entries and 5,615 direct cases,
plus 58 separate mode/key transition checks. See `docs/INTRO_OWNER.md` for all
Evidence IDs, owned/span extents, program data and acceptance domains. Reused
complete 11-58 REA dossiers without opening another session. Mode/key tables
now default modes 0, 1 and 4 to maintained source. Last Score shares existing
0x422D18, not an independent global. Point animation uses keyed sprite 0x404040.
Wave arguments/scales come from retained instructions/data. Credits-wave
invocation remains redraw-only; SetEntries retains the original span+48 count.
The native descriptor bridge strictly checks request size 108/flags 14 and
returns pixels through host pointers; it does not assert raw host/x86 layout.

All earlier suites, 40 cold exact units, eight rejection checks, native/MinGW/
VC4 products, Wine inspectors and saved REA verification pass as one grouped
checkpoint. Current pan literal bindings remain $T637/$T638, unchanged. Complete
reports/input identities are at `.analysis/checkpoints/intro-168-40/`.
Cleanup preview finds no additional disposable artifacts after earlier
195.15 MiB recovery; immutable evidence, snapshots and checkpoints survive.

The game-over checkpoint adds eight entries and 6,531 direct cases, plus
76 separate finish-game/mode/key/menu transition checks. See
`docs/GAMEOVER_OWNER.md` for Evidence IDs, body ranges, state ownership,
ranking/name behavior, file persistence and accepted domains. One REA
interactive session obtained thirteen sequential results and explicitly closed
with 211 cumulative Evidence records. Native/MinGW/VC4 now compile gameover.c;
production mode/key tables default modes 0, 1, 3 and 4 to maintained source.
Rank insertion re-reads scores, orders equal scores before existing equals,
shifts names with strcpy preserving poison tails and attempts persistence only
for access(path, 2) == 0. Shift must equal 1 for uppercase name entry. The
non-editing key switch is a confirmed no-op. Default C-locale conversion bodies
execute in the original oracle; FID library labels do not establish compiler
version. Direct ranking requires a valid selected surface in the fixture.

All earlier suites, forty cold exact units, eight rejection checks, three
compiler products, Wine inspectors and saved REA verification pass at the
family checkpoint. The fresh game-over report is reused with identical complete
inputs and native-library identity, avoiding duplicate replay. Full reports,
input identities and logs are at `.analysis/checkpoints/gameover-176-40/`.

The editor checkpoint adds ten entries and 2,921 direct cases, plus 32 separate
menu/editor/board-command/Escape/menu/game transition checks. See
`docs/EDITOR_OWNER.md` for all Evidence IDs, reconciled owned/span ranges,
state ownership and accepted storage/backend domains. One REA interactive
session collected thirteen results and closed with 224 cumulative records.
Mode/key tables now default all five modes to maintained source. Selected tile
0x438AF0 is a DWORD whose low byte is painted; the 100-record hit table ends
at the separate existing clock divisor. Argument 23 stores count 24 and clears
25 records; lookup includes edges and retains the highest matching region.
Backspace clears only working tiles. Plus/minus store before switching or
clamping; L/S reuse existing actual bank I/O. Native host stdio and original
controlled CRT use independent files. Tool selection invalidates 0x408B70;
it does not immediately copy a region (0x408A50). Empty F-key cases are no-ops.

Earlier suites, forty cold exact units, eight rejection checks, native/MinGW/
VC4 builds, Wine inspectors and saved REA verification run at this grouped
checkpoint. The editor report is reused only with identical complete inputs
and native-library identity. Checkpoint records are retained under
`.analysis/checkpoints/editor-186-40/`. Journaled cleanup recovered another
12.28 MiB of duplicate closed-run catalogs/root aliases; original evidence,
snapshot, tools and checkpoint records remain intact.

Continue into real DirectSound/Windows/WinMM adapters and
complete EXE integration.
Prefer connected controller families over independent leaves and reuse retained
REA dossiers before new queries. Full playable reconstruction remains active.
Mode 4 initializes first and routes to mode 0. Keep resource and clock behavior
connected, explicit-count UI strings (including NUL/padding), the 287-record
point table and the 360-pair wave table. All five controller families have scoped
original-execution evidence; actual driver/backend delivery remains pending.


The MDS/music checkpoint adds thirteen entries with 2,109 direct cases and
134 separate connected lifecycle checks. Reused open/parser REA dossiers;
one constrained session obtained eleven further dossiers and one data read,
then explicitly closed with 236 cumulative Evidence records. See
`docs/MIDI_OWNER.md` for every ID, body range, ownership and accepted domain.
Original instructions return 6/7 on play state errors despite pseudocode zero;
the callback has five stdcall parameters and RET 0x14 despite inferred four.
Headers/context grow naturally to 120/48 bytes on the native host versus 64/36
on i686. Import header-size requests stay 64; native fixtures check this boundary
without pretending host records have the original raw layout.

The independent oracle executes actual parser/converter/controller/callback
bodies against all six private songs and bounded malformed/failure fixtures.
Partial event writes, output preservation, lock-failure leak, dangling freed
buffer pointer, pending count, loop/pause/stop flags and ignored cleanup errors
are preserved. Platform load/resume/pause/close and final runtime music close
default to maintained source. Kernel32/WinMM implementations and asynchronous
hardware scheduling remain controlled; there is no playable EXE yet.

All earlier suites, forty cold exact units, eight rejection checks, native,
MinGW/VC4 builds, Wine inspectors and saved REA verification run as one group.
Complete input/native-library identities and reports are retained at
`.analysis/checkpoints/midi-199-40/`. No new exact claim is made. Cleanup freed
10.18 MiB of duplicate archived aliases/catalogs during collection; final
cleanup checks again for disposable artifacts while retaining evidence/tools.
The previous public CI job could not acquire a runner after five attempts;
rerun requests returned HTTP500. This is external infrastructure evidence,
not a local verification pass or a code failure.


The MDS checkpoint's remote run 37647258018 obtained a runner and exposed a
GCC 13.3 format-overflow error in the editor decimal scratch buffer. It is a
code portability failure, distinct from the preceding runner-acquisition
failure. Shared scratch capacity is now 12 bytes for signed 32-bit formatting;
the accepted board domain and display calls remain unchanged. Native builds
now use locally available GCC 13.3, matching the remote warning behavior.
After switching compilers, explicitly reconfigure Debug: CMake can reset the
build-type cache during a compiler change. An interrupted initial replay is
retained as incomplete, and only the final complete replay refreshes evidence.
Current source/input/native-library hashes, full grouped regression and public
CI records are retained at `.analysis/checkpoints/editor-format-199-40/`.


Next core family: the provisional 1,705-byte DirectSound initializer at `0x405120`,
its `0x4050F0` preparation wrapper, `0x4057D0` pause controller and connected WAV/
buffer lifecycle. Existing platform harness boundaries establish their caller
addresses, not their recovered bodies. Reuse archived REA Evidence before a
new constrained query session; do not classify unreviewed leaves by proximity.

The DirectSound checkpoint adds fifteen connected entries in src/sound.c with
1,603 direct cases and 36 separate lifecycle checks, covering all 26 original
WAV assets, split buffer locks, startup dialogs/terminal exits, pause/reinitialize
and lost-buffer reload/retry. See docs/SOUND_OWNER.md for every REA Evidence ID,
body ranges, COM slots, the 20-byte descriptor, allocation37 uncertainty and
explicit dangling-record/handle-leak failure scope. Audio callbacks now default
to maintained controllers; real DirectSound/WinMM/DirectDraw adapters and a
playable EXE remain pending. Current screen-pan VC4 literals are $T1072/$T1073;
complete cold comparison still checks their original data and every byte.
The native compiler is GCC13.3 Debug; single-job MinGW and pinned VC4 builds
share the same C source. Periodic cleanup journals preserve originals, pinned
tools, immutable REA evidence and accepted checkpoints.

Windows adapter preflight now has SDK-backed i686 ABI probes in
tests/windows_core_abi.c and tests/windows_directx_abi.c, run by
tests/test_windows_abi.py. Core Win32/WinMM layouts pass both VC4 and MinGW;
the DirectX SDK corroborates the 20-byte original descriptor, 108-byte surface
descriptor, 100-byte fill record and every called COM slot. Three console
probes execute under Wine and preserve their outputs/identities. No source
owner/header, acceptance count, native library or existing exact input changed;
the complete sound checkpoint's oracles remain reusable. The private CI adds
the ABI check. See docs/WINDOWS_ADAPTER.md for scope and remaining real binding.

Sound checkpoint commit 36a097c passed all local checks. Remote run 37655488010
failed before any step: GitHub reported five unsuccessful runner acquisitions,
runner_id0 and no steps; the failed-job rerun API returned HTTP500. Original
remote metadata/annotations are retained in the private sound checkpoint.
This infrastructure result does not establish a public compiler failure.

The Windows adapter checkpoint reuses the saved platform/resource/MIDI/sound
REA contracts and binds actual SDK APIs through src/windows_adapter.c, with an
SDK WinMain entry in src/windows_entry.c. VC4 and MinGW build game EXEs; no
owner body/header, function acceptance count or native analysis-library hash
changed. Declared semantic inputs and all forty exact build input sets remain
unchanged, so the complete sound checkpoint's original-execution/cold replay
reports remain reusable. Changed build orchestration is checked separately.

tests/test_windows_runtime.py runs the original and both builds sequentially
on Xvfb640x480x8 through opening/key-to-menu/held-click-to-first-board/Escape-to-
menu/Escape-to-zero-exit. Captures/logs/identities survive under build/reports;
the reviewed first-board tile region has zero differing pixels in both source
builds, while whole-screen unsynchronized differences remain reported. Early
X focus intervention left the original at a blank window; the final harness
waits for actual nonblank presentation before focus. The same palette artifacts
appear in the original control, and ALSA MIDI delivery is unavailable. Real
ball play, editor, focus recovery, all boards, embedded resources and physical
audio remain open; do not mark the reconstruction complete.

scripts/run-windows.py prepares a verified data copy and preserves manual saves;
scripts/build-windows.py serializes/limits MinGW compilation. Public CI now
also compiles the Windows adapter with strict warnings. Private CI includes the
runtime probe after ABI checks. Periodic cleanup journals remove only resettable
probe-* working copies; manual runtime directories and accepted evidence stay.

The Windows gameplay checkpoint adds tests/windows_state_reader.c and
tests/test_windows_play.py. The observer only reads process state using Win32
query/read rights, with original addresses from retained REA-derived oracle
contracts, VC4 linker-map symbols and MinGW remote DLL/export offsets. The
original and both source builds pass real paddle x480/x200, ball release/motion,
P pause/frozen-ball/resume, Control-F1 editor, held-Control paint, whole-bank S,
next/previous board, Backspace/L and file-recreating S, editor return to completed
menu mode and zero-code shutdown. The three 20,000-byte saved banks are identical
SHA256 b88441eb5e06676a106501a60a450b8046fa7b880e8f53ffe5f556ae75a42cd2.

The previous exploratory editor exit remains an incomplete attempt, not a
source failure. Original live state establishes mode0/end_requested1 during
initialization, then end_requested0 at completion; subsequent input now waits
for that boundary. Pause flags similarly precede completed fades. Original
file recreation uses lowercase default.bds after uppercase probe-file removal;
the runtime preparer now preserves manual saves regardless of case and resets
only probe aliases. No owner body/header or declared semantic/exact input was
changed. VC4 now emits a map; strict C90/O3 observer compilation and public
Windows compilation are separate build checks. Preserve complete new actual
runtime reports and reuse unchanged core/exact acceptance with hash checks.
Final original/VC4/MinGW runs contain 86/87/82 read-only state observations;
reports, saved banks, initial attempts, SDK/compiler identities and the
67-input/eight-build reuse audit are retained in
`.analysis/checkpoints/windows-play-214-40/`. Journaled cleanup removed
4.85 MiB of resettable probe files after retaining those artifacts.

Next real-runtime families: natural life-loss/game-over/ranking persistence,
focus/surface recovery, level progression, embedded resources and actual
audio/asynchronous MIDI delivery. Full reconstruction remains unproven.

The natural game-over checkpoint adds tests/test_windows_gameover.py and a
bounded 660-byte score-table read to the SDK observer. Retained REA/oracle state
contracts identify name-entry/ranking globals and the fifteen-record score table.
Actual mouse input misses three released balls, observing lives 3/2/1/0 before
completed mode3. Keys enter rex, Backspace, Shift-A and Return; complete file and
in-memory bytes must match the earned-score insertion with preserved name tails.
A fresh process reads the same persisted table and exits zero. Initial complete
original/VC4/MinGW controls earned 222 points and selected row0; trajectories are
not claimed synchronized, and expectations remain per-run.

The original two-color high-score screen was incorrectly rejected by a generic
four-color capture heuristic. Its retained screenshot has visible content;
only those game-over captures now permit two colors. State/file checks remain
independent and no pixel-fidelity claim is added. An earlier pre-window original
launch exited without a diagnostic and remains an incomplete attempt. No owner
source/header or semantic/exact input changed. Final checks rebuild the strict
SDK observer and recheck all affected Windows harnesses as one serial batch.
Reuse unchanged original-function/cold acceptance only after its identity audit.
The final six serial checks pass: public native/tracking, strict MinGW build,
baseline Windows controls, play/editor, natural game-over and target tracking.
Original/VC4/MinGW final game-over runs retain 180/178/169 state observations;
each earned 222 points and persisted the same complete table. Reports, complete
score/bank files, initial attempts, SDK observer product and the 67-input/eight-
build reuse audit are retained at
`.analysis/checkpoints/windows-gameover-214-40/`. Cleanup again removes only
resettable probe fixtures after retaining the evidence.

Next: focus/surface recovery, complete level progression, embedded resources
and physical audio/asynchronous MIDI. Full reconstruction remains active.
