# C++ terminal callbacks and SEH ownership

October 16 object follow-up: [construction and destruction](RUNTIME_CPP_OBJECT.md)
now have complete source, with destruction exact and construction a four-byte
nonexact candidate. Earlier checkpoint totals below remain historical.

`src/runtime_cpp_terminal.cpp` restores the two complete terminal functions from
the original `hooks.obj`, including their compiler-owned SEH registration,
filters, cleanup continuations and scope tables.

| Entry | Source | Code bytes | Scope bytes | Differences |
| --- | --- | ---: | ---: | ---: |
| `0x0041BC60` | `dxball_cpp_terminate` | 115 | 24 | 0 |
| `0x0041BCE0` | `dxball_cpp_inconsistency` | 115 | 24 | 0 |

Each function tests its genuine callback cell, invokes a nonnull callback in
an inner `__try` with a constant-one `__except` filter, and runs its terminal
fallback in an outer `__finally`. The inner handler consumes callback faults.
Terminate falls back to the maintained abort boundary at `0x41E230`;
inconsistency falls back to terminate. No manual FS manipulation, copied code,
artificial locals or replacement exception dispatcher is needed.

All sixteen code relocations and six scope-table relocations are explicit in
`config/match-units.toml`. Same-function labels use their actual COFF section
and offset. The scope tables at `0x4201E8` and `0x420200` are attested in full,
including both enclosing-state values and all filter/handler pointers. The
`__except_list` relocations denote FS offset zero; the genuine compiler/CRT
`_except_handler3` remains a separate runtime dependency at `0x41C724`.

The original default state is also restored as an explicitly initialized
16-byte record on i386:

| Original cell | Default |
| --- | --- |
| `0x42389C` | Null SE translator |
| `0x4238A0` | Null terminate callback |
| `0x4238A4` | Terminate as unexpected callback |
| `0x4238A8` | Terminate as inconsistency callback |

The complete emitted `.data` section, its four actual symbol offsets and both
pointer relocations match the original. An initial implicit-zero control put
the null cells in BSS; explicit initialization restores the original initialized
producer boundary without changing either function. These 16 storage bytes are
reported separately from the exact code and attached scope-table counters.
The unexpected callback cell does not establish a reconstructed unexpected
function: that pinned library member's additional body has no established
original placement here.

The source uses actual Win32 SEH language constructs. VC4 and Clang targeting
i386 Windows compile the same implementation. A compiler without Win32 SEH
support cannot build this owner; no Linux fallback or ordinary C++ catch block
is substituted. As with the other standalone CRT owners, this file is outside
the CMake game library pending runtime integration. This result closes two
source gaps, not the Windows dispatcher, unwind helpers or entire CRT startup.

Seven fresh Wine processes execute the maintained VC4 object with the real
linked VC4 SEH support. They check empty, returning and faulting callbacks for
both entries, plus the default inconsistency-to-terminate chain. The controlled
abort endpoint records the ordered callbacks and calls `ExitProcess(73)`.
All seven reach that endpoint with the expected events; faulting callbacks do
not resume after `RaiseException`. This proves the bounded generated-code
dispatch under Wine, not original-game execution, the maintained abort body,
native Windows behavior or arbitrary unwinding. The first output guard rejected
an Xvfb shutdown message; its raw result is retained and the repaired reader
selects exactly one fixture event record without discarding the raw output.

The retained original authority is
`.analysis/cpp-terminal-boundaries-20261014/original-proof.json`, with REA IDs
`ev_06745feb23b4c1b0c656b39548712dadb099e59d4a043230cbe90f4f93a44d61`
and `ev_f561022b68290f5ac8530cdf4642e42957fba725cea515587a46e868788f0a66`.
No new provider session was opened. Both complete pinned sections include the
final RET omitted by the older provisional 114-byte extents.

The new private carrier `.analysis/cpp-terminal-source-20261016/` retains source
controls, compiler receipts, complete comparisons, initialized-storage proof,
Clang products and the bounded Wine fixture/results. `verification.json` records
**543 inventory / 459 source / 369 exact**, with **75,861 code bytes / 184 scope
and other attached metadata bytes**. The previous 367 exacts are reused after
verifying unchanged recipes, actual inputs, flags and product hashes; they were
not recompiled. Historical semantic rows remain 249. No game or platform-port
campaign ran.
