# DX-Ball reconstruction

Reconstructing DX-Ball v1.07 from its Windows executable into readable source
that can be rebuilt and played. This repository shows how
[REA](https://github.com/morluto/rea) supports that work.

## How it works

We start from a game operation—launching a ball, hitting a brick, changing
screens—and follow it through the original executable.

1. **Investigate with REA.** Follow pseudocode, instructions, callers and data
   references through its Ghidra provider to recover control flow and shared state.
2. **Write the source.** Recover structures and complete routines in C/C++,
   using REA's saved evidence to resolve missing details.
3. **Compile and compare.** Compare original-era compiler output with the
   executable; use the differences to guide the next REA investigation.
4. **Rebuild and play.** Connect the recovered routines, run the game, and
   repeat for the next missing behavior.

The same source serves the portable tools and Windows game builds.

See [REA in practice](docs/REA.md) for a worked example,
[the source map](src/README.md) to follow the game, and
[build and play](docs/BUILD.md) to run it.

DX-Ball was created by Michael P. Welch, with 3D graphics by Seumas McNally.
Original game files are supplied separately. See [LICENSE](LICENSE).
