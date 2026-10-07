# Oracle matrix

| Oracle | Establishes | Does not establish |
| --- | --- | --- |
| Target/file and Ghidra attestation | Same executable and sampled mapped bytes | Semantic correctness |
| Original x86 vs compiled native C | State and ordered dependency effects for tested domains | Original code emission, Windows/pixel equivalence |
| Pinned VC4.0 COFF replay | Complete function bytes after every explicitly reviewed relocation | Whole-EXE layout, untested function behavior |
| Resource x86 vs compiled native C | SBK/PCX decoded pixels, initialized sprite state, fonts and palettes | Actual DirectDraw rasterization/display |
| Gameplay x86 vs compiled native C | Tile/count/score changes, full integer returns, list links, pan and ordered boundary calls | Ball physics, bonus/particle/audio backends |
| Native/Windows board inspector | Shared source builds and decodes actual boards | Playable reconstruction |

Run `scripts/repo-python tests/test_boards_differential.py` after building the
native library. It validates all 50 load/store/init slots, all 23 supported
sprite values, 256 tile bytes across representative modes, update flags and
coordinates, all 50 complete boards in two modes, and missing/short/full/oversize
bank files. The 9,502 cases compare execution of the hash-attested target x86,
not another transcription of the intended algorithm.

The target's unsupported sprite-helper inputs read an uninitialized local; the
host helper aborts. No equality is claimed outside 0..22. Draw-cell behavior for
all byte values is separately tested. Board indices and coordinates require the
target caller domains: 0..49 and 0..19 respectively.

Exact replay cold-compiles the shared owner using the pinned compiler and
explicit flags. Every function must occupy one complete `/Gy` COMDAT code
section; the oracle cannot accept a requested matching prefix. It requires the
complete relocation offset/type/symbol/addend set and applies DIR32/REL32 fields
to reviewed target destinations. Mapped string literals are checked in both
the object and target. Size differences and all bytes count as failures.

Generated reports under `build/reports/` bind target, toolchain, source/header,
manifest, object, and relevant code-span hashes. A passing source build alone is
never recorded as an exact match. Changing shared input requires cold replay.

The resource owner adds 1,869 cases across all seven supplied SBK files, five
PCX files, all 256 character values in three fonts, retry/failure branches,
edge slots, pitch padding, clipping and RLE packet boundaries. Its target
oracle executes parsing and pixel writes rather than decoding at the boundary.
Native source uses host libc against the same files. See
[resource evidence](RESOURCE_OWNER.md) for exact acceptance domains.

`config/source-owners.toml` lists each owner's evidence inputs. Semantic and
exact rows bind complete input hash sets; shared headers and oracle helpers
cannot change silently. Hardware DirectDraw effects and undefined/uninitialized
state are excluded from semantic acceptance.

The gameplay owner adds 12,786 cases. It executes original hit, scan, list
append, pan and board-render bodies. Pan tests also execute the original x87
conversion helper; allocation, brick-effect, audio, range RNG and particle
dependencies are controlled. Traces observe intermediate state as well as
arguments, checking mutation and RNG order. All byte values, repeated damage,
repeated scans, list payload poison and null-return exit are included.
See [gameplay evidence](GAMEPLAY_OWNER.md) for the accepted domains.
