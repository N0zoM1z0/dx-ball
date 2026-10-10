# Shared file services

The binary-file loader at `0x403320` and MDS opener at `0x401000` use the same
Kernel32 import cells. [`file.c`](../../../src/file.c) now owns those four
services and the complete loader; sound and MIDI consume that shared interface.
The Windows adapter binds each service once to its existing SDK wrapper.

| Service | Original cell | stdcall arguments |
| --- | --- | ---: |
| CreateFileA | `0x44127c` | 7 |
| GetFileSize | `0x441270` | 2 |
| ReadFile | `0x441298` | 5 |
| CloseHandle | `0x441264` | 1 |

REA's complete saved dossiers identify nine calls: five in the loader and four
in the MDS opener. PE import entries and each `FF 15` operand corroborate the
shared storage. Three duplicate MIDI definitions and four sound-table fields
are replaced by these independently typed cells. The portable callbacks and
Windows wrappers use the same declarations.

The loader keeps the original `..\\` fallback, optional allocation, successful
short reads and failure ownership. Allocation failure leaves the file open;
read failure frees the destination and leaves the handle open. The sound
upload body already follows the original calls and live buffer reads, so its
logic stays intact.

## Compiler feedback

One compilation of each of 24 affected recipes produces 127 complete
comparisons with 1,312 actual relocations. The loader emits 307 bytes against
304; a longer `ReadFile` output-address instruction accounts for the extra
three bytes. Its ordinary local declarations remain intact. The MDS opener
remains 480/522 bytes. Both are candidates with full unmasked comparisons.
The fallback's four bytes are checked in the object and original executable.

Of 125 previously accepted affected functions, 124 still match. Changing the
shared declarations changes VC4's indexing expression emission in
`dxball_draw_effect_sprite`: 365 bytes against 361. Its source body is unchanged;
the current ledger moves it to candidate and retains the previous exact
product. Current totals are 134 exact functions / 20,887 code bytes and
283 source-present functions.

The existing MIDI Oracle passes 2,109 direct cases and 134 connected checks;
the existing sound Oracle passes 5,782 and 48. Only their native callback
bindings change. Native, VC4 and MinGW builds use the shared file module.

## Evidence

Loader: `ev_a52bb0030eab7563b8a83f854ffdd76af7e5b0382cd75bda896a04c3efed70a0`.
MDS opener: `ev_b065fc674d2df0514ae7b30b49b895ceb361f5ec770b3c4e0ec21eb8512ef3ed`,
with complete 522-byte span
`ev_a7b7f4ce05473f020601101338f2392f0e732597eaed9078a2bd13128a77a584`.

Existing October 7/10 REA archives are reused; no provider session is needed.
Full source inputs, objects, comparisons and reviews are retained under
`.analysis/checkpoints/exact-file-services-283-134/`.
