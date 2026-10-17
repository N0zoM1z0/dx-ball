# Independent board globals: tested reconstruction, not yet adopted

The original immediate explosion-list receivers and its26-byte generated
initializer support an independent global owner. The current reconstructed
aggregate instead produces LEA receivers and a32-byte embedded initializer.
This is a concrete ownership question, rather than a request for missing
original declarations. The canonical source and its382 exact claims remain
unchanged while the proposed replacement is checked.

## Storage model and evidence

The proposal defines seven real neighboring objects: the20,000-byte bank,
palette clock, four mutable unclassified bytes, explosion list, ball count,
four mutable unclassified bytes, and400-byte tiles. The list retains its real
constructor-cleared `unclassified_0c` word. The existing enclosing type serves
only as an `offsetof`/`sizeof` descriptor. No actual enclosing instance,
alias cell, invented padding, copied code or alternate function body is added.
Original spellings and declarations remain inferred, not uniquely recovered.

The retained [terminal-storage evidence](../TERMINAL_RUNTIME.md#original-read-boundary)
establishes the bank/read boundary, clock/count consumers and overlapping
index50 copy. Relevant original REA Evidence is:

- Loader: `ev_5aa7369fc6fd8a1333d312332d7a4e40977ab9fa76272a6e0dd9192277fe66d2`.
- Initializer: `ev_92be01dc5bd27943d2a7e4db4df66ded90a7e2b76219f3c62058ef728d7ba02c`.
- Terminal advance: `ev_10dedc1278e4815286d503ac118934dbfa5686b95b7ab47456756e5f5df0672a`.
- Backward CRT copy: `ev_7c4ccda4f0b66e6e162c21ff7248a6806209fa96607f7d9e75dd5b00befe53a9`.

The two generated initializer dossiers are retained in
[the earlier embedded-initializer note](LIST_EMBEDDED_INITIALIZATION.md).
No new original-provider query or game run was needed for this investigation.

Ordered linker sections express the actual adjacency contract. VC4 accepts
`data_seg` and an allocated section for the class object; GCC/MinGW use section
attributes. ELF additionally needs a sorted, nonloaded output section. Each
object keeps its natural alignment and the host's genuine pointer width.
Cross-object bank traversal is explicitly a supported compiler/linker ABI
contract; it is not a claim of ISO C/C++ array-bounds portability.

## Diagnostic placement and overlap

One successful diagnostic execution per ABI checks every actual object address,
initial zero state and both complete-region index50 transfer directions.
Observation copies each object within its own bounds. The observed offsets,
relative to the bank, are:

| Object / extent | VC4 and MinGW x86 | Native64 |
| --- | ---: | ---: |
| Clock | 20,000 | 20,000 |
| Clock tail | 20,004 | 20,004 |
| Explosion list | 20,008 | 20,008 |
| Ball count | 20,024 | 20,040 |
| Count tail | 20,028 | 20,044 |
| Tiles | 20,032 | 20,048 |
| Total extent | 20,432 | 20,448 |

Terminal reads preserve32 peer bytes plus368 old tile bytes on x86, and48 plus352
on Native64. The latter is a host-layout observation, not equality with x86.
These programs use diagnostic settings; real production placement, optimization
and startup remain separate gates.

Closed failures remain evidence. VC4 rejects `bss_seg`; `data_seg` alone fails
to place the uninitialized class with its peers, and the address guard stops
before traversal. Allocating the real class in its section succeeds. Its program
returns zero, although the first driver then rejects trailing Wine output during
JSON parsing. That successful program was not repeated. MinGW rejects the first
observer's whole-region array accesses under `-Werror`; bounded gather/scatter
fixes only observation, leaving the storage, constructor and board functions
unchanged. This is distinct from a game-function failure.

A separate ELF shared-library control finds two actual `R_X86_64_COPY`
relocations: a normal executable moves bank and tiles independently, breaking
their adjacency to the library's other objects. Protected storage definitions
and a PIC data consumer remove those copy relocations and pass the address and
overlap checks. The proposal therefore includes those linkage controls for ELF.
The Windows model does not receive ELF visibility attributes.

## Complete consumer comparisons

The first two-owner pilot yields complete zeros for editor load/store, queue
explosion and brick hit. The independent globals also expose four changed
left-neighbor expression groups in `spread-explosive-bricks`. Using the flat
index `x + y *20 -1` restores that prior exact under the existing `x >0` grid
guard. All other instructions remain accounted for. The inference is restricted
to the real0..19 grid domain; arbitrary signed-overflow equivalence is not claimed.
The16-unit pilot preserves all12 prior exact companions.

A broad five-declaration interface trial then finds13 prior regressions and six
mapping issues. A bounded complete-interface control adds declarations for the
two genuinely defined mutable tail arrays, exposing exactly the seven objects.
It preserves all nine MIDI/bitmap comparisons. Broadening this same interface
does not preserve every other exact; it is not a universal emission fix.
The observed context sensitivity does not establish a parser-ID explanation.
No name, declaration-count, ordering or compiler-flag sweep was performed.

The current seven-object authority compares all278 complete units sharing the
header:248 prior exacts and30 prior candidates. Each of29 stable owner products
is compiled once or reused after full input/flag/object equivalence. Nine control
comparisons are reused. Six initially unhandled mappings are then reconciled
from actual named external identities and compared from the same objects;
the272 completed comparisons are retained rather than repeated.

There are17 new private zero results, covering7,528 complete code bytes:

| Function | Complete bytes |
| --- | ---: |
| Editor load / store | 52 / 52 |
| Queue explosion / clear all entities | 99 / 106 |
| Blit / stretch / draw effect sprite | 362 / 306 / 361 |
| Rotated sprite height | 191 |
| Drop bricks / game frame | 426 / 1,688 |
| Hit board tile / editor key | 1,315 / 632 |
| Sort present regions | 296 |
| Update paddle position / refresh score | 203 / 74 |
| Palette transition | 1,339 |
| Generated explosion-list inner initializer | 26 |

These are16 authored functions and one generated function, **not accepted ledger
promotions**. Eight previously exact functions become nonexact: keyed draw,
keyed stretch, rotated offset, rotated width, hit-region search, sprite release,
round reset and bonus update. A selective report of only the new zeros would
misstate the result. All other240 prior exact companions in this closure remain
exact. Canonical source, ledgers, caches and delivery remain unchanged.

Literal contents, relocation addends and actual same-section local destinations
remain checked by the maintained full-span comparator. Named operand loads can
change order: relocation occurrence order alone is insufficient for the six
reconciled cases. The first pilot's proof also has six unequal unnormalized sums:
four encode `-1` as `0xFFFFFFFF`, and two editor rows replace a separate
`root +20032` instruction sequence with a direct tile-symbol push. Whole-body
agreement and the independently established tile address support those cases;
not all raw relocation sums are equal.

An independent read-only review checks all409 records in the six reconciled
functions, including34 reordered named external bindings. The three additional
zeros retain full original-span hashes and active local-target checks; the other
three functions remain nonexact. That review performs no compilation or replay.

One further uniform dependency-boundary control moves the analysis descriptor
and derived metadata out of the common game interface, leaving real global
declarations there. The source graph supports that separation: only `boards.c`
needs the post-split descriptor. Nevertheless, two representative owner compiles
produce nine regressions across27 prior exacts. This branch is closed without
another broad build; owners must not receive selective header variants.

## Continuation and acceptance

The seven-object proposal is concrete enough for production placement, startup
and storage checks. Before adopting it, verify the actual VC4 restored-CRT,
MinGW Release DLL and Native Debug library layouts; exactly-once list construction
and the real `+0xC` clear; existing full-storage/terminal controls and affected
flows; all current compiler inputs; exports, source-generator anchors and delivery.
The diagnostic executables do not discharge those gates.

Resolve the eight regressions through supported source evidence, or explicitly
justify and record any demotions when adopting a better-supported ownership
model. Comparing accepted companions is a repository requirement; a monotonic
exact count is an acceptance policy, not proof of original declaration fidelity.
Never reuse old accepted objects as receipts for changed source inputs. Do not
repeat the closed member-call, declaration-interface or layout-split controls.

Private root: `.analysis/independent-board-storage-20261017/`.
The main authorities are `allocated-class/summary.json`,
`shared-linkage/summary.json`, `complete-interface/summary.json`,
`complete-wide/reconciled/{comparison,selected-units,proofs,summary}.json` and
`candidate/candidate.json`. The current frozen29-owner tree and products are
retained for reuse. Closed diagnostic products and superseded input/product
trees are archived with member hashes verified before deletion; the two cleanup
receipts distinguish raw allocation removed from net storage released.
Together they remove239 superseded files and release4,927,488 allocated bytes
net of the verified compressed carriers. Current reusable products remain.
