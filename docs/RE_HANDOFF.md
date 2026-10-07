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
presentation, round reset, UI, audio, and MIDI remain pending. Main ball motion
and full frame routing now have scoped maintained implementations.

VC4.0 compiler 10.00.5270 and linker 3.00.5270 are pinned and executable.
Forty configured units cold-replay exactly, totaling 4,079 bytes; accepted
records are in `config/matches.csv`. Eighty-five source functions have scoped
semantic evidence from 65,894 differential cases. Eight oracle rejection checks
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

The current core checkpoint adds nine functions and 4,580 direct cases, including
200 continuous frames as a subset. Main ball updater 0x410770 (3,223 bytes) and
full gameplay frame 0x40F8B0 (1,683 owned / 1,688 span) are maintained alongside
point hits, retirement, drops, fire effects and shooting. See `docs/CORE_OWNER.md`
for every Evidence ID, typed queue, original collision/input order and scope.
The twelve frame callbacks remain explicit pending implementations; both main
bodies execute in the oracle. Global 0x43A884 is now correctly named displayed_score.
No new exact claims were made while prioritizing core behavior.

Continue with the runtime spine: retained paddle renderer 0x412EC0,
restart transition 0x415DF0 and round initialization 0x415C40, then frame caller
0x403730 and game initialization 0x40E570 as required. Restore connected core
behavior before independent leaf matching. Reuse complete dossiers under
`.analysis/rea/runs/2026-10-07T08-21-37.400Z-interactive-2545594/`;
main ball evidence remains in the earlier 07-42 interactive run. The successful
session saved 113 Evidence records; six records from the previous failed
transport run remain separately archived. Feedback goes to the requested
`/tmp/dxball_rea_feedback.md`. See `docs/REA.md` for interactive reuse and the
32-MiB client cap. New feedback covers large dossier projection and floating
expressions omitted by pseudocode.

This checkpoint performs one grouped cold replay of all 40 accepted units,
all earlier differential suites plus the core oracle, exact rejection tests,
REA verification, three toolchain builds and Wine inspector comparisons.
Private reports and exact objects are retained under
`.analysis/checkpoints/core-85-40/`. Reuse unchanged reports before the next
connected batch; no per-function cold replay is needed.

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
