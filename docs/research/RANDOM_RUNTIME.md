# Original random state and portable defaults

The subsequent [optimized compilation](exact/EXACT_RANDOM_RUNTIME.md) matches
both complete RNG functions, totaling52 bytes, and their four-byte initializer.
Their source is unchanged. The current ledger reaches209 exact functions and
44884 code bytes; the unoptimized compiler results below are historical.

The real native default previously used host `rand/srand`. With seed 1, the
unmodified original game returns `41, 18467, 6334, 26500, 19169`, while the old
native library returns `17767, 9158, 6249, 18547, 23633` through the actual
`dxball_random_range(32768)` wrapper. The retained before receipt binds both
executable/library hashes; no fixture interposition supplies these results.

`src/random.c` now implements the original global 32-bit state, initially 1,
and its recurrence `state = state * 214013U + 2531011U`, returning
`(state & 0x7fff0000U) >> 16`. Unsigned arithmetic defines the observed low-word
wrap on every supported host. Startup and range selection call this shared
implementation in native, MinGW and VC4 builds. Clock seeding still uses
unsigned `timeGetTime() % 300`; range selection retains signed remainder and
the original nonzero-limit contract. No profile-specific implementation is used.

## Original and runtime evidence

| Complete observation | REA Evidence |
| --- | --- |
| Seed writer at `0x4179F0`, 10 bytes, stores its unsigned argument at `0x4230F4` | `ev_25f7f3aed6a65c29e1ae6659c1351396bc3a157f9abbc1b7871017ee695e320b` |
| Next-value extent at `0x417A00`, 42 bytes | `ev_0be2800bbaa0b8de39a6acf3b70302a1541bbbc94d5cfbf37926abbcf4ca0c11` |
| All 12 next-value instructions, including the state store, mask and shift | `ev_379007ac2a3fcba011d66ff74552cab8e02ec3aa79a635917f54970feec764a4` |
| Complete initial four-byte state `01000000` at the observed address | `ev_abd38e29952f538ecb52be1d10e9555b606ebd4b481cccb236df24b6c69f9a95` |
| Full 39,136-byte CRT carrier containing both bodies | `ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12` |

The original LEA/ADD/SHL/SUB sequence independently derives multiplier 214013;
its increment is `0x269EC3`. The pinned VC4 `libc.lib` member at archive header
offset 677870 contains both complete bodies. All three actual DIR32 fields
refer to the same COFF symbol index 4, static `_holdrand$S178`. Relocating that
member to the independently observed cell reproduces all 52 original code bytes.
The whole four-byte member initializer is 1, with no relocations. The private
proof retains archive/member/vendor-source hashes and every relocation.

These two entries are now classified as runtime dependencies, with shared
recovered source and scoped semantic acceptance. This proves complete code
compatibility and the observed producer/consumer state contract. It does not
prove independently unique CRT data placement, unique original link selection,
or original source spelling. It neither publishes scoped CRT exports nor extends
the maintained 89-code/20-data section and seven initialized-object authority.

## Compilation and validation

One matching VC4 compilation each of startup and random uses the ordinary
canonical `/Od /Ob0 /Oi- /Oy- /Gd /MT /Gy` flags. All six startup exact units
remain complete matches: 125, 359, 723, 94, 31 and 49 bytes, totaling 1,381.
Twenty-two binding updates record actual emitted literal/API aliases after
complete literal and original-call-target checks; the compiler is not repeated.
All unrelated build recipes, units and candidates remain unchanged.
Final receipt review caught 13 literal labels cascaded by sequential text
replacement. A bounded consumer repairs each actual unit/offset once and
rechecks all complete comparisons against the emitted object. The failed
manifest and repair receipt are retained; no compiler, oracle or provider is
repeated to resolve this recording error.

The recovered runtime functions remain nonexact candidates: seed 19/current
versus 10/original bytes with 19 differences; next 65/current versus 42/original
with 62 differences. No attempt forces the optimized vendor instruction schedule.
The current exact total stays 206 functions, 44,406 code and 136 metadata bytes.
Source presence becomes 285; authored presence stays 270. Scoped semantic
acceptance becomes 249, with origins 117 runtime, 42 generated and 99 unknown.

The new focused fixture executes the unmodified original seed/next bodies and
the real native defaults. It compares the full state after each call, the initial
state, reseeding, results and adjacent original guard bytes. It passes 169 seeds
and 2,728 direct next calls, including full-width unsigned boundaries, individual
bits and deterministic fixture seeds. Another 90 calls compare the actual signed
range wrapper. Eight clock cases control only the clock transport, verify modulo
300 and compare the following real next call. The existing startup fixture also
passes its unchanged 158 cases and one connected dispatch check after adapting
its actual ELF import names. Both fixtures run once.

Native and MinGW rebuild once. VC4 links the two matching objects and 35 verified
unchanged objects, resources and import libraries, with zero additional legacy
source compilations. All 206 exact input closures and 247 historical semantic
scopes are reconciled without replaying historical cases. The new reports bind
the current native library. No fresh physical game, audio or full campaign run
is claimed; complete trajectories and original source identities remain open.

Private receipts: `.analysis/crt-random-origin/`. Current product hashes:
`product-verification.json`. Immutable seal:
`.analysis/checkpoints/crt-random-origin-285-206/sha256.json`. The new REA session
uses pinned 6.4.0/Ghidra 12.1.4 and is closed; full carriers stay on disk.
Optional feedback is appended only to the existing `/tmp` document. Cleanup
deduplicates immutable hash-equal before/seal copies against the immediately
preceding rotation-pixel seal, preserving current/public inode independence.
