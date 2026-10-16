#ifndef DXBALL_RUNTIME_X87_DISPATCH_CONSTANTS_H
#define DXBALL_RUNTIME_X87_DISPATCH_CONSTANTS_H

#include "runtime_fp_dispatch.h"
#include <stddef.h>

/* Complete readonly 87cdisp.obj record. FSCALE consumes the adjustment values
   as binary64 exponents; the remaining fields bound or replace its result. */
typedef struct DxBallX87DispatchConstants {
    DxBallDoubleConstant maximum_finite;
    DxBallDoubleConstant minimum_normal;
    DxBallDoubleConstant overflow_exponent;
    DxBallDoubleConstant underflow_exponent;
    DxBallDoubleConstant infinity;
    DxBallDoubleConstant zero;
} DxBallX87DispatchConstants;

typedef char DxBallX87DispatchConstantsMustBe48[
    sizeof(DxBallX87DispatchConstants) == 48 ? 1 : -1];
typedef char DxBallX87DispatchConstantsOffsets[
    offsetof(DxBallX87DispatchConstants, minimum_normal) == 8 &&
    offsetof(DxBallX87DispatchConstants, overflow_exponent) == 16 &&
    offsetof(DxBallX87DispatchConstants, underflow_exponent) == 24 &&
    offsetof(DxBallX87DispatchConstants, infinity) == 32 &&
    offsetof(DxBallX87DispatchConstants, zero) == 40 ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
extern const DxBallX87DispatchConstants dxball_x87_dispatch_constants;
#ifdef __cplusplus
}
#endif

#endif
