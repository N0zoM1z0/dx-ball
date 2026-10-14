# Remaining exact functions

All 34 authored candidates were compared against the complete original extents
on October 13, 2026. Current compiler inputs and objects match their receipts.
Every relocation, declared literal and attached metadata block is included.
None of these candidates is already exact. The accepted total remains
**334 functions / 69,697 code bytes / 136 metadata bytes**.

Stream seeking/output restore full153/381-byte bodies with21/29 differences;
neither is exact. Source453/candidates110, all334 old exacts/108 candidates
preserved. See [stream operations](RUNTIME_STREAM_OPERATIONS.md).

The full 229-byte CRT fabs is exact, including real special-value/error handling
and all seven calls. Source450/candidates107; all333 old exacts/107 candidates
are preserved. See [double absolute value](RUNTIME_ABSOLUTE_DOUBLE.md).

Sixteen whole compiler-generated list initializer stages add 376 exact bytes
from unchanged current source and products. Source-emission entries448;
authored270/candidates106 remain unchanged. All317 prior exacts and42 shared-
owner exact units are preserved. See [generated list stages](LIST_GENERATED_EXACT.md).

The full 79-byte physical FDIV probe is exact. Source432, candidates106;
all316 preceding exacts/106 candidates are preserved. Three member-call ABI
attempts are rejected, not accepted source. See [physical FDIV](RUNTIME_FDIV_PHYSICAL.md).

Signed CRT absolute value adds one complete10-byte exact; source429 and
candidates104. Unsigned wraparound variants were nonexact; the signed API
requires a representable absolute value. All315 preceding exacts/104 candidates
are preserved. See [absolute value](RUNTIME_ABSOLUTE.md).

[FDIV processor testing](RUNTIME_FDIV_PROCESSORS.md) adds the full278-byte exact
and five complete89-byte literals. Source426; all314 old exacts/102 candidates
remain unchanged. Physical hardware testing and integration are open.

[Filter initialization/lifetime](RUNTIME_FILTER_LIFETIME.md) adds two full exacts
across35 bytes and a complete4-byte initialized record. Inventory543/source425;
all312 preceding exacts/102 candidates remain unchanged. Linker integration is open.

[Stream position/C++ filtering](RUNTIME_POSITION_FILTER.md) adds two full exacts
across101 bytes and the ftell413/432/360 candidate. Inventory541/source423/
candidates102 (34 authored/68 runtime); all310 old exacts/101 candidates remain.

[The full x87 bridge](RUNTIME_X87_BRIDGE.md) adds source288/288/14 and corrects
its omitted33-byte switch/alignment tail. Source420/candidates101 (34 authored/
67 runtime); all310 old exacts and100 candidates remain unchanged. No new exact.

[File access checking](RUNTIME_ACCESS.md) adds one complete77-byte exact.
Source419; all309 preceding exacts and100 candidates retain their inputs/products.

[Complete C++ handler search](RUNTIME_CPP_HANDLER.md) adds the full659-byte source
candidate663/605. Source418/candidates100 (34 authored/66 runtime); all preceding
exact and candidate producers remain unchanged. No new exact claim.

[C++ dispatch/transfer](RUNTIME_CPP_TRANSFER.md) adds two full exacts across232
bytes and one candidate. Inventory540/source417/candidates99 (34 authored/65
runtime); all307 prior exacts and98 candidates are preserved.

[C++ exception tables](RUNTIME_CPP_TABLES.md) add four source bodies and three
complete exacts across214 bytes. One candidate remains; source414,
inventory539 and candidates98 (34 authored/64 runtime). All304 preceding exacts
and97 candidates are preserved.

[Floating dispatch](RUNTIME_FP_DISPATCH.md) adds two complete source candidates
and all40 initialized constant bytes, with no new exact claim. Source410,
candidates97 (34 authored/63 runtime); all preceding comparisons are preserved.

[Decomposition/exceptions](RUNTIME_FP_DECOMPOSITION.md) adds two complete exacts
across266 bytes and four candidates. Source408, candidates95 (34 authored/61
runtime); all302 preceding exacts are preserved. The converter candidate changes
94 to95 differences in the genuine matherr-marker source context.

[FP control/classification](RUNTIME_FP_CONTROL.md) adds six complete exacts
across517 bytes and two candidates. Source402, candidates91 (34 authored/57
runtime); all prior comparisons remain intact.

