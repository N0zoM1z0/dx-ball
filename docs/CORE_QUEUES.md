# Projectile and fire-effect queue entries

The core frame now calls independently reconstructed projectile/fire-effect
queue entries, projectile retirement and ball ignition in shared C.
REA's two new instruction dossiers fill the missing begin/removal entries;
eight matching closed dossiers supply the other contracts without another
binary query. These are dependencies used by the already maintained frame,
projectile update and fire animation owners.

## State, ABI and cursor effects

Original owners at `0x43A898` (projectiles) and `0x43A8E0` (fire effects) contain
current/first/last pointers. Their i686 size is 12 bytes. Projectile nodes have
four signed 32-bit payload fields and next/previous pointers at offsets 16/20,
for 24 bytes. Fire nodes have three fields and links at offsets 12/16, for 20
bytes. Host pointers grow naturally; no profile-dependent records are used.

The eight list entries take their owner in ECX and return a full EAX integer.
Append initializes only links and owner pointers, preserving payload bytes;
allocation failure exits with status 1. Begin sets current to first. Advancing
past the tail rewinds current to first while returning zero. A null current
also returns zero. Removal selects next, or previous at the tail, updates
both links and first/last, then frees the old node. Its result is one for a
removed node and zero for null current. Removing then advancing consequently
skips a successor, as the original callers do.

Projectile retirement at `0x4134B0` forwards the removal result and decrements
the count even when current is null. Ghidra's inferred void signature does not
capture that EAX forwarding. Ball ignition at `0x415630` changes sprite to 61
for every ball, preserving other payload and begin/advance cursor effects.
The frame now calls that maintained entry for the deferred kind-7 power.

## REA instruction evidence

| Original entry | Maintained function | Owned bytes / span | Evidence |
| --- | --- | ---: | --- |
| `0x410030` | begin_fire_effects | 57 / 57 | `ev_b6253aac5e138638d2538a2c36a3eb032a1e5bc82362923a44fe93a52fcfdf62` |
| `0x410130` | begin_projectiles | 57 / 57 | `ev_486b331b8d0f2c90bbc7bf666e701389d8bf5a5275a09c16bfb392d83ba85602` |
| `0x410230` | advance_projectile | 89 / 89 | `ev_f346971775972564d3df0cf90c5a9bbf622f652beb1c4f5906d0525e2ae67276` |
| `0x413410` | append_projectile | 146 / 146 | `ev_795c1af759609398f1bf4e5445e984b338706d39ca41b54043032d5252668d8d` |
| `0x4134B0` | retire_projectile | 32 / 32 | `ev_965bc693de951987a3f1c057f3bf26a09b554d0bfb113c1e04805448966f6c2c` |
| `0x4134D0` | remove_projectile | 215 / 220 | `ev_7e37d6b4a6b93d0007e1b0679c02cddce7d7956455acffda59a5c0f6617099ca` |
| `0x413670` | append_fire_effect | 146 / 146 | `ev_180304c402a6603ffd9ca1178288a139f84751fa978d2206736975d6cd57ba16` |
| `0x413790` | remove_fire_effect | 215 / 220 | `ev_af528cd7404de0f2e8bb6408f7832e2abd28901fba6e04e8dfee1c295b69da8e` |
| `0x413870` | advance_fire_effect | 89 / 89 | `ev_11a49b151d89a53b048ed74ee85f855ffc1894ce79fbb063b6467d52611437bb` |
| `0x415630` | ignite_balls | 64 / 64 | `ev_16a999378ab495ab51c5c38e4a2073ec85e85de4231d049842a3e6aa2f30c30e` |

Both removal bodies have two inclusive ranges and a five-byte gap before the
return block. Their 220-byte spans are not contiguous 220-byte bodies. The
ten dossiers total 1,110 owned bytes across 1,120 span bytes. These static
observations do not establish execution, compiler identity or exact matching.

## Original/native verification

`tests/test_core_queues_differential.py` compares all ten complete original
entries with maintained native C: **590 direct cases**, including two terminal
allocation failures. Each list entry has 42 topology/payload fixtures over
lengths zero through five, every valid current position plus null, and two
payload seeds; append has one additional allocation-failure fixture. Retirement
has 210 cases, and ignition has 42. Another **64 connected calls** cover eight
removal/advance/append/begin traces; those calls are counted separately.

The reused core harness compares complete globals, tiles, auxiliary/pixel
buffers, typed roots/cursors, forward/back links, live ownership and ordered
callbacks. Released storage is poisoned and checked for subsequent writes.
Original helper bodies are not intercepted, and original code bytes remain
unchanged. The core oracle's fixture construction now calls maintained append
entries instead of manually linking host nodes. Both core and queue scripts
reject optimized Python explicitly before running comparisons or writing reports.

Allocation/release and terminal exit remain controlled dependency boundaries;
this does not accept the original CRT implementation. Valid lists/backing and
finite count decrement are required. Malformed roots, signed overflow,
allocator internals, arbitrary host padding, physical APIs and full campaigns
remain outside these claims. Actual i686 SDK compilation independently checks
both node/link/owner layouts. Source/compiler/runtime evidence and exactness
remain separate.

```bash
scripts/repo-python tests/test_core_queues_differential.py
```
