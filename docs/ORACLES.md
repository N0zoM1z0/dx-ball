# Oracle matrix

| Oracle | Establishes | Does not establish |
| --- | --- | --- |
| Target/file and Ghidra attestation | Same executable and sampled mapped bytes | Semantic correctness |
| Original x86 vs compiled native C | State and ordered dependency effects for tested domains | Original code emission, Windows/pixel equivalence |
| Pinned VC4.0 COFF replay | Complete function bytes after every explicitly reviewed relocation | Whole-EXE layout, untested function behavior |
| Resource x86 vs compiled native C | SBK/PCX decoded pixels, initialized sprite state, fonts and palettes | Actual DirectDraw rasterization/display |
| Gameplay x86 vs compiled native C | Tile/count/score changes, full integer returns, list links, pan and ordered boundary calls | Ball physics, bonus/particle/audio backends |
| Animation x86 vs compiled native C | Timers, propagation order, occupancy lifecycle, payload bytes and deletion traversal | Bonus creation, rendering drivers, full frame behavior |
| Entity x86 vs compiled native C | Bonus RNG/production, particle lifecycle, typed queues and full pixel buffers | Bonus movement/application, hardware presentation, complete frame |
| Power-up x86 vs compiled native C | Bonus collection/application, board powers, paddle cursor state, typed ball ownership, computed trig and rebounds | Main ball frame, terminal adjacent-memory reads, platform drivers |
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

The gameplay owner adds 13,689 cases. It executes original hit, scan, request-list
helpers, pan and board-render bodies. Pan tests also execute the original x87
conversion helper; allocation, brick-effect, audio, range RNG and particle
dependencies are controlled. Traces observe intermediate state as well as
arguments, checking mutation and RNG order. All byte values, repeated damage,
repeated scans, list payload poison and null-return exit are included.
See [gameplay evidence](GAMEPLAY_OWNER.md) for the accepted domains.

The effects owner adds 12,977 direct cases, 864 frame-phase cases and 1,536
hit-to-animation integration cases. Actual animation constructors, timer steps and dispatcher
execute; allocation/deletion, bonus and rendering dependencies are controlled.
Released node storage is poisoned. The integration suite executes the original
frame updater with unrelated phases neutralized and compares only animation and
request state. Integration cases are excluded from the 61,314 direct-case total;
the frame updater is not marked reconstructed. See [effects evidence](EFFECTS_OWNER.md).

The entity oracle adds 7,343 direct cases (5,204 particles and 2,139 bonuses),
bringing that checkpoint's direct total to 45,380. Another 980 integration checks
connect real hit, animation, bonus production and particle bodies. The test
compares typed payloads, allocation ownership, poisoned deletion, RNG/audio
traces and complete 8-bit buffers including pitch padding and guards. Actual
target memset executes; controlled DirectDraw callbacks supply storage and
Lock retries. Earlier owner tests continue to isolate their explicit
dependencies. Integration counts remain separate from function acceptance.
See [entity evidence](ENTITIES_OWNER.md) for precise domains and missing work.

The connected power-up oracle adds 15,934 direct cases, bringing the current
total to 61,314 across 76 maintained functions. It executes actual geometry,
bonus movement/application, board powers, round transitions, ball ownership and
rebound math. Both entire computed trig tables, x87 returns, ordered callbacks,
all relevant globals/grids and live/freed storage agree. Sixteen multi-frame
bonus checks are a subset of this direct count. Terminal board initialization
is controlled for index 50; connected valid initialization covers indices 1..49.
See [power-up evidence](POWERUPS_OWNER.md) for arithmetic and platform limits.

Owners can route individual semantic units to a connected oracle through
`unit_oracles`; its selected file and complete helper/input set are hash-bound.
Earlier isolated oracles remain part of the private suite. A stable family is
cold-replayed together, and unchanged completed reports are reused at that
checkpoint rather than replaying after each restored function.
