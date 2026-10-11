# Exact explosive source collection and neighbor conversion

The complete explosive-neighbor function at `0x4150A0..0x4153D7` now matches
all 824 bytes after 39 actual relocations. One canonical VC4 MT compilation
restores the collection phase and per-column scan lifetimes in the shared
typed source. Names, types and executable tokens remain unchanged. The current
total is 202 exact functions, 42,336 code bytes and 136 metadata bytes.

## Source and original evidence

The function first collects every explosive source in x-major order, then
walks that captured list and converts its four neighbors. Collection completes
before any conversion. Each neighbor block reads the live signed board byte,
updates the count when an empty/hard tile becomes explosive, writes the byte
and immediately draws that neighbor. The final source-list cleanup remains.

Propagation coordinates `x` and `y` stay in the function scope. Collection
coordinates and the consumed signed tile integer belong to the collection
phase; its inner scan coordinate belongs to each column's loop body. VC4 emits
the original 20-byte frame with these homes:

| Local role | EBP displacement |
| --- | ---: |
| Propagation x | -4 |
| Propagation y | -8 |
| Collection column | -12 |
| Consumed signed tile | -16 |
| Per-column scan row | -20 |

The original complete, contiguous REA dossier is Evidence
`ev_3d377be2b21a0bacfa9d8a165f08def8fa9f77830b0d0fe671d3aaedbf5ac7cf`,
private `06-analyze_function.json` in run
`2026-10-07T07-26-59.211Z-rea-bonus-dependencies-2331079`.
It is bound to target SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
Every one of its 208 instruction addresses agrees with the emitted boundary;
all 26 branches, nine calls and the full return are covered. The existing
relocation declarations retain their symbols, types, addends and independently
established targets. No bytes are masked, and no provider session is needed.

The preserved before object has 58 unmasked differences. The new object has
zero. A lexical comparison also verifies that all executable tokens remain
identical after declaration movement and scope braces are excluded. This
establishes matching maintained source, not unique original identifier spelling.
No name, padding, capacity or declaration-permutation trial is used.

## Validation and remaining gaps

Four affected exact companions remain exact across 748 bytes: screen pan,
explosive scan, special-brick softening and destructible counting. Their full
comparison records are identical to the before object. The complete hit and
enqueue candidates also retain identical comparison records: 1,316/1,315 bytes
with 418 differences and 100/99 with 51. Their gaps remain unresolved.

The unchanged maintained powerup Oracle passes 706 existing spread cases:
256 uniform byte grids, all 50 original boards and 400 boundary/interior grids.
The selection preserves the original random stream after the omitted rectangle
draws and compares full board/auxiliary state, ordered callbacks, active surface,
list payload and links, live allocations and poisoned released memory. No
fixture, case or original execution body changes; physical drawing and the
complete campaign remain outside this scope.

Native and MinGW rebuild the affected owner and products. VC4 links the final
matching gameplay object with 35 hash-verified unchanged objects, without
another source compile. All 202 current exact input closures, 36 production
objects and 247 unchanged historical semantic scopes verify. Their 235 changed
input inventories refresh without claiming execution of unrelated suites.

Private inputs, before products, complete comparison, instruction proof,
focused Oracle and product hashes are in `.analysis/explosive-collection-scopes/`.
The independent seal is
`.analysis/checkpoints/explosive-collection-scopes-283-202/sha256.json`, with
explicit dependencies on before products and the original closed REA carriers.
