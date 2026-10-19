# Ranking right-edge coordinate subtraction

October 19, 2026. Ranking drawing now makes the original DWORD subtraction
explicit before passing the signed coordinate to text drawing. All eight
complete gameover code identities remain unchanged, including seven exacts.
Ranking stays 403 bytes against original 404, with 330 strict differences.

## Original operation and source

The original complete 404-byte body contains this chain:

| Address | Operation |
| --- | --- |
| 406C81 | Load right edge 630 into EBX |
| 406C8E | Call actual measure-text at 404FD0 |
| 406C96 | SUB EBX,EAX; PUSH EBX |
| 406C99 | Call actual draw-text at 404EE0 |

The source expression becomes
`(DxBallInt)((DxBallUInt)630 - (DxBallUInt)dxball_measure_text(...))`.
The supported VC4/GNU 32-bit-int conversion preserves the DWORD result and its
signed coordinate interpretation. Original cast spelling is unknown. The
existing [whole-body correspondence](RANKING_OWNER_FAMILY.md) still explains
the one-byte shortening through the selected-row comparison producer; all
36-byte frame homes agree. This change does not resolve that compiler context.

The retained original carrier is operation05 of
`2026-10-07T13-44-46.898Z-interactive-3331671`, Evidence
`ev_a42b5c952ba3c544d58bf1b3c0c2456c9e13f6149d7090c32e2952888fd6ff3e`.
The complete carrier, actual instruction bytes and pinned target were checked
without a new provider query.

## Finite owner counterexample

An actual 17-byte font has count2, glyph width268435455, height0, code '1' and
baseline0. The existing CreateSurface failure path publishes those fields with
a NULL source surface. Fifteen empty-name score rows hold unsigned11111111;
spacing is1 and no row is selected. Actual measurement returns INT_MIN, and
the original subtraction produces signed X=-2147483018. The old instrumented
source fails at `630 - INT_MIN`; the restored source completes all15 rows and
120 glyph Blt calls with the same original/native coordinates and rectangles.
Later text additions, glyph right edges and baselines stay representable.

The fixture executes actual loader, formatter, measurement, ranking, text and
glyph code. Typed COM callbacks explicitly accept the NULL source and return
failure without rasterization. All660 score bytes, destination pixels/padding
and descriptors across ranking stay fixed. This is a direct ranking-entry
boundary fixture, not whole-game initialization or physical-driver evidence.
Two gameover-only UBSan compilations reuse every other native object.

One VC4 compile compares all8 complete functions,234 actual bindings and13
entire literal references. All raw/resolved bodies remain identical; seven
exacts/2775 bytes survive. Duplicate score.dat payloads keep their separately
attested targets through identical whole bodies and actual field offsets/types/
addends, rather than generated symbol ordinals. A candidate literal extending
past a data section cannot match; actual bindings still require full payloads.
Independent source and result reviews retain these checks.

The incremental native build changes gameover.c only. Library SHA256 is
`cd30d703f106cece05e62912d6033519b2c7238f25e26bc456fa3464efe83e2e`.
All17 unchanged existing selected-row cases pass with maintained state/buffer
assertions. Authored coverage remains248 exact/22 candidates across30 current
closures; overall393 exacts/84633 code bytes/244 metadata bytes stay fixed.
Semantic scopes/case counts do not expand when input hashes refresh.

## Closed text-advance trial

One separate proposal changes only `advance += spacing` to an unsigned-RHS
compound assignment. Its complete seven-function UI comparison preserves six
other identities/five exacts, but draw-text loses its150-byte exact body and
becomes153 bytes with20 differences. No second variant is tried.

An actual17-byte font with width INT_MAX and one-digit score0 rows isolates the
final glyph advance. Original execution stores INT_MIN at404F64 exactly15 times;
old UBSan source rejects INT_MAX+1 and the proposal completes. In this witness,
the wrapped advance is unused before each draw-text return. This establishes
the arithmetic boundary, not a missing consumed coordinate or a broader
exceptional-input contract. Reject the proposal for this source-fidelity work;
keep canonical ui.c and its150-byte exact body. This does not establish that
every possible text input avoids signed overflow. The prepared216-case selector
is not run; no canonical UI/native build or claim change follows this trial.

Private authorities are `.analysis/ranking-coordinate-wrap-20261019/` and
`.analysis/ui-advance-wrap-20261019/`: full comparisons, producer identities,
reviews, finite cases, selected17-case receipt and the UI rejection decision.
Compiler/native work is serial on CPU0 at35% CPU,384MiB high/512MiB max. Ranking
VC4 compilation takes14.106s, peaks167391232 bytes and has zero limit events;
the17-case process takes10.596s including startup, peaking53428224 bytes.
No relink, game run, full replay or new exact claim follows. The verified
EXE/ZIP still represents717cc2f and predates these source corrections.

The two closed trials archive49/31 copied inputs, temporary products and helpers
in1080999/680666-byte archives. Every member's size/SHA256 verifies before exact-
list removal, releasing10285056 allocated bytes net before the small receipts.
The unexecuted UI selector is labeled separately. Current objects/native library,
tested game/ZIP, original evidence, comparisons, reviews and useful caches stay;
protected SHA/size/mode/mtime identities remain fixed across cleanup.
