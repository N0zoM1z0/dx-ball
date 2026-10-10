#include "bonuses.h"
#include "effects.h"
#include "geometry.h"
#include "paddle.h"
#include "round.h"
#include "balls.h"
#include "sound.h"
#include "particles.h"
#include "startup.h"

#include <stdlib.h>

DxBallInt dxball_bonus_count;
DxBallInt dxball_bonus_3_active, dxball_bonus_3_ticks;
DxBallInt dxball_bonus_7_active, dxball_bonus_8_active, dxball_bonus_9_active;
DxBallInt dxball_bonus_12_active, dxball_bonus_14_active;
DxBallInt dxball_bonus_17_active, dxball_bonus_18_active;

void dxball_update_bonuses(void)
{
    if (dxball_begin_bonuses(&dxball_bonuses)) {
        do {
            dxball_bonuses.current->x += dxball_bonuses.current->dx;
            dxball_bonuses.current->y += dxball_bonuses.current->dy;
            ++dxball_bonuses.current->gravity_ticks;
            if (dxball_bonuses.current->gravity_ticks > 20) {
                ++dxball_bonuses.current->dy;
                dxball_bonuses.current->gravity_ticks = 0;
            }
            if (dxball_bonuses.current->x < 20) {
                dxball_bonuses.current->x = 20;
                dxball_bonuses.current->dx = abs(dxball_bonuses.current->dx);
                dxball_stop_sound(4);
                dxball_play_sound(4, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
            }
            if (dxball_bonuses.current->x > 619 - dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_bonuses.current->sprite]->width) {
                dxball_bonuses.current->x = 619 - dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_bonuses.current->sprite]->width;
                dxball_bonuses.current->dx = -abs(dxball_bonuses.current->dx);
                dxball_stop_sound(4);
                dxball_play_sound(4, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
            }
            if (dxball_bonuses.current->y < 0) {
                dxball_bonuses.current->y = 0;
                dxball_bonuses.current->dy = abs(dxball_bonuses.current->dy);
                dxball_stop_sound(4);
                dxball_play_sound(4, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
            }
            if (dxball_bonuses.current->y > 478 - dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_bonuses.current->sprite]->height) {
                dxball_retire_bonus();
            } else if (dxball_rectangles_overlap(
                dxball_paddle_previous_x - dxball_paddle_width / 2 + 5,
                dxball_paddle_previous_y,
                dxball_paddle_previous_x + dxball_paddle_width / 2 - 5,
                dxball_paddle_previous_y + 7,
                dxball_bonuses.current->x, dxball_bonuses.current->y,
                dxball_bonuses.current->x + dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_bonuses.current->sprite]->width,
                dxball_bonuses.current->y + dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_bonuses.current->sprite]->height)) {
                dxball_score += 100;
                switch (dxball_bonuses.current->kind) {
                case 0:
                    ++dxball_lives;
                    dxball_displayed_score = 999999999;
                    dxball_play_sound(13, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_bonus_8_active = 0;
                    dxball_bonus_9_active = 0;
                    dxball_destroy_hard_tiles = 0;
                    break;
                case 1:
                    dxball_play_sound(8, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_advance_level();
                    break;
                case 2:
                    dxball_play_sound(8, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_soften_special_bricks();
                    break;
                case 3:
                    dxball_play_sound(8, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_bonus_3_active = 1;
                    dxball_bonus_3_ticks = 0;
                    break;
                case 4:
                    dxball_play_sound(8, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_spread_explosive_bricks();
                    break;
                case 5:
                    dxball_play_sound(8, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_destroy_hard_tiles = 1;
                    break;
                case 6:
                    dxball_play_sound(8, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_scan_explosive_tiles();
                    break;
                case 7:
                    dxball_play_sound(8, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_bonus_7_active = 1;
                    break;
                case 8:
                    dxball_play_sound(8, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_bonus_8_active = 1;
                    break;
                case 9:
                    dxball_play_sound(8, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_bonus_9_active = 1;
                    break;
                case 10:
                    dxball_release_attached_balls();
                    dxball_play_sound(10, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    if (dxball_paddle_width < dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width) {
                        dxball_paddle_width = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width;
                    } else {
                        dxball_paddle_width += dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width;
                        if (dxball_paddle_width > dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width * 4) dxball_paddle_width = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width * 4;
                    }
                    dxball_update_paddle_position();
                    break;
                case 11:
                    dxball_release_attached_balls();
                    dxball_play_sound(11, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    if (dxball_paddle_width <= dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width)
                        dxball_paddle_width = (DxBallInt)((double)dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width / 2.0);
                    else dxball_paddle_width -= dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width;
                    dxball_update_paddle_position();
                    break;
                case 12:
                    dxball_play_sound(12, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_bonus_12_active = 1;
                    break;
                case 13:
                    dxball_lose_life();
                    break;
                case 14:
                case 15:
                    dxball_play_sound(9, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_bonus_14_active = 1;
                    break;
                case 16:
                    dxball_release_attached_balls();
                    dxball_play_sound(11, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_paddle_width = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width / 2;
                    dxball_update_paddle_position();
                    break;
                case 17:
                    dxball_play_sound(9, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_bonus_17_active = 1;
                    break;
                case 18:
                    dxball_play_sound(9, 0, dxball_screen_pan(dxball_bonuses.current->x), 0);
                    dxball_bonus_18_active = 1;
                    break;
                }
                dxball_retire_bonus();
            }
        } while (dxball_advance_bonus(&dxball_bonuses));
    }
    return;
}

DxBallInt DXBALL_FASTCALL dxball_append_bonus(DxBallBonusList *list)
{
    DxBallBonusNode *node;
    node = (DxBallBonusNode *)dxball_allocate_node(sizeof(DxBallBonusNode));
    if (node != NULL) {
        node->previous = list->last;
        node->next = NULL;
        if (list->last != NULL) list->last->next = node;
        else list->first = node;
        list->last = node;
        list->current = list->last;
    } else {
        exit(1);
    }
    return 1;
}

DxBallInt DXBALL_FASTCALL dxball_begin_bonuses(DxBallBonusList *list)
{
    list->current = list->first;
    return list->current != NULL;
}

DxBallInt DXBALL_FASTCALL dxball_advance_bonus(DxBallBonusList *list)
{
    if (list->current != NULL) {
        list->current = list->current->next;
        if (list->current == NULL) {
            list->current = list->first;
            return 0;
        }
        return 1;
    }
    return 0;
}

DxBallInt DXBALL_FASTCALL dxball_remove_bonus(DxBallBonusList *list)
{
    DxBallBonusNode *node;
    if (list->current != NULL) {
        node = list->current;
        if (node->previous != NULL) node->previous->next = node->next;
        if (node->next != NULL) {
            node->next->previous = node->previous;
            list->current = node->next;
        } else {
            list->current = node->previous;
        }
        if (list->first == node) list->first = node->next;
        if (list->last == node) list->last = node->previous;
        dxball_deallocate_node(node);
        return 1;
    } else {
        return 0;
    }
}

/* FUNCTION: DXBALL 0x00416570 */
DxBallInt DXBALL_FASTCALL dxball_clear_bonus_list(DxBallBonusList *list)
{
    while (dxball_remove_bonus(list)) {
    }
    return 1;
}

void dxball_generate_bonus(DxBallInt x, DxBallInt y, DxBallInt dx, DxBallInt dy)
{
    DxBallInt screen_x, chance, screen_y, kind;
    DxBallInt reduced_particle, full_particle, life_chance, level_chance;
    chance = dxball_random_range(10);
    if (dxball_bonus_count < 1 && chance <= 1) {
        screen_x = x * 30 + 19;
        screen_y = y * 15 + 50;
        dxball_stop_sound(2);
        dxball_play_sound(2, 0, dxball_screen_pan(screen_x), 0);
        /* The supported compilers evaluate these RNG arguments dy/dx/y/x. */
        if (dxball_reduced_particles != 0) {
            for (reduced_particle = 0; reduced_particle < 8; ++reduced_particle) {
                dxball_spawn_particle(screen_x + dxball_random_range(30),
                    screen_y + dxball_random_range(15), 4 - dxball_random_range(9),
                    2 - dxball_random_range(7), 16, 1);
            }
        } else {
            for (full_particle = 0; full_particle < 15; ++full_particle) {
                dxball_spawn_particle(screen_x + dxball_random_range(30),
                    screen_y + dxball_random_range(15), 4 - dxball_random_range(9),
                    2 - dxball_random_range(7), 16, 1);
            }
        }
        dxball_append_bonus(&dxball_bonuses);
        dxball_bonuses.current->x = screen_x;
        dxball_bonuses.current->y = screen_y;
        dxball_bonuses.current->dx = dx;
        dxball_bonuses.current->dy = dy;
        dxball_bonuses.current->gravity_ticks = 0;
        kind = dxball_random_range(19);
        switch (kind) {
        case 0:
            life_chance = dxball_random_range(5);
            if (life_chance == 1) {
                dxball_bonuses.current->kind = 0;
                dxball_bonuses.current->sprite = 35;
            } else {
                dxball_bonuses.current->kind = 13;
                dxball_bonuses.current->sprite = 48;
            }
            break;
        case 1:
            level_chance = dxball_random_range(5);
            if (level_chance == 1) {
                dxball_bonuses.current->kind = 1;
                dxball_bonuses.current->sprite = 36;
            } else {
                dxball_bonuses.current->kind = 13;
                dxball_bonuses.current->sprite = 48;
            }
            break;
        case 2:
            dxball_bonuses.current->kind = 2;
            dxball_bonuses.current->sprite = 37;
            break;
        case 3:
            dxball_bonuses.current->kind = 3;
            dxball_bonuses.current->sprite = 38;
            break;
        case 4:
            dxball_bonuses.current->kind = 4;
            dxball_bonuses.current->sprite = 39;
            break;
        case 5:
            dxball_bonuses.current->kind = 5;
            dxball_bonuses.current->sprite = 40;
            break;
        case 6:
            dxball_bonuses.current->kind = 6;
            dxball_bonuses.current->sprite = 41;
            break;
        case 7:
            dxball_bonuses.current->kind = 7;
            dxball_bonuses.current->sprite = 42;
            break;
        case 8:
            dxball_bonuses.current->kind = 8;
            dxball_bonuses.current->sprite = 43;
            break;
        case 9:
            dxball_bonuses.current->kind = 9;
            dxball_bonuses.current->sprite = 44;
            break;
        case 10:
            dxball_bonuses.current->kind = 10;
            dxball_bonuses.current->sprite = 45;
            break;
        case 11:
            dxball_bonuses.current->kind = 11;
            dxball_bonuses.current->sprite = 46;
            break;
        case 12:
            dxball_bonuses.current->kind = 12;
            dxball_bonuses.current->sprite = 47;
            break;
        case 13:
            dxball_bonuses.current->kind = 13;
            dxball_bonuses.current->sprite = 48;
            break;
        case 14:
            dxball_bonuses.current->kind = 10;
            dxball_bonuses.current->sprite = 45;
            break;
        case 15:
            dxball_bonuses.current->kind = 15;
            dxball_bonuses.current->sprite = 50;
            break;
        case 16:
            dxball_bonuses.current->kind = 16;
            dxball_bonuses.current->sprite = 51;
            break;
        case 17:
            dxball_bonuses.current->kind = 17;
            dxball_bonuses.current->sprite = 52;
            break;
        case 18:
            dxball_bonuses.current->kind = 18;
            dxball_bonuses.current->sprite = 53;
            break;
        }
        ++dxball_bonus_count;
    }
    return;
}

void dxball_retire_bonus(void)
{
    dxball_remove_bonus(&dxball_bonuses);
    --dxball_bonus_count;
    return;
}

void dxball_draw_bonuses(void)
{
    if (dxball_begin_bonuses(&dxball_bonuses)) {
        do {
            dxball_effect_ops.reduced_sprite(dxball_bonuses.current->sprite,
                                             dxball_bonuses.current->x,
                                             dxball_bonuses.current->y);
        } while (dxball_advance_bonus(&dxball_bonuses));
    }
    return;
}
