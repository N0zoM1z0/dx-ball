# Exact moving-ball and projectile update scopes

The reconstructed `dxball_update_balls` at **0x410770** now matches the
complete original **3223 bytes and 276 relocations**. The reconstructed
`dxball_update_projectiles` at **0x413170** matches all **328 bytes and
23 relocations**. This adds 3551 complete code bytes and two exact entries:
192 exact functions, 40110 code bytes and 136 separately attested metadata bytes.
Source presence remains 283 and historical semantic acceptances remain 247.

## Source restoration

In `src/core.c`, keep the moving-ball `chance` and `x` locals at function
scope. Declare `y` and `sign` in the surviving, in-bounds ball branch.
Declare `i` and `j` in their respective reduced/full particle branches.
The original stack operands identify six distinct four-byte homes in that
order: offsets 4, 8, 12, 16, 20, 24 below EBP. Six existing compiler conversion
temporaries occupy offsets 28 through 48; the complete frame is 48 bytes.
No padding, invented variables, identifier trials, type changes, altered
operations or RNG ordering were introduced.

For projectiles, keep `column` at function scope and declare `row` inside
the current-projectile iteration. The original complete listing stores
column at EBP-4 and row at EBP-8, before checking retirement and tile hits.
The eight-byte frame and every instruction now match. These scopes are a
source model supported by complete compiler emission; original source
identifiers and declaration spelling are still unknown.

Two bounded canonical VC4 `/MT` owner compiles were used. The first makes
the moving-ball body exact; the second restores the projectile iteration
scope while preserving that result. The intermediate source/object and
both comparisons are retained. The initial source has 23 moving-ball and
8 projectile byte differences under the same relocation proof recipe.
All six previously exact core companions remain exact across 771 bytes:
retire ball 45, fire projectiles 321, spawn fire effect 185, process fire
effects 124, ignite balls 64 and retire projectile 32.

## Complete artifact evidence

The retained REA dossiers identify a single contiguous body for each
function, ending at 0x411406 and 0x4132B7 respectively. Moving balls has 864
instructions, 59 branch instructions and 64 calls. Projectiles has 89
instructions, 10 branches and 6 calls. Every current COFF instruction address
and length covers the independently retained original listing, and the
complete relocated bytes match the pinned original PE. No gaps, table
bytes, tails or mismatches are masked.

Original REA Evidence:

- `ev_c7fd5e1c178073afb10924d1dbfa6df93f8ba8566533fd41f8dcb8f48b3a92a1`,
  `.analysis/rea/runs/2026-10-07T07-42-20.694Z-interactive-2387716/05-analyze_function.json`.
- `ev_412b7a2d61e8a498417dca7a456838ed290b17317e4af4585d8b936b69b07495`,
  `.analysis/rea/runs/2026-10-07T08-21-37.400Z-interactive-2545594/19-analyze_function.json`.

Both target identities and terminal session records verify. No new provider
session, analysis request or gameplay capture was needed. The private proof
folder is `.analysis/moving-ball-scope/`, including `body-proof.json`,
`comparison.json`, `before-scope-control.json`, the matching compilation
receipt and immutable intermediate `balls-only/`.

## Validation and rebuilt products

A private driver selects eight unchanged case-loop ASTs from
`tests/test_core_differential.py`, retaining the maintained setup and complete
Harness comparisons. It passes **2373 moving-ball updates, 126 projectile
updates and 6 projectile spawn setups**, 2505 calls total. Cases cover strict
death/bounds, multiple wall contacts, sticky offsets, speed caps, brick drop,
reduced/full particles, attachment/release, 1400 board/RNG cases, queue removal
and successor skipping, sprite banks, x87 sample boundaries and projectile
tile/score interactions. State, complete queues, allocation ownership,
ordered events and RNG consumption are compared with original execution.
The selected AST, maintained test, driver and current library hashes are saved
in `core-oracle.json`. An initial private aggregate expectation counted the
sticky grid as 960 instead of 480; all comparisons passed before that guard
failed. The corrected driver produced the final receipt. Tests are unchanged.

Native and MinGW affected products rebuild successfully. The VC4 game links
the final matching core object with 35 identity-verified unchanged objects;
no additional legacy source compiles. All 192 exact input/object closures,
247 unchanged historical semantic scopes and 36 production object closures
verify. Historical semantic input hashes refresh without claiming reruns of
unrelated suites. Current product hashes are in
`.analysis/moving-ball-scope/product-verification.json`; the independent seal
is `.analysis/checkpoints/moving-ball-scope-283-192/sha256.json`.

These complete function matches strengthen reconstruction of physics and
projectile control. They do not establish original declaration spelling,
synchronized rendering/audio or the full 50-board campaign.
