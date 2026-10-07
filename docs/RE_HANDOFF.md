# Current handoff

The original target is DX-Ball v1.07, English, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
The provided archive is private under the parent `game_exe/`; verified files
live under ignored `original/`. Ghidra 12.1.3 imported 528 provisional functions.
Its private project is `ghidra-project/DXBALL`.

The first maintained family is board-bank I/O, editor load/store, per-board
initialization, tile-to-sprite mapping, active-surface selection, and board
drawing. Original x86 execution is the behavioral oracle. File I/O and rendering
dependencies are intercepted; memcpy/memset execute the target's actual CRT.
Drawing validation checks ordered call arguments, not pixels or DirectDraw.

Portable builds are analysis libraries and a board-inspection utility. There is
no reconstructed playable game yet. Windows integration, sprite/PCX decoding,
ball physics, bonuses, UI, audio, and MIDI remain pending.

VC4.0 is the first compiler candidate. Configure its exact-unit replay and
record only cold-build successes in `config/matches.csv`. Continue with the
current board owner's producers/consumers, then sprite-bank ownership at
`0x00404610`, sprite draw `0x00404180`, and board-hit logic `0x00411F40`.
