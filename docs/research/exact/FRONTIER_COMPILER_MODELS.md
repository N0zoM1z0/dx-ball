# Bounded compiler-model checks

The current checkpoint remains **207 exact functions / 44,832 code bytes**.
Five VC4 compilations tested four specific questions. None produced a new
complete match; all source changes were reverted and the canonical objects
were retained. All 207 accepted functions and their compiler input/object
identities verify against the original executable.

| Question | Complete comparison result |
| --- | --- |
| Reverse the spelling of the minimum-top condition in presentation | Still two differences across 984 bytes; all nine exact display companions remain exact. |
| Compile the existing UI source as C++ | Five exact companions remain exact, but RGB rotation stays at four differences, right palette shift worsens from six to nine, and text measurement grows from 279 to 281 bytes. |
| Limit allocation and upload locals to their sound-loading operations | The 695-byte loader worsens from 31 to 38 differences; all fourteen exact sound companions remain exact. |
| Express the embedded explosion-list address using the real storage offset | All gameplay comparisons stay unchanged; VC4 still emits LEA where the original loads an immediate address. |

VC4 requires `/Tp<source>` to select C++ for a `.c` input. It rejects `/TP`
with warning D4002 and still emits a C object. That first diagnostic object
is retained separately from the actual C++ result. The C++ comparison maps
the emitted decorated symbols and actual relocation offsets to the existing
reviewed target identities; it is diagnostic and changes no accepted recipe.

The presentation condition computes the same signed minimum under either
read schedule. Likewise, an embedded-list address explains a code-generation
difference rather than a different list owner or layout. Repeating equivalent
conditions, these two language models, these sound scopes or the offset
projection will not advance the current frontier without new evidence.

Private inputs, compiler outputs and complete comparisons are retained in
`.analysis/presentation-top-order-20261012/`, `.analysis/ui-cpp-model-20261012/`,
`.analysis/sound-upload-scopes-20261012/` and
`.analysis/explosion-storage-address-20261012/`. Their verification and bounded
cleanup receipt are in `.analysis/exact-frontier-20261012/`. Only a hash-equal
duplicate diagnostic object was removed. No game run or portable rebuild was
needed for the rejected changes.

A later `/Z7` diagnostic on the geometry and core owners preserves all their
existing complete comparisons, including every remaining candidate difference.
Debug information does not resolve their stack-home allocation. The two objects
and full literal-alias checks are retained in
`.analysis/debug-compiler-model-20261012/`; canonical recipes are unchanged.
