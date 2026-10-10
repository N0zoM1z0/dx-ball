#include "allocator.h"
#include "effects.h"
#include "bonuses.h"
#include "display.h"

#include <stdlib.h>

DxBallInt dxball_hit_dx, dxball_hit_dy;
DxBallSurface dxball_effect_surface;
DxBallEffectOps dxball_effect_ops = {
    dxball_runtime_delete, dxball_generate_bonus, dxball_draw_keyed_sprite, dxball_draw_reduced_sprite, dxball_restore_effect_region
};

void dxball_deallocate_node(void *node)
{
    dxball_effect_ops.deallocate_node(node);
}

DxBallInt DXBALL_FASTCALL dxball_begin_brick_effects(DxBallBrickEffectList *list)
{
    list->current = list->first;
    return list->current != NULL;
}

DxBallInt DXBALL_FASTCALL dxball_advance_brick_effect(DxBallBrickEffectList *list)
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

DxBallInt DXBALL_FASTCALL dxball_append_brick_effect(DxBallBrickEffectList *list)
{
    DxBallBrickEffectNode *node;
    node = (DxBallBrickEffectNode *)dxball_allocate_node(sizeof(DxBallBrickEffectNode));
    if (node != NULL) {
        node->previous = list->last;
        node->next = NULL;
        if (list->last != NULL) {
            list->last->next = node;
        } else {
            list->first = node;
        }
        list->last = node;
        list->current = list->last;
    } else {
        exit(1);
    }
    return 1;
}

DxBallInt DXBALL_FASTCALL dxball_remove_brick_effect(DxBallBrickEffectList *list)
{
    DxBallBrickEffectNode *node;
    if (list->current != NULL) {
        node = list->current;
        if (node->previous != NULL) {
            node->previous->next = node->next;
        }
        if (node->next != NULL) {
            node->next->previous = node->previous;
            list->current = node->next;
        } else {
            list->current = node->previous;
        }
        if (list->first == node) {
            list->first = node->next;
        }
        if (list->last == node) {
            list->last = node->previous;
        }
        dxball_runtime_delete(node);
        return 1;
    } else {
        return 0;
    }
}

/* FUNCTION: DXBALL 0x004165A0 */
DxBallInt DXBALL_FASTCALL dxball_clear_brick_effect_list(DxBallBrickEffectList *list)
{
    while (dxball_remove_brick_effect(list)) {
    }
    return 1;
}

void dxball_spawn_explosion_effect(DxBallInt x, DxBallInt y)
{
    dxball_append_brick_effect(&dxball_brick_effects);
    dxball_brick_effects.current->kind = 1;
    dxball_brick_effects.current->sprite = 22;
    dxball_brick_effects.current->x = x * 30 + 20;
    dxball_brick_effects.current->y = y * 15 + 50;
    dxball_brick_effects.current->frames = 8;
    dxball_brick_effects.current->period = 0;
    dxball_brick_effects.current->ticks = 0;
    dxball_board_aux[x + y * DXBALL_BOARD_WIDTH] = 1;
    return;
}

void dxball_spawn_brick_effect(DxBallInt x, DxBallInt y, DxBallByte tile, DxBallInt mode)
{
    dxball_append_brick_effect(&dxball_brick_effects);
    if (mode == 0) {
        dxball_brick_effects.current->kind = 2;
        dxball_brick_effects.current->x = x;
        dxball_brick_effects.current->y = y;
        dxball_brick_effects.current->tile = tile;
        dxball_brick_effects.current->frames = 3;
        dxball_brick_effects.current->sprite = 20;
        dxball_brick_effects.current->period = 2;
        dxball_brick_effects.current->ticks = 2;
        dxball_generate_bonus(x, y, dxball_hit_dx, dxball_hit_dy);
    } else {
        dxball_brick_effects.current->kind = 2;
        dxball_brick_effects.current->x = x;
        dxball_brick_effects.current->y = y;
        dxball_brick_effects.current->tile = tile;
        dxball_brick_effects.current->frames = 2;
        dxball_brick_effects.current->sprite = 19;
        dxball_brick_effects.current->period = 2;
        dxball_brick_effects.current->ticks = 2;
    }
    return;
}

