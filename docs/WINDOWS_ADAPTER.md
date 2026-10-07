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
WinMain controller after `dxball_bind_windows()`. `src/windows_adapter.c`
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
the analysis library/inspectors. Original embedded resource fidelity, including
the icon, remains pending; a successful window does not prove those resources.

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

These controls leave real game-over/ranking input, focus/surface recovery,
complete level progression, embedded resources and actual MIDI/audio delivery
open. Function acceptance remains 214 maintained /95,873 direct cases /40
exact functions, separate from these three actual Windows runs.
