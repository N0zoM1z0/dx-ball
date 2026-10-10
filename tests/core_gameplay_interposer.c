/* Native-test boundaries for real production sound/RNG/render/lifecycle references. */
#include "gameplay.h"
#include "core.h"
#include "effects.h"
#include "allocator.h"
#include "bonuses.h"
#include "particles.h"
#include "display.h"
#include "device.h"
#include "midi.h"
#include "sound.h"
#include "startup.h"
#include "ui.h"
#include "platform.h"
#include "intro.h"
#include "editor.h"
#include "gameover.h"
#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static DxBallGameplayOps *bound_ops;
static DxBallGameplayOps *bound_particle_ops;
static void (*real_particle)(DxBallInt, DxBallInt, DxBallInt, DxBallInt, DxBallInt, DxBallInt);
static unsigned particle_active;
static DxBallGameplayOps *bound_brick_effect_ops;
static void (*real_brick_effect)(DxBallInt, DxBallInt, DxBallByte, DxBallInt);
static unsigned brick_effect_active;
static DxBallGameplayOps *bound_new_ops;
static void *(DXBALL_NEW_CALL *real_new)(DxBallUInt);
static void *(*new_default)(size_t);
static unsigned new_active;
static DxBallRenderOps *bound_render;
static DxBallFrameOps *bound_frame;
static DxBallEffectOps *bound_effect;
static void (DXBALL_NEW_CALL *real_delete)(void *);
static void (*real_sprite)(DxBallInt, DxBallInt, DxBallInt);
static void (*real_reduced)(DxBallInt, DxBallInt, DxBallInt);
static void (*real_region)(DxBallRect);
static void (*region_default)(DxBallInt, DxBallInt, DxBallInt, DxBallInt);
static void (**bound_particle_region)(DxBallInt, DxBallInt, DxBallInt, DxBallInt);
static void (*real_queue_region)(DxBallRect);
static void (*particle_region_default)(DxBallInt, DxBallInt, DxBallInt, DxBallInt);
static unsigned queue_region_active;
static unsigned delete_active, sprite_active, reduced_active, region_active;
static DxBallRuntimeOps *bound_runtime;
static DxBallPlatformOps *bound_platform;
static DxBallKeyModeOps *bound_keys;
static DxBallModeOps *bound_modes;
static void (*real_modes[7])(void);
static unsigned mode_active[7];
static void (*real_mode_lifecycle[8])(void);
static void (*real_mode_cleanup[4])(DxBallInt);
static unsigned mode_lifecycle_active[12];
static unsigned intro_key_active, editor_key_active, game_over_key_active, splash_key_active;
static DxBallDisplayOps *bound_display;
static void (*real_recover_surfaces)(void);
static unsigned recover_surfaces_active;
static unsigned sound_update_active;
static void (*platform_music_default)(const char *, DxBallInt);
static unsigned music_load_active, prepare_sound_active;
static unsigned initialize_sound_active, pause_sound_active;
static unsigned resume_music_active, pause_music_active, release_audio_active;
static unsigned stop_active, play_active, random_active;
static unsigned invalidate_active, effect_active;
static unsigned palette_load_active, palette_active, clear_active, reset_active;
static unsigned sounds_release_active, banks_release_active, music_close_active, wait_active;
static unsigned pcx_load_active, bank_load_active, capture_active, sound_load_active;
static unsigned board_bind_active, display_bind_active, centered_text_active;
static unsigned text_active, keyed_active;
static unsigned current_time_active, elapsed_active, animate_palette_active, update_score_active, restore_regions_active, draw_paddle_active, last_brick_active, draw_last_brick_active, present_active, restart_round_active, bonus_active;

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

/* The loader verifies this real body's copied-image ownership. Stage it before
   unchanged inherited constructors replace the current GameplayOps slots. */
int dxball_test_bind_particle_ops(DxBallGameplayOps *ops,
                                  void (*real)(DxBallInt, DxBallInt, DxBallInt,
                                               DxBallInt, DxBallInt, DxBallInt))
{
    if (real == NULL) return -1;
    if (real == dxball_spawn_particle) return -2;
    bound_particle_ops = ops;
    real_particle = real;
    return 0;
}

void dxball_spawn_particle(DxBallInt x, DxBallInt y, DxBallInt dx, DxBallInt dy,
                           DxBallInt color, DxBallInt gravity)
{
    void (*callback)(DxBallInt, DxBallInt, DxBallInt, DxBallInt, DxBallInt, DxBallInt);
    callback = real_particle;
    if (bound_particle_ops != NULL && bound_particle_ops->particle != NULL &&
        bound_particle_ops->particle != dxball_spawn_particle)
        callback = bound_particle_ops->particle;
    if (callback == NULL || callback == dxball_spawn_particle || particle_active)
        binding_failure("CoreNative spawn_particle: missing real owner or recursive callback");
    particle_active = 1;
    callback(x, y, dx, dy, color, gravity);
    particle_active = 0;
}

