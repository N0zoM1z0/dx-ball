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

Portable builds are analysis libraries and a board-inspection utility. There is
no reconstructed playable game yet. Windows integration,
device/driver integration, glyph UI, audio, and MIDI remain pending. Main ball motion,
full frame routing/drawing, game initialization and life-loss reset now have
scoped maintained implementations. All twelve frame phases default to source.

VC4.0 compiler 10.00.5270 and linker 3.00.5270 are pinned and executable.
Forty configured units cold-replay exactly, totaling 4,079 bytes; accepted
records are in `config/matches.csv`. One hundred thirty-four source functions have scoped
semantic evidence from 75,670 differential cases. Eight oracle rejection checks
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
Current pan literal names are `$T617` / `$T618`, with both contents attested.

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
platform implementations. Continue through actual Windows binding, working
resource setup at 0x403A00, mode-0 intro, mode-3 game-over/UI and audio. Retained
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

The current platform checkpoint adds eleven entries and 4,742 direct cases
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
