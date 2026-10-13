# C++ frame dispatch and catch transfer

The complete pinned frame.obj sections and five retained REA records establish
frame dispatch188, catch transfer148 and rethrow recognition44. Dispatch and
recognition match in full, including every actual relocation. Catch transfer
emits147 bytes with90 complete-span differences and remains a candidate.
The new44-byte entry at0x0041B930 lies between catch-block calling and object
construction; the provisional inventory previously omitted it.

Dispatch preserves magic validation, unwind flags0x66, state/nesting conditions,
newer-version throw-info forwarding and the low-byte recursive argument passed
to FindHandler. Rethrow recognition checks the actual code, parameter count3,
magic and null throw-info slot. Transfer conditionally constructs the catch
object, selects the marker frame, performs the genuine stdcall nested unwind,
unwinds to try_low, writes try_high+1, invokes the catch block with flag0x100 and
conditionally jumps to the returned continuation. State values come from valid
compiler metadata; no overflow, placeholder callback or transfer result is added.

The new owner consumes a real exception-record header and three native-width EH
information slots. Its first member is the previously consumed code prefix;
the original table owner remains unchanged. An initial shared-header expansion
lost the159-byte range exact and was rejected. The final dedicated record header
keeps all307 old exacts and98 candidates unchanged; retained canonical products
are reused only after verifying their actual input/object hashes.

Current totals:540 inventory,417 source,309 exact,68,512 code bytes,136 metadata
bytes and99 candidates (34 authored/65 runtime). All249 semantic rows are
unchanged. Focused VC4/native/i686 compilation and whole comparisons ran; no
runtime/game tests. The provider is closed, and unique failed/shared-header
trials plus the final objects and proofs remain private under
`.analysis/runtime-cpp-transfer-20261014/`. Full structured unwinding,
FindHandler, object construction, catch-block execution and integration remain
open genuine dependencies.
