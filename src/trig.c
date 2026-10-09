#include "trig.h"
#include <math.h>

DxBallInt dxball_sine_table[361], dxball_cosine_table[361];

void dxball_initialize_trig(void)
{
    DxBallInt angle;
    double cosine_value, sine_value;
    for (angle = 0; angle <= 360; ++angle) {
        cosine_value = cos((double)((long double)angle * 3.14159 / 180.0));
        sine_value = sin((double)((long double)angle * 3.14159 / 180.0));
        dxball_cosine_table[angle] = (DxBallInt)(cosine_value * 1024.0);
        dxball_sine_table[angle] = (DxBallInt)(sine_value * 1024.0);
    }
    return;
}

float dxball_sine(DxBallInt angle)
{
    float result;
    if (angle < 0) angle = 360 - (-angle) % 360;
    else angle %= 360;
    angle = dxball_sine_table[angle];
    result = (float)((double)angle / 1024.0);
    return result;
}

float dxball_cosine(DxBallInt angle)
{
    float result;
    if (angle < 0) angle = 360 - (-angle) % 360;
    else angle %= 360;
    angle = dxball_cosine_table[angle];
    result = (float)((double)angle / 1024.0);
    return result;
}
