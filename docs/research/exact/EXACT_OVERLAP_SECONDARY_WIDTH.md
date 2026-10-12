# Exact rectangle overlap

The rectangle collision helper at `0x402100` now matches all **329 bytes and
four actual abs-call relocations**. The complete comparison includes both
five-byte jumps outside the provider's owned ranges. The total reaches
**231 functions / 58,775 code bytes / 136 metadata bytes**, leaving 42 authored
functions nonexact.

Secondary width is an independent scalar in the outer scope. The five other
consumed values stay in the inner overlap cache. This keeps all six observed
homes and restores the original width-A-before-width-B read in the combined
width comparison. Arithmetic, four abs calls, fallback calculations and returns
are unchanged. The selected cache occupies 20 bytes beside the four-byte scalar.

| Value | Original and reconstructed EBP offset |
| --- | --- |
| Secondary width | `-4` |
| Primary horizontal distance | `-8` |
| Primary height | `-12` |
| Primary vertical distance | `-16` |
| Primary width | `-20` |
| Secondary height | `-24` |

Separating secondary height from the inner cache first gives 18 differences;
that model is rejected. Keeping its observed prefix in the cache yields zero
whole-body differences. The scope and storage model are inferred from the
original homes and verified emission.

One final compilation preserves the 109-byte angle and 130-byte distance
companions. Their generated literal names are refreshed using complete object
and target bytes at the existing addresses. The unchanged original/native
rectangle selection passes 8,000 cases, covering integer centers, touching and
odd dimensions, inverted rectangles and negative coordinates without overflow.
Complete returns, state, queues and events compare. Native and MinGW builds pass;
VC4 links one matching object with 36 verified unchanged objects. All 231 complete
code/literal/metadata closures pass. Historical case scopes are unchanged; 235
input inventories refresh. No game runs.

Independent review verifies all six recursive compiler inputs, the 24-byte
frame, every original saved instruction address and both gap jumps. The original
full-byte Evidence `ev_6d9765478c63299676c89c2efc5bea93b134606a61edd8d3f818a72efde2c404`
corroborates `ev_38098a89555f0662ce749fc26b6fe5b78bea2da42431812abbdbf888c320c2cd`.
Private compiler, native selection, full-closure and build receipts are in
`.analysis/overlap-secondary-scopes-20261013/`.
