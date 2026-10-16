# Original x87 operation tables

Twelve writable operation records now have typed C90 source across four
original CRT data owners. Their complete comparisons match all
**480 initialized record bytes and 72 actual relocations**. These storage bytes
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
| sqrt | `0x004232E0` | 32 | 4 |
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
| `runtime_x87_sqrt_table.c` | `87sqrt.obj` | 32 bytes / 4 relocations |

The trig and transcendental owners restore complete named table objects at original data
section offsets 18 and 68. Their preceding constant regions remain outside
this source claim; no partial record or full constant-section claim is made.
All four sources compile with native GCC and i686 MinGW under C90 and warnings
as errors. The sqrt follow-up compiles only its new owner, reusing the preceding
448-byte family products and alignment result with unchanged inputs.

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

Their low-level source remains open. At that checkpoint origins comprised **270 authored /
219 runtime / 21 compiler-generated / 10 unknown**. Inventory 520, parent
fragments 24, source-present functions 464 and exact functions 376 are unchanged.
The verified section also retains its other exported and internal labels;
this does not declare the provisional function inventory complete.

The initial checkpoint left seven C-dispatcher origins unresolved. Two now have
complete [BSS-free origin proofs](RUNTIME_X87_DISPATCH_TAIL.md); the remaining
five still need independent placement of the nine-byte BSS section (`LocalFac`
plus `intrinflag`). The [subsequent constant recovery](RUNTIME_X87_TRIG_ENTRIES.md)
supplies all 48 readonly constant bytes as typed source, without authorizing
guesses for the BSS addresses or claiming the full dispatcher.

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

## Square-root record and the bounded descriptor inventory

The final square-root record has ordinary C90 source and a dedicated header,
leaving all preceding owner inputs untouched. Its complete 32-byte VC4 output
matches the original with all four pointers: normal kernel, zero handling,
unary NaN handling and infinity handling. The original `87sqrt.obj` code is
27 bytes at `0x419350`; a unique 23-byte nonrelocated anchor establishes its
position before the one external relocation is resolved through the previously
verified `87disp.obj`. Its actual local definitions then ground the kernel,
zero and infinity addresses. The fourth target is the verified unary NaN helper.
The complete original code and data both match the pinned PE and CRT member.

Existing REA 4.1 observations are reused with their actual coverage. The full
code read covers all 27 kernel bytes. The saved table observation covers only
the **16-byte header**:
`ev_f6a414600d6f4d61172f65edeb5491e6d910bbcfc248fad3ddebaba403ab32cc`,
run `.analysis/rea/runs/2026-10-09T16-35-10.894Z-math-table-requests-1298340/`.
This is not described as a new whole-table REA observation. All 32 file-backed
data bytes are compared directly with the pinned PE after applying each
original and source-object relocation. No pointer value is used to guess the
kernel's code position.

A single bounded archive inventory finds sixteen named `__OP_...jmptab`
definitions. Twelve complete sixteen-byte headers occur uniquely in the
original; all twelve corresponding complete records now have source and full
data comparisons. No matching headers are found for fmod, sinh, cosh or tanh;
those four are not added as target records. This is the pinned descriptor family,
not proof of a complete function/source denominator or unique original link.

Only one new VC4 data owner is compiled, followed by native/i686 C90 compilation.
The earlier three products, their 448 bytes and 68 bindings are retained with
unchanged source/header/object identities. No provider, runtime test, game build
or full replay runs. Proof, compiler receipt, descriptor inventory and final
verification are in `.analysis/x87-remaining-operation-records-20261016/`.
Function source464/exact376 and every acceptance ledger/comparison report remain
unchanged. The special machine helper bodies still need implementation.
