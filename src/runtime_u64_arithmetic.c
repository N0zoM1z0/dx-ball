#include "runtime_u64_arithmetic.h"

/* Win32 and the supported native hosts use little-endian 32-bit limbs. */
typedef union DxBallU64Words {
    DxBallCrtUInt64 value;
    struct { DxBallUInt low, high; } words;
} DxBallU64Words;

/* FUNCTION: DXBALL 0x0041FE00 */
DxBallCrtUInt64 DXBALL_U64_CALL dxball_crt_u64_divide(
    DxBallCrtUInt64 dividend, DxBallCrtUInt64 divisor)
{
    DxBallU64Words numerator, denominator, quotient, remainder;
    DxBallUInt carry, bit, borrow;
    int remaining;

    numerator.value = dividend;
    denominator.value = divisor;
    quotient.words.low = quotient.words.high = 0;
    remainder.words.low = remainder.words.high = 0;

    if (denominator.words.high == 0) {
        quotient.words.high = numerator.words.high / denominator.words.low;
        remainder.words.low = numerator.words.high % denominator.words.low;
        for (remaining = 32; remaining != 0; --remaining) {
            carry = remainder.words.low >> 31;
            remainder.words.low = (remainder.words.low << 1) | (numerator.words.low >> 31);
            numerator.words.low <<= 1;
            quotient.words.low <<= 1;
            if (carry || remainder.words.low >= denominator.words.low) {
                remainder.words.low -= denominator.words.low;
                quotient.words.low |= 1;
            }
        }
    } else {
        for (remaining = 64; remaining != 0; --remaining) {
            bit = numerator.words.high >> 31;
            numerator.words.high = (numerator.words.high << 1) | (numerator.words.low >> 31);
            numerator.words.low <<= 1;
            carry = remainder.words.high >> 31;
            remainder.words.high = (remainder.words.high << 1) | (remainder.words.low >> 31);
            remainder.words.low = (remainder.words.low << 1) | bit;
            quotient.words.low <<= 1;
            if (carry || remainder.words.high > denominator.words.high ||
                    (remainder.words.high == denominator.words.high &&
                     remainder.words.low >= denominator.words.low)) {
                borrow = remainder.words.low < denominator.words.low;
                remainder.words.low -= denominator.words.low;
                remainder.words.high -= denominator.words.high + borrow;
                quotient.words.low |= 1;
            }
        }
    }
    return quotient.value;
}

/* FUNCTION: DXBALL 0x0041FE70 */
DxBallCrtUInt64 DXBALL_U64_CALL dxball_crt_u64_remainder(
    DxBallCrtUInt64 dividend, DxBallCrtUInt64 divisor)
{
    DxBallU64Words numerator, denominator, remainder;
    DxBallUInt carry, bit, borrow;
    int remaining;

    numerator.value = dividend;
    denominator.value = divisor;
    remainder.words.low = remainder.words.high = 0;

    if (denominator.words.high == 0) {
        remainder.words.low = numerator.words.high % denominator.words.low;
        for (remaining = 32; remaining != 0; --remaining) {
            carry = remainder.words.low >> 31;
            remainder.words.low = (remainder.words.low << 1) | (numerator.words.low >> 31);
            numerator.words.low <<= 1;
            if (carry || remainder.words.low >= denominator.words.low)
                remainder.words.low -= denominator.words.low;
        }
    } else {
        for (remaining = 64; remaining != 0; --remaining) {
            bit = numerator.words.high >> 31;
            numerator.words.high = (numerator.words.high << 1) | (numerator.words.low >> 31);
            numerator.words.low <<= 1;
            carry = remainder.words.high >> 31;
            remainder.words.high = (remainder.words.high << 1) | (remainder.words.low >> 31);
            remainder.words.low = (remainder.words.low << 1) | bit;
            if (carry || remainder.words.high > denominator.words.high ||
                    (remainder.words.high == denominator.words.high &&
                     remainder.words.low >= denominator.words.low)) {
                borrow = remainder.words.low < denominator.words.low;
                remainder.words.low -= denominator.words.low;
                remainder.words.high -= denominator.words.high + borrow;
            }
        }
    }
    return remainder.value;
}
