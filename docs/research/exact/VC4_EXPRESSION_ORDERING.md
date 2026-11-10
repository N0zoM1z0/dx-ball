# VC4 expression ordering observations

The October 2026 compiler investigation explains mechanisms that helped bound
source candidates. All authored game functions now match. These compiler facts
do not uniquely recover original names, frontend IDs or declarations. Use
[the current owners](README.md) and
[the source-candidate policy](../../agent/SOURCE_CANDIDATE_SEARCH.md) for new work.

The target is VC4 `c2.exe`, SHA-256
`820ed4e4930db97bcba646afb88fdb7d1f329631ca8e5b84096c0d6daa82e9a9`.
Related notes cover [symbol records](VC4_BACKEND_SYMBOL_RECORDS.md),
[frontend traversal](VC4_FRONTEND_SYMBOL_ORDER.md) and
[C frontend keys](VC4_C_FRONTEND_SYMBOL_KEYS.md).

## Actual ordering decision

The 58-byte helper at `0x413DED` swaps node children at `+0x0c` and `+0x10`
when the left unsigned rank is less than the right. Ties preserve order. It
returns the unsigned minimum. Attribute bit `0x10` gates opcode replacement
through `0x430323(opcode, 0)`, whose mode-zero table is at `0x481C0C`.
Opcodes `0x1f..0x24` map as `1f→1f`, `20→20`, `21↔23`, `22↔24`.
Their attributes are `0x6118`; source operator names were not established.

The caller at `0x408D62` conditionally visits the right child before the left,
then obtains the current rank through `0x40846E`. Attribute bit `0x8` and a
special path gate swapping. This traversal alone is not the final instruction
evaluation order, and not every node reaches the helper.

## Consumed record field

For opcode `0x26`, `0x40846E` reads the pointer at node `+0x14`, then the
32-bit field at record `+0x24`. A null record or kind `0x18` at record `+0x0c`
returns rank `0x10`. Otherwise the observed arithmetic is:

```text
k = u32(record + 0x24)
a = k >> 8
b = ((a - k) mod 2^32) >> 4
rank = 0x10 | ((b - a + k) & 0x0f)
```

Both shifts are logical. Only sixteen results exist, and rank is not monotonic
in the key: keys 16 and 18 yield 31 and 16. The reader at `0x41BB61` writes
integer-reader results to `+0x24`; `0x41A4C1` compares it with a lookup key.
The builder at `0x407575` installs the supplied record at node `+0x14`.
This connects a consumed key to ordering without identifying its original
frontend assignment rule.

## Output and storage boundaries

The observed `0x402F39` consumer and post-phase-six driver lead to byte-buffer
output at `0x41D6C8`/`0x41C920` and ModRM/SIB construction at `0x425DA1`.
Address IR, glyph/operand construction, physical-register assignment and final
COFF correspondence are distinct boundaries. A static path between them does
not prove a same-run original-game tuple.

Separate C1XX windows establish typed-record completion, parent construction,
selector tables and operand field copies. Preserve numeric selectors and actual
stores when reasoning about those windows. Do not name a field from an inferred
signature, collapse rereads without state/nonaliasing proof, or infer feasible
paths from every encoded branch destination. A selected raw instruction window
is not a complete original function or ABI proof.

The final bounded field-value observation returns one of two input pointers on
its selected local returns. External continuations and earlier side effects
remain outside that result. It does not recover a full historical argument
or prove that an incoming selector is globally unused.

## Source implications

Frontend hash traversal, sequential symbol IDs and C2 operand rank are separate
mechanisms. A name-only search need not address an ID-rank residual. A name
cannot move a local outside its allocation scope. Likewise, adjacency of stack
homes does not establish a source aggregate.

The fixed resource arithmetic family and several declaration/type controls
produced no acceptable whole-owner improvement. Keep those conclusions scoped
to their actual context. Later accepted source models changed meaningful scope,
type or translation-unit preconditions and passed complete comparisons; see
[closed controls](CLOSED_STORAGE_DIAGNOSTICS.md).

## Provider limits

A full C2 dossier exceeded REA's 10 MiB transport budget. Repeating that producer
is unnecessary: use the retained continuation with small native facets. See [REA operations](../../agent/REA.md). Cold compiler imports can take several minutes. Use the existing conclusions
before starting another import, and keep the project's current resource limits.
