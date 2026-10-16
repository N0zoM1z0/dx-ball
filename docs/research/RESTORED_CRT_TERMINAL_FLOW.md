# Terminal boundary through the restored CRT

The current `vc40-restored-crt` image clears all 50 editor-created single-brick
boards, returns to the menu at index 50 with three lives and 500 points, passes
the original adjacent-storage fixture and exits zero. This completes that
selected terminal check for the user-approved 19-member CRT configuration.
Game source, objects and all function claims remain unchanged.

The maintained observer now accepts the restored-CRT profile:

```bash
scripts/repo-python tests/test_windows_terminal.py --profile vc40-restored-crt
```

Use the resource scope and silent sink in [REA commands](../agent/REA.md).
The adopted run reuses the current executable and SDK reader without compiling
either. Only this profile runs. The direct public entry retains its reader-build
step; default profile selection remains the three historical controls.
The Xvfb depth is now selectable, defaulting to 24 for the original palette here.

## Observed game and storage

Real editor keys and CTRL painting create one tile1 at column 6 / row 18 in every
board. S must save the complete expected 20,000-byte bank. Each of the 50 game
starts requires the full 400-byte board, one brick, an attached ball, three
lives and the expected score. Real paddle input and clicks release the balls.
All 49 intervening stable initializations and the terminal routing are checked.
The passing run records **1,608 read-only states** and one game process.

At index 50, the unchecked loader reads 400 bytes starting at bank+20000 and
copies them to the tile buffer at bank+20032. The 368-byte overlap requires the
recovered `memmove` behavior. The terminal tiles contain the variable clock
bytes, the expected empty request region, a ball-count DWORD of one and the
zeroed suffix. Their complete 400 bytes are retained. The SDK also reads the
400-byte source window before the last release and at the terminal state;
its last 368 bytes agree with the corresponding tile prefix. These source
samples span 400 bytes. The complete adjacent region and tile buffer span 432.

The observed terminal brick count is three, consistent with the actual bytes
and the exclusion of tile values 0 and 2. Clock bytes vary, so three is an
observation rather than a fixed contract. The complete edited bank is checked
again after normal shutdown. All 49 original files remain unchanged. The reviewed
terminal capture shows the menu and `Last Score - 500`.

The editor uses the synchronized CTRL-paint sequence already established by
the [round observer](RESTORED_CRT_ROUND_FLOW.md). All six assertion nodes in
the terminal observation function, its final routing predicate and its storage
predicate remain AST-identical. Existing stable next-board checks and the
sampling-safe clear waiter remain in place. No game behavior changes.

## Nonzero overlap and linked implementation

A separate private x86 check executes the unmodified original and current VC4
PE instructions for `load(50)`, `store(50)` and `initialize(50)`. Each starts with
the same nonzero 20,432-byte storage image and nonzero auxiliary grid. All six
executions preserve the expected whole-image state, exact 400/800-byte image
write footprints, caller stack, nonvolatile registers and clear direction flag.
The resulting complete storage agrees between original and reconstruction.
Both overlap directions are exercised. The original CRT copy entry and the
current `memmove` adapter/recovered copy body are observed executing.

Eight complete source bodies agree with the executed image after all
**23 bindings / 729 bytes**: load/store/initialize, level advance, memory copy,
memory fill and the two CRT adapters. The earlier round and editor linkage
receipts also remain valid for this identical executable. No MSVCRT DLL is
imported. The image SHA-256 remains
`cbe767d19d7adc1363facdc862652d2c42342ba50bb01ec4d8eca57383183cfe`.

These three fixed emulator cases supplement the natural empty-board fixture;
they add no all-input semantic acceptance. The [original boundary research](TERMINAL_RUNTIME.md)
retains the REA instruction evidence and broader earlier storage controls.
REA remains pinned to 6.5.0. No new provider query or full replay runs.

## Evidence and remaining scope

Private `.analysis/restored-crt-terminal-20261017/` retains the CLI run, states,
50 transition rows, full bank, tile/source samples, captures, executed inputs,
selected objects and original/current emulator results. A private verifier's
initial 432-byte sample assumption is retained with its correction to the
existing 400-byte reader contract; the passing game is not rerun. Executable,
map and reader carriers are reused only after full-byte verification.

After preserving evidence, 49 verified automated runtime files are removed and
235 frozen inputs are archived with complete byte checks, releasing 2,899,968
allocated bytes across those operations. Heavy work is serial under CPU 35%,
memory high 640 MiB / maximum 768 MiB. A retained live sample confirms the cap
and about 238 MiB peak memory at that point; it is not a final peak measurement.

Totals stay **475 source / 380 exact / 95 candidates**, including 34 authored
candidates. Those authored candidates remain the priority. This 50-custom-board
fixture does not establish the original campaign, all terminal states, focus
recovery or physical graphics/audio fidelity. The reconstruction remains
unfinished and platform ports stay deferred.
