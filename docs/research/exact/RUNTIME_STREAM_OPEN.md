# CRT file opening

Five complete source bodies restore both stream wrappers, mode parsing,
descriptor allocation and the underlying OS open flow. The two wrappers and
mode parser are whole exacts across584 bytes and all19 actual bindings.

| Entry | Original/current bytes | Differences |
| --- | ---: | ---: |
| `_fsopen`, `0x417BF0` | 37/37 | 0 |
| `fopen`, `0x417C20` | 21/21 | 0 |
| `_openfile`, `0x41A390` | 526/526 | 0 |
| `_alloc_osfhnd`, `0x41D7D0` | 184/184 | 4 |
| `_sopen`, `0x41DB80` | 1053/1053 | 2 |

Shipped `_open.c` establishes register mode/flags/stream lifetimes, a single
initial commit flag, preincrement scanning and the original flag-update order.
After successful opening, increment the shared counter before capturing the
stream argument, then perform the original chained pointer clears. Restoring
this closes526 bytes and all16 relocations, including411 instruction bytes,
one alignment byte and the full114-byte switch carrier. No table or padding
inside the carrier is excluded. All348 old exacts and100 other candidate byte
results remain; allocation184/4 and sopen1053/2 retain their complete byte hashes.
One compiler set, no runtime/provider work. Retained object consumers refresh
actual local-symbol bindings without recompilation. Full pinned section and
REA `ev_a445b56fc2e2b4edb1f2820dd32de51b1b6cf10ab9ad4ce4167f3c808b7e101b`
are reused. Receipt `.analysis/stream-open-original-register-lifetimes-20261015/verification.json`.

Shipped `osfinfo.c` uses a block index and record cursor, not redundant base,
slot and cached-end owners. Restoring these and table-before-capacity publication
improves allocation184/37 to184/4. All instruction addresses and widths, plus180
other bytes, agree. Only CMP/JAE versus CMP/JBE at0x41D7EE/0x41D7F0 and CMP/JB
versus CMP/JA at0x41D7FF/0x41D801 differ; no exact is claimed. Both owner exacts
and all348 preceding exacts remain. Openfile526/49 and sopen1053/2 retain identical
complete byte hashes; their actual local-symbol bindings are refreshed.
One compiler set, no runtime/provider work. Re-consume the retained object after
local-symbol names change, without recompiling. Full pinned184-byte section and
REA `ev_fd61eddd9f92bb9a855286cceef9a6c9bb8ccc2298a8c07f192cdafe5a0a80b5`
are reused. Receipt `.analysis/descriptor-allocation-original-index-20261015/verification.json`.

The complete original openfile carrier includes411 instruction bytes, one
alignment byte and114 switch bytes; sopen includes981 instruction bytes,
three alignment bytes and69 switch bytes. Both pinned CRT sections match
the original in full, including all local and external relocations. The
inventory extents are reconciled to these526/1053-byte carriers; following
interfunction alignment is excluded. Neither comparison drops its tables.

Mode parsing retains `a/r/w`, update/binary/text flags, access/temporary hints
and commit toggles. Duplicate or unknown suffixes stop parsing rather than
rejecting the already accepted prefix. Only successful opens increment the
shared counter and initialize the six observed stream fields. Initializing
the parsing-active state after the base mode reduces372→49 differences.
Reusing the flags scalar for the descriptor worsens49→63 and is not retained.

Descriptor allocation scans64 blocks of32 records, grows handle capacity
only after allocation succeeds, and initializes only handle/flags/lookahead.
An existing free slot has only its invalid handle rewritten. Allocation does
not publish the open bit. Only the two loop-comparison commutations remain.

OS opening keeps the actual variadic creation mode, sharing/access validation,
creation dispositions, default text mode, creation mask, delete/temporary hints
and sequential/random priority. The security descriptor and inheritance fields
are explicitly zeroed; enabling inheritance is a separate conditional write.
That state restores1053 bytes and reduces934→15 differences. The two consumed
creation words become the cached device byte and record offset only after the
OS call. Handle installation precedes open-flag publication; the first block
load is consumed by that publication, while subsequent record accesses reread
the cached block slot after calls. This reduces15→2 differences, leaving only
the temporary record-base register. All switch bytes already match.

Opening retains zero file-type close-before-error lookup, text update-mode
Ctrl-Z handling, the original read-zero condition, error131 exception, seek
reset and failure close. `_chsize` remains a genuine declared dependency,
not a host shortcut; its body and global registry/default storage remain open.
Portable pointer widths and security layout grow naturally; no host FILE is used.

The closed REA run `2026-10-13T14-43-01.272Z-interactive-1740880` retains15
info/pseudo/assembly records. Assembly Evidence IDs:
`ev_e4aa6f69811388a9696ef6aac8020a39e1d41d7b4e1aea3701ec017e81e61c2e`,
`ev_0ede71f9e868d6b2360f60b7f2627e3a86515e8359056c3533972bb197299543`,
`ev_a445b56fc2e2b4edb1f2820dd32de51b1b6cf10ab9ad4ce4167f3c808b7e101b`,
`ev_fd61eddd9f92bb9a855286cceef9a6c9bb8ccc2298a8c07f192cdafe5a0a80b5`,
`ev_9863090a3e77dfd842bf0f97e0bd074e187e6f084f718ad0dfeeb7ad81bb85a3`.
Private whole-section proof and producer seal:
`.analysis/runtime-stream-open-20261013/verification.json`.

Source335/exact259/64,243 code bytes; attached metadata136 unchanged.
All257 preceding exacts and61 candidates retain unchanged inputs/products/results.
Current candidates64:34 authored/30 runtime. Native/i686 standalone compilation
and five complete final comparisons run; no runtime tests or game builds.
