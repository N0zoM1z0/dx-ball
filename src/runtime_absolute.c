#include "runtime_absolute.h"

int dxball_crt_absolute(int value)
{
    return value < 0 ? -value : value;
}
