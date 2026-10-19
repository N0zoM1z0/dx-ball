# Signed source-row displacement

October20,2026. The shared renderer now interprets its existing DWORD row delta
as signed32 before adding it to the source pixel pointer:

```cpp
pixel += (DxBallInt)(source_desc.pitch - width + 1);
```

Width remains unsigned32 and descriptor pitch remains signed32. Their subtraction
and increment still occur modulo32. The final conversion preserves those bits on
VC4 and supplies the signed displacement when applied to a Native64 pointer.
The former implicit unsigned displacement moved backward rows nearly4GiB forward
on Native64. No dimension, loop, FP rounding, local, API, header or flag changes.
This recovers the target pointer operation without claiming original cast spelling.

Retained original Evidence
`ev_1dfa14e3428cac399a6bc2876da74d5bbc4a5edc8a8e03a6af79783e189daf26`
contains the actual sequence:402C12 loads source descriptor pitch,402C18 subtracts
sampled width,402C1E increments EAX, and402C1F adds its DWORD to the pixel pointer.
The update also executes after the final pixel. Existing rotation fixtures
explicitly restrict their source pitches to nonnegative values; their previous
acceptance did not cover this signed-pointer interpretation.

A finite witness uses width2,height2,pitch−4 in one32-byte source allocation.
The initial pointer is offset16. Original reads visit16,17,12,13; successive
pointer updates reach17,12,13,8. Even the final unused pointer remains inside
the allocation. All four distinct source colors reach the guarded destination;
the complete904-byte destination, ordered descriptor/lock/unlock events and
unchanged source, records, banks and both complete trig tables are retained.
The old Native64 library faults with SIGSEGV after starting the same call;
the recovered source matches the original complete result. Core dumps are disabled.
This is a controlled typed COM descriptor, not a physical-driver reachability claim.

Two initial original-only harness failures remain recorded. The first used an
unneeded hand-calculated destination expectation; the second exposed omitted
trig initialization and four writes to one center pixel. The corrected witness
uses the existing genuine original/native trig prelude and the complete original
destination as its oracle. Neither failure caused a source/compiler trial.

One complete VC4 rotation compile preserves all five raw and relocated code
identities,115 actual bindings and25 full literal references. All four exact
companions/900 bytes survive; renderer remains1458/1572 bytes with1466 strict
differences. The full40-byte `.rdata` is unchanged and matches the original
container at420038. Nineteen generated-symbol references change names; mappings
use actual offsets, whole payloads, targets, types, addends and multiplicities.
No ordinal-based binding or selective old object is used. Independent review
finds73 repeated-reference provenance annotations paired to the first equivalent
occurrence; the receipt alone is corrected to a115-row occurrence bijection.
Both versions remain retained, with no recompile or comparison rerun.

The canonical native build recompiles only rotation and relinks in0.892s;
38 other objects remain fixed. Current library SHA-256 is
`2fc51bd6c8272ebfe13f18dd572fe757cf234380ed7fb802f60b3bc1a4e1f19e`.
The negative-stride witness and nine selected unchanged calls pass: two baseline
entries and seven live-surface/bank/retry callback scenarios. The historical
full queue is not rerun. Existing semantic scopes/case counts remain unchanged.
The VC4 compile takes10.732s, peaks at167,174,144 bytes; the canonical native
build/check scope peaks at50,282,496 bytes. Both use CPU0/35%,384/512MiB with zero
high/max/OOM events. There is no provider query, game rebuild/run or full replay.

Private authority is `.analysis/rotation-signed-row-step-20261020/`, including
the source review, frozen single-cast proposal, complete objects/comparisons,
literal/provenance correction, retained old failure library and focused results.
Independent complete-result review SHA-256 is
`f24af3455d8f5ab9905917984c39faf52126ee1402421268065ee96dac669a3d`.
Overall counts remain392 exacts,247 authored exacts/23 candidates. Complete game
verification stays deferred while authored source recovery continues.

All270 authored receipts verify across30 current compiler closures. All249
semantic rows retain their ordered address/unit identities, scopes and counts;
235 input inventories and two owner-source hashes refresh. The shared manifest's
19 renamed literal bindings require a new digest reference in all392 exact rows;
only four rotation producers change. Tracking initially catches that omitted
global reference refresh, then passes after its correction without another
compile or replay. The independent final review records the actual native
results, producer identities and full ordered ledger comparison, SHA-256
`c73d7e58355d9d5fb5db89986448b19e77487dc7eb4d43a762d8ff64c57617b5`.

The36 closed copied inputs/products/helpers are archived and every member's
size/SHA verified before exact-list removal. The789,312-byte archive SHA-256 is
`7833acf909e702e198bfd46a9e79bba647a5043119ebe56d30f0c2acf1bb5938`.
Cleanup releases7,090,176 allocated bytes net including archive, manifest,
protected snapshot and receipt; all908 current protected identities verify.
Unique failures, current matching/native products, useful caches and the
historical tested game/ZIP remain intact. The latter products predate this
source change and both UI changes; no game acceptance is refreshed.
