# Current reconstruction handoff

Continue toward nearly complete source restoration and a rebuildable, playable
game. The README explains the public workflow; operational instructions are in
[AGENTS.md](../../AGENTS.md) and [WORKFLOW.md](WORKFLOW.md).

## Current source checkpoint

- 283 source-present functions; 128 complete exact functions / 20,354 code bytes.
- Latest family: [sound buffers](../research/exact/EXACT_SOUND_BUFFERS.md).
  Pause and release are exact at 214/149 bytes. The complete loader and create
  helper retain 31/8 differing EBP-displacement bytes. All six prior sound
  exact functions remain matched.
- The current VC4 and MinGW Windows games are linked. Earlier builds have
  recorded playable campaigns; this family ran one existing sound Oracle.
  Follow [the architecture](../ARCHITECTURE.md) for connected game flows.

## Next source family

Continue sound initialization (0x405120), WAV parsing (0x406290), and binary
file loading (0x403320). Reuse the saved REA dossiers and
[sound note](../research/SOUND_OWNER.md). Reconcile the initializer's fourteen
owned ranges and the parser's gaps against original instructions before choosing
complete compiler spans. Restore dialog, import, allocation and file-handle
flow with the same shared source and minimal affected comparisons.

Use only affected exact comparisons and a focused existing Oracle when it
answers a concrete question. Seven redundant test/check scripts and the broad
default CI queue have been removed; keep iteration focused on source recovery.

## Local evidence

The completed source acceptance epoch is sealed in
`.analysis/checkpoints/exact-sound-buffers-283-128/`. It retains full inputs,
compiler products, the affected Oracle result and the independent reviews.
Its parent is `exact-sound-voices-283-126`; publication receipts are separate.
The cumulative REA snapshot contains 478 Evidence records.

The canonical native library SHA-256 is
`5624d36dffba8902e65131fa2ecd193112759cce6183f1d103d4cd30b19d696c`.
Raw investigation files remain under `.analysis/exact-sound-buffers/`.
The user's REA development checkout is `/home/pentester/Project/rea/`;
this game continues to use its pinned analysis toolchain.
