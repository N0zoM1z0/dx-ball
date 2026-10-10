# Projectile retirement and its void boundary

`dxball_retire_projectile` at original `0x4134B0` now matches its complete
32-byte body and all three actual relocations. Shared natural C calls projectile
removal, decrements the count, then returns without a value. No saved result,
fake local, assembly, padding or alternate profile body is needed. Totals are
185 exact functions /32,688 complete code bytes plus136 metadata bytes;
source presence283 and scoped semantic acceptance247 remain unchanged.

## Instructions and consumers

Closed REA Evidence
`ev_965bc693de951987a3f1c057f3bf26a09b554d0bfb113c1e04805448966f6c2c`
owns all32 bytes. The body has no local frame: it sets the projectile owner in
ECX, calls removal, decrements the global count and joins its epilogue. There
is no explicit EAX producer after the call. The decompiler models a void entry.

The controller dossier, Evidence
`ev_412b7a2d61e8a498417dca7a456838ed290b17317e4af4585d8b936b69b07495`,
records two callers at `0x413231` and `0x413278`. The first jumps to a join
whose next phase independently reloads EAX; the second immediately overwrites
EAX from its live projectile local. Neither consumes a retirement result.
A scan of original executable sections for relative E8/E9 targets finds exactly
those two calls and no jump. A whole-file literal-address search finds none.
These bounded searches do not exclude computed, self-modified or external
callers. Unique original return declaration, naming and no-argument calling
convention spelling remain unproved.

The former int-returning reconstruction saved deletion's result in a local.
Its fixture promoted surviving original EAX into an API assertion. The current
void boundary explicitly supersedes that inferred return contract. The deletion
helper still returns a complete integer and retains its existing assertions.
Retirement still decrements count when current is null, after deletion.

## Affected compilation and dependency identities

One compilation per22 real matching owners consuming the changed header
passes151 complete units: this entry plus150 preceding exacts. Comparisons
apply every actual relocation and check full literal contents, including named
storage. All18 generated list initializers and the ordered36-byte /nine-relocation
constructor table remain unchanged. Pinned flags and recursively consumed
project headers are retained. Remaining candidates are still nonexact.

Four unchanged matching recipes and eleven unchanged game objects had
conservative inventories that unnecessarily declared `core.h`. Original VC4
preprocessing with the same flags, replacing `/c` by `/E`, establishes their
actual project inputs and absence of that header. Their objects, source,
consumed input hashes and flags remain unchanged. Inventories and associated
receipt rows are narrowed using this proof; their bodies are not recompiled
or newly compared. Previous declarations and raw compressed preprocessing
output remain available privately.

The first game-adoption attempt compiled three additional genuine header
consumers before rejecting an unused declared input. Those actual products
are retained and reused. The final VC4 link verifies all36 objects:22 matching,
three additional compiled consumers and eleven unchanged objects. Native and
MinGW builds pass. Current PE imports retain DirectDrawCreate and
DirectSoundCreate without parser warnings. Native C++ allocator adapters remain
local symbols with no dynamic operator exports; this is integration evidence.

## Existing runtime check

The maintained queue fixture passes590 direct cases and64 separate connected
calls, including two terminal allocation failures. All210 retirement cases
have a void native result; original EAX0/1 is retained separately as
`incidental_target_eax`. Ignition also uses its existing void ABI. No cases,
state comparisons, ownership checks or full integer list assertions are removed.
The changed header requires preparing the owned shim once before the runtime
compiler lock; the initial pre-case cache failure and successful preparation
are retained.

The fixture checks globals, payload preservation, roots/cursors, forward/back
links, ordered callbacks, live ownership and poisoned released storage.
Allocation, release and exit use controlled dependency bridges. Valid typed
backing and finite count decrement are required; malformed lists, signed
overflow, allocator internals, arbitrary host padding, physical APIs and full
campaigns remain outside scope. No new live-game run or broad historical replay
is claimed. Raw receipts have a separate supplemental product-input inventory
for actual C++ and build dependencies.

Private proof: `.analysis/projectile-retirement-contract/`, with reused complete
REA archives and no new provider request. Immutable seal:
`.analysis/checkpoints/projectile-retirement-283-185/sha256.json`.
The overall source-restoration and whole-game fidelity goal remains open.
