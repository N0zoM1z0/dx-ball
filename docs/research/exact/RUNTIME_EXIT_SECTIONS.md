# Complete CRT tables and linked cleanup

XP/XT now join the reconstructed XC/XI contributions in the writable merged
CRT table. The complete 84 bytes and all 13 callback bindings match the original
and the actual VC4 image. No function body, public declaration or match recipe
changes; all 380 exact function results and producers remain byte-identical.

| Range including end marker | Original address | Bytes | Consumed bytes |
| --- | --- | ---: | ---: |
| XC | `0x421000` | 48 | 44 |
| XI | `0x421030` | 16 | 12 |
| XP | `0x421040` | 12 | 8 |
| XT | `0x42104C` | 8 | 4 |

The existing two-slot pretermination array owns the null start and stdio callback
in `.CRT$XPA`; `.CRT$XPZ` supplies its null end marker. The termination array
contributes to `.CRT$XTA`, followed by `.CRT$XTZ`. This groups the original
XPA/XPX pair in one typed source array. It preserves the current array API,
whole emitted table and original caller bounds; it does not reproduce the
original separate XPX producer. No synthetic gap or padding is introduced.

The controller's actual linked relocations still bind the complete two-slot
and one-slot consumed ranges. The controller128, walker32 and stdio finalizer20
also agree with their retained objects after all image relocations. The walker
remains the existing six-difference candidate, not a new original exact.

## Focused execution

Three custom-entry VC4 processes import only KERNEL32 and exclude a host CRT.
They run the maintained real heap/low-I/O, XI/XC, stdio/onexit allocation, filter
installation and list constructors before reaching cleanup.

- Returning normal cleanup calls B, A, the real filter-restoration callback,
  then controlled flushall/fcloseall endpoints: visible trace `BAFC`.
- Returning quick cleanup skips callbacks and pretermination. Normal cleanup
  with return-mode256 stores a zero low-byte flag, returns and emits `BAF`.
- Normal physical exit emits `BAF` and reaches actual ExitProcess63. Quick
  physical exit emits no callbacks or stdio events and reaches ExitProcess64.

The flush endpoint checks that the real Windows filter was already restored,
so the callback/pretermination ordering is observed. Stdio, fatal and unused
exception-dispatch dependencies are typed fixture boundaries. Physical stdio
drivers, FP initialization, complete CRT entry and final game remain unclaimed.

Only the two data owners are recompiled by VC4; other source products and two
unchanged fixture helpers are reused by full input/product identity. Native
and i686 C90 checks pass. The affected native termination owner passes its
existing 1,031 calls/1,026 fixtures with unchanged observations. Four existing
semantic input identities are refreshed; the other245 rows remain unchanged.
There is no COFF queue, full historical replay or game build.

The 84-byte REA6.5.0 Evidence is reused:
`ev_73a146a038dc9800cd869abb7261b6989c3713c813683a1453cd464602ea0586`.
No new provider session runs. Recipes are in
`config/runtime-initializer-sections.json` and
`config/runtime-termination-tables.json`. Private receipts:
`.analysis/crt-exit-sections-20261016/`, including `source/`, `verification.json`,
`windows-probe.json`, `native-termination.json`, `link.json` and `adoption.json`.
The linked-byte reader was corrected to omit a wrapper discarded by the linker;
the same objects/executable were retained.

Counts remain 543 inventory, 468 source, 380 exact, 88 candidates and249 semantic
rows; exact code/metadata remain77,485/244 bytes. Heavy work is serial on one
allowed CPU with CPU35%, memory high640MiB/maximum768MiB. Remaining function
recovery, FP/CRT dependencies and the final original-compiler game/play check
remain open; ports follow that work.

Sharing12 identical immutable carriers reclaimed about3.6MiB. Unique process
receipts, current native library and compiler products remain archived.
