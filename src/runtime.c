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
#include "gameover.h"
#include "editor.h"
#include "midi.h"
#include "sound.h"
#include <stdlib.h>
#include <string.h>

DxBallClockOps dxball_clock_ops;
DxBallRuntimeOps dxball_runtime_ops = {
    dxball_load_saved_palette, dxball_palette_transition, dxball_clear_surface, dxball_reset_regions,
    dxball_load_pcx, dxball_load_sprite_bank, dxball_capture_sprite,
    dxball_load_sound, dxball_bind_board_surface, dxball_bind_display_surface, dxball_draw_text, dxball_draw_centered_text, dxball_release_sounds, dxball_release_sprite_banks, dxball_close_music
};
DxBallModeOps dxball_mode_ops = {
    {dxball_initialize_intro, dxball_initialize_game, dxball_initialize_editor, dxball_initialize_game_over, dxball_initialize_splash},
    {dxball_redraw_intro, dxball_redraw_game, dxball_redraw_editor, dxball_redraw_game_over, dxball_redraw_splash},
    {dxball_intro_frame, dxball_game_frame, dxball_editor_frame, dxball_game_over_frame, dxball_splash_frame},
    {dxball_dispose_intro, dxball_dispose_game, dxball_dispose_editor, dxball_dispose_game_over, dxball_dispose_splash},
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
DxBallDDSurface *dxball_primary_surface, *dxball_secondary_surface;

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
    if (start > now) return 1;
    if (interval + start > now) {
        return 0;
    } else {
        return 1;
    }
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
    _ultoa((unsigned long)(DxBallUInt)dxball_score, text, 10);
    count = (DxBallInt)strlen(text);
    rect.left = 20; rect.top = 0; rect.right = count * 35 + 20; rect.bottom = 32;
    ((DxBallDDSurface *)dxball_board_surface)->vtable->blt_fast(
        (DxBallDDSurface *)dxball_board_surface, 20, 0,
        (DxBallDDSurface *)dxball_background_surface, &rect, 0x10);
    dxball_select_surface((DxBallSurface)dxball_board_surface);
    dxball_draw_text(30, 31, count, text);
    dxball_invalidate_region(rect);
    lives = dxball_lives;
    if (lives > 10) lives = 10;
    ++lives;
    lives *= 22;
    rect.left = 620 - lives; rect.top = 0; rect.right = 620; rect.bottom = 16;
    ((DxBallDDSurface *)dxball_board_surface)->vtable->blt_fast(
        (DxBallDDSurface *)dxball_board_surface, rect.left, 0,
        (DxBallDDSurface *)dxball_background_surface, &rect, 0x10);
    x = 598; y = 2;
    if (dxball_lives > 20) dxball_lives = 20;
    for (i = 1; i <= dxball_lives - 1; ++i) {
        dxball_draw_keyed_sprite(31, x, y);
        x -= 22;
        if (i == 10) { x = 598; y += 8; }
    }
    dxball_invalidate_region(rect);
    return;
}

void dxball_refresh_score(void)
{
    if (dxball_score != dxball_displayed_score) {
        if ((DxBallUInt)dxball_score > 999999999U) dxball_score = 0;
        dxball_draw_score();
        dxball_displayed_score = dxball_score;
    }
    return;
}

void dxball_clear_all_entities(void)
{
    dxball_clear_projectile_list(&dxball_projectiles);
    dxball_clear_ball_list(&dxball_balls);
    dxball_clear_brick_effect_list(&dxball_brick_effects);
    dxball_clear_explosion_list(&dxball_explosions);
    dxball_clear_bonus_list(&dxball_bonuses);
    dxball_clear_particle_list(&dxball_particles);
    dxball_clear_ball_list(&dxball_duplicate_balls);
    dxball_clear_explosion_list(&dxball_explosive_sources);
    dxball_clear_fire_effect_list(&dxball_fire_effects);
    return;
}

