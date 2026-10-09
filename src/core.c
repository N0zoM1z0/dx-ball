#include "core.h"
#include "bonuses.h"
#include "effects.h"
#include "geometry.h"
#include "paddle.h"
#include "particles.h"
#include "round.h"
#include "runtime.h"
#include "display.h"
#include "trig.h"
#include <stdlib.h>

DxBallInt dxball_projectile_count;
DxBallInt dxball_launch_requested, dxball_attached_ball_cue;
DxBallInt dxball_paused, dxball_mouse_action;
DxBallInt dxball_draw_to_primary = 1;
DxBallInt dxball_last_brick_deadline;
DxBallFrameOps dxball_frame_ops = {
    dxball_current_time, dxball_elapsed, dxball_animate_palette, dxball_refresh_score,
    dxball_wait_frames, dxball_restore_regions, dxball_draw_effect_sprite, dxball_draw_paddle,
    dxball_last_brick, dxball_draw_last_brick, dxball_present, dxball_restart_round
};

/* Both typed owners use ECX and preserve remove/advance successor skipping. */
DxBallInt DXBALL_FASTCALL dxball_append_projectile(DxBallProjectileList *list)
{
    DxBallProjectileNode *node;
    node = (DxBallProjectileNode *)dxball_allocate_node(sizeof(DxBallProjectileNode));
    if (node == NULL) exit(1);
    node->previous = list->last;
    node->next = NULL;
    if (list->last != NULL) list->last->next = node;
    else list->first = node;
    list->last = list->current = node;
    return 1;
}
DxBallInt DXBALL_FASTCALL dxball_begin_projectiles(DxBallProjectileList *list)
{
    list->current = list->first;
    return list->current != NULL;
}
DxBallInt DXBALL_FASTCALL dxball_advance_projectile(DxBallProjectileList *list)
{
    if (list->current == NULL) return 0;
    list->current = list->current->next;
    if (list->current != NULL) return 1;
    list->current = list->first;
    return 0;
}
DxBallInt DXBALL_FASTCALL dxball_remove_projectile(DxBallProjectileList *list)
{
    DxBallProjectileNode *node;
    node = list->current;
    if (node == NULL) return 0;
    if (node->previous != NULL) node->previous->next = node->next;
    if (node->next != NULL) {
        node->next->previous = node->previous;
        list->current = node->next;
    } else list->current = node->previous;
    if (list->first == node) list->first = node->next;
    if (list->last == node) list->last = node->previous;
    dxball_deallocate_node(node);
    return 1;
}


DxBallInt DXBALL_FASTCALL dxball_append_fire_effect(DxBallFireEffectList *list)
{
    DxBallFireEffectNode *node;
    node = (DxBallFireEffectNode *)dxball_allocate_node(sizeof(DxBallFireEffectNode));
    if (node == NULL) exit(1);
    node->previous = list->last;
    node->next = NULL;
    if (list->last != NULL) list->last->next = node;
    else list->first = node;
    list->last = list->current = node;
    return 1;
}
DxBallInt DXBALL_FASTCALL dxball_begin_fire_effects(DxBallFireEffectList *list)
{
    list->current = list->first;
    return list->current != NULL;
}
DxBallInt DXBALL_FASTCALL dxball_advance_fire_effect(DxBallFireEffectList *list)
{
    if (list->current == NULL) return 0;
    list->current = list->current->next;
    if (list->current != NULL) return 1;
    list->current = list->first;
    return 0;
}
DxBallInt DXBALL_FASTCALL dxball_remove_fire_effect(DxBallFireEffectList *list)
{
    DxBallFireEffectNode *node;
    node = list->current;
    if (node == NULL) return 0;
    if (node->previous != NULL) node->previous->next = node->next;
    if (node->next != NULL) {
        node->next->previous = node->previous;
        list->current = node->next;
    } else list->current = node->previous;
    if (list->first == node) list->first = node->next;
    if (list->last == node) list->last = node->previous;
    dxball_deallocate_node(node);
    return 1;
}

DxBallInt dxball_retire_projectile(void)
{
    DxBallInt removed;
    removed = dxball_remove_projectile(&dxball_projectiles);
    --dxball_projectile_count;
    return removed;
}

/* FUNCTION: DXBALL 0x004165D0 */
DxBallInt DXBALL_FASTCALL dxball_clear_projectile_list(DxBallProjectileList *list)
{
    while (dxball_remove_projectile(list)) {
    }
    return 1;
}

