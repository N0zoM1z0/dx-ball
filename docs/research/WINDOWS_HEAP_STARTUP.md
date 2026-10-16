# Windows heap initialization before the game entry

Win32 allocator defaults now call genuine HeapCreate/HeapAlloc/HeapFree before
the game adapter is installed. The other hosts retain the explicit malloc/free
bridge. The public allocator header, import-cell ABI and all eight exact
allocator function bodies remain unchanged.

The old default initializer returned the host bridge's identity byte on Windows.
That value was not a Windows heap. Even when a caller explicitly installed the
Windows bindings first, the host WinMain wrapper unconditionally created another
heap, replacing the handle associated with earlier allocations. This prevents
safe staged initialization before the game entry.

The wrapper now creates a heap only when `dxball_runtime_heap` is null. Rebinding
the Windows callbacks preserves an existing real heap and its allocations.
The original 21-byte initializer itself still always invokes HeapCreate, as
required by its exact source; the lifetime condition belongs in the host wrapper.
Windows clients using allocation before WinMain must explicitly initialize the
heap first. The defaults supply the physical API, rather than lazy allocation.

The resource inspector now supplies that initialization before decoding. Its
owned memory surfaces continue using their separate CRT allocation/release
pair. Default legacy console links also need `winmm.lib`: their shared clock
owners reference timeGetTime. The previously missing dependency is fixed for
both tools. The game already linked that library.

## Focused evidence

| Entry scenario | Old result | Current result |
| --- | --- | --- |
| Fresh WinMain | Pass | Pass |
| Default initialization before WinMain | Not a Windows heap; exit 2 | Real heap retained; exit 0 |
| Windows bindings and initialization before WinMain | Heap replaced; exit 2 | Original heap retained; exit 0 |

These cases execute the actual maintained WinMain body. Only its typed game-call
dependency is renamed for the fixture, whose endpoint checks argument/return
transport and returns 37. Heap APIs, adapter bindings, allocator bodies, C++
operators and typed list operations are real. GetProcessHeaps/HeapValidate check
the physical handle and ownership. A seven-byte buffer and typed node allocated
before entry remain valid afterwards; contents survive and real release works.
No alternate game implementation or fabricated heap handle supplies the pass.

A separate MinGW C90 executable verifies the same default private heap, binding
record/cells and physical allocation/release. The native host translation unit
is identical after preprocessing, ignoring empty lines only. Its affected core
and resource tool rebuild successfully. Native and VC4 inspectors produce
identical complete SFONT output (96 sprites) and INTRO pixel/palette fingerprints;
the VC4 board inspector also exits zero. Already completed successful tool runs
are reused after separating Wine's display-close diagnostic from JSON output.

The default VC4 game/tools build reuses 35 objects and compiles four. Original
allocator/list/C++ API compiler products retain their preceding identities.
No full replay, historical Oracle queue, GUI/campaign or new provider runs.
The preceding first-board evidence belongs to its recorded checkpoint; this
check establishes heap/entry ownership and tool behavior, not a fresh GUI run.

All 376 original-target exact results and 88 candidate results remain unchanged.
The 249 semantic scopes/counts remain historical, with 243 dependency input
closures refreshed through unchanged native preprocessing and focused Windows
controls. This does not claim fresh execution of every historical owner.
Function source remains 464; the complete reconstructed CRT entry/storage/link
and heap teardown remain open.

Private source snapshots, the two baseline failures, real Win32/MinGW products,
native preprocessing, inspector outputs and adoption receipt are retained in
`.analysis/windows-heap-startup-20261016/`. Commands run serially on one CPU under
the 35% CPU, 640 MiB high and 768 MiB maximum memory scope.
