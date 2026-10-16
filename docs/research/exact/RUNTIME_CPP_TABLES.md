# C++ exception tables and unwind filtering

October 16 tail-pointer follow-up: foreign handling is now 212/213 bytes with
105 strict differences; the three owner exacts remain unchanged. The earlier
checkpoint comparisons below remain historical.

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

The later [terminal source recovery](RUNTIME_CPP_TERMINAL.md) supplies the
translator/default callback state and exact inconsistency/terminate SEH bodies.
The translator execution and complete exception-runtime integration remain open.

## Original catch-list tail pointer (October 16)

At `0x0041B58C..0x0041B5A6`, the original forms the one-past handler pointer,
reads the final type at displacement -12 and subtracts one handler only when
preparing CatchIt's argument. The maintained source now carries that actual
one-past pointer, checks `end[-1].type`, and passes `end - 1`. It previously
materialized the last-handler pointer before the type checks. The nonempty
catch-list metadata precondition and all effects remain unchanged.

One VC4 compilation and four complete comparisons preserve the 33-byte pointer
adjustment, 159-byte try-range selection and 22-byte filter exactly. Foreign
handling becomes 212/213 bytes with 105 strict differences, versus the previous
213/213 with 70. Both have 83 instructions. The restored tail calculation,
negative-offset type load and deferred subtraction now follow the original;
state/entry register choices, equivalent loop-bound comparisons and scheduling
remain different. The shorter encoding shifts subsequent byte positions.
The increased strict difference count is explicit; no normalized comparison is
used for exact acceptance and no register/declaration sweep follows this change.

The retained full `frame.obj` proof and REA evidence above are reused. Native
and i686 C++98 compilation pass with warnings as errors. No provider, runtime
check or full replay runs. Only this source file and its four comparison units
are refreshed; the other 370 accepted rows and all outside candidate/producer
rows are retained unchanged. Totals remain 464 source-present / 373 exact,
76,842 exact code bytes and 244 metadata bytes.

Products, the initial stale-relocation comparison rejection, the corrected
four-unit comparison, diagnostic instruction correspondence and adoption
receipt remain in `.analysis/cpp-foreign-handler-tail-20261016/`. The actual
CatchIt relocation moves from object offset 181 to 180; its target remains
`0x0041B780`. Complete byte comparisons retain that genuine binding.
