# Floating control and classification

Eight full bodies are recovered from the local executable,18 fresh REA records
and whole pinned VC4 CRT sections. Six are exact after every actual relocation:

| Entry | Body | Bytes |
| --- | --- | ---: |
| 0041CF90 | Hardware-to-abstract control word | 161 |
| 0041D040 | Abstract-to-hardware control word | 141 |
| 0041CF70 | Control entry, excluding denormal-mask changes | 24 |
| 00419C40 | Math errno selection | 42 |
| 00419CA0 | Prioritized exception-to-error mapping | 50 |
| 00419D20 | Infinity/quiet-NaN/signaling-NaN classification | 99 |

Name lookup retains38 bytes/5 register-allocation differences. Exponent editing
improves60/57 bytes with57 differences to57/57 with22 differences. Both remain
candidates. Its full int argument contributes only a wrapped biased low word;
unsigned biasing avoids signed overflow and negative-shift undefined behavior.
Binary64 views are alias-safe, and the work union retains natural double alignment.

All27 name records/216 initialized bytes,27 pointer relocations and134 complete
literal bytes match. Native record pointers retain natural width. The control
wrapper calls the genuine remaining `_control87` body; no simulated hardware
backend or omitted x87 operation is claimed. Hardware state and integration remain
open. Evidence/products: `.analysis/runtime-fp-control-20261014/`. The REA session
closed after18 queries. Only scoped VC4/native/i686 compilation and full comparisons
ran; all296 preceding exacts and89 candidates retain their inputs/products/results.
Current totals:402 source bodies,302 exacts/67,800 code bytes/136 metadata bytes,
and91 candidates, including the unchanged34 authored candidates. No runtime tests
or game builds were run.
