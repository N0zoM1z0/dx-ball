# Software rotation pixel traversal

`dxball_render_rotated_sprite` at `0x4026A0` now restores the original per-pixel
source cursor, pitch rollover, origin-dimension copies, destination-address
stores, live surface operands and ignored Unlock-result writes. The existing
original/native checks pass 351 renderer and 344 wrapper cases once. Source,
native/MinGW products and the VC4 game use the same maintained implementation.

The complete renderer candidate is 1,447 / 1,572 bytes with 1,491 strict
unmasked differences; before it was 1,335 / 1,572 with 1,490. This source recovery
does not improve the strict byte-difference count or establish whole-frame
instruction equality. All 58 actual COFF fields and complete referenced literal
bytes are explicit in the newly configured candidate.

## Observed source operations

The unsigned source-column counter starts at zero before the dimension reads.
After each executed pixel the original increments it. When it reaches width,
the counter resets and the source pointer advances by `pitch - width + 1`;
otherwise that pointer advances by one. The former source combined these
operations into unconditional per-pixel increment and a separate row-end skip.
The restored loop also preserves the original zero-width path's lack of source
pointer advancement.

Width and height are captured independently before API calls. After source
locking, separate copies feed the origin calculations. Destination and source
operands are read at their actual descriptor, retry and unlock boundaries rather
than through cached local surface pointers. The original explicitly stores each
computed destination address before writing the pixel; the current source does
so for both rounded-Y and optional truncated-Y writes. Rounded X remains the
column for both writes. Both final Unlock return values are stored in the real
HRESULT local even though no later call consumes them.

The first X term follows division, negation and addition of the unsigned center.
Pixel and row coordinate updates retain the observed step-plus-coordinate
addition. The 0.5 rounding operand is read directly rather than initialized as a
named local. The intermediate double stores and the differing 2.046 Y divisor
remain intact.

## Remaining emission and storage gaps

The original has 365 instructions; the accepted current object has 366. There
are 363 paired normalized opcodes after excluding two original zero writes of
unestablished purpose and three additional current FDIV fallback argument
pushes. Three conditional encodings also differ. This is a bounded opcode
inventory: operand/register/frame identity, every instruction width and complete
floating-point behavior are not established by that pairing.

The original's first three divisors are four-byte `2.0` operands and use the
m32 FDIV fallback. A `2.0f` literal in the existing extended-expression context
still emits an eight-byte operand and m64 calls. Complete current double-2.0
literal bindings reuse the independently verified original constant at `0x420098`
from the exact ball updater. That is a diagnostic current-literal binding,
not authority for the renderer's original four-byte operand at `0x420038`.
The normal division path is tested; physical FDIV-workaround behavior remains
outside the current pixel acceptance scope.

Two actual MT compiler stages are preserved. The accepted traversal stage is
1,447 bytes. A subsequent typed four-byte stored divisor recovers m32 calls
and emits 1,437 bytes, but loses the three preceding exact projection emissions.
That stage is rejected; its source/object/receipts remain private. The accepted
source and completed object are restored by hashes without compilation.
No further name, declaration, storage, capacity or padding variant is tried.
The two unclassified zero stores remain unimplemented; no fake local is added.

## Exact projection membership

The accepted natural renderer change also alters ordinary lowering of two
unchanged helpers. Y offset at `0x402DE0` now matches all 191 bytes and ten
actual relocations. The retained five-byte unowned epilogue jump at `0x402E8B`
is included, not masked. Its complete exact claim is restored.

Height at `0x402FB0` now emits 193 / 191 bytes with 158 differences, so its
current exact claim is withdrawn and a complete candidate retained. The prior
191-byte exact checkpoint remains historical. Wrapper, horizontal offset and
width retain their complete exact results across 558 bytes. Both helpers'
source tokens remain unchanged; no unrelated helper is edited to force code
selection. The exact set stays at 206 functions / 44,406 code / 136 metadata.

## Validation and evidence

The unchanged fixture functions run 688 renderer/wrapper baseline comparisons
and seven live-surface/bank/retry callback scenarios: 351 renderer plus 344
wrapper cases. Complete guarded destination buffers, source/record/bank/trig
storage, finite lock sequences and ordered API calls agree. No new case,
full historical replay or fresh Wine play run occurs. Native and MinGW rebuild
once. VC4 links the accepted matching rotation object with 35 unchanged verified
objects, with zero additional legacy source compilation. All 206 exact input
closures and 36 game objects verify. Historical semantic scopes remain 247;
235 input inventories refresh without rerunning those historical cases.

Reuse closed REA records:

- Renderer: `ev_1dfa14e3428cac399a6bc2876da74d5bbc4a5edc8a8e03a6af79783e189daf26`,
  run `2026-10-07T10-33-32.118Z-interactive-2912559`, operation 03.
- Complete 40-byte constant carrier:
  `ev_3981d4fe3871c6d5f4976aaec23007d066c24f80aedca23dd51270d63c19de71`,
  run `2026-10-08T02-50-35.710Z-graphics-requests-820757`, operation 00.
- Y offset: `ev_0bb8d29f0bbb9230ce62dfeaaa226c4099138a7443f31974dbb2b206ef459987`;
  its five-byte gap: `ev_ef7ec380e69c68892ba8533b87c32732187310fd913801791fd55af7d41f3d99`.
  Both are in closed `2026-10-09T16-15-21.487Z-interactive-1181426`.

Consumer repairs handle twelve complete generated-literal aliases, the observed
helper membership change and an interleaved build declaration accidentally
included by an initial table-replacement range. The corrected manifest is
compared structurally with its retained predecessor: every build declaration
and unrelated unit/candidate stays identical. Only bounded consumers repeat;
no completed compiler, fixture or provider invocation is restarted.

Private `.analysis/rotation-pixel-traversal/`; seal
`.analysis/checkpoints/rotation-pixel-traversal-283-206/sha256.json`.
Source-present 283, authored 270 and origins 115 runtime / 42 generated / 101
unknown stay unchanged. Original spelling, the complete authored denominator,
physical graphics/audio and complete campaign fidelity remain open. Optional
REA feedback stays in the one existing `/tmp/dxball_rea_feedback_20261010.md`.
Preserve both stages and unique evidence; deduplicate only hash-equal immutable
copies against the immediately preceding screen-point seal.
