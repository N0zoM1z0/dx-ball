# Runtime-library dependencies

Thirteen complete original function bodies agree with corresponding objects in
the hash-pinned VC4 **`libc.lib`** after applying every relocation. The comparison
covers **546 bytes** and checks four library variants independently: **52
function/library comparisons**. It supplies runtime-origin evidence, separate
from maintained C, differential cases and the configured exact units.

This batch resolved eight previously unknown entries. At its checkpoint, totals
were **14 identified runtime dependencies / 292 unknown origins**, with
maintained source at **222 functions / 105,036 direct cases / 36 exact units /
3,518 bytes**. See the [current handoff](RE_HANDOFF.md) for subsequent game-owner
acceptance. The three previously identified heap entries gain object-level
corroboration without another origin promotion.

The later [termination batch](TERMINATION_OWNER.md) adds complete quick-exit
and initializer-walker observations and whole-section comparisons, identifying
two further runtime entries. Current origin totals are **17 runtime / 276
unknown**. Its four maintained standalone functions and 1,031 direct calls are
separate semantic acceptance; game/host CRT integration remains open.

| Original entry | Defined COFF symbol | Whole body bytes |
| --- | --- | ---: |
| `0x0041678C` | `__ftol` | 39 |
| `0x00416760` | `??3@YAXPAX@Z` — operator delete | 14 |
| `0x00416770` | `??2@YAPAXI@Z` — operator new | 16 |
| `0x00417910` | `_exit` — the C `exit` function | 18 |
| `0x00417DF0` | `_strlen` | 119 |
| `0x00417750` | `_free` | 24 |
| `0x00417770` | `_malloc` | 20 |
| `0x00417790` | `__nh_malloc` | 64 |
| `0x004177D0` | `__heap_alloc` | 21 |
| `0x00419EA0` | `__callnewh` | 33 |
| `0x00417950` | `_doexit` | 128 |
| `0x00417930` | `__exit` — C `_exit` | 18 |
| `0x004179D0` | `__initterm` | 32 |

The leading underscore in `_exit` is COFF C-name decoration; this row refers
to `exit`, rather than the C `_exit` function. The latter has the distinct COFF
symbol `__exit`. The reviewed wrapper passes `(status, 0, 0)` to `_doexit`.

## REA instruction contracts

The [focused dependency review](DEPENDENCY_FRONTIER.md#focused-rea-instruction-review)
supplies five saved dossiers. Three matching heap dossiers are also reused.
A subsequent sequential REA session adds three bodies and complete byte reads
for all eleven entries, then closes and saves its snapshot. No original bytes
are patched, and existing matching function queries are not repeated.

Heap allocation Evidence
`ev_f6b1749c4f67167beacf3f0af7c69e992dc13304478a79c28a14e9278f719acc`
observes `HeapAlloc` with heap storage `0x00440D70`, flags zero and the requested
size. EAX is forwarded even though the inferred pseudocode return is `void`.
New-handler Evidence
`ev_f350f41184bab52523f0483486ead9de4bd0a0db5c326426842820aa5b3b20df`
reads the callback at `0x0043FB10`, skips null and normalizes any nonzero callback
result to one. The previously reviewed allocation loop retries only when its
handler flag and this result permit it; zero requests become one and unsigned
sizes above `0xFFFFFFE0` are rejected.

Termination Evidence
`ev_708cef33a373375bddd52f451b3dcb5c0c69e2fefd4e9cb94a8f8876f53e098b`
sets the termination-done flag and byte exit mode. Normal cleanup walks the
on-exit table backwards, skipping null entries, then invokes the pretermination
table. The termination table runs in both cleanup modes. When the return-to-
caller flag is zero, `ExitProcess` receives the supplied status. This is an
observed instruction contract; arbitrary callbacks and physical termination
services have not received a new runtime validation here.

`__ftol` temporarily selects x87 truncation and restores the control word;
the scanner returns a byte count and can read an aligned word beyond a zero
byte. Exceptional floating conversions, inaccessible backing and arbitrary
allocator/exit callbacks remain outside the maintained owners' existing
controlled dependency boundaries.

## Complete object comparisons

[crt-provenance.json](../config/crt-provenance.json) fixes the thirteen reviewed
addresses/extents, library candidates and explicit relocation map. The map
uses REA-observed call/data references: heap and handler state, Win32 IAT slots,
termination flags, callback-table bounds and the initializer-table helper.
The comparator applies each DIR32 or REL32 operand, including its addend, then
compares every byte. Unmapped relocations, overlapping fields and incomplete
extents are rejected; no relocation bytes are masked.

The object reader requires a defined function at section offset zero and a
complete code section containing one typed function. The assembly `strlen`
and `_ftol` objects use ordinary `.text` sections; the origin comparator accepts
those complete sections. The existing exact oracle still requires its dedicated
COMDAT sections. No exact-oracle rule or accepted replay input is changed.

| Pinned library candidate | Whole functions agreeing | Contradicting entries |
| --- | ---: | --- |
| `libc.lib` | 13/13 | None in this batch |
| `libcmt.lib` | 9/13 | `_nh_malloc`, `_callnewh`, `doexit`, `_initterm` |
| `libcd.lib` | 2/13 | All except `_ftol` and `strlen` |
| `libcmtd.lib` | 2/13 | All except `_ftol` and `strlen` |

The threaded `_nh_malloc` has the same section length but different compared
bytes; this cannot be dismissed as an extent difference. The results establish
compatibility with these pinned single-threaded release CRT objects for this
batch. They do not uniquely identify a historical compiler release, every
library in the executable or the complete original build configuration.

The private report binds selected archive/member hashes, all applied relocations,
target-byte hashes, complete REA records/close markers and the verifier inputs.
Evidence hashes are computed from the same bytes parsed, so replacing a record
cannot associate cached observations with a replacement file's identity.
The public rejection controls cover section tails, extra functions, internal
symbol starts, invalid relocations, wrong/missing mappings, truncated archives,
unrelated high-byte symbols and record replacement.

```bash
# On a fresh private checkout, collect the dossiers and whole-byte observations.
# Reuse matching closed REA records when already available.
scripts/rea session config/rea-crt-provenance.json
scripts/repo-python scripts/verify-crt-provenance.py

# Public parser/integrity controls require neither originals nor VC4 libraries.
scripts/repo-python tests/test_crt_library.py
```

The libraries, selected vendor objects and original byte observations stay
private. Maintained game source receives no copied vendor bodies. Host services
remain integration bridges until their broader behavior is independently
established; origin identification does not claim full game reconstruction.

## Unsigned score conversion dependency

The [game setup/score batch](EXACT_RUNTIME_SETUP.md) independently identifies
_ultoa at 0x41F570 (30 bytes) and static xtoa at 0x41F510 (96 bytes). Modern REA
owns both complete contiguous bodies and observes the explicit helper call,
zero sign flag, returned buffer and unsigned DIV. Complete dedicated sections
in pinned libc.lib agree with all 126 bytes, including the wrapper's single
REL32 operand bound to the separately observed helper. This establishes two
runtime origins (50 runtime / 166 unknown), independently of source presence,
maintained vendor bodies and configured exact compiler units. The checked Linux
score bridge supports unsigned32 decimal only; Windows supplies its real CRT.
Original compiler release and broader vendor runtime behavior remain unproved.
