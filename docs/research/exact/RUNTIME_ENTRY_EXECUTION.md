# Actual process entry, arguments and SEH exit

The restored `dxball_crt_startup` now runs as the PE entry point of an isolated
VC4 Windows-subsystem executable. All 48 source objects are reused by complete
input, flags and product identity; no production source is recompiled. Only
the application observations, filter observations and process launcher are new
fixtures. The image imports KERNEL32 alone and uses `/NODEFAULTLIB`.

[The checked link scope](../../../config/runtime-entry-link.json) records the
48-owner order, additional data/adapter producer recipes, explicit original
dependencies and application boundary. It preserves stdio-before-onexit ordering
inside `.CRT$XIC`. This is a checked standalone entry scope, not the final game
build command; the actual game and Win32 binding still need integration.

## Three actual Windows child processes

A separate custom-entry launcher calls `CreateProcessA` with an explicit image
path and mutable raw command line. It supplies real startup/show fields and
inherited standard handles, waits for each child, reads its full DWORD exit
status, and closes both process handles. The children run sequentially.

| Case | Executable token | WinMain tail | Show | Full exit status | Cleanup |
| --- | --- | --- | ---: | --- | --- |
| Normal | `alias.exe` | `normal "two words"` | 10 | `0x0000001F` | `BAF` |
| Quoted/show | `"alias with space.exe"` followed by TAB | `shown "two words"` | 7 | `0x00000020` | `BAF` |
| SEH quick | `alias.exe` | `fault "two words"` | 10 | `0xC0000005` | Skipped |

The observed application uses the actual C-linkage/stdcall declaration from
`platform.h`. Every process verifies the module and null previous-instance
arguments, all four version fields, real private-heap validity, three parsed
arguments and a null argv terminator. `_pgmptr` agrees with the real module path,
independently of the arbitrary argv[0] alias. The argument and environment arrays
belong to the maintained heap. Environment processing preserves the named
`DXBALL_CRT_ENTRY_PROBE` value and removes drive pseudo-entries; no unrelated
environment values are printed.

FP reports 53-bit precision, cleared sticky exception flags and the host's
zero FDIV flag. The active positive callback executes successfully. Real stdio
state and actual OS filter installation are checked, then two callbacks are
registered. The normal entry return reaches the maintained exit owner with
codes 31/32. Callback B precedes A; the flush observation verifies that the real
filter-restoration callback has already run. Close-all is not selected for this
physical normal-exit path.

For the exception case, the application sets the recovered signal record's
genuine DIE action 5 and calls real `RaiseException`. The maintained exception
filter selects the original outer execute-handler path; actual SEH dispatch
and unwind reach the entry's quick-exit block. No normal cleanup callbacks run.
The launcher observes the full `0xC0000005`, not only a truncated host-shell
status. This checks the selected DIE path, not all default signal/exception
delivery behavior.

## Complete linked checks

The full 390-byte entry agrees with its retained source object after all 34
actual code bindings. Its 12-byte scope record has two genuine local-label
bindings. That record is independently located by its unique, fully relocated
contents; its address is not inferred from the code operand being checked.

Thirteen whole source bodies, totaling 2,034 bytes, agree with their actual
linked image bytes, including entry, command-line parser, environment publication,
multibyte initialization, selected exception filter and the preceding FP chain.
The source setter's private program-name placement is not promoted to a separate
whole linked-body claim; its unchanged producer and actual WinMain observations
cover the argument publication checks.

The complete 52-byte FP state/nine bindings and 84-byte CRT table/thirteen
bindings also remain correct under real image addresses. These are emitted
source-to-image checks. Existing nonexact math/control/filter bodies remain
nonexact; the 390-byte entry and scope were already counted before this check.
Original REA/member evidence remains in [CRT startup](RUNTIME_ENTRY.md), and
the prior initializer evidence is in [FP startup](RUNTIME_FP_STARTUP.md).

The first application fixture mixed SDK and reconstructed CRT declarations in
C++ and failed type/linkage checks. It was separated into C application
observations and a narrow C++ filter observer. A missing process-API include
was then repaired in that fixture. Production objects were unchanged. Fixture
sources, failed logs and superseded products are retained; the unaffected
launcher and filter objects are reused after their successful compilations.

## Remaining scope

The application body is an observation fixture, not the game. The verified CRT
entry calls `dxball_win_main` directly, while the existing host `WinMain` wrapper
in `windows_entry.c` calls `dxball_bind_windows` first. Connect real game/Win32
bindings before replacing that host-startup path; do not silently bypass them
or initialize a second heap over the live argument/environment allocations.

Physical x87/SEH and two narrow-string dependencies remain five pinned original
library members. Flush/close effects remain typed fixture boundaries. Remaining
low-level source, the actual game, physical stdio cleanup and final playability
are still open. This process check does not finish the reconstruction objective.

All function/source/origin/exact ledgers, producer inputs/products and the
380-exact/95-candidate reports remain unchanged. The 249 historical semantic rows
are byte-identical. Totals remain 545 inventory and 475 source entries, with
77,485 exact code bytes and 244 metadata bytes. No full replay or provider query
ran. CPU is capped at 35%, memory high 640 MiB/maximum 768 MiB, with serial work
and one allowed CPU through the project wrapper.

After adoption, 102 byte-identical immutable header snapshots share retained
copies, releasing 440 KiB of allocated storage. Unique fixture variants, failed
logs, compiler products, images and mutable canonical objects are preserved.

Private receipts are `.analysis/crt-full-entry-20261016/`: `closure.json`,
`application-product.json`, `filter-product.json`, `launcher-product.json`,
`link.json`, `runtime.json`, `verification.json` and `adoption.json`.
The retained entry evidence includes code
`ev_04a70593d1fc3d7c3fe06b103084423cc9d4f7b7429fe2002ef260be1fce411f`
and scope `ev_922d290e19de2d38525e82a3e2c401ec47e0f7827dbf2eb9d0c21721273b2807`.
REA remains pinned to 6.5.0.
