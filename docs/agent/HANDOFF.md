# DX-Ball reconstruction handoff

Updated October 21, 2026. The user stopped and cleared the reconstruction goal,
then requested cleanup and handoff. Reconstruction is incomplete; do not resume
experiments, compile, publish pending matches or run the unfinished helpers
without a new request. The standing source-search authorization remains
available if reconstruction is explicitly resumed.

## Maintained checkpoint

| Verified fact | Current state |
| --- | ---: |
| Classified authored functions with source |270 /270|
| Authored byte-exact functions |256|
| Authored nonexact candidates |14|
| Overall exact functions, including runtime/compiler units |401|
| Exact code / attached metadata bytes |87,891 /244|
| Current authored compiler closures |32|

The maintained source/object checkpoint is `6e937a3` (direct-owner reset TU);
`624b251` adds the closed presentation/paddle probe results without changing
those artifacts. Private authority is
`.analysis/reset-tu-source-search-20261021/current-checkpoint.json`.
Its declared artifact hashes were rechecked unchanged at handoff.
No new game relink or play run follows the clock/reset source splits. Retained
delivery/runtime results apply to their recorded image identities, not an
unverified newly linked game; see [build status](../research/CURRENT_VC4_BUILD.md).

## Unadopted frame-wait recovery: preserve, do not count

The last interrupted work has a complete new exact candidate, but **is not an
adopted257/270 checkpoint**. Canonical `wait-frames` remains170 bytes /6 differences
in `src/display.cpp`; `src/frame_wait.cpp` is not installed.

Private root: `.analysis/timing-cursor-source-search-20261021/`.
The handoff index and member-verified recovery archive retain its relative paths.

- Six timing-cohort probes compare three functions/18 bindings each. Full-prefix
  wait-before/after models make waiting170/0 but lose elapsed81/3; reject those
  whole objects. The existing canonical clock source/object remain unchanged.
- One current-C++ cursor retest compares the full display owner: presenter984/12,
  sort296/3 lost. Reject it; the older C cursor984/14 is a separate historical input.
- `frame-wait-followup/standalone/` emits the unchanged waiting body alone with
  the inherited full display prelude:20 project inputs, nine unchanged flags,
  one compile,170/0.
- The matching `frame-wait-followup/remainder/` compiles once. The full20-function
  split checks419 code bindings, two initializer relocations and the57-byte
  portable bridge. All19 other resolved identities and17 prior exacts survive.
- Comparison, mapping and raw COFF proofs are complete. No rollback preparation,
  canonical source/object installation, maintained native build,18-case replay,
  ledger promotion or delivery build occurred. `native-check.py` and `publish.py`
  are syntax-checked drafts, not executed validations or approved auto-resume jobs.

If later asked to resume, restore only needed members, verify current inputs
against the retained receipts, review the draft helpers, then finish adoption
and its affected checks. Reuse the nine successful compiler outputs; do not
recompile identical digests. Expected257/13 and402 overall remain conditional
on successful maintained adoption, not current facts.

## Remaining authored candidates

Sizes below are original/current; differences are strict full-span counts.

| Unit | Owner | Bytes | Differences |
| --- | --- | ---: | ---: |
| draw-sprite |resources.cpp|105 /107|94|
| blt-sprite |resources.cpp|195 /199|173|
| fill-triangle |raster.cpp|1710 /1710|48|
| present-regions-now |display.cpp|984 /984|2|
| wait-frames |display.cpp|170 /170|6|
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
Historical249 semantic scopes/cases/order have not been rerun by this handoff.

## Read and verify without restarting reconstruction

Read [AGENTS.md](../../AGENTS.md), [workflow](WORKFLOW.md),
[source-search policy](SOURCE_CANDIDATE_SEARCH.md) and the relevant research note.
The1430-line preceding handoff is preserved in
[handoff history](HANDOFF_HISTORY_20261021.md); it is not a fresh work queue.
For retained compiler/provider evidence and its limits, see [REA operations](REA.md).

```bash
git status --short
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py
```

Do not run `replay-exact-units.py` as a read-only status command: it compiles.
Do not infer live jobs from lock files. No owned compiler/provider/native job
remains running at handoff; idle Wine/MCP infrastructure is not a pending trial.

Preserve `original/`, `.tools/`, `ghidra-project/`, current `build/exact/`, reports,
tested delivery products, valid CMake caches and the141-record frontend snapshot.
Raw evidence is private. Closed trial inputs/products may be retired only after
full member-size/SHA verification with recoverable paths; see the private
`.analysis/handoff-cleanup-20261021/` journal and the waiting recovery archive.
This handoff retires216 temporary trial files after full member verification,
releasing2,797,568 allocated bytes net. The ordinary cleanup preview finds no
additional eligible actions; retained products/caches are intentionally kept.

Future heavy work stays serial on CPU0,35% CPU,384/512MiB memory, CMake parallel1
and the silent audio sink. Use `scripts/repo-python`; do not request nonexistent
original project/PDB/MAP/build records. Verified future checkpoints use the
`gpt-6.1-sol: ` commit prefix and configured `origin/main`.
