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

char *dxball_crt_math_function_name(int function)
{
    struct Name { int function; char *name; };
    /* The original catalog is writable: matherr receives a borrowed char *. */
    static char exp_text[] = "exp", pow_text[] = "pow", log_text[] = "log";
    static char log10_text[] = "log10", sinh_text[] = "sinh", cosh_text[] = "cosh";
    static char tanh_text[] = "tanh", asin_text[] = "asin", acos_text[] = "acos";
    static char atan_text[] = "atan", atan2_text[] = "atan2", sqrt_text[] = "sqrt";
    static char sin_text[] = "sin", cos_text[] = "cos", tan_text[] = "tan";
    static char ceil_text[] = "ceil", floor_text[] = "floor", fabs_text[] = "fabs";
    static char modf_text[] = "modf", ldexp_text[] = "ldexp", cabs_text[] = "_cabs";
    static char hypot_text[] = "_hypot", fmod_text[] = "fmod", frexp_text[] = "frexp";
    static char y0_text[] = "_y0", y1_text[] = "_y1", yn_text[] = "_yn";
    static Name names[] = {
        {20, exp_text}, {29, pow_text}, {26, log_text}, {27, log10_text},
        {31, sinh_text}, {19, cosh_text}, {33, tanh_text}, {14, asin_text},
        {13, acos_text}, {15, atan_text}, {16, atan2_text}, {5, sqrt_text},
        {30, sin_text}, {18, cos_text}, {32, tan_text}, {12, ceil_text},
        {11, floor_text}, {21, fabs_text}, {28, modf_text}, {25, ldexp_text},
        {17, cabs_text}, {24, hypot_text}, {22, fmod_text}, {23, frexp_text},
        {34, y0_text}, {35, y1_text}, {36, yn_text}
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
