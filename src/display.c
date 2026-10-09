#include "display.h"
#include "device.h"
#include "effects.h"
#include "geometry.h"
#include "paddle.h"
#include "particles.h"
#include "sound.h"

#include <stdlib.h>
#include <string.h>

DxBallRect dxball_dirty_regions[DXBALL_DIRTY_CAPACITY][2];
DxBallInt dxball_dirty_counts[2], dxball_dirty_page;
DxBallRect dxball_present_regions[DXBALL_PRESENT_CAPACITY];
DxBallInt dxball_present_keys[DXBALL_PRESENT_CAPACITY], dxball_present_count;
DxBallInt dxball_clip_regions, dxball_wait_vertical_blank;
DxBallUInt dxball_frame_wait_tick;
DxBallSurface dxball_restore_surface;
DxBallRect dxball_lightning_rect;
DxBallDisplayOps dxball_display_ops = { dxball_update_sound, dxball_recover_surfaces };

static void queue_dirty(DxBallInt page, const DxBallRect *rect)
{
    if (dxball_dirty_counts[page] < DXBALL_DIRTY_CAPACITY) {
        dxball_dirty_regions[dxball_dirty_counts[page]][page] = *rect;
        ++dxball_dirty_counts[page];
    }
}

static void queue_present(const DxBallRect *rect)
{
    if (dxball_reduced_particles == 1 && dxball_present_count < DXBALL_PRESENT_CAPACITY) {
        dxball_present_regions[dxball_present_count++] = *rect;
    }
}

static void queue_other_page(const DxBallRect *rect)
{
    if (dxball_draw_to_primary == 0 && dxball_display_buffer_count > 0 && dxball_reduced_particles == 0) {
        queue_dirty(1 - dxball_dirty_page, rect);
    }
}

static DxBallInt clip_rect(DxBallRect *rect)
{
    if (rect->top >= 481 || rect->bottom < 0 || rect->left >= 641 || rect->right < 0) return 0;
    if (rect->top < 0) rect->top = 0;
    if (rect->bottom > 480) rect->bottom = 480;
    if (rect->left < 0) rect->left = 0;
    if (rect->right > 640) rect->right = 640;
    return 1;
}

void dxball_reset_regions(void)
{
    memset(dxball_dirty_regions, 0, sizeof(dxball_dirty_regions));
    dxball_dirty_counts[0] = dxball_dirty_counts[1] = 0;
    dxball_dirty_page = 0;
    memset(dxball_present_regions, 0, sizeof(dxball_present_regions));
    dxball_present_count = 0;
}

/* FUNCTION: DXBALL 0x00408180 */
void dxball_blt_effect_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    DxBallRect rect;
    rect.left = x;
    rect.top = y;
    rect.right = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->width + x;
    rect.bottom = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->height + y;
    ((DxBallDDSurface *)dxball_effect_surface)->vtable->blt(
        (DxBallDDSurface *)dxball_effect_surface, &rect,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect,
        0x01008000, NULL);
    if (dxball_dirty_counts[dxball_dirty_page] < DXBALL_DIRTY_CAPACITY) {
        dxball_dirty_regions[dxball_dirty_counts[dxball_dirty_page]][dxball_dirty_page] = rect;
        ++dxball_dirty_counts[dxball_dirty_page];
    }
    if (dxball_reduced_particles == 1 && dxball_present_count < DXBALL_PRESENT_CAPACITY) {
        dxball_present_regions[dxball_present_count] = rect;
        ++dxball_present_count;
    }
    return;
}

