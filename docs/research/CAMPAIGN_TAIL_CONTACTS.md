# Tail-grid contact counterfactuals

The current-image original50 attempt ended at its observation deadline, with
twenty initialized layouts and no full pass. A bounded follow-up checks a possible
controller improvement without launching another game or changing its policy.

Two retained board-index7 observations supply the same four-tile geometry,
a single falling speed9 ball with sprite61, nine-pixel dimensions and paddle
width146. Each geometry is seeded into the existing original/native core fixture
with all six current contact phases. Other globals use fixture defaults. These
are counterfactuals derived from observed geometry, not complete live-state replays.

## Original-frame results

All twelve cases catch the ball. Complete original/native comparisons pass for
1,229 frames, including state, grids, list roots/cursors, ordered effects, pixels
and freed-memory poisoning. One request is delivered per frame with no delay;
the selected phase stays fixed through one paddle/field trip.

| Geometry, observation seconds | Saved request phase | Phases with a subsequent grid change | Fastest phase | Frames after contact |
| --- | ---: | --- | ---: | ---: |
| 5702.759 | 4 | 3, 4, 5 | 5 | 38 |
| 5852.930 | 0 | 1, 2, 5 | 5 | 71 |

The fastest phase is an observation within these six choices, not a global
optimum. A hit means the first board-cell change: the fireball converts a tile
to type8. It does not establish a cleared brick or completed board.

The earlier offline center-ray estimate predicts only two hits per geometry;
the original updater finds three. Its side/corner probes matter. A ray can help
rank choices but cannot replace the game's collision rules. The saved phase4
also hits in the first controlled geometry, so these results do not explain the
live plateau or establish a closed orbit.

## Fixture limit and preserved checks

The initial full-frame run stops on an unclassified native particle deletion at
frame65. A diagnostic identifies an original36-byte particle payload,44-byte
x86 node and56-byte host node. A newly created fire-trail particle can be removed
in the same frame before a callback or frame boundary classifies its published
list root. The old core fixture only allows an unclassified ball-clone deletion.

The private native adapter records allocation provenance while invoking the
saved genuine, typed particle callback. It classifies a previously unobserved
free only when that producer tag and the real particle size both agree. It
retains the parent's payload, liveness, event and poison checks. No ownership
rule is relaxed based on an ambiguous host size alone. The original fixture and
game code stay unchanged; the final full comparisons pass.

## Scope and next gate

The initial assessment leaves the controller unchanged. Its follow-up selector
is described below. Fixed-phase
results here prove neither physical input delivery nor campaign speedup. SDK
snapshots may mix frames; unobserved modifiers are not reconstructed.

Private `.analysis/campaign-tail-original-frames-20261017/` retains the executed
probe, initial failure/diagnostic, source identities, complete traces and the
joined static/original results. The two large JSON records are byte-verified
in gzip carriers before removing disposable uncompressed copies. The run uses
the existing native fixture with one CPU/35% quota and640/768 MiB memory limits.
No compilation, provider query, game, relink or full replay runs; source/exact
acceptance remains475/380, with34 authored candidates.

## Sparse-tail selector and delayed-input checks

The controller now ranks the six existing contact choices with a bounded center
ray when there is one falling speed9 ball below the brick field, square5/9-pixel
dimensions, bank0, no falling bonuses or kind3 drift, and two through eight
nonempty cells without hard type2 tiles. Other situations retain the existing
contact policy. The forecast uses the original discrete wall clamp, actual
reachable mouse positions and the six measured interior rebound bins. It stops
after200 ray steps; incoming contact projection is capped at100 frames.

The ray ranks approximate first hits, including a possible ceiling reflection.
It omits side/corner collision and unobserved modifiers. Selection is a heuristic,
not a replacement physics model or a promise that a predicted cell will be hit.

Twelve new controlled cases compare the old policy with the selector on both
geometries, at sampling intervals1/3 and input delays0/2 frames. All909 complete
original/native frame comparisons pass and all twelve catches succeed. In each
timing control the first geometry changes a cell38 frames after contact versus46
for the old policy; the second changes a cell after71 frames while the old phase
returns below the field unchanged. These are bounded frame outcomes, not live
FPS, measured input latency or a campaign-speedup claim. Eleven additional controls
verify unchanged fallback requests for missing/bad grids, dense/hard grids,
modifiers, bonuses, multiple balls, unsupported motion and a nonpositive width.

The reusable [controlled check](../../tests/test_campaign_tail_selector.py) tags
particle allocation at the genuine typed boundary, then retains complete parent
state/event/list/pixel/poison comparisons. It encounters six same-frame particle
frees. No compiler or native-fixture rebuild is needed.

`choose_mouse_decision` returns both selected and scheduled phase. The Windows
observer counts the selected phase and records both phases, policy and predicted
cell. The integer `choose_mouse` API dispatches to the same decision. Existing
historical campaign reports keep their original controller identities and data.

The final909 frames execute the current controller source after wrapper
integration and the width guard. An earlier preliminary run is preserved
separately. Only these affected frame cases repeat for the final change; the
historical suites do not. Both observed geometries also verify the integer
wrapper's selected request. The Windows CLI help check passes; no new live game
runs.

Private `.analysis/campaign-tail-selector-20261017/` preserves before/tested
source, actual execution inputs, complete controls and wrapper checks. A
preliminary local cost sample averages about0.29ms process CPU time per eligible
decision; it is not runtime throughput. Heavy checks remain
serial under the existing resource limits. Game source, objects, executable and
acceptance ledgers stay unchanged. A bounded real-input check is still needed
before claiming live behavior; full original50 completion remains unproved.
