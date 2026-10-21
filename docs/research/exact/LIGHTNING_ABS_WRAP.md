# Last-brick clipping absolute value

October22 supersession: the [complete exact controller](LAST_BRICK_EXACT_SOURCE_OWNER.md)
is now adopted at269/270. Its coherent independent owner retains all18 current
display exacts and both real absolute calls. The controls below are historical.

The later [shared magnitude-call control](LIGHTNING_MAGNITUDE_BOUNDARY.md)
restores both actual call targets in one private model but gains no complete
exact and loses four companions. It is rejected; the source below stays current.

October 20, 2026. Both negative last-brick crop branches now preserve the
original 32-bit absolute-value operation without relying on undefined
`abs(INT_MIN)` behavior:

```cpp
(DxBallInt)(0u - (DxBallUInt)value)
```

The expression executes only after the existing `value < 0` guard. For every
ordinary negative value it produces the positive magnitude. For `INT_MIN` it
retains the original low 32 bits and stores `INT_MIN`. The later X/Y reset,
rectangle construction, clipping, lightning state, effects and callbacks are
unchanged. This recovers an operation contract, not unique historical cast
spelling.

## Original operation and bounded witness

Retained complete last-brick Evidence
`ev_f8610be2baa2323aec8fcd14317794aebe74eefa78b4d66c9cf874ca117eb5bc`
shows calls at `0x4161FC` and `0x41626F` to the original CRT `_abs` at
`0x416780`. That complete helper loads the DWORD argument, executes
`CDQ; XOR EAX,EDX; SUB EAX,EDX`, and returns. It has no overflow branch or
trap. On `0x80000000` the returned DWORD is again `0x80000000`. The restored
unsigned subtraction defines exactly those low bits before the supported
two's-complement signed-32 conversion.

The focused fixture uses one real tile at column 0/row 0, giving center
`(35,57)`, and a complete bank-2/slot-1 sprite with width 0 and height
`-2147483591` (`0x80000039`). The already-restored DWORD Y subtraction produces
exactly `INT_MIN`. Original x86 stores rectangle `(0, INT_MIN, 0,
-2147483591)`, resets destination Y to 0, publishes destination `(35,0)` and
four lightning frames, and emits 79 ordered harness events.

The preceding native library happened to agree through its host libc call;
that observation did not define the C/C++ `abs(INT_MIN)` expression. The
restored native library agrees through explicit source arithmetic. The harness
compares complete state, buffers, queues, guarded allocations and ordered
events. It does not claim invalid tile state, arbitrary corrupted sprite data,
overlay rendering or physical-driver behavior. The X branch uses the same
observed original helper contract; its initialized board geometry cannot reach
`INT_MIN` with a signed 32-bit sprite width, so no artificial X reachability is
claimed.

## Complete compiler comparison and focused checks

One Visual C++ 4.0 display compile compares all 20 complete functions and 419
actual bindings. The two former `_abs` bindings are the only removed bindings.
All 19 companion code identities remain unchanged and all 16 exact functions
survive. Last-brick improves from 1,061 current bytes/992 strict differences to
1,047 current bytes/976 differences against the 1,057-byte original. No result
is masked or promoted to exact.

The current native core SHA-256 is
`63d4f3c64eadb51adc2f3200b971c77811635f80b99ab44c62f9ccce9a143c30`.
The incremental build recompiles `display.cpp`; it also recompiles byte-identical
`ui.c` because the rejected loop-spelling check immediately before this phase
touched and restored that file. No other source object recompiles. The new
INT_MIN fixture and all 197 existing last-brick countdown/crop cases pass; the
unchanged overlay entry is not run. No broader replay, game executable build or
game run follows.

Private authority is `.analysis/lightning-abs-wrap-20261020/`. It retains the
before/after witness receipts, full display comparison, actual mapped bindings,
existing-case receipt, adoption record and current authored-coverage audit.
