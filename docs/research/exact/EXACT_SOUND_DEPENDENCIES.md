# Sound initialization and WAV loading

The shared implementation in [`sound.c`](../../../src/sound.c) now follows
the complete initialization, WAV parsing and binary-file loading bodies.

| Function | Original bytes | Emitted bytes | Comparison |
| --- | ---: | ---: | --- |
| Initialize sound, `0x405120` | 1,705 | 1,741 | Candidate; local storage differs |
| Parse WAV, `0x406290` | 269 | 269 | Candidate; 30 local-displacement bytes differ |
| Load binary file, `0x403320` | 304 | 307 | Shared imports recovered; local storage differs |

## Source recovery

Initialization uses the original retry state, signed HRESULT switches and
dialog responses. Each failure branch releases the same resources in the same
order; primary creation checks a partial output, while primary playback releases
the established buffer directly. Exit codes 10–13 precede cleanup. The final
loop copies each retained filename before reloading its slot.

A typed stdcall adapter connects the original DirectSound factory call to the
existing native/Windows backend. It represents the import boundary; the
initializer comparison covers the game body at `0x405120`.

WAV parsing now reads the three header words in order, advances a byte cursor,
and dispatches fmt/data chunks through a switch. A data chunk returns immediately;
loading requires a usable preceding fmt chunk. Chunk lengths advance with the
original unsigned rounding expression. The DWORD reads follow the original x86
accesses, including unaligned chunks.

File loading calls the recovered malloc/free bodies directly. It retains the
fallback path, successful short-read behavior, and original handle ownership
on allocation/read failure. The subsequent [file-service recovery](EXACT_FILE_SERVICES.md) moves this
body to `file.c` and binds its four independently owned IAT cells.

## Complete boundaries and compiler feedback

REA's saved initializer dossier owns 1,635 bytes in fourteen ranges; the parser
owns 264 bytes in two ranges. Focused `read_bytes` queries verified the complete
1,705/269-byte spans. The excluded 70/5 bytes are internal jumps and participate
in comparison.

The first emission exposed duplicate switch endings. VC4 adds an ending branch
for the last case; explicit nonfinal case breaks remain necessary. Correcting
that source spelling gives the same complete instruction flow as the original:
377 initialization instructions and 80 parser instructions. Initialization
retains 41 differing local operands; twelve longer response accesses account
for its extra 36 bytes. These observations leave both bodies as candidates.

The final grouped comparison covers 17 functions, 235 actual relocations and
12 complete literals. All eight accepted sound functions remain exact. One
existing sound Oracle passes 5,782 direct cases and 48 connected checks. VC4 and
MinGW games link; GNU keeps the recovered loader's fmt-before-data diagnostic
visible through the source-specific option in `CMakeLists.txt`.

## Evidence

Original dossiers: initialization
`ev_0c19fd7b02df4709514364206dec7df270a537b02ffbdda25a57516fcd78ce1f`,
parser `ev_8c97f00d8301c9fad99e761f8bbe2ea90f8dc14d6e8db6709a75e15c49c6c1a3`,
file loader `ev_a52bb0030eab7563b8a83f854ffdd76af7e5b0382cd75bda896a04c3efed70a0`.

Complete byte spans:
`ev_ea17c0f8232c3bed494b5f8e97ff67790e1d38eb410d071395c0337072d22447`
and `ev_94e9828bd14fb37d829065569ecc12507b58c3fd897901734ec17b6a076da576`.
Full responses are retained in the REA runs from October 7 and October 10;
comparison inputs, both emission epochs and reviews are retained under
`.analysis/exact-sound-dependencies/` and its checkpoint.
