# Rotation destination-offset arithmetic

October 20, 2026. Both destination pixel addresses in the rotated-sprite
renderer now form their row/column offset with explicit modulo-32 arithmetic:

```cpp
destination_desc.pixels +
    (DxBallInt)((DxBallUInt)row * destination_desc.pitch + rounded_x)
```

The final conversion is the signed 32-bit displacement used at the native
pointer boundary. The two expressions differ only in their `rounded_y` and
`truncated_y` row inputs. Source traversal, floating-point coordinates, guards,
pixel reads, two possible writes and DirectDraw calls remain unchanged. This is
a recovered operation contract; the original cast spelling is not claimed.

## Original operations and bounded witnesses

Retained complete REA Evidence
`ev_1dfa14e3428cac399a6bc2876da74d5bbc4a5edc8a8e03a6af79783e189daf26`
shows both original address producers. At `0x402B80` and `0x402BCD`, two-operand
`IMUL` keeps the low 32 bits of row times pitch. The following `ADD` at
`0x402B87` and `0x402BD4` adds the rounded X coordinate in the same 32-bit
domain. Only then does the code add the destination pixel base. No overflow
branch consumes the arithmetic flags.

Two finite fixtures use the real trigonometric initializer, typed surface
callbacks, a two-byte source with one visible pixel, and a guarded 96-byte
destination allocation:

- pitch `INT_MAX`, center `(16,3)`, width 32 and height 8 make the first
  row product and following addition wrap to displacement 15; both writes land
  at allocation offset 63;
- pitch `INT_MAX`, center `(INT_MAX-1,2)`, unsigned width `0x80000001` and
  height 8 make the column addition wrap to displacement -2; both writes land
  at allocation offset 46.

All floating-point-to-integer conversions are representable and all executed
addresses stay inside the one destination allocation. The second source row is
zero, avoiding an unrelated later conversion. Original x86 and the recovered
native library agree on the complete destination buffers, ordered descriptor,
lock and unlock events, source bytes, sprite records, banks and trig tables.
These fixtures do not claim arbitrary descriptor reachability, invalid
conversions, aliasing, concurrency or physical-driver behavior.

## Complete compiler comparison

The focused Visual C++ 4.0 comparison covers all five rotation-owner functions,
115 actual bindings and 25 full literal references. The renderer retains its
complete 1,458-byte relocated identity and remains a 1,572-byte/1,466-difference
candidate. Offset and width remain exact at 259 bytes each; height remains exact
at 191 bytes.

The source edit changes VC4's shared compiler context for the otherwise
unchanged Y-offset helper. It returns to the already recorded October 17
193-byte/191-byte, 159-difference identity with relocated SHA-256
`3cc171768e982bc7808e5b6e6784d007c3d07927881da0d2dfb04aa2b43cafad`.
That historical complete identity, all ten actual bindings and the full current
comparison agree. The helper is explicitly demoted; no old-object mix hides the
loss. Totals become 391 exact functions and 83,646 exact code bytes, including
246 authored exacts and 24 authored complete candidates.

The current exact object SHA-256 is
`9c06d52741c21cfb3583216185f650fd11d74ce984ceabd12560efbaf8c6f678`.
VC4 generated new internal literal suffixes, but all actual targets, addends,
payloads and multiplicities are checked. Three short serial owner compilations
were needed because the fail-closed comparator first exposed the literal-name
drift and then the Y-helper relocation/layout ripple; the third completed the
five-function report. No unrelated owner or full replay ran.

One native incremental build recompiles only `rotation.cpp` and relinks the
maintained products. Its core library SHA-256 is
`83f3c356335ebcf284a46d2db6e6d256eafe0372befdad9640f49f39a34d7266`.
The two new original/native fixtures pass. The one directly affected existing
rotation differential also passes all 1,024 renderer, wrapper and offset cases
and 151 complete guarded destination buffers. No broader replay, game executable
rebuild or game run follows this source checkpoint.

Private authority is `.analysis/rotation-destination-arithmetic-20261020/`.
Together with the preceding
`.analysis/rotation-destination-arithmetic-review-20261020/`, it retains the
source review, focused comparison, original/native receipts, targeted rotation
differential and current 270-entry authored coverage reconciliation.
Compiler/provider/game work was serialized under the project CPU and memory
limits; no provider query was needed.
