# Explosion requests and brick animations

The [complete brick-power restoration](EXACT_BRICK_POWERS.md) calls the real
brick-effect entry directly. GameNative now selects the verified owned copied
image and binds its existing callbacks; one typed byte-preserving wrapper reads
the live callback slot and falls back to that image's actual source body.
EffectsNative may subsequently install its actual body. This bridge does not
prove effects implementation or hardware behavior. The effects input closure
now includes the four actually consumed loader/shim/resource-control inputs.

REA/Ghidra tracing distinguishes the request queue at `0x43F8E0` from the
animation queue at `0x43FA98`. `src/gameplay.c` owns request traversal, deletion
and enqueueing; `src/effects.c` owns the animation lifecycle. Both retain natural
C pointer layouts, with x86 node sizes 20 and 40 bytes respectively. Animation
payload is 32 bytes: kind, sprite, x, y, one tile byte with natural alignment,
frames remaining, frame period and elapsed ticks. Kind 1 stores screen
coordinates; kind 2 stores tile coordinates. Allocation leaves payload and
alignment bytes untouched until a constructor writes them.

| Original address | Maintained storage | Meaning |
| --- | --- | --- |
| `0x43F8E0` | `dxball_explosions` | Request current/first/last |
| `0x43FA98` | `dxball_brick_effects` | Animation current/first/last |
| `0x43A918` | `dxball_board_aux` | Per-tile explosion occupancy |
| `0x43A8A8` / `0x43A8AC` | `dxball_hit_dx` / `dxball_hit_dy` | Direction passed to bonus production |
| `0x42E690` | `dxball_effect_surface` | Explosion sprite destination |

The native oracle executes the original list and animation bodies against the
compiled maintained C. It compares complete payload bytes, links, current
position, board and occupancy grids, counters, surfaces, RNG consumption and
ordered boundary calls. Deletion poisons released storage and checks for double
release. Allocation/deletion remain explicit CRT boundaries; bonus creation,
keyed/reduced rendering and region updates remain controlled callbacks.
No implementation of those dependencies is inferred from matching their calls.
The shared allocation/release defaults now use the separately accepted
[runtime allocation chain](ALLOCATOR_OWNER.md); these owner oracles retain
their controlled allocation boundary.

## Observed behavior

Begin resets current to first and returns a full integer 0/1, despite Ghidra's
`bool` signature. Advance moves to next and returns 1; reaching the end resets
current to first and returns 0. Delete chooses next, or previous when deleting
the tail, reconnects both links and updates first/last before release. A loop
that deletes and then advances skips the immediate successor. This behavior
applies to requests and animation cleanup and is preserved across frames.

An explosion constructor assigns sprite 22 and eight frames, converts tile
coordinates to `(20 + 30*x, 50 + 15*y)`, and sets occupancy to 1. Each due step
reduces the frame count. At five frames remaining, it clears the center tile;
nonempty tiles other than type 2 also decrement the remaining-brick counter.
When the center is type 8, it enqueues nonempty neighbors in this order:
N, NW, NE, S, SW, SE, W, E, with edge checks. Cleanup restores a 30x15 background
rectangle, reports its region, clears occupancy and deletes the node. The
reduced-particle setting selects an alternate sprite dependency.

Ordinary brick effects use sprite 20 with three frames in mode 0 and produce a
bonus request with the stored hit direction. Other modes use sprite 19 with two
frames and no bonus request. Both use period 2 and initially elapsed ticks 2.
Their due steps redraw the underlying tile, overlay the keyed animation or
remove the completed node, then report the screen rectangle. The dispatcher
switches on kinds 1 and 2 and advances unknown kinds without changing payload.

The original frame updater `0x40F8B0` processes animations before consuming
explosion requests. A kind-1 request creates an animation only when occupancy is
zero, adds four points, and requests a bonus with RNG-derived dx and dy=-2.
Consumed nodes are deleted using the original skip behavior. Only pending==1
triggers a random explosion sound and resets pending to zero. The maintained
`dxball_apply_explosion_requests` extracts that phase; it is not counted as an
implementation of the complete frame updater.

## Validation and exact boundaries

