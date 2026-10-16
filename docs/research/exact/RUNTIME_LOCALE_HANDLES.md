# Locale category and code-page storage

`runtime_locale_handles.c` now supplies the six `__lc_handle` category slots and
`__lc_codepage`. These are 32-bit LCID/UINT values, including on a host with
eight-byte pointers. All slots initially select the C locale; the code-page
selector initially contains CP_ACP (zero). The existing consumer declarations
are compatible and remain unchanged.

The shipped nlsdata2.c, locale.h and setlocal.h establish all six categories
(ALL, COLLATE, CTYPE, MONETARY, NUMERIC and TIME) and the two field types. The
actual pinned nlsdata2.obj at archive header offset `0xA48EE` contains one complete
28-byte zero-initialized data section without relocations. VC4 source output
matches its complete relative layout, alignment and exports: category array at
offset zero and code-page word at offset 24. All 28 bytes belong to declared fields.

**Absolute original placement remains independently unverified.** All-zero
storage is not a unique target anchor. Existing function operands do not become
new independent data-address authority. The public recipe
`config/runtime-locale-handles.json` therefore leaves `target_address` null.
This restores a source owner and its relative ABI; it adds no function exact or
independently placed target-data bytes.

## Focused consumer checks

One VC4 source compilation and native/i686 C90 compilations pass. A native
fixture links the new owner with the actual maintained case/code-page bodies
and the preceding real character/locale state. It supplies typed dependency
endpoints for mapping and CPINFO; those endpoints are fixtures, not Windows
locale drivers.

Twelve calls write each category separately and execute uppercase/lowercase.
Only CTYPE selects the mapping boundary. The check verifies the complete locale,
flag, input, count, output-capacity and code-page transport, including controlled
output bytes that differ from the C-locale shortcut. Other category writes keep
the C-locale path. All values retain their 32-bit representation.

Four scenarios execute `dxball_crt_setmbcp(-4)` against the source-owned locale
code page: zero, the built-in 932 record, supplied single-byte CPINFO for 1252,
and a supplied 65001 failure. They verify the selected page, real classification
state, expected CPINFO calls and system-selector fallback. The two new locale
globals are restored afterward. The fixture does not define replacement locale
storage or replace either consuming function.

The preceding 3,855 character-table cases are unchanged and are not repeated.
All existing function/compiler inputs remain identical, so no function replay,
game build, provider session or campaign runs. Function source/exact/semantic
ledgers and both raw comparison reports remain byte-identical: 465 source
entries, 377 exact functions and 88 complete candidates. The new standalone
owner remains outside the current game build; other locale storage, absolute
placement and complete restored CRT integration remain open.

Private member/source snapshots, compiler products, boundary fixtures and
receipts: `.analysis/locale-handles-source-20261016/`. Compiler work runs serially
under the 35% CPU, 640 MiB high and 768 MiB maximum memory scope.
