# Reconstructing DX-Ball with REA

This project recovers readable C for English DX-Ball v1.07 from its Windows
executable. The goal is a nearly complete reconstruction that can be rebuilt
and played. [REA](https://github.com/morluto/rea) supplies the binary evidence:
functions, instructions, references, data and the unanswered questions that
connect them. Contributors turn that evidence into the shared source in
[`src/`](../src).

## The version used here

This repository pins **REA 4.1.0 with Ghidra 12.1.4** in
[`config/rea.lock.json`](../config/rea.lock.json). Always use `scripts/rea`.
It checks the target and installed analysis inputs, selects Ghidra, and applies
the project's process limits.

The original executable and assets are private. Supply your own matching copy
under `original/`; [`config/target.toml`](../config/target.toml) identifies it.
On a fresh workspace, install the pinned analysis tools with:

```bash
scripts/repo-python scripts/bootstrap-rea.py
scripts/rea doctor --provider ghidra --json
```

## From a question to evidence

Start with a game action: what creates a projectile, advances it, draws it,
and removes it? Look up the relevant entry in `config/functions.csv` and read
any saved owner investigation. Existing dossiers often answer the next
question without another provider query.

For one focused function, the pinned CLI accepts:

```bash
scripts/rea function original/DXBALL.EXE 0x00413410 --provider ghidra \
  --snapshot .analysis/rea/dxball.snapshot.json --json
```

For related questions, keep one imported program open:

```bash
scripts/rea session --interactive
```

Enter requests using the pinned server's advertised schemas. These are actual
4.1 request shapes accepted by the repository session helper:

```json
{"name":"analyze_function","arguments":{"procedure":"0x00413410"}}
{"name":"read_bytes","arguments":{"address":"0x00413410","length":146}}
{"close":true}
```

The helper opens the configured executable, records complete responses and
Evidence IDs under `.analysis/rea/runs/`, and saves the cumulative snapshot on
close. Use the archived run when citing a result; root-level result files are
latest-query aliases. A request array can also be passed as
`scripts/rea session path/to/requests.json`. Inspect the saved tool catalog
before composing requests for another operation.

## A worked example: appending a projectile

The saved dossier for `0x413410` covers every instruction through the `RET` at
`0x4134A1`: 146 bytes. Its Evidence ID is
`ev_795c1af759609398f1bf4e5445e984b338706d39ca41b54043032d5252668d8d`.
The [list investigation](research/exact/EXACT_PROJECTILE_LISTS.md) records the surrounding
family; the implementation is `dxball_append_projectile` in
[`src/core.c`](../src/core.c).

The instructions establish more than the decompiler's unnamed pointer array:

- The list argument arrives in ECX, establishing the recovered fastcall API.
- The allocator receives 24 bytes, the original i686 projectile-node size.
- The new node's previous link gets the old tail; its next link becomes null.
- An empty list gets a first node; otherwise the old tail links to the new node.
- Last is written, then read back into current. Allocation failure calls exit.

Related list consumers establish the link meanings and node layout. The shared
C uses a typed list, a consumed node local, and `sizeof(DxBallProjectileNode)`.
It initializes only the fields the original writes. Host pointer sizes can
change the allocation size while the legacy i686 build retains 24 bytes.

That source produces a complete 146-byte match with the configured VC4 compiler.
The comparison maps both real calls—allocation and exit—and applies their COFF
relocations before comparing all bytes against the original PE. The unit and
its compiler inputs are in [`config/match-units.toml`](../config/match-units.toml).
A nearby projectile controller still differs at eight stack-displacement bytes;
that difference remains recorded in the full comparison.

## What each result tells us

REA pseudocode suggests a model; instructions and callers resolve widths,
calling conventions, ownership and evaluation order. A function's body can have
gaps or embedded tables, so an imported extent is only a starting point.
The saved Evidence retains those distinctions and provider limitations.

Recovered source, observed behavior and exact emitted bytes answer different
questions. An original-x86 Oracle can compare a specific game operation when
needed. A rebuild/startup/play check establishes practical progress. An exact
unit requires a full configured compiler comparison, including relocations,
literals and any accepted metadata.

Read [the contributor workflow](agent/WORKFLOW.md) for the small next-step loop.
Keep detailed evidence in the relevant research notes and continue with the next game behavior.
