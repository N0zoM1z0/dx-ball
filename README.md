# DX-Ball reconstruction

<p align="center">
  <img src="resources/dxball-title.png" alt="DX-Ball title screen" width="900">
</p>

<p align="center">
  <img src="resources/progress.svg" alt="DX-Ball source reconstruction progress" width="900">
</p>

Recovering English DX-Ball v1.07 as readable C/C++ that can be rebuilt and played.

[REA](https://github.com/morluto/rea) lets the coding agent query Ghidra's
analysis of the original executable. Reconstruction follows a simple loop:

1. **Trace a game behavior with REA.** Follow calls and data references, then
   read pseudocode alongside instructions to understand the logic and objects.
2. **Recover the source.** Turn those findings into typed C/C++ and connect
   the recovered functions into the game.
3. **Rebuild and refine.** Compile with VC4, compare the affected functions,
   and check the restored behavior. Use differences to guide the next REA query.

[REA in practice](docs/REA.md) · [Source map](src/README.md) ·
[Build and play](docs/BUILD.md)

DX-Ball was created by Michael P. Welch, with 3D graphics by Seumas McNally.
Original game files are supplied separately. See [LICENSE](LICENSE).
