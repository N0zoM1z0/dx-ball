# Polygon endpoint rereads and indexed edge storage

Both raster controllers now restore the original endpoint reread and repeated
indexed field stores. Only `src/raster.cpp` changes. Original local spelling and
complete controller correspondence remain unproved; neither candidate is exact.

The closed original REA dossiers establish contiguous complete bodies:

| Controller | Original bytes | Before bytes / differences | Current bytes / differences | Original / current instructions |
| --- | ---: | ---: | ---: | ---: |
| Polygon `0x40B550` | 1543 | 1428 / 1239 | 1484 / 1025 | 458 / 442 |
| Clipped polygon `0x40BB60` | 1592 | 1488 / 1280 | 1544 / 1048 | 468 / 452 |

Descending endpoints assign `first = second`, then reload `second = points[i]`.
The original performs both point-field reads again; a saved third-point swap
misses that observed producer. Construction writes `top`, `bottom`, `x`, `dx`,
`dy` and `error` directly through `storage[used]`, repeatedly forming the
28-byte record index. Offset12 is unwritten. It publishes `&storage[used]` into
`pending[used]` before incrementing `used`. The genuine `edge` pointer remains
for later incremental updates. Allocation, failure cleanup, Shell sorts,
scan conversion, clipping and horizontal fill remain unchanged in source.

The complete construction intervals `0x40B61D..0x40B729` and
`0x40BC2D..0x40BD39` each contain269 bytes and89 instructions, including the
closing five-byte loop jump. Every instruction starts at the same offset as
original. Eight bijective local homes explain the stack references. The clipped
interval has matching normalized instructions throughout. Ordinary construction
retains two equivalent conditions: operand-reversed equality and signed
`first.y <= second.y` versus `second.y >= first.y`. These account for five
unequal instructions. Their raw CMP flags are not claimed equal. This scoped
producer/storage correspondence does not cover the remaining sorts/controllers.

One actual VC4 owner compilation uses the manifest's four consumed project
inputs and `/Od /Ob0 /Oi- /Oy- /Gd /MT /Gy /GX`. Nine existing accepted raster
units remain exact:715 code bytes and136 metadata bytes. Generated labels are
refreshed only after verifying old/current COFF section, value, type and storage,
actual relocation order/type/addend, and independent original targets. Full
triangle remains1710/1710 with109 code differences and zero differences across
its complete160-byte/17-relocation metadata; that metadata is candidate evidence
and does not increase the accepted136-byte total. Its unchanged source compiles
with reversed operands for one `pitch * y` MOV/IMUL producer at offsets422/425;
all482 instruction boundaries and mnemonics remain unchanged. Low32-bit product
and IMUL overflow behavior agree; this does not establish original spelling.

Validation uses unchanged existing case bodies and guarded destination payloads.
Each of the original/Native and actual VC4 COFF/Native profiles passes1080
polygon cases:288 ordinary and792 clipped, covering the selected four ordinary
contours, seven existing clipped contours, allocation masks/orders, pitches,
colors and complete effects/buffers. Each profile separately passes72 existing
triangle cases because its emitted producer changed. Horizontal span is unchanged
and byte-exact; its1080 historical cases are not rerun. These are separate profile
runs, not a claim of2304 distinct vectors or full-game/runtime fidelity.

Native and MinGW compile only raster, then relink their dependent products.
VC4 links this same matching object with35 verified unchanged game objects;
no additional source compilation. All186 exact identities and36 current game
object/input closures verify.235 historical semantic input closures refresh;
their247 acceptance scopes and case counts remain historical. Source283,
exact186/33001 code/136 metadata and origins270/83/42/133 remain unchanged.

Private records are in `.analysis/polygon-endpoint-storage/`, including the
actual compile, complete candidate comparisons, instruction listings,
construction proof, profile payloads, game-link recipe and final identities.
Immutable seal: `.analysis/checkpoints/polygon-endpoint-storage-283-186/sha256.json`.
The two reused closed original carriers are2786590/2858306 retained file bytes;
complete compact assembly projections are17025/17327 bytes. No fresh provider
query, latency/token/RSS measurement or original-source spelling claim follows.
