# Current handoff

Updated October 31, 2026. Read [progress](../PROGRESS.md) for the generated status,
[the build record](../research/CURRENT_VC4_BUILD.md) for products and
[playability results](../research/PLAYABILITY_20261031.md) for the latest runs.

## Completed

- All 270 authored functions and 84,968 authored code bytes are exact across
  53 compiler closures. The closing audit checks 4,759 code bindings, 252 full
  literal references and current recursive source/header/flag/object identities.
- The restored-CRT VC4 game links 138 source objects, three integration objects
  and 19 approved original CRT members. Its 53 authored recipes use the audited
  objects. Source checkpoint: `ecfc475715238c43241a5979b1745a163749b9dc`.
- Basic play, pause/resume, editor save/reload, real round transition, natural
  life loss, name editing and full ranking reload pass. Fifty editor-created
  single-brick boards clear through terminal routing/storage and normal exit.
- A 900.046-second original-bank episode reaches board index 2, with final
  sampled score 2,718/lives 3 and 27,596 valid samples. The verified game stream
  produces 5.991678 seconds of finite stereo PCM with nonzero signal.
- October 31 isolated Wine checks pass built-in basic/editor and cnc-ddraw
  basic/editor plus 960×720 game-over/ranking/restart flows. The user reports
  no major issue in Windows 11 windowed play. Keep that feedback scoped.
- Native Windows compilation passes all 141 units. Its 270 authored functions
  remain exact across 53 closures; the linked image differs from the tested
  game only in PE/resource timestamps. The linker child uses `WIN7RTM`; source
  compiler flags and game bodies are unchanged.
- Original Windows WAV/MIDI assets are restored after the temporary muted copy.
  The native source package has English recording/build launchers and progress.

## Current work and remaining coverage

The user stopped full background testing and frame sampling, then requested
documentation/folder cleanup, restored sound and a Windows recording build.
Do not restart the historical test queue merely because coverage remains open.
Keep the progress graphic focused on 270/270 authored functions; broader
runtime inventories remain in the ledgers and status CLI.

Unverified scope remains: the original 50-board campaign, every power-up in live
play, exclusive focus/surface recovery and complete native audio/MIDI/frame
pacing. The windowed wrapper filters activation messages, so its failure to
enter the exclusive fixture's inactive state is a contract mismatch, not a
surface-recovery pass. Retain the October 22 failures separately.

Follow [background execution](BACKGROUND_PLAY.md) for future requested Wine
checks. Never drive the user's Windows/WSLg input desktop. Native build checks
do not launch a Windows game automatically.

## Artifacts and evidence

| Record | Location |
| --- | --- |
| Current game and map | `build/vc40-restored-crt/dxball.exe`, `dxball.map` |
| Full link inputs and objects | `build/vc40-restored-crt/build.json` |
| Local delivery and member manifest | `build/delivery/dxball-v1.07-vc40-reconstructed.zip`, adjacent `.manifest.json` |
| Authored closing audit | `.analysis/pcx-file-prefix-source-search-20261022/completion-audit.json` |
| Current link/basic/editor/round checkpoint | `.analysis/current-vc4-exact270-20261022/current-checkpoint.json` |
| Expanded validation and cleanup | `.analysis/playability-exact270-20261022/current-checkpoint.json` |
| Expanded REA process responses | `.analysis/rea/playability-exact270-20261022/` |
| October 31 Wine process responses | `.analysis/rea/wine-background-20261101/` |
| Native Windows object/image comparisons | `.analysis/native-windows-build-20261101/` |
| Native rebuilt EXE | `build/dxball-native-windows.exe` |
| Native Windows package exporter | `scripts/export-windows-build.py` |
| Public verification metadata | `config/playability-status.json` |

The final PCX, last-brick, rotation and other source recoveries are indexed in
[exact notes](../research/exact/README.md). Closed helper/input copies are in
member-verified archives beside their receipts. The full preceding handoff is
available in [Git history](https://github.com/N0zoM1z0/dx-ball/blob/9752a6954ec1bea5da2885ba236ca51a5c8976a0/docs/agent/HANDOFF.md);
[October21 history](HANDOFF_HISTORY_20261021.md) contains earlier checkpoints.

## Before the next change

```bash
git status --short
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

Use [AGENTS.md](../../AGENTS.md) and the [workflow](WORKFLOW.md) for execution,
source changes and publication. `replay-exact-units.py` compiles selected owners;
use the retained audit for status-only work.
