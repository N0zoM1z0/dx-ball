# Reconstruction handoff

Continue toward nearly complete original English DX-Ball v1.07 source that
rebuilds and plays. Commit locally with `gpt-6.1-sol: ` subjects; pushes remain
deferred. This repository handoff is authoritative. The older
`/tmp/dxball_reconstruction_handoff.md` is stale and is not updated: the user
requires all ongoing REA feedback in one existing `/tmp` document only.

## Current state

- 283 source-present entries and 247 scoped semantic acceptances.
- 186 exact functions / 33,001 complete code bytes / 136 accepted metadata bytes.
- Origins: 270 authored, 76 runtime, 42 compiler-generated, 140 unknown.
- Score initialization/read/name editing and the connected score-table source
  recovery are complete checkpoints; do not restart score initialization.
- Full authored denominator, original declaration spelling, synchronized render
  or audio fidelity and nearly complete original-source recovery remain unproved.

The latest connected MDS cleanup batch changes only `src/midi.cpp`: five loader
errors and three parser block-header/capacity/conversion errors use the observed
common-cleanup gotos. The compiler generates all26 common-cleanup jumps /130
original bytes, including65 bytes outside Ghidra's imported ownership. See
[complete MDS cleanup](../research/exact/EXACT_MDS_OPEN_CLEANUP.md) and private
`.analysis/source-dataflow-frontier/`.

- Open remains530/522 with443 unmasked differences. Its135 original/140 current
  instructions correspond through9 frame references and3 input-normalization
  groups; all30 direct branch targets match. Original parameter declaration and
  EAX residue through arbitrary external callees are not proved. A whole-slot
  load whose high bits are discarded does not prove a wide source parameter.
- Parse is868/868 with40 unmasked differences, down from838/868 with341.
  All231 instructions/operands/CFG targets correspond through12 frame references;
  all16 common-cleanup jumps /80 bytes, including40 unowned bytes, are retained.
  No operand-reversed comparison or differing register residue remains.
- Release149 and pause133 remain exact. Converter source is unchanged:343/343,
  now41 differences rather than the historical38 after canonical frame reassignment.
- Final selected checks:253 parser +284 loader +80 wrapper cases /617 direct;
  134 separate connected checks, including all six original songs. Original
  matrices, case bodies, ordered effects and complete payload/context comparisons
  stay intact. Other semantic suites are historical with refreshed inputs.
- Ten actual matching compilations:2 diagnostic MIDI,6 diagnostic header consumers,
  one valid open-only stage and one final connected MIDI stage. Both parameter
  hypotheses and all six diagnostic owners are reverted; restored owner objects
  differ from diagnostics only in COFF timestamps. Headers/tests stay unchanged.
- Native/MinGW rebuild only MIDI in each valid stage. Final VC4 links one matching
  owner and35 verified unchanged objects, without additional source compilation.
- 235 historical semantic input inventories refresh; counts/scopes stay fixed.

Current product identities are in
`.analysis/source-dataflow-frontier/product-verification.json`; actual final
source/object verification is in `final-review.json`. Do not reuse historical
product hashes from an earlier checkpoint or call a loader-only test a final
parser result. The immutable seal is
`.analysis/checkpoints/mds-cleanup-flow-283-186/sha256.json`.

## Recent anchors worth retaining

| Checkpoint | Evidence and remaining limit |
| --- | --- |
| `1f40ee1` intro pixel pointer | Natural consumed pointer/timer exit;682/711 with604 differences;178 retained instructions/14 branch targets/11 frame references;36 point +58 connected checks. Unpassed100-byte region has only two stores; type unknown. Native descriptor fixture supports actual108/120 callers; original Oracle stays108/14. |
| `9beaac4` raster metadata | Correct current generated definitions/interior offsets; complete160 metadata bytes exact, triangle code1710/1710 with107 differences.482 instructions/37 frame references/four signed comparisons explained; EAX/flag residue checked through actual callees. This160-byte candidate metadata is not added to accepted136. |
| `9d5bcd7` effects exhaustion | Both signed zero predicates restored. Brick step complete313 bytes exact; explosion797 remains47 differences.540 existing step cases +128 queue calls. Four relational spelling changes compiled identically and were reverted; do not repeat them. |
| `905dacc` window/runtime origins |227 reachable window instructions correspond; embedded20-byte table and five dispatch destinations bound. Full code1171/1166 remains1006 differences. Eight whole-section CRT origins accepted; runtime total76, unknown140. |
| `63bf276` game frame | Natural void pause return, signed byte and zero brick predicate;1691/1688 with1156 differences.379 instructions/162 relocations/40 branch targets explained. Historical708 phase-one calls and final24 pause checks retain separate products. |
| `5674dca` projectile retirement | Complete32-byte void helper exact; callers discard/overwrite EAX. Relevant unused-header closures were proved rather than guessed. |

