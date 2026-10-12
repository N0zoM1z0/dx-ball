#include "geometry.h"

#include <stdlib.h>
#include <math.h>

/* FUNCTION: DXBALL 0x00402100 */
DxBallInt dxball_rectangles_overlap(DxBallInt left_a, DxBallInt top_a,
    DxBallInt right_a, DxBallInt bottom_a, DxBallInt left_b, DxBallInt top_b,
    DxBallInt right_b, DxBallInt bottom_b)
{
    DxBallInt width_b;
    {
        struct {
            DxBallInt height_b;
            struct { DxBallInt width_a, distance_y, height_a, distance_x; } primary;
        } overlap;
        overlap.primary.width_a = right_a - left_a;
        overlap.primary.height_a = bottom_a - top_a;
        width_b = right_b - left_b;
        overlap.height_b = bottom_b - top_b;
        overlap.primary.distance_x = abs(left_a + overlap.primary.width_a / 2 - (left_b + width_b / 2));
        overlap.primary.distance_y = abs(top_a + overlap.primary.height_a / 2 - (top_b + overlap.height_b / 2));
        if ((overlap.primary.width_a + width_b) / 2 >= overlap.primary.distance_x &&
                (overlap.primary.height_a + overlap.height_b) / 2 >= overlap.primary.distance_y) {
            return 1;
        } else {
            if (abs(left_a + overlap.primary.width_a / 2 - (left_b + width_b / 2)) < overlap.primary.width_a / 2 &&
                    abs(top_a + overlap.primary.height_a / 2 - (top_b + overlap.height_b / 2)) < overlap.primary.height_a / 2) {
                return 1;
            } else {
                return 0;
            }
        }
    }
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
    struct { double distance, squared_distance, dy, dx; } measurement;
    measurement.dx = fabs((double)x1 - x2);
    measurement.dy = fabs((double)y1 - y2);
    measurement.squared_distance = measurement.dx * measurement.dx + measurement.dy * measurement.dy;
    measurement.distance = sqrt(measurement.squared_distance);
    return (DxBallInt)measurement.distance;
}
