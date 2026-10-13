# CRT exit registration and entry wrappers

Two maintained registration bodies now share the termination owner's actual
begin/end globals and the recovered heap-size/realloc boundaries. Three entry
wrappers are complete exacts; registration and the existing walker are candidates.

| Entry | Original/current bytes | Differences |
| --- | ---: | ---: |
| `_onexit`, `0x41F7E0` | 121/121 | 2 |
| `atexit`, `0x41F860` | 19/19 | 0 |
| `exit`, `0x417910` | 18/18 | 0 |
| `_exit`, `0x417930` | 18/18 | 0 |
| `_initterm`, `0x4179D0` | 32/32 | 6 |

Registration first queries current heap capacity, then rereads shared bounds.
Insufficient space triggers a second capacity query and growth by four callback
slots. Reallocation failure returns null without publishing a new table.
Successful growth rereads shared addresses after callbacks, preserves the
whole-slot offset, publishes begin before end, then appends and advances end.
Null callbacks are still appended; atexit reports failure from the null return.
There is no invented initial allocation or extra overflow policy.

The API retains VC4's int-returning `_onexit_t`, distinct from void initializer
callbacks. Explicit legacy cdecl function-pointer conversions share the existing
result-discarded slots; registration does not invoke callbacks. Slot width and
four-slot growth expand on the supported native pointer ABI. Address arithmetic
is explicit, including the post-realloc reload; it is not subtraction through
freed array storage. Backed, aligned shared tables and representable requests
remain required; bootstrap allocation and broader teardown integration are open.

All121 bytes except the comparison opcode/branch match, with every14 actual
binding covered. An explicit common append guard leaves the same two differences
and is a closed trial. The unchanged walker has six ESI/EDI register differences.
Normal/quick wrappers retain their actual three arguments and call target; all
36 bytes and both bindings match. Atexit19 and its one binding also match.
The existing cleanup controller retains its documented portable cdecl platform
bridge and has no new exact claim. Wrapper exactness does not close that backend.

The new closed REA run `2026-10-13T15-31-15.686Z-interactive-1778538` retains six
info/pseudo/assembly records. Registration assembly:
`ev_cd653b68a2a67d545be2b4256f898e06775c644f44f51332dfd8105ef3aae8a0`;
atexit assembly:
`ev_8e8d8d02968523f24d04529077d84082b5b35f2ce9e4e8cee92bf62cec4b3829`.
Existing [termination evidence](../TERMINATION_OWNER.md) supplies all three
controls, including complete32-byte walker instructions. All five whole pinned
CRT sections independently match after every actual relocation.
Private proof: `.analysis/runtime-onexit-20261013/verification.json`.

Source340/exact263/64,657 code bytes; metadata136 and historical semantic249
unchanged. All260 preceding exacts and66 candidates retain unchanged producers
and results. Two new candidates bring the set to68:34 authored/34 runtime.
Five complete comparisons and native/i686 standalone compilation cover both
owners. Existing termination source/header and semantic inputs are unchanged;
no runtime tests or game builds run. Initialized table storage, physical process
exit and complete runtime/game integration remain open.
