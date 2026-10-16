#ifndef DXBALL_RUNTIME_MEMORY_COPY_H
#define DXBALL_RUNTIME_MEMORY_COPY_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
/* Ordinary backed count-byte spans; both original entries support overlap. */
void *dxball_crt_copy_memory(void *destination, const void *source, size_t count);
void *dxball_crt_memcpy(void *destination, const void *source, size_t count);
#ifdef __cplusplus
}
#endif
#endif
