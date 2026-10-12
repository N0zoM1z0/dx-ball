# Exact optimized RNG dependencies

The unchanged shared source in `src/random.c` now matches both original CRT
functions under the optimized VC4 recipe. The project reaches **209 exact
functions / 44,884 code bytes / 136 metadata bytes**.

| Runtime function | Original entry | Complete code | Relocations |
| --- | --- | ---: | ---: |
| Seed writer | `0x4179F0` | 10 bytes | 1 |
| Next value | `0x417A00` | 42 bytes | 2 |

Both whole functions compare with zero differences. Every state reference binds
to `0x4230F4`; the complete four-byte initializer `01000000` is also checked in
the compiled object and original image. The next-value body includes the exact
LEA/ADD/SHL/SUB strength reduction, increment, state store, mask and shift.

The selected flags are `/O2 /Ob0 /Oi- /Gd /MT /Gy`. Optimization restores the
frameless seed body and original integer schedule. No source expression or data
layout changes. These are runtime dependencies; the 64-function authored
nonexact queue is unchanged. [The original investigation](../RANDOM_RUNTIME.md)
contains the retained REA Evidence IDs, complete extents and state contract.

The first `/ML` object also matched all 52 bytes, but linking it into the current
`/MT` game produced duplicate CRT startup symbols. One `/MT` compilation preserves
both complete matches and resolves that integration failure. The legacy builder
now uses the RNG owner's configured flags for subsequent builds. The accepted
object links with 36 verified unchanged game objects, including the recovered
line owner. No additional game source compilation is needed.

All 209 accepted byte extents, compiler inputs and object identities verify.
The RNG source and portable products are unchanged by this compiler-recipe
update; their prior semantic vectors retain their historical scope. No RNG
case suite or game campaign is repeated. The same checkpoint passes the line
owner's 486 existing original/native comparisons and Linux/MinGW builds.

Both compiler stages, original Evidence identities, complete comparisons,
initializer attestations and current products are retained in
`.analysis/random-optimized-model-20261012/`. Verified gzip carriers preserve
completed diagnostic and previous product bytes during cleanup.
