# DirectSound controller and WAV loading

## Current complete helper matching

The [buffer batch](exact/EXACT_SOUND_BUFFERS.md) recovers pause, individual
release, upload and buffer creation. Pause and release match all 214/149 bytes;
the complete loader and create helper retain 31/8 local-displacement differences.
Loading now uses the genuine malloc/free/exit calls and live record reads.
One existing sound Oracle passes with its heap and termination boundaries
adapted to those calls. Both Windows game profiles are linked.

The [voice-control batch](exact/EXACT_SOUND_VOICES.md) recovers playback,
looping, stop/rewind, persistent parameters and lost-buffer recovery. Play and
update now match all 289 bytes each. The other five complete bodies retain
4–13 differing local-displacement bytes. One existing sound Oracle passes;
the VC4 and MinGW games are linked with the recovered source.

The [complete exits batch](exact/EXACT_EXITS.md) accepts four complete sound helpers:
prepare, release-all, stop-all and release-audio, totaling 181 code bytes.
Their ordinary exit branches and all direct game-call relocations pass grouped
cold replay. Sound initialization, loading and physical/asynchronous audio
fidelity retain their existing limits. Historical
semantic-only statements below describe the initial sound checkpoint.

## Current allocation defaults

Sound records and WAV backing now default to maintained malloc-mode allocation
and heap release. Current owner replay and a separate physical SDK/default
probe pass. The connected private draft below retains its original scope and
input identities; see [allocation ownership](ALLOCATOR_OWNER.md).

The initial `src/sound.c` batch maintains fifteen connected entries: startup, file loading, RIFF
parsing, buffer upload, playback, lost-buffer restoration and focus cleanup.
Binary observations came from one REA 4.1.0 / Ghidra 12.1.4 interactive session
against the hash-pinned DX-Ball v1.07. Saved archives were checked first; these
entries had no matching prior dossiers. Twenty-one focused queries extended
the saved snapshot from 236 to 257 Evidence records. The session was explicitly
closed before compiler work or cleanup.

The subsequent [persistent sound controls](SOUND_CONTROLS.md) add frequency,
pan and volume setters with their own three REA dossiers. The current sound
suite has eighteen maintained entries, 5,782 direct cases and 48 separate
connected checks. The fifteen-entry table and counts below describe the initial
checkpoint; physical audio delivery and complete sound byte-exact reconstruction remain open.

The static dossier establishes instructions, references and inclusive body
ranges; execution claims come separately from `tests/test_sound_differential.py`.
Ghidra signatures and inferred local types are provisional. In particular, the
allocation wrapper was inferred void; its caller and callee instructions show
that EAX returns the allocated pointer. The initializer has fourteen owned
ranges: its 1,635 code bytes span 1,705 bytes. The excluded seventy bytes are
not counted as maintained instructions or claimed exact.

## Entry evidence

