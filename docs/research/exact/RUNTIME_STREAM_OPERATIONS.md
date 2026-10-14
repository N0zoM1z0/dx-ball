# CRT stream seeking and output

The complete pinned `_fseek` and `_fwrite` sections match the original at
0x418310/153 and 0x417E70/381 after all actual relocations. Shared typed source
now restores both functions through the existing stream and low-I/O owners.
Current complete comparisons retain 21 and 29 differences, respectively;
neither is exact. The seeking differences are register allocation/scheduling;
output differences are local storage, copy scheduling and comparison direction.
No artificial storage or declaration permutations are used to force a match.

Seeking validates stream flags and origin, clears EOF, resolves relative offsets
through the real `ftell`, ignores the flush result, resets update-stream direction
or read-buffer capacity, and tests the real descriptor seek against -1. Relative
offset addition requires a representable signed32 result, as the CRT interface.

Output preserves unsigned32 size multiplication, zero-total early return,
buffered copying, direct whole-buffer writes, short-write error accounting and
the signed-byte slow path. The capacity clamp occurs only after that slow path.
Buffer storage, nonoverlapping copies, coherent stream counts and lower-I/O
results follow the original contracts; no host FILE, new capacity or fixture
boundary substitutes for the recovered dependencies.

REA run `2026-10-14T02-10-53.412Z-interactive-2478528` is closed. Output assembly:
`ev_3b59c9879db2d503b99b9b3e0ec6f34523efac49e245ba5acd18a6874bb8f377`;
seek assembly: `ev_ece29d49a4ee18b1d3dfd8fc12eb9c9fe54d418bda79f3269fc8509bb63ec356`.
Five queries completed; the third pseudocode was a destruction-boundary survey,
not a source or exact claim. Retained startup evidence likewise adds no claim.

One VC4/native/i686 compilation set and whole comparisons ran. All334 preceding
exacts,108 candidates and249 semantic rows preserve their inputs and products.
Source453/candidates110; exact334/code69,697/metadata136 remain unchanged.
Private receipts: `.analysis/runtime-stream-operations-20261014/verification.json`.
No runtime/game tests or hardware execution; broader integration remains open.
