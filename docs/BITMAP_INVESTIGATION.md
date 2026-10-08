# Bitmap loader: investigation in progress

The saved REA function dossier for `0x00409F70` retains a contiguous 976-byte
body through `0x0040A33F`, under Evidence ID
`ev_e408e41080570698d5068c6aa811cbae0a93e65442822fc191ea85ea46c93cad`.
Its complete private record is in the closed 10-33 interactive run, SHA-256
`a638c4ad17795b11803e0b0337f1d0221e88c417d8ef662a9190f8ec7da9d803`.
This investigation reuses that record without another Ghidra import. Origin,
maintained source, semantic acceptance and exact matching remain open.

## File and surface boundaries

Instructions establish two cdecl stack arguments: a DirectDraw surface and a
path passed to `CreateFileA`. The inferred `uint *` path type is not a recovered
source declaration. File opens request access `0x80000000`, share 1, disposition
3, attributes `0x80`, and null security/template handles. If the primary open
returns `-1`, the routine copies a prefix from `0x422798`, concatenates the path,
and retries. That prefix's initial bytes and producers remain unresolved. The
already maintained sound loader uses another address, `0x42106C`; its prefix
must not be substituted here without evidence.

The sequential reads request 14 header bytes, 40 information-header bytes,
1,024 palette bytes, and the low 32 bits of width times height for pixel data.
The information-header bit count must equal eight. The body tests `ReadFile`'s
Boolean return without checking the transferred count. It does not validate
the file signature, compression or pixel offset, seek to the declared offset,
or account for BMP row padding. Successful short reads and invalid geometry
need separate domain review before source acceptance.

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

## Original-machine probe and next steps

```bash
scripts/repo-python tests/probe_bmp_loader.py
```

The probe executes the hash-verified, unmodified original x86 body and its
actual string/memory helpers. It controls only file, allocation and COM
dependencies, plus input data and caller stack storage. Twenty-three fixtures
check three positive pitches with four stack seeds, nine failure gates, and
two fallback paths. Comparisons cover complete destination storage and guards,
unchanged source pixels, converted RGB bytes, all 256 fourth bytes, ordered
calls, return values and cdecl register/stack preservation. A deliberately
non-BM header still reaches the successful path. Nonzero unlock/set-palette
results and a false close result still return one.

The complete private report is `build/reports/bmp-investigation/original.json`.
It records the original/dossier identities, nine input hashes, every fixture
and the controlled-boundary limitations. It is original-only investigation
evidence: no maintained C comparison, real file/DirectDraw behavior, short-read
acceptance, function-origin promotion or new semantic case count is claimed.
It generates no EXE, compiler object or raw stream archive.

The missing prefix bytes/producers and incoming references are prepared as
three requests in `config/rea-bitmap.json`, checked against REA's retained
catalog. They remain unexecuted while the full campaign owns the shared
compiler/Ghidra/Wine session:

```bash
scripts/rea session config/rea-bitmap.json
```

Retain their Evidence IDs and coverage limitations. Empty historical incoming
reference lists do not prove this routine is unused. Resolve the prefix and
palette-flags contract before selecting natural shared C, then compare that
implementation against original execution in a related batch.
