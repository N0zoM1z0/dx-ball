# Current VC4 build and play check

October 19, 2026. Source checkpoint `717cc2f4cb0748c62e04cdfd785b3ff9d007f7f7`
includes both sprite-bank byte-count and live count-bound recoveries. The current
restored-CRT game is rebuilt from that source and passes the existing actual
play/editor flow under Wine. The22 authored candidates remain nonexact.

## Build and linked contents

```bash
systemd-run --user --scope --quiet \
  -p CPUQuota=35% -p MemoryHigh=384M -p MemoryMax=512M \
  scripts/repo-python scripts/build-legacy.py --restored-crt
```

The pinned VC4 compiler10.00.5270/linker3.00.5270 build completes in17.003s.
All118 objects are reused after checking current source/header inputs, flags,
compiler identity and object hashes. They comprise115 source owners and three
integration objects. The resource object comes from the preceding focused VC4
compile; no second resource compilation is needed. The link retains the19
explicit user-approved original CRT members and uses `/NODEFAULTLIB`.

Product: `build/vc40-restored-crt/dxball.exe`,166,400 bytes, SHA-256
`f0f2fa2eefaa48aceb23b150dd894ee2daf6db13efe709f98c8cacacfcb8b5d4`.
The only changed source object relative to the preceding delivery is resources.
All1,099 named map records retain their addresses. Imports and embedded game
resources remain unchanged.

Complete linked checks cover673 file-backed sections/144,666 bytes from the137
source/approved-CRT objects, with5,904 actual COFF bindings. Actual linked fields
anchor some private section bases; that inference is recorded. Five additional
whole initialized-data containers and three complete SDK import thunks account
for the remaining loader fields. All4,488 HIGHLOW fields are owned:4,485 actual
COFF fields and three SDK-thunk fields. This establishes the current source/object
linkage within that scope, without claiming original-EXE byte identity.

## Existing actual play flow

The maintained `test_windows_play.observe` body runs unchanged. Its read
transport uses the retained persistent SDK reader at SHA-256
`f9dda62006f50395eb367cd0b60ea8137dbaa9cad58348a39ceafb2df4f4a8a1`.
The first observed ball-list node supplies the existing first-ball view. Input
uses ordinary X events; the reader opens the game for read/query/synchronization.
No game state or instructions are patched, and no game/reader is compiled during
this run. The display is640×480 at24-bit host depth; audio uses the silent sink.

The run passes opening/menu entry, attached-ball initialization, paddle movement
to480 then200, ball release and motion, half-second pause stability after input
processing, and resume. Actual editor CTRL painting saves exactly two tile2 cells
and the unchanged49 later boards. Next/previous board, clearing, L reload and a
second S recreate the complete expected20,000-byte bank. Editor Escape reaches
the completed menu; the next Escape exits0 and removes the game window.

There are589 recorded state observations and2,444 valid SDK samples, with zero
malformed samples. The complete saved bank SHA-256 is
`b88441eb5e06676a106501a60a450b8046fa7b880e8f53ffe5f556ae75a42cd2`.
All49 originals stay fixed. Reviewed pause/editor-reload/menu captures show the
board and PAUSED text, the two yellow cells/editor controls, and the DX-Ball title
and bonus legend respectively. All three recorded owned process identities are
absent after exit.

Build peak memory is174,387,200 bytes. Play takes86.614s, averaging33.42% of one
CPU and peaking at367,554,560 bytes. Both use CPU0/35%, memory high384MiB/max512MiB,
with zero high/max/OOM events. The default audio sink stays unchanged.

Private authorities are `.analysis/current-vc4-build-20261019/` and
`.analysis/current-vc4-play-20261019/`: current linked summary, full archived
section/binding proof, loader ownership, frozen inputs, executed observer,
complete states/files/captures and execution/verification receipts. Seven closed
build-helper/evidence files are member-hash verified in a140,888-byte archive,
releasing1,572,864 allocated bytes net before the receipt. The49 automated runtime
copies are removed only after matching retained originals, current game or the
complete saved bank. Current products, useful caches and manual runtime files stay.

This flow does not establish the full50-board campaign, focus/surface recovery,
physical graphics/audio fidelity or every exceptional path. It creates no new
exact/semantic ledger acceptance. Authored coverage remains248 exact/22 complete
candidates,393 overall exacts; final inventory and source optimality remain open.
