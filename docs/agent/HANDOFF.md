# Current reconstruction handoff

Continue toward nearly complete source restoration and a rebuildable, playable
game. The README explains the public workflow; operational instructions are in
[AGENTS.md](../../AGENTS.md) and [WORKFLOW.md](WORKFLOW.md).

## Current source checkpoint

- 283 source-present functions; 118 complete exact functions / 18,229 code bytes.
- Latest family: [projectile/fire lists](../research/exact/EXACT_PROJECTILE_LISTS.md).
  Eight whole helpers were restored; the two append bodies add 292 exact bytes.
  The other helpers and projectile controller retain full candidate comparisons.
- The existing Windows VC4 and MinGW builds have recorded playable campaigns.
  Follow [the architecture](../ARCHITECTURE.md) for connected game flows.

## Next source family

Continue the rendering path: `draw_reduced_sprite` (0x4085D0),
`restore_effect_region` (0x408A50), `restore_regions` (0x408CC0),
`draw_bonuses` (0x414740), and `draw_particles` (0x414CB0).
The five original spans total 1,876 bytes. Consult the existing REA dossiers and
[display](../research/DISPLAY_OWNER.md)/[entity](../research/ENTITIES_OWNER.md) notes.

Use only affected exact comparisons and a focused existing Oracle when it
answers a concrete question. Seven redundant test/check scripts and the broad
default CI queue have been removed; keep iteration focused on source recovery.

## Local evidence

The completed source acceptance epoch is sealed in
`.analysis/checkpoints/exact-projectile-lists-283-118/`. It retains the previous
checkpoint, full compiler products, Oracle results and the allocator-header
input correction. Later documentation and pruning changes are separate receipts.
The cumulative REA snapshot contains 478 Evidence records.

The canonical native library SHA-256 is
`0c0cb3728a00d50adb5a8d938419fe37f58ca21e637e79e353e945951c9ac92e`.
Raw investigation files remain under `.analysis/exact-projectile-lists/`.
The user's REA development checkout is `/home/pentester/Project/rea/`;
this game continues to use its pinned analysis toolchain.
