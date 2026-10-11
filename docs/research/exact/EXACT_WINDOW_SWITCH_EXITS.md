# Exact window switch exits

WindowProc at `0x40DA70` now matches the complete 1,171-byte span and all
74 actual relocations. Source retains the per-case switch exit following the
cursor's direct return and places the empty create/erase-background message
exit after right-button release. The runtime statements, callback boundaries,
locals and parameter declarations remain those already recovered.

The original cursor returns one at `0x40DAB2`, then retains an unreachable
switch-end jump at `0x40DAB7`. The empty message exit lies at `0x40DD65`, after
the right-button release exit; default return has its own switch tail at
`0x40DDEE`. Current source previously omitted the cursor tail and placed the
empty-message exit after default, producing two adjacent dead jumps and a
1,166-byte body. Restoring the observed structured exits gives exactness in
one matching compilation. This does not establish unique original C spelling.

[The earlier topology proof](EXACT_WINDOW_PROC.md) already pairs all 227
reachable instructions and their defined operands/edges. The new complete
comparison also includes all three dead five-byte exits. The whole partition
is 230 instructions / 1,151 bytes plus the complete 20-byte five-entry message
table; no gaps or dead bytes are masked. The table routes messages
`0x201..0x205` to their original code destinations. Original and emitted internal
COFF definitions resolve to the same positions; actual offsets/types/addends,
section/value/storage and external bindings are checked before comparison.

Eight existing platform exact units retain all 1,767 bytes, including the
newly recovered 831-byte game-key body. Other platform candidates stay unchanged:
fullscreen 1406/1343 with 1278 differences, compatible 1180/1147 with 1092.
A sequential text replacement initially collides when one new relocation offset
matches a later old descriptor. The comparison client stops before writing the
manifest; replace descriptors in a single pass keyed by their original identity.
No extra compilation or source trial is performed to recover that receipt.

Native/MinGW each compile only platform and link selected core/game products.
VC4 links this same matching object plus 35 verified unchanged objects, with no
additional source compilation. Only four unchanged existing WindowProc loops
run: 2,138 cases covering activation, cursor, key modifiers, shutdown/focus,
audio flags, mouse capture/buttons, palettes and default messages. Existing
ordered Windows/COM effects, initialized state and returns match original
execution. The private extraction initially omits the literal `messages` tuple
and fails before any case; its log is retained. Include that unchanged
prerequisite and run all 2,138 once. No game-key, clock, dispatch, full-platform
or gameplay/audio replay runs. The 235 refreshed historical semantic closures
retain their 247 existing scopes.

Totals are 283 source-present, 188 exact functions / 35,003 complete span bytes /
136 accepted metadata bytes. Origins remain 270 authored, 83 runtime,
42 compiler-generated and 133 unknown. The inline table is inside the full
unit span; it is not extra accepted metadata. Original declaration spelling,
physical Windows/COM/audio behavior and complete-game fidelity remain unproved.

Reuse the closed complete read
`ev_454b9b00147a98b6a0f82cf928c9a3af94a4d1f90f0311809c080c7e4d2664bc`
from `2026-10-10T10-38-17.818Z-requests-241415`, independently verified against
the target. No fresh provider/setup. Private before state, matching recipe,
complete comparisons, topology, selected cases and products:
`.analysis/window-switch-exits/`. Immutable seal:
`.analysis/checkpoints/window-switch-exits-283-188/sha256.json`.

The WindowProc source/CFG hypothesis is closed. Further reconstruction needs
actual missing whole-owner producers or an independently distinguished origin
binding; do not retry these exits, local layout or equivalent expressions.

Cleanup verifies 98 owned files / 188 explicit immutable dependencies and four
current products after 52 scoped hardlinks replace 4,317,184 single-link
allocated bytes. Unique before/current evidence and products remain. No
measured device-free-space delta. Supplemental post-cleanup identities bind
cleanup and current documentation without changing the immutable seal.
