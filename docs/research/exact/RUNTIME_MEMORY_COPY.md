# Memory-copy source recovery

Both original entries now have complete C implementations for ordinary valid
memory, including either overlap direction and zero length. They remain
nonexact candidates. The maintained `dxball_crt_copy_memory` API is preserved;
`dxball_crt_memcpy` supplies the previously missing source at 0x00416610.

| Original entry | Maintained symbol | Original bytes | VC4 bytes | Differing positions |
| --- | --- | ---: | ---: | ---: |
| `memcpy`, 0x00416610 | `dxball_crt_memcpy` | 334 | 215 | 329 |
| `memmove`, 0x00417CA0 | `dxball_crt_copy_memory` | 334 | 215 | 327 |

The pinned LIBC members reproduce both complete original spans after resolving
their 12 local DIR32 relocations each, including two 16-byte tail tables. The
shipped `intel/memcpy.asm` produces both members through `_MEMMOVE_`. Existing
C++ vector relocation bindings to `_memmove` at 0x00417CA0 corroborate that
entry's role; the relocation-equivalent algorithms alone do not distinguish
their names. Observed function-ID names remain separate from this evidence.

## Reverse-copy register dependency

The original large, unaligned reverse path uses incoming EDX before initializing
it locally. The earlier forward-only recovery left that path open. Inspection
of the full algorithm establishes a narrower consequence: `NEG EDX; AND EDX,3`
selects a prefix of zero through three bytes. With count greater than 12, every
such prefix is safe. The following backward DWORD copies and final tail cover
exactly

`prefix + 4 * floor((count - prefix) / 4) + (count - prefix) % 4 == count`.

Each grouping stays inside the supplied spans. Backward traversal preserves
the source bytes when the destination starts inside the source. Thus ordinary
final memory does not depend on incoming EDX. The C source needs no hidden
register argument or guessed register value. Its reverse four/two/one-byte
groups preserve that result; their access widths and order differ from the
original. Forward copying retains the existing alignment and bounded tail
phases. Both functions contain actual C implementations, without assembly,
copied instruction bytes or a host `memmove` wrapper.

The contract covers ordinary backed spans without address wrap, with the x86
direction flag clear on entry. Return value, cdecl stack behavior, saved
registers, final direction flag and data-span bounds are checked. MMIO,
volatile/concurrent observers, intermediate access order, invalid nonempty
spans and machine-code equivalence are outside this claim.

## Focused validation

The original-only baseline exercised 836 layouts per entry with eight incoming
EDX values, totaling 13,376 emulated executions. Values include all four low-bit
choices, both signed extremes and mixed high bits. Counts through 127, four
source alignments and eleven destination placements cover equal, forward,
reverse and disjoint copies. Full arena images and data bounds agree with
snapshot-copy results.

One compilation per VC4, native and i686 profile checks the stable source family.
Strict native/i686 C90 compilation passes. The generated-code comparison reuses
the saved original observations for all 1,672 layouts rather than repeating the
original matrix. Sixteen additional 20,000-byte layouts compare original, VC4,
i686 and native results, including page crossings and both overlap directions.
Eight additional zero-count cases use unmapped pointers and make no data access.
Together these are 1,688 ordinary layouts and eight unmapped zero-count cases.
Emulated generated code also passes return, stack, saved-register, direction-flag
and access-bound checks; native results include full arena comparison.

The source family shares no inputs with accepted exact recipes. All 380 exact
results and the other 89 candidate recipes, inputs and results are preserved;
all 249 historical semantic rows remain byte-identical. No full replay or game
play check ran for this change. The previous 124/334-byte forward-only candidate
is retained as historical evidence, superseded for the ordinary-memory contract.

## Evidence

Current member mappings, source snapshots, compiler products and probes are in
`.analysis/memory-copy-entries-20261016/`: `original-proof.json`,
`original-equivalence.json`, `source/comparison.json`, `differential.json`,
`large-differential.json` and `adoption.json`.

Original bytes reuse retained REA evidence
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`
under `.analysis/rea/runs/2026-10-09T17-33-35.918Z-rea-runtime-requests-1477421/00-read_bytes.json`.
The prior direct 0x00417CA0 observation is
`ev_40f1c8b828cd093aa3050b6d8172db05b91bf3ef0dba1e470a2dac112b3901e2`;
the earlier partial checkpoint is `.analysis/runtime-memory-copy-20261014/`.
No new provider session was needed.
