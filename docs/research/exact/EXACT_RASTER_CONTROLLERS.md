# Independent raster controllers and horizontal fill

The latest [endpoint/storage restoration](EXACT_POLYGON_ENDPOINT_STORAGE.md)
restores both point rereads and repeated indexed stores, with89-instruction
construction correspondence in each controller. Current candidates are
1484/1543 with1025 differences and1544/1592 with1048. Triangle remains
1710/1710 with109 differences and complete160-byte candidate metadata exact;
the following earlier counts/checks retain their historical product and scope.

The later [metadata and correspondence audit](../RASTER_METADATA_CORRESPONDENCE.md)
reconciles stale generated metadata names and explains all 482 current triangle
instructions. Full code remains 107/nonexact; the historical checks below
retain their original product and scope.

The shared C++ raster owner now restores the original horizontal fill at
`0x40B4C0` and two independent polygon controllers at `0x40B550` / `0x40BB60`.
Their previous implementation factored sorting and scan conversion into generic
helpers, with indirect allocation/free callbacks. Retained REA instructions
establish separate controllers and genuine direct calls to runtime malloc
`0x417770` and release `0x417750`. The maintained allocator implementations supply
those calls; the original unsigned request width is retained. Native pointer
arrays grow with the host ABI, while their logical contents and the 28-byte
scalar edge records remain comparable.

The controllers retain all three allocations before the failure gate, nonnull
failure cleanup in pool order, horizontal-edge exclusion, ascending endpoint
orientation, separate strict Shell sorts by top and x, overlapping active-edge
removal, signed error updates and inclusive horizontal spans. Clipping tests
the pair before clamping to the original 640-by-480 limits. No return is added
for the original unbounded zero-edge domain. Original local spelling and full
controller storage scheduling remain unproven.

The horizontal span keeps a real alignment counter initialized to zero, advances
the row by the left endpoint, and writes an alignment prefix only for lengths
greater than four and nonzero address alignment. The two loop conditions retain
their postfix increment/decrement evaluation. The observed final return is
explicit. This natural shared source matches all **144 contiguous bytes** on
its first stable VC4 compilation, with no relocations or attached metadata.
There are no declaration/name/layout trials, copied instructions, padding,
assembly or alternate profile bodies.

All eight existing fixed-point functions remain exact across their complete
571 code bytes and 136 metadata bytes. The complete triangle code/metadata
comparison remains a candidate: 1,710/1,710 bytes, 107 unaligned differences.
The new polygon candidates are 1,428/1,543 bytes with 1,239 differences and
1,488/1,592 with 1,280 differences. Their eleven bindings each declare the real
allocator, release, overlap-copy and span targets. No candidate is promoted
because its selected behavior passes.

One matching `/MT /GX` compilation consumed the four declared recursive project
inputs, including `allocator.h`. All affected accepted code and metadata was
compared together. The same actual object supplies the VC4 game link alongside
34 verified unchanged objects; no separate production source compilation was
needed. Existing SDK import libraries and game resources were identity-checked
and reused. Native and MinGW builds pass.

The native raster fixture now controls the actual physical heap allocate/release
slots, exercising the maintained runtime allocator bodies with malloc mode zero.
It preserves and restores the heap API, handle and mode. Existing failure masks,
allocation ordering, guards and scratch comparisons are unchanged. Original and
relocated VC4 execution retain their explicitly controlled allocator and MulDiv
boundaries. No process-wide allocator interposition is used.

Each final product check uses the same **2,232 selected existing cases**: 1,080
polygon cases, 72 triangle cases and all 1,080 span cases. Polygon selection uses
four existing ordinary contours and all seven existing clipped contours, with
existing orders, pitches, colors and all eight failure masks. Triangle selection
uses four existing shapes. Complete guarded pixels, row padding, immutable point
storage, scalar scratch, normalized pointer entries and ordered calls agree.
The original code and IAT remain unchanged. These separate checks do not double
historical case totals. No full owner queue, new Wine game run, physical driver,
exceptional unwind or actual raster game-use claim is made. Direct game use
remains unresolved in the retained bounded cross-reference results.

Global acceptance becomes **171 exact functions /30,744 code bytes**, with 136
metadata bytes. Source presence stays 283 and scoped semantic rows stay 247;
their historical case counts and scopes survive actual input-identity refresh.

REA Evidence: span `ev_e55d01a59c45980c265834061218ad417ec912723618f19099f1de192067f5cf`,
polygon `ev_493013a754a8856f617731fcd1fddd0b00f6bd3d39f2de9d39f29742e542e205`,
clipped polygon `ev_4ae581c6e8ad135b183d562df04de63db4419e39e3f9b46891bdec2634ee5358`.
All three enclosing bodies are fully owned and contiguous. No new provider was
opened. Receipts and complete selected native/COFF checks are retained under
`.analysis/exact-raster-controllers/`; the sealed checkpoint is
`.analysis/checkpoints/raster-controllers-283-171/sha256.json`. REA feedback entry
24 remains in the user's single `/tmp/dxball_rea_feedback_20261010.md` document.
