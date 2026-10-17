# Board transition through the restored CRT

The earlier 19-member `vc40-restored-crt` image identified below clears an editor-created
single-brick board, loads the untouched original second board and exits zero.
This adds the round transition to its existing [editor](RESTORED_CRT_EDITOR_FLOW.md)
and [game-over](RESTORED_CRT_GAMEOVER_FLOW.md) observations. Game source,
compiled objects and all function claims remain unchanged.

The maintained round driver now accepts the restored-CRT profile and reports
only selected product identities:

```bash
scripts/repo-python tests/test_windows_round.py --profile vc40-restored-crt
```

Use the resource scope and silent sink in [REA commands](../agent/REA.md).
The adopted run reuses the attested game and reader; neither is compiled.
Other profiles and the known failed focus diagnostic are not rerun. The public
direct entry retains its existing reader-build step.

## Actual board and file checks

Real Control-F1, Backspace, tile selection and CTRL painting create one tile1
at column6/row18. S saves all 20,000 expected bank bytes; the other 49 boards
remain byte-identical to the original bank. The game starts that edited board
with one remaining brick, three lives and an attached ball.

Real paddle movement and a click release the ball. Clearing the brick earns
ten points. The completed next initialization has board index1, an attached
ball, three lives and all 400 bytes equal to original board1. Its destructible
brick count is 222. The full saved bank is checked again after the game returns
to the menu and exits with code zero. All 49 original files remain unchanged.
The passing run records 135 read-only observations.

The edited bank SHA-256 is
`4bd50fcfa3674f91ceb98e0c06a001e10185e06a734594857c2a35cf76b5c8cc`;
the loaded second-board SHA-256 is
`3cb8aaac594508ad464533a79683ddcba2d2959dc731f1886010abba300fab9c`.
Reviewed captures show the editor's single brick and the next board's colored
heart pattern. Complete state and file checks establish the transition;
screenshots alone do not.

## Input and sampling corrections

The first run times out before painting: the board stays empty, selected tile
is one, and the mouse reaches `(215,327)` with its action already cleared.
The fixed-duration click did not establish that the editor consumed that cell.
This is consistent with input arriving across a slow redraw; cursor sampling
inside that frame was not captured, so the precise event interleaving is not
claimed. Its failure, states, screenshot and executed observer are retained.

The driver now waits for toolbar release, uses the original CTRL painting
behavior until the complete expected board is observed, then releases mouse
and CTRL in `finally` and waits for both state flags to clear. Game instructions,
timing, backing memory and API calls are not patched.

The clear waiter also accepts an earned score when the board index has already
advanced. The zero-brick state can disappear before the next SDK sample, as
already observed in the [terminal control](TERMINAL_RUNTIME.md#sampling-a-fast-clear).
All ten final assertions in the round observation function remain AST-identical,
including complete next-board bytes and counts, lives, score, saved bank and
normal shutdown. A control over the retained passing states omits zero-brick
samples: the old predicate misses completion, while the new predicate accepts
the actual board1/222-brick state. This control runs no additional game and
adds no historical semantic cases.

## Executed source and remaining scope

Eleven complete source bodies match the executed image after all **441
bindings / 5,744 bytes**: board load/store/initialization, brick count/hit, editor
frame/key, game frame, round reset/restart and level advance. Full strings and
the floating literal are attested. The floating constant is an interior symbol
in a shared readonly section, not a dedicated COMDAT; its full eight bytes
follow the existing manifest attestation. Current source-to-linked checks do
not create new original-function exact claims.

The image remains
`cbe767d19d7adc1363facdc862652d2c42342ba50bb01ec4d8eca57383183cfe`.
It imports no MSVCRT DLL, and the earlier board/stdio/low-I/O linkage proof still
applies to this same image. The 19 explicit original CRT members remain
user-approved dependencies.

All source/function/origin/exact/semantic ledgers and complete comparison
reports remain unchanged: **475 source / 380 exact / 95 candidates**, including
34 authored candidates. No full replay or provider query runs. This one-board
fixture does not establish the original campaign, terminal index50, successful
focus recovery or physical graphics/audio fidelity. Authored exact work stays
first; ports remain deferred.

Private `.analysis/restored-crt-round-20261017/` retains the passing CLI run,
initial failure, frozen inputs/objects, 135 passing states, complete files,
captures, sampling control and linkage verification. Executed image/map/reader
carriers are reused only after full-byte verification.
After retaining evidence, 49 verified automated runtime copies are removed and
236 frozen inputs are archived, releasing 2,920,448 allocated bytes across
those cleanup operations. Other profile and manual runtime directories remain
untouched. Heavy work stays serial under CPU 35%, memory high 640 MiB / maximum
768 MiB.

## Current image bounded entry and exit

The later brick-hit scope image
`50e406099293b5de1d5088b3d022e585aa493c8a53f152342e526ed15943958c`
passes a separate 5.019-second original-board0 episode and normal shutdown.
The unchanged maintained campaign observer verifies all 400 initial board
bytes and uses ordinary XTest mouse input. The last gameplay sample has score10,
167 remaining bricks and three lives. A reviewed capture shows the board,
moving ball and paddle. Escape reaches a completed menu; the next Escape exits0
and removes the game window. All 20,000 bank bytes and 49 originals stay fixed.

The persistent reader is reused at SHA-256
`f9dda62006f50395eb367cd0b60ea8137dbaa9cad58348a39ceafb2df4f4a8a1`.
It yields 1,410 valid SDK samples, no malformed lines and 1,257 processed episode
samples. The private driver appends only the menu/exit helper after the original
episode loop; removing that call restores the maintained observer's complete AST.
No game or reader compilation, relink, new function acceptance or full replay runs.
This short episode does not repeat the earlier edited-board transition or
establish full50 progression, focus recovery or physical-driver fidelity.

An earlier per-read observation of this same image fails before gameplay:
42 samples retain the graphics-reset request and the opening-ready wait times
out. Its observer exits1 and stops the process during cleanup; no normal exit
is claimed for that attempt. The passing persistent transport is a different
observation method, not proof that reader startup caused the first failure.
Neither attempt has a new HRESULT trace establishing the known focus mechanism.
Keep both outcomes; do not restart either producer or patch game code for them.

Private `.analysis/current-restored-crt-entry-20261017/` retains the failed
attempt; `.analysis/current-restored-crt-persistent-entry-20261017/` retains the
passing run, complete frozen compiler inputs including C++, AST proof, bounded
states, capture, real exit and verification. All three recorded owned process
identities are absent. Measured average CPU is32.1% of one CPU, peak301.668 MiB,
with no memory-limit events under the35% /640 /768 MiB scope. Audio remains on
the silent sink and the default sink stays unchanged. After byte verification,
the passing run's49 disposable runtime copies are removed. Historical public
reports retain their own image identities.
