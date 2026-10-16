# Real game through the restored CRT entry

The optional `vc40-restored-crt` build now starts the actual game through the
recovered CRT. A small Windows entry adapter installs the real API bindings,
then calls the unchanged `dxball_crt_startup`. It creates no second heap and
does not repeat initialization. The existing host-CRT game build remains the
default.

Use the resource scope described in [REA commands](../agent/REA.md) on this host:

```bash
scripts/repo-python scripts/build-legacy.py --restored-crt
scripts/repo-python scripts/run-windows.py --profile vc40-restored-crt --prepare-only
```

The first command builds only the game under `build/vc40-restored-crt/`.
The second prepares an isolated Windows directory; omit `--prepare-only` to
launch it. The same original assets and compiler prerequisites apply.

## Source and original boundaries

[The checked link recipe](../../config/restored-crt-link.json) names every
input and preserves the verified initializer order. It uses 113 maintained
source objects, three integration objects, 21 pinned original library members
and the resource object, with `/NODEFAULTLIB`.

`runtime_legacy_imports.c` binds the original CRT names to their existing typed
implementations, including allocation, normal/quick exit, onexit, stdio,
strings, case conversion, matherr and the x87 exception bridge. The C++ adapter
preserves the original unhandled-filter link name and delegates to the
maintained filter. These adapters are integration glue; they add no original
function or exact claim. Original memcpy grouping and member-call tail-frame
differences remain described in their owner notes.

The original members still supply thirteen x87/control/kernel modules, four
C++ frame/hooks/transport modules, two SEH modules, signed64 division and the
stack probe. In particular, the C++ frame dispatcher and terminal callback
hooks remain original code in this profile. Their presence is not evidence
that the corresponding recovered source is integrated. The exact remaining
members, archive offsets and full hashes are explicit in the recipe.

No original stdio, allocation, CRT startup, onexit or matherr owner is silently
pulled from a default library. This resolves the earlier whole-LIBC collision
without forcing duplicate definitions. Shared COFF common variables merge
normally: the actual matherr marker, FP initializer pointer and argument count
resolve to their maintained source owners. Source string/stdio adapters also
remove the preceding entry probe's original memmove/strncpy dependencies.

The initial three integration files compile once. All 113 preceding objects
retain complete current inputs, flags and product identities. The public
builder then reuses all 116 objects and compiles none. Its receipt records each
producer, original member, resource and import library. Cold builds use the
public recipes and pinned library; private analysis files are not required.
Changed products and preceding build receipts are retained in the profile's
history directory. Resource conversion stays inside that profile's directory.

## Actual first-board evidence

One real Wine process uses the original copied data and existing observation
helpers. The state reader is reused, not recompiled. Its addresses come from
the actual map and emitted board-layout record. The adopted run establishes:

- Opening mode 4, then menu mode 0 after input.
- First-board mode 1 with all 400 tiles equal to the original first board,
  168 remaining bricks, three lives, zero score and one attached ball.
- Real release and subsequent ball movement.
- The same nonzero private-heap handle throughout the observed phases.
- Return to menu, normal exit code zero and no surviving game window.

Reviewed captures show the actual menu and first board. All 49 original files
remain unchanged, and copied asset contents remain equal after the run.
Audio APIs remain active through the project's silent sink.

An earlier screenshot-only run is not used as first-board evidence: its frame
change still showed the opening fade. The adopted run uses live state and
reviewed images. The first launch also encountered a sound dialog because the
null sink was absent; using the existing sink-creation helper resolves that
environment issue without changing the game. Those diagnostics are retained.

## Linked verification and limits

The public image's full code, read-only data, writable data, imports,
relocations, virtual extents and entry address agree with the executed image.
Resource payloads, identifiers, addresses and all other resource bytes agree;
only resource-directory and PE timestamps vary. This static comparison reuses
the completed process observation without another gameplay run.

The complete 390-byte CRT entry and 12-byte scope record agree with their
source object under all 34 code and two scope bindings. The scope is located
independently by its unique relocated contents. Retained integration bodies
also agree with their actual source objects. The full 84-byte CRT table keeps
all thirteen original callback bindings and stdio-before-onexit ordering.

Function/source/origin/exact ledgers and both comparison reports are unchanged:
545 inventory entries, 475 source entries, 380 exacts and 95 complete candidates.
The builder is a declared input of four termination semantic rows. Reusing the
existing native library, the affected 1,031 original/native cases pass with the
same complete observation projection. Only those four builder-input hashes are
refreshed; all scopes/counts and the other 245 rows remain unchanged.
No full replay or new provider query runs. CPU remains capped at
35%, memory high 640 MiB/maximum 768 MiB, with serial heavy work on one CPU.
REA remains pinned to 6.5.0.

After adoption, 603 unused member-cache copies are removed only after full
byte equality with the pinned archive is checked. All previously selected
diagnostic members remain. Sharing 51 identical immutable header snapshots
brings the allocated-storage reduction to about 2.8 MiB. Unique observations,
failures, history, current build products and runtime data are preserved.

This is a first-board integration checkpoint. Remaining function recovery,
C++ frame/callback-state integration, x87/SEH transport source, exceptional
game paths and complete playability remain open. Ports still follow that work.
The MinGW CRT errno macro issue is unchanged; this optional profile uses VC4.

Private evidence is `.analysis/crt-game-members-20261016/`: `archive-catalog.json`,
`source-closure.json`, `link.json`, `state-startup.json`, `state-startup/states.json`,
`verification.json` and `adoption.json`. Complete library members, failed
diagnostics, source snapshots and reviewed images remain private.
