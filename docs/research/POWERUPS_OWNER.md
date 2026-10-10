# Bonus application, paddle and ball dependencies

The [complete brick-power restoration](exact/EXACT_BRICK_POWERS.md) restores the
whole source for spread, softening and counting. The full 397-byte softener and
149-byte counter are exact; spread compares 844/824 with 753 differences.
Four independent neighbor blocks preserve collection-before-mutation, live
signed-byte reads and immediate drawing. Original source spelling and storage
homes are not proved; the single-case scan switch is an inference. All existing
direct and application cases remain unchanged.

The [complete bonus restoration](exact/EXACT_BONUSES.md) restores all nineteen
inline application cases with live sprite/bank reads, original sound/callee
order, floating half for kind 11 and signed integer half for 16. The whole
2,168-byte enclosing span is exact, including the jump gap and switch table.
Existing original/native application checks retain their cases and oracles.

The later [core exact batch](exact/EXACT_CORE.md) restores the trig and ball
constructor emissions; [cloning and cleanup](exact/EXACT_LISTS.md) restores the
637-byte clone. The entry table and counts below describe this owner's
historical acceptance checkpoint.

REA's retained bonus-updater dossier led this batch through collision geometry,
paddle position, board powers, life/level transitions, ball ownership and the
quantized trigonometry used for paddle rebounds. The connected original-x86
oracle validates 21 additional maintained functions with 15,934 direct cases.
Seven complete functions cold-replay exactly, adding 675 bytes. The repository
checkpoint has 76 maintained functions and 40 exact functions / 4,079 bytes.

## Entry evidence and acceptance

Full inline Evidence and request logs are retained privately under
`.analysis/rea/runs/`. This table reports Ghidra's owned instruction bytes and
complete enclosing span separately; a semantic claim does not upgrade its span
to a byte-exact claim. Exact units compare complete dedicated COFF sections.

| Entry | Maintained function | Owned / span bytes | Direct cases | Exact | REA Evidence ID |
| --- | --- | ---: | ---: | --- | --- |
| `0x00402100` | `dxball_rectangles_overlap` | 319 / 329 | 8000 | semantic | `ev_38098a89555f0662ce749fc26b6fe5b78bea2da42431812abbdbf888c320c2cd` |
| `0x00402250` | `dxball_initialize_trig` | 232 / 232 | 1 | semantic | `ev_be4c847d5647acb8d0ff686d8f938d149e4fd0968604c98669ff41f847fb20c5` |
| `0x00402400` | `dxball_sine` | 130 / 130 | 2161 | semantic | `ev_844ec55c396bf6f53e88092f8514d492707cf2625133ae9ea2e38d42c948cf50` |
| `0x00402490` | `dxball_cosine` | 130 / 130 | 2161 | semantic | `ev_34e8f2372ac37a7c69a602c5366b18f1cc8cd0873e9dbd3a51a4999d0e6f92bd` |
| `0x004100F0` | `dxball_begin_balls` | 57 / 57 | 56 | yes | `ev_9c8b8c82788851cb2ca5063efe7775823e05178d9f96d9089ac7c8532375bd45` |
| `0x004101D0` | `dxball_advance_ball` | 89 / 89 | 56 | yes | `ev_bd9c2b70f5e2b0d677e3027b58e618e3a7d1c5e341d9cb72b316a5def1e48895` |
| `0x004105D0` | `dxball_spawn_ball` | 244 / 244 | 37 | semantic | `ev_80aebbb169f0d2bc78a9f894e8a4f8a0dc72c3a0d0a4049fdc19518219a5f52b` |
| `0x004106D0` | `dxball_append_ball` | 146 / 146 | 57 | yes | `ev_ec03d81a1de8e23be7f38b75a66795e8b67db909881265d0ac39f9c371ab480e` |
| `0x00411410` | `dxball_bounce_ball_from_paddle` | 681 / 681 | 714 | semantic | `ev_6055fe1d318fa3f71d76b5cdbbbe862a3944dd9890035a53264b8ccfa2d7a074` |
| `0x00411850` | `dxball_remove_ball` | 215 / 220 | 56 | semantic | `ev_ad944e908a2b23a9361befd1410ae97034be779d87b3b006536ec2d702031394` |
| `0x00412DF0` | `dxball_update_paddle_position` | 203 / 203 | 189 | yes | `ev_5be09046f1c60aeabad5697e07a604bbd89c05139b40ac5bda631e4864a44630` |
| `0x00413E20` | `dxball_update_bonuses` | 2087 / 2168 | 912 | semantic | `ev_927b00b89e0931308e5cd78eb83b9e33a11d5e7c63e32d7d9da49f53ca6f81cf` |
| `0x00414DF0` | `dxball_clone_balls` | 637 / 637 | 40 | semantic | `ev_82922c280cc6891fafb4d3e9d135352e6b4541f3309f61a8e6c06abf7a615da8` |
| `0x00415070` | `dxball_clear_ball_list` | 48 / 48 | 28 | yes | `ev_2b488b414ef253dd6f2fa64a0d106e1fa3cf7cb3180733f969a4bb32c6b16425` |
| `0x004150A0` | `dxball_spread_explosive_bricks` | 824 / 824 | 706 | semantic | `ev_3d377be2b21a0bacfa9d8a165f08def8fa9f77830b0d0fe671d3aaedbf5ac7cf` |
| `0x004153E0` | `dxball_clear_explosion_list` | 48 / 48 | 28 | yes | `ev_f6ca939462f1939faaf7ee83637adee102af92a1397958a9805a9a716417e5e0` |
| `0x00415410` | `dxball_soften_special_bricks` | 397 / 397 | 306 | semantic | `ev_2658970814be31782b2c65645873f87b091af5efdba4f7936cd30159a223cf4b` |
| `0x00415820` | `dxball_release_attached_balls` | 84 / 84 | 40 | yes | `ev_87baad441437023715a9e29bebce7676439ea8bb7fda9ab3704dc3c9699fe754` |
| `0x00415A90` | `dxball_count_destructible_bricks` | 149 / 149 | 306 | semantic | `ev_a3ef22630731d5acabc8242cde15f9f53faed00efd493b43428731c7a2caa2dc` |
| `0x00415B30` | `dxball_advance_level` | 123 / 123 | 65 | semantic | `ev_10dedc1278e4815286d503ac118934dbfa5686b95b7ab47456756e5f5df0672a` |
| `0x00415BB0` | `dxball_lose_life` | 81 / 81 | 15 | semantic | `ev_fa22e3d77987a1e02fa7436c87dfc635c546f7a333ce9e25e2b3561940374fb9` |

