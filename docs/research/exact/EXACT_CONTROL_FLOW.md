# Exact score update and raster control flow

The score update at `0x00415880` now emits its complete 74-byte original body.
The maintained C compares the score before the displayed score and includes
the observed terminal return branch. All seven relocations bind explicitly:
score `0x422D18`, displayed score `0x43A884`, and score drawing `0x4158D0`.
The grouped cold replay accepts 81 units / 10,759 code bytes plus the previous
136 separate exception metadata bytes. All 80 previous units remain exact.

The triangle at `0x0040AB90` remains a complete candidate. Explicit right and
left scanline coordinates restore the original clamp branches, repeated
fixed-point conversion on the unclamped path, and right-before-left evaluation.
Each coordinate is initialized and passed to the horizontal span routine.
Complete comparison improves from 235 to 99 differing code bytes within the
same 1,710-byte extent. Its complete 160-byte exception metadata still matches;
that metadata is corroboration and adds no accepted metadata or exact unit.
Independent review separates the 99 differences into 51 persistent-local,
24 class-temporary and 24 consumed-coordinate displacement bytes; no branch,
call or arithmetic opcode differences remain. The remaining frame allocation
is unresolved. Original identifiers and
declaration spelling are unknown.

The elapsed-time helper at `0x004034F0` restores the second comparison's
interval-plus-start expression and explicit return alternatives. Its complete
81-byte candidate differs in three bytes in the first unsigned comparison.
The sampled clock value and 32-bit wrap behavior retain the existing contract.
A const-qualified timestamp emits the same three differences and is not adopted.

## Original evidence and complete boundaries

All evidence remains tied to English DX-Ball v1.07, SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`,
through pinned REA 4.1.0 / Ghidra 12.1.4.

- Score update: saved dossier
  `ev_f58f31dcc563b9653e897718b068dc40ec22843226aefb9e5dceaa2f4c366c90`
  supplies the continuous inclusive range `0x415880–0x4158C9`, all globals,
  the call and final jump/epilogue. Nothing is trimmed or masked.
- Triangle: saved dossier
  `ev_ad1b11b19724c19c9001ac422c47b0b3b83c6b2965625e31729f969414a6467a`
  and the complete extent/metadata evidence in
  [EXACT_FIXED_POINT.md](EXACT_FIXED_POINT.md) cover the entire function,
  sixteen cleanups, handler and plain-RET continuation. The previous handoff's
  three tail gaps were only a subset of the 235 full-body differences.
- Elapsed time: saved dossier
  `ev_dc428fd862c9ce4132ee472c5865486bb43a7deef839266da3a08d839717038f`
  spans 81 bytes but assigns only 76 to the imported function. The new bounded
  [runtime request](../../../config/rea-control-flow-runtime.json) reads all 81 bytes
  and inspects the five-byte gap at `0x40352D`. The provider leaves that gap
  undecodable/unowned; it does not attest a decoded instruction. The read
  supplies `e90a000000`, matching the emitted branch bytes. Full comparison
  includes it. The read is
  `ev_6d8df29bd4997303b97df806aa1848fc78278242f57763213486a0cea8d3d6ee`;
  the limited inspection is
  `ev_dd0eb4d1e68549537959c531fdf4971fad5d22a042153a854736e2ac76aca2f0`.
- The [control-flow requests](../../../config/rea-control-flow.json) collect the
  stretch-sprite dossier/read (139 bytes) and store-board dossier/read (52).
  Stretch dossier/read IDs are
  `ev_a1de6b1fd71e04e5cb19b2cd96c5b604b588748746650f4a7e2bb791e0220953`
  and `ev_59ed8a6903a34d0dba0bebfd2c39363072c715c090bac6d7b54c8e52831613e5`.
  Store-board IDs are
  `ev_e1306a85acdb2e3478f5b9bff87b3787f63be873c0fe931ed6077dc9644529b5`
  and `ev_f7d01915f42bafba0065bffd9456b63b261ef411bb8c195eb29ee3ce6f871ecb`.

## Bounded hypotheses and verification

Moving the triangle's scalar initialization to its later algorithmic phases
worsens full comparison to 239 differences and is not selected. Swapping
commutative operands leaves stretch and paddle at four differences each.
Compiling unchanged owners as C++ with ordinary C linkage worsens stretch to
141/139 bytes and 90 differences; paddle stays at four. Unwrapped C++ owners
have different mangled APIs. These models are retained privately, not adopted.
VC4 rejects `/TP`; the valid diagnostic uses a `.cpp` source filename.
Board/queue aggregate address differences remain unresolved; the complete
20,432-byte board owner, including terminal bank access, is preserved.

The stable batch runs the 22 existing owner scripts once, the existing 7,164
raster COFF vectors, grouped exact replay, 14 rejection controls, MinGW and
full VC4 builds, and 1,024 existing rotation COFF vectors. Raster class-helper
symbol numbers change after the real coordinate declarations; their mappings
use actual defined COFF labels and original attested addresses. All previous
code and accepted metadata are compared in full. No new tracked tests,
fixtures, semantic rows or distinct cases are added. The 235 affected
application semantic input closures are refreshed with unchanged scopes.

Source presence stays 283; scoped acceptance stays 247 entries / 112,273 cases.
Origins stay 270 authored / 48 runtime / 42 compiler-generated / 168 unknown.
Two closed REA runs add six records; the cumulative snapshot contains 465.
The private `.analysis/checkpoints/exact-control-flow-283-81` checkpoint retains
frozen sources, failed/final models, compiler products, closed REA records and
reviews before verified cleanup. Resource limits keep one compiler/provider
session, one build CPU and a 512 MiB provider heap. Native products remain
separate, with the current library in `build/native-exact-control-flow`.
The complete authored denominator and >=95% complete-source objective remain
open. No padding, fake local, copied code, assembly, profile-specific source,
volatile barrier or identifier enumeration is introduced.
