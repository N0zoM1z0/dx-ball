# Line drawing workspace and axis steps

The complete line at `0x403070` now emits **445 bytes**, matching the original
extent. Its strict comparison improves from 379 differences to **nine**.
All 121 instruction boundaries and widths agree, and every other byte matches.

The shared iterator precedes the error and coordinate extents. The surface
descriptor spans GetSurfaceDesc, Lock retries and Unlock. The pixel cursor and
two axis steps belong to the locked traversal and end before Unlock. The steps
form a two-element pair: X advances one byte, Y advances one signed pitch.

These declarations restore every observed home in the 140-byte frame:

| Value | Original and current EBP |
| --- | ---: |
| Iterator / error / X extent / Y extent | -4 / -8 / -12 / -16 |
| Lock result / descriptor base | -20 / -128 |
| Pixel cursor / X step / Y step | -132 / -140 / -136 |

The nine remaining bytes are three signed comparison groups: major-axis choice
and the two loop bounds. Current instructions exchange operands and reverse the
corresponding branch condition. Branch destinations remain identical. The line
stays a candidate. A negated-guard source model produced the same nine differences
and was rejected without repeating the successful compilation.

The complete original dossier is
`ev_25f8571b40b1ee8c589f398fa1211552c03d241352d0737d904789e2664b8af2`,
from the closed October 7 11:58 run. Its entire assembly is reused; no new
provider query is needed. The complete function has no COFF relocations.

Five exact UI companions retain 559 bytes. Linux and MinGW builds and the VC4
relink pass. One unchanged 486-case line loop compares all octants, both endpoint
directions, equality, zero length, retries, complete padded pixels and COM calls.
No text/palette suite or game campaign runs. Private evidence and products are
retained in `.analysis/line-locked-cursor-20261012/`.
