# Current VC4 natural last-brick expiry

The current restored-CRT game passes one natural countdown-to-round-transition
episode. It uses the existing 116 source objects and 19 approved original CRT
members, without compiling the game or SDK reader again.

Image SHA-256:
`345a68875bad0693476c55fcd69f41c5a9b158fc96e1f3e4f3189358001d3f14`.
Reader SHA-256:
`4c29a9c7c4b5132a6e840d138841027af331016b2953a0892ba030837feb1f57`.

## Actual input and observed result

The existing editor/round observer opens the editor, clears board 0, paints one
tile at column 6 / row 18 and saves it through the game. The other 49 original
saved boards remain unchanged. The controller then starts gameplay and keeps
the ball attached. It replaces the existing release step with countdown
observation; there are no target-memory writes or timing hooks.

The SDK records a nonzero last-brick deadline. All 95 board-0 ball samples during
the countdown retain the attached flag. About 55.299 seconds after the armed
sample, the observer reaches the stable next-board predicate. The controller's
position writes are sampled at `(136,0)`; subsequent round reset restores Y to 2.
The score becomes 4, lives remain 3, and all 400 loaded bytes equal original
board 1, the second board. The destructible count is 222 and the final deadline
is zero.

The game returns to menu mode 0 and exits with status 0; its window is absent.
The editor-saved 20,000-byte bank is checked again after exit, and all 49 immutable
original files retain their pinned identities. Reviewed captures show the single
brick before expiry and the colored original second board after the transition.
There are 228 state reads in this episode.

No sample contains `lightning_frames > 0`. This run therefore supplies current
image evidence for natural countdown, automatic clear, loading and shutdown,
without claiming a captured flash, exact animation timing, synchronized pixels,
physical Windows/audio fidelity or a full original campaign. Earlier tests and
GUI episodes keep their own source/product identities and scopes.

## Preservation and cost

The executed observer reuses the maintained editor, file, input, board-loading
and shutdown checks. It changes only the release step to wait for expiry and adds
read-only lightning fields. All 116 source objects, their inputs, the 19 member
files and the existing image verify. Imports are Kernel32, User32, Gdi32, WinMM,
DirectDraw and DirectSound; no MSVCRT DLL is imported.

Work runs serially on one CPU with CPU quota 35%, memory high 640 MiB and maximum
768 MiB, on Xvfb 640x480x24 and the existing silent audio sink. A live cgroup sample
records about 338.3 MiB memory.peak at that point; it is not a final lifetime-peak
measurement. No compiler, relink, provider query, full replay or campaign runs.

Private `.analysis/restored-crt-lightning-expiry-20261017/` retains frozen inputs,
the executed controller, compressed complete observations, captures, resource
sample and verification. After backup equality checks, 49 disposable runtime
copies are removed and the state trace is compressed, releasing 2,105,344 allocated
bytes. Current game products and unique evidence remain available.
Source 475 / exact 380 / complete candidates 95 and semantic 249 are unchanged.
