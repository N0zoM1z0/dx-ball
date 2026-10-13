# Decimal conversion source

Four missing bodies now have maintained source: numeric digits to an extended
record, the seven-argument parser, packed multiplication and decimal scaling.
Source presence is 306; exact totals remain 249 / 63,697 code bytes / 136 metadata.
All ten affected exacts preserve 502 bytes. The 239 other producers are unchanged.

| Candidate | Current/original bytes | Differences |
| --- | ---: | ---: |
| Numeric digits | 232/232 | 21 |
| Parser and embedded tables | 1851/1871 | 1661 |
| Multiplication | 708/678 | 666 |
| Decimal scaling | 133/123 | 127 |

The parser preserves sign/point/exponent rollback, `D/E` markers, optional
implicit exponents and all seven parameters. It stores up to 25 digits, then
tests and increments retained digit23 before reducing the count to24. This
original rounding behavior is not replaced with a modern conversion algorithm.
Output fields become live only after parsing. Numeric conversion keeps the
aggregate snapshot and captured digit read before clearing its upper words.
Multiplication preserves five diagonal sums, packed x86 word access and the
original guard/sticky handling. Scaling uses integer group indices instead of
forming temporary pointers outside the two power arrays.

Both complete 29-record arrays match; their original 700-byte carrier includes
four alignment bytes. Original parser ownership is 1,871 bytes: 1,578 decoded
instruction bytes plus 293 embedded table/alignment bytes. Whole pinned CRT
sections independently agree at all four target addresses. The existing
project parser API name is retained; its pinned CRT symbol is `___strgtold12`.

Closed REA runs `2026-10-13T10-47-40.296Z-requests-1432685` and
`2026-10-13T10-51-34.468Z-multiply-requests-1440271` supply the original bodies.
Assembly Evidence is `ev_7a8b102d547d6d5f0f0bba2267ace9d6e4fbf747d07886e72f76a079b6702fef`,
`ev_2c740590f894740eca79103890cc4d81d72e9c898aef1ad19ea3fa554dbb3ce5`,
`ev_43a99f9bda05d6825175fa7358b51f4098ccf538e1cd825c25d6e4b5190e00a0`
and `ev_384c8cf6f2c8847ca9ae9e649a67140541714c529fc0f86c34b27409b6dae957`.
Power bytes reuse `ev_b739e7f968490a9c85dd91573b9bbbacf7d8361d44ac9c31cd884e82c2395dac`.
Source stages and full comparisons are in `.analysis/runtime-decimal-conversion-20261013/`.
All four owners compile on VC4, native and i686. No runtime tests or game builds
run. Locale dependencies, remaining exact gaps and game integration stay open.
