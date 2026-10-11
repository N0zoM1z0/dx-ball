# Sprite, font, PCX and palette owner

The latest [complete capture flow](exact/EXACT_CAPTURE_ADDRESS_FLOW.md) explains
all248 original/current instructions without a new source change.18 actual
bank-address groups prove the same1048*bank+4*sprite slot address;104 other
instructions agree through a complete140-byte typed frame map and five direct
successors/seven calls. Already-linked production and matching capture code/
42 relocations are identical. The876/852-byte candidate retains803 differences;
no compiler/provider/runtime replay or new acceptance. This retires capture's
abstract groups as a missing-producer hypothesis. The earlier owner checks
below retain their own historical products and scopes.

The PCX decoder now follows the original independent RLE and literal-pixel
paths. Both paths retain their own wrap, clip and consumed pixel-pointer
updates. A byte pointer fills the complete 128-byte disk header; typed signed
16-bit maxima occupy offsets eight and ten. Other header bytes remain opaque
encoded input, rather than invented fields. Dimensions and pitch remain saved
from GetSurfaceDesc before Lock. Separate header/run indices, the observed
source-row initialization and increments, inclusive decoded limit, zero-count
packets and packet overshoot are preserved. The row count has no later consumer
in the original; it is retained from its actual stores and increments, not
introduced to change the frame. Scoped GCC diagnostics preserve both this
update and the original redundant 192..255 byte test in shared source.

The complete 862-byte original body is contiguous. Its current `/ML` comparison
is 984/862 bytes with eight explicit relocations and 869 unaligned differences;
it remains a candidate. Current/original frames are 308/312 bytes. Local homes,
address scheduling and the remaining frame bytes are unresolved; no additional
local, padding, declaration or name trials were used to force agreement. The
complete three-byte `rb` literal is bound to `0x422794`. All twelve accepted
resource units and five candidates were compared together; exact totals stay
169 functions /30,238 complete code bytes /136 metadata bytes.

REA information, pseudocode and assembly are retained in closed run
`2026-10-10T17-54-16.976Z-requests-866362`, with Evidence identities
`ev_c50e6d43ad08314dafcb3121bfd836d0e3a93d04d480533b5ab9b77043f8b6a2`,
`ev_13ac465a95860ab7b511475a2174d532caacd558004ca45bb872179fb03aa192`
and `ev_93b5290136b33bfcc5cee2cc186d2f6440c5a8c1595647d46ec6172e7d5c8566`.
Two matching compilations retain the intermediate and final objects/inputs.
The final native library passes 99 unchanged selected PCX cases: all five
supplied images, all palette modes, retry, clipping, signed maxima, zero runs
and overshoot. Native/MinGW builds pass. One established `/MT` production
compile and 34 verified object reuses relink the VC4 game. Real-Wine ball/pause/
editor/save/reload/exit passes with 84 read-only states, five captures, the
expected saved-bank hash, exit zero and all 49 originals unchanged. The play
selection and its limitations are recorded in
`.analysis/windows-play-pcx-decoding/`; compiler and selected-oracle receipts
are in `.analysis/exact-pcx-decoding/`. Other semantic scopes and prior controls
remain historical after input-identity refresh; no full owner or historical
validation queue was replayed.

Glyph lookup at `0x404E40` now matches its complete 145 bytes and six
relocations. The source restores the count-first short-circuit loop, preserving
the excluded final slot, zero for a missing character and one for an empty
bank. Glyph drawing restores the original found-glyph fallthrough, rectangle
operand order and separate zero-return branch. Its complete 332/328-byte
comparison remains a candidate with seventeen bindings and 258 unaligned
differences. Its twenty-byte frame agrees, but bank-address scheduling differs;
no declaration, name, layout or padding trials were used.

The closed REA run `2026-10-10T17-38-24.772Z-requests-846003` retains separate
information, pseudocode and assembly facets for both functions. Lookup assembly
Evidence is `ev_9eb642c30e5cca30a9729baaf268061b881e8ea769519a14219e1f7a6e130834`;
drawing assembly is
`ev_21080b939b28e2885082bf86ee64b5815bdfeaea9276e5163a6318197d18b244`.
The drawing view owns 323 instruction bytes in the complete 328-byte span.
Independent pinned-image decoding covers its omitted five-byte JMP at
`0x404E27..0x404E2B`: `e907000000`, destination `0x404E33`.
The comparison includes every byte, including that unreachable jump.

