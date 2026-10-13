#ifndef DXBALL_RUNTIME_FP_EXCEPTIONS_H
#define DXBALL_RUNTIME_FP_EXCEPTIONS_H
#include "runtime_float.h"
#include "runtime_fp_control.h"

#pragma pack(push, 8)
typedef struct DxBallIeeeValue {
    union {
        float fp32;
        double fp64;
        unsigned short fp80[5], bcd80[5];
        unsigned int fp128[4], integer64[2];
        short i16;
        unsigned short u16;
        int i32, compare;
        unsigned int u32;
        char *string;
    } value;
    unsigned int valid : 1;
    unsigned int format : 4;
} DxBallIeeeValue;
typedef union DxBallIeeeFlags {
    /* The producer clears all32 storage bits, then uses the SDK bit view. */
    unsigned int raw;
    struct {
        unsigned int inexact : 1;
        unsigned int underflow : 1;
        unsigned int overflow : 1;
        unsigned int zero_divide : 1;
        unsigned int invalid : 1;
    } bits;
} DxBallIeeeFlags;
typedef struct DxBallIeeeRecord {
    unsigned int rounding : 2;
    unsigned int precision : 3;
    unsigned int operation : 12;
    DxBallIeeeFlags cause, enable, status;
    DxBallIeeeValue operand1, operand2, result;
} DxBallIeeeRecord;
#pragma pack(pop)
typedef char DxBallIeeeRecordMustBe88[sizeof(DxBallIeeeRecord) == 88 ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
extern int _matherr_flag;
double dxball_crt_user_math_error(int error, int operation, double argument1,
                                 double argument2, double result, unsigned int control);
double dxball_crt_handle_single_exception(unsigned int flags, int operation,
                                         double argument, double result, unsigned int control);
double dxball_crt_handle_single_quiet_nan(int operation, double argument, unsigned int control);
/* Genuine remaining physical exception boundaries, with their actual ABI. */
unsigned int _ctrlfp(unsigned int value, unsigned int mask);
int dxball_crt_handle_float_exception(unsigned int flags, double *result, unsigned int control);
void dxball_crt_raise_float_exception(DxBallIeeeRecord *record, unsigned int *control,
                                     unsigned int flags, int operation,
                                     const double *argument, double *result);
#ifdef __cplusplus
}
#endif
#endif
