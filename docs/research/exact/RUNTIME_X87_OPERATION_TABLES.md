# Original x87 inverse-trigonometric operation tables

The writable `87triga.obj` records at `0x00423230..0x004232DF` now have typed
C90 source in `runtime_x87_operation_tables.c` and its dedicated header. One
VC4 compilation matches all **176 initialized bytes and 28 actual relocations**.
This storage is separate from the 376 accepted exact functions, 76,908 code
bytes and 244 attached exception-metadata bytes.

| Operation | Address | Complete bytes | Dispatch slots |
| --- | --- | ---: | ---: |
| asin | `0x00423230` | 32 | 4 |
| acos | `0x00423250` | 32 | 4 |
| atan | `0x00423270` | 32 | 4 |
| atan2 | `0x00423290` | 80 | 16 |

Each record begins with a sixteen-byte header: a length byte, eleven name
bytes, the observed selector at offset 12, the operand count at 13, and the
operation word at 14. The source retains the selector as `unclassified_0c`.
The unary/binary counts are 1/2 and the operation values are 14/13/15/16.
The first dispatch pointer is at offset 16. Names are ordinary initializers;
no anonymous gap, alignment padding or executable bytes are manufactured.
Native pointer fields grow naturally. The source also compiles under native
GCC and i686 MinGW with C90 and warnings as errors.

Dispatch targets have a custom x87/register ABI. Their addresses are represented
by pointers to an incomplete machine-entry type; the declarations supply no
fictional C arguments, return contract or replacement bodies. The four records
preserve every normal, zero, infinity, NaN and indefinite entry, including
repeated binary-case targets. Writable storage and the borrowed name bytes
remain available to the genuine dispatcher.

## Complete original code and data authority

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

One serial provider read and one VC4 data-owner compilation ran under the 35%
CPU / 640 MiB high / 768 MiB maximum scope. An initial batch containing an
interactive-only close directive was rejected locally before opening a provider;
the corrected one-read batch closed and saved normally. No full replay,
existing owner recompilation, runtime probe or game build ran. Existing source,
exact and semantic acceptance ledgers and both function comparison reports
remain byte-identical. This standalone storage does not supply the remaining
machine helpers or establish the final restored-game link and playability.
