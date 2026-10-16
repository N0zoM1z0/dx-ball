# Editor key address producer and complete switch

The complete editor-key comparison remains **638 current / 632 original bytes,
260 differing positions**. One board-clear address producer accounts for its
six extra bytes and two extra instructions. No source or exact acceptance changes.

| Original at `0x40C817` | Current producer |
| --- | --- |
| Push tiles address `0x43F8F8` | Load storage root `0x43AAB8`, add tiles offset20032, push EAX |

The current source passes `&dxball_board_tiles[0]` to `memset` for 400 bytes.
The actual shared `DxBallBoardStorage` puts tiles at offset20032. That storage
also preserves the original terminal index50 overlap; replacing it with invented
padding or independent globals to collect a shorter producer is not justified.
The earlier [byte-owner slice](CLOSED_STORAGE_DIAGNOSTICS.md#board-byte-owner-slice)
already rejects equivalent offset/cast forms in the board-copy consumers.

## Complete instruction, table and continuation correspondence

The retained REA dossier owns 86 instructions / 362 code bytes in three ranges.
Its enclosing 632-byte span also contains a five-byte jump at `0x40C87D` to
the common exit at `0x40C9AE`, plus 265 bytes of compiler switch data. The whole
original therefore contains 87 instructions / 367 code bytes. The maintained
owner emits 89 instructions / 373 code bytes and the same-sized tables.

| Region | Original offset | Current offset | Bytes |
| --- | ---: | ---: | ---: |
| Eighteen target addresses | 357 | 363 | 72 |
| Byte selector | 429 | 435 | 193 |
| Common exit, including its jump | 622 | 628 | 10 |

The proof uses actual COFF definitions to delimit data and decodes only the
maintained code regions. Every original owned instruction start maps to a
maintained instruction or the explicit address producer. The remaining mapped
instruction is the five-byte otherwise unowned jump, verified against the full
original bytes. All direct branches and 48 actual relocation fields are
accounted for, including both complete `default.bds` strings. The four-byte frame
is unchanged. Every one of the 256 input-byte routes agrees after the original
signed-byte promotion, unsigned range guard and two-table dispatch.

An in-memory explanatory projection substitutes the observed original producer,
then recomputes direct branches and relocation fields at their mapped sites.
Every remaining byte of the full 632-byte span agrees, including tables and exit.
This projection is never saved as an object/executable, used in production or
submitted as an exact result. The strict 638/632/260 receipt stays unchanged.
This does not establish original declarations, arbitrary EAX/flags across the
producer, unknown callee contracts or whole CPU equivalence.

## Evidence and preservation

REA Evidence
`ev_c3b032921ff367662243437140e61960889bc020f84de66d663fcd0d86c2cc17`
is operation03 of closed run `2026-10-07T14-34-29.713Z-interactive-3470017`,
bound to the pinned original. The cached editor object and every consumed
project input verify against the current complete candidate report.

Private `.analysis/editor-key-address-correspondence-20261017/` retains the
executed proof, all 256 routes, branch/site mappings, full identities and seal.
An initial bookkeeping assertion guessed21 direct branches after the byte and
route checks had passed. The corrected count derives from the dossier's 22
owned direct branches plus the one unowned jump; both script versions remain.
No compiler, provider, runtime, relink or full replay runs. Source475 / exact380 /
complete candidates95, canonical products and the current image stay unchanged.
