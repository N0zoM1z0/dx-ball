# Exact point-distance workspace

`dxball_point_distance` at `0x00402610` now matches its complete 130-byte
original body and four CRT call relocations. A 32-byte measurement record
groups the four doubles already consumed by the calculation: absolute X/Y
separations, their squared sum and the square-root result.

The original 48-byte frame places X/Y differences at EBP-8/-16, squared
distance at EBP-24 and distance at EBP-32. Four compiler-generated integer
conversion temporaries occupy EBP-36 through EBP-48. Both fabs results are
stored and popped before the products; the final sqrt result is stored without
popping before the original integer conversion. Every byte now agrees.

The [overlap workspace](GEOMETRY_FRAME_RECORDS.md) first changes the previously
127-byte distance emission into the original 130-byte sequence with ten home
differences. The measurement record removes those remaining differences in
the final geometry compilation. Point-angle preserves its 109 exact bytes
and complete constants. Original declaration spelling remains unknown.

Six existing finite inputs execute original, complete relocated VC4 and native
bodies with identical results, including zero, diagonal, negative coordinates
and a two-billion-unit separation. Actual original CRT math executes. The
same product passes 8,000 existing rectangle cases and 708 frame cases.
Linux and MinGW build; VC4 relinks the two changed owners with 35 verified
unchanged objects and no extra legacy source compilation.

All 223 accepted units and input closures verify: 55,481 code bytes and
136 separate metadata bytes, with 50 authored functions remaining nonexact.
No game campaign runs. Original evidence is
`ev_c00ff92fb8c6b7716952bed048968fc8ee66daaf782d6dd40d19389de053df98`,
operation 04 of run `2026-10-09T16-15-21.487Z-interactive-1181426`.
No new REA query is needed. Four geometry stages, before inputs, full comparisons,
case receipts and verified compressed products remain in
`.analysis/rectangle-overlap-record-20261012/`.
