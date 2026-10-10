# Frame boundary and lightning control

This batch restores four complete bodies in `src/display.c`, covering 1,674
original bytes. It reuses the saved REA dossiers.

| Routine | Address / bytes | REA Evidence |
| --- | --- | --- |
| Reset regions | `0x408070` / 267 | `ev_7fa4a6f3aca679c5c635db0c51c110bfda08836742abef83dc71b0f1ee1d1d34` |
| Present frame | `0x409040` / 180 | `ev_fcc3a545dae1d448edd6d472e4a638685b211cd3a231c967d9837b585b0f4692` |
| Wait frames | `0x409610` / 170 | `ev_86e83ae4d777813cd233a8b5c9d0f3ccf67349f7605b270938902c442f023087` |
| Last-brick lightning | `0x415F40` / 1,057 | `ev_f8610be2baa2323aec8fcd14317794aebe74eefa78b4d66c9cf874ca117eb5bc` |

Reset copies one zero rectangle into both dirty pages and the presentation
queue. Presentation reads the live primary surface on each Flip, exits on
success or a non-busy result, and calls the genuine surface-recovery API when
the surface is lost. A successful Flip switches the dirty page before waiting.

Frame waiting chooses vertical blank or timer waiting once at entry. Both
loops use postincrement conditions. Timer waiting checks rollback before its
17 ms threshold, then reads the clock again to publish the next tick.

Lightning uses the raw millisecond clock, direct RNG and sound calls. Its
column-major scan keeps the last eligible tile and computes that tile's center
inside the selection branch. Separate loops emit 15 or 30 particles. Clipping
uses live sprite dimensions and a local rectangle, then publishes position,
top, bottom, left and right in the observed order.

The source retains the original eligible-tile precondition. Nested RNG
arguments use the supported compilers' observed right-to-left evaluation;
the affected Oracle checks their resulting order. The clock relocation binds
only `DxBallClockOps.time_ms`, at offset zero, to the original `timeGetTime`
IAT slot `0x4413A4`.

GCC builds keep the resulting `maybe-uninitialized` warning for `display.c`
without treating it as an error. MinGW Release builds and links the game.

## Compiler and behavior results

Only the display recipe was rebuilt; all 20 affected units were compared in
full with their actual relocations. An initial missing RNG declaration was
fixed by including `startup.h`. Presentation's explicit non-busy exit and
unconditional backedge were then recovered from the original instructions.
The preceding objects and reports are retained.

Reset (267 bytes) and presentation (180 bytes) are exact. Effect-sprite drawing
also returns to exact at 361 bytes. Queue-sprite-region and dirty-region
restoration return to candidates. The ledger now records **124 exact functions
/ 19,413 code bytes**, a net decrease of 291 bytes from the preceding epoch.

Frame waiting remains a complete 171/170-byte candidate with 64 differences;
lightning remains 1,063/1,057 bytes with 337 differences. Their full comparison
reports retain those differences.

The native build and one unchanged display Oracle pass: 2,409 direct cases
and 192 connected frames. The Windows VC4 game links using the new display
object and 30 validated existing objects. Full inputs, evidence, comparisons
and products are retained in `.analysis/checkpoints/exact-frame-boundary-283-124/`.
