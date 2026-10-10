# DX-Ball reconstruction

Using [REA](https://github.com/morluto/rea), we are reconstructing DX-Ball v1.07
from its Windows executable into readable C/C++ and a playable rebuild.

## How it works

REA gives the agent access to Ghidra's pseudocode, instructions, calls and data
references. We use it in a repeating workflow:

1. **Trace a game behavior through REA.** Follow calls and shared data—for
   example, from a brick collision through scoring, bonus creation and drawing.
2. **Recover the source.** Infer structures and control flow from that evidence,
   then implement and connect them in C/C++.
3. **Compare, refine and play.** Compile with the original-era toolchain.
   Differences from the executable guide the next REA query. Check the restored
   behavior, then continue with the next game flow.

[REA in practice](docs/REA.md) · [Source map](src/README.md) ·
[Build and play](docs/BUILD.md)

DX-Ball was created by Michael P. Welch, with 3D graphics by Seumas McNally.
Original game files are supplied separately. See [LICENSE](LICENSE).
