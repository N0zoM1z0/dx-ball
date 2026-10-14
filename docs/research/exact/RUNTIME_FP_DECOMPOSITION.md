# Floating decomposition and exception entries

Six complete source bodies now cover decomposition, classification, integer
parity and single-argument exception dispatch. The187-byte exception entry and
79-byte quiet-NaN entry match completely after every actual relocation.

The caller's IEEE record is88 bytes, established by the pinned SDK and all
actual accesses. Operand2 validity is a named bitfield assignment, not a read of
an uninitialized integer. The raising boundary fills the other named fields;
unobserved padding is not invented initialized state. Genuine rounding, raw
control, exception handling and raising bodies remain external dependencies.

User matherr copies all three original binary64 representations, allows a
callback to replace the result, restores raw control before calling it and
preserves unknown-name fallback. The27 catalog names are now writable borrowed
arrays, matching their original storage and the callback's char-pointer API.
All216 table bytes,134 text bytes and27 actual relocations still match.
The matherr.obj default marker is9876, not zero; its full4 bytes are restored in
the existing default-callback owner.

Remaining candidates: user error174/174 bytes with28 differences, decomposition
209/238 with192, classification161/162 with148, and integer type154/127 with141.
Integer classification explicitly preserves unordered acceptance and both
actual rounding calls on NaNs; ordinary modern NaN equality would change it.
The full eight-byte half constant is attested at its source-pool offset.

Fifteen recompiled preceding exacts are preserved. Five of six preceding
recompiled candidates are unchanged; the converter remains459 bytes but changes
94 to95 differences after adding the genuine marker. Other287 exact and85
candidate producers are reused unchanged. Only scoped VC4/native/i686 compilation
and complete comparisons ran; no runtime tests or game builds.
Evidence/products: `.analysis/runtime-fp-decomposition-20261014/`; one closed
17-record REA session. Current source408/exact304/68,066 code bytes/136 metadata,
candidates95 (34 authored/61 runtime). Hardware and game integration remain open.

The later whole-representation copy checkpoint reduces user matherr's41
differences to28 without changing its174-byte body,32-byte record frame or six
relocations. Each argument/result copy now captures the complete typed two-word
representation, without floating conversion or extra storage. Both187-byte and
79-byte companion exacts remain unchanged. Retained REA assembly
`ev_95943a9002f12f85b1d17855e0f5d023b69a31798acc9898cce8a9fd7c9fde93`
and the complete pinned `__umatherr` section supply the original. One
VC4/native/i686 compilation set and full owner comparisons; no runtime tests.
Global source457/exact336/code69,846/candidates113 and249 semantic rows remain
unchanged. Receipt: `.analysis/math-error-representation-20261014/verification.json`.
