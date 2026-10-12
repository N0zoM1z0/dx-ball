# Exact intro point rendering phases

Point animation at `0x0040ED40` now matches its complete **711-byte** original
body, all 180 instructions and 40 actual relocation bindings. Plain scopes
separate the written header request, shared point iteration, locked pixel pass
and per-point pointer. The same source serves native and Windows builds.

The request is written before background restoration and has no subsequent
consumer. The loop index survives both point passes. The result and surface
description belong to the first pass through Unlock; each pixel pointer belongs
to its kind-zero point. The rectangle remains a standalone object from the
initial BltFast call through final by-value invalidation. Existing names, types,
capacities, expressions and call order remain unchanged.

Every object matches its original home in the 236-byte frame:

| Object | EBP home | Bytes |
| --- | ---: | ---: |
| Redraw rectangle | -16 | 16 |
| Written fill request | -116 | 100 |
| Shared point index | -120 | 4 |
| Lock result | -124 | 4 |
| Surface description | -232 | 108 |
| Per-point pixel pointer | -236 | 4 |

The earlier emitter contained 702 bytes and 570 differing positions. Four
record diagnostics also made the point update exact but lost the accepted
palette pulse: two emitted 368/114, a three-value pulse record emitted 370/2,
and a two-value record emitted 368/116. All four are rejected. The selected
plain phases preserve the complete 370-byte pulse and all **17 preceding intro
exacts / 6,095 bytes**. Redraw and scroller candidates remain unchanged.

The unchanged update loop passes 36 original/native tick, time and Lock-retry
cases, plus 36 separately compared point preparations. Complete point, wave,
palette and pixel arrays, state and ordered calls compare. Native and MinGW
builds pass. VC4 links the single matching intro object with 36 verified
unchanged objects. All **232 complete exact closures** verify; 235 historical
input inventories refresh without changing their case scopes. No game runs.

Current totals are **232 exact functions / 59,486 code bytes / 136 metadata
bytes**, with 41 authored candidates. Their code hashes are unchanged.

Original REA evidence is
`ev_380287bfea6a4f582b8e8ee477b5c7d470de69c6555f3ab997e0f5f7d4650b2d`,
operation 19 in the closed `2026-10-07T11-58-17.972Z-interactive-3053414` run.
Its complete assembly is reused. Source scope spelling is inferred from the
consumers and verified emission. Full comparisons, actual compiler inputs,
rejected stages, independent review and build receipts are retained in
`.analysis/intro-point-pass-workspace-20261013/`.

Twenty-nine completed source, object and tracking copies are preserved in
verified gzip carriers, releasing 4,460,544 allocated bytes. Current compiler
objects and build products remain available.
