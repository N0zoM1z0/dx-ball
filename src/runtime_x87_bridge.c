#include "runtime_x87_bridge.h"
#include <string.h>

void dxball_crt_x87_exception_bridge(int operation, DxBallMathException *exception,
    const unsigned short *control_word)
{
    unsigned int control = *control_word;
    unsigned int flags;
    int handled;
    switch (exception->type) {
    case 1:
    case 5: flags = 8; break;
    case 2: flags = 4; break;
    case 3: flags = 0x11; break;
    case 4: flags = 0x12; break;
    case 7:
        exception->type = 1;
        /* fall through */
    default: flags = 0; break;
    case 8: flags = 0x10; break;
    }
    if (flags && !dxball_crt_handle_float_exception(flags, &exception->retval, control)) {
        DxBallIeeeRecord record;
        if (operation == 0x10 || operation == 0x16 || operation == 0x1d) {
            record.operand2.valid = 1;
            record.operand2.format = 1;
            /* The original copies integer words, without an x87 value load. */
            memcpy(&record.operand2.value.integer64[1],
                (const unsigned char *)&exception->arg2 + 4, 4);
            memcpy(&record.operand2.value.integer64[0], &exception->arg2, 4);
        } else {
            record.operand2.valid = 0;
        }
        dxball_crt_raise_float_exception(&record, &control, flags, operation,
            &exception->arg1, &exception->retval);
    }
    _ctrlfp(control, 0xffff);
    handled = 0;
    if (exception->type != 8 && _matherr_flag == 0)
        handled = dxball_math_error(exception);
    if (!handled)
        dxball_crt_set_math_errno(exception->type);
}
