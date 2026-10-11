# Complete CRT code and pointer-bearing data groups

Eight previously unknown FDIV entries are now grounded in a complete pinned
CRT code/data pair. Origins become 270 authored / 113 runtime / 42
compiler-generated / 103 unknown. Source 283, scoped semantic 247 and game
exact 188 / 35,003 code bytes / 136 metadata bytes remain unchanged.

The prior data investigation independently located two storage bases from
unique nonrelocated subobjects, but their pointer targets remained unverified.
That partial placement was insufficient binding authority. The new verifier
places both code and data independently, compares both complete sections, and
publishes the group's actual member-index definitions only after every check
and receipt guard passes. A failed group publishes no definitions.

| Member | Code base / bytes | Independent code anchor | Data base / bytes | Independent data anchor |
| --- | --- | --- | --- | --- |
| `87trig.obj` | `0x418960` / 43 | First 39 bytes | `0x423120` / 114 | First 18 initialized bytes |
| `adj_fdiv.obj` | `0x4167F0` / 3,467 | Offset 292, 1,793 bytes | `0x422F30` / 352 | `fprem_risc_table`, offset 28, 24 bytes |

Each anchor is nonzero, lies completely outside relocation fields and is unique
across the original executable carrier. Actual file offsets and the PE mapping
determine each section base. Relocation fields do not supply guessed target
addresses. Full code then agrees with the complete retained original read and
PE; full data agrees with the PE and a new complete REA observation. Code/data
section identities, entire extents, actual symbol indices/storage/values,
existing external bindings and every relocation are checked.

Trigonometric code has one code relocation and twelve data relocations. Its
single external target is the previously verified `__rtindfnpop`; local code
definitions then close the sine/cosine/tangent table targets. FDIV has 21 code
relocations to its data and 64 data relocations to its code. All belong to the
same actual member and close together. Provisional local addresses remain
private to the group's comparison; they cannot authorize other callers before
both whole sections pass. Cross-section receipts explicitly identify the
complete atomic group, rather than claiming an earlier independent section.

The imported function inventory omits the trigonometric assembly entry at
`0x418960`. Unknown-only and all-row discovery therefore fail to locate its
43-byte extent. Independent code bytes resolve that missing ownership without
inventing an inventory row. There are 23 decoded instructions in all 43 bytes,
and 1,095 in all 3,467 FDIV bytes. The eight reclassified rows are:

`0x4167F0`, `0x416DA6`, `0x416DB9`, `0x416DCC`, `0x416E18`, `0x416E98`,
`0x416ECC`, `0x416F18`.

The new maintained helper is `scripts/crt_coupled.py`, invoked by the existing
runtime-section verifier after its independently verified preceding sections.
One positive run preserves every previous 83-code-section/12-data-section
result row exactly. Three bounded helper controls reject a shifted data base,
a partial code extent and an altered dispatch pointer at offset 94. All three
leave the caller's member-scoped authority unchanged. Original target/library
payloads stay fixed; the corrupt carrier is a separate retained fixture.

Current maintained scope is 85 complete code sections / 13,760 bytes / 103
declared origin entries, 14 data sections / 2,997 bytes and 380 actual scoped
definitions, including 212 static definitions. Original code spans are disjoint
in this scope: the new 3,510 bytes also increase distinct coverage by 3,510.
Code provenance bytes remain separate from game exact-code totals. The actual
candidate-path verification receipt is retained unchanged; the published
recipe is a byte/hash-identical alias, recorded explicitly.

Original complete code Evidence is reused:
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
One closed REA 6.3/Ghidra 12.1.4 session reads the two missing data extents:

- 114 bytes: `ev_f585a80429f6f35d273f39b3a7cd2b5c0ab75c5c2a4f84a4037271fa1621974b`.
- 352 bytes: `ev_5176e8ed2bd57ff9721f2a44761480e9f6538457d72aea989f5bed9b49324d70`.

Run: `2026-10-11T04-40-02.986Z-requests-1720639`. First read takes
66,497.05 ms; the second takes 1.64 ms. Serialized carriers total 7,982 bytes
for 466 original bytes. These are provider log timings/file sizes, not model
tokens, measured peak RSS or end-to-end savings. The existing 512 MiB heap
configuration and one-provider/one-CPU workflow remain. No function dossier,
setup, doctor or historical snapshot replay occurs.

No game source, maintained gameplay test, compiler, production build or runtime
case changes. Four current products remain those of the window-switch
checkpoint. Complete library provenance does not prove the unique original
link selection, full authored denominator, source spelling, physical x87
hardware behavior or synchronized rendering/audio fidelity.

Private proof: `.analysis/crt-pointer-storage/`. Immutable seal:
`.analysis/checkpoints/crt-pointer-storage-283-188/sha256.json`.
The earlier assert/transcendental partial data and unresolved BSS remain open.
The next step requires an independent placement or full code/data authority;
do not repeat an unchanged seeded scan or infer globals from observed fields.
All REA feedback remains in the user's one existing `/tmp` document.
