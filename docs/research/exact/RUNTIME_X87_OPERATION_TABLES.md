# Original x87 operation tables

Eleven writable operation records now have typed C90 source across three
original CRT data owners. One stable VC4 compilation per owner matches all
**448 initialized record bytes and 68 actual relocations**. These storage bytes
are separate from the 376 accepted exact functions, 76,908 code bytes and
244 attached exception-metadata bytes.

| Operation | Address | Complete bytes | Dispatch slots |
| --- | --- | ---: | ---: |
| sin | `0x00423132` | 32 | 4 |
| cos | `0x00423152` | 32 | 4 |
| tan | `0x00423172` | 32 | 4 |
| asin | `0x00423230` | 32 | 4 |
| acos | `0x00423250` | 32 | 4 |
| atan | `0x00423270` | 32 | 4 |
| atan2 | `0x00423290` | 80 | 16 |
| pow | `0x00423F34` | 80 | 16 |
| log10 | `0x00423F84` | 32 | 4 |
| log | `0x00423FA4` | 32 | 4 |
| exp | `0x00423FC4` | 32 | 4 |

Each record begins with a sixteen-byte header: a length byte, eleven name
bytes, the observed selector at offset 12, the operand count at 13, and the
operation word at 14. The source retains the selector as `unclassified_0c`.
The first dispatch pointer is at offset 16. Names and typed entry references
use ordinary initializers. Native pointer fields grow with the host.

The actual sin record starts at `0x423132`, an address divisible by two but
not four. This establishes two-byte record alignment, which the shared header
now expresses with a scoped pack directive. Its earlier default pointer
alignment could not represent this original address correctly. VC4, native GCC
and i686 MinGW compile the same header; a focused offset probe confirms that
a record following one byte begins at offset two. The record/header extents
and the earlier inverse-trigonometric contents remain unchanged.

| Maintained source | Original owner | Complete restored records |
| --- | --- | ---: |
| `runtime_x87_operation_tables.c` | `87triga.obj` | 176 bytes / 28 relocations |
| `runtime_x87_trig_tables.c` | `87trig.obj` | 96 bytes / 12 relocations |
| `runtime_x87_transcendental_tables.c` | `87tran.obj` | 176 bytes / 28 relocations |

The last two owners restore complete named table objects at original data
section offsets 18 and 68. Their preceding constant regions remain outside
this source claim; no partial record or full constant-section claim is made.
All three sources compile with native GCC and i686 MinGW under C90 and warnings
as errors. Only these data owners and the alignment probe are compiled.

Dispatch targets have a custom x87/register ABI. Their addresses are represented
by pointers to an incomplete machine-entry type; the declarations supply no
fictional C arguments, return contract or replacement bodies. The records
preserve every normal, zero, infinity, NaN and indefinite entry, including
repeated binary-case targets. Writable storage and the borrowed name bytes
remain available to the genuine dispatcher.

## Earlier inverse-trigonometric code and data authority

The pinned member is `..\build\intel\st_obj\87triga.obj`, archive offset
`0x000EBEC8`. The independent 104-byte nonrelocated code run locates its entire
162-byte code section at `0x004192A0`. The complete sixteen-byte operation-header
subobject independently occurs once in the PE, placing its entire 176-byte data
section at `0x00423230`. Header boundaries follow the first pointer relocation
and the original dispatcher consumers at offsets 12 and 14. This is explicit
record-header authority, rather than the previously rejected partial
initialized-symbol placement rule. That older general helper is unchanged.

Both locations are established before applying any pointer field. All five
code and 28 data relocations then resolve through this complete atomic group
or actual external definitions in the already verified complete `87disp.obj`
sections. Every relocated byte agrees with the PE. The new full table read
also agrees; the old full code observation is reused under its original
REA 4.1 identity. No BSS location is inferred from a code operand.

The group identifies two previously unknown inventory entries:

| Entry | Complete bytes | Original identity and machine contract |
| --- | ---: | --- |
| `0x004192DC` | 48 | Internal asin/acos reduction at section +60; ST0, inherited EBP scratch and nonlocal error path |
| `0x0041930C` | 9 | External `__rtpiby2` at +108; pop ST0 and load the genuine extended-precision half-pi constant |

Their low-level source remains open. Origins now comprise **270 authored /
219 runtime / 21 compiler-generated / 10 unknown**. Inventory 520, parent
fragments 24, source-present functions 464 and exact functions 376 are unchanged.
The verified section also retains its other exported and internal labels;
this does not declare the provisional function inventory complete.

The seven unresolved C-dispatcher entries still need independent placement of
its nine-byte BSS section (`LocalFac` plus `intrinflag`). Its literal code and
48-byte constants have unique anchors, but that does not authorize guessing
the BSS addresses. Those entries are not reclassified by this recovery.

## Evidence and validation

- Reused complete code:
  `ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
- New REA 6.5.0 / Ghidra 12.1.4 complete 176-byte read:
  `ev_d7b5e3077aa89e06757c2366971896bffbded18b2eeb3e07f63c6486a8a3fafa`.
- Closed new run:
  `.analysis/rea/runs/2026-10-16T06-24-20.876Z-requests-258624/`.
- Complete public source/data recipe and actual entry bindings:
  `config/runtime-x87-operation-tables.json`.
- Original group proof, source comparison, compiler receipts and all scoped
  input identities: `.analysis/crt-dispatch-boundaries-20261016/`.

At the initial inverse-trigonometric checkpoint, one serial provider read and
one VC4 data-owner compilation ran under the 35%
CPU / 640 MiB high / 768 MiB maximum scope. An initial batch containing an
interactive-only close directive was rejected locally before opening a provider;
the corrected one-read batch closed and saved normally. No full replay,
existing owner recompilation, runtime probe or game build ran. Existing source,
exact and semantic acceptance ledgers and both function comparison reports
remain byte-identical. This standalone storage does not supply the remaining
machine helpers or establish the final restored-game link and playability.

## Seven further records and alignment follow-up

The sin/cos/tan records reuse the complete verified 43-byte code / 114-byte data
`87trig.obj` group. Pow/log10/log/exp reuse the complete verified 519-byte code /
244-byte data `87tran.obj` group. Their current named table ranges and every
machine-entry address follow actual definitions in those hash-pinned members
or the previously verified complete `87disp.obj` sections. Object-local names
remain scoped to the actual member. No observed pointer field supplies a
new guessed binding.

Complete retained data observations are reused under their original REA 6.3
identities:
`ev_f585a80429f6f35d273f39b3a7cd2b5c0ab75c5c2a4f84a4037271fa1621974b`
and `ev_86e6cb7d19a108f9784a3a93e2ab193547dfcfc6258578eb1c0e07e753b3a3ce`.
See [the code/data group policy](../CRT_CODE_DATA_GROUPS.md). This follow-up
opens no provider and runs no runtime test or full replay.

The current family recipe is `config/runtime-x87-operation-tables.json`.
Compiler receipts, complete per-owner comparisons, portable products, alignment
results and verification are in `.analysis/x87-unary-operation-tables-20261016/`.
The earlier 176-byte result remains independently retained in its original phase.
The new 272 record bytes change no function source, exact or semantic acceptance
claim; both function comparison reports and all existing acceptance ledgers stay
byte-identical. The opaque machine entries and the remaining constants still
need their original implementations/storage before a final game link.
