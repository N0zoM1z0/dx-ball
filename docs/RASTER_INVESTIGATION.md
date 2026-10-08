# Software raster controllers: investigation in progress

REA identifies three remaining large graphics routines as triangle and polygon
fillers. The two polygon bodies own 1,543 and 1,592 contiguous bytes; the
triangle owns 1,542 bytes but reaches shared exception-cleanup code outside
that recorded extent. These are investigation candidates, with no origin,
maintained-source, semantic-count or exact promotion yet.

## Controller evidence

| Entry | REA observation | Evidence ID |
| --- | --- | --- |
| `0x40AB90` | Triangle, nine cdecl stack arguments; shared cleanup confirmed separately | `ev_ad1b11b19724c19c9001ac422c47b0b3b83c6b2965625e31729f969414a6467a` |
| `0x40B550` | Polygon, five stack arguments, `RET 0x14` | `ev_493013a754a8856f617731fcd1fddd0b00f6bd3d39f2de9d39f29742e542e205` |
| `0x40BB60` | Polygon with fixed 640-by-480 clipping, same five-argument ABI | `ev_4ae581c6e8ad135b183d562df04de63db4419e39e3f9b46891bdec2634ee5358` |

Arguments are pixel storage, signed pitch, coordinate/point inputs and a
color byte. The polygon pair takes a point-array pointer and signed count.
The triangle takes three signed coordinate pairs. Ghidra's inferred source
signature is evidence about its analysis, not authority over stack cleanup.

Focused direct `xrefs` return no incoming references for these three entries:
`ev_68078d60f8181998d46168217f5550783a739ced22332448afde1bd6459c9705`,
`ev_54789e1eaedec8ac98ebf8aaef1ee4473beb4820f15ee015fe36fd84a3880e7e`,
and `ev_5d2153a0da17fcd67b13003b7b2304070d289ffa21673c825bef2d980bab84a8`.
This bounds Ghidra's direct-reference result; indirect references, actual game
use and source authorship remain unresolved.

## Polygon edge lifecycle

Both routines allocate three pools before checking any allocation result:
28 bytes per edge and two arrays of four-byte edge pointers on original x86.
Horizontal edges are skipped. Remaining edges are oriented by ascending y,
then ordered by their top scanline. Active edges are added, expired, sorted by
x and paired on each scanline. Shell-sort gaps and strict comparisons preserve
the observed ordering for ties. Removing an active edge uses the original
overlap-safe memory helper.

Each edge retains signed top/bottom/x, an unwritten four-byte interval, signed
dx/dy and an error accumulator. Incremental positive and negative slopes use
different carry loops. Pair endpoints also depend on the error sign: the left
endpoint advances when error is positive; the right retreats when its error
is nonpositive. The lower y endpoint is excluded.

The clipped version tests the pair before clamping. It visits only y in
`0..479`, maps a left endpoint below one to zero and a right endpoint above
638 to 639. Clamping can reverse a span, which then writes no bytes. Moving
that test after clipping can alter control flow. Successful and failed
allocation paths free nonnull pools in edge/pending/active order.

Native pointer arrays grow with the host ABI. Their logical entries and edge
identity can be compared after validating pointer range/alignment; their raw
allocation byte counts cannot be claimed identical to original x86. The
28-byte scalar edge pool, including its unwritten bytes, needs full comparison.
Zero-edge/all-horizontal contours and invalid counts reach uninitialized or
unbounded target behavior; no arbitrary early return is inferred for them.

The actual horizontal-span helper (`0x40B4C0`, 144 bytes) is retained as
`ev_e55d01a59c45980c265834061218ad417ec912723618f19099f1de192067f5cf`.
It handles an alignment prefix and then writes individual bytes through the
inclusive right endpoint. Reverse spans write none. A simple natural C loop
can preserve the bounded pixel effects without claiming matching instructions.

## Triangle fixed-point boundary

The triangle sorts vertices by y, then fills the upper and lower phases using
signed 16.16 coordinates. The first phase chooses left/right by slope; the
second compares the accumulated long-edge x to the middle vertex's x. Signed
arithmetic shift converts coordinates to pixel endpoints, and the routine
clips to 640 by 480. Its C++ helper/exception scaffolding is executed by the
original-machine probe, rather than replaced by a triangle host callback.

