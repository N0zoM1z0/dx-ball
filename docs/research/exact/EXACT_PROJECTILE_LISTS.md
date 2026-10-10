# Complete projectile and fire-effect list lifecycle

This batch restores eight whole list helpers and independently reviews the
already restored 328-byte projectile controller. The nine enclosing spans total
1,352 bytes. Each deletion has 215 owned instruction bytes in a 220-byte span;
all five intervening bytes are retained and compared separately from ownership.

| Entry | Shared C entry | Owned / span bytes | Complete REA Evidence |
| --- | --- | ---: | --- |
| `0x410030` | begin-fire-effects | 57 / 57 | `ev_b6253aac5e138638d2538a2c36a3eb032a1e5bc82362923a44fe93a52fcfdf62` |
| `0x410130` | begin-projectiles | 57 / 57 | `ev_486b331b8d0f2c90bbc7bf666e701389d8bf5a5275a09c16bfb392d83ba85602` |
| `0x410230` | advance-projectile | 89 / 89 | `ev_f346971775972564d3df0cf90c5a9bbf622f652beb1c4f5906d0525e2ae67276` |
| `0x413170` | update-projectiles | 328 / 328 | `ev_412b7a2d61e8a498417dca7a456838ed290b17317e4af4585d8b936b69b07495` |
| `0x413410` | append-projectile | 146 / 146 | `ev_795c1af759609398f1bf4e5445e984b338706d39ca41b54043032d5252668d8d` |
| `0x4134D0` | remove-projectile | 215 / 220 | `ev_7e37d6b4a6b93d0007e1b0679c02cddce7d7956455acffda59a5c0f6617099ca` |
| `0x413670` | append-fire-effect | 146 / 146 | `ev_180304c402a6603ffd9ca1178288a139f84751fa978d2206736975d6cd57ba16` |
| `0x413790` | remove-fire-effect | 215 / 220 | `ev_af528cd7404de0f2e8bb6408f7832e2abd28901fba6e04e8dfee1c295b69da8e` |
| `0x413870` | advance-fire-effect | 89 / 89 | `ev_11a49b151d89a53b048ed74ee85f855ffc1894ce79fbb063b6467d52611437bb` |

One focused pinned REA/Ghidra session reads the missing five bytes at
`0x41359B` and `0x41385B`. Both complete reads return `e907000000`, recorded as
`ev_cfeffd063a4cc65df314d6958f2cab7ae28761c1029c5cfbfa2c37a8557b810e`
and `ev_2201bb1ef461da82a1f339a0fc864116395208f284dff55d2324bd4e8c482220`.
Their interpretation as jumps to `0x4135A7` and `0x413867` is inference;
instruction ownership stays 215 bytes. Explicit close/save extends the full
snapshot from 476 to 478 Evidence records, with zero primitive entries.

The shared helper source preserves the original positive branch structure,
full integer results and separate live owner writes. Appending initializes
only links, sets last to the saved node, then reloads last into current.
Natural typed `sizeof` values retain the original 24/20-byte i686 nodes and
grow with host pointers. Begin writes current before its explicit branch.
Advance rewinds after reaching the tail while returning zero. Deletion tests
the current node before saving it, writes both neighboring links, changes the
cursor, updates first and last, then calls the genuine runtime deletion entry.
Its meaningful saved node is consumed; the two observed compiler pointer-copy
homes are not invented as additional named source variables.

The controller remains unchanged. A separate review of every instruction,
reference and state effect confirms the existing movement/RNG/death/hit order.
The parent whole comparison's eight remaining bytes are swapped column/row
stack displacements. Original declaration spelling and storage assignment are
unknown; no local-order or body alternatives follow this observation.

The three-pointer access prefix is distinct from the current complete owner
layout: its constructor also clears the unresolved word at `+0xC`, for 16 i686
bytes. These helpers access only the pointer prefix. That fourth word, node
payloads and all other source bodies remain unchanged.

Native fixtures require one genuine typed `runtime_new(uint32_t)` boundary for
the newly direct calls. The existing allocation slot has a separate genuine
`size_t` adapter. The loader verifies both bodies and the actual table belong
to its copied image, and stages their original identities before inherited
constructors install callbacks. The C export reads the current allocation
slot, widens the request for a controlled callback, and uses the real recovered
body for default, null or self slots. Recursive entry is rejected. Existing
runtime-delete forwarding and all previous C wrapper bodies remain unchanged.
This host boundary forwarding does not establish allocator or hardware fidelity.

