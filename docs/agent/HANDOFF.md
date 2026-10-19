# DX-Ball reconstruction handoff

Updated October 19, 2026. The reconstruction is unfinished. Recover the English
DX-Ball v1.07 functions as exactly as possible, as readable shared C/C++;
then verify the original VC4 build and playability; resume ports after that.
The user permits the **19 explicit original CRT members** in the restored-CRT
delivery. Removing them is not a delivery gate. Prioritize authored functions.

Repository: `/home/pentester/coding/codex_ida/dx-ball-reconstruction/dx-ball`.
The environment may start one directory above it. Read [AGENTS.md](../../AGENTS.md),
[WORKFLOW.md](WORKFLOW.md) and the selected owner note before changing source.
Keep code, tracked documentation and commits English. Keep the README focused on
the reconstruction approach and REA, with its two centered 900px images.

This file describes current decisions and open work. The detailed
[handoff at c99ab9e](https://github.com/N0zoM1z0/dx-ball/blob/c99ab9e62fcc1625a0c0754a3ee0abb67dc10623/docs/agent/HANDOFF.md)
retains the preceding adoption and cleanup chronology. Owner notes and private
receipts remain authoritative within their stated scopes. Historical totals
are not current totals.

The user resumed authored-source recovery, followed by the final game build and
then actual game verification. Whole-EXE byte identity is not required. Use only
necessary focused checks; no new campaign is pending.

## Current authorities

| Inventory | Current value |
| --- | ---: |
| Provisional independent entries | 553 |
| Retired parent-owned compiler-fragment rows, counted separately | 24 |
| Source-present entries | 475 |
| Accepted complete exact functions | 393 |
| Exact code / attached metadata bytes | 84,633 / 244 |
| Complete nonexact comparisons | 82: 22 authored / 60 runtime / 0 generated |
| Scoped semantic ledger rows | 249 |
| Entries without source | 78: 77 runtime / 1 generated |
| Inventory origins | 270 authored / 261 runtime / 21 generated / 1 unknown |

All 270 classified authored entries have source and complete current comparisons:
248 exact and 22 candidates across 30 compiler closures. The source-present
16-byte no-op at `0x40CC20` remains origin/prototype-unknown. Neither the final
authored denominator nor source optimality has been established. These inventories
are separate claims, not interchangeable completion percentages.

| Authority | Purpose |
| --- | --- |
| `config/functions.csv`, `function-origins.csv` | Provisional entries, reconciled extents and origins |
| `config/compiler-fragments.csv` | Retired aliases owned by complete C++ parents; not every internal block |
| `config/implemented.csv`, `matches.csv`, `semantic-acceptance.csv` | Source, exact and scoped semantic claims |
| `config/source-owners.toml`, `match-units.toml` | Source ownership; full compiler recipes, extents and bindings |
| `build/reports/exact-replay.json` | Current 393 accepted comparisons and producers |
| `.analysis/exact-candidate-audit-20261012/comparison.json` | Current 82 complete candidates; directory date is historical |
| [Remaining-functions table](../research/exact/REMAINING_EXACT_FUNCTIONS.md) | All candidate results and owner-note links |
| `.analysis/bank-count-bound-20261019/authored-coverage.json` | Current authored source/comparison/closure coverage |

Original `original/DXBALL.EXE`: English v1.07, 158,208 bytes, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
The pinned compiler is VC4 10.00.5270 and linker 3.00.5270; original CRT provenance
uses `.tools/msvc400/lib/libc.lib`. The compiler identity is
`f097e736bb04d38391c8b524945d58809ec4c42e97c056eca6f40bba2de910c3`.
Original compiler settings cannot be inferred solely from this candidate toolchain.

Keep `original/`, `.tools/`, `build/`, `.analysis/` and `ghidra-project/` private.
A source-only clone does not include the assets, tools, products or raw evidence.

## Current source and delivery

Current delivery: `build/vc40-restored-crt/dxball.exe`,166,400 bytes, SHA-256
`f0f2fa2eefaa48aceb23b150dd894ee2daf6db13efe709f98c8cacacfcb8b5d4`.
The [current VC4 build and play check](../research/CURRENT_VC4_BUILD.md) includes
both October19 source recoveries at717cc2f. All118 current source/integration
objects are verified and reused, then linked with the19 approved CRT members.
Resources is the only changed source object relative to the preceding delivery.
All1,099 named map addresses remain fixed. Complete linked sections,5,904 COFF
bindings and all4,488 loader fields are checked; imports/resources stay fixed.

The existing actual play flow passes on this image: ball/paddle/pause/resume,
editor CTRL painting, exact20,000-byte save/reload and normal exit0. There are
589 state observations and2,444 valid SDK samples,zero malformed samples;
all49 originals remain fixed. CPU/memory are35%/384MiB high/512MiB max, with
no high/max/OOM events. This does not establish full50,focus/surface recovery,
physical-driver fidelity or every exceptional path. Detailed evidence and limits
are in the linked note and private `current-vc4-build-20261019/` and
`current-vc4-play-20261019/` directories under `.analysis/`.

The [bank byte-count recovery](../research/exact/BANK_BYTE_COUNT_ARITHMETIC.md)
defines the observed low32 allocation/fread product and explicitly demotes two
glyph exacts after changed address producers. The latest
[count-bound recovery](../research/exact/BANK_COUNT_BOUND.md) preserves the live
modulo32 increment and signed guard, improving bank64→63 differences. All18
resource bodies/262 bindings/six full literals compare together;11 exacts and
16 complete code identities survive the count-bound change. The bounded actual
INT_MAX counterexample and ten existing bank cases pass. PCX stays979/850;
find-glyph146/86 and draw-glyph332/258 remain candidates. Current authored totals
stay248 exact/22 complete candidates across30 verified compiler closures.
The focused native receipts are `.analysis/bank-count-bound-20261019/native-build.json`
and `selected-oracle.json`.

The older `build/native/retained-build.json` predates MulDiv integration in four
non-resource inputs; it remains historical and must not be used as a current
whole-build input attestation. No such native claim is added here.

Relevant accepted source contracts:

- [Independent board storage](../research/exact/INDEPENDENT_BOARD_STORAGE.md)
  preserves seven real objects, two mutable unknown slots, the real list word
  at +0xC, natural pointer widths, ordered linker sections and retained memmove.
  The 20,432-byte layout and 368-byte terminal overlap are ABI observations;
  the descriptor is a view, with no enclosing instance or ISO array-bounds claim.
  Adoption promoted17 complete units and demoted eight; do not hide those losses
  with old objects or selective header variants.
- [Score workspace](../research/exact/INTRO_SCORE_PHASE.md) and
  [score strip](../research/exact/SCORE_STRIP_SOURCE.md) capacities follow real
  consumers and independent workspace regions. They do not justify padding in
  unrelated functions.
- [Paddle sampling](../research/exact/PADDLE_WIDTH_SAMPLING_SCOPE.md) preserves
  the sampled width and dirty-right sum; its complete body remains677/68.
- Bank loading preserves callback-visible state, partial failure ownership,
  and the pitch snapshot before Lock. Keep the Windows allocation-mode argument
  and COM behavior; foreign Image/backend records are different.
- Keep the documented GNU C++17/x87/excess-precision options for `balls.cpp`,
  C linkage, real Win32 heap/raster defaults, and stdio-before-onexit ordering.

## Last closed work

October19 [current VC4 rebuild and play](../research/CURRENT_VC4_BUILD.md) closes
the previously missing current-source delivery check. The17.003s build and
86.614s existing play flow pass under the capped scope. Seven closed build
helper/evidence files are member-hash verified in a140,888-byte archive,
releasing1,572,864 allocated bytes net before the receipt. The49 automated runtime
copies are removed after matching retained originals,current game or complete
saved bank; current products,caches and manual files stay. Exact/semantic counts
are unchanged. Source recovery and broader acceptance remain unfinished.

October19 [count-bound recovery](../research/exact/BANK_COUNT_BOUND.md) retains
the original live count reload, DWORD increment and signed comparison without
signed C++ overflow. Independent source/result review confirms the bounded
counterexample and complete18-body comparison. Totals stay248 authored exacts/
22 candidates,393 overall exacts; all270 current authored closure receipts pass
without a replay. Private authority is `.analysis/bank-count-bound-20261019/`.
Its26 closed input/product copies are member-hash verified in a1,025,437-byte
archive, releasing7,774,208 allocated bytes net before the small receipt.
Current products and incremental caches remain. The preceding byte-count work
and its cleanup follow.

October19 [byte-count arithmetic](../research/exact/BANK_BYTE_COUNT_ARITHMETIC.md)
is adopted with its full18-body comparison, bounded overflow witness, ten existing
bank cases and explicit two-glyph demotion. All270 authored entries have current
source/object/flag/complete-comparison receipts. The28 reviewed closed input and
product files are member-hash verified in a1,023,104-byte archive, releasing
7,790,592 allocated bytes after archive cost and before the small cleanup receipt.
Current products and caches remain. Private authority is
`.analysis/bank-byte-count-20261019/`, including independent review, coverage and
`cleanup.json`. The following filename/path review is the preceding closed work.

The [bank filename and path review](../research/exact/MAC_CANDIDATE_FLOW_CONNECTIONS.md#bank-filename-qualification-and-path-boundary)
reads one previously missing416-byte Mac helper through REA6.5 process capture
of the saved Ghidra project. All104 instructions,18 branches and six calls are
accounted for. Direct nonstack writes use a separate pointer loaded through r2;
input/output aliasing and four callee effects remain unknown. This does not
recover the Windows qualifier or prove mutable input.

One fixed filename/callback qualifier inference then receives one resource
compile. All18 complete raw/resolved bodies,262 bindings and six full literals
remain identical;13 prior exacts/3,050 bytes survive. Both complete12,332-byte
COFF files differ only in timestamp bytes4–5. Bank remains1475/64. Reject the
whole model; keep the canonical const API. The other27 owners/254 functions
remain uncompiled and unknown for that proposal. All754 protected SHA/mode/
nsmtime identities restore. No native build, relink, game or full replay follows.

The compiler/restore/comparison pipeline takes4.795s, peak193,404,928 bytes,
zero memory-limit events. The saved-project capture peaks403,165,184 bytes,
767 soft-high events and zero max/OOM events. Both use CPU0/35%,384/512MiB.
The verified33-member archive removes two temporary objects, seven proposals
and closed capture/runner inputs, releasing729,088 allocated bytes net.
Current products, useful caches, the saved project and selected helper export
remain. Private receipts:

- `.analysis/bank-filename-qualifier-20261018/`: eligibility/plan/result reviews,
  `summary.json`, `restoration.json`, `protected.json`, `archive-manifest.json`,
  `cleanup.json`, and `closed-model-and-path-capture.tar.gz`.
- `.analysis/mac-path-contract-20261018/`: question, complete selected export,
  process resource receipts and `independent-path-contract-review.json`.
- Capture Evidence `ev_acd98536850530d1f826c778dcdfaea0a33588ea746708b4111168ceaf0ce64c`.
  Full process Evidence is inside the verified archive, not a native snapshot.

Other recent closed models are indexed in
[Mac candidate flows](../research/exact/MAC_CANDIDATE_FLOW_CONNECTIONS.md) and
[fixed-point notes](../research/exact/EXACT_FIXED_POINT.md): bank API names,
paddle float-input precision, line public name, score parameter kind, and the
paired triangle/span DWORD colour declaration. The colour model regresses both
polygons while preserving ten other bodies; reject the whole model. The score
parameter model regresses paddle. Do not repeat these trials or widen them in
response to their outputs. The bounded polygon source-index lookup returned
zero matches with shard limits; it does not prove source absence.

## Resuming authored recovery

Start with the current [22-function table](../research/exact/REMAINING_EXACT_FUNCTIONS.md#authored-candidates),
`config/functions.csv`, the relevant owner note and retained complete evidence.
Missing original declarations are reconstruction work, not an external blocker.
Form one bounded inference from actual producers, consumers, ownership or layout;
unique historical spelling is not required. A small byte-difference count alone
is not a new source question. Keep inference separate from recovered fact.

| Family | Reuse before another proposal | Boundary to preserve |
| --- | --- | --- |
| Bank/resources | [Bank flow and closed controls](../research/exact/MAC_CANDIDATE_FLOW_CONNECTIONS.md#reused-bankshape-bodies-and-api-name-control), current frontend/backend traces | Bank1475/63 restores extent/yoffset and low32 byte/count arithmetic; names, filename qualification, cursor/row/column and transfer scopes are closed |
| PCX | [Complete packet proof](../research/exact/EXACT_PCX_PACKET_LOOP.md), [storage diagnostics](../research/exact/CLOSED_STORAGE_DIAGNOSTICS.md) | Original862/current979; all227 instructions accounted. Current308-byte frame has305 typed bytes plus3 slot padding. Original unaddressed four bytes do not justify a132-byte header or fake local |
| Triangle/polygons | [Fixed-point](../research/exact/EXACT_FIXED_POINT.md), [polygon workspace](../research/exact/POLYGON_SCAN_WORKSPACE.md) | Four root FixedPoint constructions/EH states;28-byte edge has one unknown word at+12. Preserve paired accesses, three pools, both Shellsorts and signed negative-error carry |
| Rotation | [Pixel-address correspondence](../research/exact/ROTATION_PIXEL_ADDRESS.md) | All365 instructions/22 calls/26 branches accounted. Unknown80-byte frame difference is not permission to add padding; integer-offset-before-base order is restored |
| Line/ranking/presentation | [Line](../research/exact/LINE_LOCKED_CURSOR.md), [ranking](../research/exact/RANKING_OWNER_FAMILY.md), [presentation](../research/exact/PRESENTATION_MERGE_SCOPE.md) | Known comparison/register producers remain. Fixed line rank model restores directions but loses correct homes; ranking has original homes and one shorter compare producer |
| Clocks/palette/last brick | [Author context](../research/exact/AUTHOR_SOURCE_CONTEXT.md), [lightning crop chain](../research/exact/EXACT_LIGHTNING_CROP_CHAIN.md) | Clock cache/sampling order accounted; shared unsigned-long context already tested. Keep clock before RNG and existing callback-visible state |

Resource callback-table extraction and historical DirectDraw header controls
can produce a private exact release-sprite while losing prior exact companions.
Those models remain rejected. Full-owner C/C++ and broad declaration controls
are also closed. Avoid name/order/count/flag sweeps, fake unused storage, assembly,
per-profile bodies, selective old objects, and repeated unchanged controls.
The [historical handoff](https://github.com/N0zoM1z0/dx-ball/blob/c99ab9e62fcc1625a0c0754a3ee0abb67dc10623/docs/agent/HANDOFF.md)
and linked owner notes retain the detailed boundaries of older trials.

## Reusable evidence and runtime limits

[REA](REA.md) is pinned at6.5.0/Ghidra12.1.4. The old MCP catalog can still report6.4;
use fresh `scripts/rea` CLI calls. Reuse closed evidence before opening a provider.
Native PEF admission is unsupported. Retained Mac observations use REA process
capture of pinned Ghidra; no native-provider snapshot or runtime r2/TOC model is
established. Use corrected `PowerPC:BE:32:default` exports with r2 unset.

Useful private Mac paths are `mac-port-payload-20261018` (carrier and321 named
traceback records), `mac-pef-focused-bodies-20261018` (corrected17-body export),
`mac-candidate-bodies-20261018` (loaded data/relocations/symbols), and the later
candidate-flow/score/path review directories, all under `.analysis/`.
The loaded645,276-byte data image is static loader evidence. Keep original
failed/wrong-width records separate. Reuse sealed compiler C1/C1XX/C2 snapshots
and traces; cold imports are expensive and do not recover original declarations
by themselves. [Frontend symbol order](../research/exact/VC4_FRONTEND_SYMBOL_ORDER.md)
and [backend records](../research/exact/VC4_BACKEND_SYMBOL_RECORDS.md) explain their limits.

[CRT dependency receipts](../research/exact/CRT_DEPENDENCY_INVENTORY.md#complete-receipt-coverage)
cover all78 no-source entries;19 original member dependencies are approved.
Do not divert authored recovery into fake C implementations of x87/SEH/stack
probe transports. Joined text/direct-flow audits retain their bounded scopes;
the final authored inventory is not established. The October19 inventory review
classifies all177 register-relative sites as DirectDraw/DirectSound COM calls
using receiver provenance and actual slots:98 surface,19 draw,9 palette,2 clipper,
13 sound-device and36 sound-buffer calls. Concrete runtime method addresses and
driver behavior remain unknown; these sites do not identify missing authored
functions. All74 retained instruction carriers are hash verified. See private
`bank-count-bound-20261019/directx-call-classification.json` and `inventory-review.json`.
These bounded reviews do not prove a final denominator or unrestricted semantic
equivalence of the22 candidates. After concrete source gaps are fixed, proceed
to the requested VC4 rebuild and actual game checks; do not block that work on
unique historical source spelling.

Earlier [entry/exit evidence](../research/RESTORED_CRT_ROUND_FLOW.md#current-image-bounded-entry-and-exit)
passes a bounded board0 episode on an earlier image. The historical
[original50 campaign](../research/ORIGINAL_CAMPAIGN.md#current-restored-crt-original-bank-prefix-october-17)
ended at its14,400s deadline after verifying initial boards0–19. It did not
complete50 or establish a crash/normal application exit; never restart that
producer. Custom single-brick boards and prior GUI episodes retain their own
image identities. Physical Windows, graphics/audio fidelity, exceptional paths,
full campaign acceptance and Wine9
[focus/surface-loss](../research/ROUND_FOCUS_RUNTIME.md) remain open.
The current image passes only the bounded play/editor flow described above;
it adds no full campaign or physical-driver acceptance. Ports remain deferred.

## Execution, cleanup and publication

Use `scripts/repo-python`, bounded LeanToken source reads, one allowed CPU and
one writable compiler/provider/Wine session. `session_lock()` is non-reentrant;
do not wrap a helper that already acquires it. CMake uses `--parallel 1`.
Heavy commands run in a user scope:

```bash
systemd-run --user --scope --quiet \
  -p CPUQuota=35% -p MemoryHigh=384M -p MemoryMax=512M \
  scripts/repo-python <focused-command>
```

REA's general Java heap cap is256MiB; the saved Mac project queries use128MiB
and Node192MiB. Do not overlap heavy trees. Automated audio uses
`PULSE_SINK=dxball_reconstruction_silent`; never change the default sink.

For a genuine new source model, verify the relevant target/toolchain, freeze
previous products and all recursive inputs, compile once per stable family,
and compare complete affected candidates and accepted companions. Include
all actual relocations, local destinations, full literals and metadata.
Restore canonical bytes, modes and nanosecond mtimes in `finally` under the lock;
verify Toolchain on both sides, including failures. Own child process groups
before restoring parent signals; unblock inherited signals in workers. Cleanup
ignores repeated TERM/INT, uses TERM plus bounded communicate, then unconditional
KILLPG and wait even if the group leader exited. A timeout preview is not a
reason to restart a still-live producer.

No default full replay, historical Oracle queue or repeated unchanged game run.
Update only changed claims; the handoff cleanup changes no ledger or progress
count. Current tested native/exact/VC4 products, useful incremental caches,
originals, manual saves and saved Ghidra project remain private and retained.
The20 existing probe/reference files inspected during handoff include reusable
readers and unique evidence; none is blindly deleted.

Archive unique closed evidence, verify every member's size/SHA, then remove only
the exact reviewed list. The latest archive/member hashes and allocated-byte
accounting are in the cleanup receipts above. Older historical raw paths may
have verified `.json.gz` carriers; check their original decompressed seals.
Never hardlink mutable products or aliases to immutable archives. The general
`scripts/clean-local.py` defaults to preview; inspect its proposed scope before
using `--apply`. Do not recursively remove evidence, tools or current caches.

Publish verified checkpoints to `origin/main` with an English subject beginning
`gpt-6.1-sol: `. Disable opportunistic Git GC/maintenance, verify raw commit message
bytes against the prepared message, check the remote with `git ls-remote`, and
finish with a clean worktree. A tidy handoff or complete source coverage does not
mean reconstruction is complete.
