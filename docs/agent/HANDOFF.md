# Current reconstruction handoff

Continue toward nearly complete original source and a rebuildable, playable
game. Prioritize coherent source recovery and affected exact comparisons.

## Current checkpoint

- 283 source-present functions; 135 exact functions / 21,248 code bytes.
- [MIDI imports and ownership](../research/exact/EXACT_MIDI_IMPORTS.md) recover
  22 independent typed service cells and C++ music object lifetime. Release,
  stream pause, music load and close add four exact units / 636 bytes. All five
  music controls are exact. Their class-specific allocator members preserve
  the real defaults; no global allocation operators are replaced.
- The shared header triggered one compile for each of 20 recipes. Complete
  comparison covers 102 units / 1,061 relocations; all 95 previously accepted
  affected units remain exact. No local-name, layout or compiler-profile trials.
- One existing MIDI Oracle passes 2,109 direct cases / 134 connected checks.
  Only Native's service-cell binding changed; no cases were added. Native,
  VC4 and MinGW builds succeed. VC4 reuses 24 current objects and compiles eight
  remaining inputs. No other owner Oracle ran.

## Next family

Recover the MDS loading/parsing/event-expansion dependency family at
`0x401000` / `0x401210` / `0x401580`. Reuse `.analysis/midi-evidence.json` and
[the MIDI owner note](../research/MIDI_OWNER.md). Open/parse have 25/40 unowned
bytes inside complete 522/868-byte spans; query only those missing full spans
before source recovery. Expand is a contiguous 343-byte body. Follow chunk
traversal, bank ownership and physical cleanup, then compare one stable family
including the accepted release/pause bodies in the same MIDI object.

Stop/callback have 14/10 local-storage differences with otherwise identical
relocated instruction boundaries and operands. Play remains 471/513 bytes;
its four error trampolines do not establish SEH syntax. Keep these candidates
without variable-spelling or layout trials. Original C++ class/member names
remain inferred, while the five caller bodies have complete exact comparisons.

Do not spend iterations rearranging sound local names or inventing aggregate
IAT aliases. Run only affected comparisons and an existing focused Oracle
when it answers a concrete question. [WORKFLOW.md](WORKFLOW.md) records the
contributor procedure; the public README stays short.

## Private evidence

The source acceptance epoch is
`.analysis/checkpoints/exact-midi-imports-283-135/`, parent
`exact-midi-lifecycle-283-131`. It retains full source/compiler inputs, prior
objects, the Oracle, original bytes and two independent reviews.
Working receipts live in `.analysis/exact-midi-imports/`.
The cumulative REA snapshot still contains 481 records; no provider queries
were needed in this batch. The full play span remains retained in the parent.

REA development checkout: `/home/pentester/Project/rea/`. This project uses
its pinned REA 4.1.0 / Ghidra 12.1.4 toolchain through `scripts/rea`.
