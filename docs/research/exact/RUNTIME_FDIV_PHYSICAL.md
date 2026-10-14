# Exact physical FDIV probe

The whole 79-byte function at 0x00418C00 matches the pinned LIBC testfdiv
member with no relocations or attached metadata. REA assembly evidence:
`ev_fd7dbe8500e00827d3f0d41acaf93ee6476c05a4f3906e7999f2e5a4b303cc00`.
Ghidra's folded return-zero pseudocode omits the physical processor test;
the complete instructions are the authority for this source restoration.

The source supplies the already-declared `_ms_p5_test_fdiv` API. Real volatile
operands prevent constant folding of `4195835 - (4195835 / 3145727) * 3145727`.
Only the residual is materialized as binary64. Return 1 preserves the original
carry-bit threshold, including unordered status. No control word is changed.
VC4 `/QIfdiv-` keeps the division unpatched; native/i686 use x87 math and retain
intermediate precision. No hardware/affinity or game execution was performed.

Independent locals emit 79 bytes with eight address differences. The three
coupled roles have observed offsets 0/8/16 in a 24-byte probe record; recovering
that consumed record produces all 79 bytes with zero differences. Two complete
VC4/native/i686 compilation sets ran. All 316 old exacts and 106 candidates
retain unchanged source/product hashes. Receipts and unique trials are under
`.analysis/runtime-fdiv-physical-20261014/`.

The preceding member-call exploration is rejected, not published source:
VC4 reserves explicit thiscall syntax, while a member-pointer receiver changes
the pinned raw-address API and misses tail transfer. Three private source
attempts and six direct REA records remain under
`.analysis/runtime-cpp-members-20261014/`; no bridge acceptance is claimed.
