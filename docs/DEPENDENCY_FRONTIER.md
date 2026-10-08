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

## Focused REA instruction review

A subsequent sequential REA `analyze_function` batch inspects five selected
entries with the pinned Ghidra provider. The complete dossiers and closed
session are retained. This supplies instruction contracts, not semantic
acceptance or a compiler/library attribution.

| Entry | Observed contract | REA Evidence |
| --- | --- | --- |
| `0x0041678C` | Convert x87 ST0 to signed 64-bit integer, temporarily selecting truncation toward zero; restore control word and return EDX:EAX | `ev_3a0b896bedfb7224268a3a8d3bfcb8d1acc636a35884319167561b64e8056aea` |
| `0x00416760` | Forward one stack argument to `0x00417750`; caller cleanup | `ev_dd4c8eb171fe4da4755816c3387814ad47a13e806c38958c44aa8cbc190e44ac` |
| `0x00416770` | Forward size and constant `1` to `0x00417790`; preserve returned EAX | `ev_2f47da62f234bfb025db282149258ce5cb1b53a74591f045695579a7d8887f91` |
| `0x00417910` | Forward argument and two zero constants to `0x00417950`; preserve returned EAX | `ev_df594328fa0899467c7969112f2ca49e255c91e1d3fb81b92b74f5e60db13234` |
| `0x00417DF0` | Return byte distance to the first zero byte; scan prefix to four-byte alignment, then aligned words | `ev_2771927e99efdb9e148301e8bf8aac67206ddd30c00c25219f34783b1586cd01` |

All five observed bodies are contiguous and match their imported sizes:
39/14/16/18/119 bytes. This reconciliation alone does not create an exact unit.

The floating conversion illustrates why the instruction evidence matters:
Ghidra's pseudocode says `ROUND`, but `OR AH, 0xc` selects x87 truncation
before `FISTP`. Likewise, the allocation wrapper's inferred `void` result
omits EAX forwarding, and the string scanner's inferred pointer result is an
integer byte distance. Neither inferred signature should be copied into C.
The scanner can read beyond a terminator within its aligned word; inaccessible
backing and exceptional floating conversions need explicit boundaries.

Existing closed REA dossiers supply two downstream contracts without another
query. Release at `0x00417750`, Evidence
`ev_71abe55c26ab63d390b070c27874d920fa335c74cc9b406dcdab748a7f3bdd33`,
skips a null pointer and otherwise calls `HeapFree` with heap `0x00440D70` and
zero flags. Allocation at `0x00417790`, Evidence
`ev_5b84dc43a44b86e3cd73f1ebfddc73bdb1f4ef29d11181f1d56181f54cc327b4`,
rejects unsigned sizes above `0xFFFFFFE0`, changes zero to one, and retries
allocation only when its handler flag and the handler result permit it.
The `0x00417950` backend and the allocation/handler dependencies need focused
review or matching saved evidence before any implementation acceptance.
Host allocation, release or string services remain dependency bridges until
the original implementations are separately recovered and validated. Names,
Ghidra's library match and these wrapper shapes do not establish a particular
VC4 library object. Function/origin/direct-case/exact ledgers remain unchanged.
