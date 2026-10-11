# Original PCX packet loop

The decoder at `0x409BB0` now puts the RLE index increment at the body tail
and jumps directly to its guard, matching the complete original control flow.
The earlier `for` lowering added an initial jump and placed the increment
before the guard. No declarations, local layout or extra header/frame bytes
were introduced. Both original pixel paths retain separate wrap, clipping,
row stores, destination increments and consumed pixel-pointer updates.

One stable `/ML` resources compilation yields 979 bytes and 227 instructions,
against the complete contiguous original's 862 bytes and 227 instructions.
The previous object was 984 bytes / 228 instructions. Strict differences fall
from 869 to 851; this remains a candidate, with no new exact acceptance.
All twelve affected accepted resource units / 2,197 target bytes remain exact;
all five resource candidates were compared with their actual relocations.
Current global totals stay 283 source / 247 semantic scopes / 188 exact
functions / 35,003 complete code bytes / 136 accepted metadata bytes.
Origins remain 270 authored / 113 runtime / 42 compiler-generated / 103 unknown.

## Complete instruction correspondence

The saved original information, pseudocode and assembly are from closed
REA 6.3 / Ghidra 12.1.4 run
`2026-10-10T17-54-16.976Z-requests-866362`, respectively:

- `ev_c50e6d43ad08314dafcb3121bfd836d0e3a93d04d480533b5ab9b77043f8b6a2`
- `ev_13ac465a95860ab7b511475a2174d532caacd558004ca45bb872179fb03aa192`
- `ev_93b5290136b33bfcc5cee2cc186d2f6440c5a8c1595647d46ec6172e7d5c8566`

No new provider work is needed. Independently decoded original addresses agree
with all 227 saved assembly addresses; the body is exactly `0x409BB0..0x409F0D`.
The current object binds all eight actual relocations, including the entire
three-byte `rb\0` literal at `0x422794`. Its original header fill, signed maxima,
description dimensions before Lock, retries, inclusive decoded bound,
zero-length packets, overshoot, both pixel paths, Unlock/close and independent
palette selections remain present.

The complete proof in `.analysis/pcx-packet-loop/body-proof.json` pairs every
instruction. After frame translation, branch destination ordinals and the
observed allocation sizes, 205 instructions normalize equally. The other 22
form six three-instruction signed comparison groups and two two-instruction
low-32-bit products. Exchanging comparison operands and reversing JGE/JLE
preserves the signed successor for every input; exchanging pitch and destination
y preserves the consumed pixel offset. These are explicit compiler scheduling
differences. Source relational/product spelling changes did **not** force the
original machine operand order. All 30 branch successors and ten call operands
agree. The packet initializer, guard, body-tail increment and backedge are
paired directly, without commutation.

Current/original frames allocate 308/312 bytes. The typed map covers 305 bytes:
108-byte surface description, 128-byte disk header, seventeen four-byte
locals and the one-byte value. Three compiler value-slot padding bytes are
mapped separately. Original EBP distances 61..64 have no observed typed use
and remain unexplained; this is not a complete 312-byte bijection. No new
local or padding was added to fill that gap. Frame pointees translate by
object identity at controlled API boundaries. Raw pointer identity/retention,
arbitrary external aliasing, uninitialized description fields, scratch
registers/flags, void-exit residue, source declaration spelling and complete
byte equality are outside the claim.

## Products and execution

The established production `/MT` resources owner is compiled once separately.
Its PCX body is 847 bytes / eight actual relocations: three `getc` calls replace
the matching `/ML` object's inline FILE/`_filbuf` sites. These machine bodies
are different; the matching instruction proof does not assert production-body
identity. Both consumed eight-file source closures are verified. The VC4 game
relinks that owner with 35 verified unchanged objects, unchanged resource
object and pinned DirectX import libraries. Native and MinGW rebuild only the
resource-dependent targets, with one compiler at a time on one CPU.

The final Native library passes 99 unchanged original/Native PCX cases:
15 across the five supplied images and palette modes, plus 84 fixture cases
covering retries, clipping, signed maxima, zero runs and overshoot. Case
vectors are unchanged from the earlier focused PCX driver. Pixels, palette
bytes and external event traces agree. No unrelated owner, full historical
replay, new Wine run or physical Windows/audio verification is claimed.
235 historical input closures refresh with their 247 acceptance scopes unchanged.

Current four product hashes are in
`.analysis/pcx-packet-loop/product-verification.json`; the previous window-switch
products and prior PCX Wine evidence retain their historical identities.
The new checkpoint is
`.analysis/checkpoints/pcx-packet-loop-283-188/sha256.json`.
Feedback continues only in `/tmp/dxball_rea_feedback_20261010.md`.
This closes the remaining packet-control hypothesis within the defined scope;
do not retry declaration, local-layout or equivalent operand spelling.
The full original-source denominator and synchronized game/audio fidelity
remain open.

Checkpoint preservation: 116 owned files and 133 explicit immutable dependencies
verify after 26 scoped hash-verified archive links replace 4,800,512 previously
single-link allocated bytes. This accounts for about 4.6 MiB of duplicate storage,
not a measured device-free-space delta. Current/public files retain independent
inodes; unique Evidence, current products and complete before inputs remain.
Cleanup is confined to this new seal. No broad archive scan or additional
provider, compiler or case replay is performed.
