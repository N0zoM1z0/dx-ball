# Exact sound initialization and WAV parsing

Sound initialization at `0x00405120` and WAV parsing at `0x00406290` now
match their complete 1,705/269-byte original bodies. Two compilations of the
shared sound owner restore the original local storage through consumed records
and their scopes. Fourteen accepted sound companions retain 2,087 exact bytes;
the upload candidate keeps its previous 695-byte body and 31 differences.

Initialization uses one 32-byte workspace containing the primary-buffer
descriptor, reload slot, retry flag and operation result. A dialog response
belongs to the block after the existing device guard; the filename belongs to
each live reload branch. The resulting 324-byte frame places result/retry/slot
at EBP-4/-8/-12, the descriptor at EBP-32, response at EBP-36 and filename at
EBP-292. All retries, dialog responses, releases, partial buffer handling and
exit codes retain their original order.

The parser groups the container end and signature separately from the current
chunk's cursor, length and tag. It still reads and advances each DWORD in order,
checks RIFF/WAVE, stores each accepted format pointer, returns immediately on
data, and rounds skipped chunk lengths to an even byte count. Its 24-byte frame
places signature/end/tag/length/cursor at EBP-4/-8/-12/-16/-20; the compiler's
switch selector occupies EBP-24. No input read or output write changes.

The first owner compilation makes the parser exact. The second also makes
initialization exact. Complete comparison covers every byte, including the
70/5 internal jump bytes outside Ghidra's owned ranges. Initialization has
97 actual relocations and twelve complete literal attestations. Six generated
title-string ordinals change in the second object; their full contents and
original addresses are verified before updating the bindings. The first
comparison consumer rejects those stale names. Its repair reads the completed
object without recompiling. Original declaration spelling remains unknown.

Linux and MinGW builds and a VC4 relink with 36 verified unchanged objects
succeed. Six unchanged oracle loops pass 798 parser cases, 116 initialization
cases and eight prepare calls. They include all 26 original WAVs, odd/short
chunks, output preservation, factory retry, absent owners, partial buffer
failures and terminal exits. The driver initially selects an extra connected
loop and stops before execution; restricting selection to the six intended
loops resolves it. The maintained tests and case bodies are unchanged.

All 217 accepted exact units and their input closures verify. Current totals
are 51,192 code bytes and 136 separate metadata bytes, with 56 authored
functions remaining nonexact. No game campaign runs.

The saved initialization/parser dossiers are
`ev_0c19fd7b02df4709514364206dec7df270a537b02ffbdda25a57516fcd78ce1f`
and `ev_8c97f00d8301c9fad99e761f8bbe2ea90f8dc14d6e8db6709a75e15c49c6c1a3`.
Complete byte evidence is
`ev_ea17c0f8232c3bed494b5f8e97ff67790e1d38eb410d071395c0337072d22447`
and `ev_94e9828bd14fb37d829065569ecc12507b58c3fd897901734ec17b6a076da576`.
All four record hashes and raw spans verify against the original executable;
no new REA query is needed. Compiler stages, before inputs, complete comparisons,
case receipts and verified compressed product copies remain private under
`.analysis/wave-chunk-records-20261012/`.
