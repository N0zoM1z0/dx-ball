#include "geometry.h"

#include <stdlib.h>
#include <math.h>

DxBallInt dxball_rectangles_overlap(DxBallInt left_a, DxBallInt top_a,
    DxBallInt right_a, DxBallInt bottom_a, DxBallInt left_b, DxBallInt top_b,
    DxBallInt right_b, DxBallInt bottom_b)
{
    DxBallInt width_a, height_a, width_b, height_b, distance_x, distance_y;
    width_a = right_a - left_a;
    height_a = bottom_a - top_a;
    width_b = right_b - left_b;
    height_b = bottom_b - top_b;
    distance_x = abs(left_a + width_a / 2 - (left_b + width_b / 2));
    distance_y = abs(top_a + height_a / 2 - (top_b + height_b / 2));
    if (distance_x <= (width_a + width_b) / 2 &&
            distance_y <= (height_a + height_b) / 2) {
        return 1;
    }
    return distance_x < width_a / 2 && distance_y < height_a / 2;
}

/* FUNCTION: DXBALL 0x004025A0 */
float dxball_point_angle(DxBallInt x1, DxBallInt y1, DxBallInt x2, DxBallInt y2)
{
    float angle;
    angle = (float)atan2((double)(y2 - y1), (double)(x2 - x1));
    angle = (float)(angle * 180.0 / 3.1415927);
    return angle;
}

/* FUNCTION: DXBALL 0x00402610 */
DxBallInt dxball_point_distance(DxBallInt x1, DxBallInt y1,
                              DxBallInt x2, DxBallInt y2)
{
    double dx, dy, squared_distance, distance;
    dx = fabs((double)x1 - x2);
    dy = fabs((double)y1 - y2);
    squared_distance = dx * dx + dy * dy;
    distance = sqrt(squared_distance);
    return (DxBallInt)distance;
}
