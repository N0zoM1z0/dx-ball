#ifndef DXBALL_STATE_TYPES_H
#define DXBALL_STATE_TYPES_H

#include <stddef.h>

typedef unsigned char DxBallByte;
typedef signed int DxBallInt;
typedef unsigned int DxBallUInt;
typedef size_t DxBallSurface;
typedef char DxBallIntMustBe32Bits[(sizeof(DxBallInt) == 4) ? 1 : -1];

enum {
    DXBALL_BOARD_COUNT = 50,
    DXBALL_BOARD_WIDTH = 20,
    DXBALL_BOARD_HEIGHT = 20,
    DXBALL_BOARD_SIZE = 400,
    DXBALL_BOARD_BANK_SIZE = 20000
};

#endif
