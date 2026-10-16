# C++ frame dispatch and catch transfer

October 16 object follow-up: [construction and destruction](RUNTIME_CPP_OBJECT.md)
now have complete source, with destruction exact and construction a four-byte
nonexact candidate. Earlier checkpoint totals below remain historical.

The complete pinned frame.obj sections and five retained REA records establish
frame dispatch188, catch transfer148 and rethrow recognition44. Dispatch and
recognition match in full, including every actual relocation. Catch transfer
now matches all148 bytes and its five actual relocations.
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

The later catch-transfer checkpoint restores the original conditional argument
transport: default registration first, nonnull marker second, one merged
stdcall unwind call. The earlier ternary materializes a merged EAX value and
emits147/148/90. Explicit marker-first branches give148/148/3; the observed
default-first order gives148/148/0. No argument, storage, call or state write is
added. Both188-byte and44-byte owner exacts remain unchanged. Whole pinned
frame.obj and retained REA `ev_422051616475627e1688206ffa76240663e159f07e5243bee1e1c0085ff3738d`
provide complete original boundaries and all five bindings.

Two VC4/native/i686 compilation sets and full owner comparisons; no runtime
tests or provider session. All336 old exacts,112 other candidates and249
semantic rows remain. Totals543 inventory/457 source/337 exact/69,994 code
bytes/136 metadata/112 candidates. This does not close structured unwinding or
game/runtime integration. Receipt:
`.analysis/cpp-marker-argument-branches-20261014/verification.json`.