/* FUNCTION: DXBALL 0x00416510 */
DxBallInt DXBALL_FASTCALL dxball_clear_fire_effect_list(DxBallFireEffectList *list)
{
    while (dxball_remove_fire_effect(list)) {
    }
    return 1;
}

/* Convenience wrappers without separate target-entry claims. */
void dxball_clear_projectiles(void)
{
    dxball_clear_projectile_list(&dxball_projectiles);
}

void dxball_clear_fire_effects(void)
{
    dxball_clear_fire_effect_list(&dxball_fire_effects);
}

void dxball_spawn_fire_effect(DxBallInt x, DxBallInt y)
{
    dxball_append_fire_effect(&dxball_fire_effects);
    dxball_fire_effects.current->x = x - 24;
    dxball_fire_effects.current->y = y - 23;
    dxball_fire_effects.current->ticks = 0;
    if (dxball_fire_effects.current->x < 0) dxball_fire_effects.current->x = 0;
    if (dxball_fire_effects.current->x + 44 > 639) dxball_fire_effects.current->x = 595;
    if (dxball_fire_effects.current->y < 0) dxball_fire_effects.current->y = 0;
    if (dxball_fire_effects.current->y + 43 > 479) dxball_fire_effects.current->y = 436;
}

void dxball_process_fire_effects(void)
{
    if (dxball_begin_fire_effects(&dxball_fire_effects)) {
        do {
            dxball_frame_ops.draw_effect_sprite(dxball_fire_effects.current->ticks + 145,
                dxball_fire_effects.current->x, dxball_fire_effects.current->y);
            ++dxball_fire_effects.current->ticks;
            if (dxball_fire_effects.current->ticks > 21) dxball_remove_fire_effect(&dxball_fire_effects);
        } while (dxball_advance_fire_effect(&dxball_fire_effects));
    }
}

DxBallInt dxball_hit_screen_point(DxBallInt x, DxBallInt y)
{
    DxBallInt column, row;
    if (y > 49 && y < 350) {
        column = (x - 20) / 30;
        row = (y - 50) / 15;
        if (column < 0) column = 0;
        if (column > 19) column = 19;
        if (row < 0) row = 0;
        if (row > 19) row = 19;
        if (dxball_board_tiles[column + row * 20] != 0) {
            if (dxball_balls.current->sprite == 61) {
                if (dxball_board_tiles[column + row * 20] == 2) ++dxball_remaining_bricks;
                dxball_board_tiles[column + row * 20] = 8;
                if (dxball_destroy_hard_tiles == 0) dxball_spawn_fire_effect(x, y);
            }
            if (dxball_hit_board_tile(column, row)) dxball_score += dxball_balls.current->speed * 2;
            return 1;
        }
    }
    return 0;
}

void dxball_retire_ball(void)
{
    if (dxball_ball_count > 0) {
        dxball_remove_ball(&dxball_balls);
        --dxball_ball_count;
    }
}

void dxball_drop_bricks(void)
{
    DxBallInt column, row, moved;
    DxBallRect rect;
    DxBallDDSurface *surface;
    moved = 0;
    dxball_gameplay_ops.stop_sound(20);
    dxball_gameplay_ops.play_sound(20, 0, 0, 0);
    for (column = 0; column < 20; ++column) {
        for (row = 18; row >= 0; --row) {
            if (dxball_board_tiles[column + row * 20] != 0 && dxball_board_tiles[column + (row + 1) * 20] == 0) {
                dxball_board_tiles[column + (row + 1) * 20] = dxball_board_tiles[column + row * 20];
                dxball_board_tiles[column + row * 20] = 0;
                moved = 1;
            }
        }
    }
    if (moved == 1) {
        rect.left = 20; rect.top = 50; rect.right = 620; rect.bottom = 350;
        surface = (DxBallDDSurface *)dxball_board_surface;
        surface->vtable->blt(surface, &rect, (DxBallDDSurface *)dxball_background_surface,
            &rect, 0x01000000, NULL);
        dxball_select_surface(dxball_board_surface);
        for (column = 0; column < 20; ++column) {
            for (row = 0; row < 20; ++row) {
                if (dxball_board_tiles[column + row * 20] != 0) dxball_draw_board_tile(column, row, 1);
            }
        }
        dxball_render_ops.invalidate(rect.left, rect.top, rect.right, rect.bottom);
    }
}

