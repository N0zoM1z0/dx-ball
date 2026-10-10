#include "editor.h"
#include "platform.h"
#include "intro.h"
#include "paddle.h"
#include "round.h"
#include "ui.h"
#include <stdio.h>
#include <string.h>

DxBallHitRegion dxball_hit_regions[DXBALL_HIT_REGION_CAPACITY];
DxBallInt dxball_hit_region_count, dxball_editor_selected_tile;

void dxball_initialize_hit_regions(DxBallInt count)
{
    DxBallInt i;
    DxBallHitRegion *region;
    dxball_hit_region_count = count + 1;
    for (i = 0; i <= dxball_hit_region_count; ++i) {
        region = dxball_hit_regions + i;
        region->left = region->top = region->right = region->bottom = region->active = 0;
    }
}
void dxball_set_hit_region(DxBallInt index, DxBallInt left, DxBallInt top,
                          DxBallInt right, DxBallInt bottom)
{
    dxball_hit_regions[index].left = left;
    dxball_hit_regions[index].top = top;
    dxball_hit_regions[index].right = right;
    dxball_hit_regions[index].bottom = bottom;
    dxball_hit_regions[index].active = 1;
    return;
}
/* FUNCTION: DXBALL 0x00401F20 */






DxBallInt dxball_find_hit_region(DxBallInt x, DxBallInt y)
{
    DxBallInt i, hit = 0;
    DxBallHitRegion *region;
    for (i = 1; i < dxball_hit_region_count; ++i) {
        region = dxball_hit_regions + i;
        if (region->active != 0 && region->left <= x && x <= region->right &&
            region->top <= y && y <= region->bottom) hit = i;
    }
    return hit;
}

void dxball_draw_editor_choices(void)
{
    DxBallInt tile, x = 20, y = 385;
    dxball_select_surface((DxBallSurface)dxball_board_surface);
    for (tile = 1; tile < 23; ++tile) {
        dxball_draw_sprite(dxball_board_tile_sprite(tile), x, y);
        dxball_set_hit_region(tile, x, y, x + 30, y + 15);
        x += 32;
        if (x > 280) { x = 20; y += 17; }
    }
}
void dxball_draw_editor_status(void)
{
    DxBallInt sprite = dxball_board_tile_sprite(dxball_editor_selected_tile);
    DxBallDDSurface *surface = (DxBallDDSurface *)dxball_active_surface;
    DxBallRect preview = {25, 5, 55, 20}, label = {65, 5, 639, 20};
    char number[12]; /* Signed 32-bit decimal, sign and terminating NUL. */
    if (sprite == 0)
        surface->vtable->blt_fast(surface, 25, 5, (DxBallDDSurface *)dxball_background_surface, &preview, 0x10);
    else dxball_draw_sprite(sprite, 25, 5);
    surface->vtable->blt_fast(surface, 65, 5, (DxBallDDSurface *)dxball_background_surface, &label, 0x10);
    sprintf(number, "%d", dxball_board_index + 1);
    dxball_draw_text(75, 17, (DxBallInt)strlen(number), number);
    dxball_draw_text(360, 380, 25, "+           -- Next Board");
    dxball_draw_text(360, 390, 29, "-           -- Previous Board");
    dxball_draw_text(360, 400, 20, "BKSP  -- Clear Board");
    dxball_draw_text(360, 410, 26, "L           -- Load Boards");
    dxball_draw_text(360, 420, 26, "S           -- Save Boards");
    dxball_draw_text(360, 430, 21, "CTRL  -- Hold to Draw");
}

