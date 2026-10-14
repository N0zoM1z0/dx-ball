# Embedded explosion-list initialization

One bounded `/Ob1` compilation permits expansion of the implicit board-storage
constructor. The actual global declaration, aggregate region and embedded
explosion-list member are unchanged. The generated inner stage now calls the
real accepted explosion-list constructor directly, at the proven member offset
20008. Its two actual relocations are completely bound; no original address is
invented for a source-only aggregate constructor.

The outer stage at0x40F140 matches all21 bytes and its inner-stage call. The
inner stage at0x40F320 remains32/26 bytes with21 differences. It is explicitly a
source candidate, not a prefix or exact claim. All58 existing owner exacts are
re-compared with the new product and retain their complete code/data results.
The ordinary-list generator checks are unchanged; a separate strict embedded
generator record verifies the real declaration, member contract, accepted
constructor, candidate inner stage and complete outer call. An exact caller
does not imply its callee is exact or establish whole startup behavior.

Retained original assembly:
`ev_e092d38ff1728d87c66a80a5c957fb81a4c966519c9b88d2f0de687aa2fa660c`
and `ev_fe538a3c09cba424e6108ca9c4cd53235fcc0325909464e5bb7728bc21405730`,
run `2026-10-09T15-09-04.195Z-interactive-1032685`. No provider analysis repeats.
One VC4 compilation and whole comparisons ran, with no source edits, new native
compile, runtime/game tests or hardware execution. All276 other exacts,110
candidates and249 semantic rows preserve their inputs/products/results.

Totals: source455/exact335/code69,718/metadata136, candidates111 including one
compiler-generated candidate; authored270 and all origin counts are unchanged.
The two source-emission entries are not new authored routines. Private receipts
are retained in `.analysis/list-implicit-inline-20261014/verification.json`.
