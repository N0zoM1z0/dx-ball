# DX-Ball reconstruction handoff

Updated October 17, 2026. The reconstruction is unfinished. Recover the English
DX-Ball v1.07 functions as exactly as possible, as readable shared C/C++;
then verify the original VC4 build and playability; resume ports after that.
The user permits the **19 explicit original CRT members** in the restored-CRT
delivery. Removing them is not a delivery gate. Prioritize authored functions.

Repository: `/home/pentester/coding/codex_ida/dx-ball-reconstruction/dx-ball`.
The environment may start one directory above it. Read [AGENTS.md](../../AGENTS.md),
[WORKFLOW.md](WORKFLOW.md) and the selected owner note before changing source.
Keep code, tracked documentation and commits English. Keep the README focused on
the reconstruction approach and REA, with its two centered 900px images.

This file describes current decisions and open work. The previous detailed
[handoff at 865a648](https://github.com/N0zoM1z0/dx-ball/blob/865a648e959df831813b07002f0dbd011c550877/docs/agent/HANDOFF.md)
retains the historical adoption and cleanup chronology. Owner notes and raw
receipts remain in place; old checkpoint totals are not current totals.

## Current authorities

| Inventory | Current value |
| --- | ---: |
| Provisional independent entries | 553 |
| Retired parent-owned compiler-fragment rows, counted separately | 24 |
| Source-present entries | 475 |
| Accepted complete exact functions | 380 |
| Exact code / attached metadata bytes | 77,485 / 244 |
| Complete nonexact comparisons | 95: 34 authored / 60 runtime / 1 generated |
| Scoped semantic ledger rows | 249 |
| Entries without source | 78: 77 runtime / 1 generated |
| Inventory origins | 270 authored / 261 runtime / 21 generated / 1 unknown |

All 270 classified authored entries have source and complete current comparisons:
236 exact and 34 candidates across 29 compiler closures. The source-present
16-byte no-op at `0x40CC20` remains origin/prototype-unknown. Neither the final
authored denominator nor source optimality has been established. These inventories
are separate claims, not interchangeable completion percentages.

| Authority | Purpose |
| --- | --- |
| `config/functions.csv`, `function-origins.csv` | Provisional entries, reconciled extents and origins |
| `config/compiler-fragments.csv` | Retired aliases owned by complete C++ parents; not every internal block |
| `config/implemented.csv`, `matches.csv`, `semantic-acceptance.csv` | Source, exact and scoped semantic claims |
| `config/source-owners.toml`, `match-units.toml` | Source ownership; full compiler recipes, extents and bindings |
| `build/reports/exact-replay.json` | Current 380 accepted comparisons and producers |
| `.analysis/exact-candidate-audit-20261012/comparison.json` | Current 95 complete candidates; directory date is historical |
| [Remaining-functions table](../research/exact/REMAINING_EXACT_FUNCTIONS.md) | All candidate results and owner-note links |
| `.analysis/brick-hit-scope-adoption-20261017/authored-coverage.json` | Current authored source/comparison/closure coverage |

Original `original/DXBALL.EXE`: English v1.07, 158,208 bytes, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
The pinned compiler is VC4 10.00.5270 and linker 3.00.5270; original CRT provenance
uses `.tools/msvc400/lib/libc.lib`. The compiler identity is
`f097e736bb04d38391c8b524945d58809ec4c42e97c056eca6f40bba2de910c3`.
Original compiler settings cannot be inferred solely from this candidate toolchain.

Keep `original/`, `.tools/`, `build/`, `.analysis/` and `ghidra-project/` private.
A source-only clone does not include the assets, tools, products or raw evidence.

## Current source and delivery

The current restored-CRT executable is
`50e406099293b5de1d5088b3d022e585aa493c8a53f152342e526ed15943958c`.
Its recipe is `vc40-restored-crt`: 116 source objects from 113 owners plus three
integration owners, 19 pinned CRT members, `/NODEFAULTLIB /OPT:REF`, six OS DLLs
and no MSVCRT DLL. The image, map and full input/object identities are in
`build/vc40-restored-crt/build.json`. Reuse only after checking the complete closure.

The latest source adoption is [brick-hit iterator scope](../research/exact/EXACT_BRICK_POWERS.md#particle-iterator-scope-adoption)
at `fd4196d`: score-flag storage returns to original EBP-8; the complete candidate
improves from 418 to 416 differences. A retained object with identical producer
inputs supplies the change without another VC4 compile. Seven complete comparisons
preserve five exacts/1,572 bytes and all other affected identities. The final
108-case native selection passes with the existing typed board-surface backing;
initial fixture crashes and a private cleanup error remain retained. Relinking
reuses all 116 objects/19 members; all 1,091 map addresses stay fixed. Only nine
proved frame displacements and twelve timestamp bytes differ from the preceding
image. Counter/pan homes and one receiver producer remain open.

Earlier adopted authored changes remain in their owner notes: [bank allocation scope](../research/exact/BANK_ALLOCATION_SCOPE.md),
[rotation pixel addresses](../research/exact/ROTATION_PIXEL_ADDRESS.md) and
[last-brick expiry scope](../research/exact/LIGHTNING_EXPIRY_SCOPE.md). Their
historical game observations retain their own image identities. No new exact
function follows from these partial improvements.

The [local-target comparator guard](../research/exact/EXACT_LOCAL_TARGET_GUARD.md)
checks actual same-section COFF destinations before accepting a zero-byte result.
Tracking also checks known function-symbol mappings against catalogued entries,
including attached metadata. These guards do not independently recover unknown
symbol identity or ABI. Keep addends separate from symbol targets. The two earlier
brick-hit case mappings are repaired; explanatory operand projections are not exacts.

## Next source question

Choose a specific unaccounted operation, ABI, ownership, lifetime or producer fact.
A small difference count is not itself a source question. Complete correspondence
and unchanged tests do not prove original declarations or absolute optimality.

An independent read-only October 17 review finds no grounded, untried edit in the
following storage gaps. The user has been asked for any existing original 1.07
project, MAP/PDB, headers or build records. New material must first be tied to this
pinned target; its mere authorship or version proximity is insufficient.
The read-only review is retained in
`.analysis/source-frontier-review-20261017/review.json`.

Continuation is currently blocked on missing producer evidence. Three consecutive
continuation checks found no new material or grounded source change within the
recorded constraints; the latest local check found no source, MAP/PDB or project
files in `original/`. Both scoped reviewers are complete, with no pending job.
Resume when target-linked declarations, build context or another independently
supported operation/ABI/storage fact supplies a concrete source question. This
does not prove source optimality or that original source is the only possible
way forward. Do not repeat closed trials or unchanged checks while waiting.

| Function | Established boundary | Missing producer fact |
| --- | --- | --- |
| `draw-score` | All 135 instructions correspond; frame56 versus48 accounts for the 21 displacement/allocation differences | Original decimal-buffer capacity and surrounding declarations; pointer-taking callees expose no capacity |
| `redraw-intro` | Both have 174 instructions; frame140 versus64 and two longer LEAs account for the nine-byte extent gap; rectangle/count homes restored | Original declarations for text/number storage; bases -120/-140 do not prove capacities100/20 or object grouping |
| `load-pcx` | All 227 instructions accounted; current frame308 contains305 typed bytes plus3 slot-padding bytes | Original distances61–64 are unaddressed; their owner, declaration/lifetime context and producer scheduling remain unknown |

Reuse [intro score phase](../research/exact/INTRO_SCORE_PHASE.md),
[score strip](../research/exact/SCORE_STRIP_SOURCE.md),
[PCX packet proof](../research/exact/EXACT_PCX_PACKET_LOOP.md) and
[closed storage diagnostics](../research/exact/CLOSED_STORAGE_DIAGNOSTICS.md).
Keep the current justified buffer capacities. Adjacency does not establish an
aggregate; a smaller body or one-position count gain does not recover a variable
home. The PCX packet trial rotates four homes and restores none; it stays rejected.
Do not repeat its API-record, scanline-record, header-scope or packet-scope trials.

Other closed authored boundaries:

- Preserve the real 20,432-byte `DxBallBoardStorage` and the 368-byte terminal
  overlap. No alias cells, split globals, artificial padding, alternate offset/cast
  spellings or source unification solely to force emission. Editor key and game
  frame differences include already explained address producers.
- [Rotation](../research/exact/ROTATION_PIXEL_ADDRESS.md) accounts for all 365
  renderer instructions, 22 calls and 26 branches under its stated stable-memory,
  finite-FP model. Height's two bank-address groups explain its two extra bytes.
  Row-add, inline-bank, max/return/FP and type-context controls are closed.
- [Effect sprites](../research/exact/EFFECT_SPRITE_PATH_CORRESPONDENCE.md) have
  complete path/ABI/RECT-write correspondence and retained SMT mutation controls.
  SDK/interface/record context trials do not justify another permutation.
- Triangle's four root-constructed FixedPoint objects precede early exits; do not
  narrow them arbitrarily. The adopted scanline scope restores y's home; vertical
  scale and polygon endpoint-scope controls are closed.
- Bank cursor/row/column, file-metadata and transfer-workspace scopes are closed.
  Preserve callback-visible state and the pitch snapshot before Lock.
- [Brick-hit pan consumer scope](../research/exact/EXACT_BRICK_POWERS.md#closed-pan-consumer-scope)
  is rejected:416→418 differences, wrong pan home and loss of the restored score
  flag. One owner compile preserves all five exact companions; keep current source.
- Line, ranking, presentation, palette, clock and text near-matches include known
  compare/register commutations. Reversing guards, renaming identifiers, changing
  equivalent types or sweeping `/G3`, `/G4`, `/G5` is not new evidence.
- Keep time sampled before RNG. The reversed-addition proposal fails an existing
  ordered case. Clang reverses the four last-brick particle RNG arguments relative
  to original/current GCC; the recorded port gap is deferred, not repaired here.

The [public author-context review](../research/exact/AUTHOR_SOURCE_CONTEXT.md)
supplies no 1.07 declaration, capacity, flag or shared-routine identity. Do not
repeat that search or import another project's settings. Do not replace source
work with repeated coverage audits or unchanged runtime episodes.

## Inventory evidence and approved runtime dependencies

[Joined text coverage](../research/exact/CRT_SUFFIX_OWNERSHIP.md#joined-declared-text-coverage)
accounts for all 126,700 declared text bytes through existing source/CRT owners;
3,650 gap bytes are CC. [Incoming-reference](../research/exact/CRT_SUFFIX_OWNERSHIP.md#incoming-references-to-declared-game-bodies)
and [PE relocation](../research/exact/CRT_SUFFIX_OWNERSHIP.md#original-pe-code-address-relocations)
reviews retain their bounded scopes. The [direct-transfer review](../research/exact/CRT_SUFFIX_OWNERSHIP.md#direct-transfers-in-the-declared-game-prefix)
accounts for all 289 declared prefix spans: 23,469 instruction sites, 3,719 direct
transfers, 16 tables/191 address words and 492 selector bytes. All represented
direct/table destinations are known entries or same-parent instructions. Another
142 calls use import cells; 177 register-relative call values remain unresolved.
Outside-prefix sources, alternate code and runtime-only targets remain open.
None of these checks proves the final authored denominator. Reuse their sealed
results rather than repeating a walk for the unchanged original.

[Dependency receipts](../research/exact/CRT_DEPENDENCY_INVENTORY.md#complete-receipt-coverage)
cover all 78 no-source entries; 19 member dependencies remain explicitly approved.
Do not fabricate ordinary C wrappers for EAX/ESP stack probes, x87/SEH transports,
or assembly memcpy/strlen/memset. C++ frame handlers use their actual implicit EAX
contract. Original dead/indeterminate reads, overlapping copies and pointer
formation are documented behaviors, not opportunities for silent repair.

Existing runtime/data source authorities remain separate from function counts:
`runtime-x87-operation-tables.json` (12 records/480 bytes),
`runtime-x87-dispatch-constants.json` (48 readonly bytes),
`runtime-character-state.json` (ctype/locale storage and pointer bindings), and
`runtime-locale-handles.json` (28-byte relative layout; target address null), all
under `config/`. No independent BSS address follows merely from a code operand.
All eight allocator functions are exact; actual C++ new/delete, entry, stdio and
exit integration are documented in their owner notes. Preserve `.CRT$XIC` stdio
before onexit, the shared callback state and real Win32 heap/raster defaults.
SEH bodies require a capable compiler; do not substitute no-op host catches.
Historical whole-cvt/C-mode/register-order controls remain rejected. Keep accepted
companions; do not split owners or add barriers solely to select private zeros.

## Actual game evidence

The [current-image bounded entry/exit check](../research/RESTORED_CRT_ROUND_FLOW.md#current-image-bounded-entry-and-exit)
passes 5.019 seconds on original board0: all 400 initial bytes, 1,410 valid samples,
no malformed lines, score10/lives3, menu return and actual exit0/no window. The
20,000-byte bank and 49 originals stay unchanged. Measured CPU is32.1% of one CPU,
peak301.668 MiB, no memory-limit events. A preceding per-read attempt fails before
gameplay with 42 reset-requested samples; keep its failure separate. Persistent
reader success does not establish failure causality or focus recovery. Both runs
reuse the game/reader without compilation. Do not repeat this unchanged episode.

The historical [original50 attempt](../research/ORIGINAL_CAMPAIGN.md#current-restored-crt-original-bank-prefix-october-17)
is terminal, observer exit1 at the14,400-second deadline. It verifies initial
boards0–19, then retains index19/15 bricks/score52,538/lives3. Its611,084 valid
samples and1,473 events do not establish full50 completion, a crash or normal
application exit. All three owned identities are absent. Never restart its
producer or reapply pass-only verification to that failure.

Earlier [editor](../research/RESTORED_CRT_EDITOR_FLOW.md),
[game-over](../research/RESTORED_CRT_GAMEOVER_FLOW.md),
[round](../research/RESTORED_CRT_ROUND_FLOW.md),
[custom terminal50](../research/RESTORED_CRT_TERMINAL_FLOW.md) and
[natural expiry](../research/RESTORED_CRT_LIGHTNING_FLOW.md) controls keep their
recorded images and limits. Custom single-brick boards are not the untouched
original campaign. [Sparse-tail controller](../research/CAMPAIGN_TAIL_CONTACTS.md)
checks do not prove live speedup or full50 progression. The original Wine9
[focus/surface-loss failure](../research/ROUND_FOCUS_RUNTIME.md) remains unresolved;
do not patch exact game behavior or rerun its unchanged loop. Physical Windows,
graphics/audio fidelity, exceptional paths and full campaign acceptance stay open.
The macOS PR was already answered and deferred; no further message or port work
is pending. The complete objective remains unachieved; continuation is blocked
as described above.

## Resources, cleanup and publication

Use `scripts/repo-python`, `resource_limits.limit_cpu()` and one allowed CPU.
One writable compiler/provider/Wine session at a time; the blocking
`legacy_toolchain.session_lock()` is non-reentrant. Do not wrap a helper that
already acquires it. CMake uses `--parallel 1`; keep `balls.cpp`'s documented GNU
C++17/x87/excess-precision options and C linkage. Prepare native interposers before
taking the lock. Automated audio goes to `PULSE_SINK=dxball_reconstruction_silent`;
never change the default sink.

Run heavy commands in a user scope with CPU35%, memory high640 MiB/max768 MiB.
[REA](REA.md) is pinned at6.5.0/Ghidra12.1.4 with a256 MiB heap. Reuse retained
Evidence first, query only missing facets, retain full responses and close/save
sessions. Use LeanToken for bounded source reads. A timeout/truncated preview is
not producer failure: poll its live handle or inspect terminal receipts before
considering a restart. Optional REA feedback stays in the existing single
`/tmp/dxball_rea_feedback_20261010.md` file.

Compile once per stable family; compare complete affected candidates and accepted
companions, including all relocations, full literals and attached metadata. Freeze
previous products and recursively consumed inputs before overwriting them. Use
only the minimum useful existing Oracle/play check. No default historical queue,
repeated unchanged checks or full replay after every edit. When beginning actual
binary/compiler work, verify relevant inputs with `verify-target.py`,
`verify-toolchain.py` and `validate-tracking.py --require-target` through repo Python.

Clean unused products regularly after verifying unique evidence. Historical
`build/native-*` directories were archived and removed; restore their retained
product only if needed. Current native/exact/VC4 caches, originals and manual saves
remain. `scripts/clean-local.py` previews cleanup and includes restored-CRT probe
directories. Its verified gzip fallback obeys the decompressed old seal; mutable
current products must never be hardlinked to immutable archives. Do not recursively
delete evidence trees or tool caches. Recent journals are
`.analysis/storage-cleanup-current-20261017/verification.json`,
`.analysis/storage-maintenance-20261017/verification.json`, and
`.analysis/game-prefix-direct-flow-20261017/verification.json`. They distinguish
allocated disk release from logical duplicate-byte totals.

Update only changed claims; refresh progress when ledgers change. Commit and push
verified checkpoints to `origin/main` with the English subject prefix
`gpt-6.1-sol: `. State the actual source question, evidence, checks and limits.
Disable opportunistic git GC for these checkpoints, verify the remote independently
with `git ls-remote`, and finish with `git status --short`. Do not mark the goal
complete because a fixture passes, all current rows have source, or a handoff is tidy.
