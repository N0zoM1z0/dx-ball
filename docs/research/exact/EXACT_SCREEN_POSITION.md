# Exact screen-point position record

`dxball_hit_screen_point` at `0x004116C0` now matches its complete 337-byte
original body. The remaining 26 differences in the
[coordinate-stages checkpoint](SCREEN_POINT_STAGES.md) were the two local
coordinate homes. One eight-byte position record, with row followed by column,
places them at EBP-8 and EBP-4 under the canonical VC4 recipe.

Both fields are used throughout the conversion from screen pixels to board
coordinates. The source retains the X/Y copy order, inclusive Y bounds,
separate subtraction and division stores, clamps and signed tile reads.
Fireball tile mutation, fire-effect calls, board hits and scoring keep their
original order. The record introduces no unused fields or extra operations;
the original declaration spelling remains unknown.

The complete comparison applies all ten actual COFF relocations and reports
zero differences. All 90 instructions, thirteen branches, two calls and the
return agree. Eight accepted core companions retain 4,322 exact bytes; the
frame and drop-bricks candidates keep their previous comparison results.
One core compilation supplies the accepted object. Linux and MinGW rebuilds
and the VC4 relink with 36 verified unchanged objects succeed.

The existing coordinate loop passes 1,152 original/native cases covering
clamps, Y boundaries, six tile values and fireball/hard-tile modes. It compares
returns, full tile and owner/list state, and ordered calls. No game campaign
runs. All 214 accepted exact units and their input closures verify, bringing
the total to 48,922 code bytes and 136 separate metadata bytes, with 59 authored
functions remaining nonexact.

The original body and boundaries reuse REA evidence
`ev_a3dbe09d41da07ce2638ea83d054f31af646f507b1cedf2495bd03630db46f7b`,
operation 00 of run `2026-10-07T08-21-37.400Z-interactive-2545594`.
No new provider request is needed. Private comparisons, compiler inputs,
build logs, oracle receipt and verified compressed product copies are retained
in `.analysis/screen-position-record-20261012/`.
