# Current handoff

Updated October 22, 2026. Read [progress](../PROGRESS.md) for the generated status,
[the build record](../research/CURRENT_VC4_BUILD.md) for products and
[playability results](../research/PLAYABILITY_20261022.md) for the latest runs.

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

## Next work

1. Diagnose focus recovery under Wine/Xvfb. Original and rebuilt controls fail
   the same fixed-interval motion check. Persistent rebuilt observation passes
   initial resumed motion, then times out returning to menu. Record actual X11
   keyboard focus/stacking and DirectDraw cooperative/surface state after the
   SDK foreground request. Preserve the existing failed controls for comparison.
2. Complete the original 50-board campaign and exercise every power-up in live
   play. The 50-board terminal fixture and the original-bank episode have their
   own recorded scopes.
3. Verify physical graphics/audio output and MIDI playback. Resume platform
   ports after current game validation.

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
