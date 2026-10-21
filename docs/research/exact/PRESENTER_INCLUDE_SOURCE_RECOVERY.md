# Exact dirty-region presenter through source context

October22,2026. The complete984-byte `dxball_present_regions_now` at0x409100 is
now byte-exact, closing the two remaining top-index load differences. All17
prior display exacts survive; the other18 complete code identities are unchanged.
Acceptance reaches **264/270 authored functions (97.78%) and78,686/84,968
complete exact code bytes (92.61%)**. Six authored candidates /6,282 original
bytes remain. Overall acceptance is409 functions /93,070 code bytes /244 metadata
bytes, across51 current authored compiler closures. The goal remains incomplete.

## Accepted shared source

The entire implementation change is in `src/display.cpp`: include the already
consumed `clock_api.h` immediately before `display.h`, and move the unchanged
complete `dxball_blt_effect_sprite` definition after `dxball_present`, before
the presenter. All headers, globals, function bodies, local declarations,
types, expressions, calls and actual state writes stay unchanged. Native and
legacy builds use this same source and the existing20-input/nine-flag recipe.

Clock-first alone makes the presenter984/0 but loses restore-regions,846/746
instead of827/0. Moving Blt after restoration restores827/0 but loses Blt,
366/332 instead of362/0. Moving that same body after presentation recovers
362/0 while preserving both other matches and every prior exact. This selects
one coherent whole object; no earlier winning function or object is borrowed.

These are permitted finite source-organization hypotheses under the standing
search policy, not uniquely recovered historical includes, definition order or
compiler IDs. The observed output selects the model. Root LOAD ranks, global
declaration keys and member/address scheduling are not treated as interchangeable
or claimed as newly observed compiler internals.

## Closed finite controls

The [previous index work](PRESENT_INDEX_DECLARATIONS.md) supplies the original
two-difference checkpoint and complete246-instruction correspondence. This
follow-up reuses it and the existing original dossiers without a provider import.

| New family | Successful compiles | Complete result / disposition |
| --- | ---: | --- |
| One real record for both consumed indices |1|984/12; loses sort; reject.|
| Four consumed-include orders |4|Clock-first gives984/0 with only restore lost; the other contexts give984/2 with zero or multiple prior losses.|
| Move the real board/display binding setters |3|Each retains presenter0 but does not repair restore; reject.|
| Reorder three genuine dirty-state header declarations |5|Same clock-first code results; reject without compiling the other24 header-dependent owners. No header change is adopted.|
| Reorder the three real dirty-state definitions |5|Same clock-first code results; reject. Only the three named BSS symbol offsets may vary; raw noncode payloads/relocations stay checked.|
| Move real functions containing consumed locals |3|Moving Blt after restore gives presenter0/restore0 with only Blt lost; the two other models retain losses.|
| A volatile page-reference view in restore |1|Presenter984/6 and sort loss; reject.|
| Move Blt after present |1|Presenter984/0 and all17 prior exacts; adopt. Two other frozen positions remain uncompiled.|

Exactly23 distinct frozen input/flag digests compile once each. Their complete
comparisons cover437 original-function instances and9453 actual code-binding
occurrences. All successful outputs and failure-free producer statuses are
retained; adoption reuses the selected output. A preparation-only page-read
count assertion is corrected to the actual22 source reads before that family's first producer;
it is not a failed or repeated compile.

## Complete proof and maintained checks

The selected whole display object compares all19 complete original functions
and411 actual code bindings. Original instruction bytes, relocation targets,
types/addends and the maintained exact local-target guard stay strict. Full
noncode sections, global definitions/offsets, initialized callback relocations
and the57-byte nonoriginal portable bridge remain identical. There are no
literals or attached metadata in this owner. Last-brick remains1047/976 with
its previous resolved identity; it is still explicitly nonexact.

The accepted presenter resolved/original SHA-256 is
`a2cd2f97c9ddfacd26090775105b477e6331d0a74d0872fd249be6c4ff1e391b`.
After installation, all19 canonical units reproduce the complete selected
comparison using the installed object, without another compiler invocation.
Tracking and progress generation pass. All249 historical semantic rows retain
their case counts/order/scopes/oracle identities; current source/dependency
hashes refresh without replaying their full historical sets.

Native incremental build changes only display.cpp and its shared-library link,
preserving59 companion objects and all62 prior command configurations. The
unchanged existing267-call selector passes: sort60, merge146, presentation60
and reset1. It preserves the sort RNG history before random merge vectors,
full setup/state and ordered COM events. The verified fixture cache remains a
hit; both cache files stay unchanged with zero preparation/rebuild invocations.

Heavy work stays serial on CPU0/35%, memory384/512MiB. The observed compiler
scope peak is156,643,328 bytes; the focused native scope peaks at59,031,552
bytes, with no memory events. No game relink/play, full campaign or physical
driver claim follows. The previously tested game delivery remains historical.

Private authority is
`.analysis/display-blt-position-source-search-20261022/current-checkpoint.json`,
with the selected `after-present` producer/comparison, installed comparison,
native summary and adoption. All seven closed family directories retain their
unique frozen inputs, outputs, plans and observations through a member-size/
SHA/mode verified archive before obsolete copies are removed. Current tested
products and useful caches stay live.
Cleanup verifies652 archive members and retires628 obsolete files, releasing
8,097,792 allocated bytes net of the archive before the small index/receipts.
The overwritten checkpoint's rollback archive is recoverable inside it.
