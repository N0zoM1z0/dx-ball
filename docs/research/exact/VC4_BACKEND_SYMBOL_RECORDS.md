# VC4 backend symbol-record observations

The October17 investigation locates actual record-reading code in the pinned
VC4 backend. It does not yet explain the game's declaration-context scheduling
changes or recover its original declarations. No compiler flag, name, order or
declaration-count sweep follows from these observations.

The target is `.tools/msvc400/bin/c2.exe`,567,296 bytes, SHA-256
`820ed4e4930db97bcba646afb88fdb7d1f329631ca8e5b84096c0d6daa82e9a9`.
It has no COFF symbols, exports or debug-directory entries. Exact literal bytes
include the diagnostic path `\school.tp3\test\c10\src\P2\p2symtab.c` at
`0x481800`, and `sym il`/`Pch sym il` at`0x481784`/`0x481860`.
Static pointer-byte matches were candidate locations only; REA subsequently
confirmed reference-source addresses and selected containing procedures. The
direct xrefs list does not expose reference kinds.

The completed REA6.5.0/Ghidra12.1.4 session retains14 Evidence records under
`.analysis/rea/vc4-backend/runs/2026-10-17T11-03-42.058Z-interactive-3335159/`.
Its snapshot is isolated from the original-game snapshot. The profile omits
`Apply Data Archives`; the exact profile and limitations accompany every record.

| Observation | Evidence |
| --- | --- |
|21 reference-source addresses for the diagnostic path | `ev_042608c5733d50ac2e6145865fe6a1b2f842468af53df56feb2828a83c3bcf40` |
| First cold reference belongs to procedure`0x4010d7` | `ev_6133303ebf8a4e1898c72fc6ff6c732fb0eef3ea0af5aaefacb4157ff29ccd15` |
| `sym il` driver`0x43a232`, pseudocode / assembly | `ev_e6737a579cb9c6b4a816506a7259faf0704e8139c145118b88ff23cedf839bb7` / `ev_74cd13f758822b1f872096a8e067ef3d2c37440e31f823e789532db7128a3e4b` |
| `Pch sym il` containing procedure`0x41bb61`, pseudocode | `ev_defaa912809d8310d487422c8c37575176bac96812fe4256ddfafdf454d81cc6` |
| Integer reader`0x41ba77`, assembly | `ev_9c6d3ad074742476d8002ef53cf0ede950caf13ce03b5b99e84b7c5cf7d1b0bf` |

The first cold reference is part of a noncontiguous100-byte function whose
enclosing span is312,663 bytes. Its kind-to-size switch returns several record
sizes; the whole span is not a function extent. The driver opens suffix-named
files and walks a flagged worklist. This is not evidence that declaration IDs,
hash iteration or allocation order cause the game's operand changes.

Pseudocode for`0x41bb61` shows kind-dependent record reads and calls to
`0x41ba77`. Its inferred types/signature and omitted terminal fallthrough retain
the provider's limitations. That initial session did not request full assembly;
the later reader observation below uses the subsequently retained assembly.
The reader's actual assembly establishes two encodings selected by a global:
one reads a low15-bit word and conditionally adds16 upper bits shifted15;
the other has separate one-, two- and three-byte paths. The global's meaning
and these values' eventual role in instruction selection remain unestablished.

The first default-profile import timed out and closed without observations.
A changed profile and startup budget then completed one cold import; all
follow-ups reused it. The session closed normally and its JVM/temporary project
were removed. Guard and mocked lifecycle checks cover rejected compiler targets,
accepted compiler targets and the existing game snapshot behavior. There were
no new original-game queries, compiler-setting changes or exact claims.

Private static metadata, request identities, failures, lifecycle checks and
cleanup receipts are in `.analysis/compiler-lowering-discovery-20261017/`.
Reuse these records before another compiler import. The later
[expression-ordering investigation](VC4_EXPRESSION_ORDERING.md) connects the
numeric lookup field at record`+0x24` to an actual subtree-ranking and swap
decision. Its64-record cumulative snapshot includes these14 observations.
The specific original-game producer link remains missing; neither investigation
authorizes arbitrary declaration experiments.

## Current bank-loader reader order