/* FUNCTION: DXBALL 0x00408460 */
void dxball_blt_reduced_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    DxBallRect rect;
    rect.left = x;
    rect.top = y;
    rect.right = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->width + x;
    rect.bottom = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->height + y;
    ((DxBallDDSurface *)dxball_effect_surface)->vtable->blt(
        (DxBallDDSurface *)dxball_effect_surface, &rect,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect,
        0x01000000, NULL);
    if (dxball_dirty_counts[dxball_dirty_page] < DXBALL_DIRTY_CAPACITY) {
        dxball_dirty_regions[dxball_dirty_counts[dxball_dirty_page]][dxball_dirty_page] = rect;
        ++dxball_dirty_counts[dxball_dirty_page];
    }
    if (dxball_reduced_particles == 1 && dxball_present_count < DXBALL_PRESENT_CAPACITY) {
        dxball_present_regions[dxball_present_count] = rect;
        ++dxball_present_count;
    }
    return;
}

/* FUNCTION: DXBALL 0x00408740 */
void dxball_stretch_effect_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y,
                                 DxBallInt width, DxBallInt height)
{
    DxBallRect rect;
    rect.left = x;
    rect.top = y;
    rect.right = width + x;
    rect.bottom = height + y;
    ((DxBallDDSurface *)dxball_effect_surface)->vtable->blt(
        (DxBallDDSurface *)dxball_effect_surface, &rect,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect,
        0x01008000, NULL);
    if (dxball_dirty_counts[dxball_dirty_page] < DXBALL_DIRTY_CAPACITY) {
        dxball_dirty_regions[dxball_dirty_counts[dxball_dirty_page]][dxball_dirty_page] = rect;
        ++dxball_dirty_counts[dxball_dirty_page];
    }
    if (dxball_reduced_particles == 1 && dxball_present_count < DXBALL_PRESENT_CAPACITY) {
        dxball_present_regions[dxball_present_count] = rect;
        ++dxball_present_count;
    }
    return;
}

/* FUNCTION: DXBALL 0x00408880 */
void dxball_queue_sprite_region(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    DxBallRect rect;
    rect.left = x;
    rect.top = y;
    rect.right = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->width + x;
    rect.bottom = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->height + y;
    if (dxball_dirty_counts[dxball_dirty_page] < DXBALL_DIRTY_CAPACITY) {
        dxball_dirty_regions[dxball_dirty_counts[dxball_dirty_page]][dxball_dirty_page] = rect;
        ++dxball_dirty_counts[dxball_dirty_page];
    }
    if (dxball_reduced_particles == 1 && dxball_present_count < DXBALL_PRESENT_CAPACITY) {
        dxball_present_regions[dxball_present_count] = rect;
        ++dxball_present_count;
    }
    return;
}

/* FUNCTION: DXBALL 0x004082F0 */
void dxball_draw_effect_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    DxBallRect rect;
    rect.left = x;
    rect.top = y;
    rect.right = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->width + x;
    rect.bottom = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->height + y;
    ((DxBallDDSurface *)dxball_effect_surface)->vtable->blt_fast(
        (DxBallDDSurface *)dxball_effect_surface, x, y,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect,
        0x11);
    if (dxball_dirty_counts[dxball_dirty_page] < DXBALL_DIRTY_CAPACITY) {
        dxball_dirty_regions[dxball_dirty_counts[dxball_dirty_page]][dxball_dirty_page] = rect;
        ++dxball_dirty_counts[dxball_dirty_page];
    }
    if (dxball_reduced_particles == 1 && dxball_present_count < DXBALL_PRESENT_CAPACITY) {
        dxball_present_regions[dxball_present_count] = rect;
        ++dxball_present_count;
    }
    return;
}

/* FUNCTION: DXBALL 0x004085D0 */
void dxball_draw_reduced_sprite(DxBallInt sprite, DxBallInt x, DxBallInt y)
{
    DxBallRect rect;
    rect.left = x;
    rect.top = y;
    rect.right = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->width + x;
    rect.bottom = dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->height + y;
    ((DxBallDDSurface *)dxball_effect_surface)->vtable->blt_fast(
        (DxBallDDSurface *)dxball_effect_surface, x, y,
        dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->surface,
        &dxball_sprite_banks[dxball_sprite_bank].sprites[sprite]->source_rect,
        0x10);
    if (dxball_dirty_counts[dxball_dirty_page] < DXBALL_DIRTY_CAPACITY) {
        dxball_dirty_regions[dxball_dirty_counts[dxball_dirty_page]][dxball_dirty_page] = rect;
        ++dxball_dirty_counts[dxball_dirty_page];
    }
    if (dxball_reduced_particles == 1 && dxball_present_count < DXBALL_PRESENT_CAPACITY) {
        dxball_present_regions[dxball_present_count] = rect;
        ++dxball_present_count;
    }
    return;
}

