# CRT stdio initialization and storage

The previously omitted `___initstdio` at `0x41DA90` now has complete shared C
source. Its 193 bytes and all 16 actual relocations match under VC4. The
standard-stream storage now supplies the real 20 records, 4096-byte input
buffer, buffer-request counter, stream limit and allocated table pointer.

Initialization chooses 512 slots for a zero limit and clamps smaller nonzero
limits to 20. It first allocates the requested zeroed pointer table, retries
with 20 slots on failure, then reports fatal reason26 if that fails too. The
first20 slots point to the actual static stream records; remaining slots stay
null. Invalid or null low-I/O handles mark the corresponding first three stream
descriptors as -1. Existing fields, input buffer and request counter are retained.

## Original and source proof

The pinned `_file.obj` at library header `0xBB106` contains the whole193-byte
function,644-byte initialized record and4096-byte common input buffer definition.
The code matches retained complete REA Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
Its dependencies agree with previously accepted allocator, stream and low-I/O
bindings; complete recipes are in `config/match-units.toml`.

Fresh REA6.5.0/Ghidra12.1.4 Evidence
`ev_84d4a2a7fd9c983f31ccc78b78acfc3b32119d64c608e4d17ec5c3f60cd8803b`
reads all644 initialized bytes at `0x424058`. Both the original member and the
new data owner match this complete record after their two DIR32 bindings. All
fixed bytes excluding those actual pointer relocations uniquely locate it in
the verified image. The input record has read/user-buffer flags and capacity
4096; stdout/stderr have write flags and descriptors1/2; the remaining17 records
are zero. The request counter follows at offset640.

Both serialized input-buffer pointers bind `0x43FC60`; its4096-byte width comes
from the member's common definition. The stream limit/pointer at
`0x43FC54`/`0x43FC58` retain their existing complete consumer bindings. These
all-zero globals have no independent unique data anchor. No serialized4096-byte
BSS comparison or complete linker-layout claim is made. The native fixture
checks genuine zero-initialized source storage before modifying it.
Data recipe: `config/runtime-stdio-state.json`.

Evidence `ev_85c015660a9dfa2442909f8e4442c485e743a1d1529e0fc998788dd14d4156df`
reads the correct XI range `[0x421030,0x42103C)`: null, `0x41DA90`, `0x41F880`.
It confirms original registration of stdio initialization followed by onexit
initialization. This supersedes the earlier diagnostic read of a C++ prefix.
Reconstructed linker-section registration, XC producers and complete restored
CRT startup remain open; no manual startup bypass is added.

## Focused checks

Each of the two new owners is compiled once by VC4 and once per native/i686 C90
profile with warnings treated as errors. The native PIC objects are reused in
the small differential library. Fourteen original/native calls cover zero,
negative and boundary limits,512/1024 slots, first-allocation failure, minimum
fallback, both failures/fatal26 and all three handle outcomes. Comparisons
include allocation counts, publication/null state, all20 stream identities,
zero tail slots and every stream field. Buffer/request state remains untouched.
Allocator/fatal and low-I/O handle boundaries are controlled typed fixtures;
there is no physical OS stdio or full runtime/game acceptance.

Private evidence: `.analysis/stdio-initialization-source-20261016/`, including
`original-proof.json`, `data-proof.json`, `source/`, `native-differential.json`
and `adoption.json`. The focused REA session closed and saved27 records.
Compiler/provider work is serial with one allowed CPU, CPU35%, memory
high640MiB/maximum768MiB and Ghidra heap256MiB.
Sharing19 verified identical immutable carriers reclaimed about8.4MiB while
retaining unique evidence and independent canonical objects.

Current totals are543 independent entries,468 source-present,380 exact functions
covering77,485 code bytes and244 metadata bytes. All379 prior exact recipes,
results and producers are unchanged; all88 candidates and249 semantic rows
are unchanged. No full replay or game rebuild ran. Final CRT table/storage
integration, remaining function recovery and the final VC4 game/play check
remain required.
