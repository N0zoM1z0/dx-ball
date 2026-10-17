# Startup and UI evidence

The [device-frame restoration](exact/DEVICE_FRAME.md) restores initialization's
direct board-loader and process-exit calls and the global COM output owner.
The complete 359-byte candidate currently differs in ten bytes; the linked
surface synchronization, recovery and cleanup bodies are exact.

REA 4.1.0 with Ghidra 12.1.4 follows `WinMain` and the real frame
caller into working-resource initialization at `0x403A00`. That function
creates the background surface, restores scores and boards, seeds random
state and measures vertical-blank timing before entering mode 4. Its shared
text, drawing and palette dependencies are maintained in a separate UI owner.
The same C source builds under the native compiler, MinGW i686 and pinned VC4.
Public headers depend only on the shared board types; platform and device
interfaces remain implementation dependencies. The Windows game is integrated;
recorded play runs are in [the original-board campaign](ORIGINAL_CAMPAIGN.md).

## Exact RNG helpers

The [RNG checkpoint](exact/EXACT_STARTUP_RNG.md) restores genuine direct
`rand/srand` calls and the independent `timeGetTime` import. Range and seed now
match all31/49 bytes and all three actual relocations. The original signed
range remainder, unsigned modulo300 seed and actual storage consumers are
preserved. One startup compile verifies all five affected exact units and
sixteen recursive inputs; device initialization retains ten differences.
The unchanged158 startup cases plus one connected dispatch check pass against
the current Native library. The copied-image fixture binds actual CRT import
slots without process-wide interposition. Native/MinGW builds and the35-object
VC4 relink pass; no further legacy source compilation or live game replay.
Exact totals are173 functions /30,824 code bytes plus136 metadata bytes.
Earlier checkpoints below retain their own scopes, products and counts.

## Current text and line source recovery

The subsequent [locked-cursor recovery](exact/LINE_LOCKED_CURSOR.md) restores
the complete445-byte line footprint and all140 frame homes. Nine differences
remain in three signed comparison groups; five exact UI companions stay exact.
The following compiler comparisons describe the earlier checkpoint.

Measurement at `0x404FD0` now restores the local glyph-search loop present in
the original instructions. Its former helper call had equivalent results but
was absent from this body. The count-first search excludes the final slot;
separate accumulation branches preserve signed half-width fallback and spacing.
Compiler inlining versus explicitly duplicated original source is unproven.
The complete comparison is 279/279 bytes with eleven relocations and three
differences at offsets 33, 36 and 38: MOV/CMP operand orientation and the signed
exit branch. Its twelve-byte frame agrees. It remains a candidate; no names,
declarations or layouts were varied to force those operands.

Line drawing at `0x403070` now sets only descriptor size/flags, uses the incoming
surface at each typed COM call, stores and tests the actual Lock result, and
retains the post-Lock pixel/pitch consumers and explicit sign branches. Its
140-byte frame agrees with the original, but the complete 409/445-byte candidate
has 379 unaligned differences and no COFF relocations. Local homes/address
scheduling differ, and the original subtract/negate error-correction sequence
has no established source expression. The equivalent natural subtraction is
retained; no redundant arithmetic was invented to force code generation.

Both complete contiguous dossiers were reused from the closed 11-58 archive,
with Evidence `ev_6a25f94931f763de87b46ce0de325939c392113a9c31de1568162431ea46a545`
and `ev_25f8571b40b1ee8c589f398fa1211552c03d241352d0737d904789e2664b8af2`.
No new provider call was needed. One `/MT` matching compilation compares all
four accepted UI units and five candidates together. Its declared inputs now
match the fourteen recursively consumed project files, narrowed from 35.
The game reuses that matching object after verifying identical production
flags and 34 other object/input identities; no further source compile is needed.
Exact totals remain 169 functions, 30,238 complete code bytes and 136 metadata
bytes. All four prior UI exacts remain exact.

Native/MinGW builds pass. The final library passes 1,134 unchanged selected
UI cases: 216 each measurement/drawing/centering and 486 line cases. Actual
glyph bodies, signed bytes, NUL, duplicate/excluded codes, endpoint order,
octants, retries and whole padded buffers are compared. The fresh VC4 real-Wine
ball/pause/editor/save/reload/exit flow passes with 77 read-only states, five
captures, expected saved-bank hash, exit zero and all 49 originals unchanged.
Receipts are in `.analysis/exact-ui-text-line/` and
`.analysis/windows-play-ui-text-line/`. Other semantic scopes and prior play
controls remain historical after input refresh; no full owner or historical
validation queue was replayed. Driver rasterization, synchronized pixels,
physical audio/MIDI and nearly complete source fidelity remain unproven.

