# Complete intro initialization, redraw, points and disposal

This batch restores four complete contiguous original bodies, totaling 3,035 bytes.
Original identifiers, declaration spelling and redraw buffer capacities remain unproven.
One maintained controller body serves the portable and Windows builds.

| Entry | Original bytes | Primary REA Evidence ID |
| --- | ---: | --- |
| 0x40DFC0 initialize_intro | 277 | ev_75f34375487bd0aa69c53dd2f4f5dd57fad9d8a4cc8ee85a09d0f40d06d65e0f |
| 0x40E0E0 redraw_intro | 587 | ev_8d3b245893789331b1a53500a14aae87ed382cd5465098be8604a64b721a1440 |
| 0x40E570 initialize_intro_points | 1,996 | ev_001f48ac971f132ed4b29b98cf1549ec4136da2eab0a9448b6ed27d7f5e41fb8 |
| 0x40F010 dispose_intro | 175 | ev_e0df354eaa8c193e9ccbfb2486aa6532ed5cba21a7ed5d8c69097af79bf7e7dc |

Initialization preserves all 18 original direct call sites, including two distinct
surface-binding branches, real music loading, point setup, dirty regions and fade.
Disposal restores the entry's real full-screen rectangle, fade gate, six direct
owners and one conditional COM Blt. Existing splash helpers remain separately scoped.

Point setup consumes a local 287-byte binary mask with 68 ones on a 41-column,
seven-row grid. Its complete bytes match the previous ASCII representation, but
the original reads signed bytes directly. The restored body initializes this real
local mask, writes each point's actual indexed fields and preserves x+=10 followed
by angle+=20; wrapping sets x=116, increments y by ten and derives angle=y-41.
All 360 offsets use the existing observed wave callees. No inert storage is added.

Redraw restores strcpy, unsigned32 _ultoa with radix ten, strcat and strlen,
then the consumed count and direct text calls. Complete pinned 232-byte CRT member
and saved original data support ordinary strcpy/strcat entry bindings at 0x4177F0
and 0x4177F8. Identical multibyte aliases leave linked spelling uncertain; these
bindings do not promote runtime origin identities. The existing 32-byte text buffer
and justified 11-byte decimal buffer cover this domain; original capacities are
unproven. Three COM Blt operations reread current shared handles after callbacks.

Four diagnostic epochs are retained separately, with one unchanged function-body
restoration. Required Windows CRT and direct-owner declarations add stdlib.h,
midi.h, startup.h and sound.h. An intermediate mistaken single-bank header is
explicitly corrected; its inputs and the failed strict native build remain retained.
The final
69-input diagnostic compares initialization and disposal as complete zero units
(452 bytes); redraw emits 578/587 bytes with 560 full differences and point setup
2,041/1,996 bytes with 750 full differences. No source/name/order, capacity or layout
trials tune those candidates. Every actual relocation and literal is explicitly
bound. The configured intro compiler closure gains the actually included midi.h,
startup.h and sound.h.

One configured cold epoch accepts 106 complete exact units / 13,416 code bytes,
plus 136 separate metadata bytes. All 104 prior complete identities are preserved.
All 22 owner scripts pass in 418.395 seconds against 287 physically frozen
inputs. Existing tests, 1,510 runtime cases and case matrices remain fixed.
Fourteen rejection controls, 7,164 fresh raster and 1,024 fresh rotation vectors,
strict MinGW and full VC4 builds pass. The actual cold raster product is adopted
for the unchanged complete semantic recipe without another compiler execution.
Native music forwarding checks the genuine copied-image void adapter and current
callback; its integer result is limited to the observed ignored-return caller.
The shim retains 46 actual compiler dependencies. The 0.391-second resumed native
serial build omitted the affinity wrapper; this deviation is explicitly retained
in native-resume-record.json, with subsequent project commands CPU-limited.
The optional 711-byte point-update controller is excluded until its unconsumed
request-state writes have a source-origin explanation. The >=95% complete-source
goal remains active and unachieved.
