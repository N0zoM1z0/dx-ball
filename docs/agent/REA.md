# REA commands

Use `scripts/rea` from the repository root. It selects Ghidra and applies the
project's target checks and process limits. Versions are pinned in
[`config/rea.lock.json`](../../config/rea.lock.json): REA 6.4.0 and Ghidra 12.1.4.

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
pinned server's advertised schemas. These shapes were verified with 6.3;
the 6.4 upgrade also checked `read_bytes` against the same original:

```json
{"name":"analyze_function","arguments":{"procedure":"0x00413410"}}
{"name":"read_bytes","arguments":{"address":"0x00413410","length":146}}
{"close":true}
```

The helper records complete responses and Evidence IDs under
`.analysis/rea/runs/` and saves the cumulative snapshot on close. REA 6.3/6.4
analysis records expose `raw_result` and `normalized_result`; older retained
responses use `result`. Cite the
archived run; root-level result files are latest-query aliases. A request array
can also be passed as `scripts/rea session path/to/requests.json`. Inspect the
saved tool catalog before composing requests for another operation.

For a missing native ABI, control-flow or instruction question, the narrower
facets are also verified with 6.3:

```json
{"name":"procedure_info","arguments":{"procedure":"0x00404E40"}}
{"name":"procedure_pseudo_code","arguments":{"procedure":"0x00404E40"}}
{"name":"procedure_assembly","arguments":{"procedure":"0x00404E40"}}
{"close":true}
```

Request only the needed facets and retain their Evidence identities. These
interfaces produced compact font records, but the first query still incurred
the cold provider delay. Native function views may omit unreachable intervals
inside the enclosing span; check information ranges against the full bytes
before claiming exact recovery. The assembly schema returns a string; general
large-body pagination has not been verified.

The upgrade from 4.1.0 to 6.3.0 retained the old snapshot at
`.analysis/rea-upgrade-6.3.0/snapshot-4.1.0.json.gz`. The new release failed its
integrity validation (root cause unisolated), so the current snapshot starts with the new focused queries.
Keep reusing historical dossiers directly; their Evidence IDs and original
bytes remain available. Upgrade receipts and both scoped doctor reports are
in `.analysis/rea-upgrade-6.3.0/`.

The old snapshot is a byte-exact gzip carrier: 72,771,098 original bytes become
4,731,476 compressed bytes. `snapshot-compression.json` records both hashes and
the verified decompressed hash before removal of the raw copy, releasing
68,034,560 allocated bytes including the receipt. Decompress only when needed;
no current task input or sealed external dependency uses the removed raw path.

The installed REA skill is synchronized with the current package: skill version
37 and 170 tools. The 6.4 upgrade receipts, prior version-34 skill, and intact
43-record 6.3 snapshot are in `.analysis/rea-upgrade-6.4.0/`. Opening that
snapshot with 6.4 returned `evidence_integrity_mismatch` / `profile_mismatch`;
the current snapshot starts with the focused 6.4 calibration. Reuse archived
6.3 Evidence directly without redoing successful analyses. Node 22.19.0,
Ghidra 12.1.4 and the JDK remain the pinned engines; no MCP registration changed.
Keep tool discovery bounded: retain the complete catalog outside the agent
context and inspect only the selected operation's schema.

The release advertises `inspect_analysis_view` for completed binary-layout and
JavaScript application Evidence, using same-session retained IDs or inline
Evidence. Native function-dossier views and old-record compatibility are not
established by that description. Continue projecting the needed facets from
retained native dossiers locally. `export_evidence_bundle` can retain a complete
session bundle when needed; avoid duplicating already archived evidence.

REA 6.4 adds bounded discovery for retained Evidence. With an existing exported
portable bundle, select a known ID or exact operation/target/profile filter:

```bash
scripts/rea inspect-evidence-bundle '{"path":"/absolute/path/bundle.json","detail":"summary","filters":{"operation":"read_bytes"}}' --json
```

The 6.4 upgrade checked a single historical 6.3 record this way: 43 records
were validated locally and only the selected record's discovery metadata was
returned. A snapshot is a separate envelope; extract its `evidence_bundle`
to a disposable bundle when needed, retaining the original snapshot. The
summary omits analysis payloads; it does not replace the complete Evidence
carrier required for a new exact claim. Full bundle parsing still consumes
local memory, even though the response is small. Within an existing MCP
session, the advertised `get_evidence_bundle` accepts the same summary and
filters. The project's native session helper currently allows only its listed
native inspection operations; use the offline CLI for archived discovery.

Retain the responses used for source recovery and link them from the relevant
research note. Follow the [reconstruction workflow](WORKFLOW.md) when changing
source or publishing a new exact claim.
