# Exact particle drawing

The complete function at `0x414CB0..0x414DEF` now matches all 320 bytes and
21 actual relocations. One canonical VC4 MT compilation restores the nonempty
surface description and per-particle pixel-pointer lifetimes. Names, types,
executable tokens and the shared implementation remain unchanged. Current
totals are 203 exact functions, 42,656 code bytes and 136 metadata bytes;
full game fidelity remains unproved.

## Source, frame and original evidence

The rectangle and Lock result stay in the function scope. The description
belongs to the nonempty-queue branch and survives through Unlock. Each pixel
pointer belongs to its draw iteration and ends after that particle's region
call. Every local is consumed; no padding or unused storage is added.

| Role | Original and emitted home |
| --- | --- |
| Rectangle | EBP-16, 16 bytes |
| Lock result | EBP-20 |
| Nonempty surface description | EBP-128, 108 bytes on i686 |
| Per-particle pixel pointer | EBP-132 |

Both frames reserve 132 bytes. Earlier flat declarations put the pixel pointer
at EBP-4 and result at EBP-132, shifting the rectangle and displacement widths.
The before object has 311/320 bytes and 212 complete comparison differences.
The restored scope matches every byte and original instruction boundary.
A lexical check confirms identical executable tokens after declaration movement
and braces are excluded. Original identifiers and unique spelling remain unknown.

The complete, contiguous REA dossier is Evidence
`ev_78508bf5cd7a13bba8f876482f913dfeffc0fee30ef126fc6a216c32b14bca6e`,
private `04-analyze_function.json` in closed run
`2026-10-07T06-51-49.754Z-rea-entity-lifecycle-2200960`. It binds target SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
Its instruction observation includes GetSurfaceDesc, Lock retry, two real CRT
memset calls, region update, list advance, Unlock and the complete return.
The saved static evidence is reused without a provider startup.

Changed displacement widths move 14 actual COFF relocation offsets. The first
comparison consumer rejects the shorter candidate's old offsets. Every new
offset is checked against the original instruction address and operand; ordered
symbols, types, addends and targets stay identical. Comparison then reuses the
completed compiler object without another compile. All 21 relocations and
320 bytes remain in the strict comparison, without masks.

## Preserved behavior and validation

An empty queue returns without touching the surface. A nonempty queue obtains
its description and retries Lock until success. Each particle writes two bytes
at its pixel position, advances by pitch and writes two bytes on the next row.
memset truncates color to eight bits. Live coordinates then form its 2x2 region,
followed by queueing and list advance. One Unlock ends the traversal. Driver
failures that never resolve remain outside the accepted terminating domain.

Two unchanged maintained entity Oracle loops pass 36 direct draw cases and
980 separate connected checks. Direct cases cover lengths 0..8, both pitches,
zero/two Lock failures, edge/overlapping particles and color truncation, comparing
complete pixels, row padding and guards. Connected hit/effect/bonus/particle
flows include 240 draw calls with full pixel comparisons, complete queues and
ownership, poison after release, ordered callbacks, RNG and state. Test cases
and original execution bodies stay fixed. Physical DirectDraw presentation
is not established.

Particle creation and movement stay exact across 477 bytes; their complete
comparison records are identical to the before object. Native and MinGW
rebuild. VC4 links the final matching particle object with 35 verified unchanged
objects and no additional source compile. Its initial consumer stops before
linking while the comparison receipt is pending; only one actual link follows.
All 203 exact closures, 36 production objects and 247 unchanged historical
semantic scopes verify. Their 235 changed input inventories refresh without
unrelated suite replays.

Working compiler inputs, before comparison, original reference, offset
reconciliation, instruction/frame proof, consumer recovery and Oracle receipts
are in `.analysis/particle-draw-scopes/`. Independent preservation is
`.analysis/checkpoints/particle-draw-scopes-283-203/sha256.json`, with explicit
before-product and closed REA dependencies. No alternate profile, name or
padding trial is used. The reconstruction goal remains active.
