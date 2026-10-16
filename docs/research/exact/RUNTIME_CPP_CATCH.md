# C++ catch-block invocation and cleanup

`src/runtime_cpp_catch.cpp` restores the complete catch-block wrapper at
`0x0041B820`. Its **272 code bytes and 24 scope bytes match exactly**, after
all 17 code and three scope relocations. The previous 213-byte imported extent
ended before the rethrow filter, handler, local unwind and final return. The
correct inclusive end is `0x0041B92F`, immediately before the existing rethrow
filter at `0x0041B930`.

One stable canonical VC4 compilation supplies this result. The same source
also passes Clang's i686 MSVC C++98 compilation with warnings as errors. It
uses genuine Win32 SEH and remains a standalone CRT owner outside the CMake
game library. No runtime check was run for this owner.

## State, scope and return value

The compiler's saved stack slot lies immediately before the registration.
A typed prefix and `offsetof` recover that real field; no frame padding is
added. Save its value, plus the previous current-exception and current-context
pointers. Set both globals to the incoming exception/context before entering
the protected call.

Seed the continuation value with the actual incoming handler address, then
replace it with the return from the original `_CallCatchBlock2` transport.
This preserves the nonnull value visible to cleanup if the transport exits
abnormally before assigning its result. The existing exact rethrow filter
receives the compiler's real `_exception_info()`. When it handles a rethrow,
clear the continuation and return null through the outer finally scope.

The finally body first restores the saved stack slot and both globals. For a
C++ exception with parameter count three and magic `0x19930520`, a nonnull
continuation triggers the restored object destructor. Pass the compiler's
`_abnormal_termination()` result as the original byte flag. A cleared
continuation skips destruction on rethrow. The complete function returns the
continuation on its normal exit.

Ghidra's partial procedure view declares a void return and omits both the
rethrow path and final return. That is a provider coverage/type limitation.
The complete original section and the actual catch-transfer caller, which
tests EAX and conditionally jumps to it, establish the pointer return contract.
Retained caller assembly:
`ev_422051616475627e1688206ffa76240663e159f07e5243bee1e1c0085ff3738d`.

The original C++ catch transport consumes opaque code and metadata addresses.
Forward declarations of its original CRT struct tags preserve the actual
mangled symbol and calling convention. The maintained wrapper calls it
directly; no replacement transport implementation or fake return is supplied.
Its low-level body remains a source gap.

## Initialized current exception state

This owner defines `dxball_cpp_current_exception` and
`dxball_cpp_current_context`, already declared and consumed by handler search.
Their full maintained eight-byte initialized section has no relocations and
matches zero state at `0x00423894` and `0x00423898`. The corresponding two fields
of the pinned original `frame.obj` also agree. The unrelated preceding original
unhandled-filter field is outside this ownership claim. These eight bytes are
recorded separately; the accepted metadata-byte gain is the 24-byte scope table.

## Complete original evidence

REA 6.5.0 / Ghidra 12.1.4 evidence:

- Pseudocode:
  `ev_d8f7e95fa4efb93e3bac0bba3d19f1244f4e931f21b2d4052cf77ff03b47e828`.
- Assembly:
  `ev_c1e027c8e339f79e88490082a466e95b86014f9dfab2f51243dff1400d8d194b`.
- All 272 code bytes:
  `ev_1c62825bded91588fdc8d78e45d79782ab40b5c75795b2153599b2640e5499ab`.
- All 24 scope bytes at `0x004201B0`:
  `ev_e12aad7e459b3a6d21c9e9cab6de0d548daae939985e2bf429852d0a197838d9`.
- Both current-state pointers:
  `ev_9d879b14fecfa7cbdaa0816924e18f643c971eaedf31841550859b8925004dba`.

Responses are in `.analysis/rea/runs/2026-10-16T05-05-58.940Z-requests-117843/`.
The complete pinned `frame.obj`, SHA-256
`ca4c0732d0860a9f0dbc519f91888999cccb47dc96c99b35572057193dfd462b`,
independently matches all code/scope bytes with explicit relocation bindings.
Private proof and compiler receipts:
`.analysis/cpp-catch-block-source-20261016/{complete-comparison,compile,canonical-comparison,adoption}.json`.

## Checkpoint and limits

Tracking is **543 inventory / 463 source-present / 372 exact**, with
**76,452 exact code bytes / 232 attached metadata bytes**. The 88 complete
nonexact candidates, three separate allocator comparison gaps and 249
historical semantic rows are unchanged. Another 80 inventory entries lack a
source row. Origins are 270 authored, 211 runtime, 45 compiler-generated and
17 unknown.

The preceding 371 exact and 88 candidate producers were retained after
verifying unchanged recipes, complete inputs, flags and actual object hashes;
they were not recompiled. The provider closed normally. Compiler/provider
commands ran serially with CPUQuota 35%, MemoryHigh 640 MiB, MemoryMax 768 MiB
and a 256 MiB Ghidra heap. A retained kernel sample confirms these limits and
no OOM. Frame-setting/catch transports, guard callbacks, remaining runtime
integration and the final restored-game build/play check remain open.
