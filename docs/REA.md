# Reconstructing DX-Ball with REA

The agent uses [REA](https://github.com/morluto/rea) to ask questions about the
original executable. REA queries Ghidra and returns pseudocode, instructions,
calls and data references with recorded evidence. Those results guide the
C/C++ implementation in [`src/`](../src).

## Follow a behavior across functions

Start with a game action: what creates a projectile, advances it, draws it,
and removes it? REA's function analysis provides the first view. Following
callers, callees and shared data reveals the surrounding flow and the objects
passed between its parts.

Read pseudocode alongside instructions to recover integer widths, calling
conventions, field offsets and the order of state changes. Compare how related
functions create and consume the same object to give its fields meaningful
types and names. Write that model into the owning source module and connect
its calls to the rest of the game.

Saved REA responses let later work reuse the analysis. Research notes link the
findings to original addresses and reconstructed functions, so readers can
follow how an implementation was recovered.

## A worked example: appending a projectile

At `0x413410`, the original routine appends a projectile to a linked list.
REA's saved instructions show the list arriving in ECX, a 24-byte allocation,
and writes to the previous, next, first, last and current pointers. Related
list routines establish what those links mean.

The recovered `dxball_append_projectile` in [`src/core.c`](../src/core.c) uses
a typed list and `DxBallProjectileNode`. Its fastcall interface and node layout
follow those observations. Compiling with VC4 produces a complete 146-byte
match after resolving the allocation and exit calls.

The [projectile-list investigation](research/exact/EXACT_PROJECTILE_LISTS.md)
records the original evidence, source decisions and comparison.

## Use compilation to ask the next question

Compile the recovered source with the original-era toolchain and compare the
affected functions with the executable. A difference in a call, branch or
memory access gives the next REA query a concrete target. Revisit that evidence,
refine the implementation, and rebuild the game. A small play check or an
existing Oracle helps check the behavior being restored.

This repository uses REA 4.1.0 with Ghidra 12.1.4 through `scripts/rea`.
See [REA commands](agent/REA.md) for setup and queries,
[matching](MATCHING.md) for compiler comparisons, and
[build and play](BUILD.md) for running the reconstruction.
