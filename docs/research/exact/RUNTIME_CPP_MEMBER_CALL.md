# C++ member-call bridges

The three original stdcall-to-thiscall entries now have C++ implementations in
`src/runtime_cpp_member_call.cpp`. They preserve the direct member-call API and
remain nonexact: the original rearranges the caller's stack and jumps, whereas
the compiler-generated C++ implementation introduces a call frame.

| Entry | Address | Original bytes | VC4 bytes | Differing positions |
| --- | --- | ---: | ---: | ---: |
| `_CallMemberFunction0` | `0x004184E0` | 7 | 37 | 37 |
| `_CallMemberFunction1` | `0x004184F0` | 7 | 42 | 42 |
| `_CallMemberFunction2` | `0x00418500` | 7 | 47 | 47 |

Each original body pops the return address and object, exchanges the method
address with the return slot, then jumps to the method. This puts the object
in ECX and leaves zero, one or two genuine arguments for the thiscall callee.
The original caller's stdcall cleanup is completed by that callee. Identical
seven-byte sections alone do not distinguish the names; the shipped
`trnsctrl.h` declarations and actual construction/destruction callers establish
the three arities.

## Typed implementation and limits

VC4 rejects an explicit `__thiscall` function-pointer type with C4234, reporting
that the keyword is reserved for future use. The maintained implementation uses
the compiler's actual C++ member-function pointer types instead. A complete
opaque class supplies the single-inheritance call convention; the original
caller has already adjusted the object address. Static assertions require
32-bit pointers and a direct, pointer-sized representation for every arity.
The opaque code address is copied into that representation with the maintained
`dxball_crt_memcpy`, then invoked with the actual typed arguments. No extra
register parameter, active-union pun, assembly or copied instruction body is used.

The same source compiles with VC4 and Clang's i686 MSVC target in C++98 mode.
This is specifically the Microsoft x86 direct-method representation; no native
Itanium member-pointer or general inheritance-descriptor conversion is claimed.
The original public declarations and existing consumer inputs stay unchanged.

The extra C++ frame changes the member's immediate return address and stack
depth. These differences are observed explicitly and remain open machine
transport differences. The source claim covers ordinary direct-method calls:
ECX, arguments, one invocation, object effects, void return and callee cleanup.
It does not establish identity for callbacks inspecting their callers' stack.

## Whole original evidence

All three complete relocation-free sections match pinned `trnsctrl.obj`,
SHA-256 `206b02d6136285da3400a3bd57538a7ca3bee816d979cdd51753322d6ed350ce`.
The retained proof is
`.analysis/cpp-exception-object-source-20261016/member-call-provenance.json`;
the current proof rechecks its member identity and all three target spans.
Retained REA assembly Evidence IDs, in address order:

- `ev_9554d6425abb2bf0af02f3f70295dd3ef28680df23c302182d2c2a101558a06d`.
- `ev_7a6ecb0fd8d57961c646fb0702fc5f096898490de4d7b729f91ca8b8062a5167`.
- `ev_1c0ff3b374b6ce4bf4babc9db7281ffbed34f8f99d3bf1428bd49fd683ecd008`.

The original callers and full member proof are described in
[exception object construction/destruction](RUNTIME_CPP_OBJECT.md).
No new provider query or REA upgrade was needed; the project remains pinned
to REA 6.5.0.

## Focused validation

One stable production compilation per VC4 and Clang MSVC-target profile checks
all three bodies. Complete comparison resolves the single actual memcpy binding
in each VC4 body. The recovered memcpy object is reused by complete input,
flags and object identity.

An emulated comparison executes the original seven-byte entries, VC4 C++ and
Clang C++ against actual VC4-compiled thiscall methods. All 784 logical cases
pass: 16 zero-argument, 96 one-argument and 672 two-argument cases. Cases vary
object placement/value, null and opaque pointer arguments, and signed integer
extremes. Checks include ECX, every stack argument, a single method invocation,
stdcall cleanup, saved registers, DF0, full guarded object bytes, and writes
restricted to the stack/object arena. The member return-address difference is
also checked rather than hidden.

Seven affected Win32 selectors reuse the existing compiled fixture and
construction/destruction/terminal owners. Real one/two-argument copy,
destruction, constructor faults, propagation with flag zero and termination
with flags 1/255 reproduce the retained original-trampoline outcomes under Wine.
The source bridges and memcpy replace their dependencies in the linked image;
all four complete linked bodies match the retained source objects after actual
relocations. Stock validators and SEH remain genuine runtime dependencies.
The pointer adapter's current maintained function body is unchanged, despite
unrelated edits elsewhere in its original source owner. That exact body and
the actual fixture inputs/products are checked before reuse.

No unaffected fixture selectors or full replay ran. All 380 exact and 92 prior
candidate recipes, complete inputs, products and results are preserved. The
249 historical semantic rows are byte-identical. Current totals are 475 source
entries, 380 exacts, 95 complete candidates and 70 inventory entries without
source. Full tail transport, remaining low-level source and the final restored
game build/play check remain open.

Private receipts: `.analysis/cpp-member-call-source-20261016/`, including
`callback-type.json`, `original-proof.json`, `source/{product,comparison,clang}.json`,
`members-product.json`, `differential.json`, `link.json`, `linked-code.json`,
`runtime.json` and `adoption.json`. Heavy work is serial with CPU 35%, memory
high 640 MiB/maximum 768 MiB; preserved objects are reused after identity checks.
Sharing three byte-identical immutable snapshots reclaimed about 2 MiB;
unique evidence, source products and mutable build objects are retained.
