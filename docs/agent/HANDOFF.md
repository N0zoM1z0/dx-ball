# DX-Ball reconstruction handoff

Prepared from `583453677bdfb57807a42c9f7a305a5ce6a3d17d` on October 13, 2026.
The user requested this handoff and stopped the current reconstruction run.
The objective remains unfinished. Resume DX-Ball when work is handed over.

This is the authoritative handoff. The previous 843-line history is preserved
[in Git at 5834536](https://github.com/N0zoM1z0/dx-ball/blob/5834536/docs/agent/HANDOFF.md).
Use its linked research notes for older evidence rather than loading it all.
The old `/tmp/dxball_reconstruction_handoff.md` is stale.

## Goal and user requirements

The user's first priority is: **“先把所有的函数尽可能 exact 还原完”**.
Recover the original English DX-Ball v1.07 functions as exactly as possible.
The broader project remains a nearly complete source reconstruction that
rebuilds and plays, but function recovery comes first.

- Work on DX-Ball. Leave TH04 alone.
- Work directly from the local original binary and retained REA evidence.
  Do not search online for existing source or another reconstruction. Original
  source and debugging files are unavailable; keep exploring and trying
  evidence-supported source models.
- Prioritize complete-function comparisons. Defer long game campaigns until
  function recovery is ready; passing gameplay samples is not an exact claim.
- Keep the full goal across turns and handoffs. A small checkpoint, compatibility
  result or passing fixture does not finish it. Mark completion only after
  current source, complete comparisons and required evidence prove the goal.
- Make concrete progress: select a missing operation, ABI, expression or lifetime
  supported by instructions; implement a bounded trial; compile and compare it;
  record the result. Avoid long speculative planning and repeated closed trials.
- Keep repository code and documentation English. Write natural, detailed prose
  without repetition or defensive claims. Preserve the reader-facing README
  tutorial and its English `/goal` example, centered title PNG and 900px SVG.

For a fresh Codex thread, the intended prompt is:

```text
/goal Recover all original English DX-Ball v1.07 functions as exactly as possible
from the local binary. Read AGENTS.md and docs/agent/HANDOFF.md first. Prioritize
complete-function restoration over game campaigns. Use retained REA evidence,
keep resource use bounded, preserve honest exact claims, and commit and push
verified checkpoints. Do not switch to TH04 or search online for a reconstruction.
```

If the thread still has a registered goal, resume it. Otherwise start a new
goal with the prompt above, preserving the same objective.

## Current authoritative state

| Item | Current value |
| --- | ---: |
| Provisional function candidates | 528 |
| Source-present functions | 302 |
| Exact functions | 249 |
| Complete exact code bytes | 63,697 |
| Attached exact metadata bytes | 136 |
| Historical scoped semantic rows | 249 |
| Confirmed authored nonexact candidates | 34 |

These are separate ledgers; 249 exact functions does not prove project completion.
All 34 authored candidates have complete comparisons. Their sizes and differences are in
[REMAINING_EXACT_FUNCTIONS.md](../research/exact/REMAINING_EXACT_FUNCTIONS.md).
The authored denominator and 96 unclassified origins remain open.

The October 13 continuation recovers two 53-byte CRT conversion wrappers and
the 3-byte default math callback in `src/runtime_float.c`. All 109 bytes and
four actual relocations match. This standalone module compiles on native,
i686 and VC4; parser recovery and backend/game integration remain
open. The game still uses its existing runtime. See
[the source note](../research/exact/RUNTIME_FLOAT_CONVERSIONS.md) and
`.analysis/runtime-conversion-functions-20261013/`. No runtime tests run.
The 34 authored candidates and previous game products are unchanged.

The follow-up recovers both complete 24-byte binary format entries and their
48 initialized data bytes. The full converter body is now maintained at the
original 459 bytes / 157 instructions, with 94 differences. Its packed result
reuses the exponent scalar; its denormal shift is stored before the copy.
It is the additional runtime candidate, bringing configured candidates to 35.
See [binary conversion](../research/exact/RUNTIME_BINARY_CONVERSION.md) and
`.analysis/runtime-binary-conversion-20261013/`. Five owner functions retain
157 exact code bytes; 239 other exact producers are unchanged.

The mantissa continuation adds all seven helpers and their addition dependency.
Tail testing (100 bytes), carry propagation (99) and clearing (15) are complete exacts.
All eight affected exacts preserve 371 bytes; 239 other producers are unchanged.
There are now 40 candidates: 34 authored and six runtime. The converter has
459 bytes / 95 differences in this source context. Rounding has 163/172 bytes,
copying has five differences, zero testing six, shifting 174/173 bytes and
addition seven differences. These remain nonexact. Decimal parsing is the remaining source dependency
of this conversion chain. See
[mantissa helpers](../research/exact/RUNTIME_MANTISSA_HELPERS.md) and
`.analysis/runtime-mantissa-helpers-20261013/`.

The next continuation makes indexed zero testing (29 bytes) and little-endian
96-bit addition (102) exact. Both one-bit shifts now have maintained source.
Ten affected exacts preserve 502 bytes; 239 other producers are unchanged.
Current candidates total 41: 34 authored and seven runtime. The converter has
94 differences, the big-endian shift has 172/173 bytes with 134 differences,
scalar addition has five differences, and the new left/right shifts have
50/62 and 48/54 bytes with 47 and 35 differences. Rounding and copy are unchanged.
See [iteration and arithmetic](../research/exact/RUNTIME_MANTISSA_LIFETIMES.md)
and `.analysis/runtime-mantissa-lifetimes-20261013/`. Runtime tests remain deferred.

Repository: `/home/pentester/coding/codex_ida/dx-ball-reconstruction/dx-ball`.
Branch and publish target: `origin/main`.
Latest published source checkpoint before this continuation: `0d914f6`
(mantissa helper source and three exact functions).
Latest pre-handoff checkpoint: `5834536` (closed device/clock controls).
Both were pushed; remote HEAD and a clean worktree were independently verified.

Original: English `DXBALL.EXE` v1.07, 158,208 bytes, SHA-256:
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
The verified game archive contains 51 files and no source, PDB, objects or map.
Native, MinGW i686 and VC4 products build at the current source checkpoint.
VC4 compiler is 10.00.5270; linker is 3.00.5270.

Current comparison and producer authorities:

- `config/match-units.toml`: exact recipes, complete extents and bindings.
- `build/reports/exact-replay.json`: all 249 exact closures and current producers.
- `.analysis/exact-candidate-audit-20261012/comparison.json`: current 41 candidates;
  its directory name is historical, its contents are current.
- `config/functions.csv`, `implemented.csv`, `matches.csv`, `semantic-acceptance.csv`
  and `source-owners.toml`: source, status, ownership and scoped evidence.
- `.analysis/runtime-mantissa-lifetimes-20261013/verification.json`: current
  standalone source/producer/ledger seal.
- `.analysis/runtime-mantissa-helpers-20261013/verification.json`: preceding
  helper checkpoint; its sources and products are frozen in the new `before/`.
- `.analysis/runtime-binary-conversion-20261013/verification.json`: preceding
  binary format/converter scope; sources are retained in the new `before/`.
- `.analysis/runtime-conversion-functions-20261013/verification.json`: preceding
  three-function scope; frozen sources are retained in the new phase's `before/`.
- `.analysis/rebound-contact-integration-20261013/verification.json` and
  `independent-review.json`: preceding unchanged game input/product seal.

## Latest recovery and closed boundaries

[Paddle contact precision](../research/exact/EXACT_REBOUND_STORED_CONTACT.md)
is now complete: 681 bytes, 181 instructions, a 28-byte frame and 50 bindings.
`src/balls.cpp` reuses one float contact value. The first comparison consumes
its immediate x87 quotient; six later cv-qualified reads consume the stored
float. Three companions retain 965 exact bytes.

GNU compiles this file with source-specific C++17, `-O2`, `-mfpmath=387`,
`-fexcess-precision=fast` and `-Wno-sequence-point`; keep these settings and its
C API linkage. The VC4
recipe is unchanged. A private native producer passes 831 existing ball cases
and four audio callback controls. Its runtime sections, relocation/symbol tables
and 36 other linked objects equal the canonical build, supporting explicit
reuse of that evidence. Two canonical witnesses also pass: 7/100 selects 150°,
12/60 selects 120°. Do not report the 831 cases as rerun on the canonical library.

[Sprite iteration lifetime](../research/exact/BANK_SPRITE_ITERATION_SCOPE.md)
reduces the 1,475-byte bank loader from 72 to 70 differences. Its two removed
positions do not prove matching scalar homes. Fifteen resource exacts preserve
3,572 bytes. [Device calls](../research/exact/DEVICE_SURFACE_PALETTE_CALLS.md)
reduce palette transition to 12 differences while preserving five exacts.

Read [closed diagnostics](../research/exact/CLOSED_STORAGE_DIAGNOSTICS.md)
before choosing another model. In particular:

- Device-local CreatePalette projection: one 14-input compile, six comparisons;
  five exacts retain 808 bytes, transition worsens 12→18. Rejected.
- Current clock-owner SDK sample: one 27-input compile, 16 comparisons; all code
  hashes unchanged, eleven exacts retain 2,708 bytes. Named Kernel32 IAT bindings
  are verified. No native union-lifetime acceptance or exact gain. Kept private.
- Paddle consumed records restore all source homes but add two bytes. Overlay
  lifetime, height projection records, palette declaration order, equivalent
  operand spellings, shared SDK contexts and list-member families have receipts.
  Reopen a model only with new evidence, not a new name or blind permutation.
- Preserve `DxBallBoardStorage` and its terminal board-copy effects. Interior
  linker aliases, cast/offset spelling trials and guessed padding are not a fix.
- Original score/intro buffer gaps do not establish larger arrays. Do not enlarge
  the 11-byte score buffer or 32/11 intro arrays to fill unexplained frame space.

Runtime and compiler-generated entries also retain separate origin records.
[CRT storage closure](../research/CRT_INITIALIZED_STORAGE_CLOSURE.md) and
[FDIV initialization](../research/CRT_FDIV_INITIALIZATION_FRONTIER.md) cover
89 complete code sections, 20 data sections and seven initialized objects.
Unresolved BSS and FP initialization remain open. Preserve unique placement,
namespace and verifier gates when investigating that frontier.

Latest private controls: `.analysis/device-ddraw-local-interface-20261013/` and
`.analysis/kernel-sample-current-owner-20261013/`. Complete source, SDK, binding
and independent reviews are retained. Their eight compressed carriers release
1,077,248 allocated bytes; canonical products remain unchanged.

## Resource and tool use

- Run Python through `scripts/repo-python`. Use project entry points rather than
  bypassing their resource limits.
- Use one already-allowed CPU via `resource_limits.limit_cpu()`. Build with
  CMake `--parallel 1`. Ghidra heap is **512 MiB**, set through the supported
  `GHIDRA_HEADLESS_MAXMEM=512M` path in `scripts/resource_limits.py`.
- Keep one writable compiler/provider/Wine session at a time using
  `legacy_toolchain.session_lock()`. It is a blocking, non-reentrant lock;
  do not wrap a helper that already acquires it in another lock.
- Automated game/audio probes use `PULSE_SINK=dxball_reconstruction_silent`.
  For native interposition, prepare the interposer before taking the session lock.
- Keep local REA updated. The verified project pin is **REA 6.4.0 / Ghidra 12.1.4**,
  and the installed REA skill is version 37. Use `scripts/rea`, check the relevant
  pin/version when resuming, and avoid repeated setup or unrelated tool upgrades.
- Reuse retained dossiers first. Save full responses and Evidence IDs under
  `.analysis/rea/`, but read small relevant facets into context. Prefer summaries,
  retained references and bounded output; do not dump giant manifests/dossiers.
- Compile once per stable source family. Reuse a completed producer only after
  checking actual inputs, flags and product hashes. Fix comparison consumers
  without rerunning their compiler or REA producer.
- A truncated preview or observation timeout is not producer failure. Retain and
  poll the live handle, or inspect terminal receipts, before deciding to restart.
- Run the minimum useful affected existing check. Do not replay the full historical
  queue or repeat unchanged successful cases. Label reused evidence explicitly.

REA feedback is optional and secondary to reconstruction. Append performance
and usability observations to the **single existing** file
`/tmp/dxball_rea_feedback_20261010.md` (latest entry 77). Record oversized output,
token/context cost, latency and usability issues when actually observed. Do not
create another feedback document, and do not spend the main task on feedback.

## Source fidelity, evidence and cleanup

Use natural typed source shared by portable and legacy builds. Preserve widths,
ABI, data ownership, actual stores and call order. Do not force matches through
copied machine code, assembly, padding, fake locals, alternate source bodies or
blind name/declaration/capacity/layout searches.

An exact claim covers the complete function, every actual relocation, full
literal contents and attached metadata. Verify all accepted units sharing the
changed inputs. Keep the real producer path and hashes; a byte-equivalent reuse
is not a fresh canonical compilation. Preserve historical scopes and case counts
when refreshing their input inventories.

Keep `original/`, `.tools/`, `build/`, `.analysis/` and `ghidra-project/` private.
Publish source, useful research notes and ledgers. Clean trial products regularly:
retain unique evidence and accepted/current products, verify gzip decompression
SHA-256 before removing raw carriers, and record allocated savings net of receipt
cost. Many historical files now have `.gz` fallbacks; read or safely extract the
retained carrier instead of rerunning the producer. Keep archive/current inode
independence, and avoid recursively copying large evidence trees or tool caches.
`scripts/repo-python scripts/clean-local.py` previews its supported cleanup.

## Commit and push requirements

Every verified checkpoint must be committed **and pushed** to `origin/main`.
The subject is English and begins exactly:

```text
gpt-6.1-sol: <concrete source recovery or evidence result>
```

The body describes the problem, final change, actual REA/source evidence,
validation, any exact gains/losses and cleanup. Distinguish executed checks from
reused evidence. Keep originals, tools, assets and raw analysis out of commits.
After pushing, independently compare `git rev-parse HEAD` with
`git ls-remote origin refs/heads/main`, and check `git status --short` is clean.

## Resume procedure

Read [AGENTS.md](../../AGENTS.md), this handoff,
[WORKFLOW.md](WORKFLOW.md), the remaining-functions table and the selected owner
note. Inspect the current worktree and authorities before using historical counts.
When beginning binary/compiler work, verify only the relevant inputs:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-toolchain.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Then select a new instruction-supported source question from the remaining
candidates or a missing dependency in the recovered runtime chain,
freeze the affected inputs/products, make the bounded trial and compare all
complete affected units. Record negative results and move on; publish verified
improvements promptly. Keep the original goal active when resumed, and do not
mark it complete from a smaller checkpoint.
