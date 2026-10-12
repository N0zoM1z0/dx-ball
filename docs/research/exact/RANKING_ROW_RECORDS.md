# Ranking text and row-position records

Ranking drawing at `0x00406B20` now groups its twenty-byte number buffer and
consumed text length separately from the row's Y coordinate, index and X
coordinate. The records restore every original home in the 36-byte frame:
count at EBP-4, buffer at EBP-24, X at EBP-28, index at EBP-32 and Y at EBP-36.
The API, score reads, formatting, highlight calls and row advancement are
unchanged.

The complete candidate is still 403 bytes against the original 404. The selected
row comparison loads the global before the local index and uses a shorter
encoding; the original reads the index first. Subsequent addresses therefore
shift by one byte. The strict comparison improves from 335 to 330 differences,
with the frame homes restored, but this function remains nonexact.

One game-over compilation preserves six exact companions across 2,329 bytes;
insertion retains its 446-byte body and three differences. Actual generated
literal contents and internal-label definitions verify before rebinding their
names. Seventeen unchanged ranking cases cover every selected row and two
outside selections, comparing complete state and ordered drawing effects.
The current product receipt is
`.analysis/intro-grid-cursor-20261012/verification.json`.

The complete saved dossier is
`ev_a42b5c952ba3c544d58bf1b3c0c2456c9e13f6149d7090c32e2952888fd6ff3e`,
operation 05 of run `2026-10-07T13-44-46.898Z-interactive-3331671`.
No new provider query runs. Before inputs, complete compiler comparison and
focused cases are retained in `.analysis/ranking-row-records-20261012/`.

Two separate UI diagnostics test a consumed measurement/index record with
either a grouped or separate glyph index. They produce 281/279 bytes with
186 differences and 280/279 with 58, respectively. Both preserve the five UI
exacts but worsen the preceding 279-byte measurement candidate. Both are
rejected; the verified source and canonical object are restored without another
compilation. No UI case replay runs. Retained records are in
`.analysis/text-measurement-record-20261012/`; do not repeat these models.
