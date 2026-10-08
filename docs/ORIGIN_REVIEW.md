# Reviewing runtime origins

The current ledger has **14 runtime dependencies / 289 unknown origins**.
The subsequent [sound controls](SOUND_CONTROLS.md) identify three application
entries through their REA instruction contracts and original/native execution.
The preceding [whole-object CRT review](CRT_PROVENANCE.md) identified eight more
runtime entries, leaving 292 unknown origins at that checkpoint. Its eleven
complete bodies agree with the pinned `libc.lib` after explicit relocations,
with threaded/debug controls retained. Maintained source and exact acceptance
were unchanged by that origin review. The first review below retains its historical scope and counts.

Origin identification is independent of maintained source, semantic acceptance
and byte-exact matching. The first reviewed runtime batch identifies six
entries without changing the 528 provisional extents, 214 maintained functions,
95,873 direct owner cases or 35 exact units / 3,478 bytes. Unknown origins fall
from 314 to 308. `runtime` / `dependency` in `config/function-origins.csv` records
library ownership and the current integration boundary; it supplies no new
implementation or acceptance claim.

REA's retained, closed Ghidra 12.1.4 runs provide complete instruction dossiers
bound to the original executable hash. Source from the existing pinned VC4
checkout corroborates the runtime structures below. This is an origin inference
from instructions, call relationships and source structure. It does not prove
which compiler options built the original or select among ambiguous library
symbol aliases. No new Ghidra import or function-identification database is
needed for this batch.

| Entry | Observed behavior | REA Evidence |
| --- | --- | --- |
| `0x00417750` | Null-guarded `HeapFree`, flags 0, shared heap at `0x440D70` | `ev_71abe55c26ab63d390b070c27874d920fa335c74cc9b406dcdab748a7f3bdd33` |
| `0x00417770` | Passes size and new-handler mode at `0x4234D4` to `0x417790`, preserving its EAX result | `ev_a3a114f83ee3fcc86ef4821ff90af4f85a55c61ba0cec1f6d53c4ee73add1e3f` |
| `0x00417790` | Rejects requests above `0xFFFFFFE0`, changes zero size to 1, retries allocation only when the enabled new handler succeeds | `ev_5b84dc43a44b86e3cd73f1ebfddc73bdb1f4ef29d11181f1d56181f54cc327b4` |
| `0x00417CA0` | Chooses backwards copying for overlapping destination-above-source buffers; otherwise copies forwards with alignment/tail branches | `ev_7c4ccda4f0b66e6e162c21ff7248a6806209fa96607f7d9e75dd5b00befe53a9` |
| `0x00418040` | C-locale ASCII uppercase fast path, classification/multibyte handling and locale mapping with uppercase flags | `ev_741079328a09289a6523e5a9365d6ca97b607694cbe5dd64cf98e1e917cddc67` |
| `0x00418130` | C-locale ASCII lowercase fast path, classification/multibyte handling and locale mapping with lowercase flags | `ev_b85e4d23ab3b7cd4d420c6629eca0ead2ace6d4c26aa6ec924e209ad525785d5` |

The allocation source in `crt/src/malloc.c` has the same size validation,
zero-request handling, new-mode forwarding and handler-controlled retry loop.
`crt/src/free.c` supplies the corresponding null-guarded Windows heap free.
Their structure identifies the runtime boundary despite Ghidra's incorrect
void return inference for the size-forwarding wrapper.

The locale helpers have library-name conflicts in their REA dossiers. Their
ASCII and locale paths agree structurally with `crt/src/toupper.c` and
`crt/src/tolower.c`. The source corroborates runtime ownership; no exact symbol
alias or complete multibyte runtime behavior is accepted by this review.

The copy dossier also has conflicting memcpy/memmove names. Its observed
overlap branch is authoritative for reconstruction; an inferred name cannot
justify changing it to a non-overlapping copy. The checked-out
`crt/src/intel/memcpy.asm` contains both variants and corroborates the overlap,
alignment, small-copy and tail structures. Ghidra owns 285 bytes across eleven
ranges in a 334-byte span here. The imported extent and embedded gaps remain
provisional; origin identification does not reconcile an exact replay extent.
The shared board-storage implementation already retains the observed overlap
behavior; this review changes no game C.

The private source comparison binds checkout
`97b4a530238f38b9320a21ca0cb98e4044df7916` and full SHA-256 identities:

| Checked-out source | SHA-256 |
| --- | --- |
| `crt/src/free.c` | `c135695ead944fb2f76cd341cbe8d62c9677fb043c2613d5d00e6c15d850160b` |
| `crt/src/malloc.c` | `5cf472238b41fb6e90a7142ac5c04fc6fe36806673d47b44296878f8d8e349a4` |
| `crt/src/toupper.c` | `2b56e9ed7a101e5cc6326583dc60011a70df84c2b67b61ae2f2c82dc262547d4` |
| `crt/src/tolower.c` | `5ea50ae560ca380b8b3bfdd6ebd054987a1d37a68c2996b2751e2b63a1fe6f2c` |
| `crt/src/intel/memcpy.asm` | `07b5bfd89b434ee7443e1c09a450c740c2682271d11bd4a503ce7e69824147b8` |

These source files and complete REA records stay private. No vendor source or
original payload is copied into maintained game source.

The remaining 308 unknown origins require individual evidence. Address ranges,
empty direct-call lists and Ghidra library matches alone do not settle them.
At batch entry, 22 unknown entries had complete dossiers in closed retained
runs; sixteen remain unknown after this review. That search covers only those
saved `analyze_function` records, not every snapshot facet or target function.
