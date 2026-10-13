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
