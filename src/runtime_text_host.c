/* Portable service for the recovered score caller's CRT conversion boundary.
   This is a host bridge, not restored vendor runtime source. */
#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>

char *_ultoa(unsigned long value, char *buffer, int radix)
{
    if (radix != 10 || value > 0xffffffffUL) abort();
    sprintf(buffer, "%lu", value);
    return buffer;
}
