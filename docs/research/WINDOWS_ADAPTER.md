# Windows adapter integration

The Windows adapter now binds the maintained mode/gameplay/audio controllers
to real Win32, DirectDraw, DirectSound and WinMM calls. Both VC4 and MinGW build
experimental game EXEs. A bounded Wine check runs the original and both source
builds through the opening screen, menu, first board, return to menu and clean
shutdown. Further state-observed controls now cover ball motion, paddle input,
pause/resume and editor persistence/exit. Complete gameplay and physical device
fidelity remain unverified.

Before calling real DLLs, `tests/test_windows_abi.py` compiles the shared owner
headers against the actual i686 SDKs and executes three console probes under
Wine. The core probe builds with both the pinned VC4 compiler/SDK and MinGW;
the DirectX probe uses MinGW's SDK, because the pinned VC4 SDK lacks DirectX
headers and import libraries. No vendor header, source layout or compiler
binary is patched to satisfy a probe.

The checks corroborate existing REA observations in
[platform evidence](PLATFORM_OWNER.md), [resource evidence](RESOURCE_OWNER.md),
[music evidence](MIDI_OWNER.md) and [sound evidence](SOUND_OWNER.md). They add no
original-function acceptance, hardware behavior or playable-game claim. No new
binary query was needed; saved dossiers supplied the target-side contracts.

| Record | Verified i686 bytes | Relevant boundary |
| --- | ---: | --- |
| Pointer / handle / window result | 4 | Win32 and COM arguments |
| MSG | 28 | Message queue and dispatch |
| WNDCLASSA | 40 | Callback registration |
| SECURITY_ATTRIBUTES | 12 | Instance semaphore |
| OSVERSIONINFOA | 148 | Startup compatibility selection |
| LARGE_INTEGER | 8 | Clock frequency/counter |
| MIDIHDR | 64 | Stream buffers and callback user state |
| MIDIPROPTIMEDIV | 8 | Music time division |
| Sound record | 36 | Known fields; original allocation requests 37 |
| DSBUFFERDESC1 | 20 | Observed DirectSound descriptor |
| Modern DSBUFFERDESC | 36 | Extra GUID tail; different from the observed descriptor |
| DDSURFACEDESC | 108 | Surface creation and locks |
| DDBLTFX | 100 | Color fills |

Compile-time assertions compare individual message, window, MIDI and surface
field offsets with SDK definitions. They also check the called DirectDraw and
DirectSound COM slot positions, including the complete twenty-one-slot sound
buffer interface and Restore at slot 20. The resulting JSON records agree
between the VC4 and MinGW core probes. These checks require 32-bit pointers;
they do not imply that the original interfaces can receive a growing 64-bit
host record unchanged.

Run the probes after installing the existing project prerequisites:

```bash
scripts/repo-python tests/test_windows_abi.py
```

The report at `build/reports/windows-abi.json` records source/header identities,
the pinned compiler/SDK identities, installed MinGW compiler and relevant SDK
header hashes, executable hashes, flags and observed output. The complete
private CI includes this check. Public CI checks portable and i686 Windows
compilation plus recorded metadata without requiring private originals/tools.

Wine/Xvfb can append its display-shutdown notice to console stdout after the
probe exits. The harness preserves the full log and permits that specific
trailing notice; unexpected text, a nonzero process result or differing JSON
fails the check.

## Real bindings and products

`src/windows_entry.c` supplies the SDK WinMain entry and calls the maintained
WinMain controller after `dxball_bind_windows()` and one call to the
[recovered heap initializer](ALLOCATOR_OWNER.md). Binding installs typed heap
imports but does not initialize or reset the heap; the Windows entry ignores
the initializer return, matching the observed original startup edge. `src/windows_adapter.c`
translates the existing dependency tables into actual SDK calls: the 27 window
operations, timers/cursor positioning, file/mapping/allocation APIs, DirectX
factories and MIDI streaming. Typed Win32 and five-parameter WinMM callback
trampolines retain the observed i686 calling conventions. MIDI header storage
is shared with the real SDK; these bindings are deliberately restricted to
32-bit pointers.

