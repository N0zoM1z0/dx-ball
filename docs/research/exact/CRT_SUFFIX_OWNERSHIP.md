# CRT suffix byte ownership and continuation extent

The declared original `.text` suffix `0x416610..0x41FEEB` contains 39,132 bytes.
A bounded review compares its gaps against the independent function inventory,
the separate parent-owned fragments and existing complete CRT section proofs.
It reuses the retained original bytes; no compiler or provider runs.

Before correction, 193 uncovered runs total 2,330 bytes. Nine runs contain
non-CC bytes. Every such byte belongs to one of seven already matched approved
CRT sections, rather than supplying a new authored-function hypothesis:

| Original section owner | Address | Complete section bytes |
| --- | --- | ---: |
| `trnsctrl.obj`, continuation transfer | `0x4184A0` | 53 |
| `87trig.obj`, trig kernels | `0x418960` | 43 |
| `87triga.obj`, arctrig kernels | `0x4192A0` | 162 |
| `87sqrt.obj`, sqrt kernel | `0x419350` | 27 |
| `exsup3.obj`, signature/handler section | `0x41C71C` | 224 |
| `87disp.obj`, common dispatcher | `0x41CA30` | 458 |
| `87tran.obj`, transcendental kernels | `0x41CC00` | 519 |
| Total verified section bytes | | 1,486 |

The full original section hashes and member identities are current. The cached
provenance's 121 input identities verify; the later arctrig/sqrt full-section
receipts supply their two code owners. No full library scan is repeated.

## One corrected function extent

The continuation-transfer inventory entry at `0x4184A0` previously stopped after
46 bytes at its indirect jump. Its original COMDAT is 53 bytes and contains a
seven-byte fallback epilogue at `0x4184CE..0x4184D4`: restore EBX, ESP and EBP,
then RET8. The entry now covers all 53 bytes through `0x4184D4`.

The additional bytes overlap no other independent entry or compiler fragment.
The complete section was already independently matched, and the current
delivery already includes it. No live edge to this otherwise unowned tail is
invented. Its source, machine interface and exact acceptance remain open; it is
one of the approved original CRT dependencies. No additional function is counted.

## Gap classification and limits

| Byte class outside function/fragment spans | Before | After extent correction |
| --- | ---: | ---: |
| Bytes in completely matched CRT sections, excluding signature | 821 | 814 |
| Original `VC20XC00` signature data | 8 | 8 |
| Remaining CC-only bytes outside those sections | 1,501 | 1,501 |
| Total | 2,330 | 2,323 |

The signature is the first eight bytes of the original `exsup3.obj` section;
the named handler begins at section offset eight. It is not a new procedure.
The other unassigned section bytes include assembler dispatch entry labels
and shared bodies. Full-section ownership does not turn each label into an
independent function or authorize a C prototype.

After correction, 193 runs remain; eight contain non-CC bytes, all covered by
the existing CRT sections. There are no residual non-CC bytes outside the
matched owners in this reviewed suffix. CC-only runs are reported as bytes,
not proof that an unseen entry or special trap routine cannot exist.
This is byte ownership, not a final function inventory, authored denominator,
whole-program semantic proof or new execution evidence.

Current no-source receipt coverage remains 78/78, with the continuation entry's
size updated to 53 in `.analysis/crt-suffix-ownership-20261017/coverage.json`.
Inventory 553 / parent fragments 24 / source 475 / exact 380 / complete candidates 95
remain unchanged. All source, ABI, implementation, match and semantic records,
objects, approved members and the current image remain unchanged except for the
single inventory extent/notes correction. No build, runtime or replay follows.

