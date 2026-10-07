# Terminal round and adjacent storage

Original, VC4 and MinGW now return to the menu with three lives and 500 points
after clearing 50 editor-created single-brick boards. Their terminal tiles
agree on the reviewed adjacent-storage pattern. REA's loader and CRT evidence
guided the shared storage reconstruction; an independent x86 copy driver also
checks nonzero state and both overlap directions. This closes the collected
storage fixture, not the original campaign or all possible terminal states.

## Reproduce the diagnostic

After importing the pinned original and building both Windows products:

```bash
# Passing original control; about three minutes on one allowed CPU.
scripts/repo-python scripts/capture-windows-probe.py --probe terminal --profile original

# Compare all three products; routing or storage mismatches return exit1.
scripts/repo-python scripts/capture-windows-probe.py --probe terminal
```

The harness creates all 50 boards through Control-F1, Backspace, tile selection,
painting and the editor's next-board key. S must persist the complete 20,000-byte
bank. Every board has one tile1 at column6/row18. Real paddle movement and clicks
release each attached ball; the harness observes collision, ten points per
clear and the next initialization. It never writes target memory or patches
an executable. The SDK observer reads sequential samples, not atomic frames.

All 50 transitions, terminal state, full saved bank after exit and zero-code
application shutdown are required. The report separates routing from the
terminal storage contract. It retains full tile/tail bytes and state samples
under ignored `build/reports/windows-terminal/`. Clock bytes are variable;
this fixture compares their location and the surrounding empty-list/single-ball
pattern, not equal clock values between independent processes. These 50 custom
boards do not establish completion of the original campaign or pixel fidelity.

The control is included in the complete private CI suite. REA's recording can
describe a failed child; the capture helper propagates the child's exit code.

REA process Evidence
`ev_051b5f3b2d676747e832207339c1ac960ff0bfd20a1da73ad2a2e9dd72fe989f`
records the completed three-profile control and child exit0. Each game exits0
after 50 actual clears, and both routing and storage checks pass.

| Product, this captured batch | Terminal mode / lives / score | Remaining count | Storage fixture |
| --- | --- | ---: | --- |
| Original | Menu0 / 3 / 500 | 4 | Pass |
| VC4 | Menu0 / 3 / 500 | 4 | Pass |
| MinGW i686 | Menu0 / 3 / 500 | 3 | Pass |

Each count agrees with the captured tile bytes using the reviewed exclusion of
0 and 2. The original clock and source pointer bytes can change these counts
between runs; the table is an observation, not a fixed numerical contract.

## Sampling a fast clear

The embedded-resource regression preserved a useful failed observation in
REA process Evidence
`ev_481a0a3766e82f0d1be8d93cc9c9ba7009438b9bce5da5cf21bb97bd16e88712`.
Original completed all 50 clears; the VC4 harness timed out waiting for clear 15.
Its preceding release sample already recorded index 16, score 160 and zero
remaining bricks. The following sample saw the next board's one brick; later
samples show its ball attached. The wait had missed an already completed clear.

The terminal harness now accepts an increased score with either the zero-brick
state or the advanced board index, then retains its separate stable reset/next
board checks. All initial board bytes, per-board score/life requirements, the
terminal routing/storage pattern, saved bank and shutdown assertions remain.
This changes the observer only. Maintained game C and shared release logic are
unchanged. The private failure archive excludes stale summaries from previous
attempts and retains the complete current samples and original input identities.

REA process Evidence
`ev_0eb0d9cda3740ea03750de89b9201a159e8cd198859a06481df42254f51ffe26`
records the revised three-product run exiting 0. Each product completes 50
clears, returns to menu with three lives and score 500, passes the scoped
storage pattern and exits 0. Captured remaining counts are 3 / 4 / 3 for
original / VC4 / MinGW; these depend on clock bytes and are not equality claims.

## Original read boundary

The reviewed static queries are also available as a public REA session request:

```bash
scripts/rea session config/rea-terminal-storage.json
```

Run it separately from the runtime capture; both serialize access to the
project's compiler/Ghidra/Wine session. Existing matching dossiers are reused
through the saved REA snapshot.

REA's fresh board-loader dossier at `0x40CEA0`, Evidence
`ev_5aa7369fc6fd8a1333d312332d7a4e40977ab9fa76272a6e0dd9192277fe66d2`,
shows an unchecked 400-byte copy from `0x43AAB8 + index * 400` to `0x43F8F8`,
calling the original CRT at `0x417CA0`. The initialization dossier at
`0x411930`, Evidence
`ev_92be01dc5bd27943d2a7e4db4df66ded90a7e2b76219f3c62058ef728d7ba02c`,
clears the auxiliary grid and invokes this loader. The retained advance-level
dossier, Evidence
`ev_10dedc1278e4815286d503ac118934dbfa5686b95b7ab47456756e5f5df0672a`,
increments index49 to50, requests menu termination and still initializes/counts
that index. An empty resulting buffer would also set lives to zero.

The bank ends at `0x43F8D8`. Index50 therefore reads 32 adjacent bytes followed
by the first 368 bytes of the old tile buffer; source and destination overlap.
The adjacent region is not a 51st board in the game file.

The follow-up CRT dossier, Evidence
`ev_7c4ccda4f0b66e6e162c21ff7248a6806209fa96607f7d9e75dd5b00befe53a9`,
reconciles 285 owned instruction bytes within a 334-byte span. Its initial
comparisons select the backwards-copy branch when `source < destination <
source + size`. This terminal call meets that condition and uses the aligned
100-DWORD `STD`/`REP MOVSD` path. That explains why the original tiles retain
the 32 adjacent bytes followed by the old grid prefix; they do not repeat the
first 32 bytes throughout the buffer. This is target-CRT instruction evidence,
not a claim that standard C memcpy defines overlapping copies.

