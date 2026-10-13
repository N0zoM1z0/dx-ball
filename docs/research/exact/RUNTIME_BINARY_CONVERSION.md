# CRT binary conversion and format entries

The two 24-byte format entries at `0x41D540` and `0x41D560` now have maintained
source and complete exact comparisons. Both actual relocations and all 24
initialized bytes of each format record match. The earlier three float-owner
exacts preserve 109 bytes. Totals are 244 exact functions / 63,352 code bytes /
136 metadata bytes. Source presence becomes 291.

The converter at `0x41D370` is fully implemented but remains a 459-byte,
157-instruction candidate with 94 unmasked differences. Its twelve calls bind
the actual zero, copy, rounding and shifting helpers. Input fields are a packed
two-byte tail, two four-byte mantissa limbs and a two-byte sign/exponent word.
The three-word work arrays preserve the original 96-bit representation.

The original packs its output into the exponent register without storing that
word back to the work array. Restoring this scalar lifetime removes eight bytes
from the initial 467-byte model. The nonnormal branch computes its shift count
before copying the saved mantissa; preserving that write reduces differences
from 107 to 94. A generic output pointer leaves code unchanged. An explicit
sign/exponent-word capture yields 108 differences and is rejected.
Five bounded source emissions compare all six complete owner functions; one
final canonical compilation follows the header-comment clarification.

The actual six-field records are `(1024,-1023,53,11,64,1023)` and
`(128,-127,24,8,32,127)`: exponent limits, precision, exponent width,
destination width and bias. Their full 48-byte initialized section was already
independently placed and verified by CRT provenance, Evidence
`ev_d7232432834b594d332edd39a56ef7400ba45fdd9a525df682a8746c5b27b6d6`.
Each current static record's full contents are also included in its exact unit.

Closed REA run `2026-10-13T08-51-15.701Z-requests-1248177` supplies complete
information, assembly and pseudocode. Converter assembly is
`ev_df281d1da85e0c065986f4563fa3a5271624480c9f676fe5b37ec7c82d325160`;
format entries are `ev_ad8eb262a5f221f6fedbcd775cd752d62682af9a7d4d2ef64957db4ab781f93a`
and `ev_d26a1cb376292a4a1f5753e1cf32f291493b90f38d24b0b9fe5b1b66ce3f1817`.
All records retain the configured original digest and complete contiguous extents.

Native and i686 standalone objects compile the same C source with the legacy
integer/float alias model (`-fno-strict-aliasing`). Source uses the two recovered
format records and backed, aligned destinations. Runtime execution, the decimal
parser, remaining mantissa helper source and game integration remain open.
No test or game campaign runs. The other 239 exact producers and all 34 authored
candidates are reused unchanged. Current receipts and source stages are in
`.analysis/runtime-binary-conversion-20261013/`.

Eight retired object/report carriers are gzip and decompression-SHA256 verified
before raw removal, releasing 1,265,664 allocated bytes including the receipt.
Canonical and portable products remain available. The receipt grew to a second
filesystem block; its net-saving calculation is corrected without recompression.
