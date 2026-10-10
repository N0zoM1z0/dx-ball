# Current reconstruction handoff

Continue toward nearly complete source restoration and a rebuildable, playable
game. The README explains the public workflow; operational instructions are in
[AGENTS.md](../../AGENTS.md) and [WORKFLOW.md](WORKFLOW.md).

## Current source checkpoint

- 283 source-present functions; 123 complete exact functions / 19,704 code bytes.
- Latest family: [dirty-region presentation](../research/exact/EXACT_PRESENTATION.md).
  Four complete matches gained, three previous matches returned to candidates;
  net gain 664 code bytes. Complete presentation/sort candidates have 51/29 differences.
- The current Windows VC4 game is linked. Earlier VC4 and MinGW builds have
  recorded playable campaigns; this family ran the affected display/entity Oracles.
  Follow [the architecture](../ARCHITECTURE.md) for connected game flows.

## Next source family

Continue the frame boundary and lightning controller: `reset_regions` (0x408070),
`present` (0x409040), `wait_frames` (0x409610), and `last_brick` (0x415F40).
The four original spans total 1,674 bytes. Reuse the saved REA dossiers and
[display note](../research/DISPLAY_OWNER.md).

Use only affected exact comparisons and a focused existing Oracle when it
answers a concrete question. Seven redundant test/check scripts and the broad
default CI queue have been removed; keep iteration focused on source recovery.

## Local evidence

The completed source acceptance epoch is sealed in
`.analysis/checkpoints/exact-presentation-283-123/`. It retains full inputs,
compiler products, the two affected Oracle results and the independent review.
Its parent is `exact-render-restoration-283-122`; publication receipts are separate.
The cumulative REA snapshot contains 478 Evidence records.

The canonical native library SHA-256 is
`838e9363bc798e619264653f58cbb95229cd040940a226c93c1a68f685880771`.
Raw investigation files remain under `.analysis/exact-presentation/`.
The user's REA development checkout is `/home/pentester/Project/rea/`;
this game continues to use its pinned analysis toolchain.
