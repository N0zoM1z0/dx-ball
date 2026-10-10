# DX-Ball reconstruction

Reconstructing English DX-Ball v1.07 from its Windows executable into readable
C/C++ and a playable rebuild, using [REA](https://github.com/morluto/rea).

## How it works

REA connects the agent to Ghidra to inspect the original executable. We work
through game behaviors, such as a brick collision leading to a score change
and a bonus:

1. Use REA to follow calls and shared data, reading pseudocode alongside
   instructions to understand the behavior.
2. Recover the structures and logic in C/C++, and connect them to the game.
3. Compile with the original toolchain and compare with the executable. Use
   differences to guide the next REA query and source revision, then play the
   rebuilt game to check the result.

[REA in practice](docs/REA.md) · [Source map](src/README.md) ·
[Build and play](docs/BUILD.md)

DX-Ball was created by Michael P. Welch, with 3D graphics by Seumas McNally.
Original game files are supplied separately. See [LICENSE](LICENSE).
