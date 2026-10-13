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
