# Intro score phase

The October 17 [cross-function workspace recovery](SCORE_WORKSPACE_REGIONS.md)
supersedes the buffer gap below: text100/decimal20 emits the complete587-byte
function exactly. Original declaration capacities remain inferred. The
following records the earlier scope-only checkpoint.

Menu redraw at `0x0040E0E0` now declares its score text, decimal buffer and text
length inside the existing score-present branch. The full-screen rectangle
stays outside that branch because it is used by all three surface copies.

The rectangle moves from EBP-20 to the original EBP-16; text length moves from
EBP-4 to the original EBP-20. The buffers keep their existing capacities of 32
and 11 bytes. Original stack addresses suggest larger storage regions, but the
original buffer capacities remain unproved. No unused storage is introduced.

The complete body remains **578 bytes / 560 differences** against 587 original
bytes. Both bodies have 174 instructions. The original reserves 140 stack bytes;
current source reserves 64. The nine-byte length gap is three bytes in the stack
allocation and three in each of two number-buffer address loads. All other
instruction widths match. Restoring two object homes changes
the code identity even though the raw difference count is unchanged. All 18
accepted intro functions retain their 6806 exact bytes, including point update
and palette pulse. The other 40 candidate code hashes are unchanged.

Nine unchanged maintained redraw cases pass: three primary-display modes and
scores zero, one and unsigned 32-bit maximum. They compare defined state,
arrays, pixels and ordered calls through the maintained original callees.
Native and MinGW builds pass. The single matching VC4 object also serves the
production recipe and links with 36 verified unchanged objects. All 232 exact
closures verify; 235 historical input inventories refresh. No game runs.

Original REA evidence is
`ev_8d3b245893789331b1a53500a14aae87ed382cd5465098be8604a64b721a1440`,
operation 01 of `2026-10-07T11-58-17.972Z-interactive-3053414`.
Independent source, frame and complete-candidate review passes, including all
22 recursively consumed project inputs. Source, full comparisons, input
identities and validation receipts are retained
in `.analysis/intro-score-phase-20261013/`.
Totals remain 232 exact functions / 59,486 code bytes / 136 metadata bytes,
with 41 authored functions still nonexact.

17 completed copies are retained in verified gzip carriers, releasing
4,329,472 allocated bytes. Current products and original evidence are preserved.
