# Current reconstruction handoff

Continue toward nearly complete original game source and a rebuildable,
playable game. Recover whole flows, compile stable families once and run only
useful affected comparisons and existing Oracles. Keep the README concise,
with its title PNG and progress SVG.

## Current checkpoint

[WinMain](../research/exact/EXACT_WIN_MAIN.md) is exact across its complete
320-byte body. Source restores the original compatible-first branch,
Control-before-Shift writes, one PeekMessage branch per loop, live message
return and direct cdecl exit boundary. Shared `platform_host.c` calls an
optional typed backend, then the host CRT exit if it returns or is absent.
The existing fixture binds its unchanged fork-isolated exit callback.

- 283 source-present functions; 136 exact functions / 21,293 code bytes.
- First stable compile per 25 affected recipes. 122 full comparisons / 1,261
  actual relocations; all 121 affected accepted functions remain exact.
- WinMain has 26 actual relocations and two distinct complete string objects.
  No local-layout, identifier or compiler-profile trials were used.
- Only the existing 56 WinMain cases were replayed. No new cases, other
  Platform-case replay or other owner Oracle runs.
- Native, VC4 and MinGW builds pass. VC4 reuses 26 objects and compiles nine,
  linking 35 source objects. The REA snapshot stays at 486 records; no new query.

The [initialization batch](../research/exact/EXACT_WINDOW_INITIALIZATION.md)
restores both complete initializer flows, three actual COM output pointers and
all 23 Window import cells. Fullscreen remains candidate at 1,406/1,343 bytes
and compatible at 1,180/1,147. `refresh-score` retains its prior exact object
and inputs but remains candidate after six operand bytes changed. Instance
claim/close remain exact at 109/51 bytes. Bitmap remains 928/976, MDS opening
480/522 and File loading 307/304; `draw-effect-sprite` remains 365/361.

## Next work

Recover complete WindowProc at `0x40DA70`. The saved dossier owns 1,136 bytes
across five ranges within a 1,171-byte span. Three five-byte gaps start at
`0x40DAB7`, `0x40DD65` and `0x40DDEE`. The remaining 20-byte switch table starts
at `0x40DECF`: five entries for messages 0x201..0x205. Query the missing bytes
through the pinned REA provider before asserting their ownership or a complete
exact unit. Read-only next-family findings live under
`.analysis/window-proc-next-review/`; collect their latest status before editing.

Continue into uncovered game entries and complete frame flows. Whole-source
origin classification and the denominator for >=95% completion remain open.

## Evidence and tools

Current epoch: `.analysis/checkpoints/exact-win-main-283-136/`; parent
`exact-window-initialization-283-135`. Drivers and full receipts:
`.analysis/exact-window-main/`. Independent source review:
`.analysis/window-main-flow-review/`; original next-family proposal:
`.analysis/window-main-next-review/`.

Complete WinMain and WindowProc dossiers:
`ev_44569046e29fafd9e3d92f911c45121c537e6f2fd3112ffd497195c11e26321e`,
`ev_ec5246e677575ed67dc6c47dec0ffc7106e9ff2c86eaf9c4c562e39071b603cf`.
Initialization dossiers:
`ev_2cc92baf4edd1bfc64e4ea142dd7d186ca9124af4dda1bda4b72cb0945cc88d8`,
`ev_11e3dc434ea2130b97aafcbdeb5927e235c6ea83b327a1346881a3898124fa3b`.

REA checkout: `/home/pentester/Project/rea/`. Use `scripts/rea`, pinned to
REA 4.1.0 / Ghidra 12.1.4; Python uses `scripts/repo-python`. One compiler or
provider session, one CPU, CMake `--parallel 1`, silent automated audio.
