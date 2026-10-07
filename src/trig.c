#include "trig.h"
#include <math.h>

DxBallInt dxball_sine_table[361], dxball_cosine_table[361];

void dxball_initialize_trig(void)
{
    DxBallInt angle;
    double radians;
    for (angle = 0; angle <= 360; ++angle) {
        radians = (double)((long double)angle * 3.14159 / 180.0);
        dxball_cosine_table[angle] = (DxBallInt)(cos(radians) * 1024.0);
        dxball_sine_table[angle] = (DxBallInt)(sin(radians) * 1024.0);
    }
    return;
}

float dxball_sine(DxBallInt angle)
{
    if (angle < 0) angle = 360 - (-angle) % 360;
    else angle %= 360;
    return (float)((double)dxball_sine_table[angle] / 1024.0);
}

float dxball_cosine(DxBallInt angle)
{
    if (angle < 0) angle = 360 - (-angle) % 360;
    else angle %= 360;
    return (float)((double)dxball_cosine_table[angle] / 1024.0);
}
