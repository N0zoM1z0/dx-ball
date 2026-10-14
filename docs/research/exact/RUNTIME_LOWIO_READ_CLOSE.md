# CRT reading and handle lifetime

Four complete source bodies now cover descriptor reads, closes, handle
installation and handle invalidation. Descriptor closing is now a complete exact.

| Entry | Original/current bytes | Differences |
| --- | ---: | ---: |
| `_read`, `0x41A120` | 611/605 | 463 |
| `_close`, `0x419ED0` | 199/199 | 0 |
| `_set_osfhnd`, `0x41D890` | 163/163 | 13 |
| `_free_osfhnd`, `0x41D940` | 144/144 | 12 |

Direct record expressions and the owned validation-error return from shipped
`close.c` improve199/14 to199/2. Capturing stdout before stderr reduces this
to one commuted comparison byte; consuming both handle snapshots restores the
original comparison and closes all199 bytes and eleven actual relocations.
The complete pinned section and retained REA assembly independently agree.
All344 old exacts and104 other candidates remain; the three owner companions
have identical complete results. Three compiler sets, no runtime/provider work.
Receipt `.analysis/descriptor-close-original-expression-20261014/verification.json`.

The low-I/O record adds only its observed lookahead byte at Win32 offset5;
natural stride remains8 and host handle width still grows. Reading retains
pending pipe/device characters, leading-LF state, CRLF compaction, Ctrl-Z EOF,
broken-pipe zero return and error5 publication. A terminal CR consumes one extra
byte: pipes/devices cache non-LF; ordinary files seek back except the original
single-character LF special case. The transferred total is reused for lookahead
errors after the scan endpoint is captured. Shared output-advance/error paths
and a three-field transfer record improve584/546 to605/463; the16-byte frame is
retained. These are source and complete comparison results, not runtime acceptance.

Close queries stdout before stderr and skips OS close when their handles alias.
It invalidates the handle even after OS failure, but clears flags only on success.
Installation does not require the open bit; invalidation does. Console mode1
updates the three actual standard-handle IDs before writing the current record.
Switch dispatch and a common zero-error phase restore all three helper lengths.
Application-mode, registry/error storage and game integration remain open.

One closed REA run, `2026-10-13T13-45-50.862Z-interactive-1670817`, retains twelve
info/pseudo/assembly records. Complete pinned CRT sections independently agree
for all four entries. Private proof: `.analysis/runtime-lowio-read-close-20261013/`.
All255 previous exact results and53 preceding candidates are unchanged after
the lookahead-header consumer compilations; the two affected exacts preserve
169 bytes and the complete360-byte private error table. Source presence324;
candidates57:34 authored and23 runtime. Native/i686 standalone compilation
covers all three affected owners. No runtime tests or game builds run.
