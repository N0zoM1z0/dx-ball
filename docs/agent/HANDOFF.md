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
| `.analysis/ranking-coordinate-wrap-20261019/authored-coverage.json` | Current authored source/comparison/closure coverage |

Original `original/DXBALL.EXE`: English v1.07, 158,208 bytes, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
The pinned compiler is VC4 10.00.5270 and linker 3.00.5270; original CRT provenance
uses `.tools/msvc400/lib/libc.lib`. The compiler identity is
`f097e736bb04d38391c8b524945d58809ec4c42e97c056eca6f40bba2de910c3`.
Original compiler settings cannot be inferred solely from this candidate toolchain.

Keep `original/`, `.tools/`, `build/`, `.analysis/` and `ghidra-project/` private.
A source-only clone does not include the assets, tools, products or raw evidence.

## Current source and delivery

Current source includes the [ranking coordinate subtraction](../research/exact/RANKING_COORDINATE_WRAP.md):
the original DWORD subtraction is explicit before the signed text coordinate.
All8 gameover code identities/234 bindings/13 literals stay fixed, including
seven exacts; ranking stays403/330. The finite boundary case and17 unchanged
ranking cases pass. Current native SHA is
`cd30d703f106cece05e62912d6033519b2c7238f25e26bc456fa3464efe83e2e`.
Private authority is `.analysis/ranking-coordinate-wrap-20261019/`.
The separate text-advance proposal loses draw-text150exact→153/20 and is rejected;
canonical ui.c stays fixed. Its finite final-advance boundary remains documented,
without claiming all exceptional text arithmetic is defined.

Current source includes the [PCX coordinate correction](../research/exact/PCX_COORDINATE_WRAP.md):
four literal/RLE destination increments preserve original DWORD wrap before
signed clipping. All18 complete resource identities/262 bindings/six literals
stay fixed, including11 exacts and PCX979/850. Four finite clipped counterexamples
and99 unchanged existing PCX cases pass. The PCX-checkpoint native SHA was
`78d8e0e6f9f63e8e19a277f3df7dc4e722243eff3fb2e605d30be5127dfb8c6c`.
Private authority is `.analysis/pcx-coordinate-wrap-20261019/`.

Source also retains the [file-field/text-width corrections](../research/exact/AUTHORED_BOUNDARY_CONTRACTS.md):
four fread output lifetimes span later EOF; both measurement branches retain
original modulo32 addition and signed half-width division. Full25-body/300-binding/
six-literal comparisons preserve17 exacts and23 other code identities. Bank
worsens1475/63→1475/68; measurement279/3→282/26. Bounded counterexamples and
10 existing bank/216 measurement cases pass. Counts stay248 authored exact/22
candidates,393 overall exacts. Both current matching objects and native library
include those source changes. The preceding boundary-checkpoint native SHA was
`8ed0f953adda504213452d801130961e1ad6ae0c6572d12e5ad077db33359bb5`.
Private authority is `.analysis/authored-boundaries-20261019/`.

The EXE/ZIP below remain the last verified delivery at717cc2f and **predate
these current source changes**. Do not transfer their play claims to the
new source. Continue authored recovery before the next final build/game check.

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
all49 originals remain fixed. Subsequent current-image lifecycle checks pass:
real single-brick clear earns10 points and loads all400 original board1 bytes/
222 bricks with three lives; natural losses3→2→1→0,`reA`/222 ranking insertion,
complete660-byte persistence and fresh-process reload both exit0. The round
uses127 observations; accepted game-over uses1,198. An initial game-over
single-sample observation times out with one live descending ball; retain that
failure separately from the accepted persistent transport. All existing flow
bodies/assertions and its90s life-loss limit remain unchanged. CPU/memory are
35%/384MiB high/512MiB max, with no high/max/OOM events. This does not establish full50,focus/surface recovery,
physical-driver fidelity or every exceptional path. Detailed evidence and limits
are in the linked note and private `current-vc4-build-20261019/` and
`current-vc4-play-20261019/` directories under `.analysis/`.
The lifecycle authority is `.analysis/current-vc4-lifecycle-20261019/`, especially
`round/verification.json`, `gameover-persistent/verification.json` and the failed
`gameover` case/observer diagnosis. Do not repeat these unchanged passing flows
as source progress. Resume the22 authored candidates from concrete source questions.
The byte-verified local delivery is `build/delivery/dxball-v1.07-vc40-reconstructed.zip`
(467,599 bytes); it includes current exe,48 unchanged supplied assets and run
instructions. It remains private, together with its member manifest.

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

