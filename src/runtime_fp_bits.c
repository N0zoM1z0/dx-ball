#include "runtime_fp_control.h"

#pragma pack(push, 1)
#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallFpDoubleParts {
#else
typedef struct DxBallFpDoubleParts {
#endif
    unsigned int low, high;
} DxBallFpDoubleParts;
#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallFpDoubleWords {
#else
typedef struct DxBallFpDoubleWords {
#endif
    unsigned short words[4];
} DxBallFpDoubleWords;
#pragma pack(pop)
typedef char DxBallFpDoubleMustBeEightBytes[sizeof(double) == 8 ? 1 : -1];
typedef union DxBallFpDoubleWork {
    double value;
    DxBallFpDoubleParts parts;
    unsigned short words[4];
} DxBallFpDoubleWork;

double dxball_crt_set_float_exponent(double value, int exponent)
{
    DxBallFpDoubleWork result;
    const DxBallFpDoubleParts *parts = (const DxBallFpDoubleParts *)(const void *)&value;
    const DxBallFpDoubleWords *input = (const DxBallFpDoubleWords *)(const void *)&value;
    unsigned short biased;
    /* Capture the complete representation without a floating load/conversion. */
    result.parts = *parts;
    /* The argument occupies a full int slot; only its wrapped biased low word
       reaches the serialized exponent field. */
    biased = (unsigned short)((unsigned int)exponent + 0x3feU);
    result.words[3] = (unsigned short)((biased << 4) | (input->words[3] & 0x800f));
    return result.value;
}

int dxball_crt_float_special_type(double value)
{
    const DxBallFpDoubleParts *parts = (const DxBallFpDoubleParts *)(const void *)&value;
    const DxBallFpDoubleWords *words = (const DxBallFpDoubleWords *)(const void *)&value;
    unsigned short exponent;
    if (parts->high == 0x7ff00000U && parts->low == 0) return 1;
    if (parts->high == 0xfff00000U && parts->low == 0) return 2;
    exponent = words->words[3] & 0x7ff8;
    if (exponent == 0x7ff8) return 3;
    if (exponent == 0x7ff0 && ((parts->high & 0x7ffffU) || parts->low)) return 4;
    return 0;
}
