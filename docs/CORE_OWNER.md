# Main ball physics and gameplay frame

This batch follows the two central gameplay entries through REA: the 3,223-byte
ball updater and the 1,688-byte enclosing gameplay frame. The maintained C
connects them to board hits, paddle rebounds, bonus application, particles,
brick animations and round advancement. Required dependencies add screen-point
hits, ball retirement, brick dropping, fire effects and paired projectiles.
Independent list leaves are kept as private typed helpers, without separate
function or exact-match claims.

Nine additional functions have 4,580 original-x86 differential cases, including
200 connected frames as a subset. The checkpoint has 85 maintained functions,
65,894 direct cases, and the existing 40 exact functions / 4,079 bytes. This
batch establishes scoped semantics; it adds no byte-exact claims. Platform
presentation, score drawing, last-brick behavior and round reset remain pending,
so the current products are still analysis utilities and a library.

## Entry evidence

All dossiers were collected with the pinned REA MCP/Ghidra session, including
instruction and referenced-data evidence. Complete inline records and logs are
retained privately under `.analysis/rea/runs/`; the completed interactive session
saved a snapshot with 113 Evidence records. Owned instruction bytes and complete
enclosing spans are distinct. In particular, the frame has 1,683 owned bytes
inside a 1,688-byte span; no unowned bytes are silently counted as exact.

| Entry | Maintained function | Owned / span bytes | Direct cases | REA Evidence ID |
| --- | --- | ---: | ---: | --- |
| `0x0040F8B0` | `dxball_game_frame` | 1683 / 1688 | 708 | `ev_5d1d8d47e797530fa172e492b60eebe40dcf8a855a6d9125eb644dccb2e15d43` |
| `0x00410770` | `dxball_update_balls` | 3223 / 3223 | 2373 | `ev_c7fd5e1c178073afb10924d1dbfa6df93f8ba8566533fd41f8dcb8f48b3a92a1` |
| `0x004116C0` | `dxball_hit_screen_point` | 337 / 337 | 1152 | `ev_a3dbe09d41da07ce2638ea83d054f31af646f507b1cedf2495bd03630db46f7b` |
| `0x00411820` | `dxball_retire_ball` | 45 / 45 | 12 | `ev_a36e9fab3ac21396c7a04fb5c8ea1b26eb31446fb29f612397d068d2eed7d17c` |
| `0x00413170` | `dxball_update_projectiles` | 328 / 328 | 126 | `ev_412b7a2d61e8a498417dca7a456838ed290b17317e4af4585d8b936b69b07495` |
| `0x004132C0` | `dxball_fire_projectiles` | 321 / 321 | 7 | `ev_d275b4fccde79ffde5a3244ff97e0be0c15cb85b03419d0c9425acb9c579b1b4` |
| `0x004135B0` | `dxball_spawn_fire_effect` | 185 / 185 | 50 | `ev_875ff3c542a834d79e1f45f8f9b68dd1ae6e354b32f2a0de4300bb862819716e` |
| `0x00413710` | `dxball_process_fire_effects` | 124 / 124 | 96 | `ev_9e33b3e41981c17ce9b99bb5029edf970e747c87fe3c82b3d6bcc19d45443a84` |
| `0x00415670` | `dxball_drop_bricks` | 426 / 426 | 56 | `ev_8602dd7fec1b8aff85a2c581b96d7a85bcf62a791d3741ecaecd0c5a411812fc` |

## Physics and collision order

The moving-ball path stores previous position, applies velocity and adds one to
Y when the kind-3 **tick field** is nonzero. Fireballs emit a trail before death
checking; its RNG order is chance, Y offset, X offset. Bottom death takes
precedence over every collision. Left, right and top walls then clamp and
reflect velocity in that order. Paddle collision uses cached coordinates from
the previous frame. More than 40 bounces raises speed up to nine; a paddle hit
resets the non-paddle count and can trigger the kind-17 brick drop.

Sticky capture clamps the attachment offset to trunc(width / 2.0 * 0.8).
The subsequent half-sprite subtraction applies to both signs. Capture does not
immediately reposition Y. On the attached path every nonzero attachment state
is treated as attached. A launch request clears it and executes the rebound,
but that frame still positions the ball relative to the paddle and sets the
attached cue. Input is sampled at the END of the frame, so launch and shooting
naturally affect different portions of consecutive frames.

Brick probing records impact velocity before vertical and horizontal samples.
Vertical collision repositions Y to a tile boundary; horizontal collision uses
15% and 85% height samples with short-circuit evaluation. Coordinates, velocity
and tile state modified by the earlier probe are visible to later probes.
Screen-point hits accept only 49 < Y < 350 and clamp the derived X tile to
0..19. A nonzero tile returns one even if its hit handler awards no score.
Fire converts that tile to 8, compensates the count when replacing tile 2,
and creates a fire animation unless the hard-tile flag suppresses it. Eligible
hits add twice the ball speed. After more than 300 non-paddle bounces the
maintained softening routine changes the board and clears kind 17.

Dropping visits columns in ascending order and rows 18 down to zero. It moves
occupied tiles into empty cells one row lower, leaving auxiliary animation
occupancy and remaining count unchanged. A moved board is restored with the
original DirectDraw Blt slot/rectangle/0x01000000 flag, redrawn column-first,
and invalidated once. Its sound plays even when nothing moves. This consumer
identifies kind 17 as brick dropping; a bottom-wall interpretation was not
supported by the earlier flag writer alone.

## Frame, shots and animation

