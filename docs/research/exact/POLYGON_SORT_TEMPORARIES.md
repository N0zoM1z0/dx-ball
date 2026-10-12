# Separate polygon sort temporaries

The later [scan/sort workspace](POLYGON_SCAN_WORKSPACE.md) keeps the two
exchange values distinct and improves the complete candidates to211/210
differences. It preserves all nine exact raster companions; neither polygon
is yet exact.

The polygon controllers now give each Shell sort its own consumed exchange
pointer. The pending-by-top sort and active-by-X sort originally use distinct
stack homes; the maintained function-wide `saved` pointer had combined them.
Each local now belongs to the swap block after its independent key exit.
The point-loop index is also initialized before the used-edge count, restoring
the recorded order of those two zero writes.

Both complete bodies restore the original 80-byte frames and twenty separately
consumed homes. The earlier 76-byte frame required a scoped alias for one
temporary. A single bijection now covers every original/current stack access.
All 458/468 instruction boundaries, branch destinations and eleven calls per
controller correspond. Complete comparisons improve from 223/220 differences
to 218/218 across 1,543/1,592 bytes. Neither function is exact; thirty-five
normalized operand-scheduling differences remain in each.

Two canonical raster compilations retain the distinct-temporary stage and the
final ordered-initialization stage. Nine accepted raster functions preserve
715 exact code bytes and 136 metadata bytes. The triangle keeps its preceding
1,710-byte comparison with 99 differences and complete candidate metadata.
Generated label names are refreshed only after checking actual COFF definitions,
relocations and original targets. The first manifest serializer stops on nested
metadata sections before writing; using complete top-level unit blocks resolves
the serialization without another compilation.

The existing polygon selection passes 1,080 cases in each original/native and
relocated VC4/native profile. Four ordinary and seven clipped contours retain
their allocation masks, orders, pitches and colors; guarded destination and
scratch payloads agree between profiles. Linux/MinGW rebuild and the combined
VC4 relink use the two changed owners and 35 verified unchanged objects.
No triangle/span case replay or game campaign runs.

The complete original dossiers remain
`ev_493013a754a8856f617731fcd1fddd0b00f6bd3d39f2de9d39f29742e542e205`
and `ev_4ae581c6e8ad135b183d562df04de63db4419e39e3f9b46891bdec2634ee5358`.
No new REA query is needed. Complete comparisons, twenty-home correspondence,
compiler stages and both profile payloads are retained in
`.analysis/polygon-sort-temporaries-20261012/`. The current combined product
receipt is `.analysis/sound-upload-workspace-20261012/verification.json`.
