# DX-Ball reconstruction handoff

Updated October 16, 2026, after CRT-startup checkpoint `14cc03c` on
`origin/main` and compiler-fragment ownership reconciliation below. Twenty-four
old auto-analysis splits now have explicit parent mappings. Source, exact and
semantic claims are unchanged; every original address remains recorded.
Three additional C++ exception entries now have complete original CRT origin
proofs; the translator guard extent is corrected from 98 to 107 bytes.
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
| Provisional independent function inventory | 520 |
| Parent-owned compiler fragments, counted separately | 24 |
| Source-present independent entries | 464 |
| Accepted exact functions | 373 |
| Complete exact code bytes | 76,842 |
| Attached exact metadata bytes | 244 |
| Historical scoped semantic rows | 249 |
| Complete nonexact comparisons | 88 |
| Source-present entries outside the two comparison reports | 3 |
| Inventory entries without a source-present ledger row | 56 |
| Nonexact origins | 34 authored / 53 runtime / 1 compiler-generated |
| Inventory origins | 270 authored / 217 runtime / 21 compiler-generated / 12 unknown |

These are separate inventories, not interchangeable completion percentages.
The authored denominator and 12 unknown origins remain open.
All 34 authored candidates have complete comparisons; the
[remaining-functions table](../research/exact/REMAINING_EXACT_FUNCTIONS.md)
now lists all 88 maintained candidates.

Three additional source-present entries remain in `src/allocator.c`: physical
HeapFree, HeapAlloc and HeapCreate wrappers. Five other allocator entries now
have complete exact acceptance. Thus 88 is not the total remaining work:
91 source-present entries are not exact, and another 56 independent inventory entries lack
a source-present row. The remaining-functions page lists the three gaps.

Current accounting is 520 independent entries plus 24 parent-owned compiler
fragments, preserving all 544 previously recorded addresses. The twenty
fixed-point unwind cleanups and four shared epilogues belong to the complete
triangle/division/comparison/addition owners. Their source, metadata and code
ranges were already part of those units; they are now recorded in
`config/compiler-fragments.csv` and validated against their parents.

All four complete parent comparisons reproduce their retained results from
the existing canonical object: three exact methods and the unchanged 88-byte
triangle candidate. No compiler/provider/runtime work was repeated. Source464,
exact373, code76,842, metadata244 and semantic249 remain unchanged. The 56
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
- `config/compiler-fragments.csv`: parent-owned unwind/epilogue aliases with original ranges and evidence; excluded from independent counts.
- `config/implemented.csv`, `matches.csv`, `semantic-acceptance.csv`:
  source, exact and scoped semantic claims.
- `config/source-owners.toml`: maintained source ownership.
- `config/match-units.toml`: compiler inputs, flags, complete extents and bindings.
- `build/reports/exact-replay.json`: current 373 accepted comparisons/producers.
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

## Last private trial: completed, not adopted

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

- Five allocator entries are now exact. The three Heap API wrappers still need
  one consistent import-cell owner. Read [allocator ownership](../research/ALLOCATOR_OWNER.md)
  before revisiting them: shared public cells and an allocator-only import header
  both lose accepted companions and are closed controls. Do not rebase one table
  differently per function. The 56 independent inventory entries without source rows remain
  in scope.
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
