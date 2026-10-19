# Current VC4 build and play check

This is the last verified game image. The subsequent
[authored boundary corrections](exact/AUTHORED_BOUNDARY_CONTRACTS.md) and
[PCX coordinate correction](exact/PCX_COORDINATE_WRAP.md) and
[ranking coordinate subtraction](exact/RANKING_COORDINATE_WRAP.md), plus
[glyph destination coordinates](exact/GLYPH_COORDINATE_WRAP.md), change
resources.cpp, ui.c and gameover.c; this EXE/ZIP and its play evidence do not cover them.
The current matching objects/native library do include those corrections.

October 19, 2026. Source checkpoint `717cc2f4cb0748c62e04cdfd785b3ff9d007f7f7`
includes both sprite-bank byte-count and live count-bound recoveries. The current
restored-CRT game is rebuilt from that source and passes the existing actual
play/editor, round-transition and game-over flows under Wine. The22 authored
candidates remain nonexact.

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

## Round transition and game-over

Two existing lifecycle scenarios subsequently run on the same image. The round
observer uses its unchanged body and retained single-sample reader. Real editor
input creates one tile1 at column6/row18. Clearing it earns10 points, preserves
three lives and loads all400 bytes of original board1, with222 destructible
bricks. The saved20,000-byte bank retains the other49 boards. Normal exit0 and
127 observations complete in86.124s, peak250,834,944 bytes.

The first game-over observation reaches the unchanged90s life-loss deadline
with one life left, score222 and the last ball still descending at255,368.
Its last30 read intervals have a median around0.8s. Source/game identities are
unchanged; the failed observation is retained. This supports changing the read
transport, without independently proving the cause of every observed delay.

The accepted observation keeps both maintained `observe` and `lose_game` bodies,
all assertions and the90s life-loss deadline unchanged. It reuses the persistent
SDK reader for scalar/first-ball samples and the original reader for exactly
the same three complete660-byte table assertions. A fresh stream follows the
actual fresh game process. No game, reader, fixture or maintained test is changed
or compiled. Natural losses3→2→1→0 earn10/202/222. Typing `rex`, Backspace and
Shift-A produces `reA`; insertion at rank0 preserves the complete expected table,
including destination string tails. A second game process reloads the same660
bytes. Both exits are0. There are1,198 observations; total169.202s, peak258,371,584
bytes. The saved table SHA-256 is
`fcc15ac92dc92e402d565da1a7fb5a23afd42d544e3308096a47aba8f65c62e8`.

Both accepted scenarios average about34.08% of one CPU, under the same35%/
384MiB high/512MiB max scope with no high/max/OOM events. All49 originals and
current source/ledger/product identities stay fixed. Reviewed frames show the
complete heart-shaped second board, name prompt and `reA`/222 ranking.
Private `.analysis/current-vc4-lifecycle-20261019/` retains passing round and
`gameover-persistent` receipts, the failed `gameover` case and diagnosis, complete
files/captures, and the member-verified13-file evidence archive. Cleanup releases
2,002,944 allocated bytes net from closed evidence and1,724,416 from49 verified
automated runtime copies. Current products/caches and manual runtimes remain.

## Local delivery

`build/delivery/dxball-v1.07-vc40-reconstructed.zip` is the current private local
bundle:467,599 bytes, SHA-256
`d48e909a090207422edeaaf484d673d95dda9f148fda134c2c441c14910c8aed`.
Its50 byte-verified members contain the rebuilt executable,48 unchanged supplied
assets and extraction instructions. The original executable is excluded. Extract
the complete folder and run `dxball.exe` there. The adjacent manifest identifies
every member; original assets and this bundle remain outside Git.

These flows do not establish the full50-board campaign, focus/surface recovery,
physical graphics/audio fidelity or every exceptional path. It creates no new
exact/semantic ledger acceptance. Authored coverage remains248 exact/22 complete
candidates,393 overall exacts; final inventory and source optimality remain open.
