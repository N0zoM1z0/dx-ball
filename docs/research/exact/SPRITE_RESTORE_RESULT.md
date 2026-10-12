# Sprite Restore result storage

The later [sprite recovery state](EXACT_SPRITE_RECOVERY_STATE.md) makes the
complete282-byte body exact, including its original homes and address schedule.
The comparisons below describe the preceding result-only checkpoint.

The sprite-bank recovery body at `0x403D30` now restores its observed discarded
32-bit Restore HRESULT write. The source captures that result in the actual
nonnull sprite/surface branch and deliberately leaves it unchecked. A failure
still proceeds through the remaining slots and bank reload. The existing bank
and slot declarations stay unchanged.

The retained original dossier is
`ev_6086488847b0abeff3f7ed6af657fd76f1d18d085752c4ae7c38ff49c74b9d94`,
in the closed 2026-10-07 10:33 interactive archive. It covers the complete
contiguous `0x403D30..0x403E49` span: 282 bytes, 85 instructions, ten branches
and two calls. `0x403E08` calls COM Restore at vtable offset `0x6C`;
`0x403E0B` stores EAX at EBP-8, without a subsequent read or HRESULT condition.
The observed store establishes the operation; whether the authored source used
an explicit local or compiler-generated result storage remains unresolved.
The recovered source does not establish original variable spelling or scope.

The maintained body now emits all **282 bytes**, improving the strict complete
comparison from **279/282 bytes with 80 differences to 282/282 with 18**.
Every original instruction boundary and width agrees. All operations, registers,
arithmetic, branches and calls agree through an explicit local-home mapping:

| Role | Original EBP displacement | Current EBP displacement |
| --- | ---: | ---: |
| Bank index | -4 | -8 |
| Discarded Restore HRESULT | -8 | -12 |
| Sprite slot | -12 | -4 |

Both frames contain 12 bytes. All eighteen differences are actual EBP
displacement bytes; no normalization or masking removes them from the strict
comparison. **This remains a candidate, not an exact function.**

Seven actual relocations retain their ordered types, symbols, addends and
independently observed targets. The newly restored three-byte store moves only
the bank-filename relocation from offset 240 to 243 and the reload call from
257 to 260. Both new positions are grounded in the original instructions.
The initial comparison consumer rejected stale offsets; its completed compiler
output was retained and compared after reconciliation, without recompiling.

Two preceding scope hypotheses are retained privately. Moving only the slot
counter into the scan gave 279 bytes/128 differences; capturing the return while
also scoping the scan gave 282/67. Both changed the array-address instruction
schedule. Neither is maintained. The accepted source keeps the original scan
declarations and only restores the observed return store. Three actual device
MT compilations occurred in total, one per source hypothesis; do not repeat the
closed scan-scope hypotheses or trial names/layouts to force remaining homes.

All four exact device companions retain their complete 526 bytes and bindings.
The palette-transition candidate's entire comparison record is unchanged.
Native and MinGW builds pass; the final matching device object links with
35 verified unchanged VC4 objects, with no additional legacy source compilation.
Three unchanged Oracle loops pass **64 sprite-bank cases, 63 surface-recovery
cases and eight connected lost-surface presentations**. They compare full
relevant state and ordered COM/reload calls, including null slots and ignored
sprite failures. Controlled COM and resource boundaries do not establish
physical rendering, audio or complete campaign fidelity.

All 206 current exact input closures, 247 historical semantic scopes and
36 game objects verify. The 235 affected historical input inventories refresh;
their prior scopes and case counts are retained, not reexecuted. Totals remain
206 exact / 44,406 code bytes / 136 metadata bytes; 283 source-present and
270 authored inventory entries. The full source denominator remains unproved.

Inputs, products, instruction correspondence, complete comparisons, unchanged
case identities and all compiler stages are preserved under
`.analysis/sprite-restore-result-only/`, `.analysis/sprite-bank-scan-scope/`
and `.analysis/sprite-restore-result/`. Current products are identified by
`.analysis/sprite-restore-result-only/product-verification.json`; the independent
seal is `.analysis/checkpoints/sprite-restore-result-283-206/sha256.json`.
