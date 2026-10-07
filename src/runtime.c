#include "runtime.h"
#include "bonuses.h"
#include "effects.h"
#include "paddle.h"
#include "particles.h"
#include "round.h"
#include "display.h"
#include "device.h"
#include "startup.h"
#include "ui.h"
#include "intro.h"
#include <stdio.h>
#include <string.h>

DxBallClockOps dxball_clock_ops;
DxBallRuntimeOps dxball_runtime_ops = {
    dxball_load_saved_palette, dxball_palette_transition, dxball_clear_surface, dxball_reset_regions,
    dxball_load_pcx, dxball_load_sprite_bank, dxball_capture_sprite,
    NULL, dxball_bind_board_surface, dxball_bind_display_surface, dxball_draw_text, dxball_draw_centered_text, NULL, dxball_release_sprite_banks, NULL
};
DxBallModeOps dxball_mode_ops = {
    {dxball_initialize_intro, dxball_initialize_game, NULL, NULL, dxball_initialize_splash},
    {dxball_redraw_intro, dxball_redraw_game, NULL, NULL, dxball_redraw_splash},
    {dxball_intro_frame, dxball_game_frame, NULL, NULL, dxball_splash_frame},
    {dxball_dispose_intro, dxball_dispose_game, NULL, NULL, dxball_dispose_splash},
    dxball_initialize_device_state, dxball_synchronize_surface
};
DxBallInt dxball_high_resolution_clock;
DxBallUInt dxball_clock_divisor;
DxBallInt dxball_paddle_frame, dxball_paddle_overlay_sprite, dxball_paddle_overlay_width;
DxBallUInt dxball_paddle_tick, dxball_paddle_overlay_deadline;
DxBallInt dxball_lightning_x, dxball_lightning_y, dxball_lightning_frames;
DxBallInt dxball_device_reset_requested = 1;
DxBallInt dxball_surface_restore_requested;
DxBallInt dxball_display_buffer_count = 1;
DxBallSurface dxball_primary_surface, dxball_secondary_surface;

DxBallUInt dxball_current_time(void)
{
    DxBallCounter value;
    if (dxball_high_resolution_clock == 0) return dxball_clock_ops.time_ms();
    if (dxball_clock_divisor == 0) {
        if (dxball_clock_ops.frequency(&value) == 0) return dxball_clock_ops.time_ms();
        dxball_clock_divisor = value.low / 1000;
    }
    dxball_clock_ops.counter(&value);
    return value.low / dxball_clock_divisor;
}

DxBallInt dxball_elapsed(DxBallUInt start, DxBallUInt interval)
{
    DxBallUInt now;
    now = dxball_current_time();
    if (now < start) return 1;
    if (now < start + interval) return 0;
    return 1;
}

void dxball_draw_paddle(void)
{
    DxBallInt base_width, factor, sprite, offset_y, margin, x, y;
    DxBallUInt now;
    DxBallSprite *overlay;
    DxBallDDSurface *surface;
    DxBallRect rect;
    base_width = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width;
    factor = dxball_paddle_width / base_width;
    sprite = factor * 4 + dxball_paddle_frame;
    if (dxball_frame_ops.elapsed(dxball_paddle_tick, 64)) {
        ++dxball_paddle_frame;
        if (dxball_paddle_frame > 3) dxball_paddle_frame = 0;
        dxball_paddle_tick = dxball_frame_ops.current_time();
    }
    if (dxball_bonus_8_active == 1) {
        sprite += 104; offset_y = 15;
    } else if (dxball_attached_ball_cue == 1) {
        sprite += 84;
        offset_y = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->height - 14;
    } else {
        sprite += 64; offset_y = 0;
    }
    if (dxball_attached_ball_cue == 1) {
        now = dxball_clock_ops.time_ms();
        if (dxball_paddle_overlay_deadline < now || dxball_paddle_overlay_width != dxball_paddle_width) {
            dxball_paddle_overlay_sprite = dxball_gameplay_ops.random_range(4) + factor * 4 + 124;
            dxball_paddle_overlay_deadline = dxball_clock_ops.time_ms() + 33;
            dxball_paddle_overlay_width = dxball_paddle_width;
        }
        margin = (DxBallInt)((long double)dxball_paddle_width * (dxball_bonus_8_active == 1 ? 0.075 : 0.03));
        x = dxball_paddle_x - dxball_paddle_width / 2 + margin;
        y = dxball_paddle_y - 14;
        overlay = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_overlay_sprite];
        rect.left = margin; rect.top = 0;
        rect.right = dxball_paddle_width - margin; rect.bottom = overlay->height;
        surface = (DxBallDDSurface *)dxball_effect_surface;
        surface->vtable->blt_fast(surface, x, y, overlay->surface, &rect, 0x11);
        dxball_particle_region(x, y, x + dxball_paddle_width, y + overlay->height);
    }
    dxball_frame_ops.draw_effect_sprite(sprite, dxball_paddle_x - dxball_paddle_width / 2,
        dxball_paddle_y - offset_y);
}

