# Runtime heap and allocation ownership

The shared source now implements eight runtime entries reached by gameplay,
MIDI, resource and sound owners. Saved REA `analyze_function` dossiers establish
213 contiguous original bytes and their contracts; original x86 execution,
native C and actual VC4/MinGW objects corroborate tested behavior. These are
runtime dependencies, counted separately from the 235 maintained game entries.
The allocation bodies have no byte-exact acceptance.

## Recovered contracts

| Original entry | Shared C | Reviewed bytes | Observed contract |
| --- | --- | ---: | --- |
| `0x416760` | `dxball_runtime_delete` | 14 | Forward the pointer to heap release |
| `0x416770` | `dxball_runtime_new` | 16 | Allocate with new-handler retries enabled |
| `0x417750` | `dxball_heap_release` | 24 | Skip NULL; call HeapFree with current heap and zero flags; ignore BOOL |
| `0x417770` | `dxball_runtime_malloc` | 20 | Read malloc mode once and forward it to the allocation loop |
| `0x417790` | `dxball_allocate_with_handler` | 64 | Reject requests above `0xffffffe0`; normalize zero to one; retry after any nonzero handler result |
| `0x4177d0` | `dxball_heap_allocate` | 21 | Reload the heap handle and call HeapAlloc with zero flags |
| `0x419e80` | `dxball_initialize_runtime_heap` | 21 | HeapCreate(1, 0x1000, 0); store the full returned handle, including NULL |
| `0x419ea0` | `dxball_call_new_handler` | 33 | Reload the callback; return zero when absent, otherwise its complete signed result |

The original heap, handler and malloc mode are at `0x440d70`, `0x43fb10` and
`0x4234d4`. Request sizes retain their unsigned 32-bit domain. Opaque heap
handles and storage pointers grow with a portable host. A negative handler
result still retries; callbacks may replace the heap or handler between calls.
The loop keeps the mode sampled by the malloc wrapper while reloading those
mutable dependencies.

The original startup dossier shows the initializer call at `0x418801` without
testing its EAX result. The reconstructed Windows entry therefore binds APIs,
initializes this heap once, ignores the return and enters the maintained WinMain
controller. `dxball_bind_windows()` only binds APIs and can be called repeatedly
without replacing the heap or resetting handler/mode state. This is a recovered
startup edge; the compiler's own startup still supplies the host CRT.

## Shared defaults and physical boundary

`src/allocator.c` contains the eight recovered bodies. `src/allocator_host.c`
supplies an explicit portable malloc/free backend and typed `size_t` bridges;
a request that cannot fit the original unsigned width is rejected before
allocation. Those dependency helpers are not additional recovered entries.
The Windows adapter installs typed stdcall HeapCreate/HeapAlloc/HeapFree
callbacks through `dxball_bind_heap_api`, including when the core resides in a
DLL. The pointer table is copied by code that owns its storage.

| Consumer | Maintained default |
| --- | --- |
| Projectile, explosion and animation nodes | new bridge / runtime delete |
| Music wrapper record | new bridge / runtime delete |
| SBK/font backing | malloc bridge / heap release |
| Sound records and WAV storage | malloc bridge / heap release |

MIDI Local/Global allocations keep their separate SDK ownership. DirectSound,
DirectDraw, file and driver dependencies keep their explicit boundaries.
Handler registration, exhaustive state-writer coverage and game heap teardown
remain open. No HeapDestroy was added to game shutdown.

## Bounded acceptance

`tests/test_allocator_differential.py` compares 1,433 fixtures / 1,437 original
calls with the actual maintained native library: complete logical results,
ordered heap/handler effects and heap/handler/mode state. Seven separate native
controls cover host pointer forwarding, initializer storage, zero-size bridges
and oversized host requests. Original allocation bodies execute unchanged;
imports and scripted callbacks supply the controlled API boundary. Finite retry
scripts do not establish arbitrary nonterminating handlers.

`tests/test_allocator_coff.py` executes both the configured VC4 object and a
fresh MinGW object over the same 1,437 calls, with all relocations resolved and
explicit twelve-byte heap-API fixture storage. It checks the compiler identity,
configured flags, object path and object hash before using the VC4 product.
These repeated calls are compiler corroboration, counted once in direct totals.

