# Exact sound operation scopes

Six complete functions in `src/sound.c` now match the original DX-Ball v1.07
executable across **965 bytes and 43 actual relocations**. One canonical VC4
`/MT` owner compile also preserves all eight existing sound exacts across
1122 bytes. The project reaches **198 exact functions / 41075 code bytes /
136 separately attested metadata bytes**. Source presence remains 283 and
historical semantic acceptance remains 247; counts do not prove completion.

| Function | Original entry | Complete bytes | Restored lifetime |
| --- | --- | ---: | --- |
| Stop and rewind | `0x405EF0` | 174 | Operation result after valid-owner guard |
| Set frequency | `0x405FA0` | 159 | Operation result after valid-owner guard |
| Set pan | `0x406040` | 159 | Operation result after valid-owner guard |
| Set volume | `0x4060E0` | 159 | Operation result after valid-owner guard |
| Restore sound bank | `0x406180` | 225 | Scan counter, valid-slot status, successful-reload filename |
| Create buffer | `0x4063A0` | 89 | Descriptor exists only during creation |

## Source and complete emission

The four voice controls retain the status local at function scope. Their
HRESULT result local belongs to the operation block after the existing null
device/record guard. The original eight-byte frame places status at EBP-4 and
result at EBP-8. All COM calls, ignored error behavior, live record reloads,
cached parameter writes and stop/rewind order remain unchanged.

Bank restoration retains the outer result, while its scan block owns the slot
counter. Status belongs to a non-null slot, and the 256-byte filename copy
belongs to successful restoration immediately before the real loader call.
The complete 268-byte frame places result/slot/status at offsets 4/8/12 and
filename at EBP-268. Copying the filename still precedes releasing/replacing
the record through loading; no stale record pointer is cached.

Buffer creation retains its returned result at EBP-4. The existing typed
20-byte descriptor belongs to the creation block at EBP-24. Its zeroing,
size 20, flags 0xE2, requested bytes/format, null aggregation argument and
returned HRESULT are unchanged.

Only declaration scopes and their indentation change. No variables, padding,
identifier trials, altered types, reordered operations, copied machine code
or alternate build bodies are added. The source before this change has 38
complete byte differences under the same relocation recipes. Each of the six
current bodies has zero differences. Original identifier spelling and exact
declaration syntax remain unknown; matching emission supports the recovered
typed source model rather than claiming a literal original source file.

## Original evidence

Six saved REA dossiers have complete contiguous bodies through their returns.
The stop, restoration and create dossiers come from
`.analysis/rea/runs/2026-10-07T16-15-32.551Z-interactive-3807439/`
at request12,13 and15. The three setters come from
`.analysis/rea/runs/2026-10-08T09-44-19.254Z-rea-sound-controls-1652685/`
at request0,1 and2. All original target digests and terminal session records
verify. Their Evidence IDs and complete record hashes are in
`.analysis/sound-operation-scopes/rea-reuse.json` and the existing
[sound owner](../SOUND_OWNER.md) / [controls note](../SOUND_CONTROLS.md).

The private `body-proof.json` records every original stack access and every
current COFF stack operand, complete body sizes, instruction counts, calls
and branches. Current instructions cover every independently retained
original listing address, and the full relocated bytes match the pinned PE.
No extent, gap, tail or mismatch is masked. `before-scope-control.json`
retains the six failing prior-source comparisons. No new provider or runtime
capture was needed.

## Targeted validation and products

A private driver selects seven unchanged loop ASTs from
`tests/test_sound_differential.py`, retaining their complete Harness
comparisons. It passes **4317 direct calls and 48 connected checks**:
12 descriptor/error/output cases, 42 each for stop/stop-all/restoration,
1393 each for frequency/pan/volume and48 connected focus/reload/recovery
calls. Cases retain absent-owner guards, zero and 32-bit values, defined
status outputs on error, rejected restoration, ignored setter errors,
synchronous slot replacement and split uploads after reinitialization.
Complete fifty-slot records, buffer payloads, heap ownership and ordered COM
effects agree with execution of the original code. The maintained test,
selected AST, driver and current library hashes are in `sound-oracle.json`.
Unrelated RIFF, file and initialization grids are omitted; tests are unchanged.

Native and MinGW affected products rebuild. The VC4 game links this final
matching sound object with 35 verified unchanged objects, without another
legacy source compile. All 198 exact input/object closures, 247 unchanged
historical semantic scopes and 36 production object closures verify. Historical
semantic input hashes refresh without implying unrelated test reruns.
Current four product hashes are in
`.analysis/sound-operation-scopes/product-verification.json`; the independent
seal is `.analysis/checkpoints/sound-operation-scopes-283-198/sha256.json`.

Initialization, WAV parsing and uploading remain nonexact. These function
matches and controlled comparisons do not prove physical DirectSound
delivery, asynchronous behavior, full rendering or the entire campaign.
