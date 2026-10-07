# Startup and UI evidence

REA 4.1.0 with Ghidra 12.1.4 follows `WinMain` and the real frame
caller into working-resource initialization at `0x403A00`. That function
creates the background surface, restores scores and boards, seeds random
state and measures vertical-blank timing before entering mode 4. Its shared
text, drawing and palette dependencies are maintained in a separate UI owner.
The same C source builds under the native compiler, MinGW i686 and pinned VC4.
Public headers depend only on the shared board types; platform and device
interfaces remain implementation dependencies. These are scoped reconstruction components; a playable executable is pending.

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
including mode-0 and mode-4 callers for the next batch. Those callers are
investigation evidence and have no source/semantic claims in this checkpoint.
Unresolved indirect flows and provider-derived prototypes remain limitations;
source ownership, widths and call sites were reviewed independently.

## Startup behavior

`src/startup.c` owns fifteen 44-byte score records (40-byte name plus unsigned
32-bit score), the default board filename and replaceable CRT file/RNG calls.
Initialization copies the original fifteen messages and assigns scores 150
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
oracle supplies the same CRT result on both sides; it does not claim that the
portable host's libc random generator equals the original Windows CRT.
Sprite-bank cleanup clears each count, selects the bank and visits all 255
slots. Actual maintained sprite release frees malloc-owned records, including
records whose COM surface is NULL. Allocation mode, filename and font-bank
selection survive; selected sprite bank ends at 2.

## UI behavior

`src/ui.c` executes maintained glyph search/draw bodies. Text length is explicit:
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

## Independent validation and limits

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

The production mode table now defaults device initialization to this owner;
runtime text/center/release-bank and gameplay range calls also default to the
maintained implementations. Audio, actual Windows/driver delivery, non-game
mode bodies and complete EXE integration remain pending. Earlier lifecycle
oracles retain their declared dependency boundaries.

One grouped checkpoint reruns every earlier suite, all 40 cold exact units,
eight rejection checks, native/MinGW/VC4 products, Wine inspector comparison
and saved REA verification. No new exact claim is made. Adding natural headers
changes screen-pan's compiler literal names from `$T617`/`$T618` to
`$T637`/`$T638`; both 8-byte constants and the complete offset/type/addend set
were checked against object and target before rebinding. Full comparisons
remain strict. Reports and identities are private in
`.analysis/checkpoints/startup-ui-148-40/`.
