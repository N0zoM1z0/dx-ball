# Unsigned 64-bit compiler arithmetic

Two omitted complete CRT helpers now have natural C implementations with the
original 64-bit return and 16-byte callee-cleaned argument ABI. Both remain
nonexact candidates.

| Original symbol/address | Original/C bytes | Differences | Nonzero pairs | Zero-divisor cases |
| --- | ---: | ---: | ---: | ---: |
| `__aulldiv`, `0x41FE00` | 104/327 | 322 | 495 | 6 |
| `__aullrem`, `0x41FE70` | 117/280 | 275 | 495 | 6 |

The original sections are assembly. Their small-divisor path uses two hardware
divisions; the other path normalizes a quotient estimate and corrects its
product. The reconstructed C uses 32-bit limbs and restoring division, with a
32-bit division/remainder first when the divisor's high limb is zero. It
implements the complete arithmetic rather than forwarding to another wide
division helper. Neither emitted C body has an instruction relocation or
runtime-helper call. No assembly, copied instruction arrays or compiler-option
sweep is introduced.

Win32 declarations use unsigned `__int64` and stdcall; other supported native
hosts use `uint64_t`. The union's two 32-bit words use the original little-endian
layout. The full quotient or remainder returns in EDX:EAX on x86. Large-divisor
quotients fit one word; the small-divisor path computes the high quotient before
processing the low dividend bits. Unsigned carries/borrows preserve limb width.

## Complete original evidence

A bounded scan of the pinned 657-member `libc.lib` compares dedicated external
single-function sections against retained REA code. It examines 951 eligible
sections, requiring at least16 bytes and an eight-byte fixed anchor. Every candidate interval
checks all non-relocation bytes; repeated-symbol operand consistency is only
discovery evidence. Three members with non-ASCII symbol names are skipped.
Shared multi-function sections and shorter/weaker anchors are outside this
scan, so it is not an exhaustive absence claim.

The two uncovered results need no inferred relocation bindings: both original
sections have none. All104/117 bytes have one complete occurrence in the
retained code and verified PE, including `RET16`. They overlap no inventoried
function. Pinned `ulldiv.obj`/`ullrem.obj` establish the definitions and extents.
REA Evidence: `ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
No new provider session runs.

## Focused checks and scope

One new owner is compiled once per VC4/native/i686 profile. Native/i686 C90
builds treat warnings as errors; the native object is reused in its shared
library. All495 operand pairs agree with independent Python quotient/remainder
arithmetic across original x86, actual VC4/i686 objects and native C. Cases
cover word/sign-bit boundaries, every normalization width and seeded operands.
Actual original fast, normalized and correction branches are all observed.

The object oracle checks the full 64-bit result, stdcall stack cleanup, EBX/ESI/
EDI/EBP preservation and absence of writes outside the stack. Six zero-divisor
numerators per function produce divide-error interrupt0 in original/VC4/i686
emulation. Native calls cover nonzero divisors; no physical OS exception or
exception-context equality is claimed. The reader adds actual DIR32NB handling
for VC4 debug-frame records; the same compiled products are reused.

These are990 logical successful cases and12 fault cases, counted once across
profiles. They do not add historical semantic rows. Private receipts:
`.analysis/crt-uninventoried-sections-20261016/`, including `scan.json`,
`original-proof.json`, `source/`, `differential.json` and `adoption.json`.
Heavy work is serial on one allowed CPU, CPU35%, memory high640MiB/maximum768MiB.

Inventory/source become545/470; exacts remain380 covering77,485 code bytes and
244 metadata bytes. Candidates become90:34 authored,55 runtime and one compiler
generated. All380 old exact and88 candidate recipes/results/products are
retained; all249 semantic rows are byte-identical. No old function compiles,
full replay or game build runs. Remaining low-level ABI work, final CRT/game
integration and the original-compiler play check remain unfinished.

Sharing eight identical immutable carriers reclaimed about3.2MiB. Unique source,
original members and compiler/probe products remain archived independently.
