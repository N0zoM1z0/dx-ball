# Exact reconstruction follow-up

Updated October 22, 2026. All 270 authored functions and 84,968 authored code
bytes are exact across 53 compiler closures. The current work is summarized in
[progress](../../PROGRESS.md) and the [handoff](../../agent/HANDOFF.md).

## Authored candidates

The authored candidate list is closed. The final accepted owners include:

| Family | Recovery record |
| --- | --- |
| PCX decoder and closing audit | [PCX file prefix](PCX_FILE_PREFIX_RECOVERY.md) |
| Last-brick controller | [Last-brick source owner](LAST_BRICK_EXACT_SOURCE_OWNER.md) |
| Rotated sprite rendering | [Typed row/cursor](ROTATION_TYPED_CURSOR_RECOVERY.md) |
| Triangle controller | [Conditional temporaries](TRIANGLE_CONDITIONAL_TEMPORARIES.md) |
| Paddle rendering | [Paddle source owner](PADDLE_RENDERER_SOURCE_OWNER.md) |

[The exact index](README.md) links the other completed families.

## Runtime candidates

The full inventory has 60 source-present nonexact runtime routines. Another
77 runtime routines and one compiler helper lack source ledger entries. The
current game links its reconstructed CRT owners with 19 original CRT members.

Use [CRT provenance](../CRT_PROVENANCE.md),
[the runtime interface investigation](VC4_RUNTIME_INTERFACE_OWNERSHIP.md) and
`config/match-units.toml` when pursuing a runtime comparison. The
[source-candidate policy](../../agent/SOURCE_CANDIDATE_SEARCH.md) describes the
accepted experimental method.

## Allocator comparison gaps closed

The eight allocator comparisons are exact. Their implementation and validation
are described in [allocator ownership](../ALLOCATOR_OWNER.md).

## Evidence and closed controls

The [October21 backlog and experiment log](https://github.com/N0zoM1z0/dx-ball/blob/9752a6954ec1bea5da2885ba236ca51a5c8976a0/docs/research/exact/REMAINING_EXACT_FUNCTIONS.md)
retains the earlier candidate counts, failed hypotheses and full receipts.
Current comparisons are recorded in `config/matches.csv` and
`config/match-units.toml`.
