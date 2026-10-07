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

For adaptive follow-ups, keep one imported program open:

```bash
scripts/rea session --interactive
```

Send a JSON request or request array per line, then `{"close":true}` to save and
close. The DX-Ball power-up investigation exercised several batches in one
session and saved 78 Evidence records. The later core investigation reused
its snapshot for 35 adaptive queries and saved 113 Evidence records on explicit
close. This avoids repeated Ghidra imports
while keeping requests sequential and recording every complete response.
The client uses the SDK's supported 32 MiB receive buffer and logs response
sizes, timings and transport errors. A ball-update dossier was 11,726,147 bytes,
above the SDK's default 10 MiB; increasing this client limit recovered the full
response without changing REA, Ghidra or the pinned SDK.

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
errors. The root files remain latest-result convenience aliases; saved smoke
verification uses a complete archived smoke run.
Run `scripts/repo-python scripts/clean-local.py` to preview local housekeeping,
then add `--apply` to remove superseded compiler probes and root query aliases
whose complete bytes survive in a closed archived session. Identical catalogs
inside closed archives share storage through hardlinks; their paths and hashes
stay intact. Mutable root aliases are never hardlinked to evidence. Cleanup
retains snapshots, archived results, checkpoint reports and pinned tools, and
writes a private SHA-256 operation journal under `.analysis/cleanup/`.
A failed later query attempts to close with a snapshot, preserving the successful
prefix; cleanup errors are recorded separately without hiding the query error.
If the transport has already closed, complete received Evidence files remain
available even though that run cannot save its new records into the snapshot.
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
functions and nine complete exact units result from that investigation. The
[power-up investigation](POWERUPS_OWNER.md) then follows the updater into paddle,
board, round and ball dependencies, adding 21 verified functions and seven exact
units. REA's assembly and CRT dispatch records recover the quantized sine/cosine
ABI that pseudocode omits; original execution checks both computed tables and
the rebound rounding. The [core investigation](CORE_OWNER.md) connects the
3,223-byte ball updater and complete frame to shots, board damage and deferred
powers. Its 4,580 original-x86 cases include 200 continuous frames; unresolved
frame dependencies remain explicit. Instruction views also recovered x87
expressions and unequal projectile offsets omitted from pseudocode.

References: upstream [installation and release boundaries](https://github.com/morluto/rea/blob/main/docs/installation.md),
[MCP lifecycle/deadlines](https://github.com/morluto/rea/blob/main/docs/mcp-contracts.md),
and [native investigation skill](https://github.com/morluto/rea/blob/main/skills/reverse-engineer-anything/references/native-and-artifacts.md).

## Following the runtime caller

The [runtime investigation](RUNTIME_OWNER.md) follows the main frame into mode
dispatch and gameplay initialization. REA's caller/switch evidence identified
`0x40F4C0` as the real initializer; a large earlier candidate, `0x40E570`, belongs
to the intro point table. Instruction evidence also distinguishes the unsigned
score-clamp branch from a signed reading of its pseudocode. Sixteen maintained
functions are checked by 1,510 original-x86 cases, including 36 connected frames
through life loss and game-over dispatch. Retained paddle/clock/reset dossiers
were reused, and the completed session saved 124 Evidence records. Platform
callbacks and non-game mode bodies remain explicitly unresolved.

Saved smoke verification (`scripts/repo-python scripts/verify-rea.py --saved`)
selects the latest completed archived smoke run. Interactive queries update
root convenience aliases, so those numbered aliases must not be mixed with an
earlier run. Verification checks the function address, target/snapshot binding,
loaded bytes, Evidence membership and completed close/save response. The shared
snapshot remains cumulative; stable run references preserve each query record.

## Connecting frame drawing

The [display investigation](DISPLAY_OWNER.md) follows the 1,057-byte last-brick
boss into deferred explosion requests, lightning and particle production, then
connects dirty-region restoration and the 984-byte rectangle merge/presentation
routine. REA's instruction/API evidence corrects the former surface-restoration
label to a frame/vblank wait. Sixteen entries pass 2,409 direct cases; 192 separate
continuous frames execute all twelve maintained gameplay phases. The session
saved 137 Evidence records. Actual platform drivers, recovery, audio and glyph/UI
work remain explicit rather than being inferred from those algorithm tests.

The [device investigation](DEVICE_OWNER.md) follows those callers into the
1,339-byte palette fade controller and lost-surface recovery. Assembly plus the
bank stride establishes that two former text-setting labels actually describe
the third bank's count and allocation mode. The source now shares that storage,
and lifecycle tests compare all bank metadata. Six entries pass 1,115 direct
cases plus 26 separate connected checks; the session saves 152 cumulative
Evidence records. Actual drivers, device creation, UI and audio still need work.


The [MDS/music investigation](MIDI_OWNER.md) reuses saved loader/parser
Evidence, then follows stream ownership and callbacks through eleven more
function dossiers. Instruction evidence corrects pseudocode return values 6/7
and establishes five stdcall callback arguments with RET 20. The independent
oracle checks all six original songs, bounded errors and connected playback
control; real WinMM delivery remains pending. Explicit close saves 236
cumulative Evidence records. Duplicate aliases are cleaned only after the
complete immutable run is archived and SHA-256 comparisons agree.

The DirectSound investigation collected 21 new queries in one interactive
session after checking saved dossiers, extending the snapshot from 236 to 257
Evidence records. Its initializer has fourteen inclusive body ranges; caller
instructions resolve an inferred-void allocator return, and recovery re-reads
records after reloading them. The [sound owner](SOUND_OWNER.md) distinguishes
these static observations from the original-x86 differential tests and pending
physical driver integration. Closing the session allowed hash-checked alias
cleanup to recover roughly 18 MiB without deleting immutable evidence.

## Capturing actual Windows probes

`scripts/repo-python scripts/capture-windows-probe.py --probe round` uses REA's
process recorder to run the existing Wine harness, preserving a declared
scenario, complete inline Evidence and the actual child exit. The original/VC4/
MinGW round control is process Evidence
`ev_8538d48e9383df10b6c761db2f40c701b75e713afdaf144caedaf983bb3d6a4e`.
This extends the showcase from static dossiers to process observation while
keeping the SDK memory reader and Wine API traces separately attributed.
The harness verifies full bank/board bytes and records its own product hashes.
See [round/focus evidence](ROUND_FOCUS_RUNTIME.md) for negative original focus
controls, retained limits and a reproduced numeric-normalization issue.

`scripts/rea capture-process SCENARIO.json --format json` still attests the
pinned REA installation. Unlike static dispatch, the recorder does not hold the
Ghidra/compiler lock: its repository child acquires that lock for actual work.
All text normalization is explicitly disabled for numeric SDK output. Recorder
success can contain a failed child; the public capture helper propagates that
child exit rather than promoting it to a passing game check.
