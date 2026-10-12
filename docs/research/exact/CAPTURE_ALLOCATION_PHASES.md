# Sprite capture allocation and API phases

Capture at `0x004042B0` now keeps its allocation pointer inside the allocation,
failure-check and publication block. All later sprite accesses still reread
the live bank. The surface description and result belong to the API phase
through the final pitch transfer; the capture rectangle and color key remain
standalone outer objects.

The pointer's original three consumers are its allocation store, null check
and publication. Its address never escapes. The description is passed to
CreateSurface and GetSurfaceDesc, then read for pitch before rectangle
construction. Final Blt consumes the live sprite and capture rectangle.
Existing names, types, expressions, writes and call order are preserved.

One selected matching compilation reduces the emitter from 876 to **873
bytes**, against 852 original bytes. Strict differences fall from **803 to
745**. All 248 instructions and 42 real relocation bindings remain compared.
This is still a candidate; descriptor/result storage and bank-address
scheduling differ. The complete 140-byte frame contains the same five objects:

| Object | Original EBP base | Selected EBP base | Bytes |
| --- | ---: | ---: | ---: |
| Capture rectangle | -16 | -16 | 16 |
| Color key | -24 | -24 | 8 |
| Allocation pointer | -28 | -28 | 4 |
| API result | -32 | -140 | 4 |
| Surface description | -140 | -136 | 108 |

All twelve resource exacts retain 2,197 bytes; the other four resource
candidates and all forty other candidate code hashes are unchanged. Twelve
existing capture cases pass across all three banks, creation failures and
descriptor retries. Three existing callback cases also pass when bank selection
changes during CreateSurface, SetColorKey or GetSurfaceDesc. Defined owner and
pixel state and ordered calls compare.

Native and MinGW builds pass. VC4 uses the separate established `/ML` matching
and `/MT` game recipes, links one production resource object with 36 verified
unchanged objects, and emits identical capture bytes and bindings in both
recipes. All 232 exact closures verify; 235 historical input inventories
refresh without changing case scopes. No game runs.

A separate PCX header-lifetime diagnostic retains its 128-byte header but
worsens the emitter from 979/851 to 985/929. It is rejected and the selected
capture source/object restored without recompilation. The four unexplained
original PCX frame bytes remain unresolved.

Original evidence is
`ev_d7dd48a6f210a1a2cffea6be8318655763959610c9d94f8f8ff5621dad169b76`,
operation 00 of the closed `2026-10-10T17-22-54.305Z-requests-825249` run.
Full source/ABI review, eight compiler inputs, complete comparisons, case and
build receipts are in `.analysis/capture-phase-scopes-20261013/`.

Twenty-five completed source/object/tracking copies are retained in verified
gzip carriers, releasing 4,370,432 allocated bytes. Current products and unique
original REA evidence are preserved.
