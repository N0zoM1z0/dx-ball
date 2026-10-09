# CRT termination owner

The allocation-failure path reaches C `exit` at `0x417910`. This batch follows
that edge through the original cleanup controller and callback-table walker,
recovering four standalone functions in [termination.c](../src/termination.c).
REA instruction evidence establishes the control flow; original x86 execution,
native C and actual VC4/MinGW objects check the resulting source independently.

| Original entry | Maintained function | Reviewed bytes | Direct calls |
| --- | --- | ---: | ---: |
| `0x417910` | `dxball_crt_exit` | 18 | 32 |
| `0x417930` | `dxball_crt_quick_exit` | 18 | 32 |
| `0x417950` | `dxball_crt_do_exit` | 128 | 552 |
| `0x4179d0` | `dxball_crt_run_initializers` | 32 | 415 |

These are runtime dependencies. The batch adds **1,031 direct calls across
1,026 fixtures**, counted once despite execution by three generated products
and cold replay. Current totals are **247 source-present (235 game + 12
runtime), 112,273 direct cases, 35 exact units / 3,379 bytes**. Two additional
entries are identified as runtime code: **17 runtime origins / 276 unknown**.
None of these four new source bodies has a configured byte-exact claim.

## Instruction contracts

The controller writes `1` to `0x4230f0`, then writes only the low byte of its
return-to-caller argument to `0x4230ec`. Its later exit decision tests the full
argument captured before callbacks. Thus `256` writes a zero flag and still
returns to its caller; a callback changing the flag cannot change that decision.

Normal cleanup walks the on-exit table backwards, skips null entries and calls
each remaining slot. It captures the end at `0x440d78` once, but reloads the
begin at `0x440d7c` after each slot. Callback changes to the begin can shorten
the walk; changes to the end do not extend it. It then walks two pretermination
slots in `[0x421040, 0x421048)`. Quick cleanup skips those two stages. Both
modes walk the one-slot termination range `[0x42104c, 0x421050)`.

The forward walker captures both bound arguments and reads each slot when
visited. It calls nonnull slots in ascending order. No done-flag guard suppresses
a second controlled call. The wrappers pass `(status, 0, 0)` and `(status, 1, 0)`
respectively. In this CRT, C `_exit` still runs the termination table. The COFF
symbol `__exit` denotes that quick wrapper; `_exit` denotes decorated C `exit`.

Source stores callbacks in host-width pointers while retaining 32-bit status,
integer arguments and an unsigned-byte flag. Tested table bounds belong to the
same backing array; callbacks may make finite mutations within that backing.
Dangling tables, address wrap, unrelated-array ordering, table relocation,
arbitrary reentrancy and nonterminating callbacks remain outside this scope.

## Executed batch and cold replay

The fixtures exhaust null/two-identity callback lists through five slots,
interior/empty/reversed subranges, full-width status and signed mode boundaries,
null on-exit begin, repeated invocation and callback mutations of table slots,
begin/end, subsequent stages and termination globals. Every comparison includes
the complete logical table contents, bound identities, flags and ordered
callback/platform events. Original text is unchanged; its internal exit and
walker entries execute directly. Original stack cleanup and callee-saved
registers are checked by the target oracle.

The generated-object loader loads every section, retains actual common/BSS
layouts, rejects overlapping globals and resolves every relocation explicitly.
Original `ExitProcess` is stdcall. The portable source's typed dependency bridge
is cdecl; the object oracle checks that separate ABI. Compiler, source/import
cache, engine, mapped library and actual product hashes are retained privately.

REA process captures `ev_74256059139d916bbf4972ea63b84ea5859e9e8f4fc50e1b19749a5afb3ad718`
and cold replay `ev_197bf19144c2012b2034c42a376a108f49d2a9285024d8c5282e421314d2ea06`
exit zero without truncation and bind the complete summary digests. Native,
VC4 and MinGW projections agree, including the cold build:
`da4051d3d037b8c6b44b5b421d9e612751fc96b289f86e85bf2eabc74d0da204`.
The two SHA-sealed checkpoints retain separate actual products. VC4 object
file identities change when rebuilt; agreement is in the complete observations,
not an assertion that whole object files are identical.

```bash
# Standalone native owner; does not require a game rebuild.
scripts/repo-python tests/test_termination_differential.py
# Cold-build and execute actual pinned VC4 and installed MinGW objects.
scripts/repo-python tests/test_termination_coff.py
# Public checkout: compile without accessing private original assets.
scripts/repo-python tests/test_termination_differential.py --compile-only
```

The controlled platform callback returns on both sides so these finite owner
observations can be collected. This does not execute physical Windows exit.
The owner is not connected to the experimental game's existing host CRT or
allocator fatal path. Callback registration, actual startup table population,
physical process termination and complete original CRT teardown remain open.
The game/source products and 35 accepted exact objects remain unchanged.

## REA evidence and library origin

Saved matching dossiers supply normal exit and the controller; only the two
missing entry dossiers and byte reads needed new provider queries. The session
closes explicitly and saves 345 cumulative Evidence records.

- Normal exit: `ev_df594328fa0899467c7969112f2ca49e255c91e1d3fb81b92b74f5e60db13234`
- Controller: `ev_708cef33a373375bddd52f451b3dcb5c0c69e2fefd4e9cb94a8f8876f53e098b`
- Quick exit: `ev_a342568802ab9da4d777a0d9d9e9337d13dbadc5981b0e6b8fc92fda720d75d0`
- Walker: `ev_db9b75cfc245d4d07c1f7ac4e273aced3e99823502913955529db3cc962382e2`
- Complete 18/32-byte reads: `ev_51f8824c0a9db04185ff3ff9b3ffcdec4041a4abf187b2df513ee44fa15e927c`,
  `ev_f69d5ec964c32f9112b4952d8a0a3d8dbedd449b996b1c370a170a2473c10d3d`

The extended [CRT provenance comparison](CRT_PROVENANCE.md) checks the complete
`__exit` and `__initterm` library sections against these byte observations, with
all relocations applied. Both agree with pinned `libc.lib`; the threaded
initializer walker differs. This establishes runtime origin, separately from
maintained-source semantics and configured exact units.

The saved direct-reference query for new-handler storage still identifies only
the existing reader. No new registration claim follows from this termination
batch; indirect state writers remain unresolved.
