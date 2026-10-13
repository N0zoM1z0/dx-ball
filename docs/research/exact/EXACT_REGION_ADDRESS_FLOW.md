# Complete dirty-region address and callback flow

The [later C++ surface integration](EXACT_DISPLAY_COM_CALLS.md) recovers all
827 original bytes and 198 instructions. The address-scheduling diagnosis below
describes the earlier C emission and explains its nineteen extra bytes.

The dirty-region restoration candidate has no newly identified source gap.
Its complete 827-byte original and current 846-byte object contain the same
198 instruction positions and control flow. All 19 changed address producers
compute the same two-page rectangle address. The current object is also the
verified object linked into the current VC4 game; shared source is unchanged.

This remains a nonexact candidate with 746 strict byte differences. No source
spelling, declaration-order, layout or padding experiment follows this result.

## Whole-body correspondence

The original producer loads the current page into EAX and shifts it by four,
then loads the local loop index into ECX and shifts it by five. The current
producer assigns those two inputs to the opposite registers and shifts them
accordingly. Both produce `page * 16 + index * 32` modulo 2^32.

All 19 producers are verified as actual four-instruction sequences. Their
14/15-byte encodings account for the complete 19-byte size difference. The
remaining 122 instructions have equal mnemonics, operand widths and operands,
with direct destinations mapped to the same instruction positions. All 22
branches, two COM calls and 61 actual relocations are checked across the complete
RET-inclusive spans; there are no skipped code bytes or embedded tables.

Every differing producer is followed through all CFG successors. Only the
commutative address sum, an equal ADD result/flags, or overwrite of the scratch
values can consume it. Differing scratch values cannot enter a stored scalar,
pushed argument, call destination or branch predicate. Partial EFLAGS writes
such as INC/DEC do not clear the differing carry flag in this audit.

The actual Blt/BltFast boundaries use stack arguments and have no specified
EAX/ECX/EDX or EFLAGS input. Scratch residue is allowed there under that ABI.
ECX/EFLAGS can also differ at the void exit; callee-saved registers and the final
EAX page value agree. This is explicit ABI-scoped correspondence, not a claim
that every machine register is equal at all times.

The source retains clipping selected once, inclusive screen-boundary behavior,
in-place updates, separate clipped/fast loops and live page/surface/count reads.
After each COM call it reads the current presentation controls and selected
dirty record, copies all four fields if eligible, then increments the count.
The final clear applies to the page selected at that final operation.

## Selected original/native observations

The unchanged existing 54 restore cases pass: both pages, clip/reduced values
0/1/2, presentation counts 0/1998/2000 and the original rectangle matrix.
The maintained constructors, case bodies, ordered events and complete buffer
assertions are retained.

Another 36 private cases use the genuine original and current native COM
callbacks, applying one controlled state change after the first draw. Both
pages and clip values 0/1/2 cover each of these actions:

| Callback change | Observed subsequent behavior |
| --- | --- |
| Switch page | Next record and loop bound use the new page; only that page is cleared. |
| Extend count from two to three | The third initialized rectangle is drawn. |
| Shrink count to one | Drawing stops after the first rectangle. |
| Enable presentation at count 1999 | The just-drawn current record fills slot 1999. |
| Fill presentation capacity | No presentation record is written. |
| Switch effect/restore surfaces | Later draws use both new surface pointers. |

The unchanged harness compares complete ordered events, dirty/presentation
arrays, counts, keys and lightning storage, including all unmodified fields.
These checks establish controlled callback behavior in valid bounded states;
they do not establish concurrent memory access or physical DirectDraw pixels.

The initial run passes the 54 existing cases and three private cases before a
new wrapper incorrectly looks for the reduced-particles scalar in the generic
extra-field map. The saved stack trace reaches private case 57 after the
explicit 54-case assertion. Correcting that wrapper to access the genuine typed
global leaves production source and maintained tests unchanged. Only the 36
private cases run afterward; the 54 successful cases are not repeated. The
final private run takes 0.337 seconds and reuses the verified native interposer.
No compiler or provider runs in either stage.

## Retained evidence and limits

Closed REA assembly Evidence
`ev_2d9050e4b74d2fcb39692d85337c3a372235cd44f4cf5d22ee74c047bb4c3f76`
covers the original complete span. Its retained carrier is 1,896,724 bytes;
the complete 198-line assembly facet compactly serializes to 6,682 bytes.
Those are historical retained-file measurements, not current REA transport,
model tokens or provider latency.

Private `.analysis/region-address-flow/` retains the complete proof, every
relocation, branch and producer consumer, unchanged test selection, initial
wrapper failure, final 36-case receipts and current input identities. Immutable
seal: `.analysis/checkpoints/region-address-flow-283-186/sha256.json`.

Source-present 283, scoped semantic 247, game exact 186 / 33,001 code bytes /
136 metadata bytes and origins 270/79/42/137 remain unchanged. No new acceptance
scope is inferred for a whole game from this owner audit. Original declarations,
full authored denominator, synchronized rendering and hardware audio remain
unproved. Reuse this correspondence instead of treating its address-scheduling
groups as missing source or recompiling to force a register order.
