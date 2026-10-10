# Current reconstruction handoff

Continue toward nearly complete source restoration and a rebuildable, playable
game. The README explains the public workflow; operational instructions are in
[AGENTS.md](../../AGENTS.md) and [WORKFLOW.md](WORKFLOW.md).

## Current source checkpoint

- 283 source-present functions; 124 complete exact functions / 19,413 code bytes.
- Latest family: [frame boundary and lightning](../research/exact/EXACT_FRAME_BOUNDARY.md).
  Reset and presentation are exact; effect-sprite drawing regained exactness.
  Queue-sprite-region and dirty-region restoration returned to candidates.
  Wait/lightning complete candidates retain 64/337 differences.
- The current Windows VC4 game is linked. Earlier VC4 and MinGW builds have
  recorded playable campaigns; this family ran one affected display Oracle.
  Follow [the architecture](../ARCHITECTURE.md) for connected game flows.

## Next source family

Continue the sound voice lifecycle: `play_sound` (0x405C50), `update_sound`
(0x405D80), `stop_sound` (0x405EF0), the frequency/pan/volume setters
(0x405FA0/0x406040/0x4060E0), and `restore_sounds` (0x406180).
These connected bodies total 1,454 original bytes. Reuse the saved REA dossiers
and [sound note](../research/SOUND_OWNER.md).

Use only affected exact comparisons and a focused existing Oracle when it
answers a concrete question. Seven redundant test/check scripts and the broad
default CI queue have been removed; keep iteration focused on source recovery.

## Local evidence

The completed source acceptance epoch is sealed in
`.analysis/checkpoints/exact-frame-boundary-283-124/`. It retains full inputs,
compiler products, the affected Oracle result and the independent reviews.
Its parent is `exact-presentation-283-123`; publication receipts are separate.
The cumulative REA snapshot contains 478 Evidence records.

The canonical native library SHA-256 is
`5dd78763f2b3123769c1bb9f722f2a09628801238c4a652c9bac2f542c865b7c`.
Raw investigation files remain under `.analysis/exact-frame-boundary/`.
The user's REA development checkout is `/home/pentester/Project/rea/`;
this game continues to use its pinned analysis toolchain.
