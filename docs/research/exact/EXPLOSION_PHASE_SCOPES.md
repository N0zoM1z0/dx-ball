# Explosion animation phase lifetimes

The later [record-copy check](RECORD_COPY_BOUNDARIES.md) restores cleanup homes
but changes rectangle-by-value code generation and is rejected. This canonical
797-byte candidate and its13 home differences remain unchanged.

The complete explosion step at `0x412730..0x412A4C` now places its board
coordinates in the frame-five branch and its rectangle/occupancy coordinates
in the expiration branch. One canonical MT compile improves the full 797-byte
comparison from 47 differences to 13. The body remains nonexact. Current totals
stay 203 exact functions / 42,656 code bytes / 136 metadata bytes.

## Source evidence

REA Evidence
`ev_b10ee96258ecd655c8f9258fc4ae6cb2c52939077283dc0409f9f912688f79b3`
retains the complete contiguous 797-byte body, including the return. Its private
carrier is `09-analyze_function.json` in closed run
`2026-10-07T06-16-05.200Z-rea-effects-family-2065454`; target SHA-256 is
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
No new provider session or capture is needed.

The original only computes and consumes its first board x/y while five frames
remain. Neither value crosses into expiration or the ordinary draw branch.
The expiration rectangle is initialized from current-node screen coordinates,
consumed by BltFast and restored by value before occupancy coordinates reload
the live current node. Those coordinates clear occupancy before node removal;
neither is consumed in the other branch. The maintained source scopes these
two operations accordingly. Existing local names, widths, declarations and all
executable tokens remain unchanged; no padding, fake locals, capacities or
name/declaration permutations are introduced.

All 251 original instruction boundaries and widths, 18 branches and 14 calls
correspond after applying the unchanged 49 explicit relocation bindings.
The proof parses original REA assembly and decodes only our emitted COFF.
Every one of the 13 full comparison differences is inside an actual EBP
displacement field. Operations, registers, immediates, call/branch targets and
32-byte frame allocation agree through the recorded frame-role mapping.
This structural correspondence is not byte-exact acceptance.

## Remaining cleanup homes

| Role | Original EBP | Before EBP | Current EBP |
| --- | ---: | ---: | ---: |
| Frame-five x | -4 | -28 | -4 |
| Frame-five y | -8 | -32 | -8 |
| Expiration rectangle base | -28 | -16 | -24 |
| Occupancy x | -32 | -20 | -28 |
| Occupancy y | -12 | -24 | -32 |
| Reserved frame bytes | 32 | 32 | 32 |

The rectangle and occupancy-coordinate homes still differ. Available evidence
does not establish their unique source declaration spelling or compiler
temporary provenance. Do not split coextensive cleanup lifetimes or change
names/declaration order merely to force those homes. Address-taking and by-value
rectangle calls remain explicitly checked and part of the nonexact comparison.

## Checks and preserved products

Four exact companions remain unchanged across 841 complete bytes: explosion
creation, animation traversal, brick creation and brick stepping. All 49
candidate relocation offsets/symbols/types/addends/targets remain unchanged.
The before object remains a negative control with 47 full differences.

Two selected existing Oracle loops pass 9720 animation steps (4860 explosion,
4860 brick) plus 288 mixed-queue process calls through completion. The unchanged
matrices include timer/frame boundaries, six signed tile values, three reduced
settings and five edge/interior positions. Full tiles, occupancy, queues, state,
released-storage ownership, ordered events and RNG consumption compare with
the original. No maintained test/case/assertion changes or unrelated suite
replays occur; physical rendering/audio remain unproved.

Native and MinGW rebuild once. VC4 links the matching MT effects object with 35
hash-verified unchanged objects, without additional legacy source compilation.
All 203 exact input closures, 36 production objects and 247 unchanged historical
semantic scopes verify. The 235 changed historical input inventories refresh
without asserting new execution for those scopes.

Working proof, before products, compiler receipt and selected Oracle are in
`.analysis/explosion-phase-scopes/`. Independent preservation is
`.analysis/checkpoints/explosion-phase-scopes-283-203/sha256.json`, with explicit
before-product and closed REA dependencies. The full reconstruction goal stays
active: authored denominator, original source spelling, full campaign and
physical render/audio fidelity remain unproved.
