#ifndef DXBALL_RUNTIME_FLOAT_RENDER_H
#define DXBALL_RUNTIME_FLOAT_RENDER_H
#include "runtime_float_format.h"
#include "runtime_decimal_output.h"

#ifdef __cplusplus
extern "C" {
#endif
void dxball_crt_format_general_exponent(const double *, char *, int, int);
void dxball_crt_format_general_fixed(const double *, char *, int);
void dxball_crt_shift_float_text(char *, int);
DxBallCrtFloatText *dxball_crt_float_output(double value);
void dxball_crt_double_to_extended(DxBallExtended10 *output, const double *value);
#ifdef __cplusplus
}
#endif
#endif