DirectDrawCreate/DirectSoundCreate use LoadLibrary/GetProcAddress and the
recovered stdcall signatures. DLLs stay loaded through process teardown,
including possible asynchronous callbacks. A missing DirectSound factory
feeds the original no-card failure code into its maintained dialog controller.
No DirectX library, header or pinned compiler was patched. SDK-backed adapter
glue is separate from the 214 accepted original functions and makes no new
exact claim. Saved REA dossiers in the owner documents supplied the contracts;
this step did not require another Ghidra import.

The VC4 linker produces `build/vc40/dxball.exe` using the same maintained C
owners and user32/gdi32/winmm imports. CMake's i686 Windows build produces
`build/windows-i686/dxball.exe` beside `libdxball_core.dll`. Native builds retain
the analysis library/inspectors. Private game builds now link the two verified
original resources. An independent SDK probe checks the complete payloads and
decoded icon while preserving the original startup identifier mismatch; see
[embedded resource evidence](EMBEDDED_RESOURCES.md). Live class/shell icon
delivery remains outside that probe.

```bash
scripts/repo-python scripts/build-legacy.py
scripts/repo-python scripts/build-windows.py
scripts/repo-python scripts/run-windows.py --profile vc40 --prepare-only
scripts/repo-python scripts/run-windows.py --profile vc40
```

Preparation verifies all 49 asset-manifest hashes, copies data into
`build/runtime/<profile>/` and copies the selected source-built EXE. Manual
runs preserve existing working scores/boards. Originals are never the working
directory. `--prepare-only` also provides a folder that can be transferred to
a suitable Windows machine for further checks.

## Observed Wine coverage

```bash
scripts/repo-python tests/test_windows_runtime.py
```

This optional check requires Wine32, Xvfb, xdotool and ImageMagick in addition
to the existing build prerequisites. It runs original, VC4 and MinGW copies
sequentially on one allowed CPU, under the project session lock. Actual
screenshots, Wine logs, executable/DLL hashes, source/input identities and
unmodified original hashes are retained in `build/reports/windows-runtime*`.
No window, COM, file or audio API is replaced by an oracle hook in these runs.

All three runs create a visible 640x480 window, change from opening screen to
menu on a key, reach the reviewed first-board fixture on a held click, return
to menu on Escape and exit with code zero on the next Escape. The first-board
tile rectangle `[20,110)..[620,275)` contains 99,000 pixels; the observed VC4
and MinGW captures each have zero differences against the original control
there. Whole-screen counts retain differences from unsynchronized frames;
these observations do not upgrade function-level exact acceptance or establish
frame-equivalent rendering across the game.

The initial 800x600x24 environment could not satisfy the original 640x480x8
display-mode request. The 640x480x8 environment does, but its palette artifacts
also appear in the original control. The test waits for nonblank presentation
before forcing X focus: changing focus during initialization left the original
control at a blank window. That is a harness limitation, not a source fix.
The Wine logs also report an unavailable ALSA sequencer. Physical audio and
asynchronous MIDI buffer delivery are therefore still unverified. Focus/lost-
surface recovery, extended gameplay and all-board behavior need further checks.

`scripts/clean-local.py` journals removal of resettable `probe-*` working
copies after their reports are retained. Manual run directories and their
scores/editor saves are preserved. Owner sources, declared semantic/exact
inputs and the native analysis-library hash did not change in this adapter
batch; the complete accepted sound checkpoint's oracles remain reusable.

## State-observed ball and editor controls

```bash
scripts/repo-python tests/test_windows_play.py
```

