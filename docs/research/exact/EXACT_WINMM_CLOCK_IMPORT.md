# Direct WinMM clock import and exact frame waiting

The shared clock callers now use the genuine `timeGetTime` function. Windows
imports its unsigned-long32, stdcall result from WinMM; the native host forwards
the same 32-bit interface through the existing live clock callback. The Windows
core DLL links `winmm`, alongside the executable's existing dependency.

This declaration context restores the last six comparison bytes in frame waiting
at `0x409610`: its complete **170-byte body and eight bindings are exact**.
The accepted total reaches **229 functions / 57,649 code bytes / 136 metadata
bytes**, leaving 44 authored candidates. The existing sampled-time/frame-index
cursor and both postincrement guards are unchanged. Original source spelling is
inferred; all emitted bytes are checked.

The original PE imports `WINMM.dll!timeGetTime` at IAT `0x4413A4`. Pinned VC4
`mmsystem.h:2084` declares `WINMMAPI DWORD WINAPI timeGetTime(void)`. Every emitted
`__imp__timeGetTime@0` binding is checked against that actual import. Kernel clock
boundaries retain their independently typed adapters. Native fixtures can still
replace `dxball_time_get_time`; the hosted function reads that cell on each call.

The three consuming recipes—runtime, display and startup—preserve all 26 prior
exact bodies. Paddle drawing now has the original 677-byte extent and 104 strict
differences, down from 678/494; it remains a candidate. Last-brick keeps 1067/1057
bytes and 992 differences. Its explicit start-time sample preserves time before
RNG across compilers. A combined-expression diagnostic reverses that order and
is rejected. The tested `register` hint does not remove its frame slot under the
pinned recipe. A local rectangle initializer gives no benefit and is reverted.

Three display stages, one runtime and one startup compilation are retained.
The final import declaration uses the actual Windows ABI and a fixed 32-bit
native interface. Earlier alias/register stages lose
an accepted blit despite making additional candidates exact; they are rejected.
Both actual game transports, `platform_host.c` and `windows_adapter.c`, compile
once. VC4 links three matching objects, two rebuilt transports and 32 verified
unchanged objects. Linux and MinGW builds pass, including the DLL's new dependency.

One unchanged fixture selection passes 1,186 calls: 216 current-clock, 252 elapsed,
332 paddle, 18 waiting, 197 countdown/crop, 162 paired overlays, one reset prelude
and eight clock-seeded original CRT-state checks. Full state, buffers, queues and
ordered calls compare. All 229 accepted code/literal/metadata closures verify;
249 historical input inventories refresh without unrelated fixture replays.
No game runs. Private receipts are in `.analysis/direct-winmm-import-20261012/`.

The complete saved waiting dossier is Evidence
`ev_86e83ae4d777813cd233a8b5c9d0f3ccf67349f7605b270938902c442f023087`,
operation 10 of closed run `2026-10-07T09-29-28.570Z-interactive-2776129`.
Its countdown dossier, operation 00, is Evidence
`ev_f8610be2baa2323aec8fcd14317794aebe74eefa78b4d66c9cf874ca117eb5bc`.
No new provider query is needed.

## Closed clock implementation owner, October18

One fixed private model groups the three adjacent original entries: current time
at403450, elapsed time at4034F0 and clock detection at403550. Detection writes the
high-resolution selection read by sampling; elapsed calls sampling. Move their
unchanged bodies and the existing clock state to one C++ owner, retaining full
runtime/platform/clock headers, C linkage and `/MT`. The hosted callback table
is necessary integration state, not evidence of an original translation unit.

Three serial compiles compare all27 affected functions with777 actual bindings,
74 complete literal references and60 same-section local-target checks. All24
prior exacts retain8,323 bytes;26 full code identities remain unchanged. Elapsed
stays81/3 and reset426/20. Only paddle changes,677/68→678/210: two instructions
exchange the local/global right-edge operands and add one byte. Its other183
instructions and frame homes agree. Reject the complete model without variants.

Independent review checks full relocated bodies, unchanged residual owners and
the moved external-C BSS objects' widths/zero initialization. Canonical source,
products, ledgers and delivery remain unchanged at394 exacts/21 authored
candidates. Private `.analysis/clock-family-owner-20261018/` retains sealed
comparisons and reviews. Archive/member-hash verification precedes removal of
36 raw inputs/products, including five objects, releasing212 KiB net of archive
and journal. Scope peak257,736,704 bytes; the one-CPU/35%/640–768 MiB limits hold
with zero high/max/OOM events. No native build, relink, provider query, runtime
case, game or full replay follows.
