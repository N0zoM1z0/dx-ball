# Dirty-region presentation

This batch restores queueing, selection sorting, sequential rectangle merging
and presentation, together with the lightning overlay's queue caller.

## REA evidence and recovered source

| Routine | Original bytes | Saved REA Evidence |
| --- | ---: | --- |
| Queue region, `0x408990` | 183 | `ev_8c8db0719620a4407f7ec289f38393456217a8f65ee947c84e20cf80f46b627c` |
| Present regions, `0x409100` | 984 | `ev_ca79613a0bb131922a4f6c409b62ad80fbc94bc7bfc427358457a912a2e388e3` |
| Sort regions, `0x4094E0` | 296 | `ev_6fa464860fec11c6c9b89b25ac22ba8445585a8dba2390986ff40878fc054f10` |
| Draw lightning, `0x416370` | 186 | `ev_63003d5621ef73504e785882f80a70043ccee9a339118544b722116d679ac13d` |

Queueing copies the incoming 16-byte rectangle into the current dirty page,
then independently appends it for presentation when the graphics flag equals
one. Each queue preserves its own capacity check. The API takes `DxBallRect`
by value; the particle callback keeps its scalar interface through a bounds
adapter. Particle, lightning and score-name drawing pass consumed rectangles.

Selection sorting moves both the signed keys and complete rectangles. It
selects a new minimum only for a strictly smaller key. Merging always stores
all four selected bounds and marks the consumed record's top as 9999.

Presentation chooses clipping once and runs the appropriate loop. Clipping
updates stored bounds in place; both paths skip merged records and read the
live primary and secondary surfaces for each Blt. The count is cleared last.
Three unused queue/clipping helpers were removed from `display.c`.

Lightning drawing constructs queued bounds after BltFast using the live
coordinates and the source rectangle's right/bottom. It queues that rectangle,
resets the sprite bank, then decrements the remaining frame count.

## Complete compiler comparison

The shared declaration affects 23 legacy recipes, compiled once. Complete
code, actual relocations, literals and attached metadata were compared.

| Newly exact routine | Code bytes |
| --- | ---: |
| Queue region | 183 |
| Draw lightning | 186 |
| Restore dirty regions | 827 |
| Queue sprite region | 272 |

The last two retain their preceding source bodies. Three earlier matches—
effect-sprite Blt, reduced-sprite drawing and elapsed time—return to candidates.
The net gain is **664 bytes**, reaching **123 exact functions / 19,704 code
bytes**, with 136 metadata bytes retained.

Presentation remains a complete 984/984-byte candidate with 51 differences;
sorting remains a complete 296/296-byte candidate with 29 differences.
Presentation's differences are local stack offsets. Sorting has 26 such
offsets and three bytes for an equivalent signed loop comparison; the remaining
instructions and branch destinations agree.

The native build and the existing display/entity Oracles pass with unchanged
cases. Windows VC4 game rebuilding reuses the matching compiled objects.
Full evidence and products are retained in `.analysis/exact-presentation/`.
