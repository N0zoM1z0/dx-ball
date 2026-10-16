# SEH collision callback and omitted CRT entries

The complete `__unwind_handler` at `0x004183CC` now has natural C source in
`runtime_seh.c`. It returns ContinueSearch without writing the dispatcher output
when neither unwind flag is set. Unwind or exit-unwind (mask 6) stores the
establisher frame through that output and returns CollidedUnwind. The third
context argument is unused. The header describes only the two consumed
EXCEPTION_RECORD words; its code word is a real field preceding flags.

The original 34-byte callback has no relocations and ends at its RET before
`__local_unwind2`. Both branch paths are decoded completely. Unlike neighboring
transport helpers, it has no CLD, FS access or implicit register input. The
surrounding local-unwind code installs its actual address as a handler, and the
abnormal-termination helper compares the registration's handler with that address.
The prior whole `exsup.obj` proof independently grounds both operands.

VC4 produces 31 bytes, with 34 differing positions across the complete 34-byte
comparison. Its byte-sized mask test and caller-clobbered register/scheduling
choices differ from the assembler original's full-word test. Both implement the
same callback on the backed record. No assembly, volatile read, artificial local
or copied instruction body forces an exact result. This is one new source body
and one complete candidate, with **no new exact claim**.

A focused x86 emulation compares the complete original and VC4 bodies in 142
cases. It checks cdecl return/stack transport, the complete write trace and the
dispatcher result. Cases include every single flag bit, combined/high-bit flags,
null and opaque frame values, an inaccessible unused context, and inaccessible
dispatcher addresses on non-unwind paths. All agree. Native and i686 C90 builds
also pass with warnings as errors. These are standalone compiler/emulation
checks, without physical Windows unwinding or game integration. The 249
historical semantic scopes remain unchanged.

## Inventory reconciliation

Sixteen external type-32 definitions were absent from the independent inventory.
Their member identities, actual symbol indices and entry intervals now agree
with the retained original bytes. All previous entries and extents are preserved.

| Entry | Address | Entry interval bytes |
| --- | --- | ---: |
| `__unwind_handler` | `0x004183CC` | 34 |
| `__except_handler3` | `0x0041C724` | 189 |
| `__adj_fdiv_r` | `0x00416907` | 1,183 |
| `__adj_fdiv_m16i` | `0x00416E64` | 52 |
| `__adj_fdivr_m16i` | `0x00416F64` | 52 |
| `__adj_fdivr_m32i` | `0x00416F98` | 52 |
| `__safe_fdiv` | `0x00416FCC` | 21 |
| `__safe_fdivr` | `0x00416FE1` | 21 |
| `__fprem_common` | `0x00416FF6` | 518 |
| `__adj_fprem` | `0x004171FC` | 178 |
| `__fprem1_common` | `0x004172AE` | 518 |
| `__adj_fprem1` | `0x004174B4` | 181 |
| `__safe_fprem` | `0x00417569` | 6 |
| `__safe_fprem1` | `0x0041756F` | 6 |
| `__adj_fpatan` | `0x00417575` | 3 |
| `__adj_fptan` | `0x00417578` | 3 |

An entry interval ends at the next named definition or section end. Some entries
use shared code, x87 operands, indirect dispatch or other machine state; that
interval alone is not an independent full-function source/exact claim. The
eight-byte prefix before `__except_handler3` is excluded from its entry. No
ordinary C prototypes are invented for the other fifteen entries.

The retained origin report still has current inputs. Its complete code proofs
cover `exsup.obj` 238 bytes/six relocations, `exsup3.obj` 224/five, and the atomic
`adj_fdiv.obj` code/data group 3,467/21 plus 352/64. Reapplying those already
grounded bindings matches all four sections, including the full dispatch table.
Original code agrees with REA Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`;
the FDIV data also agrees with
`ev_5176e8ed2bd57ff9721f2a44761480e9f6538457d72aea989f5bed9b49324d70`.
No provider session or historical origin queue is repeated.

Current totals are 540 independent entries plus 24 parent-owned fragments,
465 source entries, 376 exacts/76,908 code bytes/244 metadata bytes, and 89
complete candidates (34 authored/54 runtime/one compiler-generated). Seventy-five
entries still lack source. Origins are 270 authored/240 runtime/21
compiler-generated/nine unknown. The larger remaining inventory exposes the
omissions; it does not represent lost source recovery.

Only the new independent compiler recipe/candidate is added. All 376 preceding
exact and 88 candidate results, recipes, inputs and products are reused after
identity checks. Their manifest identities refresh; no full replay runs.
Private boundaries, control edges, compiler products and differential evidence:
`.analysis/crt-omitted-entries-20261016/`.
