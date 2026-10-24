# Exact polygon local-source recovery

October22,2026. Both complete polygon controllers are now byte-exact in shared
portable/VC4 source, each in its own C++ owner. Acceptance reaches
**263/270 authored functions (97.41%) and77,702/84,968 code bytes (91.45%)**.
Seven authored candidates /7,266 original bytes remain; the goal stays active.

| Complete function | Before bytes / differences | Accepted bytes / differences |
| --- | ---: | ---: |
| Ordinary polygon,0x40B550 |1543 /216|1543 /0|
| Clipped polygon,0x40BB60 |1592 /213|1592 /0|
| Triangle remainder,0x40AB90 |1710 /48|1710 /60; still a candidate|

The two promotions add3,135 complete exact authored bytes. Nine prior raster
exacts retain their complete code and attached metadata identities. Overall
acceptance is408 exact functions /92,086 code bytes /244 metadata bytes, with51
current authored compiler closures. The additional triangle differences are
explicitly retained rather than borrowing its preceding incompatible object.

## Natural source model

The retained [full instruction correspondence](RASTER_OPERATION_CORRESPONDENCE.md)
shows original point storage interleaving with scalar/pointer homes. The old
contiguous64-byte workspace cannot express that layout; the previously rejected
full80-byte aggregate adds address producers for point copies. The
[preceding private probes](SOURCE_CONTEXT_CONTROLS_20261022.md) instead expose
the16 actually consumed workspace values as real local scalars/pointers, keeping
two separate POD endpoint points. That model initially gives39 differences in
each controller.

The accepted implementation preserves every executable operation, point-copy
expression, allocation and cleanup order, queue reread, clipping condition and
span call. An inverse alpha-renaming/declaration-removal check preserves the
executable token sequence. The heap edge record remains28 bytes; unclassified
bytes12–15 remain untouched. There are no unused locals, padding, assembly,
patched output or separate legacy game bodies.

`src/fill_polygon.cpp` and `src/fill_polygon_clipped.cpp` share the same local
name/declaration model. Their genuine `RasterEdge` definitions are identical.
`src/raster.cpp` retains the horizontal span, triangle and eight FixedPoint
bodies; the now-unused edge/workspace types leave that remainder. Both build
systems and the restored-CRT link recipe include the new owners, increasing
source objects134→136. Public ABI, headers and pinned raster flags stay fixed.

## Bounded reconstruction and limits

The finite dictionary has16 meaningful synonyms per role. The retained C1XX
bucket traversal predicts storage order; separate declaration-order screening
uses C2 LOAD ranks. The first4097-order screen selects one source in471,549
name states. That usable source gives1543/7: only two endpoint-y comparisons and
the scanline/pitch product differ. The next10,000-order screen uses the two
retained outputs and independent parameter-rank intervals, visiting2448 name
states. It gives1543/5, correcting the product.

An assumed pitch key at local-base minus4 predicts no possible phase and is
discarded explicitly. Root LOAD ranks also incorrectly predict the point-member
comparisons. No parameter IDs, member-load formula or original spellings are
claimed as observed. The final source swaps only the two consumed same-type
point declarations, whose distinct buckets preserve storage order. It restores
the last five bytes. Applying that exact model to the clipped body gives1592/0.

The five-attempt target family includes one malformed preparation that selected
an `extern "C"` brace, failed compilation and produced no object. Its actual
source and diagnostic limitation are retained; the full compiler stderr was
truncated before the helper saved failures. A distinct corrected input supplies
the usable7/5/0 ordinary outputs, followed by one clipped0 output. The helper
then saves producer status/logs before comparison. No failed or successful
frozen input is recompiled. The coherent remainder is a separately frozen
single adoption-closure compile, not another target search.

Complete unmasked emitted equality establishes acceptance, independently of
these layout/rank predictions. The resolved/original SHA-256 values are
`e0f925a9a6dce46ceeff02ce08948383bcee3639d3e710018dc2c022abaabb86`
and `128d5d228c486432725cd13156d1dd469481d7f541497070b2a1c19ce064f1aa`.

## Coherent comparison and maintained verification

All12 affected complete functions compare across three coherent objects, with
116 code bindings,25 metadata bindings and296 attached metadata bytes. The
remainder maps all61 non-file symbols and real associative COMDAT parents,
checks auxiliaries/noncode payloads and preserves all nine prior exacts.
Generated labels are mapped by actual section/value/type/storage, not numeric
name coincidence. The unchanged full comparator and exact local-target guard
apply. No literal, metadata or differing byte is masked.

Publication initially leaves the fragment ledger's metadata-carrier column on
old generated names, which tracking validation rejects. The existing COFF
bijection repairs both carrier and cleanup-label references directly from the
original rows; numeric aliases are never applied recursively. No producer is
repeated and neither validator nor comparison rules change. Tracking then
passes with553 candidates,475 source-present entries and408 exacts.

The maintained native target rebuilds only the three affected sources and link,
preserving57 companion objects and all60 previous compile configurations.
Exactly936 selected existing original/native polygon cases pass: triangle,
rectangle and concave contours plus all seven clipping contours, every existing
point-order variant, pitch/color pair and allocation-failure mask. Checks retain
complete guarded pixels/padding, immutable points, scratch bytes/pointer arrays
and allocation/free events. The historical5400 polygon,684 triangle and1080
span sets are not represented as newly rerun. All249 historical semantic
scope/count/order/oracle fields stay intact; only current dependencies refresh.

Compiler and native checks run serially on CPU0/35%, memory384/512MiB. Successful
compiler scope peaks are below148MiB; the focused native check peaks at43,470,848
bytes, with no memory events. No new provider import, game relink, game campaign
or physical-driver claim follows. The tested game delivery still predates these
source changes.

Private authority is
`.analysis/polygon-declaration-source-search-20261022/current-checkpoint.json`:
complete proof, native summary, adoption and corrected-publication records.
The earlier39-difference phase and closed declaration proposals are archived
with every member size/SHA/mode verified before obsolete copied inputs/objects
are retired. Current canonical objects, native library and useful caches stay.
Cleanup verifies107 archive members and retires79 obsolete files, releasing
917,504 allocated bytes net of the archive before small index/receipts. The
overwritten checkpoint's rollback archive is recoverable inside that archive.
