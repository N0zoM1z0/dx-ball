# Sprite-bank byte-count arithmetic

October 19, 2026. The shared loader now converts width to unsigned32 before
multiplying by height:

```cpp
nbytes = (DxBallUInt)width * height;
```

This restores the observed modulo32 byte-count contract. It does not recover
the historical cast spelling, validate a malformed image, or establish a source
optimum. Width and height retain their signed declarations and later consumers.

## Original producer and observable boundary

The complete original bank dossier is
`ev_b55c6def4c1b4af6c165acfb1623311bffa077753d93fab01531787dca6b6d70`.
The retained complete instruction carrier is
`.analysis/author-plasma-bank-linkage-20261018/routine-linkage-proof.json.gz`.
At 404714/404717 the original loads width and multiplies by height; 40471B
stores only the low DWORD. At 404721/404725 it adds three in that same width
and calls malloc. At 40478B/40478E/404795 the original passes the stored DWORD
as the fread count. No overflow check or high-half consumer intervenes.

Previously the shared C++ expression multiplied two signed32 operands before
assigning to unsigned32. The assignment conversion was too late to define a
signed-overflow product. Converting one operand before multiplication gives
both operands the observed unsigned32 arithmetic domain. The existing `+3`
already operates in that domain; no allocation policy or error cleanup changes.

One bounded witness supplies count1 and positive dimensions65536×65536, then
uses the existing CreateSurface failure boundary. The original produces a zero
byte count, requests three pixel-buffer bytes, performs fread with size1/count0,
publishes the signed dimensions and returns with the partial owner/open stream.
It never enters the upload loops or allocates a large image. The old actual
loader compiled with signed-overflow instrumentation fails at the multiply.
The changed actual loader passes against the unmodified original x86 routine,
including the create event, partial record and file position17. Only this
input prefix and boundary are claimed; arbitrary damaged-input safety is not.

## Complete compiler comparison and explicit demotions

One unchanged-recipe VC4 resource compile compares all18 complete functions,
262 actual bindings and six complete literals. Fifteen resolved code identities
remain unchanged. The bank remains1475 bytes/64 differences; the arithmetic
contract improvement is in the source definition, without a new exact claim.

| Function | Previous bytes / differences | Current bytes / differences |
| --- | ---: | ---: |
| find-glyph | 145 / 0 | 146 / 86 |
| draw-glyph | 328 / 0 | 332 / 258 |
| load-pcx | 979 / 851 | 979 / 850 |

The two glyph functions are explicitly demoted together. Independent instruction
review finds changed bank/slot effective-address producers, with the same
1048*bank+4*sprite addresses under the existing stable ordinary-memory scope.
Lookup's count-first short circuit, signed code comparison, sentinel and returns
remain. Drawing retains its rectangle, height/baseline/width/surface reads,
both calls and live width reread after Blt. No missing glyph operation is hidden
by the exact-count change. The PCX one-byte improvement is incidental scheduling,
not a newly restored operation. No old companion object is selected.

Current resource acceptance is11 exacts/2577 code bytes and seven candidates.
Overall totals are393 exacts/84633 code bytes/244 metadata bytes, with248
classified authored exacts and22 complete authored candidates. Source remains
present for all270 classified authored entries and475 inventory entries total.

The first comparator stopped at compiler-renumbered literal symbols. A separate
comparison consumes the same object, matching each whole literal and its
original target/addend/type before checking every actual relocation. No compiler
is repeated for that correction. The instrumented observer also retains its
field-name and JSON-serialization failures before the corrected observation;
neither correction recompiles its two private instrumented products.

## Focused validation and retained state

Native builds only resources and relinks its library. The ten unchanged bank
cases pass: seven supplied SBKs plus the existing small-stream, empty-bank and
creation-failure cases. The overflow witness is additional private evidence;
historical semantic case counts and scopes are unchanged. Other owners, the
full replay and game execution are not repeated.

The last linked VC4 delivery remains the October18 `40f92f0f…` image; it predates
this source checkpoint. Final game reconstruction/build and actual play checks
follow the remaining authored-source work. Neither that historical image nor
its play evidence is relabelled as a build or execution of this source.

Private `.analysis/bank-byte-count-20261019/` retains the fixed proposal,
complete comparisons, literal mappings, instrumented counterexample, corrected
observation, independent review and adoption/coverage receipts. Heavy commands
use CPU35%, one allowed CPU and memory high384MiB/max512MiB. Unique closed inputs
and proposal products are archived and member-size/SHA verified before removal;
current matching objects, the native library and useful caches remain.
The verified archive retains28 closed members in1,023,104 bytes. Removing the
reviewed originals releases7,790,592 allocated bytes after archive cost, before
the small cleanup receipt. The cleanup scope peaks at43,405,312 bytes with no
high/max/OOM events; that measurement does not describe the earlier compiler
scope. No blanket peak-memory claim is made for steps without a retained peak.
