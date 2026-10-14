# CRT descriptor modes and heap resizing

Three original entries now have maintained, shared C source. Heap sizing and
resizing are exact; descriptor modes remain a candidate.

| Entry | Original bytes | Current bytes | Differences |
| --- | ---: | ---: | ---: |
| `_setmode`, `0x41FCC0` | 128 | 128 | 2 |
| `realloc`, `0x41FD70` | 111 | 111 | 0 |
| `_msize`, `0x41FDE0` | 21 | 21 | 0 |

Shipped `realloc.c` establishes an unbounded retry loop and an owned failure
return after the new handler. Restoring these closes111 bytes and all seven
actual relocations, including the unconditional heap reload at0x41FDD2 before
the backward branch. The full pinned section and retained REA
`ev_a7c91aa32057e35dc478b2453e1f69719213eb4b36a84df67971d205b09236cd`
independently cover the original. Msize21 exact, calloc82/11 and all346 old exacts
remain. One compiler set, no runtime/provider work. Current347/code71,723;
receipt `.analysis/heap-resize-original-retry-20261014/verification.json`.

`runtime_file_modes.c` validates the unsigned descriptor limit and open bit,
indexes 32-record low-I/O blocks with an eight-byte stride, and changes only
flag byte four. Text and binary modes return the preceding mode; invalid
descriptors set errno 9, invalid modes 22. The other record bytes stay opaque.
Only the initial CMP operand order and corresponding branch differ. Direct
byte updates restored the remaining instructions; positive validation and a
shared failure exit do not resolve the comparison. The size profile is worse.

`runtime_resize.c` reuses the allocator's heap, mode, malloc, free and handler
owners. NULL requests use malloc; zero-size requests free. Other requests use
the genuine stdcall HeapReAlloc import, reject sizes above `0xFFFFFFE0`, and
retry failed allocations only when the current mode and handler permit it.
The original reloads the heap unconditionally after the handler, before its
backward branch. The earlier reconstructed do/while loaded it at the next
iteration. An explicit loop-carried heap/result value adds a separate register
and is worse; direct and cached import calls retained15 differences. Those
trials are closed; original retry/failure ownership now restores the exact body.
The exact heap-size wrapper uses the existing heap and genuine HeapSize import.

The intervening `0x41FD40` entry is the 47-byte compiler stack probe, with EAX
as its size input and special ESP handling. The complete pinned section has
two co-located labels, `__chkstk` and `__alloca_probe`, and no relocations.
It is a compiler dependency, not a fabricated C function or additional exact unit.

Pinned VC4 library members for all four complete sections match the original
after every real relocation. REA runs
`2026-10-13T11-39-53.950Z-requests-1509370` and
`2026-10-13T12-11-08.976Z-mode-access-requests-1548641` retain complete info,
pseudocode and assembly. Their assembly Evidence IDs are recorded in the
function ledger. The latter run also confirms that `0x4177F0` is an interior
string-copy entry, not an allocator mode getter.

Private proof and producer receipts: `.analysis/runtime-digit-core-20261013/`.
The complete digit-conversion candidate also improves from 21 to 20 differences
by restoring the coarse shift's middle-limb carry accumulator. Its exact
102-byte addition companion is unchanged. All 249 preceding exact results
are preserved; the new 21-byte wrapper brings totals to 250 functions and
63,718 code bytes. Native/i686 standalone compilation covers the three changed
owners. No runtime tests or game builds run; the game uses its existing runtime.