/* Main physics: the cached paddle position belongs to the previous frame. */
void dxball_update_balls(void)
{
    DxBallBallNode *ball;
    DxBallSprite *sprite;
    DxBallInt x, y, sign, limit, i, dx, dy, hit;
    if (!dxball_begin_balls(&dxball_balls)) {
        dxball_lose_life();
        return;
    }
    do {
        ball = dxball_balls.current;
        sprite = dxball_sprite_banks[dxball_sprite_bank].sprites[ball->sprite];
        if (ball->attached != 0) {
            if (dxball_launch_requested == 1) {
                ball->attached = 0;
                dxball_bounce_ball_from_paddle();
            }
            dxball_attached_ball_cue = 1;
            ball->previous_x = ball->x;
            ball->previous_y = ball->y;
            ball->x = ball->attach_offset + dxball_paddle_x;
            ball->y = dxball_paddle_y - sprite->height;
        } else {
            ball->previous_x = ball->x;
            ball->previous_y = ball->y;
            ball->x += ball->dx;
            ball->y += ball->dy;
            if (dxball_bonus_3_ticks != 0) ++ball->y;
            if (ball->sprite == 61) {
                limit = (dxball_reduced_particles == 0 ? 11 : 14) - ball->speed;
                if (dxball_gameplay_ops.random_range(limit) == 0) {
                    dy = ball->dy / 2; dx = ball->dx / 2;
                    y = ball->y + dxball_gameplay_ops.random_range(sprite->height);
                    x = ball->x + dxball_gameplay_ops.random_range(sprite->width);
                    dxball_gameplay_ops.particle(x, y, dx, dy, 95, 0);
                }
            }
            if (ball->y > 479 - sprite->height) {
                dxball_gameplay_ops.stop_sound(5);
                dxball_gameplay_ops.play_sound(5, 0, dxball_screen_pan(ball->x), 0);
                dxball_retire_ball();
            } else {
                if (ball->x < 20) {
                    ball->x = 20; ball->dx = abs(ball->dx);
                    dxball_gameplay_ops.stop_sound(4);
                    dxball_gameplay_ops.play_sound(4, 0, dxball_screen_pan(ball->x), 0);
                    ++ball->bounce_count; ++ball->wall_bounces;
                }
                if (ball->x > 619 - sprite->width) {
                    ball->x = 619 - sprite->width; ball->dx = -abs(ball->dx);
                    dxball_gameplay_ops.stop_sound(4);
                    dxball_gameplay_ops.play_sound(4, 0, dxball_screen_pan(ball->x), 0);
                    ++ball->bounce_count; ++ball->wall_bounces;
                }
                if (ball->y < 0) {
                    ball->y = 0; ball->dy = abs(ball->dy);
                    dxball_gameplay_ops.stop_sound(4);
                    dxball_gameplay_ops.play_sound(4, 0, dxball_screen_pan(ball->x), 0);
                    ++ball->bounce_count; ++ball->wall_bounces;
                }
                if (dxball_rectangles_overlap(dxball_paddle_previous_x - dxball_paddle_width / 2,
                    dxball_paddle_previous_y, dxball_paddle_previous_x + dxball_paddle_width / 2,
                    dxball_paddle_previous_y + 7, ball->x, ball->y,
                    ball->x + sprite->width, ball->y + sprite->height) && ball->dy > 0) {
                    ball->wall_bounces = 0;
                    if (ball->bounce_count > 40) {
                        ++ball->speed;
                        if (ball->speed > 9) ball->speed = 9;
                        ball->bounce_count = 0;
                    }
                    if (dxball_bonus_17_active == 1) dxball_drop_bricks();
                    if (dxball_bonus_9_active == 1) {
                        dxball_gameplay_ops.stop_sound(18);
                        dxball_gameplay_ops.play_sound(18, 0, dxball_screen_pan(ball->x), 0);
                        ball->attached = 1;
                        ball->attach_offset = ball->x - dxball_paddle_x;
                        sign = ball->attach_offset < 1 ? -1 : 1;
                        limit = (DxBallInt)((long double)dxball_paddle_width / 2.0 * 0.8);
                        if (abs(ball->attach_offset) > limit) {
                            ball->attach_offset = limit * sign;
                            ball->attach_offset -= sprite->width / 2;
                        }
                    } else {
                        dxball_gameplay_ops.stop_sound(0);
                        dxball_gameplay_ops.play_sound(0, 0, dxball_screen_pan(ball->x), 0);
                        dxball_bounce_ball_from_paddle();
                        if (ball->speed > 7) {
                            dxball_gameplay_ops.play_sound(15, 0, dxball_screen_pan(ball->x), 0);
                            limit = dxball_reduced_particles == 0 ? 10 : 6;
                            for (i = 0; i < limit; ++i) {
                                dy = -1 - dxball_gameplay_ops.random_range(3);
                                dx = 3 - dxball_gameplay_ops.random_range(7);
                                dxball_gameplay_ops.particle(ball->x, ball->y, dx, dy, 176, 1);
                            }
                        }
                    }
                }
                dxball_hit_dx = ball->dx; dxball_hit_dy = ball->dy / 2;
                sign = ball->dy < 0 ? 1 : -1;
                y = ball->dy < 0 ? ball->y : ball->y + sprite->height;
                if (dxball_hit_screen_point(ball->x + sprite->width / 2, y)) {
                    if (dxball_destroy_hard_tiles == 0) {
                        ball->dy = abs(ball->dy) * sign;
                        if (sign == 1) ball->y += 15 - (y - 50) % 15;
                        else ball->y -= (y - 50) % 15;
                    }
                    ++ball->bounce_count; ++ball->wall_bounces;
                }
                sign = ball->dx < 0 ? 1 : -1;
                x = ball->dx < 0 ? ball->x - 2 : ball->x + sprite->width + 2;
                y = ball->y + (DxBallInt)((long double)sprite->height * 0.15);
                hit = dxball_hit_screen_point(x, y);
                if (!hit) {
                    y = ball->y + (DxBallInt)((long double)sprite->height * 0.85);
                    hit = dxball_hit_screen_point(x, y);
                }
                if (hit) {
                    if (dxball_destroy_hard_tiles == 0) ball->dx = abs(ball->dx) * sign;
                    ++ball->bounce_count; ++ball->wall_bounces;
                }
                if (ball->wall_bounces > 300) {
                    dxball_soften_special_bricks();
                    ball->wall_bounces = 0;
                }
            }
        }
    } while (dxball_advance_ball(&dxball_balls));
}

