#include "runtime_stream_position.h"

DxBallCrtLong dxball_crt_ftell(DxBallCrtStream *stream)
{
    int descriptor = stream->descriptor;
    DxBallCrtLong position;
    unsigned int flags, offset, adjusted, total, index;
    char *cursor, *end;
    DxBallLowioRecord **slot;
    if (stream->count < 0)
        stream->count = 0;
    position = dxball_crt_seek(descriptor, 0, 1);
    if (position < 0)
        return -1;
    flags = (unsigned int)stream->flags;
    if (!(flags & 0x108))
        return (DxBallCrtLong)((unsigned int)position - (unsigned int)stream->count);
    offset = (unsigned int)((size_t)stream->cursor - (size_t)stream->buffer);
    adjusted = offset;
    cursor = stream->buffer;
    if (flags & 3) {
        if (__pioinfo[descriptor >> 5][descriptor & 31].flags & 0x80)
            while (cursor < stream->cursor) {
                if (*cursor++ == '\n')
                    ++adjusted;
            }
    } else if (!(flags & 0x80)) {
        errno = 22;
        return -1;
    }
    if (position == 0)
        return (DxBallCrtLong)adjusted;
    if (flags & 1) {
        if (stream->count == 0)
            return position;
        total = offset + (unsigned int)stream->count;
        slot = &__pioinfo[descriptor >> 5];
        index = (unsigned int)descriptor & 31;
        if ((*slot)[index].flags & 0x80) {
            if (dxball_crt_seek(descriptor, 0, 2) == position) {
                cursor = stream->buffer;
                end = cursor + total;
                while (cursor < end) {
                    if (*cursor++ == '\n')
                        ++total;
                }
                if (stream->flags & 0x2000)
                    ++total;
            } else {
                dxball_crt_seek(descriptor, position, 0);
                if (total > 512 || !(stream->flags & 8) || (stream->flags & 0x400))
                    total = (unsigned int)stream->capacity;
                else
                    total = 512;
                if ((*slot)[index].flags & 4)
                    ++total;
            }
        }
        position = (DxBallCrtLong)((unsigned int)position - total);
    }
    return (DxBallCrtLong)(adjusted + (unsigned int)position);
}
