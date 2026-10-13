#ifndef DXBALL_RUNTIME_FP_DECOMPOSITION_H
#define DXBALL_RUNTIME_FP_DECOMPOSITION_H
#include "runtime_fp_control.h"
#include "runtime_float.h"
#ifdef __cplusplus
extern "C" {
#endif
double dxball_crt_decompose_double(double value, int *exponent);
int dxball_crt_classify_double(double value);
int dxball_crt_double_integer_type(double value);
/* Actual rounding-mode-dependent x87 boundary. */
double _frnd(double value);
#ifdef __cplusplus
}
#endif
#endif