| Entry | Maintained function | Owned / span bytes | REA Evidence |
| --- | --- | --- | --- |
| `0x00403320` | `dxball_load_binary_file` | 304 / 304 | `ev_a52bb0030eab7563b8a83f854ffdd76af7e5b0382cd75bda896a04c3efed70a0` |
| `0x004050F0` | `dxball_prepare_sound` | 33 / 33 | `ev_5345b28e6714252665c89598e94047ef4b2947c4ad089e47fa294ed785c5c948` |
| `0x00405120` | `dxball_initialize_sound` | 1635 / 1705 | `ev_0c19fd7b02df4709514364206dec7df270a537b02ffbdda25a57516fcd78ce1f` |
| `0x004057D0` | `dxball_pause_sound` | 214 / 214 | `ev_1052e31287c62f41ca5b91c02788d01d7f819378263ad1d5e7ea84f65a4c7d49` |
| `0x004058B0` | `dxball_release_sounds` | 61 / 61 | `ev_94a38a0c816a05c2eae87be84cd560341ef73e597cb6637f535aec41f628d6f9` |
| `0x004058F0` | `dxball_release_sound` | 149 / 149 | `ev_4a17a83a14ba89a55ddecad057550d34cfe4c60e655615affb7c6361e3496d05` |
| `0x00405990` | `dxball_load_sound` | 695 / 695 | `ev_e5e44144f4d74b3812d2c83fe7b7b649dde02f9a2107482ff677eb58455dd745` |
| `0x00405C50` | `dxball_play_sound` | 289 / 289 | `ev_ef6fb9d2676911af136542d534690483b0b4cd60bb87e1bb51ad2912875ed2b4` |
| `0x00405D80` | `dxball_update_sound` | 289 / 289 | `ev_4f3837704530a529e08b8bbab841430914566e16220c1de39590fb279df06952` |
| `0x00405EB0` | `dxball_stop_all_sounds` | 61 / 61 | `ev_2b3dd1168377f765b3a2aa76502a2a941735ed95a792fab6139481e60c68e8c4` |
| `0x00405EF0` | `dxball_stop_sound` | 174 / 174 | `ev_a7d4f764f321d44850e595e49fee07e60442eeaececc6441770300b95dbedf96` |
| `0x00406180` | `dxball_restore_sounds` | 225 / 225 | `ev_5dc1b0f0c563f51eecd77fab5ff675667f74ae773f9dfee9b2d1e7b444301e16` |
| `0x00406270` | `dxball_release_audio` | 26 / 26 | `ev_a555f330cfa6fce76d239915d26e68401117a5a9fdc4df26ebda7a734f239585` |
| `0x00406290` | `dxball_parse_wave` | 264 / 269 | `ev_8c97f00d8301c9fad99e761f8bbe2ea90f8dc14d6e8db6709a75e15c49c6c1a3` |
| `0x004063A0` | `dxball_create_sound_buffer` | 89 / 89 | `ev_d0e9ffafba6bc56b0694c2b6b8f17f504beebd0138ce8f0f103be5de5c90b275` |

At that initial checkpoint, all fifteen entries had semantic acceptance only,
with no sound exact claim. Its forty configured exact units were replayed as one batch
when shared inputs changed. That VC4 epoch used screen-pan constants `$T1072` and
`$T1073`; their data still resolves to the separately attested original double
literals at 0x420068 and 0x420070.

## State and interface contracts

| Original address | Shared owner | Observed meaning |
| --- | --- | --- |
| `0x421098` | `dxball_sound_device` | DirectSound device |
| `0x42109C` | `dxball_primary_sound` | Looping primary buffer |
| `0x4265D0` | `dxball_sounds[50]` | Fifty sound-record pointers |
| `0x42106C` | `dxball_file_fallback_prefix` | Initial literal `..\\` |
| `0x4228B0` | existing `dxball_direct_draw` | Non-null suppresses sound failure dialogs |

The device uses COM slots 2 Release, 3 CreateSoundBuffer and 6
SetCooperativeLevel. The buffer uses the original twenty-one-slot interface;
GetVolume/Pan/Frequency are slots 6/7/8, GetStatus 9, Lock 11, Play 12,
SetCurrentPosition 13, SetVolume/Pan/Frequency 15/16/17, Stop 18, Unlock 19 and
Restore 20. Methods and imports retain x86 stdcall; handles/pointers grow
naturally on the native host, while HRESULT/LONG/DWORD retain 32 bits.

The original buffer descriptor is twenty bytes, with four DWORDs followed by
a format pointer. The maintained record is naturally twenty-four bytes on the
64-bit host but still passes the observed size field 20 to the controlled API.
Modern MinGW defaults to a larger DirectSound descriptor with a GUID tail;
using that version's sizeof would misrepresent the observed contract. The
local MinGW SDK's DSBUFFERDESC1 corroborates the five original fields. VC4's
pinned SDK does not ship dsound.h/dsound.lib; real legacy DirectSound binding
is still separate work. No pinned SDK file was modified.

Sound records have a buffer pointer, a twenty-byte filename, frequency, pan
and volume, at original offsets 0, 4, 24, 28 and 32. These fields occupy 36
bytes on x86; the allocator requests 37. The purpose of the spare byte remains
unknown. Source requests sizeof(record)+1 and leaves it untouched; no invented
field or packing rule forces emission. Native tests compare logical fields,
filename bytes and the spare byte, with allocation-overrun canaries.

