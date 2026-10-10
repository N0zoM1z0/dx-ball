# DX-Ball reconstruction

<p align="center">
  <img src="resources/dxball-title.png" alt="DX-Ball title screen" width="900">
</p>

This project reconstructs English DX-Ball v1.07 from its original executable
into readable C/C++ that can be rebuilt and played. It shows how
[REA](https://github.com/morluto/rea) helps a coding agent recover a real game:
follow its behavior, understand the original code, and rebuild the pieces
into a working whole.

## Reconstruction with REA

REA gives the agent access to Ghidra's analysis of the executable: pseudocode,
instructions, calls, and data references. We use those observations to recover
the game's logic and object layouts, working through complete flows such as
startup, a gameplay frame, or sprite loading.

1. **Trace a game behavior with REA.** Follow calls and data references, then
   read pseudocode alongside instructions to establish the logic, field layouts,
   and order of state changes.
2. **Recover the source.** Turn those findings into typed C/C++ and connect
   the recovered functions into the game.
3. **Rebuild and refine.** Compile with VC4, compare the affected functions
   against the original executable, and check the restored behavior. Differences
   guide the next focused REA query.

Saved REA responses connect the recovered source to its evidence. The
[worked example](docs/REA.md) follows a projectile-list routine from analysis
to source and a complete compiler match.

## Progress

<p align="center">
  <img src="resources/progress.svg" alt="DX-Ball source reconstruction progress" width="900">
</p>

The diagram tracks recovered functions and exact compiler matches. See the
[progress records](docs/PROGRESS.md) for current counts and the
[research notes](docs/research/README.md) for the recovered game flows.

## Build and explore

- [Build and play](docs/BUILD.md) — supply the original files, compile, and launch.
- [Source map](src/README.md) — find the modules behind each part of the game.
- [Architecture](docs/ARCHITECTURE.md) — follow startup, mode dispatch, and a frame.

DX-Ball was created by Michael P. Welch, with 3D graphics by Seumas McNally.
Original game files are supplied separately. See [LICENSE](LICENSE).