Focused division-helper Evidence
`ev_c6a480b4faac1007c9b9251ce36a0995bcb10a4b08deadb831a14ed1c509e04a`
retains all 35 bytes at `0x40B390`. It passes its two fixed-point arguments and
multiplier 65,536 to the imported Win32 `MulDiv`. Exact instruction Evidence
`ev_8918b1c9e1c00cc27bea91410f1e26a891db3fa2703cffd585a82ae93c3d9558`
confirms `ff15a8124400`: an indirect call through IAT slot `0x4412A8`.
The PE import table names that slot `KERNEL32.dll!MulDiv`.

The initial unmapped fetch at `0x415EC` was the probe's unresolved import-name
RVA, not a broken game jump. Only this declared API boundary is supplied in
the next probe. Original target instructions and IAT bytes remain unchanged.
The [Win32 API contract](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-muldiv)
uses a 64-bit intermediate and nearest-integer rounding. Truncating the
reconstructed slope with ordinary integer division therefore loses behavior.
The bounded fixed-point fixtures use positive denominators and cannot produce
half ties or overflow; other Win32/legacy-platform corner cases remain open.

The triangle's inferred `__stdcall` signature is contradicted by its actual
shared epilogue. Byte Evidence
`ev_d64bd45eddb6639bae4fff303b983603d672b1995ecd881e2b97ecccb71be2d9`
returns all 16 bytes from `0x40B230`; instruction Evidence
`ev_a8978da4df2ff66d0deb5d0c94667943aeedf6cab27913ac3be8051538c83f6e`
confirms plain `RET` (`c3`) at `0x40B23D`. Original execution restores ESP to
caller ESP plus four, leaving all nine arguments for the caller to remove.
The C candidate therefore uses cdecl for the triangle and stdcall for the
polygon pair. The shared continuation is not silently added to the triangle's
owned-body exact extent.

REA's inferred comparator prototype also loses its result and arguments:
`ev_be6e9a7d382f289a211cef852ca5eea60578a845fbded075f21af4729e0a2285`.
The instructions compare `[ECX]` with a stack operand and return zero or one.
SEH continuations outside the owned extent make argument/return inference and
exact extent reconciliation separate questions.

## Related palette-tail loader

The same controller batch also retains the 376-byte cdecl loader at
`0x409A30`, Evidence
`ev_98c57eefa7609b36f191aa5039d7824322068c7f66ab662dc571d9bd57642930`.
It opens the path, seeks 768 bytes back from the file end, reads 256 RGB
triples into the live four-byte palette entries, closes the file and creates
then installs a palette. The fourth entry byte is untouched. The body does
not check open/seek/EOF results; its error-domain and resource-lifetime review
remain open. This observation adds no loader implementation or acceptance.

## Reproduction and acceptance boundary

The public request sets use the pinned REA entry point:

```bash
scripts/rea session config/rea-remaining-controllers.json
scripts/rea session config/rea-raster-helpers.json
scripts/rea session config/rea-fixed-point.json
scripts/rea session config/rea-raster-abi.json
```

The current private native draft passes **6,084 original-machine comparisons**:
2,448 ordinary polygons, 2,952 clipped polygons and 684 triangle permutations.
The polygon cases vary contour order, color, pitch and all eight allocation
failure masks; triangle cases include horizontal, degenerate and off-screen
vertices. Comparisons cover complete guarded pixel storage and row padding,
immutable point inputs, pool guards, complete scalar scratch bytes, normalized
pointer entries, ordered allocation/free calls and `MulDiv` arguments. Original
code bytes remain identical, and the triangle restores its synthetic SEH head.
`MulDiv` is a controlled API contract, not a tested Win32 implementation.

The fresh report binds the candidate source, actual native product, compiler
identity, driver and dependency inputs before and after execution. An earlier
5,400-case report whose original source/product were overwritten is explicitly
historical; it is not reused as current acceptance. The inferred-stdcall failure
also retains its actual source/product and original stack diagnostic.

Complete requests, results, Evidence IDs, snapshots and session closes are
retained privately. A natural typed C candidate and its native product remain
private experiments. Promotion needs a public shared owner, native/original
and actual VC4 comparisons, affected owner replay, and the configured cold
replay batch. Current accepted progress remains 217 maintained functions,
96,897 direct owner cases and 36 exact units covering 3,518 bytes.
