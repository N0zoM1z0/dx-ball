extern "C" {
#include "runtime.h"
#include "bonuses.h"
#include "paddle.h"
#include "round.h"
#include "sound.h"
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

