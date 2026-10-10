# Complete round lifecycle source restoration

This batch restores four complete observed controllers from retained full REA
dossiers: finish-game (46) bytes, reset-round (426), restart-round (327) and dispose-game (112).
The combined original extent is 911 bytes. All four saved bodies are contiguous
through their plain returns. No new original query was needed. Original source
spelling and declaration order remain unproven.

| Entry | Unit | Original bytes | Primary REA Evidence |
| --- | --- | ---: | --- |
| 0x415C10 | finish-game | 46 | ev_38805c95418919116424ecc4729962d9da487a44a77a72a1b06608165afffaab |
| 0x415C40 | reset-round | 426 | ev_b1e60404eed3263e429779d493ed38ef1ee1290f2a0e3d31ac348647d03e946f |
| 0x415DF0 | restart-round | 327 | ev_7c445e5d515f3a15804b10c82ed404e443f39953efa2f8d7add2449b832c3731 |
| 0x416430 | dispose-game | 112 | ev_6cd0575b1e5a42d65bb1061f6443204f9f12afdbd651badd502fd0edc5d502b3 |

Reset retains count/redraw/palette/sound/ball call order, clears real state and
computes paddle X using the old signed width. After assigning sprite 68, it reads
the actual live selector to obtain the new width. It attaches the actual current
new ball and clears level/restart flags last. Shared sprite-bank ownership and
one layout remain common to native, MinGW and VC4.

Restart executes only when requested==1. The unchanged-level path keeps all 256
palette entries, zero-extends the unsigned component bytes and computes a signed
integer average. Its two consumed DWORD values occupy EBP-4/index and EBP-8/gray
in the actual diagnostic compiler output, matching the saved original. The low
byte is then stored separately into red, green and blue; palette flags survive.
The prior byte-local/unsigned expression gives the same defined numerical result
for components 0..255, so this restores representation and emission rather than
asserting a new visible color bug. All three distinct palette-transition sites,
board/primary clears, memset, real entity/region cleanup and signed lives branch
remain explicit.

Dispose preserves fade!=0 and restart==0 gates, performs ordered real palette,
surface, sound, bank and MIDI teardown, then always clears entities. The former
generic finalizer corresponds to the actual close_music target 0x401DA0; dependency
behavior remains independently scoped. Finish directly waits 30 frames and sets
end/menu state. Each controller has its observed ordinary return-to-epilogue.

One diagnostic runtime compilation compares all bytes and every relocation.
Finish (46), restart (327) and dispose (112) match all 485 bytes. Reset has equal 426-byte
extents but retains 20 bank-address scheduling differences at offsets 291..316.
Its genuine values, ABI and control flow remain restored; it is a nonexact
candidate. No padding, profile-selected source, fake locals, copied code or
name/declaration-order trials eliminate those differences. Generated path label
rebinding requires the complete null-terminated mbbkgrnd.pcx content attestation.
The single configured grouped cold epoch reproduces all three complete zeros
and reset's 20 differences. The final ledger has 102 exact units /11,959 code bytes
plus 136 separate metadata bytes. All 99 preceding complete code/metadata identities
remain unchanged. Source presence stays 283; scoped rows 247 and cases 112,273 stay
fixed. All 78 relocations are explicit, including complete path literal content.

Native fixtures add eight genuine typed symbol boundaries to the existing five:
load_saved_palette, palette_transition, clear_surface, reset_regions,
release_sounds, release_sprite_banks, close_music and wait_frames. Wrappers read
the currently bound real RuntimeOps/FrameOps tables from the copied image at
call time, including descendant replacement slots. Binding follows callback
installation, verifies table/function ownership and rejects null/self/reentry.
Default audits retain a separate canonical LOCAL image. This host boundary proof
does not establish physical driver fidelity or substitute for dependency bodies.

Existing owner matrices and 346 selected lifecycle cases remain unchanged. Source
presence, scoped semantics, exact code and metadata remain separate. All 22 owner scripts pass against 284 frozen inputs in 428.330 seconds. The sole
cold epoch supplies 22 retained actual objects. Fourteen existing rejection
controls, rerun 7,164 raster and 1,024 rotation COFF vectors, strict MinGW and full
VC4 builds pass. The actual cold raster object serves the same complete semantic
recipe without recompilation, with explicit product-adoption provenance. The
semantic driver is identity-attested and was not executed for this product.
No new cases or campaigns are added. The >=95% complete-source goal stays open.
