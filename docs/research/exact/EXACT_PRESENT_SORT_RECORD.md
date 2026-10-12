# Exact presentation selection sort

`dxball_sort_present_regions` at `0x004094E0` now matches its complete
296-byte original body, including all ten actual COFF relocations. It sorts
the requested inclusive range by signed key and moves each key together with
its rectangle. Equal keys keep the existing selection; a selected index must
be greater than the output index before an exchange occurs.

The selected index and the rectangle/key exchange values form one 24-byte
selection record. Every field is consumed by the existing scan or exchange.
The output index belongs to the sorting block, and the scan index belongs to
each selection pass. These scopes place the original values at EBP-4 for the
selected index, EBP-8 for the exchange key, EBP-24 for its rectangle, EBP-28
for the output index and EBP-32 for the scan index. The original 32-byte frame
and complete instruction sequence agree, with zero differences.

Three canonical display compilations establish the source organization.
Separate exchange and cursor records produce 30 differences. A joint
selection record and nested cursor record restore the homes but retain eight
comparison-scheduling differences. Keeping ordinary loop indices in their
individual scopes removes those remaining differences. No statement, state
write or comparison relation changes; original identifier spelling is unknown.

Nine accepted display companions retain all 1,843 exact bytes. Presentation
remains a 984-byte candidate with two differences. The unchanged palette and
frame-wait candidates acquire three and six additional comparison bytes in
this compiler context; their operations and maintained source bodies are
unchanged. Complete current comparisons remain in the private receipt.

Linux and MinGW builds and a VC4 relink using 36 verified unchanged objects
succeed. Existing original/native loops pass 60 sorting, 146 merging and 60
presentation cases, plus their one-call reset prelude. Sorting preserves the
original RNG history before the merge vectors. All 215 accepted units and
their input closures verify: 49,218 code bytes, 136 separate metadata bytes
and 58 authored functions remaining nonexact. No game campaign runs.

The original contiguous body through RET reuses REA evidence
`ev_6fa464860fec11c6c9b89b25ac22ba8445585a8dba2390986ff40878fc054f10`,
operation 13 of run `2026-10-07T09-29-28.570Z-interactive-2776129`.
No new provider query is needed. Full compiler stages, before inputs, complete
comparisons, build logs and focused-case receipts are retained under
`.analysis/presentation-sort-records-20261012/`. Completed product copies are
compressed with full-byte verification.