This batch also corrects an error in the preceding private comparison helper:
release, capture and SBK load were registered under the runtime recipe although
their actual comparisons used the resources object. Their byte comparisons
remain independently reproducible; the release match row now records the
correct resources source, object, flags and eight consumed inputs. The original
bad manifest and receipts remain preserved. Tracking now checks every exact
and candidate recipe against the implementation's source owner and rejects
the archived wrong manifest. All twelve resource exacts and four candidates
were compared together on one `/ML` compilation; none of the existing exacts
was lost. Current totals are 169 exact functions, 30,238 complete code bytes
and 136 metadata bytes.

Native/MinGW builds pass. The final native library passes 1,537 unchanged
selected font cases: 769 lookups and 768 drawings across all byte codes in
the three supplied fonts, including the empty-bank lookup. One separate `/MT`
production compile and 34 verified object reuses relink the VC4 game. Its real
ball/pause/editor/save/reload/exit flow passes with 78 read-only states, five
captures, the expected saved-bank hash, exit zero and all 49 originals unchanged.
Receipts are in `.analysis/exact-font-rendering/` and
`.analysis/windows-play-font-rendering/`. Other semantic scopes and prior play
controls remain historical after input-identity refresh; no full owner or
historical queue was replayed. Full-game, synchronized pixels and physical
audio/MIDI fidelity remain unproven.

The preceding sprite-lifetime batch restores capture and SBK loading's live
bank/record reads across CreateSurface, SetColorKey, GetSurfaceDesc, Lock and
Unlock. Their allocation locals publish a record; they do not cache the record
for later COM calls. Both controllers now call the actual maintained malloc
entry. SBK caps read the current bank's allocation mode, and uploads use the
pitch saved from GetSurfaceDesc before Lock. A genuinely consumed destination
pixel pointer and the original bottom-up row/column predicates are retained.
Partial creation failures still preserve their original owner and leak effects.

The complete release controller at `0x404BE0` matches all 262 bytes with fifteen
relocations after restoring its NULL early return. All ten previous resource
exacts remain exact. Capture and load remain complete candidates: 876/852 bytes
with 803 unaligned differences and 42 bindings; 1,655/1,475 bytes with 1,577
unaligned differences and 77 bindings. Their frames have the observed 140/180
bytes, but local homes and bank-address scheduling still differ. No declaration,
name, layout or padding trials were used. The loader's full `rb` literal,
including its terminator, is bound to `0x421094`.

Three REA 6.3/Ghidra dossiers were required for these concrete storage questions.
The closed run is `2026-10-10T17-22-54.305Z-requests-825249`; complete bodies are
contiguous at 852, 1,475 and 262 bytes. Evidence identities are capture
`ev_d7dd48a6f210a1a2cffea6be8318655763959610c9d94f8f8ff5621dad169b76`,
load `ev_b55c6def4c1b4af6c165acfb1623311bffa077753d93fab01531787dca6b6d70`
and release `ev_fdfd328a6cc5c4a7bf1b5af0691079718afc8aa479782f79257bd54947a07159`.
Raw/normalized responses and limitations remain private with those identities.

One `/ML` matching compilation verifies all affected bodies. A recursive
include audit narrows its declared project closure from 29 files to the eight
actually consumed, without changing compiler flags or recompiling source.
The game retains its established `/MT` production recipe: substituting the
matching object initially caused a LIBC/LIBCMT startup conflict. One separate
production compilation then links successfully with 34 verified reused objects.
Native/MinGW builds pass. That checkpoint recorded 168 exact functions, 30,093
complete code bytes and 136 metadata bytes; its recipe associations are
corrected above.

