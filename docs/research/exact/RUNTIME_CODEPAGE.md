# Code-page startup and classification storage

`runtime_codepage.c` restores all five complete bodies at41C450/41C630/41C680/
41C6E0/41C710. System selection77, locale mapping95, single-byte reset44 and
initialization11 are exact across227 bytes, including every relocation and the
mapping function's39 embedded dispatch bytes. Its old56-byte imported boundary
is corrected. The full setter currently emits473/475 bytes with128 differences;
only its final12-byte case publication differs in instruction selection/scheduling.

Source owns257 classification bytes, code page, locale ID, six case words, system
fallback flag, four range flags and all five48-byte code-page records:525 logical
initialized bytes agree with the original. The original536-byte section includes
alignment gaps; no artificial padding or contiguous source placement is claimed.
The setter preserves clearing, byte truncation contracts, range endpoint reloads,
system-request fallback, exact GetCPInfo success value1, and trail flags only for
bytes1..254. Backend lead ranges must contain a backed terminating pair in the
12-byte CPINFO field. Existing classification consumers remain unchanged.

Private evidence: `.analysis/runtime-codepage-20261014/verification.json`.
One closed15-record REA run recovers all five procedures; complete pinned
`mbctype.obj` code/data and retained full original bytes prove the extents.
Two VC4 source-family trials and native/i686 standalone compilation run. Whole
case-record assignment retains all four exacts but worsens128→129 differences;
it is reverted. Final source/input/product hashes support reuse of the first
completed producer; canonical publication is not a new compilation. All277
preceding exacts and79 candidates are unchanged. No runtime tests/game builds.
Codepage/OS/game integration and the setter's final copy scheduling remain open.
