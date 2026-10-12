# Exact explosion cleanup scope

The complete explosion animation controller at `0x412730` now matches all
**797 bytes and 49 relocation bindings**. The accepted total reaches
**230 functions / 58,446 code bytes / 136 metadata bytes**, leaving 43 authored
functions nonexact.

The remaining 13 differences were stack displacements. Cleanup Y belongs to a
block around the expiration/drawing split. The rectangle and cleanup X stay
inside the expiration branch, and the rectangle remains a standalone object.
This preserves direct frame loads when it is passed by value to the existing
restore helper. No runtime operation or variable is added.

| Consumed value | Original and reconstructed EBP offset |
| --- | --- |
| Neighbor X / Y | `-4 / -8` |
| Cleanup Y | `-12` |
| RECT left / top / right / bottom | `-28 / -24 / -20 / -16` |
| Cleanup X | `-32` |

Reordering the same inner-block declarations leaves all 13 differences and is
rejected. Earlier nested records restored the homes but added an address-based
argument read. The selected scope model restores the homes while keeping the
four direct RECT loads. All 251 original instructions, 14 calls and 18 branches
match through the complete return. The scope is inferred from the observed
homes and verified emission.

One final VC4 compilation preserves four effects companions across 841 bytes.
The unchanged original/native selection passes 810 explosion cases: three
frame states, three timer boundaries, six tile bytes, three reduced modes and
five board positions. It compares full grids, effect/request lists, globals,
RNG cursor and ordered drawing, restoration and deallocation calls. Native
and MinGW builds pass; VC4 links the one matching object and 36 verified
unchanged objects. All 230 complete code/literal/metadata closures pass.
235 historical input inventories refresh; their case scopes are unchanged.
No game runs.

An independent review verifies every original instruction address, the eight
homes, all 18 recursive compiler inputs, object identity, five complete owner
comparisons and source scope-only change. Existing REA dossier:
`ev_b10ee96258ecd655c8f9258fc4ae6cb2c52939077283dc0409f9f912688f79b3`,
`.analysis/rea/runs/2026-10-07T06-16-05.200Z-rea-effects-family-2065454/09-analyze_function.json`.
Private compiler, focused-case, full closure and build receipts are in
`.analysis/explosion-cleanup-homes-20261012/`.
