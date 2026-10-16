# Windows raster defaults

The Windows raster callback table now starts with the genuine Kernel32 MulDiv
entry. The same writable `DxBallRasterOps` interface still supports explicit
callback replacement and `dxball_bind_windows()`. Original raster function
bodies and public headers are unchanged. Non-Windows builds retain the existing
portable arithmetic; their complete preprocessed translation unit is identical.

The original fixed-point ratio calls `KERNEL32!MulDiv` through IAT `0x4412A8`,
as established by retained REA Evidence
`ev_8918b1c9e1c00cc27bea91410f1e26a891db3fa2703cffd585a82ae93c3d9558`.
The previous Windows default instead retained `portable_muldiv`, whose wide
division introduced the explicit `lldiv.obj` dependency. That member is no
longer needed. The restored-CRT game links 113 maintained source objects, three
integration objects and **19 explicit original members**. All 116 source
products are reused during the public link; the builder compiles none.

An ordinary typed import-library declaration keeps the default table a static
initializer. Its complete twelve bytes have three actual pointer bindings:
malloc, free and MulDiv. The loaded function pointer resolves through the
import-library jump to the real Kernel32 IAT cell. A private dllimport-address
control generated an additional C++ initializer and is not adopted. The
accepted source adds no initializer: the complete 84-byte CRT table still has
the same thirteen original callback bindings and ordering.

## Affected comparisons

One stable owner object supplies twelve complete comparisons. All nine accepted
exacts retain 715 code bytes and 136 metadata bytes. Triangle code and its
160-byte metadata retain the previous complete result: 1,710 bytes and 88
differences. The ordinary/clipped polygons remain 1,543/1,592 bytes, now with
214/214 differing positions against the original, previously 211/210.

Only five signed comparison groups differ between the old and new polygon
objects. They reverse operands and reverse the signed branch condition. The
ordinary polygon loads both record pointers from the same live stack slot;
the clipped groups read the same two stack values. Each predicate is equal
for every signed32 pair. A complete CFG walk checks that the changed scratch
register and flags are dead on both successors, including the genuine cdecl
heap-release boundary. All other instruction bytes across the 458/468
instruction bodies agree. This proof assumes the existing backed ordinary
storage domain; it does not establish fault-order or exception-context equality.

Private metadata labels follow actual COFF section/offset/storage definitions
and relocations. The 24 parent-owned compiler fragments retain their original
ranges and bindings under their refreshed source label identities. No new
function/source/exact claim follows. Totals remain 545 inventory entries,
475 source entries, 380 exacts and 95 complete candidates. The other 371 exact
and 92 candidate results and products are reused.

## Focused execution and reuse

One Wine process starts a small probe with the production source closure and
explicit original dependencies. Before CRT initialization or Windows binding,
twelve default calls agree with direct OS MulDiv calls. Inputs include signs,
half ties, zero divisor, boundary values and overflow. Fixed-point ratio then
returns 98,304 for 3/2. Replacing the callback records the actual three arguments
and returns its controlled value; the real Windows binding restores OS behavior.
This uses a probe entry, not a gameplay run or arbitrary startup-path claim.

Wine returns -1 for MulDiv(INT_MIN, 1, 1); the retained portable expression
computes INT_MIN there. The fresh observation belongs to Wine. Native Windows
behavior and complete cross-platform corner equivalence remain unverified;
the native fallback is unchanged and ports remain deferred.

The unchanged native preprocessed program supports reuse of the existing native
observations without rerunning their queues. Only source input identities
refresh in 235 semantic rows, including four primary raster source identities;
all 249 scopes, counts, oracle identities and observations are retained. The
other fourteen rows are byte-identical. No full replay, new provider query or
game campaign runs. Tracking validates the maintained reports and ledgers.
Heavy work is serial with CPU35%, memory high640MiB/maximum768MiB.
Verified gzip roundtrips for both native preprocessing carriers and sharing
four identical immutable headers release 112KiB of allocated storage. Unique
sources, objects, maps and observations remain retained.

Private evidence is `.analysis/raster-win32-default-20261017/`: complete source
and before snapshots, `compile.json`, `comparison-equivalence.json`,
`native-equivalence.json`, `adoption.json`, `runtime.json` and `verification.json`.
The prior 21-member first-board evidence remains historical; this change checks
the affected boundary and current link. See [restored game entry](RESTORED_CRT_GAME_ENTRY.md).
