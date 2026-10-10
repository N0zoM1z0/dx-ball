# Board-hit gameplay owner

The [complete brick-power restoration](EXACT_BRICK_POWERS.md) restores the
whole hit body with live board-byte reads, direct brick-effect/audio/RNG/particle
calls, separate strength transitions and two particle loops. Its complete
1,316/1,315 comparison retains 418 differences. A full pinned REA 71-byte read
reconciles all 12 jump addresses and 23 selectors; the original recovered table
count of 11 is incomplete. The 1,244 owned instruction bytes remain separate
from the 1,315-byte enclosing comparison span. Existing hit cases remain fixed.

`src/gameplay.c` continues DX-Ball reconstruction from REA's tile-hit
investigation. The same C source builds on the native host, MinGW i686 and the
pinned VC4.0 toolchain. It owns tile transitions, hit eligibility for scoring,
the explosion request queue, screen-to-pan conversion and the explosive-tile
scan. The animation owner now supplies explosion processing; see
[explosion and animation evidence](EFFECTS_OWNER.md). Ball/projectile updates,
bonus generation, particle animation and DirectSound remain pending.

## REA evidence

All observations below come from the original hash-pinned executable through
REA 4.1.0 / Ghidra 12.1.4. Complete Evidence and snapshots remain private under
`.analysis/rea/`; public documentation records findings and identifiers.

| Operation | Evidence ID | Finding |
| --- | --- | --- |
| Tile-hit `analyze_function` | `ev_d09866ff22dc07f3ac28ef1d992c5876c1e58e1796dbe0f0c5c2814544aa27eb` | Cases, state writes, calls, full integer return and noncontiguous body |
| Gameplay `batch_decompile` | `ev_bb71d7ed5b420295eabab97c75f6b0050860ba550760b91d7ec261d33df98a32` | Ball-hit and projectile consumers use the returned EAX to award score; explosive scan uses x-major traversal |
| Pan `analyze_function` | `ev_ddca58134d89a2eb0aba5bf5694bb06ce7b5cb28aac0eb847891506244e70490` | Stack input, x87 operations and 63-byte complete extent |
| Explosion append `analyze_function` | `ev_4e8d52c7cb6398fdd93ddd2d9018f42208554126966f47176e512a58d444929f` | ECX owner, five-field node, pointer-write order and 146-byte complete extent |
| Explosive scan `analyze_function` | `ev_0b89bb714a56483d674b64accbc32f8de26c976f450c9680e3078d60293643a4` | Signed byte read, full EAX condition, terminal epilogue jump and 139-byte complete extent |
| Allocation entry `analyze_function` | `ev_419db51a7f08831470d0ff22cf5733bb2deb259dea477851690e11303637800b` | Runtime allocation wrapper; excluded from authored source claims |
| Pan constants `read_bytes` | `ev_6a56fda997bcda2df677257601da0174ff8041d44c8c83c48356df31edf0f7ae` | Doubles 1.5625 and 500.0 |
| Pan scale `read_bytes` | `ev_64752f4ecf1ec74384ce01083c21fcfffb716931f6c31a7dac351a136df7979e` | Initial double 1.0 |
| Focused producer `batch_decompile` | `ev_b5cad0b63e97abac8491687a9953736d05d3e62dfe957033da8489d273bc803e` | Reduced-particle flag is also set during DirectDraw capability initialization |

REA's pan pseudocode omitted its argument and x87 expression. The instruction
facet reads `[EBP+8]`, loads the integer onto the x87 stack, then multiplies,
subtracts and multiplies before `_ftol`. Tile-hit pushes `20 + 30*x` at the
call site. The maintained expression is `(1.5625*x - 500.0)*pan_scale`, truncated
to an integer. The original stack input and full return take precedence over
the incomplete decompiler signature.

The tile-hit body owns 1,244 bytes in a 1,315-byte span, with ranges
`0x411F40..0x4123EE` and `0x412436..0x412462`. The intervening switch tables
are not counted as instructions. Preserve the provisional ledger span; there
is no exact claim for the tile-hit body.

## State and transitions

| Original address | Maintained storage | Scope |
| --- | --- | --- |
| `0x43A8F4` | `dxball_remaining_bricks` | Destructible-brick count used by the hit owner |
| `0x43FAC0` | `dxball_destroy_hard_tiles` | Nonzero changes hard/damaged-tile destruction; bonus producer remains pending |
| `0x4228D8` | `dxball_reduced_particles` | Nonzero chooses four particles instead of eight |
| `0x422D20` | `dxball_explosion_pending` | Set to one when an explosive tile is queued |
| `0x422D18` | `dxball_score` | Scan adds four for each eligible hit |
| `0x4210A0` | `dxball_pan_scale` | Double multiplier, initially one |
| `0x43F8E0` | `dxball_explosions` | Current, first and last node pointers |

