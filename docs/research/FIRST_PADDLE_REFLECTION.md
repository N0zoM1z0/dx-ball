# Current first paddle reflection

The original executable and current VC4 game agree on all 108 complete sampled
ball vectors, in order, through the first actual paddle reflection. Twenty-four
of these vectors follow the reflection: angle 105, speed five, dx minus one and
dy minus four. Both retain three lives and ten points, rise to x381/y349, return
to the menu and exit normally.

This is a new actual-input case following the [first missed ball](FIRST_BALL_FLIGHT.md).
Opening/play input initializes the attached ball at x320/y441. A real mouse
press releases it, and mouse motion moves the paddle to x415 to catch the
returning ball. The initial upward flight and brick collision are prerequisites
of this reflection; the successful missed-ball case is not rerun unchanged.
No target writes, injected calls, game build or helper recompilation are needed.

## Sampled reflection and board effects

The verified persistent reader from the first-flight checkpoint records all
thirteen ball fields and both sprite dimensions. Full initial fields agree with
the independent one-shot reader. The retained streams contain 540 original and
523 current VC4 records, with zero malformed records. Offline comparison
validates every indexed byte extent, including original Windows CRLF bytes,
before comparing the finite attached-to-reflected interval.

| Observed state or effect | Original and current VC4 |
| --- | --- |
| Initial complete board | Original `DEFAULT.BDS`, first 400 bytes |
| Only board change | Tile 291: 11 to 0; score 0 to 10 |
| Brick collision | x362/y275, dx1/dy4, bounce count 1 |
| Paddle at reflection | x415 |
| First sampled reflected ball | x404/y441, previous x403/y439 |
| Reflected motion | Angle 105, speed 5, dx-1/dy-4 |
| Ball counters at reflection | Bounce count 1, wall bounces 0 |
| Last compared rising ball | x381/y349, previous x382/y353 |
| Final compared score/lives | 10 / 3 |
| Distinct complete vectors | 108 each; all equal in order |
| Reflected complete vectors | 24 each; all equal in order |
| Game and reader shutdown | Exit code zero for both profiles |

There are no unpaired sampled vectors in this interval. Complete resulting
400-byte board states also agree. The host receipt intervals range from about
10.01 to 17.40 ms for the original and 10.36 to 13.51 ms for VC4. These are
receipt timings, not simulation ticks. Sequential field and sprite reads are
not atomic snapshots; equal sampled vectors do not establish every simulation
frame or synchronized clocks. Other paddle positions, speeds, later boards,
whole campaigns and physical display/audio/MIDI remain open. No source, exact
function or origin count changes follow from this observation.

## Evidence and preservation

Current VC4 SHA-256:
`0302cf38a82c7d9843af135e2c054b26d2dd5c7f1d12d53199f1b1584c3a4b28`.
All four current products and all original files retain their input identities.
The helper and its actual recursive compiler-input closure are reused from
`.analysis/first-ball-flight/reader-identity.json`.

REA 6.4 controlled-replay Evidence:
`ev_bb68bea389757a7cf605b424b195a0f0651f3f0330aeefd9b97ad41edc46a0e3`.
Its 33.271-second capture ends with child exit zero and hashes the complete
10,567-byte report without filesystem enumeration or hash omissions. The
64-sample process limit is reached, with explicit partial coverage and zero
sampling failures. This preserves the recorder's incomplete descendant-history
and non-atomic executable-binding limits. Two retained terminal frames are
child progress messages, separate from the SDK records.

Private `.analysis/first-paddle-reflection/` retains the report, complete raw
streams, byte indexes, actual scenario, Evidence, progress log and comparison.
The unique raw carriers total 1,205,704 bytes and are referenced by the small
seal without a second copy. Hash-verified temporary runtime copies are removed
after both processes stop, releasing 3,424,256 allocated bytes. Feedback on REA
performance, response size and usability continues in the single existing
`/tmp/dxball_rea_feedback_20261010.md`.
