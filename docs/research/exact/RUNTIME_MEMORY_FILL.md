# Memory fill phases

The whole 88-byte memset at 0x00417C40 matches the pinned LIBC member without
relocations. Direct REA assembly:
`ev_970cfc68bfac8ed34e2548a51849c06abe3b2f423071fd91a778947d38065b34`.

Shared typed C preserves the low-byte fill, no-access zero-count path, bounded
alignment prefix, four-byte word stores and byte tail. It neither extends the
destination span nor invents capacity. The word alias is alignment-safe; GNU
may_alias preserves the same byte-storage contract on native/i686 builds.

One VC4 compilation produces 177/88 bytes with 176 differences. Original
REP STOSD is not reproduced; the whole function remains a candidate. Strict
native/i686 compilation passes, with no runtime/game checks. All 316 old exacts
and 105 candidates retain unchanged source/product hashes.

The two REA queries completed. Close reported cleanup_incomplete; a subsequent
process inventory confirms both owned wrapper/provider PIDs are gone. Retained
evidence and temporary resources remain available, and successful snapshot
cleanup is not claimed. Products are in `.analysis/runtime-memory-fill-20261014/`.
