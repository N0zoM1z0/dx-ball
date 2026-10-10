# MIDI streams and music controls

Ten complete routines in [`src/midi.c`](../../../src/midi.c) now follow the
original stream and music-object lifetime. Music resume, pause and restart
compile exactly with VC4: three functions, 258 code bytes. The total is
131 exact functions / 20,612 code bytes.

| Routine | Original address | Original bytes | Emitted bytes | Result |
| --- | --- | ---: | ---: | --- |
| Release MDS | `0x4016E0` | 149 | 149 | Import storage unresolved |
| Play MDS | `0x401780` | 513 | 471 | Cleanup branches and import storage unresolved |
| Pause MDS | `0x401990` | 133 | 133 | Import storage unresolved |
| Stop MDS | `0x401A20` | 225 | 225 | Import storage unresolved |
| MIDI callback | `0x401B10` | 127 | 127 | Import storage unresolved |
| Load music | `0x401B90` | 249 | 222 | Candidate |
| Resume music | `0x401C90` | 77 | 77 | Exact |
| Pause music | `0x401CE0` | 75 | 75 | Exact |
| Restart music | `0x401D30` | 106 | 106 | Exact |
| Close music | `0x401DA0` | 105 | 90 | Candidate |

## Recovered behavior

Release captures the context, attempts to stop an active stream, then unlocks
and frees the buffer bank. Each operation obtains its handle from the current
buffer pointer. It writes the freed cookie before releasing the context,
including when stopping fails.

Play validates the context and existing-stream state before opening a stream.
It sets the time division, prepares and queues each buffer, and increments
the pending count only after both calls succeed. Header traversal uses the
header's current length. A failure cleans up a newly created stream; resuming
an existing paused stream preserves that stream on failure.

Stop sets the stopping bit before resetting the device. Reset failure clears
that bit and returns; success unprepares every buffer, closes the current
stream, and clears the stream and state. Pause sets the paused bit only after
the device call succeeds.

The callback has five stdcall arguments, confirmed by `RET 0x14`. A successful
looping requeue returns immediately. Other completion paths decrement the
pending count. Two consecutive reads of the header's user field are retained
from the instructions; the reason for that repetition is unknown.

Music controls use the live global at `0x421060`. Loading replaces an existing
song and allocates the wrapper through the recovered runtime-new entry.
Failed loading or playback releases the relevant objects. Resume, pause and
restart return on failure before changing the playing flag.

## Evidence and comparison

The ten full REA dossiers are `01`–`10-analyze_function.json` in the private
run `.analysis/rea/runs/2026-10-07T15-16-14.218Z-interactive-3602154/`.
Their Evidence IDs and extents are indexed in `.analysis/midi-evidence.json`.

Play has 493 Ghidra-owned bytes inside its 513-byte span. A new complete
`read_bytes` response attests all 513 bytes, including four excluded five-byte
jumps to cleanup. It is retained at
`.analysis/rea/runs/2026-10-10T07-13-33.419Z-requests-4072877/00-read_bytes.json`,
Evidence `ev_63cb8dd0c62cd2c2e8e121e730540f10d836f953facd739adb6d4c6573b1ba9a`.
The response agrees with the verified executable. The cumulative snapshot
contains 481 records and preserves all 480 parent records.

One MIDI recipe consumes eight recursively included project files. Its flags
are the established `/Od /Ob0 /Oi- /Oy- /Gd /MT /Gy` configuration. Two compiler
emissions were retained: the first exposed the callback's missing success
return; the second includes that source correction. Five music units were
compared through their complete exits with all 40 actual relocations resolved
to original calls and the music global.

The portable MIDI API table differs from the original Kernel32 and WinMM
import storage. Recovering that dependency ownership is the next step for
the stream bodies. Play's four error trampolines also leave its original
control syntax unresolved. Load and close contain original deletion
temporaries whose C++ lowering remains to be recovered.

## Validation and retained products

One unchanged MIDI Oracle passes 2,109 direct cases and 134 connected checks,
including all six original songs. No cases were added. Native, VC4 and MinGW
builds succeed. The VC4 game reuses the fresh MIDI object and 30 unchanged
objects; no other source was recompiled for that link.

Full compiler inputs, both emissions, comparisons, Oracle results, independent
reviews and game products are retained under
`.analysis/checkpoints/exact-midi-lifecycle-283-131/`.
Working receipts are in `.analysis/exact-midi-lifecycle/`.
