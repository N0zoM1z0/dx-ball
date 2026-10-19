# PCX destination-coordinate increments

October19,2026. Both PCX pixel paths now explicitly preserve the original
unsigned32 increment followed by signed-coordinate clipping. Exactly four
assignments change; all18 complete resource machine-code identities survive.
PCX remains979/862 bytes with850 strict differences. No exact is gained/lost.

## Original contract

The complete862-byte original decoder contains these DWORD instructions:

| Path | Original increment | Current source value |
| --- | --- | --- |
| RLE row wrap |409DDB |destination_y |
| RLE pixel advance |409E2E |destination_x |
| Literal row wrap |409E5D |destination_y |
| Literal pixel advance |409EB0 |destination_x |

Each C++ `value = value + 1` becomes
`value = (DxBallInt)((DxBallUInt)value + 1)`. The supported VC4/GNU32-bit-int
conversion preserves the stored DWORD bit pattern. Subsequent comparisons
remain signed. Historical cast spelling is unknown. Header reads, signed16
maxima, inclusive product bound, run count, source row/column, pixel address
formation, Lock retries, Unlock and
independent palette-mode calls stay unchanged. This is not a PCX format repair
or another header/frame/operand-order experiment.

Signed16 header maxima bound the other decoder counters below INT_MAX, even
including a63-pixel packet overshoot. Destination coordinates instead begin
with unrestricted signed API arguments, so their four increments need the
explicit modulo32 contract. Inspected real-game callers pass0,0; this does not
claim the exceptional offsets occur during shipped gameplay.

Original retained assembly Evidence:
`ev_93b5290136b33bfcc5cee2cc186d2f6440c5a8c1595647d46ec6172e7d5c8566`.
The [complete packet correspondence](EXACT_PCX_PACKET_LOOP.md) accounts for227
original/current instructions, including these sites. Independent review binds
all four raw instruction bytes to the pinned original body and verifies normal
Unlock409EC6, fclose409ED0 and return409F0D.

## Four finite counterexamples

All inputs have a complete128-byte header, palette mode0 and a valid8×6 surface
with three padding bytes per row. No pixel address forms on these clipped paths.

| Path | xmax,ymax | Encoded bytes | Destination offset | Total file bytes |
| --- | --- | --- | --- | ---: |
| Literal X |0,0 |07 |INT_MAX,0 |129 |
| RLE X |0,0 |C1 07 |INT_MAX,0 |130 |
| Literal Y |1,2 |07 08 09 |0,INT_MAX |131 |
| RLE Y |1,2 |C3 07 |0,INT_MAX |130 |

The Y increment occurs on the third pixel, after the column exceeds xmax.
Actual original x86 decoding returns through normal Unlock/close and leaves all
66 surface/padding bytes unchanged. Each old instrumented source fails at its
corresponding INT_MAX+1 statement. All four restored cases match the original
external events, bytes and cleanup, using actual native stdio. The case report's
original increment address labels the statically verified site; no breakpoint
or instruction-level runtime trace is claimed. Two resource-only UBSan source
compilations reuse every other native object.

## Complete comparison and integration

One VC4 resource compile compares all18 complete functions,262 actual bindings
and six entire literal references. Every raw/resolved body remains unchanged,
including11 exacts/2,577 bytes. Complete COFF differences are confined to two
timestamp bytes and the later space-literal symbol spelling. Full literal bytes
and targets, rather than generated symbol ordinals, justify the binding refresh.
Authored coverage stays248 exact/22 candidates across30 verified closures;
overall393 exacts/84,633 code bytes/244 metadata bytes remain.

Only resources.cpp rebuilds in the native library. Its SHA256 is
`78d8e0e6f9f63e8e19a277f3df7dc4e722243eff3fb2e605d30be5127dfb8c6c`.
The99 unchanged existing PCX cases pass:15 cases across five original images
and three modes, plus84 fixture cases. Existing pixel/padding, palette and
ordered-event assertions stay unchanged. Historical semantic scopes/counts do
not expand when source-input hashes refresh. The270 authored source/object/
comparison receipts verify without a full replay.

Heavy work is serial on CPU0 with35% CPU,384MiB high/512MiB max. VC4 compilation
takes13.956s and peaks167,923,712 bytes; the99-case process takes32.293s including
startup and peaks62,566,400 bytes. All recorded high/max/OOM counters are zero.
No game build/run or physical-driver claim follows; the last verified EXE/ZIP
still represents717cc2f and predates this and the preceding boundary corrections.

Private `.analysis/pcx-coordinate-wrap-20261019/` retains complete comparisons,
producer, independent result review, counterexamples,99-case selection, adoption
and current coverage. The independent original-site review is
`.analysis/pcx-destination-wrap-review-20261019/review.json`. All37 closed inputs,
products and executed helpers are member-hash verified in a1,074,769-byte archive
before removal, releasing7,815,168 allocated bytes net after archive cost and
before the small manifest/cleanup receipt. Current tested products/caches stay.