## Glyph/text implementation owner control, October18

One fixed C++ owner groups the five consecutive original entries at404CF0,
404E40,404EE0,404F80 and404FD0. Glyph lookup/drawing and text drawing/centering/
measurement share a real call graph, signed-code/font-bank contracts and the
existing spacing state. This differs from the older whole-UI C++/COM controls,
which leave the two lower glyph functions in resources. It is an inferred
implementation family, not unique recovery of the original translation unit.

The private model moves exactly five byte-identical bodies and the actual
`dxball_text_spacing = 1` definition. Complete unchanged `ui.h`/`resources.h`
retain C linkage; the new owner inherits the UI `/MT` recipe. Three serial
compiles compare all27 functions and300 actual bindings/six complete literal
references: resources16, residual UI6 and text5. No exact is gained. Glyph
lookup loses its145-byte match, becoming146/86 through one bank/slot address
producer. PCX exchanges two multiplicand loads while retaining979/851;
25 other code identities stay unchanged, including measurement279/3.
Equal size/difference counts are not code-identity evidence.

Reject the whole fixed model without selective adoption or header/order/name/
flag variants. Private `.analysis/text-glyph-owner-20261018/` retains complete
inputs, transformation, comparisons, independent reviews and final verification.
The review corrects an informal26-unchanged inference to the actual25 before
documentation/adoption. No source, claim, canonical object or delivery changes;
no native build, relink, provider, game or full replay follows. One CPU35%,
memory high640MiB/max768MiB limits hold; observed peak is167,350,272 bytes with
zero high/max/OOM events. All24 disposable copied inputs/products, including
five objects, are archived/member-hash verified before removal, releasing
118,784 allocated bytes after archive/journal costs. Tested products and useful
incremental caches remain.

## Exact score initialization and reading

The initializer at `0x406EE0` now restores all fifteen explicit name-clear,
`strcat`, and score-store phases, followed by direct CRT file calls. Its first
stable VC4 compilation matches the complete 723-byte body, with all 87 actual
relocations resolved and all eighteen consumed string operands attested,
including their terminating NULs and three independent separator literals.
The existing 125-byte bank-release unit remains exact; device initialization
remains a 359-byte candidate with ten differing bytes. No source spelling or
storage experiments were needed. Receipts are in
`.analysis/exact-score-initialization/`.

Accepted board-bank callers establish `fopen` at `0x417C20`, `fwrite` at
`0x417E70`, and `fclose` at `0x417A30`. Reuse these caller/API bindings while the
runtime origins are investigated. New REA 6.3.0 evidence establishes the
77-byte `access` implementation at `0x417FF0`, corroborated against the complete
fixed CRT `access.obj` member and its five relocations. This establishes the
API binding; its runtime origin row and unique original alias spelling remain
separate questions. Literal bytes are supported by one complete 592-byte read.

- Access dossier: `ev_3c45a24fc90e2bb90489bc9c3533d438174388a59cbd469eb9c5b5f992897241`.
- Literal read: `ev_8e62c86b8565325f7f6450aed6e6a8b3c37df251bb87cee577dfaf1a8d0776cb`.
- Archived run: `.analysis/rea/runs/2026-10-10T14-29-24.089Z-score-boundaries-590652/`.

The existing startup fixture uses `tests/native_imports.py` to bind only the
copied image's resolved ELF import slots to its existing typed stdio callbacks.
It preserves data-page permissions, checks the image owner and selected slots,
and verifies unchanged process-wide libc resolution. The canonical library,
shared recovered source, real default libc calls and existing cases remain
the actual maintained inputs. No libc symbol is exported by the global shim.
The 158 existing startup cases and one connected dispatch check passed once,
including poisoned name tails, access/open branches, ignored results and exact
660-byte writes. This transport is fixture infrastructure, not original code.

The following persistence recovery also restores `read_scores` at `0x406CC0`
as genuine `fopen` / `fread` / `fclose` calls with an early NULL return and no
local storage. Its first compilation matches the complete 94-byte body and
all ten relocations. The initializer and bank release retain their full exact
matches. The original `rb` and `score.dat` storage at `0x42148C` and `0x421490`
is attested by REA Evidence
`ev_50dc90850c2746cf0f049db856c7e3f770b112e29d726f2aabb23149ebf2b3e7`,
archived in the 2026-10-10 14-38 literal-request run. The copied-image fixture
now binds its existing typed `fread` callback too. Fresh checks are recorded
in `.analysis/exact-score-reading/`, with the complete score-insertion recovery
described in [game-over evidence](GAMEOVER_OWNER.md).

