#ifndef DXBALL_BOARDS_H
#define DXBALL_BOARDS_H

#include <stddef.h>
#include <stdio.h>
#include "board_storage.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DxBallRect {
    DxBallInt left, top, right, bottom;
} DxBallRect;

/* Host bridge for dependencies whose original implementations are still pending.
   Surface handles are opaque; the original executable uses 32-bit COM pointers. */
typedef struct DxBallRenderOps {
    void (*sprite)(DxBallInt sprite, DxBallInt x, DxBallInt y);
    void (*restore)(DxBallSurface destination, DxBallInt x, DxBallInt y,
                    DxBallSurface source, const DxBallRect *rect, DxBallUInt flags);
    void (*invalidate)(DxBallRect rect);
} DxBallRenderOps;

/* Explosion-animation occupancy: set on spawn and cleared on final cleanup. */
extern DxBallByte dxball_board_aux[DXBALL_BOARD_SIZE];
extern DxBallInt dxball_board_index;
extern DxBallInt dxball_display_mode;
extern FILE *dxball_board_file;
extern DxBallSurface dxball_active_surface;
struct DxBallDDSurface;
extern struct DxBallDDSurface *dxball_board_surface;
extern struct DxBallDDSurface *dxball_background_surface;
extern DxBallRenderOps dxball_render_ops;

/* Board index precondition: 0 <= board < 50. The original has no bounds checks. */
void dxball_read_board_bank(const char *path);
void dxball_write_board_bank(const char *path);
void dxball_load_editor_board(DxBallInt board);
void dxball_store_editor_board(DxBallInt board);
void dxball_initialize_board(void);

/* The target's return is uninitialized outside 0..22. This maintained source
   terminates there; semantic acceptance is explicitly restricted to 0..22. */
DxBallInt dxball_board_tile_sprite(DxBallInt tile);
void dxball_select_surface(DxBallSurface surface);
/* x/y precondition: 0..19. Nonzero defer_update suppresses invalidation. */
void dxball_draw_board_tile(DxBallInt x, DxBallInt y, DxBallInt defer_update);
void dxball_draw_board(DxBallInt defer_update);

#ifdef __cplusplus
}
#endif
#endif
