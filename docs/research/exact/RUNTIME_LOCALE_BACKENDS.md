# CRT locale backends

`__crtGetStringTypeA` at `0x41E000` is complete exact across291 bytes and
all15 actual relocations, including both full2/4-byte probe constants.
`__crtLCMapStringA` at `0x41AA10` has complete551/555-byte source with110
differences; private `strncnt` at `0x41AC40` has44/44 bytes with15 differences.
Neither candidate is exact. Full pinned CRT sections independently prove all
original extents and bindings; imports are checked against the PE import table.

Source restores cached ANSI/Unicode probing, code-page/locale defaults,
bounded input counting, both wide conversions, sorting-key output and every
allocation/free path. The original counter also reads the bound's sentinel:
positive-count input must back that extra byte. Original COFF `.file` records
identify `aw_map.c` and `aw_str.c`; VC4 also emits C++-style local-static names
in C mode, so those names do not establish a C++ source boundary. The two cache cells retain local static
zero initialization and the probe constants keep their complete original sizes.

Closed REA run `2026-10-13T16-22-03.789Z-interactive-1828283`; assembly IDs:
map `ev_e7659c72931b8bf01792878b3338d776b2981b07db91c0292626e01c2cafef04`,
count `ev_f49f4dba00890637cf91c60d334ffeecc4feda4b8b61e522f92fe7cc3b5d95e3`,
classification `ev_221cf7a9e3cb1eb98bb0c355c294b1d90003c20610c98fba9bafaff578ccffe9`.
Four bounded legacy compilations include the initial C model, per-branch result
checks, recovered C++ local caches and corrected C allocator linkage. The third
object's allocator mangling was rejected, not accepted through fake bindings.
Native/i686 standalone compilation and complete final comparisons run; all267
prior exacts and70 candidates reuse unchanged producer inputs/products/results.
Source349/exact268/65,496 code bytes; metadata136, candidates72 unchanged in
meaning. Runtime locale storage/OS execution and game integration remain open;
no runtime tests or game builds. Private seal:
`.analysis/runtime-locale-backends-20261014/verification.json`.

The later lifetime checkpoint begins the four wide-buffer/count/result
declarations only after ANSI and invalid-cache exits. It retains all original
initializers, allocation/conversion calls and cleanup, reducing565/280 to561/278.
Classification291 remains exact, with both full probe constants; counter44/15
is unchanged. Explicit captured-mode publication produces identical mapper
bytes and is not adopted. Two VC4 stages and one native/i686 set, retained REA,
no runtime tests. All336 exacts/111 other candidates/249 semantic rows remain;
global counts do not change. Receipt:
`.analysis/locale-mode-publication-20261014/verification.json`.

The original C producer and separate object boundaries reduce mapping from
561/555/278 to551/555/110. Mapper and counter now live in
`src/runtime_locale_map.c`; classification retains its unchanged exact C++ body
in `src/runtime_locale_backends.cpp`. A C classification control loses exactness
and is not adopted. Restoring the shipped mapper's five-local layout instead
produces561/555/118 and changes the counter, so that control is also rejected.
The selected counter's complete byte result is unchanged. Both producers retain
the full2/4-byte probe constants. Five VC4/native/i686 sets; selected objects are
reused with identical maintained inputs. All357 exacts and91 other candidate byte
results remain, with no new exact claim or runtime tests. Receipt:
`.analysis/locale-original-c-producer-20261015/verification.json`.
