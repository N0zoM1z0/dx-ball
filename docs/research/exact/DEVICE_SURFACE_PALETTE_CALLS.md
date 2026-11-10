# Device surface and palette calls

The device implementation now uses the shared C++ DirectDraw surface and
palette interfaces for eight virtual calls. Its public functions retain C
linkage, so existing game callers and native fixtures use the same API.
Surface recovery, palette creation, fills and both transition paths preserve
their arguments, guards, writes and call order. The existing 100-byte fill
payload passes at the same address through the SDK argument type.

The complete palette transition at `0x40A340` remains 1,339 bytes, with
334 instructions. Its differences fall from 18 to 12. Both blue-channel
comparison groups now reproduce the original load order and signed branch;
the remaining four groups concern red and green. Six differing positions
disappear, and no new ones appear. This is a partial improvement; the function
remains a candidate.

All five exact device companions preserve their complete 808 bytes:
palette initialization, surface clearing, sprite-bank restoration, surface
recovery and synchronization.

One matching compilation compares all six complete functions with actual
COFF relocations. Canonical source, thirteen recursive inputs and flags agree
byte for byte with that retained producer, allowing its object to be reused.

All 238 exact closures pass; the other 34 candidate code identities are
unchanged. Native and MinGW build, and VC4 links the matching device object
with 36 verified existing objects. The current native library passes 796
unchanged function cases: 774 transitions, four palette creations and eighteen
fills. Historical inventories refresh all 249 semantic rows while retaining
their recorded case counts. The exact total remains 238 functions / 62,514
code bytes / 136 metadata bytes. No game run accompanies this change.

Independent review seals the current inputs, products and ledgers. Current products and unique evidence remain.
