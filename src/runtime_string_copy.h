#ifndef DXBALL_RUNTIME_STRING_COPY_H
#define DXBALL_RUNTIME_STRING_COPY_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
/* Real source/destination spans are nonoverlapping, as in the original CRT. */
char *dxball_crt_strncpy(char *destination, const char *source, size_t count);
char *dxball_crt_strncat(char *destination, const char *source, size_t count);
#ifdef __cplusplus
}
#endif
#endif
