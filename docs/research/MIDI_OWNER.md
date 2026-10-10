# MDS music owner

## Current allocation defaults

The [MDS loader and converter recovery](exact/EXACT_MDS_PARSER.md) restores
the 12-byte format record, eight-byte block record and full input MIDIHDR.
Open, parse and event expansion preserve the original cursor and cleanup
order. The converter is now 343/343 bytes with 38 local-storage differences;
all three remain candidates. The existing MIDI Oracle passes 2,109 direct
cases / 134 connected checks, and all 99 affected accepted units remain exact.

Music wrapper allocation/deletion uses C++ object lifetime with maintained
runtime defaults. Local/Global ownership remains separate. The latest
[import and ownership recovery](exact/EXACT_MIDI_IMPORTS.md) adds exact release,
stream pause, music loading and closing. All five music controls are exact.
One existing Oracle
passes 2,109 direct cases and 134 connected checks. Native, MinGW and VC4 builds
succeed. Earlier investigations below retain their original evidence epochs.

`src/midi.c` maintains the original RIFF/MIDS reader, compact event expansion,
stream controller and completion callback. `src/music.cpp` owns five music
controls. Portable, MinGW i686 and VC4 builds share these implementations.
The Windows adapter supplies the 22 independently typed Kernel32/WinMM cells.
Stop and callback still differ in local storage; play retains a control-flow
gap in its compiler emission.

## REA evidence

The two loader/parser dossiers were reused from the completed interactive run
`2026-10-07T10-33-32.118Z-interactive-2912559`. A single constrained session,
`2026-10-07T15-16-14.218Z-interactive-3602154`, obtained the remaining eleven
function dossiers and a read of the zero-initialized music pointer at `0x421060`.
Open took 17.6 seconds; lazy first analysis took 48.1 seconds; later dossiers
took 0.02–0.32 seconds. Explicit close saved 236 cumulative Evidence records.
Complete private requests/results and one cumulative snapshot remain in
`.analysis/rea/`; checkpoints record identities rather than duplicating it.

| Entry | Owner function | Owned/span bytes | Evidence ID |
| --- | --- | --- | --- |
| `0x00401000` | `open_mds` | 497/522 | `ev_b065fc674d2df0514ae7b30b49b895ceb361f5ec770b3c4e0ec21eb8512ef3ed` |
| `0x00401210` | `parse_mds` | 828/868 | `ev_77dddb1d53c6bab6fa3f14d7c99306f681a2924a232ea0cb30d347ac7180e7a9` |
| `0x00401580` | `expand_mds_events` | 343/343 | `ev_0e7f8948f3c0f268ac5c6331fff206ed9abcb368225c4fc744fb40d8a8b979cf` |
| `0x004016E0` | `release_mds` | 149/149 | `ev_f57dc5564b0c8e08a95e0c6130497dc7d7a41e7067182e7fef3cbe1e7ef839c5` |
| `0x00401780` | `play_mds` | 493/513 | `ev_731ffd0b77a82869a867a736b02d245cc55b41b97dfc1974dee55fe3f83d27a4` |
| `0x00401990` | `pause_mds` | 133/133 | `ev_5aa9fc414d361f9b0c90d03cf2eddc3f917cab539e0cf69ab6a04d7fc29e871a` |
| `0x00401A20` | `stop_mds` | 225/225 | `ev_c16f07a25664c6b672390f14698cb3e71c3df902266c28f23d2e1b122f50b1ab` |
| `0x00401B10` | `midi_callback` | 127/127 | `ev_b6d7ad536b3a34effbc5d45b98de2b6431f5e966064bdca80b546b357a3fe9ba` |
| `0x00401B90` | `load_music` | 249/249 | `ev_4ebf4ef2dff1e4a680cc4b6a29428da728cf13e9170119b7005f33cafaa6f0ee` |
| `0x00401C90` | `resume_music` | 77/77 | `ev_ead155bb522a0775dd31c15dfc1bd7b6d53c381afe009ded310d87844d38a08c` |
| `0x00401CE0` | `pause_music` | 75/75 | `ev_aa6fbad0061313afd3af030415fd8f96f4cff4b166cc604fcf463b5ec13eb47c` |
| `0x00401D30` | `restart_music` | 106/106 | `ev_39f91496229ef7fc03f698838983d3e51ab2fc24f35ad2babe9606ebab9814f0` |
| `0x00401DA0` | `close_music` | 105/105 | `ev_b4bb1ebcf4f76cda81d97d5a75bc251b707fe70c37dd773d8d78e3b693e5f493` |

Noncontiguous bodies:

