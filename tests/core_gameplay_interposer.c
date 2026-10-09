/* Native-test boundaries for real production sound/RNG/render references. */
#include "gameplay.h"
#include "core.h"
#include "display.h"
#include "sound.h"
#include "startup.h"
#include <stdio.h>
#include <stdlib.h>

static DxBallGameplayOps *bound_ops;
static DxBallRenderOps *bound_render;
static DxBallFrameOps *bound_frame;
static unsigned stop_active, play_active, random_active;
static unsigned invalidate_active, effect_active;

static void binding_failure(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    abort();
}

int dxball_test_bind_gameplay_ops(DxBallGameplayOps *ops)
{
    if (ops == NULL) return -1;
    if (ops->stop_sound == NULL || ops->play_sound == NULL || ops->random_range == NULL)
        return -2;
    if (ops->stop_sound == dxball_stop_sound || ops->play_sound == dxball_play_sound ||
        ops->random_range == dxball_random_range) return -3;
    bound_ops = ops;
    return 0;
}

int dxball_test_bind_render_frame_ops(DxBallRenderOps *render, DxBallFrameOps *frame)
{
    if (render == NULL || frame == NULL) return -1;
    if (render->invalidate == NULL || frame->draw_effect_sprite == NULL) return -2;
    if (render->invalidate == dxball_invalidate_region ||
        frame->draw_effect_sprite == dxball_draw_effect_sprite) return -3;
    bound_render = render;
    bound_frame = frame;
    return 0;
}

void dxball_invalidate_region(DxBallRect rect)
{
    if (bound_render == NULL || bound_render->invalidate == NULL)
        binding_failure("CoreNative invalidate_region: fixture table is unbound or callback is null");
    if (invalidate_active || bound_render->invalidate == dxball_invalidate_region)
        binding_failure("CoreNative invalidate_region: recursive interposer callback");
    invalidate_active = 1;
    bound_render->invalidate(rect);
    invalidate_active = 0;
}

void dxball_draw_effect_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    if (bound_frame == NULL || bound_frame->draw_effect_sprite == NULL)
        binding_failure("CoreNative draw_effect_sprite: fixture table is unbound or callback is null");
    if (effect_active || bound_frame->draw_effect_sprite == dxball_draw_effect_sprite)
        binding_failure("CoreNative draw_effect_sprite: recursive interposer callback");
    effect_active = 1;
    bound_frame->draw_effect_sprite(sprite, x, y);
    effect_active = 0;
}

void dxball_stop_sound(DxBallInt sound)
{
    if (bound_ops == NULL || bound_ops->stop_sound == NULL)
        binding_failure("CoreNative stop_sound: fixture table is unbound or callback is null");
    if (stop_active || bound_ops->stop_sound == dxball_stop_sound)
        binding_failure("CoreNative stop_sound: recursive interposer callback");
    stop_active = 1;
    bound_ops->stop_sound(sound);
    stop_active = 0;
}

void dxball_play_sound(DxBallInt sound, DxBallInt frequency, DxBallInt pan, DxBallInt volume)
{
    if (bound_ops == NULL || bound_ops->play_sound == NULL)
        binding_failure("CoreNative play_sound: fixture table is unbound or callback is null");
    if (play_active || bound_ops->play_sound == dxball_play_sound)
        binding_failure("CoreNative play_sound: recursive interposer callback");
    play_active = 1;
    bound_ops->play_sound(sound, frequency, pan, volume);
    play_active = 0;
}

DxBallInt dxball_random_range(DxBallInt limit)
{
    DxBallInt result;
    if (bound_ops == NULL || bound_ops->random_range == NULL)
        binding_failure("CoreNative random_range: fixture table is unbound or callback is null");
    if (random_active || bound_ops->random_range == dxball_random_range)
        binding_failure("CoreNative random_range: recursive interposer callback");
    random_active = 1;
    result = bound_ops->random_range(limit);
    random_active = 0;
    return result;
}