void dxball_finish_game(void)
{
    dxball_wait_frames(30);
    dxball_end_requested = 1;
    dxball_return_to_menu = 3;
    return;
}

void dxball_reset_round(void)
{
    dxball_remaining_bricks = dxball_count_destructible_bricks();
    dxball_redraw_mode();
    dxball_load_saved_palette("mbbkgrnd.pcx");
    dxball_palette_transition(1, 6, 0, 255, 1);
    dxball_bonus_9_active = 0; dxball_bonus_8_active = 0;
    dxball_bonus_3_active = 0; dxball_bonus_14_active = 0;
    dxball_bonus_18_active = 0; dxball_bonus_12_active = 0;
    dxball_destroy_hard_tiles = 0; dxball_bonus_7_active = 0;
    dxball_bonus_3_ticks = 0; dxball_bonus_17_active = 0;
    dxball_last_brick_deadline = 0;
    dxball_stop_sound(21);
    dxball_lightning_y = 2; dxball_lightning_frames = 0;
    dxball_paddle_overlay_deadline = 0;
    dxball_paddle_overlay_sprite = 0; dxball_paddle_overlay_width = 0;
    dxball_paddle_x = dxball_mouse_x - dxball_paddle_width / 2;
    dxball_paddle_y = 450;
    dxball_paddle_previous_x = 0; dxball_paddle_previous_y = 0;
    dxball_paddle_sprite = 68;
    dxball_paddle_width = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width;
    dxball_ball_count = 0; dxball_bonus_count = 0; dxball_palette_tick = 0;
    dxball_launch_requested = 0; dxball_projectile_count = 0;
    dxball_spawn_ball();
    dxball_balls.current->attached = 1;
    dxball_level_changed = 0; dxball_restart_requested = 0;
    return;
}

void dxball_restart_round(void)
{
    DxBallInt i;
    DxBallInt gray;
    if (dxball_restart_requested == 1) {
        if (dxball_level_changed == 0) {
            for (i = 0; i <= 255; ++i) {
                gray = (dxball_saved_palette[i].red +
                    dxball_saved_palette[i].green + dxball_saved_palette[i].blue) / 3;
                dxball_saved_palette[i].red = (DxBallByte)gray;
                dxball_saved_palette[i].green = (DxBallByte)gray;
                dxball_saved_palette[i].blue = (DxBallByte)gray;
            }
            dxball_palette_transition(1, 3, 0, 255, 1);
            dxball_palette_transition(1, 6, 0, 255, 0);
        } else dxball_palette_transition(1, 6, 0, 255, 0);
        dxball_clear_surface((DxBallSurface)dxball_board_surface, 0);
        dxball_clear_surface((DxBallSurface)dxball_primary_surface, 0);
        memset(dxball_board_aux, 0, DXBALL_BOARD_SIZE);
        dxball_clear_all_entities();
        dxball_reset_regions();
        if (dxball_lives < 1) dxball_finish_game();
        else dxball_reset_round();
    }
    return;
}

void dxball_redraw_game(void)
{
    DxBallRect rect;
    rect.left = 0; rect.top = 0; rect.right = 640; rect.bottom = 480;
    dxball_clear_surface((DxBallSurface)dxball_primary_surface, 0);
    dxball_clear_surface((DxBallSurface)dxball_board_surface, 0);
    ((DxBallDDSurface *)dxball_board_surface)->vtable->blt(
        (DxBallDDSurface *)dxball_board_surface, &rect,
        (DxBallDDSurface *)dxball_background_surface, &rect, 0x01000000, NULL);
    dxball_draw_score();
    dxball_draw_board(0);
    if (dxball_paused == 1) dxball_draw_centered_text(320, 240, 6, "PAUSED");
    ((DxBallDDSurface *)dxball_primary_surface)->vtable->blt(
        (DxBallDDSurface *)dxball_primary_surface, &rect,
        (DxBallDDSurface *)dxball_board_surface, &rect, 0x01000000, NULL);
    if (dxball_display_buffer_count > 0 && dxball_draw_to_primary == 0) {
        ((DxBallDDSurface *)dxball_secondary_surface)->vtable->blt(
            (DxBallDDSurface *)dxball_secondary_surface, &rect,
            (DxBallDDSurface *)dxball_board_surface, &rect, 0x01000000, NULL);
    }
    return;
}