The second real-runtime harness runs the original, VC4 and MinGW versions
through the same input script. It observes an initialized attached ball,
mouse-positioned paddle at x480 and x200, release by left click, changing ball
coordinates, frozen ball fields over a 0.5-second pause, and resumed motion.
Actual Win32/DirectX calls and maintained frame bodies execute throughout.
Random trajectories are not synchronized or claimed equal between runs.

It then enters the editor with Control-F1, clears a working board, selects tile
2 and holds Control while painting its first two cells. S writes the whole bank:
the expected 20,000 bytes preserve the other 49 original boards. Next/previous
board selection, Backspace, L and another S are checked. The second save must
recreate a deliberately removed probe file, avoiding a stale-file success. All
three saved banks have SHA-256
`b88441eb5e06676a106501a60a450b8046fa7b880e8f53ffe5f556ae75a42cd2`.
Both editor return to menu and the subsequent zero-code process exit are
observed, with the visible game window gone. All 49 originals are reverified.

After the score, game-over, editor, board and menu recovery through `732731b`,
the unchanged `observe('vc40', ...)` flow passes again on the current VC4 EXE.
It records 77 read-only state observations, all five existing captures, the
same saved-bank hash and exit code zero; all 49 original assets remain unchanged.
The first attempt stopped before observation because the full-build receipt
still described an older map. The reader now accepts the focused link receipt
only after verifying the actual EXE/map, all 35 objects and their consumed
inputs, and the resource object/inputs. Five simulated stale source, object,
resource, map and EXE identities are rejected without changing those inputs.
The previous full-build identity checks remain supported. No gameplay input or
assertion was changed. Receipts, states, captures and the failed attempt are
retained in `.analysis/windows-play-menu-732731b/`.

This selection does not rerun the previous original or MinGW controls, compare
synchronized frames/trajectories, or establish audio/MIDI or all-board fidelity.
It verifies this source product's ball/pause/editor/exit path independently of
the native fixture. Function acceptance stays at 164 exact functions; runtime
observations do not promote candidates.

The previous exploratory editor session ended without a verified exit. The
original control now establishes that mode 0 can already be selected while
`end_requested` remains 1 during its initializer/fade; it becomes 0 on completion.
The new harness waits for that completed transition before its next input.
Pause also sets its flag before the display fade completes, so screenshot
capture waits for actual nonblank presentation. No owner body was altered to
make either transition pass. Failed harness attempts remain retained privately.

`tests/windows_state_reader.c` uses FindWindow/GetWindowThreadProcessId and
ReadProcessMemory with query/read rights. It neither writes target memory nor
hooks code or suspends threads. Original addresses reuse the reviewed globals
in the existing board/platform/core/power-up/editor oracles. Source-built VC4
addresses come from its generated linker map, whose hash is recorded; MinGW
addresses resolve the actual DLL exports relative to its remote module base.
Only the observer's own DLL mapping is loaded without initialization. Ball
fields follow the already recovered i686 list/node layout. Reads are sequential
and do not constitute an atomic frame snapshot.

VC4 builds now retain `dxball.map`; this changes build metadata, with no source
owner/exact-unit change. The modern SDK reader builds as strict C90 at O3 in
the private harness and as a Windows CMake target checked by public CI. It is
a testing utility, with no original-function acceptance claim. Complete states,
screenshots, Wine logs, source/reader/product/map hashes and saved-bank hashes
survive in `build/reports/windows-play*`. Private CI runs both runtime harnesses.

Wine recreates a deleted uppercase `DEFAULT.BDS` as lowercase `default.bds`.
Working-copy preparation now respects Windows filename equivalence: manual
runs preserve an existing save regardless of case, while probe reset removes
superseded case aliases. Reports resolve the actual saved filename. The
immutable imported assets are not renamed or modified.

These controls initially left real game-over/ranking input, focus/surface recovery,
complete level progression, live class/shell icons and actual MIDI/audio delivery
open. Function acceptance remains 214 maintained /95,873 direct cases /40
exact functions, separate from these three actual Windows runs.

## Current VC4 play and complete captured frames

