# Exact WAV upload workspace

`dxball_load_sound` at `0x00405990` now matches all 695 original bytes and
40 actual relocations. A single 40-byte upload workspace holds the ten values
already consumed by allocation, parsing, creation, locking, copying, unlocking
and cleanup. Each field follows the recorded original stack home; there are
no unused fields. The source retains the live slot rereads and call order.

The first locked span's address and length occupy EBP-12/-8; the second span
uses EBP-28/-20. The file, parsed format, payload and total byte count occupy
EBP-16/-40/-24/-32. The allocated sound record and operation result use
EBP-36/-4. Grouping these values makes their shared upload ownership explicit
without changing their widths or the public API. Exact emission establishes
a compatible source model; original declaration spelling remains unknown.

Allocation is still published before file loading. Error paths release the
same objects and retain the original slot behavior. A successful lock copies
both returned spans before unlocking and reading frequency, pan and volume.
The device-absent branch retains its null buffer. The final file release and
filename copy remain last.

One canonical sound compilation removes the preceding 31 differences.
All sixteen other configured sound functions retain 4,061 exact bytes;
the sound owner now has seventeen exact bodies totaling 4,756 bytes.
Linux and MinGW build, and VC4 links the sound and raster objects with
35 verified unchanged objects and no extra legacy compilation.

The existing upload block passes 227 original/native cases: all 26 WAVs with
device absence/presence and four split modes, file and COM failures, invalid
RIFF, allocation failures and terminal exit. Complete records, buffer bytes,
heap ownership and ordered effects compare. The same product also passes
the [polygon temporary checks](POLYGON_SORT_TEMPORARIES.md).
All 218 accepted exact units and input closures verify, reaching 51,887 code
bytes and 136 separate metadata bytes. Fifty-five authored candidates remain.

Original evidence is
`ev_e5e44144f4d74b3812d2c83fe7b7b649dde02f9a2107482ff677eb58455dd745`,
operation 06 of run `2026-10-07T16-15-32.551Z-interactive-3807439`.
Its contiguous body includes the final RET. No new provider query or game
campaign runs. Compiler inputs, complete comparisons, case receipts and
verified compressed before/staging products remain under
`.analysis/sound-upload-workspace-20261012/`.
