# Exact scroller-wave cursor

`dxball_draw_scroller_wave` at `0x407BA0` matches its complete 235-byte original
body. An eight-byte iteration cursor holds the horizontal position and five-pixel
step; the rectangle stays separate because each DirectDraw call takes its address.
All six original homes in the 24-byte frame agree: step EBP-4, x EBP-8, and
rectangle left/top/right/bottom at EBP-24/-20/-16/-12.

Each strip spans x through x+5 and y=440 through475. Positions run from40
through595. The two destination branches preserve their live surface reads,
sine input, multiplication by20, integer conversion and y offset420.
The whole comparison includes all13 bindings and the complete eight-byte
floating-point multiplier at `0x420078`.

The saved REA carrier is
`.analysis/rea/runs/2026-10-07T11-58-17.972Z-interactive-3053414/26-analyze_function.json`,
Evidence `ev_ecc8bc98f207e2dcf6101e2f1fbf61126d0081fced68e29388f49128c78d7f89`.
Its contiguous body supplies the original frame, both rendering branches,
loop and terminal return. The source cursor spelling remains inferred.

An initial combined rectangle/cursor workspace also matches the waveform,
but changes the unchanged palette pulse to368/370 bytes with114 differences.
That stage is rejected. The selected separate iteration cursor preserves all
sixteen accepted intro companions across5,860 bytes, including the complete
370-byte pulse. No compiler flags or public interfaces change.

Two intro compilations are retained. The first comparison stops at a stale
generated double-symbol name; the completed object is then consumed with
full literal attestation, without recompilation. The selected object preserves
all prior bindings and adds the whole waveform unit to exact acceptance.

Four unchanged original/native waveform cases pass. Each compares full state
and all112 ordered strip blits across reduced-particle modes0,1,2,-1. Linux
and MinGW products build, and the VC4 executable links the changed intro object
with36 verified unchanged objects. No game campaign runs.

All224 accepted exact closures verify across55,716 code bytes and136 metadata
bytes. There are49 authored nonexact functions left. Full private receipts
are in `.analysis/scroller-wave-cursor-20261012/`.
