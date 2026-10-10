# DX-Ball reconstruction

This project uses [REA](https://github.com/morluto/rea) to reconstruct DX-Ball
v1.07 from its Windows executable into readable C/C++ and a playable rebuild.

## How it works

Through REA, the agent queries Ghidra for functions, pseudocode, instructions,
calls and data references. It uses this evidence to recover how the game works.

1. **Trace a game action.** Follow it through REA, from input to state changes
   and drawing—for example, a ball hitting a brick and spawning a bonus.
2. **Recover the source.** Use the instructions and related functions to recover
   data structures and call order, then connect the implementation to the game.
3. **Refine with compiler feedback.** Compile with the original-era toolchain
   and compare against the executable. Differences guide the next REA query.
4. **Rebuild and play.** Check the restored behavior, then continue with the
   next part of the game.

[REA in practice](docs/REA.md) · [Source map](src/README.md) ·
[Build and play](docs/BUILD.md)

DX-Ball was created by Michael P. Welch, with 3D graphics by Seumas McNally.
Original game files are supplied separately. See [LICENSE](LICENSE).
