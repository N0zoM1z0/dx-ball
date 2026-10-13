# Exact CRT conversion wrappers and default math callback

Three maintained bodies in `src/runtime_float.c` match complete original
functions: double conversion at `0x41D580` (53 bytes), float conversion at
`0x41D5C0` (53 bytes), and the default math-error callback at `0x41D7C0`
(3 bytes). The total becomes 242 exact functions / 63,304 code bytes / 136
metadata bytes. These are runtime entries; the 34 authored candidates remain.

Both wrappers allocate a twelve-byte CRT extended value and an end pointer,
call the parser with four zero options, then return the selected converter's
full status. Each has two real REL32 bindings at offsets 27 and 45. The float
entry calls `0x41D560`; the double entry calls `0x41D540`. Their conflicting
imported names do not determine the output type. Those two callees already have
separate complete pinned CRT section evidence. The extended value is a raw CRT
record, rather than a host `long double` object.

Original `__umatherr` passes its actual exception record to `0x41D7C0` and
tests the returned EAX before setting errno. Its record and calling convention
corroborate the pinned SDK callback declaration. The callback leaves that
record untouched and returns zero; its complete extent contains only XOR/RET.

REA 6.4 / Ghidra 12.1.4 run
`2026-10-13T08-23-41.020Z-requests-1214458` supplies complete information,
assembly and pseudocode for all four entries and closes normally. Primary
assembly Evidence IDs are
`ev_7dfae3807bc41b299b1aa30dddc6fbd6e97277c90191565ac8ec3ed4ac16c85d`,
`ev_303c82601fd292e68914e354abe283ce69ec89e0f5b06025ea83fa3f44809f4a`,
`ev_e0699a8bbb276b5973b0e86c85d454f3cd3e77c0ade4cd9348df782dc184d7fc`
and caller `ev_b94ec26c821c24f465811ee1f668d3d0226e2c078cc1623e08f20740ed02b64a`.
All records bind the configured original SHA-256.

The first shared C emission matches all 109 bytes. A subsequent prototype-only
correction gives the four unresolved parser options neutral names; its single
new compilation reproduces those matches. Both products and inputs remain in
`.analysis/runtime-conversion-functions-20261013/`. All three complete units,
four relocations and their original instruction boundaries are checked.

This is a standalone recovered CRT module, like the existing termination owner.
It compiles as the same source on native, i686 and VC4 targets. The maintained
game still links its existing runtime. Parser/converter source recovery, portable
backend integration and full exception dispatch remain open; no substitute
parser or execution acceptance is added. Existing game source/products and the
239 earlier accepted compiler inputs are reused unchanged.

Eleven retired comparison/object copies are preserved in verified gzip carriers,
releasing 1,294,336 allocated bytes net of the cleanup receipt. Current products
remain available; the archived raw copies can be recovered from their carriers.
