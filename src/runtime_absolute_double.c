#include "runtime_absolute_double.h"
#include "runtime_fp_exceptions.h"

#if defined(__GNUC__)
typedef unsigned short DxBallAbsoluteHalf __attribute__((__may_alias__));
typedef struct __attribute__((__may_alias__)) DxBallAbsoluteBits {
#else
typedef unsigned short DxBallAbsoluteHalf;
typedef struct DxBallAbsoluteBits {
#endif
    unsigned int low, high;
} DxBallAbsoluteBits;

double dxball_crt_absolute_double(double value)
{
    union {
        double value;
        DxBallAbsoluteBits bits;
    } result;
    const DxBallAbsoluteBits *input = (const DxBallAbsoluteBits *)(const void *)&value;
    unsigned int control = _ctrlfp(0x133f, 0xffff);
    if ((((const DxBallAbsoluteHalf *)(const void *)&value)[3] & 0x7ff0) == 0x7ff0) {
        int special = dxball_crt_float_special_type(value);
        switch (special) {
        case 1:
            _ctrlfp(control, 0xffff);
            return value;
        case 2:
            _ctrlfp(control, 0xffff);
            return -value;
        case 3:
            return dxball_crt_handle_single_quiet_nan(21, value, control);
        default:
            return dxball_crt_handle_single_exception(8, 21, value, 1.0 + value, control);
        }
    }
    /* Preserve object bits and defer the x87 result load until control restore. */
    result.bits.high = input->high & 0x7fffffffU;
    result.bits.low = input->low;
    _ctrlfp(control, 0xffff);
    return result.value;
}
