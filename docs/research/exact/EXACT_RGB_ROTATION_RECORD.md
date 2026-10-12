# Exact RGB rotation record

`dxball_rotate_rgb_colors` at `0x0040AA60` now matches its complete 188-byte
original body and both actual relocations. A twelve-byte color record groups
the three signed DWORD components already consumed by the rotation. Green,
red and blue occupy EBP-12/-8/-4; the inner shift index occupies EBP-16.
All four preceding red/green displacement differences are gone.

The source still saves the first RGB triplet, shifts the requested component
range, appends the saved triplet and submits the new first color. Values retain
their signed 32-bit storage until the existing byte conversions at submission.
The disabled guard and every array read/write remain in their original order.
The record has no unused field; matching emission does not establish the
original declaration spelling.

One canonical UI compilation preserves five accepted companions across
559 bytes. Text measurement, palette shift and line drawing keep their
preceding complete comparisons. Linux and MinGW build; VC4 relinks with
36 verified unchanged objects. Twenty unchanged RGB cases cover four disable
values, five counts including partial triplets, signed and over-byte components,
and three canary words. Complete pools, palette/flag bytes and ordered effects
agree between original and native execution.

All 222 accepted exact units and input closures verify. Current totals are
55,351 code bytes and 136 metadata bytes, with 51 authored functions remaining
nonexact. No game campaign runs. Original evidence is
`ev_d69a03478a3300403b907eadb1d092d72ea91325ee9a2d51042a1105207b5bb3`,
operation 30 of run `2026-10-07T11-58-17.972Z-interactive-3053414`.
No new REA query is needed. Complete private receipts remain in
`.analysis/rgb-rotation-record-20261012/`.

The same turn checks a consumed capture workspace in the resources owner.
Its candidate improves to 864/852 bytes with 726 differences, but glyph search
loses its accepted match: 146 bytes and 86 differences. That stage is rejected;
source and canonical object identities are restored without recompilation.
No resource case replay runs. Retained stage and rejection receipt are in
`.analysis/sprite-capture-workspace-20261012/`; do not repeat this workspace model.
The PCX frame's unobserved four-byte region remains unresolved in its existing
[complete packet proof](EXACT_PCX_PACKET_LOOP.md).
