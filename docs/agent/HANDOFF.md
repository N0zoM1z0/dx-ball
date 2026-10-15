# DX-Ball reconstruction handoff

Prepared from `583453677bdfb57807a42c9f7a305a5ce6a3d17d` on October 13, 2026.
The user requested this handoff and stopped the current reconstruction run.
The objective remains unfinished. Resume DX-Ball when work is handed over.

This is the authoritative handoff. The previous 843-line history is preserved
[in Git at 5834536](https://github.com/N0zoM1z0/dx-ball/blob/5834536/docs/agent/HANDOFF.md).
Use its linked research notes for older evidence rather than loading it all.
The old `/tmp/dxball_reconstruction_handoff.md` is stale.

## Goal and user requirements

The user's first priority is: **“先把所有的函数尽可能 exact 还原完”**.
Recover the original English DX-Ball v1.07 functions as exactly as possible.
The broader project remains a nearly complete source reconstruction that
rebuilds and plays, but function recovery comes first.

- Work on DX-Ball. Leave TH04 alone.
- Work directly from the local original binary and retained REA evidence.
  Do not search online for existing source or another reconstruction. Original
  source and debugging files are unavailable; keep exploring and trying
  evidence-supported source models.
- Prioritize complete-function comparisons. Defer long game campaigns until
  function recovery is ready; passing gameplay samples is not an exact claim.
- Keep the full goal across turns and handoffs. A small checkpoint, compatibility
  result or passing fixture does not finish it. Mark completion only after
  current source, complete comparisons and required evidence prove the goal.
- Make concrete progress: select a missing operation, ABI, expression or lifetime
  supported by instructions; implement a bounded trial; compile and compare it;
  record the result. Avoid long speculative planning and repeated closed trials.
- Keep repository code and documentation English. Write natural, detailed prose
  without repetition or defensive claims. Preserve the reader-facing README
  tutorial and its English `/goal` example, centered title PNG and 900px SVG.

For a fresh Codex thread, the intended prompt is:

```text
/goal Recover all original English DX-Ball v1.07 functions as exactly as possible
from the local binary. Read AGENTS.md and docs/agent/HANDOFF.md first. Prioritize
complete-function restoration over game campaigns. Use retained REA evidence,
keep resource use bounded, preserve honest exact claims, and commit and push
verified checkpoints. Do not switch to TH04 or search online for a reconstruction.
```

If the thread still has a registered goal, resume it. Otherwise start a new
goal with the prompt above, preserving the same objective.

## Current authoritative state

| Item | Current value |
| --- | ---: |
| Provisional function candidates | 543 |
| Source-present functions | 457 |
| Exact functions | 353 |
| Complete exact code bytes | 73,495 |
| Attached exact metadata bytes | 136 |
| Historical scoped semantic rows | 249 |
| Confirmed authored nonexact candidates | 34 |

These are separate ledgers; 353 exact functions does not prove project completion.
All 34 authored candidates have complete comparisons. Their sizes and differences are in
[REMAINING_EXACT_FUNCTIONS.md](../research/exact/REMAINING_EXACT_FUNCTIONS.md).
The authored denominator and 24 unclassified origins remain open.

Low-I/O startup improves468/467/304 to467/467/32 through shipped ioinit.c block
index, packed-handle cursor, shared descriptor counter and acquisition guards.
All19 actual relocations are compared; remaining register rotation and equivalent
comparison direction are nonexact. Original flag/standard-handle types give37
differences and are rejected. All353 exacts and95 other candidate results remain;
totals353/code73,495/candidates96 unchanged. Two VC4/native/i686 sets; selected
private product reused through identical canonical inputs. Retained REA/full CRT
section reused, no runtime/game tests. See [low-I/O startup](../research/exact/RUNTIME_LOWIO_STARTUP.md)
and `.analysis/lowio-startup-original-cursors-20261015/verification.json`.

Command-line parsing closes466 bytes and all four actual relocations through
shipped stdargv cursor phases and character/unsigned lead-index types, in the
original stdargv producer boundary and function order. Cursor recovery improves
475/466/280 to464/466/185; character types close466/466/0. Environment setup moves
unchanged to runtime_environment_setup.cpp and remains219 exact. Argument
setup151/155/116 is unchanged, including after original byte-block ownership and
argc-before-argv publication. All352 old exacts and96 other candidate results
remain; current353/code73,495/candidates96. Five VC4/native/i686 sets; selected
two products reused through byte-identical canonical inputs. Retained REA/full
CRT section reused, no runtime/game tests. See [arguments](../research/exact/RUNTIME_ARGUMENTS.md)
and `.analysis/arguments-original-object-owners-20261015/verification.json`.

Stream traversal closes107 bytes and all three actual relocations through
the original fflush.obj producer boundary and shipped function order. All four
bodies are unchanged. Buffer acquisition75/retirement57 and the other three
flushing exacts remain, as do all351 old exacts and97 other candidates. Current
352/code73,029, candidates97. Two VC4/native/i686 compiler sets; byte-identical
canonical inputs reuse the private products. Retained REA and full CRT section
reused; no runtime/game tests. See [stream buffers](../research/exact/RUNTIME_STREAM_BUFFERS.md)
and `.analysis/stream-flushing-original-owner-20261015/verification.json`.

Fcloseall closes115 bytes and all seven actual relocations through original
independent closeall.obj ownership. Its source body is unchanged; chsize359
and all350 old exacts remain, as do98 other candidates. Current351/code72,922,
candidates98. Two successful compiler sets, one failed private extraction
corrected before producing an object, no runtime tests. Retained REA and full
CRT section reused. Register index/count hints and original fread identifiers
each give identical complete results and are reverted. See
[stream retirement](../research/exact/RUNTIME_FILE_SIZE.md) and
`.analysis/stream-retirement-original-object-owner-20261015/verification.json`.
The rejected commit/seek/mapper ownership cascade is fully restored; retain
`.analysis/descriptor-commit-original-object-owner-20261015/closed-trials.json`.
Four unimplemented short entries received new scoped REA evidence; their code
requires x87/intrinsic or special-entry support. No shared C implementation
or exact acceptance is claimed for them.

Original fread object ownership and seven genuine scalar lifetimes improve
328/326/232 to326/326/2. All128 instruction addresses/widths and324 other bytes
agree; the initial multiplication loads opposite parameters. Reversing product
operands or initializing the owned total first emits identical full results;
both trials are reverted. Removing fread and its unused string header closes
the unchanged getstream126 body and all seven actual relocations. All349 old
exacts and98 other candidates remain; current350/code72,807, candidates99.
Four compiler sets, selected isolated product reused through identical canonical
inputs; retained evidence re-consumed after a publication-reader error without
recompilation. No runtime/provider work. See
[stream transfer](../research/exact/RUNTIME_STREAM_TRANSFER.md) and
`.analysis/bulk-read-original-object-owner-20261015/verification.json`.

Output refill improves328/328/67 through50 to328/328/1. Original conditional
safe-record selection reduces17 differences; independent _flsbuf object
ownership closes the register rotation and error-epilogue scheduling. Only
the CMP operand commutation at0x41A738 remains; swapping source operands gives
the identical result and is reverted. All349 exacts and getstream126/2 remain;
unchanged fread source emits328/326/232 instead of324/326/218 after separation.
Three compiler sets for ownership, with the selected isolated object reused
through byte-identical source/header inputs; no runtime/provider work. See
[stream transfer](../research/exact/RUNTIME_STREAM_TRANSFER.md) and
`.analysis/output-refill-original-object-owner-20261015/verification.json`.
The independent fread assignment/update-order trial worsens324/218 to324/223
and is fully reverted; its retained evidence prevents repeating that route.

Codepage setter improves473/475/128 to475/475/11 through the original six-word
case-info publication loop. Unsigned counters, local lead-range ownership and
OS clear-counter lifetime follow shipped mbctype.c. Only EAX/ECX rotation in the
OS lead-byte loop remains; all instruction addresses/widths and464 other bytes
agree. Four owner exacts, all525 initialized data bytes and all349 old exacts
remain. Four compiler sets, no runtime/provider work; retained objects re-consume
actual local-symbol bindings without compiler repeats. See
[codepage startup](../research/exact/RUNTIME_CODEPAGE.md) and
`.analysis/codepage-original-case-copy-20261015/verification.json`.
Three shared-open flag/index trials worsen1053/2; all source is reverted.

Openfile closes526 bytes and all16 actual relocations, including its alignment
byte and full114-byte switch carrier. Shipped _open.c establishes register mode,
flags and late stream capture, preincrement scanning, flag update order and
chained null stores after successful opening. All348 old exacts and100 other
candidate byte results remain; local-symbol bindings are refreshed from the
retained object without recompilation. One compiler set, no runtime/provider
work. Current349/code72,681. See [stream opening](../research/exact/RUNTIME_STREAM_OPEN.md)
and `.analysis/stream-open-original-register-lifetimes-20261015/verification.json`.

Float digits improves122/129/68 to122/129/65 through genuine register pointers,
consumed guard-byte advance and original conditional stores from shipped _fptostr.c.
Keep the defined complete memmove shift: original REP strlen/copy remains nonexact.
Explicit forward copying emits108/129/69 and is rejected. All four owner exacts,
both other owner candidates and all348 exacts remain. Two compiler sets, no
runtime/provider work. See [float formatting](../research/exact/RUNTIME_FLOAT_FORMAT.md)
and `.analysis/float-digits-original-lifetimes-20261015/verification.json`.

Descriptor allocation improves184/37 to184/4 through original block-index and
record-cursor lifetimes, direct bounds and table-before-capacity publication.
All instruction addresses/widths and180 other bytes match; only two commuted
loop comparisons and their equivalent branches remain. Both owner exacts,
all348 old exacts and the other100 candidate byte results remain. One compiler
set; retained object re-consumed with actual local-symbol bindings, no compiler
repeat or runtime/provider work. See [stream opening](../research/exact/RUNTIME_STREAM_OPEN.md)
and `.analysis/descriptor-allocation-original-index-20261015/verification.json`.
The onexit live-table byte-distance trial remains121/2 and is reverted.

Stream position closes432 bytes and all six actual relocations through the
original same-buffer pointer differences and seek-result assignment condition.
The pointer fields require coherent backed spans and representable differences;
32-bit offset wrapping remains explicit. All347 old exacts and101 other candidates
remain. One compiler set, no runtime/provider work. Current348/code72,155. See
[stream position](../research/exact/RUNTIME_POSITION_FILTER.md) and
`.analysis/stream-position-original-pointer-differences-20261015/verification.json`.

Heap resizing closes111 bytes and all seven actual relocations through the
original unbounded retry and owned handler-failure return from shipped realloc.c.
This restores the unconditional post-handler heap reload before the backward
branch. Msize21 exact, calloc82/11 and all346 old exacts remain. One compiler set,
no runtime/provider work. Current347/code71,723/candidates102. See
[heap resizing](../research/exact/RUNTIME_FILE_MODES.md) and
`.analysis/heap-resize-original-retry-20261014/verification.json`.
Signed-counter/cursor recovery gives44/19 instead of44/15 and is reverted;
the multibyte consumed-index/logical-return trial is byte-identical58/7 and
reverted. Their private producer phases retain the negative evidence.

Original CRT object ownership resolves the handle-gate conflict: `close.obj`
and `osfinfo.obj` are separate source producers, not one reconstructed aggregate.
Shared `runtime_close.c` preserves199 exact; shared `runtime_osfinfo.c` closes144
invalidation bytes and all six relocations, installation163/13 improves to163/2.
Read source is unchanged but emits609/611/473 in its separate context. All345 old
exacts remain; current346/code71,612/candidates103. Three producer compilations,
no runtime/provider work. See [handle lifetime](../research/exact/RUNTIME_LOWIO_READ_CLOSE.md)
and `.analysis/lowio-original-source-owners-20261014/verification.json`.

Zero allocation improves77/82/16 to82/82/11 through the original consumed size
parameter, retry loop and owned failure return. The unconditional post-handler
heap reload and complete extent are restored; multiplication input and initial
import/heap load order remain nonexact. Msize21 exact, realloc106/111/15 and all345
old exacts remain. Two compiler sets, no runtime/provider work. See
[zero allocation](../research/exact/RUNTIME_FILE_SIZE.md) and
`.analysis/zero-allocation-original-retry-20261014/verification.json`.
The handle-gate trial reaches144/0 but makes close199/3; all changes are reverted.
Do not repeat it: `.analysis/descriptor-handle-original-gates-20261014/` retains
three producer sets and the comparison-commutation proof. The authentic setmode
register/record trial remains128/2 and is also reverted.

Descriptor close closes199 bytes and all eleven actual relocations through
direct record expressions, owned validation errors and both standard-handle
snapshots in original query/comparison order. All344 old exacts and104 other
candidates remain. Three compiler sets, no runtime/provider work. See
[handle lifetime](../research/exact/RUNTIME_LOWIO_READ_CLOSE.md) and
`.analysis/descriptor-close-original-expression-20261014/verification.json`.

Descriptor seek closes188 bytes and all nine actual relocations through the
original record expressions, assignment conditions and owned invalid-descriptor
return from shipped CRT source. All343 previous exacts,105 other candidates and
the complete360-byte error table remain. One compiler set, no runtime/provider
work. See [low-I/O](../research/exact/RUNTIME_LOWIO_WRITE.md) and
`.analysis/descriptor-seek-source-expression-20261014/verification.json`.

Descriptor commit improves110/111/65 to111/111/2 through genuine register
descriptor/status and shared error/completion ownership from shipped CRT source.
All109 other bytes, instruction addresses and widths match; only bound CMP/Jcc
commutation remains. Both owner exacts/full360-byte table remain. Seek15 becomes13,
write19 becomes22 in this context, with unchanged source. Two compiler sets;
retained objects re-consume restored table metadata without recompiling. All343
exacts/103 outside-owner candidates/249 semantic rows preserved, no runtime/provider
work. See [low-I/O](../research/exact/RUNTIME_LOWIO_WRITE.md) and
`.analysis/descriptor-commit-register-owner-20261014/verification.json`.

Character classification closes145 bytes and all three actual relocations.
The shipped isleadbyte macro's unsigned-char table index, signed three-byte
payload and consumed payload/length order restore the exact body. Both229-byte
converters/all342 prior exacts remain; source457/exact343/code71,081/candidates106.
One compiler set, no runtime/provider work. See [case conversion](../research/exact/RUNTIME_CASE_CONVERSION.md)
and `.analysis/character-classification-macro-selection-20261014/verification.json`.

Bulk output closes381 bytes and all three actual relocations through the seven
genuine scalar lifetimes, unsigned write result and original update order from
shipped CRT source. Seeking153/21 improves to153/20 through its register stream
and relative-offset/origin update order. Three compiler sets, no runtime/provider
work; all341 old exacts and106 outside-owner candidates remain. Source457,
exact342/code70,936/candidates107. See [stream operations](../research/exact/RUNTIME_STREAM_OPERATIONS.md)
and `.analysis/stream-seek-register-owner-20261014/verification.json`.

Stream position improves413/432/360 to431/432/324 through the genuine register
stream/cursor, single adjusted offset, path-local scans and shared zero-count
return from shipped CRT source. Direct record expressions retain seek-time
reloads. Three compiler sets, no runtime/provider work; all341 exacts and107
other candidates remain. Not exact. See [stream position](../research/exact/RUNTIME_POSITION_FILTER.md)
and `.analysis/stream-position-register-owner-20261014/verification.json`.

Input refill closes240 bytes and all four actual relocations through its genuine
register stream, zero/-1 error exit and conditional safe-record selection from
shipped CRT source. All340 preceding exacts and three owner candidates remain;
source457/exact341/code70,555/candidates108. First retained object is re-consumed
without recompiling; scalar fread324/223 is rejected/restored to324/218. Three
compiler sets, no runtime/provider work. See [stream transfer](../research/exact/RUNTIME_STREAM_TRANSFER.md)
and `.analysis/input-buffer-register-owner-20261014/verification.json`.

Buffer acquisition75 and flushing100 are now complete exacts after all three
actual relocations. Genuine register locals follow shipped CRT source, not
guessed storage. Three owner exacts/all338 prior exacts remain; source457,
exact340/code70,315/candidates109. Unchanged traversal source emits107/14 after
register rotation; both traversal trials14 are closed. Four compiler sets,
no runtime/provider work. See [stream buffers](../research/exact/RUNTIME_STREAM_BUFFERS.md)
and `.analysis/stream-buffer-register-owner-20261014/verification.json`.

Raise improves393/393/323 to397/393/215 through its tagged handler snapshot,
captured FPE countdown and shared callback segment with genuine hardware guard.
No fake initialization or diagnostic suppression; all53 original dispatch bytes,
both lookup exacts/full140-byte state and filter351/9 remain. Four VC4/native sets,
four i686 attempts/two pass; no runtime/provider/game work. Global counts unchanged.
See [signal dispatch](../research/exact/RUNTIME_SIGNALS.md) and
`.analysis/signal-raise-separated-traversal-20261014/verification.json`.

Decimal insertion restores the original leading-e/E branch: skip digit scanning,
not insertion. Whole101/101 comparison improves5 to4 differences; four owner
exacts and both other candidates remain. The remaining loop scheduling is not
exact; captured-write reordering10 is rejected. Two compiler sets, no runtime
tests. See [float formatting](../research/exact/RUNTIME_FLOAT_FORMAT.md) and
`.analysis/decimal-point-insertion-flow-20261014/verification.json`.

Exception filtering improves376/351/355 to351/351/9 through the real tagged
handler snapshot and captured FPE action-slot countdown. Both exact lookups and
full140-byte state remain; raise393/323 including53 dispatch bytes is unchanged.
Its corresponding369/358 trial is rejected; renamed private COFF definitions
are independently resolved with equal values/whole393 raw bytes. Four VC4/native/
i686 sets, retained REA and no runtime/provider/game tests. Global counts unchanged.
See [signal dispatch](../research/exact/RUNTIME_SIGNALS.md) and
`.analysis/signal-filter-fpe-countdown-20261014/verification.json`.

Output refill now328/328/67, improving320/328/277 through genuine register
stream/count locals and separately owned final error return from shipped CRT
source. Both bodies have122 instructions; register/address/epilogue scheduling
remains nonexact. Two owner exacts and three other candidates remain; all340
exacts/249 semantic rows are preserved. Two compiler sets, no runtime/provider
work. See [stream transfer](../research/exact/RUNTIME_STREAM_TRANSFER.md) and
`.analysis/output-buffer-register-owner-20261014/verification.json`.

Terminal dependency identities/boundaries close two unknown origins:
terminate0x41BC60/inconsistency0x41BCE0, each115 bytes including the omitted RET.
Full hooks.obj code and both24-byte SEH tables match; source/exact remain open.
Origins270/204/45/24;338 exact/source457/candidates111 unchanged. See
[C++ handler dependencies](../research/exact/RUNTIME_CPP_HANDLER.md).

MessageBox lazy binding closes all146 bytes,14 actual relocations and58 literal
bytes by grouping the required module/export checks into a positive success
block. VC4 restores the terminal failure return; all four owner exacts remain.
Exact338/code70,140/candidates111; source457 and249 semantic rows unchanged.
One VC4/native/i686 set, retained REA, no runtime/UI/game tests. See
[error controls](../research/exact/RUNTIME_ERROR_CONTROL.md) and
`.analysis/messagebox-binding-success-20261014/verification.json`.

Catch transfer closes all148 bytes and five actual relocations by restoring
default-frame-first argument branches around the single genuine stdcall unwind
call. Intermediate marker-first148/3 is retained; final148/0 exact. Both188-byte
and44-byte owner exacts remain; all336 old exacts/112 other candidates/249 semantic
rows are preserved. Exact337/code69,994/candidates112; source457 unchanged.
Two VC4/native/i686 sets, retained REA and no runtime tests/provider session.
See [catch transfer](../research/exact/RUNTIME_CPP_TRANSFER.md) and
`.analysis/cpp-marker-argument-branches-20261014/verification.json`. Full SEH,
catch-object/catch-block execution and game integration remain open.

Locale mapping improves565/555/280 to561/555/278 by beginning wide-buffer/count/
result lifetimes only after ANSI and invalid-mode exits. Classification291 exact
and counter44/15 remain; all336 exacts/111 other candidates/249 semantic rows
are preserved. Explicit mode publication emits identical mapper bytes and is
reverted. Two VC4 stages, one native/i686 set, retained REA and no runtime tests;
global counts unchanged. See [locale backends](../research/exact/RUNTIME_LOCALE_BACKENDS.md)
and `.analysis/locale-mode-publication-20261014/verification.json`.

Scaling improves133/123/127 to125/123/115 through the native-width numeric table
address cursor, avoiding a pre-array C pointer. All47 instructions correspond;
only two MOV5/LEA6 root loads remain. Split capture is unchanged; pointer/address
union149/146 rejected. Coupled multiplication678/103, parser1851/1662; actual
definition offsets/tables and all336 exacts/110 other candidates/249 semantic
rows preserved. Three VC4 stages, one native/i686 set, no runtime tests. See
[decimal conversion](../research/exact/RUNTIME_DECIMAL_CONVERSION.md) and
`.analysis/decimal-power-address-cursor-20261014/verification.json`.

Multiplication further improves678/678/446 to678/678/104 through complete input
exponent-word snapshots and branch-local sticky reads. Its28-byte frame and all
three actual calls remain; not exact. Raw-exponent-only672/678/316 is retained.
Parser1851/1871/1662 and scaling133/123/127 retain their counts, with proved parser
output-register interchange/generated-label rebinding. Two VC4 stages, one
native/i686 set, retained REA and no runtime tests; all336 exacts/110 other
candidates/249 semantic rows remain. See [decimal conversion](../research/exact/RUNTIME_DECIMAL_CONVERSION.md)
and `.analysis/multiply-exponent-snapshot-20261014/verification.json`.

Multiplication improves708/678/666 to678/678/446 by restoring the product and
operand byte cursors and original positive-count entry. Not exact. Coupled parser
1851/1871/1661 becomes1662 through equality-CMP/output-register changes; internal
definition offsets, branches and tables remain. Scaling133/123/127 is unchanged.
Three VC4 trials, one native/i686 set, retained REA, no runtime tests. All336
exacts/110 other candidates/249 semantic rows are preserved; totals unchanged.
See [decimal conversion](../research/exact/RUNTIME_DECIMAL_CONVERSION.md) and
`.analysis/multiply-product-cursor-20261014/verification.json`.

Whole typed two-word copies improve user matherr174/174/41 to174/174/28;
both187-byte/79-byte owner exacts are preserved. No new exact; global counts
remain unchanged. One VC4/native/i686 set, retained REA reused, no runtime tests.
See [floating decomposition](../research/exact/RUNTIME_FP_DECOMPOSITION.md) and
`.analysis/math-error-representation-20261014/verification.json`. A separate
unordered-rounding expression trial expands154 to165 against original127;
rejected and source restored, with its unique product retained under
`.analysis/decomposition-zero-representation-20261014/`. Do not repeat it.

Exit control128 is exact through real ExitProcess stdcall and decrement-before-
comparison address traversal. Both18-byte wrapper exacts remain; walker32/6 is
unchanged. Source457/exact336/code69,846/candidates113, old335 exacts/113 candidates
preserved. Only four semantic rows refresh after the same1,031 calls/1,026 fixtures
across native and reused VC4/i686 objects, with unchanged observation digest.
See [termination](../research/TERMINATION_OWNER.md) and
`.analysis/termination-process-api-20261014/verification.json`. Retained REA,
one VC4/native/i686 set plus one native shared fixture build; no new cases,
provider/game/hardware tests or physical process exit. The native operation
table is fixture-only; source now invokes the genuine API. Startup/integration open.

Exponent editing improves57/57/22 to57/57/4 through a typed two-word snapshot.
The99-byte classification companion remains exact; generic memcpy59/57/57 is
rejected. Remaining initial word load/store order is nonexact. See [FP control](../research/exact/RUNTIME_FP_CONTROL.md)
and `.analysis/runtime-float-exponent-20261014/verification.json`. Two
VC4/native/i686 sets, retained REA reused, no provider/runtime/game tests.
Global457/335/code69,718/candidates113 unchanged; no permutation sweep.

Float assignment improves77/76/47 to76/76/9 through genuine binary64 word
representation/transport. Separate scalar carriers76/19 enlarge the frame and
whole-copy77/47 is rejected. All four owner exacts/two other candidates remain;
global457/335/code69,718/candidates113 unchanged. See [float formatting](../research/exact/RUNTIME_FLOAT_FORMAT.md)
and `.analysis/runtime-float-assignment-20261014/verification.json`. Three
VC4/native/i686 sets, retained REA reused, no provider/runtime/game tests.
Remaining register/load differences do not justify a permutation sweep.

String copy/concatenation add full source models198/232/232 and291/224/276.
Strcpy's old7-byte range was only its entry jump; full232-byte shared original
extent overlaps strcat224, not independent byte coverage. Exact335/code69,718
unchanged; source457/candidates113, all old335 exacts/111 candidates preserved.
See [string concatenation](../research/exact/RUNTIME_STRING_CONCATENATION.md)
and `.analysis/runtime-string-concatenation-20261014/verification.json`.
One closed one-record REA session; one VC4/native/i686 set, no runtime/game tests.
Explicit aggregate initialization is rejected by VC4 C2552; source restored,
unique failure retained. Do not repeat equivalent initializer spellings.

Embedded list initialization adds one complete21-byte exact outer stage and a
full inner candidate32/26/21. `/Ob1` expands only the implicit aggregate bridge;
all58 existing owner exacts remain unchanged, with genuine constructor bindings.
Source455/exact335/code69,718/candidates111; authored and origins unchanged.
See [embedded initialization](../research/exact/LIST_EMBEDDED_INITIALIZATION.md)
and `.analysis/list-implicit-inline-20261014/verification.json`. One VC4 compile,
retained REA reused, no runtime/game tests. These are generated source emissions,
not new authored routines; the inner stage and startup graph remain nonexact.

Stream seeking/output add full153/381-byte source bodies with21/29 differences.
No new exact:334/code69,697 unchanged; source453/candidates110. Preserve all334
old exacts/108 candidates/249 semantic rows. See [stream operations](../research/exact/RUNTIME_STREAM_OPERATIONS.md)
and `.analysis/runtime-stream-operations-20261014/verification.json`. One closed
five-record REA session; one VC4/native/i686 set, no runtime/game tests.

Aligned strlen adds a full source model,102/119 bytes with112 differences.
Preserve32-bit zero-byte detection, actual word reread and precise byte probes;
the original readable terminator-word footprint is explicit. Source451/
candidates108, all334 old exacts/107 candidates unchanged. See
[string length](../research/exact/RUNTIME_STRING_LENGTH.md) and
`.analysis/runtime-string-length-20261014/verification.json`. One closed two-
record REA session; one VC4/native/i686 compilation set, no runtime/game tests.

Full CRT fabs229 is exact. Preserve real control/classification/error boundaries,
infinity/NaN handling and finite binary64 representation before control restore
and return load. Category dispatch130→18, genuine result union18→0. Source450/
exact334/code69,697; all333 old exacts/107 candidates unchanged. See
[double absolute value](../research/exact/RUNTIME_ABSOLUTE_DOUBLE.md) and
`.analysis/runtime-absolute-double-20261014/verification.json`. One closed two-
record REA session; no runtime/game checks. Exponent suffix differences remain
commuted additions; no unsupported spelling/layout trial was made.

Memory copy adds partial forward-phase source,124/334 bytes with333 differences.
The declared nonoverlapping API is modeled, but the original reverse extension
and its incoming EDX path remain unmodeled. Source449/candidates107; all333
exacts/106 candidates unchanged. See [partial copy](../research/exact/RUNTIME_MEMORY_COPY.md)
and `.analysis/runtime-memory-copy-20261014/verification.json`. Raster cleanup
fragments are already inside parent extents and must not be counted twice.
One closed two-record REA session; no runtime/game checks.

Sixteen compiler-generated list initializer stages are now registered as exact,
376 complete bytes from the unchanged current source/product. Source448/exact333/
code69,468; authored270 and origins270/200/45/28 remain unchanged. Explicit
source_generator records bind real global declarations, accepted constructors
and inner stages; no wrapper source or storage is added. All42 existing owner
exacts re-compared unchanged; all317 prior exacts/106 candidates/249 semantic
rows preserved. See [generated list exacts](../research/exact/LIST_GENERATED_EXACT.md)
and `.analysis/list-generated-exact-20261014/verification.json`. No compilation,
provider or game/runtime execution repeated. Embedded board-storage pair and
whole startup graph remain unclaimed.

Physical FDIV detection now supplies the full79-byte exact body. Volatile
operands retain hardware division; the consumed24-byte dividend/divisor/residual
record removes eight scalar-local address differences. Source432/exact317/
code69,092; all316 old exacts/106 candidates unchanged. See
[physical FDIV](../research/exact/RUNTIME_FDIV_PHYSICAL.md) and
`.analysis/runtime-fdiv-physical-20261014/verification.json`. The eight-record
REA session closed successfully. Three member-call attempts are rejected:
explicit thiscall is reserved in VC4; member-pointer interfaces are not the
original raw-address ABI. Unique rejected trials are retained, no bridge
source/acceptance is added. No hardware, affinity, runtime or game execution.

Memory fill adds real alignment/word/tail source,177/88 bytes with176 differences.
Original REP STOSD remains nonexact; no assembly/intrinsic forcing. Source431,
candidates106; all316 old exacts/105 candidates unchanged. See
[memory fill](../research/exact/RUNTIME_MEMORY_FILL.md). The two REA queries
completed; close reported cleanup_incomplete, but owned wrapper/provider PIDs
are confirmed gone. Retained temporary resources are not removed. No runtime/game tests.

Pow special handling adds a full584-byte source body with eight differences,
down from567/140. Preserve unordered carry branches and binary64 result/word
transport; alias stores584/32 are rejected. Source430, candidates105;
all316 old exacts/104 candidates unchanged. See
[pow special values](../research/exact/RUNTIME_POW_SPECIAL.md) and
`.analysis/runtime-pow-special-20261014/verification.json`. No runtime/game tests.

The full10-byte CRT absolute-value body is exact under its signed representable-
result contract. Source429/exact316/code69,013; all315 old exacts/104 candidates
remain unchanged. See [absolute value](../research/exact/RUNTIME_ABSOLUTE.md)
and `.analysis/runtime-absolute-20261014/verification.json`. No runtime/game tests.

Bounded string copy/append now have maintained source:58/36 bytes with56
differences and69/49 with68 differences. Their handwritten string-instruction
bodies remain candidates; exact315/code69,003 is unchanged, candidates104.
All315 old exacts/102 candidates are preserved. See
[bounded strings](../research/exact/RUNTIME_STRING_COPY.md).

Multiprocessing FDIV testing adds a full278-byte exact and all89 literal bytes.
Separating process-handle acquisition removes the initial twelve preparation
differences. Preserve32-position system-mask scanning, ignored affinity failures,
system-mask restoration and retained module reference. Source426/exact315/code69,003;
all314 preceding exacts/102 candidates are preserved. See
[FDIV processors](../research/exact/RUNTIME_FDIV_PROCESSORS.md) and
`.analysis/runtime-fdiv-processors-20261014/verification.json`. One empty provider
session and one two-record session are closed; no CPU/runtime/game tests.
The actual physical x87 test and game integration remain open.

Filter lifetime adds installer30 and forwarding initializer5 as full exacts,
plus the complete4-byte CRT$XCC pointer record. Restoration registration precedes
installation; its return is ignored and the prior OS filter is saved. Two newly
proved compiler-generated entries bring inventory543/source425/exact314/code68,725,
origins270/200/45/28. All312 preceding exacts/102 candidates are preserved.
See [filter lifetime](../research/exact/RUNTIME_FILTER_LIFETIME.md) and
`.analysis/runtime-filter-lifetime-20261014/verification.json`. One closed three-record
REA run; no runtime/game tests. Original linker placement/startup execution remain
open; the explicit typed record does not claim that integration.

Stream position and C++ filtering add three bodies and two full exacts across101
bytes (filter88/restoration13). Ftell413/432/360 remains a candidate. Restoration
is a newly proved entry; inventory541/source423/exact312/code68,690, candidates102
(34 authored/68 runtime), origins270/200/43/28. All310 old exacts/101 candidates
are preserved. The4-byte saved-filter BSS lies in the PE zero-filled virtual
tail; the failed file-backed state consumer is corrected without recompiling.
See [position/filter](../research/exact/RUNTIME_POSITION_FILTER.md) and
`.analysis/runtime-position-filter-20261014/verification.json`. One closed five-record
REA run; no runtime/game tests. Filter installation and integration remain open.

The full x87 bridge now supplies288 bytes of maintained source:255 code plus33
alignment/switch bytes previously omitted from its boundary. Original15
relocations and all switch bytes are covered. DWORD transport improves292/234
to288/14; a22-difference write-phase trial is reverted. Final source matches the
retained14-difference producer. No new exact: source420/exact310/code68,589,
candidates101 (34 authored/67 runtime), origins270/197/43/30. All310 preceding
exacts/100 candidates are preserved. See [bridge](../research/exact/RUNTIME_X87_BRIDGE.md)
and `.analysis/runtime-x87-bridge-20261014/verification.json`. One closed three-record
REA run; no runtime/game tests. Physical control and integration remain open.

File access checking adds a full77-byte exact with all five actual relocations.
The SDK confirms int mode; genuine attribute/error APIs and errno13/doserrno5
writes are preserved. Source419/exact310/code68,589; all309 preceding exacts and
100 candidates remain unchanged. See [access](../research/exact/RUNTIME_ACCESS.md)
and `.analysis/runtime-access-20261014/verification.json`. One closed six-record
REA run includes four exploratory string records; no runtime/game tests.

Complete C++ FindHandler659 now has maintained source663/659/605. It preserves
rethrow substitution, actual ValidateRead length1, inline name/qualifier tests,
all handler/type scans and recursive destruction/foreign termination. The
single-record-view trial reduces initial671/616 to663/605; no new exact claim.
All309 preceding exacts/99 candidates remain unchanged. Current source418 and
candidates100 (34 authored/66 runtime), origins270/196/43/31. See
[handler search](../research/exact/RUNTIME_CPP_HANDLER.md) and
`.analysis/runtime-cpp-handler-20261014/verification.json`. One closed two-record
REA run; no runtime/game tests. Catch-object SEH and integration remain open.

C++ frame dispatch and rethrow recognition add two full exacts across232 bytes
(188/44), plus the catch-transfer147/148/90 candidate. A dedicated exception
record owner keeps the preceding table inputs unchanged; the initial shared
header expansion's range regression is rejected. All307 old exacts/98 candidates
are preserved. Current source417/exact309/code68,512, inventory540 and
candidates99 (34 authored/65 runtime); origins270/195/43/32. See
[transfer](../research/exact/RUNTIME_CPP_TRANSFER.md) and
`.analysis/runtime-cpp-transfer-20261014/verification.json`. One closed five-record
REA session; no runtime/game tests. Genuine structured unwinding and integration
remain open.

C++ exception tables add four bodies and three complete exacts across214 bytes:
pointer adjustment33, range159 and unwind filter22. Foreign213/213/70 remains
a candidate. The newly proved filter brings inventory539; source414/exact307,
code68,280 and candidates98 (34 authored/64 runtime). All304 preceding exacts
and97 candidates are preserved. Native-width metadata, PMD displacements and
real pre-table state reads are restored without fabricated sentinel storage.
See [C++ tables](../research/exact/RUNTIME_CPP_TABLES.md) and
`.analysis/runtime-cpp-tables-20261014/verification.json`. Two closed REA runs,
seven records; no runtime/game tests. Exception transfer/integration remains open.

FP dispatch now supplies both complete raising/handling bodies and all40
initialized util constants. Raise880/876/328 and handle708/704/436 remain
candidates; no new exact claim. Raising's full876-byte extent includes18 bytes
past its imported code prefix. Real raw-word/bitfield views preserve IEEE88
layout and the original precision-writeback mask. All304 old exacts/95 candidates
are preserved; current candidates97 (34 authored/63 runtime). See
[dispatch](../research/exact/RUNTIME_FP_DISPATCH.md) and
`.analysis/runtime-fp-dispatch-20261014/verification.json`. One closed five-record
REA run; no runtime/game tests. Physical x87 helpers and integration remain open.

FP decomposition/exception recovery adds six bodies and two full exacts across
266 bytes: exception entry187 and quiet-NaN entry79. The88-byte IEEE record uses
the real operand2-valid bitfield. Callback names are now writable; all350 logical
catalog bytes match. The default matherr owner restores its9876 marker4. All302
preceding exacts are preserved, including15 fresh shared-owner replays. Of six
recompiled old candidates, only converter459 changes94 to95 differences.
Current candidates95 (34 authored/61 runtime), origins270/189/43/36. See
[decomposition/exceptions](../research/exact/RUNTIME_FP_DECOMPOSITION.md) and
`.analysis/runtime-fp-decomposition-20261014/verification.json`. One closed17-record
REA session; no runtime/game tests. Physical rounding/control/exception boundaries
and integration remain open.

FP control/classification adds eight source bodies and six complete exacts across
517 bytes: translations161/141, control24, errno42, error priority50 and special
type99. Name lookup38/5 and exponent editing57/22 remain candidates. All27 name
records/216 bytes and134 literal bytes match; native pointers remain natural.
All296 preceding exacts and89 candidates are preserved. Current candidates91
(34 authored/57 runtime), origins270/186/43/39. See
[FP control](../research/exact/RUNTIME_FP_CONTROL.md) and
`.analysis/runtime-fp-control-20261014/verification.json`. One closed18-query REA
session; no runtime/game tests. Physical x87 control and integration remain open.

Float rendering/output adds eight source bodies and six full exacts across654
bytes: fixed251, general176, mode wrappers43/38, shift43 and output103. Exponent
310/2 and binary64 conversion185/187/75 remain candidates. E/F return signatures
are corrected without losing any preceding290 exacts or87 candidates. Current
candidates89 (34 authored/55 runtime), origins270/185/43/40. See
[rendering](../research/exact/RUNTIME_FLOAT_RENDER.md) and
`.analysis/runtime-float-render-20261014/verification.json`. No runtime/game tests;
physical integration remains open.

Float formatting adds eight source bodies and five complete exacts across280
bytes: callback initialization56, dispatch101, zero cropping89, positive23 and
unavailable support11. Six newly proved boundaries bring inventory to538.
All285 preceding exacts and84 candidates are preserved; candidates87
(34 authored/53 runtime), origins270/178/43/47. Full24-byte callback defaults and
six relocations match. See [float formatting](../research/exact/RUNTIME_FLOAT_FORMAT.md)
and `.analysis/runtime-float-format-20261014/verification.json`. No runtime/game
tests; remaining E/F/G formatter bodies and integration are open.

Runtime/FP initialization adds four full source bodies and the complete28-byte
initialized state. Controller48, precision19 and thread noop1 are exact across68
bytes. The true noop entry4175A0, absent from Ghidra's inventory, extends it to532
through full CRT/actual callback-slot/REA-byte/decode proof. Math25/23/5 remains
nonexact: the original final FNCLEX, omitted by pseudocode, is retained through a
real clear API boundary; unsupported intrinsic forcing is removed. Source378/
exact285/66,349 code bytes; candidates84 (34 authored/50 runtime), origins270/
171/43/48. All282 preceding exacts and83 candidates retain inputs/products/results.
See [initialization](../research/exact/RUNTIME_INITIALIZATION.md) and
`.analysis/runtime-initialization-20261014/verification.json`. One closed11-record
REA session; no runtime tests/game builds. Actual linker initializer storage,
conversion/FDIV/hardware boundaries and integration remain open.

Argument/environment recovery adds four full bodies. Environment setup219 is
exact; setup151/155/116, parsing475/466/280 and acquisition389/411/404 remain
candidates. Separate native-width globals follow proven external ownership;
quoted DBCS counting asymmetry and all original stores are retained. Cached OS
acquisition has an original uninitialized-stack read and remains unproved.
Source374/exact282/66,281 code bytes; candidates83 (34 authored/49 runtime),
origins270/168/43/50. Four code-page exacts227 and its candidate are recompiled
unchanged after the shared unsigned locale declaration correction; other277
exacts/79 candidates are reused. See [startup arguments](../research/exact/RUNTIME_ARGUMENTS.md)
and `.analysis/runtime-arguments-20261014/verification.json`. One closed12-record
REA run and whole CRT sections ground the source. No runtime tests/game builds;
startup/OS/game integration and native semantic acceptance remain open.

Code-page recovery adds five full bodies and525 logical initialized bytes.
System selection77, locale mapping95, single-byte reset44 and startup11 are
exact across227 bytes. Mapping includes39 dispatch bytes beyond its imported
56-byte prefix. Setter473/475/128 remains a candidate; its final case copy is
the instruction-scheduling gap. Source370/exact281/66,062 code bytes; candidates
80 (34 authored/46 runtime), origins270/165/43/53. All277 preceding exacts and79
candidates preserve their inputs/products/results. See [code pages](../research/exact/RUNTIME_CODEPAGE.md)
and `.analysis/runtime-codepage-20261014/verification.json`. One closed15-record
REA run and whole CRT sections ground the source; no runtime tests/game builds.
Shared classification storage is now source-owned; OS/game integration remains open.

Decimal output and multibyte recovery adds three full source bodies. Lead-byte
classification18 is exact; its private classifier58/7 and decimal output922/923/
535 remain candidates. Original80-bit argument,26-byte result, full special-value
strings and guard-digit/rounding lifetimes are restored without before-object
pointers. Source365/exact277/65,835 code bytes; candidates79 (34 authored/45
runtime), origins270/162/43/56. All276 preceding exacts and77 candidates preserve
their inputs/products/results. See [decimal output](../research/exact/RUNTIME_DECIMAL_OUTPUT.md)
and `.analysis/runtime-decimal-output-20261014/verification.json`. Retained REA
evidence and full pinned CRT sections are reused; no new provider, runtime tests
or game builds. Classification register allocation, decimal scheduling and
shared storage/integration remain open.

Signal/exception recovery adds four complete bodies and initialized state140.
Both lookup bodies49/47 are exact; raise includes all53 switch bytes beyond its
old340-byte prefix. Raise393/323 and filtering376/351/355 remain nonexact.
Two verified entries absent from Ghidra's inventory extend it to531: filter
0x41BD60/351 and lookup0x41BEC0/47. Full REA byte ranges and complete pinned CRT
sections agree; local decoding supplements unavailable provider procedures.
Hardware-context scopes preserve typed callbacks and all restoration order.
Source362/exact276/65,817 code bytes; candidates77 (34 authored/43 runtime),
origins270/161/43/57. All274 preceding exacts and75 candidates preserve their
inputs/products/results. See [signal dispatch](../research/exact/RUNTIME_SIGNALS.md)
and `.analysis/runtime-signals-20261014/verification.json`. Registration and
physical OS/exception/game integration remain open; no runtime tests/game builds.

Error-control recovery adds MessageBox, three validators and abort source.
Read/write/code checks32/32/27 and full abort31 are exact across122 bytes; the
imported abort27-byte boundary is corrected. MessageBox improves152/121 to146/90
and remains nonexact with all58 literal bytes checked. C++ validation ABI and
local static callback ownership follow pinned symbols. Source358/exact274/
65,721 code bytes; candidates75 (34 authored/41 runtime), origins270/158/43/58.
All270 old exacts and74 candidates retain their producer inputs/products/results.
See [error controls](../research/exact/RUNTIME_ERROR_CONTROL.md) and
`.analysis/runtime-error-control-20261014/verification.json`. Signal source and
physical UI/exception/game integration remain open; no runtime tests/game builds.

Low-I/O startup/fatal recovery adds four full bodies and the complete17-row
error catalog. Fatal42 and banner61 are exact; the old fatal38-byte extent is
corrected through its trailing cleanup/return. Packed inherited metadata restores
the startup68-byte frame; initialization468/467/304 and formatting493/494/419
remain nonexact. Source353/exact270/65,599 code bytes; candidates74 (34 authored/
40 runtime), origins270/156/43/60. All268 old exacts and72 candidates preserve
their producer inputs/products/results. See [startup/fatal recovery](../research/exact/RUNTIME_LOWIO_STARTUP.md)
and `.analysis/runtime-lowio-startup-20261014/verification.json`. Message-box
backend, original formatting frame and OS/game integration remain open.
No runtime tests or game builds run.

The locale-backend follow-up restores both mapping/classification paths and
their private bounded counter. Character-type conversion291 is exact with all
bindings and both complete probe constants. Mapping565/555/280 and counting44/15
remain candidates. The original private-cache mangling establishes C++ local
statics; real maintained C allocator linkage is explicit. Source349/exact268/
65,496 code bytes; candidates72 (34 authored/38 runtime), origins270/152/43/64.
All267 preceding exacts and70 candidates retain their producer inputs/products.
See [locale backends](../research/exact/RUNTIME_LOCALE_BACKENDS.md) and
`.analysis/runtime-locale-backends-20261014/verification.json`. OS/runtime
integration remains open. No runtime tests or game builds run.

The October14 continuation restores both full229-byte case converters and the
145-byte classification dependency. Both converters are exact across458 bytes;
classification retains17 differences. Source346/exact267/65,205 code bytes;
candidates70 (34 authored/36 runtime), origins270/150/43/66. All265 previous
exact results and69 candidates preserve their producer inputs and products.
See [case conversion](../research/exact/RUNTIME_CASE_CONVERSION.md) and
`.analysis/runtime-case-conversion-20261014/verification.json`. Locale storage
and mapping backends remain open. No runtime tests or game builds run.

The October 13 continuation recovers two 53-byte CRT conversion wrappers and
the 3-byte default math callback in `src/runtime_float.c`. All 109 bytes and
four actual relocations match. This standalone module compiles on native,
i686 and VC4; parser recovery and backend/game integration remain
open. The game still uses its existing runtime. See
[the source note](../research/exact/RUNTIME_FLOAT_CONVERSIONS.md) and
`.analysis/runtime-conversion-functions-20261013/`. No runtime tests run.
The 34 authored candidates and previous game products are unchanged.

The follow-up recovers both complete 24-byte binary format entries and their
48 initialized data bytes. The full converter body is now maintained at the
original 459 bytes / 157 instructions, with 94 differences. Its packed result
reuses the exponent scalar; its denormal shift is stored before the copy.
It is the additional runtime candidate, bringing configured candidates to 35.
See [binary conversion](../research/exact/RUNTIME_BINARY_CONVERSION.md) and
`.analysis/runtime-binary-conversion-20261013/`. Five owner functions retain
157 exact code bytes; 239 other exact producers are unchanged.

The mantissa continuation adds all seven helpers and their addition dependency.
Tail testing (100 bytes), carry propagation (99) and clearing (15) are complete exacts.
All eight affected exacts preserve 371 bytes; 239 other producers are unchanged.
There are now 40 candidates: 34 authored and six runtime. The converter has
459 bytes / 95 differences in this source context. Rounding has 163/172 bytes,
copying has five differences, zero testing six, shifting 174/173 bytes and
addition seven differences. These remain nonexact. Decimal parsing is the remaining source dependency
of this conversion chain. See
[mantissa helpers](../research/exact/RUNTIME_MANTISSA_HELPERS.md) and
`.analysis/runtime-mantissa-helpers-20261013/`.

The next continuation makes indexed zero testing (29 bytes) and little-endian
96-bit addition (102) exact. Both one-bit shifts now have maintained source.
Ten affected exacts preserve 502 bytes; 239 other producers are unchanged.
Current candidates total 41: 34 authored and seven runtime. The converter has
94 differences, the big-endian shift has 172/173 bytes with 134 differences,
scalar addition has five differences, and the new left/right shifts have
50/62 and 48/54 bytes with 47 and 35 differences. Rounding and copy are unchanged.
See [iteration and arithmetic](../research/exact/RUNTIME_MANTISSA_LIFETIMES.md)
and `.analysis/runtime-mantissa-lifetimes-20261013/`. Runtime tests remain deferred.

Decimal parsing and its three arithmetic dependencies now have maintained
source, together with all 58 power records. Exact totals are unchanged; all
249 unit results and 41 preceding candidates are preserved. Four new candidates
bring the total to 45: 34 authored and 11 runtime. Numeric digits are 232/232
bytes with 21 differences; the complete parser/table carrier is 1851/1871 with
1661 differences, multiplication 708/678 with 666 and scaling 133/123 with 127.
The original parser owns 293 table/alignment bytes beyond its decoded body.
See [decimal conversion](../research/exact/RUNTIME_DECIMAL_CONVERSION.md) and
`.analysis/runtime-decimal-conversion-20261013/`. Locale dependencies and
game integration remain open; no runtime tests or game builds run.

The latest continuation restores descriptor modes, realloc and heap-size source.
Heap size is complete exact across21 bytes and both actual bindings. All249
preceding exact results are unchanged; the three source bodies bring presence
to309 and exacts to250/63,718. Numeric digits improve to20 differences; descriptor
modes have128/128 bytes with2 differences and realloc106/111 with15. Current
candidates total47:34 authored and13 runtime. The intervening47-byte chkstk is
verified as a special-ABI compiler dependency, not an invented C unit. Origins
are270 authored/122 runtime/43 compiler-generated/93 unknown. See
[modes and resizing](../research/exact/RUNTIME_FILE_MODES.md) and
`.analysis/runtime-digit-core-20261013/verification.json`. Native/i686 standalone
compilation covers the three changed owners. No runtime tests or game builds run.

The stream continuation restores six CRT buffer/flush bodies. Retirement57,
fflush76 and the previously unlisted flushall11 entry are complete exacts across
144 bytes and five actual bindings. All250 preceding exacts and47 candidates
are unchanged. Source presence315 and exacts253/63,862 are current. The full
traversal improves109/107/83 to107/107/13 by following shared table ownership;
acquisition75/75/23 and buffer flushing100/100/12 remain scheduling candidates.
There are50 candidates:34 authored and16 runtime. The new11-byte boundary is
grounded by complete pinned CRT code and a full REA read; Ghidra has no procedure
at the entry. Inventory529 and origins270/127/43/89 are current. See
[stream buffering](../research/exact/RUNTIME_STREAM_BUFFERS.md) and
`.analysis/runtime-stream-buffers-20261013/verification.json`. Lower-I/O
write/commit and registry/counter storage remain open. No runtime tests or game builds run.

The low-I/O continuation restores write555, seek188, commit111, handle lookup67
and error mapping102 source, plus the complete45-record/360-byte private error
table. Lookup and mapper are exact across169 bytes and12 bindings. All253
preceding exact results and50 candidates are unchanged; source320 and
exacts255/64,031 are current. Write improves563/288 to555/37 with a shared OS
failure path and consumed cache/progress record. Seek188/15 and commit110/111/65
remain candidates; the pinned io.h signatures are retained. The original ST
CRT profile is `/ML`, preserving direct global errno rather than an accessor.
File-mode source/header now expose the proven native-width handle and flags;
its128-byte/two-difference result is preserved with a refreshed producer. Origins
are270/131/43/85; candidates53:34 authored and19 runtime. See
[low-I/O writing](../research/exact/RUNTIME_LOWIO_WRITE.md) and
`.analysis/runtime-lowio-write-20261013/verification.json`. No runtime tests or
game builds run; low-I/O registry/error storage and game integration remain open.

The next write continuation separates OS outcome and cache/progress records.
All five scalar homes and the translation buffer now match; the complete555-byte
writer improves37→19 differences. Input/output/inserted-count register rotation
remains. Consuming text cursor scopes do not change emission. All255 exact
results and52 other candidates are preserved; totals remain320/255/64,031.
See [the source note](../research/exact/RUNTIME_LOWIO_WRITE.md) and
`.analysis/runtime-write-lifetimes-20261013/verification.json`. Two VC4 trials,
five complete final comparisons and native/i686 standalone compilation cover
the changed owner; no runtime tests, game builds or new REA session run.

Read/close recovery now supplies four more complete source bodies and the
observed lookahead byte. Console switch/common-zero-error dispatch restores
close199/14, handle invalidation144/12 and installation163/13. The full reader
is605/611/463 after transferred-count/end/error-phase recovery. None is exact;
all255 accepted results and53 preceding candidate results remain unchanged.
Source presence324 and candidates57:34 authored/23 runtime are current; origins
270/135/43/81. See [read/close](../research/exact/RUNTIME_LOWIO_READ_CLOSE.md) and
`.analysis/runtime-lowio-read-close-20261013/verification.json`. One closed
twelve-record REA session and complete pinned CRT sections ground all four.
All three header-consuming owners compile natively/i686 and their ten complete
units compare; the two affected exacts retain169 bytes and table360. No runtime
tests or game builds run. Registry/application/error storage and integration remain open.

Stream transfer recovery adds six complete bodies and exact fclose112/isatty42
with all six actual bindings. Source330/exact257/64,185 are current. Slot
acquisition improves48→2 and remains nonexact. Terminal flags become exact in
the corrected final shared header context, which also avoids MinGW errno macros.
Bulk read324/326/218, input refill251/240/238 and output refill288/328/311 are
complete candidates. All255 preceding exacts and57 candidates are unchanged;
current candidates61:34 authored/27 runtime, origins270/141/43/75. See
[stream transfer](../research/exact/RUNTIME_STREAM_TRANSFER.md) and
`.analysis/runtime-stream-transfer-20261013/verification.json`. The closed REA
run retains18 records; six whole pinned CRT sections establish the original
boundaries. Only native/i686 standalone compilation and full unit comparisons
run; no runtime tests or game builds. Shared registry/storage and integration
remain open; conditional-arm/minimum/loop spelling and grouped read state
trials are closed, not new exacts.

Opening recovery adds five bodies, including both exact stream wrappers37/21
and all three call bindings. Source335/exact259/64,243 are current. Base-mode
parsing lifetime improves the full526-byte parser372→49 differences; security
inheritance and installed-record publication restore the full1053-byte opener
and reduce934→15→2. Allocation184/37 remains a third candidate. Original
parser/opener extents now include their115/72 additional alignment/switch bytes;
all tables and actual relocations are included, not omitted. All257 preceding
exacts and61 candidates are unchanged; current candidates64:34 authored/30
runtime, origins270/146/43/70. See [file opening](../research/exact/RUNTIME_STREAM_OPEN.md)
and `.analysis/runtime-stream-open-20261013/verification.json`. One closed15-record
REA run and complete pinned CRT sections ground all five. Only standalone
native/i686 compilation and whole comparisons run; no runtime tests/game builds.
The opener's two temporary-register differences, parser49 and allocation37
remain open. `_chsize` is the next missing direct dependency; registry/default
storage and integration are still open. Consumed flags-result and publication
without the local flag phase are closed worse trials, not retained.

Length changes, calloc and fcloseall now add three complete source bodies.
Chsize359 is exact across18 bindings and its4100-byte frame. Full intrinsic
zeroing and a common seek-failure exit restore376/284→359/0; mode/position
restoration and original error distinctions are retained. Calloc77/82/16 and
fcloseall115/19 remain candidates. Source338/exact260/64,602 are current;
candidates66:34 authored/32 runtime, origins270/148/43/68. The old msize21 and
realloc106/111/15 are recompiled and preserved, with preceding inputs/products
frozen under `.analysis/runtime-file-size-20261013/before/`. Other258 exacts
and63 candidates are unchanged. See [file sizing](../research/exact/RUNTIME_FILE_SIZE.md)
and `.analysis/runtime-file-size-20261013/verification.json`. One closed nine-record
REA run and three whole pinned CRT sections ground the new bodies; five final
comparisons and native/i686 compilation cover both changed owners. No runtime
tests or game builds. Opener header consolidation worsens2→42 and is reverted;
loop-carried calloc heap/result worsens77/16→85/64 and is not retained.
Shared registry/default storage and integration remain open.

Exit registration now adds two complete source bodies. Atexit19 and unchanged
normal/quick exit wrappers18/18 are exact across55 bytes and three bindings.
Onexit121/2 and the unchanged initializer walker32/6 remain candidates.
Registration keeps the int-returning API, explicit legacy result-discarded slot
conversion, four-slot growth, post-callback shared-bound reloads and publication
order. Source340/exact263/64,657 are current; candidates68:34 authored/34 runtime.
Origins remain270/148/43/68. See [exit registration](../research/exact/RUNTIME_ONEXIT.md)
and `.analysis/runtime-onexit-20261013/verification.json`. Six new closed REA
records and retained termination dossiers ground five complete comparisons;
all five pinned CRT sections match. Existing termination source/header and
semantic inputs are unchanged, as are all260 prior exact and66 candidate
producers/results. Native/i686 standalone compilation covers both owners;
no runtime tests/game builds. The common append guard leaves two differences
and is closed. The controller's portable platform bridge, initialized callback
storage, physical exit and full teardown/game integration remain open.

Integer text recovery adds all three bodies. Itoa60 and ultoa30 are exact
across90 bytes/three call bindings; static xtoa96/2 remains nonexact. The
first pointer translation matches186 bytes but forms a before-array cursor
after a single-character swap. The retained address-cursor source avoids that
operation while preserving96 bytes and all writes; two comparison-direction
bytes remain. Unsigned negation supports INT_MIN; sign is decimal-only, and
the original two divisions and mandatory reversal are retained. Source343/
exact265/64,747, candidates69:34 authored/35 runtime, origins270/149/43/67
are current. See [integer text](../research/exact/RUNTIME_INTEGER_TEXT.md) and
`.analysis/runtime-integer-text-20261013/verification.json`. Old helper/unsigned
REA dossiers are reused; only itoa needs a closed three-record query. All three
pinned CRT sections match. Three final comparisons and native/i686 standalone
compilation cover the owner; all263 old exacts/68 candidates are unchanged.
No runtime tests/game builds. The unsafe first-pass match is not accepted;
runtime integration remains open and the score owner keeps its prior boundary.

Repository: `/home/pentester/coding/codex_ida/dx-ball-reconstruction/dx-ball`.
Branch and publish target: `origin/main`.
Latest published source checkpoint before this continuation: `26de2c1`
(exact filter lifetime entries and initialized record).
Latest pre-handoff checkpoint: `5834536` (closed device/clock controls).
Both were pushed; remote HEAD and a clean worktree were independently verified.

Original: English `DXBALL.EXE` v1.07, 158,208 bytes, SHA-256:
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
The verified game archive contains 51 files and no source, PDB, objects or map.
Native, MinGW i686 and VC4 products build at the current source checkpoint.
VC4 compiler is 10.00.5270; linker is 3.00.5270.

Current comparison and producer authorities:

- `config/match-units.toml`: exact recipes, complete extents and bindings.
- `build/reports/exact-replay.json`: all 334 exact closures and current producers.
- `.analysis/exact-candidate-audit-20261012/comparison.json`: current 108 candidates;
  its directory name is historical, its contents are current.
- `config/functions.csv`, `implemented.csv`, `matches.csv`, `semantic-acceptance.csv`
  and `source-owners.toml`: source, status, ownership and scoped evidence.
- `.analysis/runtime-fdiv-processors-20261014/verification.json`: current
  standalone source/producer/ledger seal.
- `.analysis/runtime-filter-lifetime-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-position-filter-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-x87-bridge-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-access-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-cpp-handler-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-cpp-transfer-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-cpp-tables-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-fp-dispatch-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-fp-decomposition-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-fp-control-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-float-render-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-float-format-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-initialization-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-arguments-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-codepage-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-decimal-output-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-signals-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-error-control-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-lowio-startup-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-locale-backends-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-case-conversion-20261014/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-integer-text-20261013/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-onexit-20261013/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-file-size-20261013/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-stream-open-20261013/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-stream-transfer-20261013/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-lowio-read-close-20261013/verification.json`: preceding
  standalone source/producer/ledger seal.
- `.analysis/runtime-write-lifetimes-20261013/verification.json`: preceding
  write lifetime scope; affected inputs/products are frozen in the new `before/`.
- `.analysis/runtime-lowio-write-20261013/verification.json`: preceding
  low-I/O source scope; affected sources/products are frozen in the new `before/`.
- `.analysis/runtime-stream-buffers-20261013/verification.json`: preceding
  stream buffering scope; its sources/products are unchanged.
- `.analysis/runtime-digit-core-20261013/verification.json`: preceding
  modes/resizing source scope; file-mode inputs/product are frozen in the new `before/`.
- `.analysis/runtime-decimal-conversion-20261013/verification.json`: preceding
  decimal source scope; affected arithmetic inputs/products are frozen in the new `before/`.
- `.analysis/runtime-mantissa-lifetimes-20261013/verification.json`: preceding
  iteration/arithmetic scope; source and products are frozen in the new `before/`.
- `.analysis/runtime-mantissa-helpers-20261013/verification.json`: preceding
  helper checkpoint; its sources and products are frozen in the new `before/`.
- `.analysis/runtime-binary-conversion-20261013/verification.json`: preceding
  binary format/converter scope; sources are retained in the new `before/`.
- `.analysis/runtime-conversion-functions-20261013/verification.json`: preceding
  three-function scope; frozen sources are retained in the new phase's `before/`.
- `.analysis/rebound-contact-integration-20261013/verification.json` and
  `independent-review.json`: preceding unchanged game input/product seal.

## Latest recovery and closed boundaries

[Paddle contact precision](../research/exact/EXACT_REBOUND_STORED_CONTACT.md)
is now complete: 681 bytes, 181 instructions, a 28-byte frame and 50 bindings.
`src/balls.cpp` reuses one float contact value. The first comparison consumes
its immediate x87 quotient; six later cv-qualified reads consume the stored
float. Three companions retain 965 exact bytes.

GNU compiles this file with source-specific C++17, `-O2`, `-mfpmath=387`,
`-fexcess-precision=fast` and `-Wno-sequence-point`; keep these settings and its
C API linkage. The VC4
recipe is unchanged. A private native producer passes 831 existing ball cases
and four audio callback controls. Its runtime sections, relocation/symbol tables
and 36 other linked objects equal the canonical build, supporting explicit
reuse of that evidence. Two canonical witnesses also pass: 7/100 selects 150°,
12/60 selects 120°. Do not report the 831 cases as rerun on the canonical library.

[Sprite iteration lifetime](../research/exact/BANK_SPRITE_ITERATION_SCOPE.md)
reduces the 1,475-byte bank loader from 72 to 70 differences. Its two removed
positions do not prove matching scalar homes. Fifteen resource exacts preserve
3,572 bytes. [Device calls](../research/exact/DEVICE_SURFACE_PALETTE_CALLS.md)
reduce palette transition to 12 differences while preserving five exacts.

Read [closed diagnostics](../research/exact/CLOSED_STORAGE_DIAGNOSTICS.md)
before choosing another model. In particular:

- Device-local CreatePalette projection: one 14-input compile, six comparisons;
  five exacts retain 808 bytes, transition worsens 12→18. Rejected.
- Current clock-owner SDK sample: one 27-input compile, 16 comparisons; all code
  hashes unchanged, eleven exacts retain 2,708 bytes. Named Kernel32 IAT bindings
  are verified. No native union-lifetime acceptance or exact gain. Kept private.
- Paddle consumed records restore all source homes but add two bytes. Overlay
  lifetime, height projection records, palette declaration order, equivalent
  operand spellings, shared SDK contexts and list-member families have receipts.
  Reopen a model only with new evidence, not a new name or blind permutation.
- Preserve `DxBallBoardStorage` and its terminal board-copy effects. Interior
  linker aliases, cast/offset spelling trials and guessed padding are not a fix.
- Original score/intro buffer gaps do not establish larger arrays. Do not enlarge
  the 11-byte score buffer or 32/11 intro arrays to fill unexplained frame space.

Runtime and compiler-generated entries also retain separate origin records.
[CRT storage closure](../research/CRT_INITIALIZED_STORAGE_CLOSURE.md) and
[FDIV initialization](../research/CRT_FDIV_INITIALIZATION_FRONTIER.md) cover
89 complete code sections, 20 data sections and seven initialized objects.
Unresolved BSS and FP initialization remain open. Preserve unique placement,
namespace and verifier gates when investigating that frontier.

Latest private controls: `.analysis/device-ddraw-local-interface-20261013/` and
`.analysis/kernel-sample-current-owner-20261013/`. Complete source, SDK, binding
and independent reviews are retained. Their eight compressed carriers release
1,077,248 allocated bytes; canonical products remain unchanged.

## Resource and tool use

- Run Python through `scripts/repo-python`. Use project entry points rather than
  bypassing their resource limits.
- Use one already-allowed CPU via `resource_limits.limit_cpu()`. Build with
  CMake `--parallel 1`. Ghidra heap is **512 MiB**, set through the supported
  `GHIDRA_HEADLESS_MAXMEM=512M` path in `scripts/resource_limits.py`.
- Keep one writable compiler/provider/Wine session at a time using
  `legacy_toolchain.session_lock()`. It is a blocking, non-reentrant lock;
  do not wrap a helper that already acquires it in another lock.
- Automated game/audio probes use `PULSE_SINK=dxball_reconstruction_silent`.
  For native interposition, prepare the interposer before taking the session lock.
- Keep local REA updated. The verified project pin is **REA 6.4.0 / Ghidra 12.1.4**,
  and the installed REA skill is version 37. Use `scripts/rea`, check the relevant
  pin/version when resuming, and avoid repeated setup or unrelated tool upgrades.
- Reuse retained dossiers first. Save full responses and Evidence IDs under
  `.analysis/rea/`, but read small relevant facets into context. Prefer summaries,
  retained references and bounded output; do not dump giant manifests/dossiers.
- Compile once per stable source family. Reuse a completed producer only after
  checking actual inputs, flags and product hashes. Fix comparison consumers
  without rerunning their compiler or REA producer.
- A truncated preview or observation timeout is not producer failure. Retain and
  poll the live handle, or inspect terminal receipts, before deciding to restart.
- Run the minimum useful affected existing check. Do not replay the full historical
  queue or repeat unchanged successful cases. Label reused evidence explicitly.

REA feedback is optional and secondary to reconstruction. Append performance
and usability observations to the **single existing** file
`/tmp/dxball_rea_feedback_20261010.md` (latest entry 77). Record oversized output,
token/context cost, latency and usability issues when actually observed. Do not
create another feedback document, and do not spend the main task on feedback.

## Source fidelity, evidence and cleanup

Use natural typed source shared by portable and legacy builds. Preserve widths,
ABI, data ownership, actual stores and call order. Do not force matches through
copied machine code, assembly, padding, fake locals, alternate source bodies or
blind name/declaration/capacity/layout searches.

An exact claim covers the complete function, every actual relocation, full
literal contents and attached metadata. Verify all accepted units sharing the
changed inputs. Keep the real producer path and hashes; a byte-equivalent reuse
is not a fresh canonical compilation. Preserve historical scopes and case counts
when refreshing their input inventories.

Keep `original/`, `.tools/`, `build/`, `.analysis/` and `ghidra-project/` private.
Publish source, useful research notes and ledgers. Clean trial products regularly:
retain unique evidence and accepted/current products, verify gzip decompression
SHA-256 before removing raw carriers, and record allocated savings net of receipt
cost. Many historical files now have `.gz` fallbacks; read or safely extract the
retained carrier instead of rerunning the producer. Keep archive/current inode
independence, and avoid recursively copying large evidence trees or tool caches.
`scripts/repo-python scripts/clean-local.py` previews its supported cleanup.

## Commit and push requirements

Every verified checkpoint must be committed **and pushed** to `origin/main`.
The subject is English and begins exactly:

```text
gpt-6.1-sol: <concrete source recovery or evidence result>
```

The body describes the problem, final change, actual REA/source evidence,
validation, any exact gains/losses and cleanup. Distinguish executed checks from
reused evidence. Keep originals, tools, assets and raw analysis out of commits.
After pushing, independently compare `git rev-parse HEAD` with
`git ls-remote origin refs/heads/main`, and check `git status --short` is clean.

## Resume procedure

Read [AGENTS.md](../../AGENTS.md), this handoff,
[WORKFLOW.md](WORKFLOW.md), the remaining-functions table and the selected owner
note. Inspect the current worktree and authorities before using historical counts.
When beginning binary/compiler work, verify only the relevant inputs:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-toolchain.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Then select a new instruction-supported source question from the remaining
candidates or a missing dependency in the recovered runtime chain,
freeze the affected inputs/products, make the bounded trial and compare all
complete affected units. Record negative results and move on; publish verified
improvements promptly. Keep the original goal active when resumed, and do not
mark it complete from a smaller checkpoint.
