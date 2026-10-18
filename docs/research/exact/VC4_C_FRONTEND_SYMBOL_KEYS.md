# VC4 C frontend symbol keys

The pinned C frontend has its own observed low24 ID writers and serializer
getter. This closes the static producer-location gap left by the
[actual C-source C2 comparison observation](VC4_EXPRESSION_ORDERING.md#c-source-comparison-observation-october18).
It does not yet connect a particular editor symbol's creation, emitted bytes
and C2 record in one execution. No source model or new exact claim follows
from the static locations alone.

## Target and retained evidence

`c1.exe` is 377,856 bytes with SHA-256
`7a7c14aff9631b9460a5666a8c344a5a177fce125ba3c4e9c2a4d57c7f402bb2`.
The new `scripts/rea compiler-session vc4-c-frontend --interactive` route
selects that attested tool and isolates its snapshot from C1XX, C2 and the game.
Twelve dispatcher and nine provider-free lifecycle cases pass, including
rejected target identity, accepted/fresh snapshots and unchanged existing modes.

One REA 6.5.0 / Ghidra 12.1.4 session retains 57 successful Evidence records
under private `.analysis/rea/vc4-c-frontend/runs/2026-10-18T04-03-49.682Z-interactive-649588/`.
The explicit profile disables `Apply Data Archives,Decompiler Parameter ID`.
The cumulative C snapshot closes normally. All eight complete byte carriers
match their own pinned PE mappings. Private
`.analysis/c1-serializer-frontier-20261018/` retains target checks, complete
responses, route tests, independent entry review, byte validation, resources
and logs. Reuse these observations before considering another cold import.

## Own-target chain

The actual `toil.c` literal at `44F728` has a code reference at `429858`, in a
cold block attributed to `417A6E`. That procedure's pseudocode follows operator
descriptors and writes the opcode and operands through the sink whose current
pointer is `45A3FC`. The `ilsink.cpp` literal at `4515D4` leads to the buffered
flush helper `4102D9` and other sink/error blocks; those helpers are not thereby
ID allocators. The formatter at `422A8F` also calls the same key getter at
`422BB4` and packs its result into a record buffer.

The operator block calls the C frontend's own `4180DB` at `407C81`. Its selected
hot path is unambiguous in instructions and bytes:

```text
4180DB  CMP [45662C], 0
4180E2  JZ 4401D7
4180E8  MOV EAX, [ECX+18]
4180EB  AND EAX, 00FFFFFF
4180F0  RET
```

With mode `45662C` zero, `4401D7` instead reads source `+14`. A nonzero packed
upper field returns that word shifted right by three through `431541`;
otherwise execution falls through into the separate cache/allocation path at
`4401E5`. The operator serializer also branches on the same mode. Its nonzero
mode writes a small key as a WORD and has a larger-key encoding path; the
formatter independently shows the low15 WORD/continuation-WORD form. These
are observed C1 paths, without transferring C1XX addresses or field formulas.

The mode's initialized PE bytes are zero. This is not the mode observed in an
actual editor compilation. Likewise, the earlier C2 keys 219 and 1178 are
actual C2 runtime values, not values read from a C1 object in this session.

## Actual low24 stores

Following actual C1 mode references reveals `41AA2A`, whose allocation path
stores kind9 and writes a key. Its counter is `455E14`. Following that
counter's reported references identifies two more independently decoded stores:

| Routine | Store | Source pointer | Observed behavior |
| --- | --- | --- | --- |
| `41859E` | `4185D9` | ESI, from incoming ECX | Allocates only when source `+18` low24 is zero; then links source through `45671C`. |
| `419A63` | `419AA2` | ESI | Allocates an object through `419BE5`, sets kind4 and assigns the counter. |
| `41AA2A` | `41AA8A` | EDI | Allocates a 44-byte object, sets kind9 and assigns the counter. |

Each selected assignment loads the old counter, increments `455E14`, and writes

```text
new_word = (old_word & FF000000) | (old_counter & 00FFFFFF)
```

The original high byte survives. Each path compares the counter with
`7FFFFFFF` and branches to a diagnostic path at or above that threshold. The
counter's initialized PE value is16; its value at arbitrary runtime points is
unobserved here. There are55 reported direct counter references. These three
stores are selected producers, not an enumeration of all writers, aliases,
object lifetimes or ordinary local-symbol constructors.

Primary getter assembly Evidence is
`ev_4bfac4ab4d3f5bfa64221472a6349e9ab33867d6baecc9e8f88300b753af2abd`.
The operator byte window is
`ev_9d42831bc0f1f7166a6cbf585197e3b6e2596101e69095d1fce4aea2e06b4095`.
The lazy writer assembly is
`ev_02627235757ba56e842167de284ba374398f2a6595594ed86dcaf4737562bbce`;
the other writer assemblies are
`ev_695ba9200492266ed3f49c8710fe84e618e961d96d58520a75455511b5f19eff`
and `ev_8292d3aac66f4e9f422af1ff07857e032909384fa1a808a866acb694609363ed`.

Imported ownership is fragmented. For example, `4180DB` owns40 bytes across
three ranges rather than its164,106-byte enclosing span. `417A6E` has409
imported bytes, while decompilation follows shared switch bodies outside those
ranges. Reconnect actual instructions and branches; do not interpret a span
or pseudocode listing as complete procedure ownership. Retained decompiler
stack-constraint warnings further limit inferred local variables and signatures.

## Validation and next question

Before the documentation update, all849 protected canonical hashes other than
the two reviewed route scripts remain unchanged. The published checkpoint also
changes the existing REA and handoff notes, leaving847 other baseline hashes
unchanged and adding this research note. No game source is staged, compiled,
relinked or replayed.
Authored coverage remains250 exact/20 candidates, and the tested delivery keeps
SHA-256 `d5dca81954937a6f9f3212fb041a1aed02f455b037dea0d9b7997a19a98587f6`.

The retained wrapper metric for the first query is260,506 ms; warm queries reuse
that one import. The whole
795.694-second scope retains CPU0/35%, memory high384 MiB/max512 MiB and the
256 MiB Java heap. Peak memory is403,206,144 bytes. The5200 soft-high reclaim
events are retained explicitly; hard-max and OOM counters remain zero. The
owned temporary project is removed after normal close.

Independent passive review verifies all57 original records, eight PE byte
carriers, selected chains and847 current baseline hashes. All88 archived
members pass size/SHA-256 verification before ten disposable copied inputs,
test helpers and logs are removed. Sharing the byte-identical closed catalog
with its retained C++ carrier releases8,769,536 allocated bytes net after the
archive and manifest cost. Full observations, the current snapshot, small
receipts, tested game products and useful incremental caches remain.

The next concrete observation is C1 runtime mode and source-symbol identity at
this getter/serializer during the unchanged editor compile, followed by the
actual relevant writer and emitted-record relationship. A selected writer is
not yet known to produce `i` or the hit-region count. Original-game IDs and
declarations remain separate questions; these locations do not justify blind
name, order, type, scope, flag or owner variants.
