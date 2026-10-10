# Current reconstruction handoff

Continue toward nearly complete source restoration and a rebuildable, playable
game. The README explains the public workflow; operational instructions are in
[AGENTS.md](../../AGENTS.md) and [WORKFLOW.md](WORKFLOW.md).

## Current source checkpoint

- 283 source-present functions; 126 complete exact functions / 19,991 code bytes.
- Latest family: [sound voices](../research/exact/EXACT_SOUND_VOICES.md).
  Play and update are exact at 289 bytes each. Stop, three parameter setters
  and recovery retain 5/4/4/4/13 differing EBP-displacement bytes.
- The current VC4 and MinGW Windows games are linked. Earlier builds have
  recorded playable campaigns; this family ran one existing sound Oracle.
  Follow [the architecture](../ARCHITECTURE.md) for connected game flows.

## Next source family

Continue sound buffer upload and release: `pause_sound` (0x4057D0),
`release_sound` (0x4058F0), `load_sound` (0x405990), and
`create_sound_buffer` (0x4063A0). These complete bodies total 1,147 original
bytes. Reuse the saved REA dossiers and [sound note](../research/SOUND_OWNER.md).
Follow record ownership through upload failures and focus cleanup. Then recover
initialization, WAV parsing and file loading as connected dependencies.

Use only affected exact comparisons and a focused existing Oracle when it
answers a concrete question. Seven redundant test/check scripts and the broad
default CI queue have been removed; keep iteration focused on source recovery.

## Local evidence

The completed source acceptance epoch is sealed in
`.analysis/checkpoints/exact-sound-voices-283-126/`. It retains full inputs,
compiler products, the affected Oracle result and the independent reviews.
Its parent is `exact-frame-boundary-283-124`; publication receipts are separate.
The cumulative REA snapshot contains 478 Evidence records.

The canonical native library SHA-256 is
`8998f24dbe8e3c86f956d1f6353165164926e4347c0f6f72c6a61e5ca8aa312e`.
Raw investigation files remain under `.analysis/exact-sound-voices/`.
The user's REA development checkout is `/home/pentester/Project/rea/`;
this game continues to use its pinned analysis toolchain.
