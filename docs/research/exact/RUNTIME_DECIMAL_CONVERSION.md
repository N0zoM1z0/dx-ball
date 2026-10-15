# Decimal conversion source

Four recovered bodies cover numeric digits to an extended record, the
seven-argument parser, packed multiplication and decimal scaling. Scaling is
now exact; the other three retain complete nonexact comparisons below.

| Candidate | Current/original bytes | Differences |
| --- | ---: | ---: |
| Numeric digits | 232/232 | 20 |
| Parser and embedded tables | 1851/1871 | 1662 |
| Multiplication | 678/678 | 21 |
| Decimal scaling | 123/123 | 0 |

Scaling restores the typed12-byte table cursor: initialize eight records before
the selected table, then advance seven records per three-bit exponent group.
Original relocations and consumers establish the96-byte bias/84-byte steps.
This replaces the numeric-address substitution and closes all123 bytes/47
instructions/three actual bindings, including both MOV-immediate root loads.
Original pre-array pointer formation is retained; defined modern-C/native runtime
behavior remains open for porting. Both complete29-record arrays and the700-byte
carrier remain exact. Parser and multiplication byte results are unchanged, as
are all360 preceding exacts and88 other candidates. One VC4/native/i686 set,
retained REA/full CRT, no runtime tests. Current361 exacts/75,408 code bytes/88
candidates. Receipt:
`.analysis/decimal-original-table-pointers-20261015/verification.json`.

Multiplication now initializes the product before capturing operand exponents
and establishes the accumulator only inside the positive-count path. Its
underflow test uses the original `<= 0x3fbf` cutoff. This reduces103 differences
to21 while retaining678 bytes and all three actual call relocations. The
remaining differences are two commuted SIB operand pairs and the scheduling
of carry-zero stores against the next comparisons; the body is not exact.
Parser/scaling byte results and all355 exacts remain unchanged. One recovery
compiler set and one formatting-only set have identical complete results;
both include native/i686 compilation. The selected private product is reused
through identical canonical inputs. Retained REA and the complete pinned
`tenpow.obj` section are reused, with no runtime/game checks. Receipt:
`.analysis/multiply-original-initialization-phases-20261015/verification.json`.

The parser preserves sign/point/exponent rollback, `D/E` markers, optional
implicit exponents and all seven parameters. It stores up to 25 digits, then
tests and increments retained digit23 before reducing the count to24. This
original rounding behavior is not replaced with a modern conversion algorithm.
Output fields become live only after parsing. Numeric conversion keeps the
aggregate snapshot and captured digit read before clearing its upper words.
Multiplication preserves five diagonal sums, packed x86 word access and the
original guard/sticky handling. Scaling retains the original biased pointer
state described above rather than replacing it with integer addresses.

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

The next continuation restores the coarse shift's middle-limb carry accumulator
and OR direction, reducing numeric conversion to 20 differences. The exact
addition companion is preserved. See [the current source note](RUNTIME_FILE_MODES.md).

The multiplication continuation restores the independent product byte cursor,
relative operand byte cursors and positive-count entry before the descending
count loop. Product position is initialized only after the early exits and
advances two bytes before the diagonal ordinal. Carry uses that same byte
position directly, without an unnecessary half-index mask. Numeric operand
cursors may end negative; no before-array pointer is formed. The original and
current bodies now both contain678 bytes, with446 full-span differences instead
of708/666; this is not exact. All three actual call relocations are included.

The unchanged parser source emits four commuted equality comparisons and a
three-register output permutation in this compiler context. Internal definition
offsets, branches and embedded tables are preserved; its full comparison changes
1661 to1662. Scaling remains133/123/127. Three VC4 compilations and one native/i686
set; retained REA reused, no runtime tests. All336 exact producers,110 other
candidates and249 semantic rows stay unchanged. Totals457 source/336 exact/
69,846 code bytes/113 candidates. Receipt:
`.analysis/multiply-product-cursor-20261014/verification.json`.

The next checkpoint captures both full input exponent words before extracting
the sign and masking their magnitudes. Sticky state is read in each consuming
branch, rather than hoisted before the exponent decrement. The raw-exponent
stage gives672/678/316; restoring both sticky read sites gives678/678/104 with
the original28-byte frame and all three call bindings. The body remains nonexact.
The parser keeps1851/1871/1662; its low/high output registers interchange, with
unchanged internal definition offsets, branches and tables. Scaling is unchanged.
Two VC4 stages and one native/i686 set; no runtime tests. All336 exacts,110 other
candidates and249 semantic rows are preserved. Receipt:
`.analysis/multiply-exponent-snapshot-20261014/verification.json`.

The earlier scaling model advances a native-width numeric table cursor by84 bytes, initially
biased96 bytes before the table. Only live power positions become pointers;
the pre-array position is never materialized as a C pointer. This restores the
original group state and improves133/123/127 to125/123/115. All47 original/current
instructions correspond, including branch ordinals and all three bindings.
Only two MOV-immediate5 versus LEA-absolute6 address loads differ. Split root
capture leaves125/115 unchanged; pointer/address union149/146 is rejected.

The shared include/compiler context commutes two multiplication SIB sums and
its final sign/exponent OR reads; all other raw body bytes are unchanged,
with678/103 rather than678/104. Parser1851/1662 and all tables remain. Three VC4
stages and one selected native/i686 set; no runtime tests, new exacts or new
semantic acceptance. All336 exacts/110 other candidates/249 semantic rows remain.
Receipt: `.analysis/decimal-power-address-cursor-20261014/verification.json`.