REA read evidence for initial globals: device/primary zero,
`ev_cf17442ea99ff39b29befce3ffcdad8583a021117f82ff340b5f53182fb876b5`;
fifty null records,
`ev_0447126d6dae9bdb817e5860fc99dd1e809e0de3b68b7435f4fe68a9424557a6`;
fallback prefix,
`ev_952400d4710db6af60afd915eb9eb7704c17dd5135ff9c776a2b9946a5ed0dda`.

## Recovered control flow

Startup returns immediately when the device is already present. Otherwise it
creates the default DirectSound device, requests cooperative level 1, creates
the primary buffer with flag 1 and starts it looping. It then reloads every
retained record using a copied filename. With no DirectDraw device yet, exact
original dialog text and flags distinguish occupied sound, absent card,
factory failure, cooperation failure and primary create/play failure. Occupied
sound retries on RETRY and on unexpected responses, returns on IGNORE, and
terminates with exit code 10 on ABORT. Other NO responses terminate with codes
11, 12 or 13. A non-null DirectDraw device suppresses these dialogs. Any
nonzero HRESULT is a failure at these gates, including positive result 1.
Terminal exits occur before the cleanup following the corresponding dialog.

Prepare releases records then initializes; release_audio releases records
then pauses. Pause first stops every record, releases its buffer, releases the
primary/device and clears those pointers, but preserves records and filenames.
ReleaseSound releases a record's buffer only when the sound device is present,
then frees the record and clears its slot.

Loading first releases the old record, allocates a replacement and immediately
stores its pointer in the slot. It loads the actual file and parses RIFF/WAVE
chunks manually. All twenty-six supplied WAVs are mono 8-bit PCM with sixteen-
byte fmt chunks; their sample rates range from 2,919 to 44,191 Hz. Resource
inventory followed the chunk sizes and odd-byte padding rather than relying
on names or a standard assumed rate. No MMIO dependency is involved.

The parser accepts fmt chunks of at least fourteen bytes, preserves output
arguments it has not written, skips chunks with even-byte rounding, and returns
on the first data chunk. It also succeeds when data precedes fmt; the format
output is then preserved. That behavior is tested directly with seeded output
storage but excluded from the loader's usable-format domain.

A secondary buffer uses flags 0xE2 and the WAV's own format/data size. Lock can
return two spans; the actual original memcpy fills both. Unlock and default
frequency/pan/volume queries ignore their HRESULTs. With no device the record
has a null buffer and retained filename, with other fields untouched.
Allocation failure for the record terminates with code 1. File/parse/create/
lock failures free the replacement but leave its slot pointing at freed
storage. Create/lock failure may also leave a COM buffer unreleased. These
quirks are recorded rather than silently normalized.

Play and looping update set frequency, pan and volume only for nonzero
arguments, then Play with flags 0 or 1. The second argument is a frequency,
not a repeat flag; the earlier gameplay parameter name is corrected. Results
2 and 0x88780096 trigger RestoreSounds followed by exactly one more Play.
RestoreSounds scans fifty records, reloads only lost buffers whose Restore
returned zero, and updates record identity through the actual loader. Playback
and Stop re-read the current record after restoration; overrides are not
reapplied to a newly loaded buffer. Stop ignores the GetStatus HRESULT, then
stops and rewinds the current buffer. Defined status output is required even
when the controlled API reports an error.

The shared binary file loader first opens the supplied path, then tries the
`..\\` prefix. It uses GetFileSize, optional allocation and ReadFile. It accepts
successful short reads without checking the transferred count. Allocation or
read failure leaks the handle; read failure deallocates the destination even
when supplied by the caller. Success closes the handle and ignores close errors.

## Differential scope and remaining work

The suite executes all fifteen unmodified original bodies, including calls
between them. Only DirectSound COM methods, actual imports, CRT allocation and
process termination are controlled. Original strcpy/strcat/memcpy/memset
instructions execute. No Python sound-controller implementation supplies the
expected results. Native C and original x86 receive the same API outcomes and
compare ordered calls, complete fifty-slot logical state, filename bytes,
retained/freed records, copied PCM buffers and allocation canaries.

