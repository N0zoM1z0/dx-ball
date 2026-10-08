# Software sprite rotation: investigation in progress

The imported function inventory leaves `0x004026A0` unclassified. Its saved REA
dossier provides a contiguous 1,572-byte body ending at `0x00402CC3`, with
Evidence ID
`ev_1dfa14e3428cac399a6bc2876da74d5bbc4a5edc8a8e03a6af79783e189daf26`.
The complete record is retained in the closed 10-33 interactive run; reusing it
requires no additional Ghidra import. This investigation has not promoted a
function, origin, semantic case or exact unit.

## Observed instructions

The body reads sprite width/height through the established bank at `0x425980`
and selected-bank scalar at `0x421088`. It obtains and locks the active surface
at `0x4265CC`, then obtains and locks the selected sprite's source surface.
Both descriptor requests set size 108 and flags 14. Each lock retries until its
result is zero; no finite failure recovery is established on this edge.

The inferred pseudocode prototype lists three parameters. Instructions read
`[EBP+0x14]` and pass it to the already reviewed sine/cosine helpers, establishing
a fourth stack argument. They add 270 before obtaining the row-direction
coefficients. Pseudocode loses both the fourth argument and that phase offset.
The body converts the first two coordinates through zero-extended 64-bit
integers before floating-point arithmetic.

Nonzero source pixels are considered only when the transformed coordinates
are strictly inside the destination's zero and width/height-minus-one bounds.
Instructions compute biased and unbiased X/Y integers through `__ftol`.
The first write uses biased X and biased Y; when either integer pair differs,
the second write uses the same biased X with unbiased Y. Thus the computed
unbiased X controls a branch without becoming a destination column.
Source traversal advances one byte per pixel and skips pitch padding at each
sprite-row boundary. Unlock order is destination, then source.

The recorded caller is a separate contiguous 40-byte entry at `0x00404280`.
Its wrapper argument order, reference coverage and actual use by game
controllers still need focused REA inspection. The historical call graph's
missing incoming edges do not prove this path is unused.

## Floating-point storage and traversal

The same retained instructions establish separate double stores at
`0x4028AC` and `0x4028FE` for initial X, then `0x40295F` and `0x4029B4` for
initial Y. Let `R64` denote a store to double, `W`/`H` the unsigned sprite
dimensions, and `C`/`S` the already reviewed table-based cosine/sine results.
Using the decoded divisor candidates, the observed sequence is:

```text
first_x = R64(unsigned_center_x - W*C(angle)/2.0)
row_x   = R64(first_x - W*S(angle)/2.0)
first_y = R64(unsigned_center_y + H*S(angle)/2.0)
row_y   = R64(first_y - H*C(angle)/2.046)
```

Both X terms use width. The differing Y divisor and the intermediate stores
are part of the observed sequence; replacing them with a conventional rotation
formula would change behavior. The backing divisor bytes still require the
pending REA read before source acceptance.

Column steps are `C(angle)` and `-S(angle)`; row steps are `C(angle+270)` and
`-S(angle+270)`. Each pixel advances X/Y before transparency and bounds checks.
Each coordinate update and row-origin update stores a double. Source traversal
uses one byte per column and a pitch-minus-width adjustment at the row boundary.
The signed row/column loop tests and unsigned conversions require an explicit
bounded dimension/arithmetic domain in the eventual oracle.

The existing [trig evidence](POWERUPS_OWNER.md) already establishes a useful
boundary: negative multiples of 360 select table entry 360, so cosine(-360)
is 1023/1024 while cosine(360) is one. Rotation tests must retain that difference.
The prepared private differential draft has 344 fixtures covering angle wrap,
multiple banks/slots, unsigned coordinates, rectangular/empty dimensions,
transparent pixels, pitch padding and independent finite destination/source
lock retries. It compares complete destination storage and guards, unchanged
source storage, and ordered surface calls. Only fixture enumeration and Python
syntax have been checked; original execution and C comparison remain pending.

## Work remaining

- Read the original constants at `0x420038..0x420057` through REA, including the
  bias used before integer conversion. The saved division path decodes the
  divisor as 2.046 (`__adj_fdiv_m64` arguments `0x3f7ced91`, `0x40005e35`);
  confirm its backing bytes before accepting maintained source.
- Inspect the wrapper and its references; reconcile the four-argument ABI.
- Recover natural shared C with the observed double-storage boundaries and
  table-based trig, without repairing asymmetric pixel writes or clipping.
- Compare unmodified original execution with full destination buffers, ordered
  descriptor/lock/unlock calls, source bytes, pitch padding and retry scripts.
- Cover angles and negative wrap, borders, zero-key pixels, multiple banks,
  dimensions and unsigned coordinate conversion before semantic promotion.

The full original-board Windows control is a separate live runtime task.
It must finish before acquiring another writable compiler/Ghidra/Wine session.
The four focused requests are prepared in `config/rea-rotation.json`, checked
against the retained REA 4.1.0 catalog. They have not been executed:

```bash
scripts/rea session config/rea-rotation.json
```

Reuse the existing renderer dossier; this batch queries only the missing
constant bytes, wrapper body and references. Save each returned Evidence ID,
body/coverage limitations and the closed session before advancing acceptance.
