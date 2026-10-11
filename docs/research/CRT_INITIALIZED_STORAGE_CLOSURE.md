# CRT code grounded by complete initialized storage

Nine independently placed initialized data sections resolve the dependencies
of 14 complete pinned VC4 CRT code sections, covering 22 previously unknown
inventory entries. All 2,897 new code bytes and 81 actual relocations agree with
the original. Origins become 270 authored / 105 runtime / 42 compiler-generated
/ 111 unknown. Game source 283, scoped semantic acceptance 247 and exact
acceptance 188 / 35,003 code bytes / 136 metadata bytes remain unchanged.

Each data section is nonzero, relocation-free and unique across the entire
original executable carrier. Its complete COFF extent independently determines
its original virtual address. Every byte then matches both the pinned PE and
a complete REA read. Actual section/value/storage definitions become available
only after the whole section passes; static names remain member/index scoped.
No code relocation is used to invent a data address, and zero-filled BSS is
outside this placement method.

| Base | Pinned member | Complete bytes | Selected definitions or purpose |
| --- | --- | ---: | --- |
| `0x4234D8` | `dosmap.obj` | 360 | Object-local error mapping table |
| `0x4230F8` | `exsup.obj` | 16 | `__NLG_Destination` |
| `0x4238B0` | `winxfltr.obj` | 140 | Exception action table, counts and status |
| `0x424390` | `constpow.obj` | 700 | `__pow10pos`, `__pow10neg` |
| `0x423FE8` | `intrncvt.obj` | 48 | Object-local float/double format records |
| `0x423EC0` | `87disp.obj` | 45 | Dispatcher constants and tag table |
| `0x423300` | `fpctrl.obj` | 28 | Object-local underflow/overflow constants |
| `0x420218` | `powhlp.obj` | 24 | Object-local floating constants |
| `0x4234A8` | `util.obj` | 40 | IEEE infinity, indefinite and limit constants |

The new complete code sections are:

| Section base | Bytes | Library definitions | Newly classified entries |
| --- | ---: | --- | ---: |
| `0x41A9A0` | 102 | `__dosmaperr` | 1 |
| `0x4183AC` | 238 | Unwind, abnormal termination and NLG helpers | 5 |
| `0x41F450` | 49 | `_siglookup` | 1 |
| `0x41D540` | 24 | `__ld12tod` | 1 |
| `0x41D560` | 24 | `__ld12tof` | 1 |
| `0x41FC40` | 123 | `___multtenpow12` | 1 |
| `0x41CA30` | 458 | `__trandisp1`, `__trandisp2` and interior entries | 5 |
| `0x4193F0` | 91 | `__set_statfp` | 1 |
| `0x41E540` | 127 | `__d_inttype` | 1 |
| `0x417FF0` | 77 | `__access` | 1 |
| `0x41BC10` | 72 | `__CallSettingFrame@12` | 1 |
| `0x41C71C` | 224 | Exception/SEH unwind helpers | 1 |
| `0x41E2F0` | 584 | `__powhlp` | 1 |
| `0x4198D0` | 704 | `__handle_exc` | 1 |

Nine first-round sections ground five second-round sections. A third round
finds none. A code section must match entirely, with actual current-section,
verified same-member or independent external bindings. An unverified sibling
section cannot provide its address. Code discovery finds no ambiguous address
in this scope. Imported inventory entries can be interior labels in a larger
CRT section; classification preserves their provisional extents and does not
claim additional authored functions or new prototypes.

Discovery parses 615 members and considers 1,503 initialized sections. Three
non-ASCII members and 1,107 unsupported `.debug$F` sections remain explicitly
uncovered. Of 38 new independent placements, 34 have full relocated equality;
only the nine consumed sections above are accepted. Unused constants/strings,
pointer-bearing partial placements and unlocated BSS stay diagnostic.

The unchanged maintained verifier passes once with the new candidate recipe:
83 complete code sections / 10,250 bytes / 95 distinct origin entries, 12 data
sections / 2,531 bytes and 272 actual member-scoped definitions. Two bounded
controls reject a shifted newly placed section and a partial data extent before
producing any acceptance report. The actual candidate-path receipt is retained
unchanged; the published recipe has identical bytes/hash, with that alias
recorded explicitly. No verification run is rebased onto unobserved inputs.

The complete original code observation is reused:
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
New data reads use one closed REA 6.3/Ghidra 12.1.4 session,
`2026-10-11T04-22-27.565Z-requests-1705272`; records `00` through `08` correspond
to the data table's order. The nine Evidence IDs are retained in
`rea-observations.json`, the published recipe and complete immutable payloads.
They include `ev_e5aea1b1fa43f15168514e949432e327c43794b19fce1f23c2a86fd6067c9f5c`
for the error table and
`ev_a01dd8e3af7a0724988d78b5474a52f88d81a656c93042dd541e84a26c621f19`
for the IEEE constants.

First read takes 59,037.66 ms; the other eight take 1.57–18.82 ms in that same
session. Total retained data carriers contain 33,105 bytes for 1,401 original
bytes. These are provider log timings and serialized file sizes, not model
token costs or measured token savings. The 512 MiB heap limit is configured;
a 498,752 KiB Java RSS sample is an observation, not a peak measurement. New
function dossiers or full historical snapshot replay are unnecessary.

No game source, maintained tests, compiler, production build or gameplay case
changes. All four current products retain the window-switch checkpoint's
identities. This proves bounded CRT provenance, not the unique original link
selection, a complete authored denominator, source declaration spelling or
synchronized rendering/audio fidelity. Remaining origin work needs new
independent BSS, pointer-storage or code authority instead of repeating the
unchanged final discovery round.

Private proof: `.analysis/crt-initialized-storage-next/`. Immutable seal:
`.analysis/checkpoints/crt-initialized-storage-283-188/sha256.json`.
All REA performance and usability feedback continues in the user's one existing
`/tmp` document. Only completed duplicate payloads may be cleaned after full
identity verification; unique evidence and current products remain.