## Recovered behavior

Collision uses integer rectangle centers, inclusive half-width/half-height
comparisons and a second strict comparison. This is observable for odd and
inverted rectangles; replacing it with conventional edge intersection would
change behavior. Bonus collision uses the cached previous paddle coordinates,
not the newly computed mouse position. Paddle position fixes y at 450, clamps
x sequentially against its width, optionally warps the Windows cursor, updates
mouse x after that call, and selects sprite 68 last. The entire 203-byte entry
matches, including the reviewed SetCursorPos import-slot relocation.

Bonus movement applies velocity first, then gravity after 20 ticks, then left,
right and top bounces in that order. Bottom removal takes precedence over paddle
collision. Collected bonuses add 100 points before application and retirement.
Deleting the current bonus and then advancing preserves the original successor
skip. All kinds 0..18 and default signed/unsupported kinds are covered. Kinds
14 and 15 set the same flag. Numeric flag names remain where their full consumer
meaning is still pending; source names do not invent a completed effect backend.

Width-changing bonuses release attached balls before playing their sound and
reading the base paddle sprite width. Growth restores the base width or adds
one base width, capped at four times the base. Shrinking subtracts a base width
when larger; otherwise it uses half the **base** width. Kind 11 computes that
half through floating-point conversion, while kind 16 uses integer division.
Life loss decrements lives and pans its sound from the current paddle position.

Explosive spread first collects every existing tile 8 into a scratch list at
`0x43FAA8`, then converts neighbors left, right, up, down. Newly converted tiles
do not become sources during the same call. Replacing tile 0 or 2 increases the
remaining-brick count; existing tile 8 is untouched. The scratch list is cleared
through its current cursor, preserving the original list deletion semantics.
Softening clears flag 17, turns 2/21 into 20, 7 into 6, and 3/4 into 5. Only tile
2 increases the count. Both operations draw changed tiles immediately, in the
original x-major traversal/order. Counting excludes only bytes 0 and 2.

Ball payloads are thirteen 32-bit fields followed by two links: 60 bytes on
x86, 72 bytes with native pointers. The active list is `0x43A8B8`; temporary
clones use `0x43AAA8`. Creation increments the ball count before allocating,
initializes every payload field and executes the maintained paddle rebound.
Cloning copies payloads without links, mirrors dx, and reduces an attached
clone's speed by one with a floor of four. It appends the temporary clones into
the active list, counts them, then clears the temporary list. Release acts only
when attached equals one and executes the actual rebound body after clearing it.
Successful and fatal allocation paths, cursor positions, poisoned payloads,
link ownership and writes after deletion are checked independently.

