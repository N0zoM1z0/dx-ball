# Exact device initialization and calibration scope

Device initialization at `0x403A00` now matches all359 original bytes and
all28 actual relocations. Its five previously accepted startup companions
remain exact across1022 bytes. The total advances from188 to189 exact functions,
with35,362 complete code bytes and136 accepted metadata bytes.

The restored source makes two supported changes in
[`src/startup.c`](../../../src/startup.c): failure calls the process-exit routine
and returns directly, and the vertical-blank calibration counter belongs to
its own block. Descriptor initialization, successful call order, all32 blank
waits, unsigned timing subtraction and mode/particle state changes stay intact.

The retained complete original dossier contains80 instructions and one
contiguous359-byte body through the final return. The failure branch at
`0x403A5E` jumps directly to the common epilogue at`0x403B62`. The previous
outer `else` instead targeted the later success-return jump at`0x403B5D`.
Removing that wrapper and adding the direct failure return reproduces the
complete original branch topology, including the success-return jump.

The original120-byte frame contains two outer four-byte scalars, the108-byte
surface descriptor, and a four-byte calibration counter below that descriptor.
The previous outer counter was allocated before the descriptor and shifted
its actual fields. A nested counter scope reproduces the observed allocation
with meaningful typed storage. No name search, padding, extra operation,
machine-code patch or operand-spelling trial is used. Original identifier
spelling remains unknown; complete byte equality establishes this compiler
emission, rather than recovering original names.

## Compilation and validation

One canonical VC4 `/MT` startup compilation produces the match, using the
unchanged flags and16 recursive project inputs. All six complete startup
bodies are compared after independently declared relocations; no byte or
epilogue is masked. The matching object is also the actual production owner:
VC4 links it with35 identity-verified unchanged game objects. Native and MinGW
rebuild only the affected startup owner and dependent products. No second
legacy source compilation, Ghidra startup or full gameplay replay is needed.

The unchanged startup differential suite passes158 original/Native cases and
one connected device-dispatch check. Its83 device cases cover timing thresholds,
timer wrap, software/reduced-particle flags and two nonreturning failure cases
with independently observed COM outputs. Other cases retain score I/O, RNG and
bank-release coverage. This validates the existing defined descriptor fields
and dependency boundaries; it does not assert arbitrary driver aliasing,
uninitialized descriptor bytes, hardware display/audio or synchronized clocks.

All189 current exact input/object closures verify. Unaffected exact results are
reused only after their source/input/object identities agree. The247 historical
semantic scopes and case counts remain unchanged;235 input closures refresh
after the shared source change. Only the startup suite is rerun. Origin totals
remain270 authored/115 runtime/42 compiler-generated/101 unknown, and source
presence remains283. Whole-game fidelity and the complete authored denominator
remain open.

## Retained evidence

Saved original REA Evidence:
`ev_8681cf5b5b27dd9358b476476e4b5b63d76ccbb091fc483c58c3cea670a6e1db`.
Its complete dossier and target digest are reverified, with a retained terminal
session receipt; no new provider request is required. Private
`.analysis/startup-calibration-scope/` retains before identities, the single
compile receipt, complete comparisons, unmodified test result, actual link
inputs, product identities and final review. The new checkpoint owns current
products independently of public paths and references large prior carriers
without copying them.
