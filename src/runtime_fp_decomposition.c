#include "runtime_fp_decomposition.h"

#pragma pack(push, 1)
#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallDecompositionParts {
#else
typedef struct DxBallDecompositionParts {
#endif
    unsigned int low, high;
} DxBallDecompositionParts;
#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallDecompositionWords {
#else
typedef struct DxBallDecompositionWords {
#endif
    unsigned short words[4];
} DxBallDecompositionWords;
#pragma pack(pop)

double dxball_crt_decompose_double(double value, int *exponent)
{
    DxBallDecompositionParts *parts = (DxBallDecompositionParts *)(void *)&value;
    DxBallDecompositionWords *words = (DxBallDecompositionWords *)(void *)&value;
    unsigned char *bytes = (unsigned char *)&value;
    /* Each path materializes a binary64 result before the shared return. */
    volatile double fraction;
    int scale, negative;
    unsigned short biased;
    if (((parts->high & 0x7fffffffU) | parts->low) == 0) {
        scale = 0;
        fraction = 0.0;
    } else {
        biased = words->words[3] & 0x7ff0;
        if (biased == 0 && ((parts->high & 0xfffffU) || parts->low)) {
            scale = -1021;
            negative = value < 0.0;
            while (!(words->words[3] & 0x10)) {
                parts->high <<= 1;
                if (parts->low & 0x80000000U)
                    parts->high |= 1;
                --scale;
                parts->low <<= 1;
            }
            words->words[3] &= 0xffef;
            if (negative)
                bytes[7] |= 0x80;
            fraction = dxball_crt_set_float_exponent(value, 0);
        } else {
            fraction = dxball_crt_set_float_exponent(value, 0);
            biased >>= 4;
            scale = (short)biased - 1022;
        }
    }
    *exponent = scale;
    return fraction;
}

int dxball_crt_classify_double(double value)
{
    const DxBallDecompositionParts *parts = (const DxBallDecompositionParts *)(const void *)&value;
    const DxBallDecompositionWords *words = (const DxBallDecompositionWords *)(const void *)&value;
    unsigned short biased = words->words[3] & 0x7ff0;
    unsigned int sign;
    if (biased == 0x7ff0) {
        switch (dxball_crt_float_special_type(value)) {
        case 1: return 0x200;
        case 2: return 4;
        case 3: return 2;
        default: return 1;
        }
    }
    sign = words->words[3] & 0x8000;
    if (((parts->high & 0x7fffffffU) | parts->low) == 0)
        return sign ? 0x20 : 0x40;
    if (biased == 0 && ((parts->high & 0xfffffU) || parts->low))
        return sign ? 0x10 : 0x80;
    return sign ? 8 : 0x100;
}

int dxball_crt_double_integer_type(double value)
{
    unsigned int classification = dxball_crt_classify_double(value);
    double half;
    if (classification & 0x90)
        return 0;
    /* The shipped x87 C3 tests accept unordered equality too. Retain both
       actual rounding calls on NaNs rather than silently changing that path. */
    if (_frnd(value) == value || (classification & 3)) {
        half = value * 0.5;
        if (_frnd(half) == half || (classification & 3))
            return 2;
        return 1;
    }
    return 0;
}
