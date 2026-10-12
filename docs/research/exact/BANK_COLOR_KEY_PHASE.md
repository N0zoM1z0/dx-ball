# Sprite-bank color-key lifetime

The bank loader now declares its existing color key in the surface-transfer
block that uses it. It remains a standalone object beside the unchanged
116-byte description/result/pixel workspace. All assignments, calls, arithmetic
and upload loops keep their order.

The complete matching body stays 1475 bytes, with 425 instructions and a
180-byte frame. Its differences fall from 74 to 72. The color key moves from
EBP-16 to its original EBP-64 home. Description, result and pixel retain their
original homes at EBP-180, EBP-72 and EBP-68. The remaining scalar homes and
two multiplication operand orders still differ; this is not an exact function.

The earlier key-as-workspace-field model also had 72 differences but lost the
accepted glyph search. This standalone scoped object preserves that search
and all other resource exacts: twelve functions totaling 2197 bytes. All forty
other candidate code identities are unchanged.

Ten existing bank cases and three callback cases pass. Native and MinGW builds,
separate VC4 matching and production compilations, linkage with 36 unchanged
objects and all 232 accepted complete closures pass. Historical input inventories
refresh 235 rows. No game session runs.

Original REA evidence is
`ev_b55c6def4c1b4af6c165acfb1623311bffa077753d93fab01531787dca6b6d70`,
operation 01 in `2026-10-10T17-22-54.305Z-requests-825249`. Actual compiler inputs,
relocation bindings, full comparisons and validation receipts remain in
`.analysis/bank-color-key-phase-20261013/`.

Independent review verifies the declaration-only move, eight actual compiler
inputs, all 77 bindings and the four original object homes. Nineteen completed
copies are retained as verified gzip files, releasing 4,325,376 allocated bytes.
Current build products remain available.

The accepted total remains 232 functions / 59,486 code bytes / 136 metadata
bytes, with 41 authored candidates still nonexact.
