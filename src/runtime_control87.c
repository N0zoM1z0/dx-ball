#include "runtime_fp_exceptions.h"

/* FUNCTION: DXBALL 0x0041CF30 */
unsigned int _control87(unsigned int value, unsigned int mask)
{
    unsigned int control = dxball_crt_abstract_control_word(
        (unsigned short)_ctrlfp(0, 0));
    control = (control & ~mask) | (value & mask);
    /* Even a zero mask canonicalizes and writes the hardware control word. */
    _ctrlfp(dxball_crt_hardware_control_word(control), 0xffff);
    return control;
}