void dxball_update_projectiles(void)
{
    DxBallInt column, row;
    DxBallProjectileNode *node;
    if (dxball_begin_projectiles(&dxball_projectiles)) {
        do {
            node = dxball_projectiles.current;
            node->previous_x = node->x; node->previous_y = node->y;
            node->y -= 8;
            dxball_hit_dx = 1 - dxball_gameplay_ops.random_range(3);
            dxball_hit_dy = -2;
            column = (node->x - 20 + dxball_sprite_banks[dxball_sprite_bank].sprites[32]->width / 2) / 30;
            row = (node->y - 50) / 15;
            if (node->y < 0) {
                dxball_retire_projectile();
            } else if (row >= 0 && row < 20 && dxball_board_tiles[column + row * 20] != 0) {
                if (dxball_destroy_hard_tiles == 0) {
                    dxball_retire_projectile();
                }
                if (dxball_hit_board_tile(column, row)) dxball_score += 4;
            }
        } while (dxball_advance_projectile(&dxball_projectiles));
    }
}

void dxball_fire_projectiles(void)
{
    DxBallSprite *sprite;
    sprite = dxball_sprite_banks[dxball_sprite_bank].sprites[32];
    dxball_append_projectile(&dxball_projectiles);
    dxball_projectiles.current->x = dxball_paddle_x - (DxBallInt)((long double)dxball_paddle_width * 0.425) - sprite->width / 2;
    dxball_projectiles.current->y = dxball_paddle_y - sprite->height / 2;
    dxball_append_projectile(&dxball_projectiles);
    dxball_projectiles.current->x = dxball_paddle_x + (DxBallInt)((long double)dxball_paddle_width * 0.43) - sprite->width / 2;
    dxball_projectiles.current->y = dxball_paddle_y - sprite->height / 2;
    dxball_projectile_count += 2;
    dxball_gameplay_ops.stop_sound(17);
    dxball_gameplay_ops.play_sound(17, 0, dxball_screen_pan(dxball_projectiles.current->x), 0);
}

/* Recompute velocity without discarding the direction already chosen by a hit.
   Zero components take the original negative sign; X has the 1.2 scale. */
