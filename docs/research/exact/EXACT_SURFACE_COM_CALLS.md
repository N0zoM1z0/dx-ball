# Complete surface COM calls

The shared [resource implementation](../../../src/resources.cpp) now calls
DirectDraw surfaces through a C++ interface with the original stdcall ABI.
Three complete functions match the original executable, including every
relocation and literal:

| Function | Original address | Complete bytes |
| --- | --- | ---: |
| `blt-sprite` | `0x4040B0` | 195 |
| `capture-sprite` | `0x4042B0` | 852 |
| `draw-glyph` | `0x404CF0` | 328 |

The change also makes the previously exact stretch function nonexact:
141 bytes against 139, with 90 differing positions. Its rectangle calculations
still match. Two bank/sprite address producers load the bank into ECX instead
of EAX, adding one byte each. The old complete match is retained as historical
evidence and removed from the current exact ledger.

The net gain is **two functions and 1,236 bytes**, bringing the total to
**234 exact functions / 60,722 code bytes / 136 metadata bytes**. All other
accepted functions survive the complete comparison. There are 39 remaining
authored candidates.

## Shared declarations and ABI

The surface declaration follows the 36 original `IDirectDrawSurface` slots,
with one `IUnknown` base and no virtual destructor. Invoked method slots agree
with the existing C callback table. Win32 declarations use the pinned SDK's
HRESULT, DWORD, ULONG, LONG and RECT types; the native analysis host keeps
their 32-bit scalar widths. The C view retains explicit receiver arguments.
DirectDraw and palette calls keep their existing C interface view.

Resource functions and globals retain C linkage. The allocator include now
explicitly uses C linkage too, following the other C++ owners. The earlier
private model emitted decorated allocator references; that diagnostic mapping
could not establish a linked implementation. Current objects bind the actual
C exports directly.

The same source serves Native, MinGW and both VC4 resource recipes. Matching
uses `/ML`; production uses `/MT`. Neither has a separate executable body.
The original source language remains inferred from the emitted calls.

## Verification

Twenty-eight affected matching recipes were compiled and compared, followed
by all 234 current complete code, literal and metadata closures. Native and
MinGW builds pass. VC4 links 27 fresh matching objects, five production objects
and five verified unchanged objects.

The existing resource driver passes 1,869 original/native cases, including
36 stretch, 36 ordinary blit, 12 capture, 768 glyph and 99 PCX cases. Six existing
capture/bank callback scenarios also pass. Historical input inventories
refresh 249 rows; those are not new behavioral runs. No game run accompanies
this checkpoint.

Of the 38 retained candidates, 37 keep identical relocated code. PCX changes
one signed comparison: exchanging the two operands and JLE/JGE preserves the
same successor. EAX and comparison flags are overwritten before another
consumer on both paths. Its complete 979/862 comparison stays at 851 differences.
Bank loading retains 1475 bytes and 72 differences.

The larger experiment that also converted DirectDraw and palette to virtual
interfaces loses additional accepted bodies and is rejected. Its separate
evidence remains in `.analysis/ddraw-full-com-20261013/`.

Original REA evidence is blit
`ev_1b6c1b404e87fc6a492e8b2ed1d3eea8020a9f5446a6c5eaf8d76b4a0533df40`,
capture `ev_d7dd48a6f210a1a2cffea6be8318655763959610c9d94f8f8ff5621dad169b76`
and glyph `ev_21080b939b28e2885082bf86ee64b5815bdfeaea9276e5163a6318197d18b244`.
Current compiler inputs, complete comparisons, ABI review, before products
and verification are retained in
`.analysis/surface-com-integration-20261013/`.
