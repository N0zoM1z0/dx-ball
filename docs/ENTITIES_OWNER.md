# Particles and bonus production through REA

`src/particles.c` and `src/bonuses.c` recover fourteen functions from the pinned
DX-Ball v1.07 target. REA's `analyze_function` dossiers supply pseudocode,
instructions, callers and body ranges. Independent original-x86 execution
corroborates the recovered behavior; the dossiers are static evidence.

The default gameplay particle callback now calls maintained particle creation,
and the default animation bonus callback calls maintained bonus production.
The earlier owner oracles still isolate those dependencies. The new entity
oracle connects their real bodies and compares all four typed queues.

## State and ABI

| Target VA | Maintained state | Original layout |
| --- | --- | --- |
| `0x0043A868` | `dxball_particles` | current / first / last, three pointers |
| `0x0043FAC8` | `dxball_bonuses` | current / first / last, three pointers |
| `0x0043FA90` | `dxball_bonus_count` | signed 32-bit count |
| `0x0042E690` | `dxball_effect_surface` | shared writable effect surface |

Particle nodes contain nine 32-bit values: x, y, dx, dy, gravity,
gravity_ticks, color, fade_steps and fade_ticks, followed by next/previous
pointers. Their original allocation is 44 bytes. Bonus nodes contain kind,
sprite, x, y, dx, dy and gravity_ticks, followed by next/previous pointers:
36 bytes. Native pointer growth gives 56-byte particle and 48-byte bonus nodes
without source-selected layouts. The bonus and animation nodes happen to share
their host allocation size; tests classify objects from typed roots instead
of guessing from that size.

Append, begin, advance and remove receive the list owner in ECX and return a
full integer. Appending replaces current with the new tail and leaves payload
bytes untouched. Allocation failure exits with status 1. Advancing past the
tail rewinds current to first while returning 0; removing chooses next or,
at the tail, previous. A subsequent advance therefore skips the successor.
Both new owners preserve that traversal behavior and all forward/back links.

## Particle behavior

Creation accepts only `20 < x < 619` and `0 < y < 479`. Movement adds velocity
before checking bounds; its surviving range includes x=20 and y=0. Gravity
applies only when the flag equals 1: every sixth update increments dy. Color
advances every fifth surviving update. The seventh color advance removes the
particle. Offscreen deletion precedes fading, and deletion/advance skipping
also affects mixed live/dead queues.

Drawing obtains the surface description, retries Lock until success, then
writes each particle as two bytes on each of two rows. `memset` supplies the
low eight bits of color. Each write is followed by a region call at `0x00408990`;
one Unlock finishes the traversal. The shared DirectDraw declaration uses
slots 22/25/32 for GetSurfaceDesc/Lock/Unlock. The surface must be writable,
8-bit, and large enough for every 2x2 write. Test callbacks do not replace its
handle during drawing. Driver failures that never resolve and real display
presentation remain outside acceptance.

## Bonus producer behavior

The chance draw with range 10 occurs even when a bonus already exists.
Production requires count < 1 and chance < 2. Tile coordinates become
`(19 + 30*x, 50 + 15*y)`: the x coordinate is one pixel left of the brick
renderer. Sound 2 is stopped and played with pan from that x coordinate.
Pseudocode omitted the pan argument, while the instruction facet and the
already recovered pan function establish it.

Production requests fifteen particles when reduced_particles is zero and
eight otherwise. Each consumes RNG in dy/dx/y/x order with ranges 7/9/15/30;
color is 16 and gravity is 1. The actual particle constructor clips requests.
Bonus allocation follows those requests. The final selector consumes range
19. Selector 0 or 1 consumes an additional range-5 draw and survives only for
value 1; other values become kind 13. Selector 14 becomes kind 10. Sprite is
kind+35, and the count increases last. Natural C expresses this selection
without copying the original switch table.

Drawing traverses bonuses through the controlled reduced-sprite dependency at
`0x004085D0`. Retiring first removes current and then decrements the count, even
if current is absent. The movement/collision/power-up application body at
`0x00413E20` has been investigated but is not implemented or accepted.

## Independent verification

`tests/test_entities_differential.py` executes the unmodified original bodies
and compiled maintained C. Its 7,343 direct cases comprise 5,204 particle cases
and 2,139 bonus cases. It compares payload bytes, list topology/current position,
RNG consumption, ordered audio/render calls, intermediate counts, and all live
allocation ownership. Deletion poisons storage; double deletion, lost live
objects and subsequent writes to released bytes fail. Null allocation is
tested against target exit and a native subprocess for both append functions.
Native callback exceptions are retained and fail the comparison.