void dxball_queue_region(DxBallInt left, DxBallInt top, DxBallInt right, DxBallInt bottom)
{
    DxBallRect rect;
    rect.left = left; rect.top = top; rect.right = right; rect.bottom = bottom;
    queue_dirty(dxball_dirty_page, &rect);
    queue_present(&rect);
}

void dxball_restore_effect_region(DxBallInt left, DxBallInt top, DxBallInt right, DxBallInt bottom)
{
    DxBallRect rect;
    DxBallDDSurface *surface;
    rect.left = left; rect.top = top; rect.right = right; rect.bottom = bottom;
    surface = (DxBallDDSurface *)dxball_effect_surface;
    surface->vtable->blt(surface, &rect, (DxBallDDSurface *)dxball_restore_surface, &rect, 0x01000000, NULL);
    queue_other_page(&rect);
    queue_present(&rect);
}

void dxball_invalidate_region(DxBallRect rect)
{
    if (dxball_dirty_counts[dxball_dirty_page] < DXBALL_DIRTY_CAPACITY) {
        dxball_dirty_regions[dxball_dirty_counts[dxball_dirty_page]][dxball_dirty_page] = rect;
        ++dxball_dirty_counts[dxball_dirty_page];
    }
    if (dxball_draw_to_primary == 0 && dxball_display_buffer_count > 0 &&
        dxball_reduced_particles == 0 &&
        dxball_dirty_counts[1 - dxball_dirty_page] < DXBALL_DIRTY_CAPACITY) {
        dxball_dirty_regions[dxball_dirty_counts[1 - dxball_dirty_page]][1 - dxball_dirty_page] = rect;
        ++dxball_dirty_counts[1 - dxball_dirty_page];
    }
    if (dxball_reduced_particles == 1 && dxball_present_count < DXBALL_PRESENT_CAPACITY) {
        dxball_present_regions[dxball_present_count] = rect;
        ++dxball_present_count;
    }
    return;
}

void dxball_restore_regions(void)
{
    DxBallInt i;
    DxBallRect *rect;
    DxBallDDSurface *surface;
    surface = (DxBallDDSurface *)dxball_effect_surface;
    for (i = 0; i < dxball_dirty_counts[dxball_dirty_page]; ++i) {
        rect = &dxball_dirty_regions[i][dxball_dirty_page];
        if (dxball_clip_regions == 1) {
            if (!clip_rect(rect)) continue;
            surface->vtable->blt(surface, rect, (DxBallDDSurface *)dxball_restore_surface, rect, 0x01000000, NULL);
        } else {
            surface->vtable->blt_fast(surface, rect->left, rect->top,
                (DxBallDDSurface *)dxball_restore_surface, rect, 0x10);
        }
        queue_present(rect);
    }
    dxball_dirty_counts[dxball_dirty_page] = 0;
}

void dxball_bind_board_surface(DxBallSurface surface) { dxball_restore_surface = surface; return; }

void dxball_bind_display_surface(DxBallSurface surface) { dxball_effect_surface = surface; return; }

void dxball_present(void)
{
    DxBallInt result;
    DxBallDDSurface *surface;
    if (dxball_reduced_particles == 0) {
        surface = (DxBallDDSurface *)dxball_primary_surface;
        do {
            result = surface->vtable->flip(surface, NULL, 0);
            if (result == 0) break;
            if (result == (DxBallInt)0x887601c2U) dxball_display_ops.recover_surfaces();
        } while (result == (DxBallInt)0x8876021cU);
        if (result == 0) {
            dxball_dirty_page = 1 - dxball_dirty_page;
            if (dxball_wait_vertical_blank == 0) dxball_wait_frames(1);
        }
    } else {
        dxball_wait_frames(1);
        dxball_present_regions_now();
    }
}