One later observation uses the unchanged current C++ resource recipe. The
retained full reader assembly is Evidence
`ev_b72644fd2d85d07e930898c7f59b826775d5ceeb65897545fdb7196799331f5a`,
record41 in the closed `2026-10-17T13-45-34.524Z-interactive-3690015` run.
At`0x41bc1f`, `MOV [ESP+0x1c],EAX` writes temporary record`+8`, because
the record begins at`ESP+0x14`. Its key is at`ESP+0x38`; the current spelling
buffer is`0x486118`. These establish the observation point without assuming
what the incoming field means.

A bounded debugger captures one unchanged resource compilation. It changes
only one instruction byte in the owned C2 process, restores it for each
single step, preserves condition flags and leaves compiler files unchanged. All three
compiler processes exit zero. There are116 reader hits and20 selected bank
events, with zero mandatory read failures. The selected events include all14
scalar roles, key, API workspace, three parameters and one unnamed record.
The previously missing `saved_bank` key is directly observed as28266.

| Current local in actual reader order | Key | Incoming field`+8` | Current EBP home |
| --- | ---: | ---: | ---: |
| count |28268|4|−4|
| cursor |28271|4|−8|
| pitch |28272|4|−12|
| row |28269|4|−16|
| sprite |28267|4|−20|
| saved_bank |28266|4|−24|
| column |28270|4|−28|
| pixels |28286|4|−32|
| code |28284|1|−36|
| baseline |28283|4|−40|
| pixel_count |28285|4|−44|
| height |28282|4|−48|
| width |28281|4|−52|
| record |28289|4|−56|
| key |28293|8|−64|
| api |28303|116|−180|

For these16 objects, the incoming field equals the source object size, and
its cumulative size rounded to four-byte boundaries agrees with every actual
frame home. This is a current-closure correlation. It does not establish the
allocator traversal algorithm, the producer of reader order, original symbol
keys/names/scopes, or original compiler settings. The raw word at record`+0x36`
is retained without naming its semantics. Known lookup buckets and numeric keys
alone do not explain the order. The earlier root/scope and multiplication controls
remain closed; no declaration variant follows this observation.

All18 complete resource comparisons retain their current identities, including
13 exacts,262 actual bindings and six full literal references. Source inputs,
flags, canonical object and toolchain identities verify before and after. The
bank stays1475 bytes/66 differences across425 matching instruction boundaries.
The first width read at`0x4046c6` uses EBP−52 in both bodies; the second height
read at`0x4046dc` uses original EBP−28/current EBP−48. An initial private verifier
transposed these role labels; its preserved correction changes only metadata.
A second correction separates the authority's `build` annotation from complete
comparator equality. Neither repeats compilation. No source, claim, delivery,
semantic case, replay or game observation changes.

Private `.analysis/sprite-bank-current-producers-20261017/` retains the complete
instruction correspondence, reader trace, verifier corrections and independent
reviews. The observer EXE and duplicate observed COFF are archived, with every
member hash checked before deletion. Another98 old copied runtime files are
verified against49 retained carriers and removed after active-reference checks.
Cleanup releases3.38 MiB of allocated storage after its archive and journal.
Originals, historical image/map/captures/states, current tested products, useful
CMake caches and direct traces remain. The job uses one CPU, CPU35%, memory
high640 MiB/maximum768 MiB; no provider import or full replay runs.

## Frame allocation from the symbol reader

The next investigation captures the same16 real records after reader copy at
`0x41bd19` and before post-emission cleanup at`0x43a473`. Each retains its
address, kind, key and actual underscore-prefixed name. Record`+4` is the only
DWORD field matching all16 signed homes; `+8` retains object sizes.

A second unchanged resource compilation watches the actual count record's
four-byte`+4` field. One hardware write changes0 to−4; ESI identifies that record
and EAX is−4. Its write-after EIP is`0x401559`. REA confirms the preceding
three-byte instruction at`0x401556`: `MOV [ESI+4],EAX`. The complete64-byte
runtime code window agrees with pinned C2. Both observed compiles preserve all18
complete resource identities,262 bindings and six literal references; source,
flags, canonical object and toolchain identities verify before/after.