[Float rendering](RUNTIME_FLOAT_RENDER.md) adds six full exacts across654 bytes
and two candidates. Current source394, candidates89 (34 authored/55 runtime);
all preceding comparisons remain intact.

[Float formatting](RUNTIME_FLOAT_FORMAT.md) adds five complete exacts across280
bytes and three candidates. All34 authored candidates remain unchanged; current
comparisons total87 candidates (34 authored/53 runtime), with386 source bodies.

The [CRT conversion wrappers](RUNTIME_FLOAT_CONVERSIONS.md) add three complete
runtime functions and 109 bytes. All 34 authored candidates below remain open.

The [binary conversion continuation](RUNTIME_BINARY_CONVERSION.md) adds two
24-byte exact runtime format entries and the maintained converter candidate:
`crt-extended-convert`, initially 459/459 bytes with 94 differences. Both
24-byte format records match in full. The [mantissa helper continuation](RUNTIME_MANTISSA_HELPERS.md)
adds three exacts and five implemented candidates. The current comparison set
initially contains 40 candidates: 34 authored and six runtime bodies. The
[iteration and arithmetic continuation](RUNTIME_MANTISSA_LIFETIMES.md) makes
zero testing and 96-bit addition exact, and adds two shift candidates. The
current set has 41 candidates: 34 authored and seven runtime bodies. The
converter has 94 differences in the current shared source context.

[Decimal conversion](RUNTIME_DECIMAL_CONVERSION.md) supplies four new source
candidates and all 58 power records. The current set therefore has 45 candidates:
34 authored and 11 runtime. All preceding exact and candidate results are preserved.

[Modes and resizing](RUNTIME_FILE_MODES.md) add the exact21-byte heap-size
wrapper and two candidates. [Stream buffering](RUNTIME_STREAM_BUFFERS.md)
adds three complete exacts across144 bytes, three candidates and a previously
unlisted11-byte function boundary. Current comparisons total50 candidates:
34 authored and16 runtime. All34 game candidates below remain unchanged.

[Low-I/O writing](RUNTIME_LOWIO_WRITE.md) adds two complete exacts across169
bytes, three candidates and all360 private error-table bytes. The current set
has53 candidates:34 authored and19 runtime. The game candidates remain unchanged.

[Reading and closing](RUNTIME_LOWIO_READ_CLOSE.md) adds four maintained source
candidates. Current comparisons total57:34 authored and23 runtime; all preceding
candidate results and255 exact results are unchanged.

[Stream transfer](RUNTIME_STREAM_TRANSFER.md) adds complete exact closure112
and terminal flags42, plus four maintained candidates. Current comparisons
total61:34 authored/27 runtime. Slot acquisition retains two comparison-
commutation differences and is not counted exact.

[File opening](RUNTIME_STREAM_OPEN.md) adds exact stream wrappers37/21 and
three maintained candidates, including both complete mode/open switch carriers.
Current comparisons total64:34 authored/30 runtime. The full1053-byte opener
retains only two temporary-register differences; the parser526/49 and
allocation184/37 remain nonexact.

[Length and retirement](RUNTIME_FILE_SIZE.md) adds complete chsize359 exact
and calloc/fcloseall source candidates. Current comparisons total66:
34 authored/32 runtime. The preceding msize exact21 and realloc106/111/15
are recompiled and preserved; all other preceding results remain unchanged.

[Exit registration](RUNTIME_ONEXIT.md) adds atexit19 exact and promotes the
existing normal/quick18/18 wrappers without modifying termination source.
Onexit121/2 and the initializer walker32/6 are complete candidates. Current
comparisons total68:34 authored/34 runtime. All preceding260 exact and66
candidate results and historical semantic inputs are unchanged.

[Integer text](RUNTIME_INTEGER_TEXT.md) adds complete itoa60/ultoa30 exacts
and the maintained96-byte helper with two comparison-direction differences.
Its reversal uses address cursors so a one-digit conversion does not form a
before-array pointer. Current candidates69:34 authored/35 runtime; all prior
263 exact and68 candidate results remain unchanged.

[Case conversion](RUNTIME_CASE_CONVERSION.md), [locale backends](RUNTIME_LOCALE_BACKENDS.md)
and [startup/fatal recovery](RUNTIME_LOWIO_STARTUP.md) add five complete runtime
exacts across852 bytes. Current candidates74:34 authored/40 runtime; every
authored result below remains unchanged.

