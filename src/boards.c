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
    switch (tile) {
    case 0: return 0;
    case 1: return 3;
    case 2: return 4;
    case 3: return 5;
    case 4: return 6;
    case 5: return 7;
    case 6: return 8;
    case 7: return 19;
    case 8: return 9;
    case 9: return 10;
    case 10: return 11;
    case 11: return 12;
    case 12: return 13;
    case 13: return 14;
    case 14: return 15;
    case 15: return 16;
    case 16: return 17;
    case 17: return 18;
    case 18: return 56;
    case 19: return 57;
    case 20: return 58;
    case 21: return 59;
    case 22: return 60;
    }
    /* Deliberate host safety policy outside the target's defined return domain.
       Never count this source as a full-domain or byte-exact reconstruction. */
    abort();
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
