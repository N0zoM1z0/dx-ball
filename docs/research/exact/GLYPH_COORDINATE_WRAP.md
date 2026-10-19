# Glyph destination coordinate arithmetic

October 19, 2026. Three destination-rectangle expressions now explicitly retain
the original four DWORD sums/subtractions before signed coordinate storage.
The complete glyph body stays332 bytes/258 differences against original328.
Its lookup, signed code, field reads, Blt arguments and live width reread remain.

## Original operations

| Original site | Observed operation |
| --- | --- |
| 404D38 | Top: subtract signed height from caller baseline |
| 404D58 | Top: subtract glyph baseline from that result |
| 404D7D | Right: add caller X to width |
| 404DA3 | Bottom: subtract glyph baseline from caller baseline |

Original Blt at404E00 consumes these DWORD coordinates; width is reread at404E1F
after the call. Operands now convert to DxBallUInt before arithmetic, then the
result converts to DxBallInt. Supported VC4/GNU32-bit-int conversion preserves
the signed DWORD bit pattern. Signed fields and API declarations stay unchanged.
This recovers the machine arithmetic contract, not historical cast spelling.

Retained complete assembly Evidence:
`ev_21080b939b28e2885082bf86ee64b5815bdfeaea9276e5163a6318197d18b244`,
operation05 of `2026-10-10T17-38-24.772Z-requests-846003`.
Carrier SHA256 is `498261a5e916ba2e5f0ad969d00ffdb8c19a2972d2408846620d838b2c4d8301`.
All four raw instruction bytes, the consuming call and post-call width load
are checked against the pinned target without another provider query.

## Four finite boundary inputs

Each17-byte SBK prefix contains count2 and the first record's width,height,
code G and glyph baseline. Its low32 bitmap product is zero, requesting only
three pixel-buffer bytes. Actual CreateSurface failure publishes those fields
and a NULL source surface, then returns before a second record is read.

| Isolated operation | Width,height,glyph baseline | Caller X,baseline | Original destination RECT |
| --- | --- | --- | --- |
| First top subtraction |0,INT_MIN,0 |0,0 |0,INT_MIN,0,0 |
| Second top subtraction |0,2,INT_MAX |0,0 |0,INT_MAX,0,-2147483647 |
| Right addition |INT_MAX,0,0 |1,0 |1,0,INT_MIN,0 |
| Bottom subtraction |0,-2,1 |0,INT_MIN |0,-2147483647,0,INT_MAX |

Actual original/native loader, lookup and glyph bodies execute. Typed Blt
callbacks accept the NULL source, capture both rectangles/flags and return
failure without rasterization. The old instrumented source rejects exactly
the isolated signed operation in each process; all four proposal cases match
original rectangles and returned widths. Full bank state, active pixels/padding
and the file-descriptor set stay fixed during drawing. The loader's failure
ownership/open stream remain. This is direct glyph-entry boundary evidence,
not actual shipped-game reachability, damaged-font safety or physical graphics.

Two resource-only UBSan compilations reuse every other current native object.
The same four cases also pass on the actual new uninstrumented native library.

## Complete owner and compiler ripple

One VC4 compile compares all18 complete resource functions,262 actual bindings
and six full literal references. Eleven exacts/2577 bytes survive;17 complete
code identities stay fixed. The unchanged PCX source instead changes979/850
to979/851. No old companion object is selected.

Its complete227-instruction before/proposal correspondence accounts for34 changed
raw byte positions in16 instructions: four exchanged clipping inputs/converse
branches and two exchanged low32 product inputs. All16 subsequent original/
proposal EAX/flag CFG checks close. Multiplication pairs have equal combined
width and rejoin before the same ADD; all calls and branch successors agree.
Every other operation stays fixed. The851 strict result remains authoritative.

The resources-only incremental native build produces library SHA256
`d400ba4da656ba3f9cb688812954e16ff87903109966cecdee1ed9d2e818097b`.
Unchanged maintained loops pass769 glyph lookups and768 draws across all256
byte values in the three original fonts, plus their actual load setups and
empty-bank lookup. Other resource loops are not repeated. Semantic scopes and
case counts remain unchanged when current input hashes refresh.

All270 authored closure receipts verify:248 exact/22 candidates across30 owners;
overall393 exacts/84633 code bytes/244 metadata bytes remain. Source optimality
and the final authored denominator are still open. Private authority is
`.analysis/glyph-coordinate-wrap-20261019/`, including the parent result review,
full comparison, finite cases, PCX ripple and current coverage. No independent
review is claimed for this parent review.

Heavy work is serial under35% CPU,384MiB high/512MiB max. The VC4 scope takes
10.005s, peaks166764544 bytes and records zero limit events. No game relink,
game run or full replay follows. The verified EXE/ZIP remain the717cc2f delivery
and predate these source corrections.

All47 closed copied inputs, temporary objects/libraries and executed helpers/logs
are archived and member-size/SHA256 verified before exact-list removal. The
1080917-byte archive releases7847936 allocated bytes net before small receipts.
All91 protected current source/config/object/product/cache identities remain
fixed across cleanup; complete reports, primary evidence and current products stay.