[Error controls](RUNTIME_ERROR_CONTROL.md) add three exact validators and full
abort31 across122 bytes, plus the complete MessageBox146/90 candidate. Current
candidates75:34 authored/41 runtime; the authored results below remain unchanged.

[Signal dispatch](RUNTIME_SIGNALS.md) adds exact lookup49/47 and full raise/filter
candidates. The original raise owns53 additional switch bytes. Two new verified
entries bring inventory to531; current candidates77:34 authored/43 runtime.

[Decimal output](RUNTIME_DECIMAL_OUTPUT.md) adds exact lead-byte classification18
and two complete candidates: decimal output922/923/535 and classification58/7.
Current candidates79:34 authored/45 runtime. All preceding results are unchanged.

[Code pages](RUNTIME_CODEPAGE.md) adds four complete exacts across227 bytes,
525 initialized logical data bytes and the setter473/475/128 candidate. The full
mapping95 includes39 embedded dispatch bytes. Current candidates80:34 authored/
46 runtime; all preceding results are unchanged.

[Argument/environment startup](RUNTIME_ARGUMENTS.md) adds environment setup219
exact and three whole candidates: setup151/155/116, parser475/466/280 and
acquisition389/411/404. Code-page companions preserve227 exact bytes after a
shared declaration correction. Current candidates83:34 authored/49 runtime.

[Initialization](RUNTIME_INITIALIZATION.md) adds controller48/precision19/noop1
exact and math25/23/5 candidate, plus the full28-byte FP record. One missing real
callback entry extends inventory to532. Current candidates84:34 authored/50 runtime.

| Function | Original bytes | Current bytes | Differing positions |
| --- | ---: | ---: | ---: |
| `present-regions-now` | 984 | 984 | 2 |
| `elapsed` | 81 | 81 | 3 |
| `measure-text` | 279 | 279 | 3 |
| `sort-present-regions` | 296 | 296 | 3 |
| `update-paddle-position` | 203 | 203 | 4 |
| `animate-palette` | 234 | 234 | 6 |
| `refresh-score` | 74 | 74 | 6 |
| `rotate-palette-right` | 234 | 234 | 6 |
| `wait-frames` | 170 | 170 | 6 |
| `draw-line` | 445 | 445 | 9 |
| `palette-transition` | 1339 | 1339 | 12 |
| `draw-score` | 433 | 433 | 21 |
| `load-editor-board` | 52 | 58 | 23 |
| `store-editor-board` | 52 | 58 | 42 |
| `queue-explosion-at` | 99 | 100 | 51 |
| `clear-all-entities` | 106 | 107 | 59 |
| `load-sprite-bank` | 1475 | 1475 | 70 |
| `fill-triangle` | 1710 | 1710 | 88 |
| `draw-paddle` | 677 | 677 | 48 |
| `rotated-sprite-height` | 191 | 193 | 158 |
| `fill-polygon-clipped` | 1592 | 1592 | 210 |
| `fill-polygon` | 1543 | 1543 | 211 |
| `stretch-effect-sprite` | 306 | 308 | 252 |
| `editor-key` | 632 | 638 | 260 |
| `drop-bricks` | 426 | 436 | 306 |
| `draw-effect-sprite` | 361 | 365 | 330 |
| `draw-high-scores` | 404 | 403 | 330 |
| `blt-effect-sprite` | 362 | 366 | 332 |
| `hit-board-tile` | 1315 | 1316 | 418 |
| `redraw-intro` | 587 | 578 | 560 |
| `load-pcx` | 862 | 979 | 851 |
| `last-brick` | 1057 | 1067 | 992 |
| `game-frame` | 1688 | 1691 | 1155 |
| `render-rotated-sprite` | 1572 | 1466 | 1466 |

Differences are raw byte positions after genuine relocation resolution, not
a count of missing operations. Different instruction lengths move later bytes.
The matching recipes and target addresses are in `config/match-units.toml`;
each candidate links its retained research evidence there.

The [stored-contact precision](EXACT_REBOUND_STORED_CONTACT.md) closes the
complete 681-byte paddle rebound while preserving its three exact companions.

The [sprite iteration lifetime](BANK_SPRITE_ITERATION_SCOPE.md) reduces bank
differences from 72 to 70 while preserving all fifteen exact resource companions.

