# Reconstruction progress

Recover the original game source into a rebuildable, playable game.
The current records cover gameplay, all five screen modes, resources, graphics and audio.

| Fact | Count |
| --- | ---: |
| Provisional function candidates | 553 |
| Parent-owned compiler fragments, counted separately | 24 |
| Source-present functions | 475 |
| Functions with scoped semantic acceptance | 249 |
| Byte-exact functions | 392 |
| Complete exact code bytes | 83837 |
| Entries identified as runtime dependencies | 261 |
| Entries identified as compiler-generated code | 21 |
| Origin still unclassified | 1 |

The inventory includes game routines, runtime dependencies and compiler-generated code.
Earlier Windows builds have recorded original-board play under Wine.
See the [current VC4 build and play check](research/CURRENT_VC4_BUILD.md) for its image and limits.

See [the architecture](ARCHITECTURE.md), [compiler matching](MATCHING.md),
and [recorded play runs](research/ORIGINAL_CAMPAIGN.md).

Generated from the ledgers by `scripts/repo-python scripts/progress.py`.
