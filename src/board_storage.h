#ifndef DXBALL_BOARD_STORAGE_H
#define DXBALL_BOARD_STORAGE_H

#include "explosion_types.h"

/* Recovered writable region 0x43AAB8..0x43FA87, not an original source type.
 * The terminal copy reads the peer globals and all twelve unclassified bytes,
 * including the explosion owner's constructor-cleared +0xC word.
 * Preserve those bytes as mutable state; the remaining clock/count tails have no
 * established writer/type or padding authority. Native pointer widths retain the host analysis ABI. */
typedef struct DxBallBoardStorage {
    DxBallByte bank[DXBALL_BOARD_COUNT][DXBALL_BOARD_SIZE];
    DxBallUInt palette_tick;
    DxBallByte unclassified_clock_tail[4];
    DxBallExplosionList explosions;
    DxBallInt ball_count;
    DxBallByte unclassified_count_tail[4];
    DxBallByte tiles[DXBALL_BOARD_SIZE];
} DxBallBoardStorage;

typedef char DxBallBoardStorageX86Contract[
    sizeof(void *) != 4 ||
    (offsetof(DxBallBoardStorage, palette_tick) == 20000 &&
     offsetof(DxBallBoardStorage, explosions) == 20008 &&
     offsetof(DxBallBoardStorage, ball_count) == 20024 &&
     offsetof(DxBallBoardStorage, tiles) == 20032 &&
     sizeof(DxBallBoardStorage) == 20432) ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
extern DxBallBoardStorage dxball_board_storage;
/* Read-only analysis metadata: bank, clock, requests, count, tiles, total size.
 * Values come from this compiler's offsetof/sizeof, not profile literals. */
extern const DxBallUInt dxball_board_storage_offsets[6];
#ifdef __cplusplus
}
#endif

#define dxball_board_bank (dxball_board_storage.bank)
#define dxball_palette_tick (dxball_board_storage.palette_tick)
#define dxball_explosions (dxball_board_storage.explosions)
#define dxball_ball_count (dxball_board_storage.ball_count)
#define dxball_board_tiles (dxball_board_storage.tiles)

#endif