Pixel cases compare complete buffers for two pitches, including row padding
and guard storage, edge and overlapping particles, color truncation, empty
queues, and Lock retries. The original CRT memset executes in the target;
the DirectDraw callbacks only provide controlled surface storage. Another
980 integration checks connect hit/animation/bonus/particle bodies and compare
their state and pixel writes. These are separate from direct-case acceptance;
they do not claim a complete original frame or bonus application.

Arithmetic domains exclude signed overflow, malformed lists and invalid draw
coordinates. Producer tile coordinates are 0..19 and RNG results are
0..limit-1. Rendering, allocation, RNG and audio backends are controlled
dependencies, with hardware DirectDraw and whole-game equivalence unclaimed.

## REA dossier ledger and exact boundaries

Full Evidence, including facets and limitations, is retained under ignored
`.analysis/rea/runs/`; the saved snapshot contains the successful records.
The table names the entry, complete span and returned Evidence ID.

| Entry | Function | Span bytes | REA Evidence |
| --- | --- | ---: | --- |
| `0x004138D0` | generate_bonus | 1,197 | `ev_ef8ebb1d4341bf24e0f31fba3bfb64c963503539c43bd3f13e61c367b4d84aed` |
| `0x00413D80` | append_bonus | 146 | `ev_4fc477413a3cc27f679939d9c009896ebe04d9188e4302c056852028388321a9` |
| `0x004146A0` | begin_bonuses | 57 | `ev_7200f1d8c975df601b205d3934efd146c77feef3869132c72b82a77eddb889c5` |
| `0x004146E0` | advance_bonus | 89 | `ev_4c71c8001b1066592397096ca4fe4617295a41270a79d68c527ae7f3bf131162` |
| `0x00414740` | draw_bonuses | 87 | `ev_18c8a1b160ceda205898808260e4886bf6c68f56001a7444f7b169469928c029` |
| `0x004147A0` | retire_bonus | 32 | `ev_d54f984055c1f61fdaea407b4d29928c71f9dc724f09b472e63e0001da6df5b7` |
| `0x004147C0` | remove_bonus | 220 | `ev_b1a3e59b2e4a28cee43842cefa27a736625c049bade614e71c11c6e452e3e0a1` |
| `0x004148A0` | spawn_particle | 179 | `ev_4d35e69679c1f453b47c74c9e927ba93112cdd0dbad1d97ccb36e7b82ceeefff` |
| `0x00414960` | append_particle | 146 | `ev_f0a14ca1d6a7e5734bfb86fbda96ab6446e8053561c412ff5119c3b3cd76559c` |
| `0x00414A00` | update_particles | 298 | `ev_8eb54857bbb5f5105e0c93e144024b4cbeed3925d1203c2d49e611908206de9a` |
| `0x00414B30` | remove_particle | 220 | `ev_e30c638667b1f7ce3a2fef6c243992dda3d59bad3a57a76cf426638f84129055` |
| `0x00414C10` | begin_particles | 57 | `ev_737ebc4fa238049f19b2ccbe3b3093cbbbe34697b4d040dd4a29c65cc352793d` |
| `0x00414C50` | advance_particle | 89 | `ev_64bcf8c88bd3b67f1ef9bea35c6ce9f3095290845b0ab61c339f0634c812b2f9` |
| `0x00414CB0` | draw_particles | 320 | `ev_78508bf5cd7a13bba8f876482f913dfeffc0fee30ef126fc6a216c32b14bca6e` |

Bonus production owns 1,116 bytes in three ranges:
`0x4138D0..0x413D07`, `0x413D0D..0x413D20` and `0x413D6D..0x413D7C`.
Its 1,197-byte span includes switch data and an unreachable epilogue jump.
Each deletion owns 215 bytes in a 220-byte span, with a five-byte gap before
the return epilogue. These spans remain distinct from instruction-byte counts.

Nine complete units cold-match exactly, totaling 1,093 bytes: both append,
begin and advance triples, particle creation/update, and bonus retirement.
All relocations are explicit in `config/match-units.toml`: allocator
`0x00416770`, exit `0x00417910`, typed globals and the reviewed helper entries.
The allocation/deletion bridges do not claim the original CRT implementations.
Deletion, compact bonus selection and dependency-based drawing have semantic
acceptance only; source is shared across native, MinGW and VC4.0 builds.

The pending bonus updater dossier is
`ev_927b00b89e0931308e5cd78eb83b9e33a11d5e7c63e32d7d9da49f53ca6f81cf`:
2,087 owned bytes in a 2,168-byte span. Continue from this retained evidence
into bonus/paddle collision and the power-up dependencies before claiming it.
