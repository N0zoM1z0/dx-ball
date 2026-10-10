# Game lifecycle and mode dispatch

The [main frame dispatcher](exact/MAIN_FRAME.md) is exact at 228 bytes.
It uses ten original direct calls and preserves the complete reset, mode frame
and end-request phases. Five prior exact runtime functions remain exact; only
the two existing dispatch loops were rerun for this source change.

The [game setup/redraw/score restoration](exact/EXACT_RUNTIME_SETUP.md) recovers three
complete controllers / 1,438 original bytes. Initialize (736) and redraw (269)
match all 1,005 bytes; score (433) retains 76 full differences. The 25 separate
sound-load sites, both display binds, live surface rereads, genuine unsigned
converter and consumed lives/restore-span value follow complete instruction
and dependency evidence. Existing 105 selected cases and all 1,510 runtime
owner cases pass without matrix changes. The portable CRT bridge is bounded
to the observed unsigned32 decimal caller; Windows uses its real CRT.

The [round lifecycle restoration](exact/EXACT_LIFECYCLE.md) recovers complete finish,
reset, restart and dispose bodies /911 original bytes. Finish (46), restart (327) and
dispose (112) match all 485 bytes. Reset's full 426-byte emission retains 20 bank-address
scheduling differences. The live paddle selector, consumed signed DWORD average,
real owner calls and ordinary returns follow saved complete REA instructions.
Existing346 lifecycle cases retain their counts; all 1,510 owner cases pass.
Native fixtures forward restored real calls through current copied-image tables,
while dependency implementations and physical hardware remain independently scoped.
The narrative below records the original runtime-owner checkpoint.

The runtime owner follows the gameplay frame outward to its caller and inward
to real initialization, life-loss reset, score drawing, paddle animation and
clock arithmetic. REA's caller/switch evidence identifies `0x0040F4C0` as the
gameplay initializer. The previously suggested `0x0040E570` initializes the
mode-0 intro point table; it is not the gameplay entry. Following actual callers
prevented an unrelated large function from being promoted as game initialization.

Sixteen functions have 1,510 original-x86 differential cases. A continuous
36-frame scenario runs actual initialization, launch, three bottom deaths,
resets, cleanup and dispatch to mode 3. These frames are INCLUDED in the direct
count. That checkpoint had 101 maintained functions and 67,404 direct cases;
the existing 40 exact functions / 4,079 bytes are unchanged. No new exact claims
are made while prioritizing connected core behavior. The products remain
analysis libraries and inspectors; platform integration is still required.

## Entry evidence

The pinned REA MCP/Ghidra session supplies complete function dossiers, including
instructions, incoming calls, switch targets and owned body ranges. Existing
paddle/clock/reset dossiers were reused. The successful session saved 124
Evidence records; raw inline results and snapshots remain private under
`.analysis/rea/runs/`. Clock and mode entry spans contain unowned gaps or tables;
owned instruction counts below are not replaced with their enclosing spans.

