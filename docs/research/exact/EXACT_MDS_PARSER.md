# MDS loading and event conversion

The file loader, RIFF/MIDS parser and compact-event converter now follow their
complete original instruction flows. The parser uses a real format record,
block record and input MIDIHDR. Four authored word/buffer helpers have been
removed from [`midi.c`](../../../src/midi.c).

| Function | Original address | Emitted / original bytes | Comparison |
| --- | --- | ---: | --- |
| Open MDS | `0x401000` | 480 / 522 | Candidate; cleanup jumps and storage differ |
| Parse MDS | `0x401210` | 788 / 868 | Candidate; control flow and storage differ |
| Expand events | `0x401580` | 343 / 343 | Candidate; 38 local-storage bytes differ |

The exact total remains 135 functions / 21,248 code bytes. All 99 previously
accepted units affected by the shared header remain exact.

## Recovering the records

The original parser copies three DWORDs into context offsets 4, 8 and 12 using
one destination base. `DxBallMdsFormat` groups the time division, buffer capacity
and flags into that 12-byte record. The context remains 36 bytes on i686.

At `0x401431`, an eight-byte block record is copied from the file into two
adjacent words. It contains a start tick and payload length. The original
copies both words even though this routine only consumes the length.

The parser's local input descriptor occupies 64 bytes, beginning at EBP−72.
At `0x4014A4..0x4014B3`, it writes the data pointer, bytes recorded, then buffer
length. The converter reads that same data/bytes-recorded prefix and writes
the output's bytes-recorded field. Both descriptors therefore use the existing
`DxBallMidiHeader`; the former three-field input type is removed. The native
record grows with pointers to 120 bytes.

## File and buffer traversal

The loader reuses its input and length parameters for the mapped view and file
size. Each failure assigns its own return code before common cleanup. Cleanup
frees a failed context, then unmaps the view and closes mapping/file handles.
The output context is assigned only after a successful parse.

The parser advances and subtracts the RIFF header in two steps: eight bytes,
size validation, then four bytes. It preserves the separate format and data
chunk updates, copies each block header before checking its payload length,
and advances output buffers using the live context capacity. Failed banks are
unlocked and freed through two fresh GlobalHandle calls.

The converter copies the tick before checking for a missing event word. It
then writes stream ID zero and the event DWORD before validating a long
payload. Payload lengths round up to four bytes. Only a successful conversion
updates bytes recorded; failures preserve the original partial writes.
These reads use the original word/record representation on the x86 builds;
arbitrary host alignment is outside the portable source contract.

## REA evidence and comparison

The full dossiers are indexed in [the MIDI owner note](../MIDI_OWNER.md).
Two focused `read_bytes` requests added the complete open/parse spans:

| Span | Evidence ID |
| --- | --- |
| Open, 522 bytes | `ev_a7b7f4ce05473f020601101338f2392f0e732597eaed9078a2bd13128a77a584` |
| Parse, 868 bytes | `ev_cbd6ebc9417a27d9bf6922089d77670686db275fa07f8514db31928b07dc2ded` |

Both responses match the verified executable. The 25/40 bytes excluded from
the function address sets are internal five-byte cleanup jumps. Complete
comparisons include those bytes. Responses are retained in
`.analysis/rea/runs/2026-10-10T07-53-15.117Z-requests-4133453/`; closing the
session saved all 483 cumulative records, including the previous 481.

Twenty affected recipes were compiled together. One further MIDI-only compile
expressed the event's high bit as a DWORD flag test, removing four promotion
instructions from the initial byte expression. The complete converter now has
107 instructions matching the original boundaries and operands except for
38 EBP local displacements. Its sole call binds to the original memcpy thunk
at `0x416610`. The differences remain visible in the comparison.

One existing MIDI Oracle passes 2,109 direct cases and 134 connected checks,
including all six songs. Its input descriptor backing now uses the complete
header; logical fields and cases are unchanged. Native, VC4 and MinGW builds
succeed. VC4 reuses 24 current objects and compiles eight remaining sources.

Full inputs, prior emissions, raw evidence, independent reviews and game
products are retained in `.analysis/checkpoints/exact-mds-parser-283-135/`.
Working receipts live in `.analysis/exact-mds-parser/`.
