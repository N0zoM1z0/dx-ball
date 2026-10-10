# Complete brick animation lifecycle

This batch restores the complete explosion step (`0x412730`, 797 bytes),
animation removal (`0x412A50`, 215 owned bytes in a 220-byte enclosing span),
brick animation constructor (`0x412BA0`, 259 bytes) and brick animation step
(`0x412CB0`, 313 bytes). The four comparison spans total 1,589 bytes.

REA supplies static observations; maintained C, unmodified original execution
and the configured compiler comparison establish separate acceptance scopes.
Original source names, declaration spelling and compiler temporary provenance
remain reconstruction decisions or unknowns.

| Entry | Full original evidence | Scope |
| --- | --- | --- |
| `0x412730` | `ev_b10ee96258ecd655c8f9258fc4ae6cb2c52939077283dc0409f9f912688f79b3` | Full 797-byte contiguous body |
| `0x412A50` | `ev_15590b4df69e7901145c02e294dca11e8f4f9c5be7675b3a332149d8dddde90e` | 215 owned bytes, 220-byte span |
| `0x412BA0` | `ev_7eda693d325f4e61bc31fe0071ee3433139eeff19ba5af6f227a22eccb923b21` | Full 259-byte body, byte tile argument, cdecl calls |
| `0x412CB0` | `ev_ddb63b6637b595283546b24dd97e5dba3e2af6a5b63142902883b2e6aa6dd702` | Full 313-byte contiguous body |

One focused pinned REA session obtains the constructor's previously missing
instruction dossier and reads all five deletion gap bytes. Raw evidence
`ev_d01134026e2cc2343a708aa0acd0b043ab354455e2353c73c0878d1bd9aef7ba`
returns `e907000000` at `0x412B1B`. Interpreting that as a jump to `0x412B27`
is an inference; Ghidra ownership stays 215 bytes and every enclosing byte
remains in comparison. Explicit close saves 476 Evidence records and zero
primitive cache entries. No target bytes or provider binaries are changed.

The constructor preserves separate mode branches, live current-node writes
and its actual bonus call. Both steppers preserve signed timing and frame
branches, consumed screen coordinates and rectangles, and direct original
dependencies. Explosion cleanup uses the existing typed COM BltFast slot,
then reloads the current node for occupancy cleanup. Brick stepping initializes
its consumed rectangle before the timing test and preserves duplicated surface
selection and tile redraw within the frame branches. Removal retains the
meaningful saved node and genuine runtime deletion boundary. It does not invent
the two compiler-generated pointer copies as named source variables.

The stable grouped replay and configured cold epoch establish the separate
acceptance scopes below. Existing cases remain the validation boundary.
The >=95% complete-source goal remains active and unachieved.

| Complete body | Object / target bytes | Full differences | Current scope |
| --- | ---: | ---: | --- |
| `step-explosion-effect` | 797 / 797 | 49 | nonexact candidate |
| `remove-brick-effect` | 208 / 220 | 52 | nonexact candidate |
| `spawn-brick-effect` | 259 / 259 | 0 | exact |
| `step-brick-effect` | 313 / 313 | 2 | nonexact candidate |

The single maintained diagnostic representation is followed by one configured
22-object cold epoch. All 115 preceding whole code and metadata identities
survive. The current acceptance is 116 complete exact units / 17,937 code bytes
and 136 separate metadata bytes, adding 1 whole units / 259 bytes.
All 95 family relocation operands are mapped from complete primary
references and established target bindings before the native replay is frozen.
No byte masks, source alternatives, name/order/layout/capacity trials or
unconsumed local variables are used. Nonexact source storage homes and compiler
deletion temporary provenance remain unknown.

Strict serial Native succeeds on its first attempt. An initial 292-input owner
epoch passes two scripts, then CoreNative exits with a segment fault because
its inherited real board surface has no BltFast slot 7. The complete failed
epoch, empty failure log, inputs and products are retained. A constructor-only
EntitiesNative correction installs that genuine slot and forwards the current
live RenderOps.restore. Source, headers, manifest, native library and shim stay
fixed; no compiler/provider restart or new test cases follow this correction.
The final 22 existing owner scripts pass in
638.667 seconds against 292 physically frozen inputs. Seven existing
checks pass: complete cold replay, rejection controls, actual cold raster product
adoption, 7,164 raster vectors, 1,024 rotation vectors, strict MinGW and full VC4.
Raster adoption records semantic_driver_executed=false and adds no compilation.
No tests, case matrices, target oracle bodies or campaigns are added.

The shared native harness forwards four genuine typed entries: runtime_delete,
draw_sprite, draw_reduced_sprite and restore_effect_region. It stages actual
EffectOps and RenderOps from the owned copied image. Default, null and self
slots use its actual maintained bodies; recursive entry is rejected. Existing generate_bonus
and keyed-sprite wrapper bodies stay fixed. EffectsNative's constructor supplies
a typed COM surface and slot-7 callback to the live RenderOps.restore; opaque
surface normalization retains the existing event comparison. EntitiesNative's
constructor binds the same actual slot on its existing inherited surface;
RuntimeNative later replaces it as before. Both fixture changes preserve every
case and target-oracle body. This establishes
host boundary forwarding, separately from rendering or hardware behavior.
The shim's actual compiler dependency closure contains 49 files.

Native family/canonical SHA256 `fb2708ddb099dccdaf282a9958492dbc9574cbd0861253602cb9e6c445d2a495`; shim `daed844174dcaf013fc324652ec63435a093baf03a8e10b2e8ede6ba080ede64`.
Source presence stays 283; scoped semantic rows 247; unit-distinct cases 112,273.
The 235 changed semantic closures refresh with fixed
case counts, addresses and scopes. Origins stay 270 authored / 50 runtime /
42 generated / 166 unknown. Checkpoint
`.analysis/checkpoints/exact-effects-phase-283-116` links to brick-powers 115.
The >=95% complete-source goal remains active and unachieved.
