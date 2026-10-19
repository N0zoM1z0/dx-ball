# Unsigned text advance and consumed coordinate wrap

October 20, 2026. Text drawing now stores its existing character advance as
`DxBallUInt`. This defines both original DWORD additions while retaining the
complete 150-byte exact body. All seven UI code identities, 38 actual bindings
and six accepted exacts remain unchanged. Authored recovery is unfinished:
247 exact functions and 23 complete nonexact candidates remain the current totals.

## Actual producers and consumers

Original `draw-text` at404EE0 performs `x += advance` at404F0E and
`advance += spacing` at404F64. The first sum supplies the next actual draw-glyph
call. The second sum supplies the next iteration's first sum. Retained Evidence
is `ev_163d2c095b63214d821d53492ba6108c07a18e965f5135a2e90af53cb53aadd3`.
Actual original memory-write EIPs and failed glyph Blt rectangles observe both
chains in the finite cases below; these are consumed results, not just a final
unused local value.

Change only the existing advance local's type. Names, declaration order,
expressions, parameter types, calls, headers and compiler settings remain fixed.
Unsigned usual arithmetic conversions give both compound additions modulo32
semantics. Glyph width/2 still uses signed truncating division before assignment;
the zero test is unchanged. Signed32 coordinate conversion follows the supported
VC4/GNU ABI. This is not a claim about all C implementations or uniquely recovered
historical declaration spelling.

The earlier [unsigned-RHS trial](RANKING_COORDINATE_WRAP.md#closed-text-advance-trial)
changed only the spacing addition, lost the exact body and observed a final
unused advance. It remains rejected under its own inputs. This distinct single
type model covers both consumed additions and preserves the exact body; no
additional type, name, operand or flag variant is tried.

## Finite source counterexamples

Each case uses a 17-byte initialized bank prefix: declared count2 and a complete
first glyph B with height0. The real loader's first CreateSurface fails before
any second-record read. Count2, initialized slot1 and its NULL surface survive
in the original partial owner. This is not a successful complete bank file.
The zero low32 pixel product allocates only three bitmap bytes.

| Glyph width | Text / initial X | Original consumed glyph X values |
| --- | --- | --- |
| INT_MAX | `BB` /0 |0, INT_MIN |
|1 | `BB` /INT_MAX |INT_MAX, −2147483647 |
| INT_MIN | `?B` /0 |−1073741824 |

Spacing is1. The first old instrumented case rejects INT_MAX+1; the second
rejects INT_MAX+2. The restored source completes both with the original two
Blt destination/source rectangles. In the third case, the missing glyph's
signed half-width becomes−1073741824 and is consumed by B. Both old and restored
source pass that preservation control.

The fixture runs actual loader, text and glyph bodies on both sides. Its typed
Blt callback accepts the explicitly scripted NULL source, records both complete
rectangles and returns failure without rasterization. Destination pixels/padding,
count/width/font and file-descriptor set are checked. Inspected bodies/callbacks
do not write remaining bank fields or descriptors; this is separate static
evidence, not an assertion over uninitialized record bytes or a physical driver.

Two UI-only UBSan compilations reuse every other native object. The initial
negative-width control stops at an incorrect harness expectation: driver width
is unsigned DWORD2147483648, while record width is signed INT_MIN. Preserve that
helper and both logs, correct only the two expected create-event widths, and
rerun that control on the same two libraries. Neither successful consumed case
nor compilation repeats. The initial checker never reaches resource-counter
collection; no memory-peak figure is claimed for that failed checker.
The corrected cached-library check peaks43,479,040 bytes with zero limit events.

## Complete comparison and integration

One VC4 compile checks all seven complete UI functions and38 actual bindings.
All raw and relocated function identities remain fixed, including measurement's
279/3 candidate and all six exact companions. Compile time is10.084s, peak
166,756,352 bytes, with zero high/max/OOM events under CPU0/35%,384MiB memory
high/512MiB max. No full replay or game build/run is performed.

Only native ui.c recompiles; all38 other objects stay fixed. The1.148s native
build produces library SHA-256
`a2f2ffa9a2bcfc624b52d747719ada2188a7b6074e0d928a95447626cae4396d`.
All216 unchanged existing draw-text cases and the three canonical boundary cases
pass. This verification/build scope peaks45,821,952 bytes with zero limit events.
Independent review verifies the actual complete COFF/PE bindings, exact type
delta, both instrumented rejections, corrected controls and explicit limits.
All270 authored source/object/flag/comparison receipts verify across30 closures
without replay. Six exact-ledger producer rows and235 historical semantic input
rows refresh. All249 semantic rows retain their ordered identities, scopes and
case counts, including duplicate unit names; no new semantic row is accepted.

The frozen generic compiler plan inherited the earlier measurement addresses.
An explicit correction receipt identifies404F0E/404F64 without rewriting that
plan or its started hash; model, executed hooks and actual mappings already
identify the correct text operations. Recipe, inputs and comparisons are fixed.

Private authority: `.analysis/text-advance-accumulator-20261020/`, including
independent source/result review, full comparisons/producers, original-write
observations, corrected and failed helpers, and integration/cleanup receipts.
Historical semantic scopes and case counts do not expand through input refresh.
Forty-seven closed inputs/products/helpers are archived and member-size/SHA
verified before exact-list removal. The976,412-byte archive releases7,020,544
allocated bytes net before small receipts. All623 protected SHA/size/mode/mtime
identities stay fixed; current products/caches, unique proofs and failure logs stay.
The tested bff527e game and local ZIP predate this source change and remain fixed.
Continue authored source recovery before complete game verification.
