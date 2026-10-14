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

/* FUNCTION: DXBALL 0x0041A030 */
int dxball_crt_flush_buffer(DxBallCrtStream *argument)
{
    register DxBallCrtStream *stream;
    register int status = 0;
    register int bytes;
    stream = argument;
    if ((stream->flags & 3) == 2 && (stream->flags & 0x108) &&
        (bytes = (int)(stream->cursor - stream->buffer)) > 0) {
        if (dxball_crt_write(stream->descriptor, stream->buffer,
                             (unsigned int)bytes) == bytes) {
            if (stream->flags & 0x80) stream->flags &= ~2;
        } else {
            stream->flags |= 0x20;
            status = -1;
        }
    }
    stream->cursor = stream->buffer;
    stream->count = 0;
    return status;
}

/* FUNCTION: DXBALL 0x00419FE0 */
int dxball_crt_fflush(DxBallCrtStream *stream)
{
    if (stream == NULL) return dxball_crt_flush_all(0);
    if (dxball_crt_flush_buffer(stream)) return -1;
    if (stream->flags & 0x4000) {
        return dxball_crt_commit(stream->descriptor) == 0 ? 0 : -1;
    }
    return 0;
}

/* FUNCTION: DXBALL 0x0041A0B0 */
int dxball_crt_flush_all(int mode)
{
    int count = 0;
    int index = 0;
    int status = 0;
    do {
        if (dxball_crt_streams[index] != NULL && (dxball_crt_streams[index]->flags & 0x83)) {
            if (mode == 1) {
                if (dxball_crt_fflush(dxball_crt_streams[index]) != -1) ++count;
            } else if (mode == 0 && (dxball_crt_streams[index]->flags & 2)) {
                if (dxball_crt_fflush(dxball_crt_streams[index]) == -1) status = -1;
            }
        }
        ++index;
    } while (index < 512);
    return mode == 1 ? count : status;
}

/* FUNCTION: DXBALL 0x0041A0A0 */
int dxball_crt_flushall(void)
{
    return dxball_crt_flush_all(1);
}
