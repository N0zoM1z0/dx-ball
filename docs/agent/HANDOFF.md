# Current reconstruction handoff

Continue toward nearly complete original game source and a rebuildable,
playable game. Recover complete flows with REA, compile stable families and
run only useful affected comparisons and existing Oracles.

## Current checkpoint

The [initialization batch](../research/exact/EXACT_WINDOW_INITIALIZATION.md)
restores both complete fullscreen and compatible initialization flows, including
original record field writes, shared HRESULT storage, direct sound preparation,
COM output publication and live global receivers. All 23 Windows services now
have independent import cells. The authored WindowApi table is removed;
Windows and the native fixture bind the same contracts. `platform_host.c`
forwards the named DirectDrawCreate boundary to its bound SDK factory.

- 283 source-present functions; 135 exact functions / 20,973 code bytes.
- One stable compile per 27 recipes; 130 complete comparisons / 1,519 actual
  relocations. 127 of 128 affected accepted functions remain exact.
- Fullscreen is candidate at 1,406/1,343 with 1,278 differing positions;
  compatible is 1,180/1,147 with 1,092. Record allocation differs from the
  original. No local-layout, identifier or compiler-profile variants were tried.
- `refresh-score` moves to candidate after its operand order changes emission.
  The original accepted object and complete prior inputs remain preserved.
- Existing Platform Oracle: 4,742 cases pass. No new cases or other owner runs.
- Native, VC4 and MinGW builds pass. VC4 reuses 26 objects and compiles nine,
  linking 35 source objects including the new SDK transport.
- One focused REA read establishes the six-byte DirectDrawCreate thunk at
  `0x416600` and actual DDRAW IAT cell `0x44122C`. Snapshot: 486 records.

The [instance-lock batch](../research/exact/EXACT_WINDOW_INSTANCE.md) retains
both complete 109/51-byte exact bodies. Bitmap remains 928/976, MDS opening
480/522 and File loading 307/304. `draw-effect-sprite` remains 365/361.

## Next work

Restore the whole WinMain entry/message flow at `0x40D930` (320 contiguous
bytes). Its saved dossier establishes the direct original process-exit call;
current source still uses an authored PlatformOps exit member. Recover a
natural typed direct boundary while retaining the actual no-return behavior,
standalone host defaults and existing native process-isolation contract.
Check original branching and state-write order against complete instructions.

Then complete WindowProc at `0x40DA70`: its saved body owns 1,136 bytes across
five ranges in a 1,171-byte span. Resolve the 35 unowned bytes before a complete
exact claim. Continue into uncovered game entries and complete frame flows.
Whole-source origin classification and the denominator for 95% completion
remain open; exact function counts alone do not establish source completion.

## Evidence and tools

Current epoch: `.analysis/checkpoints/exact-window-initialization-283-135/`,
parent `exact-window-instance-283-136`. Working drivers/receipts are under
`.analysis/exact-window-initialization/`. Reviews:
`.analysis/window-init-import-review/` and
`.analysis/window-surface-ownership-review/`.

Complete initialization dossiers:
`ev_2cc92baf4edd1bfc64e4ea142dd7d186ca9124af4dda1bda4b72cb0945cc88d8`,
`ev_11e3dc434ea2130b97aafcbdeb5927e235c6ea83b327a1346881a3898124fa3b`.
Complete thunk read:
`ev_3597b5834cfe1492671d77296cc122baf817aaa5d4b565180b3d4735a12ee517`.
WinMain/WindowProc primary dossiers:
`ev_44569046e29fafd9e3d92f911c45121c537e6f2fd3112ffd497195c11e26321e`,
`ev_ec5246e677575ed67dc6c47dec0ffc7106e9ff2c86eaf9c4c562e39071b603cf`.

REA checkout: `/home/pentester/Project/rea/`. Use `scripts/rea`, pinned to
REA 4.1.0 / Ghidra 12.1.4; Python uses `scripts/repo-python`. One compiler or
provider session, one CPU, CMake `--parallel 1`, silent automated audio.
Keep README concise, with its title PNG and current progress SVG.
