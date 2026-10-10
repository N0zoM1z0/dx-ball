#include "boards.h"
#include "display.h"

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
   Dependency calls cross the host bridge; DirectDraw and sprite drawing are
   still pending. Unsupported tile bytes perform no drawing but may invalidate. */
void dxball_draw_board_tile(DxBallInt x, DxBallInt y, DxBallInt defer_update)
{
    DxBallRect rect;
    DxBallByte tile = dxball_board_tiles[x + y * DXBALL_BOARD_WIDTH];
    rect.left = x * 30 + 20;
    rect.top = y * 15 + 50;
    rect.right = rect.left + 30;
    rect.bottom = rect.top + 15;

    if (tile == 0 || (tile == 7 && dxball_display_mode == 1)) {
        dxball_render_ops.restore(dxball_active_surface, rect.left, rect.top,
                                  (DxBallSurface)dxball_background_surface, &rect, 0x10);
    } else if (tile <= 22) {
        dxball_render_ops.sprite(dxball_board_tile_sprite(tile), rect.left, rect.top);
    }
    if (defer_update == 0) {
        dxball_render_ops.invalidate(rect);
    }
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
