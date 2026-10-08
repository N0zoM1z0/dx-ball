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
