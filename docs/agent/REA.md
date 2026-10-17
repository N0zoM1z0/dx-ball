# REA commands

Use `scripts/rea` from the repository root. It selects Ghidra and applies the
project's target checks and process limits. Versions are pinned in
[`config/rea.lock.json`](../../config/rea.lock.json): REA 6.5.0 and Ghidra 12.1.4.

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

For a concrete compiler-lowering question, a dedicated session can inspect the
hash-pinned VC4 compiler tools:

```bash
scripts/rea compiler-session vc4-backend path/to/requests.json
scripts/rea compiler-session vc4-backend --interactive
scripts/rea compiler-session vc4-cpp-frontend --interactive
```

The backend mode verifies the complete installed toolchain and selects its attested
`c2.exe`. Its records and snapshot live under `.analysis/rea/vc4-backend/`,
separately from game investigations. The opened target hash must agree before
the session may save a snapshot; a rejected target is closed without saving.
Compiler records have immutable per-run paths without duplicate latest-result
aliases. Interactive use requires an open stdin; automation here uses a PTY.
Use the same serial systemd resource scope below. Compiler observations can
support a specific source hypothesis, but do not establish the original game's
compiler settings or translation-unit declarations.

An interactive inspection returning REA category `invalid_input` retains an
indexed `.error.json` with its request, error and full response, then keeps the
same import open. `inspection-errors.json` lists those failed attempts. This
does not retry a request or reopen the provider. Batch errors and transport,
provider, open, target-identity and close failures still terminate the session.
Successful records keep their attempted-request indices, including any gaps.

The first compiler import exceeded the default 330-second provider startup
budget. The completed focused session omitted `Apply Data Archives` using
`REA_GHIDRA_DISABLED_ANALYZERS='Apply Data Archives'` and set
`REA_GHIDRA_STARTUP_TIMEOUT_MS=900000`. Compiler-session client calls allow
930 seconds; game sessions retain their existing timeout and analysis profile.
The first query took394,604 ms, with subsequent queries reusing the live import.
CPU35%, memory high640 MiB/max768 MiB and the256 MiB Java heap were retained.
See [the record reader](../research/exact/VC4_BACKEND_SYMBOL_RECORDS.md) and
[expression ordering](../research/exact/VC4_EXPRESSION_ORDERING.md) findings
before importing again. The closed cumulative snapshot now retains86 records.
The ordering follow-up reuses one live import after its407,402 ms cold query;
44 synthetic executions confirm the actual rank/swap helpers, without claiming
original-game record keys or a cause for its instruction differences.