void dxball_initialize_editor(void)
{
    dxball_runtime_ops.reset_regions();
    dxball_runtime_ops.clear_surface(dxball_background_surface, 0);
    dxball_runtime_ops.load_pcx((DxBallDDSurface *)dxball_background_surface, "mbbkgrnd.pcx", 2, 0, 0);
    dxball_runtime_ops.load_sprite_bank(0, 1, "mball2.sbk");
    dxball_runtime_ops.load_sprite_bank(1, 1, "sfont.sbk");
    dxball_runtime_ops.load_sprite_bank(2, 1, "mainmenu.sbk");
    dxball_select_sprite_bank(0); dxball_select_font_bank(1);
    dxball_runtime_ops.bind_board_surface((DxBallSurface)dxball_board_surface);
    dxball_runtime_ops.bind_display_surface((DxBallSurface)(dxball_draw_to_primary == 0 ? dxball_secondary_surface : dxball_primary_surface));
    dxball_editor_selected_tile = 1; dxball_initialize_hit_regions(23);
    dxball_board_index = 0; dxball_load_editor_board(0);
    dxball_redraw_mode(); dxball_runtime_ops.palette_transition(1, 6, 0, 255, 1);
}
void dxball_redraw_editor(void)
{
    DxBallRect rect = {0, 0, 640, 480};
    DxBallDDSurface *board = (DxBallDDSurface *)dxball_board_surface;
    DxBallDDSurface *primary = (DxBallDDSurface *)dxball_primary_surface;
    DxBallDDSurface *secondary = (DxBallDDSurface *)dxball_secondary_surface;
    dxball_runtime_ops.clear_surface((DxBallSurface)dxball_primary_surface, 0);
    if (dxball_draw_to_primary == 0) dxball_runtime_ops.clear_surface((DxBallSurface)dxball_secondary_surface, 0);
    dxball_runtime_ops.clear_surface((DxBallSurface)dxball_board_surface, 0);
    board->vtable->blt(board, &rect, (DxBallDDSurface *)dxball_background_surface, &rect, 0x1000000, NULL);
    dxball_draw_board(0); dxball_draw_editor_choices(); dxball_draw_editor_status();
    primary->vtable->blt(primary, &rect, board, &rect, 0x1000000, NULL);
    if (dxball_draw_to_primary == 0) secondary->vtable->blt(secondary, &rect, board, &rect, 0x1000000, NULL);
}