| Entry | Maintained function | Owned / span bytes | Direct cases | REA Evidence ID |
| --- | --- | ---: | ---: | --- |
| `0x00403450` | `dxball_current_time` | 128 / 148 | 216 | `ev_d16dbb80ace85b76e9671a6ab40608772eacc9c59210806b5387e23802de2114` |
| `0x004034F0` | `dxball_elapsed` | 76 / 81 | 252 | `ev_dc428fd862c9ce4132ee472c5865486bb43a7deef839266da3a08d839717038f` |
| `0x004036B0` | `dxball_redraw_mode` | 102 / 127 | 7 | `ev_8771ae59b5d8c734a29634ce18f163f6247a0da754feadafe4cd8c76c008538d` |
| `0x00403730` | `dxball_dispatch_frame` | 203 / 228 | 164 | `ev_fe891f4e2c0b787941b66990f074b6e3ad5575dc3b2080a68641c8f9629b6363` |
| `0x004038D0` | `dxball_initialize_mode` | 102 / 127 | 7 | `ev_ddf811bf45fa69ec6ed95204fd1225d97a5588d2ee943b2763d9afbbb4106742` |
| `0x00403950` | `dxball_cleanup_mode` | 137 / 162 | 7 | `ev_edf31fdc7ce974415c981438767f173e4b3666134e6650ef7e7b08a5e8c2cb91` |
| `0x0040F4C0` | `dxball_initialize_game` | 736 / 736 | 19 | `ev_8dcd43fc9cee3e9d52bc3af33b744a2136c00f6ae467d12e84ba774fb3037077` |
| `0x0040F7A0` | `dxball_redraw_game` | 269 / 269 | 24 | `ev_aeece82729d07e73584d5066745d79f92597ed573a1580ab42f3a47dbbf9a3cd` |
| `0x00412EC0` | `dxball_draw_paddle` | 677 / 677 | 332 | `ev_0b4d5d681d951be5b6a69ac1d9d09db3cc965811c767e0b2b4f7296609cc020a` |
| `0x00415880` | `dxball_refresh_score` | 74 / 74 | 63 | `ev_f58f31dcc563b9653e897718b068dc40ec22843226aefb9e5dceaa2f4c366c90` |
| `0x004158D0` | `dxball_draw_score` | 433 / 433 | 63 | `ev_5bd8ce0bb9a8d5a889e6d06e213d148ea1bd2ad54e5d755b82c7705c50cfff4c` |
| `0x00415C10` | `dxball_finish_game` | 46 / 46 | 1 | `ev_38805c95418919116424ecc4729962d9da487a44a77a72a1b06608165afffaab` |
| `0x00415C40` | `dxball_reset_round` | 426 / 426 | 300 | `ev_b1e60404eed3263e429779d493ed38ef1ee1290f2a0e3d31ac348647d03e946f` |
| `0x00415DF0` | `dxball_restart_round` | 327 / 327 | 36 | `ev_7c445e5d515f3a15804b10c82ed404e443f39953efa2f8d7add2449b832c3731` |
| `0x00416430` | `dxball_dispose_game` | 112 / 112 | 9 | `ev_6cd0575b1e5a42d65bb1061f6443204f9f12afdbd651badd502fd0edc5d502b3` |
| `0x004164A0` | `dxball_clear_all_entities` | 106 / 106 | 10 | `ev_ec6f209a3116f545cd612d3e34e16b25c30d54c60708744e4d82883fb47b2eaa` |

## Initialization, redraw and reset

Initialization loads `mbbkgrnd.pcx`, the gameplay and font SBK banks, captures
`bigbolt.pcx` into bank 2, and issues the original 25 WAV loads in order. It
sets font/glyph options, score, three lives, paddle animation and board index,
then executes maintained board initialization and round reset. Surface/region
binding remains an explicit backend operation. Resource operations default to
maintained parsing/capture source; this lifecycle oracle controls their calls
with prepared valid sprite metadata. Actual decoding is independently covered
by the resource owner, not asserted from these call traces.

Redraw clears primary and board surfaces, copies the background using the
original Blt slot and flag, draws score and the column-first board, optionally
requests `PAUSED`, then copies the board to primary and eligible secondary
surfaces. These names are provisional surface roles, not hardware claims.

Round reset counts destructible bricks, redraws the current mode, reloads the
saved palette and requests the original transition before clearing bonus flags.
It stops sound 21 and clears lightning/overlay state. Paddle X uses the OLD
width before sprite 68 supplies the new width. Counters are reset, a real ball
is spawned and attached, then restart/level-change flags are cleared. The
initializer does not itself clear entity queues; valid callers establish that
precondition.

Life-loss restart executes only when its flag equals ONE. An unchanged level
first converts saved RGB values to an integer-average gray while preserving
palette flags, then requests two transitions. A changed level skips the gray
step and first transition. Board/primary surfaces and the auxiliary grid are
cleared, all nine typed queues are cleared from their CURRENT cursors, and
regions reset. Positive lives enter real round reset; exhausted lives wait
thirty frames and request mode 3. Queue cleanup does not reset counters and does
nothing to a queue whose current cursor is null, even if its head is non-null.
Two necessary core cleanup helpers are not independent target-entry claims.

## Clock, paddle and score details

The high-resolution clock divides only `LARGE_INTEGER.LowPart`. Frequency is
truncated to an unsigned divisor by `/1000`; HighPart is deliberately ignored.
A failed frequency query falls back to `timeGetTime`; the counter return value
is ignored. The elapsed test uses unsigned comparisons and wrapped addition:
clock wrap before the start counts as elapsed. Scope excludes frequency below
1000 with a zero divisor and counter failure without written output.

