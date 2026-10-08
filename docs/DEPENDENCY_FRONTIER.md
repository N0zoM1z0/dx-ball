# Dependencies reached from maintained functions

A bounded review of saved REA `analyze_function` records identifies the next
supporting contracts to inspect after the connected gameplay owners. It reuses
closed, target-matching Ghidra records; no new binary query or provider import
was needed. This is a static dependency inventory, not additional function
acceptance or observed runtime coverage.

The review retains 179 Evidence records covering **174 of 222 maintained
entries**. Their callee lists reach **41 unmaintained imported entries**:
36 still have unknown origins, and five already have runtime classifications.
Those are copied ledger labels, not classifications inferred by this review.
Thirty dossiers exceed its 2 MiB per-record read boundary, and four are in runs
without a close record; all are excluded. Thus the other 48 maintained entries
and unrepresented computed/indirect calls remain outside this inventory.
External address namespaces such as `EXTERNAL:0x4f` stay separate from numeric
PE addresses.

The most frequently referenced targets in this bounded set are:

| Target | Saved candidate name | Distinct maintained callers | Provisional bytes |
| --- | --- | ---: | ---: |
| `0x0041678C` | `__ftol` | 8 | 39 |
| `0x00417910` | `FUN_00417910` | 7 | 18 |
| `0x00416760` | `FUN_00416760` | 7 | 14 |
| `0x00417DF0` | `FUN_00417df0` | 6 | 119 |
| `0x00417C40` | `_memset` | 6 | 88 |
| `0x004177F0` | `FUN_004177f0` | 6 | 7 |
| `0x00416770` | `FUN_00416770` | 5 | 16 |
| `0x0041F570` | `__ultoa` | 4 | 30 |

Names and sizes come from the existing imported inventory. A familiar library
name, a short wrapper or its location in the image does not establish its
implementation, provenance or reviewed extent.

For example, saved rebound Evidence
`ev_6055fe1d318fa3f71d76b5cdbbbe862a3944dd9890035a53264b8ccfa2d7a074`
and paddle-rendering Evidence
`ev_0b4d5d681d951be5b6a69ac1d9d09db3cc965811c767e0b2b4f7296609cc020a`
both list `0x0041678C`. Their caller contracts and compiler comparisons do not
accept that helper's body. Saved brick-effect constructor Evidence
`ev_6a32fd651ca3a7fb5d9cfda71f66a09b545b0a7baf59e584310935a7953e64af`
lists allocation entry `0x00416770`. The removal entry at `0x00412A50`, Evidence
`ev_15590b4df69e7901145c02e294dca11e8f4f9c5be7675b3a332149d8dddde90e`,
lists release entry `0x00416760`.
The [gameplay owner](GAMEPLAY_OWNER.md#linked-list-layout-and-dependencies)
already distinguishes its default host allocator from the original allocator
and new-handler behavior. Mapping an append call relocation does not recover
that dependency.

The next focused review should reconcile these supporting entries' instructions,
ABI, callees and failure paths through REA before proposing source or an origin
classification. Compiler/library attribution needs its own corroboration;
forwarding to a host service remains a bridge. Independent unused graphics
leaves can follow the dependencies needed by the connected game.

The private inventory `.analysis/maintained-call-frontier.json` binds the
current function/origin ledgers, its producer and each retained Evidence file
by SHA-256. It preserves the excluded-record list and per-target caller
references, so a later pass can expand the boundary without repeating the
existing queries. The accepted totals remain **222 maintained / 105,036 direct
cases / 36 exact units / 3,518 bytes**, with 300 unknown origins and six identified
runtime entries.
