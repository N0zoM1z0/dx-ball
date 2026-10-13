#include "runtime_float.h"

/* FUNCTION: DXBALL 0x0041D580 */
int dxball_ascii_to_double(double *result, const char *text)
{
    DxBallExtended12 value;
    const char *end;
    _strgtold12(&value, &end, text, 0, 0, 0, 0);
    return _ld12tod(&value, result);
}

/* FUNCTION: DXBALL 0x0041D5C0 */
int dxball_ascii_to_float(float *result, const char *text)
{
    DxBallExtended12 value;
    const char *end;
    _strgtold12(&value, &end, text, 0, 0, 0, 0);
    return _ld12tof(&value, result);
}

/* FUNCTION: DXBALL 0x0041D7C0 */
int dxball_math_error(DxBallMathException *exception)
{
    (void)exception;
    return 0;
}

/* FUNCTION: DXBALL 0x0041D540 */
int _ld12tod(const DxBallExtended12 *value, double *result)
{
    static DxBallBinaryFormat format = {1024, -1023, 53, 11, 64, 1023};
    return _ld12cvt(value, result, &format);
}

/* FUNCTION: DXBALL 0x0041D560 */
int _ld12tof(const DxBallExtended12 *value, float *result)
{
    static DxBallBinaryFormat format = {128, -127, 24, 8, 32, 127};
    return _ld12cvt(value, result, &format);
}

/* FUNCTION: DXBALL 0x0041D370 */
int _ld12cvt(const DxBallExtended12 *value, void *result,
            const DxBallBinaryFormat *format)
{
    unsigned int mantissa[3], saved[3];
    int exponent, sign, status;
    exponent = (value->exponent & 0x7fff) - 0x3fff;
    sign = value->exponent & 0x8000;
    mantissa[0] = value->high;
    mantissa[1] = value->low;
    mantissa[2] = (unsigned int)value->extra << 16;
    if (exponent == -0x3fff) {
        exponent = 0;
        if (_IsZeroMan(mantissa)) {
            status = 0;
        } else {
            _FillZeroMan(mantissa);
            status = 2;
        }
    } else {
        int minimum;
        _CopyMan(saved, mantissa);
        if (_RoundMan(mantissa, format->precision)) ++exponent;
        minimum = format->min_exponent;
        if (exponent < minimum - format->precision) {
            exponent = 0;
            _FillZeroMan(mantissa);
            status = 2;
        } else if (exponent <= minimum) {
            minimum -= exponent;
            _CopyMan(mantissa, saved);
            _ShrMan(mantissa, minimum);
            _RoundMan(mantissa, format->precision);
            exponent = 0;
            _ShrMan(mantissa, format->exponent_bits + 1);
            status = 2;
        } else if (exponent >= format->max_exponent) {
            _FillZeroMan(mantissa);
            mantissa[0] |= 0x80000000U;
            _ShrMan(mantissa, format->exponent_bits);
            exponent = format->bias + format->max_exponent;
            status = 1;
        } else {
            exponent += format->bias;
            mantissa[0] &= 0x7fffffffU;
            _ShrMan(mantissa, format->exponent_bits);
            status = 0;
        }
    }
    exponent = (int)(((unsigned int)exponent << (31 - format->exponent_bits)) |
                     (sign ? 0x80000000U : 0) | mantissa[0]);
    if (format->destination_bits == 64) {
        ((unsigned int *)result)[1] = (unsigned int)exponent;
        ((unsigned int *)result)[0] = mantissa[1];
    } else if (format->destination_bits == 32) {
        ((unsigned int *)result)[0] = (unsigned int)exponent;
    }
    return status;
}

/* FUNCTION: DXBALL 0x0041D0E0 */
int _ZeroTail(const unsigned int *mantissa, int position)
{
    int word = position / 32;
    int bit = 31 - position % 32;
    if (mantissa[word] & ~(~0U << bit)) return 0;
    for (++word; word < 3; ++word) {
        if (mantissa[word] != 0) return 0;
    }
    return 1;
}

/* FUNCTION: DXBALL 0x0041D150 */
int _IncMan(unsigned int *mantissa, int position)
{
    unsigned int increment = 1;
    int word = position / 32;
    int carry;
    increment <<= 31 - position % 32;
    carry = __addl(mantissa[word], increment, &mantissa[word]);
    for (--word; word >= 0; --word) {
        if (carry == 0) break;
        carry = __addl(mantissa[word], 1, &mantissa[word]);
    }
    return carry;
}

/* FUNCTION: DXBALL 0x0041D1C0 */
int _RoundMan(unsigned int *mantissa, int precision)
{
    int carry = 0;
    int previous_position = precision;
    int round_position = previous_position--;
    int word = round_position / 32;
    int bit = 31 - round_position % 32;
    unsigned int *selected = &mantissa[word];
    if (*selected & (1U << bit)) {
        if (!_ZeroTail(mantissa, round_position + 1))
            carry = _IncMan(mantissa, previous_position);
    }
    *selected &= ~0U << bit;
    for (++word; word < 3; ++word) mantissa[word] = 0;
    return carry;
}

/* FUNCTION: DXBALL 0x0041D270 */
void _CopyMan(unsigned int *destination, const unsigned int *source)
{
    int word;
    for (word = 0; word < 3; ++word) destination[word] = source[word];
}

/* FUNCTION: DXBALL 0x0041D290 */
void _FillZeroMan(unsigned int *mantissa)
{
    int word;
    for (word = 0; word < 3; ++word) mantissa[word] = 0;
}

/* FUNCTION: DXBALL 0x0041D2A0 */
int _IsZeroMan(const unsigned int *mantissa)
{
    int word = 0;
    do {
        if (*mantissa != 0) return 0;
        ++mantissa;
        ++word;
    } while (word < 3);
    return 1;
}

/* FUNCTION: DXBALL 0x0041D2C0 */
void _ShrMan(unsigned int *mantissa, int bits)
{
    int words = bits / 32;
    int partial = bits % 32;
    unsigned int carry = 0;
    unsigned int mask = ~(~0U << partial);
    int word;
    for (word = 0; word < 3; ++word) {
        unsigned int tail = mantissa[word] & mask;
        mantissa[word] >>= partial;
        mantissa[word] |= carry;
        carry = tail << ((32 - partial) & 31);
    }
    for (word = 2; word >= 0; --word) {
        if (word >= words) mantissa[word] = mantissa[word - words];
        else mantissa[word] = 0;
    }
}
