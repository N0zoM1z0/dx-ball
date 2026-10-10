# DX-Ball reconstruction

Reconstructing DX-Ball v1.07 from its Windows executable into readable source
that can be rebuilt and played, using [REA](https://github.com/morluto/rea).

## How it works

We start with a game behavior, such as a ball hitting a brick. Through REA,
the agent asks Ghidra for the original functions, instructions, callers and
data, then follows how that behavior works across the game.

1. Trace the behavior with REA to recover control flow and shared structures.
2. Write the corresponding C/C++ and connect it to the rest of the game.
3. Compile with the original-era toolchain; use differences from the executable
   to guide the next REA query and refine the source.
4. Rebuild, play, and repeat until the whole game is restored.

[REA in practice](docs/REA.md) · [Source map](src/README.md) ·
[Build and play](docs/BUILD.md)

DX-Ball was created by Michael P. Welch, with 3D graphics by Seumas McNally.
Original game files are supplied separately. See [LICENSE](LICENSE).
