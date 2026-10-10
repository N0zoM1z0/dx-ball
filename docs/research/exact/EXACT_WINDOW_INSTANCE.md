# Window instance-lock lifetime

[`platform.c`](../../../src/platform.c) now recovers the complete semaphore
claim and close routines. Both match on their first stable VC4 compilation:

| Routine | Original range | Complete match |
| --- | --- | ---: |
| `dxball_claim_instance` | `0x40DF10..0x40DF7C` | 109 bytes |
| `dxball_close_instance` | `0x40DF80..0x40DFB2` | 51 bytes |

The original claim stores the opened handle in a local and tests it for zero.
An existing semaphore returns zero without closing that handle or changing
the global. Otherwise it creates the semaphore with security attributes
12/NULL/1, initial count zero and maximum count one, stores the result, and
rereads the global for return. Closing samples that global, ignores the
CloseHandle result, then clears it.

OpenSemaphoreA and CreateSemaphoreA use independent cells at `0x4412B0` and
`0x4412AC`. Platform now owns their typed pointers. Closing uses the shared
File CloseHandle cell at `0x441264`. Windows binds the two semaphore services
once and reuses its existing File binding. Their three old Window table fields
are removed, leaving 24 slots; GetVersionEx moves to slot 23. The native
Platform constructor binds the real cells. Sound's message-box fixture still
uses slot 9, with only its table-view extent changed.

Saved REA dossiers
`ev_62be40ba52c99f99d98901a5d736ae5250673c0cd2a257527bb0748dce67c357`
and `ev_1c8812cfc0cee3f5a725c911a8611a98678bac2db8eb4363445fadfda4b10263`
establish the calls and state flow. Two focused reads complete their evidence:

- `ev_7dbfc11820be1873717327d586d542dff0bd036a754698d9db2132f6280f3867`
  retains all 109 claim bytes, including the five-byte jump omitted from the
  provisional Ghidra body. Its `E907000000` targets the existing epilogue.
- `ev_0a43fa7b195da89748b440011a7a22c726bffb69573e8574010b4cff63bf3769`
  retains both eight-byte `DX-Ball` names at `0x422BBC` and `0x422BC4`.
  The reconstructed arrays keep those original storage addresses distinct.

All 125 supplemented bytes equal the verified PE. The session closes with
485 snapshot records. Complete relocation bindings cover the three actual
import cells, shared semaphore global and both full name strings.

One compile per 25 affected recipes compares 122 complete units and 1,242
relocations. All 120 affected accepted units remain exact; the two new matches
add 160 code bytes. Current totals are 283 source-present functions and
136 exact functions / 21,047 code bytes.

The existing Platform Oracle passes all 4,742 cases, including startup and
destruction callers. Its cases and target boundary logic are unchanged;
no other owner Oracle is rerun. Native, VC4 and MinGW builds pass. Full inputs,
prior/current products, REA responses and two bounded reviews are retained
in `.analysis/checkpoints/exact-window-instance-283-136/`.
