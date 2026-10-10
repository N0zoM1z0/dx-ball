# Sound upload and release

This batch recovers four complete bodies in `src/sound.c`, covering 1,147
original bytes, from existing REA dossiers.

| Routine | Address | Bytes | Compiler result |
| --- | --- | ---: | --- |
| Pause sound | `0x4057D0` | 214 | Exact |
| Release one sound | `0x4058F0` | 149 | Exact |
| Load and upload a WAV | `0x405990` | 695 | 31 differing bytes |
| Create a buffer | `0x4063A0` | 89 | 8 differing bytes |

Pause stops all voices, releases and clears each live buffer, then releases
and clears the primary buffer and device. Release returns for an empty slot,
conditionally releases its buffer, calls the original heap-release API on the
current record, and clears the slot.

Loading initializes its file pointer before releasing the previous record.
It calls the recovered malloc API for the record and publishes it in the slot.
The loader reads that live slot for creation, lock/unlock, parameter queries,
cleanup and the final filename write. The allocated-record local is used only
for checking and publishing the allocation.

Create and Lock store their HRESULTs before checking them. A successful Lock
can return two spans; memcpy fills each before Unlock and parameter queries.
The buffer helper zeroes its typed descriptor, sets size 20, flags `0xE2`,
bytes and format, then stores and returns the CreateSoundBuffer result.

Record allocation failure calls `exit(1)`. File, parse, create and lock failures
free the replacement record while leaving the slot unchanged. Create/lock
failure also retains the original buffer ownership behavior.

## Evidence and results

| Routine | REA Evidence |
| --- | --- |
| Pause | `ev_1052e31287c62f41ca5b91c02788d01d7f819378263ad1d5e7ea84f65a4c7d49` |
| Release | `ev_4a17a83a14ba89a55ddecad057550d34cfe4c60e655615affb7c6361e3496d05` |
| Load | `ev_e5e44144f4d74b3812d2c83fe7b7b649dde02f9a2107482ff677eb58455dd745` |
| Create | `ev_d0e9ffafba6bc56b0694c2b6b8f17f504beebd0138ce8f0f103be5de5c90b275` |

One sound recipe compile supplies all 15 affected comparisons and 138 actual
relocations. All six previously accepted sound functions remain exact.
Pause and release add 363 bytes, bringing the ledger to **128 exact functions
/ 20,354 code bytes**. Loader and create emit their original lengths; all 39
residual bytes are EBP-relative local displacements. Full-byte inspection
extends beyond the comparison report's 24-difference preview.

The existing sound Oracle passes 5,782 direct cases and 48 connected checks.
Its fixture binds the recovered allocator's real heap callbacks to the existing
responses. A child-process `on_exit` callback records the loader's direct
termination. The same cases still execute the actual controllers.

Native and MinGW Release builds pass. VC4 links the new sound object with
30 validated prior objects. Full inputs, evidence and products are retained
in `.analysis/checkpoints/exact-sound-buffers-283-128/`.
