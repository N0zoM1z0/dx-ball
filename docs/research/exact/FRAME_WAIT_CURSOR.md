# Frame-wait cursor

The [direct WinMM import](EXACT_WINMM_CLOCK_IMPORT.md) historically made waiting
exact across170 bytes. Current declaration context emits170 bytes with eight
differences: two signed postincrement-guard transposes and the unsigned17ms
threshold transpose. The retained October17 review's complete resolved digest
`8440353b39b8b60a2d9904abc90778cf6fac772948a27691f9408c9e54521b41`
still equals the current candidate report. No missing operation or new trial
follows from the older six-difference description below. The import closure
preserves the explicit last-brick time sample; historical diagnostics retain
their original scopes.

`dxball_wait_frames` at `0x409610` now has the original 170-byte extent and
16-byte stack frame. An eight-byte cursor holds the sampled clock and completed
frame index. Its members occupy EBP-8 and EBP-4; the two postincrement guards
use the compiler's original EBP-12 and EBP-16 temporaries.

Both paths preserve the postincrement, including for zero and negative frame
counts. Vertical-blank waiting calls the live DirectDraw object. Timer waiting
checks clock rollback before the 17 ms threshold, then samples the clock again
to publish the next tick.

The complete relocated comparison retains six byte differences. In each guard,
the original loads the requested frame count and compares the saved index;
VC4 loads the saved index and compares the requested count, with the corresponding
opposite branch. Reversing the source comparison emits identical bytes. That
check is closed; the natural `cursor.index++ < frames` spelling is retained.

The saved REA carrier is
`.analysis/rea/runs/2026-10-07T09-29-28.570Z-interactive-2776129/10-analyze_function.json`,
Evidence `ev_86e83ae4d777813cd233a8b5c9d0f3ccf67349f7605b270938902c442f023087`.
Its complete contiguous span establishes both guards, all four stack homes
and the eight external bindings. The cursor's source spelling remains inferred.

Two display compilations preserve all ten accepted display bodies across
2,139 bytes. Eighteen unchanged waiting cases compare full state and ordered
calls against the original: frame counts, vertical-blank modes, threshold expiry,
DWORD wrap and clock rollback. Linux and MinGW products build; the VC4 game
links one changed object with 36 verified unchanged objects. No live game runs.

All 223 accepted exact closures remain valid across 55,481 code bytes and
136 metadata bytes. Waiting remains a candidate, leaving 50 authored nonexact
functions. Private receipts are in `.analysis/frame-wait-cursor-20261012/`.
