# Current handoff

Updated November 10, 2026. Start with [progress](../PROGRESS.md),
[the current build](../research/CURRENT_VC4_BUILD.md) and
[playability](../research/PLAYABILITY_20261031.md).

## Current result

All 270 authored functions and 84,968 code bytes are exact across 53 compiler
closures. Complete comparisons include code, relocations, literals and attached
metadata. The current VC4 game links 138 source objects, three integration
objects and 19 explicitly approved original CRT members.

The tested EXE is `build/vc40-restored-crt/dxball.exe`, SHA-256
`bdd425241ba51d6fe671bb0184b4ad86062326fc9e1eb407d2536235b93df79c`.
Its map, objects and `build.json` remain beside it. The local delivery is
`build/delivery/dxball-v1.07-vc40-reconstructed.zip`; the current runtime copy
is `build/runtime/vc40-restored-crt/`. The native Windows EXE is
`build/dxball-native-windows.exe`.

Basic play, pause/resume, editor save/reload, real round transition, natural
life loss, name editing and ranking reload pass. Fifty editor-created
single-brick boards clear through terminal routing and normal exit. The
900-second original-bank episode reaches board index 2. Game-stream digital
audio has finite nonzero stereo PCM. October 31 isolated Wine checks cover
built-in and cnc-ddraw windowed play/editor/ranking flows. Windows 11 windowed
play is user-reported, not a complete native validation.

Native Windows compilation passes all 141 units and complete authored
comparisons. Only build timestamps differ from the tested image. The linker
child needs `WIN7RTM`; the compiler recipes remain unchanged. Export a fresh
native source package with `scripts/export-windows-build.py` when needed.

## Remaining work

Exclusive focus/surface recovery is unresolved. The original and rebuilt
Wine/Xvfb controls fail the October 22 motion check. A windowed wrapper that
filters activation messages does not satisfy the exclusive fixture's contract.

The original 50-board campaign, every power-up in live play, and complete native
audio/MIDI/frame pacing remain unverified. Broad background testing and frame
sampling were stopped by the user; do not restart them automatically. Never
drive the user's Windows/WSLg input desktop. Use [background execution](BACKGROUND_PLAY.md)
for requested live checks.

Runtime source/comparison work remains separate from completed authored
recovery. See [runtime follow-up](../research/exact/REMAINING_EXACT_FUNCTIONS.md).
Platform ports follow game validation.

## Continue efficiently

```bash
git status --short
scripts/repo-python --stdlib scripts/ci.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

The default CI needs Python 3.11+, CMake and a host C/C++ compiler; no private
inputs or analysis packages. Add `--build` for a portable compilation. Choose
complete comparisons and behavior checks for changed owners. Do not replay an
unchanged historical queue for documentation work.

Keep inputs, current products and concise useful conclusions. Raw historical
experiments and cleanup journals are disposable. Retain a hard-to-rebuild
compiler context only when a current unresolved question actually needs it.
See [workflow](WORKFLOW.md) and [AGENTS.md](../../AGENTS.md).
