#include "runtime_decimal_output.h"
#include <string.h>

typedef union DxBallDecimalWork {
    DxBallExtended12 extended;
    unsigned int words[3];
    unsigned char bytes[12];
} DxBallDecimalWork;

#pragma pack(push, 1)
/* An alias-safe view of the serialized 80-bit argument, not a native long double. */
#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallExtended10Parts {
#else
typedef struct DxBallExtended10Parts {
#endif
    unsigned int low, high;
    unsigned short exponent;
} DxBallExtended10Parts;
#pragma pack(pop)

int dxball_crt_decimal_output(DxBallExtended10 value, int precision, int flags,
                             DxBallDecimalOutput *output)
{
    const DxBallExtended10Parts *parts = (const DxBallExtended10Parts *)(const void *)&value;
    DxBallDecimalWork fraction, tenth, saved;
    int result;
    unsigned short exponent, sign;
    short decimal_exponent;
    int shift, count;
    char *cursor, *first;

    tenth.bytes[0] = 0xcc;
    tenth.bytes[1] = 0xcc;
    tenth.bytes[2] = 0xcc;
    tenth.bytes[3] = 0xcc;
    tenth.bytes[4] = 0xcc;
    tenth.bytes[5] = 0xcc;
    tenth.bytes[6] = 0xcc;
    tenth.bytes[7] = 0xcc;
    tenth.bytes[8] = 0xcc;
    tenth.bytes[9] = 0xcc;
    tenth.bytes[10] = 0xfb;
    tenth.bytes[11] = 0x3f;
    result = 1;

    sign = parts->exponent & 0x8000;
    exponent = parts->exponent & 0x7fff;
    if (sign)
        output->sign = '-';
    else
        output->sign = ' ';
    if (exponent == 0 && parts->high == 0 && parts->low == 0) {
        output->sign = ' ';
        output->exponent = 0;
        output->length = 1;
        output->digits[0] = '0';
        output->digits[1] = '\0';
        return 1;
    }
    if (exponent == 0x7fff) {
        output->exponent = 1;
        if ((parts->high != 0x80000000U || parts->low != 0) &&
            !(parts->high & 0x40000000U)) {
            result = 0;
            memcpy(output->digits, "1#SNAN", 7);
            output->length = 6;
        } else if (sign && parts->high == 0xc0000000U && parts->low == 0) {
            result = 0;
            memcpy(output->digits, "1#IND", 6);
            output->length = 5;
        } else if (parts->high == 0x80000000U && parts->low == 0) {
            result = 0;
            memcpy(output->digits, "1#INF", 6);
            output->length = 5;
        } else {
            result = 0;
            memcpy(output->digits, "1#QNAN", 7);
            output->length = 6;
        }
        goto finished;
    }
    fraction.extended.exponent = exponent;
    decimal_exponent = (short)((((int)(exponent >> 8) +
        (int)(parts->high >> 24) * 2) * 0x4d + (int)exponent * 0x4d10 -
        0x134312f4) >> 16);
    fraction.extended.extra = 0;
    fraction.extended.low = parts->low;
    fraction.extended.high = parts->high;
    __multtenpow12(&fraction.extended, -(int)decimal_exponent, 1);
    if (fraction.extended.exponent >= 0x3fff) {
        ++decimal_exponent;
        __ld12mul(&fraction.extended, &tenth.extended);
    }
    output->exponent = decimal_exponent;
    if (flags & 1) {
        precision += decimal_exponent;
        if (precision <= 0) {
            output->sign = ' ';
            output->exponent = 0;
            output->length = 1;
            output->digits[0] = '0';
            output->digits[1] = '\0';
            return 1;
        }
    }
    if (precision > 21)
        precision = 21;
    shift = (int)fraction.extended.exponent - 0x3ffe;
    fraction.extended.exponent = 0;
    count = 8;
    do {
        __shl_12(fraction.words);
    } while (--count);
    if (shift < 0) {
        count = (-shift) & 0xff;
        while (count > 0) {
            __shr_12(fraction.words);
            --count;
        }
    }
    /* Character pointers cover the whole output object: a backward scan may
       reach its length byte, but never forms a pointer before the object. */
    first = (char *)output + 4;
    cursor = first;
    count = precision + 1;
    while (count > 0) {
        saved = fraction;
        __shl_12(fraction.words);
        __shl_12(fraction.words);
        __add_12(fraction.words, saved.words);
        __shl_12(fraction.words);
        *cursor++ = (char)(fraction.bytes[11] + '0');
        fraction.bytes[11] = 0;
        --count;
    }
    {
    char rounding = cursor[-1];
    cursor -= 2;
    if (rounding >= '5') {
        while (cursor >= first && *cursor == '9') {
            *cursor = '0';
            --cursor;
        }
        if (cursor < first) {
            ++output->exponent;
            ++cursor;
        }
        ++*cursor;
    } else {
        while (cursor >= first && *cursor == '0')
            --cursor;
        if (cursor < first) {
            output->exponent = 0;
            output->digits[0] = '0';
            output->sign = ' ';
            output->length = 1;
            output->digits[1] = '\0';
            return 1;
        }
    }
    output->length = (char)(cursor - (char *)output - 3);
    output->digits[(int)output->length] = '\0';
    }
finished:
    return result;
}