void dxball_step_explosion_effect(void)
{
    DxBallInt x, y;
    DxBallRect rect;
    DxBallInt cleanup_x, cleanup_y;
    ++dxball_brick_effects.current->ticks;
    if (dxball_brick_effects.current->period <= dxball_brick_effects.current->ticks) {
        --dxball_brick_effects.current->frames;
        if (dxball_brick_effects.current->frames == 5) {
            x = (dxball_brick_effects.current->x - 20) / 30;
            y = (dxball_brick_effects.current->y - 50) / 15;
            if ((signed char)dxball_board_tiles[x + y * DXBALL_BOARD_WIDTH] == 8) {
                if (y - 1 >= 0) {
                    dxball_queue_explosion_at(x, y - 1);
                    if (x - 1 >= 0) dxball_queue_explosion_at(x - 1, y - 1);
                    if (x + 1 < DXBALL_BOARD_WIDTH) dxball_queue_explosion_at(x + 1, y - 1);
                }
                if (y + 1 < DXBALL_BOARD_HEIGHT) {
                    dxball_queue_explosion_at(x, y + 1);
                    if (x - 1 >= 0) dxball_queue_explosion_at(x - 1, y + 1);
                    if (x + 1 < DXBALL_BOARD_WIDTH) dxball_queue_explosion_at(x + 1, y + 1);
                }
                if (x - 1 >= 0) dxball_queue_explosion_at(x - 1, y);
                if (x + 1 < DXBALL_BOARD_WIDTH) dxball_queue_explosion_at(x + 1, y);
            }
            if ((signed char)dxball_board_tiles[x + y * DXBALL_BOARD_WIDTH] != 0 &&
                    (signed char)dxball_board_tiles[x + y * DXBALL_BOARD_WIDTH] != 2) {
                --dxball_remaining_bricks;
            }
            dxball_board_tiles[x + y * DXBALL_BOARD_WIDTH] = 0;
        }
        if (dxball_brick_effects.current->frames < 1) {
            rect.left = dxball_brick_effects.current->x;
            rect.top = dxball_brick_effects.current->y;
            rect.right = dxball_brick_effects.current->x + 30;
            rect.bottom = dxball_brick_effects.current->y + 15;
            ((DxBallDDSurface *)dxball_board_surface)->vtable->blt_fast(
                (DxBallDDSurface *)dxball_board_surface,
                dxball_brick_effects.current->x, dxball_brick_effects.current->y,
                (DxBallDDSurface *)dxball_background_surface, &rect, 0x10);
            dxball_restore_effect_region(rect.left, rect.top, rect.right, rect.bottom);
            cleanup_x = (dxball_brick_effects.current->x - 20) / 30;
            cleanup_y = (dxball_brick_effects.current->y - 50) / 15;
            dxball_board_aux[cleanup_x + cleanup_y * DXBALL_BOARD_WIDTH] = 0;
            dxball_remove_brick_effect(&dxball_brick_effects);
        } else {
            dxball_select_surface(dxball_effect_surface);
            if (dxball_reduced_particles != 0) {
                dxball_draw_reduced_sprite(dxball_brick_effects.current->sprite,
                                           dxball_brick_effects.current->x,
                                           dxball_brick_effects.current->y);
            } else {
                dxball_draw_sprite(dxball_brick_effects.current->sprite,
                                   dxball_brick_effects.current->x,
                                   dxball_brick_effects.current->y);
            }
            ++dxball_brick_effects.current->sprite;
            dxball_brick_effects.current->ticks = 0;
        }
    }
    return;
}

void dxball_step_brick_effect(void)
{
    DxBallRect rect;
    DxBallInt x, y;
    x = dxball_brick_effects.current->x * 30 + 20;
    y = dxball_brick_effects.current->y * 15 + 50;
    ++dxball_brick_effects.current->ticks;
    rect.left = x;
    rect.top = y;
    rect.right = x + 30;
    rect.bottom = y + 15;
    if (dxball_brick_effects.current->period <= dxball_brick_effects.current->ticks) {
        --dxball_brick_effects.current->frames;
        if (dxball_brick_effects.current->frames < 1) {
            dxball_select_surface(dxball_board_surface);
            dxball_draw_board_tile(dxball_brick_effects.current->x, dxball_brick_effects.current->y, 0);
            dxball_remove_brick_effect(&dxball_brick_effects);
        } else {
            dxball_select_surface(dxball_board_surface);
            dxball_draw_board_tile(dxball_brick_effects.current->x, dxball_brick_effects.current->y, 0);
            dxball_draw_keyed_sprite(dxball_brick_effects.current->sprite, x, y);
            ++dxball_brick_effects.current->sprite;
            dxball_brick_effects.current->ticks = 0;
        }
        dxball_restore_effect_region(rect.left, rect.top, rect.right, rect.bottom);
    }
    return;
}

void dxball_process_brick_effects(void)
{
    if (dxball_begin_brick_effects(&dxball_brick_effects)) {
        do {
            switch (dxball_brick_effects.current->kind) {
                case 1: dxball_step_explosion_effect(); break;
                case 2: dxball_step_brick_effect(); break;
            }
        } while (dxball_advance_brick_effect(&dxball_brick_effects));
    }
    return;
}

void dxball_apply_explosion_requests(void)
{
    DxBallInt present, sound, dx;
    present = dxball_begin_explosions(&dxball_explosions);
    while (present != 0) {
        if (dxball_explosions.current->kind == 1 &&
                dxball_board_aux[dxball_explosions.current->x +
                                  dxball_explosions.current->y * DXBALL_BOARD_WIDTH] == 0) {
            dxball_spawn_explosion_effect(dxball_explosions.current->x,
                                           dxball_explosions.current->y);
            dxball_score += 4;
            dx = dxball_gameplay_ops.random_range(5) - 2;
            dxball_effect_ops.bonus(dxball_explosions.current->x,
                                    dxball_explosions.current->y, dx, -2);
        }
        dxball_remove_explosion(&dxball_explosions);
        present = dxball_advance_explosion(&dxball_explosions);
    }
    if (dxball_explosion_pending == 1) {
        sound = dxball_gameplay_ops.random_range(3) + 30;
        dxball_gameplay_ops.stop_sound(sound);
        dxball_gameplay_ops.play_sound(sound, 0, 0, 0);
        dxball_explosion_pending = 0;
    }
}
