# Runtime surface calls

The shared [runtime implementation](../../../src/runtime.cpp) uses virtual
stdcall calls through the recovered DirectDraw surface interface. Six calls
change: one BltFast call in paddle drawing, two in score rendering, and
three Blt calls in redraw. Arguments, branches, local scopes and state writes
remain unchanged. Public functions and globals retain C linkage.

The complete paddle body stays 677 bytes. Differences against the original
fall from 104 to 68. The remaining differences comprise 44 stack displacement
bytes, 20 bytes in the first bank/sprite-width address calculation, and four
bytes in the overlay-width equality comparison. These are byte positions,
not missing operation counts. The function remains a candidate.

All ten runtime exact functions retain their 2,282 bytes. The five other
runtime candidates have identical relocated code. Across the repository,
all 235 complete exact closures pass and the other 37 candidate code identities
are unchanged. The accepted total remains **235 functions / 61,716 code bytes /
136 metadata bytes**, with 38 authored candidates remaining.

A consumed drawing-record model was also compiled in this C++ call context.
It emits 679 bytes with 487 differences, so it is rejected. A separate game-over
surface-call projection preserves its seven exact companions but worsens
high-score drawing from 403 bytes/330 differences to 408/334. That owner stays
unchanged. Neither trial supplies an exact claim.

## Verification

One canonical matching compilation compares all sixteen runtime functions.
Each actual relocation is bound explicitly. Six reordered global reads in
paddle drawing use independently established target addresses; no positional
mapping or masked byte is used. Compiler inputs include every recursively
consumed project header.

Native and MinGW builds pass. VC4 links the fresh matching runtime object with
36 verified unchanged objects. The existing native driver passes 950 focused
clock, elapsed, paddle, score and redraw cases. Six existing paddle callback
cases preserve the dirty rectangle when BltFast changes paddle width and
overlay height during drawing. Both receipts identify the current library.
No connected gameplay frames or game run accompany this checkpoint.
Historical input inventories refresh 249 rows without claiming fresh execution
of those unrelated scopes.

Original paddle REA evidence is
`ev_0b4d5d681d951be5b6a69ac1d9d09db3cc965811c767e0b2b4f7296609cc020a`.
Complete current comparisons, relocation provenance, before products and
independent review are retained in `.analysis/runtime-com-integration-20261013/`.
The selected projection and rejected record combination are in
`.analysis/runtime-surface-com-20261013/`; the game-over trial is in
`.analysis/gameover-surface-com-20261013/`.