/* The loader stages the genuine copied-image body before fixture callbacks. */
int dxball_test_bind_brick_effect_ops(DxBallGameplayOps *ops,
                                      void (*real)(DxBallInt, DxBallInt,
                                                   DxBallByte, DxBallInt))
{
    if (real == NULL) return -1;
    if (real == dxball_spawn_brick_effect) return -2;
    bound_brick_effect_ops = ops;
    real_brick_effect = real;
    return 0;
}

void dxball_spawn_brick_effect(DxBallInt x, DxBallInt y, DxBallByte tile, DxBallInt mode)
{
    void (*callback)(DxBallInt, DxBallInt, DxBallByte, DxBallInt);
    callback = real_brick_effect;
    if (bound_brick_effect_ops != NULL && bound_brick_effect_ops->brick_effect != NULL &&
        bound_brick_effect_ops->brick_effect != dxball_spawn_brick_effect)
        callback = bound_brick_effect_ops->brick_effect;
    if (callback == NULL || callback == dxball_spawn_brick_effect || brick_effect_active)
        binding_failure("CoreNative spawn_brick_effect: missing real owner or recursive callback");
    brick_effect_active = 1;
    callback(x, y, tile, mode);
    brick_effect_active = 0;
}

/* The size_t table has its own genuine host adapter for the uint32_t API. */
int dxball_test_bind_new_ops(DxBallGameplayOps *ops,
                            void *(DXBALL_NEW_CALL *real)(DxBallUInt),
                            void *(*default_allocate)(size_t))
{
    if (ops == NULL || real == NULL || default_allocate == NULL) return -1;
    if (real == dxball_runtime_new ||
        (void (*)(void))default_allocate == (void (*)(void))dxball_runtime_new) return -2;
    bound_new_ops = ops;
    real_new = real;
    new_default = default_allocate;
    return 0;
}

void *DXBALL_NEW_CALL dxball_runtime_new(DxBallUInt bytes)
{
    void *(*callback)(size_t) = NULL;
    void *result;
    if (real_new == NULL || real_new == dxball_runtime_new || new_active)
        binding_failure("CoreNative runtime_new: missing real owner or recursive callback");
    if (bound_new_ops != NULL) callback = bound_new_ops->allocate_node;
    new_active = 1;
    if (callback != NULL && callback != new_default &&
        (void (*)(void))callback != (void (*)(void))dxball_runtime_new)
        result = callback((size_t)bytes);
    else
        result = real_new(bytes);
    new_active = 0;
    return result;
}

/* Stage genuine current tables before inherited fixtures install callbacks. */
int dxball_test_bind_effect_render_ops(DxBallEffectOps *effect, DxBallRenderOps *render,
    void (DXBALL_NEW_CALL *deallocate)(void *),
    void (*sprite)(DxBallInt, DxBallInt, DxBallInt),
    void (*reduced)(DxBallInt, DxBallInt, DxBallInt),
    void (*region)(DxBallRect),
    void (*region_adapter)(DxBallInt, DxBallInt, DxBallInt, DxBallInt))
{
    if (effect == NULL || render == NULL || deallocate == NULL || sprite == NULL ||
        reduced == NULL || region == NULL || region_adapter == NULL) return -1;
    if (deallocate == dxball_runtime_delete || sprite == dxball_draw_sprite ||
        reduced == dxball_draw_reduced_sprite || region == dxball_restore_effect_region) return -2;
    bound_effect = effect;
    bound_render = render;
    real_delete = deallocate;
    real_sprite = sprite;
    real_reduced = reduced;
    real_region = region;
    region_default = region_adapter;
    return 0;
}

void DXBALL_NEW_CALL dxball_runtime_delete(void *node)
{
    void (DXBALL_NEW_CALL *callback)(void *) = real_delete;
    if (bound_effect != NULL && bound_effect->deallocate_node != NULL &&
        bound_effect->deallocate_node != dxball_runtime_delete)
        callback = bound_effect->deallocate_node;
    if (callback == NULL || callback == dxball_runtime_delete || delete_active)
        binding_failure("CoreNative runtime_delete: missing real owner or recursive callback");
    delete_active = 1;
    callback(node);
    delete_active = 0;
}

void dxball_draw_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    void (*callback)(DxBallInt, DxBallInt, DxBallInt) = real_sprite;
    if (bound_render != NULL && bound_render->sprite != NULL &&
        bound_render->sprite != dxball_draw_sprite) callback = bound_render->sprite;
    if (callback == NULL || callback == dxball_draw_sprite || sprite_active)
        binding_failure("CoreNative draw_sprite: missing real owner or recursive callback");
    sprite_active = 1;
    callback(sprite, x, y);
    sprite_active = 0;
}

void dxball_draw_reduced_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    void (*callback)(DxBallInt, DxBallInt, DxBallInt) = real_reduced;
    if (bound_effect != NULL && bound_effect->reduced_sprite != NULL &&
        bound_effect->reduced_sprite != dxball_draw_reduced_sprite) callback = bound_effect->reduced_sprite;
    if (callback == NULL || callback == dxball_draw_reduced_sprite || reduced_active)
        binding_failure("CoreNative draw_reduced_sprite: missing real owner or recursive callback");
    reduced_active = 1;
    callback(sprite, x, y);
    reduced_active = 0;
}

