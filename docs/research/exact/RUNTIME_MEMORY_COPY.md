# Partial memory-copy source recovery

The entire 334-byte entry at 0x00417CA0 matches the pinned LIBC memcpy member,
including both 16-byte tail tables and all 12 self relocations. Direct REA:
`ev_40f1c8b828cd093aa3050b6d8172db05b91bf3ef0dba1e470a2dac112b3901e2`.

Shared C restores forward phases for the declared nonoverlapping memcpy
contract: short unaligned byte copies, bounded destination alignment, four-byte
transports, and two/one-byte tails. Packed alias-safe views preserve unaligned
source reads and object representations without reading beyond count.

This is partial source, not complete behavioral recovery. The original also
has a reverse overlap extension. Its large unaligned branch consumes incoming
EDX without initializing it locally, as both assembly and pseudocode establish.
No guessed register value, artificial argument, corrected reverse algorithm
or portable memmove equivalence is claimed. That path remains a source gap.

One VC4 compilation yields 124/334 bytes with 333 differences. Comparison covers
the full original span, not a matching prefix; this remains a candidate. Native
and i686 strict compilation passes. All 333 old exacts, 106 candidates and 249
semantic rows are unchanged. No runtime/game checks. Inputs, pinned member and
closed two-record REA session are retained under
`.analysis/runtime-memory-copy-20261014/`.

The raster cleanup review found that the examined fragments already lie inside
the attested parent extents. They are not counted again as independent exacts.
