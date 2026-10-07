#ifndef DXBALL_GEOMETRY_H
#define DXBALL_GEOMETRY_H

#include "boards.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Original integer-center test; arithmetic and abs must not overflow. */
DxBallInt dxball_rectangles_overlap(DxBallInt left_a, DxBallInt top_a,
    DxBallInt right_a, DxBallInt bottom_a, DxBallInt left_b, DxBallInt top_b,
    DxBallInt right_b, DxBallInt bottom_b);

#ifdef __cplusplus
}
#endif
#endif
