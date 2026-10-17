# Score formatting workspace regions

Two complete game functions now match the pinned original with VC4:

| Function | Original / emitted bytes | Differences before / after |
| --- | ---: | ---: |
| `draw-score`, `0x4158D0` | 433 / 433 | 21 / 0 |
| `redraw-intro`, `0x40E0E0` | 587 / 587 | 560 / 0 |

The shared source uses a 20-byte decimal array in both functions and a 100-byte
text array in menu redraw. These are the existing consumed arrays; no object,
padding field, executable operation or alternate implementation was added.
Names, types, scopes, expressions and call order stay unchanged.

## Inference and complete comparison

The earlier [score-strip correspondence](SCORE_STRIP_SOURCE.md) maps the decimal
address to EBP-40, immediately below the rectangle boundary at EBP-20. The
[intro correspondence](INTRO_SCORE_PHASE.md) independently maps decimal storage
to EBP-140, text storage to EBP-120, and the count boundary to EBP-20. Together
they support a concrete hypothesis: the two unsigned-decimal producers use
20-byte workspaces, with 100 bytes for the concatenated menu text.

Original REA Evidence is
`ev_5bd8ce0bb9a8d5a889e6d06e213d148ea1bd2ad54e5d755b82c7705c50cfff4c`
and
`ev_8d3b245893789331b1a53500a14aae87ed382cd5465098be8604a64b721a1440`.
The target remains English v1.07 SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
Existing full responses are reused; no provider query repeats them.

The previous 11-byte decimal and 32-byte menu arrays were sufficient minimums,
not recovered original declarations. Requiring uniquely proven capacities
before trying the independently supported regions was too restrictive. An
independent read-only review finds no contrary instruction evidence and confirms
that the trial uses real arrays, rather than unused padding.

One compilation per owner compares all 36 affected complete functions. Both
candidates become exact, preserving all 30 prior exact companions and all four
other candidate identities. Score retains all 135 instruction boundaries;
intro retains all 174, restoring its 140-byte frame and two longer LEAs.
Relocation sites follow the same decoded instructions, preserving symbol
identity, type, addend and original target. All literal bytes are checked.
The full relocation-resolved comparisons report zero differences; the local
target guard remains enabled. No displacement masking or operand projection
contributes to acceptance.

Independent read-only acceptance review checks all67 relocation mappings against
both COFF decodings. Score sites stay fixed; intro sites move by3/6/9 bytes with
the identified instruction expansions. No target, addend or literal is changed.

Exact emitted code does **not** uniquely establish the original array
declarations. The capacities remain an inference supported by both storage
regions and the complete compiler result. Defined unsigned32 formatting writes
at most 11 bytes including NUL; menu concatenation needs at most 24. The larger
arrays preserve those strings and their existing consumers.

## Focused validation

The affected native owners rebuild serially. Existing case loops pass 63 score
draws, 63 refresh calls and nine menu redraws: decimal boundaries, life strips,
surface modes, defined state, pixels and ordered calls. Tracked fixtures and
case loops are unchanged. There is no full runtime suite or game campaign.

The restored-CRT delivery relinks with all116 source objects reused and all19
approved members preserved, without another source compilation. Its image SHA-256
is `1fcba8f2f40a2c6e822159475048f26a656d7e954b1b11bd532fd74a61ede9c4`.
Earlier game observations retain their earlier image identities; this checkpoint
does not claim a new physical display or playability observation.

The totals become **382 exact functions / 78,505 code bytes / 244 metadata
bytes**, with **93 complete candidates: 32 authored, 60 runtime and one
generated**. All 270 classified authored entries remain source-present with
complete comparisons: 238 exact and 32 candidates. These counts do not prove
the final authored denominator or whole-game completion.

Private compiler inputs, before products, original correspondence dependencies,
instruction-based relocation reconciliation, complete comparisons, native
checks and adoption receipts are retained in
`.analysis/score-workspace-regions-20261017/`. Compiler and build commands use
one allowed CPU, CPU quota35%, memory high640 MiB/max768 MiB. No full replay.
Verified archives replace28 compiler-input copies and four raw objects,
releasing188 KiB of allocated storage after carrier cost. Current objects,
delivery and unique before evidence remain preserved.
