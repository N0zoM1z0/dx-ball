# Exact main frame dispatcher

The main frame at `0x403730` now uses the original ten direct calls in
[runtime.c](../../../src/runtime.c). Its first stable VC4 compilation matches
all 228 bytes, including the five-entry mode table and the compiler's trailing
switch jump.

A requested device reset initializes the device and current mode, then clears
`device_reset_requested` before `surface_restore_requested`. Surface
synchronization runs before reading the current mode. The switch calls the
intro, game, editor, game-over or splash frame for modes 0 through 4. Other
values skip the frame and continue to the transition phase.

After the frame, an end request calls `cleanup_mode(1)`, copies the current
`return_to_menu` DWORD into `display_mode`, initializes that mode and finally
clears the end request. The return target is copied directly; it is not reduced
to a Boolean. The function always returns 1 to WinMain.

REA dossier
`ev_fe891f4e2c0b787941b66990f074b6e3ad5575dc3b2080a68641c8f9629b6363`
covers 46 instructions and all ten calls. Full read
`ev_a0a1fa3c462d3100bf6c48ddb0cf18486b3364307d43807e508af764a772c1e0`
accounts for the whole span: 203 instruction bytes, a five-byte jump at
`0x4037A8` and 20 table bytes at `0x4037C1`. The table routes to `0x403776`,
`0x403780`, `0x40378A`, `0x403794` and `0x40379E`. Both saved records were
reused; this source batch opened no provider. The original switch spelling
remains inferred from those instructions and the compiler result.

Six whole comparisons apply 167 actual relocations: 24 in this dispatcher and
143 in finish-game, restart-round, dispose-game, initialize-game and redraw-game.
All five previously exact functions remain exact. The runtime recipe compiled
once, with no source or compiler alternatives. Totals are 140 exact functions,
22,674 code bytes and 136 metadata bytes.

The native fixture forwards the seven newly direct frame/device boundaries
through its existing live ModeOps table. Real owners come from the actual
copied library. Untouched defaults reach those owners; callbacks retain null,
self and reentry guards. Gameplay mode still executes the real game frame.
The shared game API and existing case bodies are unchanged.

Only the two existing frame-dispatch loops ran: 128 cases covering mode bounds,
reset flags, end flags and frame-requested transitions. A private reporting
assertion initially expected 240 after the comparisons had completed; its
correction caused a second invocation of the same loops. Both logs are retained.
Other semantic rows retain their historical case scope after input hashes are
refreshed. Native, VC4 and MinGW builds pass; the VC4 link reuses 35 valid
objects and compiles no additional sources.

Full compiler inputs, original bytes, explicit bindings, comparisons and Oracle
receipts are retained under `.analysis/exact-main-frame/` and
`.analysis/main-frame-byte-review/`. The next connected recovery is mode
initialization, redraw and cleanup, which still use authored callback routing.
