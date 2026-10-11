# Score-strip source and remaining storage footprint

The complete score-display body at `0x4158D0..0x415A80` restores its original
life-strip arithmetic, rectangle store order and Y argument. Its 433-byte
comparison improves from 76 differences to 21. All remaining differences are
actual frame allocation or EBP displacement bytes. The body stays nonexact;
the total remains 203 exact functions / 42,656 code bytes / 136 metadata bytes.

## Restored source

The original reads the capped life count, increments its register value and
scales that value before one result store. Shared source now uses
`lives = (lives + 1) * 22`, replacing the extra intermediate memory increment.
The strip rectangle stores top, bottom, left and right in observed order.
The second BltFast reads `rect.top` for Y, rather than pushing a literal zero.
The temporary life span belongs to that clear-strip operation and ends before
icon-row traversal. Existing live global life reads, caps, callbacks and the
11-byte decimal buffer remain unchanged.

REA Evidence
`ev_5bd8ce0bb9a8d5a889e6d06e213d148ea1bd2ad54e5d755b82c7705c50cfff4c`
supplies the full contiguous body, including return. The private carrier is
`24-analyze_function.json` in closed run
`2026-10-07T08-21-37.400Z-interactive-2545594`. Its target SHA-256 is
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
No new provider session is needed.

One canonical MT compiler emission has every one of the same 135 original
instruction addresses and widths. The proof parses retained REA assembly for
the original and decodes only the emitted COFF. All operation/register operands,
seven branches and nine calls agree through the explicit frame-role mapping,
except the recorded eight-byte allocation difference. Every one of the 21
strict byte differences lies inside an actual frame displacement or allocation
operand; none is omitted from the full comparison.

The 19 relocation bindings retain ordered symbols, types, addends and original
targets. One background-surface operand moves by two bytes after the compound
expression is restored. Its new offset is checked against the original REA
instruction. The comparison consumer rejects the old offset and then reuses
the completed compiler object after reconciliation. No second compile occurs.

## Unresolved footprint

| Role | Original EBP | Current EBP |
| --- | ---: | ---: |
| Text length | -4 | -4 |
| Rectangle base | -20 | -20 |
| Decimal text address | -40 | -32 |
| Icon x | -44 | -36 |
| Icon iterator | -48 | -40 |
| Icon y | -52 | -44 |
| Clear-strip life span | -56 | -48 |
| Reserved frame bytes | 56 | 48 |

Eight additional original bytes precede the decimal text address in this role
correspondence. The dossier does not establish its declared capacity or unique
source layout. The maintained 11-byte array holds every unsigned32 decimal
value and NUL; address correspondence does not justify enlarging it merely to
force the frame. Array addresses escape to actual CRT/text calls, so this is
explicit structural correspondence, not byte-exact or arbitrary stack-renaming
acceptance. No capacity, padding, name or declaration-permutation trial is used.

## Validation and retained products

The unchanged runtime Oracle score/lives loop passes 63 score-display cases
and 63 refresh calls: unsigned decimal boundaries, negative/zero/capped lives,
clear rectangles, icon rows, shared life cap and complete ordered events/state/
queues/ownership. No tracked test or case changes; physical display remains
outside the controlled backend scope.

Ten exact runtime companions remain unchanged across 2,282 bytes, and every
other runtime candidate retains its full before comparison. Native/MinGW
rebuild; VC4 links the matching recipe's runtime object with 35 verified
unchanged objects, without another source compile. All 203 exact input closures,
36 production objects and 247 unchanged historical semantic scopes verify.
The 235 changed historical input inventories refresh without unrelated replays.

Working proof, both source/product identities, offset reconciliation, complete
original instruction correspondence and selected Oracle are in
`.analysis/score-strip-source/`. Independent preservation is
`.analysis/checkpoints/score-strip-source-283-203/sha256.json`, with explicit
before-product and closed REA dependencies. The full reconstruction goal remains
active; this checkpoint closes source operations and records the storage gap.
