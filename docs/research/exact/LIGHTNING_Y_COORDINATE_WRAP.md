# Last-brick destination Y arithmetic

October 19, 2026. The last-brick routine now preserves the consumed DWORD
subtraction before storing its signed destination Y:

```cpp
y = (DxBallInt)((DxBallUInt)center_y
              - (DxBallUInt)dxball_sprite_banks[dxball_sprite_bank].sprites[1]->height);
```

Only this expression changes. The signed height field, live bank/slot lookup,
clipping branches, `abs` call, crop producers and subsequent state writes remain.
This restores an observed operation without claiming original cast spelling.

## Original producer and finite witness

Retained REA Evidence
`ev_f8610be2baa2323aec8fcd14317794aebe74eefa78b4d66c9cf874ca117eb5bc`
contains the complete 1,057-byte original routine. At `0x4161A2`, `2B410C`
subtracts sprite height from EAX; `0x4161A5` stores the DWORD at EBP-0x28.
The signed negative test at `0x416261`, actual `abs` call at `0x41626F`,
rectangle-top store and Y reset consume that result. Six instruction encodings
are checked directly against the pinned original PE. No new provider query runs.

The [glyph-coordinate evidence](GLYPH_COORDINATE_WRAP.md) already establishes
that a finite 17-byte bank prefix can publish width zero and height `INT_MIN`
when CreateSurface fails. Its low32 bitmap product is zero; failure precedes
the row loop. This is retained input provenance, not a newly executed loader test.

The focused witness supplies those dimensions in a complete typed bank2/slot1
record and one real tile at column0/row0. The center is (35,57). Original DWORD
subtraction produces -2147483591, so the routine stores rectangle top2147483591,
sets Y to0 and retains bottom `INT_MIN`. It publishes destination (35,0) and
four lightning frames. The existing harness compares complete state, buffers,
queues, guarded allocations and all79 ordered boundary events with the original.
No overlay draw or rasterization follows.

The old display source fails signed-overflow instrumentation at `57 - INT_MIN`.
The restored source passes the same witness. The actual `abs` argument in this
case is representable; this does not close `abs(INT_MIN)`, every exceptional
arithmetic path, arbitrary aliasing or physical-driver behavior.

## Complete comparison and focused checks

One VC4 display compile compares all20 complete functions and421 actual
bindings. Every raw body, resolved body and actual binding retains its prior
identity. All16 exact companions survive; last-brick remains1061 current bytes
against1057 original bytes, with992 strict differing positions. The manifest,
targets, extents, flags, relocation recipes and membership remain unchanged.
Totals stay393 exact functions and248 exact/22 candidate authored functions.

Two display-only instrumented compilations reuse every other native object.
The canonical native build then recompiles only display and links once, taking
1.989s. Its library SHA-256 is
`e980f545aca7e5019c46a4914caca066bd4d9eab5fa6ad52fe04950f39b080a0`.
The canonical library passes the same finite witness and197 unchanged existing
countdown/crop cases. The unchanged overlay entry is not rerun. Historical
semantic case counts/scopes remain fixed; only current input identities refresh.
All270 authored source/object/comparison receipts across30 closures verify.

Compiler and native processes use CPU0/35%,384MiB high/512MiB max. The VC4
comparison takes10.606s, peak166,608,896 bytes; instrumented work takes4.007s,
peak57,544,704 bytes; canonical checks take15.520s, peak50,987,008 bytes.
All report zero high/max/OOM events. There is no full replay, game rebuild or
game run at this source checkpoint.

Private authority: `.analysis/lightning-y-wrap-20261019/`, including the question,
original-byte checks, complete comparison, root review, instrumented failure and
success, canonical check, adoption and authored-coverage receipts. The review
is by the root agent, not independent. Closed copies, temporary products and
executed helpers are archived and member-size/SHA verified before removal;
current products, valid caches and unique evidence remain.

Cleanup member-verifies57 files in a1,303,455-byte archive before exact-list
removal, releasing7,733,248 allocated bytes net before small receipts. All925
protected file identities survive; the failed-play evidence remains untouched.
