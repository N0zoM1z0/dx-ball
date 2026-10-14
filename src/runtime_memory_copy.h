#ifndef DXBALL_RUNTIME_MEMORY_COPY_H
#define DXBALL_RUNTIME_MEMORY_COPY_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
/* Real count-byte spans must not overlap, as required by the CRT memcpy API. */
void *dxball_crt_copy_memory(void *destination, const void *source, size_t count);
#ifdef __cplusplus
}
#endif
#endif
