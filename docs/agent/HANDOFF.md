# Current reconstruction handoff

Continue toward nearly complete original source and a rebuildable, playable
game. Prioritize coherent source recovery and affected exact comparisons.

## Current checkpoint

- 283 source-present functions; 128 exact functions / 20,354 code bytes.
- [Sound dependencies](../research/exact/EXACT_SOUND_DEPENDENCIES.md) now recover
  initialization, WAV parsing and direct binary-file allocation. Their complete
  original spans are 1,705/269/304 bytes. Initializer and parser instruction
  flows agree; local storage remains nonexact. File-import storage is unresolved.
- All eight accepted sound units remain exact. The final sound object supports
  17 complete comparisons / 235 relocations / 12 literals. The first emission
  exposed duplicate last-case breaks; one source correction preceded the final
  comparison. No variable spelling, layout or compiler-profile trials.
- One unchanged sound Oracle passes 5,782 direct cases / 48 connected checks.
  Native bytes remain identical after the diagnostic-option change. VC4 and
  MinGW games link; the original fmt-before-data precondition stays visible as
  a source-specific GNU diagnostic in `CMakeLists.txt`.

## Next family

Recover the MIDI stream lifecycle and music controls in `src/midi.c`, starting
with release/play/pause/stop/callback at `0x4016E0`–`0x401B10` and music controls
at `0x401B90`–`0x401DA0`. Reuse `.analysis/midi-evidence.json` and
[the MIDI owner note](../research/MIDI_OWNER.md). Follow buffer ownership,
callback requeueing and physical WinMM call signatures. Keep whole bodies;
expand to parsing dependencies when their flow requires it.

Do not spend iterations rearranging sound local names or inventing aggregate
IAT aliases. Run only affected comparisons and an existing focused Oracle
when it answers a concrete question. [WORKFLOW.md](WORKFLOW.md) records the
contributor procedure; the public README stays short.

## Private evidence

The source acceptance epoch is
`.analysis/checkpoints/exact-sound-dependencies-283-128/`, parent
`exact-sound-buffers-283-128`. It retains full source/compiler inputs, both
emission epochs, the Oracle, original bytes and independent reviews.
Working receipts live in `.analysis/exact-sound-dependencies/`.
The cumulative REA snapshot contains 480 Evidence records; the new complete
byte-span responses are in the October 10 archived run.

REA development checkout: `/home/pentester/Project/rea/`. This project uses
its pinned REA 4.1.0 / Ghidra 12.1.4 toolchain through `scripts/rea`.