- `open_mds`: `0x401000..0x40104e`, `0x401054..0x401076`, `0x40107c..0x4010e5`, `0x4010eb..0x401126`, `0x40112c..0x401156`, `0x40115c..0x401209`.
- `parse_mds`: `0x401210..0x40125e`, `0x401264..0x40128c`, `0x401292..0x4012dd`, `0x4012e3..0x401357`, `0x40135d..0x4013b8`, `0x4013be..0x40142b`, `0x401431..0x40146d`, `0x401473..0x4014d9`, `0x4014df..0x401573`.
- `play_mds`: `0x401780..0x401827`, `0x40182d..0x401866`, `0x40186c..0x4018d1`, `0x4018d7..0x40192d`, `0x401933..0x401980`.

Ranges in the table use inclusive ends. Open, parse and play have separated
instruction ranges. Subsequent full-span reads establish the open/parse gaps
as internal cleanup jumps and retain all 522/868 bytes for comparison. The
original Ghidra address-set ownership counts remain unchanged.

REA's instruction view resolves two consequential pseudocode limitations.
`play_mds` loads return codes **6** and **7** for an invalid cookie and an
already-active stream, although the pseudocode shows zero on those paths.
The completion callback ends with **RET 0x14**: its real ABI has five stdcall
arguments, including an unused fifth argument. The inferred four-parameter
prototype is incomplete. Wrapper `extraout_EAX` expressions are replaced only
after checking the actual call result and subsequent TEST instruction. The
independent oracle executes these paths and checks stack cleanup and preserved
callee registers. VC4 and MinGW object symbols independently confirm
`_dxball_midi_callback@20` for the maintained implementation.

## Storage and imports

The original context contains magic, time division, per-buffer capacity, format
flags, buffer pointer, stream handle, state bits, buffer count and pending count.
It occupies 36 bytes on i686 and grows naturally to 48 bytes on this native
host. MIDIHDR occupies 64 bytes on i686 and 120 bytes on the host; context and
header fields use typed pointers rather than copied x86 offsets. Each allocated
buffer is a header followed by its payload. The stride is `sizeof(header)` plus
capacity. All six original songs use capacity 4096; accepted native fixtures
retain aligned header strides. Original WinMM header-size arguments remain
64 and are checked separately from host record size.

The import table exposes the original LocalAlloc/LocalFree, file mapping,
GlobalAlloc/GlobalLock/GlobalHandle/GlobalUnlock/GlobalFree and MIDI stream
operations. Their calling convention is x86 stdcall. A real i686 SDK adapter
must bridge callback DWORD, LPBYTE property and nominal SDK header/handle types
explicitly; directly assigning incompatible function pointers is inappropriate.
The portable mock table is not a real 64-bit WinMM adapter.

`dxball_music` corresponds to the original pointer at `0x421060`. Its wrapper
holds a context pointer and playing flag. Platform music load, resume, pause
and close defaults now call maintained wrappers; final runtime music cleanup
also defaults to maintained close. The platform's void loader slot uses a
small bridge around the original integer-returning loader. This bridge is not
an additional reconstructed original function.

## Preserved behavior

Open accepts low mode bits 1 for file mapping or 2 for caller memory; 0 and 3
return 4 without changing the output pointer. It allocates a zeroed context,
sets the MDSI cookie and parses the data. Failed opens free the context before
unmapping and closing mapping/file handles. A successful memory open does no
file work. Output changes only on success.

The parser checks RIFF/MIDS, then fmt and data tags, reads timing/capacity/flags
and allocates the original buffer count. Some chunk bounds compare with the
remaining total before subtracting the chunk header; the reconstruction keeps
those checks rather than silently tightening the format. Per-buffer start
ticks are ignored. Raw format copies bytes; compact format expands events.
GlobalLock is attempted even after GlobalAlloc returns zero. A failed lock does
not free the returned allocation handle. Later parse failure unlocks/frees the
buffer allocation but leaves its pointer in the context. These failure effects
remain observable and are preserved, including the original allocation leak.

Compact events contain delta/event DWORDs; expanded events add a zero stream
ID. High-bit events use the low 24 bits as a payload length rounded up to four.
Malformed inputs can write a delta or all three event DWORDs before failing.
Only successful conversion updates bytes recorded; the input descriptor is
unchanged. Capacity errors, missing event words and truncated long payloads
therefore have distinct partial-write behavior.

Play creates a stream only when none exists, sets time division, prepares and
queues every header, then restarts. Pending count increments only after both
prepare and queue succeed. Bit 2 selects looping and bit 4 marks pause. Errors
on a newly created nonzero stream attempt stop; failure while resuming an
existing paused stream preserves the existing handle and prior mutations.
Pause avoids redundant API calls. Stop sets bit 1 before reset; reset failure
clears that bit and preserves other state. Successful stop ignores unprepare
and close return codes, clears handle/state and leaves pending count intact.
Release attempts stop, frees buffers, writes the freed cookie and frees the
context even if stop failed.

