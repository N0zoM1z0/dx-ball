# Sprite-bank upload pointer

The later [color-key phase](BANK_COLOR_KEY_PHASE.md) keeps the key independent
and moves it into the same consuming block. Current bank differences are 72;
the results below describe the preceding pointer checkpoint.

The bank loader's API workspace now includes the existing destination pixel
pointer alongside its surface description and return value. The pointer is
computed and consumed only during the locked upload. File pixels, metadata,
the color key and traversal counters keep their separate ownership. The
workspace lasts from surface setup through Unlock.

The complete matching body stays 1475 bytes and 425 instructions in a 180-byte
frame. Its differences fall from 76 to 74. Description, result and pixel now
match their original homes at EBP-180, EBP-72 and EBP-68. Scalar homes and two
commuted multiplication pairs still differ; the function remains nonexact.

A separate 124-byte workspace also includes the color key. It reduces the
bank comparison to 72 differences but changes the accepted glyph search to
146 bytes with 86 differences. That stage is rejected. The selected 116-byte
workspace preserves all twelve resource exact functions, totaling 2197 bytes.

Ten existing bank cases and three existing callback cases pass, including bank
changes during color-key and descriptor calls and a pitch change during Lock.
The sampled pitch, live bank reads, call order and upload writes are unchanged.
Native and MinGW builds pass. VC4 compiles matching `/ML` and production `/MT`
separately, then links the production object with 36 unchanged objects. All 232
accepted complete closures pass; 39 other candidate code identities are
unchanged. PCX source is unchanged, but its emitted loop-bound product loads
the two local operands in the opposite order. Only two operand bytes change;
all other instructions, widths and relocations stay identical. The low-32-bit
product is equal. Both inputs are sign-extended 16-bit header maxima, so their
product also fits signed 32-bit C arithmetic. Its complete comparison remains 979/862 with 851
differences. Historical input inventories refresh 235 rows. No game session runs.

Original REA evidence is
`ev_b55c6def4c1b4af6c165acfb1623311bffa077753d93fab01531787dca6b6d70`,
operation 01 in `2026-10-10T17-22-54.305Z-requests-825249`. Complete comparisons,
compiler inputs and validation receipts are retained in
`.analysis/bank-transfer-workspace-20261013/`.

Independent review verifies the declaration-only transfer, all eight source
inputs, all 77 bindings, the three restored homes and the PCX operand change.
Twenty-one completed copies are retained as verified gzip files, releasing
4,341,760 allocated bytes. Current build products remain available.

The accepted total remains 232 functions / 59,486 code bytes / 136 metadata
bytes, with 41 authored candidates still nonexact.
