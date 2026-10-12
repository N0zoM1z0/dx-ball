# DirectDraw pointer qualifiers

The recovered DirectDraw declarations now use mutable rectangle, color-key and
palette-entry pointers, matching the original-interface declarations in the
local SDK. Blt has two rectangle parameters; BltFast and Lock have one each.
SetColorKey takes a color-key pointer, and palette SetEntries takes an entry
pointer. Their previous `const` qualifiers made the C function types differ
from those declared by the SDK.

The board-restore callback and its display forwarding function use the same
mutable rectangle type. The resource inspector's typed Lock, SetColorKey and
SetEntries implementations follow the corrected declarations. Calling slots,
stdcall, pointer widths, field layouts and function bodies are unchanged.
The vtable pointer remains read-only. No casts discard constness.

The installed `ddraw.h` corroborates the original IDirectDrawSurface interface
at lines 1926, 1928, 1946 and 1950, and palette SetEntries at line 1304.
The pinned VC4 headers also define mutable LPRECT and LPPALETTEENTRY.
No historical DirectDraw header was found locally. All four retained SDK-type
trial headers still had the const parameters, so those earlier comparisons
did not cover this declaration correction.

Twenty-eight affected matching recipes preserve 221 exact functions and 58,719
code bytes. All 232 global exact closures verify. All 41 candidate code hashes
are unchanged, so this correction adds no exact function. One initial resource
probe precedes the stable family compilation. Native and MinGW libraries,
game transports and resource inspectors build. VC4 links 27 fresh matching
objects, five separately compiled production objects and five verified
unchanged objects. Historical input inventories refresh 235 rows. No game runs.

Local SDK hashes, exact declaration lines, source comparison and full build
receipts are retained in `.analysis/ddraw-mutable-pointers-20261013/`.
The independent review confirms only the twelve pointer-qualifier removals
across five files and unchanged forwarding bodies.
Totals remain 232 exact functions / 59,486 code bytes / 136 metadata bytes,
with 41 authored functions still nonexact.

147 completed copies are retained in verified gzip carriers, releasing
4,632,576 allocated bytes. Current products and original evidence are preserved.
