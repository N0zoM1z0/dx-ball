#ifndef DXBALL_RUNTIME_FP_DISPATCH_H
#define DXBALL_RUNTIME_FP_DISPATCH_H
#include "runtime_fp_exceptions.h"
#include "runtime_fp_decomposition.h"
#include "runtime_lowio.h"

/* Native double alignment with an exact serialized IEEE initialization view. */
typedef union DxBallDoubleConstant {
    struct { unsigned int low, high; } words;
    double value;
} DxBallDoubleConstant;
typedef char DxBallDoubleConstantMustBeEight[sizeof(DxBallDoubleConstant) == 8 ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
extern DxBallDoubleConstant _d_inf, _d_ind, _d_max, _d_min, _d_mzero;
/* Actual remaining physical x87 operations, not emulated replacements. */
int _statfp(void);
int _clrfp(void);
void _set_statfp(unsigned int status);
DXBALL_CRT_IMPORT void DXBALL_CRT_OS_CALL RaiseException(DxBallCrtDword code,
    DxBallCrtDword flags, DxBallCrtDword count, const size_t *arguments);
#ifdef __cplusplus
}
#endif
#endif
