/* Portable decimal services for recovered CRT conversion boundaries.
   This is a host bridge, not restored vendor runtime source. */
#include "runtime.h"
#include "runtime_text_host.h"
#include <stdio.h>
#include <stdlib.h>

char *_ultoa(unsigned long value, char *buffer, int radix)
{
    if (radix != 10 || value > 0xffffffffUL) abort();
    sprintf(buffer, "%lu", value);
    return buffer;
}

char *_itoa(int value, char *buffer, int radix)
{
    if (radix != 10) abort();
    sprintf(buffer, "%d", value);
    return buffer;
}
