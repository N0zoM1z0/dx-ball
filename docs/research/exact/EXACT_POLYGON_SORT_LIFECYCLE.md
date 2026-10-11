# Independent polygon sort lifecycle and early exits

Both polygon controllers now recover the original Shell-sort gap lifecycle and
independent key exit in all four sorts. Only `src/raster.cpp` changes. Each
complete sort has70 instructions at the original relative offsets and14 direct
branches with corresponding successors. Neither complete controller is exact.

The original divides gap by3 before the condition, then has a distinct division
block for iteration. Source now uses `for (gap /= 3; gap > 0; gap /= 3)` after
the unchanged gap-growth loop. The independent inner loop checks `j >= 0`,
then exits when the next key is greater than or equal to the current key;
the following swap is unconditional. Equal keys remain stable. Pending sorts
use `top`; active sorts use `x`. Index expressions, data layout and scan
conversion remain unchanged in source.

| Complete sort | Original start | Current start | Bytes / instructions |
| --- | --- | --- | ---: |
| Ordinary pending | `0x40B72A` | `0x40B72A` | 241 / 70 |
| Ordinary active | `0x40B8EC` | `0x40B8E7` | 243 / 70 |
| Clipped pending | `0x40BD3A` | `0x40BD3A` | 241 / 70 |
| Clipped active | `0x40BEFC` | `0x40BEF7` | 243 / 70 |

All968 bytes/280 instructions are retained and examined. Each sort has six
scoped frame homes, two independent IDIV blocks and three commutative gap+j
producers. Paired operand-reversed signed comparisons choose the same direct
successor. The clipped pending sort needs no comparison reversal.42 unequal
normalized instructions belong to explicit producer groups;238 others agree.
Raw CMP flags are not claimed equal. The reused current `saved` pointer maps
to distinct original temporary slots in the two disjoint sorts; there is no
claim of a whole-function bijection or original local spelling.

An initial conditional-swap/else-break interpretation was wrong: it adds a jump
around the else arm and changes the original key-exit structure. Its matching
compile is retained as a rejected diagnostic, with1542/1543 and631 differences
for ordinary,1602/1592 and712 for clipped. Native/MinGW and VC4 were also built
before the complete branch review; those intermediate products are preserved.
No runtime case runs on that diagnostic. Correcting the source requires a second
matching compilation and second affected Native/MinGW build/link. A smaller raw
difference count does not justify accepting the wrong control structure.

Final complete comparisons are:

| Candidate | Before bytes / differences | Final bytes / differences | Original / final instructions |
| --- | ---: | ---: | ---: |
| Ordinary polygon | 1484 / 1025 | 1532 / 886 | 458 / 456 |
| Clipped polygon | 1544 / 1048 | 1592 / 721 | 468 / 466 |
| Triangle | 1710 / 109 | 1710 / 99 | 482 / 482 |

Nine accepted raster units retain715 exact code bytes and136 metadata bytes.
Triangle's complete160-byte/17-relocation candidate metadata remains exact;
it does not increase accepted metadata. Its unchanged source emits14 changed
instructions: four reversed MOV/CMP/JGE-or-JLE predicates and one commutative
pitch*y MOV/IMUL producer. All482 boundaries remain stable;468 instructions
retain their before bytes. This is explained before/current emission evidence,
not a new original/current exact or whole raw-register/flags claim.

Each final original/Native and actual relocated VC4 COFF/Native profile passes
1080 unchanged existing polygon cases (288 ordinary/792 clipped), plus72
separately recorded unchanged triangle cases. Full guarded buffers and ordered
effects remain compared. Horizontal span's144 exact bytes are unchanged; its
historical1080 cases are not rerun. These are1152 selected vectors in two
profiles, not2304 distinct vectors or a physical game/audio check.

The final CMake selection compiles only raster and relinks core/game products;
resource/board utility targets are excluded. VC4 links this matching object
plus35 verified unchanged objects, with no additional source compilation. All186
exact identities,36 game objects and four final product hashes verify.235
historical semantic closures refresh; their247 scopes/case counts remain
historical. Source283/exact186/33001 code/136 metadata/origins270/83/42/133
remain unchanged.

The next concrete original-source gaps are the scan setup's independent zero
assignments and `pending[next]` initial-y producer, plus the consumed row-address
local before horizontal fill. Original clipped fill selects capped arguments
in registers rather than rewriting left/right. The complete enclosing
instructions are retained; source spelling and complete body correspondence
still require a dedicated review. Do not trial names, layout or equivalent
comparison spelling to manipulate compiler allocation.

Evidence reuses the same closed dossiers as
[endpoint/indexed storage](EXACT_POLYGON_ENDPOINT_STORAGE.md). No fresh REA
query or provider latency/token/RSS measurement. Private proofs, actual recipes,
profile payloads and rejected-stage identities are in
`.analysis/polygon-sort-lifecycle/`; seal:
`.analysis/checkpoints/polygon-sort-lifecycle-283-186/sha256.json`.