static void apply_ball_speed(DxBallInt slow)
{
    DxBallBallNode *ball;
    DxBallInt sign_x, sign_y;
    if (dxball_begin_balls(&dxball_balls)) {
        do {
            ball = dxball_balls.current;
            sign_x = ball->dx > 0 ? 1 : -1;
            sign_y = ball->dy > 0 ? 1 : -1;
            if (slow) ball->speed = 4;
            else {
                ball->speed += 2;
                if (ball->speed > 9) ball->speed = 9;
            }
            ball->dx = abs((DxBallInt)((long double)dxball_cosine(ball->angle) * ball->speed * 1.2)) * sign_x;
            ball->dy = abs((DxBallInt)(-(long double)dxball_sine(ball->angle) * ball->speed)) * sign_y;
            if (slow && ball->sprite != 61) ball->sprite = 1;
        } while (dxball_advance_ball(&dxball_balls));
    }
}

static void apply_ball_sprite(DxBallInt sprite)
{
    if (dxball_begin_balls(&dxball_balls)) {
        do { dxball_balls.current->sprite = sprite; } while (dxball_advance_ball(&dxball_balls));
    }
}

void dxball_ignite_balls(void)
{
    apply_ball_sprite(61);
}

void dxball_game_frame(void)
{
    if (dxball_paused == 1) {
        if (dxball_frame_ops.elapsed(dxball_palette_tick, 32)) {
            dxball_frame_ops.animate_palette(224, 231, 1);
            dxball_palette_tick = dxball_frame_ops.current_time();
        }
        return;
    }
    dxball_attached_ball_cue = 0;
    dxball_frame_ops.update_score();
    dxball_update_paddle_position();
    dxball_update_balls();
    dxball_update_projectiles();
    dxball_update_bonuses();
    dxball_update_particles();
    if (dxball_draw_to_primary != 0) dxball_frame_ops.wait_frames(1);
    dxball_frame_ops.restore_regions();
    dxball_paddle_previous_x = dxball_paddle_x;
    dxball_paddle_previous_y = dxball_paddle_y;
    dxball_process_brick_effects();
    if (dxball_begin_projectiles(&dxball_projectiles)) {
        do {
            dxball_frame_ops.draw_effect_sprite(32, dxball_projectiles.current->x, dxball_projectiles.current->y);
        } while (dxball_advance_projectile(&dxball_projectiles));
    }
    dxball_process_fire_effects();
    dxball_frame_ops.draw_paddle();
    if (dxball_begin_balls(&dxball_balls)) {
        do {
            dxball_frame_ops.draw_effect_sprite(dxball_balls.current->sprite, dxball_balls.current->x, dxball_balls.current->y);
        } while (dxball_advance_ball(&dxball_balls));
    }
    dxball_draw_bonuses();
    dxball_draw_particles();
    if (dxball_remaining_bricks == 1) dxball_frame_ops.last_brick();
    else if (dxball_remaining_bricks > 1 && dxball_last_brick_deadline != 0) {
        dxball_last_brick_deadline = 0;
        dxball_gameplay_ops.stop_sound(21);
    }
    dxball_frame_ops.draw_last_brick();
    if (dxball_draw_to_primary == 0) dxball_frame_ops.present();
    if (dxball_frame_ops.elapsed(dxball_palette_tick, 20)) {
        dxball_frame_ops.animate_palette(224, 231, 1);
        dxball_palette_tick = dxball_frame_ops.current_time();
    }
    dxball_apply_explosion_requests();
    if (dxball_bonus_3_active == 1) {
        apply_ball_speed(1); dxball_bonus_3_active = 0;
    }
    if (dxball_bonus_14_active == 1) {
        apply_ball_speed(0); dxball_bonus_14_active = 0;
    }
    if (dxball_bonus_18_active == 1) {
        apply_ball_sprite(55); dxball_bonus_18_active = 0;
    }
    if (dxball_bonus_12_active == 1) {
        dxball_clone_balls(); dxball_bonus_12_active = 0;
    }
    if (dxball_bonus_7_active == 1) {
        dxball_ignite_balls(); dxball_bonus_7_active = 0;
    }
    if (dxball_remaining_bricks < 1 && !dxball_begin_brick_effects(&dxball_brick_effects)
        && !dxball_begin_fire_effects(&dxball_fire_effects)) dxball_advance_level();
    dxball_frame_ops.restart_round();
    if (dxball_mouse_action == 1) {
        dxball_launch_requested = 1;
        if (dxball_bonus_8_active == 1 && dxball_projectile_count < 6) dxball_fire_projectiles();
        dxball_mouse_action = 0;
    } else dxball_launch_requested = 0;
    if (dxball_mouse_action == 2) dxball_mouse_action = 0;
}
