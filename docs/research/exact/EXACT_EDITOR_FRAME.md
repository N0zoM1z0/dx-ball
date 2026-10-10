# Exact editor mouse frame

The editor frame at `0x40C3B0` now follows the original cursor, paint, erase
and toolbar phases in [editor.c](../../../src/editor.c). VC4 reproduces the
complete 908-byte function on the first stable compilation.

The frame waits when drawing to primary, restores regions, copies the mouse
coordinates and applies the original cursor clamps. It selects bank 2, calls
the hit-region lookup, then draws sprite 6 or 4 in two separate branches.
Each branch reads the current cursor coordinates after lookup. Bank 0 is
restored before the live presentation check.

Both board-edit paths keep their full coordinate sequence: copy X and Y,
subtract the board origins, divide by 30 and 15, clamp, write the tile byte,
draw the tile and store the current board. Left clicks write the selected
DWORD's low byte; right clicks write zero. Outside the board, left clicks
retain two distinct hit-region lookups, draw status and invalidate the actual
`(0,0,639,49)` rectangle by value. The right-action test remains independent,
and each handled action reads Control before deciding whether to clear it.

The previous helpers preserved most logical effects, but factored away these
original call and value phases. They had no other consumers and are removed.
The shared API, fixture and case bodies are unchanged.

REA dossier
`ev_12f27f7831f215d80c2a1a27d88e1638ffa9ab2fd568793f66258b328927431e`
covers all 209 instructions, 16 direct calls and the terminal return at
`0x40C73B`. The complete span is contiguous, with no missing bytes or internal
tables. The main frame dispatcher reaches this entry at `0x40378A`, recorded
in `ev_fe891f4e2c0b787941b66990f074b6e3ad5575dc3b2080a68641c8f9629b6363`.
Saved evidence was sufficient; this batch opened no provider session.

The whole comparison applies all 62 actual relocations. Five existing exact
functions in the same source remain exact: clear-hit-region, hit-region-contains,
reset-hit-region-count, set-hit-region and the separately classified no-op at
`0x40CC20`. Six complete comparisons cover 78 relocations. Totals rise to
139 exact functions and 22,446 code bytes; metadata remains 136 bytes.

Only the three existing editor-frame loops ran: 1,272 paint/erase, input-gate
and toolbar-edge cases. The native, VC4 and MinGW builds pass; the VC4 game
reuses all 35 valid objects. Full source/compiler inputs, objects and receipts
are retained in `.analysis/checkpoints/exact-editor-frame-283-139/`.