| Tile | Normal transition | Count change | Return / effect |
| --- | --- | --- | --- |
| 0 | Remains 0 | None | Returns 1; normal callers first check for a nonempty cell |
| 1, 5, 6, 9–20, 22 | Becomes 0 | Minus one | Returns 1; effect mode 0, sound 7 |
| 2 | Remains 2 | None | Returns 0; effect mode 1, sound 3 |
| 3, 4 | Becomes 4, 5 | None | Returns 1; effect mode 1, sound 1 |
| 7 | Becomes 6 | None | Returns 1; effect mode 1, sound 19 and particles |
| 8 | Remains 8 | None | Returns 1; queue kind 1 with tile x/y, pending flag 1 |
| 21 | Becomes 2 | Minus one | Returns 1; effect mode 1, sound 1 |
| Other byte values | Becomes 0 | None | Returns 1; no sound/effect |

When the hard-tile flag is nonzero, cases 2, 3, 4, 7 and 21 become zero.
Case 2 then returns one without decrementing the count. Cases 3, 4 and 7
decrement once. Case 21 still decrements exactly once. Negative nonzero flags
have the same branch behavior as one.

Case 7 consumes RNG in the order dy, dx, y, x, with ranges 5, 5, 15, 30.
Velocity is `2-random(5)`; position is sampled inside the brick; color is 119
and particle mode is one. The native implementation sequences these calls
explicitly so C argument evaluation order cannot change the random stream.
Sound stop/play happens before a regular destruction decrements its counter.
All hit branches finally select the board surface and draw/invalidate the cell.

The scan visits x in the outer loop and y in the inner loop. It invokes the
actual hit owner for tile 8 and adds four when the full integer return is
nonzero. It neither clears these tiles nor consumes queued explosions.
Repeated scans therefore queue them again; the animation owner now validates
their later consumption and occupancy guard.

## Linked-list layout and dependencies

The original explosion node is 20 bytes: kind/x/y at offsets 0/4/8, next at
12 and previous at 16. The owner has current/first/last at 0/4/8. Append uses
fastcall (ECX owner), requests one node, leaves its payload uninitialized,
links previous/next, updates the former tail or first pointer, then writes
last and current. A null allocation return calls `exit(1)`.

Portable pointers grow naturally: the 64-bit node has alignment padding and
is 32 bytes. Tests compare payload and logical pointer links, verify each
ABI's requested allocation size, and check untouched payload poison. They
do not assert raw host addresses equal original x86 addresses.

`dxball_allocate_node` remains a typed dependency boundary, now defaulting to
the [maintained new chain](ALLOCATOR_OWNER.md) recovered from `0x416770`.
Release defaults to maintained runtime delete. The gameplay oracle still
controls allocation failures and checks the owner's null-return exit; the
allocator oracle separately executes the internal retry and handler bodies.
Mapping an append call relocation alone does not accept those dependencies.

`dxball_gameplay_ops` supplies brick effects, sound stop/play, range RNG and
particle creation. Brick effects default to the maintained animation constructor;
the hit oracle controls this boundary, while the effects oracle executes it.
The other dependency implementations remain pending. The hit oracle hooks those same entries,
executes the original append and pan bodies, and runs the already accepted
board renderer with its established surface/sprite boundaries.

## Acceptance

`tests/test_gameplay_differential.py` has 13,689 independent cases:

- 3,205 pan cases: every integer x from 0 through 640, scales 0, 0.5, 1, 20
  and -1; actual target x87 arithmetic and `_ftol` execute unhooked.
- 129 append cases: empty/nonempty lists, 128 sequential appends, current
  pointing to an earlier node, uninitialized payload, and null-return exit.
- 9,240 hit cases: all 256 tile bytes, zero/positive/negative hard-tile flags,
  both particle modes and display modes, three cell positions, plus repeated
  hits preserving damage stages, hard-brick behavior and queue growth.
- 212 scan cases: all 50 hash-verified shipped boards plus empty/all-explosive/
  mixed-byte fixtures, both display modes, and repeated scans.
- 903 request-helper cases: all 256 tile values at three positions and
  begin/advance/delete at every current position in lists of length 0..8.

Comparison includes the full board, all owned integer state, active surface,
complete EAX returns, list payload/links, random consumption and ordered
dependency traces. Effect/audio/allocation callbacks also observe intermediate
state, detecting mutation-order differences. Coordinates are restricted to
valid 0..19 cells, counters/scores to the tested non-overflow domain. General
floating-point overflow, NaN, driver output and missing backend behavior are
outside semantic acceptance.

Cold VC4.0 replay retains the original three complete COMDAT units: append (146 bytes),
pan (63 bytes) and scan (139 bytes). Their nine relocations are explicit, and both double constants
are independently checked in object and target storage. No bytes are masked,
padded or copied into source. The scan preserves the observed signed byte
comparison and explicit terminal return, including its natural epilogue jump.
Tile-hit has semantic acceptance only; its maintained control flow and
dependency bridge need not emit the original instruction sequence.

The request begin, advance and enqueue helpers now add three exact units,
documented with their REA dossiers in [the animation owner](EFFECTS_OWNER.md).
Request deletion has scoped semantic acceptance only.
