# Surface fill and sprite-bank recovery

The subsequent [Restore-result checkpoint](SPRITE_RESTORE_RESULT.md) now
captures the observed unused HRESULT write. The full candidate is282/282 bytes
with 18 strict frame-home differences; all 85 original boundaries agree. The
historical omission and80-difference comparison below describe this earlier
checkpoint, not the current source.

The restored device initializer clears the primary surface before creating its
palette. Surface recovery later scans sprite banks and reloads those stored in
video memory. This batch follows those two direct dependencies from the saved
REA dossiers into [device.c](../../../src/device.c).

`clear_surface` at `0x409F10` now writes only DDBLTFX size 100 and the full color
DWORD, then RECT top 0, bottom 480, left 0 and right 640. Blt receives the actual
surface parameter, the rectangle, two null source arguments, flags `0x400` and
the fill object. Removing the extra memset and cached destination restores the
complete original **89 bytes**, exact on the first stable compilation.

`restore_sprite_banks` at `0x403D30` scans banks 0..2 whose allocation mode is
exactly 1. It checks all 255 slots regardless of count, reading the live sprite
and surface for each null check and COM Restore call. Each eligible bank then
calls `load_sprite_bank` directly at `0x404610` with `(bank, 1, bank.filename)`.
The existing typed native boundary forwards that call through its actual live
callback slot; headers, fixtures and case bodies are unchanged.

The original stores each unused Restore HRESULT at EBP-8. Evidence does not
resolve whether this came from a source local or compiler storage. The source
discards the result; its **279/282-byte candidate has 80 counted differences**.
No unused local was added to reproduce that store.

REA's three complete contiguous dossiers cover 577 bytes and 170 instructions,
including the unchanged exact palette initializer:

- Fill 89: `ev_017375bcddb7d6708aadc8ec0d071b77e9d37c7f877f9da584462f4e561360db`
- Bank recovery 282: `ev_6086488847b0abeff3f7ed6af657fd76f1d18d085752c4ae7c38ff49c74b9d94`
- Palette 206: `ev_1f7ee3646ca9d02b5f9f7b91f0c1cbfe3f3af3a8f021debadd09191a0c844cbd`

There are no gaps or embedded tables. Snapshot 495 was reused without a new
provider query. One device recipe compiled once; all three prior exact units
retained identical code and relocations. Five whole comparisons account for
35 actual relocations. The palette, synchronization and recovery bodies stay
exact; the accepted total is **147 functions / 23,490 code bytes**, plus
136 metadata bytes.

Only four existing Oracle loops ran: 18 fill, 64 bank and 63 recovery cases,
plus eight connected lost-surface presentations. Native, VC4 and MinGW builds
pass; VC4 reuses all 35 valid game objects. Complete source, target, compiler
inputs and products are retained in `.analysis/exact-device-dependencies/`
and its checkpoint. Other semantic rows retain historical scope after their
input hashes are refreshed.