October19 [full early-SDK source check](../research/exact/EXACT_FIXED_POINT.md#full-sdk-carrier-and-source-corpus-check-october19)
verifies both received Game SDK/DirectX2 packages and retains551 source/text
members with original CRC and retained SHA checks. The1995 triangle was already
obtained earlier; the1996 counterpart differs only in copyright year range.
No new declaration model or compile follows the unchanged source. Four bounded
fingerprints expose no new connected PCX/polygon candidate. Do not repeat the
earlier SDK model; reuse `.analysis/early-sdk-raster-20261019/` for the now-retained
source corpora and explicit search limits. Verified cleanup replaces the two
whole package copies and18 closed files with source/helper archives, releasing
41267200 allocated bytes net before small receipts. All90 protected identities
and all claim totals stay fixed; no provider/runtime/relink/replay runs.

October19 ranking subtraction recovery adopts one expression after a complete
eight-body comparison, finite original/native counterexample and17 existing
ranking cases. All code identities and claim counts remain unchanged. The
separate UI unsigned-advance trial is rejected after its full comparison loses
draw-text's exact body; no alternate source model or216-case replay follows.
See [ranking coordinates](../research/exact/RANKING_COORDINATE_WRAP.md) for the
source/fixture boundaries and private authorities.
Both closed trials archive/member-verify80 files before exact-list removal,
releasing10285056 allocated bytes net before the small receipts. Current tested
products, useful caches, comparisons and unique evidence remain.

October19 PCX destination-coordinate recovery adopts four explicit modulo32
increments while preserving all18 complete resource code identities. One VC4
owner compile and one resource-only native build suffice; four bounded cases
and99 unchanged PCX cases pass. All270 current authored closure receipts verify.
Independent source/result reviews, full receipts and37 verified archived
inputs/products/helpers are retained; cleanup releases7,815,168 allocated bytes
net before small receipts. Source recovery remains unfinished at22 candidates;
no final game rebuild or game run follows this source checkpoint.

October19 authored boundary-contract recovery adopts the two source corrections
above despite worse byte comparison. Two owner compiles and one two-source
native incremental build are sufficient; no full replay, relink or game run.
Independent source/result reviews and focused current native receipts are in
the new private authority. The earlier iteration-scope inference is explicitly
corrected; historical semantic case scopes/counts remain unchanged.
The61 closed inputs/products/helpers are member-hash verified in a1,217,038-byte
archive before removal, releasing9,302,016 allocated bytes net before its small
receipts. Current matching/native products, useful caches and previous tested
EXE/ZIP remain. See `archive-manifest.json` and `cleanup.json` in the authority.

A subsequent [13-pattern Mac traceback check](../research/exact/AUTHOR_SOURCE_CONTEXT.md#nonzero-parameter-traceback-patterns-october19)
finds no new bounded nonempty name/declaration under the primary32-bit PEF
extension grammar: nine name overruns, one anchor-array overrun and three empty
names, all with parameter-count contradictions. Private
`.analysis/mac-traceback-parameter-layout-20261019/` retains raw slices, complete
compressed format sources and independent verification. This closes only those
previously excluded patterns, without changing source/counts or proving scan
exhaustiveness. No new compile/provider/runtime or disposable files follow.

October19 current-image round/game-over checks and the local delivery bundle
close the missing current-version lifecycle evidence described above. Source,
objects and all acceptance counts stay fixed; no compiler,relink,full replay or
campaign runs. Thirteen closed input/state/resource/helper files are archived
and member-hash verified before cleanup, releasing2,002,944 allocated bytes net.
Forty-nine verified runtime copies release another1,724,416 bytes. Complete
files/captures,current products/caches,the467,599-byte delivery and failed-run
evidence remain. The preceding rebuild/basic-flow checkpoint follows.

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
| Bank/resources | [Bank flow and closed controls](../research/exact/MAC_CANDIDATE_FLOW_CONNECTIONS.md#reused-bankshape-bodies-and-api-name-control), [conditional-output lifetime](../research/exact/AUTHORED_BOUNDARY_CONTRACTS.md) | Bank1475/68 preserves extent/yoffset, low32 byte/count arithmetic and four later-EOF fields; names, filename qualification, cursor/row/column and transfer scopes are closed |
| PCX | [Complete packet proof](../research/exact/EXACT_PCX_PACKET_LOOP.md), [storage diagnostics](../research/exact/CLOSED_STORAGE_DIAGNOSTICS.md) | Original862/current979; all227 instructions accounted. Current308-byte frame has305 typed bytes plus3 slot padding. Original unaddressed four bytes do not justify a132-byte header or fake local |
| Triangle/polygons | [Fixed-point](../research/exact/EXACT_FIXED_POINT.md), [polygon workspace](../research/exact/POLYGON_SCAN_WORKSPACE.md) | Four root FixedPoint constructions/EH states;28-byte edge has one unknown word at+12. Preserve paired accesses, three pools, both Shellsorts and signed negative-error carry |
| Rotation | [Pixel-address correspondence](../research/exact/ROTATION_PIXEL_ADDRESS.md) | All365 instructions/22 calls/26 branches accounted. Unknown80-byte frame difference is not permission to add padding; integer-offset-before-base order is restored |
| Line/ranking/presentation | [Line](../research/exact/LINE_LOCKED_CURSOR.md), [ranking](../research/exact/RANKING_OWNER_FAMILY.md), [presentation](../research/exact/PRESENTATION_MERGE_SCOPE.md) | Known comparison/register producers remain. Fixed line rank model restores directions but loses correct homes; ranking has original homes and one shorter compare producer |
| Clocks/palette/last brick | [Author context](../research/exact/AUTHOR_SOURCE_CONTEXT.md), [lightning crop chain](../research/exact/EXACT_LIGHTNING_CROP_CHAIN.md) | Clock cache/sampling order accounted; shared unsigned-long context already tested. Keep clock before RNG and existing callback-visible state |

Ranking's signed630−measure_text question is closed by the adopted explicit
DWORD subtraction. Its eight complete identities stay fixed; do not replay
the closed equality/owner controls. The connected unsigned text-advance trial
is also closed without adoption: the finite witness consumes no wrapped final
advance, while the proposal loses a complete exact. Retain that boundary and
avoid treating UBSan completion alone as an original-source declaration proof.

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
