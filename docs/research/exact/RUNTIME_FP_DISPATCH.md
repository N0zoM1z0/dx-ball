# Floating exception dispatch

The complete local CRT sections and retained/fresh REA evidence establish
raise876 and handle704. Raise includes18 switch/alignment bytes beyond its old
858-byte inventory entry. Current source emits880/328 and704/21 respectively;
both remain candidates, with every actual relocation and self-relative case
binding compared across the whole original extent.

Handling now separates the decompose output slot, adjusted exponent and shift
countdown. Positive/unordered overflow branches precede negative stores; the
nonzero underflow path precedes its zero fallback. Explicit inexact writes and
ordered zero stores restore the original207 instructions and704-byte extent.
The full difference count improves436 to21. All operands, calls and branch
targets agree; four adjacent instruction-scheduling swaps remain nonexact.
Raising's complete byte result and all40 initialized constant bytes are unchanged.
Four VC4/native/i686 sets cover flag writes, exponent lifetimes, result branches
and the final inexact phase. The selected private product is reused through
identical canonical inputs. All355 exacts and93 other candidate byte results
remain; retained REA/full CRT are reused, with no runtime tests. Receipt:
`.analysis/fp-underflow-original-flag-lifetimes-20261015/verification.json`.

The implementations retain cause/code priority, raw status capture and clearing,
the native-width OS pointer payload, callback-modified enable/rounding/precision
and result writeback. Precision deliberately retains the original0xfffff3ff
rounding-bit clear mask. Handling preserves its single primary-exception choice,
rounding-directed overflow values,1536 exponent offset, sticky shifted bits and
the separate inexact phase. Raising requires a nonzero unhandled IEEE cause,
as established by its original caller; no empty-cause exception code is invented.

All40 util.obj constant bytes match: infinity, indefinite, maximum, minimum and
minus zero. The integer-initialized/native-double union view keeps real double
alignment. IEEE cause/enable/status expose their actual complete-word reset and
SDK bitfield views without altering the88-byte record. Both affected preceding
exacts187/79 and the existing174/41 candidate remain unchanged.

The explicit result-cursor trial worsens328 to346 differences and is reverted;
its final source hash matches the retained earlier producer. Source410/exact304/
68,066 code bytes/136 metadata, candidates97 (34 authored/63 runtime). Other302
exact and94 candidate producers are reused unchanged. Only scoped VC4/native/
i686 compilation and full comparisons ran; no runtime tests or game builds.
One closed five-record REA session supplements retained raising pseudocode.
Evidence/products: `.analysis/runtime-fp-dispatch-20261014/`. Physical x87 helper
bodies and OS/game integration remain open; this checkpoint adds no exact claim.
