#include "bonuses.h"
#include "effects.h"

#include <stdlib.h>

DxBallBonusList dxball_bonuses;
DxBallInt dxball_bonus_count;

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
