#ifndef DXBALL_TRIG_H
#define DXBALL_TRIG_H
#include "boards.h"

extern DxBallInt dxball_sine_table[361], dxball_cosine_table[361];
void dxball_initialize_trig(void);
/* Negative multiples of 360 address the separately initialized endpoint. */
float dxball_sine(DxBallInt angle);
float dxball_cosine(DxBallInt angle);
#endif