`tests/test_windows_allocator.py` links the actual maintained adapters/products
against both SDK profiles and executes them under Wine. Observer callbacks
forward to the saved physical Windows table. Each profile confirms one heap
creation, four allocations and four successful releases, with HeapValidate and
payload round trips. The four paths cover malloc, new, node and sound defaults.
NULL release and oversize rejection skip the API. HeapDestroy is fixture cleanup
only. Real link files, generated link-map records and emitted PEs have distinct
recorded identities; generated pseudo-relocation records have no independent
on-disk file identity. This is a Wine/SDK result, not native Windows or whole-game
heap correctness.

The fresh owner batch passes all 23 oracles with the new shared native library.
The compiler/integration batch passes all 18 checks, reusing only completed
checks whose full relevant identities remain unchanged. Resource-free negative
control linking now includes the host backend as part of the game object graph.
The previously sealed private MIDI/resource/sound failure connections remain
historical supporting evidence; their old products and input hashes were not
silently relabelled as execution of the new maintained defaults. Complete
connected frame failures, i686 owner failure matrices and reconstructed full
campaigns remain open.

The source ledger now has **243 entries: 235 game functions and 8 runtime
functions**, with **111,242 direct cases**. Cold replay retains **35 exact units /
3,379 bytes**. `stretch-keyed-sprite` remains behavior-accepted, but its rebuilt
139-byte body differs at two operand bytes, so its exact claim was withdrawn.
The two sound-pan compiler literal names changed to `$T1142` / `$T1143`; both
contents and complete relocation mappings were checked before reconciliation.
No emission tuning, masking or copied machine bytes were introduced.

## REA evidence and reproduction

The retained static dossier IDs are:

- delete: `ev_dd4c8eb171fe4da4755816c3387814ad47a13e806c38958c44aa8cbc190e44ac`
- new: `ev_2f47da62f234bfb025db282149258ce5cb1b53a74591f045695579a7d8887f91`
- release: `ev_71abe55c26ab63d390b070c27874d920fa335c74cc9b406dcdab748a7f3bdd33`
- malloc: `ev_bab5314682949a397f2c04f0c60c4d9c0e5c760c6d5adaf4a98355d823f22354`
- allocation loop: `ev_5b84dc43a44b86e3cd73f1ebfddc73bdb1f4ef29d11181f1d56181f54cc327b4`
- HeapAlloc: `ev_f6b1749c4f67167beacf3f0af7c69e992dc13304478a79c28a14e9278f719acc`
- initializer: `ev_10ce1eaed90f0753871a24f6fad805895e13fb1cbf155903597f6e751ae3cd91`
- handler: `ev_f350f41184bab52523f0483486ead9de4bd0a0db5c326426842820aa5b3b20df`
- startup edge: `ev_d4cdbb3cea74cf5ff8ce35743dcfa01fdcd54a492152e16462402ddb2f6429c8`

REA process capture binds the fresh 23-owner batch to
`ev_911a399dfcce71ec469c266581cd1f8f470c0be788a25166db9ac8f7dc8b2377`
and the complete compiler/SDK/integration batch to
`ev_17b58ccfd32822dd33322cae85442db7d55fbc760907abfc9318a8f7e6e20fe9`.
Both record child exit zero and complete final-report digests. A focused
follow-up, `ev_463da6a4ff8f660f9be715a33ae72796c6b795df95fab83127140f053031c076`,
checks repository-relative object resolution from `/tmp`; both generated
objects, case counts and observation digests remain identical. Failed link and
stale-input controls remain separately sealed. Reusing saved static dossiers
avoids another Ghidra import while preserving the target/provider identities.

After installing the [private prerequisites](../README.md#get-the-original-game)
and building the native and Windows profiles, run:

```bash
scripts/repo-python tests/test_allocator_differential.py
scripts/repo-python scripts/compile-semantic-build.py --build allocator
scripts/repo-python tests/test_allocator_coff.py
scripts/repo-python tests/test_windows_allocator.py
scripts/repo-python scripts/replay-exact-units.py
```

The tests retain bounded observation digests instead of expanded retry logs.
SHA-sealed pre-integration snapshots preserve the old source/library/reports;
cleanup can deduplicate immutable copies without linking them to mutable build
paths. Use `scripts/repo-python scripts/clean-local.py --evidence-only --apply`
while current probe products are still inputs to accepted reports.

The maintained source commit `f894f72` passes public CI **37822675045**.
Post-seal retention verifies 8,520 sealed paths, 7,704 external references and
all 49 originals, then shares 64 completed capture files with their archived
copies. Actual disk use falls by another 10,543,104 bytes; logical duplicate
sharing is reported separately. Current acceptance identities remain unchanged.