void dxball_restore_effect_region(DxBallRect rect)
{
    void (*callback)(DxBallInt, DxBallInt, DxBallInt, DxBallInt) = NULL;
    if (bound_effect != NULL && bound_effect->region != region_default)
        callback = bound_effect->region;
    if (real_region == NULL || real_region == dxball_restore_effect_region || region_active)
        binding_failure("CoreNative restore_effect_region: missing real owner or recursive callback");
    region_active = 1;
    if (callback != NULL)
        callback(rect.left, rect.top, rect.right, rect.bottom);
    else
        real_region(rect);
    region_active = 0;
}

int dxball_test_bind_particle_region(
    void (**slot)(DxBallInt, DxBallInt, DxBallInt, DxBallInt),
    void (*real)(DxBallRect),
    void (*default_bounds)(DxBallInt, DxBallInt, DxBallInt, DxBallInt))
{
    if (slot == NULL || real == NULL || real == dxball_queue_region || default_bounds == NULL) return -1;
    bound_particle_region = slot;
    real_queue_region = real;
    particle_region_default = default_bounds;
    return 0;
}

void dxball_queue_region(DxBallRect rect)
{
    void (*callback)(DxBallInt, DxBallInt, DxBallInt, DxBallInt) = NULL;
    if (bound_particle_region != NULL && *bound_particle_region != NULL &&
        *bound_particle_region != particle_region_default) callback = *bound_particle_region;
    if (real_queue_region == NULL || real_queue_region == dxball_queue_region || queue_region_active)
        binding_failure("CoreNative queue_region: missing real owner or recursive callback");
    queue_region_active = 1;
    if (callback != NULL)
        callback(rect.left, rect.top, rect.right, rect.bottom);
    else
        real_queue_region(rect);
    queue_region_active = 0;
}

int dxball_test_bind_render_frame_ops(DxBallRenderOps *render, DxBallFrameOps *frame,
                                     DxBallEffectOps *effect)
{
    if (render == NULL || frame == NULL || effect == NULL) return -1;
    if (render->invalidate == NULL || frame->draw_effect_sprite == NULL ||
        frame->wait_frames == NULL || effect->keyed_sprite == NULL) return -2;
    if (render->invalidate == dxball_invalidate_region ||
        frame->draw_effect_sprite == dxball_draw_effect_sprite ||
        frame->wait_frames == dxball_wait_frames ||
        effect->keyed_sprite == dxball_draw_keyed_sprite) return -3;
    if (frame->current_time == NULL ||
        frame->elapsed == NULL ||
        frame->animate_palette == NULL ||
        frame->update_score == NULL ||
        frame->restore_regions == NULL ||
        frame->draw_paddle == NULL ||
        frame->last_brick == NULL ||
        frame->draw_last_brick == NULL ||
        frame->present == NULL ||
        frame->restart_round == NULL ||
        effect->bonus == NULL) return -2;
    if (frame->current_time == dxball_current_time ||
        frame->elapsed == dxball_elapsed ||
        frame->animate_palette == dxball_animate_palette ||
        frame->update_score == dxball_refresh_score ||
        frame->restore_regions == dxball_restore_regions ||
        frame->draw_paddle == dxball_draw_paddle ||
        frame->last_brick == dxball_last_brick ||
        frame->draw_last_brick == dxball_draw_last_brick ||
        frame->present == dxball_present ||
        frame->restart_round == dxball_restart_round ||
        effect->bonus == dxball_generate_bonus) return -3;
    bound_render = render;
    bound_frame = frame;
    bound_effect = effect;
    return 0;
}

int dxball_test_bind_runtime_ops(DxBallRuntimeOps *ops)
{
    if (ops == NULL) return -1;
    if (ops->load_saved_palette == NULL || ops->palette_transition == NULL ||
        ops->clear_surface == NULL || ops->reset_regions == NULL ||
        ops->load_pcx == NULL || ops->load_sprite_bank == NULL || ops->capture_sprite == NULL ||
        ops->load_sound == NULL || ops->bind_board_surface == NULL ||
        ops->bind_display_surface == NULL || ops->draw_text == NULL ||
        ops->draw_centered_text == NULL ||
        ops->release_sounds == NULL || ops->release_sprite_banks == NULL ||
        ops->finalize_game_resources == NULL) return -2;
    if (ops->load_saved_palette == dxball_load_saved_palette ||
        ops->palette_transition == dxball_palette_transition ||
        ops->clear_surface == dxball_clear_surface || ops->reset_regions == dxball_reset_regions ||
        ops->load_pcx == dxball_load_pcx || ops->load_sprite_bank == dxball_load_sprite_bank ||
        ops->capture_sprite == dxball_capture_sprite || ops->load_sound == dxball_load_sound ||
        ops->bind_board_surface == dxball_bind_board_surface ||
        ops->bind_display_surface == dxball_bind_display_surface ||
        ops->draw_text == dxball_draw_text ||
        ops->draw_centered_text == dxball_draw_centered_text ||
        ops->release_sounds == dxball_release_sounds ||
        ops->release_sprite_banks == dxball_release_sprite_banks ||
        ops->finalize_game_resources == dxball_close_music) return -3;
    bound_runtime = ops;
    return 0;
}

