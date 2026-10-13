# Float rendering and output

Eight complete CRT bodies are recovered from the local executable, fresh REA
assembly/pseudocode and whole pinned VC4 sections. Six match every byte:

| Entry | Body | Bytes |
| --- | --- | ---: |
| 00418FF0 | Fixed formatting | 251 |
| 004190F0 | General formatting | 176 |
| 004191A0 | General-to-exponent mode wrapper | 43 |
| 004191D0 | General-to-fixed mode wrapper | 38 |
| 00419270 | Overlap-safe text shifting | 43 |
| 0041D690 | Floating output record | 103 |

Exponent formatting remains310 bytes/2 differences, both in suffix-address
addition scheduling. Binary64-to-serialized80 conversion remains185/187 bytes
with75 differences. These are candidates, not exact claims. Every actual
relocation and the complete six-byte `e+000` literal is attested.

The output routine takes double by value, not the argument-free prototype shown
by the decompiler. E/F formatters return the original buffer. Correcting those
signatures preserves all eight affected preceding exacts and four candidates.
The renderer retains general-mode, magnitude, rounding expansion and cached
record state, including hot-path differences. Fixed output uses the original
signed minimum for leading fractional zeros. Binary conversion handles zero,
denormals and exponent2047 as separate cases; both signed zeros become zero.

All six initialized renderer state bytes and46 zero-initialized output/pointer
bytes agree. Original alignment gaps are not source fields; native pointers grow
naturally. One failed REA request-name setup was closed and recovered; the next
session completed13 queries and closed. Products and full evidence are retained
in `.analysis/runtime-float-render-20261014/`. Only scoped compilation and whole
comparisons ran, with no game/runtime tests. All290 preceding exacts and87
candidates are preserved. Current totals:394 source bodies,296 exacts/67,283 code
bytes/136 metadata bytes, and89 candidates. Physical integration remains open.
