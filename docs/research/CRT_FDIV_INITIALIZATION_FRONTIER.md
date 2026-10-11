# CRT FDIV initialization frontier

The complete 278-byte multiprocessing FDIV test at `0x418C50` now has pinned
CRT origin evidence, including all twelve actual relocations. One imported
unknown entry becomes runtime: 270 authored / 114 runtime / 42 compiler-generated
/ 102 unknown. Game source 283, semantic scopes 247 and exact 188 / 35,003 code
bytes / 136 metadata bytes remain unchanged. Current products remain those of
`.analysis/pcx-packet-loop/product-verification.json`.

## Independently placed code and strings

The actual `testfdiv.obj` member is at archive header offset 997722, SHA-256
`ba7e32f4909af498435d8d48bb567aab92221d3a55f0ce2d4b7ecf4cf3eb7e7b`.
Its already verified 79-byte `__ms_p5_test_fdiv` body is at `0x418C00`.
The new section's address independently follows a unique nonrelocated code
run, before resolving any relocation field. Five complete initialized strings
are unique in the original carrier and determine their own section addresses:

| Address | Bytes | Complete string | Section |
| --- | ---: | --- | ---: |
| `0x423194` | 17 | `GetCurrentThread\0` | 5 |
| `0x4231A8` | 22 | `SetThreadAffinityMask\0` | 6 |
| `0x4231C0` | 18 | `GetCurrentProcess\0` | 7 |
| `0x4231D4` | 23 | `GetProcessAffinityMask\0` | 8 |
| `0x4231EC` | 9 | `KERNEL32\0` | 9 |

The twelve fields resolve through these independently placed 89 bytes, the
already verified test body, and named PE IAT cells for LoadLibraryA and
GetProcAddress. No observed field supplies a guessed symbol address. The
whole relocated section agrees with complete retained original code Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12` and the PE.
The actual member/index/storage/value identities remain scoped to their member.

A separate complete relocation-free `__positive` body from `cvt.obj`, section 6,
uniquely matches 23 bytes at `0x418E40`. That entry is absent from the imported
function inventory; the verified section and its definitions are retained
without inventing a new function row or expanding the authored denominator.
Five related members were inspected. Unused initialized extents and unresolved
code/data dependencies remain diagnostic; no unchanged full-library scan occurs.

Current maintained scope is 87 complete code sections / 14,061 disjoint code
bytes / 104 declared origin entries, 19 data sections / 3,086 bytes, and 394
actual scoped definitions including 219 static definitions. Every preceding
85-code-section and 14-data-section result row survives unchanged. These CRT
provenance bytes remain separate from game exact-code totals.

## Complete small-string validation

The maintained data helper now supports `unique_initialized_string` explicitly.
It requires a whole relocation-free initialized section, an actual external
MSVC string-literal symbol at offset zero, at least eight printable ASCII
characters followed by exactly one terminal NUL, and unique placement across
the original carrier. Complete REA and PE bytes must agree before publication.
This accepts the nine-byte library name without relaxing the existing minimum
of sixteen bytes for untyped initialized constants.

One positive maintained verification and four bounded negative controls pass.
The controls reject an eight-byte partial extent, a shifted address, an untyped
short-constant declaration and a static `.data` symbol posing as a literal.
They publish no reports and preserve the positive receipt. The observed
candidate recipe is published as a byte/hash-identical alias; the actual
candidate-path receipt is retained unchanged.

## Remaining floating-point initialization storage

`fpinit.obj`, archive header offset 936384, defines `__adjust_fdiv` at offset 12
in a 28-byte initialized data section. A unique nonrelocated sixteen-byte prefix
independently places the section at `0x423090`. The initial four words are
`0x9875`, `0x9873`, zero and zero, corresponding to `__fltused`, `__ldused`,
`___fastflag` and the candidate `__adjust_fdiv` at `0x42309C`.

The final twelve bytes are three pointer slots: observed `__FPinit` points to
`0x417580`; both thread callbacks point to `0x4175A0`. Those values are
observations, not independent code binding authority. The complete 28 bytes
have now been observed, but `__fpmath`, `__fpclear`, conversion initialization
and their dependencies have not closed as a complete pinned code/data group.
No partial section definitions, including `__adjust_fdiv`, are published.
Remaining conversion-table, locale and BSS placements need independent authority;
do not solve an address from an observed code field merely to fit a relocation.

## REA and preservation

One closed REA 6.3 / Ghidra 12.1.4 session reads the five consumed strings and
the 28-byte diagnostic initialization extent: 117 original bytes in total.
Run `2026-10-11T05-19-29.800Z-requests-1762049`; six retained carriers total
18,787 bytes. Provider read timings are 53,374.63 ms, then 1.17, 1.03, 5.33,
1.15 and 7.21 ms. These are provider log timings and retained serialized file
sizes, not model tokens or peak memory. The configured heap remains 512 MiB,
with one provider on one CPU. Snapshot reports 41 Evidence records and seven
primitive cache entries. No setup, doctor or function/value-flow dossier runs.

Private evidence: `.analysis/crt-fdiv-control/`; immutable checkpoint:
`.analysis/checkpoints/crt-fdiv-control-283-188/sha256.json`.
Raw Evidence identities and digests are in `rea-observations.json`.
No game source, build, compiler or gameplay replay is needed. Full original
source, authored denominator, physical x87 hardware behavior and synchronized
rendering/audio fidelity remain unproved. Feedback continues only in
`/tmp/dxball_rea_feedback_20261010.md`.

This checkpoint preserves 62 owned files and 277 explicit immutable dependencies.
Eleven scoped archive links replace 1,433,600 previously single-link allocated
bytes, about 1.4 MiB; no device-free-space delta is claimed. Mutable current and
public paths remain on independent inodes. Unique Evidence, before inputs,
current products and probe objects stay. Cleanup is confined to the new seal.
No additional game/compiler/provider/case queue runs.
