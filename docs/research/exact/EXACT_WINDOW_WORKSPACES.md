# Exact window and DirectDraw setup

Both initialization paths in `src/platform.c` now match their complete original
bodies. The checkpoint adds **2,490 exact application bytes**, bringing the total
to **211 functions / 47,374 code bytes / 136 metadata bytes**. The remaining
authored nonexact queue drops from 64 to 62 functions.

| Entry | Whole code | Instructions | Relocations | Frame |
| --- | ---: | ---: | ---: | ---: |
| Fullscreen `0x40CF70` | 1,343 bytes | 325 | 114 | 472 bytes |
| Compatible `0x40D4B0` | 1,147 bytes | 288 | 110 | 468 bytes |

The window-class workspace ends after registration. The capability record ends
after GetCaps and its software/video-memory policy checks. The surface descriptor
spans primary and board creation; the shared HRESULT belongs to the graphics
setup workspace. The fullscreen attachment request keeps its existing DWORD
representation. These scopes preserve the existing types, capacities, operations,
selected-field writes and every success/failure path.

| Frame value | Fullscreen EBP | Compatible EBP |
| --- | ---: | ---: |
| Attachment request | -4 | — |
| HRESULT | -8 | -4 |
| Surface descriptor | -116 | -112 |
| Capabilities | -432 | -428 |
| Window class | -472 | -468 |

The final object matches every byte after all actual import, global, callback
and complete string bindings are applied. Nine prior platform exacts retain
their complete 2,938 bytes. The compatible path matched after the first scope
recovery. Fullscreen then matched when HRESULT storage was placed outside the
descriptor workspace. Four platform compilations are retained; the intermediate
attachment-record and sibling-result models were rejected. No declaration
names, array capacities, padding or source operations changed in the final body.

Original REA dossiers are
`ev_2cc92baf4edd1bfc64e4ea142dd7d186ca9124af4dda1bda4b72cb0945cc88d8`
and `ev_11e3dc434ea2130b97aafcbdeb5927e235c6ea83b327a1346881a3898124fa3b`,
from the closed October 7 11:04 run. Both bodies are contiguous through RET.
Their complete instruction boundaries agree with the final object.

The unchanged initialization loops pass **126 fullscreen and 122 compatible
cases**: failed/null outputs, buffer counts, clipping, capability bits, GetCaps
errors and video-memory boundaries. They compare full relevant state, selected
record fields and ordered Win32/COM calls. Linux and MinGW builds pass; VC4 links
the same object with 36 verified unchanged objects. All 211 accepted extents and
compiler-input/object identities verify. No key/message suite or game campaign
runs. Historical semantic scopes retain their case counts while input hashes
refresh for the source change.

Before inputs, all four compiler stages, complete comparisons, the selected
Oracle and products are retained in `.analysis/window-workspaces-20261012/`.
Completed diagnostics and before-product copies use verified gzip carriers.