The [device surface and palette calls](DEVICE_SURFACE_PALETTE_CALLS.md)
restore two blue comparison groups and reduce transition differences from
18 to 12. Five exact device companions retain 808 bytes.

The [palette interface](EXACT_PALETTE_COM_CALLS.md) promotes complete stretch
and reset while preserving all affected exacts. Paddle improves from 68 to 48
differences; the other 34 retained candidate code identities are unchanged.

The [intro surface calls](EXACT_INTRO_COM_CALLS.md) promote the complete
233-byte scroller while preserving all eighteen intro exact companions. The
remaining 37 candidate code identities are unchanged.

The [runtime surface calls](RUNTIME_SURFACE_COM_CALLS.md) reduce paddle
differences from 104 to 68 while preserving all ten runtime exact functions.
The other 37 candidate code identities are unchanged. The drawing-record
combination and game-over call projection are rejected.

The [display COM integration](EXACT_DISPLAY_COM_CALLS.md) promotes four complete
functions and explicitly demotes three, for a net gain of one function and
994 bytes. All 35 retained candidate code identities stay unchanged.

The [surface COM integration](EXACT_SURFACE_COM_CALLS.md) promotes ordinary
blit, capture and glyph drawing, and explicitly demotes stretch. Its two
longer address producers leave 141/139 with 90 differences. PCX commutes one
signed comparison group and retains 979/862 with 851 differences. The other
37 retained candidate code identities stay unchanged. All 234 accepted
closures, 1,869 existing resource cases and six existing callback cases pass.

The latest rotation expression, axis-cursor and sampled-plane records are
rejected: they leave the renderer nonexact and lose two accepted projection
bodies. Floating consistency also leaves it nonexact. C++ rectangle passing
retains the extra instruction in explosion cleanup; both direct cursor-import
contexts leave four paddle-position differences. See
[closed diagnostics](CLOSED_STORAGE_DIAGNOSTICS.md#rotation-and-value-copy-follow-up).

The latest [polygon workspace](POLYGON_SCAN_WORKSPACE.md) reduces the two
polygon comparisons while preserving all accepted raster functions. The three
raster candidates above reflect that verified checkpoint. The original EXE has
no COFF symbols or debug directory.
The verified original game archive contains 51 files, with no source, PDB,
object files or linker map. Its inventory is retained in
`.analysis/exact-input-frontier-20261013/audit.json`; no online search runs.

The [explosion cleanup scope](EXACT_EXPLOSION_CLEANUP_SCOPE.md) promotes its
797-byte controller; the [secondary-width scope](EXACT_OVERLAP_SECONDARY_WIDTH.md)
promotes the 329-byte overlap. The [triangle scanline scope](TRIANGLE_SCANLINE_SCOPE.md)
reduces its differences from 107 to 88. The latest
[intro point phases](EXACT_INTRO_POINT_PHASES.md) promote the 711-byte update.
The [capture allocation phases](CAPTURE_ALLOCATION_PHASES.md) reduce its
comparison from 803 to 745 differences. The latest
[API workspace](CAPTURE_API_WORKSPACE.md) restores the remaining frame homes
and reduces differences to 726; the other 40 candidate hashes are unchanged.

The [sprite-bank API workspace](BANK_API_WORKSPACE.md) restores the complete
1475-byte loader size and reduces its comparison from 1577 to 76 differences,
while preserving all 12 resource exacts.

The later [upload-pointer workspace](BANK_TRANSFER_WORKSPACE.md) restores the
pixel pointer's original EBP-68 home and reduces that comparison to 74
differences. The descriptor and result homes remain exact; the loader is still
a candidate.

The [standalone color-key phase](BANK_COLOR_KEY_PHASE.md) restores EBP-64 and
brings the bank comparison to 72 differences. It preserves glyph search,
which the earlier key-as-record-field model lost.

The [intro score phase](INTRO_SCORE_PHASE.md) restores rectangle and text-length
homes while keeping the buffers unchanged. Redraw remains 578/587 with 560
differences; the change preserves every accepted intro body.

The [rotation visible-pixel scope](ROTATION_VISIBLE_PIXEL_PHASE.md) brings its
comparison to 1466/1572 with 1466 differences while preserving all four accepted
rotation functions. The frame and instruction count stay unchanged; the local
homes still differ from the original.

Private complete comparison: `.analysis/exact-candidate-audit-20261012/comparison.json`.
No new game, fixture or provider session accompanies this audit.
