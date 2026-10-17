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

The live controller stays unchanged. A future grid-based selector needs a
bounded original-frame comparison with sampling/input delays and reachable
paddle positions, plus honest reporting of its selected phase. Fixed-phase
results here prove neither physical input delivery nor campaign speedup. SDK
snapshots may mix frames; unobserved modifiers are not reconstructed.

Private `.analysis/campaign-tail-original-frames-20261017/` retains the executed
probe, initial failure/diagnostic, source identities, complete traces and the
joined static/original results. The two large JSON records are byte-verified
in gzip carriers before removing disposable uncompressed copies. The run uses
the existing native fixture with one CPU/35% quota and640/768 MiB memory limits.
No compilation, provider query, game, relink or full replay runs; source/exact
acceptance remains475/380, with34 authored candidates.
