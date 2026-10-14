#ifndef DXBALL_RUNTIME_STRING_LENGTH_H
#define DXBALL_RUNTIME_STRING_LENGTH_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
/* Preserves the original physical read footprint: aligned words through the
   word containing NUL must be readable, including bytes following that NUL. */
size_t dxball_crt_string_length(const char *text);
#ifdef __cplusplus
}
#endif
#endif
