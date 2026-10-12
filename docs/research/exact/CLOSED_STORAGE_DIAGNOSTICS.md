# Closed drawing and SDK storage diagnostics

These models were tested against the frozen 041b1c1 compiler inputs and rejected.
Canonical source, objects and accepted receipts are restored by hash. Preserve
these results when choosing the next question.

| Model | Complete result | Decision |
| --- | --- | --- |
| Line iteration record: extents, error and index | 445 bytes, nine differences; six UI companions exact | No improvement |
| Four paddle scale/animation/overlay records | 679/677 bytes, 487/496/487/487 differences; ten runtime companions exact | No complete match |
| DirectDraw descriptor/key DWORD and LONG kinds | Line445/3; ordinary Blt195 and glyph328 exact; accepted stretch gains four differences and glyph search becomes146/86 | Reject companion losses |
| Descriptor pitch LONG only | Line445/6; glyph328 exact; accepted draw/keyed draw107/94 and stretch141/92 | Reject companion losses |
| Complete SDK declaration kinds, including RECT, COM signatures and specified fill fields | Same resource regressions as descriptor/key stage; six UI companions exact, line445/3 | Reject companion losses |

The final paddle record restores all observed source homes in the 68-byte frame:
scale, animation, margin, both rectangles and overlay coordinates. Bank/sprite
address scheduling still adds two bytes relative to the original; canonical
678/677 remains preferable. No record introduces unused fields or changes buffer
capacity. The original paddle dossier is Evidence
`ev_0b4d5d681d951be5b6a69ac1d9d09db3cc965811c767e0b2b4f7296609cc020a`.

The SDK diagnoses use actual declarations: pinned VC4 `windef.h` defines DWORD
as unsigned long and RECT members as LONG; `winnt.h` defines LONG as long;
`wtypes.h` defines HRESULT as LONG. The installed DirectDraw header corroborates
descriptor pitch and COM slots. Portable aliases retain32-bit width on LP64.
These corrections are legitimate ABI models, but do not preserve the current
accepted emission closure. No SDK declaration stage is adopted.

Independent narrow-parameter review found that raster colors and glyph forwarding
already emit the original DWORD argument reads. Editor key and line color use
original byte reads. There is no missing operation that justifies widening them.

Private complete source stages, objects and comparisons are in
`.analysis/line-iteration-record-20261012/`,
`.analysis/paddle-drawing-records-20261012/` and
`.analysis/ddraw-word-types-20261012/`. There are one, four and six completed
compilations respectively. No fixture, game or provider run accompanies these
rejected models. Completed copies are retained in verified gzip carriers.