void dxball_present_regions_now(void)
{
    DxBallInt i, current;
    DxBallRect *a, *b;
    DxBallDDSurface *surface;
    for (i = 0; i < dxball_present_count; ++i) {
        dxball_present_keys[i] = dxball_present_regions[i].left + dxball_present_regions[i].top;
    }
    if (dxball_present_count > 0) {
        dxball_sort_present_regions(0, dxball_present_count - 1);
        current = 0;
        for (i = 1; i < dxball_present_count; ++i) {
            a = &dxball_present_regions[current]; b = &dxball_present_regions[i];
            if (!dxball_rectangles_overlap(a->left, a->top, a->right + 1, a->bottom + 1,
                    b->left, b->top, b->right, b->bottom)) current = i;
            else {
                if (b->left < a->left) a->left = b->left;
                if (b->top < a->top) a->top = b->top;
                if (b->right > a->right) a->right = b->right;
                if (b->bottom > a->bottom) a->bottom = b->bottom;
                b->top = 9999;
            }
        }
    }
    surface = (DxBallDDSurface *)dxball_primary_surface;
    for (i = 0; i < dxball_present_count; ++i) {
        a = &dxball_present_regions[i];
        if (a->top == 9999) continue;
        if (dxball_clip_regions == 1 && !clip_rect(a)) continue;
        surface->vtable->blt(surface, a, (DxBallDDSurface *)dxball_secondary_surface, a, 0x01000000, NULL);
    }
    dxball_present_count = 0;
}

void dxball_sort_present_regions(DxBallInt first, DxBallInt last)
{
    DxBallInt i, j, selected, key;
    DxBallRect rect;
    for (i = first; i < last; ++i) {
        selected = i;
        for (j = i; j <= last; ++j) {
            if (dxball_present_keys[j] < dxball_present_keys[selected]) selected = j;
        }
        if (i < selected) {
            key = dxball_present_keys[i];
            dxball_present_keys[i] = dxball_present_keys[selected];
            dxball_present_keys[selected] = key;
            rect = dxball_present_regions[i];
            dxball_present_regions[i] = dxball_present_regions[selected];
            dxball_present_regions[selected] = rect;
        }
    }
}

void dxball_wait_frames(DxBallInt frames)
{
    DxBallInt i;
    DxBallUInt now;
    for (i = 0; i < frames; ++i) {
        if (dxball_wait_vertical_blank != 0) {
            dxball_direct_draw->vtable->wait_vertical_blank(dxball_direct_draw, 1, NULL);
        } else {
            do { now = dxball_current_time(); }
            while (now >= dxball_frame_wait_tick && now < dxball_frame_wait_tick + 17);
            dxball_frame_wait_tick = dxball_current_time();
        }
    }
}

void dxball_animate_palette(DxBallInt first, DxBallInt last, DxBallInt rotate)
{
    DxBallByte red, green, blue;
    DxBallInt i;
    if (dxball_cursor_warp_disabled == 1) return;
    if (rotate == 1) {
        red = dxball_live_palette[first].red;
        green = dxball_live_palette[first].green;
        blue = dxball_live_palette[first].blue;
    } else {
        red = 0; green = 0; blue = 0;
    }
    for (i = first; i < last; ++i) dxball_live_palette[i] = dxball_live_palette[i + 1];
    dxball_live_palette[last].red = red;
    dxball_live_palette[last].green = green;
    dxball_live_palette[last].blue = blue;
    dxball_direct_palette->vtable->set_entries(dxball_direct_palette, 0, first,
        last - first + 1, &dxball_live_palette[first]);
    return;
}

