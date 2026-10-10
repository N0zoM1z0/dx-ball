# REA commands

Use `scripts/rea` from the repository root. It selects Ghidra and applies the
project's target checks and process limits. Versions are pinned in
[`config/rea.lock.json`](../../config/rea.lock.json): REA 4.1.0 and Ghidra 12.1.4.

Supply the matching executable and assets under `original/`; see
[`config/target.toml`](../../config/target.toml) and [build setup](../BUILD.md).
On a fresh workspace:

```bash
scripts/repo-python scripts/bootstrap-rea.py
scripts/rea doctor --provider ghidra --json
```

Look up entries in `config/functions.csv` and reuse saved investigations before
making another query. For one function:

```bash
scripts/rea function original/DXBALL.EXE 0x00413410 --provider ghidra \
  --snapshot .analysis/rea/dxball.snapshot.json --json
```

For related questions, keep one imported program open:

```bash
scripts/rea session --interactive
```

The session helper opens the configured executable. Enter requests using the
pinned server's advertised schemas; these are supported 4.1 request shapes:

```json
{"name":"analyze_function","arguments":{"procedure":"0x00413410"}}
{"name":"read_bytes","arguments":{"address":"0x00413410","length":146}}
{"close":true}
```

The helper records complete responses and Evidence IDs under
`.analysis/rea/runs/` and saves the cumulative snapshot on close. Cite the
archived run; root-level result files are latest-query aliases. A request array
can also be passed as `scripts/rea session path/to/requests.json`. Inspect the
saved tool catalog before composing requests for another operation.

Retain the responses used for source recovery and link them from the relevant
research note. Follow the [reconstruction workflow](WORKFLOW.md) when changing
source or publishing a new exact claim.
