#include "runtime_stream_transfer.h"

/* FUNCTION: DXBALL 0x0041A620 */
int dxball_crt_flush_output(int value, DxBallCrtStream *argument)
{
    register DxBallCrtStream *stream;
    register int expected;
    register int written;
    int descriptor;
    stream = argument;
    descriptor = stream->descriptor;
    if ((stream->flags & 0x82) == 0 || (stream->flags & 0x40)) {
        stream->flags |= 0x20;
        return -1;
    }
    if (stream->flags & 1) {
        stream->count = 0;
        if (stream->flags & 0x10) {
            stream->cursor = stream->buffer;
            stream->flags &= ~1;
        } else {
            stream->flags |= 0x20;
            return -1;
        }
    }
    stream->flags |= 2;
    stream->flags &= ~0x10;
    written = expected = stream->count = 0;
    if ((stream->flags & 0x10c) == 0) {
        if (!((stream == &dxball_crt_standard_streams[1] ||
               stream == &dxball_crt_standard_streams[2]) && dxball_crt_isatty(descriptor)))
            dxball_crt_get_buffer(stream);
    }
    if (stream->flags & 0x108) {
        expected = (int)(stream->cursor - stream->buffer);
        stream->cursor = stream->buffer + 1;
        stream->count = stream->capacity - 1;
        if (expected > 0) written = dxball_crt_write(descriptor, stream->buffer, expected);
        else {
            DxBallLowioRecord *record = descriptor != -1
                ? &__pioinfo[descriptor >> 5][descriptor & 31] : &dxball_crt_invalid_io;
            if (record->flags & 0x20) dxball_crt_seek(descriptor, 0, 2);
        }
        *stream->buffer = (char)value;
    } else {
        expected = 1;
        written = dxball_crt_write(descriptor, &value, 1);
    }
    if (written != expected) {
        stream->flags |= 0x20;
        return -1;
    }
    return value & 0xff;
}
