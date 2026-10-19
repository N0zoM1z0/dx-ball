# Complete raster candidate instruction correspondence

October 19, 2026. The three current raster candidates now have a complete
instruction correspondence under explicit frame-role and comparison rules.
This explains their existing emissions; it changes no source, compiler inputs,
exact acceptance or semantic case scope.

| Function | Complete bytes | Instructions | Strict differing bytes | Comparison groups |
| --- | ---: | ---: | ---: | ---: |
| Triangle | 1710 | 482 | 88 | 2 |
| Polygon | 1543 | 458 | 216 | 11 |
| Clipped polygon | 1592 | 468 | 213 | 7 |

All 4845 bytes and 1408 instructions are included, including the triangle's
cleanup/handler continuation. The helper checks current source/header hashes,
object/target identities and all 90 actual code bindings against the maintained
manifest. Resolved digests reproduce the current candidate report. Every paired
instruction retains its boundary, width, prefix and address size; branch targets
retain their instruction identities. No difference is masked in that report.

## Frame roles

Paired stores and address producers establish consistent, one-to-one mappings
over every referenced frame home: 28 for triangle and 20 in each polygon. The
two polygon mappings are identical. These are representation correspondences,
not new aggregate declarations, unused locals or an original layout claim.

| Triangle role | Original EBP offset | Current EBP offset |
| --- | ---: | ---: |
| Long step | -24 | -20 |
| Short step | -20 | -24 |
| Long X | -32 | -28 |
| Short X | -16 | -16 |
| Unread vertical-scale result | -28 | -32 |
| Scanline Y | -36 | -36 |

The remaining temporary/clamp homes also map bijectively. The reserved EH chain
home stays at -12, and the construction state stays at -4. All 36 low-byte state
stores at -4 have identical bytes, values and addresses; they are not treated as
DWORD writes. Full cleanup code is covered. The existing exact 160-byte triangle
metadata and its 17 bindings remain the retained authority; actual exceptional
unwinding is not newly executed or accepted.

## Comparison producers

After frame correspondence, the only remaining instruction changes are 20
three-instruction groups: load one comparison input into EAX, compare the other
against EAX, and branch. Current code exchanges the inputs and uses the converse
signed branch; the one equality branch stays unchanged. Neither body jumps into
the middle of a group. All other normalized instructions agree.

For both original and current code, a CFG traversal checks subsequent EAX reads
and condition-flag reads on both successors. Each changed value is overwritten
before observation. Four triangle traversal paths first reach the integer
conversion call: its complete accepted 30-byte body is independently byte-checked,
has no incoming condition-flag reads and overwrites EAX before consuming it.
No general unknown-call or return-register assumption closes a traversal. All
80 original/current register/flag checks pass with no unexplained instruction.

This establishes the correspondence in the valid-storage, representable-arithmetic
domain documented in raster.h. It does not prove arbitrary intermediate/final
machine register identity, physical fault-address identity, outside entry into
an interior label, undefined arithmetic or driver behavior. The polygon edge's
untouched bytes 12..15 remain unclassified. Source spelling, original ownership
and the compiler context producing the physical homes remain unresolved.

Original primary Evidence is retained in the [triangle lifetime](TRIANGLE_SCANLINE_SCOPE.md)
and [polygon workspace](POLYGON_SCAN_WORKSPACE.md) notes. Private authority is
`.analysis/raster-operation-correspondence-20261019/inspection.json`, with input
seals, full mappings, every comparison group and CFG closure records. Its SHA256
is `cbe7dccbeb112c4010433e8d07377319bc4e36177f34650f885d642f2d1978df`.
The parent review is explicit about its scope and is not an independent review.

No compiler, provider query, target execution, native build, relink, runtime test
or full replay runs. Parsing uses one CPU at 35%, memory high 384 MiB/max 512 MiB.
All 90 protected current identities remain fixed. Totals stay 393 exacts overall,
248 authored exacts and 22 authored candidates; this is not source optimality or
a final authored-inventory claim.

Three closed helper/bytecode files are archived with per-member size/SHA256
verification before removal. The 12593-byte archive retains the executed helper;
complete inspection/review JSON stays directly available. Cleanup releases
20480 allocated bytes net before small receipts and preserves all protected
source/config/object/product identities.
