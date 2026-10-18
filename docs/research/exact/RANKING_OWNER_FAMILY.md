# Ranking implementation owner control

One private source model places ranking drawing, reading, insertion and default
initialization, together with `dxball_scores[15]`, in a shared `scores.c` owner.
The original functions are consecutive at `0x406B20`, `0x406CC0`, `0x406D20` and
`0x406EE0`; they share the same records and persistence format. Current source
splits them between gameover and startup. This supports a bounded ownership
hypothesis, without proving original translation-unit boundaries or definition
order.

The model uses that one original address sequence. All four function bodies,
local records, capacities, expressions and calls remain byte-identical as source.
Existing public headers remain unchanged. Selected-row UI state stays in
gameover, and the shared file pointer retains its current owner. No order,
include, name, flag or local-layout variants are tried.

## Complete result

Three serial VC4 compilations compare the complete modified gameover and startup
owners plus the four-function scores owner: exactly the original 14 functions.
Every complete resolved code and metadata identity remains unchanged, including
13 exact functions and 4,156 exact code bytes. Actual literals and their original
targets are checked after generated symbol renaming; local-target guards remain
active for the full key-dispatch span. The owner model is rejected without
canonical source, object, report, ledger or delivery changes.

Ranking drawing remains 403 bytes against the original 404, with 330 strict
differing positions. Its complete 135-instruction correspondence explains that
result through one comparison producer:

| Original | Current |
| --- | --- |
| Load row index from EBP-32 into EAX | Load selected global into EAX |
| Compare selected global against EAX | Compare row index at EBP-32 against EAX |

The current pair is one byte shorter. The immediately following JNE observes
the same equality result; subsequent instruction addresses move by one byte.
Every other normalized instruction agrees, including every branch destination
by instruction identity, all calls and 18 actual bindings. Both complete frames
reserve 36 bytes and retain the original homes: X at -28, Y at -36, row at -32,
text count at -4 and the 20-byte text workspace at -24. This is a complete
correspondence, not an exact claim or unrestricted intermediate register/flags
equivalence. Source spelling and the original producer context remain open.

The original dossier is reused from operation05 of the closed
`2026-10-07T13-44-46.898Z-interactive-3331671` run, Evidence
`ev_a42b5c952ba3c544d58bf1b3c0c2456c9e13f6149d7090c32e2952888fd6ff3e`.
There is no new provider query. The earlier
[fixed-X/row-cursor control](CLOSED_STORAGE_DIAGNOSTICS.md#clock-and-cursor-follow-up)
and equality-spelling controls remain closed. Moving the text record into each
row is declined before compiling: all physical homes already agree, and no
evidence connects that lifetime to the remaining producer.

No native build, relink, oracle, game or full replay follows unchanged complete
emissions. Existing cases and acceptance scopes remain untouched. Commands use
one allowed CPU, CPU quota 35%, memory high 640 MiB and maximum 768 MiB. Private
`.analysis/ranking-owner-family-20261017/` retains frozen inputs, complete
comparisons, bindings and the instruction proof. Disposable source/object
carriers are archived and individually verified before deletion. Totals remain
391 exact functions and 24 authored candidates; reconstruction is unfinished.

## Connected Mac score producers, October 18

The [complete producer/consumer follow-up](MAC_CANDIDATE_FLOW_CONNECTIONS.md#reused-score-producers-and-parameter-kind-control)
reuses both Mac score bodies and preserves their grouped-list/file-format
boundary. Metadata qualifies one input-only unsigned-long inference; it does
not establish the row field kind, which remains unchanged. One fixed alias
proposal compares all 35 affected functions in three serial compilations.
All 31 prior exacts survive and high-score drawing remains 403/330. Paddle
regresses 677/68 to 678/210 from one width+X load/add pair, so reject the
entire model without adoption or variants. The original ranking CMP producer
and 36-byte frame correspondence above remain unchanged. All 754 protected
identities restore; current totals are 250 authored exact/20 candidates.
No native build, relink, game, provider or full replay runs. Thirty closed
raw members are archived/member-verified before deletion, with current
products and shared evidence retained. This is a later bounded control;
the historical totals and resource settings above describe the earlier run.
