# MIDI error exits and C++ lowering

The later [MDS controller states](EXACT_MDS_CONTROLLER_STATES.md) make loading
and playback exact across522/513 bytes, completing all eight MIDI bodies.
The byte parameters and candidate comparisons below belong to this earlier epoch.

The MIDI owner now has one shared implementation in
[`midi.cpp`](../../../src/midi.cpp), compiled as C++ by Native, MinGW and VC4.
Project declarations retain C linkage, so existing C callers, independent
Kernel32/WinMM cells and the five-argument stdcall callback keep their ABI.
Headers, parameter widths, record layouts and Oracle vectors are unchanged.
Restart failure now explicitly jumps to cleanup, as the original instructions
do; the previous source assigned error 5 and fell through. Calls, pending counts,
live header traversal and newly-created versus paused-stream cleanup remain.

## Original evidence and diagnosis

Play at `0x401780` has 493 owned bytes within its complete 513-byte span.
Retained REA dossier: Evidence
`ev_731ffd0b77a82869a867a736b02d245cc55b41b97dfc1974dee55fe3f83d27a4`,
`02-analyze_function.json` in `2026-10-07T15-16-14.218Z-interactive-3602154`.
Complete bytes: Evidence
`ev_63cb8dd0c62cd2c2e8e121e730540f10d836f953facd739adb6d4c6573b1ba9a`,
`00-read_bytes.json` in `2026-10-10T07-13-33.419Z-requests-4072877`.
All 513 bytes agree with the pinned PE. No new provider query is needed;
the REA 6.3.0 snapshot remains at twenty records.

Open, property, prepare/output and restart errors jump to four tail stubs at
`0x401977`, `0x401972`, `0x40196D` and `0x401968`. Each jumps backwards to
cleanup at `0x401933`. Four five-byte intervals excluded from the Listing,
at `0x401828`, `0x401867`, `0x4018D2` and `0x40192E`, are ordinary jumps skipped
after the error exits. They remain included in the complete comparison.
The dossier's pseudocode collapses the stubs into gotos and incorrectly prints
zero for early errors; instructions return 6 for bad magic and 7 for an active
stream. Maintained source and original execution retain those actual values.

One private C++ diagnostic compiles the maintained body with C linkage and the
observed final error goto. The compiler generates all four error exits, skipped
jumps and tail stubs naturally. The production source expresses that language
boundary with the unchanged `/Od /Ob0 /Oi- /Oy- /Gd /MT /Gy` recipe. One matching
compile consumes all seventeen recursively included declared project files.
A complete instruction review verifies those twelve jumps and the same 32-byte
frame. This supports the reconstruction choice, without uniquely proving
original language, filenames, parameter types or local names. No alternate
profile body, copied instructions, fake locals, padding or layout/name trials.

| Body | Emitted/original bytes | Complete differences | Result |
| --- | ---: | ---: | --- |
| Release MDS | 149/149 | 0 | Remains exact |
| Pause MDS | 133/133 | 0 | Remains exact |
| Play MDS | 516/513 | 169 | Candidate |
| Stop MDS | 225/225 | 14 | Candidate |
| Callback | 127/127 | 10 | Candidate |
| Parse MDS | 838/868 | 347 | Candidate |
| Expand events | 343/343 | 38 | Candidate |
| Open MDS | 480/522 | 406 | Candidate |

All actual relocations resolve to the same reviewed cells/callees; candidate
offsets refresh to their actual emissions. Exact release/pause retain all seven
relocation operands. Play's extra three bytes come from promotion of the
unchanged byte flag: `XOR EAX,EAX; MOV AL,[EBP+0xC]; TEST AL,1`, versus the original
memory test. Local storage and shifted operands also differ. These bytes remain
unmasked; the inferred byte prototype is not changed to force a match. Five
music exact units keep their verified unchanged objects.

## Affected checks and products

The unmodified maintained MIDI Oracle passes 2,109 direct cases and 134 separate
connected checks on current Native against original x86. It covers six original
songs, compact-event partial writes and poison tails, RIFF/MIDS boundaries,
allocation/mapping failures, 256 open-mode bytes, stream errors, pause/stop/
release, callback state and connected replacement. Existing nonnegative counts,
representable sizes, backing/alignment and wrapper-allocation-success limits
remain; no historical case count increases.

Actual relocated MIDI and unchanged music COFF objects pass identical vectors
and assertions against that current Native reference. Thirteen entries and all
internal direct calls use emitted bodies in separate executable memory, with
every actual relocation explicitly bound. Original code remains immutable.
The controlled SDK callback pointer keeps original address identity; callback
vectors explicitly call the emitted callback. This checks its convention and
state effects, not asynchronous SDK delivery or physical audio.

Native and MinGW each compile only the shared MIDI C++ owner and relink. VC4
uses one matching object plus 34 verified unchanged objects, resources and SDK
import libraries, with no extra production compile. PE imports retain genuine
DirectX factory names and have no parser warnings.

- Native SHA: `5a6af7461f4338deae4d9b03d7ddca3e4ea4b760af82480dee859cab4c1c8495`.
- VC4 EXE SHA: `c5fbd73e57b35379df46ec98420bd633345b4fd10fdff0b13af153bf261a0ca4`.
- MinGW game SHA: `242977e109f57f8378c89d772afbe456eff7bab35e87bc5eb2f87e77e2617ff2`.

Private receipts/helpers: `.analysis/exact-midi-play/`; seal:
`.analysis/checkpoints/midi-play-283-171/sha256.json`.
Current products/inputs and all 171 retained exact receipts are verified without
the historical owner replay. The 235 affected semantic input rows refresh with
their earlier scopes/counts. Current build/owner paths use `midi.cpp`; older
sealed checkpoints retain original `midi.c` paths and hashes.
No new live-game, synchronized trajectory or hardware claim. Totals stay
283 source-present, 171 exact /30,744 code bytes /136 metadata bytes and 247
scoped semantic rows. Complete reconstruction remains unproven.
