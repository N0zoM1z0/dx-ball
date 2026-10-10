# Exact typed list deletion

Projectile deletion at `0x4134D0` and fire-effect deletion at `0x413790` now
match their complete 220-byte spans. Exact acceptance rises to 175 functions
/31,264 code bytes plus 136 separate metadata bytes. Source presence remains
283; scoped semantic acceptance remains 247. Origins are unchanged.

## Recover the expression that owns the temporaries

Both original bodies save the current node, update neighboring links and the
current/first/last owner pointers, then make two additional pointer copies
before calling operator delete at `0x416760`. The preceding C implementation
expressed a direct runtime-delete call and omitted that compiler lowering.

One private C++ diagnostic shows that ordinary `delete node` generates both
copies naturally and matches every byte. No additional named pointer homes,
padding, source variants or declaration/layout trials are needed. The original
source spelling, class method names and unique language provenance remain
unproven; the matched expression corroborates this reconstruction.

The retained instruction dossiers are:

- Projectile: `ev_7e37d6b4a6b93d0007e1b0679c02cddce7d7956455acffda59a5c0f6617099ca`.
- Fire: `ev_af528cd7404de0f2e8bb6408f7832e2abd28901fba6e04e8dfee1c295b69da8e`.

Each dossier owns 215 instruction bytes across a 220-byte span. The intervening
five-byte jump is retained by complete reads
`ev_cfeffd063a4cc65df314d6958f2cab7ae28761c1029c5cfbfa2c37a8557b810e`
and `ev_2201bb1ef461da82a1f339a0fc864116395208f284dff55d2324bd4e8c482220`.
The complete comparison includes those bytes without changing provider ownership.

## Shared C++ lifetime and allocator boundary

Ten projectile/fire list helpers now live with their constructors in
`src/list_initializers.cpp`. The C consumers retain their existing ECX owner
ABI and full integer results. Append uses ordinary uninitialized POD `new`;
delete uses ordinary typed `delete`. Payloads, cursor successor skipping,
the fourth unresolved owner word, and terminal allocation failure stay intact.

`src/cpp_allocator.cpp` connects both C++ operations to the existing recovered
C allocator. These are integration adapters, not additional original function
or exact claims. Typed game requests remain inside the original unsigned32
size domain. They do not supply general large-host-allocation, exception or
physical allocator fidelity claims. GCC/Clang retain nullable-new checks for
the list owner. The ELF link map localizes only the paired C++ adapters; both
are absent from the dynamic export table, while public C allocator APIs remain
available. Other host C++ images retain their own allocation APIs.

The initial Native compile rejected visibility attributes on the built-in
operators. That failure and source are preserved; the corrected linker rule
passes without suppressing compiler diagnostics. A separate manifest writer
initially combined inline and nested relocation declarations; parsing rejected
it before promotion. The preserved comparison dictionaries are unchanged after
rebuilding valid TOML and checking structural equality.

## Complete comparison and affected execution

One stable compile per changed owner uses the pinned flags: core has 23 actual
recursive project inputs and the C++ list owner 13. Eighteen complete units
pass: the two new deletions and all sixteen preceding affected exacts. All
actual relocations and consumed literals pass. Eighteen compiler-generated
initialization functions retain their complete raw bytes and relocations.
Begin/advance and other core candidates remain explicitly nonexact.

The unchanged Native/original queue check passes 590 direct cases, including
two terminal allocation failures, plus 64 separately counted connected calls.
It checks untouched payloads, roots/cursors, live ownership, neighboring links,
full integer results and writes after poisoned release. Its raw input inventory
is supplemented by a separate receipt for the new C++ adapter and build/link
configuration; the original runtime receipt remains intact.

Native and MinGW build the three affected sources. VC4 reuses two matching
objects and 33 verified unchanged objects, compiling the new adapter once,
then links all 36 objects with verified resources and import libraries.
The current VC4 executable passes the existing real-Wine ball/pause/editor/
save-reload/exit selection: 84 read-only states, five captures, expected whole
saved-bank hash, exit zero, and all 49 original files unchanged. This does not
establish synchronized trajectories/pixels, physical audio, asynchronous MIDI
or full-game fidelity. Other semantic scopes and cases remain historical after
input refresh; no full historical replay was run.

Private proof: `.analysis/list-delete-recovery/` and
`.analysis/core-language-lifetime/`. Immutable seal:
`.analysis/checkpoints/list-delete-283-175/sha256.json`.
REA 6.3.0 reuses the four complete closed records without opening a provider.
Performance and usability feedback stays in entry 34 of the user's one existing
feedback document.
