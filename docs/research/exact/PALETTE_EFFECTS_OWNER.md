# Shared palette-effects implementation owner

October 18, 2026. One fixed C++ owner for four consecutive original palette
functions leaves all29 affected complete code identities unchanged. Reject the
model as an exactness improvement. Canonical source, headers, objects and delivery
stay unchanged:394 exact functions and21 authored candidates.

## Source basis and fixed model

The original entries are consecutive at40A880 (right shift),40A970 (left shift),
40AA60 (RGB-pool rotation) and40AB20 (set RGB). They share live palette state,
the cursor-warp control and the SetEntries interface. The first two are mirrored
shifts; the RGB-pool routine calls the RGB setter. This supports one inferred
implementation family without proving the historical translation-unit boundary.

The private model extracts exactly those four functions from `ui.c` and
`display.cpp` into `palettes.cpp`, in that fixed original address sequence.
It includes the complete unchanged `ui.h`, `display.h` and `paddle.h` under C
linkage. The last header supplies the consumed cursor-warp declaration. There
is no private header view or declaration duplication.

Only two executable spellings change: right shift and RGB set use the existing
genuine C++ palette SetEntries member instead of C vtable dispatch. Receiver,
arguments, local names/types/scopes, bounds, color snapshots and writes remain
unchanged. The other two moved bodies are byte-identical source. All unrelated
function text and state definitions stay in their existing owners.

The prior whole-UI C++/COM control included text and line functions; it did not
test this four-function owner. No additional language, function-order, header,
identifier, mask or flag variants follow the present result.

## Complete comparison

Three serial VC4 compilations use the unchanged owner flags and recursively
attest every consumed project input. All29 original functions compare, including
all459 actual relocation bindings and full local-target checks. There are no
attached metadata or literal-ordinal remappings in this closure.

| Owner | Complete functions | Existing exacts preserved |
| --- | ---: | ---: |
| UI after extraction |6|4|
| Display after extraction |19|16|
| Shared palette effects |4|2|

All29 relocation-resolved digests equal their current baselines. The22 exacts
retain5,375 code bytes. Both shifts remain234/9 bytes/differences; RGB-pool
rotation remains188 exact and RGB setting remains108 exact. All seven candidate
results retain their current scope; no gain or loss is hidden by the extraction.

The public symbols, target addresses, types, addends and original extents are
preserved. Binding offsets are read from the actual objects; the independent
comparison checks every full span. No decorated or literal identity rebind is
needed. The result tests the complete owner model, not an isolated causal claim
about language, headers or source order.

Private `.analysis/palette-implementation-owner-20261018/` retains source
transformation proofs, source/object identities, all comparisons and independent
review. No original provider session, native build, relink, runtime case, game
or full replay follows this rejected model. Work remains serial on one CPU
under CPU35%, memory high640MiB/max768MiB. Disposable proposal copies and five
before/proposal objects are archived and every member hash verified before
removal; current tested products and useful caches remain.

Cleanup removes28 raw copied inputs/products, including all five objects, and
the disposable Python preflight cache. It releases163,840 allocated bytes net
of the verified archive and cleanup journal. Full receipts remain available.
