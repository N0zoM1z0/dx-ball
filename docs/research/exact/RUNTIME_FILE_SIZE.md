# CRT length changes, zero allocation and stream retirement

Three complete bodies close the opener's missing length-change dependency and
add zero allocation and nonstandard-stream retirement. Length change is exact.

| Entry | Original/current bytes | Differences |
| --- | ---: | ---: |
| `_chsize`, `0x41F670` | 359/359 | 0 |
| `calloc`, `0x41F590` | 82/77 | 16 |
| `_fcloseall`, `0x41F5F0` | 115/115 | 19 |

All359 chsize bytes and18 actual bindings match, including the compiler's
special-ABI stack probe. Its4100-byte frame contains the consumed original
position and4096-byte zero buffer, not inferred padding. Both initial seek
failures share an exit. Explicit memset with `/Oi` restores the complete
1024-word zero fill; a byte-array initializer instead emits a first-byte store
and partial tail. Common seek failure plus full zeroing reduces376/284 to359/0.
Growth temporarily uses binary mode and subtracts actual writes; write-zero
does not invent progress or a new stop condition. Error5 becomes errno13.
Truncation retains the unchecked seek and SetEndOfFile, publishing errno13 and
the OS error on failure. The final position restore does not override status.
Invalid descriptors change errno but preserve doserrno. Signed offset
arithmetic requires representable differences; no host truncate shortcut is used.

Calloc retains the original unsigned32 product, wrap/zero-to-one rule,
`0xFFFFFFE0` ceiling, HeapAlloc flag8, allocation mode and retry handler.
An explicit loop-carried heap/result phase adds a register and worsens77/16 to
85/64; it is not retained. The heap's unconditional reload at the original
latch remains a candidate, along with multiplication operand selection.
Both preceding resize functions retain their results: msize21 exact and
realloc106/111/15. Their affected inputs/products are frozen in this phase's
`before/`; the final producer is refreshed rather than treated as unchanged.

Fcloseall skips slots0–2, counts successful closes, and frees/nulls dynamic
records from slot20 even after close failure. Registry and limit are reread
after calls. The20 threshold establishes retirement ownership, not an invented
standard-array capacity. Register rotation and loop comparison remain nonexact.
Its115/21 initial result becomes115/19 in the final intrinsic/SDK context.
Replacing the opener's existing genuine chsize declaration with a new header
worsens its two differences to42; that context trial is closed and reverted.
The opener's preceding source/inputs/product/results remain unchanged.

The closed REA run `2026-10-13T15-04-02.420Z-interactive-1756028` retains nine
info/pseudo/assembly records. Assembly Evidence IDs:
`ev_b07adf899efe2a9d42478b47f49cdab7d86051a78c166328b5a9563e5dc42849`,
`ev_4ea2a3daef2a5b9ff7dcaf86f2d74cc2e6035db22af65e1963e44d67371aa50c`,
`ev_8108527114cb39b0e9bf0ebf350343179e195387e547cbe76d8214a2a388aef2`.
All three whole pinned CRT sections independently match the original.
Private proof and seal: `.analysis/runtime-file-size-20261013/verification.json`.

Source338/exact260/64,602 code bytes; metadata136 unchanged. Five affected
complete comparisons preserve the old21-byte exact;258 other exacts and63
other candidates reuse unchanged inputs/products/results. Candidates66:
34 authored/32 runtime. Both changed owners compile natively/i686. No runtime
tests or game builds run; shared storage and integration remain open.
