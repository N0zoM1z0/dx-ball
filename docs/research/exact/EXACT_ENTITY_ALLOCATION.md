# Entity allocation and explosion phase boundaries

The particle, bonus, explosion-request and brick-animation owners now call the
actual shared operator-new/delete APIs. Their list ownership, failure exit and
untouched payload behavior remain unchanged. Together with the preceding ball
checkpoint, every maintained queue append/remove body uses the genuine runtime
allocation chain. The explosion-phase extraction also calls actual RNG, bonus
production and sound APIs, agreeing with the already recovered full game frame.

## Original evidence

Seven complete retained REA dossiers provide six list routines and the original
frame at `0x40F8B0`; its Evidence is
`ev_5d1d8d47e797530fa172e492b60eebe40dcf8a855a6d9125eb644dccb2e15d43`.
Original append calls target operator-new `0x416770` and fatal
exit `0x417910`; removal calls operator-delete `0x416760`. Complete 220-byte
removal spans include the five-byte internal jump outside the 215 Ghidra-owned
bytes. The existing whole-span append-explosion attestation at `0x412470` also
establishes both direct edges independently of a new provider query.

| Entry | REA Evidence |
| --- | --- |
| `0x40FF50` remove explosion | `ev_1538f8576bc2c7b207799609630f986e3933507a8a2a23a9a16767404a1a93d4` |
| `0x412690` append brick effect | `ev_6a32fd651ca3a7fb5d9cfda71f66a09b545b0a7baf59e584310935a7953e64af` |
| `0x413D80` append bonus | `ev_4fc477413a3cc27f679939d9c009896ebe04d9188e4302c056852028388321a9` |
| `0x4147C0` remove bonus | `ev_b1a3e59b2e4a28cee43842cefa27a736625c049bade614e71c11c6e452e3e0a1` |
| `0x414960` append particle | `ev_f0a14ca1d6a7e5734bfb86fbda96ab6446e8053561c412ff5119c3b3cd76559c` |
| `0x414B30` remove particle | `ev_e30c638667b1f7ce3a2fef6c243992dda3d59bad3a57a76cf426638f84129055` |

At `0x40FAF6`, the original frame calls RNG(5) before reading the live request
coordinates for bonus production at `0x40FB14`. Pending explosion sound uses
RNG(3), stop and play at `0x40FB60/0x40FB72/0x40FB87`. The maintained extraction
retains its meaningful consumed RNG result and live request reads while using
these genuine APIs. It remains an extracted phase, without a separate original
function or exact claim. Generic allocation/free bridges remain available for
existing fixture compatibility; authored queue bodies no longer call them.

## Matching

Four stable VC4 source compilations preserve all 28 affected accepted units and
their 5,400 complete code bytes. Every relocation, consumed literal and generated
label is checked. Replacing an allocation bridge changes the link identity to
the actual shared implementation at the same reviewed target and ABI. Existing
nonexact candidates remain nonexact; the three newly configured removal bodies
are each 208 object / 220 original bytes with 52 full-span differences. No locals,
names, declarations, padding or assembly are tuned to force a match.

Actual recursive project closures are gameplay 19, effects 18, particles 14 and
bonuses 22 files. All are covered by 28 declared inputs per build. Explicit
allocator, sound and RNG-owner headers declare the restored calls; existing
shared headers are unchanged. Global totals remain 171 exact functions / 30,744
code bytes / 136 metadata bytes, 283 source-present and 247 scoped semantic rows.

## Runtime and product evidence

Selected maintained vectors and unchanged assertions pass on the final native
library: 1,085 entity calls, 264 effect-list calls and 288 separate explosion-phase
frames. Entity selection covers append/begin/advance/remove, fatal allocation,
all nineteen bonus selectors with existing rare/reduced/corner vectors, retirement
and drawing. Effects cover append, fatal allocation and every live cursor for
lengths 0..8. Phase frames select existing lengths 0/1/3, all four pending values,
busy/unoccupied states and twelve successive frames. Native is checked against
unmodified original x86 with the maintained controlled dependencies.

Actual relocated VC4 bodies pass the same vectors and produce identical per-case
trace hashes. Internal COFF jump-table labels resolve to their emitted section
offsets, keeping bonus selection inside the compiled body. Explicit original
bindings remain the authority for external calls and complete literal contents.
For connected phase checks, the two emitted phase bodies execute consecutively
against the native reference already checked against the original frame. The
helper initially discarded first-phase events between its two calls; the old
assertion rejected that run. Correct aggregation retains the complete event
sequence. This was a private test transport correction, not a source workaround.

All checks retain ordered calls, globals, payloads, queue roots, live allocation
ownership and poisoned freed bytes. Original instruction storage stays unchanged.
Fatal native subprocesses now use the existing owned copied-image loaders and
typed owners, preserving the same expected exit status and failure cases after
direct runtime allocation replaced the callback bridge. Canonical native defaults
remain separately loadable; no process-wide libc interception was introduced.

Native/MinGW builds pass. VC4 reuses all four matching objects and 31 verified
unchanged objects, with no additional production source compilation. Resources
and SDK import libraries are verified and reused. Previous Wine play records
retain their own product hashes; no new game campaign, full-owner queue,
physical driver or asynchronous audio fidelity is claimed. Historical semantic
counts/scopes retain their identity after current input-hash refresh.

Private receipts: `.analysis/exact-entity-allocation/`.
Immutable seal: `.analysis/checkpoints/entity-allocation-283-171/sha256.json`.
REA was not reopened. Retained dossiers total 11,479,750 bytes; selected local
procedure/pseudocode/assembly projections total 41,676 bytes. Feedback entry 26
is appended only to the existing `/tmp/dxball_rea_feedback_20261010.md`; these
sizes do not measure current MCP transport, provider latency or model tokens.
