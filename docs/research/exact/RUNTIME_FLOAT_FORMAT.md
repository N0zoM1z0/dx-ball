# Float formatting callbacks

The local v1.07 executable and complete pinned VC4 CRT sections establish eight
source bodies. Seven match every byte after every actual relocation:

| Entry | Body | Bytes |
| --- | --- | ---: |
| 004175B0 | Initialize six conversion callbacks | 56 |
| 00419200 | Dispatch e/E, f and general formatting | 101 |
| 00418DE0 | Crop trailing fractional zeros | 89 |
| 00418E40 | Classify nonnegative or unordered value | 23 |
| 00418E60 | Assign parsed float/double | 76 |
| 0041D0D0 | Report unavailable float support | 11 |
| 0041D600 | Generate and round mantissa digits | 129 |

Decimal insertion remains101 bytes/4 differences. Assignment now matches all76
bytes. Digit generation matches all129 bytes, including the original
inline REP string scan and forward word/byte copy.
VC4 assignment preserves object representations, including NaNs. The original
three-argument digit routine uses a guard digit and updates decimal position on
carry. Decimal insertion requires a defined spare byte after the terminator.

The shipped `fltintrn.h` defines a single-member `DOUBLE` struct expressly to
avoid floating instructions during copies. Restoring that aggregate model in
assignment replaces the two-word union/memcpy sequence and closes76 bytes/both
actual bindings, with the original12-byte frame and integer transfers. Float
transport is unchanged. Native double destinations now follow the record's
ordinary alignment; the earlier unaligned-destination scope is not a native
runtime guarantee. One VC4/native/i686 set; five existing owner exacts and the
remaining insertion candidate have identical results. All361 preceding exacts
and87 other candidate results remain. Current362 exacts/75,484 code bytes/87
candidates. Receipt:
`.analysis/float-assignment-original-double-record-20261015/verification.json`.

Shipped `_fptostr.c` explicitly uses `strcpy(buf, buf + 1)` to remove the unused
guard digit. Restoring that operation replaces the earlier memmove substitution
and closes129 bytes with no relocations. This preserves the original overlapping
call; it does not establish defined modern-C overlap behavior or native runtime
acceptance. Platform-port handling remains deferred. One VC4/native/i686 set;
the four existing owner exacts, two other candidate results and all358 previous
exacts remain unchanged. Current359 exacts/75,189 code bytes/90 candidates.
Receipt: `.analysis/float-digits-original-string-operation-20261015/verification.json`.

Shipped `_fptostr.c` uses genuine register value/output/mantissa pointers; x86
REG4 for the digit count is empty. Restoring the guard-byte advance and conditional
digit stores improves122/129/68 to122/129/65. The original suffix scans length and
uses REP word/byte copies, not a byte-copy loop. Explicit safe forward copying
emits108/129/69 and was rejected; that checkpoint retained memmove. The original
strcpy operation is restored above. All four owner exacts, both other
owner candidates and all348 old exacts remain. Two compiler sets, no runtime or
provider work. Full129-byte pinned section and retained REA
`ev_15ae8106c5ec8f0c8ad0f4d532027870d80f14b3db5e3a2166d499292c7b498e`
are reused. Receipt `.analysis/float-digits-original-lifetimes-20261015/verification.json`.

The insertion entry's original JE at0x418D85 targets0x418DBB, not the return:
leading e/E skips digit scanning but still inserts the decimal point. Restoring
this shared path reduces5 differences to4. Both pinned CRT and retained REA
bytes `ev_632e632c407b30e55f8a6eeb4be8d564b0dc36a776d0c668ef38ce4cfd80cdd2`
confirm the branch. A captured-write reordering gives10 differences and is
rejected; remaining differences are loop store/scheduling. Four owner exacts
and both other candidates remain unchanged. Two compiler sets, no runtime tests;
receipt `.analysis/decimal-point-insertion-flow-20261014/verification.json`.

The earlier assignment continuation restores the two-word binary64 representation
and separate four-byte transport, without floating loads or NaN conversion.
Independent word temporaries give76/19 but enlarge the frame; the real union
view retains the original12-byte conversion frame and76/9. Whole representation
copy reverts to77/47 and is rejected. The remaining nine differences are register
and load scheduling; no permutation sweep is made. All four owner exacts and two
other owner candidates are re-compared unchanged, all331 other exacts/110 other
candidates/249 semantic rows retain their inputs/products. Three VC4/native/i686
sets run; retained REA bytes `ev_c8fb3a302ec8caa477585de4fe2ba67b16cfa1dad5b34c4b08a38abff4c645d8`
and the complete pinned section are reused. No provider/runtime/game tests run.
Current totals457/335/69,718, candidates113. Receipt:
`.analysis/runtime-float-assignment-20261014/verification.json`.

The callback state matches all24 initialized bytes and six genuine relocations.
Typed union slots hold the unavailable callback before activation and each
properly typed callback afterward; native pointer width remains natural. The
complete334-byte pinned memmove body proves its actual dependency address.

Evidence and retained compiler products are under
`.analysis/runtime-float-format-20261014/`. Fresh REA procedure evidence covers
the initializer and digit routine; complete byte reads plus complete CRT sections
establish six previously unlisted bodies where Ghidra had no procedure. No game
or runtime tests were run. Remaining exponent/fixed/general formatter bodies and
physical integration are open. Preceding285 exacts are preserved; total290 exact
functions/66,629 code bytes/136 metadata bytes,386 source bodies and87 candidates.
