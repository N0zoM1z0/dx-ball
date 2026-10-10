# Exact integer trigonometry and hit-region stores

Five complete functions add 365 code bytes to the exact reconstruction:

| Entry | Function | Complete bytes | REA Evidence |
| --- | --- | ---: | --- |
| `0x402340` | `raw_sine` | 84 | `ev_f54833f6bdefa3ac2f65eb81ed53cd5e9722d4155caeae6d947f02db2c6242d1` |
| `0x4023A0` | `raw_cosine` | 84 | `ev_dfb4bd59f79a192687135c6244bb42f195fa6e89d307f8146a685f02ac44b3fe` |
| `0x402520` | `wave_x` | 50 | `ev_916def4083f9636ec2455ade5918e3a2ad718cbfb806f38e649d086280c1a1b1` |
| `0x402560` | `wave_y` | 50 | `ev_1b08c598ad977d80959318e20842816faa305f5345f823cf80b5cba35d227c00` |
| `0x401EB0` | `set_hit_region` | 97 | `ev_5eaf4df89184d5cd2372ce07008f453d3320f40a61205fdbfa5c79538fe2b180` |

All five saved REA dossiers attest contiguous bodies through the final RET.
The comparison covers every byte and relocation; no selected prefix, masked
instruction, copied machine code or generated wrapper is accepted. Existing
[menu](../INTRO_OWNER.md) and [editor](../EDITOR_OWNER.md) observations are reused.
No new original-analysis session or test matrix is added.

`src/intro.c` now normalizes the signed angle inside each raw lookup function,
then stores the table value back to that parameter before returning it. The
last store is present in the original instructions although the decompiler
folds it into a return expression. Negative multiples of 360 select endpoint
360; nonnegative multiples select zero. Negation of INT_MIN and overflowing
wave arithmetic remain outside the previously accepted semantic domain.
The wave functions add their scaled displacement to the origin parameter and
return the updated origin, matching the observed memory ADD and reload.

`src/editor.c` stores each region field through its indexed aggregate. The
original recomputes the 20-byte record address for all five writes. Removing
the cached record pointer restores that access pattern. Field order, storage
ownership and public prototypes are unchanged. Exact emission supports these
operations; it does not establish original identifiers or source spelling.

Relocations bind the sine table at `0x424650`, cosine table at `0x424BF8`, raw
lookup entries at `0x402340`/`0x4023A0`, and whole hit-region array at
`0x4251A0`. These targets come from saved original references, independently
of the emitted objects. `config/match-units.toml` records all bindings and
the complete input closure for the new `intro` compiler owner.

Earlier bounded diagnostic models are retained privately: a signed elapsed
sample leaves three differences, commuted height indexing leaves 158, and
triangle conditional assignment worsens 99 differences to 267. None is
adopted. The maintained triangle remains a full 1,710-byte candidate with 99
frame-displacement differences; its matching 160-byte table is not separately
accepted. Elapsed and height remain candidates.

The frozen native Debug batch passes all 22 existing owner scripts. A
continuation interrupted its process after 11 completed checks; their actual
input, library and log hashes were verified before resuming, and only the
unfinished check was restarted. Complete grouped cold replay passes all 86
units / 11,124 code bytes and 136 separate metadata bytes, preserving all 81
prior units. Existing 14 rejection controls, MinGW and full VC4 builds pass.
The unchanged raster and rotation compiler-input closures justify reuse of
their preceding 7,164 and 1,024 COFF vectors. No tracked test or fixture changes.

Acceptance stays at **283 source-present / 247 scoped semantic entries /
112,273 distinct cases**, with **86 exact units**. Origins remain 270 authored,
48 runtime, 42 compiler-generated and 168 unknown. Private checkpoint:
`.analysis/checkpoints/exact-integer-trig-283-86`, parent
`.analysis/checkpoints/exact-control-flow-283-81`. It retains full frozen
inputs, actual products, saved original evidence, failed models, interrupted
logs and independent reviews before verified cleanup. The 465-record REA
snapshot is unchanged.

Source presence, semantic scopes and distinct cases stay unchanged. The full
authored denominator, types, whole-game fidelity and **>=95% complete-source
objective remain open**.
