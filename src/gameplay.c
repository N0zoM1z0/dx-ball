#include "gameplay.h"
#include "effects.h"
#include "particles.h"

#include <stdlib.h>

DxBallInt dxball_remaining_bricks;
DxBallInt dxball_destroy_hard_tiles;
DxBallInt dxball_reduced_particles;
DxBallInt dxball_explosion_pending;
DxBallInt dxball_score;
double dxball_pan_scale = 1.0;
DxBallExplosionList dxball_explosions;
DxBallGameplayOps dxball_gameplay_ops = { malloc, dxball_spawn_brick_effect, NULL, NULL, NULL, dxball_spawn_particle };

void *dxball_allocate_node(size_t size)
{
    return dxball_gameplay_ops.allocate_node(size);
}

DxBallInt DXBALL_FASTCALL dxball_append_explosion(DxBallExplosionList *list)
{
    DxBallExplosionNode *node;
    node = (DxBallExplosionNode *)dxball_allocate_node(sizeof(DxBallExplosionNode));
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

DxBallInt dxball_screen_pan(DxBallInt x)
{
    double pan;
    pan = (double)x;
    pan = pan * 1.5625;
    pan = pan - 500.0;
    pan = pan * dxball_pan_scale;
    return (DxBallInt)pan;
}

DxBallInt dxball_hit_board_tile(DxBallInt x, DxBallInt y)
{
    DxBallInt score_hit, pan, cell, i, count, px, py, dx, dy;
    DxBallByte tile;
    score_hit = 1;
    pan = dxball_screen_pan(x * 30 + 20);
    cell = x + y * DXBALL_BOARD_WIDTH;
    tile = dxball_board_tiles[cell];
    switch (tile) {
    case 0:
        break;
    case 1: case 5: case 6: case 9: case 10: case 11: case 12:
    case 13: case 14: case 15: case 16: case 17: case 18: case 19:
    case 20: case 22:
        dxball_gameplay_ops.brick_effect(x, y, tile, 0);
        dxball_board_tiles[cell] = 0;
        dxball_gameplay_ops.stop_sound(7);
        dxball_gameplay_ops.play_sound(7, 0, pan, 0);
        --dxball_remaining_bricks;
        break;
    case 2:
        dxball_gameplay_ops.brick_effect(x, y, tile, 1);
        if (dxball_destroy_hard_tiles != 0) {
            dxball_board_tiles[cell] = 0;
        } else {
            score_hit = 0;
        }
        dxball_gameplay_ops.stop_sound(3);
        dxball_gameplay_ops.play_sound(3, 0, pan, 0);
        break;
    case 3: case 4:
        dxball_gameplay_ops.brick_effect(x, y, tile, 1);
        dxball_board_tiles[cell] = (DxBallByte)(tile + 1);
        if (dxball_destroy_hard_tiles != 0) {
            dxball_board_tiles[cell] = 0;
            --dxball_remaining_bricks;
        }
        dxball_gameplay_ops.stop_sound(1);
        dxball_gameplay_ops.play_sound(1, 0, pan, 0);
        break;
    case 7:
        dxball_gameplay_ops.brick_effect(x, y, tile, 1);
        dxball_board_tiles[cell] = 6;
        if (dxball_destroy_hard_tiles != 0) {
            dxball_board_tiles[cell] = 0;
            --dxball_remaining_bricks;
        }
        dxball_gameplay_ops.stop_sound(19);
        dxball_gameplay_ops.play_sound(19, 0, pan, 0);
        count = dxball_reduced_particles == 0 ? 8 : 4;
        for (i = 0; i < count; ++i) {
            /* Target evaluation order is dy, dx, y, x. Keep RNG consumption. */
            dy = 2 - dxball_gameplay_ops.random_range(5);
            dx = 2 - dxball_gameplay_ops.random_range(5);
            py = 50 + y * 15 + dxball_gameplay_ops.random_range(15);
            px = 20 + x * 30 + dxball_gameplay_ops.random_range(30);
            dxball_gameplay_ops.particle(px, py, dx, dy, 119, 1);
        }
        break;
    case 8:
        dxball_explosion_pending = 1;
        dxball_append_explosion(&dxball_explosions);
        dxball_explosions.current->kind = 1;
        dxball_explosions.current->x = x;
        dxball_explosions.current->y = y;
        break;
    case 21:
        dxball_gameplay_ops.brick_effect(x, y, tile, 1);
        dxball_board_tiles[cell] = 2;
        if (dxball_destroy_hard_tiles != 0) {
            dxball_board_tiles[cell] = 0;
        }
        dxball_gameplay_ops.stop_sound(1);
        dxball_gameplay_ops.play_sound(1, 0, pan, 0);
        --dxball_remaining_bricks;
        break;
    default:
        dxball_board_tiles[cell] = 0;
    }
    dxball_select_surface(dxball_board_surface);
    dxball_draw_board_tile(x, y, 0);
    return score_hit;
}

void dxball_scan_explosive_tiles(void)
{
    DxBallInt x, y;
    for (x = 0; x < DXBALL_BOARD_WIDTH; ++x) {
        for (y = 0; y < DXBALL_BOARD_HEIGHT; ++y) {
            /* The target scan sign-extends the stored byte before comparing. */
            if ((signed char)dxball_board_tiles[x + y * DXBALL_BOARD_WIDTH] == 8) {
                if (dxball_hit_board_tile(x, y) != 0) {
                    dxball_score += 4;
                }
            }
        }
    }
    return;
}

DxBallInt DXBALL_FASTCALL dxball_begin_explosions(DxBallExplosionList *list)
{
    list->current = list->first;
    return list->current != NULL;
}

DxBallInt DXBALL_FASTCALL dxball_advance_explosion(DxBallExplosionList *list)
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

DxBallInt DXBALL_FASTCALL dxball_remove_explosion(DxBallExplosionList *list)
{
    DxBallExplosionNode *node;
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

void dxball_queue_explosion_at(DxBallInt x, DxBallInt y)
{
    if ((signed char)dxball_board_tiles[x + y * DXBALL_BOARD_WIDTH] != 0) {
        dxball_explosion_pending = 1;
        dxball_append_explosion(&dxball_explosions);
        dxball_explosions.current->kind = 1;
        dxball_explosions.current->x = x;
        dxball_explosions.current->y = y;
    }
    return;
}
