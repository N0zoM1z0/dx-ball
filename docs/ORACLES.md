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
| Core x86 vs compiled native C | Full ball/frame bodies, connected collision, shot damage, fire animation, power/input order and 200 continuous frames | Its isolated dependency bodies, platform drivers, playable game |
| Runtime x86 vs compiled native C | Initialization, life-loss reset, mode dispatch, clock, paddle and score bodies; 36 connected frames through game-over | Controlled resources, glyph/render/audio backends, device setup and non-game modes |
| Display x86 vs compiled native C | Lightning, dirty arrays, sort/merge, palette, waits and flip dispatch; 192 continuous frames with twelve actual gameplay phases | Hardware Blt/Flip/palette pixels, recovery, audio, glyph/resource and non-game boundaries |
| Device x86 vs compiled native C | Palette fades/creation, color fill requests, bank/surface recovery and synchronization; 26 connected checks | Driver rasterization, reload parsing on this edge, glyph/audio/platform and non-game bodies |
| Platform x86 vs compiled native C | WinMain, window messages, fullscreen/compatible creation and input bodies; 4,742 cases including stdcall cleanup and process exit | Real Win32 callback delivery, driver behavior, audio/UI/non-game implementations, playable game |
| Startup x86 vs compiled native C | Working-surface setup, score I/O, board-loader dispatch, timing, RNG calls and actual bank release; 158 cases and one connected dispatch check | Board-parser execution on this edge, CRT random-generator identity, drivers, mode-0/4 bodies, playable game |
| UI x86 vs compiled native C | Text/glyph placement, line pixel buffers, fill requests, full palette flags and RGB-int pools; 1,266 cases | Driver rasterization, actual window presentation, invalid storage/arithmetic |
| Menu/splash x86 vs compiled native C | Twenty controller/math entries, point pixels, scroller/credit waves, text and palette arrays; 5,615 direct cases plus 58 separate transitions | Resource parsing/release on this edge, audio/MIDI, real drivers, editor/game-over and playable EXE |
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
request state. Integration cases are excluded from the 82,709 direct-case total. This
phase-only suite does not establish the whole frame; its later scoped acceptance
comes from the core oracle. See [effects evidence](EFFECTS_OWNER.md).

The entity oracle adds 7,343 direct cases (5,204 particles and 2,139 bonuses),
bringing that checkpoint's direct total to 45,380. Another 980 integration checks
connect real hit, animation, bonus production and particle bodies. The test
compares typed payloads, allocation ownership, poisoned deletion, RNG/audio
traces and complete 8-bit buffers including pitch padding and guards. Actual
target memset executes; controlled DirectDraw callbacks supply storage and
Lock retries. Earlier owner tests continue to isolate their explicit
dependencies. Integration counts remain separate from function acceptance.
See [entity evidence](ENTITIES_OWNER.md) for precise domains and missing work.

The connected power-up oracle adds 15,934 direct cases, bringing that checkpoint
to 61,314 across 76 maintained functions. It executes actual geometry,
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

The core oracle adds 4,580 direct cases across nine functions, bringing the
that checkpoint total to 65,894 across 85 maintained functions. Both original bosses
execute: the 3,223-byte main ball updater and complete gameplay frame. Point
hits, projectiles, fire effects, board damage, powers, bonuses, particles and
brick animation remain connected. That isolated core suite traces twelve explicit time/render/score/last-brick/
reset dependencies; the subsequent runtime suite executes five of those bodies. The 200
continuous-frame cases are a subset of the direct count. Source uses actual
payloads and natural typed list helpers, without separate leaf claims. See
[core evidence](CORE_OWNER.md) for original quirks, complete input domains and
the remaining runtime work. All earlier suites and 40 exact units pass together.

The runtime owner adds 1,510 direct cases across sixteen functions, bringing
that checkpoint to 67,404 across 101 maintained functions. The oracle
executes actual mode dispatch, initialization, reset, cleanup, clock, paddle
animation and score entry bodies, connected to the maintained gameplay frame.
Its 36-frame new-game/three-life-loss/game-over scenario is a subset of the
count. Seven remaining frame dependencies, resource loading in lifecycle cases,
glyph rendering, device setup, audio and non-game modes are explicitly controlled.
See [runtime evidence](RUNTIME_OWNER.md) for input domains and exact boundaries.
Earlier 76 semantic entries and 40 exact units have unchanged complete inputs,
so this checkpoint reuses their prior completed reports and reruns the changed
core oracle, the new runtime oracle and all three toolchain products.

