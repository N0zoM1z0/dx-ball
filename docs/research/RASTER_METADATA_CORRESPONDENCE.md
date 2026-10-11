# Triangle metadata and complete instruction correspondence

The triangle candidate can again compare its entire 1,710-byte span and attached
160-byte exception metadata. Its data descriptor contained stale generated
names although the code already used the current root. Eighteen metadata names
are reconciled through actual COFF definitions. All 17 relocations retain their
original targets: one interior unwind-map pointer and sixteen owner-local
cleanup labels. No source, compiler flags, relocation targets, extents or
comparison rules change. Complete metadata matches; code keeps 107 unmasked
differences and remains nonexact.

The matching root and each interior/local definition are checked against the
correct earlier fixed-point compiler object and original bytes. The original
FuncInfo header and whole unwind map are independently covered by the retained
288-byte observation starting at `0x4202A0`, Evidence
`ev_6c6c33dc195917063f7db16dfa2c0358a9df49960944255f739688593df6d089`.
Both descriptor size and owning code/data sections are preserved; symbol
ordinals alone do not establish identity. The later raster-controller object
already exposes the stale descriptor and is not used as a valid metadata anchor.
Historical byte/behavior results retain their scopes rather than being rerun
or rewritten as fresh observations.

## What accounts for the remaining code differences

All 482 decoded original/current instructions occur at identical offsets and
have the same widths. Their control-flow destinations correspond. A bijective
mapping covers 37 frame references, keeping all nine argument offsets and
three frame-control offsets fixed. Every other instruction operand corresponds
under that explicit mapping except four signed comparison groups.

Those groups load and compare opposite operands, then use opposite ordered
branches. Two test the upper scan bound and two the lower bound. Original
`upper_bound <= scan_y` and current `scan_y >= upper_bound` both exit the loop,
including signed extremes. A matching destination alone would be insufficient:
the comparisons leave different EAX values and arithmetic flags.

Successor liveness checks show that these differences are not subsequently
consumed. The complete, byte-exact 30-byte fixed-point conversion overwrites EAX
before reading it. Each of sixteen mapped nine-byte owner cleanup funclets calls
the complete, byte-exact 22-byte destructor. That destructor neither reads nor
writes EAX, so those calls preserve the residue without consuming it; the later
caller overwrites it. Arithmetic flags are also overwritten before consumption.
These effects are established from the actual bodies, without assuming that an
opaque call always kills a register. Ordinary control flow, actual call targets,
frame references and complete cleanup/handler/continuation code remain explicit.

This is an explanatory structural correspondence, not byte-exact acceptance or
recovery of original variable names/declaration order. It does not mask the 107
remaining bytes. Ghidra's 1,542 owned bytes and the 168 shared cleanup, handler
and plain-RET continuation bytes remain distinct. Complete exceptional-unwind
execution, indirect game use and physical graphics behavior are unproved.

## Validation and continued work

The nine accepted raster units, including all 136 accepted metadata bytes,
compare completely against the existing verified object. All 186 current exact
identities and production hashes remain valid. The global exact manifest hash
is refreshed after the candidate-only metadata correction; source/object input
hashes and accepted unit descriptors stay unchanged. Source presence 283,
scoped semantic acceptance 247, exact code 33,001 and origins 270 authored /
76 runtime /42 generated /140 unknown are unchanged.

There is no new compiler, provider or runtime invocation. The previous animation
checkpoint's actual runtime result remains attached to its unchanged library.
No historical game/raster suite is rerun. A bounded read-only frontier of small,
equal-size candidates finds no new CMP-immediate or MOVSX/MOVZX differences;
this is not a complete residual source audit. Resolve another concrete source,
call or storage discrepancy rather than trying identifiers or frame layout.
The full authored denominator and near-complete original source remain unproved.

Original triangle dossier: Evidence
`ev_ad1b11b19724c19c9001ac422c47b0b3b83c6b2965625e31729f969414a6467a`.
Full 168-byte continuation: Evidence
`ev_4af9d8adb831616c11cd7ebb0df5dd4803ee50949a47e165dce19938e3284bb0`.
All reused records bind original SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
Private proof: `.analysis/raster-metadata-reconciliation/`; seal:
`.analysis/checkpoints/raster-metadata-283-186/sha256.json`.
REA 6.3.0 remains official npm latest; feedback 41 appends only to the existing
`/tmp/dxball_rea_feedback_20261010.md`.
