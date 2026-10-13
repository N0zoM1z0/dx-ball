# Complete palette interface calls

The shared [resource header](../../../src/resources.h) exposes the seven original
IDirectDrawPalette slots to C++ callers: IUnknown's three methods followed by
GetCaps, GetEntries, Initialize and SetEntries. The methods use the established
SDK scalar types and stdcall ABI. The existing C view remains unchanged.

Three calls use the virtual member interface: live-palette loading in resources,
rotation in display, and splash palette pulsing in intro. Their arguments,
branches, state writes and public C linkage are preserved. DirectDraw factory
calls continue using their existing interface.

Two functions now match their complete original bodies:

| Function | Original address | Bytes | Actual relocations |
| --- | --- | ---: | ---: |
| `stretch-keyed-sprite` | `0x4041F0` | 139 | 6 |
| `reset-round` | `0x415C40` | 426 | 43 |

Stretch regains its former complete match. Reset's original bank/sprite address
calculation now agrees. All 219 affected previous exact functions retain 60,122
bytes. The net gain is **two functions and 565 bytes**, bringing the repository
to **238 exact functions / 62,514 code bytes / 136 metadata bytes**.

Paddle drawing also improves from 68 to 48 differing byte positions in its
complete 677-byte body. The first bank/sprite address calculation now agrees;
44 frame displacement bytes and four equality-comparison bytes remain.
Paddle stays a candidate. A separate consumed drawing-record trial in this
palette context matches the original 68-byte frame homes but emits 679 bytes
with 467 differences. All eleven runtime exacts remain; the trial is rejected.
Its complete proof is in `.analysis/paddle-consumed-palette-20261013/`.
The other 34 retained candidate code identities are
unchanged; 35 authored candidates remain.

## Verification

The isolated model compiles all 26 affected matching recipes once, covering
253 complete units, actual relocations, literals and metadata. Its four source
changes reverse exactly to the previous files. Native C and pinned Win32 C
preprocessing produce identical palette views before and after the change.

Integration reuses those matching objects after verifying that every consumed
source and recursive project header is byte-identical to its canonical file,
and that the compiler and flags agree. The actual frozen producer receipts and
path-equivalence proof remain explicit. No redundant matching compilation is
needed. All 238 current repository closures pass afterward.

Native and MinGW build. VC4 links 25 verified matching objects, five fresh
production objects with their required flags, and seven unchanged objects.
The maintained drivers pass 542 focused cases: 36 stretch, five live-palette,
81 palette rotation, 120 splash pulse and 300 reset cases. Existing vectors and
assertions are unchanged. Completed case groups are retained when the selection
runner's setup/count checks are corrected. No connected gameplay or game run
accompanies the checkpoint. Historical input inventories refresh 235 rows;
all 249 recorded semantic scopes and case counts are preserved.

SDK slot/signature authority is the installed `ddraw.h`, lines 1294–1304.
Original function evidence remains linked from the configured match units.
The frozen model and C-view/source proofs are in
`.analysis/palette-only-com-20261013/`. Current complete comparisons, actual
producer/input-equivalence receipts, before products, focused cases and
independent review are in `.analysis/palette-com-integration-20261013/`.
