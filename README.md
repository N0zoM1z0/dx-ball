# DX-Ball reconstruction

Using [REA](https://github.com/morluto/rea) to reconstruct English DX-Ball v1.07
from its Windows executable into readable C/C++ that rebuilds and plays.

## Reconstruction workflow

REA lets the coding agent query Ghidra for functions, calls, instructions and
shared data. We recover one game behavior at a time, such as a brick hit and
its scoring, drawing and sound.

1. Use REA to trace the behavior, reading pseudocode alongside instructions.
2. Recover structures and logic in C/C++ from those observations.
3. Compile with VC4 and compare affected functions with the original.
   Use differences to guide the next REA query and revision.
4. Integrate the recovered code and play the rebuilt game.

[REA in practice](docs/REA.md) · [Source map](src/README.md) ·
[Build and play](docs/BUILD.md)

DX-Ball was created by Michael P. Welch, with 3D graphics by Seumas McNally.
Original game files are supplied separately. See [LICENSE](LICENSE).
