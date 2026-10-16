# C++ exception object construction and destruction

Later October 16 follow-up: [frame unwinding](RUNTIME_CPP_UNWIND.md) is now
restored and exact. Checkpoint totals below describe this object-source adoption.

The restored owner is `src/runtime_cpp_object.cpp`, with genuine Win32
`__try`/`__except` source. VC4 produces the complete 113-byte destruction
function and its 12-byte scope table exactly. Construction produces all 510
bytes with four register-encoding differences; its 12-byte table is exact.
Both functions remain standalone CRT owners outside the CMake game library.

| Original entry | Complete code | Code differences | Attached scope | Status |
| --- | ---: | ---: | ---: | --- |
| BuildCatchObject, `0x0041B960` | 510 | 4 | 12 bytes, exact | Complete candidate |
| DestructExceptionObject, `0x0041BB60` | 113 | 0 | 12 bytes, exact | Accepted exact |

The checkpoint totals are 543 inventory entries, 461 source-present entries,
370 accepted exacts, 75,974 exact code bytes and 196 attached metadata bytes.
There are 88 complete nonexact candidates and three other source-present
allocator gaps. Another 82 inventory entries lack a source row. Origin counts
are 270 authored, 209 runtime, 45 compiler-generated and 19 unknown. The
historical 249 semantic rows are unchanged.

## Recovered contracts

The construction destination is the registration address plus the registration
size and signed catch displacement. A null type, empty type name or zero catch
displacement bypasses construction. Catchable metadata extends the existing
properties/type prefix with the three signed PMD fields, object size and copy
constructor address; no frame padding or invented state is added.

Handler bit 8 selects reference construction: validate, store the thrown object
pointer, then store its PMD-adjusted value. Catchable bit 1 selects a simple
copy. A pointer-sized nonnull result receives pointer adjustment; a null result
bypasses it. Without a copy constructor, move the declared size from the adjusted
source. Otherwise validate the executable constructor and call its real member
ABI. Catchable bit 4 adds the final virtual-base argument with value 1.

Read and write validation retain the original length **1**, including paths
which subsequently copy more bytes. Failed validation calls the genuine
inconsistency owner. The protected body catches faults with a constant-one
filter and calls the genuine terminate owner. Initial metadata guards and
frame-address calculation remain outside that scope.

Destruction bypasses a null exception or null destructor. Its protected member
call uses the original object and destructor addresses. The unsigned byte
`throw_not_allowed` becomes a Boolean filter: zero continues exception search,
and every nonzero value catches and terminates. The generated filter and
handler are part of the complete comparison, although the retained provider
procedure listings omit those blocks.

The four construction differences at offsets 63, 66, 74 and 78 exchange EAX
and ECX when loading/testing catch displacement and forming the destination.
All remaining code positions agree after relocation. No name, declaration,
type or register-spelling sweep was used to eliminate these equivalent choices.

## Original producer and evidence

Complete `frame.obj` from the pinned VC4 `libc.lib` matches both original code
sections and scope tables after all **32 code and four scope relocations**.
The original member SHA-256 is
`ca4c0732d0860a9f0dbc519f91888999cccb47dc96c99b35572057193dfd462b`.
The private complete proof is
`.analysis/cpp-exception-object-source-20261016/complete-comparison.json`.
`config/match-units.toml` records every maintained relocation and both complete
scope tables at `0x004201C8` and `0x004201D8`. The memmove binding is the actual
`0x00416610` entry, not the separate memory-copy owner.

Retained REA 6.4 evidence remains identified as 6.4:

- Construction pseudocode:
  `ev_233acc017ca6909591ba84f4f7718e79eb80f789c8b1851a1d93ba5e6d0ed176`.
- Construction assembly:
  `ev_6c03116da19af1710c6392a3ab9e6d61b410e90e351f7bedf9808ee5ec864b58`.
- Destruction assembly:
  `ev_d255dfe534c4690060a83bc274407fdfc544fccd9fb3bd9d33dac6fa20a71837`.
- Complete 625-byte enclosing read:
  `ev_4235cebca7f829f90678f802a5d958549ec066d16553f98319882d7dc8b93341`.

These are in `.analysis/rea/runs/2026-10-16T04-18-41.755Z-requests-60444/`.
The fresh REA **6.5.0** read independently confirms both scope tables and the
four intervening padding bytes:
`ev_ad8b7d65b442e9a523841c43f495ec948be8f44624cf7d644cfa9c818756eb1c`.
See [REA configuration and upgrade proof](../../agent/REA.md).

## Actual member-call transport

The three entries at `0x004184E0`, `0x004184F0` and `0x00418500` are the original
`_CallMemberFunction0/1/2` stdcall-to-thiscall trampolines. Each complete seven-byte
section matches pinned `trnsctrl.obj`. They move the object to ECX, arrange the
return/argument stack and jump to the member address. Their identical bytes
alone do not distinguish names: actual caller arity and the shipped C++
stdcall declarations establish each contract. The maintained header retains
those declarations with opaque code addresses; no replacement thunk body is
introduced. Their origins are classified as runtime, with source recovery open.

The complete member comparison is `member-call-provenance.json` in the private
phase directory. REA assembly IDs, in address order:
`ev_9554d6425abb2bf0af02f3f70295dd3ef28680df23c302182d2c2a101558a06d`,
`ev_7a6ecb0fd8d57961c646fb0702fc5f096898490de4d7b729f91ca8b8062a5167`,
`ev_1c0ff3b374b6ce4bf4babc9db7281ffbed34f8f99d3bf1428bd49fd683ecd008`.

## Validation and limits

One stable VC4 compilation supplies both whole-function comparisons. The same
maintained source also compiles with Clang's i686 MSVC target, C++98 and warnings
as errors, using the shipped VC4 SDK headers. The prior 369 exacts and 87
candidates are reused after checking unchanged recipes, full input hashes,
flags and actual object hashes; they were not recompiled.

Twelve bounded Wine cases pass: construction bypass, adjusted reference,
nonnull/null simple pointers, adjusted raw copy, real thiscall copy with one
or two arguments, invalid-read inconsistency, constructor fault, destruction
bypass/success, propagation with flag zero, and termination with flags 1/255.
They execute the maintained object and terminal owners, pinned CRT member
trampolines, validators and SEH runtime. The abort boundary records events and
exits with a controlled code. Pointer adjustment is an unchanged source extract
from the existing exact helper; the full table owner is not linked. A failed
attempt to call its private original CRT symbol and an unrelated full-owner
link failure are retained, rather than adding fake dependencies.

`canonical-comparison.json` retains the original compiler receipt, before
construction was moved into the candidate category. `current-comparison.json`
records the final manifest reader result. `runtime.json`, `adoption.json` and
compiler/link logs retain the actual products and inputs. Clang's initial
missing target-header failure is retained separately. Heavy commands ran
serially with CPUQuota 35%, MemoryHigh 640 MiB and MemoryMax 768 MiB.

These checks do not establish native Windows behavior or a final restored-game
build. Remaining transfer helpers and dispatcher integration
remain open; construction still has four compiler register differences.
