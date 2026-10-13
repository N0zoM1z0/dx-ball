#ifndef DXBALL_RUNTIME_STREAM_H
#define DXBALL_RUNTIME_STREAM_H

#include "allocator.h"

/* The pinned VC4 _iobuf layout. Host pointers retain their native width;
   this is not a host-libc FILE and is not passed to host stdio. */
typedef struct DxBallCrtStream {
    char *cursor;
    int count;
    char *buffer;
    int flags;
    int descriptor;
    int char_buffer;
    int capacity;
    char *temporary_name;
} DxBallCrtStream;

#ifdef __cplusplus
extern "C" {
#endif

extern int dxball_crt_buffer_requests;
extern DxBallCrtStream **dxball_crt_streams;

/* Original lower-I/O and stream traversal dependencies, not host stdio. */
int dxball_crt_write(int descriptor, const void *buffer, unsigned int bytes);
int dxball_crt_commit(int descriptor);
int dxball_crt_flush_all(int mode);
int dxball_crt_flushall(void);

void dxball_crt_get_buffer(DxBallCrtStream *stream);
void dxball_crt_free_buffer(DxBallCrtStream *stream);
int dxball_crt_flush_buffer(DxBallCrtStream *stream);
int dxball_crt_fflush(DxBallCrtStream *stream);

#ifdef __cplusplus
}
#endif
#endif
