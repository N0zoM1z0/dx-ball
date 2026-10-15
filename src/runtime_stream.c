#include "runtime_stream.h"

/* FUNCTION: DXBALL 0x0041AEF0 */
void dxball_crt_get_buffer(DxBallCrtStream *argument)
{
    register DxBallCrtStream *stream;
    ++dxball_crt_buffer_requests;
    stream = argument;
    if ((stream->buffer = (char *)dxball_runtime_malloc(4096)) != NULL) {
        stream->flags |= 8;
        stream->capacity = 4096;
    } else {
        stream->flags |= 4;
        stream->buffer = (char *)&stream->char_buffer;
        stream->capacity = 2;
    }
    stream->cursor = stream->buffer;
    stream->count = 0;
}

/* FUNCTION: DXBALL 0x00419FA0 */
void dxball_crt_free_buffer(DxBallCrtStream *stream)
{
    if ((stream->flags & 0x83) && (stream->flags & 8)) {
        dxball_heap_release(stream->buffer);
        stream->cursor = NULL;
        stream->flags &= ~0x408;
        stream->buffer = NULL;
        stream->count = 0;
    }
}
