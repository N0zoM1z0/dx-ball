# VC4 build and play records

October 20, 2026. Source recovery remains the active task: **247 authored exact
functions and 23 complete nonexact candidates**. Overall totals are392 exacts
and83 candidates, including60 runtime candidates. The user reiterated that
source recovery comes before complete game verification. The checks recorded
below ran prematurely; they do not establish source readiness or completion.
Do not extend them into a campaign or repeat them as source progress.

The subsequent [text-width accumulator recovery](exact/TEXT_WIDTH_ACCUMULATOR.md)
improves its candidate to279/3. The tested bff527e products below predate that
source change and retain their recorded identities. No further game rebuild or
observation follows the source change.

## Current local products

The current restored-CRT executable is built from source checkpoint
`bff527e290098db516e3948905c92d1472ccb210`, including the last-brick Y subtraction
and all six Blt destination-edge sums. It is166,400 bytes, SHA-256
`76be8c25a07f972ff55465c47ea47a067434e84c669bf7f64c3cd96692b21db6`, at
`build/vc40-restored-crt/dxball.exe`.

The private bundle `build/delivery/dxball-v1.07-vc40-reconstructed.zip` is475,005
bytes, SHA-256
`b9e81852cb1e6096e0014835103548682396fcec648ea8f319daac0e543017b0`.
Its50 members are read back and checked by size, SHA and ZIP CRC: the current
rebuilt executable,48 unchanged supplied assets and unchanged extraction
instructions. The original score table is included; the automated test ranking
is excluded. The adjacent manifest records every member. Extract the complete
folder and run `dxball.exe` there. Products and supplied assets remain private.

## Build and linked contents

The pinned VC4 compiler10.00.5270/linker3.00.5270 build takes14.894s, reusing118
verified objects:115 source owners and three integration objects. No source is
compiled in this relink. The builder checks current compiler identity, flags,
source/header inputs and object hashes. It retains the19 explicitly approved
original CRT members under `/NODEFAULTLIB`.

Relative to the preceding12ccdb1 image, only display and resource source objects
change. All1,099 named map addresses remain fixed. Complete checks account for
673 file-backed sections/144,681 bytes across137 source/CRT objects and5,904
actual COFF bindings. All4,488 HIGHLOW fields have owners:4,485 actual COFF fields
and three complete SDK import-thunk fields. Five whole initialized-data
containers account for39 additional actual fields. Some private section bases
are inferred from actual linked fields, as recorded in the proof. Imports and
embedded resources remain fixed. This verifies the source/object linkage within
that scope; it adds no original-EXE exactness claim.

## Existing observations on this image

All three maintained flow bodies and their assertions remain unchanged. The
basic flow retains its20s readiness deadline. The game-over flow retains its90s
life-loss deadline. No game or reader is compiled or patched during these runs.

| Existing flow | Observed result | State observations | Seconds | Peak bytes |
| --- | --- | ---: | ---: | ---: |
| Basic/editor | Opening/menu, ball/paddle, pause/resume, editor painting, save/reload, exit0 |541 |81.822 |264,458,240 |
| Round transition | Real brick clear, score10, three lives, complete original board1/222 bricks, exit0 |130 |77.190 |239,632,384 |
| Game-over/restart | Natural losses3→2→1→0, name editing, ranking persistence, fresh-process reload, two exits0 |1052 |152.225 |277,860,352 |

Basic play uses the retained persistent SDK reader, with2,134 valid samples and
zero malformed samples. Fourteen additional read-only scalar fields observe
menu initialization. Return-menu readiness spans13.699s in the recorded samples;
the deadline remains20s. A diagnostic capture hook for deadline failure is not
triggered. Editor painting saves exactly two tile2 cells; next/previous, clear,
L reload and a second S verify the complete20,000-byte bank, SHA-256
`b88441eb5e06676a106501a60a450b8046fa7b880e8f53ffe5f556ae75a42cd2`.
Reviewed pause/editor/menu captures show the original board and PAUSED glyphs,
two yellow editor cells, and the DX-Ball title/bonus legend.

Round transition reuses the retained single-sample reader. Real editor input
creates one tile1 at column6/row18. The20,000-byte edited bank retains the other49
boards; all400 loaded bytes match original board1. Game-over reuses the persistent
reader for scalar/first-ball observations and the original reader for exactly
three complete660-byte score-table reads. Its two streams have4,089 valid SDK
samples and zero malformed samples. Natural losses earn10/202/222; `rex`,
Backspace and Shift-A produce `reA`, inserted at rank0. The entire persisted table
and fresh-process reload match SHA-256
`fcc15ac92dc92e402d565da1a7fb5a23afd42d544e3308096a47aba8f65c62e8`.

All49 originals and frozen source/protected inputs remain unchanged in each
flow. Recorded owned controller/game/reader identities are absent afterward.
Heavy operations run serially on CPU0, capped at35% CPU,384MiB memory high and
512MiB max. Build peak is172,982,272 bytes. All operations record zero high/max/
OOM events; play averages33.39%,34.06% and33.79% of one CPU respectively.
Audio uses the silent sink; the default sink remains unchanged.

These observations cover existing Wine scenarios. Full50-board play,
focus/surface recovery, physical graphics/audio fidelity and exceptional paths
remain unverified. No exact or semantic ledger acceptance changes.

## Retained history and evidence

The previous12ccdb1 image, SHA-256
`4d962eaaa2c6070047ffeb8e1edfb390f092a01b1f8e27eadda685242b217846`,
failed its20s return-menu deadline after pause/resume. Its cause remains
unresolved. Passing on the current image does not prove that historical cause
or identify a fix. Complete failed evidence remains under
`.analysis/current-vc4-refresh-20261019/`, together with retained image history.
The earlier717cc2f image and delivery have their own passing records in
[the preceding note](https://github.com/N0zoM1z0/dx-ball/blob/bff527e290098db516e3948905c92d1472ccb210/docs/research/CURRENT_VC4_BUILD.md).

Current private authority is `.analysis/current-vc4-build-20261020/`: complete
linked section/binding and loader proofs, frozen inputs, executed helpers,
observations/captures, complete banks/tables, per-flow verification/resource/
process receipts and all50 delivery member identities. Preserve unique evidence
before removing closed copied inputs/helpers or verified isolated runtime copies.
Nineteen closed copied-input/helper files are member-size/SHA verified in a
1,731,770-byte archive before exact-list removal, releasing1,654,784 allocated
bytes net before small receipts. All183 protected identities stay fixed.
Forty-nine isolated runtime copies are removed after matching retained current
image, original assets or the complete saved ranking, releasing1,724,416 bytes.
Current products, useful caches, manual runtimes and historical failure stay.

Resume concrete source questions in the23 authored candidates. Original
source declarations/compiler context and the final inventory proof remain open;
these build/play records do not close them.
