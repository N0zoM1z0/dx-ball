# Exact rotation through typed row state

October 22, 2026. The complete1572-byte renderer at `0x004026A0` and all four
rotation helpers compare byte-exact in one coherent shared-source object.
Authored acceptance becomes268/270 and83,049/84,968 complete exact code bytes.
Last-brick and PCX loading remain required: two functions/1919 original bytes.

## Recovered shared implementation

The [preceding full-frame model](ROTATION_COMPLETE_FRAME_RECOVERY.md) restored
all424 frame-role bytes but left two reversed MOV/IMUL operand pairs and a
private height-helper demotion. Its primitive coordinate and source-column
loads were ranked differently from the actual surface-descriptor member load.

The selected implementation retains a real12-byte row-projection record with
width, rounded Y and truncated Y, and a real4-byte source-column value record:

```cpp
struct DxBallRowProjection {
    DxBallUInt width;
    DxBallInt rounded, truncated;
};
typedef struct {
    DxBallUInt column;
} DxBallSourceColumn;
```

Every field represents an existing stored/read value. The row record occupies
EBP−332..−321, and the column word remains at−212. No storage, unused field,
padding, constructor/destructor effect or artificial operation is added. All
remaining real declarations are ordered under the observed bucket mechanism,
with the five visible-pixel values at function-root scope. Named objects use344
bytes and the retained nested double-rounded expressions use80 temporary bytes.
The complete renderer definition follows horizontal offset; all four helper
bodies and all other source bytes remain unchanged.

Pixel offsets use explicit low32 arithmetic followed by signed32 conversion
before host pointer addition. This retains the actual x86 product/offset and
negative-offset direction without an extra i386 instruction. The source inverse
checks both rewritten expressions, every original initialization/write/call and
the already retained double-rounding expressions. Both portable and legacy
builds consume this implementation, with the same eight recursive project
inputs and nine flags. No conditional exact-only body or recipe change is used.

## Member ordering evidence and bounded search

Three consumed-header orders leave the preceding1572/4 output unchanged. Two
explicit word-arithmetic forms also retain its four renderer differences; the
whole-offset form restores all four exact helpers. Two row-record positions
restore both IMUL pairs but leave1572/11 or1572/9 in other operand directions.
Two larger workspace models and two three-cohort models remain nonexact and
lose a helper. None is adopted or mixed with an old matching helper object.

One new frozen declaration position is compiled under the previously verified
function-tagged C2 observer. REA6.5.0 process Evidence is
`ev_819130f6fc77b0fe1649d642e61683c199786eb0d1d46d2c3303f957c112b212`.
All301 rank entries have explicit function tags and zero mandatory read
failures; CL/C1XX/C2 exit0. The actual row-record key28192 yields member ranks
71/84/64 at offsets0/4/8; descriptor key28195 yields pitch rank75. The captured
zero-offset address layer and extra local-type IDs invalidate the simpler
descriptor-base and declaration-count approximations. No Ghidra import occurs.

The existing full C2 rank-helper evidence
`ev_cb5eba78e7e479074c1480e2f9f262737eecb4896f899fccb83cb2305d0bcaa1`
reproduces those actual ranks. Two source-column record candidates then constrain
22 operand directions. A corrected ordinary C++ declaration model gives the
complete renderer1572/0 but loses vertical offset193/159. A consumed anonymous
record typedef form instead makes all five complete functions exact. The third
frozen projection-typedef alternative is left uncompiled at that stopping point.
Changed-source IDs/ranks remain screening predictions, not newly observed
runtime values or uniquely recovered historical spelling/type choices.

Exactly16 distinct successful compiler inputs occur, including the one observed
compile. No compiler repeats for mapping or bookkeeping. Offline vocabulary
and syntax corrections before compiler launch consume no compiler attempt.

## Complete closure and maintained verification

All five full functions compare through115 actual bindings and25 entire literal
references. Four eight-byte literals permute within the40-byte readonly carrier;
their complete cells, original float and four alignment bytes are checked.
Every anchor maps by actual payload/value and logical section identity. All28
non-FILE symbols and every raw auxiliary byte compare, with only the renderer's
actual section length1458→1572 updated. Actual section flags, relocation counts,
associative parents and complete noncode mappings remain checked. Strict local
target guards remain enabled. All four prior exacts retain their code identities.

Native rebuild changes only rotation.cpp/link, preserving60 companion objects
and63 compile command configurations. Exactly351 unchanged existing renderer
cases pass:344 geometry/angle/bank/slot/padding/retry fixtures and seven live
surface/bank callback cases. Complete guarded destinations, row padding, source
records/banks/trig tables, ordered calls and original code bytes are checked.
The verified fixture cache remains unchanged, with zero preparation. These
bounded finite-FP cases add no negative-pitch, wrapper, helper or full-game replay.

All work is serial on CPU0/35%, memory high/max384/512MiB. Whole compiler/capture
peak is393,588,736 bytes; native build/check peaks are43,409,408/59,117,568 bytes.
All recorded compiler/native memory events are zero. Historical249 semantic
scopes retain their original counts/order/oracle identities, refreshing only
current dependency hashes. No game relink/play follows this adoption; the
[retained October20 game record](../CURRENT_VC4_BUILD.md) keeps its own image.

## Retained products

Private authority is
`.analysis/rotation-member-context-source-search-20261022/current-checkpoint.json`,
with frozen producer inputs, full comparisons, raw observation/REA Evidence,
source/symbol/auxiliary proof, native351, installed comparison and adoption.
Overwritten files remain recoverable; closed unique evidence is member-size,
SHA256 and mode verified before obsolete inputs/objects are retired. Current
accepted objects, the tested native library and useful caches remain.

Accepted source SHA256:
`98861901264157ea3674210457a9de183702dcf70d177d03b254b20c1ef19096`.
Object SHA256:
`651b85a1cada97255360bf1483b6d2802395878c3b7655d231e91d5d4886afd2`.
The complete resolved/original renderer SHA256 is
`abccb5f9a755d8d297c2da1f806b286bada2d00c6d1bf36ae0ad914585735fc8`.

Cleanup verifies268 new archive members and14 superseded members in the prior
carrier before retiring209 obsolete files. Net released allocation is1,945,600
bytes before small index/checkpoint receipts. Accepted products/caches and the
canonical REA process Evidence remain; the earlier private1572/4 raw copies are
superseded and remain recoverable from their original verified archive.
