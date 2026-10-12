# Signed glyph codes

The sprite record, bank-loader byte and glyph lookup/draw parameters now use
explicit `signed char`. Text measurement converts each input byte to that same
signed domain before comparing it with a sprite code. The one-byte field and
all function argument widths retain their existing ABI.

The bank loader reads exactly one byte at `0x4046EE..0x4046FB` and stores it at
sprite offset `0x24` at `0x40485F`. Glyph lookup then uses paired signed reads:
`MOVSX` for the stored code at `0x404E8E` and the incoming byte at `0x404E92`.
Measurement likewise sign-extends the sprite and text bytes at `0x405040` and
`0x40504A`. Explicit signed types preserve this contract even when a host's plain
`char` is unsigned.

The unsigned-code diagnostic loses the accepted glyph search. Combined with
SDK descriptor fields it makes ordinary blit and glyph drawing exact, but loses
search and stretch. Explicit signed codes with SDK fields still lose those two
companions. These three stages are rejected. The selected explicit signed model
uses the current descriptor and stretch contracts; every existing exact survives.

Twenty-six matching recipes preserve **213 complete functions / 56,151
code bytes**. All 44 candidate code hashes and relocation descriptors remain
unchanged. The full accepted total stays at **229 functions / 57,649 code bytes /
136 metadata bytes**, with 44 authored functions still nonexact.

The unchanged original/native selection passes 769 lookups and 768 glyph draws,
covering every byte value in all three original font banks and the empty-bank
case. Another 648 text calls cover signed high bytes, embedded NULs, duplicate
codes, misses, spacing and exclusive slot bounds. Returns, pixel buffers,
palette bytes and ordered API events compare. Native and MinGW builds pass.
VC4 links 25 matching objects, five game objects compiled with their actual
recipes and seven verified unchanged objects. The resource matching recipe uses
`/ML`; the game recipe uses `/MT`, so its matching object is not reused for the
game. All 229 complete code/literal/metadata closures verify; 235 historical input
inventories refresh without changing their case scopes. No game runs.

Retained REA evidence:

- Bank loader: `ev_b55c6def4c1b4af6c165acfb1623311bffa077753d93fab01531787dca6b6d70`,
  `2026-10-10T17-22-54.305Z-requests-825249/01-analyze_function.json`.
- Lookup: `ev_9eb642c30e5cca30a9729baaf268061b881e8ea769519a14219e1f7a6e130834`,
  `2026-10-10T17-38-24.772Z-requests-846003/02-procedure_assembly.json`.

Private complete comparisons, rejected source stages, unchanged fixture
selections and build receipts are in `.analysis/glyph-code-domain-20261012/`.
