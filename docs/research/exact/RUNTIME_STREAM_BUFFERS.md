# CRT stream buffering

All six stream-buffering functions are exact. Buffer acquisition and retirement
remain in `runtime_stream.c`; the four original `fflush.obj` functions live in
`runtime_stream_flushing.c`, in their shipped `fflush.c` order.

| Entry | Original/current bytes | Differences |
| --- | ---: | ---: |
| `_getbuf`, `0x41AEF0` | 75/75 | 0 |
| `_freebuf`, `0x419FA0` | 57/57 | 0 |
| `_flush`, `0x41A030` | 100/100 | 0 |
| `fflush`, `0x419FE0` | 76/76 | 0 |
| `flsall`, `0x41A0B0` | 107/107 | 0 |
| `_flushall`, `0x41A0A0` | 11/11 | 0 |

Restoring that producer boundary and function order closes all107 traversal
bytes and three actual relocations without changing any function body or flags.
The full pinned `fflush.obj` section and retained REA assembly
`ev_0d9a280f965f1b554b92650e44a97ba496a0947f8056451e0236fd91485a9582`
cover the original. Both remaining buffer functions and the other three flushing
functions stay exact. Two VC4/native/i686 compilation sets were used, one per
owner; identical canonical source/header bytes reuse those products. All351
old exacts and97 other candidates remain. Current totals are352 exact functions
and73,029 code bytes. No runtime or game checks ran. Receipt:
`.analysis/stream-flushing-original-owner-20261015/verification.json`.

Earlier register-local recovery:

The shipped CRT `_getbuf.c` and `fflush.c` establish genuine local stream
ownership and `REG1/REG2/REG3`, defined as C `register` for x86 by `cruntime.h`.
Restoring those locals closes75 and100 bytes through all three actual bindings.
The request counter precedes stream capture; flushing retains its status and
byte-count locals. Full pinned members and retained REA assembly confirm both.
All338 prior exacts remain; totals340/70,315 code bytes, candidates109.
Traversal source is unchanged, but shared compiler context rotates registers
and changes13 differences to14. Its register-index and explicit-return trials
also give14 and are not retained. Four compiler sets, no runtime tests;
receipt `.analysis/stream-buffer-register-owner-20261014/verification.json`.

The eight-field record follows pinned VC4 `stdio.h:159–167`, not host FILE.
Acquisition preserves the request counter, 4096-byte allocation and two-byte
embedded fallback. Retirement frees only an in-use owned buffer. Flushing
retains original write guards, error bits, update-stream flags and cursor/count
resets. NULL fflush traverses 512 shared entries; mode0 returns write failure,
mode1 counts successful in-use streams. Lower-I/O write/commit, registry/counter
storage and game integration remain open. Host pointers keep native width.

The captured traversal pointer emitted109 bytes/83 differences. Direct shared
table accesses restore107 bytes and the pointer/flag chain, leaving13 register
differences. Acquisition and buffer flushing differ only in store scheduling.
Consuming the allocation result in its assignment condition changes no code;
the Pentium scheduler worsens all four compared functions and is rejected.

Complete pinned CRT sections independently agree for all six entries. REA
runs `2026-10-13T12-23-19.527Z-requests-1563297` and
`2026-10-13T12-30-10.052Z-traversal-requests-1574261` retain info/pseudo/assembly.
The 11-byte wrapper was absent from the imported inventory: its full REA read
is `ev_2b96ddc20d95568cb8f2717d4ed51aaf96288f922afc0effc425fe20fb9d8390`.
Ghidra reports no procedure at that entry; the complete pinned function section,
actual call binding and original byte read establish its recovered boundary.
The inventory grows to529; source presence315; exacts253/63,862 code bytes.
All250 previous exact results and47 previous candidates are unchanged.

Private proof: `.analysis/runtime-stream-buffers-20261013/`. Five bounded VC4
producers, six final complete comparisons and native/i686 standalone compilation
cover this owner. No runtime tests or game builds run.
