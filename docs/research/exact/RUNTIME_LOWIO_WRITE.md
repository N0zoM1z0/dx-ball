# CRT low-I/O write chain

Five complete functions now have shared C source in `runtime_lowio.c`.
Handle lookup and error mapping are exact across169 bytes and12 bindings;
the mapper also enforces all360 initialized table bytes in its match recipe.

| Entry | Original/current bytes | Differences |
| --- | ---: | ---: |
| `_write`, `0x41A770` | 555/555 | 22 |
| `_dosmaperr`, `0x41A9A0` | 102/102 | 0 |
| `_lseek`, `0x41AF40` | 188/188 | 13 |
| `_get_osfhandle`, `0x41D9D0` | 67/67 | 0 |
| `_commit`, `0x41DA20` | 111/111 | 2 |

The shipped `commit.c` establishes a register descriptor/status and shared
error/completion labels, with DOS error published before errno9. Restoring that
ownership improves110/111/65 to111/111/2. All instruction addresses and widths
agree; only the bound CMP and its equivalent JAE/JBE encoding differ at two
bytes, so no exact is claimed. Seek15 becomes13 and write19 becomes22 through
shared-context register allocation; neither source body changed. Both owner
exacts and the complete360-byte table remain. Two compiler sets, no runtime
tests; retained objects are re-consumed with the table attestation restored
after its comparison metadata was omitted, without recompilation. All343 old
exacts/103 outside-owner candidates/249 semantic rows remain unchanged.
Receipt `.analysis/descriptor-commit-register-owner-20261014/verification.json`.

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

The follow-up separates the two-field OS outcome from the three-field
cache/progress owner. This preserves555 bytes and restores all five scalar
homes relative to the post-save ESP: error16, written20, block24, offset28 and
total32. The translation buffer remains at36. Eighteen differing displacement
positions disappear; the remaining19 rotate input/output/inserted-count registers.
Text input, per-chunk output and per-byte values now have their consuming
lifetimes, but that second trial changes no code. Two complete owner exacts
preserve169 bytes and the full360-byte table. No new exact function is claimed.
Current proof: `.analysis/runtime-write-lifetimes-20261013/verification.json`.
