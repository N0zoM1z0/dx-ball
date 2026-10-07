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
ball physics, bonuses, UI, audio, and MIDI remain pending.

VC4.0 compiler 10.00.5270 and linker 3.00.5270 are pinned and executable.
Twenty-four configured units cold-replay exactly, totaling 2,311 bytes; accepted
records are in `config/matches.csv`. Forty-one source functions have scoped
semantic evidence from 38,037 differential cases. Eight oracle rejection checks
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
the whole frame updater. Continue with bonus production at `0x4138D0`, particle
production/updates at `0x4148A0` / `0x414A00`, and ball/paddle physics.
Ball/projectile
consumers are observed through REA but not implemented. The hard-tile flag's
full bonus producer and sound backends remain pending. Feedback goes to the
user-requested `/tmp/dxball_rea_feedback.md`; it distinguishes provider issues
from project-client issues. REA sessions now archive each run and save successful
Evidence prefixes even when a later query fails.

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
