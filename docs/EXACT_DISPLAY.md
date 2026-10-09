# Display-surface sprite drawing and rectangle queues

This batch restores six complete display emissions and recovers the ordinary
resource sprite blit, adding 2,219 exact bytes and four source mappings.
The checkpoint is **257 source-present entries (245 game + 12 runtime) / 247
directly validated entries / 112,273 distinct direct cases / 55 exact units /
8,231 bytes**. The stable-source owner batch and grouped cold replay pass.
All extents are complete COMDATs, with every relocation applied and no masked
bytes. Shared C and natural pointer layouts serve native, MinGW and pinned VC4.

| Original entry | Maintained unit | Complete bytes | Retained REA Evidence |
| --- | --- | ---: | --- |
| `0x4040B0` | blt-sprite | 195 | `ev_1b6c1b404e87fc6a492e8b2ed1d3eea8020a9f5446a6c5eaf8d76b4a0533df40` |
| `0x408180` | blt-effect-sprite | 362 | `ev_82e6d49881f8641a426f66235acef4c51d18f0d3420d746c0d1f13c535afb861` |
| `0x408460` | blt-reduced-sprite | 362 | `ev_40b8ddcf6aa3efdcf4aca2672b36818f47380c9acd8421be17e47d27f638fd8e` |
| `0x408740` | stretch-effect-sprite | 306 | `ev_2d69c6041416a67a1548d91dc71a945b13a33e065d32e96528ffacd6f80ce455` |
| `0x408880` | queue-sprite-region | 272 | `ev_3687124640959271155870347ab4ae5dc46934963ac07b33e841cb1d0db8f413` |
| `0x4082F0` | draw-effect-sprite | 361 | `ev_ddac92d3e1a7e508d55181c07f05bbbbabb7870694d36de94fa3eeb7ada0155f` |
| `0x4085D0` | draw-reduced-sprite | 361 | `ev_cc1db01cb0efa2d9fd45a7a3e26b2ebdd4d865c6a37d2bc671fe348434314ef0` |

The first five dossiers are bounded new `analyze_function` operations in
`config/rea-pending-owners.json`. The two BltFast dossiers are reused from
matching retained Evidence. Each function has one contiguous range ending
in plain ret. The same session also reviews the separate list constructor
`0x40F200`; that observation is preparation for later ownership recovery and
adds no source or exact claim here. The session closes with a reusable snapshot.

## Restored source and state

Each display entry computes a real local RECT before dispatch. Normal sizes
come from the current bank's sprite width/height; stretch uses supplied width
and height. The source RECT stays in the sprite and its surface is reread for
the call. Blt targets global effect surface `0x42E690` through slot five, with
flags `0x01008000` for keyed copies or `0x01000000` for plain copies and a null
FX pointer. The two existing BltFast entries use slot seven and flags `0x11`
or `0x10`. Their previous convenience helper and short wrappers cached a sprite
pointer and made calls absent from the original entries. Explicit original
field reads, a real RECT and direct typed COM calls restore both full bodies.
The queue-only entry computes the same source-sized RECT without a COM call.

After dispatch, the current page and its count are reread. Counts below 1,000
append the full RECT at root `0x4305E8` plus count times 32 plus page times 16,
then increment only that page's count at `0x4305E0`. Independently, reduced
particles exactly one and present count below 2,000 append a RECT at
`0x426990` plus count times 16, then increment `0x4305D8`. Full queues skip the
corresponding append. Other mode values skip the present queue. There is no
other-page invalidation, clipping, HRESULT check or added retry in these entries.
The existing interleaved two-page and present arrays retain their reviewed
representation; no new storage alias or compiler-selected layout is introduced.

Direct copies are ordinary struct assignments. The maintained functions are
grouped by Blt/queue and BltFast operations. Bounded compiler diagnostics showed
that VC4's unoptimized expression scheduling depends on source definition
placement: compatible alternatives changed sprite-index address arithmetic by
four bytes and commuted two dimension operand bytes. Rearranging the restored
related bodies yields the original complete emissions for all six. This does
not establish unique historical names, definition order or compiler flags.
No fake locals, padding, forced assembly or extra operations are used.

The ordinary resource blit had a 199-byte emission after earlier shared storage
changes. Its current source/header context produces all 195 original bytes.
Its ten original DIR32 targets stay fixed; the canonical relocation offsets
are refreshed to those of the complete current object before cold acceptance.
No semantic cases or source mappings are added for that already maintained entry.
All 48 preceding exact units are replayed with explicit content-attested literal
ordinal refreshes. The resource build retains `/ML`; the display build uses the
same existing default `/MT` flags as the other game exact units.

## Verification and remaining scope

The existing 22 game owner scripts run once against frozen source inputs and
one native library. Existing display direct cases cover the restored BltFast
entries; the four new entries add no tracked semantic rows or direct-case counts.
A 30-case private probe reuses the display target/native snapshots and passes
complete buffers and ordered COM arguments across empty, last-slot and full
queues, both pages and reduced-particle modes. A local external Blt callback
observes the separate destination and sprite-source rectangles; the existing
board-restore callback assumes equal rectangles. Original function bodies are
unmodified. Its repeated cases are not published as additional
direct acceptance. Physical COM driver pixels and active use of the four newly
mapped entries remain unresolved. One grouped cold replay compares all 55 exact
units; existing rejection controls and a MinGW build complete this batch.

A read-only review of saved fixed-point dossiers identifies a genuine class
lifetime/API gap alongside the already behavior-validated triangle rasterizer.
The class has thiscall ECX ownership, by-value operands, a hidden division-result
pointer and compiler-generated exception cleanup continuations. Adjacent nine-
byte pieces are not automatically independent authored functions. The retained
constructor at `0x40F200` writes four zero dwords whereas maintained list owners
currently expose three links; its fourth field needs consumer evidence before
adding layout or assigning meaning. These larger owner/lifetime gaps remain
future reconstruction work. Ghidra's CReObject library signature is a heuristic,
not proof of source origin or historical class names.

The >=95% complete-source objective remains open. The provisional inventory has
266 unknown origins and five identified runtime dependencies without maintained
source; a complete authored denominator has not been proven.
