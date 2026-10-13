extern "C" {
#include "balls.h"
#include "allocator.h"
#include "effects.h"
#include "paddle.h"
#include "sound.h"
#include "trig.h"
}
#include <stdlib.h>


void dxball_bounce_ball_from_paddle(void)
{
    float ratio;
    ratio = (float)((long double)dxball_paddle_x - dxball_paddle_width / 2);
    if ((ratio = (ratio = (long double)(dxball_balls.current->x +
        dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_balls.current->sprite]->width / 2) - ratio) / dxball_paddle_width) <= 0.07) {
        dxball_balls.current->angle = 150;
        dxball_stop_sound(16);
        dxball_play_sound(16, 0, dxball_screen_pan(dxball_balls.current->x), 0);
    }
    else if (static_cast<const volatile float &>(ratio) <= 0.2) dxball_balls.current->angle = 135;
    else if (static_cast<const volatile float &>(ratio) <= 0.35) dxball_balls.current->angle = 120;
    else if (static_cast<const volatile float &>(ratio) <= 0.5) dxball_balls.current->angle = 105;
    else if (static_cast<const volatile float &>(ratio) <= 0.65) dxball_balls.current->angle = 75;
    else if (static_cast<const volatile float &>(ratio) <= 0.8) dxball_balls.current->angle = 60;
    else if (static_cast<const volatile float &>(ratio) <= 0.93) dxball_balls.current->angle = 45;
    else {
        dxball_balls.current->angle = 30;
        dxball_stop_sound(16);
        dxball_play_sound(16, 0, dxball_screen_pan(dxball_balls.current->x), 0);
    }
    if (dxball_balls.current->angle > 30 && dxball_balls.current->angle < 150) {
        dxball_balls.current->y = dxball_paddle_y -
            dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_balls.current->sprite]->height;
    }
    dxball_balls.current->dx = (DxBallInt)((long double)dxball_cosine(dxball_balls.current->angle) * dxball_balls.current->speed * 1.2);
    dxball_balls.current->dy = (DxBallInt)(-(long double)dxball_sine(dxball_balls.current->angle) * dxball_balls.current->speed);
    return;
}

void dxball_spawn_ball(void)
{
    ++dxball_ball_count;
    dxball_append_ball(&dxball_balls);
    dxball_balls.current->sprite = 1;
    dxball_balls.current->x = dxball_paddle_x + 1;
    dxball_balls.current->y = dxball_paddle_y - dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_balls.current->sprite]->height;
    dxball_balls.current->previous_x = dxball_balls.current->x;
    dxball_balls.current->previous_y = dxball_balls.current->y;
    dxball_balls.current->dx = 0;
    dxball_balls.current->dy = 0;
    dxball_balls.current->angle = 0;
    dxball_balls.current->speed = 5;
    dxball_balls.current->bounce_count = 0;
    dxball_balls.current->attached = 0;
    dxball_balls.current->attach_offset = 0;
    dxball_balls.current->wall_bounces = 0;
    dxball_bounce_ball_from_paddle();
    return;
}

void dxball_release_attached_balls(void)
{
    if (dxball_begin_balls(&dxball_balls)) {
        do {
            if (dxball_balls.current->attached == 1) {
                dxball_balls.current->attached = 0;
                dxball_bounce_ball_from_paddle();
            }
        } while (dxball_advance_ball(&dxball_balls));
    }
    return;
}

void dxball_clone_balls(void)
{
    if (dxball_begin_balls(&dxball_balls)) {
        do {
            dxball_append_ball(&dxball_duplicate_balls);
            /* Copy payload in sprite-first order; retain the new node's links. */
            dxball_duplicate_balls.current->sprite = dxball_balls.current->sprite;
            dxball_duplicate_balls.current->x = dxball_balls.current->x;
            dxball_duplicate_balls.current->y = dxball_balls.current->y;
            dxball_duplicate_balls.current->previous_x = dxball_balls.current->previous_x;
            dxball_duplicate_balls.current->previous_y = dxball_balls.current->previous_y;
            dxball_duplicate_balls.current->dx = dxball_balls.current->dx;
            dxball_duplicate_balls.current->dy = dxball_balls.current->dy;
            dxball_duplicate_balls.current->angle = dxball_balls.current->angle;
            dxball_duplicate_balls.current->speed = dxball_balls.current->speed;
            dxball_duplicate_balls.current->bounce_count = dxball_balls.current->bounce_count;
            dxball_duplicate_balls.current->attached = dxball_balls.current->attached;
            dxball_duplicate_balls.current->attach_offset = dxball_balls.current->attach_offset;
            dxball_duplicate_balls.current->wall_bounces = dxball_balls.current->wall_bounces;
            if (dxball_duplicate_balls.current->attached == 1) {
                --dxball_duplicate_balls.current->speed;
                if (dxball_duplicate_balls.current->speed < 4) dxball_duplicate_balls.current->speed = 4;
            }
            dxball_duplicate_balls.current->dx = dxball_duplicate_balls.current->dx * -1;
        } while (dxball_advance_ball(&dxball_balls));
    }
    if (dxball_begin_balls(&dxball_duplicate_balls)) {
        do {
            ++dxball_ball_count;
            dxball_append_ball(&dxball_balls);
            dxball_balls.current->sprite = dxball_duplicate_balls.current->sprite;
            dxball_balls.current->x = dxball_duplicate_balls.current->x;
            dxball_balls.current->y = dxball_duplicate_balls.current->y;
            dxball_balls.current->previous_x = dxball_duplicate_balls.current->previous_x;
            dxball_balls.current->previous_y = dxball_duplicate_balls.current->previous_y;
            dxball_balls.current->dx = dxball_duplicate_balls.current->dx;
            dxball_balls.current->dy = dxball_duplicate_balls.current->dy;
            dxball_balls.current->angle = dxball_duplicate_balls.current->angle;
            dxball_balls.current->speed = dxball_duplicate_balls.current->speed;
            dxball_balls.current->bounce_count = dxball_duplicate_balls.current->bounce_count;
            dxball_balls.current->attached = dxball_duplicate_balls.current->attached;
            dxball_balls.current->attach_offset = dxball_duplicate_balls.current->attach_offset;
            dxball_balls.current->wall_bounces = dxball_duplicate_balls.current->wall_bounces;
        } while (dxball_advance_ball(&dxball_duplicate_balls));
    }
    dxball_clear_ball_list(&dxball_duplicate_balls);
    return;
}
