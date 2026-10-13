# Complete intro surface calls

The shared [intro implementation](../../../src/intro.cpp) now uses the recovered
DirectDraw surface interface for twenty stdcall virtual calls. Public functions
and globals keep C linkage. Expressions, local scopes, storage and state writes
are unchanged.

`update-scroller` at **0x407C90** now matches all **233 bytes and 20 relocations**.
Its advance guard reads shift before comparing advance, matching the original
MOV/CMP/JGE sequence. The previous C emission read advance first and used the
equivalent CMP/JLE sequence. Three byte positions differed. The existing source
guard is retained; the owner language and call interface change its emission.

All eighteen previous intro exacts remain, giving nineteen exact functions and
7,039 bytes in this owner. Redraw stays 578/587 bytes with 560 differences.
All 37 remaining candidate code identities are unchanged. The repository total
is **236 exact functions / 61,949 code bytes / 136 metadata bytes**, with no
exact demotions in this checkpoint.

## Verification

One canonical matching compilation compares all twenty intro functions with
actual relocation bindings, complete literal contents and attached metadata.
All 236 repository closures pass afterward. Native and MinGW build; VC4 links
the fresh matching intro object with 36 verified unchanged objects.

The maintained native driver supplies 110 unchanged focused cases: 48 scroller,
36 point-update, one point initialization, nine intro redraw and sixteen splash
redraw cases. All pass against the original oracle. The first reporting assertion
expected twice the actual point-case count; the corrected count is 36, and the
final receipt verifies the current library. No connected gameplay frames or
game run accompany this checkpoint. Historical input inventories refresh 249
rows while preserving their scopes and case counts.

Original scroller evidence is
`ev_60ffa0dd2052ca4d66e244d13dff9c0927c40df0a2c284e69e239173f8e96e25`.
The complete source projection and independent guard review are retained in
`.analysis/intro-surface-com-20261013/`. Current compiler inputs, all comparisons,
before products, focused receipt and independent acceptance review are in
`.analysis/intro-com-integration-20261013/`.

A separate core surface-call projection preserves all eleven complete code
hashes, including nine exacts totaling 4,659 bytes. Drop-bricks and game-frame
remain candidates, so that projection is rejected. Its single compilation and
frozen inputs are retained in `.analysis/core-surface-com-20261013/`.
