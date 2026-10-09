/* Native-test boundaries for real production sound/RNG/render/lifecycle references. */
#include "gameplay.h"
#include "core.h"
#include "display.h"
#include "device.h"
#include "midi.h"
#include "sound.h"
#include "startup.h"
#include <stdio.h>
#include <stdlib.h>

static DxBallGameplayOps *bound_ops;
static DxBallRenderOps *bound_render;
static DxBallFrameOps *bound_frame;
static DxBallRuntimeOps *bound_runtime;
static unsigned stop_active, play_active, random_active;
static unsigned invalidate_active, effect_active;
static unsigned palette_load_active, palette_active, clear_active, reset_active;
static unsigned sounds_release_active, banks_release_active, music_close_active, wait_active;

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
    if (render->invalidate == NULL || frame->draw_effect_sprite == NULL ||
        frame->wait_frames == NULL) return -2;
    if (render->invalidate == dxball_invalidate_region ||
        frame->draw_effect_sprite == dxball_draw_effect_sprite ||
        frame->wait_frames == dxball_wait_frames) return -3;
    bound_render = render;
    bound_frame = frame;
    return 0;
}

int dxball_test_bind_runtime_ops(DxBallRuntimeOps *ops)
{
    if (ops == NULL) return -1;
    if (ops->load_saved_palette == NULL || ops->palette_transition == NULL ||
        ops->clear_surface == NULL || ops->reset_regions == NULL ||
        ops->release_sounds == NULL || ops->release_sprite_banks == NULL ||
        ops->finalize_game_resources == NULL) return -2;
    if (ops->load_saved_palette == dxball_load_saved_palette ||
        ops->palette_transition == dxball_palette_transition ||
        ops->clear_surface == dxball_clear_surface || ops->reset_regions == dxball_reset_regions ||
        ops->release_sounds == dxball_release_sounds ||
        ops->release_sprite_banks == dxball_release_sprite_banks ||
        ops->finalize_game_resources == dxball_close_music) return -3;
    bound_runtime = ops;
    return 0;
}

void dxball_load_saved_palette(const char *path)
{
    if (bound_runtime == NULL || bound_runtime->load_saved_palette == NULL)
        binding_failure("CoreNative load_saved_palette: fixture table is unbound or callback is null");
    if (palette_load_active || bound_runtime->load_saved_palette == dxball_load_saved_palette)
        binding_failure("CoreNative load_saved_palette: recursive interposer callback");
    palette_load_active = 1;
    bound_runtime->load_saved_palette(path);
    palette_load_active = 0;
}

void dxball_palette_transition(DxBallInt frames, DxBallInt step,
                               DxBallInt first, DxBallInt last, DxBallInt direction)
{
    if (bound_runtime == NULL || bound_runtime->palette_transition == NULL)
        binding_failure("CoreNative palette_transition: fixture table is unbound or callback is null");
    if (palette_active || bound_runtime->palette_transition == dxball_palette_transition)
        binding_failure("CoreNative palette_transition: recursive interposer callback");
    palette_active = 1;
    bound_runtime->palette_transition(frames, step, first, last, direction);
    palette_active = 0;
}

void dxball_clear_surface(DxBallSurface surface, DxBallInt color)
{
    if (bound_runtime == NULL || bound_runtime->clear_surface == NULL)
        binding_failure("CoreNative clear_surface: fixture table is unbound or callback is null");
    if (clear_active || bound_runtime->clear_surface == dxball_clear_surface)
        binding_failure("CoreNative clear_surface: recursive interposer callback");
    clear_active = 1;
    bound_runtime->clear_surface(surface, color);
    clear_active = 0;
}

void dxball_reset_regions(void)
{
    if (bound_runtime == NULL || bound_runtime->reset_regions == NULL)
        binding_failure("CoreNative reset_regions: fixture table is unbound or callback is null");
    if (reset_active || bound_runtime->reset_regions == dxball_reset_regions)
        binding_failure("CoreNative reset_regions: recursive interposer callback");
    reset_active = 1;
    bound_runtime->reset_regions();
    reset_active = 0;
}

void dxball_release_sounds(void)
{
    if (bound_runtime == NULL || bound_runtime->release_sounds == NULL)
        binding_failure("CoreNative release_sounds: fixture table is unbound or callback is null");
    if (sounds_release_active || bound_runtime->release_sounds == dxball_release_sounds)
        binding_failure("CoreNative release_sounds: recursive interposer callback");
    sounds_release_active = 1;
    bound_runtime->release_sounds();
    sounds_release_active = 0;
}

void dxball_release_sprite_banks(void)
{
    if (bound_runtime == NULL || bound_runtime->release_sprite_banks == NULL)
        binding_failure("CoreNative release_sprite_banks: fixture table is unbound or callback is null");
    if (banks_release_active || bound_runtime->release_sprite_banks == dxball_release_sprite_banks)
        binding_failure("CoreNative release_sprite_banks: recursive interposer callback");
    banks_release_active = 1;
    bound_runtime->release_sprite_banks();
    banks_release_active = 0;
}

void dxball_close_music(void)
{
    if (bound_runtime == NULL || bound_runtime->finalize_game_resources == NULL)
        binding_failure("CoreNative close_music: fixture table is unbound or callback is null");
    if (music_close_active || bound_runtime->finalize_game_resources == dxball_close_music)
        binding_failure("CoreNative close_music: recursive interposer callback");
    music_close_active = 1;
    bound_runtime->finalize_game_resources();
    music_close_active = 0;
}

void dxball_wait_frames(DxBallInt frames)
{
    if (bound_frame == NULL || bound_frame->wait_frames == NULL)
        binding_failure("CoreNative wait_frames: fixture table is unbound or callback is null");
    if (wait_active || bound_frame->wait_frames == dxball_wait_frames)
        binding_failure("CoreNative wait_frames: recursive interposer callback");
    wait_active = 1;
    bound_frame->wait_frames(frames);
    wait_active = 0;
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
