# Low-I/O startup and fatal errors

Four complete bodies now have maintained source. Fatal dispatch at `0x418930`
is42-byte exact, not the imported38-byte prefix: the trailing stack cleanup and
return are included. Banner dispatch at `0x41C800` is61-byte exact. All nine
actual bindings match. Initialization at `0x41AD10` has468/467 bytes with304
differences; error formatting at `0x41C840` has493/494 with419. Both remain candidates.

Initialization restores32-record allocation,64-block ownership, the2048-handle
inheritance cap, packed count/handle decoding, post-import handle reloads and
the original standard-stream flags. STARTUPINFOA retains68 Win32 bytes and
native-width pointers. Byte-packed alias-safe packet types remove the memcpy
locals' extra homes, improving506/467/367 to468/467/304 with the original68-byte
frame. Three startup compilations include the C allocator-linkage correction;
one fatal compilation covers all three fatal-owner functions.

The full17-row136-byte error table and every complete string match the original.
Error mode and application type are distinct cells at `0x423114`/`0x423118`.
The exit callback's four-byte initializer targets the existing quick-exit entry
at `0x417930`; debug callbacks remain optional and are read after banner output.
Formatting preserves console output, filename fallback, the59-character tail,
three-byte ellipsis overwrite and the GUI message-box call. Its139-byte output
bound follows all format/text maxima. Unexplained original frame space is not
turned into a guessed larger array; original formatting frame recovery is open.
Inputs require a catalog reason, terminated module filename and backed nonnegative
inherited packet. The startup allocation-failure exit must not return. Native
packets carry native-width handles; original Win32 packets retain four-byte handles.

Closed REA run `2026-10-13T16-37-26.660Z-interactive-1845579`, assembly:
startup `ev_ff7340af30b2e504f64919461b80d310aaea86a1280a86f1a33fcde880d36f87`,
fatal `ev_851cf2b71d136e23d4b9af1063451b2165d151d2d95ec2fcfef200a68b4df76c`,
banner `ev_5728861eadf1839d5726e6492f8cdafee59fcc2b4a908ff3e3cabf6b6a3d4eb5`,
format `ev_4337657dfbcfb469e995ef62b64dbd6d0ee53aa2189f2439a7b420161e4b53c7`.
Whole pinned CRT sections independently prove all extents, imports and literals.
Native/i686 standalone compilation covers both owners; intentional non-NUL tail
overwrite disables only the MinGW string-truncation diagnostic. No runtime tests
or game builds; OS/startup integration and the message-box backend remain open.
All268 prior exacts and72 candidates preserve producer inputs/products/results.
Source353/exact270/65,599 code bytes; candidates74, metadata136 unchanged.
Private seal: `.analysis/runtime-lowio-startup-20261014/verification.json`.
