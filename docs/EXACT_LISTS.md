# Ball cloning and typed list cleanup

This batch restores the complete ball-cloning source emission and five missing
typed cleanup entries, then connects them to the maintained total-cleanup
routine. The accepted checkpoint has **252 source-present entries / 247 directly
validated entries / 112,273 distinct direct cases / 45 exact units / 4,992 bytes**.
The frozen owner batch and grouped cold replay pass. The six new exact units
add 877 bytes; five also add independent source mappings.
The same C and natural pointer layouts serve native, MinGW and pinned VC4.

| Entry | Maintained unit | Complete bytes | Retained REA Evidence |
| --- | --- | ---: | --- |
| `0x414DF0` | clone-balls | 637 | `ev_82922c280cc6891fafb4d3e9d135352e6b4541f3309f61a8e6c06abf7a615da8` |
| `0x416510` | clear-fire-effect-list | 48 | `ev_9079032d5d51ed50f8093cb9c0029da2fc1ccfafa4a94690b926f6cc5097cf94` |
| `0x416540` | clear-particle-list | 48 | `ev_0de8921eaa08a2e03e602ed2479edd222e956f905fd63160b548ae3b6d2bd6bc` |
| `0x416570` | clear-bonus-list | 48 | `ev_046d2688735634355139cd40311164ecef5678d0c72c5d709a650561ada2fa7d` |
| `0x4165A0` | clear-brick-effect-list | 48 | `ev_77d66ee7458edb5c8504d596db1bf86909164dcf8d8feb0ab85101e184748750` |
| `0x4165D0` | clear-projectile-list | 48 | `ev_d03e455e9b512ca03c865a482daeddf5b5f12289f947ee04e038553a8e3c9765` |

The clone dossier is reused from its closed session. Five bounded
`analyze_function` operations in `config/rea-clear-lists.json` obtain the
previously unreviewed cleanup entries with the pinned REA/Ghidra provider.
Each body is one contiguous range ending in `ret`; none needs a gap excluded
from comparison. Explicit close preserves the cumulative Evidence snapshot.

The 637-byte original clone function has no local variables or copy-helper
calls. It writes thirteen payload fields twice, first from active balls to a
temporary list, then from that list to newly allocated active nodes. Both
blocks copy sprite before x/y, previous x/y, dx/dy, angle, speed, bounce count,
attachment state, attachment offset and wall-bounce count. Each assignment
reloads the source and destination current roots. The two allocation-owned
links stay intact. The maintained copy helper previously emitted two calls and
reduced this entry to 233 bytes; explicit typed assignments recover the observed
payload sequence without struct copies or a forced-inline profile.

Only attachment state exactly one reduces clone speed, with a floor of four.
Reflection uses `dx = dx * -1`. VC4 emits a saved value, doubled value,
subtraction and negation for that ordinary multiplication, reproducing the
original sequence. Subtracting twice dx produced different instructions;
those unsuccessful compiler experiments are retained privately and are not
the maintained source. The accepted expression retains the existing bounded
signed-state precondition and does not introduce a doubling overflow into C.
The temporary list is traversed and cleared through the existing maintained
ball owners; count is incremented before each append into the active list.

Each cleanup entry receives its typed list owner in ECX, spills that real
parameter and repeatedly calls its maintained removal entry until it returns
zero. Cleanup returns one even when the initial current cursor is null.
It does not begin iteration from first or reset unrelated counters. Thus a
null current with nonnull first/last is left as it was. Existing removal
semantics choose next, or previous at the tail, and release only removed nodes.
The corresponding delete entries are `0x413790`, `0x414B30`, `0x4147C0`,
`0x412A50` and `0x4134D0`. Typed game roots and deletion targets, corroborated
by the total-cleanup caller, support the authored game-owner inference.
This inference does not recover historical class or variable names.

All relocation positions, types, symbols, addends and target addresses are
explicit in `config/match-units.toml`. Added declarations renumber three
compiler literal names: pan uses `$T1152`/`$T1153`, and board I/O uses
`$SG756`/`$SG760`. Their contents and original targets are independently
checked before refreshing the bindings. No relocation or byte is masked.

The existing 40 direct clone cases and ten total-cleanup cases are reused.
The five new leaf mappings have complete-byte acceptance and transitive
cleanup coverage; no separate direct-case counts or semantic rows are
invented. All game-source input closures are frozen for one run of the 22
existing owner scripts before semantic hashes are refreshed. One grouped
cold replay validates the complete emitted COMDATs for all 45 exact units.
No fixtures, test scripts or campaign observations are added.

## Total-cleanup candidate

The reused caller dossier
`ev_ec6f209a3116f545cd612d3e34e16b25c30d54c60708744e4d82883fb47b2eaa`
provides the complete 106-byte original body at `0x4164A0`. It calls cleanup
for projectiles, active balls, brick effects, explosions, bonuses, particles,
temporary balls, explosive-source scratch and fire effects in that order.
The maintained source now makes those typed calls directly and retains the
explicit terminal return. Convenience wrappers remain for source callers and
carry no additional original entry claims.

Its current emission is 107 bytes with 59 unmasked differences. The explosion
root is a member of the reviewed shared board-storage owner; VC4 emits a
six-byte `lea` where the original has a five-byte `mov` immediate. The
explicit mapping resolves board-storage root `0x43AAB8` plus addend 20008 to
`0x43F8E0`. The complete 107-byte section is compared against all 106 original
bytes and stays under candidates. Storage is not split or given another
profile-selected representation to remove this difference.

The >=95% complete-source objective remains open. The provisional inventory
still has 271 unknown origins and five identified runtime dependencies without
maintained source; those counts are not a proven full authored denominator.
This batch establishes six specific emissions and five additional source
mappings, not a whole-game or complete dependency fidelity claim.
