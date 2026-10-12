# Exact binary-file transfer state

`dxball_load_binary_file` at `0x00403320` now matches its complete 304-byte
original body. One consumed file-state record groups the byte count, actual
handle and 260-byte fallback path. The separate transferred-byte output belongs
to the function scope because ReadFile writes it directly.

The canonical VC4 frame remains 272 bytes. Transferred bytes occupy EBP-4;
the fallback path starts at EBP-264, handle at EBP-268 and file size at EBP-272.
This restores the original short LEA for the ReadFile output argument and every
other local operand. The preceding body was 307 bytes with 89 differences.
The current complete comparison has zero differences after all ten actual
relocations, including full four-byte `..\` prefix attestation.

Opening, fallback retry, size query, optional allocation, read and close retain
their original order. Allocation failure still leaves the handle open. Read
failure still releases the destination without closing the file. Successful
short reads return the destination with its untouched suffix. The record adds
no field or operation beyond those already consumed by the loader; original
declaration spelling remains unknown.

One file compilation supplies the accepted object. Linux and MinGW build;
VC4 relinks with 36 verified unchanged objects and no extra source compilation.
Two unchanged oracle loops pass 38 original/native cases covering allocation,
short-read poison tails, failure ownership and primary/fallback open outcomes.
Complete buffers and ordered effects agree.

All 220 accepted exact units and input closures verify. Current totals are
54,187 code bytes and 136 separate metadata bytes, with 53 authored functions
remaining nonexact. No game campaign runs.

Original evidence is
`ev_a52bb0030eab7563b8a83f854ffdd76af7e5b0382cd75bda896a04c3efed70a0`,
operation 16 of run `2026-10-07T16-15-32.551Z-interactive-3807439`.
The complete contiguous dossier is reused without a new provider query.
Before inputs, compiler output, full comparison, case receipt and verified
compressed product copies remain in `.analysis/file-transfer-state-20261012/`.
