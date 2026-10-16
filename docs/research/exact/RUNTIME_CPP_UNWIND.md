# C++ frame unwinding to a state

`src/runtime_cpp_unwind.cpp` restores `__FrameUnwindToState` at `0x0041B690`.
One canonical VC4 compilation matches the complete **206-byte body and
12-byte scope table**, including all nine code and two scope relocations.
The unchanged source also compiles as C++98 with Clang's i686 MSVC target and
warnings as errors. It requires Win32 SEH and remains outside the CMake game
library. No new runtime test was run for this owner.

## State and lifetime

The function keeps a reference to the registration's state field and a local
current state. While that local differs from the requested state, validate its
signed index against zero and `max_state`. Invalid indices call the genuine
inconsistency owner before entering the protected action scope.

An unwind entry contains a signed `to_state` and a function pointer. A nonnull
action is invoked through the original stdcall `_CallSettingFrame` transport,
with the actual registration and flag `0x103`. The action executes in the
protected scope. Its exception filter receives the compiler's real
`_exception_info()` value and calls the existing exact
`dxball_cpp_frame_unwind_filter`: a C++ exception terminates, while other
exceptions continue searching. The handler body is empty, as in the complete
original scope. No substitute transport or fabricated exception record is added.

After the action scope, reload the unwind map and advance the local state to
`to_state`. Preserve the original final consistency check, then commit the
local state through the registration reference. The registration is not written
at each step. The unused dispatcher argument remains in its original ABI slot.
The new typed unwind-entry view leaves all preceding metadata owners unchanged.

The maintained source uses actual C++ references and SEH language constructs.
It contains no copied code bytes, assembly, padding, fake locals or alternate
compiler bodies. The compiler and CRT supply exception registration and
frame-setting mechanics.

## Complete evidence

REA **6.5.0**, Ghidra 12.1.4, read the original without executing it:

- Pseudocode:
  `ev_84c3606b512d7eaadd1a049ae8e1e24b4f85688ce3aac74f092b421da91596c2`.
- Assembly:
  `ev_f169e7cedaf8953e13d9654e0dc30010d5278acd0a2538e5ff18630639a2564d`.
- All 206 code bytes:
  `ev_758f7e638b2cd22e57e3e1266fda2228f9c975455f4ee3edae875d65fd7f4691`.
- All 12 scope bytes at `0x004201A0`:
  `ev_ed47bedc737a8a5920ca67614aafb5ed0740a92d2b545250a3611ee4118e560a`.

Full responses are retained in
`.analysis/rea/runs/2026-10-16T04-56-13.333Z-requests-104325/`.
Procedure listings omit the filter and handler blocks, so their absence from
pseudocode does not establish a missing scope. The complete read and pinned
`frame.obj` section cover both blocks and the final return. The scope's filter
and handler entries are `0x0041B70E` and `0x0041B71B`.

The pinned original member SHA-256 is
`ca4c0732d0860a9f0dbc519f91888999cccb47dc96c99b35572057193dfd462b`.
Both its complete section and the maintained object match the verified target,
with explicit bindings to inconsistency, frame-setting transport, the existing
filter, SEH support and the scope table. Private proof and compiler receipts:
`.analysis/cpp-frame-unwind-source-20261016/{complete-comparison,compile,canonical-comparison,adoption}.json`.

## Checkpoint and remaining work

Tracking now has **543 inventory entries / 462 source-present / 371 exact**,
with **76,180 exact code bytes / 208 attached metadata bytes**. The 88 complete
candidates, three separate allocator comparison gaps and 249 historical
semantic rows remain. Another 81 inventory entries lack a source row. Origins
are 270 authored, 210 runtime, 45 compiler-generated and 18 unknown.

The preceding 370 exact and 88 candidate producers are reused after checking
unchanged recipes, complete input hashes, flags and actual object hashes;
they were not recompiled. Only this stable owner was compiled with VC4 and
Clang. The provider closed and saved normally. Heavy commands ran serially
with CPUQuota 35%, MemoryHigh 640 MiB and MemoryMax 768 MiB; Ghidra used a
256 MiB heap. A retained kernel sample confirms these limits and no OOM.

This closes the source gap used by frame dispatch and catch transfer. The
frame-setting transport still has no maintained body; catch-block execution,
remaining transfer helpers and complete dispatcher/game integration remain
open. Complete byte agreement does not establish final game playability.
