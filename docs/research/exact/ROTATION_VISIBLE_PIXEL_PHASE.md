# Rotation visible-pixel locals

The renderer's four round/truncate locals are now declared in the visible,
nonzero-pixel branch that consumes them. Their names, types and declaration
order stay the same. The destination pointer already belongs to this branch.
No arithmetic, guards, writes or calls change.

The complete comparison improves from 1451/1572 bytes with 1475 differing
positions to 1466/1572 with 1466. Both versions contain 365 instructions and
use a 424-byte frame. The extra 15 bytes come from five accesses to truncated
coordinates changing from short to long EBP displacements. Instruction order
and all other instruction lengths are unchanged. The new homes still differ
from the original; this is a partial reconstruction, not an exact function.

All four accepted rotation functions retain their 749 exact bytes. The height
candidate remains 193/191 with 158 differences. The original evidence is the
retained REA analysis of October 7, evidence
`ev_1dfa14e3428cac399a6bc2876da74d5bbc4a5edc8a8e03a6af79783e189daf26`.
An independent review checks the declaration-only change, eight compiler inputs,
actual relocation bindings and all six complete owner comparisons.

Receipts are retained under `.analysis/rotation-visible-pixel-phase-20261013/`.
The existing 351 renderer and 344 wrapper cases pass, including seven callback
and finite-retry scenarios. Native and MinGW builds pass; VC4 links the changed
matching object with 36 unchanged objects. All 232 accepted complete closures
pass, and the other 40 candidate code identities are unchanged. Historical
input inventories refresh 235 rows. No game session runs.

The completed rotation and rejected SDK stages retain 124 verified gzip copies,
releasing 8,622,080 allocated bytes. Current build products and original evidence
remain available.

The accepted total remains 232 functions / 59,486 code bytes / 136 metadata
bytes, with 41 authored candidates still nonexact.