There are 1,603 direct cases, with positive and negative HRESULTs, factory retry,
partial buffer output on failure, every original WAV, split locks, preserved
parser outputs, ignored query errors and leaked/dangling failure states. Thirty-
six additional connected checks run initialize/load/play/pause/reinitialize/
lost-buffer replay/release sequences. They are not counted again as direct
acceptance. Native terminal cases run in forked processes with real exit codes;
original execution stops at its nonreturning exit boundary. There is no invented
return from exit or simulated post-exit ABI claim.

Accepted domains require slots 0..49, terminated filenames within nineteen
characters, valid bounded caller buffers, mapped RIFF backing without pointer/
size overflow, usable fmt before data for loading, and API-defined status/query/
lock outputs. Non-null device+record implies a usable buffer for Play, Stop and
Restore. Freed blocks are retained as mock tombstones solely to observe failure
state; subsequent unsafe use is not accepted. CRT heap/new-handler internals
are a boundary, with allocator dossiers
`ev_a3a114f83ee3fcc86ef4821ff90af4f85a55c61ba0cec1f6d53c4ee73add1e3f`,
`ev_5b84dc43a44b86e3cd73f1ebfddc73bdb1f4ef29d11181f1d56181f54cc327b4`
and deallocator dossier
`ev_71abe55c26ab63d390b070c27874d920fa335c74cc9b406dcdab748a7f3bdd33`.
They are not promoted as authored sound functions.

Gameplay, display, runtime and platform audio callbacks now default to these
maintained controllers. Physical DirectSound output, real WinMM delivery,
Win32/DirectDraw adapters and playable whole-EXE integration remain pending.

## Connected malloc ownership draft

The next bounded connection uses the actual maintained sound library through
its explicit allocate/deallocate API. A typed C boundary connects that API to
the eight-entry allocator draft; it does not rebuild sound.c. The original
malloc/free replacement hooks are removed, so original sound and allocator
bodies execute together. Only Kernel32, DirectSound COM, physical heap and
new-handler outcomes are controlled. No game audio is emitted.

REA process Evidence
`ev_f5afb693f6a73efe341e3428df1fa1f52f72ce591d17bde8eecbf63bf996852f`
records exit zero and the complete final-report SHA
`ddabac832fab02ac50f3453e5f168445dfaefa41a55a2de38791c58af1b1fd54`.
The corrected run passes **91 fixtures / 303 normal sound calls**, plus
three separately compared terminal exits, one paired seed and four paired
fixture releases. All 26 original WAVs run through load/pause/initialize/play/
release sequences with contiguous and split locks. Original entry observers
record 272 malloc requests, 354 heap allocation attempts, 84 handler calls
and 268 heap releases, including the separate terminal/fixture activity.

Record requests normalize original 37 bytes against the natural native 41
bytes by typed field offsets; checked file payloads are at least 64 bytes.
Per-call comparisons include ordered effects, complete logical slots, PCM
payloads, retained blocks, free poison and allocation guards. Failures retain
the original dangling slot and leaked file handle. Mode capture, later mode
mutation, negative handler returns and heap replacement before the first owned
block are checked without assuming cross-heap release success. The three
terminal controls compare a forked native child's state and real exit code
against original stop-at-exit, without claiming the native parent executed
those calls.

Before replay, independent source review fixes two evidence gaps: bind the
actual gold-selection JSON before use, and check callback errors/guards before
terminal exit serialization. The first successful run remains a superseded
control, separate from this corrected capture. Source review certifies its
reviewed scope rather than runtime execution. Full comparison observations
stream 15,794,008 bytes into a digest; the final report remains retained, without
storing duplicate PCM snapshots. Seed/free assertions have separate counts
and are outside that streamed digest.

This is private connection evidence for the maintained owner, not production
default allocation or exact acceptance. Physical audio, startup/teardown
binding, connected i686 execution and complete reconstructed campaigns remain
open. At that private draft checkpoint, maintained/direct/exact totals stayed
**235 / 109,805 / 36 / 3,518**.
