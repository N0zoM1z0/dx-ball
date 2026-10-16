# Rotation pixel-address evaluation

Both renderer writes now form the integer row-plus-column offset before adding
the destination pixel base. This follows the original address computation,
while keeping the maintained types, dimensions, guards and pixel writes.

```c
destination_pixel = destination_desc.pixels +
    (rounded_y * destination_desc.pitch + rounded_x);
```

The second write substitutes truncated Y and still uses rounded X. The original
first loads Y, multiplies by pitch, adds rounded X, then adds the pixel base.
The maintained multiplication still loads pitch first; that commuted product
and frame/register allocation remain unresolved.

One eight-input VC4 compilation compares all six complete rotation functions,
including every relocation and referenced literal. Only four ADD memory
operands change, across eight bytes: the column and base additions exchange
order at the two writes. Every other instruction byte stays unchanged. All
365 instructions and the 424-byte frame remain. The renderer stays
**1466/1572 bytes with 1466 differing positions**; raw differing positions do
not reflect this restored dependency order. This is not an exact acceptance.
Four exact companions retain 749 bytes, and the height candidate is unchanged.

The review reuses original REA Evidence
`ev_1dfa14e3428cac399a6bc2876da74d5bbc4a5edc8a8e03a6af79783e189daf26`,
operation 03 of `2026-10-07T10-33-32.118Z-interactive-2912559`, and the
[established frame roles](ROTATION_FRAME_ROLES.md). No provider query runs.

The existing 351 renderer and 344 wrapper cases pass once, including seven
finite-retry and live-surface/bank callback scenarios. They compare complete
guarded buffers, owner storage and ordered calls against the original. Their
bounded geometry, representable source arithmetic and normal division-path
scope remain unchanged; no semantic cases are added. The 235 historical input
inventories receive the source hash without rerunning their other cases.

The native incremental build compiles rotation and links the library; its
default target also refreshes the pending board inspector. The restored-CRT
builder reuses all 116 source objects and only relinks, retaining the same 19
approved original members. The renderer is absent from the `/OPT:REF` delivery
map. All 1,091 mapped addresses remain identical, and a complete image comparison
finds only twelve changed bytes inside six parsed COFF/resource timestamp fields.
All other image bytes and resource payloads are unchanged. No game runs again.

Current image SHA-256:
`844247ba7095eedbf99cc7e3bfeaf3ec43a4d232c1cb6b7fcfc2e68de8ed42be`.
Earlier GUI observations remain associated with their recorded image hashes.

Private `.analysis/rotation-pixel-address-20261017/` retains frozen inputs,
before/after objects, full comparisons, instruction/address proof, unchanged
fixture selection, input-ledger reversal and complete image verification.
Totals remain **475 source / 380 exact / 95 complete candidates**, including
34 authored candidates. There is no full replay or port work. Heavy operations
remain serial under CPU 35%, memory high 640 MiB / maximum 768 MiB.

## Complete renderer correspondence

A subsequent review pairs all 365 original/current instructions through their
actual operands, the established 424-byte frame map and complete relocation
bindings. All 22 direct/indirect calls agree; all 26 branch destinations map to
the same instruction ordinal. No partial-byte mask establishes this result.

| Instruction class | Paired instructions | Remaining difference |
| --- | ---: | --- |
| Ordinary operations | 285 | Operand identity after frame/branch translation |
| Eight sprite-bank address producers | 64 | Register allocation and equivalent scaled-address decomposition |
| Signed column-loop guard | 3 | Transposed operands and JLE/JGE |
| Unsigned source-column rollover | 3 | Transposed operands and JB/JA |
| Two row/pitch products | 4 | Commuted low-32-bit multiplication |
| Two row-origin updates | 6 | FLD coordinate/FADD step versus FLD step/FADD coordinate |
| Total | 365 | Complete instruction inventory |

Four bit-vector queries prove equal bank effective addresses, signed and
unsigned branch predicates, and low-32-bit products for all 32-bit inputs.
The eight address producers have identical graphs on each side, so one query
covers their repeated arithmetic. Equal addresses imply equal loads from stable
memory. Four separate expression mutants produce counterexamples. A CFG walk
also checks 36 scratch-register boundaries: the differing EAX/ECX/EDX values
are overwritten or leave through the normal void/cdecl/stdcall boundary before
being consumed. Source and destination memory remain ordinary mapped storage;
concurrent writes, arbitrary frame aliasing, flags residue and raw frame-pointer
identity are outside this correspondence.

The row additions transpose two finite operands and store the same coordinate.
This explanation uses the established normal masked floating-point environment;
it does not claim unrestricted NaN payload, status residue or trap-location
equivalence. There is no missing arithmetic, call, guard or branch in this
bounded correspondence. Frame/register allocation, original producer context
and the listed operand scheduling still prevent an exact result.

One isolated source control reverses only the two row-origin addition
expressions to follow the original load order. It emits identical complete raw
functions and relocation bindings for all six owner functions; their resolved
comparisons are also unchanged. Reject the control and do not repeat this
spelling trial. Canonical source, objects, image, ledgers and counts stay
unchanged. No native build/test, delivery relink, game or full replay follows
that result.

The first array-valued mutant query reaches its explicit five-second solver
limit after proving the unmutated load equality. That incomplete attempt is
retained. The completed proof compares the actual effective-address expressions
directly and obtains all four UNSAT/four SAT results; it does not treat timeout
as evidence of equivalence. No compiler or provider repeats for this correction.

Private `.analysis/rotation-row-origin-order-20261017/` retains the complete
instruction map, original dossier identity, address/guard/product queries,
scratch-boundary walks, rejected source/object and six-function comparisons.
This is analysis evidence, not a new exact or semantic acceptance.
