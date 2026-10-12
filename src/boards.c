#include "boards.h"
#include "display.h"
#include "resources.h"

#include <stdlib.h>
#include <string.h>

const DxBallUInt dxball_board_storage_offsets[6] = {
    offsetof(DxBallBoardStorage, bank), offsetof(DxBallBoardStorage, palette_tick),
    offsetof(DxBallBoardStorage, explosions), offsetof(DxBallBoardStorage, ball_count),
    offsetof(DxBallBoardStorage, tiles), sizeof(DxBallBoardStorage)
};
DxBallByte dxball_board_aux[DXBALL_BOARD_SIZE];
DxBallInt dxball_board_index;
DxBallInt dxball_display_mode;
FILE *dxball_board_file;
DxBallSurface dxball_active_surface;
struct DxBallDDSurface *dxball_board_surface;
struct DxBallDDSurface *dxball_background_surface;
DxBallRenderOps dxball_render_ops = { dxball_draw_sprite, dxball_restore_board_region, dxball_invalidate_region };

/* FUNCTION: DXBALL 0x0040CC30
   Failed opens preserve the bank. Short reads replace only the prefix. The
   original ignores the transfer result and keeps the closed FILE pointer. */
void dxball_read_board_bank(const char *path)
{
    dxball_board_file = fopen(path, "rb");
    if (dxball_board_file == NULL)
        return;
    fread(dxball_board_bank, 1, DXBALL_BOARD_BANK_SIZE, dxball_board_file);
    fclose(dxball_board_file);
    return;
}

/* FUNCTION: DXBALL 0x0040CC90 */
void dxball_write_board_bank(const char *path)
{
    dxball_board_file = fopen(path, "wb");
    if (dxball_board_file == NULL)
        return;
    fwrite(dxball_board_bank, 1, DXBALL_BOARD_BANK_SIZE, dxball_board_file);
    fclose(dxball_board_file);
    return;
}

/* FUNCTION: DXBALL 0x0040CEA0 */
void dxball_load_editor_board(DxBallInt board)
{
    memmove(dxball_board_tiles, (const DxBallByte *)&dxball_board_storage
            + board * DXBALL_BOARD_SIZE, DXBALL_BOARD_SIZE);
    return;
}

/* FUNCTION: DXBALL 0x0040CEE0 */
void dxball_store_editor_board(DxBallInt board)
{
    memmove((DxBallByte *)&dxball_board_storage + board * DXBALL_BOARD_SIZE,
            dxball_board_tiles, DXBALL_BOARD_SIZE);
    return;
}

/* FUNCTION: DXBALL 0x00411930 */
void dxball_initialize_board(void)
{
    memset(dxball_board_aux, 0, DXBALL_BOARD_SIZE);
    dxball_load_editor_board(dxball_board_index);
    return;
}

/* FUNCTION: DXBALL 0x0040CCF0
   Cases are independently corroborated by the board renderer and the editor's
   1..22 palette producer. Colors/bonus meanings have not been established. */
DxBallInt dxball_board_tile_sprite(DxBallInt tile)
{
    DxBallInt sprite;
    switch (tile) {
    case 0: sprite = 0; break;
    case 1: sprite = 3; break;
    case 2: sprite = 4; break;
    case 3: sprite = 5; break;
    case 4: sprite = 6; break;
    case 5: sprite = 7; break;
    case 6: sprite = 8; break;
    case 7: sprite = 19; break;
    case 8: sprite = 9; break;
    case 9: sprite = 10; break;
    case 10: sprite = 11; break;
    case 11: sprite = 12; break;
    case 12: sprite = 13; break;
    case 13: sprite = 14; break;
    case 14: sprite = 15; break;
    case 15: sprite = 16; break;
    case 16: sprite = 17; break;
    case 17: sprite = 18; break;
    case 18: sprite = 56; break;
    case 19: sprite = 57; break;
    case 20: sprite = 58; break;
    case 21: sprite = 59; break;
    case 22: sprite = 60; break;
    }
    /* Unsupported tiles read the uninitialized result in the original.
       Game/editor producers supply tile values 0..22. */
    return sprite;
}