Only MOM_DONE (`0x3c9`) touches a callback header. A looping, non-stopping
context requeues it; failed requeue or a non-looping/stopping context decrements
pending count. Other messages accept a null header and do nothing. Wrappers
replace an existing player before loading, preserve playing state on failed
pause/resume/restart and clear the global on close. Close followed by release
can attempt reset twice when the first stop fails.

## Independent verification and limits

`tests/test_midi_differential.py` runs every original body with only imports
and original wrapper malloc/free intercepted. No parser/converter/controller
algorithm is replaced by a Python reference implementation. Native and x86
allocations are separate; only logical pointer roles and ABI-dependent
allocation sizes are normalized. Tests strictly check original import sizes,
complete logical context/header fields, reserved fields, full payloads,
ordered effects and state visible at API boundaries. Zero-sized allocation
behavior is supplied by the controlled allocator.

Coverage includes every mode byte, malformed chunk boundaries, raw/compact
buffers, converter poison tails and partial writes, mapped-file cleanup,
allocation/lock failures, every stream failure stage, high state bits and the
five-argument callback. All six private MDS assets execute the actual parser
and connected load/queue/callback/pause/resume/restart/replace/close paths.
Connected lifecycle checks are recorded separately from direct cases.

The claim requires nonnegative bounded counts, mapped backing storage, aligned
header strides and no allocation/arithmetic overflow. Native wrapper malloc
failure is outside this domain because the original dereferences its result.
The controlled WinMM boundary supplies header mutations and completion calls;
real asynchronous callback scheduling, driver playback, imported API
implementations and hardware sound are not established by these tests.

The family checkpoint groups every differential suite, forty cold exact units,
eight rejection checks, native/MinGW/VC4 builds, Wine inspectors and saved REA
verification. Reports/configuration and complete input identities are retained
under `.analysis/checkpoints/midi-199-40/`. Journaled cleanup retains immutable
evidence and removes only verified duplicates and obsolete compiler probes.

## Connected allocator ownership draft

A private shared-C copy now connects the music wrapper to the reviewed new/delete
chain. The original side removes its two wrapper allocator replacements and
executes the original internal bodies. **186 fixtures / 528 MIDI entry calls**
compare complete logical state, payloads and ordered effects. Original entry
observation records 210 new calls, 210 deletes, 458 HeapAlloc attempts
and 248 handler invocations. These counts are separate from maintained direct
cases.

The matrix covers immediate success, one or three failures before successful
retry, a negative handler result and heap replacement, with malloc mode zero.
It includes opening/playing failures, malformed data, wrapper replacement and
all six original songs through callback, pause, resume, restart and close.
Wrapper requests independently check the original eight-byte and native typed
16-byte sizes. LocalAlloc contexts and GlobalAlloc banks keep their own APIs;
wrapper deletion snapshots semantic fields before poisoning retained storage,
and later checks detect writes to that freed mock block. Lock-failure leaks and
release after reset failure remain visible rather than receiving invented
cleanup.

REA `capture-process` Evidence
`ev_b087b62a57af4b1dce3ac5dc92df7052238ad0295108ba62b65f15f501d472cc`
records the corrected run's child exit zero and complete report SHA. Its 360
input identities include pre-execution loaded engines, actual GCC components
and prebound link objects/libraries. An independent source review prompted
those checks and the poison check; the earlier result/source remain sealed as
a superseded control. A process alarm bounds broken callback diagnostics without
changing the reconstructed allocation retry loop. Full comparisons stream into
a digest (94,623,490 serialized bytes), avoiding a redundant large snapshot file.

This remains an isolated native ownership draft. The heap is fixture-seeded;
production startup/teardown, resource/frame connection, i686 connected MIDI
execution, real WinMM delivery and asynchronous callback lifetimes remain open.
Null new-result faults are a separate unexecuted diagnostic. Retained mock
context/buffer storage is not physical lifetime proof. Maintained source and
its existing semantic/exact ledgers remain unchanged.

The corrected 60-file checkpoint retains sources, report, products, source review
and REA capture, with 319 external references. Subsequent retention removes
13 superseded working files after matching their sealed copies, shares 43
immutable duplicates and recovers another 592 KiB of measured disk usage.
All 6,881 immutable paths, 2,004 references and 49 originals verify; the next
cleanup preview is empty. The current successful inputs/products stay retained.
