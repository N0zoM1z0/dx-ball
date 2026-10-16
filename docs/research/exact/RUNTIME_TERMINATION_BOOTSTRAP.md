# CRT exit bootstrap and default cleanup

Two previously omitted complete runtime functions now have shared C source and
exact VC4 comparisons. The default pretermination table now calls the recovered
stdio finalizer instead of containing only null slots.

| Original entry | Maintained function | Complete bytes | Differences |
| --- | --- | ---: | ---: |
| `0x41F880`, `___onexitinit` | `dxball_crt_initialize_onexit` | 54 | 0 |
| `0x41DB60`, `___endstdio` | `dxball_crt_end_stdio` | 20 | 0 |

The initializer allocates 32 callback slots, publishes begin, reports fatal
reason 24 on failure, writes the first null slot and sets end to begin. It does
not clear the entire allocation. Existing registration supplies subsequent
slots and grows capacity by four slots when needed.

The stdio finalizer always calls flushall. It calls fcloseall only when the
exit flag's low byte is nonzero. Thus callable cleanup closes streams, ordinary
process exit flushes them, quick cleanup skips the pretermination table, and a
return-mode value of 256 still returns while storing a zero low-byte flag.

## Complete code and data evidence

The pinned CRT `onexit.obj` at library header `0xA423C` supplies the complete
54-byte text section and six relocations. `_file.obj` at `0xBB106` supplies the
complete 20-byte text section and three relocations. Every actual binding is
recorded in `config/match-units.toml`. Both original member sections also match
the verified target after relocation. Retained complete original code Evidence:
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.

Fresh REA 6.5.0 / Ghidra 12.1.4 Evidence
`ev_e071555ff2a07f693cdf6788da722cec1f2704cd05724223a14276f33a3d58e8`
reads all 20 bytes at `0x421040`. The existing complete controller independently
binds the consumed ranges: pretermination `[0x421040,0x421048)` contains null
and `0x41DB60`; termination `[0x42104C,0x421050)` contains null.

The separate maintained data owner supplies these two arrays. Its eight-byte
and four-byte records match those separate ranges, including the one actual
DIR32 binding. The original intervening end marker is outside both claims;
the source object's contiguous 12 bytes are not claimed as one original span.
The null termination slot has caller-bound placement, not a unique standalone
zero-data anchor. Recipe: `config/runtime-termination-tables.json`.

The same REA session's first read at `0x421000` was mistakenly requested as an
XI prefix. It is a C++ initializer prefix and is retained only as a diagnostic:
`ev_06b8cc8067d7cad06a541872608c08d15957883f2fb014e7d982c857cf6d197b`.
Actual XI bounds are `0x421030..0x42103C`; no recovered XI registration or full
constructor-table placement follows. The batch session closed and saved.

## Affected checks and retained products

One selected four-owner VC4 family supplies both new functions, the existing
termination functions and the initialized data owner. The old controller128,
normal wrapper18 and quick wrapper18 remain exact; walker32 remains six
differences. All four selected owners also compile as native/i686 C90 with
warnings treated as errors. An initial model placing initialized tables inside
the controller owner changed four controller bytes; that model is rejected.
Moving the actual storage to its separate producer restores the accepted code.

The affected native termination fixture passes its existing 1,031 direct calls
across 1,026 fixtures with unchanged observation digest
`da4051d3d037b8c6b44b5b421d9e612751fc96b289f86e85bf2eabc74d0da204`.
Only its four existing semantic rows are refreshed. Eight selected original/COFF
comparisons check the updated storage resolver using retained VC4/i686 objects;
the full COFF queue is not rerun. Fixtures replace the genuine typed dependency
boundaries and reset their callback tables before execution.

A small VC4/Wine probe uses the real Win32 private heap and maintained allocator,
reallocation, registration, controller, default tables and both new bodies.
It verifies the empty table, 37 registrations with a null slot, real capacity
growth from 128 to 160 bytes, reverse callback order, callable cleanup, quick
cleanup and return-mode 256. Separate processes reach fatal24/exit88 and actual
normal/quick ExitProcess statuses63/64. Stdio and fatal endpoints are controlled
typed fixtures. This is not physical stdio-driver or fatal-dialog acceptance.

Wine/X-server teardown output invalidated a first-line-only quick-log parser.
The executable and selected objects were retained; only quick mode was rerun
to retain its terminal exit64 receipt, then that receipt was parsed without
restarting the producer. Earlier modes' status and trace gates had completed
before the subsequent logs were written. The original diagnostic logs remain.

Private receipts: `.analysis/crt-termination-bootstrap-20261016/`, including
`original-proof.json`, `separate-tables/`, `tables-comparison.json`,
`native-termination.json`, `coff-smoke.json`, `windows-probe.json` and
`adoption.json`. Heavy work is serial under CPU35% / memory high640MiB,
maximum768MiB, with one allowed CPU; Ghidra heap is256MiB.
Sharing47 verified identical immutable evidence carriers reclaimed13.7MiB;
unique trials and current canonical objects remain independent.

The two additions bring inventory to542, source-present to467 and exacts to379
covering77,292 code bytes plus244 attached metadata bytes. All377 prior exact
results and all88 candidates are unchanged. Unaffected objects, complete input
identities and results are reused; no full historical replay or game build ran.

The subsequent [stdio initialization recovery](RUNTIME_STDIO_INITIALIZATION.md)
accepts the complete193-byte initializer at0x41DA90 and644-byte stream storage,
and observes the correct XI contents. XI source/linker registration, wider CRT
storage/linkage, remaining low-level functions and the final VC4 game/play check
remain open. These standalone owners remain outside the current game build.
