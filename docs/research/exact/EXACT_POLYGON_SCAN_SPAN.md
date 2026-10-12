# Polygon scan setup and consumed span arguments

Historical checkpoint: [separate sort temporaries](POLYGON_SORT_TEMPORARIES.md)
now restore both original 80-byte frames and twenty distinct consumed homes.
The complete candidates retain 218 differences each.

Both polygon controllers now restore the original independent `live` and `next`
zero assignments, initial `pending[next]->top` load, and consumed row-address
local before horizontal fill. Clipped fill selects `left > 0 ? left : 0` and
`right < 639 ? right : 639` as arguments without rewriting the endpoint locals.
The clipping gate and unresolved zero-edge domain remain unchanged. Only
`src/raster.cpp` changes; no fake locals or frame padding are introduced.

The complete original/current bodies have identical instruction boundaries and
corresponding direct branch destinations/call targets:

| Controller | Original / current bytes | Instructions | Direct branches / calls | Before / final strict differences |
| --- | ---: | ---: | ---: | ---: |
| Ordinary polygon | 1543 / 1543 | 458 | 67 / 11 | 886 / 223 |
| Clipped polygon | 1592 / 1592 | 468 | 71 / 11 | 721 / 220 |

All3135 bytes/926 instructions are decoded and reviewed. Source producers and
ABI-defined effects correspond through explicit groups; this is not exact code.
Original frames have20 local words, current frames19. The current saved pointer
has nonoverlapping pending/active uses corresponding to two original slots.
The19 base homes therefore need a scoped override for the active sort, rather
than a whole-function bijection. Independent point-loop zero stores commute
without an intervening effect; their original declaration spelling/order remains
unproved. Signed operand-reversed comparisons choose the same successor;
commutative gap+j producers form the same sum.53 ordinary and36 clipped
normalized unequal instructions are covered by21/15 explicit groups;837 others
agree. Raw ESP, CMP flags, arbitrary callee scratch and void-exit register
residue are outside this claim. Both controllers retain five32-bit stack
arguments and `RET20`.

One stable matching VC4 compilation precedes complete comparisons and dependent
builds. Nine accepted raster units retain715 exact code bytes/136 metadata
bytes. Triangle remains1710/1710 with99 strict differences; its complete
160-byte/17-relocation candidate metadata remains exact but is not added to
accepted metadata. Triangle's1710 raw code bytes and all68 actual relocations
are unchanged before/current; horizontal span's144 raw bytes are unchanged.
Generated labels are checked through actual old/current COFF definitions,
relocation offsets/types/addends and independent original targets.

Native rebuilding moves triangle by48 bytes, changing94 PC-relative call fields.
All662 instruction boundaries remain stable and every changed instruction is
a five-byte direct call with the same computed target. Complete canonical
instructions/operands and internal targets agree for triangle, horizontal span
and eight fixed-point functions:10 unique functions represented by13 symbol
names. Actual external/RIP targets, full PLT bytes and285 actual PLT relocation
identities agree. A raw symbol-byte hash alone would misclassify this relocation
change. Their unchanged historical cases are not rerun; this is emission
identity evidence, not a fresh runtime or complete-game claim.

Each original/Native and actual VC4 COFF/Native profile passes1080 unchanged
existing polygon cases (288 ordinary/792 clipped), with full guarded buffers
and ordered effects. No triangle/span or historical full replay runs this batch.
Native/MinGW each compile only raster and link the selected core/game targets;
VC4 links the matching object plus35 verified unchanged objects. All36 object
closures and four final products verify.235 historical semantic input closures
refresh while their247 scopes remain historical. Source283/exact186/33001 code/
136 accepted metadata and origins270/83/42/133 remain unchanged.

Evidence reuses closed REA dossiers from
[endpoint/indexed storage](EXACT_POLYGON_ENDPOINT_STORAGE.md), with no new
provider query or transport/token/latency/RSS measurement. Actual recipes,
complete disassemblies, producer/CFG proofs, Native emission identity, selected
profile payloads and product hashes are in `.analysis/polygon-scan-span/`.
Immutable seal: `.analysis/checkpoints/polygon-scan-span-283-186/sha256.json`.

This completes the concrete scan-source gaps identified by the
[sort lifecycle review](EXACT_POLYGON_SORT_LIFECYCLE.md). Complete body strict
matches and original declarations remain unproved. Further source recovery
requires independent enclosing evidence for an actual missing producer or
complete game flow; do not trial local names, scope layout or comparison
spelling merely to alter register allocation. The full authored denominator,
synchronized rendering/audio fidelity and original-source goal remain open.

Cleanup verifies79 sealed files/173 explicit immutable dependencies after36
scoped hardlinks replace4,227,072 single-link allocated bytes. Three downloaded
wheel caches remove17,997,824 allocated bytes after their installed package
versions/module locations are verified. Installed tools and current products
remain unchanged. These are inode-allocation counts, not a measured device
free-space delta. Supplemental post-cleanup identities retain the cleanup
receipts and current documentation without modifying the immutable seal.