void dxball_draw_score(void)
{
    char text[11];
    DxBallInt count, lives, x, y, i;
    DxBallRect rect;
    DxBallDDSurface *surface;
    sprintf(text, "%u", (DxBallUInt)dxball_score);
    count = (DxBallInt)strlen(text);
    rect.left = 20; rect.top = 0; rect.right = count * 35 + 20; rect.bottom = 32;
    surface = (DxBallDDSurface *)dxball_board_surface;
    surface->vtable->blt_fast(surface, 20, 0, (DxBallDDSurface *)dxball_background_surface, &rect, 0x10);
    dxball_select_surface(dxball_board_surface);
    dxball_runtime_ops.draw_text(30, 31, count, text);
    dxball_render_ops.invalidate(rect.left, rect.top, rect.right, rect.bottom);
    lives = dxball_lives;
    if (lives > 10) lives = 10;
    rect.left = 620 - (lives + 1) * 22; rect.top = 0; rect.right = 620; rect.bottom = 16;
    surface->vtable->blt_fast(surface, rect.left, 0, (DxBallDDSurface *)dxball_background_surface, &rect, 0x10);
    x = 598; y = 2;
    if (dxball_lives > 20) dxball_lives = 20;
    for (i = 1; i <= dxball_lives - 1; ++i) {
        dxball_effect_ops.keyed_sprite(31, x, y);
        x -= 22;
        if (i == 10) { x = 598; y += 8; }
    }
    dxball_render_ops.invalidate(rect.left, rect.top, rect.right, rect.bottom);
}

void dxball_refresh_score(void)
{
    if (dxball_displayed_score != dxball_score) {
        if ((DxBallUInt)dxball_score > 999999999U) dxball_score = 0;
        dxball_draw_score();
        dxball_displayed_score = dxball_score;
    }
}

void dxball_clear_all_entities(void)
{
    dxball_clear_projectiles();
    dxball_clear_ball_list(&dxball_balls);
    while (dxball_remove_brick_effect(&dxball_brick_effects)) {}
    dxball_clear_explosion_list(&dxball_explosions);
    while (dxball_remove_bonus(&dxball_bonuses)) {}
    while (dxball_remove_particle(&dxball_particles)) {}
    dxball_clear_ball_list(&dxball_duplicate_balls);
    dxball_clear_explosion_list(&dxball_explosive_sources);
    dxball_clear_fire_effects();
}

void dxball_finish_game(void)
{
    dxball_frame_ops.wait_frames(30);
    dxball_end_requested = 1;
    dxball_return_to_menu = 3;
}

