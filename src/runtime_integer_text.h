#ifndef DXBALL_RUNTIME_INTEGER_TEXT_H
#define DXBALL_RUNTIME_INTEGER_TEXT_H

#include "state_types.h"

/* VC4 unsigned long is32 bits; retain that value domain on the native host. */
#if defined(_WIN32)
typedef unsigned long DxBallIntegerTextWord;
#else
typedef DxBallUInt DxBallIntegerTextWord;
#endif

#ifdef __cplusplus
extern "C" {
#endif
char *dxball_crt_itoa(int value, char *buffer, int radix);
char *dxball_crt_ultoa(DxBallIntegerTextWord value, char *buffer, int radix);
#ifdef __cplusplus
}
#endif
#endif
