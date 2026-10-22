# Expanded playability checks

October 22, 2026. These checks exercise the current restored-CRT VC4 image,
SHA-256 `bdd425241ba51d6fe671bb0184b4ad86062326fc9e1eb407d2536235b93df79c`,
built from the completed 270-function authored-exact source. The
[build record](CURRENT_VC4_BUILD.md) covers its existing basic/editor and
single-brick transition passes. No game source, EXE, matching recipe or exact
ledger changes during this validation.

## Natural life loss and ranking persistence: pass

Ordinary mouse input releases three balls and deliberately misses them. Lives
fall 3→2→1→0, with final score 222. The game accepts `rex`, Backspace and Shift+A
as `reA`, inserts the result at rank 0, and writes the expected complete
660-byte score table. After normal exit, a second game process reads the same
complete table. Both game processes exit normally.

The unchanged existing game-over test body uses the verified persistent
read-only scalar/ball reader, with three complete SDK table reads at its
existing assertions. There are 1,219 state reads, 4,575 valid stream samples
and zero malformed samples. All 49 original files remain unchanged. Test scores
stay in the isolated runtime/evidence and do not enter the delivery bundle.

REA process evidence:
`ev_589ddef739ddbc7c56006332a31b0161a290ba8dda646596881a96152fbf6c7b`.
Private receipt:
`.analysis/playability-exact270-20261022/gameover/verification.json`.

## Focus restoration: not accepted

The current image and unmodified original EXE both fail the same existing
fixed 0.5-second sustained-motion assertion under Wine/Xvfb and the same resource
bounds. Activity returns to 1 and the surface-restore flag clears, but two
successive ball samples are equal. The current image's later failure capture
shows another ball position. Independent clock/RNG trajectories prevent a
unique causal attribution from this comparison.

Using a persistent read-only transport, the current image passes the initial
resume and 0.5-second motion predicates, then fails the unchanged 20-second
return-menu deadline. That full flow remains failed. No game patch or deadline
relaxation is adopted. The host/DirectDraw/input cause remains unresolved;
these observations do not establish a reconstruction-specific regression.

Current/original initial process evidence:
`ev_f63711367427d4795f7df00563d922e33cd5d2b535f4e271b8d95fc0d8ad8d07` /
`ev_4cae6f0b8bc511f34d981a43834a754583072771d7832756bc9645e819c05af5`.
The complete failed responses, transport failure and comparison remain under
`.analysis/playability-exact270-20261022/` and
`.analysis/rea/playability-exact270-20261022/`.

## Fifty real clears and terminal routing: pass

The unchanged existing terminal test creates a single brick in each of 50
boards through real editor input and saves the complete expected 20,000-byte
bank. It then performs 50 real ball/brick clears. Every next-board index, score
increment and life count matches: terminal index 50, score 500, lives 3 and
menu mode 0. All 400 terminal tile bytes and the separate diagnostic bank-tail
reads retain the original fixture's scoped storage pattern, including variable
clock bytes. The game exits normally; saved-frame review confirms the menu
and Last Score 500.

There are 6,848 state reads, 22,921 valid persistent samples, zero malformed
samples and 11 complete diagnostic tail reads. The run takes 708.368 seconds.
All 49 originals remain unchanged. This editor-created fixture establishes the
50-transition/terminal path separately from the original 50-board campaign.

REA process evidence:
`ev_6a51b822fb76523793e513c7096ba652c256cff9bd31900f045371384848ac7f`.
Private receipt:
`.analysis/playability-exact270-20261022/terminal/verification.json`.

## Original-bank episode: running

A 900-second real-input episode uses the complete unchanged
original bank, retaining actual initialized boards and sampled state. A bounded
episode will not be described as full-campaign completion. A six-second read-only
monitor of only the verified game's digital audio stream is also planned;
physical sound hardware and audio equivalence remain separate.

Commands run serially on CPU 0 with 35% CPU, 384 MiB memory high and 512 MiB max,
640×480×24 Xvfb and the silent audio sink. Successful and failed cases retain
actual resource events. Owned runtime copies are carrier-checked and archived
with member size/SHA/mode verification before retirement. The current delivery,
originals, accepted objects and useful caches remain.
