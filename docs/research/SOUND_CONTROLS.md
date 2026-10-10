# Persistent sound parameters

REA's Ghidra instruction dossiers identify three adjacent application entries
that change a sound's frequency, pan or volume without starting playback. The
shared C implementations extend the existing [sound owner](SOUND_OWNER.md),
including its actual lost-buffer restoration and file reload path.

| Original entry | Maintained function | Owned / span bytes | REA Evidence |
| --- | --- | ---: | --- |
| `0x00405FA0` | `dxball_set_sound_frequency` | 159 / 159 | `ev_28bae731b59d7595344f0772d6f48a5b9caafd8756ec263f808a967111e8b065` |
| `0x00406040` | `dxball_set_sound_pan` | 159 / 159 | `ev_5a702fba01f0411b85ff3cfd2647d7e1118425098ae4f0dace560a0112c1c261` |
| `0x004060E0` | `dxball_set_sound_volume` | 159 / 159 | `ev_77abf2fa6a9958ea9290a3640b3553f7a54f25fb6a2f31192452faf3b6875916` |

The three complete, contiguous instruction bodies agree with the imported
extents. Their closed, target-matching REA session retains the requests, full
dossiers, provider metadata and timings. Matching saved evidence is reused for
the restoration dependency; its binary implementation is not queried again.
Static inspection supplies these contracts, while original-x86 execution
against native C supplies the separately scoped behavior comparisons.

Each entry first checks for a sound device and a non-null record. It calls
GetStatus at COM slot 9 and ignores its HRESULT. A defined output with bit 2
set invokes the existing whole-bank restoration routine. The entry then loads
the current record and buffer again, calls SetFrequency/SetPan/SetVolume at
slots 17/16/15, and ignores that HRESULT too. Finally it loads the current
record again and writes the requested value at x86 offset 24/28/32.

Zero is an actual requested setting here. The playback wrappers instead use
zero to omit an override. A failed setter still changes the record's cached
parameter. Restoration can replace the record and buffer through a real file
reload; keeping the earlier pointer would write freed storage. A synchronous
setter callback can also replace the slot, so the final cache write must use
the current record. Frequency is an unsigned DWORD; pan and volume are signed
32-bit values. Host pointers grow naturally, and COM methods retain stdcall
on i686.

`tests/test_sound_differential.py` executes the three unmodified original
entries, their actual restoration/reload dependencies and the native bodies.
It compares ordered API effects, all fifty logical sound slots, complete buffer
payloads, retained and freed records, spare bytes and allocation guards. The
original caller also checks preserved registers and stack discipline. COM
methods, imports, heap allocation and termination keep their controlled
boundaries; no sound-control algorithm supplies the expected results.

There are **1,393 direct cases per control / 4,179 added cases**. The complete
sound suite passes 5,782 direct cases and 48 separate connected checks. These
counts include control-specific rejected Restore paths: the old lost buffer
remains in place, yet the setter and cached write still happen. An explicit
runtime guard rejects optimized Python before constructing the harness or
writing a pass report; the rejection is checked in a separate `-O` invocation.

The control cases cover slots 0/17/49, absent devices and records, zero and
32-bit boundary values, playing/lost/high-bit status combinations, defined
GetStatus output with positive and negative errors, setter failure and a
synchronous slot replacement. Connected focus/recovery sequences use these
entries alongside load, playback, pause, reinitialization and release.

Slots must be in 0..49. Live records require valid buffers, GetStatus must
supply defined output even on error, and a successful restoration reload must
leave a usable record. Unwritten outputs, invalid backing, reload failures
leading to dangling records, concurrent mutation and physical DirectSound
delivery remain outside this acceptance. Passing arbitrary DWORD requests to
a controlled API does not show that a real audio device accepts them. These
entries have no configured byte-exact unit.
