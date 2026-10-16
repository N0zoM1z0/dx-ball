#include "runtime_mantissa_arithmetic.h"

/* FUNCTION: DXBALL 0x0041E5C0 */
int __addl(unsigned int left, unsigned int right, unsigned int *result)
{
    int carry = 0;
    unsigned int sum = left + right;
    if (sum < left || sum < right) carry = 1;
    *result = sum;
    return carry;
}

/* FUNCTION: DXBALL 0x0041E5F0 */
void __add_12(unsigned int *left, const unsigned int *right)
{
    if (__addl(left[0], right[0], &left[0])) {
        if (__addl(left[1], 1, &left[1])) ++left[2];
    }
    if (__addl(left[1], right[1], &left[1])) ++left[2];
    __addl(left[2], right[2], &left[2]);
}

/* FUNCTION: DXBALL 0x0041E660 */
void __shl_12(unsigned int *mantissa)
{
    unsigned int low_carry = mantissa[0] & 0x80000000U;
    unsigned int middle_carry = mantissa[1] & 0x80000000U;
    low_carry >>= 31;
    middle_carry >>= 31;
    mantissa[0] <<= 1;
    mantissa[1] = (mantissa[1] << 1) | low_carry;
    mantissa[2] = (mantissa[2] << 1) | middle_carry;
}

/* FUNCTION: DXBALL 0x0041E6A0 */
void __shr_12(unsigned int *mantissa)
{
    unsigned int high_carry = mantissa[2] & 1U;
    unsigned int middle_carry = mantissa[1] & 1U;
    high_carry <<= 31;
    middle_carry <<= 31;
    mantissa[2] >>= 1;
    mantissa[1] = (mantissa[1] >> 1) | high_carry;
    mantissa[0] = (mantissa[0] >> 1) | middle_carry;
}

/* Digit accumulation uses all three words before publishing the exponent.
   Retain the two-byte alignment of the incoming extended record. */
#pragma pack(push, 2)
#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallMantissa96 {
#else
typedef struct DxBallMantissa96 {
#endif
    unsigned int words[3];
} DxBallMantissa96;
#pragma pack(pop)

/* FUNCTION: DXBALL 0x0041E6E0 */
void __mtold12(const char *digits, int count, DxBallExtended12 *result)
{
    DxBallMantissa96 saved;
    unsigned int *mantissa = (unsigned int *)result;
    unsigned short exponent = 0x404e;
    mantissa[0] = 0;
    mantissa[1] = 0;
    mantissa[2] = 0;
    while (count != 0) {
        unsigned int digit;
        saved = *(const DxBallMantissa96 *)(const void *)result;
        __shl_12(mantissa);
        --count;
        ++digits;
        __shl_12(mantissa);
        __add_12(mantissa, saved.words);
        __shl_12(mantissa);
        digit = (unsigned int)digits[-1];
        saved.words[1] = 0;
        saved.words[2] = 0;
        saved.words[0] = digit;
        __add_12(mantissa, saved.words);
    }
    if (mantissa[2] == 0) {
        unsigned int high;
        do {
            unsigned int middle, low, low_carry;
            exponent -= 16;
            middle = mantissa[1];
            high = middle >> 16;
            low = mantissa[0];
            middle <<= 16;
            mantissa[2] = high;
            low_carry = low >> 16;
            low <<= 16;
            middle |= low_carry;
            mantissa[1] = middle;
            mantissa[0] = low;
        } while (high == 0);
    }
    while ((((unsigned char *)result)[9] & 0x80) == 0) {
        --exponent;
        __shl_12(mantissa);
    }
    result->exponent = exponent;
}
