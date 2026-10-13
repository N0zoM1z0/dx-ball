# CRT low-I/O write chain

Five complete functions now have shared C source in `runtime_lowio.c`.
Handle lookup and error mapping are exact across169 bytes and12 bindings;
the mapper also enforces all360 initialized table bytes in its match recipe.

| Entry | Original/current bytes | Differences |
| --- | ---: | ---: |
| `_write`, `0x41A770` | 555/555 | 37 |
| `_dosmaperr`, `0x41A9A0` | 102/102 | 0 |
| `_lseek`, `0x41AF40` | 188/188 | 15 |
| `_get_osfhandle`, `0x41D9D0` | 67/67 | 0 |
| `_commit`, `0x41DA20` | 111/110 | 65 |

The shared low-I/O record now exposes only its proven handle and flag byte.
Natural Win32 layout retains the eight-byte stride; host handles grow with
pointer width. File-mode code retains its complete128-byte/two-difference result.
Pinned `io.h:168,181,195,231` grounds the public signatures. Seek offsets remain
signed32; the signed handle return grows with the host. The low-I/O recipe uses
the original single-thread `/ML` contract: `/MT` plus stddef introduces an errno
accessor absent from the original. No accessor is falsely bound to a data cell.

Writing preserves append seeking, generated CRLF, short writes, device Ctrl-Z,
error5 remapping and the original subtraction of every generated CR. The
1025-byte source buffer follows the maximum generated extent, not Ghidra's
1028-byte stack span. Captured block-slot address and byte offset survive OS
calls while the block value is reread. One shared failure path and a consumed
three-field cache/progress record restore the original555-byte emitter and
1048-byte frame, improving563/288 to555/37. Grouping the OS output into the same
record instead worsens566/491 and is rejected. Pinned seek signatures retain15
differences; the earlier integer-signature diagnostic had2 and is not published.
Commit validation leaves doserrno untouched; a nonzero OS failure publishes
errno9. Error mapping retains all45 records, duplicate error6 and both ranges.

Whole pinned CRT sections independently agree for all five entries. REA run
`2026-10-13T12-45-07.899Z-interactive-1599344` retains fifteen info/pseudo/assembly
records in one closed session. Table bytes reuse
`ev_e5aea1b1fa43f15168514e949432e327c43794b19fce1f23c2a86fd6067c9f5c`.
Private producers/proof: `.analysis/runtime-lowio-write-20261013/`.
All253 previous exact results and50 preceding candidate results are unchanged.
Totals are320 source-present functions and255 exacts/64,031 code bytes.
Native/i686 standalone compilation covers both changed owners. No runtime tests
or game builds run. Low-I/O registry/error storage and game integration stay open.
