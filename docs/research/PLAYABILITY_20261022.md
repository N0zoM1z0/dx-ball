# Expanded playability checks

October 22, 2026. These checks exercise the current restored-CRT VC4 image,
SHA-256 `bdd425241ba51d6fe671bb0184b4ad86062326fc9e1eb407d2536235b93df79c`,
built from the completed 270-function authored-exact source. The
[build record](CURRENT_VC4_BUILD.md) covers its existing basic/editor and
single-brick transition passes. No game source, EXE, matching recipe or exact
ledger changes during this validation.

| Check | Result |
| --- | --- |
| Natural life loss, name editing and full ranking reload | Pass; two normal game exits |
| Fifty editor-created boards and real clears through terminal routing/storage | Pass; normal exit |
| Untouched original-bank continuous play | Pass within a 900.046-second episode; advances to original board index 2 |
| Game-only digital audio signal | Pass within a 5.991678-second stereo recording |
| Complete focus recovery flow | Not accepted; failed current/original controls retained |

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
The next focused diagnosis should record actual X11 keyboard focus/stacking and
DirectDraw cooperative/surface state after the SDK foreground request. The
current comparison does not identify which of those mechanisms is responsible.

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

## Original-bank episode: pass within 900 seconds

One game process runs 900.046 seconds after ready gameplay begins, using ordinary
XTest mouse input and the complete unchanged 20,000-byte original bank. It
naturally advances from board index 0 through 1 to 2. Each initialized board's
full 400 bytes matches the original file in two ready samples. Final sampled
score is 2,718, lives 3. There are 27,596 valid SDK samples, 27,585 processed
samples, zero malformed samples and 102 retained transition/periodic samples.

The run takes 937.028 seconds including startup and cleanup. No crash or input
deadline failure occurs. The existing harness deliberately stops the game at
the episode boundary, so this case does not establish a normal user exit;
game-over/restart and terminal cases above separately check that. The saved
third-board frame is captured during subsequent cleanup, rather than at the
exact final state-read instant. All 49 originals and the complete runtime bank
remain unchanged.

REA process evidence:
`ev_9a1b9247d29c1cd1475fb554097d2cea2ded5c249f0aba19fcf68903c52ad9e3`.
Private receipt:
`.analysis/playability-exact270-20261022/campaign/verification.json`.
This is bounded natural progression and stability evidence. Full original
50-board completion and coverage of every power-up remain open.

## Digital audio signal: pass within the observed stream

The verified game's own PulseAudio sink input produces 5.991678 seconds of
finite float32 stereo PCM at 44,100 Hz. Each channel has 264,233 samples;
27,669 left and 27,672 right samples are nonzero. Stream identity, PID/start
identity, routing and monitor selection match before/after. No other stream
is recorded and the host default sink is unchanged. The retained gzip is
decompressed and checked against the full PCM digest before sample statistics
are recomputed.

PCM SHA-256:
`4fb5b0c9add230d24d6e06d9675dd33dd008ca97b6a5d206777a6b633e67932d`.
Private receipt:
`.analysis/playability-exact270-20261022/campaign/audio-verification.json`.
This establishes digital signal presence after Wine/Pulse conversion. Physical
playback, original-byte mixing equivalence, complete voice controls and MIDI
remain outside the observation.

## Resource bounds and evidence retention

Commands run serially on CPU 0 with 35% CPU, 384 MiB memory high and 512 MiB max,
640×480×24 Xvfb and the silent audio sink. Successful and failed cases retain
actual resource events. Owned runtime copies are carrier-checked and archived
with member size/SHA/mode verification before retirement. The current delivery,
originals, accepted objects and useful caches remain.

| Successful flow | Seconds including startup/cleanup | Peak bytes | Soft high events | Max/OOM events |
| --- | ---: | ---: | ---: | ---: |
| Game-over/restart | 169.406 | 403,173,376 | 638 | 0 |
| Fifty-clear terminal fixture | 708.368 | 403,275,776 | 422 | 0 |
| Original-bank episode, including audio observation | 937.028 | 403,177,472 | 287 | 0 |

Seven owned 49-file runtimes, including failed controls, are verified and retired:
343 copied files. Full failed evidence and canonical REA responses remain. The
local delivery ZIP retains the same tested executable and 50 member identities;
its adjacent manifest links this expanded validation, including the open focus
failure. Private final authority is
`.analysis/playability-exact270-20261022/current-checkpoint.json`.
