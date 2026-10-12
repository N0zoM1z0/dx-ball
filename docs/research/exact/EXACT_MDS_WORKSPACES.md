# Exact MDS parser and compact-event conversion

The parser and event converter in `src/midi.cpp` now match their complete
original bodies, adding **1,211 application bytes**. The ledger reaches
**213 exact functions / 48,585 code bytes / 136 metadata bytes**, with 60 authored
functions still nonexact.

| Function | Original entry | Whole code | Frame |
| --- | --- | ---: | ---: |
| Parse MDS | `0x401210` | 868 bytes | 88 bytes |
| Expand compact events | `0x401580` | 343 bytes | 20 bytes |

The parser retains its eight-byte disk block record. Its input MIDIHDR and
chunk word enclose the mutable parse progress: current output header, result
and remaining buffer count. The converter keeps the payload length outside
one cursor record containing input/output byte budgets and their pointers.
Every member is initialized and consumed; native pointer widths grow naturally.
These shared declarations reproduce the observed storage without changing the
existing operations, cleanup gotos, interfaces or record capacities.

| Parser home | EBP | Converter home | EBP |
| --- | ---: | --- | ---: |
| Disk block base | -8 | Payload length | -4 |
| Input MIDIHDR base | -72 | Input cursor | -8 |
| Chunk length | -76 | Output cursor | -12 |
| Remaining buffers | -80 | Output capacity | -16 |
| Result | -84 | Input remaining bytes | -20 |
| Current output header | -88 | | |

The first owner compilation already made the converter exact and reduced parser
differences from 40 to 14. Grouping the parser's three progress values made the
second compilation exact for both complete functions. Four prior MIDI exacts
retain 634 bytes. Loader and playback candidate comparisons remain unchanged.

The original dossiers are
`ev_77dddb1d53c6bab6fa3f14d7c99306f681a2924a232ea0cb30d347ac7180e7a9`
and `ev_0e7f8948f3c0f268ac5c6331fff206ed9abcb368225c4fc744fb40d8a8b979cf`.
The complete parser read,
`ev_cbd6ebc9417a27d9bf6922089d77670686db275fa07f8514db31928b07dc2ded`,
attests all 868 bytes, including forty bytes outside the provider's function
ownership. Every actual relocation and all those internal jumps participate in
the zero-difference comparison. Matching supports these maintained source
declarations; original identifiers and declaration spelling are unknown.

The unchanged existing loops pass **253 parser and 588 converter cases**,
including all six original songs, truncated chunks, allocation failures,
long-event padding, capacity boundaries, poisoned tails and partial writes.
Linux and MinGW builds pass. VC4 links the same owner with 36 verified unchanged
objects, without another source compilation. All 213 accepted byte extents and
compiler-input/object identities verify. No loader/controller/callback suite or
game campaign runs. Historical semantic scopes retain their case counts while
their input inventories refresh for this source change.

Before inputs, both compiler stages, full comparisons, selected Oracle and
products are retained in `.analysis/mds-workspaces-20261012/`. Completed staging
and before-product files use verified gzip carriers after cleanup.
