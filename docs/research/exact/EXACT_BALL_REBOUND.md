# Ball ownership and paddle rebound

The shared `src/balls.c` now calls the genuine runtime operator-new/delete and
direct sound functions. Paddle rebound preserves the original independent live
angle check and current sprite-bank/height reads after its audio calls. This
restores state flow across controlled callbacks without changing the historical
ordinary-input acceptance scope.

## Retained evidence and source recovery

The pinned original rebound is `0x411410..0x4116B8`, all 681 contiguous bytes.
Evidence `ev_6055fe1d318fa3f71d76b5cdbbbe862a3944dd9890035a53264b8ccfa2d7a074`
shows two separate extreme branches with stop/pan/play calls. The independent
check at `0x4115F8` reloads the live angle and requires `30 < angle < 150` before
reading the live bank/sprite height. Cached metadata and an else-only height
adjustment cannot express that state flow when a callback changes it.

At `0x411421..0x411435`, integer paddle-x enters x87 before the half-width
subtraction and float store. The first ratio threshold uses the retained x87
value; later thresholds load the stored float. Source retains these distinct
precision stages using ordinary arithmetic and typed locals. VC4's emitted
frame/precision spelling remains unresolved; no declaration/name/layout search,
assembly replacement or copied original instruction bytes was used.

Append `0x4106D0..0x410761` calls operator-new at `0x416770` and fatal exit at
`0x417910`; Evidence
`ev_ec03d81a1de8e23be7f38b75a66795e8b67db909881265d0ac39f9c371ab480e`.
Removal calls operator-delete `0x416760`; Evidence
`ev_ad944e908a2b23a9361befd1410ae97034be779d87b3b006536ec2d702031394`.
The removal comparison covers the complete enclosing 220-byte span through
`0x41192B`, including the previously reviewed five-byte internal jump outside
Ghidra's 215 owned bytes. No gap is excluded from matching.

## Matching and runtime scope

One pinned VC4 compile uses `/Od /Ob0 /Oi- /Oy- /Gd /MT /Gy`. The actual recursive
project closure contains 18 files, fully covered by 28 declared inputs, including
`allocator.h`. All seven accepted ball units remain exact: append 146, begin 57,
advance 89, clear 48, release 84, spawn 244 and clone 637 bytes. The append relocation
now names the actual shared operator-new implementation at the same reviewed
ABI and target. Generated float labels are refreshed only with identical
offset/type/addend and fully attested contents.

| Complete candidate | Object / original bytes | Differences | Relocations |
| --- | ---: | ---: | ---: |
| Remove ball | 208 / 220 | 52 | 1 |
| Paddle rebound | 687 / 681 | 550 | 50 |

Every actual relocation and eight complete eight-byte threshold/scale constants
are bound to the pinned original instructions/data. Candidates remain nonexact.
Global totals remain 171 exact functions / 30,744 code bytes / 136 metadata bytes,
283 source-present entries and 247 historical scoped semantic rows.

The final native library and actual relocated VC4 object each pass the same
1,085 selected maintained cases with unchanged assertions: trig initialization 1,
append57, begin 56, advance 56, remove 56, clear 28, spawn 37, clone 40, release 40 and
rebound 714. They compare returns, ordered calls, globals, payloads, roots,
allocation ownership and poisoned freed storage. Original code bytes remain
unchanged. Native fixtures use verified copied images and existing ownership
checked interposition; production native Windows-independent transports are
not replaced in the canonical library.

Four additional controlled audio cases change angle to 75, sprite to 2 and bank
to 2 during stop or play, at each extreme. Original and both new products set y
to 423 using the current height 27. The retained old native product leaves y 449
in all four expected negative controls. These cases are separate from the
historical semantic ledger counts. This does not establish physical/asynchronous
audio behavior, full-owner coverage or a new Wine game-use observation.

Native/MinGW builds pass. The VC4 game link reuses this matching object and 34
verified unchanged objects, with zero additional production source compiles.
Resource and SDK import products are verified and reused. Prior Wine play
records retain their historical executable identities.

Private reproducible receipts and helpers: `.analysis/exact-ball-rebound/`.
Immutable seal: `.analysis/checkpoints/ball-rebound-283-171/sha256.json`.
REA was not reopened; three retained archives total 2,067,168 bytes and selected
local projections 16,492 bytes. Feedback entry 25 is appended to the same existing
`/tmp/dxball_rea_feedback_20261010.md`, without a measured token/latency claim.
