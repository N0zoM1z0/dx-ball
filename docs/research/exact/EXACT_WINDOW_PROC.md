# Window messages, focus and shutdown

The window procedure at `0x40DA70` connects input, audio focus and resource
shutdown. [platform.c](../../../src/platform.c) now follows its complete
original flow, including the order of state writes and calls into other owners.

Activation stores the full `wParam`, then clears Control before Shift. Key
dispatch precedes modifier updates. Mouse capture precedes action changes;
left and right button releases retain separate branches. Mouse movement reads
the system cursor, copies both coordinates and reaches the shared default
window procedure. Focus gain initializes sound when DirectDraw exists, then
resumes music. Focus loss conditionally pauses sound, pauses music and requests
surface restoration.

Shutdown disposes the working surface, releases audio and closes music. With
DirectDraw present it releases sprite banks, board, primary and palette in
that order. Secondary is cleared only within the primary-present branch.
COM calls read the live canonical pointers. The DirectDraw pointer is cleared
without a Release call. The semaphore closes before PostQuitMessage.
Seven calls now use the actual typed audio, music and sprite-bank owners.

REA dossier
`ev_ec5246e677575ed67dc6c47dec0ffc7106e9ff2c86eaf9c4c562e39071b603cf`
contains 227 instructions covering 1,136 bytes in five ranges. Focused read
`ev_454b9b00147a98b6a0f82cf928c9a3af94a4d1f90f0311809c080c7e4d2664bc`
supplies the complete 1,171-byte span. The three five-byte gaps at `0x40DAB7`,
`0x40DD65` and `0x40DDEE` are jumps to `0x40DEF5`, each following an
unconditional transfer. They appear to be compiler switch-end remnants;
their original source spelling remains unknown. The internal 20-byte table
at `0x40DECF` routes messages `0x201..0x205` to `0x40DD09`, `0x40DD3B`,
`0x40DDD3`, `0x40DD22` and `0x40DD50`.

VC4 emits 1,166 bytes. Comparing the complete span, including the switch data,
with all 74 actual relocations gives 1,006 differing positions. WindowProc
remains a candidate. Its 24 calls comprise eleven direct calls, nine named
Windows imports and four COM calls. The compiler's table pointer and five
entries map explicitly to their original objects and message destinations.
The four accepted functions sharing this source remain exact: sprite-bank
initialization, instance claim/close and WinMain. This batch compares five
complete units and 112 relocations; totals stay at 136 exact functions and
21,293 code bytes.

Strict native compilation required the recognized `/* fall through */`
annotation. Two earlier comment forms failed that warning check, producing
three VC4 invocations in total. Executable statements and complete function
emissions are identical across all three retained versions.

Only the existing 2,138 WindowProc cases were replayed. Five typed native
forwarders and their default-owner bindings connect the existing callback
slots; the case bodies are unchanged. Native, VC4 and MinGW builds pass.
The VC4 game reuses 35 valid objects, including the current platform object.
Full evidence and compiler inputs are retained under
`.analysis/checkpoints/exact-window-proc-283-136/`.
