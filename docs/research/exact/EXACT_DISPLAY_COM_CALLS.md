# Complete display surface calls

The later [effect-sprite path review](EFFECT_SPRITE_PATH_CORRESPONDENCE.md)
checks all six paths in each of the three remaining effect-sprite candidates,
including mutable RECT callbacks and ordered queue writes. Their strict byte
comparisons and maintained source stay unchanged.

The shared [display implementation](../../../src/display.cpp) now uses the
same stdcall surface interface as the resource owner. Thirteen calls change
from explicit C vtable dispatch to virtual member dispatch. Expressions,
branches, local scopes and state writes stay the same; public functions and
globals retain C linkage.

Four functions now match their complete original bodies:

| Function | Original address | Complete bytes |
| --- | --- | ---: |
| `blt-reduced-sprite` | `0x408460` | 362 |
| `queue-sprite-region` | `0x408880` | 272 |
| `draw-reduced-sprite` | `0x4085D0` | 361 |
| `restore-regions` | `0x408CC0` | 827 |

The restoration controller matches all 198 instructions and 61 relocations.
Its nineteen address producers now use the original register order, removing
the nineteen extra bytes from the previous C emission. Reads of the current
page, counts, surfaces and rectangles still occur after each drawing callback.

Three previous exact functions become candidates:

| Function | Current / original bytes | Differing positions |
| --- | ---: | ---: |
| `blt-effect-sprite` | 366 / 362 | 332 |
| `sort-present-regions` | 296 / 296 | 3 |
| `wait-frames` | 170 / 170 | 6 |

Their old complete matches are retained privately and removed from the current
exact ledger. The net gain is **one function and 994 bytes**, bringing the total
to **235 exact functions / 61,716 code bytes / 136 metadata bytes**. The other
35 retained candidate code identities are unchanged; 38 authored candidates
remain.

## Verification

One canonical matching compilation checks all twenty display functions. All
235 current complete code, literal and metadata closures pass afterward.
Native and MinGW build; VC4 links the matching display object with 36 verified
unchanged objects. There is one implementation across all builds.

The maintained display driver supplies 2,040 unchanged focused cases covering
queues, drawing, restoration, sorting, merging, palette changes, waiting and
presentation. All pass. Thirty-six existing callback cases also pass, including
page changes, count growth/shrinkage, presentation capacity and surface changes
during restoration. The 54 ordinary restore cases already passed in the
focused run and are not repeated by the callback driver. No connected gameplay
frames or game run accompany this checkpoint. Historical input inventories
refresh 249 rows.

The UI surface-call trial is rejected: it gains no exact function, loses
draw-text at three differences, and leaves line drawing at 445 bytes with nine
differences. Using the interface's HRESULT type for Lock's result produces the
same comparisons. The canonical UI source stays unchanged.

Original REA evidence for the first three promotions is
`ev_40b8ddcf6aa3efdcf4aca2672b36818f47380c9acd8421be17e47d27f638fd8e`,
`ev_3687124640959271155870347ab4ae5dc46934963ac07b33e841cb1d0db8f413`
and `ev_cc1db01cb0efa2d9fd45a7a3e26b2ebdd4d865c6a37d2bc671fe348434314ef0`.
Restoration evidence is
`ev_2d9050e4b74d2fcb39692d85337c3a372235cd44f4cf5d22ee74c047bb4c3f76`.

Complete current inputs, comparisons, before products, callback receipts and
independent review are retained in `.analysis/display-com-integration-20261013/`.
The initial one-compile projection is in `.analysis/display-surface-com-20261013/`;
the two rejected UI compiles are in `.analysis/ui-surface-com-20261013/`.
