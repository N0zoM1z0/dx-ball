#ifndef DXBALL_EXPLOSION_TYPES_H
#define DXBALL_EXPLOSION_TYPES_H

#include "state_types.h"

/* The target has three 32-bit payload fields, followed by two pointers. */
typedef struct DxBallExplosionNode {
    DxBallInt kind, x, y;
    struct DxBallExplosionNode *next, *previous;
} DxBallExplosionNode;

typedef struct DxBallExplosionList {
    DxBallExplosionNode *current, *first, *last;
} DxBallExplosionList;

#endif
