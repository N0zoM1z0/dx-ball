# Window initialization

The fullscreen and compatible initialization routines recover the original
window creation, DirectDraw setup, audio preparation and failure paths in
`src/platform.c`. Their complete saved REA bodies contain 1,343 and 1,147 bytes.

WNDCLASS, capability and surface descriptor records retain their original
selected-field writes. A shared signed HRESULT receives each COM result;
GetCaps is stored without a failure test. Surface creation publishes directly
through the primary, secondary and board globals, which now have genuine
surface-pointer storage. Existing numeric drawing interfaces receive value
conversions at their boundaries.

Window services use independent typed cells matching the original imports.
`platform_host.c` supplies the shared DirectDrawCreate transport; Windows binds
its SDK loader and the native fixture binds the same factory contract.
The original call targets the six-byte jump at `0x416600`, whose operand is
the DDRAW import cell at `0x44122C`.

Evidence: `ev_2cc92baf4edd1bfc64e4ea142dd7d186ca9124af4dda1bda4b72cb0945cc88d8`,
`ev_11e3dc434ea2130b97aafcbdeb5927e235c6ea83b327a1346881a3898124fa3b`, and
`ev_3597b5834cfe1492671d77296cc122baf817aaa5d4b565180b3d4735a12ee517`.
One stable compile per 27 affected recipes compares 130 complete units and
1,519 actual relocations. The two initialization routines remain candidates:
1,406/1,343 bytes with 1,278 differing positions, and 1,180/1,147 with 1,092.
Their local records occupy different homes under VC4; no layout variants were
compiled. Of 128 affected accepted units, 127 retain zero differences.
`refresh-score` changes its comparison operand order and moves to candidate;
its prior exact object remains retained. Totals are 135 exact functions and
20,973 code bytes, with 283 source-present functions.

The existing Platform Oracle passes all 4,742 cases. Its logical API callbacks,
case vectors and state contracts stay the same. The constructor binds the real
cells; a typed native shim forwards the recovered direct sound-preparation
call to its existing controlled boundary. Sound's existing MessageBox fixture
binds the shared cell. No other owner Oracle runs.

Native, VC4 and MinGW builds pass. VC4 reuses 26 source objects and compiles
nine, including the new shared transport, to link 35 objects. Full source
inputs, prior/current products, responses and bounded reviews are retained at
`.analysis/checkpoints/exact-window-initialization-283-135/`.
