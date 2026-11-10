# REA commands

Use `scripts/rea` for new binary analysis. The lock pins REA 6.5.0, Ghidra 12.1.4,
Node 22.19.0 and the JDK. The wrapper verifies those inputs and sets the Ghidra
heap to 256 MiB. Installations may share immutable Factory tools; keep this
game's Ghidra project, snapshots and writable state separate.

```bash
scripts/repo-python scripts/bootstrap-rea.py
scripts/rea doctor --provider ghidra --json
```

The target must match `config/target.toml`. Check `config/functions.csv` and
existing research conclusions before starting an import. Full new responses
and Evidence IDs go under `.analysis/rea/`; keep records that support current
work rather than accumulating every historical copy.

## Resource scope

Run one compiler/provider/Wine job at a time, on one already allowed CPU:

```bash
systemd-run --user --scope --quiet \
  -p CPUQuota=35% -p MemoryHigh=384M -p MemoryMax=512M \
  scripts/rea session path/to/requests.json
```

The wrapper applies single-CPU affinity. Automated game audio uses
`PULSE_SINK=dxball_reconstruction_silent`. Older import timings and memory
peaks do not prove operation inside the current tighter limits.

## Game queries

For one function:

```bash
scripts/rea function original/DXBALL.EXE 0x00413410 --provider ghidra \
  --snapshot .analysis/rea/dxball.snapshot.json --json
```

For related questions, reuse one imported program:

```bash
scripts/rea session --interactive
```

Verified request shapes include:

```json
{"name":"analyze_function","arguments":{"procedure":"0x00413410"}}
{"name":"read_bytes","arguments":{"address":"0x00413410","length":146}}
{"name":"procedure_assembly","arguments":{"procedure":"0x00404E40"}}
{"name":"procedure_references","arguments":{"procedure":"0x00404E40","direction":"incoming"}}
{"close":true}
```

Inspect the actual tool catalog for other schemas. Prefer the narrow facet that
answers the question. Assembly views may omit unreachable intervals; compare
against all original bytes before claiming a complete span. Incoming-reference
results include self-body edges. Computed destinations remain unknown unless
established separately. Interactive automation needs an open stdin/PTY.

## Compiler queries

```bash
scripts/rea compiler-session vc4-backend --interactive
scripts/rea compiler-session vc4-c-frontend --interactive
scripts/rea compiler-session vc4-cpp-frontend --interactive
```

These select the attested `c2.exe`, `c1.exe` or `c1xx.exe`. Target identity must
agree before saving a snapshot. Each target has separate runs and snapshots.
Cold compiler imports take minutes; reuse the [compiler conclusions](../research/exact/VC4_EXPRESSION_ORDERING.md)
and [frontend notes](../research/exact/VC4_FRONTEND_SYMBOL_ORDER.md) first.

Compiler imports use a 900-second provider startup budget and a 930-second
client budget. Historical successful profiles omitted `Apply Data Archives`;
later focused profiles also omitted `Decompiler Parameter ID`. A profile change
is explicit and separate from an old snapshot. Full instructions and bytes take
precedence over inferred signatures. Static compiler observations can guide a
source hypothesis without proving original-game declarations or live transport.

## Errors and snapshots

Interactive `invalid_input` keeps the same import open after recording the error.
A transport-budget `resource_constraint` likewise permits bounded continuation
through `inspect_analysis_view`. Use the server's exact reference and small page
facets; do not repeat a completed oversized dossier. Close without a cumulative
snapshot after any transport-budget error, preserving the prior snapshot and
successful responses. Other resource/provider/connection errors and batch errors
terminate the session. Do not increase memory ceilings to conceal the failure.

Old 6.3/6.4 snapshots failed 6.5 profile/integrity checks. Start a fresh compatible
snapshot instead of relabeling the old one. Provider-free lifecycle/transport
checks are in `tests/test_rea_session_transport.mjs`; they do not start Ghidra.