The unchanged release/capture/SBK Oracle loops pass all 31 cases, including
seven supplied streams. Six separate private original/native COM probes change
the selected bank during capture/load or change a record's pitch during Lock.
The restored library passes all six; the preceding sealed library fails each.
They compare ordered events and defined bank/record/pixel fields; unwritten
partial-record pitch is excluded. These probes extend evidence without altering
the maintained matrix or claiming physical driver behavior.

The new VC4 product also passes the existing real-Wine ball/pause/editor/exit
flow with 83 read-only states, five captures, the expected saved-bank hash,
normal exit and all 49 originals unchanged. Receipts are in
`.analysis/exact-sprite-lifetime/` and `.analysis/windows-play-sprite-lifetime/`.
Other owner suites and prior original/MinGW play controls were not rerun;
their input identities are refreshed with their historical scopes preserved.
Synchronized pixels, physical audio/MIDI and full-game fidelity remain unproven.

Current [connected-effects cold replay](exact/EXACT_CONNECTED_EFFECTS.md) naturally
recovers the full keyed-stretch body while ordinary blt_sprite loses historical
exact acceptance. Current shared source and all relocations determine the claims;
historical objects remain available separately.

## Current allocation defaults

SBK/font storage now defaults to maintained malloc-mode allocation and heap
release. Current owner replay passes with the shared allocator present. The
connected private draft below remains historical failure-path evidence; see
[allocation ownership](ALLOCATOR_OWNER.md) for current acceptance and limits.

Evidence is the hash-pinned DX-Ball v1.07 target in `config/target.toml`.
Attested Ghidra queries cover the entries below; original x86 execution supplies
the behavioral evidence. The maintained implementation is `src/resources.c`.

| Entry | Maintained function | Target extent | Acceptance |
| --- | --- | ---: | --- |
| `0x00403E70` | select_sprite_bank | 24 | full exact |
| `0x00403E90` | select_font_bank | 24 | full exact |
| `0x00403F70` | blt_keyed_sprite | 195 | full exact |
| `0x00404040` | draw_keyed_sprite | 105 | full exact |
| `0x004040B0` | blt_sprite | 195 | scoped semantic; exact candidate |
| `0x00404180` | draw_sprite | 105 | full exact |
| `0x004041F0` | stretch_keyed_sprite | 139 | full exact |
| `0x004042B0` | capture_sprite | 852 | scoped semantic; exact candidate |
| `0x00404610` | load_sprite_bank | 1475 | scoped semantic; exact candidate |
| `0x00404BE0` | release_sprite | 262 | full exact |
| `0x00404CF0` | draw_glyph | 328 | scoped semantic; exact candidate |
| `0x00404E40` | find_glyph | 145 | full exact |
| `0x00409790` | load_live_palette | 337 | full exact |
| `0x004098F0` | load_saved_palette | 307 | full exact |
| `0x00409A30` | load_surface_palette | 376 | full exact; active use unresolved |
| `0x00409BB0` | load_pcx | 862 | scoped semantic; exact candidate |

## Storage and interface

The three banks begin at `0x00425980`, stride `0x418`. Each owns 255 sprite
pointers, a count at `+0x3FC`, allocation mode at `+0x400`, and a 20-byte filename
at `+0x404`. Current sprite/font selectors are `0x00421088` / `0x0042108C`.
The file pointer at `0x004265C8` is shared with board I/O. Selectors and banks
are zero-initialized in the file-backed target image.

A sprite has a surface pointer at `+0`, unclassified integer at `+4`, width,
height and pitch at `+8/+12/+16`, source RECT at `+20`, character byte at `+36`,
and signed baseline adjustment at `+40`. Allocation requests 45 bytes for this
44-byte i386 record. The spare byte and opaque integer are not assigned meaning
or accepted as initialized output. Native pointers grow naturally; the same
source and declarations compile for the native host and Windows i386.

