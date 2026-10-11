# Exact startup RNG calls

Current follow-up: [original random runtime](../RANDOM_RUNTIME.md) replaces
host-dependent defaults with the recovered 32-bit generator in every build.
The complete 31/49-byte startup helpers remain exact, along with all four other
startup units (1,381 bytes total). The current fixture binds the actual
`dxball_crt_srand/dxball_crt_rand` imports. The counts and libc-default discussion
below describe this note's historical checkpoint.

The two startup RNG helpers now match their complete original spans: range
selection at `0x403B70` is 31 bytes, and seeding at `0x403B90` is 49 bytes.
Exact acceptance rises to 173 functions /30,824 code bytes plus 136 separate
metadata bytes. Source presence remains 283 and scoped semantic acceptance 247.

The retained contiguous REA dossiers establish genuine direct CRT calls and
an independent clock import:

| Entry | Evidence | Observed contract |
| --- | --- | --- |
| Range | `ev_dcaab4c60684caf5c24767829432c46b7d7fc94f93fbcd7d15813b604710e8f1` | Call `rand` at `0x417A00`, signed remainder by the incoming limit, store back to its argument home and return |
| Seed | `ev_17cf72657ba0a29ec43b5716ed09347c3645e4eaa4374f80256a5eb7b58296f6` | Call `timeGetTime` through `0x4413A4`, unsigned remainder by 300, local seed storage, direct `srand` at `0x4179F0` |

The original instructions include the return jumps and all exits; neither
body has excluded intervals. The current source preserves the signed range
division and unsigned timer domain. It does not add a zero-divisor guard or
change negative-limit behavior. The original spelling and local names remain
unproven. SDK success, timer resolution and complete random game trajectories
are outside this static/function-level claim.

## Shared source and complete comparison

`src/startup.c` uses genuine `rand/srand` calls and the existing independent
`dxball_time_get_time` import boundary. One natural seed local and the observed
parameter assignment preserve actual consumers; no fake storage, padding,
alternate profiles or naming/layout trials are used.

One stable `/MT` VC4 compilation emits all five startup exact units together.
The complete range/seed bodies and all three actual relocations pass. Bank
release (125 bytes), score initialization (723 bytes /87 relocations) and score
reading (94 bytes /10 relocations) retain complete exact matches. Device
initialization remains a 359-byte candidate with ten differences. All sixteen
recursively consumed project inputs equal the declared recipe closure.

Adding the clock header changes compiler-generated string labels. The first
comparison rejected the stale relocation names before acceptance. The manifest
then records the actual emitted labels at their original offsets, after checking
the full literal contents and existing target bindings. The same already-built
object passes every complete comparison; no recompilation or source permutation
was needed. The failure log is retained.

## Affected validation and products

The existing Native/original startup fixture passes its unchanged 158 cases
and one connected device/frame dispatch check. Its RNG callbacks now bind only
the copied image's actual `rand/srand` ELF import slots. Existing callbacks,
case values and assertions remain unchanged; the fixture verifies image owner,
slot identity, page permissions and unchanged process-wide libc resolution.
Production retains genuine defaults. The eight timer cases include unsigned
wrap values; the 32 range cases include negative nonzero limits.

Native and MinGW compile only the affected source. VC4 links the same matching
object with 34 verified unchanged source objects, resources and import libraries;
there is no additional production source compile. All 173 current exact receipts
retain valid object/input identities. Other semantic cases and scopes remain
historical after input refresh; no full historical replay or new live game run
is attributed to these products.

Private receipts: `.analysis/startup-rng-recovery/`. Immutable seal:
`.analysis/checkpoints/startup-rng-283-173/sha256.json`. Retained REA dossiers are
reused without opening a provider; feedback entry 33 stays in the user's one
existing `/tmp` document.
