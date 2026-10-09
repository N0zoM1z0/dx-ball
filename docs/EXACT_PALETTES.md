# Palette tail loaders and surface binding

This batch restores three complete palette emissions, adding 1,020 exact bytes
and one source mapping. The checkpoint has **253 source-present entries / 247
directly validated entries / 112,273 distinct direct cases / 48 exact units /
6,012 bytes**. The frozen existing owner batch and grouped cold replay pass. The private
mapping preparation is diagnostic evidence; acceptance uses the cold outputs.

| Entry | Maintained unit | Complete bytes | REA Evidence |
| --- | --- | ---: | --- |
| `0x409790` | load-live-palette | 337 | `ev_16d6d2a7bdc6f682c0baf44faef5d7f479199cf2170180bd5d51533d911006fc` |
| `0x4098F0` | load-saved-palette | 307 | `ev_983db51f277ff605c3d36619e21a5f2c81318101a225c46ca1c1c41b528f159c` |
| `0x409A30` | load-surface-palette | 376 | `ev_98c57eefa7609b36f191aa5039d7824322068c7f66ab662dc571d9bd57642930` |

Two bounded `analyze_function` operations in `config/rea-palette-loaders.json`
review the existing loaders with pinned REA/Ghidra. The surface constructor
reuses its retained, closed dossier. Each original body is contiguous and ends
in `ret`; all original bytes and complete emitted COMDAT extents are compared.
No relocation, padding or instruction is excluded.

Each loader opens its path in binary mode, seeks 768 bytes before EOF and reads
256 RGB triples. The fourth palette byte is untouched. The live loader closes
the file before calling palette SetEntries with flags zero, start zero and
count 256; the saved loader only updates the saved RGB buffer. The restored
surface loader reads the live buffer, closes the file and calls DirectDraw
CreatePalette with capability value four, the live entries and the global
palette output pointer. A nonzero HRESULT returns immediately. Successful
creation calls surface SetPalette. The original does not release the old
palette or test the SetPalette result. The maintained API is void: its final
EAX contains an incidental HRESULT, with no proven meaningful integer return.
The constructor has no recovered callers or incoming references; that does
not establish that it was unused. Active use remains unresolved.

The resource exact build uses `/ML`, replacing `/MT` for this translation unit.
VC4 stdio.h defines getc as its FILE count/pointer expression and then removes
that macro for `_MT`; `/ML` consequently emits the observed inline reads and
_filbuf fallbacks. `/MT` emitted 199 and 169 bytes for the existing loaders;
`/ML` restores their full 337 and 307 bytes. The separate CRT provenance work
found 13 of 13 representative libc.lib bodies matching 546 original bytes,
versus nine for libcmt.lib. These observations support the selected compatible
compiler model; they do not prove unique historical flags. Other exact builds
retain their existing flags. Source, structures and function bodies are shared
by native, MinGW and VC4 without profile-selected implementations.

The three equal `rb` literals have distinct original addresses `0x422788`,
`0x42278C` and `0x422790`. Each COFF literal and each original target is checked
against `726200` before its explicit DIR32 binding. CRT calls bind to fopen
`0x417C20`, fseek `0x418310`, _filbuf `0x418220` and fclose `0x417A30`.
Palette globals and byte addends are explicit in `config/match-units.toml`.
Compiler-generated literal ordinals in other units are refreshed only after
independent content, offset, type and addend verification.

An ordinary unnamed forward declaration keeps the restored two-parameter ABI
and all previous exact units intact. In the pinned VC4 compiler, naming those
prototype parameters changed unrelated keyed-blit address arithmetic from
195 to 199 bytes. The definition retains meaningful parameter names. This is
a compatible declaration form, not a recovery of historical identifier names.
Private failed emissions are diagnostic evidence, not accepted source.

The existing 22 owner scripts replay once against frozen sources and one
native library. Existing direct live/saved palette cases are reused; no new
tracked tests, fixtures, semantic rows or campaign observations are added.
The new surface entry has complete-byte acceptance without an independent
direct-case claim. A private three-case check reuses the existing target/native
resource boundaries for creation success, creation failure and attachment
failure, checking complete RGB/flag storage, palette replacement and call order.
Its three cases are not added to tracked direct-case counts. Controlled COM callbacks do not prove physical DirectDraw
hardware behavior. One grouped cold replay checks all 48 exact units, followed
by the existing rejection controls and a MinGW build.

The >=95% complete-source objective remains open. The provisional inventory
contains 270 unknown origins and five identified runtime dependencies without
maintained source; its full authored denominator remains unproven.