/* FUNCTION: DXBALL 0x00403E50 */
void dxball_select_surface(DxBallSurface surface)
{
    dxball_active_surface = surface;
    return;
}

/* FUNCTION: DXBALL 0x004119F0
   Unsupported signed tile bytes skip drawing but retain invalidation. */
void dxball_draw_board_tile(DxBallInt x, DxBallInt y, DxBallInt defer_update)
{
    DxBallRect rect;
    DxBallInt tile = (char)dxball_board_tiles[x + y * DXBALL_BOARD_WIDTH];
    rect.left = x * 30 + 20;
    rect.top = y * 15 + 50;
    rect.right = x * 30 + 50;
    rect.bottom = y * 15 + 65;
    switch (tile) {
    case 0:
        ((DxBallDDSurface *)dxball_active_surface)->vtable->blt_fast(
            (DxBallDDSurface *)dxball_active_surface, x * 30 + 20, y * 15 + 50,
            (DxBallDDSurface *)dxball_background_surface, &rect, 0x10);
        break;
    case 1: dxball_draw_sprite(3, x * 30 + 20, y * 15 + 50); break;
    case 2: dxball_draw_sprite(4, x * 30 + 20, y * 15 + 50); break;
    case 3: dxball_draw_sprite(5, x * 30 + 20, y * 15 + 50); break;
    case 4: dxball_draw_sprite(6, x * 30 + 20, y * 15 + 50); break;
    case 5: dxball_draw_sprite(7, x * 30 + 20, y * 15 + 50); break;
    case 6: dxball_draw_sprite(8, x * 30 + 20, y * 15 + 50); break;
    case 7:
        if (dxball_display_mode == 1) {
            ((DxBallDDSurface *)dxball_active_surface)->vtable->blt_fast(
            (DxBallDDSurface *)dxball_active_surface, x * 30 + 20, y * 15 + 50,
            (DxBallDDSurface *)dxball_background_surface, &rect, 0x10);
        } else {
            dxball_draw_sprite(19, x * 30 + 20, y * 15 + 50);
        }
        break;
    case 8: dxball_draw_sprite(9, x * 30 + 20, y * 15 + 50); break;
    case 9: dxball_draw_sprite(10, x * 30 + 20, y * 15 + 50); break;
    case 10: dxball_draw_sprite(11, x * 30 + 20, y * 15 + 50); break;
    case 11: dxball_draw_sprite(12, x * 30 + 20, y * 15 + 50); break;
    case 12: dxball_draw_sprite(13, x * 30 + 20, y * 15 + 50); break;
    case 13: dxball_draw_sprite(14, x * 30 + 20, y * 15 + 50); break;
    case 14: dxball_draw_sprite(15, x * 30 + 20, y * 15 + 50); break;
    case 15: dxball_draw_sprite(16, x * 30 + 20, y * 15 + 50); break;
    case 16: dxball_draw_sprite(17, x * 30 + 20, y * 15 + 50); break;
    case 17: dxball_draw_sprite(18, x * 30 + 20, y * 15 + 50); break;
    case 18: dxball_draw_sprite(56, x * 30 + 20, y * 15 + 50); break;
    case 19: dxball_draw_sprite(57, x * 30 + 20, y * 15 + 50); break;
    case 20: dxball_draw_sprite(58, x * 30 + 20, y * 15 + 50); break;
    case 21: dxball_draw_sprite(59, x * 30 + 20, y * 15 + 50); break;
    case 22: dxball_draw_sprite(60, x * 30 + 20, y * 15 + 50); break;
    }
    if (defer_update == 0) dxball_invalidate_region(rect);
    return;
}

/* FUNCTION: DXBALL 0x00411970
   Traversal order is x-major even though board storage is row-major. */
void dxball_draw_board(DxBallInt defer_update)
{
    DxBallInt x, y;
    dxball_select_surface((DxBallSurface)dxball_board_surface);
    for (x = 0; x < DXBALL_BOARD_WIDTH; ++x) {
        for (y = 0; y < DXBALL_BOARD_HEIGHT; ++y) {
            dxball_draw_board_tile(x, y, defer_update);
        }
    }
    return;
}