## Entries and retained observations

Every entry below is contiguous and has equal owned/span lengths. Its imported
extent was reconciled with REA's inclusive body ranges and instructions. The
Evidence IDs identify static observations, not execution proof.

| Address | Maintained entry | Owned/span bytes | REA Evidence ID |
| --- | --- | ---: | --- |
| `0x00403A00` | `initialize_device_state` | 359 | `ev_8681cf5b5b27dd9358b476476e4b5b63d76ccbb091fc483c58c3cea670a6e1db` |
| `0x00406EE0` | `initialize_scores` | 723 | `ev_8dac6e01bb85d2646a688aaa07a710a92aa40634ba392304d3263f05ee92cbd6` |
| `0x00406CC0` | `read_scores` | 94 | `ev_60906ff615d2fceb6d7e4cb83c367f0f2612498b4c30cf1d1b20cd4d1c80f2ea` |
| `0x00403B90` | `seed_random` | 49 | `ev_17cf72657ba0a29ec43b5716ed09347c3645e4eaa4374f80256a5eb7b58296f6` |
| `0x00403B70` | `random_range` | 31 | `ev_dcaab4c60684caf5c24767829432c46b7d7fc94f93fbcd7d15813b604710e8f1` |
| `0x00403CB0` | `release_sprite_banks` | 125 | `ev_446beb8f1f3a4a6caef3507317a6cc511c2d3afc8ebaf75fecd4cfa3ff164d8e` |
| `0x00404EE0` | `draw_text` | 150 | `ev_163d2c095b63214d821d53492ba6108c07a18e965f5135a2e90af53cb53aadd3` |
| `0x00404F80` | `draw_centered_text` | 73 | `ev_3aaaa3e23bdd7e6a30fce980204aff52420ded4f7e5cbb9015195196594b429a` |
| `0x00404FD0` | `measure_text` | 279 | `ev_6a25f94931f763de87b46ce0de325939c392113a9c31de1568162431ea46a545` |
| `0x00403070` | `draw_line` | 445 | `ev_25f8571b40b1ee8c589f398fa1211552c03d241352d0737d904789e2664b8af2` |
| `0x00403230` | `fill_rect` | 85 | `ev_b99b4211419ba41390b72f70b56be67edc16632cfcad034c0a02edccf4b57629` |
| `0x0040A880` | `rotate_palette_right` | 234 | `ev_35f62db7fc86382109be50f01f5d0ead909598ff5cb4328d8d76157b157b21d0` |
| `0x0040AA60` | `rotate_rgb_colors` | 188 | `ev_d69a03478a3300403b907eadb1d092d72ea91325ee9a2d51042a1105207b5bb3` |
| `0x0040AB20` | `set_palette_rgb` | 108 | `ev_677c089ab1d99c09f648bf51f8d486dc81df271573b32af3ba3f53fdb5c50e68` |

The earlier working-resource dossier is retained in the 11-04 interactive
archive; it was reused rather than queried again. The remaining dossiers are
in the closed 11-58 archive, which retains 198 cumulative Evidence records,
including mode-0 and mode-4 callers for the next batch. That subsequent
[menu/splash checkpoint](INTRO_OWNER.md) now maintains those callers; their
source and semantic claims are separate from this startup/UI acceptance.
Unresolved indirect flows and provider-derived prototypes remain limitations;
source ownership, widths and call sites were reviewed independently.

## Startup behavior

`src/startup.c` owns fifteen 44-byte score records (40-byte name plus unsigned
32-bit score), the default board filename and direct CRT file/RNG calls. Controlled native
fixtures bind those actual imports only inside their copied library image.
Initialization clears each leading name byte, appends its message and assigns scores 150
through 10. Bytes after the terminating name remain untouched. Only
`access("score.dat", 0) == -1` attempts to create the default file; other results
retain the existing shared FILE slot. Read and write operations preserve the
original element sizes/counts. Failed opens, short reads and ignored write/close
results retain the original behavior. Successful close leaves a nonzero,
closed handle in shared `0x4265C8`, also used by board I/O.

Device initialization requests a 640 by 480 surface with descriptor size 108,
flags 7 and caps `0x840`. COM failure output is stored before process exit 1,
which cannot return. Success clears the end request, sets mode/next mode 4,
initializes then reads scores, loads `default.bds`, and seeds RNG using
`timeGetTime() % 300`. It clears primary, creates the palette and waits for
vertical blank 32 times. Unsigned elapsed time must be strictly greater than
400 to enable the vblank path. Reduced mode equal to 1 disables it; software
mode equal to 0 with disabled vblank forces reduced mode. The final clock read
sets the frame wait tick. Undefined descriptor fields are outside the claim.

