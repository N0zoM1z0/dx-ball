# Exact sprite-bank recovery state

`dxball_restore_sprite_banks` at `0x403D30` matches all282 original bytes and
seven bindings. Its shared recovery state holds the active bank and discarded
Restore result; a scalar slot belongs to each bank's scan. These three actual
values occupy the original12-byte frame: bank EBP-4, result EBP-8, slot EBP-12.

The original reloads live sprite and surface pointers, calls Restore only for
nonnull surfaces, writes its HRESULT and proceeds without checking it. After
scanning all255 slots, it reloads each allocation-mode1 bank with its actual
filename. All live reads, failure behavior and call order remain shared by
portable and legacy builds.

The saved REA carrier is
`.analysis/rea/runs/2026-10-07T10-33-32.118Z-interactive-2912559/06-analyze_function.json`,
Evidence `ev_6086488847b0abeff3f7ed6af657fd76f1d18d085752c4ae7c38ff49c74b9d94`.
It covers the contiguous282-byte body and85 instructions. The original result
write at `0x403E0B` supports the retained state; its authored spelling and whether
it came from an explicit local remain unknown.

Three bounded record models distinguish the actual bank and slot phases.
The whole-scan record and a slot/result cursor restore allthree homes but
load the slot before the bank in array-address production, retaining60 byte
differences. Both are rejected. The selected bank/result recovery state with
a bank-scoped scalar slot also restores the original bank-first address schedule.
The prior [result-only recovery](SPRITE_RESTORE_RESULT.md) had18 home differences;
its scalar scan-scope hypotheses remain closed.

Allfour accepted device companions retain526 exact bytes. Palette transition
keeps its1339-byte candidate and18 global-read differences. Sixty-four unchanged
original/native bank cases compare full state and ordered Restore/reload calls,
including allocation modes, null pointers, terminal slots and ignored failures.
Linux and MinGW products build; VC4 links one changed object with36 verified
unchanged objects. No game runs.

The checkpoint verifies all225 exact closures across55,998 code bytes and136
metadata bytes, leaving48 authored nonexact functions. Completed private receipts
and rejected models are retained in `.analysis/sprite-recovery-cursor-20261012/`.
