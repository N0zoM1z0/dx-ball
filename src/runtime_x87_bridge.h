#ifndef DXBALL_RUNTIME_X87_BRIDGE_H
#define DXBALL_RUNTIME_X87_BRIDGE_H
#include "runtime_fp_dispatch.h"

#ifdef __cplusplus
extern "C" {
#endif
void dxball_crt_x87_exception_bridge(int operation, DxBallMathException *exception,
    const unsigned short *control_word);
#ifdef __cplusplus
}
#endif
#endif
