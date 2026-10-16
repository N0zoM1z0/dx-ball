# Effect-sprite path correspondence

Three complete sprite candidates now have a bounded symbolic comparison of
their current VC4 bodies against the retained original instructions. All six
paths per entry correspond in the declared memory and DirectDraw model. No
missing call argument or queue write is found. Their strict comparisons and
source remain unchanged:

| Entry | Original bytes | Current bytes | Differing positions | Instructions per body |
| --- | ---: | ---: | ---: | ---: |
| Blt effect sprite, `0x408180` | 362 | 366 | 332 | 105 |
| Stretch effect sprite, `0x408740` | 306 | 308 | 252 | 89 |
| Draw effect sprite, `0x4082F0` | 361 | 365 | 330 | 106 |

These are **three candidates, not new exact functions**. The ten additional
current bytes remain in the complete comparison. Register/address scheduling
does not justify another source declaration, interface or operand-spelling
trial for these entries without new evidence.

## Complete paths and state effects

The comparison interprets all 300 original and 300 current instructions.
Every decoded instruction must be reached by a symbolic path. Each entry has
six feasible paths: the dirty queue may append or be full, while reduced mode
may skip presentation, append to it, or find it full.

The paired paths compare the actual indirect call target, all six stdcall
arguments, passed local rectangle contents, ordered public write addresses and
values, complete final public memory, return target, callee-saved registers and
stack restoration. Path predicates and valid-address conditions must also
correspond. Thus an equal final buffer alone cannot hide a different call,
write order or capacity boundary.

The caller stack pointer and incoming registers/arguments are symbolic.
Ordinary public DWORD memory must be aligned, mapped and disjoint from the
private caller frame. The one DirectDraw call may replace all public memory,
clobber EAX/ECX/EDX and modify all four fields of its passed destination RECT.
An unpassed private rectangle remains private. This preserves arbitrary live
page/count/mode changes during the callback, rather than assuming cached state
survives it.

Address arithmetic is modulo 2^32. Six distinct affine normalization patterns
have an independent bit-vector check after abstracting their memory operands;
the comparison does not assume algebraic equivalence from similar disassembly.
Z3 4.13.0 checks the retained complete obligations.

There are 34 adopted queries: three equivalence checks, six path-coverage
checks, eighteen feasible-path checks, six negative controls and one check of
all normalization rules. All expected results hold; none is unknown.
Feasibility and negative controls use ordinary bounded queue counts and one
nonnull sprite/surface setup. The equivalence checks are not restricted to
those concrete witness values.

## Sensitivity controls

Private instruction mutations are rejected for:

- Removing keyed-copy flags from each of the three calls.
- Decrementing a dirty count instead of incrementing it.
- Restoring EDI from the saved EBX word.
- Changing the dirty capacity from 1,000 to 1,001.

The capacity control produces a valid witness with a dirty page already holding
1,000 records. The original skips that append; the mutation takes it. The
controls establish sensitivity of the checker, without adding production
variants or historical semantic-case counts.

## Original evidence and current linkage

Original instruction boundaries agree with these retained REA dossiers:

| Entry | REA Evidence |
| --- | --- |
| Blt | `ev_82e6d49881f8641a426f66235acef4c51d18f0d3420d746c0d1f13c535afb861` |
| Stretch | `ev_2d69c6041416a67a1548d91dc71a945b13a33e065d32e96528ffacd6f80ce455` |
| Draw | `ev_ddac92d3e1a7e508d55181c07f05bbbbabb7870694d36de94fa3eeb7ada0155f` |

The first two are operations 01/03 of the closed October 9 13:18 pending-owner
run; Draw reuses the full dossier retained by the original display checkpoint.
The verified PE, complete code extents, actual relocations and current producer
receipt bind the comparison. No new provider or compiler runs.

The same display object is used by the current restored-CRT image. Its linked
Draw body matches all 365 bytes and 23 actual bindings at `0x40DCB0`. The other
two entries have no incoming relocation across the 116 source objects and no
current LINK map entry under `/OPT:REF`; their maintained bodies remain in the
comparison object. This does not establish their original active use.

## Limits and retention

Code is immutable; public memory here means ordinary data. The model assumes
a normal stdcall return and no concurrent memory changes
between ordinary instructions. It does not model access faults, arbitrary
hidden ABI inputs, callees inspecting machine return addresses, or physical
driver pixels. Caller-saved residue and flags outside the void-function
contract are not compared. This is a bounded VC4 machine-body correspondence,
not a proof for every portable C/C++ compiler or a byte-exact claim.

Source, game objects, all function ledgers and complete comparison reports stay
unchanged: **380 exact functions / 95 candidates, including 34 authored**.
No native fixture, game, full replay or new semantic acceptance runs.

Private `.analysis/effect-sprite-paths-20261017/` retains the checker, all adopted
SMT queries, negative controls, complete comparisons, producer/object identity,
REA dependencies and linkage review. Frozen inputs are archived only after
full-byte verification, releasing 839,680 allocated bytes. Superseded analysis
queries remain separate from the adopted report. CPU/memory limits remain in
force; no assembly, padding, fake storage or source permutation is adopted.