DirectDraw dependencies use actual vtable slot order and the Windows stdcall
ABI. Surface slots used here are Release 2, Blt 5, BltFast 7, GetSurfaceDesc 22,
Lock 25, SetColorKey 29 and Unlock 32. IDirectDraw CreateSurface and palette
SetEntries use slot 6. The target descriptor is 108 bytes, with height/width/
pitch at `+8/+12/+16`, pixels at `+36`, and caps at `+104`. Microsoft's
[DDSURFACEDESC declaration](https://learn.microsoft.com/en-us/windows/win32/api/ddraw/ns-ddraw-ddsurfacedesc)
corroborates these fields. Unused vtable slots and descriptor fields remain
opaque.

## SBK stream and ownership

The stream starts with a signed little-endian 32-bit sprite count. Each record
is width i32, height i32, character byte, baseline i32, then exactly
`width * height` pixel bytes. Rows are stored bottom-up: the first stream row
becomes the last surface row. Surface pitch comes from GetSurfaceDesc and may
exceed width; padding bytes remain untouched.

All seven supplied streams consume exactly their file lengths: CANDY 52,
CHISEL2 50, MAINMENU 7, MBALL2 166, SFONT 96, SYSFONT 94 and THEFONT 48 sprites.
The loader frees slots 1 through 253 before opening the file, preserving slots
0 and 254. Successful loading restores the prior bank; an empty stream leaves
the previous count, allocation mode and filename unchanged. Mode 1 requests
surface caps `0x40`, other modes `0x840`; source color key is zero, flags 8.
Descriptor and Lock failures are retried until success.

CreateSurface failure returns with the new bank selected, an open file and
allocated partial record/pixel buffer. These observed effects are preserved.
Input filenames must fit the original 20-byte field; supplied basenames do.
Malformed/unbounded counts, dimensions and filenames are outside acceptance.
Allocation failure and open failure invoke exit(1); process-exit behavior has
not yet been compared. Release handles NULL records and NULL surfaces.

Capture releases an old slot, creates an offscreen surface and copies a RECT
from the active surface through Blt. The oracle accepts initialized record
fields and ordered API arguments, not hardware Blt pixel results. After failed
creation, uninitialized pitch and opaque fields are outside the compared state.

## Drawing and fonts

BltFast uses flags `0x10` for plain sprites and `0x11` for keyed sprites.
Blt uses `0x01000000` for plain copies and `0x01008000` for keyed copies.
Unstretched destination dimensions come from the sprite; stretch takes explicit
dimensions. Stored source RECTs are passed directly without replacement.

Glyph lookup checks slots 1 through count-1 and deliberately excludes the last
slot. No match returns 0; an empty bank returns 1 without inspecting a record.
Drawing requires populated records and accepts all 256 character byte values
for the three supplied fonts. Glyph top is `baseline-height-record.baseline`;
bottom is `baseline-record.baseline`. The return value is glyph width, or zero
for missing characters. Drawing an empty bank is outside acceptance.

## PCX behavior and palette

The decoder reads 128 header bytes and treats header xmax/ymax as signed i16.
It ignores xmin/ymin and bytes-per-line. It decodes while the number of emitted
pixels is **less than or equal to xmax*ymax**, rather than decoding the full
image area. A final RLE packet may overshoot this limit. Packet bytes below
192 are literals; other bytes supply count byte-192 and the following value.
Count-zero packets consume a value without emitting pixels.

Column wraps when it exceeds xmax. Output is clipped to the destination width
and height, with supplied x/y offsets and descriptor pitch. The original saves
dimensions and pitch before Lock. Palette mode 1 loads the live palette and
calls SetEntries; mode 2 loads the saved palette without that call; other modes
leave both untouched. Both loaders seek 768 bytes before EOF, read RGB triplets,
and preserve each entry's fourth flag byte.

## Reproducible evidence and limits

`scripts/repo-python tests/test_resources_differential.py` compares 1,869 cases:
all supplied SBK/PCX files, bank restoration, edge slots, creation failure,
descriptor/Lock retries, row reversal, pitch padding, clipping, RLE overshoot,
zero-count packets, signed maxima, all font bytes, glyph placement and palettes.
The unmodified target performs its own decoding and record access. Synthetic
CRT boundaries supply file buffers; target inline getc accesses those buffers
directly. The native implementation uses host libc on identical files.

Comparisons cover initialized bank/sprite state, all resulting allocated pixel
bytes, palette RGB/flags, return values, and ordered DirectDraw call arguments.
Target file traces and allocation/free ownership receive explicit checks.
DirectDraw operations are controlled boundary callbacks; COM driver behavior,
real Blt pixels, actual display, and backend error codes beyond modeled retries
are not proven by this test. Shared-source changes require fresh replay.

The current palette/display checkpoint accepts nine complete resource COMDATs,
1,668 bytes with every relocation applied and zero differences. The ordinary
195-byte blit is recovered by [EXACT_DISPLAY.md](exact/EXACT_DISPLAY.md); its previous
199-byte mapping is historical. Stretch remains a 139/139-byte candidate with
four unmasked differences. Seven entries retain scoped semantic evidence
without exact claims. No different object length is masked or reported as exact.

The related software renderer, offset helper and wrapper now live in the
[rotation owner](ROTATION_INVESTIGATION.md), with 1,024 separately counted direct
cases and an exact 40-byte wrapper. The resource translation unit is unchanged.

## Connected malloc ownership draft

A private natural shared-C copy connects capture/release and SBK loading to
the reviewed malloc-mode and heap-release entries. The original side removes
its malloc/free replacements and executes their complete internal chain.
**234 fixtures / 5,738 resource calls** pass: 161 captures, 143 bank loads and
5,434 releases, with 440 separately checked seed calls. All seven original SBK
files load and reload; slots 0/254 survive reloading and slots 1..253 retire
through the same allocation family.

Original entry observation records 21,127 malloc calls, 21,434 HeapAlloc
attempts, 307 handler calls and 21,124 heap releases. The three outstanding
allocations are deliberately retained pixel scratch after CreateSurface failure.
Controlled API traces, initialized records, full pixel data, bank state,
request sizes and ownership agree. Original record requests are 45 bytes;
native typed requests are independently checked at 49. Negative handler
results, one/three failed attempts, mode mutation during a request and mode
reload by later requests execute with their original bodies. One empty-owner
capture switches heap before allocating, without inventing a guarantee for
freeing old blocks on another heap.

The three synthetic partial-owner fixtures keep the selected bank, open file,
record and scratch on failed creation. Their live pixel bytes are compared
before record retirement; the file closes only through explicit fixture
cleanup afterward. Null-surface pitch is outside initialized-state acceptance.
Per-release effects, cleared slots and poison checks run immediately, with
complete bank/payload/ownership comparisons after each retirement batch.

REA `capture-process` Evidence
`ev_9973d4d648f070cacbddb52400b483c73df2f858af435235c94f813efc219ce5`
binds the successful child exit zero and complete report. Its 364 inputs
include the exact seven SBK files, pre-execution loaded engines, actual compiler
components and prebound link objects/libraries. Explicit typed fixture storage
provides the two board-owned globals; board-renderer functions are outside this
standalone comparison. A strict link rejects unresolved dependencies. Host
GCC's unused-result diagnostics remain visible through a narrowly declared
exception for deliberately ignored fread results; other warning errors remain.
The earlier compiler/load rejections and sources survive as separate controls.

The 69,700,317-byte comparison sequence streams into a digest, avoiding a large
redundant temporary snapshot. This is private native ownership evidence with
controlled file, DirectDraw and heap APIs. Production binding, connected i686
execution, malloc-NULL/open termination and actual startup/teardown remain open.
It adds no maintained, direct-case or exact ledger acceptance.

The corrected 57-file checkpoint retains inputs, products, source review and
REA capture, with 327 external references. Retention then removes 23 failed
working files after matching their sealed controls, shares 47 immutable
duplicates and recovers 828 KiB of measured disk usage. All 6,981 immutable
paths, 2,015 references and 49 original files verify; the next preview is empty.
Current successful products, original assets and pinned tools stay retained.


## Subsequent exact palette restoration

[EXACT_PALETTES.md](exact/EXACT_PALETTES.md) restores the complete 337-byte live loader,
307-byte saved loader and missing 376-byte surface palette constructor. The
resource exact build selects `/ML` for the original inline stdio reads. The
new constructor has complete-byte acceptance and three private bounded COM
checks; it adds no tracked direct cases or semantic row. Its active use and
physical DirectDraw behavior remain unresolved.
