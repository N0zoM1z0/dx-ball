#include "termination.h"
#include "runtime_stdio_finalization.h"
#include <stddef.h>

/* The observed half-open ranges contain two preterminators and one terminator. */
DxBallCrtCallback dxball_preterminators[2] = { NULL, dxball_crt_end_stdio };
DxBallCrtCallback dxball_terminators[1] = { NULL };
