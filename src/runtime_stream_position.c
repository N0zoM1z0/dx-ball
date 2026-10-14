#include "runtime_stream_position.h"

DxBallCrtLong dxball_crt_ftell(DxBallCrtStream *argument)
{
    register DxBallCrtStream *stream;
    unsigned int offset;
    DxBallCrtLong position;
    register char *cursor;
    char *end;
    int descriptor;
    unsigned int total;
    stream = argument;
    descriptor = stream->descriptor;
    if (stream->count < 0)
        stream->count = 0;
    if ((position = dxball_crt_seek(descriptor, 0, 1)) < 0)
        return -1;
    if (!(stream->flags & 0x108))
        return (DxBallCrtLong)((unsigned int)position - (unsigned int)stream->count);
    offset = (unsigned int)(stream->cursor - stream->buffer);
    if (stream->flags & 3) {
        if (__pioinfo[descriptor >> 5][descriptor & 31].flags & 0x80)
            for (cursor = stream->buffer; cursor < stream->cursor; ++cursor) {
                if (*cursor == '\n')
                    ++offset;
            }
    } else if (!(stream->flags & 0x80)) {
        errno = 22;
        return -1;
    }
    if (position == 0)
        return (DxBallCrtLong)offset;
    if (stream->flags & 1) {
        if (stream->count == 0)
            offset = 0;
        else {
            total = (unsigned int)stream->count +
                (unsigned int)(stream->cursor - stream->buffer);
            if (__pioinfo[descriptor >> 5][descriptor & 31].flags & 0x80) {
                if (dxball_crt_seek(descriptor, 0, 2) == position) {
                    end = stream->buffer + total;
                    for (cursor = stream->buffer; cursor < end; ++cursor) {
                        if (*cursor == '\n')
                            ++total;
                    }
                    if (stream->flags & 0x2000)
                        ++total;
                } else {
                    dxball_crt_seek(descriptor, position, 0);
                    if (total <= 512 && (stream->flags & 8) && !(stream->flags & 0x400))
                        total = 512;
                    else
                        total = (unsigned int)stream->capacity;
                    if (__pioinfo[descriptor >> 5][descriptor & 31].flags & 4)
                        ++total;
                }
            }
            position = (DxBallCrtLong)((unsigned int)position - total);
        }
    }
    return (DxBallCrtLong)(offset + (unsigned int)position);
}
