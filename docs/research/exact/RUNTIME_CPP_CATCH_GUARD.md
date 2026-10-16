# Catch transport and the omitted guard callback

The catch transport at `0x004185B0` stores `0x00418620` as its temporary
registration's handler. That address is a real **41-byte CatchGuardHandler**,
ending at `0x00418648`. The provisional inventory omitted it because Ghidra
does not define a procedure at the address. The inventory now includes it;
this reconciliation adds no maintained source or accepted exact function.

Both complete sections match the pinned `trnsctrl.obj` after their actual
relocations:

| Entry | Bytes | Relocations | Actual bindings |
| --- | ---: | ---: | --- |
| `_CallCatchBlock2`, `0x004185B0` | 98 | 2 | Guard `0x00418620`, frame setter `0x0041BC10` |
| `CatchGuardHandler`, `0x00418620` | 41 | 1 | Internal frame handler `0x0041B1B0` |

The original C++ catch-transport symbol and five-argument ABI are already
consumed directly by the [exact catch wrapper](RUNTIME_CPP_CATCH.md).
Their identities are grounded in the full CRT sections, actual bindings and
caller contract, rather than a library-name guess.

The guard starts with **CLD**, then forwards the exception and context, the
guard's function/registration/nesting values, a null dispatcher, the guard as
marker, and a zero recursive flag to the internal frame handler. It preserves
the returned disposition. The direction-flag write is an actual machine-state
operation. No ordinary C wrapper, omitted operation or manufactured byte is
adopted as its source. Recovering the low-level transport and guard remains open.

## Evidence and provider coverage

REA 6.5.0 / Ghidra 12.1.4 evidence:

- Full transport read:
  `ev_d6151e8f684ec5f76809b0f912d45d2c7bc02ddf86ea5f5fb858c95bd467a9ab`.
- Full guard read:
  `ev_2f5b0729f185df86fe78b66cd025fb299714c7b78584120d344c9fe41bc05f82`.
- Decoded CLD, with no containing procedure and the incoming stored-address
  reference at `0x004185CB`:
  `ev_fd908e8bbe01431944507ee02a49cb292813aeee5200752fdc0a57024d45218d`.

Responses and the rejected `procedure_info` lookup are retained in
`.analysis/rea/runs/2026-10-16T05-13-56.899Z-requests-129676/`.
The lookup reports no procedure at the observed address. This is a provider
inventory limitation, not absence of the callback. The three successful
reads/decodes were retained before that rejection; the session then closed
and saved normally. No repeated query or function-creation annotation was needed.

The member was extracted again from pinned `libc.lib` at archive offset
`0x0002DD2C`. Its SHA-256 is
`206b02d6136285da3400a3bd57538a7ca3bee816d979cdd51753322d6ed350ce`.
Complete proof and exact bindings:
`.analysis/cpp-catch-guard-origin-20261016/complete-comparison.json`.

Current totals are **544 inventory / 463 source-present / 372 exact**,
76,452 exact code bytes and 232 attached metadata bytes. There are 81 inventory
entries without source rows. Origins are 270 authored, 213 runtime,
45 compiler-generated and 16 unknown. The 88 complete nonexact candidates,
three separate allocator comparison gaps and 249 semantic rows are unchanged.
The source and exact ledgers are byte-for-byte unchanged by this reconciliation.
No compiler or runtime test ran for these original-section origin claims.

## Frame entry and SE translator boundary review (October 16)

Three further complete sections from the same pinned `trnsctrl.obj` match the
original with every relocation resolved:

| Entry | Address | Complete bytes | Relocations |
| --- | --- | ---: | ---: |
| `___CxxFrameHandler` | `0x00418570` | 60 | 1 |
| `_CallSETranslator` | `0x00418650` | 209 | 3 |
| `TranslatorGuardHandler` | `0x00418730` | 107 | 2 |

The old guard extent stopped at the indirect continuation jump. The original
section also includes a nine-byte fallback epilogue at `0x00418792`: return 1,
restore ESI/EBX/EBP, then RET. Its bytes match through `0x0041879A`; no live
control-flow edge to this otherwise unreachable tail is invented.

The frame entry takes its function descriptor implicitly in EAX and executes
CLD. The translator installs a temporary FS registration with guard `0x418730`,
local continuation `0x4186E7`, and translator callback cell `0x42389C`. The guard
uses the original internal frame handler and nested-frame unwind entries,
restores saved ESP/EBP and jumps to that continuation. These machine-state
contracts remain open source work; ordinary C forwarding would lose behavior.

REA 6.5.0 / Ghidra 12.1.4 complete reads:
`ev_5997988a35c92ec75e177c0d3602a3e76f3c0f2a8d9567d1d377dedba83d305a`
and `ev_a6a2fe2f32fcd6d0e7516dd958192ef0ce2b4e7bb473ada8e3f814da782cda52`.
The earlier complete frame dossier is reused under its original REA 4.1
identity, `ev_4508867ac2559a1476790eebf4ebcc66f06b1002418ecd68cef6f5580ad461a4`.
New responses are retained in
`.analysis/rea/runs/2026-10-16T05-46-21.766Z-requests-188128/`;
the three complete section comparisons and explicit bindings are in
`.analysis/cpp-translator-boundaries-20261016/complete-comparison.json`.

Current origins are 270 authored, 217 runtime, 21 compiler-generated and 12
unknown. The 520 independent entries, 24 parent fragments, 464 source-present
entries and 373 accepted exact functions are unchanged. This review compared
only the three affected original sections: no compiler, full replay or runtime
check ran, and no source/exact acceptance was added.
