# Region restoration and entity drawing

This family restores the rendering operations used by a gameplay frame:
immediate background restoration, queued dirty regions, bonuses, and particles.
It also reviews the complete reduced-sprite routine already in the source.

## What REA established

The five saved dossiers cover every instruction through each final `RET`:

| Routine | Original span | REA Evidence |
| --- | ---: | --- |
| Reduced sprite, `0x4085D0` | 361 | `ev_bde5005e002236529be930995e10017c75e10aad8e724216cbac463f299af083` |
| Effect region, `0x408A50` | 281 | `ev_28f895bfecc1cab9128bfbf634996e85c59e059ed77b0a81b83d293466ad9603` |
| Dirty regions, `0x408CC0` | 827 | `ev_2d9050e4b74d2fcb39692d85337c3a372235cd44f4cf5d22ee74c047bb4c3f76` |
| Bonus drawing, `0x414740` | 87 | `ev_18c8a1b160ceda205898808260e4886bf6c68f56001a7444f7b169469928c029` |
| Particle drawing, `0x414CB0` | 320 | `ev_78508bf5cd7a13bba8f876482f913dfeffc0fee30ef126fc6a216c32b14bca6e` |

Effect restoration passes the address of its incoming 16-byte rectangle to
DirectDraw. Both stepping callers copy the existing four rectangle fields onto
the stack. The recovered API therefore takes `DxBallRect` by value. The portable
callback table keeps its scalar bounds interface through a small adapter.

Dirty-region restoration selects clipping once, then runs one of two loops.
The clipped loop rejects invisible records and updates stored bounds in place;
the fast loop passes each stored rectangle directly to BltFast. Both read the
current page and surfaces at each operation, append eligible presentation
records after drawing, and finally clear the current page's count.

Bonus drawing calls the real reduced-sprite entry. Particle drawing reads the
effect surface again for descriptor, lock retries and unlock. Its consumed pixel
pointer advances between the two row writes; four fresh coordinates form the
rectangle passed to the real queue entry. These replace cached state and
factored callback calls in the previous source.

## Complete compiler comparison

| Newly accepted routine | Exact code bytes |
| --- | ---: |
| Effect-region restoration | 281 |
| Bonus drawing | 87 |
| Reduced-sprite drawing | 361 |
| Effect-sprite Blt | 362 |
| Elapsed time | 81 |

The last three retain their existing source bodies. The same compilation
recovers their full matches. The previous effect-sprite BltFast emission changes
to 365 bytes against its 361-byte original and returns to the candidate ledger.
The net gain is **811 code bytes**: **122 exact functions / 19,040 code bytes**,
with the existing 136 metadata bytes preserved.

Dirty restoration remains a complete 846/827-byte candidate with 746 differences;
particle drawing remains a complete 311/320-byte candidate with 212 differences.
All real relocations are applied. Generated literal names are refreshed against
their complete contents, and switch labels against their actual code sections.

## Build and behavior

The shared rectangle declaration affects 23 compiler recipes, compiled together
once. The native build and the existing display/entity Oracles pass; the other
owner suites are reused. Source presence and existing case counts stay fixed.
The native fixture forwards the genuine aggregate API and queue call through
their actual owned defaults or current callbacks.

Full dossiers, before/after inputs, objects, comparisons and bounded review
receipts are retained privately under `.analysis/exact-render-restoration/`.
