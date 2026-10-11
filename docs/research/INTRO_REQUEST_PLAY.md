# Current intro recovery in real Wine play

The later [display-depth comparison](WINDOWS_DISPLAY_DEPTH.md) locates the
missing glyph/title pixels below in the eight-bit Xvfb configuration. The
unchanged original renders complete text on a 640-by-480 24-bit host screen.
The historical captures and original executable identities in this note stay
unchanged; they do not describe the later display configuration.

The VC4 game built from source checkpoint `b92e6ab` passes the unchanged
`observe(vc40)` opening/menu/ball/pause/editor/exit path after the
[point animation request-write recovery](exact/INTRO_UNUSED_FILL_WRITES.md).
An original-executable control passes the same path under the same
640-by-480, eight-bit Wine/Xvfb settings. No source or exact ledger changes
follow; this is current-product integration evidence.

The rebuilt executable's SHA-256 is
`4070daf5398f67a95975cca45ef98c2c8fdffeb4effe45acad2bc8d711bdd5be`.
The original retains its verified
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
The SDK reader records 77 rebuilt and 79 original read-only observations.
Both runs check actual mouse movement, attached-ball release and motion,
P pause with unchanged ball fields for half a second, resume, return to menu,
Control-F1 editor entry, painting two tile-2 cells, full-bank save, next/previous
board, Backspace/load/save, return to menu and zero-status exit with no window.
All 49 supplied originals retain their hashes.

Both saved bank files have SHA-256
`b88441eb5e06676a106501a60a450b8046fa7b880e8f53ffe5f556ae75a42cd2`:
the complete first board contains exactly the two painted cells, and all
49 other boards retain their original bytes. The game receives ordinary XTest
mouse/key input. The observer uses ReadProcessMemory without writing target
memory, hooking code or suspending threads. Observations are sequential rather
than atomic frame snapshots.

## Rendering evidence and limits

Visual inspection found absent filled glyph pixels in the opening and paused
screens. The original control has the same visible issue in this environment;
the cause remains unlocated. It is not resolved by a passing state assertion.
The captured opening, editor and editor-reload RGB buffers are exactly equal
between original and rebuilt runs, with zero differing pixels in each complete
640-by-480 buffer. Pause differs at 8,125 pixels and return-menu at 11,101;
these animation frames are not synchronized, so those differences do not
establish a source defect or whole-renderer equivalence.

Five PNGs and complete state records are retained per profile in
`.analysis/windows-play-intro-request-writes/`, together with both reports,
input/product hashes, the saved banks and the screenshot comparison. No image
is repaired or replaced. Physical display, audio/MIDI, synchronized moving
frames and a complete campaign remain unproved.

The existing reader is reused from its actual later compilation receipt in
`.analysis/windows-play-current-render/reader-compile.json`. Its binary, source,
flags, compiler and six recorded SDK headers agree. The first reuse check
selected an older reader receipt and rejected it before game launch; that
validation failure is retained. No new reader, game or legacy source compile
occurs. Only the VC4 source profile and original control are run; prior MinGW
and owner-oracle observations retain their historical identities.

The immutable play checkpoint is
`.analysis/checkpoints/intro-request-play-283-206/`. The prior source checkpoint
and all 206 exact / 44,406 code / 136 metadata claims remain unchanged. Temporary
probe runtime copies are cleaned only after their exit state and unique files
are retained. REA feedback remains optional in the single existing `/tmp` file.