void dxball_last_brick(void)
{
    DxBallInt remaining, x, y, tile_x, tile_y, center_x, center_y, i, dx, dy, px, py;
    DxBallUInt now;
    DxBallSprite *sprite;
    if (dxball_last_brick_deadline == 0) {
        now = dxball_clock_ops.time_ms();
        dxball_last_brick_deadline = (DxBallInt)(now + dxball_gameplay_ops.random_range(20000) + 40000);
    }
    remaining = (DxBallInt)((DxBallUInt)dxball_last_brick_deadline - dxball_clock_ops.time_ms());
    if (remaining > 0) {
        remaining /= 2;
        if (remaining < 4) remaining = 3;
        dxball_display_ops.update_sound(21, 0, 0, -(remaining / 3));
        return;
    }
    dxball_gameplay_ops.stop_sound(21);
    dxball_gameplay_ops.play_sound(22, 0, 0, 0);
    tile_x = tile_y = -1;
    for (x = 0; x < DXBALL_BOARD_WIDTH; ++x) {
        for (y = 0; y < DXBALL_BOARD_HEIGHT; ++y) {
            if (dxball_board_tiles[x + y * DXBALL_BOARD_WIDTH] != 0 &&
                dxball_board_tiles[x + y * DXBALL_BOARD_WIDTH] != 2) { tile_x = x; tile_y = y; }
        }
    }
    /* The original uses uninitialized coordinates if no eligible tile exists. */
    if (tile_x < 0) abort();
    center_x = tile_x * 30 + 35; center_y = tile_y * 15 + 57;
    dxball_queue_explosion_at(tile_x, tile_y);
    dxball_spawn_fire_effect(center_x, center_y);
    for (i = 0; i < (dxball_reduced_particles == 0 ? 30 : 15); ++i) {
        dy = 4 - dxball_gameplay_ops.random_range(11);
        dx = 6 - dxball_gameplay_ops.random_range(14);
        py = center_y - 7 + dxball_gameplay_ops.random_range(15);
        px = center_x - 15 + dxball_gameplay_ops.random_range(30);
        dxball_spawn_particle(px, py, dx, dy, 16, 1);
    }
    dxball_select_sprite_bank(2);
    sprite = dxball_sprite_banks[dxball_sprite_bank].sprites[1];
    x = center_x - sprite->width / 2; y = center_y - sprite->height;
    dxball_lightning_rect.left = dxball_lightning_rect.top = 0;
    dxball_lightning_rect.right = sprite->width; dxball_lightning_rect.bottom = sprite->height;
    if (x < 0) { dxball_lightning_rect.left = -x; x = 0; }
    if (sprite->width + x > 639) dxball_lightning_rect.right -= sprite->width + x - 639;
    if (y < 0) { dxball_lightning_rect.top = -y; y = 0; }
    if (sprite->height + y > 479) dxball_lightning_rect.bottom -= sprite->height + y - 479;
    dxball_lightning_x = x; dxball_lightning_y = y;
    dxball_lightning_frames = 4; dxball_last_brick_deadline = 0;
    dxball_select_sprite_bank(0);
}

void dxball_draw_last_brick(void)
{
    DxBallDDSurface *surface;
    if (dxball_lightning_frames > 0) {
        dxball_select_sprite_bank(2);
        surface = (DxBallDDSurface *)dxball_effect_surface;
        surface->vtable->blt_fast(surface, dxball_lightning_x, dxball_lightning_y,
            dxball_sprite_banks[dxball_sprite_bank].sprites[1]->surface, &dxball_lightning_rect, 0x11);
        dxball_queue_region(dxball_lightning_x, dxball_lightning_y,
            dxball_lightning_x + dxball_lightning_rect.right, dxball_lightning_y + dxball_lightning_rect.bottom);
        dxball_select_sprite_bank(0);
        --dxball_lightning_frames;
    }
}

void dxball_restore_board_region(DxBallSurface destination, DxBallInt x, DxBallInt y,
                                DxBallSurface source, const DxBallRect *rect, DxBallUInt flags)
{
    DxBallDDSurface *surface;
    surface = (DxBallDDSurface *)destination;
    surface->vtable->blt_fast(surface, x, y, (DxBallDDSurface *)source, rect, flags);
}
