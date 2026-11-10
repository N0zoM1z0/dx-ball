# Windows build and windowed play

October 31, 2026, Europe/Berlin (UTC+01). Raw process receipts retain UTC timestamps. Game source
and the October 22 tested executable remain unchanged. The [earlier record](PLAYABILITY_20261022.md)
retains its fifteen-minute original-bank episode, fifty-clear editor fixture and
digital audio results; these were not repeated in this update.

## Current result

The user played the reconstruction on Windows 11 with a windowed DirectDraw
wrapper and reported no major playability problem. This is scoped manual
feedback. The current automated play checks run under isolated Wine/Xvfb.

| New check | Result |
| --- | --- |
| Wine built-in DirectDraw | Basic play, ball/paddle input, pause/resume, complete editor save/reload and normal exit; 559 state reads. |
| cnc-ddraw, 640×480 client | The same basic/editor flow passes, including normal exit; 323 state reads. One initial real click acquires wrapper cursor capture. |
| cnc-ddraw, 960×720 client | Three natural life losses, score 222, name editing to `reA`, complete 660-byte ranking persistence, fresh-process reload and two normal exits; 540 reads. |
| Windowed round prefix | A real editor-created single brick clears, score 10/lives 3, then all 400 bytes of original board index 1 match. This prefix does not certify the subsequent focus test or shutdown. |
| Native Windows source build | 141 units compile with the pinned VC4 recipes; all 270 authored functions and 84,968 code bytes match across 53 closures. |

The background checks use private 24-bit Xvfb screens. The windowed client has
origin 160/120 and dimensions 960×720 inside a 1280×960 screen. A read-only SDK
helper establishes those coordinates; XTest requests are scaled from game
coordinates. The complete behavioral assertions are retained. Screenshot
collection is adapted to the larger isolated display.

All observed owned game audio streams route to a muted PulseAudio null sink.
The default sink remains `RDPSink`. The initial basic summary incorrectly looked
for binary name `dxball.exe`; the retained routing audit joins REA process PIDs
to `application.name=dxball.exe` with binary `wine`, identifying 65 game-stream
samples on the silent sink without replaying the game.

## Native build

The native Windows build uses the same source/headers/flags and compiler
10.00.5270. The 141-unit cold compilation is retained; subsequent linker trials
reuse those objects after checking their context and hashes. Nineteen original
CRT members remain explicit and are extracted from the pinned library.

Link 3.00 fails during Pass1 on this Windows 11 host, including with the retained
Wine-produced objects. `WIN7RTM` applied only to the linker child resolves that
failure without administrator rights or compatibility registry changes. An XP
compatibility trial cannot start without elevation and is not used. An exploratory
LLD link also fails and is not part of the delivered build.

| Image | Bytes | SHA-256 |
| --- | ---: | --- |
| October 22 tested VC4 game | 166,400 | `bdd425241ba51d6fe671bb0184b4ad86062326fc9e1eb407d2536235b93df79c` |
| Native Windows rebuild | 166,400 | `526b890eed0e3fe53bd86add6a883770aceff45dbf54e9060aa976940d4c4afd` |

The full comparison finds 18 differing bytes, all within six PE/resource build
timestamp fields. Code, read-only data, game data, imports, board storage and
relocations are identical, with the same section RVAs and sizes. No new native
game launch is inferred from this build/image check. The current game copy is
preserved separately from the newly compiled `build/game/dxball.exe`.

## Windowed profile and sound

The local profile uses [cnc-ddraw v7.1.0.0](https://github.com/FunkyFr3sh/cnc-ddraw/releases/tag/v7.1.0.0),
GDI rendering, `windowed=true`, `fullscreen=false`, `nonexclusive=true`, 4:3
aspect ratio and a 960×720 client. `maxfps=60` caps presentation;
`maxgameticks=-1` leaves the game's own timing in charge. DLL SHA-256:
`85e0f7d530dfda134793a57cb3e76b0287dcc96892ee57162dd68f47283b03a9`.

The original EXE requests an eight-bit exclusive mode. The user initially reports
a fullscreen startup followed by exit, then reports generally successful play
with the windowed setup. This supports the practical configuration change; it
does not prove a specific Windows driver fault.

The temporary silent installation replaced WAV sample data and parked six MIDI
files. Its 26 original WAV and six original MIDI files are now restored and
hash-checked. A running game must restart to reload silent buffers. Windows
master volume, default device and other application volumes are not changed.
Restoring files does not certify physical audio or MIDI playback.

## Activation and timing limits

The exclusive focus fixture does not pass under the windowed wrapper: the
expected inactive/surface-restore state is never observed. The wrapper's
[window procedure](https://github.com/FunkyFr3sh/cnc-ddraw/blob/v7.1.0.0/src/wndproc.c)
filters activation messages when `windowed` is enabled. This explains the
contract mismatch; it is not a pass for the original surface-loss path. The
October 22 original/rebuilt exclusive-mode failures remain unresolved.

Ball slowing is present in the original recovered logic: bonus kind 3 sets the
ball speed to 4; new balls start at 5; the fast effect adds two, capped at 9.
Paddle rebound also recomputes integer velocity from an angle. Frame pacing is
separate: the game moves by fixed per-frame velocities and its software wait
branch targets at least 17 ms between updates.

A passive twenty-second Windows observation records 7,628 active gameplay
samples, speed values 4 and 5, and about 44.57 observed timer updates per second.
The median timer delta is 17 ms; the 95th percentile is 54 ms. This is a limited
game-state cadence observation, with sampling/observer limitations, not GPU
presentation FPS or a synchronized original/rebuilt timing comparison. No 5→4
transition is captured. The first sampling attempt records only menu state.
The user stops further frame-rate investigation and broad background testing;
no frame-pacing fix is claimed.

## Evidence and remaining coverage

| Retained REA process record | Evidence ID |
| --- | --- |
| Built-in basic/editor | `ev_0e809417a43ea8ce90935274507492f81ec95bc613dea50541ede8929356de90` |
| Windowed basic/editor | `ev_948f1a061e1c2a87ba5626f7e1170ebdcbeca70413b87c366c422c2b2397cf94` |
| Windowed game-over/restart | `ev_00c6a4adad4d193270f26e017a7cf78487f39d97410d16769b9dd4dac98b7b76` |
| Round prefix and failed exclusive activation predicate | `ev_6317be4a475d3695da551456f38ba4dbdee875974c2d6f9bd6445633b37d837c` |

Complete responses are under `.analysis/rea/wine-background-20261101/`. Earlier failed fixture adaptations
(cursor acquisition, screenshot dimensions and board-reader shape) are retained
and are not promoted as game failures or successful checks. Directory suffixes retain their original run labels; this report's date follows
the local Europe/Berlin timezone.

The full original fifty-board campaign, every power-up in live play, exclusive
surface recovery and complete native audio/MIDI/frame-pacing coverage remain
unverified. The machine-readable [verification record](../../config/playability-status.json)
keeps each check's date and scope. [Background execution](../agent/BACKGROUND_PLAY.md)
documents the host-isolation requirements.
