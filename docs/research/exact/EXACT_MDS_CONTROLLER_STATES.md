# Exact MDS loading and stream submission

The MDS loader at `0x401000` matches all 522 original bytes and ten bindings.
The player at `0x401780` matches all 513 bytes and seven bindings. This completes
all eight configured MIDI bodies across 2,880 bytes and adds 1,035 exact bytes.
The checkpoint has 227 exact functions /57,033 code bytes /136 metadata bytes,
with 46 authored nonexact functions remaining.

## Recovered state and flags

The loader holds its error result, context, mapped-view ownership and two handles
in one loading state. Its original 20-byte frame is restored: result EBP-20,
context EBP-16, mapped flag EBP-12, mapping EBP-8 and file EBP-4. Initialization
order, partial allocation cleanup, output publication and file/view release
remain the original operations.

The player holds its current header, result, context, remaining count, created
flag, property and device in one submission state. All eight words of the
original 32-byte frame agree: header EBP-32, result EBP-28, context EBP-24,
remaining EBP-20, created EBP-16, property EBP-12/-8 and device EBP-4. The property
is still passed by address. Header traversal reloads the live buffer length,
and only a newly created stream is stopped after an error.

The old byte parameter declarations introduced promotion instructions. The
original loader mixes a four-byte mode-slot read with AL masks and comparison;
the player tests the low bit directly in its flags slot. The selected fixed-width
model uses `DxBallInt mode` and `DxBallUInt flags`. Under the pinned compiler,
these reproduce the complete original operations without narrowing casts. The
native fixture now declares those actual four-byte arguments. The source typedef
spellings remain inferred; low-bit consumers and whole-body equality ground the
reconstruction.

Five MIDI compilations retain the progression. Loading state alone restores
its homes but leaves 530/522 bytes and 439 differences. Submission state restores
its homes too, leaving playback 516/513 and 143 differences. Signed-byte parameters
leave 527/522 and 515/513. The unsigned-word mode with a narrowed input view leaves
524/522, while playback reaches 513 exact bytes. The final signed-word selector
removes the remaining loader width differences and reaches 522 exact bytes.
Earlier narrowing-after-mask hypotheses remain closed and are not repeated.

## Evidence and complete extents

| Body | Saved REA dossier | Complete read |
| --- | --- | --- |
| Open | `ev_b065fc674d2df0514ae7b30b49b895ceb361f5ec770b3c4e0ec21eb8512ef3ed` | `ev_a7b7f4ce05473f020601101338f2392f0e732597eaed9078a2bd13128a77a584` |
| Play | `ev_731ffd0b77a82869a867a736b02d245cc55b41b97dfc1974dee55fe3f83d27a4` | `ev_63cb8dd0c62cd2c2e8e121e730540f10d836f953facd739adb6d4c6573b1ba9a` |

The full comparisons include 25 loader and 20 player bytes excluded from imported
Ghidra ownership. Their original continuation jumps and cleanup stubs are emitted
by the shared C++ error gotos. All declared bindings are applied; no bytes are
masked. The full carriers and their hashes are listed in the private
`.analysis/mds-open-state-20261012/rea-reuse.json`. No new REA request occurs.

## Verification and products

Six header-consuming match recipes preserve 62 accepted companion bodies.
The Windows adapter is also rebuilt against the new header. Its code, initialized
data, BSS layout, symbols and relocations are identical; only the COFF timestamp
changes. A comparison consumer initially treated a BSS raw offset of zero as file
offset zero. It is corrected to verify the actual uninitialized section, and
reuses the completed object without recompilation.

Two unchanged loader loops pass 284 cases, and the existing playback matrices
pass 372 cases. Fifty-six additional full-word flag cases cover all four mode
classes and both playback-bit classes with high-bit prefixes, including negative
signed modes and paused streams. Full returns, context/header/payload storage,
ownership, ordered SDK calls and cleanup compare with the original. These new
vectors are recorded separately from historical semantic counts.

Linux and MinGW products build. VC4 links seven matching recipe objects, one
rebuilt adapter and 29 verified unchanged objects. The initial link preflight
caught that adapter dependency before executing the linker. All 227 whole exact
closures and current compiler inputs verify. Completed private products and
tracking copies are compressed; originals and unique evidence remain intact.
No game campaign runs. Final receipts are in
`.analysis/mds-open-state-20261012/verification.json`.
