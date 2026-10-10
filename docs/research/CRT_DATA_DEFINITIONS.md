# Complete CRT storage and definitions

This checkpoint resolves two unknown entries as runtime dependencies without
adding game source or function exact acceptance. Current origins are 270
authored, 68 runtime, 42 compiler-generated and 148 unknown. Source presence
remains 283; exact acceptance remains 171 functions /30,744 code bytes plus
136 separate metadata bytes; scoped semantic acceptance remains 247.

## Independent storage placement

The pinned VC4 `libc.lib` supplies two complete initialized data sections.
Member identity, section extent, actual definitions and all relocations are
checked before any definition becomes available to a consumer.

| Original base | Member | Complete bytes | Independent placement | Relocations |
| --- | --- | ---: | --- | ---: |
| `0x4230AC` | `crt0dat.obj` | 72 | Reviewed `__exitflag=0x4230EC` and `__C_Termination_Done=0x4230F0`, at actual COFF offsets 64 and 68 | 0 |
| `0x423670` | `ctype.obj` | 522 | Unique complete 514-byte `__ctype` array, at COFF offset 8 and original file offset 138872 | 2 |

The first section contains only initial zeros. A zero search cannot establish
its address: two existing anchors independently imply the same base. Only
after the full comparison does `_errno` at offset zero become a verified
binding. The second section's array is a discovery seed, not a substitute for
the entire section. Both DIR32 pointers at offsets zero and four are relocated
to `__ctype+2=0x42367A`; every one of the 522 bytes must then agree.

Complete REA reads also match the pinned original PE:

- 72 bytes: `ev_1bd03ba587bf4cb8cb739d2e1ec4fd40ea4aabd9238dbe9fc0f4136976870bc0`.
- 522 bytes: `ev_84b9961d1896477a16328bb23a2f1fe39d45cf14bdf71e35bafc0536fae3fe6b`.

These are static initial storage observations. They do not establish runtime
writes, original declaration spelling, common/BSS symbol addresses or unique
original link selection. In particular, `___pioinfo` and `__nhandle` remain
unbound; this initialized-section route does not establish their placement.

## Code definitions before consumers

All thirteen prior CRT definitions are re-extracted from the pinned archive
and checked over their full 546 bytes with every relocation against the retained
39,136-byte original observation and PE. Eleven actual external COFF definitions
can supply bindings. `_doexit` and `__initterm` have static storage class and
remain object-local. The historical cached eleven-function report is not used
as a thirteen-function proof. The first helper rejected static definitions
before acceptance; the failed helper/log are retained, then the visibility rule
was corrected to verify static bodies without exporting their names.

Two consumers now have complete provenance:

| Original entry | Complete bytes | COFF symbol | Newly grounded dependency |
| --- | ---: | --- | --- |
| `0x41FD70` | 111 | `_realloc` | Full `_malloc` definition and named `KERNEL32.dll!HeapReAlloc` IAT cell `0x441278`, plus reviewed CRT bindings |
| `0x419C40` | 42 | `__set_errno` | `_errno=0x4230AC` from the complete independently placed storage |

Code corroboration uses Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
The verifier now checks 54 complete code sections /6,026 bytes /55 code-origin
rows, two data sections /594 bytes, and three forwarding entries /18 bytes:
58 distinct origin rows. These provenance bytes are separate from the game's
accepted exact-code and metadata totals.

## Validation and limits

Five actual-verifier controls reject a shifted zero section, unsupported zero
anchors, a pointer-bearing discovery seed, altered observed data and a partial
prior code definition. Complete inputs and current product hashes are checked.
No game source, acceptance ledger or production product changes; no compiler,
SDK runtime or gameplay check is needed for this ownership-only checkpoint.
Both new REA sessions closed successfully. Cold read latency is recorded in
the user's one existing feedback document, without claiming warm-cache timing,
exact model-token cost or measured peak memory.

Private proof: `.analysis/crt-data-frontier/`. Immutable seal:
`.analysis/checkpoints/crt-data-definitions-283-171/sha256.json`.
Repeat the bounded verifier with
`scripts/repo-python scripts/verify-runtime-origin-sections.py`.
