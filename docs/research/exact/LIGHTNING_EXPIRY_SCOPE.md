# Last-brick expiry-local scope

The last-brick controller now declares its tile, center, scan, rectangle and
destination locals inside the existing expired-deadline branch. Every producer
and consumer of those values belongs there. Remaining time and the explicit
time-before-RNG sample retain their scopes. Names, types, initializations,
operations, call order and headers are unchanged.

One matching VC4 compilation compares all twenty complete display functions,
including every actual relocation and referenced literal. Last-brick improves
from **1067/1057 bytes with 992 differences** to **1067/1057 with 990**. It remains
nonexact. All twelve exact companions retain 3,303 bytes, and the other nineteen
function code identities remain unchanged.

## Complete instruction and storage evidence

Both current versions contain 302 instructions and reserve 68 frame bytes.
Exactly sixty one-byte EBP displacements change. A bijection of all seventeen
actual DWORD homes explains every changed byte, including the four fields of
the existing rectangle. Every other instruction byte is identical. There is no
new stack-slot reuse or smaller frame.

Six original homes are restored; offsets are signed EBP displacements:

| Value | Previous | Current / original |
| --- | ---: | ---: |
| Remaining time | -44 | -4 |
| Selected tile Y | -4 | -12 |
| Rectangle left | -20 | -28 |
| Rectangle top | -16 | -24 |
| Rectangle right | -12 | -20 |
| Rectangle bottom | -8 | -16 |

The other homes still differ. Raw differences count byte positions, including
suffix shifts from existing producer differences; they do not measure missing
operations or matching value roles. Original time preservation in EBX and the
two crop producers remain unresolved. This scope does not establish original
source spelling. The [complete crop-chain review](EXACT_LIGHTNING_CROP_CHAIN.md)
and its rejected direct-subtraction/clock controls remain closed.

The prior complete instruction correspondence has the same before-code identity
and supplies the original frame-role map. It reuses REA Evidence
`ev_f8610be2baa2323aec8fcd14317794aebe74eefa78b4d66c9cf874ca117eb5bc`,
operation 00 of `2026-10-07T09-29-28.570Z-interactive-2776129`.
There is no new provider query.

## Focused validation and integration

The existing 35 deadline/time pairs and 162 expiry/crop scenarios pass against
the original: 197 calls covering wrap, inclusive expiry, volume rounding,
grid positions, reduced particles and sprite dimensions. Existing harnesses,
full state/buffer comparisons and ordered effects are retained. The unchanged
overlay entry is not replayed. No new semantic cases are added; 235 historical
input inventories receive the source hash without rerunning their other cases.

The native incremental build compiles only display and links its library.
The VC4 delivery builder reuses all 116 source objects and only relinks, retaining
the same nineteen approved original CRT members. All 1,091 mapped addresses
remain unchanged. A complete image comparison finds only the sixty proved
last-brick displacement bytes and twelve bytes in six parsed COFF/resource
timestamp fields. All resource payloads and other image bytes agree. The full
linked 1,067-byte body verifies with its 51 actual bindings. No game runs again.

Current image SHA-256:
`345a68875bad0693476c55fcd69f41c5a9b158fc96e1f3e4f3189358001d3f14`.
Earlier GUI observations keep their recorded image hashes.

Private `.analysis/lightning-expiry-scope-20261017/` retains frozen inputs,
before/after objects, complete comparisons, source reversal, frame proof,
selected existing cases, ledger reversal and whole-image verification.
Verified archive/compression releases 1,425,408 allocated bytes of duplicate
carriers; current products and unique evidence remain available.
Totals remain **475 source / 380 exact / 95 complete candidates**, including
34 authored candidates. No full replay or port work runs; heavy operations stay
serial under CPU 35%, memory high 640 MiB / maximum 768 MiB.

## Closed scan-only scope

One later private model limits column, row and tile to a block containing only
the board scan. Selected tile/center results retain their expiry-branch scope.
All operations, types, names and order stay unchanged. One compilation compares
all twenty functions: twelve exacts retain 3,303 bytes and the other nineteen
code identities remain unchanged, but last-brick worsens990→991 differences.
Reject this block and retain the maintained990 result. Source, cached objects,
image and ledgers remain unchanged; no native check, relink or game follows.
Frozen inputs, objects and complete comparisons are retained under
`.analysis/lightning-scan-scope-20261017/`. Do not repeat this scope model.
