# Screen-point coordinate stages and signed tile reads

Historical checkpoint: the remaining coordinate homes are now recovered by
the [position record](EXACT_SCREEN_POSITION.md); all 337 bytes are exact.
The comparisons below describe the earlier scalar-local stage.

`dxball_hit_screen_point` at `0x4116C0` now preserves the original coordinate
copies, ordered in-place arithmetic and signed tile reads in `src/core.c`.
The complete candidate improves from 325 / 337 bytes with 302 strict differences
to 337 / 337 bytes with 26. All 90 instruction boundaries and widths, thirteen
branches, two calls and ten relocation fields correspond. Only the two scalar
stack homes differ; this remains a candidate, with no exact promotion.

## Source recovered from instructions

The retained REA dossier begins by copying the input X and Y into local words.
It checks the copied Y with inclusive limits 50 and 349, subtracts 20 from the
X copy and 50 from the Y copy, then divides those already-written words by 30
and 15 respectively. The earlier source combined subtraction and division
and tested the input Y directly. These expressions agree in the existing
bounded fixtures but omit actual original stores and their order.

Both board reads use `MOVSX` from one byte: the nonzero test at `0x411760` and
the fireball's tile-two test at `0x41178B`. Explicit `signed char` conversions
recover these reads while retaining the shared byte storage. Clamping, tile
mutation, fire-effect coordinates, board-hit arguments, scoring and exits keep
their established contracts.

The original frame is eight bytes: column at EBP-4 and row at EBP-8. Current
VC4 emission uses column at EBP-8 and row at EBP-4. Applying only that observed
bijection to the 26 actual displacement bytes makes all 337 relocated bytes
identical to the original, including every branch, call and return. Whole
original boundaries come from REA; the original is not re-disassembled through
another decoder. All ten actual COFF relocations agree with their original raw
operand fields. Original declaration spelling and storage selection remain
unproved. No names, capacities, padding or coextensive scope variants are tried.

## Actual verification

Two canonical VC4 MT source compilations occur. The coordinate-only stage is
339 bytes with 189 differences and retains the two unsigned byte-read lowering
sequences. Its source, object and receipts are preserved. The second compilation
adds the two instruction-grounded signed conversions and produces the final
337-byte candidate. Both stages preserve all eight exact core companions across
4,322 bytes; existing frame/drop-bricks candidate comparisons stay unchanged.
The completed products are consumed without recompiling for consumer repairs.

The existing core oracle's single coordinate loop runs once: 1,152 original/native
comparisons cover coordinate clamps, Y boundaries, six tile values, fireballs
and hard-tile modes. Return values, complete board and owner/list state, and
ordered calls agree. No new test or full historical replay is added.
Native and MinGW products rebuild once; the final matching core object links
with 35 unchanged verified VC4 objects and zero additional legacy source
compilations. All 206 exact input closures and 36 game-object identities verify.
The 247 historical semantic scopes retain their counts and contracts; 235 input
inventories refresh without rerunning those historical cases.

Source-present 283, authored 270, exact 206 / 44,406 code / 136 metadata and
origins 115 runtime / 42 generated / 101 unknown remain unchanged. The fresh
Wine follow-up in [INTRO_REQUEST_PLAY.md](../INTRO_REQUEST_PLAY.md) covers the
preceding executable, not this new link. Physical graphics/audio, complete
campaign fidelity, unique original source spelling and full authored denominator
remain open.

## Evidence and preservation

Reuse the closed REA dossier
`ev_a3dbe09d41da07ce2638ea83d054f31af646f507b1cedf2495bd03630db46f7b`,
run `2026-10-07T08-21-37.400Z-interactive-2545594`, operation 00. Its full
337-byte body ends at `0x411810`; the carrier and original SHA-256 are bound
in the private receipt. No new REA session or original byte request occurs.

The preparation initially lacks a callee name in the prior relocation map;
its actual original call field supplies the independently checked target.
A proof-receipt assertion initially selects the wrong two assembly ordinals.
Selecting the observed instruction addresses repairs the receipt and repeats
only its complete-byte check, with no compilation, case-loop or provider repeat.
The strict candidate result and source do not change during either repair.

Private evidence: `.analysis/screen-point-stages/`. Immutable checkpoint:
`.analysis/checkpoints/screen-point-stages-283-206/sha256.json`. Preserve the
coordinate-only intermediate and before inputs. Deduplicate only hash-equal
immutable copies against the immediately preceding play seal; keep current
and public files on independent inodes. Optional REA feedback continues only
in the existing `/tmp/dxball_rea_feedback_20261010.md` document.
