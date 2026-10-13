#include "runtime_fp_control.h"

unsigned int dxball_crt_abstract_control_word(unsigned short hardware)
{
    unsigned int result = 0;
    if (hardware & 0x01) result = 0x10;
    if (hardware & 0x04) result |= 0x08;
    if (hardware & 0x08) result |= 0x04;
    if (hardware & 0x10) result |= 0x02;
    if (hardware & 0x20) result |= 0x01;
    if (hardware & 0x02) result |= 0x80000;
    switch (hardware & 0xc00) {
    case 0x400: result |= 0x100; break;
    case 0x800: result |= 0x200; break;
    case 0xc00: result |= 0x300; break;
    }
    switch (hardware & 0x300) {
    case 0: result |= 0x20000; break;
    case 0x200: result |= 0x10000; break;
    }
    if (hardware & 0x1000) result |= 0x40000;
    return result;
}

unsigned short dxball_crt_hardware_control_word(unsigned int abstract_word)
{
    unsigned short result = 0;
    if (abstract_word & 0x10) result = 0x01;
    if (abstract_word & 0x08) result |= 0x04;
    if (abstract_word & 0x04) result |= 0x08;
    if (abstract_word & 0x02) result |= 0x10;
    if (abstract_word & 0x01) result |= 0x20;
    if (abstract_word & 0x80000) result |= 0x02;
    switch (abstract_word & 0x300) {
    case 0x100: result |= 0x400; break;
    case 0x200: result |= 0x800; break;
    case 0x300: result |= 0xc00; break;
    }
    switch (abstract_word & 0x30000) {
    case 0: result |= 0x300; break;
    case 0x10000: result |= 0x200; break;
    }
    if (abstract_word & 0x40000) result |= 0x1000;
    return result;
}

unsigned int _controlfp(unsigned int value, unsigned int mask)
{
    return _control87(value, mask & 0xfff7ffffU);
}
