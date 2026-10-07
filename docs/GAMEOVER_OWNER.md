# Game-over and high-score evidence

REA 4.1.0 with Ghidra 12.1.4 follows actual mode 3 from initialization and
redraw into the per-frame controller, key routing, name editing and persisted
ranking insertion. Eight maintained entries connect to existing mode dispatch,
UI/glyph, pixel-line, dirty-region, palette and clock bodies. The controller
family uses one shared C implementation for native, MinGW i686 and pinned VC4.
The subsequent [editor checkpoint](EDITOR_OWNER.md) maintains mode 2.
The later [Windows adapter](WINDOWS_ADAPTER.md) binds real APIs and checks
natural life loss, name entry and ranking persistence in experimental game
EXEs; complete-game and physical audio fidelity remain pending.

## Entries and retained observations

| Address | Maintained entry | Owned/span bytes | Direct cases | REA Evidence ID |
| --- | --- | ---: | ---: | --- |
| `0x00406440` | `initialize_game_over` | 321/321 | 24 | `ev_e451d766f08e8c36f876fdfe8bef512825c87dfeb0863a987a730e60bbf46eac` |
| `0x00406590` | `redraw_game_over` | 414/414 | 36 | `ev_4b2af1f701976b189e8daa926e6081b26294ae671955a84d7652b6cec1785467` |
| `0x00406730` | `game_over_frame` | 696/696 | 192 | `ev_54d614d0b6c8bc8c57c1d6d1c398571395adc17f9cf4bab066210d8833dab437` |
| `0x00407370` | `dispose_game_over` | 175/175 | 16 | `ev_459723b74e3925d93b9442ca92f71a9d5f2285a7801f3ece0d689c970074aab0` |
| `0x004069F0` | `game_over_key` | 153/302 | 1,024 | `ev_d2e980af80173ecba1f8fda0f2ff3584911f60bd2228fcc9b408d17c9049f32b` |
| `0x00406B20` | `draw_high_scores` | 404/404 | 17 | `ev_a42b5c952ba3c544d58bf1b3c0c2456c9e13f6149d7090c32e2952888fd6ff3e` |
| `0x00406D20` | `insert_high_score` | 446/446 | 102 | `ev_b8a8525ffa6ad9d00db1a74e35f1aabae8aa6ff5e8823367769dd78876448eb6` |
| `0x004071C0` | `edit_score_name` | 421/421 | 5,120 | `ev_8211b56370f2de5643ba3e9d8f5a733fac0c5018dfcbf8bfbf8b84fae4daefb9` |

The key controller owns 153 bytes in three inclusive ranges inside a 302-byte
span; intervening switch data is excluded from owned instructions. All other
entries are contiguous. Imported candidate spans were reconciled with REA body
ranges. Evidence IDs are static observations, not execution proof; unresolved
indirect flows and prototype inference retain their limitations.

One interactive session retains thirteen new results: eight authored dossiers,
three read-bytes results and two CRT conversion dossiers. Open took 17.9 seconds;
lazy first-query analysis took 44.0 seconds, with later dossiers below 0.51 seconds.
Explicit close saved 211 cumulative Evidence records in the reusable snapshot.
Complete results are in the closed 13-44 private archive.

## State, initialization and display

`src/gameover.c` owns name position at `0x426698`, unsigned blink tick at
`0x42669C`, selected rank at `0x4266A0`, cursor visibility at `0x4266A4`, ranking
view at `0x42693C`, name-entry state at `0x426940` and the 40-byte name buffer at
`0x426948`. Scores reuse the fifteen 44-byte records in `src/startup.c` at
`0x4266A8`. Eligibility compares the last record's unsigned score at `0x426938`
with the existing game score at `0x422D18`; no duplicate score or cursor globals
are introduced. The menu/splash cursor coordinates are shared here too.

Initialization resets regions, loads `highscor.pcx`, `mainmenu.sbk`,
`sysfont.sbk` and `acker-gs.mds`, binds the observed surfaces, then re-reads
scores. It clears only the first name byte, preserving the buffer tail. Name
position, blink tick and visibility become zero; selected rank becomes -1.
Eligibility includes an equal lowest score. Ranking view starts at zero,
followed by actual redraw and fade-in. Untouched globals initially equal zero,
corroborated by retained reads and unmodified original image execution.

Redraw clears and copies the observed surfaces. Ranking view exactly equal to
1 takes precedence; otherwise name-entry exactly equal to 1 displays the input
prompt, and other states display the game score as unsigned decimal. The ranking
body draws fifteen names and right-aligned decimal scores twenty pixels apart.
Only the selected valid row receives four original pixel lines in color 200.
Name copying and drawing require terminated strings within their record bounds.

## Frame and input behavior

Each frame waits only when draw-to-primary is nonzero, restores regions and
clamps the shared cursor X to 8..599 and Y only at its upper bound 447. Name-entry
state exactly equal to 1 selects the display surface, draws the current name
and, for visibility exactly equal to 1, an underscore after its measured width.
The underscore is drawn before the 300 ms blink gate toggles visibility; current
tick is stored after the toggle. Region `(0,210,639,234)` is invalidated.
Presentation occurs only for draw-to-primary zero. Ranking view exactly equal
to 1 with entry state exactly zero uses the same tick for 100 ms palette rotation
of entries 200..207. Unsigned clock wrap and equality thresholds are preserved.

