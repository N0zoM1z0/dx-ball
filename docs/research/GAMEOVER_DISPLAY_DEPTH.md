# Current-product natural game-over and rendering

The current original, VC4 and MinGW games complete natural life loss, name
editing, ranking insertion, persistence and a fresh-process restart on
640x480x24 Xvfb. This extends the [display-depth correction](WINDOWS_DISPLAY_DEPTH.md)
to the [game-over owner](GAMEOVER_OWNER.md). The game still requests its original
eight-bit DirectDraw mode. Ordinary mouse/keyboard events drive the game;
the existing SDK observer has query/read rights only.

| Profile | Read-only observations | Lives lost | Earned score | Normal process exits |
| --- | ---: | ---: | ---: | ---: |
| Original | 219 | 3 | 222 | 2 |
| VC4 | 234 | 3 | 222 | 2 |
| MinGW | 213 | 3 | 222 | 2 |

Each run observes 3→2→1→0, enters `rex`, removes `x` with Backspace and appends
Shift-A to form `reA`. Enter inserts the score at rank zero. Each independent
expectation checks all 660 bytes, including terminated names and preserved
destination tails, against both the live table and file. A second process has
a distinct observed Windows PID and reads the same complete table from disk.
All six process exits are zero and remove the game window. All 49 original
assets remain unchanged.

In these particular runs all three earned scores and complete saved rankings
agree. Their file SHA-256 is
`fcc15ac92dc92e402d565da1a7fb5a23afd42d544e3308096a47aba8f65c62e8`.
This is an observed result, not an assertion of deterministic trajectories
or equal scores in every future run.

Four complete, unaltered 640x480 frames per profile cover opening, name entry,
ranking and restart opening. All eight original/source RGB comparisons have
zero differing pixels. The name-entry and ranking captures each contain 44
colors; visual review shows filled green title letters, the name prompt and
complete ranking text. Historical two-color eight-bit-host captures remain
retained. State reads and frames are sequential, without presentation
synchronization; these samples do not establish moving-frame or all-state
fidelity, campaign completion, physical audio or asynchronous MIDI.

`tests/test_windows_gameover.py` now accepts `--profile` to select only an
affected control. Both it and `tests/test_windows_round.py` accept
`--display-depth {8,24}` and default to 24, forwarding arguments to their child
process and recording the chosen depth. The round harness's CLI/syntax were
checked; its board-transition/focus flows were not rerun in this checkpoint.
Existing historical round receipts retain their own products/display scope.

The focused driver reuses the fully attested SDK reader without recompilation.
No game source/object, exact manifest, acceptance scope or product changes:
285 source-present, 249 scoped semantic acceptances and 206 exact functions
remain. No owner-oracle replay, game build/link or new REA request is needed.
The existing closed REA-backed state/layout contracts are reused.

Private `.analysis/gameover-display-depth/` retains the driver, each completed
profile receipt, complete state histories, all 12 frames, score files, input
identities, frame comparisons, product verification and cleanup. The immutable
seal is `.analysis/checkpoints/gameover-display-depth-285-206/sha256.json`.
Cleanup preserves unique runtime exits before removing resettable probe copies
and deduplicates only hash-equal before/new-seal files against the immediately
preceding editor-cursor seal. Current/public files remain independent of archives.