The game computes 361 sine/cosine entries using the observed constant 3.14159
and truncates results scaled by 1024. The source computes these tables; it does
not copy original array bytes. Negative multiples of 360 select index 360,
while positive multiples select index zero. Consequently cosine(-360) is
1023/1024 while cosine(360) is one. Rebounds choose eight angles using the
observed double thresholds. The first 0.07 comparison uses extended precision;
remaining comparisons use the stored float ratio. Horizontal velocity also
uses the observed 1.2 multiplier. These rounding stages are retained explicitly.

REA pseudocode omits the lookup argument and floating-point return. Assembly,
the initializer, its callers, and CRT dispatch records recover those details.
The dispatch records contain sin/cos names, independently confirming which
computed table each shim fills. Supporting constant/dispatch Evidence:

- Thresholds: `ev_4d766dda426ad0a72b1d9e9700d27f1f48013ba918174e50331482545a06bf99`.
- Pi/divisor/scales: `ev_b0d04f79977431d3976612eaace13d3b294e8121d6b522814f2f0f4569212ff2`.
- Horizontal scale: `ev_1a4b41da4e8cfde08fcaf855bcaaee2fd4ec11286940864b1a7ca8f7aded231f`.
- CRT names/dispatch data: `ev_c58b457e62dee86eb29270fc16d2e048b9946784d9363ece24dfd27510984d74`.

## Validation boundaries

`tests/test_powerups_differential.py` executes the unmodified target entries,
including their maintained callees and actual CRT/math routines. It compares
return values (including the x87 floating return), all relevant globals, full
board/auxiliary grids, ordered dependency calls, typed roots, live allocations
and poisoned freed storage. Both entire computed trig tables agree. Inputs
cover all 256 tile bytes, all 50 supplied boards, boundary/interior explosive
sources, eight rebound angle bands, three bonus movement/gravity boundaries,
odd sprite sizes, alternate banks and cached paddle positions. Sixteen connected
multi-frame bonus checks are a subset of the direct cases, not an added total.
The earlier owners' separate integration counts retain their existing meaning.

Scopes require finite bounded arithmetic without signed overflow or INT_MIN
negation, valid sprite metadata, nonzero paddle width for rebounds, successful
storage except the explicit fatal-path cases, and state-preserving controlled
audio/render/cursor callbacks. Spread and clone entry tests start their scratch
containers empty. Windows cursor motion, DirectDraw hardware, DirectSound and
CRT CPU-erratum adjustment behavior are not established by these tests.

Level advancement sets restart/change state and increments the zero-based
board index. Above 49 it sets end/menu state but still invokes initialization
and counting. That original call order is preserved through explicit round
operations. Connected initialization is tested for resulting indices 1..49.
Terminal index 50 and later branches use controlled initialization/counting:
the original initializer would read beyond the 50-board bank. Its adjacent-memory
behavior and the terminal whole-game path remain unresolved. The default native
initializer must only be used with a valid board index; no fake extra board or
silent skipped callee is introduced to hide this boundary.

The retained main ball updater at `0x410770`, Evidence
`ev_c7fd5e1c178073afb10924d1dbfa6df93f8ba8566533fd41f8dcb8f48b3a92a1`,
and paddle renderer at `0x412EC0`, Evidence
`ev_0b4d5d681d951be5b6a69ac1d9d09db3cc965811c767e0b2b4f7296609cc020a`,
were retained for the next batch. Main ball physics, projectiles and frame
orchestration are now maintained with scoped validation in
[CORE_OWNER.md](CORE_OWNER.md). Paddle rendering and platform integration remain
pending; the project is still an analysis library.

## Reproduce the batch

```bash
scripts/repo-python tests/test_powerups_differential.py
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Source is shared across native, MinGW i386 and pinned VC4 builds. Build and REA
sessions run sequentially under the project resource limits. Function-specific
semantic oracle routing in `source-owners.toml` binds the expanded gameplay and
bonus scopes to this connected oracle while keeping their earlier direct tests.
Every acceptance binds its complete declared source/header/oracle input set.

Batch validation also reruns all earlier differential oracles, exact-oracle
rejections, REA's actual MCP/Ghidra smoke path, and all native/MinGW/VC4 inspector
runs. Cold exact replay is performed once after source stabilization; its report
is reused while those complete inputs remain unchanged. Pan literal labels are
now `$T617` / `$T618`; both target and object contents remain explicitly attested.
See [REA workflow](../REA.md) for the adaptive session and large-response client
feedback, which is also recorded in the requested private feedback file.
