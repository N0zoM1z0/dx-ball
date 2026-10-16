# Reconstruction progress

Recover the original game source into a rebuildable, playable game.
The current records cover gameplay, all five screen modes, resources, graphics and audio.

| Fact | Count |
| --- | ---: |
| Provisional function candidates | 520 |
| Parent-owned compiler fragments, counted separately | 24 |
| Source-present functions | 464 |
| Functions with scoped semantic acceptance | 249 |
| Byte-exact functions | 376 |
| Complete exact code bytes | 76908 |
| Entries identified as runtime dependencies | 217 |
| Entries identified as compiler-generated code | 21 |
| Origin still unclassified | 12 |

The inventory includes game routines, runtime dependencies and compiler-generated code.
Both Windows builds have completed recorded original-board campaigns under Wine.
Continue with the remaining rendering and runtime routines.

See [the architecture](ARCHITECTURE.md), [compiler matching](MATCHING.md),
and [recorded play runs](research/ORIGINAL_CAMPAIGN.md).

Generated from the ledgers by `scripts/repo-python scripts/progress.py`.