One REA6.5.0 import retains22 new records in
`2026-10-17T14-59-10.027Z-interactive-3840208`. Its first query takes417,663 ms;
follow-ups reuse the import. It closes and saves the86-record cumulative snapshot.

| Actual instruction/control-flow evidence | Evidence ID |
| --- | --- |
| Store`0x401556` | `ev_418fb7cd83932a1e1c5c51e48f3f8a52ef27eaa657ddf34e153401530a665f12` |
| Reader loop and call`0x41b877 → 0x401508` | `ev_d97167a8c80b3bcf0e7bf2043f79c3114c8f0f8d505f864a50a42dbd140d907f` |
| Storage allocator`0x401508` | `ev_39e7d020c2953a85cd140179aa6dd0376e42d7f45f28d3b8a262a756ff17aaa8` |
| Negative frame cursor helper`0x40aed4` | `ev_8afd04dca8799979d3de5a2b025a7cb4e1e976eac61373c4703bbec2cd8ed56d` |
| Alignment helper`0x40aeff` | `ev_d715b0bae3f8ead36ff7343e6b55fc54cbb5c41066128e2ffbe8d7fdb46459c2` |
| Shared return tail`0x401559..0x401565` | `ev_b53bf95127532a4e2d3446a6103ce8d62ed147ae96007e05ddc9d225fc8d888d` |

The actual kind1 path reads a record, processes/inserts it, checks its flags,
calls the allocator and returns to the reader loop. In the observed normal
storage case, it rounds`record+8` to the alignment at`0x47ea30`, obtains a
negative position through`0x40aed4`/`0x40aeff`, writes`+4` and sets allocated
bit`0x800` at`+0x10`. A subsequent request returns zero without changing the
record or cursor. This normal path does not read key`+0x24` or walk a lookup
bucket; reader-order production upstream remains unresolved.

Imported boundaries require care. Ghidra splits the13-byte shared return tail
from its parent and splits the reader prologue from its loop. Actual jumps,
fallthrough and saved-register restoration reconnect them. The tail is not an
independent normal callable entry. Ghidra gives`0x40aed4` a void signature,
although its actual EAX is consumed as the negative frame position.

Seventeen final controlled calls execute unmodified mapped C2 instructions:
16 retained pre-records in observed order and one already-allocated guard.
With explicit starting cursor0/alignment4, all16 homes, the180-byte frame,
padded returns, allocated flags, saved registers and stack balance agree. Four
is also the initialized PE alignment default; this does not independently observe
the runtime global. Other storage cases and frontend emission are outside the
check. The initial harness whitelist omitted the already-retained cold guard;
its correction and failure remain available, with no compiler repeat.

All66 bank differences are explained:63 ordinary home substitutions and three
within two commuted products. All425 boundaries,23 calls and22 branches agree.
One product instruction is byte-identical despite different role operands, so
both complete product groups are included. Width already matches EBP−52;
thirteen other scalar homes differ. This is a candidate explanation with no new
exact or semantic acceptance.

An offline archive proof closes root14 precisely: its body equals the retained
C++ before-iteration model, including the116-byte API workspace and current
operations. That complete comparison is1475/72. A later context alone supplies
no new source-model basis. A target-ordered aggregate of all14 roles lacks an
independent aggregate producer/consumer and is not compiled.

Private `.analysis/bank-frame-writer-20261017/` retains both direct traces,
hardware write, complete comparisons, corrections, archive proof and independent
reviews. Four observer products are archived/member-verified before removal;
the closed run's identical8.36 MiB catalog shares its immutable carrier while
preserving all paths and bytes. Cleanup releases8.66 MiB after archive/journal.
Current tested products, valid caches and unique evidence remain. Source,
394 exact/21 authored candidates, delivery and semantic cases stay unchanged.
No game or full replay runs. Heavy work is serial on one CPU under CPU35%,
memory high640 MiB/maximum768 MiB.

The later [C1XX traversal investigation](VC4_FRONTEND_SYMBOL_ORDER.md) recovers
the actual name hash, head insertion and ascending bucket walk.36 controlled
pinned-helper calls reproduce all16 current bank names in the retained reader
order using the four current source scopes. Emitter/header calls are explicit
boundaries; no live frontend transport or original identifier recovery is
claimed. No source, exact count or delivery changes follow.
