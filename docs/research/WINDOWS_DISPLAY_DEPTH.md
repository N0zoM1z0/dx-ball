# Correct Wine display depth and MinGW runtime deployment

The missing filled text/title pixels in prior captures were reproduced in the
unmodified original on an eight-bit Xvfb screen. Holding resolution at 640 by
480 and changing the host screen to 24 bits restores complete colored letters
and title edges. The original still requests its original eight-bit DirectDraw
mode. The old failed 800-by-600 24-bit run changed resolution too; it did not
establish that a 24-bit host screen was unsupported.

The focused original opening check records 41 read-only SDK observations,
captures the complete rendered frame, enters the menu and exits with status
zero. Visual review confirms filled letters. Within the unchanged text rectangle
`[15,165)..[615,355)`, nonblack pixels rise from 3,632 in the historical eight-bit
capture to 26,858 in the new original control. These counts support the visual
observation; they are not a general font-correctness test. The historical source
and original eight-bit opening buffers were independently equal. Images are
never altered or repaired.

Both maintained Windows runtime/play checks now default to 640-by-480 24-bit
Xvfb. `--display-depth 8` retains historical reproduction. Headless manual play:

```bash
xvfb-run -a -s '-screen 0 640x480x24' scripts/repo-python scripts/run-windows.py --profile vc40
```

## Actual input acknowledgement

The first extended original control reached gameplay, pause/resume and editor
entry, but its fixed 0.25-second tile-selection press was missed before release.
The game remained active with selected tile 1 and correctly observed pointer
coordinates. This is retained as a failed attempt; no game-source change follows.

The play check now holds that real mouse press until the read-only observer sees
tile 2 selected, then waits for release consumption. CTRL painting waits for the
first and second actual tile writes before moving/releasing. The positions,
two-tile fixture, complete saved-bank expectation and game calls stay the same.
This supports slow presentation without substituting state writes or API hooks.
All 49 original assets remain unchanged.

## Missing MinGW runtime dependency

The original and VC4 extended controls passed. MinGW exited before a window:
the actual core DLL imported `libwinpthread-1.dll`, absent from the isolated
runtime and Wine system directory. The POSIX MinGW toolchain's statically linked
C++ support had pulled in a dynamic pthread dependency. The prior flags covered
GCC and C++ support but left that dependency unresolved at deployment.

The MinGW-only core link now also uses `-static`. The complete emitted core import
inventory contains only `ddraw.dll`, `dsound.dll`, `KERNEL32.dll` and `msvcrt.dll`;
the game retains its Windows imports and `libdxball_core.dll`. All 43 existing
MinGW object hashes remain unchanged: one selected relink, zero source
compilations. Native and VC4 products remain byte-identical. No extra runtime
DLL is needed in the tested isolated game directory.

Only MinGW is rerun after this repair; the successful original/VC4 controls are
retained. A consumer recovers their completed observations, five captures and
full saved banks from the terminated three-profile attempt. The pass messages
were emitted only after the maintained observer asserted zero exit and window
removal. The failed MinGW launch and all preceding partial evidence survive.

## Completed play observations and remaining limits

| Profile | Read-only states | Captures | Result |
| --- | ---: | ---: | --- |
| Original | 103 | 5 | Ball movement/release, pause/resume, editor, save/load, zero exit |
| VC4 source | 115 | 5 | Same complete path and two-cell saved-bank bytes |
| Repaired MinGW source | 116 | 5 | Same complete path and two-cell saved-bank bytes |

All three complete saved banks hash to
`b88441eb5e06676a106501a60a450b8046fa7b880e8f53ffe5f556ae75a42cd2`.
Both rebuilt opening and initial editor RGB buffers equal the original across
all 307,200 pixels. Text and the PAUSED label visibly render correctly.
Editor-reload captures retain 186 differing pixels per rebuilt profile, entirely
within the original red/white pointer at inclusive bounds `(65,57)..(86,76)`.
That presentation phase is not synchronized; no source-defect or complete
reload-frame equivalence claim follows. Pause and return-menu frames also
remain unsynchronized (18,111 pause differences; 18,344 VC4 and 13,446 MinGW
return-menu differences). No pixels are masked from these counts.

The SDK reader is reused by complete compiler/header/product identity; zero
reader or legacy source compilations, owner-oracle replays or new REA requests.
Exact counts remain 206 functions /44,406 code /136 metadata bytes. Source stays
285 present /270 authored, semantic acceptance 249, origins 117 runtime /42
generated /99 unknown. Historical semantic scopes/cases remain unchanged after
refreshing their CMake input inventory for the MinGW-only link option.
Physical display/audio, asynchronous MIDI, synchronized moving frames, full
campaign fidelity and original source identity remain unproved.

Private receipts/captures: `.analysis/windows-glyph-display-depth/`. Current
product receipt: `product-verification.json`. Seal:
`.analysis/checkpoints/windows-glyph-display-depth-285-206/sha256.json`.
Cleanup removes only recorded resettable probe copies after retaining unique
exit files, then deduplicates immutable copies against the immediately preceding
random-runtime seal. Public/current files remain independent of archives.