Paddle animation chooses the sprite using the OLD animation frame before a
64-ms timer advances that frame. Laser and attached-ball variants select
different banks of sprite indices and Y offsets. Attached overlays separately
sample raw WinMM time, use a strict deadline comparison, consume RNG only for
a refresh, and read raw time again when setting the 33-ms deadline. Margins use
the observed 0.075/0.03 doubles and truncation. BltFast uses a cropped source
rectangle, while dirty-region width deliberately remains the FULL paddle width.
Referenced constants: `ev_7272023822d4c797b7d12811ae28a53cdbf22d7a8a9620159da89b334a148bdd`.

Score digits are rendered as unsigned decimal. REA's instruction view at
`0x004158A1` uses JBE, so the refresh clamp is also unsigned; a negative signed
view of the same bits exceeds 999,999,999 and resets to zero. Lives restoration
uses at most ten lives before the global count is capped at twenty. After ten icons, drawing
starts a second row, and the original restored rectangle is invalidated.
Text glyph drawing remains a configured boundary; its ordered arguments and
state are checked, not its missing rasterization implementation.

## Dispatcher and oracle boundaries

Mode 1 defaults to maintained initialize/redraw/frame/cleanup functions. The
four other valid modes require supplied callbacks; out-of-range modes perform
no mode operation. Device reinitialization remains a traced dependency: its
controlled callback changes mode/flags, exercising subsequent dispatch order.
The real dispatcher initializes after device reset, clears reset/restore flags,
synchronizes the surface, executes the selected frame, then processes an end
request. Next mode is read AFTER cleanup, and end is cleared AFTER initialization.
Cleanup with nonzero fade preserves palette gating, surface clearing and
resource-release call order before clearing entities.

Five previously pending frame dependencies now default to maintained code:
current time, elapsed test, score refresh, paddle drawing and round restart.
The subsequent [display owner](DISPLAY_OWNER.md) now implements the other
seven frame operations: palette animation, frame waits, region restoration,
effect sprites, last-brick processing/overlay and presentation. The original
restore_surfaces label was corrected to wait_frames; 0x4228D0 is draw_to_primary.
Win32 input/window setup, audio, device
reinitialization, synchronization and non-game modes remain pending. No silent
no-op backend is supplied.

`tests/test_runtime_differential.py` removes exactly those five original-entry
interceptions from the core harness. Original lifecycle, mode, clock, paddle,
score and gameplay bodies execute without patched instructions. Comparison
covers return values, phase-entry state, relevant globals and surface/bank roles,
complete tile/aux/palette buffers, particle pixels, ordered COM/backend calls,
all typed queue roots/cursors/payloads, allocation ownership, poisoned freed
storage and inherited callee-saved-register/stack checks. Native board restoration
and target BltFast cell calls are normalized only at the declared rendering
bridge, retaining all their arguments.

Cases cover all 50 reset boards, width/mouse combinations, clock truncation and
wrap, overlay raw-time/RNG order, score clamp/life bounds, pause/buffer copies,
nine-owner cursor cleanup, restart/fade gates, valid/invalid modes and actual
new-game through game-over dispatch. Arithmetic is bounded and defined, sprite
metadata and list cursors valid, and backend callbacks preserve the tested
state unless explicitly configured. DirectDraw hardware, resource loading inside
these lifecycle cases, glyph rendering, audio and other modes are not established.

The grouped checkpoint reruns the changed core oracle (4,580 cases), adds this
runtime oracle, builds native/MinGW/VC4 source and compares both Windows inspectors
under Wine. Complete inputs for the earlier 76 semantic functions and all 40
exact units are verified unchanged, so their completed reports are reused from
`core-85-40`. No per-function cold replay is performed. Private reports and
identity records are retained under `.analysis/checkpoints/runtime-101-40/`.

## Next connected work

The display owner now connects actual frame/render dependencies. The subsequent
[device owner](DEVICE_OWNER.md) connects fades, fills and recovery. It also
corrects `0x4265AC` / `0x4265B0` to the third sprite bank's count/allocation mode,
replacing the duplicated text-setting globals. The lifecycle oracle now compares
all three banks' metadata without claiming additional entries or cases. Continue
through mode-3 transition/UI and window/input/device/audio startup to a playable
executable.
Investigate mode-0 intro separately when needed; `0x0040E570` is no longer a
candidate gameplay initializer. Independent leaves and byte tuning remain
secondary to the runtime path.

```bash
scripts/repo-python tests/test_runtime_differential.py
scripts/repo-python scripts/ci.py
```
