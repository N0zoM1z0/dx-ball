# I/O error, default-mode and invalid-record state

Later [real-game entry integration](../RESTORED_CRT_GAME_ENTRY.md) uses this
state and actual source stdio through the restored CRT. The optional build
passes the first original board and normal exit while retaining explicit
original x87/SEH/C++ dependencies. The text below retains the state-adoption scope.

`runtime_io_state.c` supplies six previously external globals used by the
recovered single-thread CRT: `errno`, `_doserrno`, the creation mask, default
commit mode, default file mode and the invalid-descriptor record. The five
words start at zero. The typed record starts with handle -1, zero flags and
newline lookahead. Windows retains its eight-byte layout; native handles grow
with the host pointer width.

[The state recipe](../../../config/runtime-io-state.json) records complete
inputs, flags, original members, observed addresses and placement limits.
One VC4 compilation emits 32 bytes without relocations: 28 bytes of typed
state and four bytes of ordinary compiler alignment before the record. Those
four bytes are not a source field. Each complete global agrees with its
original value and actual linked image; the emitted 32-byte section also
agrees with the image. The original globals are not one contiguous 32-byte
record.

## Original evidence and placement limits

| State | Original address | Bytes | Original member |
| --- | --- | ---: | --- |
| `errno` | `0x4230AC` | 4 | `crt0dat.obj` |
| `_doserrno` | `0x4230B0` | 4 | `crt0dat.obj` |
| Creation mask | `0x4230B4` | 4 | `crt0dat.obj` |
| Default commit mode | `0x4242DC` | 4 | `ncommode.obj` |
| Default file mode | `0x424364` | 4 | `txtmode.obj` |
| Invalid-descriptor record | `0x423888` | 8 | `ioinit.obj` |

The complete eight-byte initialized record occurs once in the original
carrier and independently establishes its address. Its pinned member and
actual REA observation agree. The three error/mask words use the established
72-byte `crt0dat` section and original declared offsets. The two isolated zero
words retain consumer bindings and complete named-member evidence; their
values do not independently locate them. No new unique-zero placement or
whole-`crt0dat` source claim follows.

The retained 72-byte observation is
`ev_1bd03ba587bf4cb8cb739d2e1ec4fd40ea4aabd9238dbe9fc0f4136976870bc0`.
One new REA 6.5.0 session reads only the remaining sixteen bytes:

- Invalid record: `ev_85bc5f1db1f3c2d3b5c17188767e792a3bc2af4aa9e3c58b854bb536830452da`.
- Commit default: `ev_672dabb18f0fe7ec6524a2d1f9c3f85a0c979bbc3ee243f5826c3bc622b5f9c0`.
- File-mode default: `ev_d88eea36ab64904f22f7c477d9e3e2e217b24af5730a60864bf23de2b8c3f135`.

## Actual entry and physical files

An isolated Windows-subsystem image runs the real restored CRT entry with
64 maintained source objects. Sixty-three are reused with current input and
product identities; only the new state owner is compiled. A typed WinMain
observation calls the actual recovered stdio functions and real Kernel32 file
APIs. The image uses `/NODEFAULTLIB` and imports KERNEL32 alone.

The process passes binary write/seek/read/close, default text CRLF output and
input translation, binary-default selection, explicit text override, commit
flag selection, read-only creation through the mask, and missing-file
publication to both error words. Independent raw OS reads check the bytes on
disk. Temporary files are removed. No flush/close observation fixture supplies
these effects: the maintained stdio finalizer, flush-all and close-all owners
are linked. Normal entry return reaches the actual exit controller.

Six whole original library members remain explicit dependencies: the physical
x87 control backend, two SEH members, memmove, strncpy and the stack probe.
Their presence is not a source-restoration claim. This check does not exercise
every error, inherited-handle or process-cleanup path.

The same new source passes strict native C90 compilation. An attempted MinGW
compile exposes its SDK's `errno` accessor macro, which conflicts with the
single-thread CRT global definition. That profile needs an explicit CRT macro
policy before adopting this owner; no header workaround or MinGW integration
claim is made. VC4 and the native source are unchanged after that diagnostic.

## Game integration remains open

A staged real-game link identified these missing state definitions. Its typed
standard-name adapters connect existing recovered implementations. Adding the
entire original LIBC then reproduces duplicate startup, error, argument,
initializer, matherr and multibyte owners, plus an unwanted `main` dependency.
Do not force that link or replace the recovered owners. Continue with explicit
low-level members and genuine typed adapters. The private Windows-binding
entry hook and standard-name adapters remain diagnostic; the public game build
still uses its existing host startup.

All function ledgers and exact/candidate reports remain byte-identical:
545 inventory entries, 475 source entries, 380 exacts, 95 candidates,
77,485 exact code bytes and 244 metadata bytes. Data definitions add no function
or exact count. No full replay or historical Oracle queue runs. Compiler,
provider and Wine work remains serial under the 35% CPU, 640 MiB high and
768 MiB maximum memory scope; Ghidra uses its 256 MiB heap.

After adoption, six byte-identical immutable header snapshots share retained
copies, releasing 24 KiB of allocated storage. Unique observations, failed
diagnostics, fixture variants and current compiler products are preserved.

Private receipts are under `.analysis/crt-game-entry-20261016/`:
`original-state-members.json`, `runtime_io_state.product.json`, `io-link.json`,
`io-runtime.json`, `io-verification.json`, `portable.json` and `adoption.json`.
The three new observations are in retained REA run
`2026-10-16T14-38-21.002Z-state-requests-956842`.
