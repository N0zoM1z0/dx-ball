#include "runtime_fp_exceptions.h"
#include <string.h>

extern "C" { extern int errno; }

typedef struct DxBallMathDoubleStorage {
    double value;
} DxBallMathDoubleStorage;

double dxball_crt_user_math_error(int error, int operation, double argument1,
                                 double argument2, double result, unsigned int control)
{
    DxBallMathException exception;
    exception.name = dxball_crt_math_function_name(operation);
    if (exception.name) {
        exception.type = error;
        *(DxBallMathDoubleStorage *)(void *)&exception.arg1 =
            *(const DxBallMathDoubleStorage *)(const void *)&argument1;
        *(DxBallMathDoubleStorage *)(void *)&exception.arg2 =
            *(const DxBallMathDoubleStorage *)(const void *)&argument2;
        memcpy(&exception.retval, &result, sizeof(unsigned int));
        memcpy((char *)&exception.retval + sizeof(unsigned int),
               (const char *)&result + sizeof(unsigned int), sizeof(unsigned int));
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
