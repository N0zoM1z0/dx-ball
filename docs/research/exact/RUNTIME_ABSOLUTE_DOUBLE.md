# Exact CRT double absolute value

The entire 229-byte fabs entry at 0x00417660 matches the pinned LIBC member
and all seven genuine call relocations. Direct REA assembly evidence:
`ev_4ad827b0c2312eead9eff692b1558a519a4bf77c46bd24fe5cdb49c4e483f301`.

Shared C preserves temporary x87 control 0x133F, the actual special-value
classifier, positive/negative infinity paths, quiet-NaN callback and signaling-
NaN invalid handling with operation 21. Finite values clear the sign bit through
the complete binary64 representation. Control is restored before loading the
result into x87. Quiet NaN retains original sign/payload behavior rather than
being replaced with a generic intrinsic fabs. All callees are existing real APIs.

The initial ladder produces 229/229 bytes with 130 differences. Explicit category
dispatch reduces this to 18; a real eight-byte binary64 result union, instead
of alias-writing a floating scalar, gives 229/0. Three VC4/native/i686 compile
sets completed; no runtime/game checks. All 333 preceding exacts and 107
candidates retain unchanged inputs/products. Frozen stages and whole comparisons
are under `.analysis/runtime-absolute-double-20261014/`.

The preliminary exponent formatter review confirms its two differences are
commuted suffix additions, with no newly missing operation. No spelling or
layout trial was performed on that unchanged source.
