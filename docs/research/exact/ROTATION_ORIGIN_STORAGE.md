# Rotation origin operands and initial storage

The later [closed follow-up](CLOSED_STORAGE_DIAGNOSTICS.md#rotation-and-value-copy-follow-up)
tests nested origin conversions, axis records, a sampled source-plane record and
floating consistency. None is adopted; the current renderer remains1451/1572
with1475 differences.

The renderer at `0x4026A0` now restores its two previously omitted zero writes
and the four-byte operand used by its first three origin divisions. One VC4
compilation preserves all four exact rotation companions, totaling 749 bytes.

| Complete renderer comparison | Before | Current | Original |
| --- | ---: | ---: | ---: |
| Code bytes | 1,447 | 1,451 | 1,572 |
| Instructions | 366 | 365 | 365 |
| Frame bytes | 416 | 424 | 424 |
| Strict differing byte positions | 1,491 | 1,475 | — |

The renderer remains a candidate. The accepted total stays **207 exact functions
and 44,832 code bytes**.

The original writes zero to independent DWORD words at EBP-344 and EBP-4,
immediately after sampling sprite dimensions. Neither word is read again in
the complete listing. The shared source represents these actual words as two
unclassified unsigned32 locals. Their semantic purpose and original signedness
are unknown. Their current homes, EBP-16 and EBP-36, still differ from the target.

The first three divisions read float `2.0` at `0x420038`; the last reads double
`2.046` at `0x420040`. A file-local float constant preserves the four-byte loads
and the three calls to `__adj_fdiv_m32` at `0x416DCC`. The previous literal in an
extended expression promoted the operand to double and emitted m64 calls.
The fourth divisor and its m64 fallback stay intact. Every constant binding
checks the full operand bytes against both the object and original image.

The retained renderer dossier is
`ev_1dfa14e3428cac399a6bc2876da74d5bbc4a5edc8a8e03a6af79783e189daf26`.
The complete constant carrier is
`ev_3981d4fe3871c6d5f4976aaec23007d066c24f80aedca23dd51270d63c19de71`.
These closed REA records cover the original writes, division operands and calls.
Remaining differences include stack homes, address-generation schedules and
instruction widths; equal instruction totals do not establish a complete match.

Linux and MinGW builds pass. VC4 links the same compiled owner with 36 verified
unchanged objects. The existing 351 renderer and 344 wrapper comparisons pass,
including complete guarded pixel buffers and seven live-handle/retry scenarios.
They exercise normal division; the FDIV fallback restoration has static
instruction evidence. All 207 accepted function extents and compiler closures
verify. Historical semantic scopes retain their case counts while their input
inventories refresh for the source change.

Inputs, complete comparisons, instruction inventories, products and the focused
Oracle are retained in `.analysis/rotation-origin-storage-20261012/`. No game
campaign ran. Verified gzip carriers retain disposable diagnostic object bytes
after cleanup.