/* DisplayNative installs its callback after inherited CoreNative construction.
   Bind the actual copied table now; validate the live slot on every call. */
int dxball_test_bind_display_ops(DxBallDisplayOps *ops, void (*recover)(void))
{
    if (ops == NULL || recover == NULL) return -1;
    if (recover == dxball_recover_surfaces) return -2;
    bound_display = ops;
    real_recover_surfaces = recover;
    return 0;
}

void dxball_recover_surfaces(void)
{
    void (*callback)(void);
    callback = real_recover_surfaces;
    if (bound_display != NULL && bound_display->recover_surfaces != NULL &&
        bound_display->recover_surfaces != dxball_recover_surfaces)
        callback = bound_display->recover_surfaces;
    if (callback == NULL || callback == dxball_recover_surfaces || recover_surfaces_active)
        binding_failure("CoreNative recover_surfaces: missing real owner or recursive callback");
    recover_surfaces_active = 1;
    callback();
    recover_surfaces_active = 0;
}

void dxball_update_sound(DxBallInt slot, DxBallInt frequency,
                         DxBallInt pan, DxBallInt volume)
{
    if (bound_display == NULL || bound_display->update_sound == NULL)
        binding_failure("CoreNative update_sound: fixture table is unbound or callback is null");
    if (sound_update_active || bound_display->update_sound == dxball_update_sound)
        binding_failure("CoreNative update_sound: recursive or unreplaced display callback");
    sound_update_active = 1;
    bound_display->update_sound(slot, frequency, pan, volume);
    sound_update_active = 0;
}

/* PlatformNative replaces this void callback after inherited fixture binders.
   Stage the actual table now; reject its untouched adapter before invocation. */
int dxball_test_bind_platform_ops(DxBallPlatformOps *ops,
                                 void (*default_music)(const char *, DxBallInt))
{
    if (ops == NULL || default_music == NULL) return -1;
    bound_platform = ops;
    platform_music_default = default_music;
    return 0;
}

int dxball_test_bind_key_mode_ops(DxBallKeyModeOps *ops)
{
    if (ops == NULL) return -1;
    bound_keys = ops;
    return 0;
}

int dxball_test_bind_mode_ops(DxBallModeOps *ops,
                             void (*intro)(void), void (*game)(void),
                             void (*editor)(void), void (*game_over)(void),
                             void (*splash)(void), void (*device)(void),
                             void (*synchronize)(void))
{
    void (*owners[7])(void) = {intro, game, editor, game_over, splash, device, synchronize};
    void (*wrappers[7])(void) = {dxball_intro_frame, dxball_game_frame,
        dxball_editor_frame, dxball_game_over_frame, dxball_splash_frame,
        dxball_initialize_device_state, dxball_synchronize_surface};
    unsigned i;
    if (ops == NULL) return -1;
    for (i = 0; i < 7; ++i)
        if (owners[i] == NULL || owners[i] == wrappers[i]) return -2;
    bound_modes = ops;
    for (i = 0; i < 7; ++i) real_modes[i] = owners[i];
    return 0;
}