The later [frame-allocation investigation](../research/exact/VC4_BACKEND_SYMBOL_RECORDS.md#frame-allocation-from-the-symbol-reader)
adds22 records through one417,663 ms cold import and fast same-session follow-ups.
It follows an actual symbol-field hardware write through the reader and allocator.
The imported allocator tail and reader loop/prologue are split across records;
reconnect actual jumps/fallthrough before reasoning about whole behavior.17 final
controlled pinned-code calls reproduce the current16 homes with explicit cursor/
alignment inputs. This establishes the current C2 allocation path, while frontend
production order and original declarations remain open. Reuse the86-record snapshot
and retained traces before another import.

The [C++ frontend traversal follow-up](../research/exact/VC4_FRONTEND_SYMBOL_ORDER.md)
selects only attested `c1xx.exe` through `vc4-cpp-frontend`, with its own directory
and snapshot under `.analysis/rea/vc4-cpp-frontend/`. It retains115 successful
observations/five indexed invalid inputs and closes normally. The first query
takes819,640ms under the same limits; reuse its records before another cold
import. Name hashing, head insertion and ascending buckets reproduce all16
current bank objects in36 controlled helper calls, with emitter/header boundaries
intercepted. This is not live frontend transport or original-name recovery.
The cold import logs retain a Decompiler Parameter ID timeout. Future imports
may consider that exact optional analyzer separately; do not silently change a
retained profile or trust its inferred signatures. Nine Python guard/dispatch
cases and six provider-free JavaScript lifecycle cases pass for the new mode.

The later [NameMap producer follow-up](../research/exact/VC4_FRONTEND_SYMBOL_ORDER.md#namemap-key-generation-october18)
explicitly omits both `Apply Data Archives,Decompiler Parameter ID`. It starts a
fresh profile after verifying the existing sealed115-record gzip against the
old mutable snapshot, then removes only that duplicate raw snapshot. Its
71 direct results/74 Evidence records remain separate from the old profile;
first query327,899ms and subsequent queries share one import. Full instructions
and bytes dominate inferred signatures. The new74-record snapshot is current;
the old115 observations retain their original immutable run/archive identities.

For a missing native ABI, control-flow or instruction question, the narrower
facets are also verified with 6.3:

```json
{"name":"procedure_info","arguments":{"procedure":"0x00404E40"}}
{"name":"procedure_pseudo_code","arguments":{"procedure":"0x00404E40"}}
{"name":"procedure_assembly","arguments":{"procedure":"0x00404E40"}}
{"name":"procedure_references","arguments":{"procedure":"0x00404E40","direction":"incoming"}}
{"close":true}
```

Request only the needed facets and retain their Evidence identities. These
interfaces produced compact font records, but the first query still incurred
the cold provider delay. Native function views may omit unreachable intervals
inside the enclosing span; check information ranges against the full bytes
before claiming exact recovery. The assembly schema returns a string; general
large-body pagination has not been verified.
The session helper also permits `procedure_references`, verified through eleven
incoming-reference queries on 6.5. It retains self-body edges as well as external
sources; exclude self-body sources explicitly when comparing it with dossier
incoming edges. Unresolved computed destinations remain unknown.

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

The installed REA skill is synchronized with 6.5.0: skill version 42 and 207
advertised tools. Upgrade receipts, the prior version-37 skill and a verified
420-record 6.4 snapshot are in `.analysis/rea-upgrade-6.5.0/`. Opening the old
snapshot with 6.5 returned `evidence_integrity_mismatch` / `profile_mismatch`.
The archived payloads remain authoritative for their original observations;
new 6.5 work uses a fresh snapshot. Earlier 6.3/6.4 upgrade evidence remains in
its existing private carriers. No MCP registration or engine version changed;
current processes with an older tool catalog require a client reconnection,
so new work here uses fresh project CLI sessions.

The 6.5 check opened the verified target with 207 actual tools, read all 28 bytes
at `0x4201C8` and matched the PE, then closed and saved one fresh Evidence record:
`ev_ad8b7d65b442e9a523841c43f495ec948be8f44624cf7d644cfa9c818756eb1c`.
The selected Ghidra doctor scope is healthy; unrelated optional environment
checks were not used as a gate. No historical native query queue was replayed.
The cold provider read took 164,048 ms under the CPU cap; sampled whole-scope
memory peak was 671,502,336 bytes, with the JVM's `-Xmx256M` observed directly.
These timings and memory samples describe this bounded upgrade check.

The old expanded runtime was removed only after a complete sequential archive
verification of its 6,506 regular files and symlink checks. Its 18,445,330-byte
rollback archive remains intact; the reviewed cleanup removed 6,522 old leaves
and released about 97 MiB of expanded tool storage. The current runtime and
standard-bootstrap `npm ci` product remain fully hash-attested.

The project REA entry point now sets the supported `GHIDRA_HEADLESS_MAXMEM=256M`.
On this development host, cap a heavy command and all descendants with a user
systemd scope, in addition to the existing one-CPU affinity and serial session:

```bash
systemd-run --user --scope --quiet \
  -p CPUQuota=35% -p MemoryHigh=640M -p MemoryMax=768M \
  scripts/rea session path/to/requests.json
```

Use the same scope for compiler/Wine commands. The kernel reports
`cpu.max` as `35000 100000` and `memory.max` as `805306368`; these are whole-tree
limits, not just launch-process settings. Do not run heavy sessions together.
The historical general helper still records its earlier 512 MiB profile;
the current REA wrapper explicitly selects the smaller heap. Node 22.19.0,
Ghidra 12.1.4 and the existing JDK remain pinned. Keep discovery bounded and
save full catalogs outside the conversation before inspecting selected schemas.

Input attestation hashes files through `hashlib.file_digest` rather than loading
each whole file. The October 18 verification preserves all VC4, Node dependency
tree, Ghidra and JDK pins. Separate children hashing the same 142,255,299-byte JDK
module file peak at 153,760 KiB with the old helper and 17,688 KiB with streaming;
their digests agree. This measures single-file hashing RSS, not whole-REA peak
memory. The serial full input attestation has zero memory-limit events. Reuse
`.analysis/streamed-input-hashing-20261018/` receipts; no provider, compiler or
game replay is needed for this helper change. Its duplicate before-copy is
removed after byte comparison with the reachable Git beforeimage.

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
