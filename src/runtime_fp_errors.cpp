#include "runtime_fp_control.h"

extern "C" { extern int errno; }

void dxball_crt_set_math_errno(int error)
{
    switch (error) {
    case 1: errno = 33; break;
    case 2:
    case 3: errno = 34; break;
    }
}

int dxball_crt_math_error_code(unsigned int flags)
{
    if (flags & 0x20) return 5;
    if (flags & 0x08) return 1;
    if (flags & 0x04) return 2;
    if (flags & 0x01) return 3;
    return (flags & 0x02) * 2;
}

const char *dxball_crt_math_function_name(int function)
{
    struct Name { int function; const char *name; };
    static Name names[] = {
        {20, "exp"}, {29, "pow"}, {26, "log"}, {27, "log10"},
        {31, "sinh"}, {19, "cosh"}, {33, "tanh"}, {14, "asin"},
        {13, "acos"}, {15, "atan"}, {16, "atan2"}, {5, "sqrt"},
        {30, "sin"}, {18, "cos"}, {32, "tan"}, {12, "ceil"},
        {11, "floor"}, {21, "fabs"}, {28, "modf"}, {25, "ldexp"},
        {17, "_cabs"}, {24, "_hypot"}, {22, "fmod"}, {23, "frexp"},
        {34, "_y0"}, {35, "_y1"}, {36, "_yn"}
    };
    int index = 0;
    Name *entry = names;
    do {
        if (entry->function == function)
            return names[index].name;
        ++entry;
        ++index;
    } while (entry < names + sizeof(names) / sizeof(names[0]));
    return 0;
}
