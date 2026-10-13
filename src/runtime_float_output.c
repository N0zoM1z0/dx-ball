#include "runtime_float_render.h"

static DxBallDecimalOutput float_output;
static DxBallCrtFloatText float_text;

#pragma pack(push, 1)
#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallDoubleParts {
#else
typedef struct DxBallDoubleParts {
#endif
    unsigned int low, high;
} DxBallDoubleParts;
#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallOutputExtendedParts {
#else
typedef struct DxBallOutputExtendedParts {
#endif
    unsigned int low, high;
    unsigned short exponent;
} DxBallOutputExtendedParts;
#pragma pack(pop)

#if defined(__GNUC__)
typedef unsigned short DxBallDoubleHighWord __attribute__((__may_alias__));
#else
typedef unsigned short DxBallDoubleHighWord;
#endif

DxBallCrtFloatText *dxball_crt_float_output(double value)
{
    DxBallExtended10 extended;
    dxball_crt_double_to_extended(&extended, &value);
    float_text.flags = dxball_crt_decimal_output(extended, 17, 0, &float_output);
    float_text.mantissa = float_output.digits;
    float_text.sign = float_output.sign;
    float_text.decimal_position = float_output.exponent;
    return &float_text;
}

void dxball_crt_double_to_extended(DxBallExtended10 *output, const double *value)
{
    const DxBallDoubleParts *input = (const DxBallDoubleParts *)(const void *)value;
    DxBallOutputExtendedParts *result = (DxBallOutputExtendedParts *)(void *)output;
    const DxBallDoubleHighWord *top = (const DxBallDoubleHighWord *)
        (const void *)((const unsigned char *)value + 6);
    unsigned short sign = *top;
    unsigned short exponent = (sign & 0x7ff0) >> 4;
    unsigned int integer_bit = 0x80000000U;
    unsigned int high = input->high & 0xfffffU;
    unsigned int low = input->low;
    sign &= 0x8000;
    switch (exponent) {
    case 0:
        if (high == 0 && low == 0) {
            /* The shipped conversion discards the sign of either zero. */
            result->exponent = 0;
            result->high = 0;
            result->low = 0;
            return;
        }
        exponent += 0x3c01;
        integer_bit = 0;
        break;
    case 0x7ff:
        exponent = 0x7fff;
        break;
    default:
        exponent += 0x3c00;
        break;
    }
    result->low = low << 11;
    result->high = (low >> 21) | (high << 11) | integer_bit;
    while (!(result->high & 0x80000000U)) {
        --exponent;
        low = result->low;
        high = result->high;
        result->low = low << 1;
        result->high = (low >> 31) | (high << 1);
    }
    result->exponent = exponent | sign;
}
