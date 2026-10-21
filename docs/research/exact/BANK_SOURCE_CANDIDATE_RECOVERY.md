# Complete sprite-bank source-candidate recovery

October 21, 2026. The complete 1,475-byte `dxball_load_sprite_bank` at
`0x404610` is byte-exact after relocation, improving from 68 differing positions
to zero. All 17 resource companions retain their complete resolved identities;
all 12 prior exacts survive. The owner now has 13 exacts / 4,197 code bytes and
five candidates. Overall acceptance is 395 exact functions / 86,253 code bytes /
244 attached metadata bytes. All 270 classified authored entries have current
receipts across 30 compiler closures: 250 exact and 20 nonexact. The goal remains
active and incomplete.

## Bounded source family

The user's [standing authorization](../../agent/SOURCE_CANDIDATE_SEARCH.md) permits
finite natural identifier, declaration-order and genuine-scope searches from
existing binary/compiler evidence. Original source or debug files are not
required. This result reconstructs an exact declaration model, not uniquely
recovered historical variable names.

The family changes only 14 real local names and their declaration order, moving
the existing trivial `nbytes`, `bitmap` and `new_shape` declarations to function
scope without initializers. All executable operations, types, compound blocks,
parameters, headers, flags and other function bytes remain unchanged. Inverse
alpha-renaming and declaration removal reproduce the original executable token
stream. The anonymous API workspace and color-key declarations stay unchanged.

Root file-field lifetimes remain intact across short reads. Newly hoisted locals
are assigned before every use; their addresses do not escape and no destructor
is introduced. Published bank records remain live array rereads rather than a
cached allocation pointer. Pitch is still captured before Lock, and failure
still preserves the original partial publication, leaks and selected bank.

A frozen dictionary allows at most 16 meaningful synonyms per role. The offline
solver retains 64 assignments and generates 12 distinct full source candidates
in 22,393 states / 0.915 seconds, below its million-state / 15-second limits.
The first candidate is exact, so the other 11 are never compiled. One separately
declared formatting-only publication compile removes whitespace remnants and
preserves every one of the 18 resolved code identities. Neither frozen search
inputs nor the failed metadata-preflight receipt are overwritten.

## Compiler mechanism and observable result

The retained [frontend traversal](VC4_FRONTEND_SYMBOL_ORDER.md) computes the
unsigned name hash `h = byte + (h >> 7) + 4*h`. The ordinary root table emits
ascending `hash & 15` buckets, reversing insertion within a tied bucket. The
solver also screens declaration orders using the actual backend LOAD rank,
not the leaf rank alone:

```text
a = key >> 8; b = u32(a - key) >> 4
leaf = 16 | ((b - a + key) & 15)
load = ((leaf - 0x2d) & 15) | ((leaf + 0x10) & 0xfff0)
```

Existing current-source records supply the predicted initial ID 28266. The
selected model predicts width rank 43 >= height 35 and row 41 >= pitch 33.
Those changed-source IDs and ranks are screening predictions, not newly observed
compiler runtime values. Complete emitted equality establishes the actual frame
and product order, independently of that prediction.

| Role | Selected local | Original and matched EBP displacement |
| --- | --- | ---: |
| Pixel cursor | `source_index` | -4 |
| Character byte | `char_code` | -8 |
| Allocated record | `shape` | -12 |
| Captured pitch | `destination_stride` | -16 |
| Input pixels | `bitmap` | -20 |
| Column | `x` | -24 |
| Height | `h` | -28 |
| Byte count | `raw_size` | -32 |
| Row | `pixel_row` | -36 |
| Bank slot | `shape_number` | -40 |
| Record count | `shape_count` | -44 |
| Baseline | `y_adjust` | -48 |
| Width | `bitmap_width` | -52 |
| Previous bank | `old_sprite_bank` | -56 |

The 180-byte frame also retains key -64, API description -180, result -72 and
pixel -68. The original width-first product at `0x404714` and row-first product
at `0x404B29` are both restored. The complete resolved/original bank SHA-256 is
`2452dfc6fcc3d7da24d923b39a74f6724c960a781f5a1100befe4ec33add5edd`.

## Verification, adoption and limits

Both actual legacy compiles use the unchanged nine-input / nine-flag resources
recipe. Each comparison covers all 18 dedicated function COMDATs, all 262 actual
relocation occurrences bijectively, six entire literal carriers against their
original PE payloads, internal targets and the complete symbol/section cohort.
The bank's generated literal name changes `$SG28280` to `$SG28283`; it retains
its separately attested original target and complete payload. No ordinal-only
mapping, copied instructions, fake locals, padding, flag sweep or old-object
mixing is used. Independent reviews recompute the full owner proof.

The formatted source and whole compiled object are installed together. The
maintained native target builds with all 41 command configurations unchanged;
38 companion objects remain unchanged. The existing ten bank cases pass:
seven real SBK files and three synthetic normal/empty/create-failure cases,
including retry, publication, pixels, cleanup and bank restoration checks.
Only dependency/source hashes refresh in the 249 ordered semantic receipts;
historical case sets, scopes and oracle seals are not represented as rerun.

Private authority is `.analysis/bank-source-search-20261021/`, including the
installed comparison, authored coverage, adoption and member-verified archive.
Old source/products/ledgers remain recoverable from the rollback evidence;
unused candidates, proposal objects and copied inputs are retired only after
member size/hash/mode verification. Current products, useful caches, tools,
originals and the 141-record compiler snapshot are preserved.
The closed phase archives 77 files in 1,280,296 bytes, releasing 1,900,544
allocated bytes net before journals. Full modes and nanosecond timestamps remain
in the recovery descriptors; no current accepted product is deleted.

Serial heavy runs use CPU0/35%, 384 MiB high / 512 MiB maximum, with zero recorded
memory events. No new provider import, debugger watch, game relink/run, broad
historical replay or physical DirectDraw claim follows this recovery. The last
verified game EXE/ZIP predates this source checkpoint.
