#include "bonuses.h"
#include "effects.h"
#include "geometry.h"
#include "paddle.h"
#include "round.h"
#include "balls.h"

#include <stdlib.h>

DxBallBonusList dxball_bonuses;
DxBallInt dxball_bonus_count;
DxBallInt dxball_bonus_3_active, dxball_bonus_3_ticks;
DxBallInt dxball_bonus_7_active, dxball_bonus_8_active, dxball_bonus_9_active;
DxBallInt dxball_bonus_12_active, dxball_bonus_14_active;
DxBallInt dxball_bonus_17_active, dxball_bonus_18_active;

/* Source helpers, not separate target function claims. */
static void play_bonus_sound(DxBallInt sound)
{
    dxball_gameplay_ops.play_sound(sound, 0,
        dxball_screen_pan(dxball_bonuses.current->x), 0);
}

static void apply_bonus_kind(void)
{
    DxBallInt base_width;
    switch (dxball_bonuses.current->kind) {
    case 0:
        ++dxball_lives;
        dxball_displayed_score = 999999999;
        play_bonus_sound(13);
        dxball_bonus_8_active = 0;
        dxball_bonus_9_active = 0;
        dxball_destroy_hard_tiles = 0;
        break;
    case 1:
        play_bonus_sound(8);
        dxball_advance_level();
        break;
    case 2:
        play_bonus_sound(8);
        dxball_soften_special_bricks();
        break;
    case 3:
        play_bonus_sound(8);
        dxball_bonus_3_active = 1;
        dxball_bonus_3_ticks = 0;
        break;
    case 4:
        play_bonus_sound(8);
        dxball_spread_explosive_bricks();
        break;
    case 5:
        play_bonus_sound(8);
        dxball_destroy_hard_tiles = 1;
        break;
    case 6:
        play_bonus_sound(8);
        dxball_scan_explosive_tiles();
        break;
    case 7:
        play_bonus_sound(8);
        dxball_bonus_7_active = 1;
        break;
    case 8:
        play_bonus_sound(8);
        dxball_bonus_8_active = 1;
        break;
    case 9:
        play_bonus_sound(8);
        dxball_bonus_9_active = 1;
        break;
    case 10:
        dxball_release_attached_balls();
        play_bonus_sound(10);
        base_width = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width;
        if (dxball_paddle_width < base_width) {
            dxball_paddle_width = base_width;
        } else {
            dxball_paddle_width += base_width;
            if (dxball_paddle_width > base_width * 4) dxball_paddle_width = base_width * 4;
        }
        dxball_update_paddle_position();
        break;
    case 11:
        dxball_release_attached_balls();
        play_bonus_sound(11);
        base_width = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width;
        if (dxball_paddle_width > base_width) dxball_paddle_width -= base_width;
        else dxball_paddle_width = (DxBallInt)((double)base_width / 2.0);
        dxball_update_paddle_position();
        break;
    case 12:
        play_bonus_sound(12);
        dxball_bonus_12_active = 1;
        break;
    case 13:
        dxball_lose_life();
        break;
    case 14:
    case 15:
        play_bonus_sound(9);
        dxball_bonus_14_active = 1;
        break;
    case 16:
        dxball_release_attached_balls();
        play_bonus_sound(11);
        base_width = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_paddle_sprite]->width;
        dxball_paddle_width = base_width / 2;
        dxball_update_paddle_position();
        break;
    case 17:
        play_bonus_sound(9);
        dxball_bonus_17_active = 1;
        break;
    case 18:
        play_bonus_sound(9);
        dxball_bonus_18_active = 1;
        break;
    }
}

void dxball_update_bonuses(void)
{
    DxBallSprite *sprite;
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
                dxball_gameplay_ops.stop_sound(4);
                play_bonus_sound(4);
            }
            sprite = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_bonuses.current->sprite];
            if (dxball_bonuses.current->x > 619 - sprite->width) {
                dxball_bonuses.current->x = 619 - sprite->width;
                dxball_bonuses.current->dx = -abs(dxball_bonuses.current->dx);
                dxball_gameplay_ops.stop_sound(4);
                play_bonus_sound(4);
            }
            if (dxball_bonuses.current->y < 0) {
                dxball_bonuses.current->y = 0;
                dxball_bonuses.current->dy = abs(dxball_bonuses.current->dy);
                dxball_gameplay_ops.stop_sound(4);
                play_bonus_sound(4);
            }
            if (dxball_bonuses.current->y > 478 - sprite->height) {
                dxball_retire_bonus();
            } else if (dxball_rectangles_overlap(
                dxball_paddle_previous_x - dxball_paddle_width / 2 + 5,
                dxball_paddle_previous_y,
                dxball_paddle_previous_x + dxball_paddle_width / 2 - 5,
                dxball_paddle_previous_y + 7,
                dxball_bonuses.current->x, dxball_bonuses.current->y,
                dxball_bonuses.current->x + sprite->width,
                dxball_bonuses.current->y + sprite->height)) {
                dxball_score += 100;
                apply_bonus_kind();
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
    DxBallInt chance, screen_x, screen_y, count, i, px, py, vx, vy, kind;
    /* The chance draw happens even when a bonus already occupies the field. */
    chance = dxball_gameplay_ops.random_range(10);
    if (dxball_bonus_count < 1 && chance < 2) {
        screen_x = x * 30 + 19;
        screen_y = y * 15 + 50;
        dxball_gameplay_ops.stop_sound(2);
        dxball_gameplay_ops.play_sound(2, 0, dxball_screen_pan(screen_x), 0);
        count = dxball_reduced_particles == 0 ? 15 : 8;
        for (i = 0; i < count; ++i) {
            vy = 2 - dxball_gameplay_ops.random_range(7);
            vx = 4 - dxball_gameplay_ops.random_range(9);
            py = screen_y + dxball_gameplay_ops.random_range(15);
            px = screen_x + dxball_gameplay_ops.random_range(30);
            dxball_gameplay_ops.particle(px, py, vx, vy, 16, 1);
        }
        dxball_append_bonus(&dxball_bonuses);
        dxball_bonuses.current->x = screen_x;
        dxball_bonuses.current->y = screen_y;
        dxball_bonuses.current->dx = dx;
        dxball_bonuses.current->dy = dy;
        dxball_bonuses.current->gravity_ticks = 0;
        kind = dxball_gameplay_ops.random_range(19);
        if (kind == 0 || kind == 1) {
            if (dxball_gameplay_ops.random_range(5) != 1) kind = 13;
        } else if (kind == 14) {
            kind = 10;
        }
        dxball_bonuses.current->kind = kind;
        dxball_bonuses.current->sprite = kind + 35;
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
