# Runtime error controls

Five full bodies now have shared C++ source. Read/write validation32/32,
code validation27 and abort31 are complete exacts across122 bytes and six
actual bindings. Abort includes the four trailing cleanup/return bytes missing
from the imported27-byte extent. C++ validation names and signatures follow
the pinned `validate.obj` definitions, not the conflicting Ghidra read/write label.

Validation preserves the default-valid scalar across the real SDK probe and
clears it on rejection. Counts retain unsigned32 while pointer/SDK count widths
grow naturally on native hosts. These are recovered historical probes, not a
claim of race-free memory safety. Abort preserves error10, signal22 and quick
exit3 in the observed order; the signal backend remains a dependency.

MessageBox is now complete146-byte exact. Its three
typed local static callbacks start null; required binding failure returns0,
optional window/popup exports remain optional, and the loaded module is kept.
All four export literals match in full across58 bytes. A shared binding-failure
exit improves152/121 to146/90. A positive short-circuit binding-success block
then restores the terminal failure return and removes all90 differences.
All14 actual relocations and58 literal bytes are covered; the four existing
owner exacts are unchanged. One VC4/native/i686 compilation set, retained REA
and no runtime/UI/game tests. Exact338/code70,140/candidates111; all337 prior
exacts,111 other candidates and249 semantic rows preserved. Current private seal:
`.analysis/messagebox-binding-success-20261014/verification.json`.
GetProcAddress results are converted to the actual export signatures, preserving
native-width window handles. Standalone GNU compilation disables only that
intentional export-pointer conversion diagnostic; there are no alternate bodies.

Closed REA run `2026-10-13T17-08-23.420Z-interactive-1877554`; assembly IDs:
MessageBox `ev_3a233ed4ababc4d5bf5e6b208fa63acb6bf4453aeea9bfcf4e94489bf842ce93`,
read `ev_7ee1cf5da65cfc491abcfce5b8ac5b0a2e1d03101ffb7434c2a61564a9cd4bd7`,
write `ev_434f30f5515619ae25123568b6398e449c17796c6cfe2b0afe3fe25b4cfa1924`,
execute `ev_768737c026ecc1e7d841490c0a6a2c860997b0a59d29572c120204621e60fd27`,
abort `ev_c1f3a9e3b773b43b501365b46829b25fb723d946eeed732d7aefe8d4f1cb9b9a`.
Five whole pinned CRT sections independently prove extents and import identities.
Two legacy compiles preserve all four exacts; complete final comparisons and
native/i686 C++98 compilation run. All270 preceding exacts and74 candidates
reuse unchanged inputs/products/results. Source358/exact274/65,721 code bytes;
candidates75, metadata136 unchanged. No runtime tests/game builds; physical
UI/exception/signal and game integration remain open. Private seal:
`.analysis/runtime-error-control-20261014/verification.json`.
