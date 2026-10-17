# Surface drawing primitive owner

October18,2026. The maintained line and rectangle-fill functions now share
`src/drawing_primitives.cpp`. The complete source model restores three original
bytes in the residual right-palette loop,234/9→234/6 bytes/differences. Eight
other complete function identities, including all six prior exacts, survive.
There is no new exact: totals remain394 exacts and21 authored candidates.

## Source inference and complete comparison

The original entries403070 and403230 are adjacent low-level destination-surface
primitives. Line uses GetSurfaceDesc/Lock, writes pixels and unlocks; fill builds
the actual100-byte color FX and submits Blt. This supports one natural source
family without proving an original translation-unit boundary. Earlier whole-UI
C++ controls already tested member-call projection, but did not test this pair
as an independent implementation owner.

The new owner includes the complete unchanged `ui.h` and `device.h` under C
linkage. Device supplies the real color-fill record. The existing36-slot C++
surface interface is unchanged. Three line calls and one fill call use actual
virtual members; the FX cast preserves its address, size100 and fill-color
offset80. All other expressions, values, scopes, live reads, stores and call
order remain unchanged. Original C entry names and public prototypes remain.
The residual seven-function UI implementation stays C with the same headers.

Two private compiles compare all nine functions/38 actual bindings, with no
literal or metadata remapping. Final canonical compiles attest both files after
moving the original line annotation and adding the fill annotation. Those
comments change no tokens; all nine comparison results equal the fixed pilot.
Line stays445/9, fill stays85 exact and measure-text stays279/3.

Only three palette bytes change: offsets109/112/114. Loading `first`, comparing
the index and using JLE restores the original guard; previously the compiler
loaded the index, compared `first` and used JGE. Every changed byte becomes an
original byte; none loses an existing match. Full accounting checks66
instructions,16 frame bytes,27 frame accesses, eight branches and one call.
The remaining six green/blue frame displacements stay visible and nonexact.
This is partial recovery of one actual producer, not an isolated causal proof
about compiler ownership or unique historical source spelling.

## Integration and limits

Native and MinGW each compile only the two affected source files and reuse
their valid CMake caches. The unchanged existing486 line,12 fill and64 right-palette
cases pass:562 calls with full pixel buffers/row padding, palette flags, retry
counters and ordered effects. No new cases or relaxed assertions are added.
The249 semantic inventories refresh their actual source/build inputs; historical
case counts and scopes remain unchanged. Current classified authored coverage is
249 exact/21 candidates across30 verified compiler closures.

VC4 reuses117 source objects from114 owners plus three integration owners, with
zero additional source compiles at link time and the same19 approved CRT members.
All1,099 owner-qualified MAP records and1,097 distinct names are reconciled.
Five functions move within the UI code region. Their complete old/new bodies,
alignment and nine incoming relocation fields verify against actual COFF/MAP
placement. Twenty old loader-relocation RVAs are replaced by twenty proved new
ones. All1,064 changed PE bytes are confined to those bodies/alignment, actual
incoming fields, the fully checked loader table and six timestamp fields.
Resource payloads and six OS DLL imports are unchanged; no MSVCRT dependency.

Current image SHA-256:
`068d2e8bc904e8433d0fa9260ebc374cd9e3349947752ab0266bacb582fd3123`.
This linked-image proof is separate from historical GUI observations; no game,
new provider query or full replay runs. Work remains serial on one CPU under
CPU35%, memory high640MiB/max768MiB. Private
`.analysis/drawing-primitives-owner-20261018/` retains the original/source
correspondence, final producers, focused cases, independent reviews and linked
proof. It also records a diff-label correction, a staging annotation assumption,
the pre-link owner-count guard correction and the incoming-reference walker's
unrelated-relocation correction. None broadens acceptance or repeats cases.

After final independent review,43 copied inputs and obsolete products are
archived and every member hash verified before deletion. This includes six
objects and four superseded history files. Net released allocation is7,647,232
bytes after archive/journal costs. Current tested objects, executable and useful
Native/MinGW caches remain. A final tracking check passes553 inventory entries,
475 source-present and394 exact claims without replaying unaffected functions.