| Original address | Reviewed meaning | Terminal fixture observation |
| --- | --- | --- |
| `0x43F8D8` | Palette clock, 32 bits | Variable clock bytes copied into tiles0..3 |
| `0x43F8DC` | Unclassified four-byte slot | Zero in the collected samples |
| `0x43F8E0` | Explosion request list, three x86 pointers / 12 bytes | Empty list |
| `0x43F8EC` | Unclassified four bytes after the known list fields | Zero in the collected samples |
| `0x43F8F0` | Ball count, 32 bits | One before the terminal cleanup |
| `0x43F8F4` | Unclassified four-byte slot | Zero in the collected samples |
| `0x43F8F8` | Existing 400-byte tile grid | Last brick has been cleared |

Focused REA exact-address xrefs find the reviewed clock and ball-count
consumers. The list's current/first/last fields are corroborated by its retained
append/remove consumers and the maintained owner at offsets0/4/8. The adjacent
four bytes are not a fourth established list field. Exact-reference/type
queries leave the intervening slots unclassified; this does not prove padding
or exclude indirect access. Ghidra reports the clock as `undefined4`; its meaning comes
from the retained frame/reset consumers, not debug/source metadata.

The clock/count xref Evidence IDs are
`ev_71b306aaf3d55dac396a0fe814a6bfc7744ba6a310157a4ade6c29de06dc8d40`
and `ev_9147b7fd67087013e96bacdb608c34ec80decb72db44b707743b6a965cc8fffb`.
The two empty exact-reference results are
`ev_5823a3528d5fcf65af2b56b13b08cdb56c8fca710dc6ec351bc62a5afde1357a`
and `ev_5640a24439302f2edfcf6b7eabd358bd181f46426c8a36f33a1b8669196b575a`.
The third slot at `0x43F8EC` likewise has no exact references in
`ev_60fd26538679ea0f4faa511e8fc67658de5ef2adbf31d65d8d03936916a5298e`
and no defined type in
`ev_73c5b60141171d900ae2dfcbd6ae023d48eb18734fad6325ca7929037fdf74fb`.

## Shared storage reconstruction

`src/board_storage.h` now represents the observed writable region as one C
object: the 20,000-byte bank, palette clock, three-pointer request list, ball
count and 400-byte tiles. The three unclassified four-byte intervals are
ordinary mutable byte arrays. They are neither identified original padding
nor fields with invented meanings; the terminal operation actually reads them.
This is a recovered storage view, not a claim about original source declarations.

All owners reference the same fields. The load/store routines use `memmove`
through the entire object's byte representation, preserving the reviewed
original CRT overlap behavior. There is no index50 branch, guard, skipped
initializer or extra board. Both x86 builds assert the reviewed offsets and
20,432-byte extent. Native pointer widths remain natural for the analysis ABI;
its byte layout is not claimed identical to x86.

The independent source-owned driver, `tests/test_windows_storage.py`, executes
actual MinGW x86 DLL load/store/initialize functions and compares every storage
byte, auxiliary byte and index against original x86 instructions. Its 459 cases
cover indices0..50 with zero, ramp and random complete images, including all
12 unknown bytes and arbitrary pointer representations (never dereferenced by
these copy operations). Nine cases exercise terminal overlap in both directions
and initialization. Fixtures/results are hashed then removed after success.
This integration evidence is separate from the existing 214 maintained functions
and 95,873 owner cases.

Source observers resolve the compiler's actual `offsetof`/`sizeof` metadata.
VC4 uses its attested EXE/map; the MinGW SDK reader reads the actual remote
metadata. Expected original addresses are not substituted for source addresses,
and observers remain read-only.

Cold replay of all 40 former exact units detects five changed emissions. The
current ledger retains 35 exact functions / 3,478 bytes, while the five reviewed
mappings remain explicit nonmatching candidates. See [compiler evidence](BUILD_MATCHING.md).
The source storage model has not been adjusted with inert fields or instruction
padding to recover those byte claims.

## Earlier layout controls

The earlier three-profile REA recording,
`ev_be5556929420bba0c59c7c58c00fb28eb603e9033cc0fd2418ea28926d00ff58`,
records child exit1 for the two source storage mismatches, despite each game's
normal exit0. Its observed remaining counts were original4 / VC4 8 / MinGW162.
That complete negative result remains archived separately from the passing run.

Before this reconstruction, the maintained bank and tiles were separate C
globals. VC4 placed the bank at `0x434FE0` and its end at `0x439E00`, followed by board
index, display mode, a surface pointer and CRT globals. The old terminal prefix
started with index50 and mode1. The old MinGW DLL instead placed the bank end
at `0x62C661C0`, where `dxball_saved_palette` began. Those products copied different
adjacent storage despite agreeing on return-to-menu routing.

The pinned-VC4 allocation experiment used actual maintained types without
padding or alignment attributes. Tentative C definitions remained linker common
symbols. Explicit zero initialization produced tail offsets 0/8/20/24 for
clock/list/count/tiles; the observed original requires 0/8/24/32. Grouping globals
alone therefore did not establish the needed relationships. A C++ comparison
changed allocation order/linkage and was not adopted. These are compiler-object
observations, not evidence of original source types.

Original-only exploratory REA process Evidence
`ev_6d75d72c70ba7c52dff3798c425940fac2b3705ca639251adfe4a3291c268ea3`
records 50 clears, menu0, lives3, score500 and application exit0. An earlier pilot
incorrectly expected ranking and timed out; that failed attempt remains archived
separately. Historical routing success alone did not establish storage fidelity.
