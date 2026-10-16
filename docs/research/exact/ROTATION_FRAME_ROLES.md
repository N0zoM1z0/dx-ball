# Rotation renderer frame roles

The later [pixel-address recovery](ROTATION_PIXEL_ADDRESS.md) restores two
integer offset/add-base orders without changing the frame or totals below.
Its [complete instruction correspondence](ROTATION_PIXEL_ADDRESS.md#complete-renderer-correspondence)
now accounts for all365 instructions under the explicit memory/FP scope; the
two-expression row-add control emits identical code and is closed.

The complete renderer at `0x4026A0` still compares at **1466/1572 bytes with
1466 differing positions**. The October 17 review accounts for all 424 bytes
of both automatic frames. There is no unexplained frame hole to fill. It does
not establish an original record, packing directive, declaration order or
whole-body instruction equivalence.

The retained REA dossier is
`ev_1dfa14e3428cac399a6bc2876da74d5bbc4a5edc8a8e03a6af79783e189daf26`,
operation 03 of `2026-10-07T10-33-32.118Z-interactive-2912559`. The review reuses
that complete 365-instruction listing and decodes the current COFF. Each has
150 instructions referencing the frame. Every negative displacement belongs
to exactly one observed role, including interior descriptor fields; positive
displacements select the four actual arguments.

## Complete storage coverage

Both 108-byte descriptors retain their established DirectDraw ABI extent.
The other values follow their original loads, stores and consumers. The two
unclassified words are actual zero stores with no later reads, not inferred
padding. Offsets below are signed EBP displacements.

| Role | Bytes | Original | Current |
| --- | ---: | ---: | ---: |
| First unclassified zero | 4 | -344 | -8 |
| Sampled height | 4 | -340 | -100 |
| Source pixel pointer | 4 | -336 | -4 |
| Sampled width | 4 | -332 | -328 |
| Rounded Y / truncated Y | 4 / 4 | -328 / -324 | -360 / -348 |
| Destination descriptor | 108 | -320 | -208 |
| Source column | 4 | -212 | -16 |
| API result | 4 | -208 | -64 |
| Row iterator | 4 | -204 | -68 |
| Column Y step | 8 | -200 | -52 |
| Rounded X / truncated X | 4 / 4 | -192 / -188 | -356 / -344 |
| Column iterator | 4 | -184 | -340 |
| Column X step | 8 | -180 | -44 |
| Origin width copy | 4 | -172 | -12 |
| Row Y / pixel Y | 8 / 8 | -168 / -160 | -88 / -96 |
| Source descriptor | 108 | -152 | -316 |
| Row X / pixel X | 8 / 8 | -44 / -36 | -60 / -80 |
| Destination pixel pointer | 4 | -28 | -352 |
| Row X / Y steps | 8 / 8 | -24 / -16 | -24 / -36 |
| Origin height copy | 4 | -8 | -72 |
| Second unclassified zero | 4 | -4 | -28 |
| First X intermediate double | 8 | -368 | -324 |
| First Y intermediate double | 8 | -400 | -336 |

Eight additional eight-byte slots hold zero-extended integer conversions for
the two centers, four origin dimension operands and two destination bounds.
Together with the first two intermediate doubles, they account for the
original lower 80 bytes. The maintained named intermediates instead consume
16 bytes in the upper region: original **344 + 80**, current **360 + 64**.
Both partitions cover exactly 424 bytes without overlap. Original source
identifiers and whether the intermediate stores came from explicit locals
remain unknown. The earlier nested-cast control already restores those two
lower homes while losing two exact companions; it is not repeated here.

## Closed coordinate-pair model

Original rounded/truncated X occupy adjacent four-byte words, as do the Y
values. A single isolated model represents each pair as an eight-byte record
inside the existing visible-pixel branch. Every field is consumed; expressions,
evaluation order, guards, writes, API calls and shared headers are preserved.
There is no added field, capacity, packing or compiler flag.

One VC4 compilation compares all six complete owner functions, including
actual relocation fields and full literal bytes. Renderer emission remains
1466 bytes and worsens by one differing position to 1467. Height stays
193/191 with 158 differences. Horizontal offset and width lose their matches,
each becoming 261/259 with 223 differences; wrapper and Y offset remain exact.
Reject the pair model. No maintained source or canonical object is replaced.

The unchanged canonical object separately retains four exact functions and
749 code bytes across six complete comparisons. No native fixture, game,
full replay or provider query runs. Totals remain 380 exact functions and 95
complete candidates, including 34 authored candidates.

The complete role/access receipt, original dossier identity, current inputs,
canonical object, rejected source/object and six-function comparisons are
retained under `.analysis/rotation-frame-roles-20261017/`.