void dxball_initialize_game(void)
{
    dxball_clear_surface(dxball_background_surface, 0);
    dxball_load_pcx((DxBallDDSurface *)dxball_background_surface, "mbbkgrnd.pcx", 2, 0, 0);
    dxball_load_sprite_bank(0, 1, "mball2.sbk");
    dxball_select_sprite_bank(0);
    dxball_load_sprite_bank(1, 0, "thefont.sbk");
    dxball_select_font_bank(1);
    dxball_sprite_banks[2].count = 1; dxball_sprite_banks[2].allocation_mode = 0;
    dxball_clear_surface((DxBallSurface)dxball_board_surface, 0);
    dxball_load_pcx((DxBallDDSurface *)dxball_board_surface, "bigbolt.pcx", 0, 0, 0);
    dxball_select_sprite_bank(2);
    dxball_capture_sprite(1, 0, 0, 159, 479);
    dxball_select_sprite_bank(0);
    dxball_load_sound(0, "boing.wav");
    dxball_load_sound(1, "effect.wav");
    dxball_load_sound(2, "bang.wav");
    dxball_load_sound(3, "ao-laser.wav");
    dxball_load_sound(4, "bassdrum.wav");
    dxball_load_sound(5, "byeball.wav");
    dxball_load_sound(7, "wowpulse.wav");
    dxball_load_sound(8, "saucer.wav");
    dxball_load_sound(9, "orchestr.wav");
    dxball_load_sound(10, "effect2.wav");
    dxball_load_sound(11, "sweepdow.wav");
    dxball_load_sound(12, "peow!.wav");
    dxball_load_sound(13, "fanfare.wav");
    dxball_load_sound(14, "padexplo.wav");
    dxball_load_sound(15, "ricochet.wav");
    dxball_load_sound(16, "swordswi.wav");
    dxball_load_sound(17, "gunfire.wav");
    dxball_load_sound(18, "humm.wav");
    dxball_load_sound(19, "glass.wav");
    dxball_load_sound(20, "orchblas.wav");
    dxball_load_sound(21, "voltage.wav");
    dxball_load_sound(22, "thudclap.wav");
    dxball_load_sound(30, "tank.wav");
    dxball_load_sound(31, "xplosht1.wav");
    dxball_load_sound(32, "xploshor.wav");
    dxball_paused = 0; dxball_displayed_score = 999999999;
    dxball_score = 0; dxball_lives = 3;
    dxball_paddle_frame = 0; dxball_paddle_tick = 0;
    dxball_board_index = 0;
    dxball_initialize_board();
    dxball_reset_round();
    dxball_reset_regions();
    dxball_bind_board_surface((DxBallSurface)dxball_board_surface);
    if (dxball_draw_to_primary != 0) {
        dxball_bind_display_surface((DxBallSurface)dxball_primary_surface);
    } else {
        dxball_bind_display_surface((DxBallSurface)dxball_secondary_surface);
    }
    return;
}

void dxball_dispose_game(DxBallInt fade)
{
    if (fade != 0) {
        if (dxball_restart_requested == 0) dxball_palette_transition(1, 6, 0, 255, 0);
        dxball_clear_surface((DxBallSurface)dxball_board_surface, 0);
        dxball_clear_surface((DxBallSurface)dxball_primary_surface, 0);
        dxball_release_sounds();
        dxball_release_sprite_banks();
        dxball_close_music();
    }
    dxball_clear_all_entities();
    return;
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
