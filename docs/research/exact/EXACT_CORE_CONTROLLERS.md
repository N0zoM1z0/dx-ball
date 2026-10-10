# Ball and projectile controller restoration

This batch restores three complete contiguous controller bodies through RET,
3,872 target code bytes in total. Fire-projectiles is the new exact unit;
update-balls and update-projectiles remain complete nonexact candidates.

| Entry | Function | Whole bytes | Saved REA Evidence |
| --- | --- | ---: | --- |
| `0x410770` | `update-balls` | 3223 | `ev_c7fd5e1c178073afb10924d1dbfa6df93f8ba8566533fd41f8dcb8f48b3a92a1` |
| `0x413170` | `update-projectiles` | 328 | `ev_412b7a2d61e8a498417dca7a456838ed290b17317e4af4585d8b936b69b07495` |
| `0x4132c0` | `fire-projectiles` | 321 | `ev_d275b4fccde79ffde5a3244ff97e0be0c15cb85b03419d0c9425acb9c579b1b4` |

Ball updates restore the moving-first branch, distinct reduced/full particle
loops, direct sound/RNG/particle calls, and repeated current-node and sprite
accesses around callbacks. The six source locals are consumed coordinates,
chance, sign and two loop counters. The saved assembly distinguishes six
compiler floating temporaries from those source values. Paddle attachment
retains the repeated width conversion and positive-offset sign branch. Vertical
and horizontal collision branches preserve their separate coordinate reads,
hit responses and bounce counters. Particle arguments preserve the observed
right-to-left RNG evaluation under the verified VC4 compiler and the tested
native compiler; C itself does not specify argument evaluation order.

Projectile updates compute column and row before the offscreen test, consume
the RNG hit vector before each death test, remove before hitting an ordinary
tile, and score the full hit return. A signed-byte tile load restores the saved
MOVSX while retaining the existing byte bank owner and nonzero test. Column
calculation centers the projectile before applying the board offset. Fire
allocation precedes four fresh slot-32 dimension accesses, with distinct
0.425/0.43 floating constants, count increment and real sound calls.

The diagnostic and complete grouped cold emissions match original lengths.
Fire matches all 321 bytes after 31 explicit relocations. Ball/projectile candidates retain
23/8 frame-displacement differences after 276/23 explicit relocations.
Every relocation is applied and compared. Six compiler floating constants
are independently compared with the verified PE at the actual saved operand
addresses. Whole sprite/list/board roots and direct callee owners remain
explicit. Original source spelling and compiler local assignment remain
unproven. No name/declaration search, fake locals, copied machine code,
padding, assembly or source profiles are introduced.

The existing native oracle uses a separate ELF interposer for the three real
sound/RNG symbols. CoreNative receives a byte-identical library copy with a
different inode, verifies its symbol owners, installs inherited callbacks and
then binds the actual copied-image gameplay table. Calls read its current slots.
Unbound, null, self and recursive bindings are rejected. Fresh canonical audits
and standalone sound fixtures retain their own LOCAL image. Importing the
loader performs no compile or symbol loading. The private four-scenario probe
checks both canonical-first and copy-only loading and abort controls.

Prepare the shim before an owner takes the compiler-session lock (the private
CI entry point prepares it automatically):
`scripts/repo-python tests/core_native_loader.py --prepare-only`.
Its cache binds the compiler, flags, loader, resource/session helpers and the
compiler-generated complete project/system header closure. All compilation
uses the existing single-session and CPU limits. The bridge validates these
test boundaries; it does not establish sound/device or whole-game fidelity.

All 22 existing owner scripts pass against 282 frozen inputs and native Debug
SHA-256 `28ecba51925c879a55e52f2fab54c5acc30d692f80d1f027d1f21ed2e75a0d0e`.
Grouped cold replay accepts **101 complete units /
12,548 code bytes + 136 separate metadata bytes**, using twenty-two retained
actual compiler objects. All 100 preceding code/metadata identities remain
unchanged. Existing fourteen rejection controls, strict MinGW and full VC4
builds pass. Unchanged complete raster/rotation compiler recipes and actual
logs justify reuse of the preceding 7,164/1,024 COFF vectors.

Before cold replay, fourteen floating-reference content attestations (six
unique constants) were added to the manifest. The initial owner manifest and
batch remain independently retained; after removing only the new data_hex
fields their complete parsed manifests are equal. Native source, test inputs,
headers, flags, library and all owner logs are unchanged. There is exactly
one actual cold compiler epoch, using the amended content-attested manifest.

Acceptance remains **283 source-present / 247 scoped semantic rows / 112,273
unit-distinct cases**, with 270 authored bodies, one unknown no-effect body and
12 runtime bodies. Origins remain 270 authored / 48 runtime / 42 generated /
168 unknown. Checkpoint `.analysis/checkpoints/exact-core-controllers-283-101`,
parent `.analysis/checkpoints/exact-bank-loops-283-100`, retains full dossiers,
source epochs, native/shim identities, compiler products and independent review
before hash-verified cleanup. The reused 465-record REA snapshot is unchanged.
No cases, oracle bodies or campaign observations are added. Source presence,
semantic scopes and exact matching remain separate; the >=95% complete-source
objective remains open.
