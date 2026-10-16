# CRT dependency inventory and omitted entries

The independent inventory now has **553 entries**, including eight omitted
CRT entry points. Source remains **475 functions / 380 exact / 95 complete
candidates**. This is an inventory correction, with no new function source,
exact acceptance or runtime case. The 24 parent-owned fragments stay separate.

All 270 currently classified authored functions have source: 236 exact and
34 complete candidates. The final authored denominator remains unproved.
The nineteen explicit original CRT members remain user-approved dependencies.

## Eight omitted definitions

Actual external COFF function definitions, type32, establish these distinct
entry boundaries. None overlaps a current independent entry or parent fragment.

| Entry | Address | Own bytes | Origin claim |
| --- | --- | ---: | --- |
| asin | `0x4175F0` | 10 | Runtime proved |
| acos | `0x4175FA` | 7 | Runtime proved |
| atan | `0x417601` | 7 | Runtime proved |
| __CIasin | `0x417612` | 10 | Unknown; dispatcher binding pending |
| __CIacos | `0x41761C` | 7 | Unknown; dispatcher binding pending |
| __CIatan | `0x417623` | 7 | Unknown; dispatcher binding pending |
| __CIatan2 | `0x41762A` | 10 | Unknown; dispatcher binding pending |
| __CIsqrt | `0x41764A` | 10 | Unknown; dispatcher binding pending |

The complete 24-byte asin/acos/atan control-flow group matches after all four
actual relocations. Selector addresses come from the independently located
176-byte operation-table owner; `__ctrandisp1` has its earlier complete 44-byte
proof. Acos and atan jump to the shared five-byte asin exit. Their own spans
do not count that exit twice. Existing scalar sqrt also verifies its complete
ten bytes and two bindings against the independent sqrt table/dispatcher.

All ten definitions in the 68-byte `87ctriga.obj` and 20-byte `87csqrt.obj`
sections decode completely. Their selectors, internal jumps and owned spans
agree with retained original observations. The intrinsic paths still require
`__cintrindisp1` or `__cintrindisp2`; the existing atan2 path requires
`__ctrandisp2`. Observed destinations supply no new binding authority.
The older atan2 origin row is retained, without newly authorizing that binding.
Neither whole member receives a new complete-origin claim.

The eight additions total 68 owned instruction bytes. Three add runtime origins;
five add unknown origins. Current origin totals are **270 authored / 248 runtime /
21 compiler-generated / 14 unknown**. Intrinsics keep their machine ABI; no
ordinary C replacement is invented.

The source data proofs remain in [operation tables](RUNTIME_X87_OPERATION_TABLES.md),
and the dispatcher proof in [the C-dispatch tail](RUNTIME_X87_DISPATCH_TAIL.md).
Reused REA bytes retain Evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
The independent arctrig table observation is
`ev_d7b5e3077aa89e06757c2366971896bffbded18b2eeb3e07f63c6486a8a3fafa`;
the earlier sqrt header observation is
`ev_f6a414600d6f4d61172f65edeb5491e6d910bbcfc248fad3ddebaba403ab32cc`.
No new provider query runs or old observation is restamped as a new one.

## No-source entries and approved carriers

There are now 78 inventory entries without source. Three are platform import
thunks: DirectDrawCreate, DirectSoundCreate and RtlUnwind. The other 75 associate
with text regions in sixteen of the nineteen approved members:

| Approved member | No-source entries | Origin still unknown |
| --- | ---: | ---: |
| fpctrl.obj | 4 | 0 |
| exsup3.obj | 2 | 0 |
| exsup.obj | 5 | 0 |
| trnsctrl.obj | 7 | 0 |
| adj_fdiv.obj | 22 | 0 |
| chkstk.obj | 1 | 0 |
| frnd.obj | 1 | 0 |
| ftol.obj | 1 | 0 |
| 87ctriga.obj | 8 | 4 |
| 87ctrig.obj | 6 | 3 |
| 87csqrt.obj | 2 | 1 |
| lowhelpr.obj | 1 | 0 |
| 87triga.obj | 2 | 0 |
| 87trig.obj | 0 | 0 |
| 87sqrt.obj | 0 | 0 |
| frame.obj | 0 | 0 |
| 87cdisp.obj | 7 | 5 |
| 87disp.obj | 5 | 0 |
| 87tran.obj | 1 | 0 |

Zero rows concern this inventory only; they do not authorize removing a member.
Member offsets and hashes remain in `config/restored-crt-link.json`.
The audit verifies the current nineteen members and reuses cached provenance
with all 121 input identities intact, rather than repeating the library scan.

Carrier association is weaker than a complete original comparison. This audit
has complete function/section/group or import receipts for 59 entries. Nineteen
have only region associations here: thirteen retain unknown origins; the other
six retain earlier runtime labels without a new full-body proof. Those six are
atan2 and the five C++ handler/catch/translator entries at
`0x418570`, `0x4185B0`, `0x418620`, `0x418650` and `0x418730`.
No association promotes source presence, origin or exactness. The other unknown
origin is the already source-present `0x40CC20` no-op.

## Five recovered existing identities

Existing full-member receipts and current selected-member payloads identify:

| Address | Actual COFF identity | Complete bytes |
| --- | --- | ---: |
| `0x419370` | __statfp | 17 |
| `0x419390` | __clrfp | 18 |
| `0x4193B0` | __ctrlfp | 52 |
| `0x4193F0` | __set_statfp | 91 |
| `0x41F8C0` | __frnd | 21 |

Their existing runtime origins stay unchanged. The 91-byte body retains all
three independently grounded relocations; the other four are relocation-free.
These names restore neither source nor an ordinary-C ABI for physical helpers.
The 91-byte body's earlier initialized-storage authority remains in
[the storage closure](../CRT_INITIALIZED_STORAGE_CLOSURE.md).

## Closed constant-view pilot

One private core compilation tests an immutable typed pointer view of the
existing explosion-list member. The owning object, mutable state, offsets and
all executable source bodies stay unchanged. VC4's current C recipe retains
ten alias-cell references; game-frame grows from 1,691 to 1,705 bytes. The alias
cell has no original binding authority and is never assigned a fictitious
address to force a comparison. Reject the model without compiling other owners.

All eleven object bodies are retained. Ten complete original comparisons
preserve the nine accepted companions' 4,659 bytes; the game-frame's unbound
new cell is reported separately. No alternate profile body, flag or identifier
sweep follows. Canonical source/header/cache/image remain unchanged.

Private `.analysis/arc-entry-inventory-20261017/` retains all eight entries,
complete scalar comparisons, unresolved bindings, data/dispatcher receipts,
78-entry coverage, ledger adoption and input identities. The pilot is retained
in `.analysis/explosion-constant-view-20261017/`. No full replay, game run or
new game build accompanies this audit. REA remains pinned to 6.5.0. This does
not establish final inventory completeness, all origins or full game fidelity.

Thirty-five frozen inputs/reports and both pilot objects are archived with
complete byte checks, releasing 5,648,384 allocated bytes. Current objects and
the linked image remain available. All heavy work is serial under CPU 35%,
memory high 640 MiB / maximum 768 MiB. Remaining runtime origin questions do
not reverse the dependency approval or become a delivery gate; authored exact
work remains the priority.