The prior long handoff is preserved in Git and the new batch's `before/`
archive. Owner notes retain the detailed historical evidence; the table above
is not a replacement for their full claim scopes.

## Next useful work

The pre-batch read-only frontier is
`.analysis/source-dataflow-frontier/discovery.json`, with compact `summary.json`.
All82 candidate code streams bind their actual declared relocations without a
compiler/provider. It abstracts frame offsets and branch destinations only for
discovery: it is not a semantic proof, metadata acceptance or switch-table
boundary audit. MIDI rows describe the pre-batch objects; final comparisons are
in `comparison.json`. Do not rescan or compile merely because a summary is old.

Investigate genuine consumers/control flow in `capture-sprite`, `restore-regions`
or the larger ball/render owners. Their larger abstract change groups need
actual instruction/caller/typed-storage inspection; register scheduling or an
inline table can explain a group without a source gap. Prefer a complete coherent
flow over a tiny passing helper. Do not perform source-name, declaration-order,
layout, padding or equivalent-relational-spelling trials to force stack homes.
A compiler API/declaration hypothesis needs evidence that distinguishes it.

Current original/VC4 Wine ball/pause/editor/save/reload/exit flows pass on the
unchanged `4c24034` source products:87 observations each and all49 originals
unchanged. Opening/editor/editor-reload complete640x480 RGB/PNG captures match.
Menu's3445 differences are entirely palette indices48..63; all14289 relevant
asset pixels match original/current right rotations11/9. Pause's7472 differences
are entirely original tile8/sprite9 indices224..231, which continue animating
while paused; live palette/phase equality remains unobserved. Full receipts,
unaltered images and index localization are in
`.analysis/windows-play-current-render/`; immutable seal
`.analysis/checkpoints/windows-play-current-render-283-186/sha256.json`.
See [current runtime scope](../research/WINDOWS_ADAPTER.md). Only the observer
compiled once; no game/provider runs. Source, counts and products stay unchanged.
Hardware display/audio, synchronized timing and whole-campaign fidelity remain
unproved. Reuse existing probes for a concrete gap; do not repeat this flow to
recover lost output or run a broad historical matrix.

## Work and verification rules

Read `AGENTS.md`, [workflow](WORKFLOW.md) and the affected owner note before edits.
Use `scripts/repo-python`; originals, toolchains, products and raw evidence stay
private. Pin REA6.3.0/Ghidra12.1.4 through `scripts/rea`. Official npm latest was
verified as6.3.0 on2026-10-11; no repeated doctor/setup is needed. Reuse closed
Evidence/ranges with their target/file hashes; request only a concrete missing
range or consumer. Retain full carriers locally and return focused projections.

Use one writable compiler/provider session, one allowed CPU, Ghidra512MiB and
CMake `--parallel 1`. Use `legacy_toolchain.session_lock()` for writable legacy
work. Route automated audio with `PULSE_SINK=dxball_reconstruction_silent`.
No proactive subagents; work sequentially unless explicitly authorized.

At a new binary/compiler phase verify the relevant inputs:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-toolchain.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

New exact claims require the complete span, compiler inputs/flags, every actual
relocation and attached initialized data/metadata. Compare affected accepted
units together after a stable owner compile; preserve unchanged current object/
input receipts instead of cold-compiling all186. Refresh changed inventories
without claiming historical suites reran. Reuse actual native fixtures and
existing affected case blocks; keep original constructors, matrices and complete
state/effect assertions. Diagnose a failed receipt/count separately from a
provider or implementation failure.

COFF uses `storage`, `DIR32` and `REL32`. Generated symbol ordinals are not stable
identities: bind owning sections, offsets, literal contents and independent
original targets. Exact objects are under `build/exact/`. Semantic rows are
unique by address, not unit label. A truncated tool response is unobserved output;
recover a narrow saved result instead of restarting a compiler/provider. Poll
only handles confirmed live; no task handle is inherited from this handoff.

Preserve unique evidence and current products before cleanup. Prefer scoped,
hash-verified hardlinks against relevant immutable seals; never link mutable
current products to old seals. Distinguish logical file-size estimates, replaced
single-link inode allocation and measured device free-space changes. Avoid a
global archive sweep/keeper reassignment after every small batch. The new seal
records explicit prior dependency links and is checked after scoped cleanup.

## REA feedback

Append English performance, output/token/context, usability and optimization
feedback only to existing `/tmp/dxball_rea_feedback_20261010.md`; last completed
entry is44; use45 for the next new entry. Never create another `/tmp` feedback/handoff document or send the
feedback externally. Record actual measurements with their limits. Retained
archive bytes are not MCP/model tokens or current-version latency. This runtime batch makes no fresh REA provider request; its Wine observations
and palette-phase limits are separate from historical static Evidence.
