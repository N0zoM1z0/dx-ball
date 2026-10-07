# REA showcase workflow

DX-Ball is a source-reconstruction showcase for
[REA — Reverse Engineer Anything](https://github.com/morluto/rea).
New binary analysis uses REA's CLI/MCP over its Ghidra provider. REA supplies
observations and evidence; maintained C, target execution and compiler replay
establish the reconstruction's separately scoped acceptance facts.

## Pinned installation

| Component | Project choice |
| --- | --- |
| REA npm package | `rea-agents` 4.1.0, exact npm integrity and dependency lock |
| Node runtime | 22.19.0; local executable hash is pinned |
| Provider | Ghidra 12.1.4, official archive SHA-256 and 206 component hashes |
| JDK | Existing hash-pinned Temurin 21.0.12.1+1 |
| Original target | DX-Ball v1.07, `config/target.toml` |

`config/rea/package-lock.json` pins all npm package tarballs and dependencies.
`config/rea.lock.json` pins the installed dependency tree, Node executable,
Ghidra archive, launcher, native decompiler and all provider JARs. The project
entry point also verifies the JDK and the original file before target queries.

```bash
scripts/repo-python scripts/bootstrap-rea.py
scripts/rea doctor --provider ghidra --json
scripts/rea providers --json
```

The published REA 4.1.0 rejects Ghidra 12.1.3. Repository main has subsequently
broadened that check to 12.1.x; installing main's skill does not change the
released package. We use the verified release boundary and install 12.1.4
separately under `.tools/ghidra-rea`. The old 12.1.3 project is historical
inventory/evidence and is retained without reclassifying its 528 candidates.
Default `bootstrap-tools.py` now installs only the JDK/compiler prerequisites;
`bootstrap-rea.py` supplies the active analysis engine. The historical Ghidra
archive is available only through explicit `--historical-ghidra` setup.

## Codex MCP and skill

Scoped upstream setup configures Codex and installs the package-matched
`reverse-engineer-anything` skill with its on-demand references:

```bash
scripts/rea setup --client codex --dry-run --json
scripts/rea setup --client codex --yes --json
scripts/rea doctor --client codex --json
```

The reviewed plan writes only the REA registration in
`~/.codex/config.toml`, preserving unrelated configuration with an upstream
`.rea.backup`, and the managed skill at
`~/.agents/skills/reverse-engineer-anything`. It reuses the verified Ghidra/JDK
paths. Persistent registration points to the locally installed 4.1.0 command;
it does not fetch an unpinned latest release at agent startup.
The Codex REA environment additionally pins `REA_ANALYSIS_PROVIDER=ghidra`.

A running agent's tool catalog does not gain tools merely because setup wrote
its configuration. Restart/reconnect Codex to use REA tools directly. The
project CLI and an actual MCP client session work immediately, so binary work
can continue through those paths. Use `provider_id: "ghidra"` when opening
DXBALL.EXE through MCP.

## Analysis and snapshots

For one function:

```bash
scripts/rea function original/DXBALL.EXE 0x00411F40 --provider ghidra \
  --snapshot .analysis/rea/dxball.snapshot.json --json
```

For several focused operations in one real MCP session, create a request array
using the connected server's input schemas and run:

```bash
scripts/rea session config/rea-smoke.json
scripts/repo-python scripts/verify-rea.py
```

The project session helper opens the hash-pinned executable with the Ghidra
provider, sends sequential MCP requests, preserves each complete result and
Evidence record under `.analysis/rea/`, saves a provider-neutral snapshot, and
closes the session. It uses the release's real MCP client library and advertised
tool schemas. The 360-second per-call deadline covers Ghidra's lazy first-query
import/auto-analysis; it is separate from MCP connection startup.
The pinned split MCP SDK takes request options as the second `callTool` argument;
the helper supplies its deadline there rather than relying on the 60-second default.

REA runs on one inherited allowed Linux CPU, with a 512 MiB maximum Ghidra heap
set through the supported `GHIDRA_HEADLESS_MAXMEM` launcher variable. REA
sanitizes external JVM option strings; inherited affinity constrains provider
and native decompiler threads without changing its pinned launcher.
These limits are applied in `scripts/resource_limits.py`; pinned provider files
are unchanged. The heap ceiling excludes native/JVM overhead and is not a total
resident-memory limit. Build entry points use the same CPU restriction and
CMake uses `--parallel 1`.

Each session also retains an independent timestamped directory under
`.analysis/rea/runs/`, including requests, tool catalog, complete results and
errors. The root files remain latest-result aliases for the smoke verifier.
A failed later query still closes with a snapshot, preserving the successful
prefix; cleanup errors are recorded separately without hiding the query error.
This was exercised against REA's uppercase-address rejection in `xrefs`: the
preceding RNG dossier remained in the saved snapshot after the nonzero exit.

Snapshots are private reusable evidence tied by REA to the exact target,
provider and analysis profile. CLI requests can reuse matching snapshots
without a new provider process. Preserve Evidence IDs and limitations when
promoting observations into owner documentation. Static pseudocode is never
reported as original source or runtime execution.

The initial verified MCP snapshot contained five Evidence records and zero
primitive cache entries; later investigations add Evidence. Those are separate
collections: the CLI function query reused
its matching saved function Evidence. Do not interpret a cache entry count as
an Evidence count or assume every MCP operation avoids provider startup.

## Verification boundaries

The smoke request binds the original SHA-256, obtains a binary overview,
analyzes the exact sprite dispatch at `0x00404180`, reads all 105 loaded bytes,
inspects the native load image, and analyzes pending tile-hit logic at
`0x00411F40`. `verify-rea.py` independently compares the read bytes to the pinned
PE and requires the accepted function's complete body size and saved snapshot.

REA's PE load-image measurements retain their declared independent-attestation
limitations. Our explicit PE byte comparison is separate corroboration. Neither
REA configuration nor a function dossier promotes semantic or byte-exact claims;
the existing original-x86 and cold compiler oracles remain required.

Public CI builds maintained source and validates acceptance metadata. Private
CI now verifies REA's actual MCP/Ghidra path before running reconstruction
oracles. Original assets, dependency installations, temporary Ghidra projects,
snapshots and raw decompilation remain ignored and unpublished.

## First DX-Ball investigation

The live REA 4.1.0 server advertises 125 MCP tools. Ghidra's overview reports
624 procedures; the earlier 528-entry ledger is a different provisional
inventory and is retained pending origin/boundary reconciliation. No progress
denominator was changed from an overview count.

The sprite dossier reports the complete contiguous 105-byte body at
`0x00404180`..`0x004041E8`. Its loaded bytes match the original PE independently.
The tile-hit dossier reports two body ranges, 1,244 owned bytes inside a
1,315-byte enclosing span. The intervening 71 bytes must not be treated as
owned instructions merely because they lie between the endpoints.

The PE load-image operation returns `unsupported` for independent attestation
and still supplies measurements. That limitation is retained; the separate
105-byte comparison does not upgrade it to a whole-image claim.
Public checkpoint identities are in `config/rea-verification.json`; complete
Evidence records remain private.

The [particle and bonus investigation](ENTITIES_OWNER.md) follows the same
workflow from REA dossiers into two typed C owners. Body ranges separate the
bonus selector's switch data from instructions, and callers connect brick hits
to particle creation. Original-x86 tests then compare list lifetimes, RNG order
and actual 2x2 pixel writes into controlled surfaces. Fourteen maintained
functions and nine complete exact units result from that investigation; bonus
movement and power-up application remain the next open scope.

References: upstream [installation and release boundaries](https://github.com/morluto/rea/blob/main/docs/installation.md),
[MCP lifecycle/deadlines](https://github.com/morluto/rea/blob/main/docs/mcp-contracts.md),
and [native investigation skill](https://github.com/morluto/rea/blob/main/skills/reverse-engineer-anything/references/native-and-artifacts.md).
