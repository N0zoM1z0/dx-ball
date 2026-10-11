# Editor cursor presentation after reload

The preceding [display-depth check](WINDOWS_DISPLAY_DEPTH.md) retained 186
editor-reload pixel differences at the red/white original cursor. This follow-up
checks stationary presentation and subsequent motion, including the same two-cell
paint/save/clear/load fixture, before treating that snapshot as a source defect.

Both original and current VC4 source run on 640-by-480 24-bit Xvfb. The existing
SDK reader is reused by complete binary/compiler/header identity. It reads
ordinary state plus original cursor X/Y at `0x438B24/0x438B28` and draw-to-primary
at `0x4228D0`. Those addresses are already explicit bindings in the complete
908-byte exact editor-frame unit. No target state, instructions or APIs are patched.

| Fixture | Original reads | VC4 reads | Complete RGB pairs |
| --- | ---: | ---: | ---: |
| Unchanged initial board | 66 | 69 | 9, all zero differences |
| Same two-cell paint/save/clear/load | 75 | 82 | 9, all zero differences |

Each fixture captures three samples before L, three after L and three after
motion from `(65,57)` to `(200,200)`, with 0.3 seconds between samples. Both
executables render the cursor at the observed position in every sample. All
36 captured frames and all 18 whole-frame pairs are retained without masks.
The two-cell fixture uses actual CTRL painting and S/Backspace/L; both complete
saved banks retain hash
`b88441eb5e06676a106501a60a450b8046fa7b880e8f53ffe5f556ae75a42cd2`.
The 49 original assets stay unchanged and all four runs exit zero without a
remaining game window. This bounds the prior difference as an unsynchronized
presentation observation, rather than evidence of a persistent missing cursor.
It does not prove atomic frame synchronization, all editor states or physical
display fidelity. MinGW has no additional cursor run in this checkpoint.

## Paddle equality spelling diagnostic

The reused complete REA paddle dossier
`ev_5be09046f1c60aeabad5697e07a604bbd89c05139b40ac5bda631e4864a44630`
observes a mouse-X load before comparing paddle X. Current complete 203-byte
matching output retains four reversed address bytes at offsets 139/140/145/146.
One canonical VC4 compilation of the equivalent mouse-first C inequality
spelling produces exactly the same complete code and all 20 actual relocations.
It neither recovers an operation nor creates a new exact match. The rejected
source/object/compiler receipt survives; original source and matching object are
restored by hashes without recompilation. Further equivalent equality spelling
trials are closed unless independent new evidence changes the question.

All four game/library products remain unchanged. No native/MinGW rebuild, legacy
link, reader compilation, new REA request or owner-oracle replay occurs. The one
matching source compilation is explicitly rejected. Counts remain 206 exact
functions /44,406 code /136 metadata bytes, 285 source-present /270 authored,
249 scoped semantic acceptances and origins 117 runtime /42 generated /99 unknown.

Private cursor receipts: `.analysis/editor-cursor-presentation/`, including
`two-cell/`. Rejected comparison: `.analysis/paddle-cursor-load-order/`. Seal:
`.analysis/checkpoints/editor-cursor-presentation-285-206/sha256.json`. Cleanup
preserves all unique observations and the rejected stage, removes only recorded
resettable probe files, and deduplicates immutable copies against the immediately
preceding display-depth seal. Full campaign, physical audio/display and original
source identity remain unproved.
