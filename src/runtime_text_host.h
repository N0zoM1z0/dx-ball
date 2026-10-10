#ifndef DXBALL_RUNTIME_TEXT_HOST_H
#define DXBALL_RUNTIME_TEXT_HOST_H

#if defined(_WIN32)
#include <stdlib.h>
#else
char *_itoa(int value, char *buffer, int radix);
#endif

#endif
