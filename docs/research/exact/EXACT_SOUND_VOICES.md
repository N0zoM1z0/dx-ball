# Sound playback and buffer recovery

This batch recovers seven complete bodies in `src/sound.c`, covering 1,454
original bytes. It uses the existing REA dossiers.

| Routine | Address | Bytes | Compiler result |
| --- | --- | ---: | --- |
| Play once | `0x405C50` | 289 | Exact |
| Play looping | `0x405D80` | 289 | Exact |
| Stop and rewind | `0x405EF0` | 174 | 5 differing bytes |
| Set frequency | `0x405FA0` | 159 | 4 differing bytes |
| Set pan | `0x406040` | 159 | 4 differing bytes |
| Set volume | `0x4060E0` | 159 | 4 differing bytes |
| Restore buffers | `0x406180` | 225 | 13 differing bytes |

## Recovered behavior

Each voice operation returns when the device or sound record is absent.
Every COM call reads the live record and buffer. This replaces the previous
cached pointer, which could survive a callback replacing the buffer.

Play and update apply nonzero frequency, pan and volume arguments, then call
Play with flags 0 and 1 respectively. Results 2 and `0x88780096` trigger buffer
recovery and one retry using the current buffer. These complete original API
bodies replace the shared private helper.

Stop and the persistent setters read status, recover lost buffers, then perform
their operation. Stop rewinds to position zero. The setters publish their
parameter into the current record after the COM call, including when it fails.
The source retains the observed HRESULT stores.

Recovery scans all 50 records. For each lost buffer, it calls Restore and,
on success, copies the filename before reloading that slot. Reloading replaces
the record, so subsequent voice calls read the replacement.

## Evidence and compilation

The complete, RET-inclusive REA bodies are recorded by these Evidence IDs:

| Routine | REA Evidence |
| --- | --- |
| Play | `ev_ef6fb9d2676911af136542d534690483b0b4cd60bb87e1bb51ad2912875ed2b4` |
| Update | `ev_4f3837704530a529e08b8bbab841430914566e16220c1de39590fb279df06952` |
| Stop | `ev_a7d4f764f321d44850e595e49fee07e60442eeaececc6441770300b95dbedf96` |
| Frequency | `ev_28bae731b59d7595344f0772d6f48a5b9caafd8756ec263f808a967111e8b065` |
| Pan | `ev_5a702fba01f0411b85ff3cfd2647d7e1118425098ae4f0dace560a0112c1c261` |
| Volume | `ev_77abf2fa6a9958ea9290a3640b3553f7a54f25fb6a2f31192452faf3b6875916` |
| Recovery | `ev_5dc1b0f0c563f51eecd77fab5ff675667f74ae773f9dfee9b2d1e7b444301e16` |

One sound recipe compile supplies all 11 affected comparisons, with complete
15-file compiler inputs and actual relocations. The four previously accepted
sound helpers remain exact. Play and update add 578 bytes, bringing the ledger
to **126 exact functions / 19,991 code bytes**.

The other five bodies emit their original sizes. Every differing byte is an
EBP-relative local displacement at a matching instruction boundary. Their full
comparisons remain candidates; this batch used no local-name or layout trials.

The native build and one existing sound Oracle pass: 5,782 direct cases and 48
connected checks covering focus, buffer recovery and callback rebinding through
controlled DirectSound, import and heap boundaries. VC4 links the game using
the new sound object and 30 validated existing objects. MinGW Release also
builds and links. Physical audio behavior retains the earlier play-run evidence.

Full inputs, dossiers, comparisons and products are retained in
`.analysis/checkpoints/exact-sound-voices-283-126/`.