After source checkpoint `4c24034`, the unchanged existing
`observe('original', ...)` and `observe('vc40', ...)` flows pass on the original
and current VC4 EXEs. The current VC4 SHA-256 is
`637790d2a5d8badb386363d87dc839b1c111a058a886588730d700366819583e`;
full receipts, 87 read-only observations per process, ten captures, saved banks
and logs are retained in `.analysis/windows-play-current-render/`. The actual
workflow durations are 20.39 seconds original and 19.79 seconds VC4. These are
runtime workflow measurements, not REA latency, CPU usage or token benchmarks.
Only the read-only observer is compiled once; no game source or provider runs.

Both runs exercise mouse movement, ball release/motion, pause stability and
resume, editor clearing/tile selection/Control painting, full-bank save,
board selection, reload/recreation and clean menu/process exit. Both persisted
banks retain the previously established `b88441eb...` full-bank hash. All 49
original assets remain unchanged. The input receipt includes the actual inputs
of all 36 game objects, including C++ owners omitted by the harness's older
`*.[ch]` discovery. MinGW is not executed in this selection.

The ten unaltered captures are compared over every decoded 640 by 480 RGB
pixel. Opening, editor and editor-reload each have zero differences and equal
PNG hashes. Pause has 7,472 differences; return-menu has 3,445. Every pause
difference maps through the original default board's tile8 cells to original
MBALL2 sprite9 color indices224..231, including the loader's vertical row
reversal. Every menu difference maps to MAINMENU.PCX indices48..63. No other
full-frame pixel differs in either scene.

The menu's complete 14,289 asset pixels in48..63 match right rotations11 and9
of the original resource palette for original and VC4 respectively, with zero
mismatches. Its checkerball image uses palette animation. The paused frame also
continues palette animation224..231 every elapsed32ms while ball state stays
frozen. This establishes the menu palette-phase explanation and supports the
same explanation for pause; live pause palettes and matching phases are not
observed. Sequential state reads and captures are not atomic or synchronized.
Identical paused ball fields do not by themselves establish identical RGB
frames. No screenshots are cropped, recolored or normalized for equality.

This is bounded current-product evidence for the played/editor flow and three
complete captured frames. It adds no function acceptance or claim about an
entire campaign, equal animation timing, physical Windows display, hardware
sound or asynchronous MIDI delivery. Both controls share Wine/Xvfb's 8-bit
palette environment. Preserve the differing images and the indexed-resource
localization when following up on render fidelity.

## Current complete menu frames at naturally equal phases

A focused follow-up observes the original executable and the current VC4 game
from the PCX packet-loop checkpoint. Real opening input reaches menu mode zero;
the existing SDK reader observes that mode before and after each capture
interval. Each process supplies 32 unmodified complete 640 by 480 captures,
with 31 distinct RGB frames. Five original/current pairs match over all
307,200 decoded pixels, independently comparing every RGB byte after selecting
equal hashes. No cropping, recoloring or palette normalization is applied.

This strengthens the palette-phase explanation with complete equal menu frames
from the current product. It does not prove synchronized animation clocks:
matching frames occur naturally in separate asynchronous samples. It also
does not establish pause, physical Windows display, audio/MIDI or whole-game
fidelity. Both controls use Wine and the same Xvfb 8-bit environment.

The current VC4 executable identity is
`0302cf38a82c7d9843af135e2c054b26d2dd5c7f1d12d53199f1b1584c3a4b28`.
Both games exit normally with code zero. All 49 originals and the four current
products remain unchanged. No compiler or game build is needed. Private
complete frames, state observations, input identities and paired comparisons
are retained in `.analysis/menu-palette-phase/report.json`; the two temporary
working copies are removed only after hash verification. This is direct
runtime observation, without a new REA Evidence claim or function acceptance.

## Current attached-ball pause frames

