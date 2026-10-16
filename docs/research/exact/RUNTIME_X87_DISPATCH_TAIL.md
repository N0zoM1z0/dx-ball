# Two complete x87 C-dispatch routines

The pinned VC4 `87cdisp.obj` proves runtime origins for two previously unknown
entries. Their complete instruction bodies match the original executable:

| Entry | Address | Bytes | Actual COFF relocations |
| --- | --- | ---: | ---: |
| `__ctrandisp1` | `0x00418B75` | 44 | One REL32 to `__trandisp1` at `0x0041CA30` |
| `__fload` | `0x00418BA1` | 60 | None |

The original member is at archive header offset `0xE8ADE`. Both are external
type-32 function definitions in its 589-byte text section. The next definition
ends the first body; the section end terminates the second. Both end in RET,
decode completely and have no trailing omitted instructions. The complete
60-byte `__fload` body is unique in the executable and independently places the
section. The one external target already has a complete original `87disp.obj`
proof, reused from the earlier runtime-origin receipt. No address is inferred
from an unresolved BSS operand.

The review includes unrelocated relative control transfers. `__fload` branches
stay inside its 60-byte body. `__ctrandisp1` calls that loader, the independently
proven `__trandisp1`, and the shared entry at `0x00418A3E`. The latter falls into
the common BSS-dependent dispatcher. It remains a separate unresolved dependency;
matching the caller's complete body does not establish that dependency's source
or the whole 589-byte section. `LocalFac` and `intrinflag` remain unplaced.

The loader distinguishes exponent-all-ones operands before loading the x87
stack. Its explicit extended temporary and the dispatcher's saved control word
remain machine-level contracts. Ordinary host math forwarding is not their
restored source. This checkpoint adds **two runtime origins**, with no source,
exact, ABI or runtime acceptance claim. The origin inventory is now 270 authored,
221 runtime, 21 compiler-generated and eight unknown, across 520 independent
entries. The 24 parent-owned fragments remain separate.

The original bytes are checked against retained REA Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`,
under its original provider identity. No new analysis session, compiler or
runtime probe is needed for these two origin comparisons. Private extraction,
placement, every decoded control edge and full comparisons are retained in
`.analysis/crt-dispatch-tail-origins-20261016/`.

All 464 source entries, 376 accepted exacts, 88 complete candidates and 249
semantic rows retain byte-identical ledgers and comparison reports. The separate
scalar/intrinsic trig entry inventory observed in the same archive still needs
its own complete control-flow and binding review.