The complete frame preserves the original ordering: score dependency, paddle
position, ball physics, projectiles, bonuses and particles; restoration and
cached paddle update; brick effects, projectiles, fire effects, paddle, balls,
bonuses and particles drawing; last-brick dependencies and presentation;
palette timing; explosion requests; deferred powers; completion/reset; input.
Pause equals ONE selects only the 32-ms palette path. Active frames use 20 ms.

Deferred slowing, speeding, enlargement, cloning and fire conversion run in
that order after drawing. Slowing sets speed four and resets non-fire sprites;
speeding adds two with a cap of nine. Both preserve the old component signs,
with zero taking the negative sign. Assembly exposes the 1.2 horizontal scale
and negative sine that pseudocode around __ftol omitted. Extended precision
and integer truncation are kept in the maintained source. Completion waits
for BOTH brick and fire animations, retaining the original short-circuit list
begin calls. Pending round reset executes before the new mouse action.

Shots are a separate four-integer payload/list at 0x43A898: x, y, previous x,
previous y. Paired shot offsets deliberately use DIFFERENT constants, 0.425
and 0.43, and count is increased after both allocations. Shots move up eight
pixels, choose impact dx through RNG, and retire before invoking tile damage
unless the hard-tile flag permits persistence. Retirement decrements the shot
count. Projectile tile X is not clamped; its valid-column precondition is
explicit. The integer Y division can select row zero above Y=50.

Fire animations have a distinct three-integer payload/list at 0x43A8E0: x, y,
ticks. Placement subtracts 24/23 and clamps to 0..595 / 0..436. Processing draws
sprite ticks+145, increments ticks, then deletes after 21. All three list
families preserve delete-then-advance skipping a successor. Typed helpers use
natural pointers and real payload sizes; they do not claim the original leaf
entries as restored. Their transitive behavior is tested through the bosses.

The score-refresh dossier at 0x415880 establishes that global 0x43A884 caches
the displayed score. The former provisional life_score_limit label is corrected
to displayed_score in the existing round/bonus owners. Its score clamp and
actual UI redraw remain part of the pending dependency, rather than an invented
life-award mechanic.

Supporting REA constants: physics fractions/divisor
`ev_413a8c78f7d3453f7a7de18683c0bcd87647ae1056a0dbd7fe5e1ddd171218a1`;
shot offsets `ev_35bab98081ce2444c7dcbf3697cf304923aaaf3bb975287cd51d5a75092f8dd6`.
The frame's instruction view uses the previously attested 1.2 at 0x420088.
Score refresh: `ev_f58f31dcc563b9653e897718b068dc40ec22843226aefb9e5dceaa2f4c366c90`.

## Oracle scope and remaining dependencies

`tests/test_core_differential.py` runs unmodified original entry bodies. The
ball updater and full frame are NEVER intercepted. Actual original and
maintained bodies execute for physics, point hits, shots, fire effects, tiles,
powers, trig, rebounds, particles, bonuses and brick animations. Comparison
covers return values, relevant globals and phase-entry state, full tile/aux
buffers, particle pixel buffers, ordered calls, every typed list/root/cursor,
allocation shape, callee-saved registers/stack, and poisoned freed storage.
New allocations are classified through reachable typed roots, not ambiguous
host allocation sizes. Fatal fire/shot allocation exits are also compared.

The frame's explicit callback table configures twelve unresolved dependencies:
current time, elapsed test, palette animation, score refresh, surface restore,
region restore, effect-sprite drawing, paddle drawing, last-brick processing,
last-brick overlay drawing, presentation and round reset. Their calls and
entry-state ordering are checked. Their bodies are not validated by a trace.
The original dependencies are intercepted at their ENTRY, without patching
instructions or changing the target file. `dxball_frame_ops` is deliberately
unconfigured until a caller supplies these operations; no dummy playable
backend or silent no-op implementation is introduced.

Allocator/deallocator, RNG, audio, cursor and rendering boundaries retain their
earlier scopes. Arithmetic must be finite and non-overflowing, list cursors
live, sprite banks/slots valid, rebound paddle width positive, fire RNG limits
positive, and projectile hit columns within 0..19. Controlled callbacks preserve
the current ball and metadata. Kind-3 movement ticks are sampled, but their
external timer producer is still pending. Terminal level initialization keeps
the prior explicitly controlled index-50 scope. Hardware DirectDraw,
DirectSound, input message routing, score rendering, last-brick execution and
round reset/game initialization must still be reconstructed for a playable
whole game.

Cases cover all 50 boards; point-hit boundaries and tile kinds; wall/death,
sticky/speed thresholds; attached/release paths; real board interactions;
odds and large sprite dimensions, alternate banks, x87 sampling truncation;
shot collisions and removal skips; pause/input/restore branches; all 32 deferred
power combinations; both animation completion gates; and 200 connected frames.
The connected cases are INCLUDED in the direct total. Earlier owners keep their
separate integration totals. Source is shared by native, MinGW and pinned VC4
builds. This bounded family receives one grouped cold replay after stabilization;
independent leaf matching is deferred while core gameplay remains the priority.

## Continue from here

Recover the runtime spine through the retained paddle renderer (0x412EC0),
restart transition (0x415DF0), round initialization (0x415C40) and caller
0x403730; investigate main game initialization 0x40E570 when required. Reuse
the completed REA dossiers before querying again. Rendering, score and
last-brick dependencies are concrete remaining work, not completed backend
claims. Keep working in connected batches and record REA feedback in the
requested `/tmp/dxball_rea_feedback.md`.

```bash
scripts/repo-python tests/test_core_differential.py
scripts/repo-python scripts/ci.py
```
