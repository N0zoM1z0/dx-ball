# Playability results

October 22, 2026. These checks use the [current VC4 game](CURRENT_VC4_BUILD.md)
under Wine with 640×480×24 Xvfb. The game source and executable stay unchanged
through the runs.

## Completed checks

| Check | Observed result |
| --- | --- |
| Basic play and editor | Paddle/ball input, pause/resume, painting, full 20,000-byte save/reload and normal exit; 534 state reads. |
| Round transition | Real single-brick clear, score 10/lives 3, complete original board index 1 loaded and normal exit; 116 reads. |
| Game-over and rankings | Lives 3→2→1→0, final score 222, name editing to `reA`, full 660-byte table save and reload in a new process; two normal exits and 1,219 reads. |
| Fifty-board terminal fixture | Real editor input creates 50 single-brick boards. All 50 clear through real ball input, ending at index 50/score 500/lives 3/menu mode 0. Terminal storage and normal exit pass; 6,848 reads. |
| Original-bank continuous play | 900.046 seconds of real mouse input naturally advances through original boards 0/1/2. Each initialized 400-byte board matches the original bank in two ready samples. Final sampled score 2,718/lives 3; 27,596 valid samples and zero malformed samples. |
| Digital audio | The game's own stream produces 5.991678 seconds of finite 44,100 Hz stereo PCM. Each channel has 264,233 samples, with 27,669 left and 27,672 right samples nonzero. |

The original-bank episode uses the unchanged 20,000-byte bank and ends through
the observer's timed cleanup. Normal user exit is checked in the other flows.
Its final screenshot is taken during cleanup, after the last state sample.

Audio capture selects only the verified game's sink input. Stream and process
identity match before/after; the gzip is decompressed, hashed and checked before
recomputing sample statistics. Saved PNG review confirms the ranking, terminal
menu and third original board.

## Focus recovery: failed

Both the original EXE and rebuilt EXE fail the existing 0.5-second sustained-
motion check. Activity returns to 1 and the surface-restore flag clears, but two
successive ball samples are equal. A later rebuilt failure capture shows the
ball at another position.

Persistent rebuilt sampling passes initial resume and the 0.5-second motion
check, then reaches the unchanged 20-second return-menu deadline. The full flow
remains failed. The cause is unresolved. The next diagnosis should record X11
keyboard focus/stacking and DirectDraw cooperative/surface state after the SDK
foreground request.

## Still to verify

- Complete the original 50-board campaign.
- Exercise every power-up in actual play.
- Resolve focus/surface recovery under Wine/Xvfb.
- Verify physical graphics/audio output and MIDI playback.

## Execution and evidence

Runs execute serially on CPU 0 with 35% CPU, 384 MiB memory high and 512 MiB max.
Audio uses the silent sink; the host default sink remains unchanged. All 49
original files and protected source/build inputs retain their hashes.

| Successful flow | Seconds including startup/cleanup | Peak bytes | Soft high events |
| --- | ---: | ---: | ---: |
| Game-over/restart | 169.406 | 403,173,376 | 638 |
| Fifty-clear terminal fixture | 708.368 | 403,275,776 | 422 |
| Original-bank episode and audio capture | 937.028 | 403,177,472 | 287 |

These flows record zero hard-limit and OOM events. Their complete process
Evidence IDs are in [the verification record](../../config/playability-status.json).

Private receipts are under `.analysis/playability-exact270-20261022/`:
`gameover/verification.json`, `terminal/verification.json`,
`campaign/verification.json` and `campaign/audio-verification.json`. The focus
controls, failed reader configuration and comparison are retained alongside
these results. Full REA responses are under
`.analysis/rea/playability-exact270-20261022/`.

Seven owned 49-file runtimes are carrier-checked, archived and member-size/SHA/
mode verified before retiring 343 copied files. Another 40 closed helper/input/
response copies are verified in `closed-evidence.tar.gz` before retirement.
`current-checkpoint.json` links the final receipts and cleanup. Current products,
originals, accepted objects and useful caches remain available.