Fresh-image observations bind display buffer count, device reset request,
draw-to-primary and software-only defaults to 1 at `0x4228A0`, `0x4228A8`,
`0x4228D0` and `0x4228D4`. REA read-bytes Evidence
`ev_15e36be26a16cac88b405a54b96696f27656d1933477c446ae88314b70e44f1c`
was reconciled with the loaded original and an untouched native library.

Random-range behavior is the CRT result modulo a nonzero signed divisor. The
historical owner oracle supplies the same CRT result on both sides. The
[random runtime follow-up](RANDOM_RUNTIME.md) now recovers the actual global
generator and connects real production defaults across all builds; its separate
focused fixture compares the unmodified original sequence and full state.
Sprite-bank cleanup clears each count, selects the bank and visits all 255
slots. Actual maintained sprite release frees malloc-owned records, including
records whose COM surface is NULL. Allocation mode, filename and font-bank
selection survive; selected sprite bank ends at 2.

## UI behavior

`src/ui.c` measures with its observed local search and draws through the
maintained glyph body. Text length is explicit:
embedded NUL and high bytes participate in search. Failed lookup advances by
half the width of slot 1, without spacing; successful glyphs add spacing.
Measurement includes the last glyph's spacing. Centering subtracts signed
half-width. Zero/negative counts read no characters. Text spacing starts at 1
(`0x421084`), supported by read-bytes Evidence
`ev_912015788fbe2640da31a1a231acd1da38864e8c84e5222e791a738e4cbbe066`.

The line algorithm obtains a descriptor, retries Lock until success, writes
both endpoints and unlocks. Its two branches use different error thresholds:
X-major stepping tests `error > dx`; Y-major stepping tests `error > 0`.
The original pixels are preserved, including this asymmetry. There is no
clipping; acceptance requires valid storage and nonoverflowing coordinates.
Rectangle fill checks the selected rectangle, flags `0x400`, effect size 100
and fill color. It does not compare unspecified original effect-stack bytes or
claim hardware rasterization.

Palette operations run when the cursor gate is not equal to 1. Right rotation
shifts complete entries and retains the first entry's flags while replacing
its RGB with the last color only for wrap equal to 1; otherwise it inserts black.
Setting RGB preserves flags and submits one entry. RGB-pool rotation shifts
32-bit integers by three and converts the new leading triple to bytes before
SetEntries. Its count is an integer count, not a byte count: mode 4 passes 66.
This checkpoint accepts valid palette bounds and pools of at least three ints.

## Recorded startup/UI checks

`tests/test_startup_differential.py` executes six unmodified original entries
for 158 direct cases, plus one separately counted connected frame-dispatch
check. Controlled file APIs check ordering, exact write bytes, poison tails,
failed opens and short/full/oversize reads. Actual clock, palette and resource
release bodies execute. The existing board-loader body at 0x40CC30 is a declared
call boundary in this startup oracle, with independent acceptance in the board
suite; it is reused rather than reimplemented or counted again. Failure tests compare original stopped execution with
native child-process exit, including retained/null COM outputs.

`tests/test_ui_differential.py` executes eight original entries for 1,266 cases.
Actual glyph bodies cover three banks, signed high bytes, NUL, duplicate codes,
exclusive slot counts, missing glyphs and signed centering. Raster tests compare
whole pixel buffers and padded rows across octants, reversed endpoints,
zero-length lines and Lock retries. Palette tests compare all bytes/flags,
submitted ranges and RGB-pool canaries. DirectDraw callbacks supply storage and
record calls; they do not implement the source algorithm or its x86 counterpart.

The production mode table defaults device initialization to this owner;
runtime text/center/release-bank and gameplay range calls also default to the
maintained implementations. Subsequent screen and audio work is recorded in
[the runtime](RUNTIME_OWNER.md), [sound](SOUND_OWNER.md), and
[Windows integration](WINDOWS_ADAPTER.md) notes.

The historical startup/UI checkpoint reran every earlier suite, all 40 cold exact units,
eight rejection checks, native/MinGW/VC4 products, Wine inspector comparison
and saved REA verification. It made no new exact claim. Adding natural headers
changes screen-pan's compiler literal names from `$T617`/`$T618` to
`$T637`/`$T638`; both 8-byte constants and the complete offset/type/addend set
were checked against object and target before rebinding. Full comparisons
remain strict. Reports and identities are private in
`.analysis/checkpoints/startup-ui-148-40/`.
