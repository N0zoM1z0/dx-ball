# Complete rectangle collision fallback

`src/geometry.c` restores the complete control flow of the integer-center
collision function at `0x402100`. The original first compares cached absolute
center distances inclusively against the combined half-width and half-height.
On failure it independently calls `abs` again for X, then conditionally for Y,
and makes strict comparisons against the first rectangle's own half-dimensions.
The maintained source previously returned a combined boolean using the two
cached distances. It now retains the original repeated expressions and nested
return branches, including the original comparison operand order.

These predicates intentionally differ from conventional edge intersection.
The existing touching, odd-size and inverted-rectangle cases remain unchanged.
Integer subtraction, center arithmetic and `abs` must remain representable;
this recovery does not broaden the declared overflow domain.

## Complete binary evidence

The retained REA dossier from closed run
`2026-10-07T07-26-59.211Z-rea-bonus-dependencies-2331079`,
`00-analyze_function.json`, is Evidence
`ev_38098a89555f0662ce749fc26b6fe5b78bea2da42431812abbdbf888c320c2cd`.
It contains 319 owned instruction bytes within the complete 329-byte span:
`0x402100..0x4021B4`, `0x4021BA..0x402237` and `0x40223D..0x402248`.
Its instructions identify four ordinary CRT `abs` calls to `0x416780` and
the separate successful and failed return paths.

One new REA 6.3.0 read covers all 329 bytes, Evidence
`ev_6d9765478c63299676c89c2efc5bea93b134606a61edd8d3f818a72efde2c404`,
closed run `2026-10-10T20-13-12.423Z-requests-1133236`.
All bytes agree with the pinned original PE. The previously unowned five-byte
intervals are `e9 8a 00 00 00` at `0x4021B5` and `e9 07 00 00 00` at
`0x402238`. Opcode/displacement arithmetic identifies both as jumps to the
common epilogue at `0x402244`. This is an inference from REA's bytes, not
provider Listing decoding or an observation that those unreachable jumps run.
Both intervals remain included in the full comparison.

## One stable compilation

The pinned VC4 recipe is unchanged: `/Od /Ob0 /Oi- /Oy- /Gd /MT /Gy`.
One geometry compilation consumes six recursively included project files,
covered by the existing 27 declared inputs. No header changes, source profiles,
copied code, padding, fake locals or declaration/name/layout permutations are
used. The resulting collision body is 329 bytes, with four explicit REL32
bindings at offsets 77, 119, 218 and 276 to `0x416780`.

The full relocated comparison has **22 differing bytes** and remains a
candidate. An instruction-level check covers every byte of both 329-byte
bodies: instruction addresses, sizes, mnemonics and register/immediate operands
agree; differing operands are negative EBP local displacements. Observed
displacement pairs do not establish a unique one-to-one source-local or storage
lifetime mapping. They are not masked or tuned away.

The shared source's complete 109-byte point-angle unit remains exact after
all seven relocations and its full constants are checked. The complete
130-byte point-distance comparison retains 52 differences and remains a
candidate. Generated literal labels refresh only at identical relocation
offset/type/addend with unchanged complete literal contents.

## Affected checks and products

The unchanged maintained power-up Oracle supplies exactly 8,000 rectangle
vectors. A private AST selector keeps the existing seed, vector loop, call and
full return/state/queue/event assertions, selecting no other owner loops.
Current Native passes against the unchanged original x86 body. The actual
relocated VC4 body passes the same vectors against that current Native product,
using the original `abs` dependency and all four actual relocation bindings.
The original code image stays immutable in both selections. These are bounded
arithmetic cases, not new direct-case ledger counts or a full power-up replay.

Native and MinGW each rebuild only geometry and relink their affected products.
VC4 links one matching geometry object with 34 identity-verified unchanged
objects; there is no additional legacy production compilation. Resource and
SDK import products are verified and reused. Current VC4 and MinGW core PE
imports retain genuine `DirectSoundCreate`/`DirectDrawCreate` and have no parser
warnings.

- Native SHA-256:
  `c3bca255028402cdaf28271eb5ab9be04fa008f3bb19d2828c0fb36e0b729901`.
- VC4 EXE SHA-256:
  `be55678a6ea2bcfacf4542a56a2258b76b5e4d7be214b059b9cc4f1be8eb2ff1`.
- MinGW game SHA-256:
  `8e9c8834fb954d3d569dd0efa72ade2c45773df9856fc08c8d07ea62d4781666`.

Private helpers, compiler/source/input receipts, complete comparisons, emitted
execution bindings and REA reuse/response metrics are in
`.analysis/exact-rectangle-collision/`. Seal:
`.analysis/checkpoints/rectangle-collision-283-171/sha256.json`.
The 171 accepted exact receipts and all current object/input identities are
verified without a full replay. Historical semantic input hashes refresh for
235 affected rows while preserving their earlier cases and scopes.

There is no new Wine episode, synchronized game trajectory or physical
driver/audio claim for these product hashes. The
[recorded entity-play episode](../CURRENT_ENTITY_PLAY.md) remains evidence for
its earlier executable. Totals remain 283 source-present entries, 171 exact
functions /30,744 code bytes /136 metadata bytes and 247 scoped semantic rows.
Complete reconstruction remains unproven.
