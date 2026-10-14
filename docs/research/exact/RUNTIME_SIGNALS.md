# Signal and exception dispatch

Signal lookup49 and exception lookup47 are complete exacts across96 bytes,
including the full140-byte initialized carrier:10 real records, FPE group3/7,
record count10, floating code140 and null information pointer. Native pointers
and handler unions grow naturally. Tagged default/ignore/die values retain0/1/5;
simple and floating callbacks use their observed one/two-argument signatures.

Raise now includes its complete393-byte carrier, not the old340-byte decoded
prefix: all53 embedded switch bytes and actual bindings are compared. Current
raise is393/393 with323 differences; exception filtering is351/351 with9.
Both remain nonexact. Handler snapshot/fallback improves filtering378/356→376/355.
Hardware-only save/call/restore scopes improve raise401/328→393/323 and avoid
MinGW's flat-guard uninitialized-state diagnostic without fake initial values.
Two exact lookups are preserved across all three legacy compilations.

Filtering now captures the original native-width tagged handler word and calls
its real one/two-argument signatures. FPE action slots use a whole-carrier byte
cursor and one captured countdown, preserving the existing coherent-group guard.
This restores the zero-local-byte frame and reduces376/355 to351/9. All351 bytes,
21 bindings and140 initialized state bytes are checked; only the entry comparison
and loop ECX/EDI allocation remain. A corresponding raise trial369/358 is rejected.
Its original393/323 and all53 dispatch bytes are preserved after actual same-value
COFF definition checks resolve renamed private labels. Four VC4/native/i686 sets,
no runtime/provider/game tests. All338 exacts/109 other candidates/249 semantic rows
remain. Current seal: `.analysis/signal-filter-fpe-countdown-20261014/verification.json`.

Lookup reads use byte views of the complete carrier, preserving terminal
metadata reads without forming an out-of-array C access. Dispatch requires
record-backed lookup results, coherent count/group bounds and correctly typed
real handlers; default process exit must not return. Invalid signal numbers
return−1 without a new errno write. Context clearing, FPE group reset, all seven
floating-code mappings and the different raise/filter restoration orders remain.

Two real entries missing from the imported inventory are added: filter
`0x41BD60`/351 and exception lookup `0x41BEC0`/47; inventory becomes531. Ghidra
has no procedures/instructions there. REA retains complete original-equal byte
ranges, independently matched against entire pinned CRT sections; local
instruction decoding is supplemental, not a REA decompilation claim.
Closed runs: `2026-10-13T17-31-08.327Z-interactive-1900244` and
`2026-10-13T17-47-15.067Z-interactive-1915478`. Raise assembly:
`ev_8d25ebcd8f1f991a76ac66c0bdbbf014d6b94fe6e9244a6d239cf4a112c2ed0d`;
signal lookup: `ev_a2ab8086de408ff97fea9a8f5f2f576f5e9387e428200f794a5f7c87f0ca6746`.
Filter/lookup byte evidence: `ev_a870a4ae15b5a9f20af8bf95864f1136bd058327b38f383c2cc51059a58b5b74`
and `ev_345f137d526724ec93de692e732a5506399018db313ac0fc0611f547a2636172`.

Four complete final comparisons and native/i686 C11 compilation run. All274
preceding exacts/75 candidates reuse unchanged inputs/products/results. No
runtime tests or game builds. Source362/exact276/65,817 code bytes;
candidates77, metadata136 unchanged. Registration and physical OS/exception/game
integration remain open. Private seal: `.analysis/runtime-signals-20261014/verification.json`.
