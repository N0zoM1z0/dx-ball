#include "balls.h"
#include "effects.h"
#include "paddle.h"
#include "trig.h"
#include <stdlib.h>

DxBallBallList dxball_balls, dxball_duplicate_balls;

DxBallInt DXBALL_FASTCALL dxball_append_ball(DxBallBallList *list)
{
    DxBallBallNode *node;
    node = (DxBallBallNode *)dxball_allocate_node(sizeof(DxBallBallNode));
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

DxBallInt DXBALL_FASTCALL dxball_begin_balls(DxBallBallList *list)
{
    list->current = list->first;
    return list->current != NULL;
}

DxBallInt DXBALL_FASTCALL dxball_advance_ball(DxBallBallList *list)
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

DxBallInt DXBALL_FASTCALL dxball_remove_ball(DxBallBallList *list)
{
    DxBallBallNode *node;
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

DxBallInt DXBALL_FASTCALL dxball_clear_ball_list(DxBallBallList *list)
{
    while (dxball_remove_ball(list)) {
    }
    return 1;
}

void dxball_bounce_ball_from_paddle(void)
{
    float left, ratio;
    long double precise_ratio;
    DxBallSprite *sprite;
    sprite = dxball_sprite_banks[dxball_sprite_bank].sprites[dxball_balls.current->sprite];
    left = (float)(dxball_paddle_x - dxball_paddle_width / 2);
    precise_ratio = ((long double)(dxball_balls.current->x + sprite->width / 2) - left) / dxball_paddle_width;
    ratio = (float)precise_ratio;
    if (precise_ratio <= 0.07) dxball_balls.current->angle = 150;
    else if (ratio <= 0.2) dxball_balls.current->angle = 135;
    else if (ratio <= 0.35) dxball_balls.current->angle = 120;
    else if (ratio <= 0.5) dxball_balls.current->angle = 105;
    else if (ratio <= 0.65) dxball_balls.current->angle = 75;
    else if (ratio <= 0.8) dxball_balls.current->angle = 60;
    else if (ratio <= 0.93) dxball_balls.current->angle = 45;
    else dxball_balls.current->angle = 30;
    if (dxball_balls.current->angle == 30 || dxball_balls.current->angle == 150) {
        dxball_gameplay_ops.stop_sound(16);
        dxball_gameplay_ops.play_sound(16, 0, dxball_screen_pan(dxball_balls.current->x), 0);
    } else {
        dxball_balls.current->y = dxball_paddle_y - sprite->height;
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

/* Copy state without copying links; this helper has no target entry claim. */
static void copy_ball(DxBallBallNode *destination, const DxBallBallNode *source)
{
    destination->sprite = source->sprite;
    destination->x = source->x;
    destination->y = source->y;
    destination->previous_x = source->previous_x;
    destination->previous_y = source->previous_y;
    destination->dx = source->dx;
    destination->dy = source->dy;
    destination->angle = source->angle;
    destination->speed = source->speed;
    destination->bounce_count = source->bounce_count;
    destination->attached = source->attached;
    destination->attach_offset = source->attach_offset;
    destination->wall_bounces = source->wall_bounces;
}

void dxball_clone_balls(void)
{
    if (dxball_begin_balls(&dxball_balls)) {
        do {
            dxball_append_ball(&dxball_duplicate_balls);
            copy_ball(dxball_duplicate_balls.current, dxball_balls.current);
            if (dxball_duplicate_balls.current->attached == 1) {
                --dxball_duplicate_balls.current->speed;
                if (dxball_duplicate_balls.current->speed < 4) dxball_duplicate_balls.current->speed = 4;
            }
            dxball_duplicate_balls.current->dx = -dxball_duplicate_balls.current->dx;
        } while (dxball_advance_ball(&dxball_balls));
    }
    if (dxball_begin_balls(&dxball_duplicate_balls)) {
        do {
            ++dxball_ball_count;
            dxball_append_ball(&dxball_balls);
            copy_ball(dxball_balls.current, dxball_duplicate_balls.current);
        } while (dxball_advance_ball(&dxball_duplicate_balls));
    }
    dxball_clear_ball_list(&dxball_duplicate_balls);
    return;
}
