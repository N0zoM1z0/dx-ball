# Editor persistence through the restored CRT

The current 19-member `vc40-restored-crt` game passes the existing real-input
ball/pause/editor flow. This checks actual board-file persistence through the
source CRT, beyond the earlier first-board startup selection. It does not add
source, exact or semantic-ledger claims.

The same image subsequently passes [natural game-over and ranking persistence](RESTORED_CRT_GAMEOVER_FLOW.md),
including a fresh process reading the complete saved score table.

The public observer now accepts this profile, validates its executable/map,
complete build inputs and actual source objects, then derives read addresses
from the map and emitted board-storage layout. The existing cases, input
sequence and assertions are unchanged. A new selector allows one profile:

```bash
scripts/repo-python tests/test_windows_play.py --profile vc40-restored-crt
```

Use a current restored-CRT build and the resource scope/silent sink described
in [REA commands](../agent/REA.md). The adopted run reuses the hash-verified
state-reader executable and game image, with no game or reader compilation.
The public entry retains its existing reader-build step when run directly.
Other profiles and historical controls are not rerun for this selection.

## Actual observations

One Wine process produces 159 read-only state observations. Real mouse input
moves the paddle to 480 and 200, releases the attached ball and changes its
coordinates. P pauses the ball state for 0.5 seconds after input is processed;
another key resumes motion.

In the editor, real CTRL painting writes two tile 2 cells. S saves exactly
20,000 bytes: the first board contains those two cells and 398 zero cells;
the other 49 boards retain all original bytes. Next/previous board navigation,
Backspace and L restore the saved working board. Removing the isolated working
file and pressing S recreates the complete expected bank, proving the reload
and subsequent write together. Escape returns to mode 0; the next Escape exits
with code 0 and removes the window. All 49 original files remain unchanged.
The reviewed editor-reload image shows the two painted cells. Conclusions use
live state and complete disk bytes rather than screenshot changes alone.

The PE entry is the maintained 10-byte Windows adapter under both actual
bindings. All 17 selected board/stdio/low-I/O bodies, totaling 3,006 bytes and 86
bindings, agree with their source objects in the executed image. Both complete
rb/wb literals are attested. The link uses the source fopen/fread/fwrite/fclose
adapters and implementations, with no imported MSVCRT. This is source-to-linked
verification, not seventeen new original-function exact claims.

## Bounded original-code coverage

The declared complete target spans cover 289 source-present units in
`0x401000..0x4165FF`. Every gap consists entirely of CC bytes: 2,145 bytes in 259
intervals. All 270 currently authored entries lie in this range, alongside 18
compiler-generated entries and the already source-present unknown 40CC20.
That unknown remains unknown. This address/extent check does not establish a
final authored denominator, new semantic fidelity or complete CRT coverage.
No function is added or removed from the inventory.

## Retention and limits

All function, source, origin, exact, semantic and comparison ledgers remain
byte-identical: 545 inventory / 475 source / 380 exact / 95 complete candidates.
No full replay or new provider query runs. Remaining function recovery,
exceptional paths, complete gameplay and native Windows/driver fidelity remain
open. Ports remain deferred.

Private evidence is `.analysis/restored-crt-editor-20261017/`: `report.json`,
`verification.json`, `coverage.json`, state observations, saved bank, captures
and logs. Full executed-image/map/reader gzip carriers roundtrip byte-for-byte;
the observation helpers are frozen. After retaining unique evidence, 49 verified
automated working copies are removed, releasing about 1.4 MiB net. Other profile
and manual runtime directories are untouched. Heavy work stays serial under
CPU 35%, memory high 640 MiB/maximum 768 MiB.
