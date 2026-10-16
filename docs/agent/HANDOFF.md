# DX-Ball reconstruction handoff

Updated October16,2026, after restoring two omitted unsigned64 helpers.
Current totals are470 source entries,380 exacts and90 complete candidates.
The original104/117-byte assembly helpers have complete327/280-byte C bodies
with actual64-bit stdcall ABI; they remain nonexact. All990 logical arithmetic
and12 emulated fault cases pass. Prior380 exact and88 candidate results/products
are reused; all249 semantic rows remain byte-identical this phase.
REA is pinned to 6.5.0.
The reconstruction objective is unfinished.

This document describes the current state, not a running history.
[Earlier handoff and trial history](https://github.com/N0zoM1z0/dx-ball/blob/d3053ebf453d5e2db1dc545dbe188f28f02f2d00/docs/agent/HANDOFF.md)
remain in Git. Historical owner-note totals describe their own checkpoints;
use the ledgers and reports below for current totals.

## Goal and priorities

The user's first priority is **“先把所有的函数尽可能 exact 还原完”**:
recover all original English DX-Ball v1.07 functions as exactly as possible,
as readable, rebuildable C/C++.

The route is:

1. Finish function reconstruction and complete-function exact comparisons.
2. Get the reconstructed game building with the original Visual C++ 4.0
   compiler and verify that it is playable.
3. Resume platform ports, including macOS.

Existing build/play evidence does not establish step 2 for the final restored
source. Do not move to ports because a partial build or a small fixture passes.
An exact-function count is progress, not the completion criterion.

- Stay on DX-Ball; leave TH04 alone.
- Use the local original, retained REA evidence and shipped compiler/CRT
  sources. Do not search online for game source or another reconstruction.
  The verified original game archive contains no source, PDB, objects or map.
- Favor concrete source recovery over test, documentation, tooling or feedback
  work. Those are supporting tasks, not the main deliverable. Run a focused
  existing check only when it answers a real question; no historical test queue.
- Work from a specific instruction-supported gap: ABI, expression, state write,
  ownership, lifetime or original producer boundary. Make a bounded trial,
  compare the complete affected family, record the result and move on.
- Keep repository prose and code English. Write plainly and concisely. Keep the
  README tutorial, centered 900px title PNG and progress SVG.
- Preserve the full objective across turns. Do not mark it complete after an
  isolated exact gain, a handoff, a successful fixture or a compatibility build.

## Current authoritative state

| Item | Value |
| --- | ---: |
| Provisional independent function inventory | 545 |
| Parent-owned compiler fragments, counted separately | 24 |
| Source-present independent entries | 470 |
| Accepted exact functions | 380 |
| Complete exact code bytes | 77,485 |
| Attached exact metadata bytes | 244 |
| Historical scoped semantic rows | 249 |
| Complete nonexact comparisons | 90 |
| Source-present entries outside the two comparison reports | 0 |
| Inventory entries without a source-present ledger row | 75 |
| Nonexact origins | 34 authored / 55 runtime / 1 compiler-generated |
| Inventory origins | 270 authored / 245 runtime / 21 compiler-generated / 9 unknown |

These are separate inventories, not interchangeable completion percentages.
The authored denominator and nine unknown origins remain open.
All 34 authored candidates have complete comparisons; the
[remaining-functions table](../research/exact/REMAINING_EXACT_FUNCTIONS.md)
now lists all 90 maintained candidates.

All eight allocator entries now have complete exact acceptance, including the
three physical Heap API wrappers. All 90 source-present nonexact entries have
complete candidate comparisons. Another 75 independent inventory entries lack
a source-present row. The [allocator note](../research/ALLOCATOR_OWNER.md)
records the preserved public binding API, three actual import cells and focused
native/Win32 evidence.

The actual C++ `new/delete` now call the recovered allocation loop and heap
release directly. Their full 16/14-byte VC4 comparisons have zero differences,
corroborating the same accepted addresses without adding two functions. The
legacy builder now includes the previously omitted `cpp_allocator.cpp` with
the allocator flags and records owner overrides. A typed-list VC4 control
reproduces the missing-object bypass; the repaired link, current native DSO and
standalone MinGW probe pass real allocation, handler retries, release and
terminal exit1/empty-list checks. Only affected native entity cases (7,343 plus
980 connections) and two Core allocation-failure selectors ran. The copied
native fixture binds the two real C++ dependency operands to its existing
typed callbacks; uninstrumented probes verify production paths separately.
No full replay, final game build or play claim follows from these checks.
See [the allocation entry repair](../research/ALLOCATOR_OWNER.md#actual-c-allocation-entries-october-16-2026).

Two complete named x87 routines now have proven runtime origins:
`__ctrandisp1`44 and `__fload`60. The complete relocation-free loader uniquely
places its text section; the dispatcher binds the independently proven
`__trandisp1`. Its unrelocated calls, including the shared418A3E dependency,
are reviewed explicitly. The shared BSS-dependent handler and full589-byte
section remain unverified. No source or exact gain follows; see
[dispatch tail](../research/exact/RUNTIME_X87_DISPATCH_TAIL.md).

The sin/cos/tan scalar group now matches all24 bytes/four independently grounded
bindings. Tan and three intrinsic entries were omitted from the inventory.
The intrinsic group still has one unresolved external exit and remains unknown;
the four additions account for the denominator and unknown-count increase.
Six readonly dispatch constants have complete48-byte C source and zero-byte
differences under VC4, with native/i686 C90 compilation. These constants remain
separate from the unchanged480-byte descriptor family. See
[trig entries and constant source](../research/exact/RUNTIME_X87_TRIG_ENTRIES.md).

At checkpoint `d11c556`, the VC4 game links the matching allocator/list/resource products with
their actual owner flags. Default LIBC is excluded after a retained mixed-CRT
link failure; the successful map uses one LIBCMT runtime. Complete owner
products and previous adapter objects are reused by compiler/flags/full project
input/object identity. The final game build reuses all 37 objects. All 52 linked
allocator/list/C++ API bodies agree after actual image relocations. A probe with
78 read-only observations confirms modes 4/0/1, attached ball, paddle input,
release/motion, menu return and exit 0; the first-board screenshot is reviewed. The coarse
pixel-only scene claim was insufficient and is retained with that limitation.
This checks current owner integration; remaining function recovery and the
standalone reconstructed CRT entry/storage/link remain open. See
[VC4 owner linkage](../research/VC4_OWNER_LINKAGE.md).

Win32 defaults now supply genuine heap APIs before game binding. The host
WinMain wrapper retains an existing heap; the resource inspector explicitly
initializes one before decoding. Fresh, early-default and early-Windows-bound
entry checks pass with actual heap handles, pre-entry bytes/typed nodes and
real release. The native translation unit is unchanged after preprocessing;
native/VC4 SFONT and INTRO inspector outputs agree, and MinGW physical default
heap checks pass. The legacy console tools now link their missing winmm
dependency. These focused checks do not repeat the previous GUI control or
integrate the standalone restored CRT entry. See
[Windows heap startup](../research/WINDOWS_HEAP_STARTUP.md).

The writable character table, two real pointer slots and small locale defaults
now have complete source storage: 534 bytes/two bindings match. Numeric consumers
use the original two-byte decimal-point array, closing exponent formatting's
complete 310 bytes and six-byte suffix. All 13 affected old exacts remain. The
multiplication C body is unchanged but its shared declaration context emits
50 differences instead of 21; it remains a complete candidate. The 3,855 native
C-locale consumer checks pass. See
[character state and exact formatting](../research/exact/RUNTIME_CHARACTER_STATE.md).

The locale category/code-page producer now supplies the real six-slot vector
and unsigned code-page word. They retain 32-bit LCID/UINT width on the native
64-bit host. Twelve category-routing calls and four locale-selector scenarios
pass through the maintained consumers and typed fixture boundaries. The whole
28-byte relative initialized layout matches; all-zero storage has no unique
original anchor, so no independent absolute data/exact claim is added. All
function ledgers and raw comparisons remain byte-identical. See
[locale handles](../research/exact/RUNTIME_LOCALE_HANDLES.md).

Two whole original sections missing from the inventory are now restored:
unsigned64 division104 and remainder117. Natural32-bit-limb C preserves the
64-bit return and stdcall16 ABI; VC4 emits327/280 bytes, so both remain candidates.
All495 operand pairs per function match original/VC4/i686/native arithmetic;
six zero-divisor cases each match emulated divide-error0. Preserved registers,
stack cleanup and stack-only writes pass. The bounded library scan retains its
three parse skips and excludes short/shared sections; no exhaustive inventory
claim follows. See [unsigned64 arithmetic](../research/exact/RUNTIME_U64_ARITHMETIC.md).

The complete84-byte CRT table now includes XP/XT and both end markers, with13
actual callback bindings matching the retained original and linked VC4 image.
The existing two-slot pretermination array groups original XPA/XPX records in
XPA while preserving the public ABI and caller bounds. Returning normal/quick
and low-byte cleanup, real filter restoration and physical exits63/64 pass
following actual XI/XC startup. Only two data owners compile; all function
producers/results stay unchanged. The affected native1,031-call scope refreshes
four semantic input identities. Stdio/fatal/unused exception dispatch remain
controlled dependencies; FP/full CRT entry, remaining function recovery and the
final game remain open. See [exit sections](../research/exact/RUNTIME_EXIT_SECTIONS.md).

XI/XC now use their real linker sections, including the previously ordinary
C++ filter pointer in `.CRT$XCC`. Four null boundary records, three explicit
registration records and nine reused C++ compiler contributions reproduce the
complete64-byte prefix/twelve bindings. The isolated VC4 image imports only
KERNEL32 and uses a custom entry: actual heap/low-I/O initialization, both table
walks, filter installation/restoration and nine prefilled list roots pass.
All380 exact results remain; only three existing producer identities change.
The board aggregate helper remains nonexact/unresolved. Later XP/XT section recovery closes the table layout; FP/full
CRT entry and the final game remain open. See
[initializer sections](../research/exact/RUNTIME_INITIALIZER_SECTIONS.md).

The complete193-byte stdio initializer now matches all16 bindings. A separate
storage owner supplies the original20 stream records,4096-byte input buffer,
request counter and table state; initialized644 bytes/two bindings match.
Fourteen original/native calls cover limits, fallback/fatal26 and invalid/null
standard handles. The correct12-byte XI range confirms both initialization
entries in order; XI/XC section registration is supplied by the later section owner; full
startup remains open. No existing consumer/header or historical scope changes. See
[stdio initialization](../research/exact/RUNTIME_STDIO_INITIALIZATION.md).

The complete54-byte onexit initializer and20-byte stdio finalizer are now exact.
The initialized pretermination/termination arrays have a separate source owner;
controller128 and both18-byte wrapper exacts are preserved, walker32/6 unchanged.
Actual private-heap registration/growth, returning cleanup and physical exit
probes pass with controlled stdio/fatal dependencies. Only the affected native
scope and eight retained-object calls ran. Later XI/XC section recovery does
not close full CRT/game linkage. See
[exit bootstrap and default cleanup](../research/exact/RUNTIME_TERMINATION_BOOTSTRAP.md).

The collision-unwind callback now has complete natural C source. Its original
34 bytes compare against a 31-byte VC4 body, so it remains nonexact; all 142
original/VC4 emulated cdecl/effect cases agree. Native/i686 C90 compilation
passes. Sixteen omitted CRT definitions are reconciled from complete existing
code/data proofs, including this callback. The other fifteen retain their
low-level ABI gaps. No current game build or physical Windows-unwind claim
follows. See [SEH and entry boundaries](../research/exact/RUNTIME_SEH_ENTRIES.md).

Current accounting is 540 independent entries plus 24 parent-owned compiler
fragments. All previous addresses are preserved, including the four added trig
entries; the latest review adds sixteen omitted CRT entries. The twenty
fixed-point unwind cleanups and four shared epilogues belong to the complete
triangle/division/comparison/addition owners. Their source, metadata and code
ranges were already part of those units; they are now recorded in
`config/compiler-fragments.csv` and validated against their parents.

All four complete parent comparisons reproduce their retained results from
the existing canonical object: three exact methods and the unchanged 88-byte
triangle candidate. That reconciliation repeated no compiler/provider/runtime
work and changed no source or exact claim. The 75
independent entries without source remain in scope. See
[compiler ownership](../research/exact/COMPILER_FRAGMENT_OWNERSHIP.md).

The preceding original CRT startup checkpoint restored the complete 390-byte
body and 12-byte scope with all 34 code/two scope bindings. Four version fields
and command state are supplied, and the genuine WinMain/exit/filter APIs are
used. The fatal owner's GUI initializer is now 2; both fatal exacts, the format
candidate and catalog/strings remain verified. It is still a standalone owner,
without a final restored-game build/play claim. See
[CRT startup](../research/exact/RUNTIME_ENTRY.md).

The preceding catch wrapper is also complete and exact, including its former
59-byte imported-boundary gap and initialized current exception/context state.
The omitted 41-byte guard is in the inventory with a proven runtime origin;
its CLD and low-level forwarding source remain open. Three more original
transport sections now match all 376 bytes and six relocations; their source
remains open. See
[catch guard](../research/exact/RUNTIME_CPP_CATCH_GUARD.md).

The preceding object checkpoint restored exact destruction and construction
with four EAX/ECX differences. Its twelve Wine cases exercise actual member
ABI and real VC4 SEH, with an isolated unchanged pointer helper and controlled
abort endpoint. Three member-call trampolines have proven runtime origins,
without source claims. These checks do not establish a final game build/play.

REA is now pinned to 6.5.0, with bundled skill version 42 and 207 tools. The
420-record 6.4 snapshot is preserved as a verified gzip carrier because 6.5
rejects its analysis profile. A fresh 6.5 read of the object-scope table bytes
matches the original and closes normally. The current profile uses a 256 MiB
Ghidra heap, 35% of one CPU and a 768 MiB whole-task memory limit. Upgrade proof
and backups are in `.analysis/rea-upgrade-6.5.0/`; see [REA commands](REA.md).

### Authorities and private inputs

- `config/functions.csv`: provisional entries and reconciled extents.
- `config/function-origins.csv`: independent entry origin classification.
- `config/runtime-x87-operation-tables.json`: twelve complete writable records, 480 bytes/72 bindings.
- `config/runtime-locale-handles.json`: complete source/member relative 28-byte locale storage; target address remains null.
- `config/runtime-character-state.json`: complete writable 522/12-byte ctype/locale source owners and two pointer bindings.
- `config/runtime-x87-dispatch-constants.json`: separate complete 48-byte readonly source record and six qword consumers.
- `config/compiler-fragments.csv`: parent-owned unwind/epilogue aliases with original ranges and evidence; excluded from independent counts.
- `config/implemented.csv`, `matches.csv`, `semantic-acceptance.csv`:
  source, exact and scoped semantic claims.
- `config/source-owners.toml`: maintained source ownership.
- `config/match-units.toml`: compiler inputs, flags, complete extents and bindings.
- `build/reports/exact-replay.json`: current 377 accepted comparisons/producers.
- `.analysis/exact-candidate-audit-20261012/comparison.json`: current 88
  candidates/producers. The directory date is historical; its contents are current.
- Selected phase `verification.json` files and owner notes explain each adoption.
  Older phase reports are historical unless their inputs/products still agree.

Repository: `/home/pentester/coding/codex_ida/dx-ball-reconstruction/dx-ball`.
The environment may start one directory above it.

Original: `original/DXBALL.EXE`, English v1.07, 158,208 bytes, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.

Original-era toolchain: VC4 compiler 10.00.5270, linker 3.00.5270;
CRT library `.tools/msvc400/lib/libc.lib`.
The compiler recorded by current reports has SHA-256
`f097e736bb04d38391c8b524945d58809ec4c42e97c056eca6f40bba2de910c3`.

Keep `original/`, `.tools/`, `build/`, `.analysis/` and `ghidra-project/`
private. A source-only clone does not include these evidence/products.
Historical native, MinGW and VC4 builds/play controls exist, but recent CRT
recovery used affected standalone compilation and complete comparisons.
Shared CRT storage/default bindings, BSS/FP initialization and physical
integration remain open; do not claim a current end-to-end rebuilt game from
standalone results. See [CRT storage closure](../research/CRT_INITIALIZED_STORAGE_CLOSURE.md)
and [FDIV initialization](../research/CRT_FDIV_INITIALIZATION_FRONTIER.md).

## Latest adopted source work

| Checkpoint | Result | Evidence / owner note |
| --- | --- | --- |
| October 16 locale category/code-page owner | Six real 32-bit LCIDs and code-page word; relative 28-byte layout; 12 category calls/four selector scenarios; no new absolute placement or exact claim | [Locale handles](../research/exact/RUNTIME_LOCALE_HANDLES.md); `.analysis/locale-handles-source-20261016/adoption.json` |
| October 16 character/locale state | Two-byte decimal-point array; complete310-byte exponent exact;13 prior family exacts preserved;534 data bytes/two bindings;3,855 native consumer checks | [Character state](../research/exact/RUNTIME_CHARACTER_STATE.md); `.analysis/ctype-state-source-20261016/adoption.json` |
| October 16 SEH/CRT entry review | Complete collision callback source; 31/34-byte candidate; 142 emulated ABI/effect cases; 16 omitted entries reconciled; prior 376 exacts unchanged | [SEH entries](../research/exact/RUNTIME_SEH_ENTRIES.md); `.analysis/crt-omitted-entries-20261016/adoption.json` |
| October 16 Windows heap startup | Real Win32 defaults; early heap/allocations survive WinMain; three physical entry controls and native/VC4 tool checks pass; eight exact bodies unchanged | [Heap startup](../research/WINDOWS_HEAP_STARTUP.md); `.analysis/windows-heap-startup-20261016/adoption.json` |
| October 16 VC4 owner linkage | Three corrected owner profiles; single LIBCMT; 37 objects reused; 52 linked bodies and read-only first-board controls pass; source/exact totals unchanged | [VC4 linkage](../research/VC4_OWNER_LINKAGE.md); `.analysis/legacy-owner-reuse-20261016/` |
| October 16 trig entries/constants | Scalar24 bytes/four bindings; four omitted entries; six readonly constants48-byte source; function exact/source totals unchanged | [Trig entries](../research/exact/RUNTIME_X87_TRIG_ENTRIES.md); `.analysis/trig-entries-dispatch-constants-20261016/adoption.json` |
| October 16 mantissa snapshot | Explicit three-limb integer snapshot; five complete byte results unchanged; one owner compilation | [Mantissa lifetimes](../research/exact/RUNTIME_MANTISSA_LIFETIMES.md); `.analysis/mantissa96-integer-snapshot-20261016/adoption.json` |
| October 16 sqrt record | Complete32-byte record/four bindings; descriptor family480 bytes/72 bindings; old448 bytes reused | [Operation tables](../research/exact/RUNTIME_X87_OPERATION_TABLES.md); `.analysis/x87-remaining-operation-records-20261016/comparison.json` |
| October 16 x87 record alignment | Two-byte ABI restored; seven more records add272 bytes; family448 bytes/68 bindings; prior176 bytes preserved | [Operation tables](../research/exact/RUNTIME_X87_OPERATION_TABLES.md); `.analysis/x87-unary-operation-tables-20261016/comparison.json` |
| October 16 x87 operation tables | Four complete writable records /176 bytes and28 bindings; two CRT origins; no function source/exact gain | [Operation tables](../research/exact/RUNTIME_X87_OPERATION_TABLES.md); `.analysis/crt-dispatch-boundaries-20261016/source-comparison.json` |
| October 16 independent heap imports | All eight allocator bodies exact; three gaps closed, +66 code bytes; total 376; public header unchanged | [Allocator ownership](../research/ALLOCATOR_OWNER.md); `.analysis/allocator-independent-imports-20261016/adoption.json` |
| October 16 foreign-handler tail | Original one-past handler pointer, negative-offset type test and deferred last-handler argument; 212/213 bytes, 105 differences; three owner exacts preserved | [C++ tables](../research/exact/RUNTIME_CPP_TABLES.md); `.analysis/cpp-foreign-handler-tail-20261016/adoption.json` |
| October 16 compiler fragments | 24 overlapping cleanup/epilogue rows mapped to four existing parents; 520 independent entries, source/exact unchanged | [Compiler ownership](../research/exact/COMPILER_FRAGMENT_OWNERSHIP.md); `.analysis/compiler-fragment-ownership-20261016/verification.json` |
| October 16 CRT startup | Complete 390 code / 12 scope bytes exact; GUI initializer fixed; fatal family preserved; total 373 | [CRT startup](../research/exact/RUNTIME_ENTRY.md); `.analysis/crt-entry-source-20261016/adoption.json` |
| October 16 catch guard | One omitted 41-byte callback reconciled; complete transport/guard origins; inventory 544, exact unchanged | [Catch guard](../research/exact/RUNTIME_CPP_CATCH_GUARD.md); `.analysis/cpp-catch-guard-origin-20261016/adoption.json` |
| October 16 catch wrapper | Complete 272 code / 24 scope bytes exact; both current-state pointers recovered; total 372 | [Catch invocation](../research/exact/RUNTIME_CPP_CATCH.md); `.analysis/cpp-catch-block-source-20261016/adoption.json` |
| October 16 frame unwind | Complete 206 code / 12 scope bytes exact; total 371 | [Frame unwind](../research/exact/RUNTIME_CPP_UNWIND.md); `.analysis/cpp-frame-unwind-source-20261016/adoption.json` |
| October 16 C++ object | Two complete sources; destruction 113 code / 12 scope bytes exact; construction 510 / 4 differences; total 370 | [C++ object source](../research/exact/RUNTIME_CPP_OBJECT.md); `.analysis/cpp-exception-object-source-20261016/adoption.json` |
| October 16 C++ terminal | Two complete SEH bodies, 230 code / 48 scope bytes; total 369 | [C++ terminal source](../research/exact/RUNTIME_CPP_TERMINAL.md); `.analysis/cpp-terminal-source-20261016/verification.json` |
| October 16 allocator | Five complete exact functions, 147 bytes; total 367 | [Allocator ownership](../research/ALLOCATOR_OWNER.md); `.analysis/allocator-complete-owner-20261016/verification.json` |
| `d3053eb` | Matherr 174-byte body: 21 → 17 → 6 differing positions; no new exact | [FP exception entries](../research/exact/RUNTIME_FP_DECOMPOSITION.md); `.analysis/math-error-original-double-record-20261015/verification.json` |
| `aa9538f` | Float assignment: complete 76-byte exact; total 362 | [Float formatting](../research/exact/RUNTIME_FLOAT_FORMAT.md); `.analysis/float-assignment-original-double-record-20261015/verification.json` |
| `a1445a0` | Decimal table scaler: complete 123-byte exact | [Decimal conversion](../research/exact/RUNTIME_DECIMAL_CONVERSION.md); `.analysis/decimal-original-table-pointers-20261015/verification.json` |
| `84c468f` | Integer reversal: complete 96-byte exact, retained VC4 producer reused | [Integer text](../research/exact/RUNTIME_INTEGER_TEXT.md); `.analysis/integer-original-pointer-reversal-20261015/verification.json` |
| `e1336ea` | Float digits: complete 129-byte exact | [Float formatting](../research/exact/RUNTIME_FLOAT_FORMAT.md); `.analysis/float-digits-original-string-operation-20261015/verification.json` |
| `f1c91a4` | Exponent transport: complete 57-byte exact | [FP control](../research/exact/RUNTIME_FP_CONTROL.md); `.analysis/exponent-original-double-transport-20261015/verification.json` |

Matherr now uses the shipped single-field DOUBLE record for argument copies
and separate low/high four-byte result copies. Its only remaining difference
is the order of two adjacent four-byte instructions at offsets 70/74: an
argument-high store and result-high load. The retained certificate proves that
interchanging those chunks matches the entire original. Both 187/79-byte
companions remain exact. C controls give the same result; the maintained
producer remains C++. Do not add volatile or artificial barriers to force order.

The new exacts restore original operations, not portability substitutes:
overlapping `strcpy(buffer, buffer + 1)`, original terminal/pre-array pointer
formation, and aligned DOUBLE aggregate assignment. Preserve these documented
source decisions for the exact stage. Native compilation alone does not establish
defined modern-C behavior or an unaligned-access guarantee.

## Retained private cvt owner control: not adopted

Directory: `.analysis/cvt-original-complete-owner-20261015/`.

The original CRT member
`.analysis/runtime-float-format-20261014/crt-members/000e369c.obj`
identifies `cvt.c` and eleven function definitions in original order.
A private control reunited those eleven current bodies, restored the three
original static helpers, and excluded the unrelated `_fptostr.c` and trap bodies.
It used one VC4 compilation plus successful native and i686 compilation.

| Unit | Maintained differences | Private complete-owner differences |
| --- | ---: | ---: |
| Exponent formatting, 310 bytes | 2 | 0 |
| Fixed formatting, 251 bytes | 0 | 1 |
| General formatting, 176 bytes | 0 | 2 |
| Force decimal point, 101 bytes | 4 | 4 |
| Seven other previously exact bodies | 0 | 0 |

Thus the private owner has eight exact bodies but loses two accepted exacts.
It is not adopted or counted. No compiler/provider process from this trial
remained running at handoff; no maintained source or ledger changed.

Retained files under `original-cvt-c-owner/` include `compile.json`,
`comparison.json`, `portable-products.json`, logs, full source/header snapshots,
`units.json` and the object. Object SHA-256:
`dd330088e7a1cd8ea82a8b505b32f46b89521e81897a70bd658307e0fa52799a`.
The private source/header changes and self-local/literal binding mappings belong
to that control only. Do not copy its zero result into maintained ledgers.

## Next useful work and closed boundaries

Read the selected owner note before editing. Choose a concrete new source
question, not merely the smallest differing-position count.

- Locale handles/code page now have a source owner. Keep six 32-bit category
  values even on LP64; the null-address recipe records the absence of independent
  absolute placement. Category/selector fixture transport passes; OS locale
  drivers and full reconstructed CRT linking remain open. Do not relabel the
  all-zero relative-layout proof as independently located target data.
- The decimal point is a two-byte array, not a scalar. Preserve its shared
  declaration and element-zero reads. Exponent formatting now matches all 310
  bytes and the full suffix with fixed/general exacts retained. Initial writable
  ctype/locale storage is restored; remaining locale/BSS/physical integration
  needs independent evidence. Multiplication remains678/50 after this context
  change; do not select its older21-difference object against changed inputs.
- The newly reconciled collision callback is complete C source but not exact.
  Its 31/34-byte result differs in mask-test width and caller-clobbered scheduling.
  Preserve that honest candidate; do not force volatile loads or add assembly.
  The other fifteen omitted entries still need their actual low-level ABI.
  Original read scalar/structured flow and char/char record controls are closed
  without improvement; see [reading](../research/exact/RUNTIME_LOWIO_READ_CLOSE.md).
- All eight allocator entries are now exact. The private typed import cells and
  retained public binding record close all three physical-wrapper gaps without
  modifying `allocator.h`. Earlier controls that removed its public declaration
  remain rejected; do not repeat them or rebase a table per function. Fixture
  updates use the existing setter, including restoration. Handler registration,
  teardown and the 75 independent entries without source remain open.
- The decimal accumulator now snapshots three integer limbs explicitly. All five
  byte results remain unchanged; native/i686 C90 compilation passes. Shift masks
  and remaining register choices are closed controls without new evidence. Do
  not repeat integer-type or mask variations to seek compiler coincidences.
- The named x87 descriptor-family recovery is closed at twelve matched records
  from sixteen pinned-library definitions. Do not repeat unchanged data compiles
  or add the four unmatched records. Continue with remaining function source and
  independently grounded runtime storage.
- Twelve x87 operation records now have complete480-byte source storage and
  the original two-byte type alignment. All twelve unique original headers in
  the pinned named descriptor family are covered; unmatched fmod/sinh/cosh/tanh
  records are not added. The last32-byte sqrt owner reuses the prior448 bytes.
  Prefix constants remain outside the trig/transcendental record claims.
  Their original opaque machine entries and low-level helpers remain open.
  Two BSS-free C-dispatch bodies have complete origin proofs; the other five
  entries still lack independent authority for LocalFac/intrinflag BSS. Do not
  infer those addresses from code operands. The scalar trig group has a complete
  origin proof; three newly inventoried intrinsic entries still need independent
  authority for their shared exit to cintrindisp1. The readonly48-byte constant
  record has source, without claiming the unverified589-byte dispatcher or BSS.
  See [operation tables](../research/exact/RUNTIME_X87_OPERATION_TABLES.md).
- Foreign handling now carries the original one-past catch-list pointer through
  its final type checks, subtracting only for the transfer argument. Its remaining
  register/bound-comparison differences are nonexact; do not sweep spellings or
  registers. Three owner exacts are preserved by one four-unit comparison.
- The C++ terminal owner now supplies callback state and two real nested SEH
  scopes. Its source requires a Win32 SEH-capable compiler; VC4 and Clang Win32
  compile the same implementation. Do not replace it with a no-op host catch.
  Object construction/destruction now have [complete source](../research/exact/RUNTIME_CPP_OBJECT.md);
  construction remains nonexact at four register encodings. [Frame unwinding](../research/exact/RUNTIME_CPP_UNWIND.md)
  is now complete and exact. [Catch invocation and cleanup](../research/exact/RUNTIME_CPP_CATCH.md)
  now have a complete exact wrapper and current-state storage. Frame-setting
  and catch transports, guard callbacks, remaining transfer helpers and full
  dispatcher integration remain open. The 41-byte catch guard is now included
  in the inventory; preserve its observed CLD and original forwarding contract.
- The original CRT entry now has [complete exact source](../research/exact/RUNTIME_ENTRY.md)
  and supplies version/command state. Fatal default application type is GUI2.
  It remains outside CMake: final CRT storage/linking, low-level helpers and
  the final original-compiler build/play check are still required. Do not
  count the new standalone object as a verified reconstructed game startup. The
  three member-call trampolines have proven runtime origins but no restored bodies.
- The complete `cvt.c` result is a useful retained control. Inspect the fixed/
  general regressions and exponent improvement together if pursuing that owner;
  do not recompile the unchanged control or split bodies solely to collect zeros.
- Matherr's adjacent store/load order remains open. FP raising is 876 bytes /
  22 differences; C mode makes raising exact but loses the 704-byte handling
  exact. Full original fpexcept ownership also worsens raising. These controls
  are closed unless new evidence changes the question.
- Pow's single-field DOUBLE result-copy control emits584/16, worsening the
  maintained584/8. It is rejected with source restored; do not repeat record or
  field forms. See [pow source](../research/exact/RUNTIME_POW_SPECIAL.md).
- The 34 authored bodies include frame/render/resource flows. Their whole-body
  comparisons and evidence links are in the remaining-functions table and
  `match-units.toml`. Preserve accepted companions when changing shared inputs.
- Near matches such as flush-output 328/1, shared-open 1053/2, fread 326/2,
  setmode 128/2, commit 111/2, handle installation 163/2 and onexit 121/2
  are candidates, not missing-operation counts. Equivalent CMP/register choices
  do not justify spelling or declaration sweeps.
- Read [closed storage diagnostics](../research/exact/CLOSED_STORAGE_DIAGNOSTICS.md).
  Device interfaces, SDK contexts, rotation records, declaration permutations,
  score/intro buffer enlargement and fake board padding have closed controls.
  Keep `DxBallBoardStorage` and its real terminal copy effects.
- Original CRT assembly memcpy/strlen/memset and the EAX/ESP stack probe are not
  ordinary C wrappers. The translator guard restores stack state and jumps.
  Do not invent callback returns, arguments, register initialization or byte arrays.
- The decimal parser has original indeterminate/dead reads. Do not introduce
  fake uninitialized locals solely to reproduce its extra bytes. Likewise,
  do not repair an original memcpy register bug and call that exact recovery.
- No original `/G3`, `/G4` or `/G5` setting has been established. Inspected
  CRT members lack compile/CPU records; shipped release `makefile.sub` says
  `-O2`. This is not evidence for a CPU-option sweep.

Integration/build/play work follows function recovery; ports follow that.
The README already states this route. The macOS PR was already thanked and
deferred in [PR #1](https://github.com/N0zoM1z0/dx-ball/pull/1#issuecomment-6186305581);
no further reply or port work is pending in this handoff.

## Source, evidence and resource requirements

Use natural typed source shared by portable and legacy builds. Preserve ABI,
integer widths, data ownership, actual stores and call order. Do not force
matches with copied machine code, assembly, guessed padding, fake locals,
alternate profile bodies or blind name/type/layout/flag permutations.
Original CRT provenance comes from actual member/file evidence, not symbol
spelling: VC4 C can emit C++-style local-static names.

An exact claim covers the complete function, every actual relocation, full
literal contents and declared attached metadata. Resolve real function exits,
embedded tables and alignment; imported boundaries are provisional. Compare
all accepted units sharing changed inputs. Freeze previous inputs/products
before overwriting them, including recursively consumed headers.

- Run Python through `scripts/repo-python`. Private Python probes use
  `resource_limits.limit_cpu()` and one already-allowed CPU.
- One writable compiler/provider/Wine session at a time.
  `legacy_toolchain.session_lock()` is blocking and non-reentrant; do not
  acquire it around a helper that already acquires it.
- CMake builds use `--parallel 1`. The REA entry point uses the supported
  `GHIDRA_HEADLESS_MAXMEM=256M` path. On this host, wrap compiler/provider/Wine
  commands in a user systemd scope with `CPUQuota=35%`, `MemoryHigh=640M` and
  `MemoryMax=768M`; run heavy tasks serially. See [REA commands](REA.md).
- Automated audio/game probes use `PULSE_SINK=dxball_reconstruction_silent`.
  Prepare native interposers before taking the session lock.
- For new binary analysis, read the installed reverse-engineering skill and
  use `scripts/rea`: pinned REA 6.5.0 / Ghidra 12.1.4.
  Reuse retained dossiers first. Save full responses, Evidence IDs and snapshots
  under `.analysis/rea/`; close/save sessions. Read only relevant facets.
- Use LeanToken for bounded repository exploration. Avoid dumping huge manifests
  or REA dossiers into context.
- Compile once per stable family. Reuse an object only after checking actual
  input closure, flags and product hashes. Repair comparison readers from
  retained objects without restarting the compiler.
- Truncated output or an observation timeout is not producer failure. Poll the
  retained handle or inspect terminal receipts before deciding to restart.
- Keep `src/balls.cpp`'s source-specific GNU C++17 / x87 / excess-precision
  options and C API linkage; see [stored contact](../research/exact/EXACT_REBOUND_STORED_CONTACT.md).
- REA feedback is optional and secondary. If useful, append observed latency,
  output/context cost or usability issues to the existing single file
  `/tmp/dxball_rea_feedback_20261010.md`; do not start another feedback document.

### Cleanup state

The unsigned64 phase shared eight identical immutable carriers and reclaimed
about3.2MiB. Unique source, member, compiler and arithmetic/fault receipts remain;
the canonical object has an independent inode. Receipt:
`.analysis/crt-uninventoried-sections-20261016/cleanup.json`.

The exit-section phase shared12 identical immutable carriers and reclaimed
about3.6MiB. The successful native fixture library is archived alongside the
three Windows-process receipts and source snapshots; current data objects keep
independent inodes. Receipt: `.analysis/crt-exit-sections-20261016/cleanup.json`.

The initializer-section phase shared33 identical immutable carriers and
reclaimed about10.5MiB. Unique source trials, provider read/error receipts and
both probe stages remain; current objects have independent inodes. Receipt:
`.analysis/crt-c-initializer-sections-20261016/cleanup.json`.

The stdio-initialization phase shared19 identical immutable header snapshots
and a closed-run catalog, reclaiming about8.4MiB. Unique products and before
ledgers remain; canonical objects retain independent inodes. Receipt:
`.analysis/stdio-initialization-source-20261016/cleanup.json`.

The exit-bootstrap phase shared47 byte-identical immutable evidence carriers,
reclaiming about13.7MiB. Unique trial sources, diagnostics and products remain;
current canonical compiler objects retain independent inodes. Receipt:
`.analysis/crt-termination-bootstrap-20261016/cleanup.json`.

The CRT-entry phase reclaimed about 33 MiB by sharing identical immutable
closed-run REA catalogs and removing the verified generated latest catalog
alias. All unique reads, the rejected guard lookup, source trials and compiler
products remain. Receipt: `.analysis/crt-entry-source-20261016/catalog-retention.json`.

The frame-unwind phase verified complete duplicate REA 6.5 catalogs before
sharing three closed-run carriers and removing the regenerated latest catalog
alias. About 25 MiB of allocated storage was reclaimed. Mutable aliases are
never hardlinked to immutable evidence. Receipt:
`.analysis/cpp-frame-unwind-source-20261016/catalog-retention.json`. All unique
Evidence, source trials and accepted products remain.

The allocator trials are closed. Their unique sources, objects, compiler
receipts and comparisons remain in `.analysis/allocator-complete-owner-20261016/`.
The maintained shared source and all previous accepted objects were restored.

`clean-local.py` now accepts a missing raw sealed file only when its canonical
regular `.gz` carrier decompresses to the declared SHA-256. Deduplication uses
the compressed carrier's own bytes and SHA, never the raw seal as a compressed
identity. A changed or symlinked raw path cannot be bypassed with a gzip copy.
Eight bounded checks cover valid raw/gzip, changed raw/gzip, invalid gzip,
symlinked raw/gzip and missing carriers.

The previously blocking compressed snapshot remains intact at
`.analysis/checkpoints/exact-midi-lifecycle-283-131/.analysis/exact-midi-lifecycle/before/.analysis/rea/dxball.snapshot.json.gz`.
Its decompressed SHA-256 remains
`dc6ac7d79539cb10b212b70d4634f4dde43be101436e91d67a12283f9f6cb3ac`.

After preview, `clean-local.py --evidence-only --apply` completed 128 archived
hardlink replacements and removed 56 verified redundant root REA aliases.
Journal: `.analysis/cleanup/20261016T040714413096Z.json`. Allocated analysis storage
fell by about 289 MiB; `build/` remained unchanged. All 82 exact producers at that
cleanup checkpoint and their inputs were hash-verified again; its tracking check
passed 543 / 457 / 367. No probe product or unique trial carrier was deleted.

Preserve unique trial sources, receipts, originals and accepted/current products.
Read verified `.gz` fallbacks instead of rerunning producers. Keep mutable current
products inode-independent from archives. Preview exact targets before cleanup;
do not recursively copy/delete evidence trees or tool caches.

## Resume and publish

1. Read [AGENTS.md](../../AGENTS.md), this handoff,
   [WORKFLOW.md](WORKFLOW.md), the remaining-functions table and the selected
   owner note. Inspect `git status --short` and the current reports.
2. When beginning binary/compiler work, verify relevant inputs:

   ```bash
   scripts/repo-python scripts/verify-target.py
   scripts/repo-python scripts/verify-toolchain.py
   scripts/repo-python scripts/validate-tracking.py --require-target
   ```

3. Freeze affected inputs/products, make one evidence-backed trial, compile the
   stable family once, and compare complete affected candidates and accepted
   companions. Use only the minimum useful existing runtime check.
4. Update only changed claims/owner notes. Refresh progress when ledgers change.
   Distinguish executed checks from reused evidence and negative controls.
5. Commit and push verified checkpoints to `origin/main`. Subjects are English
   and begin exactly `gpt-6.1-sol: `. The body states the source question,
   evidence, actual checks, gains/losses and any cleanup.

   ```bash
   git -c http.version=HTTP/1.1 push origin main
   git rev-parse HEAD
   git ls-remote origin refs/heads/main
   git status --short
   ```

Verify remote HEAD independently and leave a clean worktree.
A handoff is not completion of the reconstruction; retain the same full
objective when work resumes. Do not create a new registered goal automatically.
