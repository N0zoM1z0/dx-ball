# Exact MIDI stop and completion callback

The shared C++ MIDI owner now reproduces the complete stop and completion
callback bodies: 352 bytes and four actual relocations. The original calls,
state writes, duplicate header-user reads and five-argument stdcall ABI remain
unchanged. Only meaningful declaration scopes move; names, types and executable
tokens are preserved. The current total is 201 exact functions, 41,512 code
bytes and 136 metadata bytes. This is a source checkpoint, not full game fidelity.

| Unit | Original entry | Complete bytes | Relocations | Frame and local homes |
| --- | --- | ---: | ---: | --- |
| Stop MDS | `0x401A20` | 225 | 3 | 12 bytes: remaining -4, current -8, header -12 |
| MIDI callback | `0x401B10` | 127 | 1 | 8 bytes: context -4, current header -8; `RET 0x14` |

## Source and original evidence

Stop keeps the traversal count in the function scope. Current-context and
header pointers belong to the validated operation after the cookie guard.
Reset failure still clears the stopping bit and returns 5. Success traverses
every header using its current length, ignores unprepare/close errors, then
clears the stream and state.

The callback keeps its extracted context in the function scope and the current
header in the callback-processing scope. The header assignment still precedes
the message guard. Both consecutive reads of the header's user field remain.
A successful looping requeue returns immediately. The header scope ends before
the fallback pending-buffer decrement and final function return.

Two saved, target-bound REA dossiers supply every original instruction:

- Stop: `ev_c16f07a25664c6b672390f14698cb3e71c3df902266c28f23d2e1b122f50b1ab`,
  `04-analyze_function.json` in private run
  `2026-10-07T15-16-14.218Z-interactive-3602154`.
- Callback: `ev_b6d7ad536b3a34effbc5d45b98de2b6431f5e966064bdca80b546b357a3fe9ba`,
  `05-analyze_function.json` in that run.

Both bodies are contiguous and include their complete returns. Original
instruction addresses match every emitted instruction boundary. The existing
typed import bindings cover reset, unprepare, close and stream-out; comparison
resolves all four actual COFF relocations without masking any byte. The callback
prototype inferred by Ghidra omits the fifth argument; its `RET 0x14` and the
maintained `_dxball_midi_callback@20` symbol retain the real ABI.

## Compiler and negative controls

Two canonical `/Od /Ob0 /Oi- /Oy- /Gd /MT /Gy` owner compiles were needed.
The first already matched stop. It also placed callback locals correctly, but
keeping the final return inside the header block emitted an extra five-byte
C++ continuation: 132/127 bytes, 15 differences. That complete source/object/
receipt remains in `callback-block-return-stage`; do not repeat that model.
Ending the header lifetime before the context-only fallback restores all 127
bytes in the second compile. No names, padding or declaration permutations
were tried. The preserved before object fails with 14 stop and 10 callback
differences; release and pause remain exact across 282 bytes.

Play remains 516/513 bytes with 169 differences, parse 868/868 with 40,
event expansion 343/343 with 41, and open 530/522 with 443. These are candidates;
the complete comparison retains their differences. Original identifier spelling
and the reason for the duplicate user read remain unknown.

## Validation and retained products

Four unchanged loops from the maintained MIDI Oracle pass 828 direct cases:
96 stop, 192 callback, 96 release, 72 pause and 372 play. They check cookie,
stream/state/flag boundaries, ordered failure cleanup, message filtering,
requeue success/failure and pending counts. A separate 54 connected checks
exercise loading, first/last buffer callbacks, pause/resume/restart, replacement
and final release for all six original songs. Complete context/header/buffer/
heap state and ordered import effects are compared with the original executable.
Physical asynchronous WinMM delivery and audible output remain outside that scope.

Native and MinGW products rebuild. VC4 links the final matching MIDI object
with 35 hash-verified unchanged objects; no further legacy source compile is
needed. All 201 current exact input closures and 247 unchanged historical
semantic scopes verify. Unrelated historical tests are not rerun.

Working proof, both compiles, original-dossier identities, focused Oracle,
negative controls and product hashes are retained under
`.analysis/midi-operation-scopes/`. The independent checkpoint is
`.analysis/checkpoints/midi-operation-scopes-283-201/sha256.json`, with explicit
dependencies on the preserved before/stage objects and original REA carriers.
