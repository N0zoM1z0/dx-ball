# Complete x87 exception bridge

The full pinned87except.obj section at0x0041CE10 is288 bytes:255 code, one
alignment byte and32 switch bytes. All fifteen original relocations and a full
REA byte read agree. The imported255-byte boundary omitted the switch tail and
is corrected through0x0041CF2F, without overlapping the next function.

The source preserves the actual cdecl operation/math-exception/control-word
pointer ABI. It maps error types to IEEE causes, normalizes type7 to1, delegates
result handling and prepares operand2 only for operations16/22/29. The transport
copies the original two DWORDs without an x87 value load, retaining binary64
payload bits. Raising may change the local control; restoration uses65535.
The actual shared matherr marker/callback and errno setter retain their priority.
No complete-record zeroing or invented default state is added.

The8-byte memcpy producer emits292/288/234. Explicit DWORD transport reaches
288/288/14; the write-phase trial worsens to22 and is reverted. Final inputs
equal the retained14-difference producer, so it is reused without recompiling.
All switch bytes match; only the operand-copy scheduling remains nonexact.

Current source420/exact310/code68,589/metadata136 and candidates101 (34 authored/
67 runtime). All310 prior exact and100 candidate producers retain their input
and object hashes;249 semantic rows are unchanged. Three focused VC4/native/
i686 source trials and full comparisons ran, with no runtime/game tests.
One closed three-record REA run and all unique trials remain private under
`.analysis/runtime-x87-bridge-20261014/`. Physical x87 control, dispatch candidates
and game integration remain open; this bridge is not claimed exact.
