# Sprite-file field lifetime and text-width arithmetic

October 19, 2026. Two source corrections preserve original behavior outside
the earlier complete-file, nonoverflowing scopes. They are adopted despite
worse byte comparisons. No exact function is gained or lost.

## Conditional file outputs

The sprite-bank loader keeps width, height, signed character code and baseline
in the same four stack objects across iterations. Reads at4046CA,4046E0,4046F6
and40470C do not initialize those objects before each call. The complete
original fread326-byte body returns from its EOF path before writing the
destination: refill417B6F, comparison417B77, branch417B7A and exit417BD2.

The previous C++ source began four new uninitialized scalar lifetimes on every
iteration. An unchecked read that writes no bytes cannot produce their values
for that lifetime. Move exactly those four declarations outside the loop;
retain their types, order and lack of initialization. Pixel count, bitmap and
allocation-only record pointer keep their existing scopes. The earlier
[iteration-scope inference](BANK_SPRITE_ITERATION_SCOPE.md) was too broad in
claiming all seven values were produced within every iteration.

An18-byte witness contains count2, one complete1x1 record, codeE9, baseline−3
and pixel77, then EOF. First CreateSurface succeeds; second fails before any
unread pixel is uploaded. Original x86 and current native source agree on both
records' defined header/rectangle fields, calls, first uploaded pixel/padding,
selected bank and partial ownership. Actual native stdio stays open at EOF,
as the original failure path requires. Uninitialized pitch/opaque fields are
excluded. This does not establish a runtime divergence of the previous native
executable, define an initially incomplete header, or repair original leaks.

Primary retained Evidence:

- Bank: `ev_b55c6def4c1b4af6c165acfb1623311bffa077753d93fab01531787dca6b6d70`.
- fread: `ev_2c3ef6dadb7fe8e79f5377c686891fa9f7960a56a3e3833e4295fc293d9986c7`.

## Modulo32 text-width sums

Original measurement404FD0 performs DWORD additions at4050A5,4050CC and4050D2,
without an overflow branch. Its missing-character path first computes signed
half-width through CDQ/SUB/SAR at40509F–4050A2. The signed C additions did not
define the original wrapping results. Both accumulation branches now use
unsigned32 additions and convert the resulting bit pattern back to DxBallInt.
The half-width division stays signed and occurs before its unsigned addition.
Glyph lookup, spacing, signed accumulator and return type stay unchanged.
The conversion contract is the supported VC4/GNU32-bit-int ABI, not a claim
about every C implementation or the historical author's cast spelling.

Finite17-byte font files publish count2, a known width, height0 and codeB before
CreateSurface fails. Allocation is only three pixel-buffer bytes. Actual
measurement can then consume that known width without a surface dereference.
The three bounded cases exercise width+spacing, accumulated matched widths
and accumulated missing-character half-widths. All three old instrumented
source paths fail with signed-overflow diagnostics; restored source matches
original x86 results −2147483648,−2147483648 and−1073741827 respectively.
A negative-width control preserves signed division, returning−1073741824.

The actual intro loads font bank1, then centered text measures before drawing.
That is a static reachability connection, not an observed corrupt-font game
run. The witness passes allocation_mode2; intro passes0. Both select caps840,
and measurement does not read the mode. Two full UI source compilations create
the before/restored UBSan libraries; every other native object is reused.
An initial harness compared events after the target call reset them. Capture
the loader events before measurement, retain that failure, then reuse both
compiled libraries for the corrected checks. No extra source compile follows.

Measurement Evidence:
`ev_6a25f94931f763de87b46ce0de325939c392113a9c31de1568162431ea46a545`.
The two independent reviews retain full carrier hashes and loader/caller proofs.

## Complete comparison and integration

| Complete owner | Units / bindings / literals | Preserved exacts | Changed candidate |
| --- | ---: | ---: | --- |
| Resources |18 /262 /6 |11 | Bank1475/63→1475/68 |
| UI |7 /38 /0 |6 | Measurement279/3→282/26 |

Each owner receives exactly one VC4 source compile. All25 complete functions,
300 actual bindings and six full literal references compare. All23 other code
identities remain fixed. Measurement's three-byte growth comes from its stored
sum's ADD/MOV producer; the signed division and frame homes remain. No alternate
names, layouts or flags are tried in response. Current authored coverage stays
248 exact/22 complete candidates across30 verified compiler closures; overall
393 exacts/84,633 code bytes/244 metadata bytes and82 complete candidates.

The current native library incrementally rebuilds only resources.cpp and ui.c.
Ten unchanged existing bank cases and216 existing measurement cases pass.
Historical semantic scopes/counts remain unchanged when input hashes refresh;
these checks do not freshly accept every historical row. Heavy operations are
serial on CPU0 with35% CPU,384MiB high/512MiB max; the two VC4 builds peak below
175MB, with zero high/max/OOM events. There is no full replay or game run.

Private authority: `.analysis/authored-boundaries-20261019/`, including both
source/result reviews, proposals, complete comparisons/producers, bounded
witnesses, selected existing cases, native build, adoption and authored coverage.
The61 closed copied inputs/products/helpers are archived and member-hash
verified in a1,217,038-byte archive before removal, releasing9,302,016 allocated
bytes net after archive cost and before the small manifest/cleanup receipt.
Current matching objects, native library/cache and previous tested EXE/ZIP stay.

The previously verified EXE and delivery ZIP still represent717cc2f and do not
contain these two changes. Rebuild and actual-game verification remain later
steps after authored recovery; final inventory/source optimality remain open.