/* Read the live fixture slot; untouched defaults use the copied real owner. */
#define MODE_FORWARD(name, index, member) \
void name(void) \
{ \
    void (*callback)(void); \
    if (bound_modes == NULL) binding_failure("CoreNative " #name ": unbound modes"); \
    callback = bound_modes->member; \
    if (callback == name) callback = real_modes[index]; \
    if (callback == NULL || callback == name || mode_active[index]) \
        binding_failure("CoreNative " #name ": null or recursive callback"); \
    mode_active[index] = 1; \
    callback(); \
    mode_active[index] = 0; \
}
MODE_FORWARD(dxball_intro_frame, 0, frame[0])
MODE_FORWARD(dxball_game_frame, 1, frame[1])
MODE_FORWARD(dxball_editor_frame, 2, frame[2])
MODE_FORWARD(dxball_game_over_frame, 3, frame[3])
MODE_FORWARD(dxball_splash_frame, 4, frame[4])
MODE_FORWARD(dxball_initialize_device_state, 5, reinitialize_device)
MODE_FORWARD(dxball_synchronize_surface, 6, synchronize_surface)
#undef MODE_FORWARD

int dxball_test_bind_mode_lifecycle_ops(DxBallModeOps *ops,
    void (*initialize_intro)(void), void (*initialize_editor)(void),
    void (*initialize_game_over)(void), void (*initialize_splash)(void),
    void (*redraw_intro)(void), void (*redraw_editor)(void),
    void (*redraw_game_over)(void), void (*redraw_splash)(void),
    void (*dispose_intro)(DxBallInt), void (*dispose_editor)(DxBallInt),
    void (*dispose_game_over)(DxBallInt), void (*dispose_splash)(DxBallInt))
{
    void (*owners[8])(void) = {initialize_intro, initialize_editor,
        initialize_game_over, initialize_splash, redraw_intro, redraw_editor,
        redraw_game_over, redraw_splash};
    void (*wrappers[8])(void) = {dxball_initialize_intro, dxball_initialize_editor,
        dxball_initialize_game_over, dxball_initialize_splash, dxball_redraw_intro,
        dxball_redraw_editor, dxball_redraw_game_over, dxball_redraw_splash};
    void (*cleanup[4])(DxBallInt) = {dispose_intro, dispose_editor,
        dispose_game_over, dispose_splash};
    void (*cleanup_wrappers[4])(DxBallInt) = {dxball_dispose_intro,
        dxball_dispose_editor, dxball_dispose_game_over, dxball_dispose_splash};
    unsigned i;
    if (ops == NULL || ops != bound_modes) return -1;
    for (i = 0; i < 8; ++i)
        if (owners[i] == NULL || owners[i] == wrappers[i]) return -2;
    for (i = 0; i < 4; ++i)
        if (cleanup[i] == NULL || cleanup[i] == cleanup_wrappers[i]) return -2;
    for (i = 0; i < 8; ++i) real_mode_lifecycle[i] = owners[i];
    for (i = 0; i < 4; ++i) real_mode_cleanup[i] = cleanup[i];
    return 0;
}

#define MODE_LIFECYCLE_FORWARD(name, index, member) \
void name(void) \
{ \
    void (*callback)(void); \
    if (bound_modes == NULL) binding_failure("CoreNative " #name ": unbound modes"); \
    callback = bound_modes->member; \
    if (callback == name) callback = real_mode_lifecycle[index]; \
    if (callback == NULL || callback == name || mode_lifecycle_active[index]) \
        binding_failure("CoreNative " #name ": null or recursive callback"); \
    mode_lifecycle_active[index] = 1; \
    callback(); \
    mode_lifecycle_active[index] = 0; \
}
MODE_LIFECYCLE_FORWARD(dxball_initialize_intro, 0, initialize[0])
MODE_LIFECYCLE_FORWARD(dxball_initialize_editor, 1, initialize[2])
MODE_LIFECYCLE_FORWARD(dxball_initialize_game_over, 2, initialize[3])
MODE_LIFECYCLE_FORWARD(dxball_initialize_splash, 3, initialize[4])
MODE_LIFECYCLE_FORWARD(dxball_redraw_intro, 4, redraw[0])
MODE_LIFECYCLE_FORWARD(dxball_redraw_editor, 5, redraw[2])
MODE_LIFECYCLE_FORWARD(dxball_redraw_game_over, 6, redraw[3])
MODE_LIFECYCLE_FORWARD(dxball_redraw_splash, 7, redraw[4])
#undef MODE_LIFECYCLE_FORWARD

#define MODE_CLEANUP_FORWARD(name, index, slot) \
void name(DxBallInt fade) \
{ \
    void (*callback)(DxBallInt); \
    if (bound_modes == NULL) binding_failure("CoreNative " #name ": unbound modes"); \
    callback = bound_modes->cleanup[slot]; \
    if (callback == name) callback = real_mode_cleanup[index]; \
    if (callback == NULL || callback == name || mode_lifecycle_active[8 + index]) \
        binding_failure("CoreNative " #name ": null or recursive callback"); \
    mode_lifecycle_active[8 + index] = 1; \
    callback(fade); \
    mode_lifecycle_active[8 + index] = 0; \
}
MODE_CLEANUP_FORWARD(dxball_dispose_intro, 0, 0)
MODE_CLEANUP_FORWARD(dxball_dispose_editor, 1, 2)
MODE_CLEANUP_FORWARD(dxball_dispose_game_over, 2, 3)
MODE_CLEANUP_FORWARD(dxball_dispose_splash, 3, 4)
#undef MODE_CLEANUP_FORWARD

void dxball_intro_key(char key)
{
    if (bound_keys == NULL || bound_keys->mode[0] == NULL)
        binding_failure("CoreNative intro_key: fixture table is unbound or callback is null");
    if (intro_key_active || bound_keys->mode[0] == dxball_intro_key)
        binding_failure("CoreNative intro_key: recursive or unreplaced callback");
    intro_key_active = 1;
    bound_keys->mode[0](key);
    intro_key_active = 0;
}

void dxball_editor_key(char key)
{
    if (bound_keys == NULL || bound_keys->mode[2] == NULL)
        binding_failure("CoreNative editor_key: fixture table is unbound or callback is null");
    if (editor_key_active || bound_keys->mode[2] == dxball_editor_key)
        binding_failure("CoreNative editor_key: recursive or unreplaced callback");
    editor_key_active = 1;
    bound_keys->mode[2](key);
    editor_key_active = 0;
}

void dxball_game_over_key(char key)
{
    if (bound_keys == NULL || bound_keys->mode[3] == NULL)
        binding_failure("CoreNative game_over_key: fixture table is unbound or callback is null");
    if (game_over_key_active || bound_keys->mode[3] == dxball_game_over_key)
        binding_failure("CoreNative game_over_key: recursive or unreplaced callback");
    game_over_key_active = 1;
    bound_keys->mode[3](key);
    game_over_key_active = 0;
}

void dxball_splash_key(char key)
{
    if (bound_keys == NULL || bound_keys->mode4 == NULL)
        binding_failure("CoreNative splash_key: fixture table is unbound or callback is null");
    if (splash_key_active || bound_keys->mode4 == dxball_splash_key)
        binding_failure("CoreNative splash_key: recursive or unreplaced callback");
    splash_key_active = 1;
    bound_keys->mode4(key);
    splash_key_active = 0;
}

/* The startup caller uses this real sound entry; PlatformNative supplies its
   existing controlled audio boundary through the current PlatformOps slot. */
void dxball_prepare_sound(DxBallHandle window)
{
    if (bound_platform == NULL || bound_platform->prepare_sound == NULL)
        binding_failure("CoreNative prepare_sound: fixture table is unbound or callback is null");
    if (prepare_sound_active || bound_platform->prepare_sound == dxball_prepare_sound)
        binding_failure("CoreNative prepare_sound: recursive or unreplaced platform callback");
    prepare_sound_active = 1;
    bound_platform->prepare_sound(window);
    prepare_sound_active = 0;
}

void dxball_initialize_sound(DxBallHandle window)
{
    if (bound_platform == NULL || bound_platform->initialize_sound == NULL)
        binding_failure("CoreNative initialize_sound: fixture table is unbound or callback is null");
    if (initialize_sound_active || bound_platform->initialize_sound == dxball_initialize_sound)
        binding_failure("CoreNative initialize_sound: recursive or unreplaced platform callback");
    initialize_sound_active = 1;
    bound_platform->initialize_sound(window);
    initialize_sound_active = 0;
}

void dxball_pause_sound(void)
{
    if (bound_platform == NULL || bound_platform->pause_sound == NULL)
        binding_failure("CoreNative pause_sound: fixture table is unbound or callback is null");
    if (pause_sound_active || bound_platform->pause_sound == dxball_pause_sound)
        binding_failure("CoreNative pause_sound: recursive or unreplaced platform callback");
    pause_sound_active = 1;
    bound_platform->pause_sound();
    pause_sound_active = 0;
}

void dxball_resume_music(void)
{
    if (bound_platform == NULL || bound_platform->resume_music == NULL)
        binding_failure("CoreNative resume_music: fixture table is unbound or callback is null");
    if (resume_music_active || bound_platform->resume_music == dxball_resume_music)
        binding_failure("CoreNative resume_music: recursive or unreplaced platform callback");
    resume_music_active = 1;
    bound_platform->resume_music();
    resume_music_active = 0;
}

void dxball_pause_music(void)
{
    if (bound_platform == NULL || bound_platform->pause_music == NULL)
        binding_failure("CoreNative pause_music: fixture table is unbound or callback is null");
    if (pause_music_active || bound_platform->pause_music == dxball_pause_music)
        binding_failure("CoreNative pause_music: recursive or unreplaced platform callback");
    pause_music_active = 1;
    bound_platform->pause_music();
    pause_music_active = 0;
}

void dxball_release_audio(void)
{
    if (bound_platform == NULL || bound_platform->release_audio == NULL)
        binding_failure("CoreNative release_audio: fixture table is unbound or callback is null");
    if (release_audio_active || bound_platform->release_audio == dxball_release_audio)
        binding_failure("CoreNative release_audio: recursive or unreplaced platform callback");
    release_audio_active = 1;
    bound_platform->release_audio();
    release_audio_active = 0;
}

DxBallInt dxball_load_music(const char *path, DxBallInt play)
{
    DxBallInt (*self)(const char *, DxBallInt) = dxball_load_music;
    _Static_assert(sizeof self == sizeof bound_platform->load_music,
                   "ELF host music callback address sizes must agree");
    if (bound_platform == NULL || bound_platform->load_music == NULL)
        binding_failure("CoreNative load_music: fixture table is unbound or callback is null");
    /* Compare address representations, never invoke an incompatible callback.
       The copied production default is a void adapter back into this symbol. */
    if (music_load_active || bound_platform->load_music == platform_music_default ||
        memcmp(&bound_platform->load_music, &self, sizeof self) == 0)
        binding_failure("CoreNative load_music: recursive or unreplaced platform callback");
    music_load_active = 1;
    bound_platform->load_music(path, play);
    music_load_active = 0;
    /* The reviewed intro caller discards the integer result; its existing
       fixture boundary is void, so no music-result semantics are claimed. */
    return 0;
}

void dxball_draw_text(DxBallInt x, DxBallInt baseline, DxBallInt count, const char *text)
{
    if (bound_runtime == NULL || bound_runtime->draw_text == NULL)
        binding_failure("CoreNative draw_text: fixture table is unbound or callback is null");
    if (text_active || bound_runtime->draw_text == dxball_draw_text)
        binding_failure("CoreNative draw_text: recursive interposer callback");
    text_active = 1;
    bound_runtime->draw_text(x, baseline, count, text);
    text_active = 0;
}

void dxball_draw_keyed_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    if (bound_effect == NULL || bound_effect->keyed_sprite == NULL)
        binding_failure("CoreNative draw_keyed_sprite: fixture table is unbound or callback is null");
    if (keyed_active || bound_effect->keyed_sprite == dxball_draw_keyed_sprite)
        binding_failure("CoreNative draw_keyed_sprite: recursive interposer callback");
    keyed_active = 1;
    bound_effect->keyed_sprite(sprite, x, y);
    keyed_active = 0;
}

void dxball_load_pcx(DxBallDDSurface *surface, const char *path,
                     DxBallInt palette_mode, DxBallInt x, DxBallInt y)
{
    if (bound_runtime == NULL || bound_runtime->load_pcx == NULL)
        binding_failure("CoreNative load_pcx: fixture table is unbound or callback is null");
    if (pcx_load_active || bound_runtime->load_pcx == dxball_load_pcx)
        binding_failure("CoreNative load_pcx: recursive interposer callback");
    pcx_load_active = 1;
    bound_runtime->load_pcx(surface, path, palette_mode, x, y);
    pcx_load_active = 0;
}

void dxball_load_sprite_bank(DxBallInt bank, DxBallInt allocation_mode, const char *path)
{
    if (bound_runtime == NULL || bound_runtime->load_sprite_bank == NULL)
        binding_failure("CoreNative load_sprite_bank: fixture table is unbound or callback is null");
    if (bank_load_active || bound_runtime->load_sprite_bank == dxball_load_sprite_bank)
        binding_failure("CoreNative load_sprite_bank: recursive interposer callback");
    bank_load_active = 1;
    bound_runtime->load_sprite_bank(bank, allocation_mode, path);
    bank_load_active = 0;
}

void dxball_capture_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y,
                           DxBallInt width, DxBallInt height)
{
    if (bound_runtime == NULL || bound_runtime->capture_sprite == NULL)
        binding_failure("CoreNative capture_sprite: fixture table is unbound or callback is null");
    if (capture_active || bound_runtime->capture_sprite == dxball_capture_sprite)
        binding_failure("CoreNative capture_sprite: recursive interposer callback");
    capture_active = 1;
    bound_runtime->capture_sprite(sprite, x, y, width, height);
    capture_active = 0;
}

void dxball_load_sound(DxBallInt slot, const char *path)
{
    if (bound_runtime == NULL || bound_runtime->load_sound == NULL)
        binding_failure("CoreNative load_sound: fixture table is unbound or callback is null");
    if (sound_load_active || bound_runtime->load_sound == dxball_load_sound)
        binding_failure("CoreNative load_sound: recursive interposer callback");
    sound_load_active = 1;
    bound_runtime->load_sound(slot, path);
    sound_load_active = 0;
}

void dxball_bind_board_surface(DxBallSurface surface)
{
    if (bound_runtime == NULL || bound_runtime->bind_board_surface == NULL)
        binding_failure("CoreNative bind_board_surface: fixture table is unbound or callback is null");
    if (board_bind_active || bound_runtime->bind_board_surface == dxball_bind_board_surface)
        binding_failure("CoreNative bind_board_surface: recursive interposer callback");
    board_bind_active = 1;
    bound_runtime->bind_board_surface(surface);
    board_bind_active = 0;
}

void dxball_bind_display_surface(DxBallSurface surface)
{
    if (bound_runtime == NULL || bound_runtime->bind_display_surface == NULL)
        binding_failure("CoreNative bind_display_surface: fixture table is unbound or callback is null");
    if (display_bind_active || bound_runtime->bind_display_surface == dxball_bind_display_surface)
        binding_failure("CoreNative bind_display_surface: recursive interposer callback");
    display_bind_active = 1;
    bound_runtime->bind_display_surface(surface);
    display_bind_active = 0;
}

void dxball_draw_centered_text(DxBallInt x, DxBallInt baseline, DxBallInt count, const char *text)
{
    if (bound_runtime == NULL || bound_runtime->draw_centered_text == NULL)
        binding_failure("CoreNative draw_centered_text: fixture table is unbound or callback is null");
    if (centered_text_active || bound_runtime->draw_centered_text == dxball_draw_centered_text)
        binding_failure("CoreNative draw_centered_text: recursive interposer callback");
    centered_text_active = 1;
    bound_runtime->draw_centered_text(x, baseline, count, text);
    centered_text_active = 0;
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

DxBallUInt dxball_current_time(void)
{
    DxBallUInt result;
    if (bound_frame == NULL || bound_frame->current_time == NULL)
        binding_failure("CoreNative current_time: frame table is unbound or callback is null");
    if (current_time_active || bound_frame->current_time == dxball_current_time)
        binding_failure("CoreNative current_time: recursive interposer callback");
    current_time_active = 1;
    result = bound_frame->current_time();
    current_time_active = 0;
    return result;
}

DxBallInt dxball_elapsed(DxBallUInt start, DxBallUInt interval)
{
    DxBallInt result;
    if (bound_frame == NULL || bound_frame->elapsed == NULL)
        binding_failure("CoreNative elapsed: frame table is unbound or callback is null");
    if (elapsed_active || bound_frame->elapsed == dxball_elapsed)
        binding_failure("CoreNative elapsed: recursive interposer callback");
    elapsed_active = 1;
    result = bound_frame->elapsed(start, interval);
    elapsed_active = 0;
    return result;
}

void dxball_animate_palette(DxBallInt first, DxBallInt last, DxBallInt step)
{
    if (bound_frame == NULL || bound_frame->animate_palette == NULL)
        binding_failure("CoreNative animate_palette: frame table is unbound or callback is null");
    if (animate_palette_active || bound_frame->animate_palette == dxball_animate_palette)
        binding_failure("CoreNative animate_palette: recursive interposer callback");
    animate_palette_active = 1;
    bound_frame->animate_palette(first, last, step);
    animate_palette_active = 0;
}

void dxball_refresh_score(void)
{
    if (bound_frame == NULL || bound_frame->update_score == NULL)
        binding_failure("CoreNative refresh_score: frame table is unbound or callback is null");
    if (update_score_active || bound_frame->update_score == dxball_refresh_score)
        binding_failure("CoreNative refresh_score: recursive interposer callback");
    update_score_active = 1;
    bound_frame->update_score();
    update_score_active = 0;
}

void dxball_restore_regions(void)
{
    if (bound_frame == NULL || bound_frame->restore_regions == NULL)
        binding_failure("CoreNative restore_regions: frame table is unbound or callback is null");
    if (restore_regions_active || bound_frame->restore_regions == dxball_restore_regions)
        binding_failure("CoreNative restore_regions: recursive interposer callback");
    restore_regions_active = 1;
    bound_frame->restore_regions();
    restore_regions_active = 0;
}

void dxball_draw_paddle(void)
{
    if (bound_frame == NULL || bound_frame->draw_paddle == NULL)
        binding_failure("CoreNative draw_paddle: frame table is unbound or callback is null");
    if (draw_paddle_active || bound_frame->draw_paddle == dxball_draw_paddle)
        binding_failure("CoreNative draw_paddle: recursive interposer callback");
    draw_paddle_active = 1;
    bound_frame->draw_paddle();
    draw_paddle_active = 0;
}

void dxball_last_brick(void)
{
    if (bound_frame == NULL || bound_frame->last_brick == NULL)
        binding_failure("CoreNative last_brick: frame table is unbound or callback is null");
    if (last_brick_active || bound_frame->last_brick == dxball_last_brick)
        binding_failure("CoreNative last_brick: recursive interposer callback");
    last_brick_active = 1;
    bound_frame->last_brick();
    last_brick_active = 0;
}

void dxball_draw_last_brick(void)
{
    if (bound_frame == NULL || bound_frame->draw_last_brick == NULL)
        binding_failure("CoreNative draw_last_brick: frame table is unbound or callback is null");
    if (draw_last_brick_active || bound_frame->draw_last_brick == dxball_draw_last_brick)
        binding_failure("CoreNative draw_last_brick: recursive interposer callback");
    draw_last_brick_active = 1;
    bound_frame->draw_last_brick();
    draw_last_brick_active = 0;
}

void dxball_present(void)
{
    if (bound_frame == NULL || bound_frame->present == NULL)
        binding_failure("CoreNative present: frame table is unbound or callback is null");
    if (present_active || bound_frame->present == dxball_present)
        binding_failure("CoreNative present: recursive interposer callback");
    present_active = 1;
    bound_frame->present();
    present_active = 0;
}

void dxball_restart_round(void)
{
    if (bound_frame == NULL || bound_frame->restart_round == NULL)
        binding_failure("CoreNative restart_round: frame table is unbound or callback is null");
    if (restart_round_active || bound_frame->restart_round == dxball_restart_round)
        binding_failure("CoreNative restart_round: recursive interposer callback");
    restart_round_active = 1;
    bound_frame->restart_round();
    restart_round_active = 0;
}

void dxball_generate_bonus(DxBallInt x, DxBallInt y, DxBallInt dx, DxBallInt dy)
{
    if (bound_effect == NULL || bound_effect->bonus == NULL)
        binding_failure("CoreNative generate_bonus: effect table is unbound or callback is null");
    if (bonus_active || bound_effect->bonus == dxball_generate_bonus)
        binding_failure("CoreNative generate_bonus: recursive interposer callback");
    bonus_active = 1;
    bound_effect->bonus(x, y, dx, dy);
    bonus_active = 0;
}
