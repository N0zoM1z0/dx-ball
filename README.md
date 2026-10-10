# DX-Ball reconstruction

Using [REA](https://github.com/morluto/rea) to recover readable C/C++ for
English DX-Ball v1.07 and rebuild the game.

REA connects the coding agent to Ghidra. The agent traces game behaviors
through the original executable, using pseudocode, instructions and data
references to recover structures and logic.

We compile with VC4 and compare the affected functions with the original.
Differences guide the next REA query and source revision, then we integrate
the recovered code and play the rebuilt game.

[REA in practice](docs/REA.md) · [Source map](src/README.md) ·
[Build and play](docs/BUILD.md)

DX-Ball was created by Michael P. Welch, with 3D graphics by Seumas McNally.
Original game files are supplied separately. See [LICENSE](LICENSE).
