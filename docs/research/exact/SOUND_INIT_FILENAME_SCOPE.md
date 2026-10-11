# Sound initialization filename lifetime

The existing 256-byte filename workspace now lives only in the nonnull sound
reload branch at the end of `dxball_initialize_sound`. It is copied immediately
before the synchronous loader call and never used elsewhere. The retry,
dialogue, device, primary-buffer and cleanup operations remain unchanged;
names, types, capacities and executable tokens are unchanged.

The complete initialization body at `0x405120..0x4057C8` now emits **1,705 bytes**,
matching the original length. Its strict comparison improves from
**1,741/1,705 bytes with 1,447 differences to 1,705/1,705 with 27**. All 377
original instruction boundaries and widths agree, including 99 branches and
34 calls. The 27 remaining differences are actual EBP displacement bytes;
**initialization remains a candidate, with no exact promotion**.

The retained original function dossier is
`ev_0c19fd7b02df4709514364206dec7df270a537b02ffbdda25a57516fcd78ce1f`,
from the closed 2026-10-07 16:15 interactive archive. Ghidra owns 1,635 bytes
in fourteen ranges. Complete read Evidence
`ev_ea17c0f8232c3bed494b5f8e97ff67790e1d38eb410d071395c0337072d22447`,
from the closed 2026-10-10 06:36 request run, attests the entire 1,705-byte span.
All seventy excluded bytes are fourteen five-byte JMP rel32 instructions.
Their saved opcode/displacement bytes and computed targets are verified and
merged with the provider assembly; none is omitted from the correspondence.
No original general-purpose decoder or new provider session is used.

Both stack frames allocate 324 bytes. Scoping the filename restores its base
at EBP-292 and the reused dialog response at EBP-36. The latter formerly lived
at EBP-292; twelve accesses now use the original shorter displacement encoding,
removing exactly 36 emitted bytes. Eight generated switch-selector homes remain
unchanged. The remaining typed homes differ:

| Role | Original EBP displacement | Current EBP displacement |
| --- | ---: | ---: |
| HRESULT | -4 | -32 |
| Retry flag | -8 | -28 |
| Reload slot | -12 | -24 |
| 20-byte buffer descriptor base | -32 | -20 |
| Descriptor flags | -28 | -16 |

Every operation, register, immediate, branch and call agrees through this
explicit role map. It is a diagnostic correspondence; the strict comparison
retains all differences. Original declaration spelling and the remaining
local allocation order are unproved. No name, capacity, padding or coextensive
scope trial was introduced to force those homes.

All 97 relocation bindings retain their ordered types, addends and original
targets. Eighty-nine offsets move as the response instructions contract. Six
generated title-string ordinals shift by one; each complete eight-byte
`DX-Ball` string, including NUL, is checked against its prior/current COFF
allocation boundaries and the original target bytes. All twelve established
complete literal attestations remain in the manifest. The comparison consumer
first rejected stale offsets; a serialization omission then dropped those
literal attestations. Both consumer problems were repaired using the completed
compiler output, without another source compilation or changed target binding.

One canonical sound MT compile preserves fourteen exact companions across
2,087 bytes and the complete load-sound/parse-wave candidate records. Native
and MinGW rebuild the affected products once. VC4 links the final matching
sound object with 35 verified unchanged objects, unchanged resources and pinned
DirectX imports; no additional legacy source compilation is needed.

Four unchanged sound Oracle loops pass **124 initialization/prepare cases and
48 connected focus/reload/lost-buffer checks**. They preserve terminal exit
codes, partial output cleanup, retry/dialog choices, complete sound ownership,
filename copies and ordered COM/import calls. Tracked tests and fixtures are
unchanged. Controlled boundaries do not establish physical or asynchronous
audio fidelity. No unrelated parser/file grid or historical full replay runs.

All 206 current exact input closures, 247 unchanged historical semantic scopes
and 36 game objects verify. Historical input inventories refresh without
claiming reexecution of their prior cases. Totals remain 206 exact / 44,406 code
bytes / 136 metadata bytes; 283 source-present and 270 authored inventory entries.
Original source spelling and the full authored denominator remain unproved.

Inputs, compiler output, full instructions, complete strict comparison,
relocation/literal repairs and focused execution are retained under
`.analysis/sound-init-filename-scope/`. Current products are identified by
`product-verification.json`; the independent seal is
`.analysis/checkpoints/sound-init-filename-scope-283-206/sha256.json`.
