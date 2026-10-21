# DX-Ball reconstruction handoff

Updated October 21, 2026. The user explicitly resumed all270 authored exact
recoveries after the earlier cleanup/handoff. Keep progressing under the standing
source-search policy, CPU/memory caps, frequent commits/pushes and periodic
member-verified cleanup. The goal is active and incomplete.

## Maintained checkpoint

| Verified fact | Current state |
| --- | ---: |
| Classified authored functions with source |270 /270|
| Authored byte-exact functions |257 /270 (95.19%)|
| Authored complete exact code bytes |73,677 /84,968 (86.71%)|
| Authored nonexact candidates / original bytes |13 /11,291|
| Overall exact functions, including runtime/compiler units |402|
| Exact code / attached metadata bytes |88,061 /244|
| Current authored compiler closures |33|

Private current artifact authority is
`.analysis/timing-cursor-source-search-20261021/frame-wait-followup/current-checkpoint.json`;
its adjacent `adoption.json` records the maintained frame-wait acceptance.
The original256/270 reset checkpoint and stopped waiting proof remain historical
and recoverable. Do not execute their preparation/installation helpers again.

## Completed frame-wait adoption

The retained standalone/remainder pair is installed as shared `src/frame_wait.cpp`
and `src/display.cpp`, with CMake, legacy source/link lists and claim owners
updated coherently. Full20-function comparison preserves19 other identities and
17 prior exacts across419 code bindings, two initializer relocations and the
57-byte portable bridge. Waiting is170/0. Both compiler outputs were reused
without recompiling identical digests; clock source/object stay unchanged.

The maintained native build preserves40 companion objects and all43 existing
compile configurations;18 existing original/native wait cases pass with the
verified fixture cache unchanged and zero fixture preparation. Native build/check
uses CPU0/35%,384/512MiB; peak112,594,944 bytes and no memory events. Draft native
command checking was corrected for display's existing lightning-only warning
exception, with the original baseline/helper retained. See
[the waiting note](../research/exact/FRAME_WAIT_CURSOR.md).

No game relink/play follows the clock/reset/wait source splits. Retained delivery
results apply to their recorded images; see [build status](../research/CURRENT_VC4_BUILD.md).

## Remaining authored candidates

Sizes below are original/current; differences are strict full-span counts.

| Unit | Owner | Bytes | Differences |
| --- | --- | ---: | ---: |
| draw-sprite |resources.cpp|105 /107|94|
| blt-sprite |resources.cpp|195 /199|173|
| fill-triangle |raster.cpp|1710 /1710|48|
| present-regions-now |display.cpp|984 /984|2|
| last-brick |display.cpp|1057 /1047|976|
| draw-high-scores |gameover.c|404 /403|330|
| draw-paddle |runtime.cpp|677 /678|210|
| release-sprite |resources.cpp|262 /269|245|
| draw-glyph |resources.cpp|328 /332|258|
| load-pcx |resources.cpp|862 /979|850|
| fill-polygon |raster.cpp|1543 /1543|216|
| fill-polygon-clipped |raster.cpp|1592 /1592|213|
| render-rotated-sprite |rotation.cpp|1572 /1458|1466|

`config/match-units.toml`, the current exact report and candidate audit are the
comparison authority; `config/function-origins.csv` defines the270 authored set.
Historical249 semantic scopes/cases/order are retained, not newly rerun.

## Continue recovery

Read [AGENTS.md](../../AGENTS.md), [workflow](WORKFLOW.md),
[source-search policy](SOURCE_CANDIDATE_SEARCH.md) and the relevant research note.
The older [handoff history](HANDOFF_HISTORY_20261021.md) and stopped proof remain
historical evidence, not instructions to pause this resumed goal.

```bash
git status --short
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py
```

`replay-exact-units.py` compiles; reuse verified unchanged outputs instead of
running it as a status reader. Select the next finite natural source family
from current residuals and retained results, compare complete affected units
strictly and update source/owner/claim ledgers together for adoption. Unknown
historical names or module organization remain experiment inputs. Do not request
nonexistent original project/PDB/MAP/build records.

Keep one compiler/provider job on CPU0,35% CPU,384MiB high/512MiB max, CMake
parallel1 and the silent audio sink. Preserve current products, useful caches,
originals/tools and the141-record frontend snapshot. Archive unique closed
results and verify member sizes/SHA before removing obsolete copies. Commit and
push verified checkpoints to `origin/main` with the `gpt-6.1-sol: ` prefix.
