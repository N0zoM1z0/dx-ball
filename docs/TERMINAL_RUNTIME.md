# Terminal round and adjacent storage

The original returns to the menu with three lives and 500 points after clearing
50 editor-created single-brick boards. VC4 and MinGW controls complete the
same inputs and exit normally, but their terminal tile buffers contain different
adjacent globals. This is an unresolved reconstruction gap, even when the
visible return-to-menu path agrees.

## Reproduce the diagnostic

After importing the pinned original and building both Windows products:

```bash
# Passing original control; about three minutes on one allowed CPU.
scripts/repo-python scripts/capture-windows-probe.py --probe terminal --profile original

# Compare all three products; storage mismatches deliberately return exit1.
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

The diagnostic remains outside the passing private CI suite while the source
storage contract is unresolved. REA's successful recording operation can
describe a failed child; the capture helper propagates the child's exit code.

REA process Evidence
`ev_be5556929420bba0c59c7c58c00fb28eb603e9033cc0fd2418ea28926d00ff58`
records the completed public three-profile diagnostic and child exit1. Each
game exits0 after 50 actual clears; the harness fails for the two source storage
mismatches. This is distinct from a timeout or an incomplete shutdown.

| Product, this captured batch | Terminal mode / lives / score | Remaining count | Storage fixture |
| --- | --- | ---: | --- |
| Original | Menu0 / 3 / 500 | 4 | Pass |
| VC4 | Menu0 / 3 / 500 | 8 | Mismatch |
| MinGW i686 | Menu0 / 3 / 500 | 162 | Mismatch |

Each count agrees with the captured tile bytes using the reviewed exclusion of
0 and 2. The original clock and source pointer bytes can change these counts
between runs; the table is an observation, not a fixed numerical contract.

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

## Reconstruction boundary

The maintained bank and tiles are separate C globals. The VC4 linker map puts
the bank at `0x434FE0` and its end at `0x439E00`; that address holds the board
index, followed by display mode, a surface pointer and CRT globals. Its observed
terminal tile prefix starts with index50 and mode1. Both the target addresses
and source symbols are resolved independently; no expected target address is
used to read a source process.

The actual MinGW DLL symbols put its bank at `0x62C613A0` and its end at
`0x62C661C0`, where `dxball_saved_palette` begins. The maintained resource
owner fills that 256-entry palette from PCX data. This product therefore copies
palette storage into the terminal tiles rather than the original clock/list/
count region. These are linked-product observations; portable C does not
guarantee either layout or define this out-of-array read.

A small pinned-VC4 allocation experiment uses the actual maintained bank,
clock, request-list, count and tile types with no padding or alignment
attributes. Tentative C definitions remain linker common symbols. Explicit
zero initialization produces section-relative offsets of 0/8/20/24 for the
clock/list/count/tiles after the bank; the original has 0/8/24/32. Merely grouping
these declarations and adding zero initializers therefore leaves the relevant
storage difference. A C++ comparison also changes allocation order/linkage;
it was not adopted as reconstruction source. These are compiler-object
observations, not evidence of the original declarations or final link layout.

The original-only exploratory run is REA process Evidence
`ev_6d75d72c70ba7c52dff3798c425940fac2b3705ca639251adfe4a3291c268ea3`.
It records 50 clears, menu0, lives3, score500 and application exit0. An earlier
pilot incorrectly expected the ranking screen and timed out; that failed
attempt remains archived separately. Exploratory routing success does not
promote the source's different terminal storage to acceptance.

No index guard, skipped initialization, invented extra board, target-memory
override or source layout padding has been added to hide this gap. Recovery
still needs a coherent source storage model preserving the now-reviewed
overlapping-copy behavior. Existing board exact units remain explicitly scoped to indices0..49;
the round oracle's terminal initialization remains a controlled dependency.
Maintained/semantic/exact totals are unchanged.
