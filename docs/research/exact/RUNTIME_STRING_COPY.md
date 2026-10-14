# Bounded string copy and append

The immutable executable and pinned VC4 LIBC members establish complete
`strncpy` (0x0041DFD0,36 bytes) and `strncat` (0x0041F490,49 bytes) spans.
Both original bodies have no relocations and use handwritten x86 string loops.
REA assembly evidence is retained as
`ev_c0c81d6e149168f963d2a48e5b7c0aa1de3bf84efec70c7f07ddab42cf800d8b` and
`ev_2fd04e24d045af5b1f1375e4ee39f75e9d9d8d1481f2238b7393fad9bec334ee`.

The shared typed C source preserves bounded copy followed by zero-fill,
and destination/source scans followed by forward copy and termination.
Source and destination have the original nonoverlap contract. A zero count
never reads source; append still scans and terminates destination.

One VC4 compilation produces58/36 bytes with56 differences for copy and
69/49 bytes with68 differences for append. Both remain candidates, not exact.
Native and i686 strict compilation succeeded; no runtime or game checks ran.
All315 preceding exact and102 candidate producers and input hashes were reused
unchanged. Full comparisons and products are retained under
`.analysis/runtime-string-copy-20261014/`; the verification receipt records hashes.
