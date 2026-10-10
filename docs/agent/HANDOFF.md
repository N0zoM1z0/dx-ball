# Current reconstruction handoff

Continue toward nearly complete original source and a rebuildable, playable
game. Prioritize coherent source recovery and affected exact comparisons.

## Current checkpoint

- 283 source-present functions; 135 exact functions / 21,248 code bytes.
- [MDS loading and conversion](../research/exact/EXACT_MDS_PARSER.md) restores
  the complete open/parse/convert family with a 12-byte format, eight-byte block
  and genuine 64-byte input MIDIHDR. Parameter cursor updates, partial event
  writes and live bank cleanup follow the original instructions.
- Open/parse remain 480/522 and 788/868-byte candidates. Conversion is 343/343;
  all 38 differences are EBP local-displacement bytes across 107 otherwise
  matching instructions. The whole comparison retains those differences.
- Twenty affected recipes compiled together, plus one MIDI-only refinement
  of the DWORD flag expression. Complete comparison covers 102 functions /
  1,069 relocations. All 99 previously accepted affected units remain exact.
- One existing MIDI Oracle passes 2,109 direct cases / 134 connected checks.
  Only descriptor backing grows to the complete header; logical cases are
  unchanged. Native, VC4 and MinGW builds succeed. VC4 reuses 24 current objects
  and compiles eight remaining inputs. No other owner Oracle ran.

The [previous MIDI ownership recovery](../research/exact/EXACT_MIDI_IMPORTS.md)
retains all five exact C++ music controls and 22 independently typed imports.
Stop/callback still have 14/10 local-storage differences; play remains 471/513.
Keep these candidates without variable-spelling or layout trials.

## Next family

Recover the file-service bindings of `dxball_load_binary_file` at `0x403320`
and its sound-loading callers. The complete 304-byte dossier is already saved;
[sound dependency recovery](../research/exact/EXACT_SOUND_DEPENDENCIES.md) records
its 307-byte emission and the four services still routed through an aggregate
whose layout differs from the original IAT. Follow actual cells and SDK/default
bindings, including imports shared with MDS, before adding a complete comparison.
Reuse existing source/byte evidence and the sound Oracle. Avoid another invented
aggregate binding or a series of local-storage trials.

The MDS type names are inferred; producer/consumer instructions establish their
physical records. The remaining open/parse cleanup jumps do not prove SEH syntax.
Original word/record reads use the supported x86 builds; do not broaden this
into an arbitrary host-alignment claim.

## Private evidence

The current source epoch is `.analysis/checkpoints/exact-mds-parser-283-135/`,
parent `exact-midi-imports-283-135`. It retains full inputs, initial and refined
emissions, prior accepted products, one Oracle and two independent reviews.
Working receipts live in `.analysis/exact-mds-parser/`.

Two REA raw-span queries verified the complete 522/868 bytes, including 25/40
bytes of internal cleanup jumps excluded from Ghidra's address sets. Full
responses live in run `2026-10-10T07-53-15.117Z-requests-4133453`. Close saved
483 cumulative records; all previous 481 were verified retained. Before/after
compressed full snapshots and expanded identities remain in the source epoch.

REA checkout: `/home/pentester/Project/rea/`; this project uses its pinned
REA 4.1.0 / Ghidra 12.1.4 through `scripts/rea`. Follow [WORKFLOW.md](WORKFLOW.md)
for source changes. Keep the public README focused on the REA workflow.
