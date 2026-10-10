# Current reconstruction handoff

Continue toward nearly complete source restoration and a rebuildable, playable
game. The README explains the public workflow; operational instructions are in
[AGENTS.md](../../AGENTS.md) and [WORKFLOW.md](WORKFLOW.md).

## Current source checkpoint

- 283 source-present functions; 122 complete exact functions / 19,040 code bytes.
- Latest family: [region restoration and drawing](../research/exact/EXACT_RENDER_RESTORATION.md).
  Five complete matches gained, one previous match returned to a candidate;
  net gain 811 code bytes. Dirty restoration and particles retain full comparisons.
- The current Windows VC4 game is linked. Earlier VC4 and MinGW builds have
  recorded playable campaigns; this family ran the affected display/entity Oracles.
  Follow [the architecture](../ARCHITECTURE.md) for connected game flows.

## Next source family

Continue dirty-region presentation: `queue_region` (0x408990),
`present_regions_now` (0x409100), and `sort_present_regions` (0x4094E0).
The three original spans total 1,463 bytes. Consult the saved REA dossiers and
the [display note](../research/DISPLAY_OWNER.md).

Use only affected exact comparisons and a focused existing Oracle when it
answers a concrete question. Seven redundant test/check scripts and the broad
default CI queue have been removed; keep iteration focused on source recovery.

## Local evidence

The completed source acceptance epoch is sealed in
`.analysis/checkpoints/exact-render-restoration-283-122/`. It retains full inputs,
compiler products, the two affected Oracle results and the independent review.
Its parent is `exact-projectile-lists-283-118`; publication receipts are separate.
The cumulative REA snapshot contains 478 Evidence records.

The canonical native library SHA-256 is
`0150484c917a5b374acdc5711de0ccee4dd7862b04d1ece5895bea0675a0b672`.
Raw investigation files remain under `.analysis/exact-render-restoration/`.
The user's REA development checkout is `/home/pentester/Project/rea/`;
this game continues to use its pinned analysis toolchain.
