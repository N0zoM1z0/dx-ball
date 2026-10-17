# Compiler fragments belong to their complete C++ owners

Twenty-four old auto-analysis entries overlap the complete triangle and
fixed-point functions already restored in `src/raster.cpp`. They are now
recorded in `config/compiler-fragments.csv`, with every original address,
extent, name, parent unit and Evidence ID preserved. They are not independent
C/C++ function definitions and no longer duplicate the parent entries in
`functions.csv` or `function-origins.csv`.

| Complete parent | Unwind cleanups | Shared epilogue | Current complete comparison |
| --- | ---: | ---: | --- |
| Triangle, `0x0040AB90`, 1,710 bytes | 16 | 1 | 88 code differences; 160 metadata bytes exact |
| Division, `0x0040B2D0`, 182 bytes | 2 | 1 | Code and 56 metadata bytes exact |
| Comparison, `0x0040B3C0`, 129 bytes | 1 | 1 | Code and 40 metadata bytes exact |
| Addition, `0x0040B450`, 110 bytes | 1 | 1 | Code and 40 metadata bytes exact |

This table lists the retired auto-analysis rows, not every internal block.
The complete parent comparisons also retain the additional conditional-return
cleanup and handler blocks that were never standalone inventory rows.
The later [original PE relocation audit](CRT_SUFFIX_OWNERSHIP.md#original-pe-code-address-relocations)
independently checks their registered addresses. All four ten-byte handlers
match the current compiled parent sections:0x40B226,0x40B36B,0x40B426 and0x40B4A3.
Each supplies its own FuncInfo in EAX before jumping to runtime0x418570. The
division metadata also references the existing conditional cleanup0x40B346.
None adds an independent source definition or exact-function claim; the table
continues to count the24 retired auto-analysis rows only.

## Ownership evidence

Each of the twenty nine-byte entries loads a fixed-point object's address from
the live parent frame, calls the existing destructor at `0x0040B260`, and
returns. Its original address is a relocation target in the parent's complete
unwind metadata. The current COFF target is a local label in that same
single-function code section, rather than a separate function COMDAT. These
are ordinary C++ object-lifetime emissions, already supplied by the parent
source and its actual constructors/destructor/operators.

The four other entries restore the parent's FS/stack/register state and return
at the exact end of its complete extent. They consume the parent's live EBP
and saved frame state; treating them as independent zero-argument functions
was an auto-analysis split. The shared epilogues are 14 bytes for triangle and
17 bytes for each of the three methods. All four are inside the same compiled
section as their parent definition.

The complete current object and input closure match the retained canonical
producer. Fresh reader comparisons reproduce all four retained parent results,
including every actual relocation and complete metadata block. No compiler
was rerun. Triangle remains nonexact; moving its generated fragments does not
create exact claims or remove any of its differences.

Retained REA 4.1 / Ghidra 12.1.4 byte records cover every retired range:

- Triangle tail, 168 bytes:
  `ev_4af9d8adb831616c11cd7ebb0df5dd4803ee50949a47e165dce19938e3284bb0`.
- Division tail, 80 bytes:
  `ev_aa5c0b2bf58c7d4c4bd771c848694a8b3a5bc2657fcf190914cbc0c4bcb13d2a`.
- Comparison tail, 36 bytes:
  `ev_2c2b4ae82da6458b42ca232f5750aa842da94b1958294cb0caa9c4b802277ee8`.
- Addition tail, 36 bytes:
  `ev_795fdc5edce200712d9b7ac9b38a3f49df961ce65494e746c8e0b352966e3859`.

These records remain under
`.analysis/rea/runs/2026-10-09T14-02-09.992Z-interactive-868197/`.
Their complete bytes still match the verified target. They are reused records,
not new REA 6.5 queries. The source/lifetime reconstruction is described in
[fixed-point recovery](EXACT_FIXED_POINT.md).

The reconciliation proof retains all old rows, the current producer/input
identity, fragment mappings and fresh complete parent comparisons at
`.analysis/compiler-fragment-ownership-20261016/verification.json`.
`validate-tracking.py` now checks parent containment, source/build identity,
actual configured unwind bindings or final-epilogue extent, and exclusion from
independent source/exact/semantic ledgers. This preserves the callback addresses
without counting overlapping code twice.

## Accounting and scope

The inventory is now **520 independent entries plus 24 parent-owned compiler
fragments**, covering the same 544 recorded addresses as before. Source remains
**464**, exact remains **373**, with **76,842 code / 244 metadata bytes**. The
source, exact and semantic ledgers, every recipe and every game/runtime source
file are unchanged. No code-byte gain or new semantic acceptance is claimed.

The independent origins are 270 authored, 214 runtime, 21 compiler-generated
and 15 unknown. The 24 archived fragments remain explicitly compiler-generated.
There are 56 independent entries without source rows; another 91 source-present
entries are not exact, comprising 88 complete candidates and three allocator
comparison gaps. Authored scope is unchanged, and the full reconstruction
objective remains open. No provider, compiler, runtime test or game build was
run for this reconciliation.
