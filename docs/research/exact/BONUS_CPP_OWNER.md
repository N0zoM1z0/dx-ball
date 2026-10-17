# Bonus implementation language boundary

On October 17, the complete `update-bonuses` span at `0x413E20` becomes
exact: **2,168 bytes, 180 → 0 differences**. Its resolved SHA-256 is
`711d52eae639b72b135468c5d589826f1af7a5c50057074e6548ceeb715e3f1f`.
Generation remains exact at 1,197 bytes, drawing at 87 and retirement at 32:
all three prior code identities, totaling 1,316 bytes, survive the same compile.
Current totals become 392 exact functions / 84,410 code bytes / 244 attached
metadata bytes, with 23 authored and 60 runtime candidates.

## Source inference and complete comparison

The maintained owner is now [`src/bonuses.cpp`](../../../src/bonuses.cpp).
Its project includes retain their complete order inside an `extern "C"` block;
`stdlib.h` follows that block. The entire subsequent implementation is unchanged.
All four function bodies, ten global definitions and five fastcall helper APIs
retain their source expressions and C linkage. This tests the C++ frontend and
the full current C++ header view together; it does not isolate either cause or
uniquely establish the original implementation language.

The preceding C comparison's 180 differences belong to nine bank/slot address
producers starting at `414326`, `414354`, `414380`, `4143A8`, `4143D9`, `414432`,
`414460`, `4144BB` and `41457D`. Eight groups occupy 31 bytes and one 32.
Both versions compute `0x425980 + 1048 * bank + 4 * slot`, but the original
forms the bank component first. The shared C++ owner recovers every group;
all other relocated body bytes retain their original identities. No expression,
API, declaration-order, name or compiler-flag variants are tried.

One VC4 compile compares all four complete functions. The updater's 209 actual
relocations include the dispatch anchor and all 19 switch entries; same-section
destinations are checked against actual COFF definitions. All three references
to the full eight-byte `2.0` literal retain their actual addends `0, 4, 0`.
The original complete spans and retained REA evidence are documented in
[the bonus dossier](EXACT_BONUSES.md). No new provider query is needed.

## Production placement and affected checks

C++ changes the ten uninitialized integers from C common symbols to one real
40-byte `.bss` section. Their actual offsets are `0, 4, …, 36`; linked addresses
are writable and initially zero. This moves 157 of the 1,097 distinct mapped
names. It does not recover the original global layout.

The restored-CRT relink reuses all 116 verified source objects, from 113 owners
and three integration owners, with zero new compiles and the same 19 approved
original CRT members. The resulting EXE SHA-256 is
`bc06b8a7018a227259cb2fc8c2a4e1a2aa13eeff417c1c7f3a5f263e6831a17b`.
Before/after verification checks all four complete linked bonus functions and
3,162 actual source/CRT relocation fields referring to moved mapped data.
Private section locations follow reachable incoming relocations and their
complete contents are verified where needed. Two duplicate clock static names
use owner-qualified MAP anchors. Thirteen unreferenced, unmapped code COMDATs
are explicitly recorded as removed by `/OPT:REF`; independent review confirms
their lack of incoming relocations across all 135 source/CRT objects.

The seven board objects preserve offsets
`0, 20000, 20004, 20008, 20024, 20028, 20032` and the six-word terminal-copy ABI.
Resource payloads and the six OS DLL imports remain identical; there is no
MSVCRT DLL dependency. These checks are not a whole-PE byte-delta proof,
original data-layout exactness or a new game observation.

Native and MinGW each compile only this owner once using their retained valid
canonical CMake configuration, then perform required links with `--parallel 1`.
The unchanged existing matrices pass 912 updater calls, including 16 connected
calls, plus 1,750 generation, 180 retirement and nine drawing calls: **2,851
affected bonus calls**, plus one existing trig setup call. Full state, list
effects, poisoned frees, RNG scripts and ordered calls remain checked. No test
case or fixture source changes, full historical replay or game run follow.

The 249 semantic ledger rows retain their case counts and scopes; 235 input
inventories move the owner path and refresh its identity. All 270 classified
authored entries have source and complete current receipts: 247 exact and 23
candidates across 29 compiler closures. Source optimality and the final authored
denominator remain open.

## Evidence and cleanup

Private phase `.analysis/bonus-cpp-owner-20261017/` retains the complete producer,
before-images, comparisons, relocation provenance, affected-flow reports,
incremental build receipts, linked verification and independent review.
The initial linked verifier's missing-anchor failure is retained with its
correction: the bitmap loader's entire public COMDAT was discarded, rather than
being a private helper. Neither verifier correction requires rebuilding.

The phase cleanup receipt records a member-hash-verified archive before removal
of 56 temporary input/product files and eight obsolete or duplicate build
products, releasing 8,990,720 allocated bytes net of the archive (about 8.57 MiB;
receipt costs excluded). Allocation accounting respects inode link counts. Current C++ objects, tested products, canonical configuration
caches and unique evidence remain available. Current records supersede the
historical C-owner comparison without invalidating its retained evidence.