The stable grouped replay and configured cold epoch establish the separate
acceptance scopes below. Existing cases, oracle bodies and campaigns remain the validation
boundary. Source presence, semantic scopes and exact matching stay separate;
the >=95% complete-source goal remains active and unachieved.

| Complete body | Object / target bytes | Full differences | Current scope |
| --- | ---: | ---: | --- |
| `begin-fire-effects` | 62 / 57 | 17 | nonexact candidate |
| `begin-projectiles` | 62 / 57 | 17 | nonexact candidate |
| `advance-projectile` | 99 / 89 | 27 | nonexact candidate |
| `update-projectiles` | 328 / 328 | 8 | nonexact candidate |
| `append-projectile` | 146 / 146 | 0 | exact |
| `remove-projectile` | 208 / 220 | 52 | nonexact candidate |
| `append-fire-effect` | 146 / 146 | 0 | exact |
| `remove-fire-effect` | 208 / 220 | 52 | nonexact candidate |
| `advance-fire-effect` | 99 / 89 | 27 | nonexact candidate |

The one maintained diagnostic object physically retains all 69 actual source
and header inputs. One configured 22-object cold epoch accepts 118 whole
units / 18,229 code bytes and 136 separate metadata bytes. All 116 preceding
code/metadata identities survive; 2 new whole units add 292 bytes.
All 29 family relocation operands, including the unchanged controller,
are applied from actual COFF records and independently checked against complete
primary references and established bindings. No relocations or bytes are masked.
16 compiler literal operands across 7 complete constants refresh
their generated names only after full emitted/target content comparison.
Their offsets, types, addends and original targets remain unchanged.
Begin/advance return spelling,
deletion-copy provenance and controller storage homes remain unknown where
the complete comparison differs. No source variants follow the diagnostic.

Strict serial Native and the prepared shim pass on their first attempts.
The 22 existing owner scripts pass in 663.317 seconds with 293
physically frozen inputs. Seven checks pass: complete cold replay, fourteen
rejection controls, actual cold raster-product adoption without recompilation,
7,164 raster vectors, 1,024 rotation vectors, strict MinGW and full VC4 builds.
All existing test/case/oracle bodies remain byte-identical. Only the loader's
two owned initialization functions change for the typed allocation boundary.
All 50 preceding C wrapper functions remain byte-identical; the shim supplies
42 genuine symbols and 43 default/adapter ownership checks, with 49
actual compiler MD dependencies. These are host boundary results, separately
from hardware and physical allocator behavior.

An initial read-only review driver accidentally included the explicitly changed
C shim in its unchanged-test-file filter. Its actual failed script/log are
retained; only that audit path filter was corrected. Source, headers, native,
fixtures, cases and compiler/provider execution were unaffected. The independent
final audit's preparation also preserves its prior script versions before
dependency/schema refinements; it performs no builds or native execution.

The first cold-validation launch reached a real 120-second timeout in the
VC4 compiler version-banner probe before producing any configured cold object.
The complete failed driver, validation receipt and logs are retained. After
explicitly terminating only this project's Wine prefix, the unfinished
validation stage was retried. All 22 already successful owner replays remain
unchanged and were not repeated; one actual configured cold epoch follows.

Native family/canonical SHA256 `0c0cb3728a00d50adb5a8d938419fe37f58ca21e637e79e353e945951c9ac92e`; shim `c5235de447ab3988a84194d68d514879d3ab5bb4b304d9bad59c2dd9173331da`.
Source presence stays 283; scoped semantic rows 247; distinct cases 112,273.
The 235 changed semantic closures refresh with
fixed addresses, scopes and cases. Origins stay 270 authored / 50 runtime /
42 generated / 166 unknown. Checkpoint
`.analysis/checkpoints/exact-projectile-lists-283-118` links to effects 116.
The >=95% complete-source goal remains active and unachieved.

The executed independent audit then found an omitted `src/allocator.h` in the
core compiler dependency ledger. This genuine included header was already
physically frozen in the 293 owner inputs and 69 diagnostic inputs. The entire
failed audit, original manifest, full 22-object epoch and original receipts are
retained. Only this dependency is added to the parsed manifest; source, flags,
relocations, native, shim, fixture and oracle inputs stay fixed. One affected
core object is recompiled, with every complete code and metadata identity
preserved; all other 21 actual objects and all 22 successful owner replay
results are reused. The corrected report and match ledger bind the complete
dependency list. This additional core attestation is separate from the initial
22-object epoch and requires no source alternatives or repeated owner tests.
