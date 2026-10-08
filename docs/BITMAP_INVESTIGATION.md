# Bitmap loader and unwritten stack storage

The saved REA function dossier for `0x00409F70` retains a contiguous 976-byte
body through `0x0040A33F`, under Evidence ID
`ev_e408e41080570698d5068c6aa811cbae0a93e65442822fc191ea85ea46c93cad`.
Its complete private record is in the closed 10-33 interactive run, SHA-256
`a638c4ad17795b11803e0b0337f1d0221e88c417d8ef662a9190f8ec7da9d803`.
This investigation reuses that record without another Ghidra import. Shared C
now passes full native and actual VC4 comparisons and is accepted after the
21-owner batch and 36-unit cold replay. No bitmap exactness is claimed.

## File and surface boundaries

Instructions establish two cdecl stack arguments: a DirectDraw surface and a
path passed to `CreateFileA`. The inferred `uint *` path type is not a recovered
source declaration. File opens request access `0x80000000`, share 1, disposition
3, attributes `0x80`, and null security/template handles. If the primary open
returns `-1`, the routine copies a prefix from `0x422798`, concatenates the path,
and retries. The new focused REA byte read confirms `2e 2e 5c 00`, or `..\`.
The maintained sound loader uses a separate address, `0x42106C`; this equality
is established by reading the bitmap prefix itself, rather than substituting
the sound-loader address.

The sequential reads request 14 header bytes, 40 information-header bytes,
1,024 palette bytes, and the low 32 bits of width times height for pixel data.
The information-header bit count must equal eight. The body tests `ReadFile`'s
Boolean return without checking the transferred count. It does not validate
the file signature, compression or pixel offset, seek to the declared offset,
or account for BMP row padding. Successful short reads preserve the untouched stack suffix and advance the
controlled file cursor by the actual transferred count. Negative or unbacked geometry remains outside the accepted domain.

Pixels use `LocalAlloc(0x40, width*height)`. A zeroed 108-byte surface descriptor
has size set to 108, then `Lock(NULL, descriptor, 0, NULL)` executes once. No
descriptor query or lock retry occurs on this path. The existing shared
[resource interfaces](RESOURCE_OWNER.md) identify the COM slots; the probe
supplies controlled descriptors and return values rather than a real device.

## Row traversal

The first source row begins at `allocation + (height-1)*width`. A signed
comparison chooses the smaller of surface pitch and file width as the copy
length. The loop uses the signed file height, without destination-height
clipping. After each copy, the destination advances by surface pitch and the
source retreats by the **copy length**, rather than file width. Instructions
`0x40A22A..0x40A234` establish the latter update.

For a 3-by-2 tightly packed pixel fixture containing `1,2,3,4,5,6`, a pitch of
two therefore produces `4,5,2,3`. A pitch of three produces `4,5,6,1,2,3`.
With pitch five, each three-byte reversed row leaves two destination padding
bytes untouched. This behavior needs to survive reconstruction even though a
conventional BMP loader would traverse the rows differently.

## Cleanup and palette effects

| Exit or stage | Observed effects after a successful open |
| --- | --- |
| Header/palette read failure, unsupported bit count, allocation failure | Return zero; no `CloseHandle` |
| Pixel read failure | Free pixel allocation, return zero; no `CloseHandle` |
| Surface lock failure | Free pixel allocation, return zero; no unlock or close |
| Successful pixel copy | Unlock surface, free allocation, close file, then create palette |
| Palette creation failure | Return zero after the pixel and cleanup effects |
| Palette creation success | Set surface palette and return one; ignore its HRESULT |

Unlock and close results are also ignored. No palette release appears in this
body. These instruction observations describe the routine's boundary effects;
they do not establish whole-game resource lifetime.

Each of the 256 palette entries receives red/green/blue from the input's
blue/green/red bytes. The routine never writes the fourth output byte and does
not first initialize that output buffer. `CreatePalette` receives caps 4 and
the complete entry array. Original execution with four caller-stack fixtures
(`00`, `5A`, `A5`, `FF`) preserves the corresponding fourth bytes. Their value
cannot be promoted to a deterministic C constant or silently zeroed. The
fallback buffer and output palette begin `0x140` (320 decimal) bytes apart;
the bounded path fixtures stay below that separation.

## Original-machine reference probe

```bash
scripts/repo-python tests/probe_bmp_loader.py
```

The probe executes the hash-verified, unmodified original x86 body and its
actual string/memory helpers. It controls only file, allocation and COM
dependencies, plus input data and caller stack storage. The original 23 fixtures
check three positive pitches with four stack seeds, nine failure gates, and
two fallback paths. Another 432 fixtures exercise successful short reads at
all four read stages, using four stack seeds and pitches two, three and five.
The fallback fixtures verify the immutable original `..\\` prefix bytes;
they do not replace the target string with a controlled prefix. Comparisons cover complete destination storage and guards,
unchanged source pixels, converted RGB bytes, all 256 fourth bytes, ordered
calls, return values and cdecl register/stack preservation. A deliberately
non-BM header still reaches the successful path. Nonzero unlock/set-palette
results and a false close result still return one.

The complete private report is `build/reports/bmp-investigation/original.json`.
It records the original/dossier identities, nine input hashes, all 455 fixtures
and the controlled-boundary limitations. The entire loaded original code
region is compared before and after execution. Complete read-buffer bytes
are interned only after full-byte comparison and collision checks: 149 unique
buffers keep the report below 800 KiB. Each read retains its requested and
returned lengths, actual cursor position, and complete before/after identities.

Partial information-header or palette reads shift the start of the next read;
they are not independent zero-filled inputs. Header and palette stack suffixes
retain the caller seed, while unread pixel bytes retain `LocalAlloc` zeroes.
Successful sampled geometry remains 3-by-2 with bit count eight; sampled
unsupported bit counts reject before allocation and leave pixels unchanged.
Arbitrary partial-header geometry and unbounded paths remain outside this
probe. This original-only probe remains reference evidence; it does not separately
increase semantic counts. The shared-source comparison below supplies the
accepted cases. Real file/DirectDraw behavior remains unestablished.
It generates no EXE, compiler object or raw stream archive.

## Focused prefix and reference review

REA `read_bytes` Evidence
`ev_0bf8c40924cea03a09e6b27ffa6d9e1c3531fdcb50b6aa934e790f870cdda023`
returns all 64 requested initialized bytes from `0x422798`. The first four
bytes are `2e2e5c00`, confirming the fallback prefix `..\`. The adjacent
filenames are separate storage and do not extend that null-terminated prefix.

Focused `xrefs` Evidence
`ev_2821d190f775c7a3bba95f0f535a7ac92279cee17c31b0cfc6b008a91cc15137`
returns only `0x409FAB`, the prefix source used by the retained loader
instructions. No additional direct producer reference is found. Loader Evidence
`ev_aa47eec0b59cc79cccfc1c8ed83f14762b962929ff1677d4c604608aa8687573`
returns no direct incoming address references. These results describe Ghidra's
reference-manager coverage; indirect accesses and actual runtime use remain
unestablished.

The three focused operations completed in the same graphics batch as the
[rotation data review](ROTATION_INVESTIGATION.md#focused-rea-data-and-reference-review).
Complete Evidence and successful session close are retained privately.
The public request set uses REA's documented lowercase addresses:

```bash
scripts/rea session config/rea-bitmap.json
```

## Shared source and compiler execution

The [shared C owner](../src/bitmap.c) and [API declarations](../src/bitmap.h)
preserve the sequential reads, signed pitch comparison, row retreat by copy
length, failure leaks, cleanup ordering and ignored HRESULT/close results.
The 260-byte fallback buffer follows the recovered 65-word storage and its
string use. Header, information, input-palette suffixes and output flags remain
unwritten locals; no constant or allocator callback supplies their values.
The Windows adapter binds the real file, LocalAlloc/LocalFree and COM APIs.

The test-only [AMD64 caller](../tests/seed_stack_x86_64.S) seeds 64 KiB of unused
stack before entering the actual native C function. This models the original
machine fixture's pre-entry stack, preserving four distinct seeds through
untouched storage. It does not replace production code or inject local values
after entry. SysV register preservation and call alignment belong to this test
driver; reconstruction source remains C. Native tests require Linux x86-64.

The original probe now supplies its five Win32 API boundaries at the unbound
PE import-name RVAs, mapped separately. Original IAT values remain unchanged:
`CreateFileA` `0x41534`, `ReadFile` `0x4159A`, `LocalAlloc` `0x41542`, `LocalFree`
`0x414F4` and `CloseHandle` `0x414D4`. Synthetic COM tables remain fixture
storage. Earlier reports that redirected IAT slots remain historical controls.
The full original code and these import slots verify before/after execution.

**975 original/native cases** include all 455 earlier fixtures plus 520
geometry/pitch cases: widths `0,1,2,3,4,7,13`, heights `0,1,2,3,5`, zero/narrow/
equal/wide pitches and four stack seeds. Zero-size allocation success is an
explicit controlled API result; actual OS zero-size behavior is unverified.
All destination/guard bytes, every palette byte including flags, successful
read buffers and their untouched suffixes, allocated pixels and ordered calls
compare directly. The report interns 376 complete buffers after full equality
and collision checks. Descriptor pointer growth and its size field follow the
existing shared DirectDraw declaration on the native host.

The actual VC4 output passes the same complete vectors. Its 949-byte public
body and 64-byte static little-endian reader occupy full dedicated COMDAT
sections in separate executable memory. Every relocation has an explicit
binding; original memcpy/memset/strcpy/strcat bodies execute. The object's
`$SG412` literal is independently checked against `2e2e5c00`. Generated API
slots point to the same controlled boundaries without altering original IAT.
The original body has 976 bytes: these behavior comparisons add no exact unit
or extra direct-case count.

```bash
scripts/repo-python tests/test_bitmap_differential.py
scripts/repo-python scripts/compile-semantic-build.py --build bitmap
scripts/repo-python tests/test_bitmap_coff.py
```

The private feasibility source, stack caller, drivers and actual native/VC4
products are sealed under `bitmap-stack-contract-221-36` before public source
integration. Arbitrary short-header geometry, negative or unbacked traversal,
arithmetic limits, overflowing fallback paths, physical DirectDraw behavior and
active gameplay use remain open. The 455 original-only cases are reference
data; the completed shared-source batch promotes the 975 direct cases once.

The current checkpoint accepts **222 maintained functions / 105,036 direct
cases / 36 exact units / 3,518 bytes**. All 21 owners pass against the new native
library, with the completed bitmap report reused only after its full input
and product identities verify. Actual bitmap/raster/rotation compiler outputs,
all ten exact-oracle checks, VC4/MinGW builds, inspectors, ABI, resources,
storage, runtime and play controls pass. The campaign replay compares 20,654
frames and five advances separately from direct-case counts. A read-only audit
finds no concrete ABI, stack-alignment or fixture-lifetime defect. Four uniform
seeds establish selected storage fixtures for the frozen compiler build; they
do not establish arbitrary uninitialized storage or every compiler layout.
