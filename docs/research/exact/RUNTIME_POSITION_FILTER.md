# Stream position and unhandled C++ filtering

Complete pinned CRT sections identify ftell432, the stdcall C++ filter88 and
restoration13. Filtering/restoration match in full; ftell emits413 bytes with360
differences and remains a candidate. Restoration's unique complete13-byte match
and REA byte read establish a previously unlisted entry at0x0041E1C0.

Position calculation preserves negative-count clamping, the buffered/unbuffered
split, newline expansion, read-count-zero behavior, EOF seeking/restoration,
buffer capacity512 rules and the distinct stream/low-I/O EOF bits. The low-I/O
block slot is reloaded after seeking. Offset arithmetic retains original32-bit
wrapping without signed overflow; pointer fields retain native width and require
coherent readable buffer spans. Low-I/O declarations precede the stream header,
avoiding the observed MinGW errno declaration/import conflict.

Filtering terminates recognized three-parameter C++ exceptions, otherwise checks
the saved callback with the genuine C++ ValidateExecute API before invoking its
live value. The filter and callback use true stdcall/long32 signatures.
Restoration passes the saved callback to the real OS import. Saved pointer storage
is original4-byte COFF BSS; its PE address lies in the zero-filled virtual tail,
not file-backed bytes. Native storage grows with pointer width. No initializer
or OS installation execution is claimed.

All310 old exact and101 candidate producers retain their input/object hashes.
Current inventory541/source423/exact312/code68,690/metadata136/candidates102
(34 authored/68 runtime);249 semantic rows remain unchanged. Focused VC4/native/
i686 compilation and complete comparisons ran. The failed state consumer is
corrected from actual PE section bounds without recompiling the unchanged filter.
One closed five-record REA run; no runtime/game tests. Private evidence and unique
trials remain in `.analysis/runtime-position-filter-20261014/`. The initial signal
name hypothesis is rejected; signal registration and filter installation remain
open, together with ftell byte matching and game integration.
