# MIDI imports and C++ music ownership

The MIDI owner now calls 22 independently typed Kernel32/WinMM service cells.
The Windows adapter binds each cell to its existing SDK wrapper. Music object
ownership lives in [`music.cpp`](../../../src/music.cpp), using ordinary
`new DxBallMusic` and `delete dxball_music`.

Four complete functions become exact, adding 636 code bytes. The total is
135 exact functions / 21,248 code bytes.

| Function | Original address | Complete bytes | Result |
| --- | --- | ---: | --- |
| Release MDS | `0x4016E0` | 149 | New exact |
| Pause MDS | `0x401990` | 133 | New exact |
| Load music | `0x401B90` | 249 | New exact |
| Close music | `0x401DA0` | 105 | New exact |
| Resume / pause / restart music | `0x401C90` / `0x401CE0` / `0x401D30` | 77 / 75 / 106 | Remain exact in C++ |

## Independent import ownership

The original instructions call distinct import cells. For example, release
uses GlobalHandle at `0x441288`, GlobalUnlock at `0x44128C`, GlobalFree at
`0x441284`, and LocalFree at `0x44126C`. Their spacing does not correspond to
the former portable MIDI API aggregate.

Each recovered service now has its own pointer definition and unchanged
stdcall signature in [`midi.h`](../../../src/midi.h) and
[`midi.c`](../../../src/midi.c). A relocation binds that pointer to one original
import cell, with zero addend. The 22 names and targets are consistent across
all callers. SDK wrappers and their argument conversions remain unchanged.

The existing Oracle supplies the same callbacks through these individual
cells. Its scenarios, backend and original execution paths are unchanged.

## Recovering deletion from compiler output

The original load and close routines contain two temporary pointer stores at
each deletion site. Calling the recovered delete function directly from C
omitted those stores, producing 222/90 bytes against the original 249/105.
Ordinary C++ deletion generates them naturally and matches both whole bodies.

`DxBallMusic` owns class-specific allocation and deletion members. They retain
the existing size-checked allocation and runtime-delete defaults. The members
have static cdecl interfaces with one argument and no hidden object pointer;
comparison binds them to the original allocation/deletion entries at
`0x416770` and `0x416760`. Their adapter bodies are dependency glue. The original
class and member names remain an inference; matching establishes the complete
caller bytes under those explicit allocator bindings.

The five music controls keep C linkage. C and C++ consumers share the same
data fields, while the C++ owner expresses object lifetime. No global allocation
operator is replaced.

## Complete comparison and remaining work

The saved REA dossiers and complete play span are indexed in
[the lifecycle recovery](EXACT_MIDI_LIFECYCLE.md). This batch reuses them and
makes no new provider queries. Full instruction and import-binding receipts
are retained in `.analysis/exact-midi-imports/`.

The shared header affects 20 compiler recipes. Each was compiled once, followed
by 102 complete unit comparisons with 1,061 actual relocations. All 95 previously
accepted affected units remain exact. The music recipe consumes its eight
recursive project inputs with the established flags.

Stop and callback remain candidates with 14/10 differing local-storage bytes.
Their complete relocated instructions otherwise agree. Play remains 471/513
bytes, with unresolved original cleanup syntax and storage choices. These
differences are retained without masking offsets or trying variable spellings.

One existing MIDI Oracle passes 2,109 direct cases and 134 connected checks,
including all six songs. Native, VC4 and MinGW builds succeed. The VC4 game
reuses 24 current objects and compiles eight remaining inputs.

The full source/compiler inputs, prior objects, comparison, Oracle, independent
reviews and game products are sealed in
`.analysis/checkpoints/exact-midi-imports-283-135/`.
