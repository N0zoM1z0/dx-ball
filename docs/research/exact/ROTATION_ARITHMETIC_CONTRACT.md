# Rotation signed-offset contract

October20,2026. One whole-owner source/build-contract recovery restores the
complete191-byte `rotated-sprite-y-offset` at402DE0. The helper's own source is
unchanged. All four other rotation code identities survive, including three
previous exacts. The renderer remains1458/1572 bytes with1466 strict differences.
This is a compiler-context recovery, not original declaration/cast spelling.

## Two complete integer producers

Both destination pixel addresses retain integer-offset-before-base evaluation:

```cpp
destination_desc.pixels +
    (rounded_y * destination_desc.pitch + rounded_x)
```

The second producer uses truncated Y, still with rounded X. The two existing
unsigned/final-signed conversion wrappers are removed together; declarations,
scopes, FP conversions, guards, reads/calls, helpers and the signed source-row
displacement cast stay fixed. CMake extends the existing per-source GNU/Clang
`-fwrapv` contract to rotation.cpp; no VC4 flag changes. Actual GNU8.4 compilation
confirms it. The [GCC8.4 contract](https://gcc.gnu.org/onlinedocs/gcc-8.4.0/gcc/Code-Gen-Options.html)
defines signed add/subtract/multiply wrap, not pointer overflow, division,
shifts, invalid FP conversion or `abs(INT_MIN)`. The option applies to existing
integer operations throughout this owner, not exclusively these four operations.
Clang sanitizer behavior is not inferred from the GNU checks.

Retained renderer Evidence
`ev_1dfa14e3428cac399a6bc2876da74d5bbc4a5edc8a8e03a6af79783e189daf26`
establishes the complete producer chains:402B80 IMUL/402B87 ADD and402BCD
IMUL/402BD4 ADD, each followed by the pixel-base addition. The
[prior finite witnesses](ROTATION_DESTINATION_ARITHMETIC.md) establish consumed
low32 results at allocation offsets63 and46. This fixed whole pair uses the
same signed displacement bits without explicit frontend type conversions.
There is no cast subset, new owner/scope, identifier/order sweep or copied code.

## Complete comparison and actual native checks

One unchanged-flag VC4 compile compares all five defined functions,115 actual
relocations and25 full literal references. Every previous-to-current relocation
occurrence has a bijective mapping with identical target/type/addend/payload.
The complete40-byte literal pool equals original420038..42005F; the duplicate
1.3 reference at420060 retains its separate primary target. Generated suffixes
do not establish identity. Complete section extents and local-target guards
remain enabled. Y-offset191 matches SHA256
`f78003af8bfdad9a5fde2fdefa1c7c6c02fbf22c00583145bed1718834106e5a`.
The other four resolved digests stay fixed; no old/new object mix is used.

After54 rollback members are size/hash verified, the canonical native build
checks all41 command configurations and39 actual compiler lines. Rotation
alone gains the option; only its object's bytes change. All38 companion objects
retain bytes/size/mode despite normal changes to all39 timestamps. Both existing
destination-wrap witnesses, the complete904-byte negative-stride witness and
all1024 unchanged maintained rotation cases pass, including151 complete guarded
buffers. Results agree with the retained originals/prior case report. Test,
oracle, witness-carrier, linker and compiler inputs have128 fixed pre/post hashes.
Native library SHA256 is
`974ca7cdae183bcce13f165d94135fa714051ff944815d01781de3169f8bbcee`.

Legacy/native REA process Evidence is respectively
`ev_b6814662c8c659cd4b7792467a1d20c3af5f104682edd7b47c61a7cba25eb334`
and `ev_468b43fd8cbd85ab089b811c82ea88ce81c640517252e7392d455ad144c2e847`.
Both exit0 with verified owned cleanup and no truncation. Serial CPU0/35%,
384MiB high/512MiB max scopes peak403,173,376/403,177,472 bytes with800/512 soft
high events and zero max/OOM events. Process samples are not exhaustive history.
No new provider import, game relink/run or full historical replay occurs.

Private authority is `.analysis/rotation-arithmetic-contract-20261020/`:
complete comparison, independent source/result reviews, native checks, installed
comparison and authored coverage. Pre-execution reviews catch the static-literal
eligibility omission and missing supplemental-input guards; both are corrected
before their respective executions. Admission installs the whole verified owner,
refreshes249 semantic dependency maps without changing ordered identities,
scopes or case counts, and verifies all270 authored receipts across30 closures.
Totals become394 overall exact/84,778 code bytes/244 metadata bytes and249
authored exact/21 candidates. The all270-authored-exact objective remains active.

Cleanup member-verifies64 closed files in a1,256,026-byte archive before
removal, releasing1,785,856 allocated bytes net before journals. All511 current
protections survive, including the adopted legacy/native products and useful
incremental caches. The manifest restores each removed path by size/hash;
`.analysis/rea/rotation-arithmetic-contract-20261020` indexes the same authority
and archive without duplicating data. No original/tool or141-record snapshot is
removed.
