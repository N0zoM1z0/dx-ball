# Aligned string-length scanning

The entire 119-byte strlen at 0x00417DF0 matches the pinned LIBC member, without
relocations. Direct REA assembly evidence:
`ev_91fdf06bc4bff27de625215b652c30801c7c197e0b1e84c86890fd856983f32c`.
The decompiler's pointer return type and wide prefix read are incorrect;
actual instructions return a length and read prefix bytes individually.

Shared C retains the byte alignment prefix and unsigned 32-bit zero-byte test
`((word + 0x7EFEFEFF) ^ ~word) & 0x81010100`. A candidate is read again and its
four bytes tested in order, including false candidates without a terminator.
Volatile word views preserve those actual reads; GNU may_alias supplies the
byte-storage view. The original aligned-word footprint can read beyond NUL
within its word. Those bytes must be readable; no larger buffer is allocated
or caller capacity invented by the source.

One VC4 compilation emits 102/119 bytes with 112 differences; the complete
function remains a candidate. Native and i686 strict compilation succeeded.
No source-name/layout/operand permutations or runtime/game tests were run.
All 334 old exacts, 107 candidates and 249 semantic rows preserve their inputs.
Frozen source/products and a closed two-record REA session are retained under
`.analysis/runtime-string-length-20261014/`.
