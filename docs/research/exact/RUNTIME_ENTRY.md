# Original WinMain CRT startup

`src/runtime_entry.c` restores `WinMainCRTStartup` at `0x004187A0` as natural
C with genuine Win32 SEH. One canonical VC4 compilation matches its complete
**390 code bytes and 12 scope bytes**, including all 34 code and two scope
relocations. The same source passes Clang's i686 MSVC C99 compilation.
This standalone owner is outside the CMake game library; it is not yet the
entry point of a verified complete restored-game build.

The [subsequent heap-boundary repair](../WINDOWS_HEAP_STARTUP.md) supplies real
Win32 default callbacks before game binding and preserves a heap initialized
before the host WinMain wrapper. It prepares the pre-entry allocation contract;
it does not integrate or execute this complete startup owner.

## Initialization and the game call

Read the full `GetVersion()` result, derive the original unsigned major/minor,
combined version and build fields, then initialize the private heap. Preserve
the ignored heap return. Those operations precede the protected scope.

Inside the scope, initialize low I/O and the multibyte table; obtain command
line and environment storage; exit with status `-1` if either is null. Run the
existing argument, environment and C initialization owners in their original
order. The existing argument-state owner still defines `_aenvptr`; no duplicate
state is introduced. This owner supplies the four initialized version fields
and the original uninitialized command-line pointer `_acmdln`.

Skip the executable token using the original quoted/unquoted scan. In a quoted
token, a recognized DBCS lead byte advances over its following byte. Then skip
nonzero whitespace bytes through space. Preserve the original string/backing
contract, without extra input guards or different escape parsing.

Use the shared 68-byte Win32 `DxBallCrtStartupInfo` type. Clear its flags before
`GetStartupInfoA`, then select the returned unsigned short show value when bit
1 is set, or the original default value 10. Invoke the genuine maintained game
WinMain API with module handle, null previous instance, remaining command line
and show value. Pass its result to the existing normal exit owner. The filter
uses the actual compiler exception code/information and the restored CRT
exception filter; its handler uses the existing quick-exit owner.

The source shares existing allocator, argument, environment, initialization,
platform and exception APIs. It adds no host fallback, replacement main, copied
code bytes, assembly, frame padding or artificial locals.

## GUI error-mode producer

The original `wincrt0.obj` initializes application type at `0x00423118` to
**2 (GUI)**. `runtime_fatal.c` previously left this field zero-initialized.
That omitted producer state would affect default fatal-message routing when
error mode is zero. Its definition now initializes to 2; no executable write
was inserted into startup.

The changed fatal owner was compiled once with its existing recipe. Both
accepted exact bodies, fatal exit (42 bytes) and banner (61 bytes), retain
identical complete comparison results. Error formatting remains 493/494 bytes
with 412 differing positions. All 136 catalog bytes and every complete pointed
to string are unchanged. The four-byte application-type initializer matches
both the full original producer field and the verified executable.

The startup owner's complete 16-byte initialized version storage matches the
corresponding `crt0dat.obj` fields and original bytes at `0x004230B8`. These data
claims are recorded separately from the 12-byte scope metadata gain. `_acmdln`
is a four-byte common definition in the original ABI; it is populated by the
real command-line import before argument processing.

## Complete evidence and validation

REA 6.5.0 / Ghidra 12.1.4 evidence:

- Pseudocode:
  `ev_82d5afb1c64ec81842e3852acadebf19ce1d35cffa2e3346ca684ba7c4db8551`.
- Assembly:
  `ev_23405af9219f09ff1db213e298ce53efc4d4f7a64c8f2a4455125d1a2c11da7f`.
- All 390 code bytes:
  `ev_04a70593d1fc3d7c3fe06b103084423cc9d4f7b7429fe2002ef260be1fce411f`.
- All 12 scope bytes at `0x00420128`:
  `ev_922d290e19de2d38525e82a3e2c401ec47e0f7827dbf2eb9d0c21721273b2807`.
- All 16 version-state bytes:
  `ev_0d31750c234dd6617d05474dd5e54d9814286b6ea945b8b8c94e6462a76268aa`.

Full responses are in `.analysis/rea/runs/2026-10-16T05-18-45.609Z-requests-134800/`.
Both the complete original `wincrt0.obj` section and maintained code/scope match
the verified target. Each actual binding is explicit, including the byte read
with addend 1 from `_osver`. `crt0.c` shipped with VC4 corroborates the original
producer language, call order, DBCS scan and GUI application-type initializer.
`wincrt0.obj` and `crt0dat.obj` were extracted from the pinned library. Their
SHA-256 values are `65e6ef43c43aa3bc17295bbd3b004a76c4ef507ab226834add259d3d60df578a` and
`39f0367c946b5ee25bc877c0115457d8ac0b91d0b509873bff1f3d1beb09294b`, respectively.
Their identities and full comparisons are in
`.analysis/crt-entry-source-20261016/complete-comparison.json`.

The stable entry and changed fatal owner each have one canonical VC4
compilation. The other 370 exact and 87 candidate producers are reused only
after checking unchanged recipes, full input closures, flags and actual object
hashes. All 30 recursively included project inputs are bound for startup.
Both changed sources also compile with Clang Win32 C99 and warnings as errors.
The existing board-layout assertion needs `-Wno-gnu-folding-constant` with the
old SDK's `offsetof` macro; its initial diagnostic is retained. The source and
layout assertion are unchanged by that compatibility option.

No runtime, game build or campaign was run for this adoption. Compiler/provider
commands ran serially under CPUQuota 35%, MemoryHigh 640 MiB and MemoryMax
768 MiB; Ghidra used a 256 MiB heap and the provider closed normally.
Compiler receipts, complete comparisons and adoption proof remain in
`.analysis/crt-entry-source-20261016/`.

Current totals are **544 inventory / 464 source-present / 373 exact**,
**76,842 exact code bytes / 244 attached metadata bytes**. There are 88 complete
nonexact candidates, three separate allocator comparison gaps and 249
historical semantic rows. Another 80 entries lack source rows. Origins are
270 authored, 214 runtime, 45 compiler-generated and 15 unknown. Low-level
runtime/compiler bodies and full reconstructed CRT/game integration remain open.
