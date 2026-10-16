# CRT initializer sections and linked startup stages

Later [FP startup integration](RUNTIME_FP_STARTUP.md) also runs the real FP
callback and maintained controller before these XI/XC ranges, then returning
XP/XT cleanup. The full84-byte table remains correct; hardware state, actual
conversion callbacks, streams/filter and list roots pass without host CRT
startup. Full CRT entry and the final game remain open.

The later [exit-section recovery](RUNTIME_EXIT_SECTIONS.md) extends this
64-byte initialization prefix to the complete 84-byte table, including XP/XT,
and checks returning cleanup and physical normal/quick exits. The following
text retains the XI/XC checkpoint and its original scope.

XI/XC now use real linker sections. Stdio and onexit contribute to `.CRT$XIC`;
the C++ filter entry contributes to `.CRT$XCC`; four null records delimit XI
and XC. The existing list object supplies nine compiler-generated `.CRT$XCU`
records unchanged. The marker owner emits the original merge into writable data.

VC4 `data_seg` and GNU `section`/`used` attributes place the same typed data;
function bodies remain unchanged. Link stdio before onexit for their same-name
XIC contributions. Other ordering follows COFF section names. Native/i686
object compilation passes; GNU/ELF linker integration remains unclaimed.

| Original range, including end marker | Bytes | Callback bindings |
| --- | ---: | ---: |
| XC, `0x421000..0x421030` | 48 | 10 |
| XI, `0x421030..0x421040` | 16 | 2 |

REA6.5.0/Ghidra12.1.4 Evidence
`ev_73a146a038dc9800cd869abb7261b6989c3713c813683a1453cd464602ea0586`
reads all84 bytes of the initialization/exit tables. The complete64-byte XC/XI
prefix matches after all12 actual callback bindings, both as source COFF
contributions and in a fresh linked image. Four markers also agree with pinned
`crt0init.obj`. Callback recipes use maintained complete function entries;
table agreement does not promote nonexact constructors or prove the board
aggregate's unresolved intermediate helper.

The full read is retained for remaining XP/XT work. REA close reported
`cleanup_incomplete` after a process-ownership token mismatch. Both reported
PIDs and its private directory were confirmed absent afterward. Complete
per-read Evidence and the error remain; no cumulative snapshot was saved and
the provider was not restarted to repeat the successful read.

## Actual isolated VC4 execution

A custom-entry executable links with `/NODEFAULTLIB`, importing only KERNEL32.
It runs actual private-heap and low-I/O initialization, then invokes XI and XC
through the maintained walker. A host CRT does not perform these steps first.

The real stdio table has512 slots,20 static stream identities and a null tail;
the onexit table starts with32 slots. The actual filter installer registers
the restoration callback, installs the Windows filter and saves the previous
OS callback. The real restoration function restores it. Nine list roots are
prefilled with nonzero bytes before XC; their maintained constructors clear
all four observed fields. List, filter, allocator and low-I/O dependency
objects are reused by complete input/product identity.

Unexercised stdio/fatal and exception-dispatch dependencies have typed traps.
A fixture C `exit` symbol forwards to the maintained controller; the real
reconstructed C++ allocator resolves the list object's APIs. A mixed-header
C++ fixture was rejected for conflicting Win32 declarations. Separate typed
observation units fix that fixture. Stable source products are reused through
fixture/link repairs; no host CRT is substituted. This checks initialization,
filter installation/restoration and list roots, not exception dispatch,
physical stdio, FP initialization, full CRT entry or the final game.

Four stable owner compiles preserve complete193/54/30/5-byte exacts. Their282
bytes also match after actual image relocations. All380 exact byte results,
88 candidates and249 semantic rows remain; the candidate report and semantic
ledger are byte-identical. Source/inventory counts remain468/543. No full
replay, game build or campaign ran.

Recipe: `config/runtime-initializer-sections.json`. Private evidence:
`.analysis/crt-c-initializer-sections-20261016/`, including `source/`,
`verification.json`, `link.json`, `probe-terminal.json`, `xi-only/`,
`provider-cleanup.json` and `adoption.json`. Heavy work is serial, one allowed
CPU, CPU35%, memory high640MiB/maximum768MiB, Ghidra heap256MiB.
Sharing33 identical immutable carriers reclaimed about10.5MiB; unique trial
sources, errors, evidence and probe products remain.

XP/XT still use ordinary default arrays. Their linker sections, remaining
FP/CRT state and low-level functions, final original-compiler game build/play
check, and later ports remain unfinished.
