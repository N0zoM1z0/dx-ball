# Exact multiprocessing FDIV test

The complete278-byte testfdiv.obj body at0x00418C50, all twelve relocations and
five complete literals totaling89 bytes match the maintained source. The first
typed producer has twelve argument-preparation differences; separating real
process-handle acquisition from the affinity call removes all twelve. No local
layout, name permutation, padding or alternate source body is used.

The routine tests the current processor first, then loads KERNEL32 and resolves
four typed stdcall exports in original order. The scan uses the system mask,
not the process mask, and visits exactly32 bit positions. Native mask/handle
widths remain natural. GetCurrentThread takes no arguments; the disassembler's
early mask push belongs to the subsequent SetThreadAffinityMask call. Set-affinity
failures are ignored, and both final paths attempt restoration to the system
mask rather than a saved thread mask. The module reference is deliberately
retained. Physical x87 testing remains the real unresolved helper, not a callback
fixture or emulation result. This supplies the existing math-initialization
dependency without changing that owner.

All314 old exact and102 candidate producers retain unchanged input/object hashes.
Current inventory543/source426/exact315/code69,003/metadata136;249 semantic rows
are unchanged. Two focused VC4/native/i686 source trials and whole code/literal
comparisons ran. One initial empty provider session was closed; the actual
two-record REA session is also closed. Earlier whole CRT/string placement evidence
is reused. No runtime tests, CPU-affinity execution or game builds. Private proof:
`.analysis/runtime-fdiv-processors-20261014/`. Physical hardware and game integration
remain open.
