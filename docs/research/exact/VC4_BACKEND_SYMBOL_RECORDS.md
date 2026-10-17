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
the provider's limitations; full assembly of that procedure was not requested.
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
