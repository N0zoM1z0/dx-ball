# Exact typed list initialization

The seven default constructors in `src/list_initializers.cpp` initialize the
nine canonical global list instances. Each original entry has a complete
64-byte extent: ECX supplies `this`, the body clears offsets 0, 4, 8 and 12,
returns `this` in EAX, and uses a plain return. The first three members retain
the observed `current`, `first`, `last` order. The fourth is an observed 32-bit
slot named `unclassified_0c`; its meaning and signedness remain unknown.
It is not asserted to be a count, pointer or alignment padding.

One shared layout and ordinary out-of-line C++ default constructor are used by
the native, MinGW and VC4 builds. C consumers see the same data members; C++
consumers also see the constructor declaration. No selected implementation,
fake argument, synthetic local, copied instruction or assembly is used.

## Constructor and root evidence

The target is English DX-Ball v1.07, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
REA 4.1.0 with Ghidra 12.1.4 supplied 42 bounded requests, reproduced by
`config/rea-list-layout.json`. Forty added distinct Evidence records; two
reused existing records. The saved snapshot contains 427 unique records.
The earlier projectile-constructor dossier was reused separately.
Ghidra's VS98 `CReObject` library-name heuristic does not establish source names
or ownership; the recovered names describe their observed consumers.

| Maintained type | Original entry | Canonical roots | REA Evidence |
| --- | --- | --- | --- |
| `DxBallProjectileList` | `0x0040F200` | `0x43A898` | `ev_b6b7058603c40a5660d7f6e56bcdbd51577a98c443f02f0d809abd5cbd93442b` |
| `DxBallBallList` | `0x0040F260` | `0x43A8B8, 0x43AAA8` | `ev_d8059a5e978ea90095e0a68a15c9a42a3f29743e6afdec1910d55f1a1ed64a30` |
| `DxBallBrickEffectList` | `0x0040F2E0` | `0x43FA98` | `ev_4c70e3fe80ab974d098cab9325ef992fa17cd91673e16226da1ac0594e4d0ecb` |
| `DxBallExplosionList` | `0x0040F340` | `0x43F8E0, 0x43FAA8` | `ev_fe484bbd5aadbe9ee7cc140b5604d1d2498c8120440abd53fdd9170b2e2cf1a3` |
| `DxBallBonusList` | `0x0040F3C0` | `0x43FAC8` | `ev_b5f0c5be8fc9a36f9d32691398afa51bb9136952688adaffda95075a6c4e5b5b` |
| `DxBallParticleList` | `0x0040F420` | `0x43A868` | `ev_ed92e50fec0a620556ebc2933dad8fdfcd70dfaa6f950b89a5f0571c159974f4` |
| `DxBallFireEffectList` | `0x0040F480` | `0x43A8E0` | `ev_bea3a0a3b6f7a32b62b939dbfa7a506f1d52349463e1466de3e8120f6c30caed` |

All seven complete VC4 COMDAT emissions matched with zero differences in the
private proposal comparison, 448 code bytes in total, without relocations or
exception metadata. The configured exact units use the same complete extents;
the stable grouped cold replay accepts all seven alongside the prior 63 units,
70 complete exact units / 9,250 code bytes. The prior 136 bytes of attached
exception metadata remain matched outside that code total.

A bounded private probe called each unmodified original constructor and its
complete VC4 emission with ECX pointing to guarded, nonzero storage. All four
words became zero, guards remained unchanged, EAX returned the object address,
and stack/register checks passed. The corresponding native placement-new
probe preserved guards and natural trailing host padding. Nine canonical
startup instances contained zero pointers and the zero fourth word. These
seven private cases and nine startup observations do not add semantic-acceptance
rows, fixture-matrix cases, or whole-game fidelity claims.

## Compiler-generated stages

The original outer initializers at `0x40F0C0`, `0x40F0E0`, `0x40F100`,
`0x40F120`, `0x40F140`, `0x40F160`, `0x40F180`, `0x40F1A0`, `0x40F1C0`
call the per-object wrappers at `0x40F460`, `0x40F400`, `0x40F3A0`,
`0x40F380`, `0x40F320`, `0x40F2C0`, `0x40F2A0`, `0x40F240`, `0x40F1E0`,
respectively. Each 21-byte outer stage calls a 26-byte wrapper, which binds a
canonical root and invokes the typed constructor. Ordinary global definitions
cause VC4 to emit this two-stage pattern. The 18 entries are classified as
`compiler_generated` in the origin ledger; they are not separate authored
functions, source-present additions, or accepted exact units.

Eight pairs (16 complete functions, 376 bytes) also matched in a private
comparison after every root/call relocation was mapped. Their bytes remain
outside the exact-code ledger. The embedded explosion instance is owned by
`dxball_board_storage`, whose reconstructed aggregate contains the list as a
member. VC4 naturally emits a 39-byte aggregate constructor and calls that
member constructor. That helper has no attested original address, so its two
initializer stages were excluded from the wrapper comparison. The original
aggregate declaration and complete startup graph have not been recovered;
no exact graph/layout claim or invented helper binding is made.

## Storage boundary

At i686 offset 20008, `DxBallBoardStorage.explosions` previously exposed three
pointers plus an adjacent four-byte unclassified request tail. The constructor
establishes that the four bytes at original address `0x43F8EC` belong to this
list's fourth slot. The outer tail is therefore absorbed into the actual list
member. Whole storage size 20432 and offsets 0, 20000, 20008, 20024 and 20032
remain unchanged on i686. This preserves the overlapping board-50 raw-copy
contract, including the mutable fourth word.

Native 64-bit lists occupy 32 bytes with the fourth word at offset 24 and four
bytes of natural trailing alignment. Native board-storage metadata now reports
`[0, 20000, 20008, 20040, 20048, 20448]`; accessors derive these offsets from
the emitted metadata. Existing native board-copy cases cover indices 0–49.
Complete original-width terminal transport is checked by the existing i686
storage test, not inferred from the native host layout.

Direct xrefs to each of the nine literal root-plus-12 addresses were empty in
the bounded REA query. That does not exclude register-relative access or raw
storage transport. Reused append/removal consumer dossiers observe the three
pointer fields; no semantic meaning is assigned to the fourth word.

The private failed `={}` aggregate-initializer proposal, final plain global
definitions, frozen inputs, compiler logs, complete comparison and behavioral
probe are retained separately. The final source uses normal default
initialization, compatible with VC4. The authored-function denominator and the
95% complete-source objective remain unresolved.

## Accepted checkpoint

All 22 existing owner scripts passed once with 265 frozen inputs against the
strict native Debug product. The complete cold batch passed all 70 exact units;
the existing 14 exact-oracle rejection/acceptance checks passed. MinGW and full
legacy inspector/game builds passed. Both compilers' existing Windows ABI
checks passed with 16-byte projectile/fire lists. The existing i686 storage
comparison passed 459 full-image cases, including nine terminal board-50 cases.
No test matrix or direct-case count was expanded.

Tracking now records 272 source-present entries (260 application / 12 runtime),
247 scoped direct entries, 112,273 distinct direct cases and 70 exact units.
The 235 affected existing application semantic closures were refreshed without
changing counts or scopes; runtime closures were unchanged. Origins comprise
260 authored, 17 runtime dependencies, 18 compiler-generated initializer stages
and 233 unknown entries. Complete source coverage is not inferred from those
provisional inventory categories.
