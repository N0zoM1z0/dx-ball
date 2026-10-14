#include "runtime_fp_exceptions.h"

extern "C" { extern int errno; }

#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallMathDoubleBits {
#else
typedef struct DxBallMathDoubleBits {
#endif
    unsigned int low, high;
} DxBallMathDoubleBits;

double dxball_crt_user_math_error(int error, int operation, double argument1,
                                 double argument2, double result, unsigned int control)
{
    DxBallMathException exception;
    exception.name = dxball_crt_math_function_name(operation);
    if (exception.name) {
        exception.type = error;
        /* The callback receives the original representations, not an early
           floating conversion that might quiet a signaling NaN. */
        DxBallMathDoubleBits *first = (DxBallMathDoubleBits *)(void *)&exception.arg1;
        DxBallMathDoubleBits *second = (DxBallMathDoubleBits *)(void *)&exception.arg2;
        DxBallMathDoubleBits *returned = (DxBallMathDoubleBits *)(void *)&exception.retval;
        const DxBallMathDoubleBits *first_input = (const DxBallMathDoubleBits *)(const void *)&argument1;
        const DxBallMathDoubleBits *second_input = (const DxBallMathDoubleBits *)(const void *)&argument2;
        const DxBallMathDoubleBits *result_input = (const DxBallMathDoubleBits *)(const void *)&result;
        *first = *first_input;
        *second = *second_input;
        *returned = *result_input;
        _ctrlfp(control, 0xffff);
        if (!dxball_math_error(&exception))
            dxball_crt_set_math_errno(error);
        return exception.retval;
    }
    _ctrlfp(control, 0xffff);
    dxball_crt_set_math_errno(error);
    return result;
}

double dxball_crt_handle_single_exception(unsigned int flags, int operation,
                                         double argument, double result, unsigned int control)
{
    DxBallIeeeRecord record;
    int error;
    if (!dxball_crt_handle_float_exception(flags, &result, control)) {
        /* Only this named bit is assigned here; the raising boundary fills
           the other named fields. Unobserved padding is not invented state. */
        record.operand2.valid = 0;
        dxball_crt_raise_float_exception(&record, &control, flags, operation, &argument, &result);
    }
    error = dxball_crt_math_error_code(flags);
    if (!_matherr_flag && error)
        return dxball_crt_user_math_error(error, operation, argument, 0.0, result, control);
    dxball_crt_set_math_errno(error);
    _ctrlfp(control, 0xffff);
    return result;
}

double dxball_crt_handle_single_quiet_nan(int operation, double argument, unsigned int control)
{
    if (!_matherr_flag)
        return dxball_crt_user_math_error(1, operation, argument, 0.0, argument, control);
    errno = 33;
    _ctrlfp(control, 0xffff);
    return argument;
}