A left click while not entering a name first fades out, loads the ranking
background, redraws and fades in. A subsequent click requests menu mode 0.
While entering a name it waits one frame; the action is then cleared. Right
click clears without transition. The key controller's many empty switch cases
are genuine no-ops outside entry state exactly equal to 1; instruction ranges
confirm the pseudocode rather than implying missing key actions.

Name entry accepts only space, digits and uppercase virtual-key A..Z. Letters
become lowercase unless Shift equals exactly 1, when uppercase is restored.
Lowercase byte keys and other bytes are ignored. Backspace removes the last
character only for positive position. Position below 30 appends a character and
terminator; at or above 30 an accepted character waits one frame instead.
Enter inserts the name/score, stores the resulting rank, disables name entry,
fades out, switches ranking view on, reloads, redraws and fades in. It preserves
the old name buffer and position. Cleanup with fade zero does nothing; nonzero
fade clears surfaces and releases banks, sounds and music in original order.

## Ranking and file persistence

Insertion first executes the maintained score-reader body against the same
controlled CRT file APIs. A score below the reloaded last record returns -1
without access/write calls. Otherwise it scans backwards while existing scores
are less than or equal to the new unsigned score. Equal scores therefore insert
before existing equals. It shifts names with `strcpy` and copies each score
separately, retaining bytes after each destination's terminator. A whole-record
memcpy would change those tails and fail the oracle. The new name and score
are then written into the selected row.

Only `access("score.dat", 2) == 0` attempts `fopen(..., "wb")`. Successful open
writes fifteen elements of size 44 and closes; write and close results are
ignored. Access/open failures keep the in-memory insertion and returned rank.
Read-open failure, empty/short/full reads and stale/closed shared FILE state
retain original behavior. The FILE slot remains shared with board I/O.

## Independent validation and limits

`tests/test_gameover_differential.py` executes all eight unmodified original
entries for **6,531 direct cases**. It covers all key bytes, Shift equality,
positions 0/1/29/30/31, every rank boundary, equal-score ordering, unsigned score
extremes, file failures, short reads, ignored write results, all valid ranking
highlights and mode/state gates. Reload fixtures deliberately differ from the
in-memory table, covering eligibility changes, changed placement, ties, partial
overwrite and failed-open preservation. It compares full score/name arrays with poison
tails, complete file output, palette flags, controlled pixel buffers and row
padding, dirty arrays, font/bank state, globals and ordered effects. File calls
also compare state before each operation, independently checking mutation order.

Another **76 checks are separate connected evidence**. Four scenarios vary
primary setting and writable/read-only persistence. Actual finish-game requests
mode 3, actual frame dispatch runs game cleanup/initialization, four game-over
frames execute, actual key routing edits and submits a name, four ranking frames
execute, then mouse/frame dispatch returns to actual menu mode 0. Production
mode and key tables are checked before providers are installed. Modes 0, 1,
3 and 4 default to maintained source at this checkpoint; the subsequent
[editor checkpoint](EDITOR_OWNER.md) adds mode 2.

Original CRT unsigned formatting, `strcpy`, strlen and default C-locale case
conversion execute rather than being replaced with a reference algorithm.
The conversion dossiers contain conflicting FID base names and a Visual Studio
1998 library label: these are recognition hints, not compiler-version proof.
Nondefault locale mapping is outside this acceptance. Valid bounded terminated
storage, finite device scripts and nonoverflowing arithmetic are required.
COM callbacks supply pixels and compare meaningful descriptors/requests; actual
hardware blits, file parsing/release on the resource lifecycle edge, audio/MIDI
and real Windows callback delivery remain explicit boundaries. Score I/O itself
executes here. No playable-EXE or new byte-exact claim is made.

The initial isolated ranking fixture retained a generic invalid active-surface
sentinel. The corrected fixture selects a real controlled surface on both sides;
original ranking pixels execute unchanged. This was a harness error, not a
recovered-algorithm or REA defect.

Every previous suite, all forty cold exact units, eight rejection checks,
native/MinGW/VC4 products, Wine inspector comparisons and saved REA verification
pass as one checkpoint. Complete earlier acceptance inputs are refreshed only
after those checks. The passing new-family report is reused with identical
complete inputs and native-library identity, avoiding a redundant replay.
Private reports, input identities and logs are retained under
`.analysis/checkpoints/gameover-176-40/`.

## Later real Windows control runs

`tests/test_windows_gameover.py` now follows ordinary mouse-driven ball losses
through the maintained reset/finish/dispatch bodies into mode 3 on the original,
VC4 and MinGW EXEs. Real key input tests lowercase letters, Backspace and Shift-A;
Enter inserts the actually earned score. All 660 file bytes and the complete
in-memory table are compared, preserving post-terminator name tails. A fresh
process reads the same saved table, and both processes exit with code zero.

This evidence reuses the retained REA state contracts through a read-only Win32
observer; it neither hooks dependencies nor writes target state. Runtime reports
are separate from the 6,531 direct/76 connected oracle checks above. Palette/text
presentation in Wine/Xvfb, all levels and actual audio delivery remain limited;
the two-color original high-score captures are retained without pixel-fidelity
acceptance. See the adapter notes for observer/toolchain identities and scope.