void dxball_reset_round(void)
{
    dxball_remaining_bricks = dxball_count_destructible_bricks();
    dxball_redraw_mode();
    dxball_runtime_ops.load_saved_palette("mbbkgrnd.pcx");
    dxball_runtime_ops.palette_transition(1, 6, 0, 255, 1);
    dxball_bonus_9_active = 0; dxball_bonus_8_active = 0;
    dxball_bonus_3_active = 0; dxball_bonus_14_active = 0;
    dxball_bonus_18_active = 0; dxball_bonus_12_active = 0;
    dxball_destroy_hard_tiles = 0; dxball_bonus_7_active = 0;
    dxball_bonus_3_ticks = 0; dxball_bonus_17_active = 0;
    dxball_last_brick_deadline = 0;
    dxball_gameplay_ops.stop_sound(21);
    dxball_lightning_y = 2; dxball_lightning_frames = 0;
    dxball_paddle_overlay_deadline = 0;
    dxball_paddle_overlay_sprite = 0; dxball_paddle_overlay_width = 0;
    dxball_paddle_x = dxball_mouse_x - dxball_paddle_width / 2;
    dxball_paddle_y = 450;
    dxball_paddle_previous_x = 0; dxball_paddle_previous_y = 0;
    dxball_paddle_sprite = 68;
    dxball_paddle_width = dxball_sprite_banks[dxball_sprite_bank].sprites[68]->width;
    dxball_ball_count = 0; dxball_bonus_count = 0; dxball_palette_tick = 0;
    dxball_launch_requested = 0; dxball_projectile_count = 0;
    dxball_spawn_ball();
    dxball_balls.current->attached = 1;
    dxball_level_changed = 0; dxball_restart_requested = 0;
}

void dxball_restart_round(void)
{
    DxBallInt i;
    DxBallByte gray;
    if (dxball_restart_requested == 1) {
        if (dxball_level_changed == 0) {
            for (i = 0; i < 256; ++i) {
                gray = (DxBallByte)(((DxBallUInt)dxball_saved_palette[i].red +
                    dxball_saved_palette[i].green + dxball_saved_palette[i].blue) / 3);
                dxball_saved_palette[i].red = gray;
                dxball_saved_palette[i].green = gray;
                dxball_saved_palette[i].blue = gray;
            }
            dxball_runtime_ops.palette_transition(1, 3, 0, 255, 1);
            dxball_runtime_ops.palette_transition(1, 6, 0, 255, 0);
        } else dxball_runtime_ops.palette_transition(1, 6, 0, 255, 0);
        dxball_runtime_ops.clear_surface(dxball_board_surface, 0);
        dxball_runtime_ops.clear_surface(dxball_primary_surface, 0);
        memset(dxball_board_aux, 0, DXBALL_BOARD_SIZE);
        dxball_clear_all_entities();
        dxball_runtime_ops.reset_regions();
        if (dxball_lives < 1) dxball_finish_game();
        else dxball_reset_round();
    }
}

void dxball_redraw_game(void)
{
    DxBallRect rect;
    DxBallDDSurface *board, *primary, *secondary;
    rect.left = 0; rect.top = 0; rect.right = 640; rect.bottom = 480;
    board = (DxBallDDSurface *)dxball_board_surface;
    primary = (DxBallDDSurface *)dxball_primary_surface;
    secondary = (DxBallDDSurface *)dxball_secondary_surface;
    dxball_runtime_ops.clear_surface(dxball_primary_surface, 0);
    dxball_runtime_ops.clear_surface(dxball_board_surface, 0);
    board->vtable->blt(board, &rect, (DxBallDDSurface *)dxball_background_surface, &rect, 0x01000000, NULL);
    dxball_draw_score();
    dxball_draw_board(0);
    if (dxball_paused == 1) dxball_runtime_ops.draw_centered_text(320, 240, 6, "PAUSED");
    primary->vtable->blt(primary, &rect, board, &rect, 0x01000000, NULL);
    if (dxball_display_buffer_count > 0 && dxball_draw_to_primary == 0) {
        secondary->vtable->blt(secondary, &rect, board, &rect, 0x01000000, NULL);
    }
}