The display owner adds 2,409 direct cases across sixteen functions, bringing
that checkpoint to 69,813 across 117 functions. Another 192 continuous frames
are SEPARATE integration evidence, not added to the direct-case total. All twelve
real gameplay phases execute alongside actual sprite/dirty/palette/wait bodies.
Full dirty/presentation/key arrays and ordered COM dispatch agree. Pixel storage
is controlled for particles; driver rasterization, recovery/audio, glyph/resource
loads and non-game modes remain boundaries. See [display evidence](DISPLAY_OWNER.md).
Shared source/header changes receive one grouped cold replay of all 40 exact
units and all earlier differential suites. Complete input closure is refreshed
only after the affected tests pass; internal literal names are rebound only
with unchanged object/target contents, offsets, types and addends.

The device owner adds 1,115 direct cases across six entries, bringing current
acceptance to 70,928 across 123 functions. Its 1,339-byte palette transition
controller and recovery chain execute alongside actual waits, game redraw and
frame dispatch. Another 26 checks are separate integration evidence, covering
lost Flip recovery, synchronization and initialization/cleanup fades. Lifecycle
and recovery share the third bank's actual count/allocation fields; all three
banks' metadata is compared. COM, reload parsing on this edge, glyph/audio and
platform/non-game boundaries remain controlled. See [device evidence](DEVICE_OWNER.md)
for equality gates, terminal fade iteration, unspecified fill fields and input
domains. All earlier suites, cold exact replay and three toolchain products
are revalidated as one batch after these shared changes.

Direct-case totals count each suite's cases once. Semantic ledger rows can
attach a shared case set to several entries; summing those row counts would
repeat the same evidence.

The platform owner adds eleven entries and 4,742 direct cases, bringing that
checkpoint to 134 maintained entries and 75,670 direct cases. Main
loops execute real mode dispatch; window input connects real game keys, palette
fades, redraw and cleanup. Windows/COM/audio and non-game boundaries are
explicit, including defined failure outputs and finite message scripts. Both
stdcall entry points verify sixteen bytes of stack cleanup and preserved
registers. Two singleton failure paths must exit in native child processes and
stop original execution at the CRT exit boundary. Every previous oracle and
40 cold exact units is replayed after shared-input changes. See
[platform evidence](PLATFORM_OWNER.md) for limits.

The startup/UI checkpoint adds fourteen entries and 1,424 direct cases, bringing
that checkpoint to 148 maintained entries and 77,094 distinct suite cases.
A connected frame dispatcher check is counted separately. Working-resource
setup executes actual clock/palette calls; real sprite release frees owned
records across three banks. UI tests execute actual glyph bodies and line writes
with row padding. CRT file/RNG and COM outputs remain explicit boundaries.
All earlier suites, 40 cold exact units and eight rejection checks replay as
one batch, followed by three compiler products, Wine inspection and saved REA
verification. See [startup/UI evidence](STARTUP_UI_OWNER.md) for all Evidence IDs,
fresh-image defaults, original quirks and complete acceptance domains.

The menu/splash checkpoint adds twenty entries and 5,615 direct cases, bringing
current acceptance to 168 maintained entries and 82,709 distinct suite cases.
Another 58 checks are separate connected mode/key evidence. Actual menu and
splash bodies execute through mode dispatch alongside existing glyph, UI,
point/line, palette, dirty-region and timing code. Controlled COM callbacks
supply storage and observe meaningful requests; resource parsing/release on this
edge, audio/MIDI, real driver effects and pending editor/game-over bodies remain
explicit boundaries. Every earlier suite, forty cold exact units, eight rejection
checks, three compiler products, Wine inspectors and saved REA verification
pass together. See [menu/splash evidence](INTRO_OWNER.md) for Evidence IDs,
original data, shared-score ownership and full acceptance domains.
