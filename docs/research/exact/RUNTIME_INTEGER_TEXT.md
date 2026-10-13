# CRT integer text conversion

All three integer-formatting bodies now have shared typed source. Both entry
wrappers are complete exacts across90 bytes and three actual call relocations.

| Entry | Original/current bytes | Differences |
| --- | ---: | ---: |
| `_itoa`, `0x41F4D0` | 60/60 | 0 |
| Static `xtoa`, `0x41F510` | 96/96 | 2 |
| `_ultoa`, `0x41F570` | 30/30 | 0 |

Only negative decimal inputs request a minus sign. The helper negates the
unsigned32 bit pattern, avoiding signed INT_MIN overflow. It retains both
observed unsigned divisions, lowercase digits, mandatory zero digit, NUL store
and the original at-least-once reversal, including single-character writes.
The Win32 unsigned-long ABI remains32 bits on native hosts; buffers keep native
pointer width. Backed output and valid radix2–36 are required; no new radix
validation, host-formatting shortcut or guessed array capacity is introduced.

The first pointer-cursor translation matches all186 original bytes, but the
last single-character swap decrements a pointer before the backing array.
The maintained version uses address cursors for reversal: only live positions
are converted for byte accesses, and the terminal address is never dereferenced.
This retains96 bytes and all original operations. Two comparison-direction
bytes differ; that helper is not exact. Mixed pointer/address and paired-address
models have the same two differences. No unsafe first-pass match is accepted.
The helper stays private; VC4 COFF storage class3 confirms its internal symbol.

Existing REA dossiers `ev_ae3a244793f13621a162cda74914dec8c6030edc2382ca7fa8cf1c7e5fc2decb`
and `ev_16217354766a89a301447e87d1396fc7f6bd91da34cd7b14476c9618f48377f6`
supply complete helper/unsigned-entry instructions. Only the missing signed
entry needs the new closed three-record run
`2026-10-13T15-51-45.061Z-interactive-1795134`; assembly:
`ev_131f98a51e030a426a224fd143ab3e7c2d1664c0c60e00e9fe5a1c6620c70924`.
All three complete pinned CRT sections independently match the original.
Private proof and seal: `.analysis/runtime-integer-text-20261013/verification.json`.

Source343/exact265/64,747 code bytes; metadata136 unchanged. All263 prior
exact results and68 candidates retain unchanged inputs/products/results.
Candidates69:34 authored/35 runtime. Three complete final comparisons and
native/i686 standalone compilation cover this new owner; no runtime tests or
game builds. The existing score owner still uses its prior CRT boundary;
broader runtime/game integration remains open.