void dxball_initialize_game(void)
{
    DxBallInt i;
    static const struct { DxBallInt slot; const char *path; } sounds[] = {
        {0, "boing.wav"}, {1, "effect.wav"}, {2, "bang.wav"}, {3, "ao-laser.wav"},
        {4, "bassdrum.wav"}, {5, "byeball.wav"}, {7, "wowpulse.wav"}, {8, "saucer.wav"},
        {9, "orchestr.wav"}, {10, "effect2.wav"}, {11, "sweepdow.wav"}, {12, "peow!.wav"},
        {13, "fanfare.wav"}, {14, "padexplo.wav"}, {15, "ricochet.wav"}, {16, "swordswi.wav"},
        {17, "gunfire.wav"}, {18, "humm.wav"}, {19, "glass.wav"}, {20, "orchblas.wav"},
        {21, "voltage.wav"}, {22, "thudclap.wav"}, {30, "tank.wav"}, {31, "xplosht1.wav"},
        {32, "xploshor.wav"}
    };
    dxball_runtime_ops.clear_surface(dxball_background_surface, 0);
    dxball_runtime_ops.load_pcx((DxBallDDSurface *)dxball_background_surface, "mbbkgrnd.pcx", 2, 0, 0);
    dxball_runtime_ops.load_sprite_bank(0, 1, "mball2.sbk");
    dxball_select_sprite_bank(0);
    dxball_runtime_ops.load_sprite_bank(1, 0, "thefont.sbk");
    dxball_select_font_bank(1);
    dxball_sprite_banks[2].count = 1; dxball_sprite_banks[2].allocation_mode = 0;
    dxball_runtime_ops.clear_surface(dxball_board_surface, 0);
    dxball_runtime_ops.load_pcx((DxBallDDSurface *)dxball_board_surface, "bigbolt.pcx", 0, 0, 0);
    dxball_select_sprite_bank(2);
    dxball_runtime_ops.capture_sprite(1, 0, 0, 159, 479);
    dxball_select_sprite_bank(0);
    for (i = 0; i < (DxBallInt)(sizeof(sounds) / sizeof(sounds[0])); ++i) {
        dxball_runtime_ops.load_sound(sounds[i].slot, sounds[i].path);
    }
    dxball_paused = 0; dxball_displayed_score = 999999999;
    dxball_score = 0; dxball_lives = 3;
    dxball_paddle_frame = 0; dxball_paddle_tick = 0;
    dxball_board_index = 0;
    dxball_initialize_board();
    dxball_reset_round();
    dxball_runtime_ops.reset_regions();
    dxball_runtime_ops.bind_board_surface(dxball_board_surface);
    dxball_runtime_ops.bind_display_surface(dxball_draw_to_primary == 0 ? dxball_secondary_surface : dxball_primary_surface);
}

void dxball_dispose_game(DxBallInt fade)
{
    if (fade != 0) {
        if (dxball_restart_requested == 0) dxball_runtime_ops.palette_transition(1, 6, 0, 255, 0);
        dxball_runtime_ops.clear_surface(dxball_board_surface, 0);
        dxball_runtime_ops.clear_surface(dxball_primary_surface, 0);
        dxball_runtime_ops.release_sounds();
        dxball_runtime_ops.release_sprite_banks();
        dxball_runtime_ops.finalize_game_resources();
    }
    dxball_clear_all_entities();
}

void dxball_initialize_mode(void)
{
    if (dxball_display_mode >= 0 && dxball_display_mode <= 4) dxball_mode_ops.initialize[dxball_display_mode]();
}

void dxball_redraw_mode(void)
{
    if (dxball_display_mode >= 0 && dxball_display_mode <= 4) dxball_mode_ops.redraw[dxball_display_mode]();
}

void dxball_cleanup_mode(DxBallInt fade)
{
    if (dxball_display_mode >= 0 && dxball_display_mode <= 4) dxball_mode_ops.cleanup[dxball_display_mode](fade);
}

DxBallInt dxball_dispatch_frame(void)
{
    if (dxball_device_reset_requested != 0) {
        dxball_mode_ops.reinitialize_device();
        dxball_initialize_mode();
        dxball_device_reset_requested = 0;
        dxball_surface_restore_requested = 0;
    }
    dxball_mode_ops.synchronize_surface();
    if (dxball_display_mode >= 0 && dxball_display_mode <= 4) dxball_mode_ops.frame[dxball_display_mode]();
    if (dxball_end_requested != 0) {
        dxball_cleanup_mode(1);
        dxball_display_mode = dxball_return_to_menu;
        dxball_initialize_mode();
        dxball_end_requested = 0;
    }
    return 1;
}
