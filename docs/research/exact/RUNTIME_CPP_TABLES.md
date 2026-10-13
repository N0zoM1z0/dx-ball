# C++ exception tables and unwind filtering

The original's complete pinned frame.obj sections prove four boundaries and
their actual ABI. FrameUnwindFilter at0x0041B760 is22 bytes, including its genuine
terminate relocation, and matches in full. This previously unlisted boundary
fits between the unwind and catch functions. AdjustPointer33 and
GetRangeOfTrysToCheck159 also match in full in the complete four-function source
family. Foreign-handler213/213/70 remains a candidate (current/original/
differences), with every actual relocation applied.

The source preserves PMD's three signed displacements, native-width virtual-base
and metadata pointers, the backward state-range scan and its reads before the
wrapped-index guard. The backing metadata blob must contain the actual two-word
prefix before the first try entry; no sentinel entry is invented. Cursor setup
belongs inside the nonnegative-nesting phase, as the instructions establish.
That lifetime correction initially reduces range differences137 to89. The
initial pointer adjustment has one equivalent SIB encoding difference. Both
disappear in the full four-function family with its genuine exception-record
prefix definitions; those bodies are not rewritten to force register choices.
No register or operand permutation search was used.

Foreign handling first attempts the genuine SE translator, then inspects only
the final handler of each eligible nonempty catch list for the empty-name/null
type catch-all. It preserves continued scanning if CatchIt returns. Only consumed
metadata and exception-record prefixes are represented; unobserved trailing
fields are not invented. Translator state, transfer, inconsistency and terminate
remain genuine external boundaries, not fixture callbacks or stubs.

Current totals are539 inventory,414 source,307 exact and68,280 code bytes;
metadata136 and all249 historical semantic rows remain unchanged. All304 old
exact and97 candidate producers are reused with unchanged input/object hashes.
Current candidates98 (34 authored/64 runtime); origins270/192/43/34.
Only focused VC4/native/i686 compilation and complete comparisons ran, without
runtime tests or game builds. Two closed REA runs retain seven records under
`.analysis/rea/`; proofs and unique compiler products are retained under
`.analysis/runtime-cpp-tables-20261014/`. OS exception transfer and game
integration remain open.
