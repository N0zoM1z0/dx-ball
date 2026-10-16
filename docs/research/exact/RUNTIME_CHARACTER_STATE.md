# Character and locale storage, and exact exponent formatting

The original decimal point is the two-byte array `"."`, followed by natural
alignment before its size_t length. Three numeric consumers previously declared
it as a single char. They now share the real array declaration and read element
zero. `runtime_locale_state.c` supplies that string, `__mb_cur_max = 1` and
`__decimal_point_length = 1`. Native size_t retains its host width.

This corrects the cross-translation-unit object type and restores the complete
310-byte exponent formatter at `0x00418EB0`. Every actual relocation and the
complete six-byte exponent suffix match. All 13 affected preceding exacts remain
exact, including fixed and general formatting. The earlier private reunited
cvt.c control remains unadopted; this change keeps the maintained owner boundaries.

Six affected owners are compiled once each. Their 19 complete comparisons give
14 exacts and five candidates. Four candidate difference counts are unchanged;
the unchanged multiplication C body emits 678 bytes/50 differences through the
new shared declaration context, against its preceding 678/21. That result is
recorded as nonexact. No accepted function is lost.

Compiler-local static and branch-table labels acquire new numbers. Bindings
follow the actual same-member definitions and offsets, rather than matching a
reused label spelling. Static storage sections retain their complete layout and
bytes. Parser labels retain their offsets/instruction layout, with only four
reviewed CMP direction changes, each followed by the same JNE. Its complete
1851/1871-byte result remains 1662 differences. No comparison bytes are patched
or normalized to claim an exact.

## Complete initial data

| Original owner | Address | Bytes | Bindings | Recovered definitions |
| --- | --- | ---: | ---: | --- |
| ctype.obj | `0x00423670` | 522 | 2 | `_pctype`, `_pwctype`, `_ctype[257]` |
| nlsdata1.obj | `0x0042387C` | 12 | 0 | `__mb_cur_max`, `__decimal_point[2]`, `__decimal_point_length` |

The classification table contains EOF followed by 256 byte entries. Named
classification flags describe ASCII control, whitespace, punctuation, digit,
letter and hex membership; high-byte entries initially remain zero. The table
and both pointer slots are writable. Each independent pointer initially selects
the first character entry, leaving the EOF entry accessible at index -1.

Complete source-produced sections match all 534 original bytes, including both
actual pointer bindings and the compiler's natural alignment. No source padding
or invented string capacity supplies those bytes. The public recipes are in
`config/runtime-character-state.json`; these standalone data owners remain
outside the current CMake game. Data bytes are separate from function exact totals.

The ctype proof reuses independently placed complete original storage from REA
Evidence `ev_84b9961d1896477a16328bb23a2f1fe39d45cf14bdf71e35bafc0536fae3fe6b`.
The locale record reuses
`ev_b5bf61f78c4eecb0f1c01d471e91e46c88a67cfa311621b1d2b0a62f8e8c4119`.
The current origin receipt, member identities and every consumed input are
verified before reuse. The shipped ctype.c and nlsdata1.c corroborate the types,
classification flags, initial pointers and natural two-byte string.

## Focused validation and remaining scope

The subsequent [locale category owner](RUNTIME_LOCALE_HANDLES.md) supplies the
six LCID slots and code-page word. Its 28-byte relative layout is verified;
independent absolute placement remains open and adds no target-data exact claim.

Both new data owners pass native/i686 C90 compilation; all six affected numeric
owners pass native/i686 C11 compilation. A native fixture links the actual
maintained classification/case functions to the new state and checks 3,855
character/mask/case results. It compares all 514 table bytes, verifies EOF,
independent writable pointer cells and table reads, and restores every fixture
mutation. Pointer and size_t widths are eight bytes on this host. Its explicit
C-locale boundary aborts if an OS locale operation is reached; non-C locales
are outside the test.

The old REA envelope and renumbered-label reader corrections reuse completed
compiler products after checking their frozen inputs. No owner recompilation,
new provider session or historical Oracle/full replay queue follows from those
reader repairs. Compiler work remains serial under the 35% CPU, 640 MiB high and
768 MiB maximum memory scope.

Totals are **377 exact functions / 77,218 code bytes / 244 attached metadata
bytes**, 465 source entries and 88 complete candidates. The inventory remains
540 plus 24 parent-owned fragments. All 249 semantic scopes retain their existing
evidence. Other locale/BSS storage, OS drivers, complete reconstructed CRT linking
and the final game build/play check remain open. Private sources, complete data
and function comparisons, reader certificates and native fixture receipts:
`.analysis/ctype-state-source-20261016/`.
