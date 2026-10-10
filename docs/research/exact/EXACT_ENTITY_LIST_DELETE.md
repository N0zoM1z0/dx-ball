# Complete typed entity-list deletion

Explosion, brick-effect, particle, bonus and ball removal now match all five
complete 220-byte spans. Exact acceptance rises to 180 functions /32,364 code
bytes and 136 separate metadata bytes. Source presence remains 283, scoped
semantic acceptance 247, and origin classifications are unchanged.

## Instructions and complete boundaries

Each retained dossier exposes 215 owned instruction bytes across a 220-byte
span. The original code saves the current node, reconnects its neighbors,
updates current/first/last pointers, then makes two additional pointer copies
before calling operator delete at `0x416760`.

| Removal | Address | Retained REA Evidence |
| --- | --- | --- |
| Explosion | `0x40FF50` | `ev_1538f8576bc2c7b207799609630f986e3933507a8a2a23a9a16767404a1a93d4` |
| Brick effect | `0x412A50` | `ev_15590b4df69e7901145c02e294dca11e8f4f9c5be7675b3a332149d8dddde90e` |
| Particle | `0x414B30` | `ev_e30c638667b1f7ce3a2fef6c243992dda3d59bad3a57a76cf426638f84129055` |
| Bonus | `0x4147C0` | `ev_b1a3e59b2e4a28cee43842cefa27a736625c049bade614e71c11c6e452e3e0a1` |
| Ball | `0x411850` | `ev_ad944e908a2b23a9361befd1410ae97034be779d87b3b006536ec2d702031394` |

One new complete 19,644-byte read, Evidence
`ev_53d09dc3764261c38bcef8301ceecefeeb2b104488e69165aa5cdbe9d75f26a9`,
attests every span and excluded five-byte jump. The full read matches the
verified original PE. It does not change Ghidra's ownership classification.

## Shared natural C++ lifecycle

Ordinary `delete node` generates both pointer homes naturally and matches
every byte. Twenty-five append/begin/advance/remove/clear helpers move into
`src/list_initializers.cpp`, alongside the earlier projectile/fire lifetimes
and constructors. All seven maintained list families use typed uninitialized
POD `new` and genuine typed `delete`, retaining the public C linkage/ECX ABI.

Node payloads are left untouched by allocation. Nullable allocation still exits
with status one. Neighbor updates, cursor successor skipping, first/last roots
and the unresolved fourth owner word retain their established behavior. The
paired portable C++ adapters and ELF visibility rule remain unchanged. Game
controllers stay in their existing C owners. No fake locals, padding, copied
code, assembly, layout or source-name trials are introduced. The matched
lowering corroborates the expression; unique original syntax, class names and
language provenance remain unproven.

## Comparison and affected checks

One stable compilation per owner uses the pinned flags and actual recursive
project inputs: gameplay 19, effects 18, particles 14, balls 18, bonuses 22,
and the C++ list owner 13. All 53 affected complete units pass, comprising five
new deletions and 48 preceding exacts. All actual relocations and full consumed
literals pass. Eighteen compiler initialization functions retain their raw
bytes/relocations, as does the ordered 36-byte constructor table with nine
relocations. Twelve other affected candidates remain nonexact.

A local comparison initially rejected renamed generated switch labels. Their
actual section offsets match the previous object definitions; reviewed
original bindings and complete literal contents establish the refreshed
manifest without recompilation. Candidate object offsets can differ from
original positions and retain their explicit comparison gaps.

The current native library passes 832 selected maintained cases against
unmodified original x86: 400 particle/bonus list calls, 264 brick-effect list
calls and 168 ball/explosion list calls. Existing assertions check integer
results, roots/cursors, payloads, neighboring links, reachable allocations and
poisoned freed storage; three terminal allocation failures pass. Selection
keeps existing loops/assertions, with no new vectors or broad historical replay.
The first combined fixture import mutated a shared shape inventory; isolated
processes run each maintained suite independently. An initial effect selection
covered allocation only and was extended to the existing cursor/removal loop
before acceptance. Both local selector failures/coverage records are retained.

Native and MinGW build the six affected sources. VC4 reuses six matching
objects and 30 verified unchanged objects, then links all 36 with verified
resources and SDK imports. No extra legacy source compilation is needed.
Earlier Wine play keeps its own earlier executable identity; this checkpoint
does not claim a new live-game run or physical allocator/audio/full-game
fidelity. Twenty-two moved semantic entries retain their original oracle
bindings; 235 historical semantic input rows refresh identities while keeping
all cases and scopes unchanged.

Private receipts: `.analysis/entity-list-delete/`. Immutable seal:
`.analysis/checkpoints/entity-list-delete-283-180/sha256.json`.
REA remains 6.3.0, verified against the installed package and official npm
latest. One focused provider session closes successfully; complete carriers
stay outside context. Performance and usability feedback remains only in
entry 35 of the user's existing `/tmp/dxball_rea_feedback_20261010.md`.
