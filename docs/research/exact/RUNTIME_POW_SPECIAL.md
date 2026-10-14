# Pow special-value handling

The complete 584-byte helper at 0x0041E2F0 matches the pinned `powhlp.c`
LIBC member after all 16 relocations. Direct REA evidence:
`ev_c15da8ce00469c2032f0db1a686150448877eea226aba37548580c7aa7d2b1ca`.

Shared C source handles infinite exponents and bases, preserving the original
x87 unordered/carry branches, genuine integer parity classification and signed
infinity/zero results. Finite/finite leaves output untouched. Return 1 denotes
indefinite output for unit magnitude with infinite exponent, not handled status.

Direct assignment produces 567/584 bytes with 140 differences; materialized
binary64 plus bulk memcpy gives 586/120. Separate high/low word transport yields
584/8: only destination-pointer/high-word load ordering differs in two blocks.
Typed alias field stores worsen this to 584/32 and are rejected. The eight-
difference source is restored by exact input hashes and its producer is reused.
This remains a candidate, not exact. All 316 exacts and 104 older candidates
retain unchanged inputs and products. Four VC4/native/i686 compilation sets
completed; no runtime/game checks. Products and full comparisons are retained in
`.analysis/runtime-pow-special-20261014/`.
