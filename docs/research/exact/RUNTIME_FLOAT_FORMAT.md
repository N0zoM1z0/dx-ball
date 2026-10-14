# Float formatting callbacks

The local v1.07 executable and complete pinned VC4 CRT sections establish eight
source bodies. Five match every byte after every actual relocation:

| Entry | Body | Bytes |
| --- | --- | ---: |
| 004175B0 | Initialize six conversion callbacks | 56 |
| 00419200 | Dispatch e/E, f and general formatting | 101 |
| 00418DE0 | Crop trailing fractional zeros | 89 |
| 00418E40 | Classify nonnegative or unordered value | 23 |
| 0041D0D0 | Report unavailable float support | 11 |

Decimal insertion remains101 bytes/5 differences, assignment76/76 bytes with9
differences, and digit generation122/129 bytes with68 differences. Digit shifting
uses overlap-safe memmove rather than the original overlapping intrinsic strcpy.
Assignment preserves object representations, including NaNs. The original
three-argument digit routine uses a guard digit and updates decimal position on
carry. Decimal insertion requires a defined spare byte after the terminator.

Assignment continuation restores the actual two-word binary64 representation
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
