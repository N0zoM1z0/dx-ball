# Signed glyph codes

The current sprite field, bank-loader byte and glyph APIs use plain `char` as
their byte carrier. Lookup explicitly converts both operands to `signed char`;
measurement likewise normalizes its field and text reads. The original signed
value contract is preserved without requiring the carrier type itself to be
signed on every supported host. The one-byte field and VC4 argument ABI remain.

## Complete plain-char cohort, October20

One fixed source model restores the complete328-byte `draw-glyph`, previously
332 bytes/258 differing positions. Existing Mac API names encode plain char,
distinct from signed/unsigned char; the historical C baseline also uses this
cohort. Those observations support a natural declaration hypothesis, not proof
of the Windows source spelling. The earlier neutral C control does not answer
the present C++ frontend question. No name/order/flag variants are tested.

The three-file change covers the sprite code field, persistent bank byte, both
font API parameters and signed-value consumers. Raw file/record/API transfers
remain bytes. UI/intro calls need no extra cast because comparison occurs after
the receiving API normalizes the byte. The independent passive review checks
all256 byte transports and65,536 comparison pairs on the supported8-bit,
two's-complement VC/GNU representations; it is not a new cross-host runtime run.

The resource gate compiles once and gains glyph drawing without losing its10
accepted companions. Its object is reused while the other27 owners compile
once. All272 complete functions,4,655 actual code bindings,232 full literal
carriers and the12-byte startup scope table/two parent-code bindings compare
together. All251 prior exacts survive.270 code identities are unchanged; PCX
changes digest but stays979/862 bytes with851 differences. Every new object is
installed together with its actual private-source producer and byte-identical
canonical input map; no selective old/new object mix is adopted.

One incremental native build and the two existing owner oracles pass:1,869
resource cases, including769 lookups/768 draws and99 PCX cases, plus1,266 UI
cases, including216 each measurement/plain/centered text. These exercise all
font byte values, three supplied font banks, high bytes and embedded NULs.
No full replay, VC4 delivery relink or game run follows. The native library is
`3c9713bc4dccfc12aaf354d19272e99722ee952e46adbeabcaa9b91d450b579c`.

Accepted totals become392 exact functions/83,974 code bytes/244 metadata bytes;
all270 authored entries remain source-present:247 exact and23 candidates.
Private complete inputs, objects, independent reviews, rollback archive,
comparison/native receipts and current authored coverage are retained under
`.analysis/glyph-char-cohort-20261020/`. Process Evidence is
`ev_aa3e0c46b9db6a71d571d3acfe138070db36fac9c065fab0225b73167539fa80`
(resource gate), `ev_bd8b4935cfd77631d94a3da1a8db14fa528d79791981740f716b101f68bdf6fe`
(complete closure), and `ev_cca13c7e700f19d72338bcd656881d8ad9b9ca826a4634415c39eb3af7bfd53e`
(native checks). The latter two retain complete terminal output but reach their
32-sample process limit; compiler/command return codes are explicitly recorded,
not inferred from complete child-process sampling.

Cleanup archives and member-size/hash verifies149 private expanded inputs,
objects, logs and helpers before deleting those copies. The identical8.4MiB tool
catalog shares an existing immutable carrier. Net allocated release is9,699,328
bytes before the journal; all current compiler/native products and useful caches,
unique evidence and the verified118-member rollback archive remain available.

## Earlier explicit-signed restoration

The bank loader reads exactly one byte at `0x4046EE..0x4046FB` and stores it at
sprite offset `0x24` at `0x40485F`. Glyph lookup then uses paired signed reads:
`MOVSX` for the stored code at `0x404E8E` and the incoming byte at `0x404E92`.
Measurement likewise sign-extends the sprite and text bytes at `0x405040` and
`0x40504A`. Explicit signed types preserve this contract even when a host's plain
`char` is unsigned.

The earlier unsigned-code diagnostic loses the accepted glyph search. Combined with
SDK descriptor fields it makes ordinary blit and glyph drawing exact, but loses
search and stretch. Explicit signed codes with SDK fields still lose those two
companions. These three stages are rejected. The selected explicit signed model
uses the current descriptor and stretch contracts; every existing exact survives.

At that checkpoint, twenty-six matching recipes preserve **213 complete functions / 56,151
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
