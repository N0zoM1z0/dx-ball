# Exact ranking insertion cursor

The complete high-score insertion at `0x406D20` now matches **446 bytes** and
all 26 relocation bindings. The accepted total reaches **228 functions /
57,479 code bytes / 136 metadata bytes**, leaving 45 authored candidates.

The selected rank and backwards shift index form an eight-byte insertion
cursor. Its rank remains at EBP-4 and index at EBP-8. Grouping these actual
values restores the original shift-loop read order and signed exit condition;
the previous three differences disappear. Score reload, equal-score placement,
name copying and direct file operations keep their observed order. No buffer
capacity, arithmetic type or interface changes.

One pinned VC4 compilation preserves the six accepted game-over companions
across 2,329 bytes. Ranking drawing retains its 403/404-byte candidate and
330 differences. The source spelling and original use of a record are inferred;
the entire emitted insertion body, literals and actual bindings match.

The complete original dossier is reused from closed run
`2026-10-07T13-44-46.898Z-interactive-3331671/06-analyze_function.json`, Evidence
`ev_b8a8525ffa6ad9d00db1a74e35f1aabae8aa6ff5e8823367769dd78876448eb6`.
The original initializes rank at `0x406D47`, shift index at `0x406DC3`, and
loads the index before comparing against rank at `0x406DCA..0x406DD0`.
Existing complete `score.dat` and `wb` literal attestations remain in the manifest.

The unchanged insertion selection passes 102 original/native cases: every
placement boundary, equal-score precedence, unsigned extremes, failed opens,
short reads and writes, reloaded rankings and poisoned tails. Each case compares
the returned rank, complete 660-byte rankings, names, file contents and ordered
CRT calls. A final report assertion incorrectly expected unused harness counters
to be absent; the completed-case counter shows all 102 comparisons passed.
The report consumer is corrected and the receipt recovered without replaying them.

Linux and MinGW builds pass. VC4 links this one matching object with 36
hash-verified unchanged objects, with no additional legacy source compilation.
All 228 accepted compiler closures and full extents pass. Historical semantic
input inventories refresh without rerunning unrelated fixtures. No game runs.
Private receipts and completed products are retained in
`.analysis/ranking-insertion-cursor-20261012/`.
