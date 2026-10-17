# Line drawing workspace and axis steps

The later [interface recovery](LINE_INTERFACE_BOUNDARY.md) gives the routine
its genuine DirectDraw surface pointer. All five consuming recipes preserve
their accepted bodies; line remains 445 bytes with nine differences.

The complete line at `0x403070` now emits **445 bytes**, matching the original
extent. Its strict comparison improves from 379 differences to **nine**.
All 121 instruction boundaries and widths agree, and every other byte matches.

The shared iterator precedes the error and coordinate extents. The surface
descriptor spans GetSurfaceDesc, Lock retries and Unlock. The pixel cursor and
two axis steps belong to the locked traversal and end before Unlock. The steps
form a two-element pair: X advances one byte, Y advances one signed pitch.

These declarations restore every observed home in the 140-byte frame:

| Value | Original and current EBP |
| --- | ---: |
| Iterator / error / X extent / Y extent | -4 / -8 / -12 / -16 |
| Lock result / descriptor base | -20 / -128 |
| Pixel cursor / X step / Y step | -132 / -140 / -136 |

The nine remaining bytes are three signed comparison groups: major-axis choice
and the two loop bounds. Current instructions exchange operands and reverse the
corresponding branch condition. Branch destinations remain identical. The line
stays a candidate. A negated-guard source model produced the same nine differences
and was rejected without repeating the successful compilation.

The complete original dossier is
`ev_25f8571b40b1ee8c589f398fa1211552c03d241352d0737d904789e2664b8af2`,
from the closed October 7 11:58 run. Its entire assembly is reused; no new
provider query is needed. The complete function has no COFF relocations.

Five exact UI companions retain 559 bytes. Linux and MinGW builds and the VC4
relink pass. One unchanged 486-case line loop compares all octants, both endpoint
directions, equality, zero length, retries, complete padded pixels and COM calls.
No text/palette suite or game campaign runs. Private evidence and products are
retained in `.analysis/line-locked-cursor-20261012/`.


## Actual backend comparison decisions, October18

One instrumented compile of the unchanged current drawing-primitive owner
connects its three residual comparisons to actual C2 ordering decisions. This
adds compiler evidence, without a source variant or exact promotion. The existing
[backend helper analysis](VC4_EXPRESSION_ORDERING.md) supplies the pinned code;
no new provider import or query is required.

The observer records all62 helper entries and actual returns:55 in line and
seven in fill. All calls pair by PID/TID/index/node, with no pending call,
secondary C2 thread, missing node/attribute or mandatory read failure. The helper
really swaps ten child pairs and returns their unsigned minimum ranks. Every
opcode/child write, saved register and ESP+8 return is checked. The compiler
process tree exits normally. Two deeper child subtrees exceed the explicit
depth5 recording bound; the three selected comparisons are fully captured.

The relevant operands are scalar loads (opcode30) of the actual named records
(opcode26). Their ranks are not the bare symbol ranks. Retained40846E assembly
at4084C0..4084E4 transforms a child rank r as
`((r-45)&15)|((r+16)&0xfff0)`. The known key formula gives leaf ranks24/25/26/27
for current i/dx/dy/error keys28656/28657/28658/28659; the load ranks are therefore
43/44/45/46. These ranks are independently derived from the assembly; the
comparison's rank arguments and resulting child/opcode writes are observed.
No additional helper emulation or compiler run is needed.

| Actual role pair | Load ranks | Actual opcode before→after | Emitted group starts |
| --- | --- | --- | --- |
| dx / dy |44 /45 |24→22 |403145,403148,40314B |
| i / dx |43 /44 |21→23 |403160,403163,403166 |
| i / dy |43 /45 |21→23 |4031C4,4031C7,4031CA |

Opcode numbers are hexadecimal. Each left rank is less than its right rank;
all three actual calls swap the children and remap the comparison opcode.
Selection uses function and operand-record identities, not event order or a
numerical-key ordering assumption. The final current MOV loads the post-right
role and CMP consumes the post-left role. The original uses the opposite role
order, with the corresponding opposite Jcc and identical destination.

A complete fresh comparison preserves all121 instruction boundaries,140 frame
bytes and445 code bytes. These three groups contain all nine differing bytes;
every other instruction byte agrees. Fill remains85 bytes exact. Both complete
functions have zero COFF bindings or literal references, and their produced
code bytes remain identical to the canonical objects. The source's complete13
project inputs, compiler identities, claim ledgers, delivery and caches remain
unchanged at394 exacts/84,872 code bytes/244 metadata bytes and21 authored
candidates.

This observes a current compiler decision and checks its correspondence to the
specific emitted comparisons. The final emitter's consumption of those exact
node identities is not traced; original keys, names, types, predicates and
compiler settings remain unknown. Thus the result does not uniquely reconstruct
original source or justify a name, scope, order, header, guard or flag sweep.
Future line source changes still require an independent producer/consumer fact.

Private `.analysis/line-backend-comparisons-20261018/` retains the complete trace,
full two-function comparison, role proof, source/tool identities and independent
reviews. The observer uses an owned kill-on-close Job, rejects extra C2 threads,
restores its entry breakpoint after the saved return address and bounds every
helper call. Timeout cleanup is limited to the owned tree; finally checks all
canonical inputs and products. Only observed compiler process memory is patched;
no tool file or emitted game code is modified. One CPU/35%, memory high640MiB/
max768MiB hold; peak210,264,064 bytes and zero high/max/OOM events are recorded.
No native/MinGW game build, runtime case, relink, game or full replay follows.

Archive/member-hash verification precedes removal of16 closed raw files:13
copied project inputs, two objects and the observer executable. Net allocated
storage released is208,896 bytes after archive/journal costs. Primary trace,
proofs and current tested products remain; no unused observer binary is kept.

## Fixed role-rank declaration inference, October 18

A subsequent independent calculation reproduces all 110 input ranks across
the 55 observed line events. The original comparison directions require
`Ri >= Rdx >= Rdy`; preserving the already matching error operations also
requires `Rerror >= Rdx`. One fixed `dy, dx, i, error = 0` declaration cohort
inside the existing coordinate block realizes those constraints under the
observed key-cohort model. This is an inferred declaration, not recovered
original names or a unique source order. No permutation search follows.

One canonical-path compile restores all three comparison directions, but
changes the original `i/error/dx` homes from `-4/-8/-12` to `-12/-4/-8`.
`dy` stays at `-16`. The complete 445-byte, 121-instruction line consequently
has 22 differing EBP-displacement bytes instead of nine comparison bytes.
Every other byte, all 16 branches, three calls and the 140-byte frame extent
agree; the 85-byte fill companion remains exact. A role-normalized comparison
explains the result but does not establish exactness. Reject the whole model
and retain the canonical source and objects. No follow-up declaration variant
is queued; this failure does not prove source optimality or impossibility.

Private `.analysis/line-rank-constraints-20261018/` and
`.analysis/line-rank-declarations-20261018/` retain the complete mathematical
review, actual full-body output, independent result review and identities.
All 13 compiler inputs and six protected authorities/products are restored.
The single compile takes 6.103 seconds, peaks at 273,899,520 bytes under the
one-CPU/35% and 640–768 MiB caps, and records zero high/max/OOM events. There
is no provider query, native/MinGW build, game run, relink or full replay.
Archive/member verification precedes deletion of 16 obsolete files: 13 copied
inputs, two objects and the proposal. Net release after archive/journal is
61,440 allocated bytes; tested delivery and useful caches remain unchanged.
