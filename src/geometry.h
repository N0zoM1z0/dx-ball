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

/* Angle uses signed differences, the observed 3.1415927 divisor and float
   stores. Distance returns a truncated int; require representable arithmetic. */
float dxball_point_angle(DxBallInt x1, DxBallInt y1, DxBallInt x2, DxBallInt y2);
DxBallInt dxball_point_distance(DxBallInt x1, DxBallInt y1,
                              DxBallInt x2, DxBallInt y2);

#ifdef __cplusplus
}
#endif
#endif
