#ifndef DXBALL_RUNTIME_DECIMAL_OUTPUT_H
#define DXBALL_RUNTIME_DECIMAL_OUTPUT_H

#include "runtime_decimal.h"

#pragma pack(push, 2)
typedef struct DxBallExtended10 {
    unsigned char bytes[10];
} DxBallExtended10;
typedef struct DxBallDecimalOutput {
    short exponent;
    char sign, length;
    char digits[22];
} DxBallDecimalOutput;
#pragma pack(pop)
typedef char DxBallExtended10MustBe10[(sizeof(DxBallExtended10) == 10) ? 1 : -1];
typedef char DxBallDecimalOutputMustBe26[(sizeof(DxBallDecimalOutput) == 26) ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif

/* precision >= 0 unless fixed-point flag bit 0 is set; output is backed in full. */
int dxball_crt_decimal_output(DxBallExtended10 value, int precision, int flags,
                             DxBallDecimalOutput *output);

#ifdef __cplusplus
}
#endif
#endif
