# Color-fill and palette-loop scopes

The complete rectangle fill at **0x403230** now matches all **85 original
bytes, with zero COFF relocations**. The shared typed source in `src/ui.c`
retains the outer rectangle and scopes its color-fill descriptor to the Blt
operation. The original 116-byte frame places the rectangle at EBP-16 and
the 100-byte descriptor at EBP-116. Size/color writes, coordinate assignment
order, flags 0x400, null source arguments and ignored HRESULT are unchanged.
No unused descriptor bytes are initialized or claimed as defined outputs.

This brings the ledger to **199 exact functions / 41160 complete code bytes /
136 metadata bytes**, with 283 source-present and 247 historical semantic
acceptances. Original identifiers and declaration spelling remain unknown;
complete matching supports the recovered source model, not a literal original
source-file claim. Reconstruction remains incomplete.

## Rotation-loop recovery and remaining gap

In RGB-pool rotation and right/left palette shifts, the loop counter now belongs
only to its shift loop. Names, types, bounds, color snapshots, flags, callbacks
and write order are unchanged. All three sixteen-byte frames now place the
counter at EBP-16, as independently observed in the original complete listings.
This removes seven differing operand bytes across the three bodies.

| Function | Address | Complete bytes | Before differences | Current differences |
| --- | --- | ---: | ---: | ---: |
| RGB-pool rotation | `0x40AA60` | 188 | 7 | 4 |
| Right palette shift | `0x40A880` | 234 | 8 | 6 |
| Left palette shift | `0x40A970` | 234 | 8 | 6 |

The remaining 16 bytes concern the red/green local homes: original blue/red/
green offsets are 4/8/12; current blue/green/red offsets are 4/8/12. The color
snapshots have the same operation lifetime. Splitting their scopes arbitrarily
or trying alternative names would not recover an evidenced lifetime, so no
such trials were made. These functions remain nonexact. Complete instruction
addresses, loop branches, API calls and actual frame operands are retained in
the private proof rather than inferred from a short difference preview.

## Rejected fade comparison hypothesis

The complete 1339-byte transition at 0x40A340 retains 18 differences: six RGB
tests each reverse operand loads and the corresponding signed branch. One
equivalent saved/live comparison-orientation hypothesis was compiled. VC4
canonicalized it to the same output: zero changed relocation symbols and the
same 18 differences. The consumer expected 12 changed bindings and stopped at
that guard after all three owner compilations had completed. The existing
objects and receipts were recovered; no producer was restarted.

The hypothesis, sources, objects and all affected comparisons are retained in
`.analysis/palette-operation-scopes/orientation-and-loop-stage/`.
`orientation-negative.json` records the rejection. The original device source
and its verified prior object were restored without recompilation; its current
input/object closure matches the preceding accepted checkpoint. No comparison
binding was changed and no fade exact claim is made. Do not repeat equivalent
orientation/spelling trials without new source or compiler evidence.

## Original evidence and bounded validation

Five archived REA dossiers identify contiguous complete bodies through their
returns. Their target hashes and terminal records verify. Record paths and
Evidence IDs are in `.analysis/palette-operation-scopes/rea-reuse.json`:
the retained 11:58 archive supplies RGB/right rotation and rectangle fill,
the 09:29 archive supplies left rotation, and the 10:33 archive supplies fade.
`body-proof.json` records complete original/current frame operands, instruction
coverage, branches, calls and actual relocations. The complete relocated fill
bytes match the pinned original PE, without masked gaps or tails. Before-source
controls retain all five initial comparisons.

Four unchanged maintained test loops pass **178 calls**: 12 fills, 20 RGB pool
rotations, 64 right shifts and 81 left shifts, plus the unchanged display-reset
setup call. They compare complete palettes and flag bytes, RGB pools/canaries,
defined fill fields/rectangle coordinates, ordered COM effects and padded
buffers with execution of the original code. The tests remain unchanged;
selected AST, driver, test and current library hashes are in
`palette-oracle.json`. The unchanged fade is not replayed.

Four legacy source compilations were performed: one each device/display and
two UI. One device hypothesis was rejected and its original object restored.
All 13 affected UI/display accepted functions remain exact across 2317 bytes;
four unchanged device companions across 526 bytes also compare exactly.
Native and MinGW affected products rebuild. VC4 links two final matching
objects with 34 verified unchanged objects and no additional source compile.
All 199 exact input/object closures, 247 unchanged historical semantic scopes
and 36 production object closures verify; historical input hashes refresh without
claiming unrelated Oracle reruns.

Current products are in `.analysis/palette-operation-scopes/product-verification.json`;
the independent seal is
`.analysis/checkpoints/palette-operation-scopes-283-199/sha256.json`.
Controlled COM calls do not establish physical driver rasterization, synchronized
display/audio or the full campaign. The user resumed publishing: verified
checkpoints are committed and pushed to `origin/main`, while originals, tools,
builds and raw evidence remain private.