The gameplay oracle now has 13,689 cases, including 903 added request-helper
cases. The effects oracle has 12,977 direct cases covering all 400 explosion
positions, all 256 brick bytes, timer boundaries, edge propagation, hard/empty
center tiles, reduced rendering, null allocation, every current position in
lists of length 0..8, mixed animation queues, and unknown dispatcher kinds.
An additional 864 integration cases execute the actual original frame updater
with unrelated physics/UI/clock dependencies neutralized, comparing only the
animation and explosion-request phases. These integration cases are reported
separately. Another 1,536 cases execute actual hit-to-animation calls across
all tile bytes, hard-tile flags and display modes. All integration cases are
excluded from function-acceptance totals. Whole-frame behavior,
bonus/particle implementation, DirectDraw rasterization and audio remain pending.

Eight new complete exact units cover both begin/advance pairs, enqueue,
animation append, explosion construction and animation dispatch: 806 bytes.
The dispatcher spans `0x412510..0x412587`: 115 Ghidra-owned bytes plus a five-byte
unreachable alignment gap. The entire 120-byte COMDAT must match, including that
gap. Other functions remain semantic-only. Deletion dossiers each own 215 bytes
in a 220-byte span and show compiler-generated C++ delete temporaries. The
maintained C uses one meaningful saved-node variable and does not invent locals
to reproduce those artifacts. Shared-header changes also renumber the pan
literals; the manifest binds their new names and independently checks their
contents in object and target.

## REA evidence

Evidence is observed static analysis, corroborated separately by unmodified
x86 execution. Full results and snapshots remain under ignored `.analysis/rea/`.
The per-function dossiers expose instructions, inclusive ranges and callers;
recovered C names and typed fields are reconstruction decisions.

| Entry | Evidence ID | Owned / span bytes |
| --- | --- | ---: |
| `0x410070` | `ev_80fc0d3eb489435cb358378c87af0ab6cdf0452ea91c3130435d301de8cd1805` | 57 / 57 |
| `0x410170` | `ev_4a996ce8b1c696f9b8499a93062c8783d6936f2bb57ebcfed07b98948fd37c3f` | 89 / 89 |
| `0x40ff50` | `ev_1538f8576bc2c7b207799609630f986e3933507a8a2a23a9a16767404a1a93d4` | 215 / 220 |
| `0x4100b0` | `ev_5f4d83a6f76902c735b47dd50457a81c0db79b9c09e8adeed59e3da294738cb8` | 57 / 57 |
| `0x412590` | `ev_886d6a238cd487da7ef3206c31fc47d874df216f023047d55b62188f86c7c1da` | 89 / 89 |
| `0x412690` | `ev_6a32fd651ca3a7fb5d9cfda71f66a09b545b0a7baf59e584310935a7953e64af` | 146 / 146 |
| `0x412a50` | `ev_15590b4df69e7901145c02e294dca11e8f4f9c5be7675b3a332149d8dddde90e` | 215 / 220 |
| `0x412cb0` | `ev_ddb63b6637b595283546b24dd97e5dba3e2af6a5b63142902883b2e6aa6dd702` | 313 / 313 |
| `0x412730` | `ev_b10ee96258ecd655c8f9258fc4ae6cb2c52939077283dc0409f9f912688f79b3` | 797 / 797 |
| `0x4125f0` | `ev_0e1624eafd38ad8ab2071252d96c8d58dc5a395fac02ff842dfc9d61f4ef0f6d` | 149 / 149 |
| `0x412510` | `ev_889bc398a93966a7b706e27e6b7af68c1e69a512723b0b40314765bcbfb57783` | 115 / 120 |

Enqueue dossier `0x412B30`: `ev_f0995a29d766938cd1cbe47ce792d20976af9379bea1da71164921488da80844`.
Brick constructor `0x412BA0` and request helpers were first followed in batch Evidence `ev_49448d4e201f7fd4da584beaa1c1bfe2fef9bdf63fbc3afb0b03b46c5275ee0a`.
Frame/update context: `ev_fad3b4a3a01c9e2c37b463f563274f395c7bee44ff37b49b316676d6265d0cb7`.
Request-base xrefs: `ev_a1e13bcfbf56b4c898376f068332369cc44c5039a6856bdcf9b7d5a62b17606b`. Empty xref results for adjacent fields do not imply no access: these helpers dereference an owner pointer and offsets.
