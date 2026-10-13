# CRT mantissa operations

This note records the preceding checkpoint. The
[iteration and arithmetic continuation](RUNTIME_MANTISSA_LIFETIMES.md) adds two
exacts (131 bytes), raises totals to 249 and supplies three arithmetic bodies.

All seven mantissa helpers and their addition dependency now have maintained
source. Complete comparisons accept tail testing (100 bytes), carry propagation
(99) and three-limb clearing (15), adding 214 exact bytes. Totals become
247 exact functions / 63,566 code bytes / 136 metadata bytes; source presence is
299. The five preceding float exacts preserve 157 bytes and both full format
records. The 34 authored candidates remain open.

`IncMan` returns its final carry in EAX. The original `RoundMan` consumes that
value; the decompiler's void inference is incomplete. Source initializes the
one-bit increment before the signed word calculation, then shifts that same
value and propagates carry toward the most significant limb. Both genuine add
calls and the complete return agree with the original.

Rounding preserves the original tail predicate and captured prior bit position.
An early trial decrements the argument home; source now uses the actual local
position instead. Copying traverses three limbs forwards. Clearing uses the
same bounded iteration and matches all 15 original bytes. Partial-bit shifting
keeps both original writes, followed by descending whole-word movement. Its
complement count explicitly preserves x86 word masking, including a zero
partial shift. Source assumes backed three-limb arrays and the recovered
precision values; no execution acceptance is added.

| Remaining runtime candidate | Current/original bytes | Differences |
| --- | ---: | ---: |
| Rounding | 163/172 | 153 |
| Copying | 29/29 | 5 |
| Zero predicate | 29/29 | 6 |
| Shifting | 174/173 | 135 |
| Addition/carry | 35/35 | 7 |
| Binary conversion | 459/459 | 95 |

The verified CRT archive places addition in `mantold.obj` and the other helpers
in `intrncvt.obj`. Its source therefore lives in the separate
`runtime_mantissa_arithmetic.c` owner, with the same shared ABI header. A private
combined-owner addition match does not become an accepted claim; the actual
separate owner retains seven differences.

REA run `2026-10-13T09-38-37.467Z-requests-1320496` supplies complete information,
pseudocode and assembly for all seven helpers. Run
`2026-10-13T09-43-20.682Z-addition-requests-1329677` supplies the 35-byte addition.
Both close normally and retain the original target digest. Primary accepted
assembly Evidence is `ev_e15c56a167de461f2f45e15a08e653e59d712bcaea9041bc16ba141e234ca02c`,
`ev_ca3848879ba23d873620e513395b2831b6a91520437662c01d975059815a4318`
and `ev_7ef91e7f67bacca4897bb206ae7d880c26686b04c6752f607e9cb1aad1662acf`.
Addition is `ev_7fb248d274c74fd95132e6b08b03197d97bc9e293ce37341c6465e26f99c258c`.
All source stages, full comparisons and actual producers are in
`.analysis/runtime-mantissa-helpers-20261013/`.

Both source owners compile on native, i686 and VC4 targets. Complete comparisons
cover all fourteen functions and actual relocations; the 239 other accepted
producers are reused unchanged. Decimal parsing remains the unresolved source
dependency of this conversion family. Runtime/game integration and remaining
exact gaps stay open. No fixture, runtime test or game build runs.

Final canonical compilation follows an EOF whitespace correction; its complete
comparisons equal the selected emission. Arithmetic and its portable products
are reused with unchanged inputs. Ten retired carriers are preserved as
decompression-SHA256-verified gzip files, releasing 1,298,432 allocated bytes
net of the cleanup receipt. Current products and all source stages remain.
