# Actual round transition and focus diagnostics

The original, VC4 and MinGW Wine controls now clear an editor-created board,
load the next untouched original board and exit normally. This closes one
connected runtime path through the maintained editor, collision, round and
resource controllers. Successful focus recovery is still unverified: the
original control stalls after a brief resume under the installed Wine/Xvfb setup.

## Reproduce the round control

After the original import and both Windows builds described in
[Windows integration](WINDOWS_ADAPTER.md):

```bash
scripts/repo-python tests/test_windows_round.py
scripts/repo-python scripts/capture-windows-probe.py --probe round
```

The second command runs the same probe through REA's `capture-process` workflow.
Completed original/VC4/MinGW Evidence
`ev_8538d48e9383df10b6c761db2f40c701b75e713afdaf144caedaf983bb3d6a4e`
records child exit0 and the bounded before/after report observation.
It retains the declared scenario, complete inline Evidence, child exit and
bounded filesystem observations under ignored `build/reports/rea-process/`.
The harness independently retains its states, screenshots and file identities;
REA's process recorder does not itself read the game's globals or trace DirectDraw.
The child acquires the project compiler/Wine lock and runs on one allowed CPU.
The recorder must not hold that lock while waiting for the child.

Actual keys enter Control-F1, clear board0 and select tile1. A click paints one
destructible brick at column6/row18; S saves the complete 20,000-byte bank.
All other 49 boards must remain byte-identical to the imported bank. Escape
returns to menu, and a click starts the edited board with one remaining brick,
three lives and an attached ball. A real paddle position and click release the
ball; collision removes the brick and awards a positive score.

The next completed initialization must select board1 with an attached ball,
three lives, the earned score and all 400 tile bytes equal to the untouched
original second board. Its destructible-brick count is 222. Two Escape inputs
must complete the return to menu and exit with code zero, with no game window
remaining. The full saved bank is checked again after exit. All49 immutable
originals are reverified. No target memory writes, hooks or injected calls are used.

Original addresses and the ball layout reuse reviewed REA/oracle contracts;
VC4 globals come from its attested linker map and MinGW globals from its actual
remote DLL exports. The SDK reader adds a bounded400-byte board snapshot. Reads
are sequential, not atomic frame snapshots. A passing `round-prefix.json` covers
only the transition before subsequent checks; the aggregate report requires
normal shutdown too. This control does not prove completion of all 50 original
boards, terminal board50 behavior, synchronized frames or physical audio.

## Retained negative focus evidence

```bash
scripts/repo-python scripts/capture-windows-probe.py --probe focus --profile original
```

This diagnostic continues after the round transition. An ordinary SDK peer
window takes focus; the game becomes inactive, requests surface restoration and
freezes its ball state over 0.5 seconds. Enter in the peer uses ShowWindowAsync
and SetForegroundWindow to restore/activate DX-Ball. The original resumes briefly,
then stops making progress. Clearing the restore-request flag and observing
temporary movement therefore do not establish successful recovery.

REA process Evidence
`ev_5ad3d1327d2c95128b6dfa66906d9288c516119beb41d09c8e63f7aec3b2e1d1`
records the failed original trace control; warning/descriptor follow-up Evidence
`ev_586c8a7cc714f9fcfe5348f32b6baf901f7142a7141b03fbbd36d6a25c7cac8c`
also records child exit1. The recorder's successful operation is not a successful
game run. These are process observations, distinct from the static Ghidra dossiers.

The separately collected Wine9.0 DirectDraw trace retains 552,707 surface1 Lock
calls in a bounded 64 MiB prefix. A 2 MiB warning prefix contains 35,506 lost-surface
warnings. The prefixes compress to766,256 and14,197 bytes respectively; both
are explicitly truncated, and full emitted streams were not stored. Before
terminating the owned control, ReadProcessMemory inspected the descriptor at
the preceding actual Lock trace's stack address `0x0031FDB4`: size108,
dimensions640x480, pitch640 and null pixel pointer. The invalid-size hypothesis
is refuted by that observation. No target thread was suspended.

The [Wine9.0 surface implementation](https://github.com/wine-mirror/wine/blob/wine-9.0/dlls/ddraw/surface.c)
checks descriptor size and returns SURFACELOST before entering its internal
lock when the surface is lost. That is consistent with the observed repeated
wrapper calls and warnings. The installed Ubuntu Wine may include distribution
patches; tag source is corroboration, not an attestation of its compiled binary.
The same control logs report unavailable OpenGL context/pixel-format creation.
The driver failure's complete cause, a successful recovery path and equivalent
behavior on physical Windows remain unresolved. Accepted game bodies were not
changed to make this control pass.

A focused REA xref query for compatibility state `0x422898`, Evidence
`ev_87c213a753df45ee0ad7d13d56878ad28429a5776c4261e87e169621f9919faf`,
finds nine exact references. Their retained instruction dossiers all show CMP
reads, including WinMain's mode selection and the recovery/palette/paddle
consumers. No direct writer appears in that exact-reference set. This bounded
result does not rule out indirect writes or establish a supported command-line
switch; no compatible-mode input or target-state override was invented.

## Numeric output and evidence limits

REA's default port normalization replaces compact JSON numeric values following
a colon, including SDK sizes and scores, with `<port>`. The minimal default
reproduction is Evidence
`ev_8be5d02a2b49a47b17e39dc6916115089bb995cfaada67a7e061632e808055ff`;
explicitly disabling text normalization preserves those numbers in
`ev_632d60d374d45f50fe8f3d138e1952ce79c51035684bbbd95dd77342291f6506`.
The public capture helper declares paths/PIDs/ports normalization false.
Numerical findings from the earlier focus captures use the retained local SDK
JSON rather than normalized terminal text. Feedback and minimal scenarios are
saved privately for REA development.

REA notes that artifact identity is unavailable for these process observations,
process trees are sampled and may miss short-lived descendants, filesystem
snapshots are not syscall traces, and inherited environment is not recorded.
The child harness's explicit original/product/input hashes remain necessary.
Owner semantic and exact acceptance counts remain 214 /95,873 /40 /4,079 bytes.


VC4 and MinGW diagnostic runs also fail the sustained-motion check: both
resume after activation, then retain the same ball fields at x227 across the
following 0.5 seconds. Their captured child exits are 1 in Evidence
`ev_f547b440ad36fd349e8dbcf71c1fb604162f171b33d0a4b6109d89d759a1e1bb`
and `ev_c3c754090233525c53353e4c6534aacacce239e92a09e39fb206a2a7d76ae431`.
This corroborates the failure symptom across builds; no API trace was collected
for those two runs, so their precise HRESULT sequence remains unobserved.
The recorder helper correctly returns the failed child's code.