The next focused observation uses actual opening/play/P/mouse input to pause
the first attached ball. Both original and current VC4 controls have paddle
x320, ball x320/y441, score zero and three lives. Complete ball observations
are identical across controls and unchanged before and after each capture
interval. Each process supplies 32 complete captures covering eight distinct
RGB frames. Every sampled distinct frame has an equal counterpart: all eight
pairs compare every decoded RGB byte, with zero differing pixels across
307,200 pixels per pair. Screenshots are not modified or phase-normalized.

Real Space input resumes; Escape returns to menu and another Escape exits
normally. Read-only state, asset identities and current product hashes remain
verified. The temporary working copies are removed after hash checks.
This proves the sampled attached-ball pause scene under Wine/Xvfb. It does
not establish moving-ball trajectory parity, synchronized clocks, physical
display/audio/MIDI or whole-campaign fidelity.

REA 6.4 process capture retains this run as controlled-replay Evidence
`ev_d5cefc4042fda9ea205b51380ca4a011c3a620d5761b675ca9eca1b9b7406791`.
The child exits zero and the after-filesystem checkpoint hashes the complete
52,368-byte runtime report. Process sampling reaches the declared 64-sample
cap; its partial coverage is retained without implying a complete process
history. Terminal frames are not screenshot frames. Executable identity is
a prelaunch path sample, with the recorder's atomic-binding limitation;
the child report separately binds the original/current game file hashes.

Complete unique PNGs, state/scene report, scenario, recorder Evidence and
progress are in `.analysis/pause-palette-phase/`. No compiler, game build or
full historical replay is needed. Existing exact/source/origin counts remain
unchanged; no new function acceptance follows from these sampled frames.

## Current first released ball

The current VC4 first-flight follow-up matches 89 complete sampled ball vectors
in order against the original. Both clear tile 291 from 11 to 0, gain ten points
and lose the first ball after mouse input moves the paddle away. Complete board
effects, new attached-ball reset, menu and zero exits agree. The two unpaired
samples remain explicit; asynchronous sampling does not prove every frame or
clock parity. The persistent read-only reader now emits all thirteen already-read
ball fields. See [first ball flight](FIRST_BALL_FLIGHT.md) for complete raw stream
identities, actual recursive SDK dependencies, the trajectory and REA process
Evidence. No game rebuild or function-count promotion is needed.

## Natural life loss and persisted rankings

`tests/test_windows_gameover.py` reuses the reviewed game-over state addresses
and fifteen-record layout from the REA-backed game-over dossier/oracle. Mouse
input releases each fresh attached ball, then moves the paddle away from the
ball. Actual collisions, score updates, retirement, life-loss resets and mode
dispatch run until lives decrease from 3 to 2 to 1 to 0 and mode 3 completes.
There are no target memory writes, injected calls or score/life fixtures.

Real keys enter `rex`, remove the last character with Backspace, and append
Shift-A to produce `reA`. Enter submits the earned score. The independent
expectation inserts ahead of equal scores, shifts terminated names while
preserving destination tails, and checks all 660 persisted bytes. The observer
also reads the entire score table. After returning to menu and exiting with
code zero, a fresh process opens the same working copy; its complete score
table and unchanged file must equal the saved result, then it exits normally.
Original/VC4/MinGW control runs pass these paths. Observed trajectories and
scores may differ; each complete file is checked against its own earned score.

The extended SDK reader supports a bounded 660-byte hexadecimal score-table
read, alongside its existing scalar/ball observations. Shared input/SDK identity
helpers let either harness run independently without requiring another test's
report. Private CI checks startup, play/editor and natural game-over in sequence;
public CI compiles the strict C90 reader and actual Windows game. Reports retain
before/after score files, live states, screenshots and compiler/map identities
under `build/reports/windows-gameover*`.

