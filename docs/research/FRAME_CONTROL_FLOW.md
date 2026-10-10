# Full frame control flow and signed consumers

The maintained `dxball_game_frame` at original `0x40F8B0` now preserves three
instruction-level details: the paused phase returns directly to the epilogue,
the explosion phase reads auxiliary occupancy as a signed byte, and completion
compares remaining bricks with zero before checking both animation queues.
The shared C implementation retains every active phase and its order.

This is a source recovery checkpoint, without a new exact acceptance. The full
candidate is 1,691 compiled bytes against 1,688 original bytes, with 1,156
unmasked byte differences after every actual relocation. Exact totals remain
185 functions /32,688 code bytes plus136 metadata bytes; source presence283
and scoped semantic acceptance247 are unchanged.

## Original evidence and complete comparison

Closed REA Evidence
`ev_5d1d8d47e797530fa172e492b60eebe40dcf8a855a6d9125eb644dccb2e15d43`
records 1,683 owned instruction bytes in the 1,688-byte enclosing span. The
complete comparison includes the five-byte interval outside that ownership;
the provider's body is not silently expanded. All observations bind to original
SHA-256 `756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
No new provider request is needed.

At `0x40F8FC`, the paused branch jumps directly to the epilogue at `0x40FF43`.
The former outer `else` source made it first visit the final jump at the active
phase's end. Returning inside the paused branch and allowing the active body
to follow naturally restores the observed destination. The active body is
textually identical to the first phase after removing the outer indentation.

At `0x40FAC1`, the original uses `MOVSX` for the auxiliary byte at `0x43A918`.
A signed-byte consumer cast reproduces that read while preserving the existing
byte storage and its zero test. At `0x40FE9D`, the original compares remaining
bricks at `0x43A8F4` with zero and skips completion when greater. The source
now expresses `<= 0`; the short-circuit animation begin calls stay in order.

An independent full instruction correspondence applies all actual COFF
relocations and compares 379 original instructions with 379 compiled
instructions. Every internal branch targets the corresponding original
instruction. Three address-loading instructions still differ: original
`MOV ECX, immediate` versus compiled `LEA ECX, [address]` for the explosion
owner. Remaining operand differences are local stack homes and the branch
distances caused by those three extra instruction bytes. This correspondence
explains the nonexact result; it does not mask differences or replace the
complete byte comparison.

The address forms come from `DxBallBoardStorage`, a recovered contiguous
writable region required by the terminal board-copy consumers. It is not an
established original source declaration. Its live peer globals and unresolved
bytes must remain preserved. No separate fake symbol, alias, layout trial,
assembly, padding, copied code or alternative profile is introduced to force
the three address instructions. Unique source declarations and local placement
remain unresolved. Projectile updates retain eight local-displacement
differences and are unchanged in this checkpoint.

## Actual build and runtime phases

There are two core compilations with the pinned flags and unchanged recursive
headers. The first restores the signed load and zero predicate. Its complete
comparison then identifies the paused return destination, prompting the second
source change. Both actual source/object/product epochs are retained. No
declaration, name or layout search is performed.

Six preceding exact core functions pass complete byte, relocation and literal
comparisons in both phases. The other three core candidates retain their
preceding emissions and difference counts. All185 canonical exact receipts
retain current object/input identity. Native and MinGW builds pass. The final
VC4 game link uses one matching core object and35 verified unchanged objects,
without additional source compilation. Actual DirectDraw/DirectSound imports
and native allocator-operator visibility remain checked integration evidence.

The first runtime phase executes the unchanged maintained frame loops:
708 cases, including200 connected frames as a subset. These cover pause,
timer/input handling, deferred powers, rendering mode, count/deadline gates,
animation completion and actual connected physics/entity phases. After the
paused return change, the final library passes the24 existing pause/timer/input
cases. Those receipts retain their distinct actual source and library hashes;
the708-case result is not relabeled as a final-library execution. Active source
preservation and final instruction/branch correspondence justify avoiding a
repeat of the unchanged active-frame cases. No fixture, vector or assertion is
edited, and no full historical suite is run.

Time, rendering, score, last-brick and restart dependencies retain their
configured boundaries. These checks do not establish physical driver behavior,
a new live-game result, complete campaigns or the full original authored
denominator. Existing semantic cases and scopes are unchanged when input
identities are refreshed.

Private proof: `.analysis/frame-signed-consumers/`; immutable seal:
`.analysis/checkpoints/frame-control-flow-283-185/sha256.json`.
The complete source and whole-game fidelity goal remains open.