/* FUNCTION: 0x0040C3B0 */
void dxball_editor_frame(void)
{
    DxBallInt x, y;
    DxBallRect status_rect;
    if (dxball_draw_to_primary != 0)
        dxball_wait_frames(1);
    dxball_restore_regions();
    dxball_intro_cursor_x = dxball_mouse_x;
    dxball_intro_cursor_y = dxball_mouse_y;
    if (dxball_intro_cursor_x > 599)
        dxball_intro_cursor_x = 599;
    if (dxball_intro_cursor_x < 8)
        dxball_intro_cursor_x = 8;
    if (dxball_intro_cursor_y > 447)
        dxball_intro_cursor_y = 447;
    dxball_select_sprite_bank(2);
    if (dxball_find_hit_region(dxball_intro_cursor_x, dxball_intro_cursor_y) != 0)
        dxball_draw_effect_sprite(6, dxball_intro_cursor_x, dxball_intro_cursor_y);
    else
        dxball_draw_effect_sprite(4, dxball_intro_cursor_x, dxball_intro_cursor_y);
    dxball_select_sprite_bank(0);
    if (dxball_draw_to_primary == 0)
        dxball_present();
    if (dxball_mouse_action == 1) {
        if (dxball_intro_cursor_x > 20 && dxball_intro_cursor_x < 620 &&
            dxball_intro_cursor_y > 50 && dxball_intro_cursor_y < 350) {
            x = dxball_intro_cursor_x;
            y = dxball_intro_cursor_y;
            x -= 20;
            y -= 50;
            x /= 30;
            y /= 15;
            if (x < 0) x = 0;
            if (x > 19) x = 19;
            if (y < 0) y = 0;
            if (y > 19) y = 19;
            dxball_board_tiles[x + y * 20] = (DxBallByte)dxball_editor_selected_tile;
            dxball_draw_board_tile(x, y, 0);
            dxball_store_editor_board(dxball_board_index);
        } else if (dxball_find_hit_region(dxball_intro_cursor_x, dxball_intro_cursor_y) != 0) {
            dxball_editor_selected_tile =
                dxball_find_hit_region(dxball_intro_cursor_x, dxball_intro_cursor_y);
            dxball_draw_editor_status();
            status_rect.left = 0;
            status_rect.top = 0;
            status_rect.right = 639;
            status_rect.bottom = 49;
            dxball_invalidate_region(status_rect);
        }
        if (dxball_control_pressed == 0)
            dxball_mouse_action = 0;
    }
    if (dxball_mouse_action == 2) {
        if (dxball_intro_cursor_x > 20 && dxball_intro_cursor_x < 620 &&
            dxball_intro_cursor_y > 50 && dxball_intro_cursor_y < 350) {
            x = dxball_intro_cursor_x;
            y = dxball_intro_cursor_y;
            x -= 20;
            y -= 50;
            x /= 30;
            y /= 15;
            if (x < 0) x = 0;
            if (x > 19) x = 19;
            if (y < 0) y = 0;
            if (y > 19) y = 19;
            dxball_board_tiles[x + y * 20] = 0;
            dxball_draw_board_tile(x, y, 0);
            dxball_store_editor_board(dxball_board_index);
        }
        if (dxball_control_pressed == 0)
            dxball_mouse_action = 0;
    }
    return;
}
void dxball_editor_key(char key)
{
    switch ((DxBallByte)key) {
    case 8: memset(dxball_board_tiles, 0, DXBALL_BOARD_SIZE); dxball_redraw_mode(); break;
    case 'L':
        dxball_read_board_bank("default.bds"); dxball_board_index = 0;
        dxball_load_editor_board(0); dxball_redraw_mode(); break;
    case 'S': dxball_store_editor_board(dxball_board_index); dxball_write_board_bank("default.bds"); break;
    case 0xBB:
        dxball_store_editor_board(dxball_board_index);
        ++dxball_board_index;
        if (dxball_board_index > 49) dxball_board_index = 49;
        dxball_load_editor_board(dxball_board_index); dxball_redraw_mode(); break;
    case 0xBD:
        dxball_store_editor_board(dxball_board_index);
        --dxball_board_index;
        if (dxball_board_index < 0) dxball_board_index = 0;
        dxball_load_editor_board(dxball_board_index); dxball_redraw_mode(); break;
    default: break;
    }
}
void dxball_dispose_editor(DxBallInt fade)
{
    if (fade != 0) {
        dxball_runtime_ops.palette_transition(1, 6, 0, 255, 0);
        dxball_runtime_ops.clear_surface((DxBallSurface)dxball_primary_surface, 0);
        dxball_runtime_ops.release_sprite_banks(); dxball_runtime_ops.release_sounds();
        dxball_platform_ops.close_music();
    }
}

void dxball_clear_hit_region(DxBallInt index)
{
    dxball_hit_regions[index].left = 0;
    dxball_hit_regions[index].top = 0;
    dxball_hit_regions[index].right = 0;
    dxball_hit_regions[index].bottom = 0;
    dxball_hit_regions[index].active = 0;
    return;
}

/* FUNCTION: DXBALL 0x00402040 */
DxBallInt dxball_hit_region_contains(DxBallInt index, DxBallInt x, DxBallInt y)
{
    if (dxball_hit_regions[index].active != 0) {
        if (dxball_hit_regions[index].left <= x &&
            dxball_hit_regions[index].right >= x &&
            dxball_hit_regions[index].top <= y &&
            dxball_hit_regions[index].bottom >= y) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

/* FUNCTION: DXBALL 0x004020E0 */
void dxball_reset_hit_region_count(void)
{
    dxball_hit_region_count = 0;
    return;
}

/* FUNCTION: DXBALL 0x0040CC20 */
/* Observed empty body; original name, prototype and source ownership unknown. */
void dxball_unclassified_noop_40cc20(void)
{
    return;
}
