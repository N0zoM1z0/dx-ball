# Complete lightning crop chains and retained countdown

The later [direct WinMM import](EXACT_WINMM_CLOCK_IMPORT.md) makes waiting fully
exact across 170 bytes. Its actual import closure preserves the explicit
last-brick time sample; the historical diagnostics below retain their scopes.

The last-brick candidate does not omit a direct right/bottom crop subtraction.
Its original arithmetic also contains inverse/negation steps that an unequal
instruction summary hides. The current source and object are retained unchanged;
a two-expression direct-subtraction diagnostic is rejected and reverted.

## Read the shared instructions as well as the differences

For each cropped dimension, the original starts with `XOR EAX,EAX`, forms
`extent + coordinate - limit` in ECX, then performs `SUB EAX,ECX`, `NEG EAX`
and subtracts EAX from the rectangle field. Limits remain 639 and 479.

The current producer forms `limit - (extent + coordinate)` and negates ECX.
It then uses the same shared zero/subtract/negate sequence before updating
the field. Both complete chains subtract `extent + coordinate - limit`,
modulo 2^32. The common final SUB/NEG has equal inputs and flags. No new
clamping, extent cache or coordinate conversion is required.

An unequal-group summary displays the original nine-instruction producer and
the current eleven-instruction producer, excluding shared instructions before
and after them. That is insufficient to infer missing source. The retained
proof checks both complete neighborhoods, their real bank/record addresses,
coordinate homes and consumers. Original/current EBX/EDX scratch residue outside
these chains is not silently treated as equal.

## Complete candidate audit

The complete spans are 1,057 original and 1,067 current bytes, containing
297/302 instructions. All 51 actual relocations are applied. The instruction
comparison checks four explicit producer groups and maps every other operand,
16 bijective frame homes, 25 branch destinations and 22 calls.

Two groups preserve the consumed initial time across RNG using original
callee-saved EBX versus a nonescaping current frame slot. The slot has exactly
one store and one load. Time still precedes RNG(20000), followed by the 40,000
addition and independent second time sample. The other two groups are the crop
chains above. The frame remains 64/68 bytes and 992 strict byte differences;
no stack-home, declaration, name or padding trial follows.

This is complete instruction/operand/CFG correspondence with explicit producer
checks and ABI limits. It is not a proof that arbitrary scratch residue agrees
through every possible external implementation, nor an exact byte or original
source-spelling claim.

## Rejected diagnostic and current behavior

One matching `/MT` display compilation changes only the two crop expressions
to direct excess subtraction. Its complete result is 1,061/1,057 bytes with
993 strict differences. The nine affected accepted units remain exact;
all eleven display candidates receive full private comparisons, with actual
candidate relocation offsets adapted only in the private descriptors.

The direct-expression change is an unsupported simplification. Both source and
the current matching/production object are restored from their verified saved
identities. No compiler, Native/MinGW build or VC4 link repeats to restore them.
The diagnostic source, object, 20 actual project inputs and comparisons remain
retained independently; production manifests and acceptance receipts stay fixed.

The final restored current Native product passes these unchanged existing cases:

- 35 deadline/time pairs, including wrap, inclusive expiry and volume rounding.
- 162 expiry/crop cases over the existing grid positions, graphics settings
  and sprite dimensions.
- 162 corresponding overlay calls, preserving queue dimensions and frame count.

The existing constructors, selected case bodies, complete state/buffer checks
and ordered effects are unchanged. These 197 last-brick cases are a selection
of the existing 198-case scope; the separate multi-tile case is not rerun and
is not claimed as fresh. The 162 overlay checks are a separate entry's scope,
not extra last-brick acceptances. Final selection takes 3.393 seconds and
reuses the verified native fixture. The rejected diagnostic is not executed.

## Evidence and remaining limits

Closed original REA Evidence:
`ev_f8610be2baa2323aec8fcd14317794aebe74eefa78b4d66c9cf874ca117eb5bc`.
Its body is contiguous through RET at `0x00416360`; the target SHA-256 is
verified. The full carrier is 2,316,097 retained bytes, while the complete
297-line assembly facet compactly serializes to 9,495 bytes. These are historical
artifact sizes, not current REA transport, context tokens or provider latency.

Private `.analysis/lightning-crop-subtraction/` retains the full current proof,
before-state, rejected diagnostic and final unchanged selected-case receipts.
Immutable seal:
`.analysis/checkpoints/lightning-crop-chain-283-186/sha256.json`.
Performance and usability feedback remains in the one existing `/tmp` document.

Source-present 283, scoped semantic 247, game exact 186 / 33,001 code bytes /
136 metadata bytes and origins 270/83/42/133 stay fixed. All 36 current game
object/input identities and four products retain the preceding `df23eea` state.
No new REA provider, whole owner replay or physical game/audio observation
occurs. Reuse the complete chain when choosing future source work; the shorter
direct-expression diagnostic is not original-source recovery.
