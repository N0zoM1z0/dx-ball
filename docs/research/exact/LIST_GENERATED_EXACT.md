# Exact compiler-generated list initialization

The unchanged `list_initializers.cpp` source and its verified current canonical
VC4 product emit eight complete initializer pairs: an outer 21-byte stage and
an inner 26-byte root/constructor stage. All 16 bodies match every byte and
all 24 relocations, totaling 376 bytes. All 42 preceding exact units in the same
object are also re-compared and unchanged. No source or compiler flags changed.

These functions were already reconstructed through ordinary typed global
definitions but remained outside the exact ledger. Each new `source_generator`
record links the real declaration, accepted constructor, inner stage and actual
COFF symbol. Tracking requires compiler-generated provenance, an exact row,
the declaration and constructor definition, and the exact stage relocation
shape; ordinary source-definition checks remain unchanged. No manual wrapper
or synthetic storage is introduced.

Source-emission coverage now includes these 16 entries, not 16 new authored
routines. Authored provenance remains 270; inventory remains 543. Current
totals are source448/exact333/code69,468, attached metadata136 and candidates106.
All 317 preceding exacts, 106 candidates and 249 semantic rows are preserved.

The embedded board-storage initializer pair is still excluded because its
source-only aggregate constructor lacks an attested original address. No whole
startup graph, CRT-table placement or execution claim follows from these units.
Complete original procedure Evidence is reused from the list-layout run of
October 9. Current comparisons and frozen inputs/products are retained under
`.analysis/list-generated-exact-20261014/`. No compilation, provider, runtime or
game test was repeated.
