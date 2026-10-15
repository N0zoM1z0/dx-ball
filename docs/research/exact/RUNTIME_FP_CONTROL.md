# Floating control and classification

Eight full bodies are recovered from the local executable,18 fresh REA records
and whole pinned VC4 CRT sections. Seven are exact after every actual relocation:

| Entry | Body | Bytes |
| --- | --- | ---: |
| 0041CF90 | Hardware-to-abstract control word | 161 |
| 0041D040 | Abstract-to-hardware control word | 141 |
| 0041CF70 | Control entry, excluding denormal-mask changes | 24 |
| 00419C40 | Math errno selection | 42 |
| 00419CA0 | Prioritized exception-to-error mapping | 50 |
| 00419CE0 | Binary64 exponent editing | 57 |
| 00419D20 | Infinity/quiet-NaN/signaling-NaN classification | 99 |

Name lookup remains a candidate with38 bytes/5 register-allocation differences.
Direct binary64 assignment replaces the two-word snapshot in exponent editing,
closing all57 bytes. VC4 uses integer transfers in the original high/low order,
then loads the floating result only after the exponent write. Its full int
argument contributes only a wrapped biased low word;
unsigned biasing avoids signed overflow and negative-shift undefined behavior.
Binary64 views are alias-safe, and the work union retains natural double alignment.

The preceding typed representation snapshot captures the complete two-word value
before editing its high halfword. It preserves all bits without an early x87
load, and reduces22 differences to4. Generic memcpy59/57/57 is rejected; the
selected typed snapshot is57/57/4. Only initial high/low word loading and saving
order differs at that checkpoint. No field/operand permutation sweep is made. The99-byte special
classifier remains exact. Two VC4/native/i686 sets and full comparisons run,
retained REA assembly `ev_d4d7a619bff0091472889fd2dab1cad759538df445e025a04ff6c08e7e9b6e22`
is reused; no provider/runtime/game tests.
Current totals457/335/code69,718/candidates113 stay unchanged. Receipts:
`.analysis/runtime-float-exponent-20261014/verification.json`.

The direct-assignment recovery preserves classification99 exact and all357
previous exact results. All91 other candidate results remain unchanged. One
VC4/native/i686 set is reused with identical maintained inputs; retained REA and
the full pinned CRT section are reused, with no runtime tests. Current totals:
358 exact functions/75,060 code bytes,91 candidates. Receipt:
`.analysis/exponent-original-double-transport-20261015/verification.json`.

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
