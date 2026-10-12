# Intro point-seeding mask lifetime

Historical checkpoint: the remaining scalar homes are now recovered by the
[grid cursor](EXACT_INTRO_GRID_CURSOR.md); all 1,996 bytes are exact.

The 287-byte binary mask in `dxball_initialize_intro_points` at `0x40E570`
is consumed only while seeding the 41 by seven point grid. Its initialized
storage now ends before the separate 360-entry wave-offset loop. The shared
index and existing coordinate/angle declarations remain unchanged; names,
types, capacity, initialization bytes and executable tokens are preserved.

One canonical VC4 MT compilation reduces the complete comparison from
2,041/1,996 bytes with 750 differences to 1,996/1,996 with 13. Original and
current frames both contain 304 bytes. All 287 mask writes now use the original
base at EBP-304; the shared index remains EBP-12. The remaining original/current
scalar homes are X 4/8, Y 8/16 and angle 16/4. Every strict difference belongs to
one of those actual displacement operands. They remain explicit candidate
differences: this does not establish the original declaration spelling.

The complete retained REA dossier is
`ev_001f48ac971f132ed4b29b98cf1549ec4136da2eab0a9448b6ed27d7f5e41fb8`,
from the closed October 7 11:58 run, response 04. All 368 original instruction
boundaries and widths, nine branches, two calls and ten ordered relocation
bindings agree. Substituting only the three observed scalar home mappings
makes every byte of the complete body identical, including the initialized
mask and branches. Original boundaries come from REA; only the reconstructed
COFF is decoded locally. No new provider request or source-name/layout trial
is used. Nine moved relocation offsets are grounded in the corresponding
original instructions and raw operand values; every other row attribute stays
unchanged. The completed compiler product was consumed after its initial
stale-offset rejection without recompiling.

All 15 exact intro companions, totaling 3,864 bytes, and every other candidate
comparison in the owner remain identical. Focused unchanged oracle selections
pass one direct initialization and 36 timed/retry point updates, including
36 separately compared preparation calls, plus 58 separate connected
splash/menu/key transition checks. The checks compare complete point, wave,
palette and pixel buffers, state and ordered calls. Physical rendering/audio
and the full campaign remain outside this evidence.

Native and MinGW products are rebuilt. The final matching MT intro object
links with 35 verified unchanged VC4 objects and no extra legacy source
compilation. Existing totals remain 206 exact functions, 44,406 code bytes and
136 metadata bytes; 247 historical semantic scopes retain their case counts.
Private receipts and complete dependencies are sealed under
`.analysis/checkpoints/intro-mask-lifetime-283-206/`.

An earlier single runtime-owner compilation in this turn tested the real
attached-ball overlay/coordinate phase lifetime. It emitted 679/677 bytes with
494 differences, versus the previous 678/677 with 494, so it was rejected.
The prior runtime source and object were restored by verified hashes without
recompilation; its unique source/object and consumer results remain retained.
Do not repeat that scope or vary declarations merely to force stack homes.
The turn therefore used one accepted intro compile and one rejected runtime
compile, not one total compile. Private oracle selection validation initially
selected an unrelated top-level seed statement; it was corrected before any
oracle body executed. The final focused oracle ran once.