The code observation is retained REA Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
Private `.analysis/crt-suffix-ownership-20261017/` retains both gap maps,
seven section authorities, every byte classification, before ledgers and the
extent adoption. The earlier [dependency coverage](CRT_DEPENDENCY_INVENTORY.md#complete-receipt-coverage)
and [authored prefix review](../../agent/HANDOFF_HISTORY_20261021.md) retain their own boundaries.

## Joined declared text coverage

A subsequent receipt audit joins those boundaries across the original `.text`
section, without compiling, decoding instructions or opening a provider session.
The section is the PE's only section marked executable. Its declared extent is
`0x401000..0x41FEEB`, or 126,700 bytes:

| Range, end exclusive | Bytes | Reconciled coverage |
| --- | ---: | --- |
| `0x401000..0x416600` | 87,552 | 289 complete source comparison spans; 2,145 CC gap bytes |
| `0x416600..0x416610` | 16 | Two existing six-byte import thunks; four CC bytes |
| `0x416610..0x41FEEC` | 39,132 | Current inventory/fragments and the matched CRT sections above |

The bridge bytes are `ff252c124400ff2534124400cccccccc`: the existing
DirectDrawCreate and DirectSoundCreate import receipts bind the first twelve
bytes. The four remaining bytes complete the interval between the earlier
reviews. All 475 source-present entries have their original target-span hashes
checked against their retained complete comparisons. The current 553 inventory
entries, 24 parent fragments and 78 complete no-source receipts reconcile with
those spans; no source or exact acceptance changes.

Across these coverage bases, 4,472 bytes lie outside declared entry spans:
814 belong to already matched CRT code sections, eight are the runtime signature
and 3,650 are remaining CC bytes. No non-CC gap byte lacks an existing owner.
This closes the address-range join, not the final independent-function inventory:
possible interior entries, raw section tail semantics and data used as code are
outside the claim. Source-present no-op `0x40CC20` still has unknown authorship;
all 34 authored candidates remain nonexact. Source optimality and complete game
behavior are not established by this byte audit.

Private `.analysis/declared-text-coverage-20261017/proof.json` retains all 475
target span hashes, segment arithmetic, bridge authorities and input identities.
The current game image remains unchanged. The original50 producer described by
that historical audit is now terminal; see the current handoff.

## Incoming references to declared game bodies

A subsequent review covers all270 classified authored functions:259 retained
REA dossiers plus eleven missing incoming-reference facets queried with6.5.
There are1,149 observed incoming sites after excluding51 self-body sites from
the new facets. Every observed non-entry destination is one of190 DATA sites
whose source lies inside the same owner's enclosing span. No observed external
call or jump enters a declared game body at a non-entry address.

This narrows the interior-entry question for those declared Ghidra bodies only.
Body-excluded or undeclared entries, unresolved computed flows and runtime-only
destinations remain open. It establishes neither the final authored denominator
nor original declarations, source optimality or new exact acceptance.

Private `.analysis/game-entry-reference-review-20261017/complete.json.gz` retains
every selected Evidence ID, input digest, body range and edge. The eleven new
records are archived in REA run `2026-10-17T04-26-55.759Z-requests-2339124`;
the session closes normally with exit0. Its whole-tree cap is35% of one CPU,
memory high640 / max768 MiB. Sampled peak is about641 MiB with high-water reclaim
events, no sampled max/OOM event. No compilation, game, relink or full replay
runs; protected source/manifest/ledger/report/image identities stay unchanged.

## Original PE code-address relocations

The original HIGHLOW directory provides a second view of addresses that can be
absent from Ghidra's declared instruction bodies. Two REA6.5 reads capture the
1,024-byte headers and10,752-byte relocation section. Its declared9,424-byte
directory contains36 blocks,4,556 HIGHLOW words and12 ABSOLUTE padding entries.
All1,328 captured bytes after the declared directory are zero.
The captured headers declare no PE debug directory or COFF symbol table. These
bytes supply no additional producer-context hint; this is not a whole-artifact
absence claim for nonstandard debug information.

Of those words,249 point into the game-code prefix `0x401000..0x4165FF`:

| Destination context | Words |
| --- | ---: |
| Already inventoried independent entries | 12 |
| Existing internal DATA references | 190 |
| Declared C++ exception metadata targets | 21 |
| Embedded table/selector addresses outside the observed instruction bodies | 21 |
| Registered parent-owned C++ handlers | 4 |
| Unselected final brick-hit switch slot | 1 |

The four registered handlers match all40 bytes of their actual current compiler
sections. Each loads its parent's FuncInfo into EAX and jumps to the proven
runtime `__CxxFrameHandler` at0x418570. The21 metadata targets comprise the20
retired cleanup entries and the division parent's existing conditional-return
cleanup at0x40B346. These additional parent blocks were already included in
complete source comparisons; the24-row fragment ledger records retired
auto-analysis rows, not every internal entry. Its accounting stays unchanged.

The final switch word at0x41241B points to0x4123BA. All twelve table words and
23 selector bytes agree with the current compiled candidate; selector index11
is never used. No unexplained address word or additional independent entry is
indicated by this set. No HIGHLOW word targets the16-byte unknown no-op40CC20;
its origin and active use remain unknown.

This is a loader-relocation audit, not proof of runtime execution or a final
function denominator. Relative/computed/unrelocated addresses remain outside
its scope. Source optimality and all34 authored nonexact functions stay open.
No compilation, complete-function comparison, game, relink or full replay runs;
current source, ledgers, reports and the50e40609… image remain unchanged.

Private `.analysis/pe-game-entry-relocations-20261017/` retains the site inventory,
original raw Evidence references, handler/table proof and protected identities.
Header Evidence is `ev_bf17f7be59c5dfb453a8ba6c17f10a47eae91d94a1d7863d6c565b8fe1048544`;
relocation Evidence is `ev_c53664744e198041fb44d9e5b75e547c264526576edaf212311da5dd2b276968`.
Both are archived in run `2026-10-17T04-51-12.726Z-requests-2428519`; the session
closes normally. Reuse this result for the unchanged original directory.

## Direct transfers in the declared game prefix

The next review accounts for the complete declared spans of all289 prefix
entries:270 authored,18 compiler-generated and the existing unknown no-op.
It reuses281 REA assembly records and queries only eight missing assembly
facets with6.5. Raw instruction lengths and immediate destinations are checked
against the verified original; this is not a source recompilation or exact replay.

The spans contain23,469 instruction sites /84,151 instruction bytes and1,256
embedded data bytes. Together with the previously verified2,145 CC alignment
bytes, they cover the87,552-byte prefix `0x401000..0x4165FF`. Data is kept out
of instruction decoding. The1,925 bytes omitted from the selected Ghidra bodies
are350 bytes of E9 sequences, one15-byte zero-store/jump block,304 bytes of
known C++ parent tails and the1,256 embedded bytes. The parent tails comprise
the24 retired fragment rows, four registered handlers and the existing19-byte
conditional return cleanup; they add no independent definitions.

All3,719 direct transfers resolve:1,253 to catalogued entries and2,466 to
instructions within the same complete parent span. This includes34 transfers
to previously body-excluded cleanup/epilogue blocks. No unclassified direct
target or additional independent entry is indicated by this set. The16 declared
switch tables contain191 original address words and492 selector bytes; every
word points to a known same-parent instruction and every selector value fits
its declared table. This does not prove runtime index bounds. Of335 originally
indirect transfer sites,16 are these table jumps and142 use declared import
cells. The remaining177 calls use register-relative memory operands; their
actual runtime destinations are not established here.

Neither direct transfers nor these table words target40CC20. Its authorship
remains unknown. Targets originating outside this prefix, dynamic call values,
alternate/overlapping code and runtime-only entries remain outside the claim.
The final authored denominator, source optimality and the34 nonexact authored
functions stay open. Do not repeat this walk for the unchanged original prefix.

Private `.analysis/game-prefix-direct-flow-20261017/` retains compressed
projections, all selected Evidence identities, original bytes, protected input
digests and verification. New records are in REA run
`2026-10-17T05-31-39.105Z-requests-2553246`; for example, the0x403E50 assembly
is Evidence `ev_f9ac2b28893c4acc5a9e0bfdcbbacfff1aea2f05b5d1723c34053ca633f5d6fa`.
The session closes with exit0 and58 cumulative Evidence records. Sampled peak
is640.5 MiB under the35% CPU /640 MiB high /768 MiB maximum scope, with
high-water reclaim and no sampled hard-limit/OOM event. Verified compression,
immutable sharing and redundant-alias removal release about19.09 MiB. All116
current source objects,19 approved CRT members and full compiler inputs verify;
source, ledgers, reports and current game image stay unchanged. No compiler,
game, relink or full replay runs.
