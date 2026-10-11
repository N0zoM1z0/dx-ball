# Complete display initialization frame and control flow

Both initialization controllers have complete instruction correspondence under
a typed frame mapping and the existing explicit relocation bindings. Fullscreen
has 325 instructions across 1,343 original and 1,406 current bytes. Compatible
has 288 across 1,147 and 1,180. Every byte of each enclosing body decodes, and
every instruction pairs; there are no omitted tails or inline tables. Strict
comparison still has 1,278 and 1,092 differences. Neither is a new exact unit.

Each pair allocates the same total frame. The complete byte bijections account
for all 472 fullscreen and 468 compatible bytes, including fields not directly
addressed by individual instructions. These are existing ABI objects, without
added padding, invented locals or declaration-order experiments:

| Object | Bytes | Fullscreen current/original base below EBP | Compatible current/original base below EBP |
| --- | ---: | ---: | ---: |
| Window class | 40 | 40 / 472 | 40 / 468 |
| Capabilities | 316 | 472 / 432 | 468 / 428 |
| Surface description | 108 | 148 / 116 | 148 / 112 |
| API result | 4 | 152 / 8 | 152 / 4 |
| Attached-surface flags | 4 | 156 / 4 | Absent |

All instructions agree after translating negative EBP displacements through
these object identities and pairing direct branch destinations by instruction
ordinal. Fullscreen has 32 direct branches, 42 calls and 114 actual relocations;
compatible has 20, 42 and 110. Branch targets are decoded instruction boundaries.
Call operands, positive frame arguments, selected structure-field writes,
global reads/writes and returned values agree. Both finish with plain `RET`.
Internal relocation definitions use actual current COFF section/value instead
of replacing a current destination with its original address. External bindings
retain the existing recipe's explicit projections; this audit does not establish
new import or literal identities independently of that earlier recovery.

The matching owner is the exact same object already linked into the current
VC4 product. Its complete input closure and the four current product hashes
verify. No source edit, compiler invocation, provider query, build or runtime
case runs. Existing initialization acceptance keeps its historical scope;
there is no new semantic acceptance or physical DirectDraw claim. Source 283,
scoped semantic 247, exact 188 / 35,003 code bytes / 136 metadata bytes and
origins 270 authored / 83 runtime / 42 compiler-generated / 133 unknown stay
unchanged.

The typed correspondence translates API frame pointees by object identity.
Raw stack addresses, arbitrary driver aliasing or retention of those addresses,
uninitialized output fields, scratch registers/flags, void-exit residue and the
unique original declaration spelling remain outside the claim. GetCaps output
and selected descriptor fields retain the defined-output boundary described in
[the platform owner](../PLATFORM_OWNER.md). Identical normalized instructions
do not turn uncontrolled backend behavior into an observed execution result.

Reuse the closed original REA dossiers from
`2026-10-07T11-04-09.689Z-interactive-2967798`, whose contiguous extents and all
assembly instruction addresses match the verified PE:

- Fullscreen: `02-analyze_function.json`, Evidence
  `ev_2cc92baf4edd1bfc64e4ea142dd7d186ca9124af4dda1bda4b72cb0945cc88d8`.
- Compatible: `03-analyze_function.json`, Evidence
  `ev_11e3dc434ea2130b97aafcbdeb5927e235c6ea83b327a1346881a3898124fa3b`.

These historical serialized carriers are 5,297,120 and 4,313,515 bytes.
Their compact complete assembly projections are 9,722 and 8,380 bytes.
They are retained file sizes, not fresh transport, latency, RSS or model token
measurements. REA 6.3.0 remains the installed release, with the latest official
registry check retained by the preceding window checkpoint. There is no setup,
doctor, provider restart or historical snapshot replay.

User-requested storage cleanup removes 1,616 optional Ghidra offline API
documentation and editor completion files: 101,491,889 logical bytes and
104,804,352 previously single-link allocated bytes. Complete per-file hashes,
the pinned restore archive URL/hash and deletion checks are retained. All 206
pinned required runtime files and four current products verify before and
after; unique historical evidence, including the 72,771,098-byte legacy
snapshot, remains. This is allocation accounting, not a measured device
free-space delta. No provider restart is needed to verify optional docs removal.

Private proof, both full streams, frame maps, actual symbol definitions,
closed-Evidence and current-product identities:
`.analysis/display-initialization-frame/`. Immutable seal:
`.analysis/checkpoints/display-frame-flow-283-188/sha256.json`.

Retire both display initialization candidates as missing-source hypotheses
within this complete typed scope. Do not trial names, declarations or storage
order to reduce displacement-width differences. Full authored denominator,
unique original source spelling and synchronized game/audio fidelity remain
open. Continue with independently distinguished unknown-origin/storage evidence
or a demonstrated missing game effect, using the existing scoped CRT member
inventory before acquiring another provider dossier.
