# Exact intro grid cursor

Intro point initialization at `0x0040E570` now matches its complete 1,996-byte
original body. A sixteen-byte grid cursor groups the angle, point index and
coordinates already consumed by point seeding and wave-table initialization.
All fields are used; the 287-byte mask and its existing scope are unchanged.

The canonical VC4 body restores X at EBP-4, Y at EBP-8, index at EBP-12 and
angle at EBP-16. The mask remains at EBP-304 in the original 304-byte frame.
The [preceding mask checkpoint](INTRO_MASK_LIFETIME.md) had thirteen remaining
coordinate/angle displacement differences. They are now zero across all
368 instructions, nine branches, two calls and ten actual relocations.
Mask writes, point initialization, row stepping and wave calls retain their
original order. Original declaration spelling remains unknown.

One intro compilation preserves fifteen exact companions across 3,864 bytes.
Generated literals in those companions are rebound only after their complete
contents and target addresses verify. The comparison consumer first rejects
stale labels; checking the completed object resolves them without recompiling.
The existing deterministic case compares all 287 point records, 360 wave
offsets, state and ordered calls. It passes on the native product; unrelated
update and transition cases are not rerun.

Linux and MinGW build, and VC4 links the intro and game-over objects with
35 verified unchanged objects. The [ranking-row records](RANKING_ROW_RECORDS.md)
pass their existing seventeen drawing cases. All 219 accepted units and input
closures verify: 53,883 code bytes, 136 metadata bytes and 54 authored functions
remaining nonexact. No game campaign runs.

Original evidence is
`ev_001f48ac971f132ed4b29b98cf1549ec4136da2eab0a9448b6ed27d7f5e41fb8`,
operation 04 of run `2026-10-07T11-58-17.972Z-interactive-3053414`.
No new REA query is needed. Full comparisons, compiler inputs, builds,
case receipts and verified compressed products remain under
`.analysis/intro-grid-cursor-20261012/`.
