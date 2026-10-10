# DX-Ball reconstruction

Reconstructing DX-Ball v1.07 from its Windows executable into readable,
rebuildable source, using [REA](https://github.com/morluto/rea).

## How it works

We work through the game one behavior at a time: launching a ball, hitting a
brick, drawing a frame. REA connects the agent to Ghidra so it can trace those
behaviors through the original program and recover the code behind them.

1. Use REA to inspect decompiled code, instructions, callers and shared data.
2. Turn that evidence into C/C++ routines, structures and connected game logic.
3. Compile with the original-era toolchain and compare against the executable.
   Follow differences back through REA to refine the reconstruction.
4. Rebuild and play the game, then continue with the next behavior.

[REA in practice](docs/REA.md) · [Source map](src/README.md) ·
[Build and play](docs/BUILD.md)

DX-Ball was created by Michael P. Welch, with 3D graphics by Seumas McNally.
Original game files are supplied separately. See [LICENSE](LICENSE).