The original name-entry scene has only two visible colors on this 8-bit
Wine/Xvfb palette; the earlier four-color capture heuristic rejected its visible
High Score title. That attempt is retained, and this scene now accepts two-color
captures. This does not establish text/palette fidelity: actual state and file
bytes provide the game-over acceptance. One earlier original launch exited
before a window without a diagnostic; subsequent complete original controls
passed, and that incomplete launch remains retained rather than classified as
a source failure or a proven environment defect.

Focus/surface recovery, complete level progression, live class/shell icons and
physical audio/asynchronous MIDI remain open. No original-function acceptance
or exact-match count changes arise from this runtime observation work.


## Real round advance and retained focus failures

After the exact round-transition recovery in `9ec72c3`, the unchanged
`observe('vc40', ...)` selection passes again with 71 read-only state reads.
The editor-created single brick clears naturally, score becomes ten, and
original board1 loads with all 400 expected bytes, 222 destructible bricks,
three lives and an attached ball. The complete edited bank and zero-code
shutdown pass; all 49 originals remain unchanged. Private artifacts are in
`.analysis/windows-round-9ec72c3/`. The previous original/MinGW controls were
not rerun, and focus recovery was not requested. Sequential reads, terminal
board50, audio/MIDI and full-game/image fidelity retain their existing limits.

`tests/test_windows_round.py` now connects real editor input to brick collision,
round advance, complete board loading and zero-code menu/exit controls in the
original, VC4 and MinGW builds. The SDK observer can read all 400 tile bytes;
the expected 20,000-byte bank is checked before gameplay and after exit. Private
CI includes this successful round family. See [round/focus evidence](ROUND_FOCUS_RUNTIME.md)
for the exact input path, captured REA process Evidence and acceptance limits.

The optional `--focus-recovery` diagnostic opens an ordinary SDK peer window;
its Enter key restores/activates the game and Escape closes that peer. Memory
observations still use query/read rights only. Original focus recovery stalls
under this Wine9/Xvfb8-bit setup after temporary motion. Its retained API warnings
show a lost-surface Lock retry, with a valid 108-byte descriptor. Successful
focus recovery stays open; these negative controls are excluded from passing
private CI. A successful REA recorder can describe a failed child, and the
capture helper propagates that child exit.


The [independent DirectDraw SDK follow-up](ROUND_FOCUS_RUNTIME.md#independent-directdraw-status-check)
now distinguishes lost-status reporting from actual restoration capability.
Both default/GDI runs report loss through IsLost/Lock while GetBltStatus returns
success. Restoring the probe-owned primary and working surfaces makes them
usable again. This explains the original gate's missed recovery as a supported
inference; no target API return was intercepted and no game body was changed.
Private CI includes the standalone observation and public CI compiles its C90
SDK target. The same stable batch reruns all five real Windows game harnesses.


The clock API follow-up passes the unchanged existing VC4 ball/pause/editor/
exit observation with 81 read-only states and five captures. The new product
uses independent WinMM/kernel clock bindings; ball release/movement, paddle
input, pause/resume, editor painting/save/reload, the established whole-bank
hash and normal exit pass. All 49 originals remain unchanged. Receipts are
in `.analysis/windows-play-clock-api/`; source/input identities identify the
working-tree product based on `8a2f125`. Original/MinGW prior play controls
were not rerun. This is a sequential read-only Wine/Xvfb observation, with no
synchronized frame, physical audio/MIDI or full-game fidelity claim.


The sprite-lifetime follow-up passes the unchanged VC4 ball/pause/editor/exit
observation with 83 read-only states and five captures. The new product uses
live sprite records at COM boundaries and preserves the pre-Lock upload stride;
startup, ball and paddle input, pause/resume, editor save/reload, the established
whole-bank hash and zero-code exit pass. All 49 originals remain unchanged.
Receipts are in `.analysis/windows-play-sprite-lifetime/`; source/input identities
identify the working-tree product based on `6f058b2`. Prior original/MinGW play
controls were not rerun. Sequential Wine/Xvfb reads do not establish synchronized
pixels, physical audio/MIDI or full-game fidelity.
